#ifndef DRAWING_PANEL_H
#define DRAWING_PANEL_H

#include "constants.h"

#include <wx/wx.h>
#include <wx/dcmemory.h>
#include <wx/dcbuffer.h>

class DrawingPanel : public wxPanel
{
public:
    DrawingPanel(wxPanel *parent,  int resetButtonID);
    wxPanel *m_parent;
    wxButton *m_resetDrawing;
    wxBitmap m_drawing;

    void OnResetDrawing(wxCommandEvent &event);
    void resetDrawing();
    int getClientAreaHeight();
    int getClientAreaWidth();

    // REFERENCE: https://wiki.wxwidgets.org/Drawing_on_a_panel_with_a_DC
    // REFERENCE: https://www.informit.com/articles/article.aspx?p=405047
    void OnPaint(wxPaintEvent & evt);
    void OnErase(wxEraseEvent& event);
    void OnMotion(wxMouseEvent& event);
    virtual void OnLeftMouseClicked(wxMouseEvent& event);
    void OnRightMouseClicked(wxMouseEvent& event);
    void OnSize(wxSizeEvent& event);
    wxDECLARE_EVENT_TABLE();

protected:
    bool isLeftMouseClicked = true;

private:
    int clientAreaWidth = 10; // dummy value, will be updated OnResize()
    int clientAreaHeight = 10; // dummy value, will be updated OnResize()
    bool initialSizeTaken = false;
};

#endif