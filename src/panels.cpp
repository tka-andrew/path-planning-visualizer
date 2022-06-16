#include "mainFrame.h"
#include "panels.h"

LeftPanel::LeftPanel(wxPanel *parent)
    : wxPanel(parent, -1, wxPoint(-1, -1), wxSize(200, 200), wxBORDER_SUNKEN)
{
    m_parent = parent;
    m_defineEnvironment = new wxButton(this, ID_DEFINE_ENVIRONMENT, wxT("Define environment"));
    m_pathFinding = new wxButton(this, ID_PATHFINDING, wxT("Path finding"));

    // REFERENCE: https://forums.wxwidgets.org/viewtopic.php?t=43787
    // wxST_NO_AUTORESIZE flag is added to prevent it from auto-sizing
    m_startingPoint = new wxStaticText(this, wxID_ANY, "Starting Point:\nundefined", wxPoint(10, 400), wxDefaultSize, wxALIGN_CENTER | wxST_NO_AUTORESIZE);
    m_destinationPoint = new wxStaticText(this, wxID_ANY, "Destination Point:\nundefined", wxPoint(10, 500), wxDefaultSize, wxALIGN_CENTER | wxST_NO_AUTORESIZE);

    Connect(ID_DEFINE_ENVIRONMENT, wxEVT_COMMAND_BUTTON_CLICKED,
            wxCommandEventHandler(LeftPanel::OnDefineEnvironment));
    Connect(ID_PATHFINDING, wxEVT_COMMAND_BUTTON_CLICKED,
            wxCommandEventHandler(LeftPanel::OnPathFinding));

    wxBoxSizer *sizer = new wxBoxSizer(wxVERTICAL);
    sizer->Add(m_defineEnvironment, 0, wxEXPAND, 0);
    sizer->Add(m_pathFinding, 0, wxEXPAND, 0);
    sizer->SetSizeHints(this);
    this->SetSizer(sizer);
}

void LeftPanel::OnDefineEnvironment(wxCommandEvent &WXUNUSED(event))
{
    MainFrame *mainFrame = (MainFrame *)m_parent->GetParent();
    if (mainFrame->currentPanel != 1)
    {
        mainFrame->switchPanel(1);
        mainFrame->currentPanel = 1;
    }
}

void LeftPanel::OnPathFinding(wxCommandEvent &WXUNUSED(event))
{
    MainFrame *mainFrame = (MainFrame *)m_parent->GetParent();
    if (mainFrame->currentPanel != 3)
    {
        mainFrame->switchPanel(3);
        mainFrame->currentPanel = 3;
    }
}

PathFindingPanel::PathFindingPanel(wxPanel *parent)
    : wxPanel(parent, wxID_ANY, wxDefaultPosition,
              wxSize(-1, -1), wxBORDER_SUNKEN)
{

    // Create a wxGrid object
    grid = new wxGrid(this,
                      -1,
                      wxPoint(0, 0),
                      wxSize(200, 200));

    // This 2 lines must be executed before CreateGrid()
    grid->SetDefaultColSize(20);
    grid->SetDefaultRowSize(20);

    grid->CreateGrid(this->gridRow, this->gridCol);

    grid->DisableDragGridSize();
    grid->EnableEditing(false);
    grid->HideRowLabels();
    grid->HideColLabels();

    wxBoxSizer *vbox = new wxBoxSizer(wxVERTICAL);
    vbox->Add(grid, 1, wxEXPAND | wxALIGN_CENTER_HORIZONTAL | wxALL, 20);
    this->SetSizer(vbox);
}

wxBEGIN_EVENT_TABLE(EnvironmentGeometryPanel, wxPanel)
    EVT_PAINT(EnvironmentGeometryPanel::OnPaint)    
    EVT_SIZE(EnvironmentGeometryPanel::OnSize)
    EVT_ERASE_BACKGROUND(EnvironmentGeometryPanel::OnErase)
    EVT_MOTION(EnvironmentGeometryPanel::OnMotion)
    EVT_LEFT_DOWN(EnvironmentGeometryPanel::OnLeftMouseClicked)
    EVT_RIGHT_DOWN(EnvironmentGeometryPanel::OnRightMouseClicked)
