// DlgCurveEditor.cpp : implementation file
//

#include "stdafx.h"
#include "CommonEditorDialog.h"
#include "DlgCurveEditor.h"
#include "PropertyControl/GuiCustomPropertyItem.h"
#include "PropertyControl/PropertyDefineMacro.h"
class CurveProps_Impl;
class CurveProps_Impl_InterpMode;
void Config_CurveProps_Impl_InterpMode(CurveProps_Impl* obj,CurveProps_Impl_InterpMode* desc);
class CurveProps_Impl
{
public:
	CCurveWnd*	m_wnd;
	FInterpCurveWndProvider*	m_curveWndProvider;
	unsigned int	m_currentSelect;
	std::vector<std::string>	m_modeString;

	CurveProps_Impl(void):m_curveWndProvider(0),m_currentSelect(-1){
		m_modeString.push_back("CIM_Linear");
		m_modeString.push_back("CIM_CurveAuto");
		m_modeString.push_back("CIM_Constant");
		m_modeString.push_back("CIM_CurveUser");
		m_modeString.push_back("CIM_CurveBreak");
	}

	const std::string& GetInterpMode(void){
		static std::string none("Unkown");
		if(m_curveWndProvider->m_curveImpl && m_currentSelect<m_curveWndProvider->m_curveImpl->m_points.size())
		{
			unsigned int mode = m_curveWndProvider->m_curveImpl->m_points[m_currentSelect].InterpMode;
			if (mode<m_modeString.size())
			{
				return m_modeString[mode];
			}
			return none;
		}
		return none;
	}
	void SetInterpMode(const std::string& v){
		if(m_curveWndProvider->m_curveImpl && m_currentSelect<m_curveWndProvider->m_curveImpl->m_points.size())
		{
			unsigned int mode = CIM_Linear;
			for (unsigned int i =0;i<m_modeString.size();i++)
			{
				if (m_modeString[i] == v)
				{
					mode = i;
					break;
				}
			}
			m_curveWndProvider->m_curveImpl->m_points[m_currentSelect].InterpMode = mode;
			m_wnd->RedrawWindow();
		}
	}
	float GetValue(void){
		if(m_curveWndProvider->m_curveImpl && m_currentSelect<m_curveWndProvider->m_curveImpl->m_points.size())
		{
			return m_curveWndProvider->m_curveImpl->m_points[m_currentSelect].OutVal;
		}
		return 0.0f;
	}
	void SetValue(float v){
		if(m_curveWndProvider->m_curveImpl && m_currentSelect<m_curveWndProvider->m_curveImpl->m_points.size()
			&& m_curveWndProvider->m_curveImpl->m_points[m_currentSelect].OutVal != v)
		{
			m_curveWndProvider->m_curveImpl->m_points[m_currentSelect].OutVal = v;
			m_wnd->RedrawWindow();
		}
	}
	float GetTime(void){
		if(m_curveWndProvider->m_curveImpl && m_currentSelect<m_curveWndProvider->m_curveImpl->m_points.size())
		{
			return m_curveWndProvider->m_curveImpl->m_points[m_currentSelect].InVal;
		}
		return 0.0f;
	}
	void SetTime(float t){
		if(m_curveWndProvider->m_curveImpl && m_currentSelect<m_curveWndProvider->m_curveImpl->m_points.size()
			&& m_curveWndProvider->m_curveImpl->m_points[m_currentSelect].InVal != t)
		{
			m_curveWndProvider->m_curveImpl->m_points[m_currentSelect].InVal = t;
			m_wnd->RedrawWindow();
		}
	}
	float GetArriveTangent(void){
		if(m_curveWndProvider->m_curveImpl && m_currentSelect<m_curveWndProvider->m_curveImpl->m_points.size())
		{
			return m_curveWndProvider->m_curveImpl->m_points[m_currentSelect].ArriveTangent;
		}
		return 0.0f;
	}
	void SetArriveTangent(float t){
		if(m_curveWndProvider->m_curveImpl && m_currentSelect<m_curveWndProvider->m_curveImpl->m_points.size()
			&& m_curveWndProvider->m_curveImpl->m_points[m_currentSelect].ArriveTangent != t)
		{
			m_curveWndProvider->m_curveImpl->m_points[m_currentSelect].ArriveTangent = t;
			m_wnd->RedrawWindow();
		}
	}
	float GetLeaveTangent(void){
		if(m_curveWndProvider->m_curveImpl && m_currentSelect<m_curveWndProvider->m_curveImpl->m_points.size())
		{
			return m_curveWndProvider->m_curveImpl->m_points[m_currentSelect].LeaveTangent;
		}
		return 0.0f;
	}
	void SetLeaveTangent(float t){
		if(m_curveWndProvider->m_curveImpl && m_currentSelect<m_curveWndProvider->m_curveImpl->m_points.size()
			&& m_curveWndProvider->m_curveImpl->m_points[m_currentSelect].LeaveTangent != t)
		{
			m_curveWndProvider->m_curveImpl->m_points[m_currentSelect].LeaveTangent = t;
			m_wnd->RedrawWindow();
		}
	}
protected:
private:
};



