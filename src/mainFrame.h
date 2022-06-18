#ifndef MAINFRAME_H
#define MAINFRAME_H

#include "constants.h"
#include "panels.h"
#include "environmentPanel.h"
#include "robotPanel.h"
#include "DotPanel.h"
#include "simpleDecompositionPanel.h"

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
    wxPanel *m_parent;
    wxBoxSizer *m_sizer;
    int currentPanel = 1;
    void switchPanel(int panelNum);

private:
    void OnExit(wxCommandEvent &event);
    void OnAbout(wxCommandEvent &event);
    void OnUsageGuide(wxCommandEvent &event);
    wxDECLARE_EVENT_TABLE();
};

#endif