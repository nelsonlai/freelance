/**
 * @file camera_basic_02.cpp
 * @brief Continuous Camera Capture - Beginner Level 2
 * @description This program demonstrates continuous camera capture with real-time
 *              display using OpenCV and MATLAB integration. It captures frames
 *              continuously until the user presses 'q' to quit.
 * @author Educational C++ MATLAB Integration Project
 * @date 2024
 * @version 1.0
 */

#include <opencv2/opencv.hpp>
#include <iostream>
#include <matlab/engine.hpp>
#include <memory>
#include <chrono>
#include <thread>

using namespace cv;
using namespace std;

/**
 * @brief Main function for continuous camera capture
 * @return int Exit status
 */
int main() {
    cout << "=== Continuous Camera Capture - Beginner Level 2 ===" << endl;
    cout << "This program demonstrates continuous camera capture with real-time display." << endl;
    cout << "Press 'q' to quit, 's' to save current frame, 'm' to send to MATLAB." << endl;
    
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
        
        // Set camera properties for better performance
        cap.set(CAP_PROP_FRAME_WIDTH, 640);   // Set width
        cap.set(CAP_PROP_FRAME_HEIGHT, 480);  // Set height
        cap.set(CAP_PROP_FPS, 30);            // Set frame rate
        cap.set(CAP_PROP_BUFFERSIZE, 1);      // Reduce buffer size for lower latency
        
        // Create Mat objects for frame processing
        Mat frame, displayFrame;
        
        // Variables for frame counting and timing
        int frameCount = 0;
        auto startTime = chrono::high_resolution_clock::now();
        
        cout << "Starting continuous capture..." << endl;
        cout << "Controls:" << endl;
        cout << "  'q' - Quit" << endl;
        cout << "  's' - Save current frame" << endl;
        cout << "  'm' - Send current frame to MATLAB" << endl;
        cout << "  'r' - Reset frame counter" << endl;
        
        // Main capture loop
        while (true) {
            // Capture frame from camera
            cap >> frame;
            
            // Check if frame was captured successfully
            if (frame.empty()) {
                cerr << "Warning: Could not capture frame!" << endl;
                continue;
            }
            
            frameCount++;
            
            // Create a copy for display (we'll add text overlay)
            frame.copyTo(displayFrame);
            
            // Add frame information overlay
            string frameInfo = "Frame: " + to_string(frameCount);
            string timeInfo = "Time: " + to_string(
                chrono::duration_cast<chrono::seconds>(
                    chrono::high_resolution_clock::now() - startTime
                ).count()) + "s";
            
            // Draw text on frame
            putText(displayFrame, frameInfo, Point(10, 30), 
                   FONT_HERSHEY_SIMPLEX, 0.7, Scalar(0, 255, 0), 2);
            putText(displayFrame, timeInfo, Point(10, 60), 
                   FONT_HERSHEY_SIMPLEX, 0.7, Scalar(0, 255, 0), 2);
            putText(displayFrame, "Press 'q' to quit, 's' to save, 'm' for MATLAB", 
                   Point(10, displayFrame.rows - 20), 
                   FONT_HERSHEY_SIMPLEX, 0.5, Scalar(255, 255, 255), 1);
            
            // Display the frame
            imshow("Continuous Camera Capture", displayFrame);
            
            // Handle keyboard input
            char key = waitKey(1) & 0xFF;
            
            if (key == 'q' || key == 27) { // 'q' or ESC to quit
                cout << "Quitting..." << endl;
                break;
            }
            else if (key == 's') { // 's' to save current frame
                string filename = "captured_frame_" + to_string(frameCount) + ".jpg";
                imwrite(filename, frame);
                cout << "Frame saved as: " << filename << endl;
            }
            else if (key == 'm') { // 'm' to send to MATLAB
                cout << "Sending frame to MATLAB..." << endl;
                
                try {
                    // Convert BGR to RGB for MATLAB
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
                    matlabPtr->setVariable(u"currentFrame", matlabFrame);
                    
                    // Execute MATLAB commands
                    matlabPtr->eval(u"figure; imshow(currentFrame); title(['Frame ' num2str(" + to_string(frameCount) + u") ' sent to MATLAB']);");
                    
                    cout << "Frame " << frameCount << " sent to MATLAB successfully!" << endl;
                    
                } catch (const std::exception& e) {
                    cerr << "Error sending to MATLAB: " << e.what() << endl;
                }
            }
            else if (key == 'r') { // 'r' to reset counter
                frameCount = 0;
                startTime = chrono::high_resolution_clock::now();
                cout << "Frame counter reset!" << endl;
            }
            
            // Calculate and display FPS every 30 frames
            if (frameCount % 30 == 0) {
                auto currentTime = chrono::high_resolution_clock::now();
                auto duration = chrono::duration_cast<chrono::milliseconds>(currentTime - startTime);
                double fps = (frameCount * 1000.0) / duration.count();
                cout << "Current FPS: " << fps << endl;
            }
        }
        
        // Clean up
        cap.release();
        destroyAllWindows();
        
        // Final statistics
        auto endTime = chrono::high_resolution_clock::now();
        auto totalDuration = chrono::duration_cast<chrono::seconds>(endTime - startTime);
        double avgFPS = frameCount / (totalDuration.count() + 0.001);
        
        cout << "\n=== Capture Statistics ===" << endl;
        cout << "Total frames captured: " << frameCount << endl;
        cout << "Total time: " << totalDuration.count() << " seconds" << endl;
        cout << "Average FPS: " << avgFPS << endl;
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
 * g++ -std=c++17 camera_basic_02.cpp -o camera_basic_02 \
 *     `pkg-config --cflags --libs opencv4` \
 *     -I/Applications/MATLAB_R2023b.app/extern/include \
 *     -L/Applications/MATLAB_R2023b.app/bin/maci64 \
 *     -lMatlabDataArray -lMatlabEngine
 * 
 * @brief Usage:
 * 1. Make sure your camera is connected and working
 * 2. Run the executable: ./camera_basic_02
 * 3. A window will open showing continuous camera feed
 * 4. Use keyboard controls:
 *    - 'q' or ESC: Quit
 *    - 's': Save current frame
 *    - 'm': Send current frame to MATLAB
 *    - 'r': Reset frame counter
 * 
 * @brief Learning Objectives:
 * - Understand continuous camera capture
 * - Learn real-time frame processing
 * - Understand keyboard input handling
 * - Learn frame counting and timing
 * - Understand FPS calculation
 * - Learn interactive MATLAB integration
 * - Understand text overlay on frames
 * - Learn frame saving functionality
 */
