#ifndef ENVIRONEMNT_PANEL_H
#define ENVIRONEMNT_PANEL_H

#include "constants.h"
#include "DrawingPanel.h"

class EnvironmentGeometryPanel : public DrawingPanel
{
public:
    EnvironmentGeometryPanel(wxPanel *parent,  int resetButtonID);
    ~EnvironmentGeometryPanel();
};

#endif