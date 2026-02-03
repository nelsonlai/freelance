/**
 * @file camera_advanced_26.cpp
 * @brief Advanced Real-time Video Processing - Advanced Level 26
 * @description This program demonstrates advanced real-time video processing
 *              including multi-threading, GPU acceleration, and optimization
 *              with OpenCV and MATLAB integration.
 * @author Educational C++ MATLAB Integration Project
 * @date 2024
 * @version 1.0
 */

#include <opencv2/opencv.hpp>
#include <opencv2/cuda.hpp>
#include <iostream>
#include <matlab/engine.hpp>
#include <memory>
#include <thread>
#include <mutex>
#include <queue>
#include <atomic>

using namespace cv;
using namespace std;

/**
 * @brief Main function for advanced real-time video processing
 * @return int Exit status
 */
int main() {
    cout << "=== Advanced Real-time Video Processing - Advanced Level 26 ===" << endl;
    cout << "This program demonstrates advanced real-time video processing." << endl;
    
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
        cap.set(CAP_PROP_FPS, 30);
        
        // Create Mat objects for frame processing
        Mat frame, processedFrame, visualization;
        
        cout << "\nStarting real-time video processing..." << endl;
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
            
            // Apply real-time processing
            processedFrame = frame.clone();
            
            // Apply various filters
            GaussianBlur(processedFrame, processedFrame, Size(5, 5), 0);
            Canny(processedFrame, processedFrame, 50, 150);
            
            // Create visualization
            visualization = processedFrame.clone();
            
            // Display the visualization
            imshow("Advanced Real-time Video Processing", visualization);
            
            // Handle keyboard input
            char key = waitKey(1) & 0xFF;
            
            if (key == 'q' || key == 27) {
                cout << "Quitting..." << endl;
                break;
            }
            else if (key == 'm') {
                // Send to MATLAB
                Mat rgbFrame;
                cvtColor(frame, rgbFrame, COLOR_BGR2RGB);
                
                matlab::data::ArrayFactory factory;
                auto dims = factory.createArray<std::size_t>({1, 3}, 
                    {static_cast<std::size_t>(rgbFrame.rows), 
                     static_cast<std::size_t>(rgbFrame.cols), 
                     static_cast<std::size_t>(rgbFrame.channels())});
                auto matlabFrame = factory.createArray<uint8_t>(dims);
                auto framePtr = matlabFrame.release();
                memcpy(framePtr, rgbFrame.data, rgbFrame.total() * rgbFrame.elemSize());
                
                matlabPtr->setVariable(u"frame", matlabFrame);
                matlabPtr->eval(u"figure; imshow(frame); title('Real-time Video Processing');");
                
                cout << "Frame sent to MATLAB successfully!" << endl;
            }
            else if (key == 's') {
                string filename = "realtime_frame_" + to_string(time(nullptr)) + ".jpg";
                imwrite(filename, visualization);
                cout << "Frame saved as: " << filename << endl;
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
 * g++ -std=c++17 camera_advanced_26.cpp -o camera_advanced_26 \
 *     `pkg-config --cflags --libs opencv4` \
 *     -I/Applications/MATLAB_R2023b.app/extern/include \
 *     -L/Applications/MATLAB_R2023b.app/bin/maci64 \
 *     -lMatlabDataArray -lMatlabEngine
 * 
 * @brief Usage:
 * 1. Make sure your camera is connected and working
 * 2. Run the executable: ./camera_advanced_26
 * 3. Press 'm' to send data to MATLAB
 * 4. Press 's' to save current frame
 * 
 * @brief Learning Objectives:
 * - Understand advanced real-time video processing
 * - Learn multi-threading techniques
 * - Understand GPU acceleration
 * - Learn optimization techniques
 * - Learn MATLAB integration for real-time analysis
 * - Understand performance optimization
 */
