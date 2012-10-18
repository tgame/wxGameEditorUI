//tgame
#ifndef _H_10172012_CurveWnd
#define _H_10172012_CurveWnd


//
class CurveWndProvider;

struct CurveHitInfo 
{
	wxPoint  ptHit;		//Cursor position
	WORD	wHitCode;	//Hit Code 
	unsigned int	nKnotIndex;	//Index of knot			HTKNOT
	wxPoint	ptCurve;	//Exact point on curve	HTCURVE
	enum ENHitType
	{
		enHitCanvas,
		enHitCurve,
		enHitKnot,
	};
};
class CCurveWnd;
struct ICurveWndCallback 
{
	virtual void OnSelectKnot(CCurveWnd* wnd,unsigned int knotIdx,CurveWndProvider* obj) = 0;
	virtual void OnMovedKnot(CCurveWnd* wnd,unsigned int knotIdx,CurveWndProvider* obj) = 0;
};

class CCurveWnd 
	: public wxPanel
{
public:
	ICurveWndCallback* m_callback;
	CCurveWnd(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style );
	virtual ~CCurveWnd();

	//Create Window
	bool Create(const char* strName, const RECT &rect, CWnd* pWndParent, unsigned int nID, bool CreateCurveObj = true);

	//Knot functions
	unsigned int GetActiveKnot();
	void SetActiveKnot(unsigned int nIndex);

	//Inline CurveObject Access function
	CurveWndProvider* GetCurveObject();
	void          SetCurveObject(CurveWndProvider* pObject, bool bRedraw = FALSE);
	void HitTest(wxPoint ptHit, CurveHitInfo* pHitInfo,CurveWndProvider* pObject);
	bool PtOnCurve(wxPoint ptHit, unsigned int nInterval, wxPoint* pt,CurveWndProvider* pObject);
	bool PtOnKnot(wxPoint ptHit, unsigned int nInterval, unsigned int* nIndex,CurveWndProvider* pObject);
protected:


	CurveHitInfo* m_pHitInfo;	  //Hit Info Structure

	unsigned int   m_nActiveKnot; //Index of active knot object;
	int	   m_iKnotRadius; 

	bool  m_bTracking;  //Tracking Knots
	
	//Drawing helper functions
	void DrawWindow(wxDC* pDC);
	void DrawGrid  (wxDC* pDC);
	void DrawCurve (wxDC* pDC);
	void DrawKnots (wxDC* pDC);

	//Hit Testing helper functions
	WORD  HitTest  	  (wxPoint ptHit);

	//Tracking support helper functions
	void StartTracking();
	void TrackKnot(wxPoint point);
	void StopTracking();

	//{{AFX_MSG(CCurveWnd)
	// Virtual event handlers, overide them in your derived class
	virtual void OnEraseBkgnd( wxEraseEvent& event );
	virtual void OnKeyDown( wxKeyEvent& event );
	virtual void OnLButtonDblClk( wxMouseEvent& event );
	virtual void OnLButtonDown( wxMouseEvent& event );
	virtual void OnLButtonUp( wxMouseEvent& event );
	virtual void OnMouseMove( wxMouseEvent& event );
	virtual void OnPaint( wxPaintEvent& event );
	virtual void OnRButtonDown( wxMouseEvent& event );
	virtual void OnRButtonUp( wxMouseEvent& event );
	virtual void OnSize( wxSizeEvent& event );

private :
	wxCursor*m_hitCurveCursor;
	wxCursor*m_hitKnotCursor;
	wxCursor*m_movingCursor;
	CurveWndProvider* m_pCurve;	//CurveObject associate with this window
};

//////////////////////////////////////////////////////////////////////////////
#endif // _JANSSENS_JOHAN_CURVEWND_H_
