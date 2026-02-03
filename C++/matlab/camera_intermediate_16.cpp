/**
 * @file camera_intermediate_16.cpp
 * @brief Stereo Vision and Depth Estimation - Intermediate Level 16
 * @description This program demonstrates stereo vision techniques including
 *              stereo calibration, disparity calculation, and depth estimation
 *              using OpenCV and MATLAB integration for real-time analysis.
 * @author Educational C++ MATLAB Integration Project
 * @date 2024
 * @version 1.0
 */

#include <opencv2/opencv.hpp>
#include <opencv2/calib3d.hpp>
#include <iostream>
#include <matlab/engine.hpp>
#include <memory>
#include <vector>
#include <algorithm>

using namespace cv;
using namespace std;

/**
 * @brief Enumeration for different stereo methods
 */
enum StereoMethod {
    STEREO_BM = 0,
    STEREO_SGBM = 1,
    STEREO_HH = 2,
    STEREO_VAR = 3,
    STEREO_3WAY = 4
};

/**
 * @brief Structure to hold stereo parameters
 */
struct StereoParams {
    int blockSize;
    int numDisparities;
    int minDisparity;
    int speckleWindowSize;
    int speckleRange;
    int uniquenessRatio;
    int textureThreshold;
    int preFilterCap;
    int preFilterSize;
    int disp12MaxDiff;
    int P1;
    int P2;
    double baseline;
    double focalLength;
};

/**
 * @brief Function to get stereo method name
 * @param method Stereo method
 * @return string Method name
 */
string getStereoMethodName(StereoMethod method) {
    switch (method) {
        case STEREO_BM: return "Stereo BM";
        case STEREO_SGBM: return "Stereo SGBM";
        case STEREO_HH: return "Stereo HH";
        case STEREO_VAR: return "Stereo VAR";
        case STEREO_3WAY: return "Stereo 3-Way";
        default: return "Unknown";
    }
}

/**
 * @brief Function to create stereo matcher
 * @param method Stereo method
 * @param params Stereo parameters
 * @return Ptr<StereoMatcher> Stereo matcher
 */
Ptr<StereoMatcher> createStereoMatcher(StereoMethod method, const StereoParams& params) {
    Ptr<StereoMatcher> matcher;
    
    switch (method) {
        case STEREO_BM:
            matcher = StereoBM::create(params.numDisparities, params.blockSize);
            break;
        case STEREO_SGBM:
            matcher = StereoSGBM::create(params.minDisparity, params.numDisparities, params.blockSize,
                                       params.P1, params.P2, params.disp12MaxDiff,
                                       params.preFilterCap, params.uniquenessRatio,
                                       params.speckleWindowSize, params.speckleRange,
                                       StereoSGBM::MODE_SGBM);
            break;
        case STEREO_HH:
            matcher = StereoSGBM::create(params.minDisparity, params.numDisparities, params.blockSize,
                                       params.P1, params.P2, params.disp12MaxDiff,
                                       params.preFilterCap, params.uniquenessRatio,
                                       params.speckleWindowSize, params.speckleRange,
                                       StereoSGBM::MODE_HH);
            break;
        case STEREO_VAR:
            matcher = StereoSGBM::create(params.minDisparity, params.numDisparities, params.blockSize,
                                       params.P1, params.P2, params.disp12MaxDiff,
                                       params.preFilterCap, params.uniquenessRatio,
                                       params.speckleWindowSize, params.speckleRange,
                                       StereoSGBM::MODE_SGBM_3WAY);
            break;
        case STEREO_3WAY:
            matcher = StereoSGBM::create(params.minDisparity, params.numDisparities, params.blockSize,
                                       params.P1, params.P2, params.disp12MaxDiff,
                                       params.preFilterCap, params.uniquenessRatio,
                                       params.speckleWindowSize, params.speckleRange,
                                       StereoSGBM::MODE_SGBM_3WAY);
            break;
    }
    
    return matcher;
}

