#include "main.h"
#include "mainFrame.h"

wxIMPLEMENT_APP(PathPlanningVisualizerApp);

bool PathPlanningVisualizerApp::OnInit()
{
    MainFrame *frame = new MainFrame("Path Planning Visualizer App", wxPoint(50, 50), wxSize(1440, 930));
    frame->Show(true);
    return true;
}
