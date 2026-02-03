/**
 * @file camera_basic_09.cpp
 * @brief Basic Morphological Operations - Beginner Level 9
 * @description This program demonstrates basic morphological operations like
 *              erosion, dilation, opening, closing, and gradient using OpenCV
 *              and MATLAB integration for real-time image processing.
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
 * @brief Enumeration for different morphological operations
 */
enum MorphologicalOperation {
    ORIGINAL = 0,
    EROSION = 1,
    DILATION = 2,
    OPENING = 3,
    CLOSING = 4,
    GRADIENT = 5,
    TOPHAT = 6,
    BLACKHAT = 7,
    HIT_MISS = 8
};

/**
 * @brief Structure to hold morphological parameters
 */
struct MorphologicalParams {
    int kernelSize;
    int iterations;
    int morphType;
    int elementType;
    Point anchor;
};

/**
 * @brief Function to get morphological operation name
 * @param operation Morphological operation type
 * @return string Operation name
 */
string getMorphologicalOperationName(MorphologicalOperation operation) {
    switch (operation) {
        case ORIGINAL: return "Original";
        case EROSION: return "Erosion";
        case DILATION: return "Dilation";
        case OPENING: return "Opening";
        case CLOSING: return "Closing";
        case GRADIENT: return "Gradient";
        case TOPHAT: return "Top Hat";
        case BLACKHAT: return "Black Hat";
        case HIT_MISS: return "Hit or Miss";
        default: return "Unknown";
    }
}

/**
 * @brief Function to create morphological kernel
 * @param params Morphological parameters
 * @return Mat Morphological kernel
 */
Mat createMorphologicalKernel(const MorphologicalParams& params) {
    int elementType;
    switch (params.elementType) {
        case 0: elementType = MORPH_RECT; break;
        case 1: elementType = MORPH_ELLIPSE; break;
        case 2: elementType = MORPH_CROSS; break;
        default: elementType = MORPH_RECT; break;
    }
    
    return getStructuringElement(elementType, 
                                Size(params.kernelSize, params.kernelSize), 
                                params.anchor);
}

/**
 * @brief Function to apply erosion operation
 * @param src Input image
 * @param dst Output image
 * @param params Morphological parameters
 */
void applyErosion(const Mat& src, Mat& dst, const MorphologicalParams& params) {
    Mat kernel = createMorphologicalKernel(params);
    erode(src, dst, kernel, params.anchor, params.iterations);
}

/**
 * @brief Function to apply dilation operation
 * @param src Input image
 * @param dst Output image
 * @param params Morphological parameters
 */
void applyDilation(const Mat& src, Mat& dst, const MorphologicalParams& params) {
    Mat kernel = createMorphologicalKernel(params);
    dilate(src, dst, kernel, params.anchor, params.iterations);
}

/**
 * @brief Function to apply opening operation
 * @param src Input image
 * @param dst Output image
 * @param params Morphological parameters
 */
void applyOpening(const Mat& src, Mat& dst, const MorphologicalParams& params) {
    Mat kernel = createMorphologicalKernel(params);
    morphologyEx(src, dst, MORPH_OPEN, kernel, params.anchor, params.iterations);
}

/**
 * @brief Function to apply closing operation
 * @param src Input image
 * @param dst Output image
 * @param params Morphological parameters
 */
void applyClosing(const Mat& src, Mat& dst, const MorphologicalParams& params) {
    Mat kernel = createMorphologicalKernel(params);
    morphologyEx(src, dst, MORPH_CLOSE, kernel, params.anchor, params.iterations);
}

/**
 * @brief Function to apply gradient operation
 * @param src Input image
 * @param dst Output image
 * @param params Morphological parameters
 */
void applyGradient(const Mat& src, Mat& dst, const MorphologicalParams& params) {
    Mat kernel = createMorphologicalKernel(params);
    morphologyEx(src, dst, MORPH_GRADIENT, kernel, params.anchor, params.iterations);
}

/**
 * @brief Function to apply top hat operation
 * @param src Input image
 * @param dst Output image
 * @param params Morphological parameters
 */
