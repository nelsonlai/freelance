/**
 * @file camera_intermediate_17.cpp
 * @brief Motion Analysis and Optical Flow - Intermediate Level 17
 * @description This program demonstrates motion analysis techniques including
 *              optical flow calculation, motion detection, and tracking using
 *              OpenCV and MATLAB integration for real-time analysis.
 * @author Educational C++ MATLAB Integration Project
 * @date 2024
 * @version 1.0
 */

#include <opencv2/opencv.hpp>
#include <opencv2/video.hpp>
#include <iostream>
#include <matlab/engine.hpp>
#include <memory>
#include <vector>
#include <algorithm>

using namespace cv;
using namespace std;

/**
 * @brief Enumeration for different optical flow methods
 */
enum OpticalFlowMethod {
    LUCAS_KANADE = 0,
    FARNEBACK = 1,
    TVL1 = 2,
    DUAL_TVL1 = 3,
    DIS = 4,
    PYR_LK = 5
};

/**
 * @brief Structure to hold optical flow parameters
 */
struct OpticalFlowParams {
    int lkWindowSize;
    int lkMaxLevel;
    double lkCriteriaEpsilon;
    int lkCriteriaMaxCount;
    int farnebackLevels;
    double farnebackScale;
    int farnebackWinsize;
    int farnebackIterations;
    int farnebackPolyN;
    double farnebackPolySigma;
    double tvl1Lambda;
    double tvl1Tau;
    double tvl1Theta;
    int tvl1Nscales;
    double tvl1Warpings;
    double disPreset;
    int pyrLkLevels;
    int pyrLkWinsize;
};

/**
 * @brief Function to get optical flow method name
 * @param method Optical flow method
 * @return string Method name
 */
string getOpticalFlowMethodName(OpticalFlowMethod method) {
    switch (method) {
        case LUCAS_KANADE: return "Lucas-Kanade";
        case FARNEBACK: return "Farneback";
        case TVL1: return "TV-L1";
        case DUAL_TVL1: return "Dual TV-L1";
        case DIS: return "DIS";
        case PYR_LK: return "Pyramidal LK";
        default: return "Unknown";
    }
}

/**
 * @brief Function to apply Lucas-Kanade optical flow
 * @param prevFrame Previous frame
 * @param currFrame Current frame
 * @param flow Output flow field
 * @param params Optical flow parameters
 */
void applyLucasKanadeFlow(const Mat& prevFrame, const Mat& currFrame, Mat& flow, 
                         const OpticalFlowParams& params) {
    // Detect corners in previous frame
    vector<Point2f> prevCorners, currCorners;
    goodFeaturesToTrack(prevFrame, prevCorners, 100, 0.01, 10);
    
    // Calculate optical flow
    vector<uchar> status;
    vector<float> error;
    calcOpticalFlowPyrLK(prevFrame, currFrame, prevCorners, currCorners, 
                        status, error, Size(params.lkWindowSize, params.lkWindowSize), 
                        params.lkMaxLevel, 
                        TermCriteria(TermCriteria::COUNT + TermCriteria::EPS, 
                                   params.lkCriteriaMaxCount, params.lkCriteriaEpsilon));
    
    // Create flow visualization
    flow = Mat::zeros(prevFrame.size(), CV_8UC3);
    for (size_t i = 0; i < prevCorners.size(); i++) {
        if (status[i]) {
            Point2f flowVec = currCorners[i] - prevCorners[i];
            double magnitude = sqrt(flowVec.x * flowVec.x + flowVec.y * flowVec.y);
            
            if (magnitude > 1.0) {
                // Draw flow vector
                arrowedLine(flow, prevCorners[i], currCorners[i], 
                           Scalar(0, 255, 0), 2, 8, 0, 0.3);
            }
        }
    }
}

/**
 * @brief Function to apply Farneback optical flow
 * @param prevFrame Previous frame
 * @param currFrame Current frame
 * @param flow Output flow field
 * @param params Optical flow parameters
 */
