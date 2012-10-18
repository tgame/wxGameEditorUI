///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Jun 30 2011)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#ifndef __DLGPROPERTYEDITORS_GUI_H__
#define __DLGPROPERTYEDITORS_GUI_H__

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/intl.h>
#include <wx/string.h>
#include <wx/textctrl.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/sizer.h>
#include <wx/panel.h>

///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
/// Class Dlg_Color_Title
///////////////////////////////////////////////////////////////////////////////
class Dlg_Color_Title : public wxPanel 
{
	private:
	
	protected:
		wxTextCtrl* m_colorTitle;
	
	public:
		wxBoxSizer* bMainSizer;
		
		Dlg_Color_Title( wxWindow* parent, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 500,300 ), long style = wxTAB_TRAVERSAL ); 
		~Dlg_Color_Title();
	
};

#endif //__DLGPROPERTYEDITORS_GUI_H__
