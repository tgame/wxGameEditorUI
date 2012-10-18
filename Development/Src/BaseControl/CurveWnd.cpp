#include "stdafx.h"
#include "CurveWnd.h"
#include "CurveWndProvider.h"

#include "wx/dcbuffer.h"


/////////////////////////////////////////////////////////////////////////////
// CCurveWnd
CCurveWnd::CCurveWnd( wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style ) 
:wxPanel( parent, id, pos, size, style )
,m_callback(0)
,m_pCurve(0)
{
	SetBackgroundStyle(wxBG_STYLE_PAINT);
	m_hitCurveCursor = new wxCursor("ArrWhite.cur");//AfxGetApp()->LoadCursor(IDC_ARRWHITE);
	m_hitKnotCursor = new wxCursor("ArrBlck.cur");//AfxGetApp()->LoadCursor(IDC_ARRBLCK);
	m_movingCursor = new wxCursor("ArrCross.cur");//AfxGetApp()->LoadCursor(IDC_ARRBLCKCROSS);

	m_hitCurveCursor=0;
	m_hitKnotCursor=0;
	m_movingCursor=0;
	//Initialise members
	m_bTracking = false;
	m_nActiveKnot = - 1;
	m_iKnotRadius = 5;
	m_pHitInfo = new CurveHitInfo;
	// Connect Events
	this->Connect( wxEVT_ERASE_BACKGROUND, wxEraseEventHandler( CCurveWnd::OnEraseBkgnd ) );
	this->Connect( wxEVT_KEY_DOWN, wxKeyEventHandler( CCurveWnd::OnKeyDown ) );
	this->Connect( wxEVT_LEFT_DCLICK, wxMouseEventHandler( CCurveWnd::OnLButtonDblClk ) );
	this->Connect( wxEVT_LEFT_DOWN, wxMouseEventHandler( CCurveWnd::OnLButtonDown ) );
	this->Connect( wxEVT_LEFT_UP, wxMouseEventHandler( CCurveWnd::OnLButtonUp ) );
	this->Connect( wxEVT_RIGHT_DOWN, wxMouseEventHandler( CCurveWnd::OnMouseMove ) );
	this->Connect( wxEVT_RIGHT_UP, wxMouseEventHandler( CCurveWnd::OnMouseMove ) );
	this->Connect( wxEVT_MOTION, wxMouseEventHandler( CCurveWnd::OnMouseMove ) );
	this->Connect( wxEVT_PAINT, wxPaintEventHandler( CCurveWnd::OnPaint ) );
	this->Connect( wxEVT_SIZE, wxSizeEventHandler( CCurveWnd::OnSize ) );
}

CCurveWnd::~CCurveWnd()
{
	delete m_pHitInfo;
	this->Disconnect( wxEVT_ERASE_BACKGROUND, wxEraseEventHandler( CCurveWnd::OnEraseBkgnd ) );
	this->Disconnect( wxEVT_KEY_DOWN, wxKeyEventHandler( CCurveWnd::OnKeyDown ) );
	this->Disconnect( wxEVT_LEFT_DCLICK, wxMouseEventHandler( CCurveWnd::OnLButtonDblClk ) );
	this->Disconnect( wxEVT_LEFT_DOWN, wxMouseEventHandler( CCurveWnd::OnLButtonDown ) );
	this->Disconnect( wxEVT_LEFT_UP, wxMouseEventHandler( CCurveWnd::OnLButtonUp ) );
	this->Disconnect( wxEVT_RIGHT_DOWN, wxMouseEventHandler( CCurveWnd::OnMouseMove ) );
	this->Disconnect( wxEVT_RIGHT_UP, wxMouseEventHandler( CCurveWnd::OnMouseMove ) );
	this->Disconnect( wxEVT_MOTION, wxMouseEventHandler( CCurveWnd::OnMouseMove ) );
	this->Disconnect( wxEVT_PAINT, wxPaintEventHandler( CCurveWnd::OnPaint ) );
	this->Disconnect( wxEVT_SIZE, wxSizeEventHandler( CCurveWnd::OnSize ) );
}

