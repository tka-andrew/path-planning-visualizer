#ifndef UTIL_H
#define UTIL_H

#include <wx/wx.h>
#include <opencv2/opencv.hpp>

namespace OpenCV_wxWidgets {
    
    cv::Mat mat_from_wxbitmap(wxBitmap &bitmap);

}

#endif