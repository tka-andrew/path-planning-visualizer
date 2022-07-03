#include "mainFrame.h"
#include "leftPanel.h"
#include "pathFindingAlgorithms_grid.h"

LeftPanel::LeftPanel(wxPanel *parent)
    : wxPanel(parent, -1, wxPoint(-1, -1), wxSize(200, 200), wxBORDER_SUNKEN)
{
    pParent = parent;
    pDefineEnvironmentBtn = new wxButton(this, ID_DEFINE_ENVIRONMENT, wxT("Define environment"));
    pDefineRobotBtn = new wxButton(this, ID_DEFINE_ROBOT, wxT("Define robot"));
    pDefineStartPoseBtn = new wxButton(this, ID_DEFINE_START, wxT("Define Start"));
    pDefineGoalPoseBtn = new wxButton(this, ID_DEFINE_GOAL, wxT("Define Goal"));
    pPathFindingBtn = new wxButton(this, ID_PATHFINDING, wxT("Path finding"));
    pStartSimulationBtn = new wxButton(this, ID_STARTSIMULATION, wxT("Start Simulation"));
    pDefineEnvironmentBtn->SetBackgroundColour(wxColor(200,200,200)); // initially first button is selected
    pStartSimulationBtn->Disable();

    wxArrayString decompositionChoices;
    decompositionChoices.Add(wxT("Simple Cell Decomposition"));
    // decompositionChoices.Add(wxT("Visibility Graph"));
    pDecompositionSelection = new wxComboBox(this, ID_DECOMPOSTION_SELECTION, "", wxDefaultPosition, wxSize(100, -1), decompositionChoices);

    wxArrayString algoChoices;
    algoChoices.Add(wxT("Dijkstra"));
    algoChoices.Add(wxT("A* Search"));
    algoChoices.Add(wxT("Greedy Best First Search"));
    algoChoices.Add(wxT("BFS"));
    algoChoices.Add(wxT("Bidirectional BFS"));
    pAlgoSelection = new wxComboBox(this, ID_ALGO_SELECTION, "", wxDefaultPosition, wxSize(100, -1), algoChoices);

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
    sizer->Add(pDefineEnvironmentBtn, 0, wxEXPAND, 0);
    sizer->Add(pDefineRobotBtn, 0, wxEXPAND, 0);
    sizer->Add(pDefineStartPoseBtn, 0, wxEXPAND, 0);
    sizer->Add(pDefineGoalPoseBtn, 0, wxEXPAND, 0);
    sizer->Add(comboBoxDescription1, 0, wxEXPAND | wxTOP, 10);
    sizer->Add(pDecompositionSelection, 0, wxEXPAND | wxBOTTOM, 5);
    sizer->Add(pPathFindingBtn, 0, wxEXPAND | wxBOTTOM, 10);
    sizer->Add(comboBoxDescription2, 0, wxEXPAND | wxTOP, 10);
    sizer->Add(pAlgoSelection, 0, wxEXPAND | wxBOTTOM, 5);
    sizer->Add(pStartSimulationBtn, 0, wxEXPAND, 0);
    sizer->SetSizeHints(this);
    this->SetSizer(sizer);
}

void LeftPanel::onDefineEnvironment(wxCommandEvent &WXUNUSED(event))
{
    MainFrame *pMainFrame = (MainFrame *)pParent->GetParent();
    if (pMainFrame->currentPanel != 1)
    {
        pDefineEnvironmentBtn->SetBackgroundColour(wxColor(200,200,200));
        pDefineRobotBtn->SetBackgroundColour(wxColor(255,255,255));
        pDefineStartPoseBtn->SetBackgroundColour(wxColor(255,255,255));
        pDefineGoalPoseBtn->SetBackgroundColour(wxColor(255,255,255));
        pPathFindingBtn->SetBackgroundColour(wxColor(255,255,255));
        pMainFrame->switchPanel(1);
        pMainFrame->currentPanel = 1;
    }
}

