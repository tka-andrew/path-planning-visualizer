#include "mainFrame.h"

wxBEGIN_EVENT_TABLE(MainFrame, wxFrame)
    EVT_MENU(wxID_EXIT, MainFrame::OnExit)
        EVT_MENU(wxID_ABOUT, MainFrame::OnAbout)
            EVT_MENU(ID_USAGEGUIDE, MainFrame::OnUsageGuide)
                wxEND_EVENT_TABLE()

                    MainFrame::MainFrame(const wxString &title, const wxPoint &pos, const wxSize &size)
    : wxFrame(NULL, wxID_ANY, title, pos, size)
{

    m_parent = new wxPanel(this, wxID_ANY);

    m_sizer = new wxBoxSizer(wxHORIZONTAL);

    m_lp = new LeftPanel(m_parent);
    m_pathFindingPanel = new PathFindingPanel(m_parent);
    m_environmentGeometryPanel = new EnvironmentGeometryPanel(m_parent);

    m_sizer->Add(m_lp, 0, wxSHAPED, 5);
    m_sizer->Add(m_environmentGeometryPanel, 1, wxEXPAND, 5); // only add environmentGeometryPanel initially, hide the rest
    m_pathFindingPanel->Hide();

    m_parent->SetSizer(m_sizer);

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

void MainFrame::OnExit(wxCommandEvent &event)
{
    Close(true);
}

void MainFrame::OnAbout(wxCommandEvent &event)
{
    wxMessageBox("The main purpose of this app is to visualize the Path Planning process. \
    \nThis app is developed using wxWdigets. \
    \nTake note that this project is being tested on Ubuntu 20.04 environment only.",
                 "About this app", wxOK | wxICON_INFORMATION);
}

void MainFrame::OnUsageGuide(wxCommandEvent &event)
{
    wxMessageBox("TODO",
                 "Usage Guide", wxOK | wxICON_INFORMATION);
}

void MainFrame::switchPanel(int panelNum)
{
    switch (panelNum)
    {
    case 1:
        m_sizer->Detach(1); // remove panel 1, which is the right panel
        m_pathFindingPanel->Hide();
        m_sizer->Add(m_environmentGeometryPanel, 1, wxGROW);
        m_environmentGeometryPanel->Show();
        break;
    case 3:
        m_sizer->Detach(1); // remove panel 1, which is the right panel
        m_environmentGeometryPanel->Hide();
        m_sizer->Add(m_pathFindingPanel, 1, wxGROW);
        m_pathFindingPanel->Show();
        break;
    }
    m_sizer->Layout();
}