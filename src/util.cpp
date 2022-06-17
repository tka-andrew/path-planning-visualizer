#include "util.h"

cv::Mat mat_from_wxbitmap(wxBitmap &bitmap)
{
    wxImage wx_img = bitmap.ConvertToImage();
    cv::Mat im2(cv::Size(wx_img.GetWidth(), wx_img.GetHeight()), CV_8UC3, wx_img.GetData());
    cv::cvtColor(im2, im2, cv::COLOR_RGB2BGR);
    return im2;
}