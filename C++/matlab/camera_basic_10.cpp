/**
 * @file camera_basic_10.cpp
 * @brief Basic Thresholding Operations - Beginner Level 10
 * @description This program demonstrates basic thresholding operations like
 *              binary, adaptive, and Otsu thresholding using OpenCV and MATLAB
 *              integration for real-time image processing.
 * @author Educational C++ MATLAB Integration Project
 * @date 2024
 * @version 1.0
 */

#include <opencv2/opencv.hpp>
#include <iostream>
#include <matlab/engine.hpp>
#include <memory>
#include <vector>

using namespace cv;
using namespace std;

/**
 * @brief Enumeration for different thresholding types
 */
enum ThresholdingType {
    ORIGINAL = 0,
    BINARY = 1,
    BINARY_INV = 2,
    TRUNC = 3,
    TOZERO = 4,
    TOZERO_INV = 5,
    ADAPTIVE_MEAN = 6,
    ADAPTIVE_GAUSSIAN = 7,
    OTSU = 8,
    TRIANGLE = 9
};

/**
 * @brief Structure to hold thresholding parameters
 */
struct ThresholdingParams {
    double thresholdValue;
    double maxValue;
    int adaptiveMethod;
    int thresholdType;
    int blockSize;
    double constant;
    int otsuThreshold;
    int triangleThreshold;
};

/**
 * @brief Function to get thresholding type name
 * @param type Thresholding type
 * @return string Thresholding type name
 */
string getThresholdingTypeName(ThresholdingType type) {
    switch (type) {
        case ORIGINAL: return "Original";
        case BINARY: return "Binary";
        case BINARY_INV: return "Binary Inverse";
        case TRUNC: return "Truncate";
        case TOZERO: return "To Zero";
        case TOZERO_INV: return "To Zero Inverse";
        case ADAPTIVE_MEAN: return "Adaptive Mean";
        case ADAPTIVE_GAUSSIAN: return "Adaptive Gaussian";
        case OTSU: return "Otsu";
        case TRIANGLE: return "Triangle";
        default: return "Unknown";
    }
}

/**
 * @brief Function to apply binary thresholding
 * @param src Input image
 * @param dst Output image
 * @param params Thresholding parameters
 */
void applyBinaryThreshold(const Mat& src, Mat& dst, const ThresholdingParams& params) {
    threshold(src, dst, params.thresholdValue, params.maxValue, THRESH_BINARY);
}

/**
 * @brief Function to apply binary inverse thresholding
 * @param src Input image
 * @param dst Output image
 * @param params Thresholding parameters
 */
void applyBinaryInvThreshold(const Mat& src, Mat& dst, const ThresholdingParams& params) {
    threshold(src, dst, params.thresholdValue, params.maxValue, THRESH_BINARY_INV);
}

/**
 * @brief Function to apply truncate thresholding
 * @param src Input image
 * @param dst Output image
 * @param params Thresholding parameters
 */
void applyTruncThreshold(const Mat& src, Mat& dst, const ThresholdingParams& params) {
    threshold(src, dst, params.thresholdValue, params.maxValue, THRESH_TRUNC);
}

/**
 * @brief Function to apply to zero thresholding
 * @param src Input image
 * @param dst Output image
 * @param params Thresholding parameters
 */
void applyToZeroThreshold(const Mat& src, Mat& dst, const ThresholdingParams& params) {
    threshold(src, dst, params.thresholdValue, params.maxValue, THRESH_TOZERO);
}

/**
 * @brief Function to apply to zero inverse thresholding
 * @param src Input image
 * @param dst Output image
 * @param params Thresholding parameters
 */
void applyToZeroInvThreshold(const Mat& src, Mat& dst, const ThresholdingParams& params) {
    threshold(src, dst, params.thresholdValue, params.maxValue, THRESH_TOZERO_INV);
}

