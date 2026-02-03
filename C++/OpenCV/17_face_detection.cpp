// 17_face_detection.cpp
// Advanced Level - Face Detection and Recognition
// This program demonstrates face detection using Haar cascades

#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/objdetect.hpp>

int main() {
    // Load the Haar cascade classifier for face detection
    cv::CascadeClassifier face_cascade;
    if (!face_cascade.load("haarcascade_frontalface_alt.xml")) {
        std::cout << "Error: Could not load face cascade classifier" << std::endl;
        std::cout << "Make sure haarcascade_frontalface_alt.xml is in the current directory" << std::endl;
        return -1;
    }
    
    // Load the Haar cascade classifier for eye detection
    cv::CascadeClassifier eye_cascade;
    if (!eye_cascade.load("haarcascade_eye_tree_eyeglasses.xml")) {
        std::cout << "Warning: Could not load eye cascade classifier" << std::endl;
        std::cout << "Eye detection will be disabled" << std::endl;
    }
    
    // Open the default camera
    cv::VideoCapture cap(0);
    
    if (!cap.isOpened()) {
        std::cout << "Error: Could not open camera" << std::endl;
        return -1;
    }
    
    std::cout << "Face Detection Demo" << std::endl;
    std::cout << "Controls:" << std::endl;
    std::cout << "  '1' - Face detection only" << std::endl;
    std::cout << "  '2' - Face + Eye detection" << std::endl;
    std::cout << "  '3' - Face detection with blur effect" << std::endl;
    std::cout << "  'q' - Quit" << std::endl;
    
    cv::Mat frame, gray;
    int mode = 1;
    int frameCount = 0;
    
    while (true) {
        // Capture frame
        cap >> frame;
        
        if (frame.empty()) {
            std::cout << "Error: Could not capture frame" << std::endl;
            break;
        }
        
        frameCount++;
        
        // Convert to grayscale
        cv::cvtColor(frame, gray, cv::COLOR_BGR2GRAY);
        cv::equalizeHist(gray, gray);
        
        // Detect faces
        std::vector<cv::Rect> faces;
        face_cascade.detectMultiScale(gray, faces, 1.1, 3, 0, cv::Size(30, 30));
        
        cv::Mat result = frame.clone();
        
        for (size_t i = 0; i < faces.size(); i++) {
            cv::Rect face = faces[i];
            
            // Draw face rectangle
            cv::rectangle(result, face, cv::Scalar(0, 255, 0), 2);
            
            // Add face number
            cv::putText(result, "Face " + std::to_string(i + 1), 
                       cv::Point(face.x, face.y - 10),
                       cv::FONT_HERSHEY_SIMPLEX, 0.7, cv::Scalar(0, 255, 0), 2);
            
            // Face center point
            cv::Point center(face.x + face.width/2, face.y + face.height/2);
            cv::circle(result, center, 3, cv::Scalar(0, 255, 0), -1);
            
            // Mode-specific processing
            if (mode == 2) {
                // Eye detection within face region
                cv::Mat faceROI = gray(face);
                std::vector<cv::Rect> eyes;
                eye_cascade.detectMultiScale(faceROI, eyes, 1.1, 3, 0, cv::Size(20, 20));
                
                for (size_t j = 0; j < eyes.size(); j++) {
                    cv::Point eye_center(face.x + eyes[j].x + eyes[j].width/2,
                                        face.y + eyes[j].y + eyes[j].height/2);
                    int radius = cvRound((eyes[j].width + eyes[j].height) * 0.25);
                    cv::circle(result, eye_center, radius, cv::Scalar(255, 0, 0), 2);
                }
            }
            else if (mode == 3) {
                // Blur the face region
                cv::Mat faceRegion = result(face);
                cv::GaussianBlur(faceRegion, faceRegion, cv::Size(15, 15), 0);
            }
        }
        
        // Add mode indicator
        std::string modeText;
        switch (mode) {
            case 1: modeText = "Face Detection"; break;
            case 2: modeText = "Face + Eye Detection"; break;
            case 3: modeText = "Face Blur"; break;
        }
        
        cv::putText(result, modeText, cv::Point(10, 30), 
                   cv::FONT_HERSHEY_SIMPLEX, 0.7, cv::Scalar(255, 255, 255), 2);
        cv::putText(result, "Faces detected: " + std::to_string(faces.size()), 
                   cv::Point(10, 60), cv::FONT_HERSHEY_SIMPLEX, 0.7, cv::Scalar(255, 255, 255), 2);
        cv::putText(result, "Frame: " + std::to_string(frameCount), 
                   cv::Point(10, 90), cv::FONT_HERSHEY_SIMPLEX, 0.7, cv::Scalar(255, 255, 255), 2);
        
        // Display result
        cv::imshow("Face Detection", result);
        
        // Handle keyboard input
        char key = cv::waitKey(1) & 0xFF;
        
        if (key == 'q' || key == 27) {
            break;
        }
        else if (key >= '1' && key <= '3') {
            mode = key - '0';
            std::cout << "Switched to mode " << mode << ": " << modeText << std::endl;
        }
    }
    
    cap.release();
    cv::destroyAllWindows();
    
    std::cout << "Face detection ended. Processed " << frameCount << " frames." << std::endl;
    
    return 0;
}
