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
	//grid->RegisterEditorClass(new DlgPropertyEditors_FloatSlider(true));
	//grid->RegisterEditorClass(new DlgPropertyEditors_FloatSlider(false));
}
void PropertywxConnector::Update(void)
{
	//m_wxGrid->RegisterAdditionalEditors();
	m_wxGrid->Clear();
	if(!m_currentProvider)
	{
		return;
	}
	AddChildPropertyProvider(0,m_currentProvider);
}
void PropertywxConnector::AddChildPropertyProvider(MyPGProperty* parent,IGuiPropertyProvider* provider)
{
	for(unsigned int i=0;i<provider->GetDesciptorList().size();i++)
	{
		IGuiPropertyDescriptor* desc = provider->GetDesciptorList()[i];
		MyPGProperty* prop = new MyPGProperty;
		prop->Bind(desc);
		//if(desc)
		if(parent)
		{
			parent->AppendChild(prop);
		}
		else
		{			
			wxPGProperty* colProp = m_wxGrid->Append(prop);
		}
		if(desc->GetChildrenPropertyProvider())
		{
			AddChildPropertyProvider(prop,desc->GetChildrenPropertyProvider());
		}
	}
}
void PropertywxConnector::ShowPropertyProvider(IGuiPropertyProvider* provider)
{
	m_currentProvider=provider;
	Update();
}











