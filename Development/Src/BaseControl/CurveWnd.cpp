#include "stdafx.h"
#include "CurveWnd.h"
#include "CurveWndProvider.h"


/////////////////////////////////////////////////////////////////////////////
// CCurveWnd
CCurveWnd::CCurveWnd( wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style ) 
:wxPanel( parent, id, pos, size, style )
,m_callback(0)
,m_pCurve(0)
{
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
	this->Connect( wxEVT_LEFT_DOWN, wxMouseEventHandler( CCurveWnd::OnMouseMove ) );
	this->Connect( wxEVT_LEFT_UP, wxMouseEventHandler( CCurveWnd::OnMouseMove ) );
	this->Connect( wxEVT_MIDDLE_DOWN, wxMouseEventHandler( CCurveWnd::OnMouseMove ) );
	this->Connect( wxEVT_MIDDLE_UP, wxMouseEventHandler( CCurveWnd::OnMouseMove ) );
	this->Connect( wxEVT_RIGHT_DOWN, wxMouseEventHandler( CCurveWnd::OnMouseMove ) );
	this->Connect( wxEVT_RIGHT_UP, wxMouseEventHandler( CCurveWnd::OnMouseMove ) );
	this->Connect( wxEVT_MOTION, wxMouseEventHandler( CCurveWnd::OnMouseMove ) );
	this->Connect( wxEVT_LEFT_DCLICK, wxMouseEventHandler( CCurveWnd::OnMouseMove ) );
	this->Connect( wxEVT_MIDDLE_DCLICK, wxMouseEventHandler( CCurveWnd::OnMouseMove ) );
	this->Connect( wxEVT_RIGHT_DCLICK, wxMouseEventHandler( CCurveWnd::OnMouseMove ) );
	this->Connect( wxEVT_LEAVE_WINDOW, wxMouseEventHandler( CCurveWnd::OnMouseMove ) );
	this->Connect( wxEVT_ENTER_WINDOW, wxMouseEventHandler( CCurveWnd::OnMouseMove ) );
	this->Connect( wxEVT_MOUSEWHEEL, wxMouseEventHandler( CCurveWnd::OnMouseMove ) );
	this->Connect( wxEVT_PAINT, wxPaintEventHandler( CCurveWnd::OnPaint ) );
	this->Connect( wxEVT_RIGHT_DOWN, wxMouseEventHandler( CCurveWnd::OnRButtonDown ) );
	this->Connect( wxEVT_RIGHT_UP, wxMouseEventHandler( CCurveWnd::OnRButtonUp ) );
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
	this->Disconnect( wxEVT_LEFT_DOWN, wxMouseEventHandler( CCurveWnd::OnMouseMove ) );
	this->Disconnect( wxEVT_LEFT_UP, wxMouseEventHandler( CCurveWnd::OnMouseMove ) );
	this->Disconnect( wxEVT_MIDDLE_DOWN, wxMouseEventHandler( CCurveWnd::OnMouseMove ) );
	this->Disconnect( wxEVT_MIDDLE_UP, wxMouseEventHandler( CCurveWnd::OnMouseMove ) );
	this->Disconnect( wxEVT_RIGHT_DOWN, wxMouseEventHandler( CCurveWnd::OnMouseMove ) );
	this->Disconnect( wxEVT_RIGHT_UP, wxMouseEventHandler( CCurveWnd::OnMouseMove ) );
	this->Disconnect( wxEVT_MOTION, wxMouseEventHandler( CCurveWnd::OnMouseMove ) );
	this->Disconnect( wxEVT_LEFT_DCLICK, wxMouseEventHandler( CCurveWnd::OnMouseMove ) );
	this->Disconnect( wxEVT_MIDDLE_DCLICK, wxMouseEventHandler( CCurveWnd::OnMouseMove ) );
	this->Disconnect( wxEVT_RIGHT_DCLICK, wxMouseEventHandler( CCurveWnd::OnMouseMove ) );
	this->Disconnect( wxEVT_LEAVE_WINDOW, wxMouseEventHandler( CCurveWnd::OnMouseMove ) );
	this->Disconnect( wxEVT_ENTER_WINDOW, wxMouseEventHandler( CCurveWnd::OnMouseMove ) );
	this->Disconnect( wxEVT_MOUSEWHEEL, wxMouseEventHandler( CCurveWnd::OnMouseMove ) );
	this->Disconnect( wxEVT_PAINT, wxPaintEventHandler( CCurveWnd::OnPaint ) );
	this->Disconnect( wxEVT_RIGHT_DOWN, wxMouseEventHandler( CCurveWnd::OnRButtonDown ) );
	this->Disconnect( wxEVT_RIGHT_UP, wxMouseEventHandler( CCurveWnd::OnRButtonUp ) );
	this->Disconnect( wxEVT_SIZE, wxSizeEventHandler( CCurveWnd::OnSize ) );
}

