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
    void OnDefineEnvironment(wxCommandEvent & event);

    wxButton *m_defineEnvironment;
    wxStaticText *m_startingPoint;
    wxStaticText *m_destinationPoint;
    wxPanel *m_parent;
};

const int ID_DEFINE_ENVIRONMENT = 101;

#endif // PANELS_H