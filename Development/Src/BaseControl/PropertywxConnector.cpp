#include "stdafx.h"
#include "PropertywxConnector.h"
#include "IGuiPropertyProvider.h"
#include "IGuiPropertyDescriptor.h"
#include "DlgPropertyEditors.h"

#include <wx/propgrid/propgrid.h>



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
	//wxPropertyGrid::()
	grid->RegisterEditorClass(new DlgPropertyEditors_Color);
}
void PropertywxConnector::Update(void)
{
	//m_wxGrid->RegisterAdditionalEditors();
	m_wxGrid->Clear();
	if(!m_currentProvider)
	{
		return;
	}
	static DlgPropertyEditors_Color* colorEditor = new DlgPropertyEditors_Color;
	for(unsigned int i=0;i<m_currentProvider->GetDesciptorList().size();i++)
	{
		IGuiPropertyDescriptor* desc = m_currentProvider->GetDesciptorList()[i];
		MyPGProperty* prop = new MyPGProperty;
		prop->Bind(desc);
		wxPGProperty* colProp = m_wxGrid->Append(prop);
		if(desc->GetEditorType()=="ColorSlider"
		   ||desc->GetEditorType()=="FloatSlider")
	   {
			//m_wxGrid->Append(wxColourProperty(wxT("Text Colour")));
			m_wxGrid->SetPropertyEditor(colProp,colorEditor);
		   
	   }
	}
}
void PropertywxConnector::ShowPropertyProvider(IGuiPropertyProvider* provider)
{
	m_currentProvider=provider;
	Update();
}