void LeftPanel::onDefineRobot(wxCommandEvent &WXUNUSED(event))
{
    MainFrame *pMainFrame = (MainFrame *)pParent->GetParent();
    if (pMainFrame->currentPanel != 2)
    {
        pDefineEnvironmentBtn->SetBackgroundColour(wxColor(255,255,255));
        pDefineRobotBtn->SetBackgroundColour(wxColor(200,200,200));
        pDefineStartPoseBtn->SetBackgroundColour(wxColor(255,255,255));
        pDefineGoalPoseBtn->SetBackgroundColour(wxColor(255,255,255));
        pPathFindingBtn->SetBackgroundColour(wxColor(255,255,255));
        pMainFrame->switchPanel(2);
        pMainFrame->currentPanel = 2;
    }
}

void LeftPanel::onDefineStart(wxCommandEvent &WXUNUSED(event))
{
    MainFrame *pMainFrame = (MainFrame *)pParent->GetParent();

    if (pMainFrame->pRobotGeometryPanel->m_robotBoundingRadius == -1)
    {
        wxLogMessage("Please define a valid robot geometry first.");
        return;
    }

    if (pMainFrame->currentPanel != 3)
    {
        pDefineEnvironmentBtn->SetBackgroundColour(wxColor(255,255,255));
        pDefineRobotBtn->SetBackgroundColour(wxColor(255,255,255));
        pDefineStartPoseBtn->SetBackgroundColour(wxColor(200,200,200));
        pDefineGoalPoseBtn->SetBackgroundColour(wxColor(255,255,255));
        pPathFindingBtn->SetBackgroundColour(wxColor(255,255,255));
        pMainFrame->switchPanel(3);
        pMainFrame->currentPanel = 3;
    }
}

void LeftPanel::onDefineGoal(wxCommandEvent &WXUNUSED(event))
{
    MainFrame *pMainFrame = (MainFrame *)pParent->GetParent();

    if (pMainFrame->pRobotGeometryPanel->m_robotBoundingRadius == -1)
    {
        wxLogMessage("Please define a valid robot geometry first.");
        return;
    }

    int startPoseX = pMainFrame->pStartPosePanel->dotPoseX;
    int startPoseY = pMainFrame->pStartPosePanel->dotPoseY; 
    if (startPoseX == -1 || startPoseY == -1)
    {
        wxLogMessage("Please define start pose first.");
        return;
    }

    if (pMainFrame->currentPanel != 4)
    {
        pDefineEnvironmentBtn->SetBackgroundColour(wxColor(255,255,255));
        pDefineRobotBtn->SetBackgroundColour(wxColor(255,255,255));
        pDefineStartPoseBtn->SetBackgroundColour(wxColor(255,255,255));
        pDefineGoalPoseBtn->SetBackgroundColour(wxColor(200,200,200));
        pPathFindingBtn->SetBackgroundColour(wxColor(255,255,255));
        pMainFrame->switchPanel(4);
        pMainFrame->currentPanel = 4;
    }
}

