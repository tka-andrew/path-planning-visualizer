#ifndef PANELS_H
#define PANELS_H

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
    wxComboBox *m_decompositionSelection;
    wxPanel *m_parent;
};

#endif // PANELS_H