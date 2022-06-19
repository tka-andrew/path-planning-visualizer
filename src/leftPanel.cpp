#include "mainFrame.h"
#include "leftPanel.h"

LeftPanel::LeftPanel(wxPanel *parent)
    : wxPanel(parent, -1, wxPoint(-1, -1), wxSize(200, 200), wxBORDER_SUNKEN)
{
    m_parent = parent;
    m_defineEnvironment = new wxButton(this, ID_DEFINE_ENVIRONMENT, wxT("Define environment"));
    m_defineRobot = new wxButton(this, ID_DEFINE_ROBOT, wxT("Define robot"));
    m_defineStartPose = new wxButton(this, ID_DEFINE_START, wxT("Define Start"));
    m_defineGoalPose = new wxButton(this, ID_DEFINE_GOAL, wxT("Define Goal"));
    m_pathFinding = new wxButton(this, ID_PATHFINDING, wxT("Path finding"));
    m_startSimulation = new wxButton(this, ID_STARTSIMULATION, wxT("Start Simulation"));
    m_defineEnvironment->SetBackgroundColour(wxColor(200,200,200)); // initially first button is selected

    wxArrayString decompositionChoices;
    decompositionChoices.Add(wxT("Simple Cell Decomposition"));
    m_decompositionSelection = new wxComboBox(this, ID_DECOMPOSTION_SELECTION, "", wxDefaultPosition, wxSize(100, -1), decompositionChoices);

    wxArrayString algoChoices;
    algoChoices.Add(wxT("Dijkstra"));
    algoChoices.Add(wxT("A* Search"));
    algoChoices.Add(wxT("Greedy Best First Search"));
    algoChoices.Add(wxT("BFS"));
    algoChoices.Add(wxT("Bidirectional BFS"));
    m_algoSelection = new wxComboBox(this, ID_ALGO_SELECTION, "", wxDefaultPosition, wxSize(100, -1), algoChoices);

    wxStaticText *comboBoxDescription1 = new wxStaticText(this, wxID_ANY, "Decomposition", wxDefaultPosition, wxDefaultSize, wxALIGN_CENTER | wxST_NO_AUTORESIZE);
    wxStaticText *comboBoxDescription2 = new wxStaticText(this, wxID_ANY, "Path Finding Algo", wxDefaultPosition, wxDefaultSize, wxALIGN_CENTER | wxST_NO_AUTORESIZE);

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
    sizer->Add(m_pathFinding, 0, wxEXPAND, 0);
    sizer->Add(comboBoxDescription1, 0, wxEXPAND | wxTOP, 10);
    sizer->Add(m_decompositionSelection, 0, wxEXPAND, 0);
    sizer->Add(comboBoxDescription2, 0, wxEXPAND | wxTOP, 10);
    sizer->Add(m_algoSelection, 0, wxEXPAND, 0);
    sizer->Add(m_startSimulation, 0, wxEXPAND | wxTOP, 20);
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

    if (mainFrame->m_robotGeometryPanel->m_robotBoundingRadius == -1)
    {
        wxLogMessage("Please define a valid robot geometry first.");
        return;
    }

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

    if (mainFrame->m_robotGeometryPanel->m_robotBoundingRadius == -1)
    {
        wxLogMessage("Please define a valid robot geometry first.");
        return;
    }

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