#undef T_Set_Prop
#undef T_PropDefine
#undef T_PropDefine_Convert

#define T_Set_Prop(TM_PropClassName,TM_DisplayName,TM_Category,TM_Editor) 
#define T_Set_Prop_Custom(TM_PropClassName,TM_CustomFunc) 
#define T_PropDefine PropDefine
#define T_PropDefine_Convert PropDefine_Convert

#include "CurveWndKnotProp.inl"

#undef T_Set_Prop
#undef T_Set_Prop_Custom
#undef T_PropDefine
#undef T_PropDefine_Convert


#define T_Set_Prop Set_Prop
#define T_Set_Prop_Custom Set_Prop_Custom
#define T_PropDefine PropDefine_Create
#define T_PropDefine_Convert PropDefine_Convert_Create

Begin_Obj(CurveProps_Impl_Provider,CurveProps_Impl)
#include "CurveWndKnotProp.inl"
End_Obj()

#undef T_Set_Prop
#undef T_Set_Prop_Custom
#undef T_PropDefine
#undef T_PropDefine_Convert


void Config_CurveProps_Impl_InterpMode(CurveProps_Impl* obj,CurveProps_Impl_InterpMode* desc){
	desc->m_supportStdValue=true;
	desc->m_exclusiveStdValue=true;
	desc->m_stdValues = &obj->m_modeString;
}

class DlgCurveEditor_WndCallback
	:public ICurveWndCallback
{
public:
	DlgCurveEditor_WndCallback(DlgCurveEditor* editor):m_editor(editor){

	}
	DlgCurveEditor*	m_editor;
	virtual void OnSelectKnot(CCurveWnd* wnd,unsigned int knotIdx,CurveWndProvider* obj)
	{
		m_editor->m_curveEditableProp->m_currentSelect = knotIdx;
		//m_editor->m_propertyFacade->UpdateProvider(m_editor->m_props);
		m_editor->m_propertyControl.RedrawWindow();
	}
	virtual void OnMovedKnot(CCurveWnd* wnd,unsigned int knotIdx,CurveWndProvider* obj)
	{
		m_editor->m_propertyControl.RedrawWindow();
	}
};


#define IDC_DCE_SaveCurve 900
#define IDC_DCE_LoadCurve 901
#define IDC_DCE_ResetCurve 902



// DlgCurveEditor

IMPLEMENT_DYNAMIC(DlgCurveEditor, CGuiContainer)

DlgCurveEditor::DlgCurveEditor()
:m_propertyFacade(new GuiCustomPropertyCollector)
,m_curveEditableProp(0)
,m_props(0)
{
	m_curveEditableProp = new CurveProps_Impl;
	m_props = new CurveProps_Impl_Provider;
	m_props->AddObjectProperty(m_curveEditableProp);
}

DlgCurveEditor::~DlgCurveEditor()
{
}


BEGIN_MESSAGE_MAP(DlgCurveEditor, CGuiContainer)
	ON_WM_CREATE()
END_MESSAGE_MAP()



// DlgCurveEditor message handlers
extern HINSTANCE g_hDllInstance;
int DlgCurveEditor::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CGuiContainer::OnCreate(lpCreateStruct) == -1)
		return -1;
	HINSTANCE oldInstance = AfxGetResourceHandle();
	AfxSetResourceHandle(g_hDllInstance);