/**
 * @brief Function to apply adaptive mean thresholding
 * @param src Input image
 * @param dst Output image
 * @param params Thresholding parameters
 */
void applyAdaptiveMeanThreshold(const Mat& src, Mat& dst, const ThresholdingParams& params) {
    adaptiveThreshold(src, dst, params.maxValue, ADAPTIVE_THRESH_MEAN_C, 
                     THRESH_BINARY, params.blockSize, params.constant);
}

/**
 * @brief Function to apply adaptive Gaussian thresholding
 * @param src Input image
 * @param dst Output image
 * @param params Thresholding parameters
 */
void applyAdaptiveGaussianThreshold(const Mat& src, Mat& dst, const ThresholdingParams& params) {
    adaptiveThreshold(src, dst, params.maxValue, ADAPTIVE_THRESH_GAUSSIAN_C, 
                     THRESH_BINARY, params.blockSize, params.constant);
}

/**
 * @brief Function to apply Otsu thresholding
 * @param src Input image
 * @param dst Output image
 * @param params Thresholding parameters
 */
void applyOtsuThreshold(const Mat& src, Mat& dst, const ThresholdingParams& params) {
    threshold(src, dst, params.thresholdValue, params.maxValue, THRESH_BINARY + THRESH_OTSU);
}

/**
 * @brief Function to apply triangle thresholding
 * @param src Input image
 * @param dst Output image
 * @param params Thresholding parameters
 */
void applyTriangleThreshold(const Mat& src, Mat& dst, const ThresholdingParams& params) {
    threshold(src, dst, params.thresholdValue, params.maxValue, THRESH_BINARY + THRESH_TRIANGLE);
}

/**
 * @brief Function to apply selected thresholding operation
 * @param src Input image
 * @param dst Output image
 * @param type Thresholding type
 * @param params Thresholding parameters
 */
void applyThresholding(const Mat& src, Mat& dst, ThresholdingType type, const ThresholdingParams& params) {
    switch (type) {
        case ORIGINAL:
            src.copyTo(dst);
            break;
        case BINARY:
            applyBinaryThreshold(src, dst, params);
            break;
        case BINARY_INV:
            applyBinaryInvThreshold(src, dst, params);
            break;
        case TRUNC:
            applyTruncThreshold(src, dst, params);
            break;
        case TOZERO:
            applyToZeroThreshold(src, dst, params);
            break;
        case TOZERO_INV:
            applyToZeroInvThreshold(src, dst, params);
            break;
        case ADAPTIVE_MEAN:
            applyAdaptiveMeanThreshold(src, dst, params);
            break;
        case ADAPTIVE_GAUSSIAN:
            applyAdaptiveGaussianThreshold(src, dst, params);
            break;
        case OTSU:
            applyOtsuThreshold(src, dst, params);
            break;
        case TRIANGLE:
            applyTriangleThreshold(src, dst, params);
            break;
    }
}

/**
 * @brief Function to create thresholding visualization
 * @param src Original image
 * @param dst Thresholded image
 * @param type Thresholding type
 * @param params Thresholding parameters
 * @return Mat Visualization of thresholding parameters
 */
