#include "stdafx.h"
#include "DlgPropertyEditors.h"
#include "PropertyHelperFunc.h"
#include "DlgPropertyEditors_Gui.h"
#include <wx/propgrid/propgrid.h>

struct WrapDlgPropertyEditorsList
{
	static const wxPGEditor* GetEditor(IGuiPropertyDescriptor* desc)
	{		
	// Determines editor used by property.
	// You can replace 'TextCtrl' below with any of these
	// builtin-in property editor identifiers: Choice, ComboBox,
	// TextCtrlAndButton, ChoiceAndButton, CheckBox, SpinCtrl,
	// DatePickerCtrl.
		static DlgPropertyEditors_FloatSlider* colorEditor = new DlgPropertyEditors_FloatSlider(true);
		static DlgPropertyEditors_FloatSlider* floatEditor = new DlgPropertyEditors_FloatSlider(false);
		if(desc->GetEditorType()=="ColorSlider")
		{
			return colorEditor;
		}
		else if (desc->GetEditorType()=="FloatSlider")
		{
			return floatEditor;
		}
		else if(desc->GetEditorType()=="Checkbox")
		{
			return wxPGEditor_CheckBox;
		}
		if(desc->GetStandardValuesSupported()
			&&desc->GetStandardValues())
		{
			if(desc->GetStandardValuesExclusive())
			{
				return wxPGEditor_Choice;
			}
			else
			{
				return wxPGEditor_ComboBox;				
			}
		}
		//return wxPGEditor_ChoiceAndButton;
		return wxPGEditor_TextCtrlAndButton;
	}
};

void _wxString2stdstring(std::string& s,const wxString& ws)
{
	wxWX2MBbuf buf = ws.mbc_str();
	s.assign(buf.data(),buf.length());
}

wxIMPLEMENT_CLASS(MyPGProperty,wxPGProperty);
bool MyPGProperty::StringToValue( wxVariant& variant, const wxString& text, int argFlags )const
{
	variant=text;
	return true;
}
const wxPGEditor* MyPGProperty::DoGetEditorClass() const
{
	return WrapDlgPropertyEditorsList::GetEditor(m_desc);
}
void MyPGProperty::Bind(IGuiPropertyDescriptor* desc)
{
	m_desc=desc;
	m_name=m_desc->GetDisplayName().c_str();
	this->SetLabel(m_desc->GetDisplayName().c_str());
	//DoGetValue();		
	wxString s;
	const std::string& v= m_desc->GetValue();
	s.assign(v.c_str(),v.size());
	m_value=s;
	m_choices.Clear();
	std::vector<std::string>* choiceList=m_desc->GetStandardValues();
	for(size_t i=0;m_desc->GetStandardValuesSupported()&&choiceList&&i<choiceList->size();i++)
	{
		std::string& v = choiceList->at(i);
		m_choices.Add(v.c_str(),i);
	}
	if (!choiceList&&m_desc->GetEditorType()=="Checkbox")
	{
		m_choices.Add("true",1);
		m_choices.Add("false",0);
	}
	
	if(m_desc->IsReadOnly())
	{
		
	}
}

void MyPGProperty::OnSetValue ()
{
	std::string sv;
	if (m_value.IsType("bool"))
	{
		if (m_value)
		{
			sv="true";
		}
		else
		{
			sv="false";
		}
	}
	else
	{
		wxString s=m_value;
		_wxString2stdstring(sv,s);
	}
	m_desc->SetValue(sv);
}

class DlgPropertyEditors_Color_Pane
	:public Dlg_Color_Title
{
public:
	DECLARE_DYNAMIC_CLASS(DlgPropertyEditors_Color_Pane);
	DlgPropertyEditors_Color_Pane(wxWindow* parent, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 500,300 ), long style = wxTAB_TRAVERSAL )
		:Dlg_Color_Title(parent,id,pos,size,style)
	{

	}
	void ResizeTitle(const wxSize& size)
	{
		m_colorTitle->SetSize(size);
	}
	void SetDisplayValue(std::vector<ColorSliderParam>& infoSlider)
	{
		int c[3]={0,0,0};
		wxString text;
		size_t sliderCount = infoSlider.size();
		for(int i=0;i<sliderCount&&i<m_slider.size();i++)
		{
			ColorSliderParam& info = infoSlider[i];
			wxSlider* s = m_slider[i];
			double sPercent = (info.m_value-info.m_minValue)/(info.m_maxValue-info.m_minValue);
			if (i<3)
			{
				c[i]=sPercent*255;
			}
			int pos = sPercent*1000.0;
			s->SetValue(pos);
			if (i+1==sliderCount)
			{
				text += wxString::Format("%g",info.m_value);
			}
			else{
				text += wxString::Format("%g,",info.m_value);
			}
		}
		m_colorTitle->SetLabel(text);
		wxColour bgColor;
		bgColor.Set(c[0],c[1],c[2]);
		m_colorTitle->SetBackgroundColour(bgColor);
	}
	void GetDisplayValue(std::vector<ColorSliderParam>& infoSlider)
	{
		size_t sliderCount = infoSlider.size();
		for(int i=0;i<sliderCount&&i<m_slider.size();i++)
		{
			ColorSliderParam& info = infoSlider[i];
			wxSlider* s = m_slider[i];
			int pos = s->GetValue();
			double percent = pos/1000.0;
			double v = percent*(info.m_maxValue-info.m_minValue)+info.m_minValue;
			info.m_value=v;
		}
	}
	//wxCLASSINFO
	std::vector<ColorSliderParam>	m_sliderInfo;
	std::vector<wxSlider*>	m_slider;
};
wxIMPLEMENT_CLASS(DlgPropertyEditors_Color_Pane,wxPanel);


