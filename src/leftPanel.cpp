#include "mainFrame.h"
#include "leftPanel.h"
#include "pathFindingAlgorithms_grid.h"

LeftPanel::LeftPanel(wxPanel *parent)
    : wxPanel(parent, -1, wxPoint(-1, -1), wxSize(200, 200), wxBORDER_SUNKEN)
{
    pParent = parent;
    m_defineEnvironment = new wxButton(this, ID_DEFINE_ENVIRONMENT, wxT("Define environment"));
    m_defineRobot = new wxButton(this, ID_DEFINE_ROBOT, wxT("Define robot"));
    m_defineStartPose = new wxButton(this, ID_DEFINE_START, wxT("Define Start"));
    m_defineGoalPose = new wxButton(this, ID_DEFINE_GOAL, wxT("Define Goal"));
    m_pathFinding = new wxButton(this, ID_PATHFINDING, wxT("Path finding"));
    m_startSimulation = new wxButton(this, ID_STARTSIMULATION, wxT("Start Simulation"));
    m_defineEnvironment->SetBackgroundColour(wxColor(200,200,200)); // initially first button is selected
    m_startSimulation->Disable();

    wxArrayString decompositionChoices;
    decompositionChoices.Add(wxT("Simple Cell Decomposition"));
    // decompositionChoices.Add(wxT("Visibility Graph"));
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
            wxCommandEventHandler(LeftPanel::onDefineEnvironment));
    Connect(ID_DEFINE_ROBOT, wxEVT_COMMAND_BUTTON_CLICKED,
            wxCommandEventHandler(LeftPanel::onDefineRobot));
    Connect(ID_DEFINE_START, wxEVT_COMMAND_BUTTON_CLICKED,
            wxCommandEventHandler(LeftPanel::onDefineStart));
    Connect(ID_DEFINE_GOAL, wxEVT_COMMAND_BUTTON_CLICKED,
            wxCommandEventHandler(LeftPanel::onDefineGoal));
    Connect(ID_PATHFINDING, wxEVT_COMMAND_BUTTON_CLICKED,
            wxCommandEventHandler(LeftPanel::onPathFinding));
    Connect(ID_STARTSIMULATION, wxEVT_COMMAND_BUTTON_CLICKED,
            wxCommandEventHandler(LeftPanel::onStartSimulation));

    wxBoxSizer *sizer = new wxBoxSizer(wxVERTICAL);
    sizer->Add(m_defineEnvironment, 0, wxEXPAND, 0);
    sizer->Add(m_defineRobot, 0, wxEXPAND, 0);
    sizer->Add(m_defineStartPose, 0, wxEXPAND, 0);
    sizer->Add(m_defineGoalPose, 0, wxEXPAND, 0);
    sizer->Add(comboBoxDescription1, 0, wxEXPAND | wxTOP, 10);
    sizer->Add(m_decompositionSelection, 0, wxEXPAND | wxBOTTOM, 5);
    sizer->Add(m_pathFinding, 0, wxEXPAND | wxBOTTOM, 10);
    sizer->Add(comboBoxDescription2, 0, wxEXPAND | wxTOP, 10);
    sizer->Add(m_algoSelection, 0, wxEXPAND | wxBOTTOM, 5);
    sizer->Add(m_startSimulation, 0, wxEXPAND, 0);
    sizer->SetSizeHints(this);
    this->SetSizer(sizer);
}

