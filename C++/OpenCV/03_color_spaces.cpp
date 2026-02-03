// 03_color_spaces.cpp
// Beginner Level - Color Space Conversion
// This program demonstrates different color spaces and their conversions

#include <iostream>
#include <opencv2/opencv.hpp>

int main() {
    // Load an image
    cv::Mat original = cv::imread("image.jpg");
    
    if (original.empty()) {
        std::cout << "Error: Could not load image 'image.jpg'" << std::endl;
        return -1;
    }
    
    // Convert to different color spaces
    cv::Mat gray, hsv, lab, yuv;
    
    // BGR to Grayscale
    cv::Mat gray_temp;
    cv::cvtColor(original, gray_temp, cv::COLOR_BGR2GRAY);
    // Convert grayscale back to 3-channel BGR for display
    cv::cvtColor(gray_temp, gray, cv::COLOR_GRAY2BGR);
    
    // BGR to HSV (Hue, Saturation, Value)
    cv::cvtColor(original, hsv, cv::COLOR_BGR2HSV);
    
    // BGR to Lab (Luminance, A, B)
    cv::cvtColor(original, lab, cv::COLOR_BGR2Lab);
    
    // BGR to YUV
    cv::cvtColor(original, yuv, cv::COLOR_BGR2YUV);
    
    // Create a combined display image
    cv::Mat combined;
    cv::hconcat(std::vector<cv::Mat>{original, gray, hsv, lab, yuv}, combined);
    
    // Resize if too large for display
    if (combined.cols > 1200) {
        double scale = 1200.0 / combined.cols;
        cv::resize(combined, combined, cv::Size(), scale, scale);
    }
    
    // Display the result
    cv::imshow("Color Spaces: Original | Grayscale | HSV | LAB | YUV", combined);
    
    std::cout << "Color space conversion completed!" << std::endl;
    std::cout << "Press any key to close..." << std::endl;
    cv::waitKey(0);
    cv::destroyAllWindows();
    
    return 0;
}
