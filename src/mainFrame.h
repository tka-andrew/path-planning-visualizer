#ifndef MAINFRAME_H
#define MAINFRAME_H

#include "constants.h"
#include "leftPanel.h"
#include "environmentPanel.h"
#include "robotPanel.h"
#include "DotPanel.h"
#include "simpleDecompositionPanel.h"
#include "visibilityGraphPanel.h"

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
    EnvironmentGeometryPanel *m_environmentGeometryPanel;
    RobotGeometryPanel *m_robotGeometryPanel;
    DotPanel *m_startPosePanel;
    DotPanel *m_goalPosePanel;
    SimpleDecompositionPanel *m_simpleDecompositionPanel;
    VisibilityGraphPanel *m_visibilityGraphPanel;
    wxPanel *pParent;
    wxBoxSizer *m_sizer;
    int currentPanel = 1;
    bool canSwitchPanel();
    void switchPanel(int panelNum);

private:
    void onExit(wxCommandEvent &event);
    void onAbout(wxCommandEvent &event);
    void onUsageGuide(wxCommandEvent &event);
    wxDECLARE_EVENT_TABLE();
};

#endif