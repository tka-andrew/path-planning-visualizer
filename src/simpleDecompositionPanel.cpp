#include "simpleDecompositionPanel.h"
#include "mainFrame.h"
#include "util.h"

#include <opencv2/opencv.hpp>

SimpleDecompositionPanel::SimpleDecompositionPanel(wxPanel *parent, int gridRow, int gridCol, int gridRowSize, int gridColSize)
    : wxPanel(parent, wxID_ANY, wxDefaultPosition, wxSize(-1, -1), wxBORDER_SUNKEN)
{
    this->m_parent = parent;
    this->gridRow = gridRow;
    this->gridCol = gridCol;
    this->gridRowSize = gridRowSize;
    this->gridColSize = gridColSize;

    // Create a wxGrid object
    grid = new wxGrid(this, wxID_ANY);

    // This 2 lines must be executed before CreateGrid()
    grid->SetDefaultColSize(this->gridRowSize);
    grid->SetDefaultRowSize(this->gridColSize);

    grid->CreateGrid(this->gridRow, this->gridCol);

    grid->DisableDragGridSize();
    grid->EnableEditing(false);
    grid->HideRowLabels();
    grid->HideColLabels();
    m_sizer = new wxBoxSizer(wxVERTICAL);
    m_sizer->Add(grid, 1, wxEXPAND | wxALIGN_CENTER_HORIZONTAL | wxALL, 20);
    this->SetSizer(m_sizer);
}

void SimpleDecompositionPanel::resetGrid()
{
    for (int i = 0; i < this->gridRow; i++)
    {
        for (int j = 0; j < this->gridCol; j++)
        {
            this->grid->SetCellBackgroundColour(i, j, wxColour(255, 255, 255));
        }
    }

}

bool hasObstacle(cv::Mat &roi)
{
    uchar *pRoiData = roi.data; // uchar pointer because roi.data return uchar type
    for (int row = 0; row < roi.rows; ++row)
    {
        for (int column = 0; column < roi.cols; ++column)
        {
            // should be: int value = pRoiData[img.channels() * (img.cols * row + column) + channel]; for each channel
            // but since gray image only has one channel, we can simplify it
            int index = roi.cols * row + column;
            int value = pRoiData[index];
            if (value != 255)
            {
                return true;
            }
        }
    }
    return false;
}

void SimpleDecompositionPanel::simpleCellDecomposition()
{
    this->resetGrid(); // reset the grid in case any changes
    
    MainFrame *mainFrame = (MainFrame *)m_parent->GetParent();
    wxBitmap cspace = wxBitmap(mainFrame->m_goalPosePanel->m_cspace);
    wxImage cspace_img = cspace.ConvertToImage();
    cv::Mat cspaceMatImg = OpenCV_wxWidgets::cvMat_from_wxImage( cspace_img );
    int imgWidth = cspaceMatImg.size().width;
    int imgHeight = cspaceMatImg.size().height;

    cv::Mat cspaceMatImg_gray;
    cv::cvtColor(cspaceMatImg.clone(), cspaceMatImg_gray, cv::COLOR_BGR2GRAY);

    int pixel_width_per_grid = ceil(float(imgWidth)/this->gridCol); // ceil is used to handle worst case
    int pixel_height_per_grid = ceil(float(imgHeight)/this->gridRow); // ceil is used to handle worst case

    int x = 0;
    int y = 0;
    for (int i=0; i<gridRow; i++)
    {
        x = 0;
        if (y+pixel_height_per_grid>=imgHeight)
        {
            int maxCol = ceil(float(imgWidth)/pixel_width_per_grid);
            for (int j=0; j<maxCol; j++)
            {
                cv::Mat roi = cspaceMatImg_gray(cv::Rect(x, y, pixel_width_per_grid, imgHeight-y));
                if (hasObstacle(roi))
                {
                    this->grid->SetCellBackgroundColour(i, j, wxColour(0,0,0));
                }
            }
            break;
        }
        for (int j=0; j<gridCol; j++)
        {
            if (x+pixel_height_per_grid>=imgWidth)
            {
                cv::Mat roi = cspaceMatImg_gray(cv::Rect(x, y, imgWidth-x, pixel_height_per_grid));
                if (hasObstacle(roi))
                {
                    this->grid->SetCellBackgroundColour(i, j, wxColour(0,0,0));
                }
                break;
            }
            
            cv::Mat roi = cspaceMatImg_gray(cv::Rect(x, y, pixel_width_per_grid, pixel_height_per_grid));
            if (hasObstacle(roi))
            {
                this->grid->SetCellBackgroundColour(i, j, wxColour(0,0,0));
            }
            x += pixel_width_per_grid;
        }
        y += pixel_height_per_grid;
    }
}