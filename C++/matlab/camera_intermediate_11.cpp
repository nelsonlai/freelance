/**
 * @file camera_intermediate_11.cpp
 * @brief Edge Detection and Contour Analysis - Intermediate Level 11
 * @description This program demonstrates advanced edge detection techniques like
 *              Canny, Sobel, Laplacian, and contour detection using OpenCV
 *              and MATLAB integration for real-time analysis.
 * @author Educational C++ MATLAB Integration Project
 * @date 2024
 * @version 1.0
 */

#include <opencv2/opencv.hpp>
#include <iostream>
#include <matlab/engine.hpp>
#include <memory>
#include <vector>
#include <algorithm>

using namespace cv;
using namespace std;

/**
 * @brief Enumeration for different edge detection methods
 */
enum EdgeDetectionMethod {
    CANNY = 0,
    SOBEL_X = 1,
    SOBEL_Y = 2,
    SOBEL_XY = 3,
    LAPLACIAN = 4,
    PREWITT_X = 5,
    PREWITT_Y = 6,
    ROBERTS = 7,
    SCHARR_X = 8,
    SCHARR_Y = 9
};

/**
 * @brief Structure to hold edge detection parameters
 */
struct EdgeDetectionParams {
    double cannyLowThreshold;
    double cannyHighThreshold;
    int sobelKernelSize;
    int laplacianKernelSize;
    double gaussianBlurSigma;
    int morphKernelSize;
    double contourAreaThreshold;
    int contourApproximationMethod;
};

/**
 * @brief Function to get edge detection method name
 * @param method Edge detection method
 * @return string Method name
 */
string getEdgeDetectionMethodName(EdgeDetectionMethod method) {
    switch (method) {
        case CANNY: return "Canny";
        case SOBEL_X: return "Sobel X";
        case SOBEL_Y: return "Sobel Y";
        case SOBEL_XY: return "Sobel XY";
        case LAPLACIAN: return "Laplacian";
        case PREWITT_X: return "Prewitt X";
        case PREWITT_Y: return "Prewitt Y";
        case ROBERTS: return "Roberts";
        case SCHARR_X: return "Scharr X";
        case SCHARR_Y: return "Scharr Y";
        default: return "Unknown";
    }
}

/**
 * @brief Function to apply Canny edge detection
 * @param src Input image
 * @param dst Output image
 * @param params Edge detection parameters
 */
void applyCannyEdgeDetection(const Mat& src, Mat& dst, const EdgeDetectionParams& params) {
    Mat blurred;
    GaussianBlur(src, blurred, Size(5, 5), params.gaussianBlurSigma);
    Canny(blurred, dst, params.cannyLowThreshold, params.cannyHighThreshold);
}

/**
 * @brief Function to apply Sobel edge detection
 * @param src Input image
 * @param dst Output image
 * @param params Edge detection parameters
 * @param direction Sobel direction (X, Y, or XY)
 */
void applySobelEdgeDetection(const Mat& src, Mat& dst, const EdgeDetectionParams& params, 
                            EdgeDetectionMethod direction) {
    Mat grad_x, grad_y, grad;
    
    switch (direction) {
        case SOBEL_X:
            Sobel(src, dst, CV_64F, 1, 0, params.sobelKernelSize);
            break;
        case SOBEL_Y:
            Sobel(src, dst, CV_64F, 0, 1, params.sobelKernelSize);
            break;
        case SOBEL_XY:
            Sobel(src, grad_x, CV_64F, 1, 0, params.sobelKernelSize);
            Sobel(src, grad_y, CV_64F, 0, 1, params.sobelKernelSize);
            magnitude(grad_x, grad_y, dst);
            break;
        default:
            Sobel(src, dst, CV_64F, 1, 0, params.sobelKernelSize);
            break;
    }
    
    // Convert to 8-bit
    dst.convertTo(dst, CV_8U);
}

/**
 * @brief Function to apply Laplacian edge detection
 * @param src Input image
 * @param dst Output image
 * @param params Edge detection parameters
 */
