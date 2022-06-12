#ifndef MAIN_H
#define MAIN_H

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

class PathPlanningVisualizerApp : public wxApp
{
public:
    virtual bool OnInit();
};

#endif