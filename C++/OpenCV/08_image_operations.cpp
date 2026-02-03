// 08_image_operations.cpp
// Beginner Level - Basic Image Operations
// This program demonstrates basic mathematical operations on images

#include <iostream>
#include <opencv2/opencv.hpp>

int main() {
    // Load an image
    cv::Mat original = cv::imread("image.jpg");
    
    if (original.empty()) {
        std::cout << "Error: Could not load image 'image.jpg'" << std::endl;
        return -1;
    }
    
    // Create a second image for operations (same size, different content)
    cv::Mat second = cv::Mat::zeros(original.size(), original.type());
    cv::rectangle(second, cv::Point(50, 50), 
                 cv::Point(original.cols-50, original.rows-50), 
                 cv::Scalar(100, 150, 200), -1);
    
    // 1. Image Addition
    cv::Mat added;
    cv::add(original, second, added);
    
    // 2. Image Subtraction
    cv::Mat subtracted;
    cv::subtract(original, second, subtracted);
    
    // 3. Image Multiplication (scalar)
    cv::Mat multiplied;
    cv::multiply(original, cv::Scalar(1.5, 1.5, 1.5), multiplied);
    
    // 4. Image Division (scalar)
    cv::Mat divided;
    cv::divide(original, cv::Scalar(2, 2, 2), divided);
    
    // 5. Bitwise operations (convert to grayscale first)
    cv::Mat gray1, gray2;
    cv::cvtColor(original, gray1, cv::COLOR_BGR2GRAY);
    cv::cvtColor(second, gray2, cv::COLOR_BGR2GRAY);
    
    cv::Mat bitwise_and, bitwise_or, bitwise_xor;
    cv::bitwise_and(gray1, gray2, bitwise_and);
    cv::bitwise_or(gray1, gray2, bitwise_or);
    cv::bitwise_xor(gray1, gray2, bitwise_xor);
    
    // Convert back to color for display
    cv::Mat and_color, or_color, xor_color;
    cv::cvtColor(bitwise_and, and_color, cv::COLOR_GRAY2BGR);
    cv::cvtColor(bitwise_or, or_color, cv::COLOR_GRAY2BGR);
    cv::cvtColor(bitwise_xor, xor_color, cv::COLOR_GRAY2BGR);
    
    // 6. Weighted addition (blending)
    cv::Mat blended;
    cv::addWeighted(original, 0.7, second, 0.3, 0, blended);
    
    // Create display layout
    cv::Mat topRow, middleRow, bottomRow, display;
    
    // Top row: original, second, added, subtracted
    cv::hconcat(std::vector<cv::Mat>{original, second, added, subtracted}, topRow);
    
    // Middle row: multiplied, divided, blended, and_color
    cv::hconcat(std::vector<cv::Mat>{multiplied, divided, blended, and_color}, middleRow);
    
    // Bottom row: or_color, xor_color, (empty), (empty)
    cv::Mat empty = cv::Mat::zeros(original.size(), original.type());
    cv::hconcat(std::vector<cv::Mat>{or_color, xor_color, empty, empty}, bottomRow);
    
    // Combine all rows
    cv::vconcat(std::vector<cv::Mat>{topRow, middleRow, bottomRow}, display);
    
    // Resize if too large
    if (display.cols > 1400 || display.rows > 1000) {
        double scale = std::min(1400.0 / display.cols, 1000.0 / display.rows);
        cv::resize(display, display, cv::Size(), scale, scale);
    }
    
    // Display result
    cv::imshow("Image Operations", display);
    
    std::cout << "Image operations demonstrated:" << std::endl;
    std::cout << "1. Addition (pixel-wise)" << std::endl;
    std::cout << "2. Subtraction (pixel-wise)" << std::endl;
    std::cout << "3. Multiplication (scalar)" << std::endl;
    std::cout << "4. Division (scalar)" << std::endl;
    std::cout << "5. Bitwise AND, OR, XOR" << std::endl;
    std::cout << "6. Weighted addition (blending)" << std::endl;
    
    std::cout << "\nPress any key to close..." << std::endl;
    cv::waitKey(0);
    cv::destroyAllWindows();
    
    return 0;
}