/**
 * @brief Function to compute disparity
 * @param left Left image
 * @param right Right image
 * @param disparity Output disparity map
 * @param method Stereo method
 * @param params Stereo parameters
 */
void computeDisparity(const Mat& left, const Mat& right, Mat& disparity, 
                     StereoMethod method, const StereoParams& params) {
    // Create stereo matcher
    Ptr<StereoMatcher> matcher = createStereoMatcher(method, params);
    
    // Compute disparity
    matcher->compute(left, right, disparity);
    
    // Normalize disparity for visualization
    normalize(disparity, disparity, 0, 255, NORM_MINMAX, CV_8U);
}

/**
 * @brief Function to compute depth from disparity
 * @param disparity Input disparity map
 * @param depth Output depth map
 * @param params Stereo parameters
 */
void computeDepthFromDisparity(const Mat& disparity, Mat& depth, const StereoParams& params) {
    // Convert disparity to depth
    depth = Mat::zeros(disparity.size(), CV_32F);
    
    for (int i = 0; i < disparity.rows; i++) {
        for (int j = 0; j < disparity.cols; j++) {
            float disp = disparity.at<uchar>(i, j);
            if (disp > 0) {
                depth.at<float>(i, j) = (params.baseline * params.focalLength) / disp;
            }
        }
    }
    
    // Normalize depth for visualization
    normalize(depth, depth, 0, 255, NORM_MINMAX, CV_8U);
}

/**
 * @brief Function to create stereo visualization
 * @param left Left image
 * @param right Right image
 * @param disparity Disparity map
 * @param depth Depth map
 * @return Mat Stereo visualization
 */
Mat createStereoVisualization(const Mat& left, const Mat& right, const Mat& disparity, const Mat& depth) {
    // Create 2x2 grid
    Mat visualization = Mat::zeros(left.rows * 2, left.cols * 2, CV_8UC3);
    
    // Convert grayscale images to BGR
    Mat leftBGR, rightBGR, disparityBGR, depthBGR;
    if (left.channels() == 1) {
        cvtColor(left, leftBGR, COLOR_GRAY2BGR);
    } else {
        leftBGR = left;
    }
    
    if (right.channels() == 1) {
        cvtColor(right, rightBGR, COLOR_GRAY2BGR);
    } else {
        rightBGR = right;
    }
    
    if (disparity.channels() == 1) {
        cvtColor(disparity, disparityBGR, COLOR_GRAY2BGR);
    } else {
        disparityBGR = disparity;
    }
    
    if (depth.channels() == 1) {
        cvtColor(depth, depthBGR, COLOR_GRAY2BGR);
    } else {
        depthBGR = depth;
    }
    
    // Place images in grid
    leftBGR.copyTo(visualization(Rect(0, 0, left.cols, left.rows)));
    rightBGR.copyTo(visualization(Rect(left.cols, 0, right.cols, right.rows)));
    disparityBGR.copyTo(visualization(Rect(0, left.rows, disparity.cols, disparity.rows)));
    depthBGR.copyTo(visualization(Rect(left.cols, left.rows, depth.cols, depth.rows)));
    
    // Add labels
    putText(visualization, "Left", Point(10, 30), FONT_HERSHEY_SIMPLEX, 0.7, Scalar(0, 255, 0), 2);
    putText(visualization, "Right", Point(left.cols + 10, 30), FONT_HERSHEY_SIMPLEX, 0.7, Scalar(0, 255, 0), 2);
    putText(visualization, "Disparity", Point(10, left.rows + 30), FONT_HERSHEY_SIMPLEX, 0.7, Scalar(0, 255, 0), 2);
    putText(visualization, "Depth", Point(left.cols + 10, left.rows + 30), FONT_HERSHEY_SIMPLEX, 0.7, Scalar(0, 255, 0), 2);
    
    return visualization;
}

/**
 * @brief Function to send stereo data to MATLAB
 * @param matlabPtr MATLAB engine pointer
 * @param left Left image
 * @param right Right image
 * @param disparity Disparity map
 * @param depth Depth map
 * @param method Stereo method
 * @param params Stereo parameters
 */
