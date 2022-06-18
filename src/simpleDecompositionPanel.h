#ifndef SIMPLE_DECOMPOSITION_PANEL_H
#define SIMPLE_DECOMPOSITION_PANEL_H

#include "constants.h"

#include <wx/wx.h>
#include <wx/grid.h>

class SimpleDecompositionPanel : public wxPanel
{
public:
    SimpleDecompositionPanel(wxPanel *parent, int gridRow = 40, int gridCol = 60, int gridRowSize = 20, int gridColSize = 20);
    wxGrid *grid;
    wxPanel *m_parent;
    int gridRow;
    int gridCol;
    int gridRowSize;
    int gridColSize;
};

#endif // SIMPLE_DECOMPOSITION_PANEL_H