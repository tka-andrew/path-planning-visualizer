#include "robotPanel.h"

wxBEGIN_EVENT_TABLE(RobotGeometryPanel, wxPanel)
    EVT_PAINT(RobotGeometryPanel::OnPaint)
    EVT_SIZE(RobotGeometryPanel::OnSize)
    EVT_ERASE_BACKGROUND(RobotGeometryPanel::OnErase)
    EVT_MOTION(RobotGeometryPanel::OnMotion)
    EVT_LEFT_DOWN(RobotGeometryPanel::OnLeftMouseClicked)
    EVT_RIGHT_DOWN(RobotGeometryPanel::OnRightMouseClicked)
wxEND_EVENT_TABLE()