void sendStereoToMATLAB(std::unique_ptr<matlab::engine::MATLABEngine>& matlabPtr, 
                       const Mat& left, const Mat& right, const Mat& disparity, const Mat& depth,
                       StereoMethod method, const StereoParams& params) {
    try {
        // Convert BGR to RGB for MATLAB
        Mat rgbLeft, rgbRight, rgbDisparity, rgbDepth;
        
        if (left.channels() == 1) {
            cvtColor(left, rgbLeft, COLOR_GRAY2RGB);
        } else {
            cvtColor(left, rgbLeft, COLOR_BGR2RGB);
        }
        
        if (right.channels() == 1) {
            cvtColor(right, rgbRight, COLOR_GRAY2RGB);
        } else {
            cvtColor(right, rgbRight, COLOR_BGR2RGB);
        }
        
        if (disparity.channels() == 1) {
            cvtColor(disparity, rgbDisparity, COLOR_GRAY2RGB);
        } else {
            cvtColor(disparity, rgbDisparity, COLOR_BGR2RGB);
        }
        
        if (depth.channels() == 1) {
            cvtColor(depth, rgbDepth, COLOR_GRAY2RGB);
        } else {
            cvtColor(depth, rgbDepth, COLOR_BGR2RGB);
        }
        
        // Create MATLAB arrays
        matlab::data::ArrayFactory factory;
        
        // Left image
        auto dimsLeft = factory.createArray<std::size_t>({1, 3}, 
            {static_cast<std::size_t>(rgbLeft.rows), 
             static_cast<std::size_t>(rgbLeft.cols), 
             static_cast<std::size_t>(rgbLeft.channels())});
        auto matlabLeft = factory.createArray<uint8_t>(dimsLeft);
        auto leftPtr = matlabLeft.release();
        memcpy(leftPtr, rgbLeft.data, rgbLeft.total() * rgbLeft.elemSize());
        
        // Right image
        auto dimsRight = factory.createArray<std::size_t>({1, 3}, 
            {static_cast<std::size_t>(rgbRight.rows), 
             static_cast<std::size_t>(rgbRight.cols), 
             static_cast<std::size_t>(rgbRight.channels())});
        auto matlabRight = factory.createArray<uint8_t>(dimsRight);
        auto rightPtr = matlabRight.release();
        memcpy(rightPtr, rgbRight.data, rgbRight.total() * rgbRight.elemSize());
        
        // Disparity map
        auto dimsDisp = factory.createArray<std::size_t>({1, 3}, 
            {static_cast<std::size_t>(rgbDisparity.rows), 
             static_cast<std::size_t>(rgbDisparity.cols), 
             static_cast<std::size_t>(rgbDisparity.channels())});
        auto matlabDisp = factory.createArray<uint8_t>(dimsDisp);
        auto dispPtr = matlabDisp.release();
        memcpy(dispPtr, rgbDisparity.data, rgbDisparity.total() * rgbDisparity.elemSize());
        
        // Depth map
        auto dimsDepth = factory.createArray<std::size_t>({1, 3}, 
            {static_cast<std::size_t>(rgbDepth.rows), 
             static_cast<std::size_t>(rgbDepth.cols), 
             static_cast<std::size_t>(rgbDepth.channels())});
        auto matlabDepth = factory.createArray<uint8_t>(dimsDepth);
        auto depthPtr = matlabDepth.release();
        memcpy(depthPtr, rgbDepth.data, rgbDepth.total() * rgbDepth.elemSize());
        
        // Set variables in MATLAB workspace
        matlabPtr->setVariable(u"leftImage", matlabLeft);
        matlabPtr->setVariable(u"rightImage", matlabRight);
        matlabPtr->setVariable(u"disparityMap", matlabDisp);
        matlabPtr->setVariable(u"depthMap", matlabDepth);
        
        // Execute MATLAB commands
        string methodName = getStereoMethodName(method);
        string matlabCmd = "figure; subplot(2,2,1); imshow(leftImage); title('Left Image'); "
                          "subplot(2,2,2); imshow(rightImage); title('Right Image'); "
                          "subplot(2,2,3); imshow(disparityMap); title('Disparity Map'); "
                          "subplot(2,2,4); imshow(depthMap); title('Depth Map');";
        matlabPtr->eval(matlab::engine::convertUTF8StringToUTF16String(matlabCmd));
        
        // Display stereo information
        matlabPtr->eval(u"fprintf('Stereo Method: " + matlab::engine::convertUTF8StringToUTF16String(methodName) + "\\n');");
        matlabPtr->eval(u"fprintf('Baseline: %.2f\\n', " + to_string(params.baseline) + u");");
        matlabPtr->eval(u"fprintf('Focal Length: %.2f\\n', " + to_string(params.focalLength) + u");");
        
        cout << "Stereo data sent to MATLAB successfully!" << endl;
        
    } catch (const std::exception& e) {
        cerr << "Error sending stereo data to MATLAB: " << e.what() << endl;
    }
}

