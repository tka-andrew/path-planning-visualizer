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
    // REFERENCE: https://docs.opencv.org/3.3.0/db/da5/tutorial_how_to_scan_images.html

    // accept only char type matrices
    CV_Assert(roi.depth() == CV_8U);
    int channels = roi.channels();
    int nRows = roi.rows;
    int nCols = roi.cols * channels;
    if (roi.isContinuous())
    {
        nCols *= nRows;
        nRows = 1;
    }
    int i,j;
    uchar* p;
    for( i = 0; i < nRows; ++i)
    {
        p = roi.ptr<uchar>(i);
        for ( j = 0; j < nCols; ++j)
        {
            if (p[j] != 255)
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
    cv::Mat cspaceMatImg = mainFrame->m_goalPosePanel->m_cspaceMatImg;
    cv::Mat cspaceMatImg_gray;
    cv::cvtColor(cspaceMatImg.clone(), cspaceMatImg_gray, cv::COLOR_BGR2GRAY);

    int imgWidth = cspaceMatImg_gray.size().width;
    int imgHeight = cspaceMatImg_gray.size().height;

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