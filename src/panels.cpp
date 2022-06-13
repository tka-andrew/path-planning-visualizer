#include "mainFrame.h"
#include "panels.h"

LeftPanel::LeftPanel(wxPanel *parent)
    : wxPanel(parent, -1, wxPoint(-1, -1), wxSize(200, 200), wxBORDER_SUNKEN)
{
    m_parent = parent;
    m_defineEnvironment = new wxButton(this, ID_DEFINE_ENVIRONMENT, wxT("Define environment"));
    m_pathFinding = new wxButton(this, ID_PATHFINDING, wxT("Path finding"));

    // REFERENCE: https://forums.wxwidgets.org/viewtopic.php?t=43787
    // wxST_NO_AUTORESIZE flag is added to prevent it from auto-sizing
    m_startingPoint = new wxStaticText(this, wxID_ANY, "Starting Point:\nundefined", wxPoint(10, 400), wxDefaultSize, wxALIGN_CENTER | wxST_NO_AUTORESIZE);
    m_destinationPoint = new wxStaticText(this, wxID_ANY, "Destination Point:\nundefined", wxPoint(10, 500), wxDefaultSize, wxALIGN_CENTER | wxST_NO_AUTORESIZE);

    Connect(ID_DEFINE_ENVIRONMENT, wxEVT_COMMAND_BUTTON_CLICKED,
            wxCommandEventHandler(LeftPanel::OnDefineEnvironment));
    Connect(ID_PATHFINDING, wxEVT_COMMAND_BUTTON_CLICKED,
            wxCommandEventHandler(LeftPanel::OnPathFinding));

    wxBoxSizer *sizer = new wxBoxSizer(wxVERTICAL);
    sizer->Add(m_defineEnvironment, 0, wxEXPAND, 0);
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

wxBEGIN_EVENT_TABLE(EnvironmentGeometryPanel, wxPanel)
    EVT_MOTION(EnvironmentGeometryPanel::OnMotion)
wxEND_EVENT_TABLE()

EnvironmentGeometryPanel::EnvironmentGeometryPanel(wxPanel *parent)
    : wxPanel(parent, wxID_ANY, wxDefaultPosition,
              wxSize(-1, -1), wxBORDER_SUNKEN)
{
    m_uploadImage = new wxButton(this, ID_UPLOAD_IMAGE, wxT("Upload Image"),
                                 wxPoint(10, 10));

    wxBoxSizer *vbox = new wxBoxSizer(wxVERTICAL);
    vbox->Add(m_uploadImage, 0, wxSHAPED, 0);
    this->SetSizer(vbox);
}

void EnvironmentGeometryPanel::OnMotion(wxMouseEvent& event)
{
    if (event.Dragging())
    {
        wxClientDC dc(this);
        wxPen pen(wxColor(0,0,0), 10 ); // black pen of width 5
        dc.SetPen(pen);
        dc.DrawPoint(event.GetPosition());
        dc.SetPen(wxNullPen);
    }
}
