#ifndef PANELS_H
#define PANELS_H

#include <wx/wx.h>
#include <wx/panel.h>
#include <wx/grid.h>


class RightPanel : public wxPanel
{
public:
    RightPanel(wxPanel *parent);
    wxGrid *grid;
    wxPanel *m_parent;
    int gridRow = 40;
    int gridCol = 60;
};

class LeftPanel : public wxPanel
{
public:

    LeftPanel(wxPanel *parent);

    wxButton *m_defineEnvironment;
    wxStaticText *m_startingPoint;
    wxStaticText *m_destinationPoint;
    wxPanel *m_parent;
};

#endif // PANELS_H