/**
 * @brief Main function for stereo vision and depth estimation
 * @return int Exit status
 */
int main() {
    cout << "=== Stereo Vision and Depth Estimation - Intermediate Level 16 ===" << endl;
    cout << "This program demonstrates stereo vision and depth estimation techniques." << endl;
    
    try {
        // Initialize MATLAB engine
        cout << "Initializing MATLAB engine..." << endl;
        std::unique_ptr<matlab::engine::MATLABEngine> matlabPtr = 
            matlab::engine::startMATLAB();
        
        // Initialize camera capture
        cout << "Initializing cameras..." << endl;
        VideoCapture cap1(0); // Left camera
        VideoCapture cap2(1); // Right camera
        
        // Check if cameras opened successfully
        if (!cap1.isOpened()) {
            cerr << "Error: Could not open left camera!" << endl;
            return -1;
        }
        
        if (!cap2.isOpened()) {
            cerr << "Error: Could not open right camera!" << endl;
            return -1;
        }
        
        cout << "Cameras opened successfully!" << endl;
        
        // Set camera properties
        cap1.set(CAP_PROP_FRAME_WIDTH, 640);
        cap1.set(CAP_PROP_FRAME_HEIGHT, 480);
        cap2.set(CAP_PROP_FRAME_WIDTH, 640);
        cap2.set(CAP_PROP_FRAME_HEIGHT, 480);
        
        // Initialize stereo parameters
        StereoParams params;
        params.blockSize = 15;
        params.numDisparities = 16 * 5;
        params.minDisparity = 0;
        params.speckleWindowSize = 200;
        params.speckleRange = 2;
        params.uniquenessRatio = 10;
        params.textureThreshold = 10;
        params.preFilterCap = 63;
        params.preFilterSize = 9;
        params.disp12MaxDiff = 1;
        params.P1 = 8 * 3 * params.blockSize * params.blockSize;
        params.P2 = 32 * 3 * params.blockSize * params.blockSize;
        params.baseline = 50.0; // mm
        params.focalLength = 500.0; // pixels
        
        // Initialize stereo method
        StereoMethod currentMethod = STEREO_SGBM;
        
        // Create Mat objects for frame processing
        Mat leftFrame, rightFrame, leftGray, rightGray, disparity, depth, visualization;
        
        cout << "\nStarting stereo camera feed..." << endl;
        cout << "Controls:" << endl;
        cout << "  'q' - Quit" << endl;
        cout << "  '0' - Stereo BM" << endl;
        cout << "  '1' - Stereo SGBM" << endl;
        cout << "  '2' - Stereo HH" << endl;
        cout << "  '3' - Stereo VAR" << endl;
        cout << "  '4' - Stereo 3-Way" << endl;
        cout << "  '+' - Increase num disparities" << endl;
        cout << "  '-' - Decrease num disparities" << endl;
        cout << "  'b' - Increase block size" << endl;
        cout << "  'B' - Decrease block size" << endl;
        cout << "  'm' - Send to MATLAB" << endl;
        cout << "  's' - Save current stereo" << endl;
        
        // Main capture loop
        while (true) {
            // Capture frames from cameras
            cap1 >> leftFrame;
            cap2 >> rightFrame;
            
            // Check if frames were captured successfully
            if (leftFrame.empty() || rightFrame.empty()) {
                cerr << "Warning: Could not capture frames!" << endl;
                continue;
            }
            
            // Convert to grayscale
            cvtColor(leftFrame, leftGray, COLOR_BGR2GRAY);
            cvtColor(rightFrame, rightGray, COLOR_BGR2GRAY);
            
            // Compute disparity
            computeDisparity(leftGray, rightGray, disparity, currentMethod, params);
            
            // Compute depth from disparity
            computeDepthFromDisparity(disparity, depth, params);
            
            // Create visualization
            visualization = createStereoVisualization(leftGray, rightGray, disparity, depth);
            
            // Display the visualization
            imshow("Stereo Vision and Depth Estimation", visualization);
            
            // Handle keyboard input
            char key = waitKey(1) & 0xFF;
            
            if (key == 'q' || key == 27) { // 'q' or ESC to quit
                cout << "Quitting..." << endl;
                break;
            }
            else if (key >= '0' && key <= '4') { // Method selection
                currentMethod = static_cast<StereoMethod>(key - '0');
                cout << "Selected method: " << getStereoMethodName(currentMethod) << endl;
            }
            else if (key == '+') { // Increase num disparities
                params.numDisparities = min(256, params.numDisparities + 16);
                cout << "Num disparities increased to: " << params.numDisparities << endl;
            }
            else if (key == '-') { // Decrease num disparities
                params.numDisparities = max(16, params.numDisparities - 16);
                cout << "Num disparities decreased to: " << params.numDisparities << endl;
            }
            else if (key == 'b') { // Increase block size
                params.blockSize = min(31, params.blockSize + 2);
                cout << "Block size increased to: " << params.blockSize << endl;
            }
            else if (key == 'B') { // Decrease block size
                params.blockSize = max(5, params.blockSize - 2);
                cout << "Block size decreased to: " << params.blockSize << endl;
            }
            else if (key == 'm') { // Send to MATLAB
                sendStereoToMATLAB(matlabPtr, leftGray, rightGray, disparity, depth, currentMethod, params);
            }
            else if (key == 's') { // Save current stereo
                string filename = "stereo_" + getStereoMethodName(currentMethod) + ".jpg";
                imwrite(filename, visualization);
                cout << "Stereo visualization saved as: " << filename << endl;
            }
        }
        
        // Clean up
        cap1.release();
        cap2.release();
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
 * g++ -std=c++17 camera_intermediate_16.cpp -o camera_intermediate_16 \
 *     `pkg-config --cflags --libs opencv4` \
 *     -I/Applications/MATLAB_R2023b.app/extern/include \
 *     -L/Applications/MATLAB_R2023b.app/bin/maci64 \
 *     -lMatlabDataArray -lMatlabEngine
 * 
 * @brief Usage:
 * 1. Make sure you have two cameras connected
 * 2. Run the executable: ./camera_intermediate_16
 * 3. Use keyboard controls to switch between stereo methods
 * 4. Adjust parameters with keyboard controls
 * 5. Press 'm' to send data to MATLAB
 * 6. Press 's' to save current stereo visualization
 * 
 * @brief Learning Objectives:
 * - Understand stereo vision principles
 * - Learn stereo calibration and rectification
 * - Understand disparity calculation methods
 * - Learn depth estimation from disparity
 * - Understand stereo matching algorithms
 * - Learn MATLAB integration for stereo analysis
 * - Understand stereo vision applications
 * - Learn to choose appropriate stereo methods
 */
