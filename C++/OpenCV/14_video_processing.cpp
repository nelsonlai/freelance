// 14_video_processing.cpp
// Intermediate Level - Video Processing
// This program demonstrates real-time video processing with various effects

#include <iostream>
#include <opencv2/opencv.hpp>

int main() {
    cv::VideoCapture cap;
    bool cameraOpened = false;
    
    // Try to open different camera indices
    std::cout << "Attempting to open camera..." << std::endl;
    for (int i = 0; i < 5; i++) {
        std::cout << "Trying camera index " << i << "... ";
        cap.open(i);
        if (cap.isOpened()) {
            std::cout << "Success!" << std::endl;
            cameraOpened = true;
            break;
        }
        std::cout << "Failed" << std::endl;
    }
    
    // If no camera is available, try to open a video file
    if (!cameraOpened) {
        std::cout << "No camera found. Trying to open 'image.jpg' as a static image..." << std::endl;
        cv::Mat testImage = cv::imread("image.jpg");
        if (!testImage.empty()) {
            std::cout << "Found image.jpg - will create a static demo instead of live video" << std::endl;
            // We'll handle this case differently below
        } else {
            std::cout << "Error: Could not open any camera or find image.jpg" << std::endl;
            std::cout << "Please ensure:" << std::endl;
            std::cout << "1. Camera is connected and not used by other applications" << std::endl;
            std::cout << "2. Camera permissions are granted" << std::endl;
            std::cout << "3. Or place an 'image.jpg' file in the current directory" << std::endl;
            return -1;
        }
    }
    
    std::cout << "Video Processing Demo" << std::endl;
    std::cout << "Controls:" << std::endl;
    std::cout << "  '1' - Original" << std::endl;
    std::cout << "  '2' - Grayscale" << std::endl;
    std::cout << "  '3' - Edge Detection" << std::endl;
    std::cout << "  '4' - Blur" << std::endl;
    std::cout << "  '5' - Sharpening" << std::endl;
    std::cout << "  '6' - Cartoon Effect" << std::endl;
    std::cout << "  '7' - Sepia Effect" << std::endl;
    std::cout << "  '8' - Negative" << std::endl;
    std::cout << "  'q' - Quit" << std::endl;
    
    cv::Mat frame, processed_frame;
    int mode = 1;  // Start with original
    int frameCount = 0;
    bool usingStaticImage = !cameraOpened;
    
    // If using static image, load it once
    if (usingStaticImage) {
        frame = cv::imread("image.jpg");
        if (frame.empty()) {
            std::cout << "Error: Could not load image.jpg" << std::endl;
            return -1;
        }
        std::cout << "Using static image mode. Press 'n' for next effect, 'q' to quit." << std::endl;
    }
    
    while (true) {
        // Capture frame from camera (if using camera)
        if (!usingStaticImage) {
            cap >> frame;
            
            if (frame.empty()) {
                std::cout << "Error: Could not capture frame" << std::endl;
                break;
            }
        }
        
        frameCount++;
        
        // Apply different effects based on mode
        switch (mode) {
            case 1: // Original
                processed_frame = frame.clone();
                break;
                
            case 2: // Grayscale
                cv::cvtColor(frame, processed_frame, cv::COLOR_BGR2GRAY);
                cv::cvtColor(processed_frame, processed_frame, cv::COLOR_GRAY2BGR);
                break;
                
            case 3: // Edge Detection
                {
                    cv::Mat gray, edges;
                    cv::cvtColor(frame, gray, cv::COLOR_BGR2GRAY);
                    cv::Canny(gray, edges, 50, 150);
                    cv::cvtColor(edges, processed_frame, cv::COLOR_GRAY2BGR);
                }
                break;
                
            case 4: // Blur
                cv::GaussianBlur(frame, processed_frame, cv::Size(15, 15), 0);
                break;
                
            case 5: // Sharpening
                {
                    cv::Mat kernel = (cv::Mat_<float>(3,3) << 
                        0, -1, 0,
                        -1, 5, -1,
                        0, -1, 0);
                    cv::filter2D(frame, processed_frame, -1, kernel);
                }
                break;
                
            case 6: // Cartoon Effect
                {
                    cv::Mat gray, edges, cartoon;
                    cv::cvtColor(frame, gray, cv::COLOR_BGR2GRAY);
                    cv::medianBlur(gray, gray, 5);
                    cv::adaptiveThreshold(gray, edges, 255, cv::ADAPTIVE_THRESH_MEAN_C, cv::THRESH_BINARY, 9, 9);
                    cv::cvtColor(edges, edges, cv::COLOR_GRAY2BGR);
                    cv::bilateralFilter(frame, cartoon, 9, 75, 75);
                    cv::bitwise_and(cartoon, edges, processed_frame);
                }
                break;
                
            case 7: // Sepia Effect
                {
                    cv::Mat sepiaKernel = (cv::Mat_<float>(3,3) << 
                        0.393, 0.769, 0.189,
                        0.349, 0.686, 0.168,
                        0.272, 0.534, 0.131);
                    cv::transform(frame, processed_frame, sepiaKernel);
                }
                break;
                
            case 8: // Negative
                processed_frame = cv::Scalar(255, 255, 255) - frame;
                break;
        }
        
        // Add frame counter and mode indicator
        std::string modeText;
        switch (mode) {
            case 1: modeText = "Original"; break;
            case 2: modeText = "Grayscale"; break;
            case 3: modeText = "Edge Detection"; break;
            case 4: modeText = "Blur"; break;
            case 5: modeText = "Sharpening"; break;
            case 6: modeText = "Cartoon Effect"; break;
            case 7: modeText = "Sepia Effect"; break;
            case 8: modeText = "Negative"; break;
        }
        
        cv::putText(processed_frame, "Frame: " + std::to_string(frameCount), 
                   cv::Point(10, 30), cv::FONT_HERSHEY_SIMPLEX, 0.7, cv::Scalar(0, 255, 0), 2);
        cv::putText(processed_frame, "Mode: " + modeText, 
                   cv::Point(10, 60), cv::FONT_HERSHEY_SIMPLEX, 0.7, cv::Scalar(0, 255, 0), 2);
        
        if (usingStaticImage) {
            cv::putText(processed_frame, "Static Image Mode - Press 'n' for next, 'q' to quit", 
                       cv::Point(10, processed_frame.rows - 20), cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(255, 255, 255), 1);
        } else {
            cv::putText(processed_frame, "Press 1-8 for effects, 'q' to quit", 
                       cv::Point(10, processed_frame.rows - 20), cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(255, 255, 255), 1);
        }
        
        // Display the frame
        cv::imshow("Video Processing", processed_frame);
        
        // Handle keyboard input
        int waitTime = usingStaticImage ? 0 : 1;  // Wait indefinitely for static image, 1ms for camera
        char key = cv::waitKey(waitTime) & 0xFF;
        
        if (key == 'q' || key == 27) {  // 'q' or ESC
            break;
        }
        else if (usingStaticImage && key == 'n') {
            // In static image mode, 'n' cycles through effects
            mode = (mode % 8) + 1;
            std::cout << "Switched to mode " << mode << ": " << modeText << std::endl;
        }
        else if (!usingStaticImage && key >= '1' && key <= '8') {
            // In camera mode, number keys switch effects
            mode = key - '0';
            std::cout << "Switched to mode " << mode << ": " << modeText << std::endl;
        }
    }
    
    // Release camera and close windows
    cap.release();
    cv::destroyAllWindows();
    
    std::cout << "Video processing ended. Processed " << frameCount << " frames." << std::endl;
    
    return 0;
}
