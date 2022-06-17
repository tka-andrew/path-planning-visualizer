#ifndef UTIL_H
#define UTIL_H

#include <wx/wx.h>
#include <opencv2/opencv.hpp>

namespace OpenCV_wxWidgets {

    // // THIS WILL HAVE WEIRD NOISE ON TOP LEFT
    // cv::Mat mat_from_wxbitmap(wxBitmap &bitmap);

    cv::Mat mat_from_wxImage(wxImage &wx_img);

}

#endif