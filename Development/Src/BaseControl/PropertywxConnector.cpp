#include "stdafx.h"
#include "PropertywxConnector.h"
#include "IGuiPropertyProvider.h"
#include "IGuiPropertyDescriptor.h"

#include <wx/propgrid/propgrid.h>


class MyPGProperty
	:public wxPGProperty
{
protected:
	IGuiPropertyDescriptor*	m_desc;
public:
	MyPGProperty( const wxString& label = wxPG_LABEL,
				const wxString& name = wxPG_LABEL,
				const wxString& value = wxEmptyString )
		: wxPGProperty(label, name)
	{
		// m_value is wxVariant
		m_value = value;
	}
	virtual ~MyPGProperty() { }
	
	void Bind(IGuiPropertyDescriptor* desc)
	{
		m_desc=desc;
		this->SetLabel(m_desc->GetDisplayName().c_str());
		DoGetValue();
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

	virtual wxString ValueToString( wxVariant& value,
									int argFlags ) const
	{
		// TODO: Convert given property value to a string
		wxString s = value;
		return s;
	}

	virtual bool StringToValue( wxVariant& variant, const wxString& text, int argFlags )
	{
		// TODO: Adapt string to property value.
		std::string s;
		s.assign(text.c_str(),text.size());
		m_desc->SetValue(s);
		return true;
	}
};

PropertywxConnector::PropertywxConnector(void)
:m_wxGrid(0),m_currentProvider(0)
{
	
}
PropertywxConnector::~PropertywxConnector(void)
{
	if(m_wxGrid)
	{
		m_wxGrid->Clear();	
	}
}
void PropertywxConnector::AssignwxControl(wxPropertyGrid* grid)
{
	m_wxGrid=grid;
}
void PropertywxConnector::Update(void)
{
	m_wxGrid->Clear();
	if(!m_currentProvider)
	{
		return;
	}
	for(unsigned int i=0;i<m_currentProvider->GetDesciptorList().size();i++)
	{
		IGuiPropertyDescriptor* desc = m_currentProvider->GetDesciptorList()[i];
		MyPGProperty* prop = new MyPGProperty;
		prop->Bind(desc);
	}
}
void PropertywxConnector::ShowPropertyProvider(IGuiPropertyProvider* provider)
{
	m_currentProvider=provider;
	Update();
}











