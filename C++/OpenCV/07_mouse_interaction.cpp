// 07_mouse_interaction.cpp
// Beginner Level - Mouse Interaction
// This program demonstrates how to handle mouse events in OpenCV

#include <iostream>
#include <opencv2/opencv.hpp>

// Global variables for mouse interaction
cv::Mat image;
cv::Mat display_image;
std::vector<cv::Point> points;
bool drawing = false;

// Mouse callback function
void mouseCallback(int event, int x, int y, int flags, void* userdata) {
    if (event == cv::EVENT_LBUTTONDOWN) {
        // Start drawing
        drawing = true;
        points.clear();
        points.push_back(cv::Point(x, y));
        
        // Copy original image to display
        image.copyTo(display_image);
        
        std::cout << "Started drawing at: (" << x << ", " << y << ")" << std::endl;
    }
    else if (event == cv::EVENT_MOUSEMOVE && drawing) {
        // Continue drawing line
        if (points.size() > 0) {
            image.copyTo(display_image);
            cv::line(display_image, points.back(), cv::Point(x, y), 
                    cv::Scalar(0, 255, 0), 2);
            cv::imshow("Mouse Interaction", display_image);
        }
    }
    else if (event == cv::EVENT_LBUTTONUP) {
        // Stop drawing
        drawing = false;
        points.push_back(cv::Point(x, y));
        
        // Draw final line
        image.copyTo(display_image);
        if (points.size() >= 2) {
            cv::line(display_image, points[0], points[1], 
                    cv::Scalar(0, 255, 0), 2);
            
            // Add text showing coordinates
            std::string text = "(" + std::to_string(points[0].x) + "," + 
                              std::to_string(points[0].y) + ") to (" +
                              std::to_string(points[1].x) + "," + 
                              std::to_string(points[1].y) + ")";
            cv::putText(display_image, text, cv::Point(10, 30), 
                       cv::FONT_HERSHEY_SIMPLEX, 0.6, cv::Scalar(255, 255, 255), 2);
        }
        cv::imshow("Mouse Interaction", display_image);
        
        std::cout << "Finished drawing at: (" << x << ", " << y << ")" << std::endl;
    }
    else if (event == cv::EVENT_RBUTTONDOWN) {
        // Right click to draw circle
        image.copyTo(display_image);
        cv::circle(display_image, cv::Point(x, y), 20, cv::Scalar(255, 0, 0), 2);
        cv::imshow("Mouse Interaction", display_image);
        
        std::cout << "Drew circle at: (" << x << ", " << y << ")" << std::endl;
    }
}

int main() {
    // Load an image or create a blank canvas
    image = cv::imread("image.jpg");
    
    if (image.empty()) {
        // Create a blank white canvas if no image is available
        image = cv::Mat::zeros(400, 600, CV_8UC3);
        image.setTo(cv::Scalar(255, 255, 255));
        
        // Add some text
        cv::putText(image, "Mouse Interaction Demo", cv::Point(150, 50), 
                   cv::FONT_HERSHEY_SIMPLEX, 1, cv::Scalar(0, 0, 0), 2);
        cv::putText(image, "Left click + drag: Draw line", cv::Point(50, 100), 
                   cv::FONT_HERSHEY_SIMPLEX, 0.6, cv::Scalar(0, 0, 0), 1);
        cv::putText(image, "Right click: Draw circle", cv::Point(50, 130), 
                   cv::FONT_HERSHEY_SIMPLEX, 0.6, cv::Scalar(0, 0, 0), 1);
        cv::putText(image, "Press 'q' to quit", cv::Point(50, 160), 
                   cv::FONT_HERSHEY_SIMPLEX, 0.6, cv::Scalar(0, 0, 0), 1);
    }
    
    // Copy image to display
    image.copyTo(display_image);
    
    // Create window and set mouse callback
    cv::namedWindow("Mouse Interaction", cv::WINDOW_AUTOSIZE);
    cv::setMouseCallback("Mouse Interaction", mouseCallback, nullptr);
    
    // Display the image
    cv::imshow("Mouse Interaction", display_image);
    
    std::cout << "Mouse Interaction Demo:" << std::endl;
    std::cout << "- Left click and drag to draw a line" << std::endl;
    std::cout << "- Right click to draw a circle" << std::endl;
    std::cout << "- Press 'q' to quit" << std::endl;
    
    // Wait for key press
    while (true) {
        char key = cv::waitKey(1) & 0xFF;
        if (key == 'q' || key == 27) {  // 'q' or ESC
            break;
        }
    }
    
    cv::destroyAllWindows();
    return 0;
}
