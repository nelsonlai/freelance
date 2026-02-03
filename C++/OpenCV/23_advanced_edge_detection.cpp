// 23_advanced_edge_detection.cpp
// Advanced Level - Advanced Edge Detection with Multiple Algorithms
// This program demonstrates various edge detection algorithms and their applications

#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
#include <vector>

class AdvancedEdgeDetector {
private:
    cv::Mat original, gray, edges;
    std::vector<cv::Mat> edge_results;
    std::vector<std::string> algorithm_names;
    
public:
    AdvancedEdgeDetector() {
        algorithm_names = {
            "Canny Edge Detection",
            "Sobel Edge Detection",
            "Laplacian Edge Detection",
            "Scharr Edge Detection",
            "Morphological Edge Detection",
            "Adaptive Threshold Edge",
            "Log Edge Detection",
            "Zero Crossing Edge Detection"
        };
    }
    
    void loadImage(const std::string& filename) {
        original = cv::imread(filename);
        if (original.empty()) {
            std::cout << "Error: Could not load image '" << filename << "'" << std::endl;
            std::cout << "Creating a sample image for demonstration..." << std::endl;
            createSampleImage();
        }
        
        // Convert to grayscale
        cv::cvtColor(original, gray, cv::COLOR_BGR2GRAY);
        std::cout << "Image loaded successfully!" << std::endl;
    }
    
    void detectAllEdges() {
        std::cout << "=== Advanced Edge Detection with Multiple Algorithms ===" << std::endl;
        
        // Clear previous results
        edge_results.clear();
        
        // 1. Canny Edge Detection
        cv::Mat canny_edges;
        cv::Canny(gray, canny_edges, 50, 150, 3);
        edge_results.push_back(canny_edges.clone());
        
        // 2. Sobel Edge Detection
        cv::Mat sobel_x, sobel_y, sobel_edges;
        cv::Sobel(gray, sobel_x, CV_64F, 1, 0, 3);
        cv::Sobel(gray, sobel_y, CV_64F, 0, 1, 3);
        cv::magnitude(sobel_x, sobel_y, sobel_edges);
        cv::convertScaleAbs(sobel_edges, sobel_edges);
        edge_results.push_back(sobel_edges.clone());
        
        // 3. Laplacian Edge Detection
        cv::Mat laplacian_edges;
        cv::Laplacian(gray, laplacian_edges, CV_64F, 3);
        cv::convertScaleAbs(laplacian_edges, laplacian_edges);
        edge_results.push_back(laplacian_edges.clone());
        
        // 4. Scharr Edge Detection
        cv::Mat scharr_x, scharr_y, scharr_edges;
        cv::Scharr(gray, scharr_x, CV_64F, 1, 0);
        cv::Scharr(gray, scharr_y, CV_64F, 0, 1);
        cv::magnitude(scharr_x, scharr_y, scharr_edges);
        cv::convertScaleAbs(scharr_edges, scharr_edges);
        edge_results.push_back(scharr_edges.clone());
        
        // 5. Morphological Edge Detection
        cv::Mat morph_edges;
        cv::Mat kernel = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(3, 3));
        cv::Mat dilated, eroded;
        cv::dilate(gray, dilated, kernel);
        cv::erode(gray, eroded, kernel);
        cv::subtract(dilated, eroded, morph_edges);
        edge_results.push_back(morph_edges.clone());
        
        // 6. Adaptive Threshold Edge Detection
        cv::Mat adaptive_edges;
        cv::adaptiveThreshold(gray, adaptive_edges, 255, cv::ADAPTIVE_THRESH_GAUSSIAN_C, 
                             cv::THRESH_BINARY, 11, 2);
        cv::bitwise_not(adaptive_edges, adaptive_edges);
        edge_results.push_back(adaptive_edges.clone());
        
        // 7. LoG (Laplacian of Gaussian) Edge Detection
        cv::Mat log_edges;
        cv::Mat blurred;
        cv::GaussianBlur(gray, blurred, cv::Size(5, 5), 1.0);
        cv::Laplacian(blurred, log_edges, CV_64F, 3);
        cv::convertScaleAbs(log_edges, log_edges);
        edge_results.push_back(log_edges.clone());
        
        // 8. Zero Crossing Edge Detection (simplified)
        cv::Mat zero_cross_edges;
        detectZeroCrossings(zero_cross_edges);
        edge_results.push_back(zero_cross_edges.clone());
        
