#include "mainFrame.h"
#include "DotPanel.h"

wxBEGIN_EVENT_TABLE(DotPanel, wxPanel)
    EVT_PAINT(DotPanel::OnPaint)
    EVT_SIZE(DotPanel::OnSize)
    EVT_ERASE_BACKGROUND(DotPanel::OnErase)
    EVT_LEFT_DOWN(DotPanel::OnLeftMouseClicked)
wxEND_EVENT_TABLE()

DotPanel::DotPanel(wxPanel *parent, wxColor dotColor)
    : wxPanel(parent, wxID_ANY, wxDefaultPosition,
              wxSize(-1, -1), wxBORDER_SUNKEN)
{
    m_parent = parent;
    m_dotColor = dotColor;
    // REFERENCE: https://docs.wxwidgets.org/3.0/classwx_auto_buffered_paint_d_c.html
    this->SetBackgroundStyle(wxBG_STYLE_PAINT);
    this->resetDrawing();
}

void DotPanel::resetDrawing()
{
    MainFrame *mainFrame = (MainFrame *)m_parent->GetParent();
    m_drawing = wxBitmap(mainFrame->m_environmentGeometryPanel->m_drawing);
    this->Refresh();
}

void DotPanel::OnPaint(wxPaintEvent &evt)
{
    if (dotPoseX != -1 && dotPoseY != -1)
    {
        wxMemoryDC mdc(m_drawing);

        mdc.SelectObject(m_drawing);
        mdc.SetBrush(m_dotColor);
        mdc.SetPen(wxPen(m_dotColor, 5));

        mdc.DrawRectangle(dotPoseX, dotPoseY, 5, 5);

        mdc.SetPen(wxNullPen);
        mdc.SelectObject(wxNullBitmap);
    }
    wxAutoBufferedPaintDC dc(this);
    dc.DrawBitmap(m_drawing, 0, 0);
}

void DotPanel::OnSize(wxSizeEvent &evt)
{
    if (!initialSizeTaken)
    {
        this->resetDrawing();
        initialSizeTaken = true; // to ensure a fixed size bitmap
    }
}

// REFERENCE: https://wiki.wxwidgets.org/Flicker-Free_Drawing#:~:text=Flicker%20free%20drawing%20can%20be,event%20and%20a%20paint%20event.
// To avoid flickering
void DotPanel::OnErase(wxEraseEvent &event)
{
    return;
}

void DotPanel::OnLeftMouseClicked(wxMouseEvent &event)
{
    resetDrawing();
    int x, y;
    event.GetPosition(&x, &y);

    dotPoseX = x;
    dotPoseY = y;

    // we need 2 different DC here
    // wxClientDC for visualization
    // wxMemoryDC for updating the bitmap, so that later wxAutoBufferedPaintDC can draw it in OnPaint() function
    wxClientDC cdc = wxClientDC(this);
    wxMemoryDC mdc(m_drawing);

    mdc.SelectObject(m_drawing);
    cdc.SetPen(wxPen(m_dotColor, 5));
    cdc.SetBrush(m_dotColor);
    mdc.SetBrush(cdc.GetBrush());
    mdc.SetPen(cdc.GetPen());

    cdc.DrawRectangle(x, y, 5, 5);
    mdc.DrawRectangle(x, y, 5, 5);

    cdc.SetPen(wxNullPen);
    mdc.SetPen(wxNullPen);
    mdc.SelectObject(wxNullBitmap);
    this->Refresh(); // to trigger refresh
}