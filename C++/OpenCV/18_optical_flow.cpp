// 18_optical_flow.cpp
// Advanced Level - Optical Flow
// This program demonstrates optical flow for motion detection

#include <iostream>
#include <opencv2/opencv.hpp>

int main() {
    // Open the default camera
    cv::VideoCapture cap(0);
    
    if (!cap.isOpened()) {
        std::cout << "Error: Could not open camera" << std::endl;
        return -1;
    }
    
    std::cout << "Optical Flow Demo" << std::endl;
    std::cout << "Controls:" << std::endl;
    std::cout << "  '1' - Lucas-Kanade Optical Flow" << std::endl;
    std::cout << "  '2' - Dense Optical Flow (Farneback)" << std::endl;
    std::cout << "  '3' - Motion Magnitude" << std::endl;
    std::cout << "  'r' - Reset" << std::endl;
    std::cout << "  'q' - Quit" << std::endl;
    
    cv::Mat frame, prev_frame, curr_frame;
    cv::Mat prev_gray, curr_gray;
    int mode = 1;
    int frameCount = 0;
    
    // Parameters for Lucas-Kanade
    std::vector<cv::Point2f> prev_points, curr_points;
    std::vector<uchar> status;
    std::vector<float> err;
    
    // Parameters for corner detection
    cv::TermCriteria termcrit(cv::TermCriteria::COUNT | cv::TermCriteria::EPS, 20, 0.03);
    cv::Size subPixWinSize(10, 10), winSize(31, 31);
    
    while (true) {
        // Capture frame
        cap >> frame;
        
        if (frame.empty()) {
            std::cout << "Error: Could not capture frame" << std::endl;
            break;
        }
        
        frameCount++;
        
        // Convert to grayscale
        cv::cvtColor(frame, curr_gray, cv::COLOR_BGR2GRAY);
        
        cv::Mat result = frame.clone();
        
        if (!prev_gray.empty()) {
            if (mode == 1) {
                // Lucas-Kanade Optical Flow
                if (prev_points.empty() || frameCount % 30 == 0) {
                    // Detect corners in the previous frame
                    cv::goodFeaturesToTrack(prev_gray, prev_points, 100, 0.01, 10, cv::Mat(), 3, false, 0.04);
                    cv::cornerSubPix(prev_gray, prev_points, subPixWinSize, cv::Size(-1, -1), termcrit);
                }
                
                if (!prev_points.empty()) {
                    // Calculate optical flow
                    cv::calcOpticalFlowPyrLK(prev_gray, curr_gray, prev_points, curr_points, status, err, winSize, 3, termcrit, 0, 0.001);
                    
                    // Draw optical flow vectors
                    for (size_t i = 0; i < prev_points.size(); i++) {
                        if (status[i]) {
                            cv::circle(result, curr_points[i], 3, cv::Scalar(0, 255, 0), -1);
                            cv::arrowedLine(result, prev_points[i], curr_points[i], cv::Scalar(0, 255, 0), 2);
                        }
                    }
                    
                    // Update points for next iteration
                    prev_points = curr_points;
                }
            }
            else if (mode == 2) {
                // Dense Optical Flow (Farneback)
                cv::Mat flow;
                cv::calcOpticalFlowFarneback(prev_gray, curr_gray, flow, 0.5, 3, 15, 3, 5, 1.2, 0);
                
                // Draw flow field
                for (int y = 0; y < flow.rows; y += 10) {
                    for (int x = 0; x < flow.cols; x += 10) {
                        cv::Point2f flow_at_point = flow.at<cv::Point2f>(y, x);
                        cv::Point2f pt1(x, y);
                        cv::Point2f pt2(x + flow_at_point.x, y + flow_at_point.y);
                        
                        // Only draw if there's significant motion
                        if (cv::norm(flow_at_point) > 2) {
                            cv::arrowedLine(result, pt1, pt2, cv::Scalar(0, 255, 0), 1);
                        }
                    }
                }
            }
            else if (mode == 3) {
                // Motion Magnitude
                cv::Mat flow;
                cv::calcOpticalFlowFarneback(prev_gray, curr_gray, flow, 0.5, 3, 15, 3, 5, 1.2, 0);
                
                // Calculate magnitude of motion
                std::vector<cv::Mat> flow_parts;
                cv::split(flow, flow_parts);
                cv::Mat magnitude, angle;
                cv::cartToPolar(flow_parts[0], flow_parts[1], magnitude, angle, true);
                
                // Normalize magnitude for visualization
                cv::normalize(magnitude, magnitude, 0, 255, cv::NORM_MINMAX, CV_8UC1);
                
                // Create color-coded motion map
                cv::Mat motion_vis = cv::Mat::zeros(magnitude.size(), CV_8UC3);
                for (int y = 0; y < magnitude.rows; y++) {
                    for (int x = 0; x < magnitude.cols; x++) {
                        float mag = magnitude.at<uchar>(y, x);
                        if (mag > 10) {  // Threshold for motion
                            motion_vis.at<cv::Vec3b>(y, x) = cv::Vec3b(255 - mag, 0, mag);
                        }
                    }
                }
                
                // Overlay motion on original image
                cv::addWeighted(result, 0.7, motion_vis, 0.3, 0, result);
            }
        }
        
        // Add mode indicator
        std::string modeText;
        switch (mode) {
            case 1: modeText = "Lucas-Kanade Optical Flow"; break;
            case 2: modeText = "Dense Optical Flow (Farneback)"; break;
            case 3: modeText = "Motion Magnitude"; break;
        }
        
        cv::putText(result, modeText, cv::Point(10, 30), 
                   cv::FONT_HERSHEY_SIMPLEX, 0.7, cv::Scalar(255, 255, 255), 2);
        cv::putText(result, "Frame: " + std::to_string(frameCount), 
                   cv::Point(10, 60), cv::FONT_HERSHEY_SIMPLEX, 0.7, cv::Scalar(255, 255, 255), 2);
        
        // Display result
        cv::imshow("Optical Flow", result);
        
        // Update previous frame
        curr_gray.copyTo(prev_gray);
        
        // Handle keyboard input
        char key = cv::waitKey(1) & 0xFF;
        
        if (key == 'q' || key == 27) {
            break;
        }
        else if (key >= '1' && key <= '3') {
            mode = key - '0';
            std::cout << "Switched to mode " << mode << ": " << modeText << std::endl;
        }
        else if (key == 'r') {
            prev_points.clear();
            curr_points.clear();
            prev_gray.release();
            std::cout << "Reset optical flow" << std::endl;
        }
    }
    
    cap.release();
    cv::destroyAllWindows();
    
    std::cout << "Optical flow demo ended. Processed " << frameCount << " frames." << std::endl;
    
    return 0;
}