void DlgPropertyEditors_Base::UpdateControl( wxPGProperty* property,
	wxWindow* ctrl ) const
{
	if (ctrl->IsKindOf(wxCLASSINFO(wxComboBox)))
	{
		wxPGChoiceEditor::UpdateControl(property,ctrl);
	}
}
bool DlgPropertyEditors_Base::OnEvent( wxPropertyGrid* propgrid,
	wxPGProperty* property,
	wxWindow* primaryCtrl,
	wxEvent& event ) const
{
	if (primaryCtrl->IsKindOf(wxCLASSINFO(wxComboBox)))
	{
		return wxPGChoiceEditor::OnEvent(propgrid,property,primaryCtrl,event);
	}
	return false;
}
bool DlgPropertyEditors_Base::GetValueFromControl( wxVariant& variant,
	wxPGProperty* property,
	wxWindow* ctrl ) const
{
	if (ctrl->IsKindOf(wxCLASSINFO(wxComboBox)))
	{
		return wxPGChoiceEditor::GetValueFromControl(variant,property,ctrl);
	}
	return false;
}

DlgPropertyEditors_FloatSlider::DlgPropertyEditors_FloatSlider(bool isColor)
	:m_isColor(isColor)
{
}

wxPGWindowList DlgPropertyEditors_FloatSlider::CreateControls(wxPropertyGrid* propgrid,
							  wxPGProperty* property,
							  const wxPoint& pos,
							  const wxSize& size) const
{
	wxString text;	
	int flags = property->HasFlag(wxPG_PROP_READONLY) ? 
		0 : wxPG_EDITABLE_VALUE;
	text = property->GetValueString(flags);
	
	//get how many slider and slider info
	std::vector<ColorSliderParam> infoSlider;
	std::string v_in(text.c_str());
	if (m_isColor)
	{
		PropertyHelperFunc::StringToColor(infoSlider,v_in);
	}
	else
	{
		PropertyHelperFunc::StringToFloatArray(infoSlider,v_in);
	}
	size_t sliderCount = infoSlider.size();
	wxSize dlgSize(size.x,size.y*sliderCount+size.y+8);
	wxPoint dlgPos(pos.x,pos.y);
	wxWindow* choiceWnd = 0;
	if (property->GetChoices().GetCount() > 1)
	{
		//wxPGChoiceEditor::CreateControlsBase(propgrid,property,pos,size,0);
		//dlgPos.y+=size.y;
	}
	DlgPropertyEditors_Color_Pane* dlg = new DlgPropertyEditors_Color_Pane(propgrid->GetPanel(),wxPG_SUBID2,dlgPos,dlgSize);
	dlg->ResizeTitle(size);
	for(int i=0;i<sliderCount;i++)
	{
		wxPoint sliderPos(0,i*size.y+size.y);
		wxSlider *ctrl = new wxSlider();
		#ifdef __WXMSW__
		//ctrl->Hide();
		#endif
		ColorSliderParam& info = infoSlider[i];
		double sPercent = (info.m_value-info.m_minValue)/(info.m_maxValue-info.m_minValue);
		ctrl->Create(dlg,wxID_ANY
			,sPercent*1000.0,0,1000.0,
			sliderPos,size,wxSL_HORIZONTAL );
		wxColour c;
		c.Set(127,127,127);
		ctrl->SetBackgroundColour(c);
		ctrl->Refresh();
		dlg->m_slider.push_back(ctrl);
		dlg->bMainSizer->Add( ctrl, 0, wxALL, 0 );
		//dlg->bMainSizer->Add(ctrl,)
	}
	dlg->bMainSizer->Layout();
	dlg->SetDisplayValue(infoSlider);
	std::vector<ColorSliderParam> infoSlider2=infoSlider;
	dlg->GetDisplayValue(infoSlider2);
	
	return wxPGWindowList(dlg,choiceWnd);

}
void DlgPropertyEditors_FloatSlider::UpdateControl( wxPGProperty* property,
					wxWindow* ctrl ) const
{
	wxString text;
	int flags = property->HasFlag(wxPG_PROP_READONLY) ? 0 : wxPG_EDITABLE_VALUE;
	text = property->GetValueString(flags);
	//get how many slider and slider info
	std::string v_in;
	_wxString2stdstring(v_in,text);
	std::vector<ColorSliderParam> infoSlider;
	if (m_isColor)
	{
		PropertyHelperFunc::StringToColor(infoSlider,v_in);
	}
	else
	{
		PropertyHelperFunc::StringToFloatArray(infoSlider,v_in);
	}
	if ( ctrl->IsKindOf(wxCLASSINFO(DlgPropertyEditors_Color_Pane)))
	{
		DlgPropertyEditors_Color_Pane* dlg = (DlgPropertyEditors_Color_Pane*)ctrl;
		dlg->SetDisplayValue(infoSlider);
		std::vector<ColorSliderParam> infoSlider2=infoSlider;
		dlg->GetDisplayValue(infoSlider2);
		return;
	}
}
bool DlgPropertyEditors_FloatSlider::OnEvent( wxPropertyGrid* propgrid,
			  wxPGProperty* property,
			  wxWindow* primaryCtrl,
			  wxEvent& event ) const
{
	if(!primaryCtrl->IsKindOf(wxCLASSINFO(DlgPropertyEditors_Color_Pane)))
	{
		return false;
	}
	DlgPropertyEditors_Color_Pane* dlg=(DlgPropertyEditors_Color_Pane*)primaryCtrl;
	if(wxEVT_COMMAND_TEXT_ENTER==event.GetEventType())
	{
		event.Skip();
		wxString text;
		text = property->GetValueString(property->HasFlag(wxPG_PROP_READONLY) ? 0 : wxPG_EDITABLE_VALUE);
		//get how many slider and slider info
		std::string v_in;
		_wxString2stdstring(v_in,text);
		std::vector<ColorSliderParam> infoSlider;
		if (m_isColor)
		{
			PropertyHelperFunc::StringToColor(infoSlider,v_in);
		}
		else
		{
			PropertyHelperFunc::StringToFloatArray(infoSlider,v_in);
		}
		dlg->SetDisplayValue(infoSlider);
		propgrid->EditorsValueWasModified();
		return true;
	}
	/*bool ret = DlgPropertyEditors_Base::OnEvent(propgrid,property,primaryCtrl,event);
	if (ret)
	{
		return true;
	}*/
	if(event.GetEventType() == wxEVT_SCROLL_CHANGED
		||event.GetEventType() == wxEVT_SCROLL_THUMBTRACK
		||wxEVT_COMMAND_TEXT_ENTER==event.GetEventType())
	{
		// Update the value   
		event.Skip();
		propgrid->EditorsValueWasModified();
		return true;
	}
	return false;
}
bool DlgPropertyEditors_FloatSlider::GetValueFromControl( wxVariant& variant,
						  wxPGProperty* property,
						  wxWindow* ctrl ) const
{
	/*if (DlgPropertyEditors_Base::GetValueFromControl(variant,property,ctrl))
	{
	return true;
	}*/
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
	if (m_isColor)
	{
		PropertyHelperFunc::StringToColor(infoSlider,v_in);
	}
	else
	{
		PropertyHelperFunc::StringToFloatArray(infoSlider,v_in);
	}
	//PropertyHelperFunc::StringToFloatArray(infoSlider,v_in);
	dlg->GetDisplayValue(infoSlider);
	std::string theValue;
	if (m_isColor)
	{
		PropertyHelperFunc::ColorToString(infoSlider,theValue);
	}
	else
	{
		PropertyHelperFunc::FloatArrayToString(infoSlider,theValue);
	}
	wxClassInfo* theClass = property->GetClassInfo();
	wxString setValue(theValue.c_str());
	variant=setValue;
	return true;
}
//void DlgPropertyEditors_FloatSlider::SetValueToUnspecified( wxPGProperty* property,
//							wxWindow* ctrl ) const
//{
//	wxPGEditor::SetValueToUnspecified(property,ctrl);
//}