void applyLaplacianEdgeDetection(const Mat& src, Mat& dst, const EdgeDetectionParams& params) {
    Laplacian(src, dst, CV_64F, params.laplacianKernelSize);
    dst.convertTo(dst, CV_8U);
}

/**
 * @brief Function to apply Prewitt edge detection
 * @param src Input image
 * @param dst Output image
 * @param params Edge detection parameters
 * @param direction Prewitt direction (X or Y)
 */
void applyPrewittEdgeDetection(const Mat& src, Mat& dst, const EdgeDetectionParams& params, 
                              EdgeDetectionMethod direction) {
    Mat kernel;
    
    if (direction == PREWITT_X) {
        kernel = (Mat_<float>(3, 3) << -1, 0, 1, -1, 0, 1, -1, 0, 1);
    } else { // PREWITT_Y
        kernel = (Mat_<float>(3, 3) << -1, -1, -1, 0, 0, 0, 1, 1, 1);
    }
    
    filter2D(src, dst, -1, kernel);
}

/**
 * @brief Function to apply Roberts edge detection
 * @param src Input image
 * @param dst Output image
 * @param params Edge detection parameters
 */
void applyRobertsEdgeDetection(const Mat& src, Mat& dst, const EdgeDetectionParams& params) {
    Mat kernel1 = (Mat_<float>(2, 2) << 1, 0, 0, -1);
    Mat kernel2 = (Mat_<float>(2, 2) << 0, 1, -1, 0);
    
    Mat result1, result2;
    filter2D(src, result1, -1, kernel1);
    filter2D(src, result2, -1, kernel2);
    
    magnitude(result1, result2, dst);
    dst.convertTo(dst, CV_8U);
}

/**
 * @brief Function to apply Scharr edge detection
 * @param src Input image
 * @param dst Output image
 * @param params Edge detection parameters
 * @param direction Scharr direction (X or Y)
 */
void applyScharrEdgeDetection(const Mat& src, Mat& dst, const EdgeDetectionParams& params, 
                             EdgeDetectionMethod direction) {
    if (direction == SCHARR_X) {
        Scharr(src, dst, CV_64F, 1, 0);
    } else { // SCHARR_Y
        Scharr(src, dst, CV_64F, 0, 1);
    }
    
    dst.convertTo(dst, CV_8U);
}

/**
 * @brief Function to apply selected edge detection method
 * @param src Input image
 * @param dst Output image
 * @param method Edge detection method
 * @param params Edge detection parameters
 */
void applyEdgeDetection(const Mat& src, Mat& dst, EdgeDetectionMethod method, 
                       const EdgeDetectionParams& params) {
    switch (method) {
        case CANNY:
            applyCannyEdgeDetection(src, dst, params);
            break;
        case SOBEL_X:
        case SOBEL_Y:
        case SOBEL_XY:
            applySobelEdgeDetection(src, dst, params, method);
            break;
        case LAPLACIAN:
            applyLaplacianEdgeDetection(src, dst, params);
            break;
        case PREWITT_X:
        case PREWITT_Y:
            applyPrewittEdgeDetection(src, dst, params, method);
            break;
        case ROBERTS:
            applyRobertsEdgeDetection(src, dst, params);
            break;
        case SCHARR_X:
        case SCHARR_Y:
            applyScharrEdgeDetection(src, dst, params, method);
            break;
    }
}

/**
 * @brief Function to detect and analyze contours
 * @param edgeImage Input edge image
 * @param contours Output contours
 * @param hierarchy Output hierarchy
 * @param params Edge detection parameters
 */
void detectContours(const Mat& edgeImage, vector<vector<Point>>& contours, 
                   vector<Vec4i>& hierarchy, const EdgeDetectionParams& params) {
    // Find contours
    findContours(edgeImage, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE);
    
    // Filter contours by area
    vector<vector<Point>> filteredContours;
    for (size_t i = 0; i < contours.size(); i++) {
        double area = contourArea(contours[i]);
        if (area > params.contourAreaThreshold) {
            filteredContours.push_back(contours[i]);
        }
    }
    
    contours = filteredContours;
}

