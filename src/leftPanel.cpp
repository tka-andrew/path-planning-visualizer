#include "mainFrame.h"
#include "leftPanel.h"
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
    m_defineGoalPose = new wxButton(this, ID_DEFINE_GOAL, wxT("Define Goal"));
    m_pathFinding = new wxButton(this, ID_PATHFINDING, wxT("Path finding"));
    m_defineEnvironment->SetBackgroundColour(wxColor(200,200,200)); // initially first button is selected

    wxArrayString decompositionChoices;
    decompositionChoices.Add(wxT("Simple Cell Decomposition"));
    m_decompositionSelection = new wxComboBox(this, ID_DECOMPOSTION_SELECTION, "", wxDefaultPosition, wxSize(100, -1), decompositionChoices);

    Connect(ID_DEFINE_ENVIRONMENT, wxEVT_COMMAND_BUTTON_CLICKED,
            wxCommandEventHandler(LeftPanel::OnDefineEnvironment));
    Connect(ID_DEFINE_ROBOT, wxEVT_COMMAND_BUTTON_CLICKED,
            wxCommandEventHandler(LeftPanel::OnDefineRobot));
    Connect(ID_DEFINE_START, wxEVT_COMMAND_BUTTON_CLICKED,
            wxCommandEventHandler(LeftPanel::OnDefineStart));
    Connect(ID_DEFINE_GOAL, wxEVT_COMMAND_BUTTON_CLICKED,
            wxCommandEventHandler(LeftPanel::OnDefineGoal));
    Connect(ID_PATHFINDING, wxEVT_COMMAND_BUTTON_CLICKED,
            wxCommandEventHandler(LeftPanel::OnPathFinding));

    wxBoxSizer *sizer = new wxBoxSizer(wxVERTICAL);
    sizer->Add(m_defineEnvironment, 0, wxEXPAND, 0);
    sizer->Add(m_defineRobot, 0, wxEXPAND, 0);
    sizer->Add(m_defineStartPose, 0, wxEXPAND, 0);
    sizer->Add(m_defineGoalPose, 0, wxEXPAND, 0);
    sizer->Add(m_decompositionSelection, 0, wxEXPAND, 0);
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
        m_defineGoalPose->SetBackgroundColour(wxColor(255,255,255));
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
        m_defineGoalPose->SetBackgroundColour(wxColor(255,255,255));
        m_pathFinding->SetBackgroundColour(wxColor(255,255,255));
        mainFrame->switchPanel(2);
        mainFrame->currentPanel = 2;
    }
}

void LeftPanel::OnDefineStart(wxCommandEvent &WXUNUSED(event))
{
    MainFrame *mainFrame = (MainFrame *)m_parent->GetParent();
    wxBitmap robotDrawing = wxBitmap(mainFrame->m_robotGeometryPanel->m_drawing);
    wxImage robotDrawing_img = robotDrawing.ConvertToImage();
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
    mainFrame->m_robotGeometryPanel->m_robotBoundingRadius = ceil(radius);

    if (mainFrame->currentPanel != 3)
    {
        m_defineEnvironment->SetBackgroundColour(wxColor(255,255,255));
        m_defineRobot->SetBackgroundColour(wxColor(255,255,255));
        m_defineStartPose->SetBackgroundColour(wxColor(200,200,200));
        m_defineGoalPose->SetBackgroundColour(wxColor(255,255,255));
        m_pathFinding->SetBackgroundColour(wxColor(255,255,255));
        mainFrame->switchPanel(3);
        mainFrame->currentPanel = 3;
    }
}

void LeftPanel::OnDefineGoal(wxCommandEvent &WXUNUSED(event))
{
    MainFrame *mainFrame = (MainFrame *)m_parent->GetParent();
    int startPoseX = mainFrame->m_startPosePanel->dotPoseX;
    int startPoseY = mainFrame->m_startPosePanel->dotPoseY; 
    if (startPoseX == -1 || startPoseY == -1)
    {
        wxLogMessage("Please define start pose first.");
        return;
    }

    if (mainFrame->currentPanel != 4)
    {
        m_defineEnvironment->SetBackgroundColour(wxColor(255,255,255));
        m_defineRobot->SetBackgroundColour(wxColor(255,255,255));
        m_defineStartPose->SetBackgroundColour(wxColor(255,255,255));
        m_defineGoalPose->SetBackgroundColour(wxColor(200,200,200));
        m_pathFinding->SetBackgroundColour(wxColor(255,255,255));
        mainFrame->switchPanel(4);
        mainFrame->currentPanel = 4;
    }
}

void LeftPanel::OnPathFinding(wxCommandEvent &WXUNUSED(event))
{

    if (this->m_decompositionSelection->GetSelection() == wxNOT_FOUND)
    {
        wxLogMessage("Please select one of the decomposition methods first.");
        return;
    }

    MainFrame *mainFrame = (MainFrame *)m_parent->GetParent();

    int startPoseX = mainFrame->m_startPosePanel->dotPoseX;
    int startPoseY = mainFrame->m_startPosePanel->dotPoseY; 
    if (startPoseX == -1 || startPoseY == -1)
    {
        wxLogMessage("Please define start pose & goal pose first.");
        return;
    }
    int goalPoseX = mainFrame->m_goalPosePanel->dotPoseX;
    int goalPoseY = mainFrame->m_goalPosePanel->dotPoseY; 
    if ( goalPoseX == -1 || goalPoseY == -1)
    {
        wxLogMessage("Please define goal pose first.");
        return;
    }

    auto decompositionSelected = this->m_decompositionSelection->GetStringSelection();

    if (decompositionSelected == wxString("Simple Cell Decomposition") && mainFrame->currentPanel != 5)
    {
        m_defineEnvironment->SetBackgroundColour(wxColor(255,255,255));
        m_defineRobot->SetBackgroundColour(wxColor(255,255,255));
        m_defineStartPose->SetBackgroundColour(wxColor(255,255,255));
        m_defineGoalPose->SetBackgroundColour(wxColor(255,255,255));
        m_pathFinding->SetBackgroundColour(wxColor(200,200,200));
        mainFrame->switchPanel(5);
        mainFrame->currentPanel = 5;
    }
}