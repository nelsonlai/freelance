// 15_geometric_transforms.cpp
// Intermediate Level - Geometric Transformations
// This program demonstrates various geometric transformations

#include <iostream>
#include <opencv2/opencv.hpp>

int main() {
    // Load an image
    cv::Mat original = cv::imread("image.jpg");
    
    if (original.empty()) {
        std::cout << "Error: Could not load image 'image.jpg'" << std::endl;
        return -1;
    }
    
    // 1. Translation (Moving the image)
    cv::Mat translationMatrix = (cv::Mat_<double>(2,3) << 1, 0, 50, 0, 1, 30);
    cv::Mat translated;
    cv::warpAffine(original, translated, translationMatrix, original.size());
    
    // 2. Rotation
    cv::Point2f center(original.cols/2.0, original.rows/2.0);
    cv::Mat rotationMatrix = cv::getRotationMatrix2D(center, 45, 1.0);
    cv::Mat rotated;
    cv::warpAffine(original, rotated, rotationMatrix, original.size());
    
    // 3. Scaling
    cv::Mat scaled;
    cv::resize(original, scaled, cv::Size(), 0.5, 0.5);
    cv::resize(scaled, scaled, original.size());  // Resize back to original size
    
    // 4. Flipping
    cv::Mat flipped_horizontal, flipped_vertical, flipped_both;
    cv::flip(original, flipped_horizontal, 1);  // 1 for horizontal
    cv::flip(original, flipped_vertical, 0);    // 0 for vertical
    cv::flip(original, flipped_both, -1);       // -1 for both
    
    // 5. Perspective Transformation
    std::vector<cv::Point2f> srcPoints = {
        cv::Point2f(0, 0),
        cv::Point2f(original.cols - 1, 0),
        cv::Point2f(original.cols - 1, original.rows - 1),
        cv::Point2f(0, original.rows - 1)
    };
    
    std::vector<cv::Point2f> dstPoints = {
        cv::Point2f(50, 50),
        cv::Point2f(original.cols - 50, 30),
        cv::Point2f(original.cols - 70, original.rows - 50),
        cv::Point2f(30, original.rows - 30)
    };
    
    cv::Mat perspectiveMatrix = cv::getPerspectiveTransform(srcPoints, dstPoints);
    cv::Mat perspective;
    cv::warpPerspective(original, perspective, perspectiveMatrix, original.size());
    
    // 6. Affine Transformation (3 points)
    std::vector<cv::Point2f> srcTri = {
        cv::Point2f(0, 0),
        cv::Point2f(original.cols - 1, 0),
        cv::Point2f(0, original.rows - 1)
    };
    
    std::vector<cv::Point2f> dstTri = {
        cv::Point2f(0, 0),
        cv::Point2f(original.cols - 1, 0),
        cv::Point2f(50, original.rows - 1)
    };
    
    cv::Mat affineMatrix = cv::getAffineTransform(srcTri, dstTri);
    cv::Mat affine;
    cv::warpAffine(original, affine, affineMatrix, original.size());
    
    // 7. Shearing
    cv::Mat shearMatrix = (cv::Mat_<double>(2,3) << 1, 0.2, 0, 0, 1, 0);
    cv::Mat sheared;
    cv::warpAffine(original, sheared, shearMatrix, original.size());
    
    // Create display layout
    cv::Mat topRow1, topRow2, middleRow, bottomRow, display;
    
    // Top row 1: Original, Translated, Rotated, Scaled
    cv::hconcat(std::vector<cv::Mat>{original, translated, rotated, scaled}, topRow1);
    
    // Top row 2: Horizontal Flip, Vertical Flip, Both Flips, Perspective
    cv::hconcat(std::vector<cv::Mat>{flipped_horizontal, flipped_vertical, flipped_both, perspective}, topRow2);
    
    // Bottom row: Affine, Sheared, (empty), (empty)
    cv::Mat empty = cv::Mat::zeros(original.size(), original.type());
    cv::hconcat(std::vector<cv::Mat>{affine, sheared, empty, empty}, bottomRow);
    
    // Combine rows
    cv::vconcat(std::vector<cv::Mat>{topRow1, topRow2, bottomRow}, display);
    
    // Resize if too large
    if (display.cols > 1400 || display.rows > 1000) {
        double scale = std::min(1400.0 / display.cols, 1000.0 / display.rows);
        cv::resize(display, display, cv::Size(), scale, scale);
    }
    
    cv::imshow("Geometric Transformations", display);
    
    std::cout << "Geometric Transformations:" << std::endl;
    std::cout << "1. Translation: Moving image in x,y direction" << std::endl;
    std::cout << "2. Rotation: Rotating image around center point" << std::endl;
    std::cout << "3. Scaling: Resizing image" << std::endl;
    std::cout << "4. Flipping: Mirroring image horizontally/vertically" << std::endl;
    std::cout << "5. Perspective: 4-point transformation" << std::endl;
    std::cout << "6. Affine: 3-point transformation" << std::endl;
    std::cout << "7. Shearing: Skewing transformation" << std::endl;
    
    std::cout << "\nTransformation Matrices:" << std::endl;
    std::cout << "Translation Matrix:" << std::endl;
    std::cout << translationMatrix << std::endl;
    std::cout << "\nRotation Matrix:" << std::endl;
    std::cout << rotationMatrix << std::endl;
    std::cout << "\nAffine Matrix:" << std::endl;
    std::cout << affineMatrix << std::endl;
    
    std::cout << "\nPress any key to close..." << std::endl;
    cv::waitKey(0);
    cv::destroyAllWindows();
    
    return 0;
}
