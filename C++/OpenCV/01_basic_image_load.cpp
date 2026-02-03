// 01_basic_image_load.cpp
// Beginner Level - Basic Image Loading and Display
// This program demonstrates how to load and display an image using OpenCV

#include <iostream>
#include <opencv2/opencv.hpp>

int main() {
    // Load an image from file
    cv::Mat image = cv::imread("image.jpg");
    
    // Check if image was loaded successfully
    if (image.empty()) {
        std::cout << "Error: Could not load image 'image.jpg'" << std::endl;
        std::cout << "Make sure the image file exists in the current directory." << std::endl;
        return -1;
    }
    
    // Display image information
    std::cout << "Image loaded successfully!" << std::endl;
    std::cout << "Image dimensions: " << image.cols << " x " << image.rows << std::endl;
    std::cout << "Image channels: " << image.channels() << std::endl;
    
    // Display the image in a window
    cv::imshow("Loaded Image", image);
    
    // Wait for a key press (0 means wait indefinitely)
    std::cout << "Press any key to close the window..." << std::endl;
    cv::waitKey(0);
    
    // Close all windows
    cv::destroyAllWindows();
    
    return 0;
}
