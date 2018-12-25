#include <iostream>
#include "opencv2/opencv.hpp"

int main(int argc, char* argv[])
{
cv::Mat Image = cv::imread(argv[1], cv::IMREAD_COLOR);
/* cv::cvtColor(image, imageGray, cv::COLOR_BGR2GRAY);
for (int y = 0; y < imageGray.rows; ++y)
{
uchar* imageGrayRow = imageGray.ptr<uchar>(y);
uchar* imageRow = image.ptr<uchar>(y);
for (int x = 0; x < imageGray.cols; ++x)
{
if (imageGrayRow[x] < 210)
{
imageRow[x * 3] = 0;
imageRow[x * 3 + 1] = 0;
imageRow[x * 3 + 2] = 0;
}
}
}*/

cv::Mat ImageHSV;
cv::cvtColor(Image, ImageHSV, cv::COLOR_BGR2HSV);
cv::Mat NewImage;
cv::inRange(ImageHSV,cv::Scalar(0, 10, 55) , cv::Scalar(20, 255, 255), NewImage);
cv::Mat ImageErode;
cv::Mat ImageErode2;
auto Kernel = cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(5, 5));

/*//cv::erode(NewImage, ImageErode, asd);
cv::erode(NewImage, ImageErode2, asd1);
cv::erode(ImageErode2, ImageErode2, asd1);
cv::dilate(ImageErode2, ImageErode, asd1);
cv::erode(ImageErode, ImageErode2, asd1);
cv::erode(ImageErode2, ImageErode2, asd1);
cv::dilate(ImageErode2, ImageErode, asd1);
cv::imshow("inRange", NewImage);
cv::imshow("erode3x3+dilate3x3+erode3x3+dilate3x3", ImageErode);
cv::imshow("erode3x3+dilate3x3+erode3x3", ImageErode2);
//cv::threshold()
//cv::dilate, cv::erode, cv::morphologyEx
*/

cv::Mat Maska;
cv::erode(NewImage, Maska, Kernel, cv::Point(-1, -1), 1);
cv::dilate(Maska, Maska,  Kernel, cv::Point(-1, -1), 1);
for(int i = 0; i < 100; ++i) {
    cv::erode(Maska, Maska, Kernel, cv::Point(-1, -1), 1);
    cv::dilate(Maska, Maska,  Kernel, cv::Point(-1, -1), 1);
}
for(int i = 0; i < 100; ++i) {
    cv::dilate(Maska, Maska,  Kernel, cv::Point(-1, -1), 2);
    cv::erode(Maska, Maska, Kernel, cv::Point(-1, -1), 2);

}
cv::GaussianBlur(Maska, Maska, cv::Size(3, 3), 0);
cv::Mat Output;
cv::Mat Maska_out;
cv::cvtColor(Maska, Maska_out, cv::COLOR_GRAY2RGB);
cv::imshow("maskargb", Maska_out);
cv::bitwise_and(Image, Maska_out, Output);
cv::imshow("input", Image);
cv::imshow("Output", Output);
cv::waitKey();

return 0;
}
