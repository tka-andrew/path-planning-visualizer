#ifndef MAINFRAME_H
#define MAINFRAME_H

#include "constants.h"
#include "panels.h"

#include <wx/wx.h>
#include <wx/grid.h>
#include <wx/panel.h>

#include <array>

class wxGrid;

class MainFrame : public wxFrame
{
public:
    MainFrame(const wxString &title, const wxPoint &pos, const wxSize &size);
    LeftPanel *m_lp;
    PathFindingPanel *m_pathFindingPanel;
    EnvironmentGeometryPanel *m_environmentGeometryPanel;
    wxPanel *m_parent;
    wxBoxSizer *m_sizer;
    int currentPanel = 1;
    std::array<int, 2> startingPoint = {-1, -1};
    std::array<int, 2> destinationPoint = {-1, -1};
    bool startingPointDefined = false;
    bool destinationPointDefined = false;
    void switchPanel(int panelNum);

private:
    void OnExit(wxCommandEvent &event);
    void OnAbout(wxCommandEvent &event);
    void OnUsageGuide(wxCommandEvent &event);
    wxDECLARE_EVENT_TABLE();
};

#endif