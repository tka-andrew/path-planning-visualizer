#ifndef VISIBILITY_GRAPH_PANEL_H
#define VISIBILITY_GRAPH_PANEL_H

#include "constants.h"

#include <wx/wx.h>
#include <wx/dcmemory.h>
#include <wx/dcbuffer.h>

class VisibilityGraphPanel : public wxPanel
{
public:
    VisibilityGraphPanel(wxPanel *parent);
    wxPanel *m_parent;
    wxBitmap m_drawing;

    void constructGraph();

    // REFERENCE: https://www.informit.com/articles/article.aspx?p=405047
    void OnPaint(wxPaintEvent & evt);
    void OnErase(wxEraseEvent& event);
    wxDECLARE_EVENT_TABLE();

};

#endif // VISIBILITY_GRAPH_PANEL_H