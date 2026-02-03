#include <opencv2/opencv.hpp>
#include <iostream>

int main() {
    // Load Haar Cascade for face detection
    cv::CascadeClassifier face_cascade;
    if (!face_cascade.load("/usr/share/opencv4/haarcascades/haarcascade_frontalface_default.xml")) {
        std::cout << "Error: Could not load Haar cascade XML file.\n";
        return -1;
    }

    // Open webcam
    cv::VideoCapture cap(0);
    if (!cap.isOpened()) {
        std::cout << "Error: Could not open webcam.\n";
        return -1;
    }

    cv::Mat frame, grayFrame;
    std::vector<cv::Rect> faces;

    while (true) {
        cap >> frame;
        if (frame.empty()) {
            std::cout << "Error: Blank frame grabbed.\n";
            break;
        }

        // Convert to grayscale
        cv::cvtColor(frame, grayFrame, cv::COLOR_BGR2GRAY);

        // Improve detection with histogram equalization
        cv::equalizeHist(grayFrame, grayFrame);

        // Detect faces
        face_cascade.detectMultiScale(grayFrame, faces, 1.1, 4, 0, cv::Size(30, 30));

        // Draw rectangles around detected faces
        for (size_t i = 0; i < faces.size(); i++) {
            cv::rectangle(frame, faces[i], cv::Scalar(0, 255, 0), 2);
        }

        // Show result
        cv::imshow("Webcam - Face Detection", frame);

        // Exit on 'q'
        if (cv::waitKey(30) == 'q') {
            break;
        }
    }

    cap.release();
    cv::destroyAllWindows();
    return 0;
}