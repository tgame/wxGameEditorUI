#pragma once


#include "PropertyControl/PropertyListCtrl.h"
#include "CurveWnd.h"
#include "CurveWndProvider.h"
// DlgCurveEditor
class GuiCustomPropertyCollector;
class CurveProps_Impl;
class CurveProps_Impl_Provider;


class _CommoneEditor_Export_ DlgCurveEditor : public CGuiContainer
{
	DECLARE_DYNAMIC(DlgCurveEditor)

public:
	CGuiSplitter	m_wnd2Property;
	CPropertyListCtrl	m_propertyControl;
	CGuiMiniTool	m_miniToolbar;
	CCurveWnd		m_curveWnd;
	FInterpCurveWndProvider	m_curveWndProvider;
	GuiCustomPropertyCollector* m_propertyFacade;
	CurveProps_Impl*	m_curveEditableProp;
	CurveProps_Impl_Provider*	m_props;
	DlgCurveEditor();
	virtual ~DlgCurveEditor();

protected:
	DECLARE_MESSAGE_MAP()
public:

	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	virtual bool OnCommand(WPARAM wParam, LPARAM lParam);
	
	void ShowCurve(FInterpCurve<float>* curve);

};