void DlgPropertyEditors_FloatSlider::DrawValue( wxDC& dc,
				const wxRect& rect,
				wxPGProperty* property,
				const wxString& text ) const
{
	wxString s = property->GetValueAsString();
	std::string v_in(s.c_str());
	std::vector<ColorSliderParam> infoSlider;
	if (m_isColor)
	{
		PropertyHelperFunc::StringToColor(infoSlider,v_in);
	}
	else
	{
		PropertyHelperFunc::StringToFloatArray(infoSlider,v_in);
	}
	int colorv[4]={0,0,0,0};
	for (unsigned int i=0;i<infoSlider.size()&&i<4;i++)
	{
		ColorSliderParam& info = infoSlider[i];
		colorv[i%4] = 255.0*(info.m_value-info.m_minValue)/(info.m_maxValue-info.m_minValue);
	}
	wxRect myrc=rect;
	myrc.Deflate(1,1);
	wxColour color;
	color.Set(colorv[0],colorv[1],colorv[2],colorv[3]);
	wxBrush brush(color);
	dc.SetBrush(brush);
	dc.DrawRectangle(myrc);
	dc.DrawText(s,myrc.GetLeftTop());
}

//void DlgPropertyEditors_FloatSlider::SetControlIntValue( wxPGProperty* property,
//								 wxWindow* ctrl,
//								 int value ) const
//{
//	
//}
	
	