/////////////////////////////////////////////////////////////////////////////
// CCurveWnd initialisation										       //
/////////////////////////////////////////////////////////////////////////////

bool CCurveWnd::Create(LPCTSTR lpszCurveName, const RECT &rect, CWnd* pWndParent, unsigned int nID, bool CreateCurveObj)
{
	ASSERT(nID != NULL);
	ASSERT(pWndParent != NULL);

	//Create CurveWnd
	DWORD dwExStyle			= WS_EX_CLIENTEDGE  ;
	LPCTSTR lpszClassName	= NULL;
	LPCTSTR lpszWindowName	= lpszCurveName;
	DWORD dwStyle			= WS_CHILD | WS_VISIBLE | WS_BORDER;
	const RECT& rc			= rect;
	CWnd* pParentWnd		= pWndParent;
	unsigned int nClientWndID		= nID;
	LPVOID lpParam			= NULL;
	
	bool b = CreateEx(dwExStyle, lpszClassName, lpszWindowName, 
		dwStyle, rc, pParentWnd, nClientWndID, lpParam);

	if(CreateCurveObj)
		CreateCurveObject(lpszCurveName);
	m_hitCurveCursor = AfxGetApp()->LoadCursor(IDC_ARRWHITE);
	m_hitKnotCursor = AfxGetApp()->LoadCursor(IDC_ARRBLCK);
	m_movingCursor = AfxGetApp()->LoadCursor(IDC_ARRBLCKCROSS);

	return b;
}

void CCurveWnd::OnEraseBkgnd( wxEraseEvent& event )
{
	event.Skip();
}
void CCurveWnd::OnKeyDown( wxKeyEvent& event )
{
	
}
void CCurveWnd::OnLButtonDblClk( wxMouseEvent& event )
{
	
}
void CCurveWnd::OnLButtonDown( wxMouseEvent& event )
{
	OnLButtonDown(0,event.GetLogicalPosition());
}
void CCurveWnd::OnLButtonUp( wxMouseEvent& event )
{
	OnLButtonUp(0,event.GetLogicalPosition());	
}
void CCurveWnd::OnMouseMove( wxMouseEvent& event )
{
	OnMouseMove(0,event.GetLogicalPosition());
}
void CCurveWnd::OnPaint( wxPaintEvent& event )
{
	wxDC* dc=0;
	DrawWindow(dc);
}
void CCurveWnd::OnRButtonDown( wxMouseEvent& event )
{
	
}
void CCurveWnd::OnRButtonUp( wxMouseEvent& event )
{
	
}
void CCurveWnd::OnSize( wxSizeEvent& event )
{
	OnSize(0,event.GetSize().GetWidth(),event.GetSize().GetHeight());
}



/////////////////////////////////////////////////////////////////////////////
// CCurveWnd drawing										               //
/////////////////////////////////////////////////////////////////////////////
void CCurveWnd::DrawWindow(wxDC* pDC)
{
	CRect rcClient;
	GetClientRect(&rcClient);

	int cx = rcClient.Width();
	int cy = rcClient.Height();
	
	//Create Memory Device Context
	CDC MemDC;
	MemDC.CreateCompatibleDC(pDC);

	//Draw BackGround
	CBitmap bitmapBkGnd;;
	bitmapBkGnd.CreateCompatibleBitmap(pDC, cx, cy);
	CBitmap*  pOldbitmapBkGnd = MemDC.SelectObject(&bitmapBkGnd);
	
	//Draw Grid
	DrawGrid(&MemDC);
	
	//Draw Knots and Curve
	//if(AfxIsValidAddress(m_pCurve, sizeof(CObject))) {

		DrawKnots(&MemDC);
		DrawCurve(&MemDC);
	//}

	pDC->BitBlt (0, 0, cx, cy, &MemDC, 0, 0, SRCCOPY);
	MemDC.SelectObject(pOldbitmapBkGnd);
	MemDC.DeleteDC();
}

