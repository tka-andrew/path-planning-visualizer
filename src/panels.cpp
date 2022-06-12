#include "mainFrame.h"
#include "panels.h"

LeftPanel::LeftPanel(wxPanel *parent)
    : wxPanel(parent, -1, wxPoint(-1, -1), wxSize(-1, -1), wxBORDER_SUNKEN)
{
    m_parent = parent;
    m_defineEnvironment = new wxButton(this, ID_SET_WALL, wxT("Define environment"),
                             wxPoint(10, 10));


    // REFERENCE: https://forums.wxwidgets.org/viewtopic.php?t=43787
    // wxST_NO_AUTORESIZE flag is added to prevent it from auto-sizing
    m_startingPoint = new wxStaticText(this, wxID_ANY, "Starting Point:\nundefined", wxPoint(10, 400), wxDefaultSize, wxALIGN_CENTER | wxST_NO_AUTORESIZE);
    m_destinationPoint = new wxStaticText(this, wxID_ANY, "Destination Point:\nundefined", wxPoint(10, 500), wxDefaultSize, wxALIGN_CENTER | wxST_NO_AUTORESIZE);

    Connect(ID_SET_WALL, wxEVT_COMMAND_BUTTON_CLICKED,
            wxCommandEventHandler(LeftPanel::OnDefineEnvironment));

    wxBoxSizer *sizer = new wxBoxSizer(wxVERTICAL);
    sizer->Add(m_defineEnvironment, 0, wxEXPAND, 0);
    sizer->SetSizeHints(this);
    this->SetSizer(sizer);
}

RightPanel::RightPanel(wxPanel *parent)
    : wxPanel(parent, wxID_ANY, wxDefaultPosition,
              wxSize(200, 200), wxBORDER_SUNKEN)
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

    wxBoxSizer *hbox = new wxBoxSizer(wxVERTICAL);
    hbox->Add(grid, 1, wxEXPAND | wxALIGN_CENTER_HORIZONTAL | wxALL, 20);
    this->SetSizer(hbox);
}