#include "mainFrame.h"

wxBEGIN_EVENT_TABLE(MainFrame, wxFrame)
    EVT_MENU(wxID_EXIT, MainFrame::onExit)
    EVT_MENU(wxID_ABOUT, MainFrame::onAbout)
    EVT_MENU(ID_USAGEGUIDE, MainFrame::onUsageGuide)
wxEND_EVENT_TABLE()

MainFrame::MainFrame(const wxString &title, const wxPoint &pos, const wxSize &size)
    : wxFrame(NULL, wxID_ANY, title, pos, size)
{

    pParent = new wxPanel(this, wxID_ANY);

    pSizer = new wxBoxSizer(wxHORIZONTAL);

    pLeftPanel = new LeftPanel(pParent);
    pEnvironmentGeometryPanel = new EnvironmentGeometryPanel(pParent, ID_RESET_ENVIRONMENT);
    pRobotGeometryPanel = new RobotGeometryPanel(pParent, ID_RESET_ROBOT);
    pStartPosePanel = new DotPanel(pParent, wxColor(0,255,0));
    pGoalPosePanel = new DotPanel(pParent, wxColor(255,0,0));
    pSimpleDecompositionPanel = new SimpleDecompositionPanel(pParent);
    pVisibilityGraphPanel = new VisibilityGraphPanel(pParent);

    pSizer->Add(pLeftPanel, 0, wxSHAPED, 5);
    pSizer->Add(pEnvironmentGeometryPanel, 1, wxEXPAND, 5); // only add environmentGeometryPanel initially, hide the rest
    pRobotGeometryPanel->Hide();
    pStartPosePanel->Hide();
    pGoalPosePanel->Hide();
    pSimpleDecompositionPanel->Hide();
    pVisibilityGraphPanel->Hide();

    pParent->SetSizer(pSizer);

    this->Centre();

    wxMenu *menuFile = new wxMenu;
    menuFile->AppendSeparator();
    menuFile->Append(wxID_EXIT);
    wxMenu *menuHelp = new wxMenu;
    menuHelp->Append(wxID_ABOUT);
    menuHelp->Append(ID_USAGEGUIDE, "&Usage Guide...\tCtrl-H",
                     "Usage Guide");
    wxMenuBar *menuBar = new wxMenuBar;
    menuBar->Append(menuFile, "&File");
    menuBar->Append(menuHelp, "&Help");
    SetMenuBar(menuBar);
    CreateStatusBar();
    SetStatusText("Path Planning Visualizer - by Tan Kui An Andrew 2022");
}

void MainFrame::onExit(wxCommandEvent &event)
{
    Close(true);
}

void MainFrame::onAbout(wxCommandEvent &event)
{
    wxMessageBox("The main purpose of this app is to visualize the Path Planning process. \
    \nThis app is developed using wxWdigets. \
    \nTake note that this project is being tested on Ubuntu 20.04 environment only.",
                 "About this app", wxOK | wxICON_INFORMATION);
}

void MainFrame::onUsageGuide(wxCommandEvent &event)
{
    wxMessageBox("TODO",
                 "Usage Guide", wxOK | wxICON_INFORMATION);
}

void MainFrame::switchPanel(int panelNum)
{
    pSizer->Detach(1); // remove panel 1, which is the right panel
    pEnvironmentGeometryPanel->Hide();
    pRobotGeometryPanel->Hide();
    pStartPosePanel->Hide();
    pGoalPosePanel->Hide();
    pSimpleDecompositionPanel->Hide();
    pVisibilityGraphPanel->Hide();
    pLeftPanel->pStartSimulationBtn->Disable();

    switch (panelNum)
    {
    case ENVIRONMENT_PANEL:
        pSizer->Add(pEnvironmentGeometryPanel, 1, wxGROW);
        pEnvironmentGeometryPanel->Show();
        break;
    case ROBOT_PANEL:
        pSizer->Add(pRobotGeometryPanel, 1, wxGROW);
        pRobotGeometryPanel->Show();
        break;
    case START_PANEL:
        pSizer->Add(pStartPosePanel, 1, wxGROW);
        pStartPosePanel->resetDrawing(); // necessary to update in case robot or enviroment updated 
        pStartPosePanel->Show();
        break;
    case GOAL_PANEL:
        pSizer->Add(pGoalPosePanel, 1, wxGROW);
        pGoalPosePanel->resetDrawing(); // necessary to update in case robot or enviroment updated 
        pGoalPosePanel->Show();
        break;
    case SIMPLE_CELL_DECOMPOSITION_PANEL:
        pSizer->Add(pSimpleDecompositionPanel, 1, wxGROW);
        pGoalPosePanel->resetDrawing(); // necessary to update in case robot or enviroment updated 
        pSimpleDecompositionPanel->simpleCellDecomposition(); // update the grid
        pSimpleDecompositionPanel->Show();
        pLeftPanel->pStartSimulationBtn->Enable();
        break;
    case VISIBILITY_GRAPH_PANEL:
        pSizer->Add(pVisibilityGraphPanel, 1, wxGROW);
        pGoalPosePanel->resetDrawing(); // necessary to update in case robot or enviroment updated 
        pVisibilityGraphPanel->constructGraph();
        pVisibilityGraphPanel->Show();
        pLeftPanel->pStartSimulationBtn->Enable();
        break;
    default:
        wxMessageBox("Invalid panel number!",
            "ERROR", wxOK | wxICON_INFORMATION);
        pSizer->Add(pEnvironmentGeometryPanel, 1, wxGROW);
        pEnvironmentGeometryPanel->Show();
        break;
    }
    pSizer->Layout();
}