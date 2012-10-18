///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Jun 30 2011)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "DlgPropertyEditors_Gui.h"

///////////////////////////////////////////////////////////////////////////

Dlg_Color_Title::Dlg_Color_Title( wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style ) : wxPanel( parent, id, pos, size, style )
{
	bMainSizer = new wxBoxSizer( wxVERTICAL );
	
	m_colorTitle = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER|wxNO_BORDER );
	m_colorTitle->SetBackgroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_BACKGROUND ) );
	
	bMainSizer->Add( m_colorTitle, 0, wxALL|wxEXPAND, 0 );
	
	this->SetSizer( bMainSizer );
	this->Layout();
}

Dlg_Color_Title::~Dlg_Color_Title()
{
}