void applyFarnebackFlow(const Mat& prevFrame, const Mat& currFrame, Mat& flow, 
                       const OpticalFlowParams& params) {
    // Calculate optical flow
    Mat flowField;
    calcOpticalFlowFarneback(prevFrame, currFrame, flowField, params.farnebackScale, 
                            params.farnebackLevels, params.farnebackWinsize, 
                            params.farnebackIterations, params.farnebackPolyN, 
                            params.farnebackPolySigma, OPTFLOW_FARNEBACK_GAUSSIAN);
    
    // Create flow visualization
    flow = Mat::zeros(prevFrame.size(), CV_8UC3);
    for (int y = 0; y < flowField.rows; y += 10) {
        for (int x = 0; x < flowField.cols; x += 10) {
            Point2f flowVec = flowField.at<Point2f>(y, x);
            double magnitude = sqrt(flowVec.x * flowVec.x + flowVec.y * flowVec.y);
            
            if (magnitude > 1.0) {
                // Draw flow vector
                Point2f endPoint(x + flowVec.x, y + flowVec.y);
                arrowedLine(flow, Point(x, y), endPoint, 
                           Scalar(0, 255, 0), 2, 8, 0, 0.3);
            }
        }
    }
}

/**
 * @brief Function to apply TV-L1 optical flow
 * @param prevFrame Previous frame
 * @param currFrame Current frame
 * @param flow Output flow field
 * @param params Optical flow parameters
 */
void applyTVL1Flow(const Mat& prevFrame, const Mat& currFrame, Mat& flow, 
                  const OpticalFlowParams& params) {
    // Create TV-L1 optical flow
    Ptr<DenseOpticalFlow> tvl1 = createOptFlow_DualTVL1();
    tvl1->set("lambda", params.tvl1Lambda);
    tvl1->set("tau", params.tvl1Tau);
    tvl1->set("theta", params.tvl1Theta);
    tvl1->set("nscales", params.tvl1Nscales);
    tvl1->set("warps", params.tvl1Warpings);
    
    // Calculate optical flow
    Mat flowField;
    tvl1->calc(prevFrame, currFrame, flowField);
    
    // Create flow visualization
    flow = Mat::zeros(prevFrame.size(), CV_8UC3);
    for (int y = 0; y < flowField.rows; y += 10) {
        for (int x = 0; x < flowField.cols; x += 10) {
            Point2f flowVec = flowField.at<Point2f>(y, x);
            double magnitude = sqrt(flowVec.x * flowVec.x + flowVec.y * flowVec.y);
            
            if (magnitude > 1.0) {
                // Draw flow vector
                Point2f endPoint(x + flowVec.x, y + flowVec.y);
                arrowedLine(flow, Point(x, y), endPoint, 
                           Scalar(0, 255, 0), 2, 8, 0, 0.3);
            }
        }
    }
}

/**
 * @brief Function to apply DIS optical flow
 * @param prevFrame Previous frame
 * @param currFrame Current frame
 * @param flow Output flow field
 * @param params Optical flow parameters
 */
void applyDISFlow(const Mat& prevFrame, const Mat& currFrame, Mat& flow, 
                 const OpticalFlowParams& params) {
    // Create DIS optical flow
    Ptr<DenseOpticalFlow> dis = createOptFlow_DIS();
    dis->set("preset", params.disPreset);
    
    // Calculate optical flow
    Mat flowField;
    dis->calc(prevFrame, currFrame, flowField);
    
    // Create flow visualization
    flow = Mat::zeros(prevFrame.size(), CV_8UC3);
    for (int y = 0; y < flowField.rows; y += 10) {
        for (int x = 0; x < flowField.cols; x += 10) {
            Point2f flowVec = flowField.at<Point2f>(y, x);
            double magnitude = sqrt(flowVec.x * flowVec.x + flowVec.y * flowVec.y);
            
            if (magnitude > 1.0) {
                // Draw flow vector
                Point2f endPoint(x + flowVec.x, y + flowVec.y);
                arrowedLine(flow, Point(x, y), endPoint, 
                           Scalar(0, 255, 0), 2, 8, 0, 0.3);
            }
        }
    }
}

/**
 * @brief Function to apply pyramidal Lucas-Kanade optical flow
 * @param prevFrame Previous frame
 * @param currFrame Current frame
 * @param flow Output flow field
 * @param params Optical flow parameters
 */
