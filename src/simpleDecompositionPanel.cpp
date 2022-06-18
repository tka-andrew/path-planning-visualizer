#include "simpleDecompositionPanel.h"

SimpleDecompositionPanel::SimpleDecompositionPanel(wxPanel *parent, int gridRow, int gridCol, int gridRowSize, int gridColSize)
    : wxPanel(parent, wxID_ANY, wxDefaultPosition, wxSize(-1, -1), wxBORDER_SUNKEN)
{
    m_parent = parent;

    // Create a wxGrid object
    grid = new wxGrid(this, wxID_ANY);

    this->gridRow = gridRow;
    this->gridCol = gridCol;
    this->gridRowSize = gridRowSize;
    this->gridColSize = gridColSize;

    // This 2 lines must be executed before CreateGrid()
    grid->SetDefaultColSize(this->gridRowSize);
    grid->SetDefaultRowSize(this->gridColSize);

    grid->CreateGrid(this->gridRow, this->gridCol);

    grid->DisableDragGridSize();
    grid->EnableEditing(false);
    grid->HideRowLabels();
    grid->HideColLabels();

    wxBoxSizer *vbox = new wxBoxSizer(wxVERTICAL);
    vbox->Add(grid, 1, wxEXPAND | wxALIGN_CENTER_HORIZONTAL | wxALL, 20);
    this->SetSizer(vbox);
}
