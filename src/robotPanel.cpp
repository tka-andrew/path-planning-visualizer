#include "robotPanel.h"

void RobotGeometryPanel::OnLeftMouseClicked(wxMouseEvent &event)
{
    this->resetDrawing();
    isLeftMouseClicked = true;
}