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
    wxButton *m_defineEnvironment;
    wxButton *m_defineRobot;
    wxButton *m_defineStartPose;
    wxButton *m_defineGoalPose;
    wxButton *m_pathFinding;
    wxButton *m_startSimulation;
    wxComboBox *m_decompositionSelection;
    wxComboBox *m_algoSelection;
    wxPanel *pParent;
};

#endif // LEFT_PANEL_H