/**
 * @file camera_basic_03.cpp
 * @brief Camera Properties Control - Beginner Level 3
 * @description This program demonstrates how to control various camera properties
 *              like brightness, contrast, exposure, and resolution using OpenCV
 *              and MATLAB integration for real-time analysis.
 * @author Educational C++ MATLAB Integration Project
 * @date 2024
 * @version 1.0
 */

#include <opencv2/opencv.hpp>
#include <iostream>
#include <matlab/engine.hpp>
#include <memory>
#include <iomanip>

using namespace cv;
using namespace std;

/**
 * @brief Structure to hold camera property values
 */
struct CameraProperties {
    double brightness;
    double contrast;
    double exposure;
    double saturation;
    double hue;
    double gain;
    double whiteBalance;
    int width;
    int height;
    double fps;
};

/**
 * @brief Function to display current camera properties
 * @param cap VideoCapture object
 * @param props CameraProperties structure
 */
void displayCameraProperties(VideoCapture& cap, const CameraProperties& props) {
    cout << "\n=== Current Camera Properties ===" << endl;
    cout << "Resolution: " << props.width << " x " << props.height << endl;
    cout << "FPS: " << fixed << setprecision(2) << props.fps << endl;
    cout << "Brightness: " << fixed << setprecision(2) << props.brightness << endl;
    cout << "Contrast: " << fixed << setprecision(2) << props.contrast << endl;
    cout << "Exposure: " << fixed << setprecision(2) << props.exposure << endl;
    cout << "Saturation: " << fixed << setprecision(2) << props.saturation << endl;
    cout << "Hue: " << fixed << setprecision(2) << props.hue << endl;
    cout << "Gain: " << fixed << setprecision(2) << props.gain << endl;
    cout << "White Balance: " << fixed << setprecision(2) << props.whiteBalance << endl;
    cout << "=================================" << endl;
}

/**
 * @brief Function to update camera properties from current settings
 * @param cap VideoCapture object
 * @param props CameraProperties structure reference
 */
void updateCameraProperties(VideoCapture& cap, CameraProperties& props) {
    props.width = cap.get(CAP_PROP_FRAME_WIDTH);
    props.height = cap.get(CAP_PROP_FRAME_HEIGHT);
    props.fps = cap.get(CAP_PROP_FPS);
    props.brightness = cap.get(CAP_PROP_BRIGHTNESS);
    props.contrast = cap.get(CAP_PROP_CONTRAST);
    props.exposure = cap.get(CAP_PROP_EXPOSURE);
    props.saturation = cap.get(CAP_PROP_SATURATION);
    props.hue = cap.get(CAP_PROP_HUE);
    props.gain = cap.get(CAP_PROP_GAIN);
    props.whiteBalance = cap.get(CAP_PROP_WHITE_BALANCE_BLUE_U);
}

/**
 * @brief Function to send camera properties to MATLAB
 * @param matlabPtr MATLAB engine pointer
 * @param props CameraProperties structure
 */
void sendPropertiesToMATLAB(std::unique_ptr<matlab::engine::MATLABEngine>& matlabPtr, 
                           const CameraProperties& props) {
    try {
        matlab::data::ArrayFactory factory;
        
        // Create arrays for each property
        auto brightnessArray = factory.createScalar(props.brightness);
        auto contrastArray = factory.createScalar(props.contrast);
        auto exposureArray = factory.createScalar(props.exposure);
        auto saturationArray = factory.createScalar(props.saturation);
        auto hueArray = factory.createScalar(props.hue);
        auto gainArray = factory.createScalar(props.gain);
        auto whiteBalanceArray = factory.createScalar(props.whiteBalance);
        auto widthArray = factory.createScalar(static_cast<double>(props.width));
        auto heightArray = factory.createScalar(static_cast<double>(props.height));
        auto fpsArray = factory.createScalar(props.fps);
        
        // Set variables in MATLAB workspace
        matlabPtr->setVariable(u"brightness", brightnessArray);
        matlabPtr->setVariable(u"contrast", contrastArray);
        matlabPtr->setVariable(u"exposure", exposureArray);
        matlabPtr->setVariable(u"saturation", saturationArray);
        matlabPtr->setVariable(u"hue", hueArray);
        matlabPtr->setVariable(u"gain", gainArray);
        matlabPtr->setVariable(u"whiteBalance", whiteBalanceArray);
        matlabPtr->setVariable(u"width", widthArray);
        matlabPtr->setVariable(u"height", heightArray);
        matlabPtr->setVariable(u"fps", fpsArray);
        
        // Create a structure in MATLAB
        matlabPtr->eval(u"cameraProps = struct('brightness', brightness, 'contrast', contrast, "
                       u"'exposure', exposure, 'saturation', saturation, 'hue', hue, "
                       u"'gain', gain, 'whiteBalance', whiteBalance, 'width', width, "
                       u"'height', height, 'fps', fps);");
        
        // Display properties in MATLAB
        matlabPtr->eval(u"fprintf('Camera Properties in MATLAB:\\n');");
        matlabPtr->eval(u"fprintf('Resolution: %.0f x %.0f\\n', width, height);");
        matlabPtr->eval(u"fprintf('FPS: %.2f\\n', fps);");
        matlabPtr->eval(u"fprintf('Brightness: %.2f\\n', brightness);");
        matlabPtr->eval(u"fprintf('Contrast: %.2f\\n', contrast);");
        matlabPtr->eval(u"fprintf('Exposure: %.2f\\n', exposure);");
        matlabPtr->eval(u"fprintf('Saturation: %.2f\\n', saturation);");
        matlabPtr->eval(u"fprintf('Hue: %.2f\\n', hue);");
        matlabPtr->eval(u"fprintf('Gain: %.2f\\n', gain);");
        matlabPtr->eval(u"fprintf('White Balance: %.2f\\n', whiteBalance);");
        
        cout << "Camera properties sent to MATLAB successfully!" << endl;
        
    } catch (const std::exception& e) {
        cerr << "Error sending properties to MATLAB: " << e.what() << endl;
    }
}

