// 22_realtime_color_tracking.cpp
// Advanced Level - Real-time Color Detection and Tracking
// This program demonstrates real-time color detection and object tracking using HSV color space

#include <iostream>
#include <opencv2/opencv.hpp>
#include <vector>
#include <cstdlib>  // For setenv on macOS

class ColorTracker {
private:
    cv::VideoCapture cap;
    cv::Mat frame, hsv, mask;
    cv::Scalar lower_bound, upper_bound;
    std::vector<cv::Point2f> tracked_points;
    
public:
    ColorTracker() {
        // Try to open camera with better settings for macOS
        cap.open(0);
        
        // Set camera properties to reduce warnings
        cap.set(cv::CAP_PROP_FRAME_WIDTH, 640);
        cap.set(cv::CAP_PROP_FRAME_HEIGHT, 480);
        cap.set(cv::CAP_PROP_FPS, 30);
        
        if (!cap.isOpened()) {
            std::cout << "Error: Could not open camera" << std::endl;
            std::cout << "Please check camera permissions in System Preferences > Security & Privacy > Camera" << std::endl;
            exit(-1);
        }
        
        std::cout << "Camera initialized successfully!" << std::endl;
    }
    
    void setColorRange(cv::Scalar lower, cv::Scalar upper) {
        lower_bound = lower;
        upper_bound = upper;
    }
    
    void trackColor() {
        std::cout << "=== Real-time Color Detection and Tracking ===" << std::endl;
        std::cout << "Note: If you see camera warnings, they are harmless system messages." << std::endl;
        std::cout << "Controls:" << std::endl;
        std::cout << "  'r' - Reset tracking points" << std::endl;
        std::cout << "  'q' - Quit" << std::endl;
        std::cout << "  '1' - Track Red objects" << std::endl;
        std::cout << "  '2' - Track Blue objects" << std::endl;
        std::cout << "  '3' - Track Green objects" << std::endl;
        std::cout << "  '4' - Track Yellow objects" << std::endl;
        std::cout << "  'c' - Calibrate color range" << std::endl;
        
        char key = '1'; // Start with red tracking
        
        while (true) {
            cap >> frame;
            if (frame.empty()) break;
            
            // Flip frame horizontally for mirror effect
            cv::flip(frame, frame, 1);
            
            // Convert BGR to HSV
            cv::cvtColor(frame, hsv, cv::COLOR_BGR2HSV);
            
            // Update color range based on key press
            updateColorRange(key);
            
            // Create mask for color detection
            cv::inRange(hsv, lower_bound, upper_bound, mask);
            
            // Apply morphological operations to clean up the mask
            cv::Mat kernel = cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(5, 5));
            cv::morphologyEx(mask, mask, cv::MORPH_OPEN, kernel);
            cv::morphologyEx(mask, mask, cv::MORPH_CLOSE, kernel);
            
            // Find contours
            std::vector<std::vector<cv::Point>> contours;
            cv::findContours(mask, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);
            
            // Process detected objects
            processDetectedObjects(frame, contours);
            
            // Display results
            displayResults(frame, mask);
            
            // Handle keyboard input
            key = cv::waitKey(1) & 0xFF;
            if (key == 'q') break;
            
            if (key == 'r') {
                tracked_points.clear();
                std::cout << "Tracking points reset!" << std::endl;
            }
            
            if (key == 'c') {
                calibrateColorRange();
            }
        }
    }
    