void applyPyramidalLKFlow(const Mat& prevFrame, const Mat& currFrame, Mat& flow, 
                         const OpticalFlowParams& params) {
    // Detect corners in previous frame
    vector<Point2f> prevCorners, currCorners;
    goodFeaturesToTrack(prevFrame, prevCorners, 100, 0.01, 10);
    
    // Calculate optical flow with pyramids
    vector<uchar> status;
    vector<float> error;
    calcOpticalFlowPyrLK(prevFrame, currFrame, prevCorners, currCorners, 
                        status, error, Size(params.pyrLkWinsize, params.pyrLkWinsize), 
                        params.pyrLkLevels, 
                        TermCriteria(TermCriteria::COUNT + TermCriteria::EPS, 
                                   30, 0.01));
    
    // Create flow visualization
    flow = Mat::zeros(prevFrame.size(), CV_8UC3);
    for (size_t i = 0; i < prevCorners.size(); i++) {
        if (status[i]) {
            Point2f flowVec = currCorners[i] - prevCorners[i];
            double magnitude = sqrt(flowVec.x * flowVec.x + flowVec.y * flowVec.y);
            
            if (magnitude > 1.0) {
                // Draw flow vector
                arrowedLine(flow, prevCorners[i], currCorners[i], 
                           Scalar(0, 255, 0), 2, 8, 0, 0.3);
            }
        }
    }
}

/**
 * @brief Function to apply selected optical flow method
 * @param prevFrame Previous frame
 * @param currFrame Current frame
 * @param flow Output flow field
 * @param method Optical flow method
 * @param params Optical flow parameters
 */
void applyOpticalFlow(const Mat& prevFrame, const Mat& currFrame, Mat& flow, 
                     OpticalFlowMethod method, const OpticalFlowParams& params) {
    switch (method) {
        case LUCAS_KANADE:
            applyLucasKanadeFlow(prevFrame, currFrame, flow, params);
            break;
        case FARNEBACK:
            applyFarnebackFlow(prevFrame, currFrame, flow, params);
            break;
        case TVL1:
            applyTVL1Flow(prevFrame, currFrame, flow, params);
            break;
        case DUAL_TVL1:
            applyTVL1Flow(prevFrame, currFrame, flow, params);
            break;
        case DIS:
            applyDISFlow(prevFrame, currFrame, flow, params);
            break;
        case PYR_LK:
            applyPyramidalLKFlow(prevFrame, currFrame, flow, params);
            break;
    }
}

/**
 * @brief Function to create motion visualization
 * @param prevFrame Previous frame
 * @param currFrame Current frame
 * @param flow Flow field
 * @return Mat Motion visualization
 */
Mat createMotionVisualization(const Mat& prevFrame, const Mat& currFrame, const Mat& flow) {
    // Create 2x2 grid
    Mat visualization = Mat::zeros(prevFrame.rows * 2, prevFrame.cols * 2, CV_8UC3);
    
    // Convert grayscale images to BGR
    Mat prevBGR, currBGR;
    if (prevFrame.channels() == 1) {
        cvtColor(prevFrame, prevBGR, COLOR_GRAY2BGR);
    } else {
        prevBGR = prevFrame;
    }
    
    if (currFrame.channels() == 1) {
        cvtColor(currFrame, currBGR, COLOR_GRAY2BGR);
    } else {
        currBGR = currFrame;
    }
    
    // Place images in grid
    prevBGR.copyTo(visualization(Rect(0, 0, prevFrame.cols, prevFrame.rows)));
    currBGR.copyTo(visualization(Rect(prevFrame.cols, 0, currFrame.cols, currFrame.rows)));
    flow.copyTo(visualization(Rect(0, prevFrame.rows, flow.cols, flow.rows)));
    
    // Add labels
    putText(visualization, "Previous", Point(10, 30), FONT_HERSHEY_SIMPLEX, 0.7, Scalar(0, 255, 0), 2);
    putText(visualization, "Current", Point(prevFrame.cols + 10, 30), FONT_HERSHEY_SIMPLEX, 0.7, Scalar(0, 255, 0), 2);
    putText(visualization, "Optical Flow", Point(10, prevFrame.rows + 30), FONT_HERSHEY_SIMPLEX, 0.7, Scalar(0, 255, 0), 2);
    
    return visualization;
}

/**
 * @brief Function to send motion data to MATLAB
 * @param matlabPtr MATLAB engine pointer
 * @param prevFrame Previous frame
 * @param currFrame Current frame
 * @param flow Flow field
 * @param method Optical flow method
 * @param params Optical flow parameters
 */
