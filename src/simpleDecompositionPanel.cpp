#include "simpleDecompositionPanel.h"
#include "mainFrame.h"
#include "util.h"

#include <opencv2/opencv.hpp>

SimpleDecompositionPanel::SimpleDecompositionPanel(wxPanel *parent, int gridRow, int gridCol, int gridRowSize, int gridColSize)
    : wxPanel(parent, wxID_ANY, wxDefaultPosition, wxSize(-1, -1), wxBORDER_SUNKEN)
{
    this->pParent = parent;
    this->gridRow = gridRow;
    this->gridCol = gridCol;
    this->gridRowSize = gridRowSize;
    this->gridColSize = gridColSize;

    // Create a wxGrid object
    pGrid = new wxGrid(this, wxID_ANY);

    // This 2 lines must be executed before CreateGrid()
    pGrid->SetDefaultColSize(this->gridRowSize);
    pGrid->SetDefaultRowSize(this->gridColSize);

    pGrid->CreateGrid(this->gridRow, this->gridCol);

    pGrid->DisableDragGridSize();
    pGrid->EnableEditing(false);
    pGrid->HideRowLabels();
    pGrid->HideColLabels();
    pSizer = new wxBoxSizer(wxVERTICAL);
    pSizer->Add(pGrid, 1, wxEXPAND | wxALIGN_CENTER_HORIZONTAL | wxALL, 20);
    this->SetSizer(pSizer);
}

void SimpleDecompositionPanel::resetGrid()
{
    for (int i = 0; i < this->gridRow; i++)
    {
        for (int j = 0; j < this->gridCol; j++)
        {
            this->pGrid->SetCellBackgroundColour(i, j, wxColour(255, 255, 255));
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
    this->resetGrid(); // reset the pGrid in case any changes
    
    MainFrame *pMainFrame = (MainFrame *)pParent->GetParent();
    cv::Mat cspaceMatImg = pMainFrame->pGoalPosePanel->m_cspaceMatImg;
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
                    this->pGrid->SetCellBackgroundColour(i, j, wxColour(0,0,0));
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
                    this->pGrid->SetCellBackgroundColour(i, j, wxColour(0,0,0));
                }
                break;
            }
            
            cv::Mat roi = cspaceMatImg_gray(cv::Rect(x, y, pixel_width_per_grid, pixel_height_per_grid));
            if (hasObstacle(roi))
            {
                this->pGrid->SetCellBackgroundColour(i, j, wxColour(0,0,0));
            }
            x += pixel_width_per_grid;
        }
        y += pixel_height_per_grid;
    }

    // Take note that x,y in grid and image/wxbitmap are in opposite
    int startPoseGridX = pMainFrame->pStartPosePanel->dotPoseY / pixel_height_per_grid;
    int startPoseGridY = pMainFrame->pStartPosePanel->dotPoseX / pixel_width_per_grid;
    int goalPoseGridX = pMainFrame->pGoalPosePanel->dotPoseY  / pixel_height_per_grid;
    int goalPoseGridY = pMainFrame->pGoalPosePanel->dotPoseX / pixel_width_per_grid;

    startingPoint = {startPoseGridX, startPoseGridY};
    destinationPoint = {goalPoseGridX, goalPoseGridY};

    this->paintStartAndGoal();
}

void SimpleDecompositionPanel::paintStartAndGoal()
{
    this->pGrid->SetCellBackgroundColour(startingPoint[0], startingPoint[1], wxColour(0,255,0));
    this->pGrid->SetCellBackgroundColour(destinationPoint[0], destinationPoint[1], wxColour(255,0,0));
}