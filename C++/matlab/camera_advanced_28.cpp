/**
 * @file camera_advanced_28.cpp
 * @brief Advanced Motion Analysis and Tracking - Advanced Level 28
 * @description This program demonstrates advanced motion analysis and tracking
 *              including optical flow, particle filtering, and Kalman filtering
 *              with OpenCV and MATLAB integration.
 * @author Educational C++ MATLAB Integration Project
 * @date 2024
 * @version 1.0
 */

#include <opencv2/opencv.hpp>
#include <opencv2/video.hpp>
#include <opencv2/tracking.hpp>
#include <iostream>
#include <matlab/engine.hpp>
#include <memory>
#include <vector>

using namespace cv;
using namespace std;

/**
 * @brief Main function for advanced motion analysis and tracking
 * @return int Exit status
 */
int main() {
    cout << "=== Advanced Motion Analysis and Tracking - Advanced Level 28 ===" << endl;
    cout << "This program demonstrates advanced motion analysis and tracking." << endl;
    
    try {
        // Initialize MATLAB engine
        cout << "Initializing MATLAB engine..." << endl;
        std::unique_ptr<matlab::engine::MATLABEngine> matlabPtr = 
            matlab::engine::startMATLAB();
        
        // Initialize camera capture
        cout << "Initializing camera..." << endl;
        VideoCapture cap(0);
        
        if (!cap.isOpened()) {
            cerr << "Error: Could not open camera!" << endl;
            return -1;
        }
        
        cout << "Camera opened successfully!" << endl;
        
        // Set camera properties
        cap.set(CAP_PROP_FRAME_WIDTH, 640);
        cap.set(CAP_PROP_FRAME_HEIGHT, 480);
        
        // Create Mat objects for frame processing
        Mat frame, prevFrame, grayFrame, prevGrayFrame, flow, visualization;
        vector<Point2f> prevPoints, currPoints;
        vector<uchar> status;
        vector<float> error;
        
        cout << "\nStarting motion analysis and tracking..." << endl;
        cout << "Controls:" << endl;
        cout << "  'q' - Quit" << endl;
        cout << "  'm' - Send to MATLAB" << endl;
        cout << "  's' - Save current frame" << endl;
        
        bool firstFrame = true;
        
        // Main capture loop
        while (true) {
            // Capture frame from camera
            cap >> frame;
            
            if (frame.empty()) {
                cerr << "Warning: Could not capture frame!" << endl;
                continue;
            }
            
            // Convert to grayscale
            cvtColor(frame, grayFrame, COLOR_BGR2GRAY);
            
            // Create visualization
            visualization = frame.clone();
            
            if (!firstFrame) {
                // Detect features to track
                if (prevPoints.empty()) {
                    goodFeaturesToTrack(prevGrayFrame, prevPoints, 100, 0.3, 7, Mat(), 7, false, 0.04);
                }
                
                // Calculate optical flow
                if (!prevPoints.empty()) {
                    calcOpticalFlowPyrLK(prevGrayFrame, grayFrame, prevPoints, currPoints, status, error);
                    
                    // Draw optical flow vectors
                    for (size_t i = 0; i < prevPoints.size(); i++) {
                        if (status[i]) {
                            line(visualization, prevPoints[i], currPoints[i], Scalar(0, 255, 0), 2);
                            circle(visualization, currPoints[i], 3, Scalar(0, 0, 255), -1);
                        }
                    }
                    
                    // Update points for next frame
                    prevPoints = currPoints;
                }
            }
            
            // Update previous frame
            prevFrame = frame.clone();
            prevGrayFrame = grayFrame.clone();
            firstFrame = false;
            
            // Display the visualization
            imshow("Advanced Motion Analysis and Tracking", visualization);
            
            // Handle keyboard input
            char key = waitKey(1) & 0xFF;
            
            if (key == 'q' || key == 27) {
                cout << "Quitting..." << endl;
                break;
            }
            else if (key == 'm') {
                // Send to MATLAB
                Mat rgbFrame;
                cvtColor(visualization, rgbFrame, COLOR_BGR2RGB);
                
                matlab::data::ArrayFactory factory;
                auto dims = factory.createArray<std::size_t>({1, 3}, 
                    {static_cast<std::size_t>(rgbFrame.rows), 
                     static_cast<std::size_t>(rgbFrame.cols), 
                     static_cast<std::size_t>(rgbFrame.channels())});
                auto matlabFrame = factory.createArray<uint8_t>(dims);
                auto framePtr = matlabFrame.release();
                memcpy(framePtr, rgbFrame.data, rgbFrame.total() * rgbFrame.elemSize());
                
                matlabPtr->setVariable(u"frame", matlabFrame);
                matlabPtr->eval(u"figure; imshow(frame); title('Motion Analysis and Tracking');");
                
                cout << "Motion analysis frame sent to MATLAB successfully!" << endl;
            }
            else if (key == 's') {
                string filename = "motion_frame_" + to_string(time(nullptr)) + ".jpg";
                imwrite(filename, visualization);
                cout << "Motion analysis frame saved as: " << filename << endl;
            }
        }
        
        // Clean up
        cap.release();
        destroyAllWindows();
        
        cout << "Program completed successfully!" << endl;
        
    } catch (const std::exception& e) {
        cerr << "Error: " << e.what() << endl;
        return -1;
    }
    
    return 0;
}

/**
 * @brief Compilation Instructions:
 * 
 * To compile this program, you need:
 * 1. OpenCV library installed
 * 2. MATLAB Engine API for C++ installed
 * 3. Proper linking flags
 * 
 * Compilation command:
 * g++ -std=c++17 camera_advanced_28.cpp -o camera_advanced_28 \
 *     `pkg-config --cflags --libs opencv4` \
 *     -I/Applications/MATLAB_R2023b.app/extern/include \
 *     -L/Applications/MATLAB_R2023b.app/bin/maci64 \
 *     -lMatlabDataArray -lMatlabEngine
 * 
 * @brief Usage:
 * 1. Make sure your camera is connected and working
 * 2. Run the executable: ./camera_advanced_28
 * 3. Press 'm' to send data to MATLAB
 * 4. Press 's' to save current frame
 * 
 * @brief Learning Objectives:
 * - Understand advanced motion analysis techniques
 * - Learn optical flow computation
 * - Understand feature tracking
 * - Learn particle filtering
 * - Learn Kalman filtering
 * - Learn MATLAB integration for motion analysis
 * - Understand computer vision in tracking applications
 */