void sendMotionToMATLAB(std::unique_ptr<matlab::engine::MATLABEngine>& matlabPtr, 
                       const Mat& prevFrame, const Mat& currFrame, const Mat& flow,
                       OpticalFlowMethod method, const OpticalFlowParams& params) {
    try {
        // Convert BGR to RGB for MATLAB
        Mat rgbPrev, rgbCurr, rgbFlow;
        
        if (prevFrame.channels() == 1) {
            cvtColor(prevFrame, rgbPrev, COLOR_GRAY2RGB);
        } else {
            cvtColor(prevFrame, rgbPrev, COLOR_BGR2RGB);
        }
        
        if (currFrame.channels() == 1) {
            cvtColor(currFrame, rgbCurr, COLOR_GRAY2RGB);
        } else {
            cvtColor(currFrame, rgbCurr, COLOR_BGR2RGB);
        }
        
        if (flow.channels() == 1) {
            cvtColor(flow, rgbFlow, COLOR_GRAY2RGB);
        } else {
            cvtColor(flow, rgbFlow, COLOR_BGR2RGB);
        }
        
        // Create MATLAB arrays
        matlab::data::ArrayFactory factory;
        
        // Previous frame
        auto dimsPrev = factory.createArray<std::size_t>({1, 3}, 
            {static_cast<std::size_t>(rgbPrev.rows), 
             static_cast<std::size_t>(rgbPrev.cols), 
             static_cast<std::size_t>(rgbPrev.channels())});
        auto matlabPrev = factory.createArray<uint8_t>(dimsPrev);
        auto prevPtr = matlabPrev.release();
        memcpy(prevPtr, rgbPrev.data, rgbPrev.total() * rgbPrev.elemSize());
        
        // Current frame
        auto dimsCurr = factory.createArray<std::size_t>({1, 3}, 
            {static_cast<std::size_t>(rgbCurr.rows), 
             static_cast<std::size_t>(rgbCurr.cols), 
             static_cast<std::size_t>(rgbCurr.channels())});
        auto matlabCurr = factory.createArray<uint8_t>(dimsCurr);
        auto currPtr = matlabCurr.release();
        memcpy(currPtr, rgbCurr.data, rgbCurr.total() * rgbCurr.elemSize());
        
        // Flow field
        auto dimsFlow = factory.createArray<std::size_t>({1, 3}, 
            {static_cast<std::size_t>(rgbFlow.rows), 
             static_cast<std::size_t>(rgbFlow.cols), 
             static_cast<std::size_t>(rgbFlow.channels())});
        auto matlabFlow = factory.createArray<uint8_t>(dimsFlow);
        auto flowPtr = matlabFlow.release();
        memcpy(flowPtr, rgbFlow.data, rgbFlow.total() * rgbFlow.elemSize());
        
        // Set variables in MATLAB workspace
        matlabPtr->setVariable(u"prevFrame", matlabPrev);
        matlabPtr->setVariable(u"currFrame", matlabCurr);
        matlabPtr->setVariable(u"flowField", matlabFlow);
        
        // Execute MATLAB commands
        string methodName = getOpticalFlowMethodName(method);
        string matlabCmd = "figure; subplot(1,3,1); imshow(prevFrame); title('Previous Frame'); "
                          "subplot(1,3,2); imshow(currFrame); title('Current Frame'); "
                          "subplot(1,3,3); imshow(flowField); title('" + methodName + " Flow');";
        matlabPtr->eval(matlab::engine::convertUTF8StringToUTF16String(matlabCmd));
        
        // Display motion information
        matlabPtr->eval(u"fprintf('Optical Flow Method: " + matlab::engine::convertUTF8StringToUTF16String(methodName) + "\\n');");
        
        cout << "Motion data sent to MATLAB successfully!" << endl;
        
    } catch (const std::exception& e) {
        cerr << "Error sending motion data to MATLAB: " << e.what() << endl;
    }
}

/**
 * @brief Main function for motion analysis and optical flow
 * @return int Exit status
 */