/////////////////////////////////////////////////////////////////////////////
// CCurveWnd initialisation										       //
/////////////////////////////////////////////////////////////////////////////

void CCurveWnd::OnEraseBkgnd( wxEraseEvent& event )
{
	event.Skip();
}
void CCurveWnd::OnKeyDown( wxKeyEvent& event )
{	
	bool bHandeldMsg = false;

	if(m_nActiveKnot != -1)
	{		
		switch(event.GetKeyCode())
		{
		case WXK_DELETE :
			if(m_pCurve)
			{
				m_pCurve->RemoveKnot(m_nActiveKnot);
				m_nActiveKnot = -1;	
				bHandeldMsg = true;
			} break;
		case WXK_UP	:
			if(m_pCurve)
			{
				CurveWndKnot* pKnot = m_pCurve->GetKnot(m_nActiveKnot);

				CurveWndKnotPoint pt;
				pKnot->GetPoint(&pt);
				pt.y -= 1;

				m_pCurve->MoveKnot(pt, m_nActiveKnot);
				bHandeldMsg = true;
			} break;
		case WXK_DOWN :
			if(m_pCurve)
			{		
				CurveWndKnot* pKnot = m_pCurve->GetKnot(m_nActiveKnot);

				CurveWndKnotPoint pt;
				pKnot->GetPoint(&pt);
				pt.y += 1;

				m_pCurve->MoveKnot(pt, m_nActiveKnot);
				bHandeldMsg = true;
			} break;
		case WXK_LEFT :
			if(m_pCurve)
			{
				CurveWndKnot* pKnot = m_pCurve->GetKnot(m_nActiveKnot);

				CurveWndKnotPoint pt;
				pKnot->GetPoint(&pt);
				pt.x -= 1;

				m_pCurve->MoveKnot(pt, m_nActiveKnot);
				bHandeldMsg = true;
			} break;
		case WXK_RIGHT :
			if(m_pCurve)
			{
				CurveWndKnot* pKnot = m_pCurve->GetKnot(m_nActiveKnot);

				CurveWndKnotPoint pt;
				pKnot->GetPoint(&pt);
				pt.x += 1;

				m_pCurve->MoveKnot(pt, m_nActiveKnot);
				bHandeldMsg = true;
			} break;

		default :
			break; //do nothing
		}
		event.Skip(bHandeldMsg);
		Refresh();
	}
}
void CCurveWnd::OnLButtonDblClk( wxMouseEvent& event )
{
	long x=0;
	long y=0;
	event.GetPosition(&x,&y);
	wxPoint point(x,y);
	switch(m_pHitInfo->wHitCode)
	{
	case CurveHitInfo::enHitCanvas : 
		if(m_pCurve)
		{	
			int iIndex = m_pCurve->InsertKnot(point);
			SetActiveKnot(iIndex);
			Refresh();
		} break;
	default : 
		break;//do nothing
	}
}
void CCurveWnd::OnLButtonDown( wxMouseEvent& event )
{
	long x=0;
	long y=0;
	event.GetPosition(&x,&y);
	wxPoint point(x,y);
	if(m_bTracking)
		return;
	SetFocus();
	switch(m_pHitInfo->wHitCode)
	{
	case CurveHitInfo::enHitKnot :
		{
			StartTracking();
			SetActiveKnot(m_pHitInfo->nKnotIndex);
		} break;
	case CurveHitInfo::enHitCanvas :
		{
			SetActiveKnot(-1);
		}
	default :		break; //do nothing
	}
}
void CCurveWnd::OnLButtonUp( wxMouseEvent& event )
{
	long x=0;
	long y=0;
	event.GetPosition(&x,&y);
	if(m_bTracking)
		StopTracking();
}
void CCurveWnd::OnMouseMove( wxMouseEvent& event )
{
	long x=0;
	long y=0;
	event.GetPosition(&x,&y);
	if(GetCapture() != this)
		StopTracking();
	wxPoint point(x,y);
	if(m_bTracking)
		TrackKnot(point);
	//////////////////////////////////////////////////////////////////////////
	//set mouse cursor
	bool b = FALSE;

	point = wxGetMousePosition();
	ScreenToClient(point);

	switch(HitTest(point)) 
	{
	case CurveHitInfo::enHitCurve :
		{
			SetCursor(*m_hitCurveCursor);
			b = TRUE;;
		} break;
	case CurveHitInfo::enHitKnot :
		{
			SetCursor(*m_hitKnotCursor);
			b = TRUE;
		} break;
	default : //do nothing
		break;
	}

	event.Skip(b);
}
void CCurveWnd::OnPaint( wxPaintEvent& event )
{
	wxAutoBufferedPaintDC dc(this);
	/*

	wxPaintDC dc(this);
	//*/
	//MemDC.SetBackgroundMode(wxSOLID);
	wxBrush black(wxColour(0,0,0));
	dc.SetBackground(black);
	//MemDC.SetBrush(black);
	dc.Clear();
	DrawWindow(&dc);
}
void CCurveWnd::OnRButtonDown( wxMouseEvent& event )
{
	
}
void CCurveWnd::OnRButtonUp( wxMouseEvent& event )
{
	
}
void CCurveWnd::OnSize( wxSizeEvent& event )
{
	CurveWndRect rcCurveWnd;
	wxRect rcClient = this->GetClientRect();
	rcClient.Deflate(1,1);
	rcCurveWnd.left=rcClient.x;
	rcCurveWnd.right=rcClient.x+rcClient.width;
	rcCurveWnd.top = rcClient.y;
	rcCurveWnd.bottom=rcClient.y+rcClient.height;
	if (m_pCurve)
	{
		m_pCurve->ChangeViewport(&rcCurveWnd);
	}
}



