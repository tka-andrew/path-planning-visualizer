#include "mainFrame.h"
#include "DotPanel.h"
#include "util.h"

#include <opencv2/opencv.hpp>

wxBEGIN_EVENT_TABLE(DotPanel, wxPanel)
    EVT_PAINT(DotPanel::OnPaint)
    EVT_SIZE(DotPanel::OnSize)
    EVT_ERASE_BACKGROUND(DotPanel::OnErase)
    EVT_LEFT_DOWN(DotPanel::OnLeftMouseClicked)
wxEND_EVENT_TABLE()

DotPanel::DotPanel(wxPanel *parent, wxColor dotColor)
    : wxPanel(parent, wxID_ANY, wxDefaultPosition,
              wxSize(-1, -1), wxBORDER_SUNKEN)
{
    m_parent = parent;
    m_dotColor = dotColor;
    // REFERENCE: https://docs.wxwidgets.org/3.0/classwx_auto_buffered_paint_d_c.html
    this->SetBackgroundStyle(wxBG_STYLE_PAINT);
    this->resetDrawing();
}

void DotPanel::resetDrawing()
{
    MainFrame *mainFrame = (MainFrame *)m_parent->GetParent();

    wxBitmap environmentDrawing = wxBitmap(mainFrame->m_environmentGeometryPanel->m_drawing);
    wxImage environmentDrawing_img = environmentDrawing.ConvertToImage();
    cv::Mat environmentImg = OpenCV_wxWidgets::cvMat_from_wxImage( environmentDrawing_img );
    cv::Mat environmentImg_gray;
    cv::cvtColor(environmentImg.clone(), environmentImg_gray, cv::COLOR_BGR2GRAY);
    cv::Mat environmentImg_thresh;
    cv::threshold(environmentImg_gray, environmentImg_thresh, 0, 127, cv::THRESH_BINARY_INV);
    std::vector<std::vector<cv::Point> > contours;
    std::vector<cv::Vec4i> hierarchy;
    cv::findContours(environmentImg_thresh, contours, hierarchy, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE );
    cv::Mat originalThresh = cv::Mat::zeros( environmentImg_gray.size(), CV_8UC3 );
    cv::Mat cspace = cv::Mat::zeros( environmentImg_gray.size(), CV_8UC3 );
    float contourRadius = mainFrame->m_robotGeometryPanel->m_robotBoundingRadius;
    contourRadius += contourRadius; // the contour is actually drawn along the edge of contour, so we need another half of it
    for( size_t i = 0; i< contours.size(); i++ )
    {
        cv::drawContours( originalThresh, contours, (int)i, cv::Scalar(255,255,255), -1, cv::LINE_8 );
        cv::drawContours( cspace, contours, (int)i, cv::Scalar(255,255,255), contourRadius, cv::LINE_8 );
    }

    // draw contour around the boundary
    std::vector<std::vector<cv::Point> > boundaryContours;
    std::vector<cv::Point> cornerPoints;
    cornerPoints.push_back({0,0});
    cornerPoints.push_back({0,environmentImg.size().height});
    cornerPoints.push_back({environmentImg.size().width,environmentImg.size().height});
    cornerPoints.push_back({environmentImg.size().width,0});
    boundaryContours.push_back(cornerPoints);
    cv::drawContours( cspace, boundaryContours, 0, cv::Scalar(255,255,255), contourRadius, cv::LINE_8 );

    cv::bitwise_or(originalThresh, cspace, cspace);
    cv::bitwise_not(cspace, cspace);

    wxImage m_img = OpenCV_wxWidgets::wxImage_from_cvMat(cspace);
    m_cspaceMatImg = cspace;
    m_cspace = wxBitmap(m_img);
    m_drawing = wxBitmap(m_img);
    this->Refresh();
}

void DotPanel::OnPaint(wxPaintEvent &evt)
{
    if (dotPoseX != -1 && dotPoseY != -1)
    {
        wxMemoryDC mdc(m_drawing);

        mdc.SelectObject(m_drawing);
        mdc.SetBrush(m_dotColor);
        mdc.SetPen(wxPen(m_dotColor, 5));

        mdc.DrawRectangle(dotPoseX, dotPoseY, 5, 5);

        mdc.SetPen(wxNullPen);
        mdc.SelectObject(wxNullBitmap);
    }
    wxAutoBufferedPaintDC dc(this);
    dc.DrawBitmap(m_drawing, 0, 0);
}

void DotPanel::OnSize(wxSizeEvent &evt)
{
    if (!initialSizeTaken)
    {
        MainFrame *mainFrame = (MainFrame *)m_parent->GetParent();
        clientAreaHeight = mainFrame->m_environmentGeometryPanel->getClientAreaHeight();
        clientAreaWidth = mainFrame->m_environmentGeometryPanel->getClientAreaWidth();
        this->resetDrawing();
        initialSizeTaken = true; // to ensure a fixed size bitmap
    }
}

// REFERENCE: https://wiki.wxwidgets.org/Flicker-Free_Drawing#:~:text=Flicker%20free%20drawing%20can%20be,event%20and%20a%20paint%20event.
// To avoid flickering
void DotPanel::OnErase(wxEraseEvent &event)
{
    return;
}

void DotPanel::OnLeftMouseClicked(wxMouseEvent &event)
{
    int x, y;
    event.GetPosition(&x, &y);
    
    if (x>=clientAreaWidth || y>=clientAreaHeight || x<0 || y<0)
        return;

    resetDrawing();
    
    dotPoseX = x;
    dotPoseY = y;

    // we need 2 different DC here
    // wxClientDC for visualization
    // wxMemoryDC for updating the bitmap, so that later wxAutoBufferedPaintDC can draw it in OnPaint() function
    wxClientDC cdc = wxClientDC(this);
    wxMemoryDC mdc(m_drawing);

    mdc.SelectObject(m_drawing);
    cdc.SetPen(wxPen(m_dotColor, 5));
    cdc.SetBrush(m_dotColor);
    mdc.SetBrush(cdc.GetBrush());
    mdc.SetPen(cdc.GetPen());

    cdc.DrawRectangle(x, y, 5, 5);
    mdc.DrawRectangle(x, y, 5, 5);

    cdc.SetPen(wxNullPen);
    mdc.SetPen(wxNullPen);
    mdc.SelectObject(wxNullBitmap);
    this->Refresh(); // to trigger refresh
}