        std::cout << "Edge detection completed using " << edge_results.size() << " algorithms." << std::endl;
    }
    
    void displayResults() {
        // Create a large display canvas
        int cols = 4;
        int rows = 3;
        int cell_width = 300;
        int cell_height = 200;
        
        cv::Mat display(rows * cell_height, cols * cell_width, CV_8UC3, cv::Scalar(0, 0, 0));
        
        // Display original image in top-left
        cv::Mat resized_original;
        cv::resize(original, resized_original, cv::Size(cell_width, cell_height));
        cv::Rect roi(0, 0, cell_width, cell_height);
        resized_original.copyTo(display(roi));
        
        // Add title
        cv::putText(display, "Original Image", cv::Point(10, 30), 
                   cv::FONT_HERSHEY_SIMPLEX, 0.7, cv::Scalar(255, 255, 255), 2);
        
        // Display edge detection results
        for (size_t i = 0; i < edge_results.size() && i < 8; i++) {
            int row = (i + 1) / cols;
            int col = (i + 1) % cols;
            
            cv::Mat resized_edge;
            cv::resize(edge_results[i], resized_edge, cv::Size(cell_width, cell_height));
            
            // Convert grayscale to BGR for display
            cv::Mat color_edge;
            cv::cvtColor(resized_edge, color_edge, cv::COLOR_GRAY2BGR);
            
            cv::Rect roi(col * cell_width, row * cell_height, cell_width, cell_height);
            color_edge.copyTo(display(roi));
            
            // Add algorithm name
            cv::putText(display, algorithm_names[i], cv::Point(col * cell_width + 10, row * cell_height + 30), 
                       cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(255, 255, 255), 1);
        }
        
        cv::imshow("Advanced Edge Detection Comparison", display);
        
        // Also display individual results for detailed analysis
        displayIndividualResults();
    }
    
    void displayIndividualResults() {
        for (size_t i = 0; i < edge_results.size(); i++) {
            cv::imshow(algorithm_names[i], edge_results[i]);
        }
    }
    
    void analyzeEdgeQuality() {
        std::cout << "\n=== Edge Quality Analysis ===" << std::endl;
        
        // Calculate edge density for each method
        for (size_t i = 0; i < edge_results.size(); i++) {
            cv::Scalar mean_val = cv::mean(edge_results[i]);
            double edge_density = mean_val[0] / 255.0;
            
            std::cout << algorithm_names[i] << ":" << std::endl;
            std::cout << "  Edge Density: " << std::fixed << std::setprecision(3) << edge_density << std::endl;
            std::cout << "  Mean Intensity: " << std::fixed << std::setprecision(1) << mean_val[0] << std::endl;
            
            // Count edge pixels (pixels above threshold)
            cv::Mat binary_edges;
            cv::threshold(edge_results[i], binary_edges, 50, 255, cv::THRESH_BINARY);
            int edge_pixels = cv::countNonZero(binary_edges);
            double edge_ratio = (double)edge_pixels / (edge_results[i].rows * edge_results[i].cols);
            
            std::cout << "  Edge Pixels: " << edge_pixels << " (" << std::fixed << std::setprecision(2) 
                     << edge_ratio * 100 << "%)" << std::endl;
            std::cout << std::endl;
        }
    }
    
    void demonstrateEdgeApplications() {
        std::cout << "\n=== Edge Detection Applications ===" << std::endl;
        
        // 1. Edge-based segmentation
        cv::Mat segmented;
        cv::watershed(original, createMarkerImage());
        
        // 2. Edge enhancement
        cv::Mat enhanced;
        cv::addWeighted(original, 1.0, cv::Mat::zeros(original.size(), original.type()), 0.0, 0, enhanced);
        
        // 3. Edge-based feature detection
        std::vector<cv::Point2f> corners;
        cv::goodFeaturesToTrack(edge_results[0], corners, 100, 0.01, 10);
        
        cv::Mat corner_image = original.clone();
        for (const auto& corner : corners) {
            cv::circle(corner_image, corner, 5, cv::Scalar(0, 255, 0), -1);
        }
        
        cv::imshow("Edge-based Corner Detection", corner_image);
        
        std::cout << "Found " << corners.size() << " corner features using edge information." << std::endl;
    }
    
