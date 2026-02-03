// opencv001.cpp
//
#include <iostream>
#include <opencv2/opencv.hpp>
using namespace cv;

int main() {
    Mat img = imread("image.jpg");
    if (img.empty()) {
        printf("Image not found\n");
        return -1;
    }
    imshow("Display window", img);
    waitKey(0);
    return 0;
}