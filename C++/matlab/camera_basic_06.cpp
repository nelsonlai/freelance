/**
 * @file camera_basic_06.cpp
 * @brief Color Space Conversion - Beginner Level 6
 * @description This program demonstrates color space conversions between RGB, HSV,
 *              LAB, YUV, and other color spaces using OpenCV and MATLAB integration.
 * @author Educational C++ MATLAB Integration Project
 * @date 2024
 * @version 1.0
 */

#include <opencv2/opencv.hpp>
#include <iostream>
#include <matlab/engine.hpp>
#include <memory>
#include <vector>
#include <iomanip>

using namespace cv;
using namespace std;

/**
 * @brief Enumeration for different color spaces
 */
enum ColorSpace {
    BGR = 0,
    RGB = 1,
    HSV = 2,
    LAB = 3,
    YUV = 4,
    GRAY = 5,
    XYZ = 6,
    LUV = 7,
    HLS = 8,
    YCrCb = 9
};

/**
 * @brief Structure to hold color space information
 */
struct ColorSpaceInfo {
    ColorSpace space;
    string name;
    int channels;
    string description;
};

/**
 * @brief Function to get color space information
 * @param space Color space type
 * @return ColorSpaceInfo Color space information
 */
ColorSpaceInfo getColorSpaceInfo(ColorSpace space) {
    switch (space) {
        case BGR: return {BGR, "BGR", 3, "Blue-Green-Red (OpenCV default)"};
        case RGB: return {RGB, "RGB", 3, "Red-Green-Blue"};
        case HSV: return {HSV, "HSV", 3, "Hue-Saturation-Value"};
        case LAB: return {LAB, "LAB", 3, "Lightness-A-B (Perceptual)"};
        case YUV: return {YUV, "YUV", 3, "Luminance-Chrominance"};
        case GRAY: return {GRAY, "GRAY", 1, "Grayscale"};
        case XYZ: return {XYZ, "XYZ", 3, "CIE XYZ Color Space"};
        case LUV: return {LUV, "LUV", 3, "CIE LUV Color Space"};
        case HLS: return {HLS, "HLS", 3, "Hue-Lightness-Saturation"};
        case YCrCb: return {YCrCb, "YCrCb", 3, "Luminance-Chrominance (JPEG)"};
        default: return {BGR, "Unknown", 0, "Unknown color space"};
    }
}

/**
 * @brief Function to convert image to specified color space
 * @param src Input image
 * @param dst Output image
 * @param space Target color space
 */
void convertToColorSpace(const Mat& src, Mat& dst, ColorSpace space) {
    switch (space) {
        case BGR:
            src.copyTo(dst);
            break;
        case RGB:
            cvtColor(src, dst, COLOR_BGR2RGB);
            break;
        case HSV:
            cvtColor(src, dst, COLOR_BGR2HSV);
            break;
        case LAB:
            cvtColor(src, dst, COLOR_BGR2LAB);
            break;
        case YUV:
            cvtColor(src, dst, COLOR_BGR2YUV);
            break;
        case GRAY:
            cvtColor(src, dst, COLOR_BGR2GRAY);
            break;
        case XYZ:
            cvtColor(src, dst, COLOR_BGR2XYZ);
            break;
        case LUV:
            cvtColor(src, dst, COLOR_BGR2LUV);
            break;
        case HLS:
            cvtColor(src, dst, COLOR_BGR2HLS);
            break;
        case YCrCb:
            cvtColor(src, dst, COLOR_BGR2YCrCb);
            break;
    }
}

/**
 * @brief Function to create color space visualization
 * @param src Input image
 * @param space Color space type
 * @return Mat Visualization of color space channels
 */
Mat createColorSpaceVisualization(const Mat& src, ColorSpace space) {
    Mat converted;
    convertToColorSpace(src, converted, space);
    
    ColorSpaceInfo info = getColorSpaceInfo(space);
    
    if (info.channels == 1) {
        // For grayscale, create a 3-channel version for display
        Mat gray3;
        cvtColor(converted, gray3, COLOR_GRAY2BGR);
        return gray3;
    } else {
        // For multi-channel images, create channel separation
        vector<Mat> channels;
        split(converted, channels);
        
        Mat visualization;
        if (channels.size() >= 3) {
            // Create a 3-channel visualization
            Mat channel1, channel2, channel3;
            
            // Normalize each channel to 0-255 range
            normalize(channels[0], channel1, 0, 255, NORM_MINMAX, CV_8U);
            normalize(channels[1], channel2, 0, 255, NORM_MINMAX, CV_8U);
            normalize(channels[2], channel3, 0, 255, NORM_MINMAX, CV_8U);
            
            // Create BGR visualization
            vector<Mat> bgrChannels = {channel3, channel2, channel1};
            merge(bgrChannels, visualization);
        } else {
            converted.copyTo(visualization);
        }
        
        return visualization;
    }
}

/**
 * @brief Function to create channel separation display
 * @param src Input image
 * @param space Color space type
 * @return Mat Channel separation display
 */