/////////////////////////////////////////////////////////////////////////////
// CCurveWnd drawing										               //
/////////////////////////////////////////////////////////////////////////////
void CCurveWnd::DrawWindow(wxDC* pDC)
{
	//*
	DrawGrid(pDC);
	DrawKnots(pDC);
	DrawCurve(pDC);
	//*/
	/*
	wxRect rcClient=GetClientRect();
	int cx = rcClient.GetWidth();
	int cy = rcClient.GetHeight();

	wxMemoryDC MemDC;
	//Draw BackGround
	wxBitmap bitmapBkGnd;;
	bitmapBkGnd.Create(cx,cy);
	//bitmapBkGnd.CreateCompatibleBitmap(pDC, cx, cy);
	MemDC.SelectObject(bitmapBkGnd);
	
	//Draw Grid
	DrawGrid(&MemDC);
	DrawKnots(&MemDC);
	DrawCurve(&MemDC);
	
	pDC->Blit (wxPoint(0, 0),wxSize(cx, cy), &MemDC, wxPoint(cx, cy));
	//*/
}

void CCurveWnd::DrawGrid(wxDC* pDC)
{
	wxRect rcClient=GetClientRect();
	int cx = rcClient.GetWidth();
	int cy = rcClient.GetHeight();
	wxColour penColor(75,75,75);
	wxPen pen(penColor);
	pDC->SetPen(pen);
	
	//Draw Vertical Grid Lines
	for(int y = 1; y < 10; y++) {
		pDC->DrawLine(wxPoint(y*cx/10, cy),wxPoint(y*cx/10, 0));
	}

	//Draw Horizontal Grid Lines
	for(int x = 1; x < 10; x++) {
		wxPoint p1(0, x*cy/10);
		wxPoint p2(cx, x*cy/10);
		pDC->DrawLine(p1,p2);
	}

}

void CCurveWnd::DrawCurve(wxDC* pDC)
{
	if (!m_pCurve)
	{
		return;
	}
	wxRect rcClient=GetClientRect();
	int cx = rcClient.GetWidth();
	int cy = rcClient.GetHeight();

	wxColour penColor(255,255,255);
	wxPen pen(penColor);
	pDC->SetPen(pen);
	
	int iY=0;
	iY = m_pCurve->GetCurveY(1);	//Get Starting point
	wxPoint p1(1,iY);

	for(int iX = 1; iX < cx; iX++)
	{
		int iYnext = m_pCurve->GetCurveY(iX);
		wxPoint p2(iX - 1, iYnext);
		pDC->DrawLine(p1,p2);
		p1=p2;
		iY = iYnext; //Set next starting point
	}
}