/**
 * @brief Main function for camera properties control
 * @return int Exit status
 */
int main() {
    cout << "=== Camera Properties Control - Beginner Level 3 ===" << endl;
    cout << "This program demonstrates camera property control and MATLAB integration." << endl;
    
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
        
        // Initialize camera properties structure
        CameraProperties props;
        updateCameraProperties(cap, props);
        
        // Display initial properties
        displayCameraProperties(cap, props);
        
        // Send initial properties to MATLAB
        sendPropertiesToMATLAB(matlabPtr, props);
        
        // Create Mat objects for frame processing
        Mat frame, displayFrame;
        
        cout << "\nStarting camera feed..." << endl;
        cout << "Controls:" << endl;
        cout << "  'q' - Quit" << endl;
        cout << "  'b' - Increase brightness" << endl;
        cout << "  'B' - Decrease brightness" << endl;
        cout << "  'c' - Increase contrast" << endl;
        cout << "  'C' - Decrease contrast" << endl;
        cout << "  'e' - Increase exposure" << endl;
        cout << "  'E' - Decrease exposure" << endl;
        cout << "  's' - Increase saturation" << endl;
        cout << "  'S' - Decrease saturation" << endl;
        cout << "  'h' - Increase hue" << endl;
        cout << "  'H' - Decrease hue" << endl;
        cout << "  'g' - Increase gain" << endl;
        cout << "  'G' - Decrease gain" << endl;
        cout << "  'w' - Toggle white balance" << endl;
        cout << "  'r' - Reset to default" << endl;
        cout << "  'p' - Print current properties" << endl;
        cout << "  'm' - Send properties to MATLAB" << endl;
        
        // Main capture loop
        while (true) {
            // Capture frame from camera
            cap >> frame;
            
            // Check if frame was captured successfully
            if (frame.empty()) {
                cerr << "Warning: Could not capture frame!" << endl;
                continue;
            }
            
            // Create a copy for display
            frame.copyTo(displayFrame);
            
            // Add property information overlay
            stringstream ss;
            ss << "Brightness: " << fixed << setprecision(1) << props.brightness;
            putText(displayFrame, ss.str(), Point(10, 30), 
                   FONT_HERSHEY_SIMPLEX, 0.6, Scalar(0, 255, 0), 2);
            
            ss.str("");
            ss << "Contrast: " << fixed << setprecision(1) << props.contrast;
            putText(displayFrame, ss.str(), Point(10, 60), 
                   FONT_HERSHEY_SIMPLEX, 0.6, Scalar(0, 255, 0), 2);
            
            ss.str("");
            ss << "Exposure: " << fixed << setprecision(1) << props.exposure;
            putText(displayFrame, ss.str(), Point(10, 90), 
                   FONT_HERSHEY_SIMPLEX, 0.6, Scalar(0, 255, 0), 2);
            
            ss.str("");
            ss << "Saturation: " << fixed << setprecision(1) << props.saturation;
            putText(displayFrame, ss.str(), Point(10, 120), 
                   FONT_HERSHEY_SIMPLEX, 0.6, Scalar(0, 255, 0), 2);
            
            putText(displayFrame, "Press 'q' to quit, 'p' for properties, 'm' for MATLAB", 
                   Point(10, displayFrame.rows - 20), 
                   FONT_HERSHEY_SIMPLEX, 0.5, Scalar(255, 255, 255), 1);
            
            // Display the frame
            imshow("Camera Properties Control", displayFrame);
            
            // Handle keyboard input
            char key = waitKey(1) & 0xFF;
            
            if (key == 'q' || key == 27) { // 'q' or ESC to quit
                cout << "Quitting..." << endl;
                break;
            }
            else if (key == 'b') { // Increase brightness
                props.brightness = min(100.0, props.brightness + 5.0);
                cap.set(CAP_PROP_BRIGHTNESS, props.brightness);
                cout << "Brightness increased to: " << props.brightness << endl;
            }
            else if (key == 'B') { // Decrease brightness
                props.brightness = max(0.0, props.brightness - 5.0);
                cap.set(CAP_PROP_BRIGHTNESS, props.brightness);
                cout << "Brightness decreased to: " << props.brightness << endl;
            }
            else if (key == 'c') { // Increase contrast
                props.contrast = min(100.0, props.contrast + 5.0);
                cap.set(CAP_PROP_CONTRAST, props.contrast);
                cout << "Contrast increased to: " << props.contrast << endl;
            }
            else if (key == 'C') { // Decrease contrast
                props.contrast = max(0.0, props.contrast - 5.0);
                cap.set(CAP_PROP_CONTRAST, props.contrast);
                cout << "Contrast decreased to: " << props.contrast << endl;
            }
            else if (key == 'e') { // Increase exposure
                props.exposure = min(100.0, props.exposure + 5.0);
                cap.set(CAP_PROP_EXPOSURE, props.exposure);
                cout << "Exposure increased to: " << props.exposure << endl;
            }
            else if (key == 'E') { // Decrease exposure
                props.exposure = max(-13.0, props.exposure - 5.0);
                cap.set(CAP_PROP_EXPOSURE, props.exposure);
                cout << "Exposure decreased to: " << props.exposure << endl;
            }
            else if (key == 's') { // Increase saturation
                props.saturation = min(100.0, props.saturation + 5.0);
                cap.set(CAP_PROP_SATURATION, props.saturation);
                cout << "Saturation increased to: " << props.saturation << endl;
            }
            else if (key == 'S') { // Decrease saturation
                props.saturation = max(0.0, props.saturation - 5.0);
                cap.set(CAP_PROP_SATURATION, props.saturation);
                cout << "Saturation decreased to: " << props.saturation << endl;
            }
            else if (key == 'h') { // Increase hue
                props.hue = min(180.0, props.hue + 5.0);
                cap.set(CAP_PROP_HUE, props.hue);
                cout << "Hue increased to: " << props.hue << endl;
            }
            else if (key == 'H') { // Decrease hue
                props.hue = max(-180.0, props.hue - 5.0);
                cap.set(CAP_PROP_HUE, props.hue);
                cout << "Hue decreased to: " << props.hue << endl;
            }
            else if (key == 'g') { // Increase gain
                props.gain = min(100.0, props.gain + 5.0);
                cap.set(CAP_PROP_GAIN, props.gain);
                cout << "Gain increased to: " << props.gain << endl;
            }
            else if (key == 'G') { // Decrease gain
                props.gain = max(0.0, props.gain - 5.0);
                cap.set(CAP_PROP_GAIN, props.gain);
                cout << "Gain decreased to: " << props.gain << endl;
            }
            else if (key == 'w') { // Toggle white balance
                props.whiteBalance = (props.whiteBalance == 0) ? 1 : 0;
                cap.set(CAP_PROP_AUTO_WB, props.whiteBalance);
                cout << "White balance auto: " << (props.whiteBalance ? "ON" : "OFF") << endl;
            }
            else if (key == 'r') { // Reset to default
                cap.set(CAP_PROP_BRIGHTNESS, 50);
                cap.set(CAP_PROP_CONTRAST, 50);
                cap.set(CAP_PROP_EXPOSURE, -6);
                cap.set(CAP_PROP_SATURATION, 50);
                cap.set(CAP_PROP_HUE, 0);
                cap.set(CAP_PROP_GAIN, 0);
                cap.set(CAP_PROP_AUTO_WB, 1);
                updateCameraProperties(cap, props);
                cout << "Camera properties reset to default!" << endl;
            }
            else if (key == 'p') { // Print current properties
                displayCameraProperties(cap, props);
            }
            else if (key == 'm') { // Send properties to MATLAB
                sendPropertiesToMATLAB(matlabPtr, props);
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
 * g++ -std=c++17 camera_basic_03.cpp -o camera_basic_03 \
 *     `pkg-config --cflags --libs opencv4` \
 *     -I/Applications/MATLAB_R2023b.app/extern/include \
 *     -L/Applications/MATLAB_R2023b.app/bin/maci64 \
 *     -lMatlabDataArray -lMatlabEngine
 * 
 * @brief Usage:
 * 1. Make sure your camera is connected and working
 * 2. Run the executable: ./camera_basic_03
 * 3. Use keyboard controls to adjust camera properties
 * 4. Press 'p' to see current properties
 * 5. Press 'm' to send properties to MATLAB
 * 
 * @brief Learning Objectives:
 * - Understand camera property control
 * - Learn to adjust brightness, contrast, exposure
 * - Understand real-time property modification
 * - Learn to send structured data to MATLAB
 * - Understand camera capability limitations
 * - Learn property value ranges and constraints
 * - Understand auto vs manual control modes
 */