/**
 * @brief Function to draw contours with analysis
 * @param src Input image
 * @param contours Input contours
 * @param dst Output image with drawn contours
 * @param params Edge detection parameters
 */
void drawContoursWithAnalysis(const Mat& src, const vector<vector<Point>>& contours, 
                             Mat& dst, const EdgeDetectionParams& params) {
    src.copyTo(dst);
    
    // Draw contours
    drawContours(dst, contours, -1, Scalar(0, 255, 0), 2);
    
    // Analyze and draw contour properties
    for (size_t i = 0; i < contours.size(); i++) {
        // Calculate contour properties
        double area = contourArea(contours[i]);
        Rect boundingRect = boundingRect(contours[i]);
        RotatedRect rotatedRect = minAreaRect(contours[i]);
        
        // Draw bounding rectangle
        rectangle(dst, boundingRect, Scalar(255, 0, 0), 2);
        
        // Draw rotated rectangle
        Point2f vertices[4];
        rotatedRect.points(vertices);
        for (int j = 0; j < 4; j++) {
            line(dst, vertices[j], vertices[(j + 1) % 4], Scalar(0, 0, 255), 2);
        }
        
        // Draw contour center
        Moments moments = cv::moments(contours[i]);
        if (moments.m00 != 0) {
            Point center(moments.m10 / moments.m00, moments.m01 / moments.m00);
            circle(dst, center, 5, Scalar(255, 255, 0), -1);
        }
        
        // Add contour information
        stringstream ss;
        ss << "Area: " << fixed << setprecision(1) << area;
        putText(dst, ss.str(), Point(boundingRect.x, boundingRect.y - 10), 
               FONT_HERSHEY_SIMPLEX, 0.5, Scalar(255, 255, 255), 1);
    }
}

/**
 * @brief Function to send edge detection data to MATLAB
 * @param matlabPtr MATLAB engine pointer
 * @param src Original image
 * @param edgeImage Edge detected image
 * @param contours Detected contours
 * @param method Edge detection method
 * @param params Edge detection parameters
 */
void sendEdgeDetectionToMATLAB(std::unique_ptr<matlab::engine::MATLABEngine>& matlabPtr, 
                             const Mat& src, const Mat& edgeImage, 
                             const vector<vector<Point>>& contours,
                             EdgeDetectionMethod method, const EdgeDetectionParams& params) {
    try {
        // Convert BGR to RGB for MATLAB
        Mat rgbSrc, rgbEdge;
        cvtColor(src, rgbSrc, COLOR_BGR2RGB);
        cvtColor(edgeImage, rgbEdge, COLOR_BGR2RGB);
        
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
        
        // Edge image
        auto dimsEdge = factory.createArray<std::size_t>({1, 3}, 
            {static_cast<std::size_t>(rgbEdge.rows), 
             static_cast<std::size_t>(rgbEdge.cols), 
             static_cast<std::size_t>(rgbEdge.channels())});
        auto matlabEdge = factory.createArray<uint8_t>(dimsEdge);
        auto edgePtr = matlabEdge.release();
        memcpy(edgePtr, rgbEdge.data, rgbEdge.total() * rgbEdge.elemSize());
        
        // Set variables in MATLAB workspace
        matlabPtr->setVariable(u"originalImage", matlabSrc);
        matlabPtr->setVariable(u"edgeImage", matlabEdge);
        
        // Execute MATLAB commands
        string methodName = getEdgeDetectionMethodName(method);
        string matlabCmd = "figure; subplot(1,2,1); imshow(originalImage); title('Original'); "
                          "subplot(1,2,2); imshow(edgeImage); title('" + methodName + " Edge Detection');";
        matlabPtr->eval(matlab::engine::convertUTF8StringToUTF16String(matlabCmd));
        
        // Display edge detection information
        matlabPtr->eval(u"fprintf('Edge Detection Method: " + matlab::engine::convertUTF8StringToUTF16String(methodName) + "\\n');");
        matlabPtr->eval(u"fprintf('Number of contours detected: %d\\n', " + to_string(contours.size()) + u");");
        
        if (method == CANNY) {
            matlabPtr->eval(u"fprintf('Canny Low Threshold: %.2f\\n', " + to_string(params.cannyLowThreshold) + u");");
            matlabPtr->eval(u"fprintf('Canny High Threshold: %.2f\\n', " + to_string(params.cannyHighThreshold) + u");");
        }
        
        cout << "Edge detection data sent to MATLAB successfully!" << endl;
        
    } catch (const std::exception& e) {
        cerr << "Error sending edge detection data to MATLAB: " << e.what() << endl;
    }
}