void CCurveWnd::DrawKnots(wxDC* pDC)
{
	if (!m_pCurve)
	{
		return;
	}
	// create and select a thin, white pen
	wxColour penColor(255,255,255);
	wxPen pen(penColor);
	pDC->SetPen(pen);

	wxColour cyColor(0,0,0);
	wxBrush blackBrush(cyColor);
	cyColor.Set(255,255,255);
	wxBrush whiteBrush(cyColor);
	//Draw Knots
	for(int pos = 0; pos < m_pCurve->GetKnotCount(); pos++)
    {
		// Create and select a solid white brush
		CurveWndKnot* pKnot =	m_pCurve->GetKnot(pos);
		//Set knot brush color
		wxBrush* brush=m_nActiveKnot == pos ? &whiteBrush : &blackBrush;
		pDC->SetBrush(*brush);
		//Draw knot
		wxRect rc(pKnot->x-m_iKnotRadius,pKnot->y-m_iKnotRadius,m_iKnotRadius*2,m_iKnotRadius*2);
		pDC->DrawEllipse(rc);
	}
}



/////////////////////////////////////////////////////////////////////////////
// CCurveWnd Message Handlers										       //
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
//Mouse Message Handlers

/////////////////////////////////////////////////////////////////////////////
// CCurveWnd Functions												       //
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
//Active Knot Acces Functions

void CCurveWnd::SetActiveKnot(unsigned int nIndex)
{	
	//Deactivate Old Knot
	if(m_nActiveKnot != - 1) {

		nIndex <= m_nActiveKnot ? 
			m_nActiveKnot += 1 : m_nActiveKnot = m_nActiveKnot;

		CurveWndKnot* pKnotOld =
			m_pCurve->GetKnot(m_nActiveKnot);
		pKnotOld->SetData(TRUE);
	}

	//Activate New Knot
	if(nIndex != -1) {
		
		CurveWndKnot* pKnotNew = 
			m_pCurve->GetKnot(nIndex);
		pKnotNew->SetData(FALSE);
	}
	
	m_nActiveKnot = nIndex;
	if (m_callback)
	{
		m_callback->OnSelectKnot(this,m_nActiveKnot,m_pCurve);
	}
	Refresh();
}

unsigned int CCurveWnd::GetActiveKnot() { return m_nActiveKnot;}

/////////////////////////////////////////////////////////////////////////////
//Curve Object Functions

void CCurveWnd::SetCurveObject(CurveWndProvider* pObject, bool bRedraw)
{
	if(pObject != m_pCurve) 
	{
		m_nActiveKnot = -1; //Reset active knot
		m_pCurve = pObject; //Set Curve Object pointer
	}
	if(m_pCurve)
	{
		CurveWndRect rcCurveWnd;
		wxRect rcClient = this->GetClientRect();
		rcClient.Deflate(1,1);
		rcCurveWnd.left=rcClient.x;
		rcCurveWnd.right=rcClient.x+rcClient.width;
		rcCurveWnd.top = rcClient.y;
		rcCurveWnd.bottom=rcClient.y+rcClient.height;
		if (m_pCurve)
		{
			m_pCurve->ChangeViewport(&rcCurveWnd);
		}
	}
	if(bRedraw)
		Refresh();
}

CurveWndProvider* CCurveWnd::GetCurveObject(){ return m_pCurve;}

/////////////////////////////////////////////////////////////////////////////
//Cursor Message Handlers
/*
bool CCurveWnd::OnSetCursor(CWnd* pWnd, unsigned int nHitTest, unsigned int message) 
{
	
}
*/
/////////////////////////////////////////////////////////////////////////////
//Keyboard Message Handlers


/////////////////////////////////////////////////////////////////////////////
// CCurveWnd functions										               //
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CCurveWnd implementation										       //
/////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
//Hit Testing

