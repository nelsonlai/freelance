/**
 * @file camera_advanced_30.cpp
 * @brief Advanced Computer Vision Applications - Advanced Level 30
 * @description This program demonstrates advanced computer vision applications
 *              including medical imaging, robotics, and autonomous systems
 *              with OpenCV and MATLAB integration.
 * @author Educational C++ MATLAB Integration Project
 * @date 2024
 * @version 1.0
 */

#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/features2d.hpp>
#include <opencv2/calib3d.hpp>
#include <iostream>
#include <matlab/engine.hpp>
#include <memory>
#include <vector>
#include <string>

using namespace cv;
using namespace std;

/**
 * @brief Enumeration for different application types
 */
enum ApplicationType {
    MEDICAL_IMAGING = 0,
    ROBOTICS = 1,
    AUTONOMOUS_SYSTEMS = 2,
    SURVEILLANCE = 3,
    QUALITY_CONTROL = 4,
    AGRICULTURE = 5,
    TRANSPORTATION = 6,
    ENTERTAINMENT = 7,
    EDUCATION = 8,
    RESEARCH = 9
};

/**
 * @brief Function to get application type name
 * @param type Application type
 * @return string Type name
 */
string getApplicationTypeName(ApplicationType type) {
    switch (type) {
        case MEDICAL_IMAGING: return "Medical Imaging";
        case ROBOTICS: return "Robotics";
        case AUTONOMOUS_SYSTEMS: return "Autonomous Systems";
        case SURVEILLANCE: return "Surveillance";
        case QUALITY_CONTROL: return "Quality Control";
        case AGRICULTURE: return "Agriculture";
        case TRANSPORTATION: return "Transportation";
        case ENTERTAINMENT: return "Entertainment";
        case EDUCATION: return "Education";
        case RESEARCH: return "Research";
        default: return "Unknown";
    }
}

/**
 * @brief Function to apply medical imaging processing
 * @param frame Input frame
 * @param processedFrame Output processed frame
 * @return bool Success status
 */
bool applyMedicalImagingProcessing(const Mat& frame, Mat& processedFrame) {
    try {
        // Convert to grayscale
        Mat gray;
        cvtColor(frame, gray, COLOR_BGR2GRAY);
        
        // Apply medical imaging specific processing
        Mat enhanced;
        equalizeHist(gray, enhanced);
        
        // Apply Gaussian blur for noise reduction
        GaussianBlur(enhanced, enhanced, Size(5, 5), 0);
        
        // Apply edge detection
        Mat edges;
        Canny(enhanced, edges, 50, 150);
        
        // Combine original and processed
        Mat combined;
        cvtColor(enhanced, combined, COLOR_GRAY2BGR);
        
        processedFrame = combined;
        return true;
    } catch (const std::exception& e) {
        cerr << "Error in medical imaging processing: " << e.what() << endl;
        return false;
    }
}

/**
 * @brief Function to apply robotics processing
 * @param frame Input frame
 * @param processedFrame Output processed frame
 * @return bool Success status
 */
