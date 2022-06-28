#include "visibilityGraphPanel.h"
#include "mainFrame.h"
#include "util.h"

#include <opencv2/opencv.hpp>

#include <vector>

wxBEGIN_EVENT_TABLE(VisibilityGraphPanel, wxPanel)
    EVT_PAINT(VisibilityGraphPanel::OnPaint)
    EVT_ERASE_BACKGROUND(VisibilityGraphPanel::OnErase)
wxEND_EVENT_TABLE()

VisibilityGraphPanel::VisibilityGraphPanel(wxPanel *parent)
    : wxPanel(parent, wxID_ANY, wxDefaultPosition,
              wxSize(-1, -1), wxBORDER_SUNKEN)
{
    m_parent = parent;
    // REFERENCE: https://docs.wxwidgets.org/3.0/classwx_auto_buffered_paint_d_c.html
    this->SetBackgroundStyle(wxBG_STYLE_PAINT);
}

void VisibilityGraphPanel::constructGraph()
{
    MainFrame *mainFrame = (MainFrame *)m_parent->GetParent();

    cv::Mat cspaceMatImg = mainFrame->m_goalPosePanel->m_cspaceMatImg;
    cv::Mat cspaceMatImg_gray;
    cv::cvtColor(cspaceMatImg.clone(), cspaceMatImg_gray, cv::COLOR_BGR2GRAY);

    cv::Mat canny_output;
    cv::Canny( cspaceMatImg_gray, canny_output, 0, 200 );
    std::vector<std::vector<cv::Point> > contours;
    cv::findContours( canny_output, contours, cv::RETR_TREE, cv::CHAIN_APPROX_SIMPLE );

    std::vector<std::vector<cv::Point> >hull( contours.size() );
    for( size_t i = 0; i < contours.size(); i++ )
    {
        cv::convexHull( contours[i], hull[i] );
    }
    cv::Mat drawing = cv::Mat::zeros( canny_output.size(), CV_8UC3 );

    for( size_t i = 0; i < contours.size(); i++ )
    {
        cv::RotatedRect rotatedRect = cv::minAreaRect(contours[i]);
        cv::Point2f rect_points[4];
        rotatedRect.points( rect_points );
        for ( int j = 0; j < 4; j++ )
        {
            cv::line( drawing, rect_points[j], rect_points[(j+1)%4], cv::Scalar(0,255,0) );
        }
    }
    
    for (size_t i = 0; i< contours.size(); i++)
    {
        std::vector<cv::Point> pts = contours[i];
        cv::Point extLeft  = *min_element(pts.begin(), pts.end(), 
                            [](const cv::Point& lhs, const cv::Point& rhs) {
                                return lhs.x < rhs.x;
                        }); 
        cv::Point extRight = *max_element(pts.begin(), pts.end(),
                            [](const cv::Point& lhs, const cv::Point& rhs) {
                                return lhs.x < rhs.x;
                        });
        cv::Point extTop   = *min_element(pts.begin(), pts.end(), 
                            [](const cv::Point& lhs, const cv::Point& rhs) {
                                return lhs.y < rhs.y;
                        }); 
        cv::Point extBot   = *max_element(pts.begin(), pts.end(),
                            [](const cv::Point& lhs, const cv::Point& rhs) {
                                return lhs.y < rhs.y;
                        });
        cv::circle(drawing, extLeft, 5, cv::Scalar(255,0,0), 5);
        cv::circle(drawing, extRight, 5, cv::Scalar(255,255,0), 5);
        cv::circle(drawing, extTop, 5, cv::Scalar(255,0,255), 5);
        cv::circle(drawing, extBot, 5, cv::Scalar(0,255,0), 5);
        cv::drawContours( drawing, contours, (int)i, cv::Scalar(255,255,255), 2, cv::LINE_8 );
    }

    cv::Mat drawing_gray;
    cv::cvtColor(drawing.clone(), drawing_gray, cv::COLOR_BGR2GRAY);
    std::vector<std::vector<cv::Point> > drawing_contours;
    cv::findContours( drawing_gray, drawing_contours, cv::RETR_TREE, cv::CHAIN_APPROX_SIMPLE );

    for( size_t i = 0; i< hull.size(); i++ )
    {
        cv::drawContours( drawing, hull, (int)i, cv::Scalar(255,0,255), 2, cv::LINE_8 );
    }

    cv::imshow( "Hull demo", drawing );

    m_drawing = wxBitmap(mainFrame->m_goalPosePanel->m_cspace);
    this->Refresh();
}

void VisibilityGraphPanel::OnPaint(wxPaintEvent &evt)
{
    wxAutoBufferedPaintDC dc(this);
    dc.DrawBitmap(m_drawing, 0, 0);
}

// REFERENCE: https://wiki.wxwidgets.org/Flicker-Free_Drawing#:~:text=Flicker%20free%20drawing%20can%20be,event%20and%20a%20paint%20event.
// To avoid flickering
void VisibilityGraphPanel::OnErase(wxEraseEvent &event)
{
    return;
}
