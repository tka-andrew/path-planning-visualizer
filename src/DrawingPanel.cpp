#include "DrawingPanel.h"

DrawingPanel::DrawingPanel(wxPanel *parent, int resetButtonID)
    : wxPanel(parent, wxID_ANY, wxDefaultPosition,
              wxSize(-1, -1), wxBORDER_SUNKEN)
{
    m_resetDrawing = new wxButton(this, resetButtonID, wxT("Reset"),
                                  wxPoint(5, 5));
    Connect(resetButtonID, wxEVT_COMMAND_BUTTON_CLICKED,
            wxCommandEventHandler(DrawingPanel::OnResetDrawing));

    wxBoxSizer *vbox = new wxBoxSizer(wxVERTICAL);
    vbox->Add(m_resetDrawing, 0, wxSHAPED, 0);
    this->SetSizer(vbox);

    // REFERENCE: https://docs.wxwidgets.org/3.0/classwx_auto_buffered_paint_d_c.html
    this->SetBackgroundStyle(wxBG_STYLE_PAINT);

    // in this constructor, it is impossible for us to know the size of this panel
    // hence we just simply use a small value
    // we will re-initialize m_drawing later in OnResize() function
    wxImage emptyImage(clientAreaWidth, clientAreaHeight);
    emptyImage.Clear(255); // default white color
    m_drawing = wxBitmap(emptyImage);
}

void DrawingPanel::OnResetDrawing(wxCommandEvent &event)
{
    wxImage emptyImage(clientAreaWidth, clientAreaHeight);
    emptyImage.Clear(255); // default white color
    m_drawing = wxBitmap(emptyImage);
    this->Refresh(); // to trigger refresh
}

void DrawingPanel::OnSize(wxSizeEvent &evt)
{
    if (!initialSizeTaken)
    {
        wxSize clientArea = this->GetClientSize();
        clientAreaWidth = clientArea.GetWidth();
        clientAreaHeight = clientArea.GetHeight();
        wxImage emptyImage(clientAreaWidth, clientAreaHeight);
        emptyImage.Clear(255); // default white color
        m_drawing = wxBitmap(emptyImage);
        initialSizeTaken = true; // to ensure a fixed size bitmap
    }
}

void DrawingPanel::OnPaint(wxPaintEvent &evt)
{
    wxAutoBufferedPaintDC dc(this);
    dc.DrawBitmap(m_drawing, 0, 0);
}

// REFERENCE: https://wiki.wxwidgets.org/Flicker-Free_Drawing#:~:text=Flicker%20free%20drawing%20can%20be,event%20and%20a%20paint%20event.
// To avoid flickering
void DrawingPanel::OnErase(wxEraseEvent &event)
{
    return;
}

// REFERENCE: https://www.informit.com/articles/article.aspx?p=405047
void DrawingPanel::OnMotion(wxMouseEvent &event)
{
    if (event.Dragging())
    {
        int x, y;
        event.GetPosition(&x, &y);

        // we need 2 different DC here
        // wxClientDC for visualization
        // wxMemoryDC for updating the bitmap, so that later wxAutoBufferedPaintDC can draw it in OnPaint() function
        wxClientDC cdc = wxClientDC(this);
        wxMemoryDC mdc(m_drawing);

        mdc.SelectObject(m_drawing);
        if (isLeftMouseClicked)
        {
            cdc.SetPen(wxPen(wxColor(0, 0, 0), 10));
            cdc.SetBrush(wxColor(0, 0, 0)); // black filling
        }
        else
        {
            cdc.SetPen(wxPen(wxColor(255, 255, 255), 10));
            cdc.SetBrush(wxColor(255, 255, 255)); // white filling
        }
        mdc.SetBrush(cdc.GetBrush());
        mdc.SetPen(cdc.GetPen());

        cdc.DrawRectangle(x, y, 10, 10);
        mdc.DrawRectangle(x, y, 10, 10);

        cdc.SetPen(wxNullPen);
        mdc.SetPen(wxNullPen);
        mdc.SelectObject(wxNullBitmap);
    }
}

void DrawingPanel::OnLeftMouseClicked(wxMouseEvent &event)
{
    isLeftMouseClicked = true;
}

void DrawingPanel::OnRightMouseClicked(wxMouseEvent &event)
{
    isLeftMouseClicked = false;
}