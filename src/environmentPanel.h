#ifndef ENVIRONEMNT_PANEL_H
#define ENVIRONEMNT_PANEL_H

#include "constants.h"
#include "DrawingPanel.h"

class EnvironmentGeometryPanel : public DrawingPanel
{
public:
    // REFERENCE: https://stackoverflow.com/questions/347358/inheriting-constructors
    using DrawingPanel::DrawingPanel;
};

#endif