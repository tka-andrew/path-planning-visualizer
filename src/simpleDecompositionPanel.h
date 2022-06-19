#ifndef SIMPLE_DECOMPOSITION_PANEL_H
#define SIMPLE_DECOMPOSITION_PANEL_H

#include "constants.h"

#include <wx/wx.h>
#include <wx/grid.h>

#include <array>

class SimpleDecompositionPanel : public wxPanel
{
public:
    SimpleDecompositionPanel(wxPanel *parent, int gridRow = 40, int gridCol = 60, int gridRowSize = 20, int gridColSize = 20);
    void simpleCellDecomposition();
    void resetGrid();
    wxGrid *grid;
    wxPanel *m_parent;
    wxBoxSizer *m_sizer;
    int gridRow;
    int gridCol;
    int gridRowSize;
    int gridColSize;
    std::array<int, 2> startingPoint = {-1, -1};
    std::array<int, 2> destinationPoint = {-1, -1};

private:
    bool initialSizeTaken = false;
};

#endif // SIMPLE_DECOMPOSITION_PANEL_H