Mat createThresholdingVisualization(const Mat& src, const Mat& dst, ThresholdingType type, 
                                   const ThresholdingParams& params) {
    Mat visualization = Mat::zeros(200, 400, CV_8UC3);
    
    // Draw threshold line
    int thresholdLine = static_cast<int>(params.thresholdValue * 200 / 255);
    line(visualization, Point(50, thresholdLine), Point(350, thresholdLine), Scalar(0, 255, 0), 2);
    
    // Add labels
    string typeName = getThresholdingTypeName(type);
    putText(visualization, typeName, Point(10, 30), 
           FONT_HERSHEY_SIMPLEX, 0.6, Scalar(0, 255, 0), 2);
    
    stringstream ss;
    ss << "Threshold: " << fixed << setprecision(1) << params.thresholdValue;
    putText(visualization, ss.str(), Point(10, 60), 
           FONT_HERSHEY_SIMPLEX, 0.5, Scalar(255, 255, 255), 1);
    
    ss.str("");
    ss << "Max Value: " << params.maxValue;
    putText(visualization, ss.str(), Point(10, 80), 
           FONT_HERSHEY_SIMPLEX, 0.5, Scalar(255, 255, 255), 1);
    
    if (type == ADAPTIVE_MEAN || type == ADAPTIVE_GAUSSIAN) {
        ss.str("");
        ss << "Block Size: " << params.blockSize;
        putText(visualization, ss.str(), Point(10, 100), 
               FONT_HERSHEY_SIMPLEX, 0.5, Scalar(255, 255, 255), 1);
        
        ss.str("");
        ss << "Constant: " << params.constant;
        putText(visualization, ss.str(), Point(10, 120), 
               FONT_HERSHEY_SIMPLEX, 0.5, Scalar(255, 255, 255), 1);
    }
    
    return visualization;
}

/**
 * @brief Function to send thresholding data to MATLAB
 * @param matlabPtr MATLAB engine pointer
 * @param src Original image
 * @param dst Thresholded image
 * @param type Thresholding type
 * @param params Thresholding parameters
 */
void sendThresholdingToMATLAB(std::unique_ptr<matlab::engine::MATLABEngine>& matlabPtr, 
                             const Mat& src, const Mat& dst, ThresholdingType type, 
                             const ThresholdingParams& params) {
    try {
        // Convert BGR to RGB for MATLAB
        Mat rgbSrc, rgbDst;
        cvtColor(src, rgbSrc, COLOR_BGR2RGB);
        cvtColor(dst, rgbDst, COLOR_BGR2RGB);
        
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
        
        // Thresholded image
        auto dimsDst = factory.createArray<std::size_t>({1, 3}, 
            {static_cast<std::size_t>(rgbDst.rows), 
             static_cast<std::size_t>(rgbDst.cols), 
             static_cast<std::size_t>(rgbDst.channels())});
        auto matlabDst = factory.createArray<uint8_t>(dimsDst);
        auto dstPtr = matlabDst.release();
        memcpy(dstPtr, rgbDst.data, rgbDst.total() * rgbDst.elemSize());
        
        // Set variables in MATLAB workspace
        matlabPtr->setVariable(u"originalImage", matlabSrc);
        matlabPtr->setVariable(u"thresholdedImage", matlabDst);
        
        // Execute MATLAB commands
        string typeName = getThresholdingTypeName(type);
        string matlabCmd = "figure; subplot(1,2,1); imshow(originalImage); title('Original'); "
                          "subplot(1,2,2); imshow(thresholdedImage); title('" + typeName + "');";
        matlabPtr->eval(matlab::engine::convertUTF8StringToUTF16String(matlabCmd));
        
        // Display thresholding information
        matlabPtr->eval(u"fprintf('Thresholding Type: " + matlab::engine::convertUTF8StringToUTF16String(typeName) + "\\n');");
        matlabPtr->eval(u"fprintf('Threshold Value: %.2f\\n', " + to_string(params.thresholdValue) + u");");
        matlabPtr->eval(u"fprintf('Max Value: %.2f\\n', " + to_string(params.maxValue) + u");");
        
        if (type == ADAPTIVE_MEAN || type == ADAPTIVE_GAUSSIAN) {
            matlabPtr->eval(u"fprintf('Block Size: %d\\n', " + to_string(params.blockSize) + u");");
            matlabPtr->eval(u"fprintf('Constant: %.2f\\n', " + to_string(params.constant) + u");");
        }
        
        cout << "Thresholding data sent to MATLAB successfully!" << endl;
        
    } catch (const std::exception& e) {
        cerr << "Error sending thresholding data to MATLAB: " << e.what() << endl;
    }
}

/**
 * @brief Main function for basic thresholding operations
 * @return int Exit status
 */