void applyTopHat(const Mat& src, Mat& dst, const MorphologicalParams& params) {
    Mat kernel = createMorphologicalKernel(params);
    morphologyEx(src, dst, MORPH_TOPHAT, kernel, params.anchor, params.iterations);
}

/**
 * @brief Function to apply black hat operation
 * @param src Input image
 * @param dst Output image
 * @param params Morphological parameters
 */
void applyBlackHat(const Mat& src, Mat& dst, const MorphologicalParams& params) {
    Mat kernel = createMorphologicalKernel(params);
    morphologyEx(src, dst, MORPH_BLACKHAT, kernel, params.anchor, params.iterations);
}

/**
 * @brief Function to apply hit or miss operation
 * @param src Input image
 * @param dst Output image
 * @param params Morphological parameters
 */
void applyHitMiss(const Mat& src, Mat& dst, const MorphologicalParams& params) {
    Mat kernel = createMorphologicalKernel(params);
    morphologyEx(src, dst, MORPH_HITMISS, kernel, params.anchor, params.iterations);
}

/**
 * @brief Function to apply selected morphological operation
 * @param src Input image
 * @param dst Output image
 * @param operation Morphological operation type
 * @param params Morphological parameters
 */
void applyMorphologicalOperation(const Mat& src, Mat& dst, MorphologicalOperation operation, 
                               const MorphologicalParams& params) {
    switch (operation) {
        case ORIGINAL:
            src.copyTo(dst);
            break;
        case EROSION:
            applyErosion(src, dst, params);
            break;
        case DILATION:
            applyDilation(src, dst, params);
            break;
        case OPENING:
            applyOpening(src, dst, params);
            break;
        case CLOSING:
            applyClosing(src, dst, params);
            break;
        case GRADIENT:
            applyGradient(src, dst, params);
            break;
        case TOPHAT:
            applyTopHat(src, dst, params);
            break;
        case BLACKHAT:
            applyBlackHat(src, dst, params);
            break;
        case HIT_MISS:
            applyHitMiss(src, dst, params);
            break;
    }
}

/**
 * @brief Function to create morphological kernel visualization
 * @param params Morphological parameters
 * @return Mat Kernel visualization
 */
Mat createKernelVisualization(const MorphologicalParams& params) {
    Mat kernel = createMorphologicalKernel(params);
    Mat visualization = Mat::zeros(200, 200, CV_8UC3);
    
    // Scale kernel for visualization
    Mat scaledKernel;
    resize(kernel, scaledKernel, Size(100, 100), 0, 0, INTER_NEAREST);
    
    // Convert to 3-channel for color display
    Mat kernel3Channel;
    cvtColor(scaledKernel, kernel3Channel, COLOR_GRAY2BGR);
    
    // Copy kernel to center of visualization
    Rect roi(50, 50, 100, 100);
    kernel3Channel.copyTo(visualization(roi));
    
    // Add labels
    putText(visualization, "Kernel", Point(10, 30), 
           FONT_HERSHEY_SIMPLEX, 0.6, Scalar(0, 255, 0), 2);
    
    stringstream ss;
    ss << "Size: " << params.kernelSize << "x" << params.kernelSize;
    putText(visualization, ss.str(), Point(10, 60), 
           FONT_HERSHEY_SIMPLEX, 0.5, Scalar(255, 255, 255), 1);
    
    ss.str("");
    ss << "Iterations: " << params.iterations;
    putText(visualization, ss.str(), Point(10, 80), 
           FONT_HERSHEY_SIMPLEX, 0.5, Scalar(255, 255, 255), 1);
    
    return visualization;
}

/**
 * @brief Function to send morphological data to MATLAB
 * @param matlabPtr MATLAB engine pointer
 * @param src Original image
 * @param dst Processed image
 * @param operation Morphological operation type
 * @param params Morphological parameters
 */