void CCurveWnd::DrawGrid(wxDC* pDC)
{
	CRect rcClipBox;
	pDC->GetClipBox(&rcClipBox);

	int cx = rcClipBox.Width();
	int cy = rcClipBox.Height();
	
	LOGBRUSH logBrush;
	logBrush.lbStyle = BS_SOLID;
	logBrush.lbColor = RGB(75, 75, 75);

	CPen pen;
	pen.CreatePen(PS_COSMETIC | PS_ALTERNATE, 1, &logBrush);
	CPen* pOldPen = pDC->SelectObject(&pen);
	
	//Draw Vertical Grid Lines
	for(int y = 1; y < 10; y++) {
		pDC->MoveTo(y*cx/10, cy);
		pDC->LineTo(y*cx/10, 0);
	}

	//Draw Horizontal Grid Lines
	for(int x = 1; x < 10; x++) {
		pDC->MoveTo(0, x*cy/10);
		pDC->LineTo(cx, x*cy/10);
	}

	pDC->SelectObject(pOldPen);
}

void CCurveWnd::DrawCurve(wxDC* pDC)
{
	CRect rcClipBox;
	pDC->GetClipBox(&rcClipBox);

	int cx = rcClipBox.Width();
	int cy = rcClipBox.Height();

	//Draw Curve
	// create and select a thick, white pen
	CPen pen;
	pen.CreatePen(PS_SOLID, 1, RGB(255, 255, 255));
	CPen* pOldPen = pDC->SelectObject(&pen);
	
	int iY=0;
	iY = m_pCurve->GetCurveY(1);	//Get Starting point
	pDC->MoveTo(1, iY);

	for(int iX = 1; iX < cx; iX++)
	{
		int iYnext = m_pCurve->GetCurveY(iX);
		pDC->LineTo(wxPoint(iX - 1, iYnext));

		iY = iYnext; //Set next starting point
	}

	// Put back the old objects
    pDC->SelectObject(pOldPen);
}

void CCurveWnd::DrawKnots(wxDC* pDC)
{
	// create and select a thin, white pen
	CPen pen;
	pen.CreatePen(PS_SOLID, 1, RGB(255, 255, 255));
	CPen* pOldPen = pDC->SelectObject(&pen);
	
	//Draw Knots
	for(int pos = 0; pos < m_pCurve->GetKnotCount(); pos++)
    {
		// Create and select a solid white brush
		CurveWndKnot* pKnot =	m_pCurve->GetKnot(pos);

		//Set knot brush color
		int cyColor;
		m_nActiveKnot == pos ? cyColor = 255 : cyColor = 0;
		CBrush brush(RGB(cyColor,cyColor,cyColor));
		CBrush* pOldBrush = pDC->SelectObject(&brush);

		//Draw knot
		CRect rc;
		rc.left   = pKnot->x - m_iKnotRadius;
		rc.right  = pKnot->x + m_iKnotRadius;
		rc.top    = pKnot->y - m_iKnotRadius;
		rc.bottom = pKnot->y + m_iKnotRadius;
		pDC->Ellipse(&rc); 

		pDC->SelectObject(pOldBrush);
	}

	// put back the old objects
	pDC->SelectObject(pOldPen);
}



/////////////////////////////////////////////////////////////////////////////
// CCurveWnd Message Handlers										       //
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
//Mouse Message Handlers

void CCurveWnd::OnLButtonDown(unsigned int nFlags, wxPoint point) 
{
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

void CCurveWnd::OnRButtonDown(unsigned int nFlags, wxPoint point) 
{
}

void CCurveWnd::OnLButtonDblClk(unsigned int nFlags, wxPoint point) 
{
	switch(m_pHitInfo->wHitCode)
	{
	case CurveHitInfo::enHitCanvas : 
		{	
			int iIndex = m_pCurve->InsertKnot(point);
			SetActiveKnot(iIndex);

			RedrawWindow();
		} break;
	default : 
		break;//do nothing
	}

	CWnd::OnLButtonDblClk(nFlags, point);
}

void CCurveWnd::OnMouseMove(unsigned int nFlags, wxPoint point) 
{
	if(GetCapture() != this)
		StopTracking();
	
	if(m_bTracking)
		TrackKnot(point);
	
}

void CCurveWnd::OnLButtonUp(unsigned int nFlags, wxPoint point) 
{
	if(m_bTracking)
		StopTracking();
			
}

void CCurveWnd::OnRButtonUp(unsigned int nFlags, wxPoint point) 
{
	
}

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
	RedrawWindow();
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
	if (GetSafeHwnd())
	{
		CRect rcCurveWnd;
		GetClientRect(&rcCurveWnd);
		rcCurveWnd.DeflateRect(1,1);
		m_pCurve->ChangeViewport(&rcCurveWnd);

		if(bRedraw)
			RedrawWindow();
	}
}

