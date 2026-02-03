/**
 * @file camera_advanced_27.cpp
 * @brief Advanced Augmented Reality - Advanced Level 27
 * @description This program demonstrates advanced augmented reality techniques
 *              including marker detection, pose estimation, and 3D rendering
 *              with OpenCV and MATLAB integration.
 * @author Educational C++ MATLAB Integration Project
 * @date 2024
 * @version 1.0
 */

#include <opencv2/opencv.hpp>
#include <opencv2/calib3d.hpp>
#include <opencv2/aruco.hpp>
#include <iostream>
#include <matlab/engine.hpp>
#include <memory>
#include <vector>

using namespace cv;
using namespace std;

/**
 * @brief Main function for advanced augmented reality
 * @return int Exit status
 */
int main() {
    cout << "=== Advanced Augmented Reality - Advanced Level 27 ===" << endl;
    cout << "This program demonstrates advanced augmented reality techniques." << endl;
    
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
        
        // Create ArUco dictionary
        Ptr<aruco::Dictionary> dictionary = aruco::getPredefinedDictionary(aruco::DICT_6X6_250);
        Ptr<aruco::DetectorParameters> detectorParams = aruco::DetectorParameters::create();
        
        // Create Mat objects for frame processing
        Mat frame, processedFrame, visualization;
        vector<int> markerIds;
        vector<vector<Point2f>> markerCorners;
        
        cout << "\nStarting augmented reality..." << endl;
        cout << "Controls:" << endl;
        cout << "  'q' - Quit" << endl;
        cout << "  'm' - Send to MATLAB" << endl;
        cout << "  's' - Save current frame" << endl;
        
        // Main capture loop
        while (true) {
            // Capture frame from camera
            cap >> frame;
            
            if (frame.empty()) {
                cerr << "Warning: Could not capture frame!" << endl;
                continue;
            }
            
            // Detect ArUco markers
            aruco::detectMarkers(frame, dictionary, markerCorners, markerIds, detectorParams);
            
            // Create visualization
            visualization = frame.clone();
            
            // Draw detected markers
            if (markerIds.size() > 0) {
                aruco::drawDetectedMarkers(visualization, markerCorners, markerIds);
                
                // Draw 3D axis for each marker
                for (size_t i = 0; i < markerIds.size(); i++) {
                    // Estimate pose
                    vector<Point3f> objectPoints;
                    objectPoints.push_back(Point3f(-0.5, -0.5, 0));
                    objectPoints.push_back(Point3f(0.5, -0.5, 0));
                    objectPoints.push_back(Point3f(0.5, 0.5, 0));
                    objectPoints.push_back(Point3f(-0.5, 0.5, 0));
                    
                    Mat cameraMatrix = Mat::eye(3, 3, CV_64F);
                    Mat distCoeffs = Mat::zeros(4, 1, CV_64F);
                    
                    Mat rvec, tvec;
                    solvePnP(objectPoints, markerCorners[i], cameraMatrix, distCoeffs, rvec, tvec);
                    
                    // Draw 3D axis
                    vector<Point3f> axisPoints;
                    axisPoints.push_back(Point3f(0, 0, 0));
                    axisPoints.push_back(Point3f(0.3, 0, 0));
                    axisPoints.push_back(Point3f(0, 0.3, 0));
                    axisPoints.push_back(Point3f(0, 0, 0.3));
                    
                    vector<Point2f> imagePoints;
                    projectPoints(axisPoints, rvec, tvec, cameraMatrix, distCoeffs, imagePoints);
                    
                    // Draw axis
                    line(visualization, imagePoints[0], imagePoints[1], Scalar(0, 0, 255), 3); // X axis - Red
                    line(visualization, imagePoints[0], imagePoints[2], Scalar(0, 255, 0), 3); // Y axis - Green
                    line(visualization, imagePoints[0], imagePoints[3], Scalar(255, 0, 0), 3); // Z axis - Blue
                }
            }
            
            // Display the visualization
            imshow("Advanced Augmented Reality", visualization);
            
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
                matlabPtr->eval(u"figure; imshow(frame); title('Augmented Reality');");
                
                cout << "AR frame sent to MATLAB successfully!" << endl;
            }
            else if (key == 's') {
                string filename = "ar_frame_" + to_string(time(nullptr)) + ".jpg";
                imwrite(filename, visualization);
                cout << "AR frame saved as: " << filename << endl;
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
 * g++ -std=c++17 camera_advanced_27.cpp -o camera_advanced_27 \
 *     `pkg-config --cflags --libs opencv4` \
 *     -I/Applications/MATLAB_R2023b.app/extern/include \
 *     -L/Applications/MATLAB_R2023b.app/bin/maci64 \
 *     -lMatlabDataArray -lMatlabEngine
 * 
 * @brief Usage:
 * 1. Make sure your camera is connected and working
 * 2. Run the executable: ./camera_advanced_27
 * 3. Press 'm' to send data to MATLAB
 * 4. Press 's' to save current frame
 * 
 * @brief Learning Objectives:
 * - Understand advanced augmented reality techniques
 * - Learn marker detection and tracking
 * - Understand pose estimation
 * - Learn 3D rendering techniques
 * - Learn MATLAB integration for AR analysis
 * - Understand computer vision in AR applications
 */