private:
    void createSampleImage() {
        // Create a complex sample image with various shapes and textures
        original = cv::Mat::zeros(400, 600, CV_8UC3);
        
        // Draw various shapes
        cv::rectangle(original, cv::Point(50, 50), cv::Point(150, 150), cv::Scalar(0, 255, 0), -1);
        cv::rectangle(original, cv::Point(200, 100), cv::Point(300, 200), cv::Scalar(255, 0, 0), -1);
        cv::circle(original, cv::Point(400, 100), 50, cv::Scalar(0, 0, 255), -1);
        cv::ellipse(original, cv::Point(500, 200), cv::Size(60, 30), 45, 0, 360, cv::Scalar(255, 255, 0), -1);
        
        // Add some text
        cv::putText(original, "Edge Detection Test", cv::Point(150, 300), 
                   cv::FONT_HERSHEY_SIMPLEX, 1, cv::Scalar(255, 255, 255), 2);
        
        // Add noise for more realistic testing
        cv::Mat noise = cv::Mat::zeros(original.size(), original.type());
        cv::randn(noise, cv::Scalar::all(0), cv::Scalar::all(25));
        original += noise;
        
        std::cout << "Sample image created for edge detection testing." << std::endl;
    }
    
    void detectZeroCrossings(cv::Mat& result) {
        // Simplified zero crossing detection using Laplacian
        cv::Mat laplacian;
        cv::Laplacian(gray, laplacian, CV_64F, 3);
        
        result = cv::Mat::zeros(gray.size(), CV_8UC1);
        
        // Find zero crossings (simplified version)
        for (int y = 1; y < laplacian.rows - 1; y++) {
            for (int x = 1; x < laplacian.cols - 1; x++) {
                double center = laplacian.at<double>(y, x);
                double neighbors[4] = {
                    laplacian.at<double>(y-1, x),   // top
                    laplacian.at<double>(y+1, x),   // bottom
                    laplacian.at<double>(y, x-1),   // left
                    laplacian.at<double>(y, x+1)    // right
                };
                
                // Check for sign change (zero crossing)
                for (int i = 0; i < 4; i++) {
                    if ((center > 0 && neighbors[i] < 0) || (center < 0 && neighbors[i] > 0)) {
                        result.at<uchar>(y, x) = 255;
                        break;
                    }
                }
            }
        }
    }
    
    cv::Mat createMarkerImage() {
        cv::Mat markers = cv::Mat::zeros(gray.size(), CV_32SC1);
        
        // Create markers from edge information
        cv::Mat binary_edges;
        cv::threshold(edge_results[0], binary_edges, 50, 255, cv::THRESH_BINARY);
        
        // Find contours and create markers
        std::vector<std::vector<cv::Point>> contours;
        cv::findContours(binary_edges, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);
        
        for (size_t i = 0; i < contours.size(); i++) {
            cv::drawContours(markers, contours, i, cv::Scalar(i + 1), -1);
        }
        
        return markers;
    }
};

int main() {
    AdvancedEdgeDetector detector;
    
    // Load image (will create sample if image.jpg not found)
    detector.loadImage("image.jpg");
    
    // Perform edge detection using multiple algorithms
    detector.detectAllEdges();
    
    // Display results
    detector.displayResults();
    
    // Analyze edge quality
    detector.analyzeEdgeQuality();
    
    // Demonstrate applications
    detector.demonstrateEdgeApplications();
    
    std::cout << "\nKey Features Demonstrated:" << std::endl;
    std::cout << "- Canny edge detection with parameter tuning" << std::endl;
    std::cout << "- Sobel and Scharr gradient-based edge detection" << std::endl;
    std::cout << "- Laplacian-based edge detection" << std::endl;
    std::cout << "- Morphological edge detection" << std::endl;
    std::cout << "- Adaptive threshold edge detection" << std::endl;
    std::cout << "- LoG (Laplacian of Gaussian) edge detection" << std::endl;
    std::cout << "- Zero crossing edge detection" << std::endl;
    std::cout << "- Edge quality analysis and comparison" << std::endl;
    std::cout << "- Edge-based feature detection applications" << std::endl;
    
    std::cout << "\nPress any key to exit..." << std::endl;
    cv::waitKey(0);
    cv::destroyAllWindows();
    
    return 0;
}
