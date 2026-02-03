// 04_basic_drawing.cpp
// Beginner Level - Basic Drawing Functions
// This program demonstrates how to draw shapes and text on images

#include <iostream>
#include <opencv2/opencv.hpp>

int main() {
    // Create a white canvas (600x600, 3 channels, white color)
    cv::Mat canvas = cv::Mat::zeros(600, 600, CV_8UC3);
    canvas.setTo(cv::Scalar(255, 255, 255));  // Set to white
    
    // Draw a circle (center, radius, color, thickness)
    cv::circle(canvas, cv::Point(150, 150), 50, cv::Scalar(0, 0, 255), 3);
    cv::putText(canvas, "Circle", cv::Point(100, 220), 
               cv::FONT_HERSHEY_SIMPLEX, 0.7, cv::Scalar(0, 0, 255), 2);
    
    // Draw a filled rectangle
    cv::rectangle(canvas, cv::Point(250, 100), cv::Point(350, 200), 
                 cv::Scalar(0, 255, 0), -1);  // -1 means filled
    cv::putText(canvas, "Rectangle", cv::Point(250, 220), 
               cv::FONT_HERSHEY_SIMPLEX, 0.7, cv::Scalar(0, 255, 0), 2);
    
    // Draw a line
    cv::line(canvas, cv::Point(450, 100), cv::Point(550, 200), 
            cv::Scalar(255, 0, 0), 3);
    cv::putText(canvas, "Line", cv::Point(450, 220), 
               cv::FONT_HERSHEY_SIMPLEX, 0.7, cv::Scalar(255, 0, 0), 2);
    
    // Draw an ellipse
    cv::ellipse(canvas, cv::Point(150, 350), cv::Size(60, 30), 0, 0, 360, 
               cv::Scalar(255, 0, 255), 3);
    cv::putText(canvas, "Ellipse", cv::Point(100, 420), 
               cv::FONT_HERSHEY_SIMPLEX, 0.7, cv::Scalar(255, 0, 255), 2);
    
    // Draw a polygon (triangle)
    std::vector<cv::Point> triangle = {
        cv::Point(300, 300),
        cv::Point(250, 400),
        cv::Point(350, 400)
    };
    cv::polylines(canvas, triangle, true, cv::Scalar(0, 255, 255), 3);
    cv::putText(canvas, "Triangle", cv::Point(270, 430), 
               cv::FONT_HERSHEY_SIMPLEX, 0.7, cv::Scalar(0, 255, 255), 2);
    
    // Draw an arrow
    cv::arrowedLine(canvas, cv::Point(450, 350), cv::Point(550, 400), 
                   cv::Scalar(255, 255, 0), 3);
    cv::putText(canvas, "Arrow", cv::Point(450, 430), 
               cv::FONT_HERSHEY_SIMPLEX, 0.7, cv::Scalar(255, 255, 0), 2);
    
    // Add a title
    cv::putText(canvas, "OpenCV Drawing Examples", cv::Point(150, 50), 
               cv::FONT_HERSHEY_SIMPLEX, 1.2, cv::Scalar(0, 0, 0), 3);
    
    // Display the canvas
    cv::imshow("Drawing Examples", canvas);
    
    std::cout << "Drawing examples completed!" << std::endl;
    std::cout << "Press any key to close..." << std::endl;
    cv::waitKey(0);
    cv::destroyAllWindows();
    
    return 0;
}