private:
    void updateColorRange(char key) {
        switch (key) {
            case '1': // Red
                lower_bound = cv::Scalar(0, 120, 70);
                upper_bound = cv::Scalar(10, 255, 255);
                break;
            case '2': // Blue
                lower_bound = cv::Scalar(100, 150, 0);
                upper_bound = cv::Scalar(124, 255, 255);
                break;
            case '3': // Green
                lower_bound = cv::Scalar(40, 50, 50);
                upper_bound = cv::Scalar(80, 255, 255);
                break;
            case '4': // Yellow
                lower_bound = cv::Scalar(20, 100, 100);
                upper_bound = cv::Scalar(30, 255, 255);
                break;
        }
    }
    
    void processDetectedObjects(cv::Mat& frame, const std::vector<std::vector<cv::Point>>& contours) {
        for (const auto& contour : contours) {
            double area = cv::contourArea(contour);
            
            // Filter out small objects
            if (area > 500) {
                // Get bounding rectangle
                cv::Rect rect = cv::boundingRect(contour);
                
                // Draw rectangle around detected object
                cv::rectangle(frame, rect, cv::Scalar(0, 255, 0), 2);
                
                // Calculate center point
                cv::Point center(rect.x + rect.width / 2, rect.y + rect.height / 2);
                
                // Draw center point
                cv::circle(frame, center, 5, cv::Scalar(255, 0, 0), -1);
                
                // Store tracking point
                tracked_points.push_back(center);
                
                // Keep only recent tracking points (last 50 points)
                if (tracked_points.size() > 50) {
                    tracked_points.erase(tracked_points.begin());
                }
                
                // Draw tracking trail
                drawTrackingTrail(frame);
                
                // Display object information
                std::string info = "Area: " + std::to_string((int)area);
                cv::putText(frame, info, cv::Point(rect.x, rect.y - 10), 
                          cv::FONT_HERSHEY_SIMPLEX, 0.6, cv::Scalar(255, 255, 255), 2);
            }
        }
    }
    
    void drawTrackingTrail(cv::Mat& frame) {
        for (size_t i = 1; i < tracked_points.size(); i++) {
            // Calculate trail color intensity based on age
            int intensity = 255 * (i / (double)tracked_points.size());
            cv::Scalar color(0, intensity, 255 - intensity);
            
            // Draw line between consecutive points
            cv::line(frame, tracked_points[i - 1], tracked_points[i], color, 2);
        }
    }
    
    void displayResults(cv::Mat& frame, const cv::Mat& mask) {
        // Create display windows
        cv::Mat display;
        cv::hconcat(frame, cv::Mat::zeros(frame.rows, 50, frame.type()), display);
        
        // Convert mask to 3-channel BGR for proper concatenation
        cv::Mat mask_bgr;
        cv::cvtColor(mask, mask_bgr, cv::COLOR_GRAY2BGR);
        cv::hconcat(display, mask_bgr, display);
        
        // Add color space visualization
        cv::Mat hsv_display;
        cv::cvtColor(hsv, hsv_display, cv::COLOR_HSV2BGR);
        
        // Resize hsv_display to match the width of display for proper vertical concatenation
        cv::Mat hsv_resized;
        cv::resize(hsv_display, hsv_resized, cv::Size(display.cols, hsv_display.rows));
        cv::vconcat(display, hsv_resized, display);
        
        cv::imshow("Color Tracking - Original | Mask | HSV", display);
        
        // Display current color range info
        std::string colorInfo = "Lower: [" + std::to_string((int)lower_bound[0]) + "," + 
                               std::to_string((int)lower_bound[1]) + "," + 
                               std::to_string((int)lower_bound[2]) + "]";
        cv::putText(frame, colorInfo, cv::Point(10, 30), cv::FONT_HERSHEY_SIMPLEX, 0.6, cv::Scalar(255, 255, 255), 2);
        
        std::string colorInfo2 = "Upper: [" + std::to_string((int)upper_bound[0]) + "," + 
                                std::to_string((int)upper_bound[1]) + "," + 
                                std::to_string((int)upper_bound[2]) + "]";
        cv::putText(frame, colorInfo2, cv::Point(10, 60), cv::FONT_HERSHEY_SIMPLEX, 0.6, cv::Scalar(255, 255, 255), 2);
    }
    
    void calibrateColorRange() {
        std::cout << "\n=== Color Range Calibration ===" << std::endl;
        std::cout << "This is a simplified calibration. In practice, you would:" << std::endl;
        std::cout << "1. Show the target color to the camera" << std::endl;
        std::cout << "2. Use trackbars to adjust HSV values" << std::endl;
        std::cout << "3. Save the calibrated range for future use" << std::endl;
        
        // Example calibration for a specific red object
        cv::Scalar sample_lower(0, 100, 100);
        cv::Scalar sample_upper(10, 255, 255);
        
        std::cout << "Sample calibrated range for red objects:" << std::endl;
        std::cout << "Lower: [" << sample_lower[0] << ", " << sample_lower[1] << ", " << sample_lower[2] << "]" << std::endl;
        std::cout << "Upper: [" << sample_upper[0] << ", " << sample_upper[1] << ", " << sample_upper[2] << "]" << std::endl;
        
        // Apply calibrated range
        lower_bound = sample_lower;
        upper_bound = sample_upper;
    }
};

int main() {
    // Suppress macOS camera warnings
    #ifdef __APPLE__
    setenv("QT_MAC_DISABLE_FORCE_STANDALONE_FOCUS_EVENTS", "1", 1);
    #endif
    
    try {
        ColorTracker tracker;
        
        // Set initial color range for red objects
        tracker.setColorRange(cv::Scalar(0, 120, 70), cv::Scalar(10, 255, 255));
        
        // Start tracking
        tracker.trackColor();
        
    } catch (const cv::Exception& e) {
        std::cout << "OpenCV Error: " << e.what() << std::endl;
        return -1;
    } catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << std::endl;
        return -1;
    }
    
    std::cout << "\nKey Features Demonstrated:" << std::endl;
    std::cout << "- Real-time color detection using HSV color space" << std::endl;
    std::cout << "- Multiple color tracking (Red, Blue, Green, Yellow)" << std::endl;
    std::cout << "- Object contour detection and filtering" << std::endl;
    std::cout << "- Real-time tracking trail visualization" << std::endl;
    std::cout << "- Morphological operations for noise reduction" << std::endl;
    std::cout << "- Interactive color range calibration" << std::endl;
    std::cout << "- Multi-window display with different views" << std::endl;
    
    cv::destroyAllWindows();
    return 0;
}
