// 05_image_resize.cpp
// Beginner Level - Image Resizing and Cropping
// This program demonstrates different ways to resize and crop images

#include <iostream>
#include <opencv2/opencv.hpp>

int main() {
    // Load an image
    cv::Mat original = cv::imread("image.jpg");
    
    if (original.empty()) {
        std::cout << "Error: Could not load image 'image.jpg'" << std::endl;
        return -1;
    }
    
    std::cout << "Original image size: " << original.cols << " x " << original.rows << std::endl;
    
    // Method 1: Resize to specific dimensions
    cv::Mat resized1;
    cv::resize(original, resized1, cv::Size(300, 300));
    
    // Method 2: Resize by scale factor
    cv::Mat resized2;
    cv::resize(original, resized2, cv::Size(), 0.5, 0.5);  // Half the size
    
    // Method 3: Resize with different interpolation methods
    cv::Mat nearest, linear, cubic;
    cv::resize(original, nearest, cv::Size(400, 300), 0, 0, cv::INTER_NEAREST);
    cv::resize(original, linear, cv::Size(400, 300), 0, 0, cv::INTER_LINEAR);
    cv::resize(original, cubic, cv::Size(400, 300), 0, 0, cv::INTER_CUBIC);
    
    // Crop a region (ROI - Region of Interest)
    int centerX = original.cols / 2;
    int centerY = original.rows / 2;
    int cropSize = 200;
    
    cv::Rect cropRect(centerX - cropSize/2, centerY - cropSize/2, cropSize, cropSize);
    cv::Mat cropped = original(cropRect);
    
    // Resize all images to the same dimensions for display
    cv::Size displaySize(300, 300);
    cv::Mat original_display, resized1_display, resized2_display, nearest_display, linear_display, cubic_display, cropped_display;
    
    cv::resize(original, original_display, displaySize);
    cv::resize(resized1, resized1_display, displaySize);
    cv::resize(resized2, resized2_display, displaySize);
    cv::resize(nearest, nearest_display, displaySize);
    cv::resize(linear, linear_display, displaySize);
    cv::resize(cubic, cubic_display, displaySize);
    cv::resize(cropped, cropped_display, displaySize);
    
    // Create a display grid
    cv::Mat display;
    cv::Mat topRow, bottomRow;
    
    // Combine top row: original, resized1, resized2 (3 images)
    cv::hconcat(std::vector<cv::Mat>{original_display, resized1_display, resized2_display}, topRow);
    
    // Combine bottom row: nearest, linear, cubic, cropped (4 images)
    // Need to add a placeholder to match 4 columns for vconcat
    cv::Mat placeholder = cv::Mat::zeros(displaySize, CV_8UC3);
    cv::hconcat(std::vector<cv::Mat>{nearest_display, linear_display, cubic_display, cropped_display}, bottomRow);
    
    // Add placeholder to top row to match bottom row width
    cv::hconcat(std::vector<cv::Mat>{topRow, placeholder}, topRow);
    
    // Combine top and bottom rows
    cv::vconcat(topRow, bottomRow, display);
    
    // Resize display if too large
    if (display.cols > 1400 || display.rows > 800) {
        double scale = std::min(1400.0 / display.cols, 800.0 / display.rows);
        cv::resize(display, display, cv::Size(), scale, scale);
    }
    
    // Display the result
    cv::imshow("Image Resizing and Cropping Examples", display);
    
    // Print information
    std::cout << "Resizing examples:" << std::endl;
    std::cout << "- Original: " << original.cols << " x " << original.rows << std::endl;
    std::cout << "- Fixed size (300x300): " << resized1.cols << " x " << resized1.rows << std::endl;
    std::cout << "- Scale factor (0.5x): " << resized2.cols << " x " << resized2.rows << std::endl;
    std::cout << "- Cropped region: " << cropped.cols << " x " << cropped.rows << std::endl;
    
    std::cout << "\nPress any key to close..." << std::endl;
    cv::waitKey(0);
    cv::destroyAllWindows();
    
    return 0;
}