WORD CCurveWnd::HitTest(wxPoint point)
{		
	HitTest(point, m_pHitInfo,m_pCurve);
	return m_pHitInfo->wHitCode;
}

void CCurveWnd::HitTest(wxPoint ptHit, CurveHitInfo* pHitInfo,CurveWndProvider* pObject)
{
	unsigned int  iIndex;	//Index of Knot			HTKNOT
	wxPoint ptCurve;	//Exact point on curve	HTCURVE

	pHitInfo->ptHit = ptHit; //Set cursor position

	if(PtOnKnot(ptHit, 3, &iIndex,pObject))		
	{
		pHitInfo->wHitCode   = CurveHitInfo::enHitKnot;
		pHitInfo->nKnotIndex = iIndex;
	}

	else if(PtOnCurve(ptHit, 0, &ptCurve,pObject))	
	{
		pHitInfo->wHitCode = CurveHitInfo::enHitCurve;
		pHitInfo->ptCurve  = ptCurve;
	}
	else pHitInfo->wHitCode = CurveHitInfo::enHitCanvas;
}


bool CCurveWnd::PtOnCurve(wxPoint ptHit, unsigned int nInterval, wxPoint* pt,CurveWndProvider* pObject)
{
	if (!pObject)
	{
		return false;
	}
	if(pObject->GetKnotCount() == -1)
		return FALSE;	//Curve Has No Knots

	int iY, iX;

	bool b = FALSE; 

	for(int i = 0; i<5; i++)
	{
		int iXdiff;

		if(i != 0) 
			(i%2 != 0) ? iXdiff = (+1)*((i+1)/2) : iXdiff = (-1)*(i/2);
		else iXdiff = 0;

		iX = ptHit.x + iXdiff;
		iY = pObject->GetCurveY(iX);

		if((iY > ptHit.y - 2) && (iY < ptHit.y + 2)) {
			b = TRUE;
			break;
		}
	}

	//Return curve exact point
	if(b) {	
		pt->x = iX;
		pt->y = iY;
	}

	return b;
}

bool CCurveWnd::PtOnKnot(wxPoint ptHit, unsigned int nInterval, unsigned int* nIndex,CurveWndProvider* pObject)
{
	if(!pObject)
	{
		return false;
	}
	if(pObject->GetKnotCount() == -1)
		return FALSE;	//Curve Has No Knots

	int iIndex = - 1;

	for(int pos = 0; pos < pObject->GetKnotCount(); pos++)
	{
		CurveWndKnot* pKnot = pObject->GetKnot(pos);

		if (ptHit.x>pKnot->x - nInterval
			&&ptHit.x<pKnot->x + nInterval
			&&ptHit.y>pKnot->y - nInterval
			&&ptHit.y<pKnot->y + nInterval)
		{
			iIndex = pos;
			break;
		}
	}

	if(iIndex != -1) {
		*nIndex = iIndex; 
		return TRUE;
	}
	else return FALSE;
}	

///////////////////////////////////////////////////////////////////////////////
//Tracking support

void CCurveWnd::StartTracking()
{
	m_bTracking = TRUE;
	this->CaptureMouse();
	//SetCapture();

	//HCURSOR hCursor;
	//hCursor = AfxGetApp()->LoadCursor(IDC_ARRBLCKCROSS);
	SetCursor(*m_movingCursor);

}

void CCurveWnd::TrackKnot(wxPoint point)
{
	int iKnot = m_pHitInfo->nKnotIndex;	//Index knot	
	CurveWndKnotPoint toPt;
	toPt.x = point.x;
	toPt.y = point.y;
	m_pCurve->MoveKnot(toPt, iKnot);
	
	Refresh();
	if (m_callback)
	{
		m_callback->OnMovedKnot(this,iKnot,m_pCurve);
	}
}

void CCurveWnd::StopTracking()
{
	if(!m_bTracking)
		return;

	m_bTracking = FALSE;
	ReleaseMouse();
}

///////////////////////////////////////////////////////////////////////////////////
//Implementation





