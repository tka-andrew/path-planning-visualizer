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

    void onResetDrawing(wxCommandEvent &event);
    virtual void resetDrawing();
    int getClientAreaHeight();
    int getClientAreaWidth();

    // REFERENCE: https://wiki.wxwidgets.org/Drawing_on_a_panel_with_a_DC
    // REFERENCE: https://www.informit.com/articles/article.aspx?p=405047
    void onPaint(wxPaintEvent & evt);
    void onErase(wxEraseEvent& event);
    void onMotion(wxMouseEvent& event);
    virtual void onLeftMouseClicked(wxMouseEvent& event);
    virtual void onLeftMouseUp(wxMouseEvent& event);
    void onRightMouseClicked(wxMouseEvent& event);
    virtual void onRightMouseUp(wxMouseEvent& event);
    void onSize(wxSizeEvent& event);
    wxDECLARE_EVENT_TABLE();

protected:
    bool isLeftMouseClicked = true;

private:
    int clientAreaWidth = 10; // dummy value, will be updated onSize()
    int clientAreaHeight = 10; // dummy value, will be updated onSize()
    bool initialSizeTaken = false;
};

#endif