void LeftPanel::onDefineEnvironment(wxCommandEvent &WXUNUSED(event))
{
    MainFrame *mainFrame = (MainFrame *)pParent->GetParent();
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

void LeftPanel::onDefineRobot(wxCommandEvent &WXUNUSED(event))
{
    MainFrame *mainFrame = (MainFrame *)pParent->GetParent();
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

void LeftPanel::onDefineStart(wxCommandEvent &WXUNUSED(event))
{
    MainFrame *mainFrame = (MainFrame *)pParent->GetParent();

    if (mainFrame->pRobotGeometryPanel->m_robotBoundingRadius == -1)
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

void LeftPanel::onDefineGoal(wxCommandEvent &WXUNUSED(event))
{
    MainFrame *mainFrame = (MainFrame *)pParent->GetParent();

    if (mainFrame->pRobotGeometryPanel->m_robotBoundingRadius == -1)
    {
        wxLogMessage("Please define a valid robot geometry first.");
        return;
    }

    int startPoseX = mainFrame->pStartPosePanel->dotPoseX;
    int startPoseY = mainFrame->pStartPosePanel->dotPoseY; 
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

void LeftPanel::onPathFinding(wxCommandEvent &WXUNUSED(event))
{

    if (this->m_decompositionSelection->GetSelection() == wxNOT_FOUND)
    {
        wxLogMessage("Please select one of the decomposition methods first.");
        return;
    }

    MainFrame *mainFrame = (MainFrame *)pParent->GetParent();

    if (mainFrame->pRobotGeometryPanel->m_robotBoundingRadius == -1)
    {
        wxLogMessage("Please define a valid robot geometry first.");
        return;
    }

    int startPoseX = mainFrame->pStartPosePanel->dotPoseX;
    int startPoseY = mainFrame->pStartPosePanel->dotPoseY; 
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

    m_defineEnvironment->SetBackgroundColour(wxColor(255,255,255));
    m_defineRobot->SetBackgroundColour(wxColor(255,255,255));
    m_defineStartPose->SetBackgroundColour(wxColor(255,255,255));
    m_defineGoalPose->SetBackgroundColour(wxColor(255,255,255));
    m_pathFinding->SetBackgroundColour(wxColor(200,200,200));

    auto decompositionSelected = this->m_decompositionSelection->GetStringSelection();

    if (decompositionSelected == wxString("Simple Cell Decomposition") && mainFrame->currentPanel != 5)
    {
        mainFrame->switchPanel(5);
        mainFrame->currentPanel = 5;
    } else if (decompositionSelected == wxString("Visibility Graph") && mainFrame->currentPanel != 6)
    {
        mainFrame->switchPanel(6);
        mainFrame->currentPanel = 6;
    }
}

void LeftPanel::onStartSimulation(wxCommandEvent &WXUNUSED(event))
{
    MainFrame *mainFrame = (MainFrame *)pParent->GetParent();

    if (this->m_algoSelection->GetSelection() == wxNOT_FOUND)
    {
        wxLogMessage("Please select one of the path finding algorithms first.");
        return;
    }

    // clearSearch(); // clearSearch before starting simulation

    auto algoSelected = this->m_algoSelection->GetStringSelection();
    auto decompositionSelected = this->m_decompositionSelection->GetStringSelection();

    if (decompositionSelected == wxString("Simple Cell Decomposition"))
    {
        this->SimpleDecompositionPathFinding(algoSelected);
    }
}

void LeftPanel::SimpleDecompositionPathFinding(wxString algoSelected)
{
    MainFrame *mainFrame = (MainFrame *)pParent->GetParent();
    SimpleDecompositionPanel *simpleDecompositionPanelPtr = (SimpleDecompositionPanel *)mainFrame->m_simpleDecompositionPanel;
    wxGrid *gridPtr = (wxGrid *)simpleDecompositionPanelPtr->grid;

    simpleDecompositionPanelPtr->simpleCellDecomposition(); // to clear previous search if any

    int row = simpleDecompositionPanelPtr->gridRow;
    int col = simpleDecompositionPanelPtr->gridCol;
    std::array<int, 2> startingPoint = simpleDecompositionPanelPtr->startingPoint;
    std::array<int, 2> destinationPoint = simpleDecompositionPanelPtr->destinationPoint;

    // return: numOfCellsVisited, numOfCellCheckingOccurrence, travelCost, prev
    std::tuple<int, int, int, std::vector<std::vector<std::array<int, 2>>>> pathFindingResult;

    if (algoSelected == wxString("Dijkstra"))
    {
        pathFindingResult = dijkstraSingleTarget(startingPoint, destinationPoint, row, col, mainFrame, gridPtr, true);
    }
    else if (algoSelected == wxString("A* Search"))
    {
        pathFindingResult = aStarSearch(startingPoint, destinationPoint, row, col, mainFrame, gridPtr, true);
    }
    else if (algoSelected == wxString("Greedy Best First Search"))
    {
        pathFindingResult = greedyBestFirstSearch(startingPoint, destinationPoint, row, col, mainFrame, gridPtr, true);
    }
    else if (algoSelected == wxString("BFS"))
    {
        pathFindingResult = bfs(startingPoint, destinationPoint, row, col, mainFrame, gridPtr, true);
    }
    else if (algoSelected == wxString("Bidirectional BFS"))
    {
        pathFindingResult = bidirectionalBFS(startingPoint, destinationPoint, row, col, mainFrame, gridPtr, true);
    }
    else
    {
        wxLogMessage("Invalid selection.");
        return;
    }

    simpleDecompositionPanelPtr->paintStartAndGoal();

    int numOfCellsVisited = std::get<0>(pathFindingResult);
    int numOfCellCheckingOccurrence = std::get<1>(pathFindingResult);
    int travelCost = std::get<2>(pathFindingResult);
    std::vector<std::vector<std::array<int, 2>>> prev = std::get<3>(pathFindingResult);

    int targetR = simpleDecompositionPanelPtr->destinationPoint[0];
    int targetC = simpleDecompositionPanelPtr->destinationPoint[1];
    std::array<int, 2> pathTrackCell{prev[targetR][targetC]};
    while (pathTrackCell[0] != -1 || pathTrackCell[1] != -1)
    {
        int row = pathTrackCell[0];
        int col = pathTrackCell[1];
        gridPtr->SetCellBackgroundColour(row, col, wxColour(100, 100, 100));
        pathTrackCell[0] = prev[row][col][0];
        pathTrackCell[1] = prev[row][col][1];

        // INSPIRED BY: https://github.com/ArturMarekNowak/Pathfinding-Visualization/blob/master/SourceFiles/cMain.cpp
        mainFrame->Update();
        mainFrame->Refresh(false);
    }

    simpleDecompositionPanelPtr->paintStartAndGoal();
    gridPtr->ForceRefresh();

    if (travelCost == INT_MAX)
    {
        wxLogMessage("Number of cells visited: %d\nNumber of cell checking occurrence: %d\nThe destination is unreachable!", numOfCellsVisited, numOfCellCheckingOccurrence);
        return;
    }

    wxLogMessage("Number of cells visited: %d\nNumber of cell checking occurence: %d\nTravel cost: %d", numOfCellsVisited, numOfCellCheckingOccurrence, travelCost);
}