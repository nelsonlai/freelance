// 02_camera_capture.cpp
// Beginner Level - Camera Capture
// This program demonstrates how to capture video from a webcam

#include <iostream>
#include <opencv2/opencv.hpp>

int main() {
    // Open the default camera (camera index 0)
    cv::VideoCapture cap(0);
    
    // Check if camera opened successfully
    if (!cap.isOpened()) {
        std::cout << "Error: Could not open camera" << std::endl;
        return -1;
    }
    
    std::cout << "Camera opened successfully!" << std::endl;
    std::cout << "Press 'q' to quit, 's' to save a screenshot" << std::endl;
    
    cv::Mat frame;
    int frameCount = 0;
    
    while (true) {
        // Capture frame from camera
        cap >> frame;
        
        // Check if frame was captured successfully
        if (frame.empty()) {
            std::cout << "Error: Could not capture frame" << std::endl;
            break;
        }
        
        // Add frame counter text to the image
        std::string text = "Frame: " + std::to_string(frameCount++);
        cv::putText(frame, text, cv::Point(10, 30), 
                   cv::FONT_HERSHEY_SIMPLEX, 1, cv::Scalar(0, 255, 0), 2);
        
        // Display the frame
        cv::imshow("Camera Feed", frame);
        
        // Wait for key press (1ms) and check for 'q' or 's'
        char key = cv::waitKey(1) & 0xFF;
        
        if (key == 'q' || key == 27) {  // 'q' or ESC key
            std::cout << "Quitting..." << std::endl;
            break;
        }
        else if (key == 's') {  // 's' key to save screenshot
            std::string filename = "screenshot_" + std::to_string(frameCount) + ".jpg";
            cv::imwrite(filename, frame);
            std::cout << "Screenshot saved as: " << filename << std::endl;
        }
    }
    
    // Release camera and close windows
    cap.release();
    cv::destroyAllWindows();
    
    return 0;
}
