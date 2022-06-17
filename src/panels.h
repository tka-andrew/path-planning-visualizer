#ifndef PANELS_H
#define PANELS_H

#include "constants.h"
#include "environmentPanel.h"
#include "robotPanel.h"

#include <wx/wx.h>
#include <wx/panel.h>
#include <wx/grid.h>

class LeftPanel : public wxPanel
{
public:
    LeftPanel(wxPanel *parent);
    void OnDefineEnvironment(wxCommandEvent &event);
    void OnDefineRobot(wxCommandEvent &event);
    void OnPathFinding(wxCommandEvent &event);
    wxButton *m_defineEnvironment;
    wxButton *m_defineRobot;
    wxButton *m_pathFinding;
    wxPanel *m_parent;
};

class PathFindingPanel : public wxPanel
{
public:
    PathFindingPanel(wxPanel *parent);
    wxGrid *grid;
    wxPanel *m_parent;
    int gridRow = 40;
    int gridCol = 60;
};
#endif // PANELS_H