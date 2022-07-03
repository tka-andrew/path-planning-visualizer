#include "robotPanel.h"
#include "util.h"

#include <opencv2/opencv.hpp>

void RobotGeometryPanel::onLeftMouseClicked(wxMouseEvent &event)
{
    resetDrawing();
    isLeftMouseClicked = true;
}

void RobotGeometryPanel::onLeftMouseUp(wxMouseEvent& event)
{
    checkRobotContour();
}

void RobotGeometryPanel::onRightMouseUp(wxMouseEvent& event)
{
    checkRobotContour();
}

void RobotGeometryPanel::checkRobotContour()
{
    m_robotBoundingRadius = -1; // as an indicator of having no valid robot contour
    wxImage robotDrawing_img = m_drawing.ConvertToImage();
    cv::Mat robotImg = OpenCV_wxWidgets::cvMat_from_wxImage(robotDrawing_img);
    cv::Mat robotImg_gray;
    cv::cvtColor(robotImg.clone(), robotImg_gray, cv::COLOR_BGR2GRAY);
    cv::Mat robotImg_thresh;
    cv::threshold(robotImg_gray, robotImg_thresh, 0, 127, cv::THRESH_BINARY_INV);
    std::vector<std::vector<cv::Point> > contours;
    std::vector<cv::Vec4i> hierarchy;
    cv::findContours(robotImg_thresh, contours, hierarchy, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE );
    if (contours.size() != 1)
    {
        if (contours.size()>0)
            wxLogMessage("Please define one robot geometry only.");
        else
            wxLogMessage("Please define the robot geometry first.");
        return;
    }

    float radius{0.0};
    cv::Point2f center;
    cv::minEnclosingCircle	(contours[0], center, radius);
    m_robotBoundingRadius = ceil(radius);
}

void RobotGeometryPanel::resetDrawing()
{
    DrawingPanel::resetDrawing();
    m_robotBoundingRadius = -1; // reset this also
}