wxEND_EVENT_TABLE()

EnvironmentGeometryPanel::EnvironmentGeometryPanel(wxPanel *parent)
    : wxPanel(parent, wxID_ANY, wxDefaultPosition,
              wxSize(-1, -1), wxBORDER_SUNKEN)
{
    m_uploadImage = new wxButton(this, ID_UPLOAD_IMAGE, wxT("Upload Image"),
                                 wxPoint(10, 10));

    wxBoxSizer *vbox = new wxBoxSizer(wxVERTICAL);
    vbox->Add(m_uploadImage, 0, wxSHAPED, 0);
    this->SetSizer(vbox);

    // REFERENCE: https://docs.wxwidgets.org/3.0/classwx_auto_buffered_paint_d_c.html
    this->SetBackgroundStyle(wxBG_STYLE_PAINT);

    // in this constructor, it is impossible for us to know the size of this panel
    // hence we just simply use a small value
    // we will re-initialize environmentDrawing later in OnResize() function
    wxImage emptyImage(clientAreaWidth, clientAreaHeight);
    emptyImage.Clear(255); // default white color
    environmentDrawing = wxBitmap(emptyImage);
}

void EnvironmentGeometryPanel::OnSize(wxSizeEvent & evt)
{
    if (!initialSizeTaken)
    {
        wxSize clientArea = this->GetClientSize();
        clientAreaWidth = clientArea.GetWidth();
        clientAreaHeight = clientArea.GetHeight();
        wxImage emptyImage(clientAreaWidth, clientAreaHeight);
        emptyImage.Clear(255); // default white color
        environmentDrawing = wxBitmap(emptyImage);
        initialSizeTaken = true; // to ensure a fixed size bitmap
    }
}

void EnvironmentGeometryPanel::OnPaint(wxPaintEvent & evt)
{
    wxAutoBufferedPaintDC dc(this);
    dc.DrawBitmap(environmentDrawing, 0, 0);
}

// REFERENCE: https://wiki.wxwidgets.org/Flicker-Free_Drawing#:~:text=Flicker%20free%20drawing%20can%20be,event%20and%20a%20paint%20event.
// To avoid flickering
void EnvironmentGeometryPanel::OnErase(wxEraseEvent& event)
{
    return;
}

// REFERENCE: https://www.informit.com/articles/article.aspx?p=405047
void EnvironmentGeometryPanel::OnMotion(wxMouseEvent& event)
{
    if (event.Dragging())
    {
        int x, y;
        event.GetPosition(&x, &y);

        // we need 2 different DC here
        // wxClientDC for visualization
        // wxMemoryDC for updating the bitmap, so that later wxAutoBufferedPaintDC can draw it in OnPaint() function
        wxClientDC cdc = wxClientDC(this);
        wxMemoryDC mdc(environmentDrawing);

        mdc.SelectObject(environmentDrawing);
        if (isLeftMouseClicked)
        {
            cdc.SetPen(wxPen(wxColor(0,0,0), 10));
            cdc.SetBrush(wxColor(0,0,0)); // black filling
        }
        else
        {
            cdc.SetPen(wxPen(wxColor(255,255,255), 10));
            cdc.SetBrush(wxColor(255,255,255)); // white filling
        } 
        mdc.SetBrush(cdc.GetBrush());
        mdc.SetPen(cdc.GetPen());

        cdc.DrawRectangle( x, y, 10, 10 );
        mdc.DrawRectangle( x, y, 10, 10 );

        cdc.SetPen(wxNullPen);
        mdc.SetPen(wxNullPen);
        mdc.SelectObject(wxNullBitmap);
    }
}


void EnvironmentGeometryPanel::OnLeftMouseClicked(wxMouseEvent& event)
{
    isLeftMouseClicked = true;
}

void EnvironmentGeometryPanel::OnRightMouseClicked(wxMouseEvent& event)
{
    isLeftMouseClicked = false;
}