Mat createChannelSeparation(const Mat& src, ColorSpace space) {
    Mat converted;
    convertToColorSpace(src, converted, space);
    
    ColorSpaceInfo info = getColorSpaceInfo(space);
    
    if (info.channels == 1) {
        // For grayscale, create a 3-channel version
        Mat gray3;
        cvtColor(converted, gray3, COLOR_GRAY2BGR);
        return gray3;
    } else {
        // For multi-channel images, create channel separation
        vector<Mat> channels;
        split(converted, channels);
        
        Mat separation;
        if (channels.size() >= 3) {
            // Create a 3-channel separation
            Mat channel1, channel2, channel3;
            
            // Normalize each channel to 0-255 range
            normalize(channels[0], channel1, 0, 255, NORM_MINMAX, CV_8U);
            normalize(channels[1], channel2, 0, 255, NORM_MINMAX, CV_8U);
            normalize(channels[2], channel3, 0, 255, NORM_MINMAX, CV_8U);
            
            // Create BGR visualization
            vector<Mat> bgrChannels = {channel3, channel2, channel1};
            merge(bgrChannels, separation);
        } else {
            converted.copyTo(separation);
        }
        
        return separation;
    }
}

/**
 * @brief Function to send color space data to MATLAB
 * @param matlabPtr MATLAB engine pointer
 * @param src Original image
 * @param converted Converted image
 * @param space Color space type
 */
void sendColorSpaceToMATLAB(std::unique_ptr<matlab::engine::MATLABEngine>& matlabPtr, 
                           const Mat& src, const Mat& converted, ColorSpace space) {
    try {
        ColorSpaceInfo info = getColorSpaceInfo(space);
        
        // Convert BGR to RGB for MATLAB
        Mat rgbSrc, rgbConverted;
        cvtColor(src, rgbSrc, COLOR_BGR2RGB);
        
        if (converted.channels() == 1) {
            // For grayscale, create a 3-channel version
            cvtColor(converted, rgbConverted, COLOR_GRAY2RGB);
        } else {
            cvtColor(converted, rgbConverted, COLOR_BGR2RGB);
        }
        
        // Create MATLAB arrays
        matlab::data::ArrayFactory factory;
        
        // Original image
        auto dimsSrc = factory.createArray<std::size_t>({1, 3}, 
            {static_cast<std::size_t>(rgbSrc.rows), 
             static_cast<std::size_t>(rgbSrc.cols), 
             static_cast<std::size_t>(rgbSrc.channels())});
        auto matlabSrc = factory.createArray<uint8_t>(dimsSrc);
        auto srcPtr = matlabSrc.release();
        memcpy(srcPtr, rgbSrc.data, rgbSrc.total() * rgbSrc.elemSize());
        
        // Converted image
        auto dimsConv = factory.createArray<std::size_t>({1, 3}, 
            {static_cast<std::size_t>(rgbConverted.rows), 
             static_cast<std::size_t>(rgbConverted.cols), 
             static_cast<std::size_t>(rgbConverted.channels())});
        auto matlabConv = factory.createArray<uint8_t>(dimsConv);
        auto convPtr = matlabConv.release();
        memcpy(convPtr, rgbConverted.data, rgbConverted.total() * rgbConverted.elemSize());
        
        // Set variables in MATLAB workspace
        matlabPtr->setVariable(u"originalImage", matlabSrc);
        matlabPtr->setVariable(u"convertedImage", matlabConv);
        
        // Execute MATLAB commands
        string matlabCmd = "figure; subplot(1,2,1); imshow(originalImage); title('Original BGR'); "
                          "subplot(1,2,2); imshow(convertedImage); title('" + info.name + " Color Space');";
        matlabPtr->eval(matlab::engine::convertUTF8StringToUTF16String(matlabCmd));
        
        // Display color space information
        matlabPtr->eval(u"fprintf('Color Space: " + matlab::engine::convertUTF8StringToUTF16String(info.name) + "\\n');");
        matlabPtr->eval(u"fprintf('Description: " + matlab::engine::convertUTF8StringToUTF16String(info.description) + "\\n');");
        matlabPtr->eval(u"fprintf('Channels: %d\\n', " + to_string(info.channels) + u");");
        
        cout << "Color space data sent to MATLAB successfully!" << endl;
        
    } catch (const std::exception& e) {
        cerr << "Error sending color space data to MATLAB: " << e.what() << endl;
    }
}

/**
 * @brief Main function for color space conversion
 * @return int Exit status
 */