//#ifdef DlgCurveEditor_Toolbar
	AddComponen(&m_miniToolbar);
	m_miniToolbar.AlingButtons(CGuiMiniTool::ALIGN_LEFT);
	m_miniToolbar.SetImageList(IDB_BITMAP_MATERIALBOX, 16,24, RGB (255, 0, 0));
	//m_miniToolbar.AddButton(0,IDC_DMP_Pick,NULL,_T(""),"Pick material");
	//m_miniToolbar.AddButton(1,IDC_DMP_AssignTheMaterialToCurObj,NULL,_T(""),"Assign material to current object");
	//m_miniToolbar.AddButton(2,IDC_DMP_GetCurObjMaterial,NULL,_T(""),"Get material from current object");
	//m_miniToolbar.AddButton(3,IDC_DMP_RecompileCurShader,NULL,_T(""),"Recompile Shader");
	//m_miniToolbar.AddButton(4,IDC_DMP_ReloadCurTexture,NULL,_T(""),"Reload Texture");
	m_miniToolbar.AddButton(7,IDC_DCE_LoadCurve,NULL,_T(""),"Open Curve");
	m_miniToolbar.AddButton(5,IDC_DCE_SaveCurve,NULL,_T(""),"Save Current Curve As");
	m_miniToolbar.AddButton(3,IDC_DCE_ResetCurve,NULL,_T(""),"Reset Current Curve");
	//m_miniToolbar.AddButton(6,IDC_DMP_SaveAllMaterial,NULL,_T(""),"Save All Material");
	m_miniToolbar.AutoSize(FALSE);
//#endif
	if (!m_wnd2Property.Create(this))
		return -1;
	if (!m_propertyControl.Create(WS_CHILD|WS_VISIBLE|LBS_OWNERDRAWFIXED|LBS_NOINTEGRALHEIGHT|WS_VSCROLL|LBS_NOTIFY,wxRect(0,0,0,0),&m_wnd2Property,5))
	{
		return -1;
	}
	m_curveWndProvider.CreateTestCurve();
	m_curveWnd.Create("", wxRect(25, 55, 500, 265), &m_wnd2Property, 2001, false);
	m_curveWnd.SetCurveObject(&m_curveWndProvider);
	m_wnd2Property.SeTypeALing(CGuiSplitter::ALINGHORZ);//ALINGVERT
	m_wnd2Property.SetSpplitterPos(0.6f);
	m_wnd2Property.SetPixelWidht(2);
	m_wnd2Property.AddLeftCtrl(&m_curveWnd,3);
	m_wnd2Property.AddRightCtrl(&m_propertyControl,4);
	m_wnd2Property.SetStyleSeparator(CGuiSplitter::STYLE3D,
		GuiDrawLayer::GetRGBColorShadow(),GuiDrawLayer::GetRGBColorShadow());

	AddComponen(&m_wnd2Property);
	//////////////////////////////////////////////////////////////////////////
	AfxSetResourceHandle(oldInstance);
	//////////////////////////////////////////////////////////////////////////
	m_curveWnd.m_callback = new DlgCurveEditor_WndCallback(this);
	m_curveEditableProp->m_wnd = &m_curveWnd;
	m_curveEditableProp->m_curveWndProvider = &m_curveWndProvider;
	m_propertyControl.SetPropertyItemManager(m_propertyFacade);
	m_propertyFacade->UpdateProvider(m_props);
	
	return 0;
}

bool DlgCurveEditor::OnCommand(WPARAM wParam, LPARAM lParam)
{
	if (wParam == IDC_DCE_SaveCurve)
	{
		
	}
	else if (wParam == IDC_DCE_LoadCurve)
	{
	}
	else if (wParam == IDC_DCE_ResetCurve)
	{
		m_curveWndProvider.m_curveImpl->m_points.clear();
		m_curveWndProvider.m_curveImpl->AddPoint(0.0f,0.0f);
		m_curveWndProvider.m_curveImpl->m_points[0].InterpMode=CIM_CurveAuto;
		m_curveWndProvider.m_curveImpl->AddPoint(1.0f,1.0f);
		m_curveWndProvider.m_curveImpl->m_points[1].InterpMode=CIM_CurveAuto;
		m_curveWnd.RedrawWindow();
	}
	__super::OnCommand(wParam,lParam);
	return true;
}

void DlgCurveEditor::ShowCurve(FInterpCurve<float>* curve)
{
	m_curveWndProvider.m_curveImpl = curve;
	m_curveWnd.RedrawWindow();
	m_propertyFacade->UpdateProvider(0);
}
