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

    m_sizer = new wxBoxSizer(wxHORIZONTAL);

    m_lp = new LeftPanel(pParent);
    pEnvironmentGeometryPanel = new EnvironmentGeometryPanel(pParent, ID_RESET_ENVIRONMENT);
    pRobotGeometryPanel = new RobotGeometryPanel(pParent, ID_RESET_ROBOT);
    pStartPosePanel = new DotPanel(pParent, wxColor(0,255,0));
    m_goalPosePanel = new DotPanel(pParent, wxColor(255,0,0));
    m_simpleDecompositionPanel = new SimpleDecompositionPanel(pParent);
    m_visibilityGraphPanel = new VisibilityGraphPanel(pParent);

    m_sizer->Add(m_lp, 0, wxSHAPED, 5);
    m_sizer->Add(pEnvironmentGeometryPanel, 1, wxEXPAND, 5); // only add environmentGeometryPanel initially, hide the rest
    pRobotGeometryPanel->Hide();
    pStartPosePanel->Hide();
    m_goalPosePanel->Hide();
    m_simpleDecompositionPanel->Hide();
    m_visibilityGraphPanel->Hide();

    pParent->SetSizer(m_sizer);

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
    m_sizer->Detach(1); // remove panel 1, which is the right panel
    pEnvironmentGeometryPanel->Hide();
    pRobotGeometryPanel->Hide();
    pStartPosePanel->Hide();
    m_goalPosePanel->Hide();
    m_simpleDecompositionPanel->Hide();
    m_visibilityGraphPanel->Hide();
    this->m_lp->m_startSimulation->Disable();

    switch (panelNum)
    {
    case 1:
        m_sizer->Add(pEnvironmentGeometryPanel, 1, wxGROW);
        pEnvironmentGeometryPanel->Show();
        break;
    case 2:
        m_sizer->Add(pRobotGeometryPanel, 1, wxGROW);
        pRobotGeometryPanel->Show();
        break;
    case 3:
        m_sizer->Add(pStartPosePanel, 1, wxGROW);
        pStartPosePanel->resetDrawing(); // necessary to update in case robot or enviroment updated 
        pStartPosePanel->Show();
        break;
    case 4:
        m_sizer->Add(m_goalPosePanel, 1, wxGROW);
        m_goalPosePanel->resetDrawing(); // necessary to update in case robot or enviroment updated 
        m_goalPosePanel->Show();
        break;
    case 5:
        m_sizer->Add(m_simpleDecompositionPanel, 1, wxGROW);
        m_goalPosePanel->resetDrawing(); // necessary to update in case robot or enviroment updated 
        m_simpleDecompositionPanel->simpleCellDecomposition(); // update the grid
        m_simpleDecompositionPanel->Show();
        this->m_lp->m_startSimulation->Enable();
        break;
    case 6:
        m_sizer->Add(m_visibilityGraphPanel, 1, wxGROW);
        m_goalPosePanel->resetDrawing(); // necessary to update in case robot or enviroment updated 
        m_visibilityGraphPanel->constructGraph();
        m_visibilityGraphPanel->Show();
        this->m_lp->m_startSimulation->Enable();
        break;
    }
    m_sizer->Layout();
}