void sendMorphologicalToMATLAB(std::unique_ptr<matlab::engine::MATLABEngine>& matlabPtr, 
                              const Mat& src, const Mat& dst, MorphologicalOperation operation, 
                              const MorphologicalParams& params) {
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
        
        // Processed image
        auto dimsDst = factory.createArray<std::size_t>({1, 3}, 
            {static_cast<std::size_t>(rgbDst.rows), 
             static_cast<std::size_t>(rgbDst.cols), 
             static_cast<std::size_t>(rgbDst.channels())});
        auto matlabDst = factory.createArray<uint8_t>(dimsDst);
        auto dstPtr = matlabDst.release();
        memcpy(dstPtr, rgbDst.data, rgbDst.total() * rgbDst.elemSize());
        
        // Set variables in MATLAB workspace
        matlabPtr->setVariable(u"originalImage", matlabSrc);
        matlabPtr->setVariable(u"processedImage", matlabDst);
        
        // Execute MATLAB commands
        string operationName = getMorphologicalOperationName(operation);
        string matlabCmd = "figure; subplot(1,2,1); imshow(originalImage); title('Original'); "
                          "subplot(1,2,2); imshow(processedImage); title('" + operationName + "');";
        matlabPtr->eval(matlab::engine::convertUTF8StringToUTF16String(matlabCmd));
        
        // Display operation information
        matlabPtr->eval(u"fprintf('Morphological Operation: " + matlab::engine::convertUTF8StringToUTF16String(operationName) + "\\n');");
        matlabPtr->eval(u"fprintf('Kernel Size: %d x %d\\n', " + to_string(params.kernelSize) + u", " + to_string(params.kernelSize) + u");");
        matlabPtr->eval(u"fprintf('Iterations: %d\\n', " + to_string(params.iterations) + u");");
        
        cout << "Morphological data sent to MATLAB successfully!" << endl;
        
    } catch (const std::exception& e) {
        cerr << "Error sending morphological data to MATLAB: " << e.what() << endl;
    }
}

/**
 * @brief Main function for basic morphological operations
 * @return int Exit status
 */
