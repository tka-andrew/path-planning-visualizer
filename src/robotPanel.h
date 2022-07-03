#ifndef ROBOT_PANEL_H
#define ROBOT_PANEL_H

#include "DrawingPanel.h"
#include "constants.h"

class RobotGeometryPanel : public DrawingPanel
{
public:
    // REFERENCE: https://stackoverflow.com/questions/347358/inheriting-constructors
    using DrawingPanel::DrawingPanel;
    void onLeftMouseClicked(wxMouseEvent& event) override;
    void onLeftMouseUp(wxMouseEvent& event) override;
    void onRightMouseUp(wxMouseEvent& event) override;
    void checkRobotContour();
    void resetDrawing() override;
    float m_robotBoundingRadius = -1;
};

#endif