CurveWndProvider* CCurveWnd::GetCurveObject(){ return m_pCurve;}

/////////////////////////////////////////////////////////////////////////////
//Cursor Message Handlers

bool CCurveWnd::OnSetCursor(CWnd* pWnd, unsigned int nHitTest, unsigned int message) 
{
	bool b = FALSE;

	wxPoint point;
	GetCursorPos(&point);
	ScreenToClient(&point);

	switch(HitTest(point)) 
	{
	case CurveHitInfo::enHitCurve :
		{
			SetCursor(m_hitCurveCursor);
			b = TRUE;;
		} break;
	case CurveHitInfo::enHitKnot :
		{
			SetCursor(m_hitKnotCursor);
			b = TRUE;
		} break;
	default : //do nothing
		break;
	}
	
	if(!b)
		return CWnd::OnSetCursor(pWnd, nHitTest, message);
	else return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
//Keyboard Message Handlers

void CCurveWnd::OnKeyDown(unsigned int nChar, unsigned int nRepCnt, unsigned int nFlags) 
{
	bool bHandeldMsg = false;
	
	if(m_nActiveKnot != -1)
	{		
		switch(nChar)
		{
			case VK_DELETE :
			{
				m_pCurve->RemoveKnot(m_nActiveKnot);
				m_nActiveKnot = -1;	
				bHandeldMsg = true;
			} break;
			case VK_UP	:
			{
				CurveWndKnot* pKnot = m_pCurve->GetKnot(m_nActiveKnot);
				
				CurveWndKnotPoint pt;
				pKnot->GetPoint(&pt);
				pt.y -= 1;

				m_pCurve->MoveKnot(pt, m_nActiveKnot);
				bHandeldMsg = true;
			} break;
			case VK_DOWN :
			{		
				CurveWndKnot* pKnot = m_pCurve->GetKnot(m_nActiveKnot);
				
				CurveWndKnotPoint pt;
				pKnot->GetPoint(&pt);
				pt.y += 1;

				m_pCurve->MoveKnot(pt, m_nActiveKnot);
				bHandeldMsg = true;
			} break;
			case VK_LEFT :
			{
				CurveWndKnot* pKnot = m_pCurve->GetKnot(m_nActiveKnot);
				
				CurveWndKnotPoint pt;
				pKnot->GetPoint(&pt);
				pt.x -= 1;

				m_pCurve->MoveKnot(pt, m_nActiveKnot);
				bHandeldMsg = true;
			} break;
			case VK_RIGHT :
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

		RedrawWindow();
	}
	
	if(!bHandeldMsg)
		CWnd::OnKeyDown(nChar, nRepCnt, nFlags);
}

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

	if(pObject->GetKnotCount() == -1)
		return FALSE;	//Curve Has No Knots

	int iIndex = - 1;

	for(int pos = 0; pos < pObject->GetKnotCount(); pos++)
	{
		CurveWndKnot* pKnot = pObject->GetKnot(pos);

		CRect rcKnot;
		rcKnot.left   = pKnot->x - nInterval;
		rcKnot.right  = pKnot->x + nInterval;
		rcKnot.top    = pKnot->y - nInterval;
		rcKnot.bottom = pKnot->y + nInterval;

		if(rcKnot.PtInRect(ptHit)) {
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
	SetCapture();

	//HCURSOR hCursor;
	//hCursor = AfxGetApp()->LoadCursor(IDC_ARRBLCKCROSS);
	SetCursor(m_movingCursor);

}

void CCurveWnd::TrackKnot(wxPoint point)
{
	int iKnot = m_pHitInfo->nKnotIndex;	//Index knot	
	CurveWndKnotPoint toPt;
	toPt.x = point.x;
	toPt.y = point.y;
	m_pCurve->MoveKnot(toPt, iKnot);
	
	RedrawWindow();
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
	ReleaseCapture();

}

///////////////////////////////////////////////////////////////////////////////////
//Implementation







void CCurveWnd::OnSize(unsigned int nType, int cx, int cy)
{
	CWnd::OnSize(nType, cx, cy);

	CRect rcCurveWnd;
	GetClientRect(&rcCurveWnd);
	rcCurveWnd.DeflateRect(1,1);
	if (m_pCurve)
	{
		m_pCurve->ChangeViewport(&rcCurveWnd);
	}
	// TODO: Add your message handler code here
}
