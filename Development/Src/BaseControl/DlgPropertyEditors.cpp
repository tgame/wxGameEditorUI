#include "stdafx.h"
#include "DlgPropertyEditors.h"
#include "PropertyHelperFunc.h"

#include <wx/propgrid/propgrid.h>


wxIMPLEMENT_CLASS(MyPGProperty,wxPGProperty);
bool MyPGProperty::StringToValue( wxVariant& variant, const wxString& text, int argFlags )const
{
	// TODO: Adapt string to property value.
	variant=text;
	//std::string s;
	//s.assign(text.c_str(),text.size());
	//m_desc->SetValue(s);
	return true;
}

void MyPGProperty::OnSetValue ()
{
	wxString s=m_value;
	std::string sv;
	sv.assign(s.c_str(),s.size());
	m_desc->SetValue(sv);
}

class DlgPropertyEditors_Color_Pane
	:public wxPanel
{
public:
	DECLARE_DYNAMIC_CLASS(DlgPropertyEditors_Color_Pane);
	//wxCLASSINFO
	std::vector<wxSlider*>	m_slider;
};
wxIMPLEMENT_CLASS(DlgPropertyEditors_Color_Pane,wxPanel);

DlgPropertyEditors_Color::DlgPropertyEditors_Color(void)
{
}

wxPGWindowList DlgPropertyEditors_Color::CreateControls(wxPropertyGrid* propgrid,
							  wxPGProperty* property,
							  const wxPoint& pos,
							  const wxSize& size) const
{
	/*
	if(!property->IsKindOf(MyPGProperty::GetClassInfoStatic()))
	{
		wxString text;
		//
		// If has children, and limited editing is specified, then don't create.
		if ( (property->GetFlags() & wxPG_PROP_NOEDITOR) &&
			 property->GetChildCount() )
			return (wxWindow*) NULL;
		if ( !property->IsValueUnspecified() )
		{
			int flags = property->HasFlag(wxPG_PROP_READONLY) ? 
				0 : wxPG_EDITABLE_VALUE;
			text = property->GetValueString(flags);
		}
		else
		{
			text = propgrid->GetUnspecifiedValueText();
		}
		int flags = 0;
		wxWindow* wnd = propgrid->GenerateEditorTextCtrl(pos,size,text,(wxWindow*)NULL,flags,
														 property->GetMaxLength());
		return wnd;
	}
	 * */
	wxString text;	
	int flags = property->HasFlag(wxPG_PROP_READONLY) ? 
		0 : wxPG_EDITABLE_VALUE;
	text = property->GetValueString(flags);
	
	//get how many slider and slider info
	std::vector<ColorSliderParam> infoSlider;
	std::string v_in(text.c_str());
	PropertyHelperFunc::StringToFloatArray(infoSlider,v_in);
	size_t sliderCount = infoSlider.size();
	wxSize dlgSize(size.x,size.y*sliderCount);
	wxPoint dlgPos(pos.x,pos.y+size.y);
	
	DlgPropertyEditors_Color_Pane* dlg = new DlgPropertyEditors_Color_Pane;
	dlg->Create(propgrid->GetPanel(),wxPG_SUBID2,dlgPos,dlgSize);
	for(int i=0;i<sliderCount;i++)
	{
		wxPoint sliderPos(0,i*size.y);
		wxSlider *ctrl = new wxSlider();
		#ifdef __WXMSW__
		//ctrl->Hide();
		#endif
		ColorSliderParam& info = infoSlider[i];
		double sPercent = (info.m_value-info.m_minValue)/(info.m_maxValue-info.m_minValue);
		ctrl->Create(dlg,wxID_ANY
			,sPercent*1024.0,0,1024,
			sliderPos,size,wxSL_HORIZONTAL );
		dlg->m_slider.push_back(ctrl);
	}

	return wxPGWindowList(dlg);

}
void DlgPropertyEditors_Color::UpdateControl( wxPGProperty* property,
					wxWindow* ctrl ) const
{
	wxString text;	
	int flags = property->HasFlag(wxPG_PROP_READONLY) ? 0 : wxPG_EDITABLE_VALUE;
	text = property->GetValueString(flags);
	//get how many slider and slider info
	std::string v_in(text.c_str());
	std::vector<ColorSliderParam> infoSlider;
	PropertyHelperFunc::StringToFloatArray(infoSlider,v_in);
	if ( ctrl->IsKindOf(wxCLASSINFO(DlgPropertyEditors_Color_Pane)))
	{
		DlgPropertyEditors_Color_Pane* dlg = (DlgPropertyEditors_Color_Pane*)ctrl;
		size_t sliderCount = infoSlider.size();
		for(int i=0;i<sliderCount&&i<dlg->m_slider.size();i++)
		{
			ColorSliderParam& info = infoSlider[i];
			wxSlider* s = dlg->m_slider[i];
			double sPercent = (info.m_value-info.m_minValue)/(info.m_maxValue-info.m_minValue);
			s->SetValue(sPercent*1024.0);
		}
	}
}
bool DlgPropertyEditors_Color::OnEvent( wxPropertyGrid* propgrid,
			  wxPGProperty* property,
			  wxWindow* primaryCtrl,
			  wxEvent& event ) const
{
	//wxPGEditor::OnEvent(propgrid,property,primaryCtrl,event);
	//wxEVT_SCROLL_THUMBTRACK
	if(event.GetEventType() == wxEVT_SCROLL_CHANGED)
	{
		// Update the value   
		event.Skip();
		propgrid->EditorsValueWasModified();
		return true;
	}
	return false;
}
bool DlgPropertyEditors_Color::GetValueFromControl( wxVariant& variant,
						  wxPGProperty* property,
						  wxWindow* ctrl ) const
{
	if (!ctrl->IsKindOf(wxCLASSINFO(DlgPropertyEditors_Color_Pane)))
	{
		return false;
	}
	DlgPropertyEditors_Color_Pane* dlg = (DlgPropertyEditors_Color_Pane*)ctrl;
	wxString text;	
	int flags = property->HasFlag(wxPG_PROP_READONLY) ? 0 : wxPG_EDITABLE_VALUE;
	text = property->GetValueString(flags);
	//get how many slider and slider info
	std::string v_in(text.c_str());
	std::vector<ColorSliderParam> infoSlider;
	PropertyHelperFunc::StringToFloatArray(infoSlider,v_in);
	size_t sliderCount = infoSlider.size();
	for(int i=0;i<sliderCount&&i<dlg->m_slider.size();i++)
	{
		ColorSliderParam& info = infoSlider[i];
		wxSlider* s = dlg->m_slider[i];
		double percent = s->GetValue()/1024.0;
		double v = percent*(info.m_maxValue-info.m_minValue);
		info.m_value=v;
	}
	std::string theValue;
	PropertyHelperFunc::FloatArrayToString(infoSlider,theValue);
	wxClassInfo* theClass = property->GetClassInfo();
	wxString setValue(theValue.c_str());
	//wxPG_PROGRAMMATIC_VALUE;
	bool ret = property->SetValueFromString(setValue);
	//property->ActualStringToValue(variant,setValue,wxPG_EDITABLE_VALUE);
	return true;
}
void DlgPropertyEditors_Color::SetValueToUnspecified( wxPGProperty* property,
							wxWindow* ctrl ) const
{
	wxPGEditor::SetValueToUnspecified(property,ctrl);
}

