#include "util.h"

// REFERENCE: https://github.com/yan9a/wxwidgets/blob/master/wxcvsimple/util.h

namespace OpenCV_wxWidgets
{
    cv::Mat cvMat_from_wxImage(wxImage &wx_img)
    {
        cv::Mat mat_img(cv::Size(wx_img.GetWidth(), wx_img.GetHeight()), CV_8UC3, wx_img.GetData());
        cv::cvtColor(mat_img, mat_img, cv::COLOR_RGB2BGR);
        return mat_img;
    }

    wxImage wxImage_from_cvMat(cv::Mat &img)
    {
        cv::Mat mat_img;
        if (img.channels() == 1)
        {
            cv::cvtColor(img, mat_img, cv::COLOR_GRAY2RGB);
        }
        else if (img.channels() == 4)
        {
            cv::cvtColor(img, mat_img, cv::COLOR_BGRA2RGB);
        }
        else
        {
            cv::cvtColor(img, mat_img, cv::COLOR_BGR2RGB);
        }
        long imsize = mat_img.rows * mat_img.cols * mat_img.channels();
        wxImage wx_img(mat_img.cols, mat_img.rows, (unsigned char *)malloc(imsize), false);
        unsigned char *s = mat_img.data;
        unsigned char *d = wx_img.GetData();
        for (long i = 0; i < imsize; i++)
        {
            d[i] = s[i];
        }
        return wx_img;
    }
}