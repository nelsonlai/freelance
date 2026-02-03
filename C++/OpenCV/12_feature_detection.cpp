// 12_feature_detection.cpp
// Intermediate Level - Feature Detection
// This program demonstrates various feature detection algorithms

#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/features2d.hpp>

int main() {
    // Load an image
    cv::Mat original = cv::imread("image.jpg");
    
    if (original.empty()) {
        std::cout << "Error: Could not load image 'image.jpg'" << std::endl;
        return -1;
    }
    
    // Convert to grayscale
    cv::Mat gray;
    cv::cvtColor(original, gray, cv::COLOR_BGR2GRAY);
    
    // 1. Harris Corner Detection
    cv::Mat harris_corners;
    cv::cornerHarris(gray, harris_corners, 2, 3, 0.04);
    cv::Mat harris_result = original.clone();
    harris_corners = cv::abs(harris_corners);
    cv::normalize(harris_corners, harris_corners, 0, 255, cv::NORM_MINMAX, CV_8UC1);
    
    // Draw Harris corners
    for (int i = 0; i < harris_corners.rows; i++) {
        for (int j = 0; j < harris_corners.cols; j++) {
            if ((int)harris_corners.at<uchar>(i, j) > 150) {
                cv::circle(harris_result, cv::Point(j, i), 3, cv::Scalar(0, 255, 0), -1);
            }
        }
    }
    
    // 2. FAST Corner Detection
    std::vector<cv::KeyPoint> fast_keypoints;
    cv::FAST(gray, fast_keypoints, 50, true);
    cv::Mat fast_result = original.clone();
    cv::drawKeypoints(original, fast_keypoints, fast_result, cv::Scalar(0, 255, 0));
    
    // 3. ORB Feature Detection
    std::vector<cv::KeyPoint> orb_keypoints;
    cv::Mat orb_descriptors;
    auto orb = cv::ORB::create(500);
    orb->detectAndCompute(gray, cv::Mat(), orb_keypoints, orb_descriptors);
    cv::Mat orb_result = original.clone();
    cv::drawKeypoints(original, orb_keypoints, orb_result, cv::Scalar(255, 0, 0));
    
    // 4. SIFT Feature Detection
    std::vector<cv::KeyPoint> sift_keypoints;
    cv::Mat sift_descriptors;
    auto sift = cv::SIFT::create(500);
    sift->detectAndCompute(gray, cv::Mat(), sift_keypoints, sift_descriptors);
    cv::Mat sift_result = original.clone();
    cv::drawKeypoints(original, sift_keypoints, sift_result, cv::Scalar(0, 0, 255));
    
    // 5. Blob Detection
    std::vector<cv::KeyPoint> blob_keypoints;
    auto blob_detector = cv::SimpleBlobDetector::create();
    blob_detector->detect(gray, blob_keypoints);
    cv::Mat blob_result = original.clone();
    cv::drawKeypoints(original, blob_keypoints, blob_result, cv::Scalar(255, 255, 0));
    
    // 6. Edge Detection with Hough Transform
    cv::Mat edges;
    cv::Canny(gray, edges, 50, 150);
    
    std::vector<cv::Vec4i> lines;
    cv::HoughLinesP(edges, lines, 1, CV_PI/180, 50, 50, 10);
    cv::Mat hough_result = original.clone();
    for (size_t i = 0; i < lines.size(); i++) {
        cv::Vec4i l = lines[i];
        cv::line(hough_result, cv::Point(l[0], l[1]), cv::Point(l[2], l[3]), 
                cv::Scalar(255, 0, 255), 2);
    }
    
    // Create display layout
    cv::Mat topRow, bottomRow, display;
    
    // Top row: Original, Harris, FAST, ORB
    cv::hconcat(std::vector<cv::Mat>{original, harris_result, fast_result, orb_result}, topRow);
    
    // Convert edges to 3-channel for display
    cv::Mat edges_color;
    cv::cvtColor(edges, edges_color, cv::COLOR_GRAY2BGR);
    
    // Bottom row: SIFT, Blob, Hough, Edges
    cv::hconcat(std::vector<cv::Mat>{sift_result, blob_result, hough_result, edges_color}, bottomRow);
    
    // Combine rows
    cv::vconcat(topRow, bottomRow, display);
    
    // Resize if too large
    if (display.cols > 1400 || display.rows > 800) {
        double scale = std::min(1400.0 / display.cols, 800.0 / display.rows);
        cv::resize(display, display, cv::Size(), scale, scale);
    }
    
    cv::imshow("Feature Detection", display);
    
    // Print feature counts
    std::cout << "Feature Detection Results:" << std::endl;
    std::cout << "Harris Corners: " << cv::countNonZero(harris_corners > 150) << " corners" << std::endl;
    std::cout << "FAST Features: " << fast_keypoints.size() << " keypoints" << std::endl;
    std::cout << "ORB Features: " << orb_keypoints.size() << " keypoints" << std::endl;
    std::cout << "SIFT Features: " << sift_keypoints.size() << " keypoints" << std::endl;
    std::cout << "Blob Features: " << blob_keypoints.size() << " keypoints" << std::endl;
    std::cout << "Hough Lines: " << lines.size() << " lines" << std::endl;
    
    std::cout << "\nFeature Detection Methods:" << std::endl;
    std::cout << "1. Harris: Corner detection" << std::endl;
    std::cout << "2. FAST: Fast corner detection" << std::endl;
    std::cout << "3. ORB: Binary features (fast)" << std::endl;
    std::cout << "4. SIFT: Scale-invariant features" << std::endl;
    std::cout << "5. Blob: Blob detection" << std::endl;
    std::cout << "6. Hough: Line detection" << std::endl;
    
    std::cout << "\nPress any key to close..." << std::endl;
    cv::waitKey(0);
    cv::destroyAllWindows();
    
    return 0;
}
