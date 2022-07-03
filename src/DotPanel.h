#ifndef DOT_PANEL_H
#define DOT_PANEL_H

#include "constants.h"

#include <wx/wx.h>
#include <wx/dcmemory.h>
#include <wx/dcbuffer.h>
#include <opencv2/opencv.hpp>

class DotPanel : public wxPanel
{
public:
    DotPanel(wxPanel *parent, wxColor dotColor);
    wxPanel *pParent;
    wxBitmap m_cspace;
    wxBitmap m_drawing;
    cv::Mat m_cspaceMatImg;
    wxColor m_dotColor;
    int dotPoseX = -1;
    int dotPoseY = -1;

    void resetDrawing();

    // REFERENCE: https://wiki.wxwidgets.org/Drawing_on_a_panel_with_a_DC
    // REFERENCE: https://www.informit.com/articles/article.aspx?p=405047
    void onPaint(wxPaintEvent & evt);
    void onErase(wxEraseEvent& event);
    void onSize(wxSizeEvent& event);
    void onLeftMouseClicked(wxMouseEvent& event);
    wxDECLARE_EVENT_TABLE();

private:
    int clientAreaWidth = 10; // dummy value, will be updated onSize()
    int clientAreaHeight = 10; // dummy value, will be updated onSize()
    bool initialSizeTaken = false;
};

#endif