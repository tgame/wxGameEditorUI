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
	grid->RegisterEditorClass(new DlgPropertyEditors_FloatSlider(true));
	grid->RegisterEditorClass(new DlgPropertyEditors_FloatSlider(false));
}
void PropertywxConnector::Update(void)
{
	//m_wxGrid->RegisterAdditionalEditors();
	m_wxGrid->Clear();
	if(!m_currentProvider)
	{
		return;
	}
	static DlgPropertyEditors_FloatSlider* colorEditor = new DlgPropertyEditors_FloatSlider(true);
	static DlgPropertyEditors_FloatSlider* floatEditor = new DlgPropertyEditors_FloatSlider(false);
	for(unsigned int i=0;i<m_currentProvider->GetDesciptorList().size();i++)
	{
		IGuiPropertyDescriptor* desc = m_currentProvider->GetDesciptorList()[i];
		MyPGProperty* prop = new MyPGProperty;
		prop->Bind(desc);
		wxPGProperty* colProp = m_wxGrid->Append(prop);
		if(desc->GetEditorType()=="ColorSlider")
	   {
			m_wxGrid->SetPropertyEditor(colProp,colorEditor);
	   }
		else if (desc->GetEditorType()=="FloatSlider")
		{
			m_wxGrid->SetPropertyEditor(colProp,floatEditor);
		}
	}
}
void PropertywxConnector::ShowPropertyProvider(IGuiPropertyProvider* provider)
{
	m_currentProvider=provider;
	Update();
}