int main() {
    cout << "=== Basic Morphological Operations - Beginner Level 9 ===" << endl;
    cout << "This program demonstrates basic morphological operations." << endl;
    
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
        
        // Initialize morphological parameters
        MorphologicalParams params;
        params.kernelSize = 5;
        params.iterations = 1;
        params.morphType = MORPH_RECT;
        params.elementType = 0; // Rectangular
        params.anchor = Point(-1, -1); // Center
        
        // Initialize morphological operation
        MorphologicalOperation currentOperation = ORIGINAL;
        
        // Create Mat objects for frame processing
        Mat frame, processedFrame, displayFrame, kernelVisualization;
        
        cout << "\nStarting camera feed with morphological operations..." << endl;
        cout << "Controls:" << endl;
        cout << "  'q' - Quit" << endl;
        cout << "  '0' - Original" << endl;
        cout << "  '1' - Erosion" << endl;
        cout << "  '2' - Dilation" << endl;
        cout << "  '3' - Opening" << endl;
        cout << "  '4' - Closing" << endl;
        cout << "  '5' - Gradient" << endl;
        cout << "  '6' - Top Hat" << endl;
        cout << "  '7' - Black Hat" << endl;
        cout << "  '8' - Hit or Miss" << endl;
        cout << "  '+' - Increase kernel size" << endl;
        cout << "  '-' - Decrease kernel size" << endl;
        cout << "  'i' - Increase iterations" << endl;
        cout << "  'd' - Decrease iterations" << endl;
        cout << "  'k' - Show kernel visualization" << endl;
        cout << "  'm' - Send to MATLAB" << endl;
        cout << "  's' - Save current operation" << endl;
        
        bool showKernel = false;
        
        // Main capture loop
        while (true) {
            // Capture frame from camera
            cap >> frame;
            
            // Check if frame was captured successfully
            if (frame.empty()) {
                cerr << "Warning: Could not capture frame!" << endl;
                continue;
            }
            
            // Convert to grayscale for morphological operations
            Mat grayFrame;
            cvtColor(frame, grayFrame, COLOR_BGR2GRAY);
            
            // Apply selected morphological operation
            applyMorphologicalOperation(grayFrame, processedFrame, currentOperation, params);
            
            // Convert back to BGR for display
            cvtColor(processedFrame, displayFrame, COLOR_GRAY2BGR);
            
            // Create kernel visualization
            kernelVisualization = createKernelVisualization(params);
            
            // Create side-by-side comparison
            Mat comparison;
            hconcat(frame, displayFrame, comparison);
            
            // Add labels
            string operationName = getMorphologicalOperationName(currentOperation);
            putText(comparison, "Original", Point(10, 30), 
                   FONT_HERSHEY_SIMPLEX, 0.7, Scalar(0, 255, 0), 2);
            putText(comparison, operationName, Point(frame.cols + 10, 30), 
                   FONT_HERSHEY_SIMPLEX, 0.7, Scalar(0, 255, 0), 2);
            
            // Add parameter information
            stringstream ss;
            ss << "Kernel: " << params.kernelSize << "x" << params.kernelSize;
            putText(comparison, ss.str(), Point(10, 60), 
                   FONT_HERSHEY_SIMPLEX, 0.5, Scalar(255, 255, 255), 1);
            
            ss.str("");
            ss << "Iterations: " << params.iterations;
            putText(comparison, ss.str(), Point(10, 80), 
                   FONT_HERSHEY_SIMPLEX, 0.5, Scalar(255, 255, 255), 1);
            
            // Display the comparison
            imshow("Basic Morphological Operations", comparison);
            
            if (showKernel) {
                imshow("Kernel Visualization", kernelVisualization);
            }
            
            // Handle keyboard input
            char key = waitKey(1) & 0xFF;
            
            if (key == 'q' || key == 27) { // 'q' or ESC to quit
                cout << "Quitting..." << endl;
                break;
            }
            else if (key >= '0' && key <= '8') { // Operation selection
                currentOperation = static_cast<MorphologicalOperation>(key - '0');
                cout << "Selected operation: " << getMorphologicalOperationName(currentOperation) << endl;
            }
            else if (key == '+') { // Increase kernel size
                params.kernelSize = min(31, params.kernelSize + 2);
                cout << "Kernel size increased to: " << params.kernelSize << endl;
            }
            else if (key == '-') { // Decrease kernel size
                params.kernelSize = max(3, params.kernelSize - 2);
                cout << "Kernel size decreased to: " << params.kernelSize << endl;
            }
            else if (key == 'i') { // Increase iterations
                params.iterations = min(10, params.iterations + 1);
                cout << "Iterations increased to: " << params.iterations << endl;
            }
            else if (key == 'd') { // Decrease iterations
                params.iterations = max(1, params.iterations - 1);
                cout << "Iterations decreased to: " << params.iterations << endl;
            }
            else if (key == 'k') { // Toggle kernel visualization
                showKernel = !showKernel;
                if (!showKernel) {
                    destroyWindow("Kernel Visualization");
                }
                cout << "Kernel visualization: " << (showKernel ? "ON" : "OFF") << endl;
            }
            else if (key == 'm') { // Send to MATLAB
                sendMorphologicalToMATLAB(matlabPtr, frame, displayFrame, currentOperation, params);
            }
            else if (key == 's') { // Save current operation
                string filename = "morphological_" + operationName + ".jpg";
                imwrite(filename, displayFrame);
                cout << "Morphological operation saved as: " << filename << endl;
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
 * g++ -std=c++17 camera_basic_09.cpp -o camera_basic_09 \
 *     `pkg-config --cflags --libs opencv4` \
 *     -I/Applications/MATLAB_R2023b.app/extern/include \
 *     -L/Applications/MATLAB_R2023b.app/bin/maci64 \
 *     -lMatlabDataArray -lMatlabEngine
 * 
 * @brief Usage:
 * 1. Make sure your camera is connected and working
 * 2. Run the executable: ./camera_basic_09
 * 3. Use keyboard controls to switch between morphological operations
 * 4. Adjust kernel size and iterations with '+'/'-' and 'i'/'d' keys
 * 5. Press 'k' to show kernel visualization
 * 6. Press 'm' to send data to MATLAB
 * 7. Press 's' to save current operation
 * 
 * @brief Learning Objectives:
 * - Understand basic morphological operations
 * - Learn erosion, dilation, opening, and closing
 * - Understand morphological gradient and hat operations
 * - Learn kernel-based image processing
 * - Understand kernel size and iteration effects
 * - Learn MATLAB integration for morphological analysis
 * - Understand morphological operation applications
 * - Learn to visualize morphological kernels
 */