/**
 * @brief Main function for edge detection and contour analysis
 * @return int Exit status
 */
int main() {
    cout << "=== Edge Detection and Contour Analysis - Intermediate Level 11 ===" << endl;
    cout << "This program demonstrates advanced edge detection and contour analysis." << endl;
    
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
        
        // Initialize edge detection parameters
        EdgeDetectionParams params;
        params.cannyLowThreshold = 50.0;
        params.cannyHighThreshold = 150.0;
        params.sobelKernelSize = 3;
        params.laplacianKernelSize = 3;
        params.gaussianBlurSigma = 1.0;
        params.morphKernelSize = 3;
        params.contourAreaThreshold = 100.0;
        params.contourApproximationMethod = CHAIN_APPROX_SIMPLE;
        
        // Initialize edge detection method
        EdgeDetectionMethod currentMethod = CANNY;
        
        // Create Mat objects for frame processing
        Mat frame, grayFrame, edgeImage, contourImage, displayFrame;
        vector<vector<Point>> contours;
        vector<Vec4i> hierarchy;
        
        cout << "\nStarting camera feed with edge detection..." << endl;
        cout << "Controls:" << endl;
        cout << "  'q' - Quit" << endl;
        cout << "  '0' - Canny" << endl;
        cout << "  '1' - Sobel X" << endl;
        cout << "  '2' - Sobel Y" << endl;
        cout << "  '3' - Sobel XY" << endl;
        cout << "  '4' - Laplacian" << endl;
        cout << "  '5' - Prewitt X" << endl;
        cout << "  '6' - Prewitt Y" << endl;
        cout << "  '7' - Roberts" << endl;
        cout << "  '8' - Scharr X" << endl;
        cout << "  '9' - Scharr Y" << endl;
        cout << "  '+' - Increase Canny high threshold" << endl;
        cout << "  '-' - Decrease Canny high threshold" << endl;
        cout << "  'l' - Increase Canny low threshold" << endl;
        cout << "  'L' - Decrease Canny low threshold" << endl;
        cout << "  'c' - Toggle contour analysis" << endl;
        cout << "  'm' - Send to MATLAB" << endl;
        cout << "  's' - Save current edge detection" << endl;
        
        bool showContours = false;
        
        // Main capture loop
        while (true) {
            // Capture frame from camera
            cap >> frame;
            
            // Check if frame was captured successfully
            if (frame.empty()) {
                cerr << "Warning: Could not capture frame!" << endl;
                continue;
            }
            
            // Convert to grayscale for edge detection
            cvtColor(frame, grayFrame, COLOR_BGR2GRAY);
            
            // Apply selected edge detection method
            applyEdgeDetection(grayFrame, edgeImage, currentMethod, params);
            
            // Convert edge image to BGR for display
            cvtColor(edgeImage, displayFrame, COLOR_GRAY2BGR);
            
            // Detect contours if enabled
            if (showContours) {
                detectContours(edgeImage, contours, hierarchy, params);
                drawContoursWithAnalysis(frame, contours, contourImage, params);
                displayFrame = contourImage;
            }
            
            // Create side-by-side comparison
            Mat comparison;
            hconcat(frame, displayFrame, comparison);
            
            // Add labels
            string methodName = getEdgeDetectionMethodName(currentMethod);
            putText(comparison, "Original", Point(10, 30), 
                   FONT_HERSHEY_SIMPLEX, 0.7, Scalar(0, 255, 0), 2);
            putText(comparison, methodName, Point(frame.cols + 10, 30), 
                   FONT_HERSHEY_SIMPLEX, 0.7, Scalar(0, 255, 0), 2);
            
            // Add parameter information
            if (currentMethod == CANNY) {
                stringstream ss;
                ss << "Low: " << params.cannyLowThreshold << " High: " << params.cannyHighThreshold;
                putText(comparison, ss.str(), Point(10, 60), 
                       FONT_HERSHEY_SIMPLEX, 0.5, Scalar(255, 255, 255), 1);
            }
            
            if (showContours) {
                stringstream ss;
                ss << "Contours: " << contours.size();
                putText(comparison, ss.str(), Point(10, 80), 
                       FONT_HERSHEY_SIMPLEX, 0.5, Scalar(255, 255, 255), 1);
            }
            
            // Display the comparison
            imshow("Edge Detection and Contour Analysis", comparison);
            
            // Handle keyboard input
            char key = waitKey(1) & 0xFF;
            
            if (key == 'q' || key == 27) { // 'q' or ESC to quit
                cout << "Quitting..." << endl;
                break;
            }
            else if (key >= '0' && key <= '9') { // Method selection
                currentMethod = static_cast<EdgeDetectionMethod>(key - '0');
                cout << "Selected method: " << getEdgeDetectionMethodName(currentMethod) << endl;
            }
            else if (key == '+') { // Increase Canny high threshold
                params.cannyHighThreshold = min(300.0, params.cannyHighThreshold + 10.0);
                cout << "Canny high threshold increased to: " << params.cannyHighThreshold << endl;
            }
            else if (key == '-') { // Decrease Canny high threshold
                params.cannyHighThreshold = max(50.0, params.cannyHighThreshold - 10.0);
                cout << "Canny high threshold decreased to: " << params.cannyHighThreshold << endl;
            }
            else if (key == 'l') { // Increase Canny low threshold
                params.cannyLowThreshold = min(200.0, params.cannyLowThreshold + 10.0);
                cout << "Canny low threshold increased to: " << params.cannyLowThreshold << endl;
            }
            else if (key == 'L') { // Decrease Canny low threshold
                params.cannyLowThreshold = max(10.0, params.cannyLowThreshold - 10.0);
                cout << "Canny low threshold decreased to: " << params.cannyLowThreshold << endl;
            }
            else if (key == 'c') { // Toggle contour analysis
                showContours = !showContours;
                cout << "Contour analysis: " << (showContours ? "ON" : "OFF") << endl;
            }
            else if (key == 'm') { // Send to MATLAB
                sendEdgeDetectionToMATLAB(matlabPtr, frame, displayFrame, contours, currentMethod, params);
            }
            else if (key == 's') { // Save current edge detection
                string filename = "edge_detection_" + methodName + ".jpg";
                imwrite(filename, displayFrame);
                cout << "Edge detection saved as: " << filename << endl;
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
 * g++ -std=c++17 camera_intermediate_11.cpp -o camera_intermediate_11 \
 *     `pkg-config --cflags --libs opencv4` \
 *     -I/Applications/MATLAB_R2023b.app/extern/include \
 *     -L/Applications/MATLAB_R2023b.app/bin/maci64 \
 *     -lMatlabDataArray -lMatlabEngine
 * 
 * @brief Usage:
 * 1. Make sure your camera is connected and working
 * 2. Run the executable: ./camera_intermediate_11
 * 3. Use keyboard controls to switch between edge detection methods
 * 4. Adjust Canny thresholds with '+'/'-' and 'l'/'L' keys
 * 5. Press 'c' to toggle contour analysis
 * 6. Press 'm' to send data to MATLAB
 * 7. Press 's' to save current edge detection
 * 
 * @brief Learning Objectives:
 * - Understand advanced edge detection techniques
 * - Learn Canny, Sobel, Laplacian, and other edge detectors
 * - Understand edge detection parameters and their effects
 * - Learn contour detection and analysis
 * - Understand contour properties and measurements
 * - Learn MATLAB integration for edge analysis
 * - Understand edge detection applications in computer vision
 * - Learn to choose appropriate edge detection methods
 */
