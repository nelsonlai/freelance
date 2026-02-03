// 21_advanced_image_stitching.cpp
// Advanced Level - Image Stitching and Panorama Creation
// This program demonstrates how to create panoramas by stitching multiple images together

#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/stitching.hpp>
#include <vector>

int main() {
    std::cout << "=== Advanced Image Stitching and Panorama Creation ===" << std::endl;
    
    // Create sample images for stitching (in real scenario, these would be loaded from files)
    cv::Mat image1 = cv::imread("image.jpg");
    
    if (image1.empty()) {
        std::cout << "Error: Could not load base image 'image.jpg'" << std::endl;
        std::cout << "Creating sample images for demonstration..." << std::endl;
        
        // Create sample images with different perspectives
        image1 = cv::Mat::zeros(300, 400, CV_8UC3);
        cv::rectangle(image1, cv::Point(50, 50), cv::Point(150, 150), cv::Scalar(0, 255, 0), -1);
        cv::rectangle(image1, cv::Point(200, 100), cv::Point(300, 200), cv::Scalar(255, 0, 0), -1);
        cv::circle(image1, cv::Point(100, 250), 30, cv::Scalar(0, 0, 255), -1);
        
        // Create a second image with slight offset (simulating different camera position)
        cv::Mat image2 = cv::Mat::zeros(300, 400, CV_8UC3);
        cv::rectangle(image2, cv::Point(80, 50), cv::Point(180, 150), cv::Scalar(0, 255, 0), -1);
        cv::rectangle(image2, cv::Point(230, 100), cv::Point(330, 200), cv::Scalar(255, 0, 0), -1);
        cv::circle(image2, cv::Point(130, 250), 30, cv::Scalar(0, 0, 255), -1);
        
        // Create a third image
        cv::Mat image3 = cv::Mat::zeros(300, 400, CV_8UC3);
        cv::rectangle(image3, cv::Point(110, 50), cv::Point(210, 150), cv::Scalar(0, 255, 0), -1);
        cv::rectangle(image3, cv::Point(260, 100), cv::Point(360, 200), cv::Scalar(255, 0, 0), -1);
        cv::circle(image3, cv::Point(160, 250), 30, cv::Scalar(0, 0, 255), -1);
        
        // Add some text to distinguish images
        cv::putText(image1, "Image 1", cv::Point(10, 30), cv::FONT_HERSHEY_SIMPLEX, 1, cv::Scalar(255, 255, 255), 2);
        cv::putText(image2, "Image 2", cv::Point(10, 30), cv::FONT_HERSHEY_SIMPLEX, 1, cv::Scalar(255, 255, 255), 2);
        cv::putText(image3, "Image 3", cv::Point(10, 30), cv::FONT_HERSHEY_SIMPLEX, 1, cv::Scalar(255, 255, 255), 2);
        
        // Store images in vector
        std::vector<cv::Mat> images;
        images.push_back(image1);
        images.push_back(image2);
        images.push_back(image3);
        
        // Display original images
        cv::imshow("Original Image 1", image1);
        cv::imshow("Original Image 2", image2);
        cv::imshow("Original Image 3", image3);
        
        std::cout << "Starting image stitching process..." << std::endl;
        
        // Create Stitcher object
        cv::Stitcher::Mode mode = cv::Stitcher::PANORAMA;
        cv::Ptr<cv::Stitcher> stitcher = cv::Stitcher::create(mode);
        
        // Perform stitching
        cv::Mat panorama;
        cv::Stitcher::Status status = stitcher->stitch(images, panorama);
        
        if (status != cv::Stitcher::OK) {
            std::cout << "Can't stitch images, error code = " << int(status) << std::endl;
            
            // Try manual feature-based stitching as fallback
            std::cout << "Attempting manual feature-based stitching..." << std::endl;
            
            // Use ORB detector for feature detection
            cv::Ptr<cv::ORB> detector = cv::ORB::create();
            
            // Detect keypoints and descriptors for each image
            std::vector<std::vector<cv::KeyPoint>> keypoints(images.size());
            std::vector<cv::Mat> descriptors(images.size());
            
            for (size_t i = 0; i < images.size(); i++) {
                detector->detectAndCompute(images[i], cv::noArray(), keypoints[i], descriptors[i]);
                std::cout << "Found " << keypoints[i].size() << " keypoints in image " << i + 1 << std::endl;
            }
            
            // Match features between consecutive images
            cv::Ptr<cv::BFMatcher> matcher = cv::BFMatcher::create(cv::NORM_HAMMING);
            
            for (size_t i = 0; i < images.size() - 1; i++) {
                std::vector<cv::DMatch> matches;
                matcher->match(descriptors[i], descriptors[i + 1], matches);
                
                std::cout << "Found " << matches.size() << " matches between image " 
                         << i + 1 << " and " << i + 2 << std::endl;
                
                // Draw matches
                cv::Mat matchImage;
                cv::drawMatches(images[i], keypoints[i], images[i + 1], keypoints[i + 1], 
                              matches, matchImage);
                cv::imshow("Matches " + std::to_string(i + 1) + "-" + std::to_string(i + 2), matchImage);
            }
            
        } else {
            std::cout << "Stitching successful!" << std::endl;
            std::cout << "Panorama size: " << panorama.cols << "x" << panorama.rows << std::endl;
            
            // Display the panorama
            cv::imshow("Stitched Panorama", panorama);
            
            // Save the panorama
            cv::imwrite("panorama_result.jpg", panorama);
            std::cout << "Panorama saved as 'panorama_result.jpg'" << std::endl;
        }
        
        std::cout << "\nKey Features Demonstrated:" << std::endl;
        std::cout << "- Image stitching using OpenCV Stitcher class" << std::endl;
        std::cout << "- Feature detection using ORB detector" << std::endl;
        std::cout << "- Feature matching using BFMatcher" << std::endl;
        std::cout << "- Panorama creation from multiple images" << std::endl;
        std::cout << "- Error handling and fallback methods" << std::endl;
        
        std::cout << "\nPress any key to exit..." << std::endl;
        cv::waitKey(0);
        
    } else {
        std::cout << "For full image stitching demonstration, please provide multiple overlapping images." << std::endl;
        std::cout << "This program works best with 2-5 images that have overlapping regions." << std::endl;
        
        cv::imshow("Loaded Image", image1);
        cv::waitKey(0);
    }
    
    cv::destroyAllWindows();
    return 0;
}
