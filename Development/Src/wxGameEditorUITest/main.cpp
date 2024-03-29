/*********************************************************************
 * Name:      	main.cpp
 * Purpose:   	Implements simple wxWidgets application with GUI
 * 				created using wxFormBuilder.
 * Author:    
 * Created:   
 * Copyright: 
 * License:   	wxWidgets license (www.wxwidgets.org)
 * 
 * Notes:		Note that all GUI creation code is implemented in
 * 				gui.cpp source file which is generated by wxFormBuilder.
 *********************************************************************/

#include "main.h"
#include <wx/propgrid/propgrid.h>
#include <wx/propgrid/advprops.h>
#include "../BaseControl/BaseControl.h"
#include "PropTest.h"
#include "../BaseControl/CurveWnd.h"

// initialize the application
IMPLEMENT_APP(MainApp);

////////////////////////////////////////////////////////////////////////////////
// application class implementation 
////////////////////////////////////////////////////////////////////////////////

bool MainApp::OnInit()
{
	SetTopWindow( new MainFrame( NULL ) );
	GetTopWindow()->Show();
	
	// true = enter the main loop
	return true;
}

////////////////////////////////////////////////////////////////////////////////
// main application frame implementation 
////////////////////////////////////////////////////////////////////////////////

MainFrame::MainFrame(wxWindow *parent) : MainFrameBase( parent )
{
	wxSize s(600,600);
	wxPropertyGrid* m_propGrid = new wxPropertyGrid(
        this, // parent
        -1, // id
        wxDefaultPosition, // position
        s,//wxDefaultSize, // size
        // Some specific window styles - for all additional styles,
        // see Modules->PropertyGrid Window Styles
        wxPG_AUTO_SORT | // Automatic sorting after items added
        wxPG_SPLITTER_AUTO_CENTER | // Automatically center splitter until user manually adjusts it
        // Default style
        wxPG_DEFAULT_STYLE );
	PropertywxConnector* conn=new PropertywxConnector;
	conn->AssignwxControl(m_propGrid);
    // Add int property
    m_propGrid->Append( new wxIntProperty(wxT("IntProperty"), wxPG_LABEL, 12345678) );
    // Add float property (value type is actually double)
    m_propGrid->Append( new wxColourProperty(wxT("ccProperty"), wxPG_LABEL, wxPG_COLOUR(255,255,0)) );
	
	CCurveWnd* curveWnd = new CCurveWnd(this);

    m_auiManage.SetManagedWindow(this);
	m_auiManage.AddPane(m_propGrid,wxLEFT,"MainFramePane");
	m_auiManage.AddPane(curveWnd,wxCENTER,"Curve");
	//m_auiManage.AddPane(curveWnd,wxRIGHT,"Curve");
	//m_auiManage.AddPane(m_panel1,wxCENTER,"Draw");
	m_auiManage.Update();
	
	TestPropertyProvider* prop = new TestPropertyProvider;
	prop->CreateSomeChild(prop->m_mayHaveChild);
	conn->ShowPropertyProvider(prop);
}

MainFrame::~MainFrame()
{
	m_auiManage.UnInit();
}

void MainFrame::OnCloseFrame(wxCloseEvent& event)
{
	Destroy();
}

void MainFrame::OnExitClick(wxCommandEvent& event)
{
	Destroy();
}