bool applyRoboticsProcessing(const Mat& frame, Mat& processedFrame) {
    try {
        // Convert to grayscale
        Mat gray;
        cvtColor(frame, gray, COLOR_BGR2GRAY);
        
        // Apply robotics specific processing
        Mat binary;
        threshold(gray, binary, 127, 255, THRESH_BINARY);
        
        // Find contours
        vector<vector<Point>> contours;
        findContours(binary, contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
        
        // Draw contours
        Mat result = frame.clone();
        drawContours(result, contours, -1, Scalar(0, 255, 0), 2);
        
        processedFrame = result;
        return true;
    } catch (const std::exception& e) {
        cerr << "Error in robotics processing: " << e.what() << endl;
        return false;
    }
}

/**
 * @brief Function to apply autonomous systems processing
 * @param frame Input frame
 * @param processedFrame Output processed frame
 * @return bool Success status
 */
bool applyAutonomousSystemsProcessing(const Mat& frame, Mat& processedFrame) {
    try {
        // Convert to grayscale
        Mat gray;
        cvtColor(frame, gray, COLOR_BGR2GRAY);
        
        // Apply autonomous systems specific processing
        Mat edges;
        Canny(gray, edges, 50, 150);
        
        // Apply Hough line detection
        vector<Vec4i> lines;
        HoughLinesP(edges, lines, 1, CV_PI/180, 50, 50, 10);
        
        // Draw lines
        Mat result = frame.clone();
        for (size_t i = 0; i < lines.size(); i++) {
            Vec4i l = lines[i];
            line(result, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(0, 0, 255), 2);
        }
        
        processedFrame = result;
        return true;
    } catch (const std::exception& e) {
        cerr << "Error in autonomous systems processing: " << e.what() << endl;
        return false;
    }
}

/**
 * @brief Function to apply surveillance processing
 * @param frame Input frame
 * @param processedFrame Output processed frame
 * @return bool Success status
 */
bool applySurveillanceProcessing(const Mat& frame, Mat& processedFrame) {
    try {
        // Convert to grayscale
        Mat gray;
        cvtColor(frame, gray, COLOR_BGR2GRAY);
        
        // Apply surveillance specific processing
        Mat background;
        GaussianBlur(gray, background, Size(21, 21), 0);
        
        // Calculate difference
        Mat diff;
        absdiff(gray, background, diff);
        
        // Threshold
        Mat thresh;
        threshold(diff, thresh, 30, 255, THRESH_BINARY);
        
        // Find contours
        vector<vector<Point>> contours;
        findContours(thresh, contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
        
        // Draw contours
        Mat result = frame.clone();
        drawContours(result, contours, -1, Scalar(0, 255, 0), 2);
        
        processedFrame = result;
        return true;
    } catch (const std::exception& e) {
        cerr << "Error in surveillance processing: " << e.what() << endl;
        return false;
    }
}

/**
 * @brief Function to apply quality control processing
 * @param frame Input frame
 * @param processedFrame Output processed frame
 * @return bool Success status
 */
bool applyQualityControlProcessing(const Mat& frame, Mat& processedFrame) {
    try {
        // Convert to grayscale
        Mat gray;
        cvtColor(frame, gray, COLOR_BGR2GRAY);
        
        // Apply quality control specific processing
        Mat edges;
        Canny(gray, edges, 50, 150);
        
        // Apply morphological operations
        Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3));
        Mat morphed;
        morphologyEx(edges, morphed, MORPH_CLOSE, kernel);
        
        // Find contours
        vector<vector<Point>> contours;
        findContours(morphed, contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
        
        // Draw contours
        Mat result = frame.clone();
        drawContours(result, contours, -1, Scalar(255, 0, 0), 2);
        
        processedFrame = result;
        return true;
    } catch (const std::exception& e) {
        cerr << "Error in quality control processing: " << e.what() << endl;
        return false;
    }
}

/**
 * @brief Function to apply application-specific processing
 * @param frame Input frame
 * @param processedFrame Output processed frame
 * @param type Application type
 * @return bool Success status
 */
bool applyApplicationProcessing(const Mat& frame, Mat& processedFrame, ApplicationType type) {
    switch (type) {
        case MEDICAL_IMAGING:
            return applyMedicalImagingProcessing(frame, processedFrame);
        case ROBOTICS:
            return applyRoboticsProcessing(frame, processedFrame);
        case AUTONOMOUS_SYSTEMS:
            return applyAutonomousSystemsProcessing(frame, processedFrame);
        case SURVEILLANCE:
            return applySurveillanceProcessing(frame, processedFrame);
        case QUALITY_CONTROL:
            return applyQualityControlProcessing(frame, processedFrame);
        default:
            processedFrame = frame.clone();
            return true;
    }
}

/**
 * @brief Function to send application data to MATLAB
 * @param matlabPtr MATLAB engine pointer
 * @param frame Input frame
 * @param processedFrame Processed frame
 * @param type Application type
 */
void sendApplicationDataToMATLAB(std::unique_ptr<matlab::engine::MATLABEngine>& matlabPtr, 
                                const Mat& frame, const Mat& processedFrame, ApplicationType type) {
    try {
        // Convert BGR to RGB for MATLAB
        Mat rgbFrame, rgbProcessed;
        cvtColor(frame, rgbFrame, COLOR_BGR2RGB);
        cvtColor(processedFrame, rgbProcessed, COLOR_BGR2RGB);
        
        // Create MATLAB arrays
        matlab::data::ArrayFactory factory;
        
        // Original frame
        auto dimsFrame = factory.createArray<std::size_t>({1, 3}, 
            {static_cast<std::size_t>(rgbFrame.rows), 
             static_cast<std::size_t>(rgbFrame.cols), 
             static_cast<std::size_t>(rgbFrame.channels())});
        auto matlabFrame = factory.createArray<uint8_t>(dimsFrame);
        auto framePtr = matlabFrame.release();
        memcpy(framePtr, rgbFrame.data, rgbFrame.total() * rgbFrame.elemSize());
        
        // Processed frame
        auto dimsProcessed = factory.createArray<std::size_t>({1, 3}, 
            {static_cast<std::size_t>(rgbProcessed.rows), 
             static_cast<std::size_t>(rgbProcessed.cols), 
             static_cast<std::size_t>(rgbProcessed.channels())});
        auto matlabProcessed = factory.createArray<uint8_t>(dimsProcessed);
        auto processedPtr = matlabProcessed.release();
        memcpy(processedPtr, rgbProcessed.data, rgbProcessed.total() * rgbProcessed.elemSize());
        
        // Set variables in MATLAB workspace
        matlabPtr->setVariable(u"originalFrame", matlabFrame);
        matlabPtr->setVariable(u"processedFrame", matlabProcessed);
        
        // Execute MATLAB commands
        string applicationName = getApplicationTypeName(type);
        
        string matlabCmd = "figure; subplot(1,2,1); imshow(originalFrame); title('Original'); "
                          "subplot(1,2,2); imshow(processedFrame); title('" + applicationName + " Processing');";
        
        matlabPtr->eval(matlab::engine::convertUTF8StringToUTF16String(matlabCmd));
        
        // Display application information
        matlabPtr->eval(u"fprintf('Application Type: " + matlab::engine::convertUTF8StringToUTF16String(applicationName) + "\\n');");
        
        cout << "Application data sent to MATLAB successfully!" << endl;
        
    } catch (const std::exception& e) {
        cerr << "Error sending application data to MATLAB: " << e.what() << endl;
    }
}

/**
 * @brief Main function for advanced computer vision applications
 * @return int Exit status
 */
int main() {
    cout << "=== Advanced Computer Vision Applications - Advanced Level 30 ===" << endl;
    cout << "This program demonstrates advanced computer vision applications." << endl;
    
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
        
        // Initialize application type
        ApplicationType currentType = MEDICAL_IMAGING;
        
        // Create Mat objects for frame processing
        Mat frame, processedFrame, visualization;
        
        cout << "\nStarting computer vision applications..." << endl;
        cout << "Controls:" << endl;
        cout << "  'q' - Quit" << endl;
        cout << "  '0' - Medical Imaging" << endl;
        cout << "  '1' - Robotics" << endl;
        cout << "  '2' - Autonomous Systems" << endl;
        cout << "  '3' - Surveillance" << endl;
        cout << "  '4' - Quality Control" << endl;
        cout << "  '5' - Agriculture" << endl;
        cout << "  '6' - Transportation" << endl;
        cout << "  '7' - Entertainment" << endl;
        cout << "  '8' - Education" << endl;
        cout << "  '9' - Research" << endl;
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
            
            // Apply application-specific processing
            if (applyApplicationProcessing(frame, processedFrame, currentType)) {
                visualization = processedFrame.clone();
            } else {
                visualization = frame.clone();
            }
            
            // Draw application type
            string typeText = "Application: " + getApplicationTypeName(currentType);
            putText(visualization, typeText, Point(10, 30), FONT_HERSHEY_SIMPLEX, 0.7, Scalar(0, 255, 0), 2);
            
            // Display the visualization
            imshow("Advanced Computer Vision Applications", visualization);
            
            // Handle keyboard input
            char key = waitKey(1) & 0xFF;
            
            if (key == 'q' || key == 27) {
                cout << "Quitting..." << endl;
                break;
            }
            else if (key >= '0' && key <= '9') {
                currentType = static_cast<ApplicationType>(key - '0');
                cout << "Selected application: " << getApplicationTypeName(currentType) << endl;
            }
            else if (key == 'm') {
                sendApplicationDataToMATLAB(matlabPtr, frame, processedFrame, currentType);
            }
            else if (key == 's') {
                string filename = "application_" + getApplicationTypeName(currentType) + "_" + to_string(time(nullptr)) + ".jpg";
                imwrite(filename, visualization);
                cout << "Application frame saved as: " << filename << endl;
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
 * g++ -std=c++17 camera_advanced_30.cpp -o camera_advanced_30 \
 *     `pkg-config --cflags --libs opencv4` \
 *     -I/Applications/MATLAB_R2023b.app/extern/include \
 *     -L/Applications/MATLAB_R2023b.app/bin/maci64 \
 *     -lMatlabDataArray -lMatlabEngine
 * 
 * @brief Usage:
 * 1. Make sure your camera is connected and working
 * 2. Run the executable: ./camera_advanced_30
 * 3. Use keyboard controls to switch between applications
 * 4. Press 'm' to send data to MATLAB
 * 5. Press 's' to save current frame
 * 
 * @brief Learning Objectives:
 * - Understand advanced computer vision applications
 * - Learn medical imaging processing
 * - Learn robotics applications
 * - Learn autonomous systems
 * - Learn surveillance systems
 * - Learn quality control applications
 * - Learn MATLAB integration for application analysis
 * - Understand real-world computer vision applications
 */
