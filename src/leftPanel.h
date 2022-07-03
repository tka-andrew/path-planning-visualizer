#ifndef LEFT_PANEL_H
#define LEFT_PANEL_H

#include "constants.h"

#include <wx/wx.h>

class LeftPanel : public wxPanel
{
public:
    LeftPanel(wxPanel *parent);
    void onDefineEnvironment(wxCommandEvent &event);
    void onDefineRobot(wxCommandEvent &event);
    void onDefineStart(wxCommandEvent &event);
    void onDefineGoal(wxCommandEvent &event);
    void onPathFinding(wxCommandEvent &event);
    void onStartSimulation(wxCommandEvent &WXUNUSED(event));
    void SimpleDecompositionPathFinding(wxString algoSelected);
    wxButton *pDefineEnvironmentBtn;
    wxButton *pDefineRobotBtn;
    wxButton *pDefineStartPoseBtn;
    wxButton *pDefineGoalPoseBtn;
    wxButton *pPathFindingBtn;
    wxButton *pStartSimulationBtn;
    wxComboBox *pDecompositionSelection;
    wxComboBox *pAlgoSelection;
    wxPanel *pParent;
};

#endif // LEFT_PANEL_H