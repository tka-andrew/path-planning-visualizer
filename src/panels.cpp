#include "mainFrame.h"
#include "panels.h"
#include "util.h"

#include <opencv2/opencv.hpp>
#include <vector>

LeftPanel::LeftPanel(wxPanel *parent)
    : wxPanel(parent, -1, wxPoint(-1, -1), wxSize(200, 200), wxBORDER_SUNKEN)
{
    m_parent = parent;
    m_defineEnvironment = new wxButton(this, ID_DEFINE_ENVIRONMENT, wxT("Define environment"));
    m_defineRobot = new wxButton(this, ID_DEFINE_ROBOT, wxT("Define robot"));
    m_defineStartPose = new wxButton(this, ID_DEFINE_START, wxT("Define Start"));
    m_pathFinding = new wxButton(this, ID_PATHFINDING, wxT("Path finding"));
    m_defineEnvironment->SetBackgroundColour(wxColor(200,200,200)); // initially first button is selected

    Connect(ID_DEFINE_ENVIRONMENT, wxEVT_COMMAND_BUTTON_CLICKED,
            wxCommandEventHandler(LeftPanel::OnDefineEnvironment));
    Connect(ID_DEFINE_ROBOT, wxEVT_COMMAND_BUTTON_CLICKED,
            wxCommandEventHandler(LeftPanel::OnDefineRobot));
    Connect(ID_DEFINE_START, wxEVT_COMMAND_BUTTON_CLICKED,
            wxCommandEventHandler(LeftPanel::OnDefineStart));
    Connect(ID_PATHFINDING, wxEVT_COMMAND_BUTTON_CLICKED,
            wxCommandEventHandler(LeftPanel::OnPathFinding));

    wxBoxSizer *sizer = new wxBoxSizer(wxVERTICAL);
    sizer->Add(m_defineEnvironment, 0, wxEXPAND, 0);
    sizer->Add(m_defineRobot, 0, wxEXPAND, 0);
    sizer->Add(m_defineStartPose, 0, wxEXPAND, 0);
    sizer->Add(m_pathFinding, 0, wxEXPAND, 0);
    sizer->SetSizeHints(this);
    this->SetSizer(sizer);
}

void LeftPanel::OnDefineEnvironment(wxCommandEvent &WXUNUSED(event))
{
    MainFrame *mainFrame = (MainFrame *)m_parent->GetParent();
    if (mainFrame->currentPanel != 1)
    {
        m_defineEnvironment->SetBackgroundColour(wxColor(200,200,200));
        m_defineRobot->SetBackgroundColour(wxColor(255,255,255));
        m_defineStartPose->SetBackgroundColour(wxColor(255,255,255));
        m_pathFinding->SetBackgroundColour(wxColor(255,255,255));
        mainFrame->switchPanel(1);
        mainFrame->currentPanel = 1;
    }
}

void LeftPanel::OnDefineRobot(wxCommandEvent &WXUNUSED(event))
{
    MainFrame *mainFrame = (MainFrame *)m_parent->GetParent();
    if (mainFrame->currentPanel != 2)
    {
        m_defineEnvironment->SetBackgroundColour(wxColor(255,255,255));
        m_defineRobot->SetBackgroundColour(wxColor(200,200,200));
        m_defineStartPose->SetBackgroundColour(wxColor(255,255,255));
        m_pathFinding->SetBackgroundColour(wxColor(255,255,255));
        mainFrame->switchPanel(2);
        mainFrame->currentPanel = 2;
    }
}

void LeftPanel::OnDefineStart(wxCommandEvent &WXUNUSED(event))
{
    MainFrame *mainFrame = (MainFrame *)m_parent->GetParent();
    wxBitmap robotDrawing = wxBitmap(mainFrame->m_robotGeometryPanel->m_drawing);
    cv::Mat robotImg = OpenCV_wxWidgets::mat_from_wxbitmap(robotDrawing);
    cv::Mat robotImg_gray;
    cv::cvtColor(robotImg.clone(), robotImg_gray, cv::COLOR_BGR2GRAY);
    cv::Mat robotImg_thresh;
    cv::threshold(robotImg_gray, robotImg_thresh, 0, 100, 1);
    std::vector<std::vector<cv::Point> > contours;
    std::vector<cv::Vec4i> hierarchy;
    cv::findContours(robotImg_thresh, contours, hierarchy, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE );
    if (contours.size() != 1)
    {
        if (contours.size() >0)
            wxLogMessage("Please define one robot geometry only.");
        else
            wxLogMessage("Please define the robot geometry first.");
        return;
    }
    cv::Mat drawing = cv::Mat::ones( robotImg_gray.size(), CV_8UC3 );
    for( size_t i = 0; i< contours.size(); i++ )
    {
        cv::drawContours( drawing, contours, (int)i, cv::Scalar(255,0,0), -1, cv::LINE_8, hierarchy, 0 );
    }
    cv::imshow( "Contours", drawing );
    if (mainFrame->currentPanel != 3)
    {
        m_defineEnvironment->SetBackgroundColour(wxColor(255,255,255));
        m_defineRobot->SetBackgroundColour(wxColor(255,255,255));
        m_defineStartPose->SetBackgroundColour(wxColor(200,200,200));
        m_pathFinding->SetBackgroundColour(wxColor(255,255,255));
        mainFrame->switchPanel(3);
        mainFrame->currentPanel = 3;
    }
}

void LeftPanel::OnPathFinding(wxCommandEvent &WXUNUSED(event))
{
    MainFrame *mainFrame = (MainFrame *)m_parent->GetParent();
    if (mainFrame->currentPanel != 5)
    {
        m_defineEnvironment->SetBackgroundColour(wxColor(255,255,255));
        m_defineRobot->SetBackgroundColour(wxColor(255,255,255));
        m_defineStartPose->SetBackgroundColour(wxColor(255,255,255));
        m_pathFinding->SetBackgroundColour(wxColor(200,200,200));
        mainFrame->switchPanel(5);
        mainFrame->currentPanel = 5;
    }
}

PathFindingPanel::PathFindingPanel(wxPanel *parent)
    : wxPanel(parent, wxID_ANY, wxDefaultPosition,
              wxSize(-1, -1), wxBORDER_SUNKEN)
{

    // Create a wxGrid object
    grid = new wxGrid(this,
                      -1,
                      wxPoint(0, 0),
                      wxSize(200, 200));

    // This 2 lines must be executed before CreateGrid()
    grid->SetDefaultColSize(20);
    grid->SetDefaultRowSize(20);

    grid->CreateGrid(this->gridRow, this->gridCol);

    grid->DisableDragGridSize();
    grid->EnableEditing(false);
    grid->HideRowLabels();
    grid->HideColLabels();

    wxBoxSizer *vbox = new wxBoxSizer(wxVERTICAL);
    vbox->Add(grid, 1, wxEXPAND | wxALIGN_CENTER_HORIZONTAL | wxALL, 20);
    this->SetSizer(vbox);
}