int main() {
    cout << "=== Basic Thresholding Operations - Beginner Level 10 ===" << endl;
    cout << "This program demonstrates basic thresholding operations." << endl;
    
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
        
        // Initialize thresholding parameters
        ThresholdingParams params;
        params.thresholdValue = 127.0;
        params.maxValue = 255.0;
        params.adaptiveMethod = ADAPTIVE_THRESH_MEAN_C;
        params.thresholdType = THRESH_BINARY;
        params.blockSize = 11;
        params.constant = 2.0;
        params.otsuThreshold = 0;
        params.triangleThreshold = 0;
        
        // Initialize thresholding type
        ThresholdingType currentType = ORIGINAL;
        
        // Create Mat objects for frame processing
        Mat frame, grayFrame, thresholdedFrame, displayFrame, visualization;
        
        cout << "\nStarting camera feed with thresholding operations..." << endl;
        cout << "Controls:" << endl;
        cout << "  'q' - Quit" << endl;
        cout << "  '0' - Original" << endl;
        cout << "  '1' - Binary" << endl;
        cout << "  '2' - Binary Inverse" << endl;
        cout << "  '3' - Truncate" << endl;
        cout << "  '4' - To Zero" << endl;
        cout << "  '5' - To Zero Inverse" << endl;
        cout << "  '6' - Adaptive Mean" << endl;
        cout << "  '7' - Adaptive Gaussian" << endl;
        cout << "  '8' - Otsu" << endl;
        cout << "  '9' - Triangle" << endl;
        cout << "  '+' - Increase threshold" << endl;
        cout << "  '-' - Decrease threshold" << endl;
        cout << "  'b' - Increase block size" << endl;
        cout << "  'B' - Decrease block size" << endl;
        cout << "  'c' - Increase constant" << endl;
        cout << "  'C' - Decrease constant" << endl;
        cout << "  'v' - Show visualization" << endl;
        cout << "  'm' - Send to MATLAB" << endl;
        cout << "  's' - Save current thresholding" << endl;
        
        bool showVisualization = false;
        
        // Main capture loop
        while (true) {
            // Capture frame from camera
            cap >> frame;
            
            // Check if frame was captured successfully
            if (frame.empty()) {
                cerr << "Warning: Could not capture frame!" << endl;
                continue;
            }
            
            // Convert to grayscale for thresholding
            cvtColor(frame, grayFrame, COLOR_BGR2GRAY);
            
            // Apply selected thresholding operation
            applyThresholding(grayFrame, thresholdedFrame, currentType, params);
            
            // Convert back to BGR for display
            cvtColor(thresholdedFrame, displayFrame, COLOR_GRAY2BGR);
            
            // Create visualization
            visualization = createThresholdingVisualization(grayFrame, thresholdedFrame, currentType, params);
            
            // Create side-by-side comparison
            Mat comparison;
            hconcat(frame, displayFrame, comparison);
            
            // Add labels
            string typeName = getThresholdingTypeName(currentType);
            putText(comparison, "Original", Point(10, 30), 
                   FONT_HERSHEY_SIMPLEX, 0.7, Scalar(0, 255, 0), 2);
            putText(comparison, typeName, Point(frame.cols + 10, 30), 
                   FONT_HERSHEY_SIMPLEX, 0.7, Scalar(0, 255, 0), 2);
            
            // Add parameter information
            stringstream ss;
            ss << "Threshold: " << fixed << setprecision(1) << params.thresholdValue;
            putText(comparison, ss.str(), Point(10, 60), 
                   FONT_HERSHEY_SIMPLEX, 0.5, Scalar(255, 255, 255), 1);
            
            if (currentType == ADAPTIVE_MEAN || currentType == ADAPTIVE_GAUSSIAN) {
                ss.str("");
                ss << "Block Size: " << params.blockSize;
                putText(comparison, ss.str(), Point(10, 80), 
                       FONT_HERSHEY_SIMPLEX, 0.5, Scalar(255, 255, 255), 1);
                
                ss.str("");
                ss << "Constant: " << params.constant;
                putText(comparison, ss.str(), Point(10, 100), 
                       FONT_HERSHEY_SIMPLEX, 0.5, Scalar(255, 255, 255), 1);
            }
            
            // Display the comparison
            imshow("Basic Thresholding Operations", comparison);
            
            if (showVisualization) {
                imshow("Thresholding Visualization", visualization);
            }
            
            // Handle keyboard input
            char key = waitKey(1) & 0xFF;
            
            if (key == 'q' || key == 27) { // 'q' or ESC to quit
                cout << "Quitting..." << endl;
                break;
            }
            else if (key >= '0' && key <= '9') { // Thresholding type selection
                currentType = static_cast<ThresholdingType>(key - '0');
                cout << "Selected thresholding type: " << getThresholdingTypeName(currentType) << endl;
            }
            else if (key == '+') { // Increase threshold
                params.thresholdValue = min(255.0, params.thresholdValue + 5.0);
                cout << "Threshold increased to: " << params.thresholdValue << endl;
            }
            else if (key == '-') { // Decrease threshold
                params.thresholdValue = max(0.0, params.thresholdValue - 5.0);
                cout << "Threshold decreased to: " << params.thresholdValue << endl;
            }
            else if (key == 'b') { // Increase block size
                params.blockSize = min(31, params.blockSize + 2);
                cout << "Block size increased to: " << params.blockSize << endl;
            }
            else if (key == 'B') { // Decrease block size
                params.blockSize = max(3, params.blockSize - 2);
                cout << "Block size decreased to: " << params.blockSize << endl;
            }
            else if (key == 'c') { // Increase constant
                params.constant = min(20.0, params.constant + 1.0);
                cout << "Constant increased to: " << params.constant << endl;
            }
            else if (key == 'C') { // Decrease constant
                params.constant = max(-20.0, params.constant - 1.0);
                cout << "Constant decreased to: " << params.constant << endl;
            }
            else if (key == 'v') { // Toggle visualization
                showVisualization = !showVisualization;
                if (!showVisualization) {
                    destroyWindow("Thresholding Visualization");
                }
                cout << "Visualization: " << (showVisualization ? "ON" : "OFF") << endl;
            }
            else if (key == 'm') { // Send to MATLAB
                sendThresholdingToMATLAB(matlabPtr, frame, displayFrame, currentType, params);
            }
            else if (key == 's') { // Save current thresholding
                string filename = "thresholding_" + typeName + ".jpg";
                imwrite(filename, displayFrame);
                cout << "Thresholding saved as: " << filename << endl;
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
 * g++ -std=c++17 camera_basic_10.cpp -o camera_basic_10 \
 *     `pkg-config --cflags --libs opencv4` \
 *     -I/Applications/MATLAB_R2023b.app/extern/include \
 *     -L/Applications/MATLAB_R2023b.app/bin/maci64 \
 *     -lMatlabDataArray -lMatlabEngine
 * 
 * @brief Usage:
 * 1. Make sure your camera is connected and working
 * 2. Run the executable: ./camera_basic_10
 * 3. Use keyboard controls to switch between thresholding types
 * 4. Adjust threshold value with '+'/'-' keys
 * 5. Adjust block size and constant for adaptive methods
 * 6. Press 'v' to show visualization
 * 7. Press 'm' to send data to MATLAB
 * 8. Press 's' to save current thresholding
 * 
 * @brief Learning Objectives:
 * - Understand basic thresholding operations
 * - Learn binary, adaptive, and Otsu thresholding
 * - Understand threshold value effects
 * - Learn adaptive thresholding parameters
 * - Understand thresholding visualization
 * - Learn MATLAB integration for thresholding analysis
 * - Understand thresholding applications in computer vision
 * - Learn to choose appropriate thresholding methods
 */
