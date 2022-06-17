#ifndef ROBOT_PANEL_H
#define ROBOT_PANEL_H

#include "DrawingPanel.h"
#include "constants.h"

class RobotGeometryPanel : public DrawingPanel
{
public:
    // REFERENCE: https://stackoverflow.com/questions/347358/inheriting-constructors
    using DrawingPanel::DrawingPanel;
    wxDECLARE_EVENT_TABLE();
};

#endif