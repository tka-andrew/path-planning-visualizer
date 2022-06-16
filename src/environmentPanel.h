#ifndef ENVIRONEMNT_PANEL_H
#define ENVIRONEMNT_PANEL_H

#include "constants.h"

#include <wx/wx.h>
#include <wx/dcmemory.h>
#include <wx/dcbuffer.h>

class EnvironmentGeometryPanel : public wxPanel
{
public:
    EnvironmentGeometryPanel(wxPanel *parent);
    wxPanel *m_parent;
    wxButton *m_resetDrawing;
    wxBitmap environmentDrawing;

    void OnResetDrawing(wxCommandEvent &event);

    // REFERENCE: https://wiki.wxwidgets.org/Drawing_on_a_panel_with_a_DC
    // REFERENCE: https://www.informit.com/articles/article.aspx?p=405047
    void OnPaint(wxPaintEvent & evt);
    void OnErase(wxEraseEvent& event);
    void OnMotion(wxMouseEvent& event);
    void OnLeftMouseClicked(wxMouseEvent& event);
    void OnRightMouseClicked(wxMouseEvent& event);
    void OnSize(wxSizeEvent& event);
    wxDECLARE_EVENT_TABLE();
private:
    int clientAreaWidth = 10; // dummy value, will be updated OnResize()
    int clientAreaHeight = 10; // dummy value, will be updated OnResize()
    bool initialSizeTaken = false;
    bool isLeftMouseClicked = true;
};

#endif