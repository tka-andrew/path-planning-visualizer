#include "visibilityGraphPanel.h"
#include "mainFrame.h"
#include "util.h"

#include <opencv2/opencv.hpp>

wxBEGIN_EVENT_TABLE(VisibilityGraphPanel, wxPanel)
    EVT_PAINT(VisibilityGraphPanel::OnPaint)
    EVT_ERASE_BACKGROUND(VisibilityGraphPanel::OnErase)
wxEND_EVENT_TABLE()

VisibilityGraphPanel::VisibilityGraphPanel(wxPanel *parent)
    : wxPanel(parent, wxID_ANY, wxDefaultPosition,
              wxSize(-1, -1), wxBORDER_SUNKEN)
{
    m_parent = parent;
    // REFERENCE: https://docs.wxwidgets.org/3.0/classwx_auto_buffered_paint_d_c.html
    this->SetBackgroundStyle(wxBG_STYLE_PAINT);
}

void VisibilityGraphPanel::constructGraph()
{
    MainFrame *mainFrame = (MainFrame *)m_parent->GetParent();
    m_drawing = wxBitmap(mainFrame->m_goalPosePanel->m_cspace);
    this->Refresh();
}

void VisibilityGraphPanel::OnPaint(wxPaintEvent &evt)
{
    wxAutoBufferedPaintDC dc(this);
    dc.DrawBitmap(m_drawing, 0, 0);
}

// REFERENCE: https://wiki.wxwidgets.org/Flicker-Free_Drawing#:~:text=Flicker%20free%20drawing%20can%20be,event%20and%20a%20paint%20event.
// To avoid flickering
void VisibilityGraphPanel::OnErase(wxEraseEvent &event)
{
    return;
}
