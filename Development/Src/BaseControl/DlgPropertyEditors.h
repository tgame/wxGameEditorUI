//tgame
#ifndef _H_20121016_DlgPropertyEditors
#define _H_20121016_DlgPropertyEditors

#include <wx/wx.h>
#include <wx/propgrid/propgrid.h>
#include <wx/propgrid/editors.h>
#include "IGuiPropertyProvider.h"
#include "IGuiPropertyDescriptor.h"


class MyPGProperty
	:public wxPGProperty
{
protected:
	IGuiPropertyDescriptor*	m_desc;
public:
	DECLARE_DYNAMIC_CLASS(MyPGProperty);
	MyPGProperty( const wxString& label = wxPG_LABEL,
				const wxString& name = wxPG_LABEL,
				const wxString& value = wxEmptyString )
		: wxPGProperty(label, name)
	{
		m_value = value;
	}
	virtual ~MyPGProperty() { 
		}
	
	void Bind(IGuiPropertyDescriptor* desc)
	{
		m_desc=desc;
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
	}
    virtual wxVariant DoGetValue() const {
		if(m_desc)
		{
			wxString s;
			const std::string& v= m_desc->GetValue();
			s.assign(v.c_str(),v.size());
			wxVariant rv =s;
			return rv;
		}
		return m_value; }

	const wxPGEditor* DoGetEditorClass() const
	{
		// Determines editor used by property.
		// You can replace 'TextCtrl' below with any of these
		// builtin-in property editor identifiers: Choice, ComboBox,
		// TextCtrlAndButton, ChoiceAndButton, CheckBox, SpinCtrl,
		// DatePickerCtrl.
		return wxPGEditor_TextCtrl;
	}
	virtual void OnSetValue ();

	virtual wxString ValueToString( wxVariant& value,
									int argFlags ) const
	{
		// TODO: Convert given property value to a string
		wxString s = value;
		return s;
	}
	virtual bool StringToValue( wxVariant& variant, const wxString& text, int argFlags ) const;
	//virtual bool StringToValue( wxVariant& variant, const wxString& text, int argFlags );
    virtual bool IntToValue( wxVariant& value,
                             int number,
                             int argFlags = 0 ) const
	 {
		 std::vector<std::string>* choiceList=m_desc->GetStandardValues();
		 if(m_desc->GetStandardValuesSupported()&&choiceList&&number<choiceList->size())
		 {
			 std::string& v = choiceList->at(number);
			 value=v.c_str();
			 return true;
		 }
		 return false;
	 }
	 virtual wxPGEditorDialogAdapter* GetEditorDialog() const
	 {
		 //return new wxSingleChoiceDialogAdapter(m_choices);
		 return 0;
	 }
    //virtual int GetChoiceSelection() const;
};

class DlgPropertyEditors_Color
	:public wxPGEditor
{
public:
	DlgPropertyEditors_Color(void);
    virtual wxString GetName() const{
		return wxString("ColorSlider");
	}
    virtual wxPGWindowList CreateControls(wxPropertyGrid* propgrid,
                                          wxPGProperty* property,
                                          const wxPoint& pos,
                                          const wxSize& size) const;
    virtual void UpdateControl( wxPGProperty* property,
                                wxWindow* ctrl ) const;
    virtual bool OnEvent( wxPropertyGrid* propgrid,
                          wxPGProperty* property,
                          wxWindow* primaryCtrl,
                          wxEvent& event ) const;
    virtual bool GetValueFromControl( wxVariant& variant,
                                      wxPGProperty* property,
                                      wxWindow* ctrl ) const;
    virtual void SetValueToUnspecified( wxPGProperty* property,
                                        wxWindow* ctrl ) const;

    virtual void DrawValue( wxDC& dc,
                            const wxRect& rect,
                            wxPGProperty* property,
                            const wxString& text ) const;
    //virtual wxPGCellRenderer* GetCellRenderer() const;

    virtual void SetControlIntValue( wxPGProperty* property,
                                     wxWindow* ctrl,
                                     int value ) const;
protected:
};

class DlgPropertyEditors_FloatSlider
	:public DlgPropertyEditors_Color
{
public:
    virtual wxString GetName() const{
		return wxString("FloatSlider");
	}
	
};




#endif