void GetFourColor(const wxString& v,int& v1,int& v2,int& v3,int& v4)
{
	unsigned int argb = 0;
	sscanf(v.c_str(),"%8x",&argb);

	v1 = (argb&0xFF000000)>>24;
	v2 = (argb&0x00FF0000)>>16;
	v3 = (argb&0x0000FF00)>>8;
	v4 = argb&0x000000FF;
}
void DlgPropertyEditors_Color::DrawValue( wxDC& dc,
				const wxRect& rect,
				wxPGProperty* property,
				const wxString& text ) const
{
	wxString s = property->GetValueAsString();
	int v1=0;
	int v2=0;
	int v3=0;
	int v4=0;
	GetFourColor(s,v1,v2,v3,v4);
	wxRect myrc=rect;
	myrc.Deflate(1,1);
	wxColour color;
	color.Set(v1,v2,v3,v4);
	wxBrush brush(color);
	dc.SetBrush(brush);
	dc.DrawRectangle(myrc);
	//dc.draw
	dc.DrawText(s,wxPoint(myrc.x+myrc.width*0.5,myrc.y));
	//dc.DrawText(s,myrc.GetLeftTop());
}

void DlgPropertyEditors_Color::SetControlIntValue( wxPGProperty* property,
								 wxWindow* ctrl,
								 int value ) const
{
	
}
	
	
