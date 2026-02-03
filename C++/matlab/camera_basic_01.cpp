/**
 * @file camera_basic_01.cpp
 * @brief Basic Camera Capture - Beginner Level 1
 * @description This program demonstrates the most basic camera capture functionality
 *              using OpenCV and MATLAB integration. It captures a single frame
 *              from the default camera and displays it.
 * @author Educational C++ MATLAB Integration Project
 * @date 2024
 * @version 1.0
 */

#include <opencv2/opencv.hpp>
#include <iostream>
#include <matlab/engine.hpp>
#include <memory>

using namespace cv;
using namespace std;

/**
 * @brief Main function for basic camera capture
 * @return int Exit status
 */
int main() {
    cout << "=== Basic Camera Capture - Beginner Level 1 ===" << endl;
    cout << "This program demonstrates basic camera capture functionality." << endl;
    
    try {
        // Initialize MATLAB engine
        cout << "Initializing MATLAB engine..." << endl;
        std::unique_ptr<matlab::engine::MATLABEngine> matlabPtr = 
            matlab::engine::startMATLAB();
        
        // Initialize camera capture
        cout << "Initializing camera..." << endl;
        VideoCapture cap(0); // 0 = default camera
        
        // Check if camera opened successfully
        if (!cap.isOpened()) {
            cerr << "Error: Could not open camera!" << endl;
            return -1;
        }
        
        cout << "Camera opened successfully!" << endl;
        
        // Set camera properties (optional)
        cap.set(CAP_PROP_FRAME_WIDTH, 640);   // Set width
        cap.set(CAP_PROP_FRAME_HEIGHT, 480);  // Set height
        cap.set(CAP_PROP_FPS, 30);            // Set frame rate
        
        // Create a Mat object to store the frame
        Mat frame;
        
        cout << "Capturing a single frame..." << endl;
        
        // Capture a single frame
        cap >> frame;
        
        // Check if frame was captured successfully
        if (frame.empty()) {
            cerr << "Error: Could not capture frame!" << endl;
            return -1;
        }
        
        cout << "Frame captured successfully!" << endl;
        cout << "Frame dimensions: " << frame.cols << " x " << frame.rows << endl;
        cout << "Frame channels: " << frame.channels() << endl;
        
        // Display the frame using OpenCV
        cout << "Displaying frame in OpenCV window..." << endl;
        imshow("Basic Camera Capture", frame);
        
        // Wait for a key press
        cout << "Press any key to continue..." << endl;
        waitKey(0);
        
        // Send frame data to MATLAB for analysis
        cout << "Sending frame data to MATLAB..." << endl;
        
        // Convert BGR to RGB for MATLAB (OpenCV uses BGR by default)
        Mat rgbFrame;
        cvtColor(frame, rgbFrame, COLOR_BGR2RGB);
        
        // Create MATLAB array from OpenCV Mat
        matlab::data::ArrayFactory factory;
        auto dims = factory.createArray<std::size_t>({1, 3}, 
            {static_cast<std::size_t>(rgbFrame.rows), 
             static_cast<std::size_t>(rgbFrame.cols), 
             static_cast<std::size_t>(rgbFrame.channels())});
        
        // Create MATLAB array with frame data
        auto matlabFrame = factory.createArray<uint8_t>(dims);
        auto framePtr = matlabFrame.release();
        
        // Copy data from OpenCV Mat to MATLAB array
        memcpy(framePtr, rgbFrame.data, rgbFrame.total() * rgbFrame.elemSize());
        
        // Set variable in MATLAB workspace
        matlabPtr->setVariable(u"capturedFrame", matlabFrame);
        
        // Execute MATLAB commands
        matlabPtr->eval(u"figure; imshow(capturedFrame); title('Frame Captured in MATLAB');");
        matlabPtr->eval(u"fprintf('Frame size: %d x %d x %d\\n', size(capturedFrame,1), size(capturedFrame,2), size(capturedFrame,3));");
        
        cout << "Frame data sent to MATLAB successfully!" << endl;
        cout << "MATLAB figure window should now be open." << endl;
        
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
 * g++ -std=c++17 camera_basic_01.cpp -o camera_basic_01 \
 *     `pkg-config --cflags --libs opencv4` \
 *     -I/Applications/MATLAB_R2023b.app/extern/include \
 *     -L/Applications/MATLAB_R2023b.app/bin/maci64 \
 *     -lMatlabDataArray -lMatlabEngine
 * 
 * @brief Usage:
 * 1. Make sure your camera is connected and working
 * 2. Run the executable: ./camera_basic_01
 * 3. A window will open showing the captured frame
 * 4. Press any key to continue
 * 5. MATLAB will open a figure window with the same frame
 * 
 * @brief Learning Objectives:
 * - Understand basic camera initialization
 * - Learn to capture a single frame
 * - Understand OpenCV Mat structure
 * - Learn basic MATLAB integration
 * - Understand BGR to RGB conversion
 * - Learn to transfer data between OpenCV and MATLAB
 */
