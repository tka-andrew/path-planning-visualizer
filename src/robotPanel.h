#ifndef ROBOT_PANEL_H
#define ROBOT_PANEL_H

#include "DrawingPanel.h"
#include "constants.h"

class RobotGeometryPanel : public DrawingPanel
{
public:
    // REFERENCE: https://stackoverflow.com/questions/347358/inheriting-constructors
    using DrawingPanel::DrawingPanel;
    virtual void OnLeftMouseClicked(wxMouseEvent& event) override;
    virtual void OnLeftMouseUp(wxMouseEvent& event) override;
    virtual void OnRightMouseUp(wxMouseEvent& event) override;
    void checkRobotContour();
    float m_robotBoundingRadius = -1;
};

#endif