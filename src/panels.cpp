#include "mainFrame.h"
#include "panels.h"

LeftPanel::LeftPanel(wxPanel *parent)
    : wxPanel(parent, -1, wxPoint(-1, -1), wxSize(200, 200), wxBORDER_SUNKEN)
{
    m_parent = parent;
    m_defineEnvironment = new wxButton(this, ID_DEFINE_ENVIRONMENT, wxT("Define environment"));
    m_defineRobot = new wxButton(this, ID_DEFINE_ROBOT, wxT("Define robot"));
    m_pathFinding = new wxButton(this, ID_PATHFINDING, wxT("Path finding"));

    Connect(ID_DEFINE_ENVIRONMENT, wxEVT_COMMAND_BUTTON_CLICKED,
            wxCommandEventHandler(LeftPanel::OnDefineEnvironment));
    Connect(ID_DEFINE_ROBOT, wxEVT_COMMAND_BUTTON_CLICKED,
            wxCommandEventHandler(LeftPanel::OnDefineRobot));
    Connect(ID_PATHFINDING, wxEVT_COMMAND_BUTTON_CLICKED,
            wxCommandEventHandler(LeftPanel::OnPathFinding));

    wxBoxSizer *sizer = new wxBoxSizer(wxVERTICAL);
    sizer->Add(m_defineEnvironment, 0, wxEXPAND, 0);
    sizer->Add(m_defineRobot, 0, wxEXPAND, 0);
    sizer->Add(m_pathFinding, 0, wxEXPAND, 0);
    sizer->SetSizeHints(this);
    this->SetSizer(sizer);
}

void LeftPanel::OnDefineEnvironment(wxCommandEvent &WXUNUSED(event))
{
    MainFrame *mainFrame = (MainFrame *)m_parent->GetParent();
    if (mainFrame->currentPanel != 1)
    {
        mainFrame->switchPanel(1);
        mainFrame->currentPanel = 1;
    }
}

void LeftPanel::OnDefineRobot(wxCommandEvent &WXUNUSED(event))
{
    MainFrame *mainFrame = (MainFrame *)m_parent->GetParent();
    if (mainFrame->currentPanel != 2)
    {
        mainFrame->switchPanel(2);
        mainFrame->currentPanel = 2;
    }
}

void LeftPanel::OnPathFinding(wxCommandEvent &WXUNUSED(event))
{
    MainFrame *mainFrame = (MainFrame *)m_parent->GetParent();
    if (mainFrame->currentPanel != 3)
    {
        mainFrame->switchPanel(3);
        mainFrame->currentPanel = 3;
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