int main() {
    cout << "=== Color Space Conversion - Beginner Level 6 ===" << endl;
    cout << "This program demonstrates color space conversions and analysis." << endl;
    
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
        
        // Set camera properties
        cap.set(CAP_PROP_FRAME_WIDTH, 640);
        cap.set(CAP_PROP_FRAME_HEIGHT, 480);
        
        // Initialize color space
        ColorSpace currentSpace = BGR;
        
        // Create Mat objects for frame processing
        Mat frame, convertedFrame, displayFrame;
        
        cout << "\nStarting camera feed with color space conversion..." << endl;
        cout << "Controls:" << endl;
        cout << "  'q' - Quit" << endl;
        cout << "  '0' - BGR (Original)" << endl;
        cout << "  '1' - RGB" << endl;
        cout << "  '2' - HSV" << endl;
        cout << "  '3' - LAB" << endl;
        cout << "  '4' - YUV" << endl;
        cout << "  '5' - GRAY" << endl;
        cout << "  '6' - XYZ" << endl;
        cout << "  '7' - LUV" << endl;
        cout << "  '8' - HLS" << endl;
        cout << "  '9' - YCrCb" << endl;
        cout << "  'c' - Show channel separation" << endl;
        cout << "  'm' - Send to MATLAB" << endl;
        cout << "  's' - Save current conversion" << endl;
        
        bool showChannels = false;
        
        // Main capture loop
        while (true) {
            // Capture frame from camera
            cap >> frame;
            
            // Check if frame was captured successfully
            if (frame.empty()) {
                cerr << "Warning: Could not capture frame!" << endl;
                continue;
            }
            
            // Convert to selected color space
            convertToColorSpace(frame, convertedFrame, currentSpace);
            
            // Create display frame
            if (showChannels) {
                displayFrame = createChannelSeparation(frame, currentSpace);
            } else {
                displayFrame = createColorSpaceVisualization(frame, currentSpace);
            }
            
            // Create side-by-side comparison
            Mat comparison;
            hconcat(frame, displayFrame, comparison);
            
            // Add labels
            ColorSpaceInfo info = getColorSpaceInfo(currentSpace);
            putText(comparison, "Original BGR", Point(10, 30), 
                   FONT_HERSHEY_SIMPLEX, 0.7, Scalar(0, 255, 0), 2);
            putText(comparison, info.name + " Color Space", Point(frame.cols + 10, 30), 
                   FONT_HERSHEY_SIMPLEX, 0.7, Scalar(0, 255, 0), 2);
            
            // Add color space information
            putText(comparison, info.description, Point(10, 60), 
                   FONT_HERSHEY_SIMPLEX, 0.5, Scalar(255, 255, 255), 1);
            putText(comparison, "Channels: " + to_string(info.channels), Point(10, 80), 
                   FONT_HERSHEY_SIMPLEX, 0.5, Scalar(255, 255, 255), 1);
            
            if (showChannels) {
                putText(comparison, "Channel Separation View", Point(frame.cols + 10, 60), 
                       FONT_HERSHEY_SIMPLEX, 0.5, Scalar(255, 255, 255), 1);
            }
            
            // Display the comparison
            imshow("Color Space Conversion", comparison);
            
            // Handle keyboard input
            char key = waitKey(1) & 0xFF;
            
            if (key == 'q' || key == 27) { // 'q' or ESC to quit
                cout << "Quitting..." << endl;
                break;
            }
            else if (key >= '0' && key <= '9') { // Color space selection
                currentSpace = static_cast<ColorSpace>(key - '0');
                ColorSpaceInfo info = getColorSpaceInfo(currentSpace);
                cout << "Selected color space: " << info.name << " - " << info.description << endl;
            }
            else if (key == 'c') { // Toggle channel separation
                showChannels = !showChannels;
                cout << "Channel separation view: " << (showChannels ? "ON" : "OFF") << endl;
            }
            else if (key == 'm') { // Send to MATLAB
                sendColorSpaceToMATLAB(matlabPtr, frame, convertedFrame, currentSpace);
            }
            else if (key == 's') { // Save current conversion
                string filename = "colorspace_" + info.name + ".jpg";
                imwrite(filename, displayFrame);
                cout << "Color space conversion saved as: " << filename << endl;
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
 * g++ -std=c++17 camera_basic_06.cpp -o camera_basic_06 \
 *     `pkg-config --cflags --libs opencv4` \
 *     -I/Applications/MATLAB_R2023b.app/extern/include \
 *     -L/Applications/MATLAB_R2023b.app/bin/maci64 \
 *     -lMatlabDataArray -lMatlabEngine
 * 
 * @brief Usage:
 * 1. Make sure your camera is connected and working
 * 2. Run the executable: ./camera_basic_06
 * 3. Use keyboard controls to switch between color spaces
 * 4. Press 'c' to toggle channel separation view
 * 5. Press 'm' to send color space data to MATLAB
 * 6. Press 's' to save current color space conversion
 * 
 * @brief Learning Objectives:
 * - Understand different color spaces and their properties
 * - Learn color space conversion techniques
 * - Understand channel separation and visualization
 * - Learn perceptual vs device-dependent color spaces
 * - Understand color space applications in computer vision
 * - Learn MATLAB integration for color analysis
 * - Understand color space mathematical foundations
 * - Learn to choose appropriate color spaces for different tasks
 */
