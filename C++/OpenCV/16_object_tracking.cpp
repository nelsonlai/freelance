// 16_object_tracking.cpp
// Advanced Level - Object Tracking
// This program demonstrates object tracking using different algorithms

#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/tracking.hpp>

// Global variables for mouse callback
cv::Mat g_frame;
bool g_tracking = false;
cv::Rect2d g_bbox;
cv::Ptr<cv::Tracker> g_tracker;
cv::Rect g_selection;
bool g_selecting = false;
cv::Point g_startPoint, g_endPoint;

// Mouse callback function
void mouseCallback(int event, int x, int y, int flags, void* userdata) {
    if (event == cv::EVENT_LBUTTONDOWN) {
        g_selecting = true;
        g_startPoint = cv::Point(x, y);
        g_selection = cv::Rect(x, y, 0, 0);
    }
    else if (event == cv::EVENT_MOUSEMOVE && g_selecting) {
        g_endPoint = cv::Point(x, y);
        g_selection = cv::Rect(
            std::min(g_startPoint.x, g_endPoint.x),
            std::min(g_startPoint.y, g_endPoint.y),
            std::abs(g_endPoint.x - g_startPoint.x),
            std::abs(g_endPoint.y - g_startPoint.y)
        );
    }
    else if (event == cv::EVENT_LBUTTONUP) {
        g_selecting = false;
        if (g_selection.width > 10 && g_selection.height > 10) {
            g_bbox = cv::Rect2d(g_selection.x, g_selection.y, g_selection.width, g_selection.height);
            // Initialize tracker
            g_tracker = cv::TrackerKCF::create();
            g_tracker->init(g_frame, g_bbox);
            g_tracking = true;
        }
    }
}

int main() {
    // Open the default camera
    cv::VideoCapture cap(0);
    
    if (!cap.isOpened()) {
        std::cout << "Error: Could not open camera" << std::endl;
        return -1;
    }
    
    std::cout << "Object Tracking Demo" << std::endl;
    std::cout << "Instructions:" << std::endl;
    std::cout << "1. Press 's' to start tracking (select region with mouse)" << std::endl;
    std::cout << "2. Press 'r' to reset tracking" << std::endl;
    std::cout << "3. Press 'q' to quit" << std::endl;
    
    cv::Mat frame;
    bool tracking = false;
    cv::Rect2d bbox;
    cv::Ptr<cv::Tracker> tracker;
    
    // Mouse callback for region selection
    cv::Rect selection;
    bool selecting = false;
    cv::Point startPoint, endPoint;
    
    cv::namedWindow("Object Tracking", cv::WINDOW_AUTOSIZE);
    cv::setMouseCallback("Object Tracking", mouseCallback, nullptr);
    
    int frameCount = 0;
    
    while (true) {
        // Capture frame
        cap >> frame;
        
        if (frame.empty()) {
            std::cout << "Error: Could not capture frame" << std::endl;
            break;
        }
        
        // Update global frame for mouse callback
        g_frame = frame.clone();
        
        frameCount++;
        
        if (g_tracking) {
            // Update tracker - convert Rect2d to Rect for the update call
            cv::Rect bbox_rect(static_cast<int>(g_bbox.x), static_cast<int>(g_bbox.y), 
                              static_cast<int>(g_bbox.width), static_cast<int>(g_bbox.height));
            bool ok = g_tracker->update(frame, bbox_rect);
            
            // Update the global bbox with the result
            g_bbox = cv::Rect2d(bbox_rect.x, bbox_rect.y, bbox_rect.width, bbox_rect.height);
            
            if (ok) {
                // Draw tracked object
                cv::rectangle(frame, bbox_rect, cv::Scalar(0, 255, 0), 2);
                
                // Add tracking info
                cv::Point center(static_cast<int>(g_bbox.x + g_bbox.width/2), 
                               static_cast<int>(g_bbox.y + g_bbox.height/2));
                cv::circle(frame, center, 5, cv::Scalar(0, 255, 0), -1);
                
                std::string text = "Tracking: (" + std::to_string(center.x) + ", " + std::to_string(center.y) + ")";
                cv::putText(frame, text, cv::Point(10, 30), 
                           cv::FONT_HERSHEY_SIMPLEX, 0.7, cv::Scalar(0, 255, 0), 2);
                
                // Draw trajectory (simple version - store last few positions)
                static std::vector<cv::Point> trajectory;
                trajectory.push_back(center);
                if (trajectory.size() > 50) {
                    trajectory.erase(trajectory.begin());
                }
                
                // Draw trajectory
                for (size_t i = 1; i < trajectory.size(); i++) {
                    cv::line(frame, trajectory[i-1], trajectory[i], cv::Scalar(255, 0, 0), 2);
                }
            }
            else {
                cv::putText(frame, "Tracking failed", cv::Point(10, 30), 
                           cv::FONT_HERSHEY_SIMPLEX, 0.7, cv::Scalar(0, 0, 255), 2);
            }
        }
        else if (g_selecting) {
            // Draw selection rectangle
            cv::rectangle(frame, g_selection, cv::Scalar(255, 0, 0), 2);
            cv::putText(frame, "Select region to track", cv::Point(10, 30), 
                       cv::FONT_HERSHEY_SIMPLEX, 0.7, cv::Scalar(255, 0, 0), 2);
        }
        else {
            cv::putText(frame, "Press 's' to start tracking", cv::Point(10, 30), 
                       cv::FONT_HERSHEY_SIMPLEX, 0.7, cv::Scalar(255, 255, 255), 2);
        }
        
        // Add frame info
        cv::putText(frame, "Frame: " + std::to_string(frameCount), 
                   cv::Point(10, frame.rows - 20), cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(255, 255, 255), 1);
        
        // Display frame
        cv::imshow("Object Tracking", frame);
        
        // Handle keyboard input
        char key = cv::waitKey(1) & 0xFF;
        
        if (key == 'q' || key == 27) {
            break;
        }
        else if (key == 's' && !g_tracking) {
            std::cout << "Click and drag to select region to track" << std::endl;
        }
        else if (key == 'r') {
            g_tracking = false;
            g_tracker.release();
            std::cout << "Tracking reset" << std::endl;
        }
    }
    
    cap.release();
    cv::destroyAllWindows();
    
    std::cout << "Object tracking ended. Processed " << frameCount << " frames." << std::endl;
    
    return 0;
}
