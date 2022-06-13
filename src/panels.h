#ifndef PANELS_H
#define PANELS_H

#include <wx/wx.h>
#include <wx/panel.h>
#include <wx/grid.h>

class LeftPanel : public wxPanel
{
public:
    LeftPanel(wxPanel *parent);
    void OnDefineEnvironment(wxCommandEvent &event);
    void OnPathFinding(wxCommandEvent &event);
    wxButton *m_defineEnvironment;
    wxButton *m_pathFinding;
    wxStaticText *m_startingPoint;
    wxStaticText *m_destinationPoint;
    wxPanel *m_parent;
};

class PathFindingPanel : public wxPanel
{
public:
    PathFindingPanel(wxPanel *parent);
    wxGrid *grid;
    wxPanel *m_parent;
    int gridRow = 40;
    int gridCol = 60;
};

class EnvironmentGeometryPanel : public wxPanel
{
public:
    EnvironmentGeometryPanel(wxPanel *parent);
    wxPanel *m_parent;
    wxButton *m_uploadImage;

    // REFERENCE: https://wiki.wxwidgets.org/Drawing_on_a_panel_with_a_DC
    // REFERENCE: https://www.informit.com/articles/article.aspx?p=405047
    void OnPaint(wxPaintEvent & evt);
    void paintNow(); // actually doesnt need this
    void OnMotion(wxMouseEvent& event);
    void render(wxDC& dc);
    wxDECLARE_EVENT_TABLE();
};

const int ID_DEFINE_ENVIRONMENT = 101;
const int ID_PATHFINDING = 102;
const int ID_UPLOAD_IMAGE = 201;
#endif // PANELS_H