void LeftPanel::onPathFinding(wxCommandEvent &WXUNUSED(event))
{

    if (pDecompositionSelection->GetSelection() == wxNOT_FOUND)
    {
        wxLogMessage("Please select one of the decomposition methods first.");
        return;
    }

    MainFrame *pMainFrame = (MainFrame *)pParent->GetParent();

    if (pMainFrame->pRobotGeometryPanel->m_robotBoundingRadius == -1)
    {
        wxLogMessage("Please define a valid robot geometry first.");
        return;
    }

    int startPoseX = pMainFrame->pStartPosePanel->dotPoseX;
    int startPoseY = pMainFrame->pStartPosePanel->dotPoseY; 
    if (startPoseX == -1 || startPoseY == -1)
    {
        wxLogMessage("Please define start pose & goal pose first.");
        return;
    }
    int goalPoseX = pMainFrame->pGoalPosePanel->dotPoseX;
    int goalPoseY = pMainFrame->pGoalPosePanel->dotPoseY; 
    if ( goalPoseX == -1 || goalPoseY == -1)
    {
        wxLogMessage("Please define goal pose first.");
        return;
    }

    pDefineEnvironmentBtn->SetBackgroundColour(wxColor(255,255,255));
    pDefineRobotBtn->SetBackgroundColour(wxColor(255,255,255));
    pDefineStartPoseBtn->SetBackgroundColour(wxColor(255,255,255));
    pDefineGoalPoseBtn->SetBackgroundColour(wxColor(255,255,255));
    pPathFindingBtn->SetBackgroundColour(wxColor(200,200,200));

    auto decompositionSelected = pDecompositionSelection->GetStringSelection();

    if (decompositionSelected == wxString("Simple Cell Decomposition") && pMainFrame->currentPanel != 5)
    {
        pMainFrame->switchPanel(5);
        pMainFrame->currentPanel = 5;
    } else if (decompositionSelected == wxString("Visibility Graph") && pMainFrame->currentPanel != 6)
    {
        pMainFrame->switchPanel(6);
        pMainFrame->currentPanel = 6;
    }
}

void LeftPanel::onStartSimulation(wxCommandEvent &WXUNUSED(event))
{
    MainFrame *pMainFrame = (MainFrame *)pParent->GetParent();

    if (pAlgoSelection->GetSelection() == wxNOT_FOUND)
    {
        wxLogMessage("Please select one of the path finding algorithms first.");
        return;
    }

    auto algoSelected = pAlgoSelection->GetStringSelection();
    auto decompositionSelected = pDecompositionSelection->GetStringSelection();

    if (decompositionSelected == wxString("Simple Cell Decomposition"))
    {
        this->SimpleDecompositionPathFinding(algoSelected);
    }
}

void LeftPanel::SimpleDecompositionPathFinding(wxString algoSelected)
{
    MainFrame *pMainFrame = (MainFrame *)pParent->GetParent();
    SimpleDecompositionPanel *simpleDecompositionPanelPtr = (SimpleDecompositionPanel *)pMainFrame->pSimpleDecompositionPanel;
    wxGrid *gridPtr = (wxGrid *)simpleDecompositionPanelPtr->pGrid;

    simpleDecompositionPanelPtr->simpleCellDecomposition(); // to clear previous search if any

    int row = simpleDecompositionPanelPtr->gridRow;
    int col = simpleDecompositionPanelPtr->gridCol;
    std::array<int, 2> startingPoint = simpleDecompositionPanelPtr->startingPoint;
    std::array<int, 2> destinationPoint = simpleDecompositionPanelPtr->destinationPoint;

    // return: numOfCellsVisited, numOfCellCheckingOccurrence, travelCost, prev
    std::tuple<int, int, int, std::vector<std::vector<std::array<int, 2>>>> pathFindingResult;

    if (algoSelected == wxString("Dijkstra"))
    {
        pathFindingResult = dijkstraSingleTarget(startingPoint, destinationPoint, row, col, pMainFrame, gridPtr, true);
    }
    else if (algoSelected == wxString("A* Search"))
    {
        pathFindingResult = aStarSearch(startingPoint, destinationPoint, row, col, pMainFrame, gridPtr, true);
    }
    else if (algoSelected == wxString("Greedy Best First Search"))
    {
        pathFindingResult = greedyBestFirstSearch(startingPoint, destinationPoint, row, col, pMainFrame, gridPtr, true);
    }
    else if (algoSelected == wxString("BFS"))
    {
        pathFindingResult = bfs(startingPoint, destinationPoint, row, col, pMainFrame, gridPtr, true);
    }
    else if (algoSelected == wxString("Bidirectional BFS"))
    {
        pathFindingResult = bidirectionalBFS(startingPoint, destinationPoint, row, col, pMainFrame, gridPtr, true);
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
        pMainFrame->Update();
        pMainFrame->Refresh(false);
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