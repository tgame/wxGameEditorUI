//tgame
#ifndef _H_20121016_DlgPropertyEditors
#define _H_20121016_DlgPropertyEditors

#include <wx/propgrid/editors.h>


class DlgPropertyEditors_Color
	:public wxPGEditor
{
public:
	DlgPropertyEditors_Color(void);
    virtual wxString GetName() const;
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
};




#endif