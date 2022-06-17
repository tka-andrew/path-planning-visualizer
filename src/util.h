#ifndef UTIL_H
#define UTIL_H

#include <wx/wx.h>
#include <opencv2/opencv.hpp>

namespace OpenCV_wxWidgets {

    cv::Mat cvMat_from_wxImage(wxImage &wx_img);
    wxImage wxImage_from_cvMat(cv::Mat &img);
}

#endif