int main() {
    cout << "=== Motion Analysis and Optical Flow - Intermediate Level 17 ===" << endl;
    cout << "This program demonstrates motion analysis and optical flow techniques." << endl;
    
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
        
        // Initialize optical flow parameters
        OpticalFlowParams params;
        params.lkWindowSize = 15;
        params.lkMaxLevel = 2;
        params.lkCriteriaEpsilon = 0.01;
        params.lkCriteriaMaxCount = 10;
        params.farnebackLevels = 3;
        params.farnebackScale = 0.5;
        params.farnebackWinsize = 15;
        params.farnebackIterations = 3;
        params.farnebackPolyN = 5;
        params.farnebackPolySigma = 1.2;
        params.tvl1Lambda = 0.15;
        params.tvl1Tau = 0.25;
        params.tvl1Theta = 0.3;
        params.tvl1Nscales = 5;
        params.tvl1Warpings = 5;
        params.disPreset = 0.0;
        params.pyrLkLevels = 3;
        params.pyrLkWinsize = 15;
        
        // Initialize optical flow method
        OpticalFlowMethod currentMethod = LUCAS_KANADE;
        
        // Create Mat objects for frame processing
        Mat frame, prevFrame, currFrame, flow, visualization;
        
        cout << "\nStarting camera feed with motion analysis..." << endl;
        cout << "Controls:" << endl;
        cout << "  'q' - Quit" << endl;
        cout << "  '0' - Lucas-Kanade" << endl;
        cout << "  '1' - Farneback" << endl;
        cout << "  '2' - TV-L1" << endl;
        cout << "  '3' - Dual TV-L1" << endl;
        cout << "  '4' - DIS" << endl;
        cout << "  '5' - Pyramidal LK" << endl;
        cout << "  'm' - Send to MATLAB" << endl;
        cout << "  's' - Save current motion" << endl;
        
        // Main capture loop
        while (true) {
            // Capture frame from camera
            cap >> frame;
            
            // Check if frame was captured successfully
            if (frame.empty()) {
                cerr << "Warning: Could not capture frame!" << endl;
                continue;
            }
            
            // Convert to grayscale
            cvtColor(frame, currFrame, COLOR_BGR2GRAY);
            
            // Apply optical flow if we have a previous frame
            if (!prevFrame.empty()) {
                applyOpticalFlow(prevFrame, currFrame, flow, currentMethod, params);
                
                // Create visualization
                visualization = createMotionVisualization(prevFrame, currFrame, flow);
                
                // Display the visualization
                imshow("Motion Analysis and Optical Flow", visualization);
            }
            
            // Store current frame for next iteration
            currFrame.copyTo(prevFrame);
            
            // Handle keyboard input
            char key = waitKey(1) & 0xFF;
            
            if (key == 'q' || key == 27) { // 'q' or ESC to quit
                cout << "Quitting..." << endl;
                break;
            }
            else if (key >= '0' && key <= '5') { // Method selection
                currentMethod = static_cast<OpticalFlowMethod>(key - '0');
                cout << "Selected method: " << getOpticalFlowMethodName(currentMethod) << endl;
            }
            else if (key == 'm') { // Send to MATLAB
                if (!prevFrame.empty()) {
                    sendMotionToMATLAB(matlabPtr, prevFrame, currFrame, flow, currentMethod, params);
                }
            }
            else if (key == 's') { // Save current motion
                if (!prevFrame.empty()) {
                    string filename = "motion_" + getOpticalFlowMethodName(currentMethod) + ".jpg";
                    imwrite(filename, visualization);
                    cout << "Motion visualization saved as: " << filename << endl;
                }
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
 * g++ -std=c++17 camera_intermediate_17.cpp -o camera_intermediate_17 \
 *     `pkg-config --cflags --libs opencv4` \
 *     -I/Applications/MATLAB_R2023b.app/extern/include \
 *     -L/Applications/MATLAB_R2023b.app/bin/maci64 \
 *     -lMatlabDataArray -lMatlabEngine
 * 
 * @brief Usage:
 * 1. Make sure your camera is connected and working
 * 2. Run the executable: ./camera_intermediate_17
 * 3. Use keyboard controls to switch between optical flow methods
 * 4. Press 'm' to send data to MATLAB
 * 5. Press 's' to save current motion visualization
 * 
 * @brief Learning Objectives:
 * - Understand motion analysis principles
 * - Learn optical flow calculation methods
 * - Understand Lucas-Kanade and Farneback algorithms
 * - Learn TV-L1 and DIS optical flow
 * - Understand pyramidal optical flow
 * - Learn MATLAB integration for motion analysis
 * - Understand motion detection applications
 * - Learn to choose appropriate optical flow methods
 */
