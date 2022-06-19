#ifndef LEFT_PANEL_H
#define LEFT_PANEL_H

#include "constants.h"

#include <wx/wx.h>

class LeftPanel : public wxPanel
{
public:
    LeftPanel(wxPanel *parent);
    void OnDefineEnvironment(wxCommandEvent &event);
    void OnDefineRobot(wxCommandEvent &event);
    void OnDefineStart(wxCommandEvent &event);
    void OnDefineGoal(wxCommandEvent &event);
    void OnPathFinding(wxCommandEvent &event);
    wxButton *m_defineEnvironment;
    wxButton *m_defineRobot;
    wxButton *m_defineStartPose;
    wxButton *m_defineGoalPose;
    wxButton *m_pathFinding;
    wxButton *m_startSimulation;
    wxComboBox *m_decompositionSelection;
    wxComboBox *m_algoSelection;
    wxPanel *m_parent;
};

#endif // LEFT_PANEL_H