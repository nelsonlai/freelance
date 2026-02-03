/**
 * @file camera_intermediate_13.cpp
 * @brief Object Detection and Tracking - Intermediate Level 13
 * @description This program demonstrates object detection and tracking using
 *              template matching, contour analysis, and basic tracking algorithms
 *              with OpenCV and MATLAB integration for real-time analysis.
 * @author Educational C++ MATLAB Integration Project
 * @date 2024
 * @version 1.0
 */

#include <opencv2/opencv.hpp>
#include <opencv2/tracking.hpp>
#include <iostream>
#include <matlab/engine.hpp>
#include <memory>
#include <vector>
#include <algorithm>

using namespace cv;
using namespace std;

/**
 * @brief Enumeration for different detection methods
 */
enum DetectionMethod {
    TEMPLATE_MATCHING = 0,
    CONTOUR_DETECTION = 1,
    COLOR_DETECTION = 2,
    MOTION_DETECTION = 3,
    CORNER_DETECTION = 4,
    BLOB_DETECTION = 5
};

/**
 * @brief Enumeration for different tracking methods
 */
enum TrackingMethod {
    NO_TRACKING = 0,
    KALMAN_FILTER = 1,
    MEAN_SHIFT = 2,
    CAMSHIFT = 3,
    MOSSE = 4,
    CSRT = 5
};

/**
 * @brief Structure to hold detection parameters
 */
struct DetectionParams {
    double templateThreshold;
    double contourAreaThreshold;
    Scalar colorLower;
    Scalar colorUpper;
    double motionThreshold;
    int cornerMaxCorners;
    double cornerQualityLevel;
    double cornerMinDistance;
    double blobMinArea;
    double blobMaxArea;
};

/**
 * @brief Structure to hold tracking parameters
 */
struct TrackingParams {
    double kalmanProcessNoise;
    double kalmanMeasurementNoise;
    int meanShiftMaxIterations;
    double meanShiftThreshold;
    int camshiftMaxIterations;
    double camshiftThreshold;
    double mosseLearningRate;
    double csrtLearningRate;
};

/**
 * @brief Function to get detection method name
 * @param method Detection method
 * @return string Method name
 */
string getDetectionMethodName(DetectionMethod method) {
    switch (method) {
        case TEMPLATE_MATCHING: return "Template Matching";
        case CONTOUR_DETECTION: return "Contour Detection";
        case COLOR_DETECTION: return "Color Detection";
        case MOTION_DETECTION: return "Motion Detection";
        case CORNER_DETECTION: return "Corner Detection";
        case BLOB_DETECTION: return "Blob Detection";
        default: return "Unknown";
    }
}

/**
 * @brief Function to get tracking method name
 * @param method Tracking method
 * @return string Method name
 */
string getTrackingMethodName(TrackingMethod method) {
    switch (method) {
        case NO_TRACKING: return "No Tracking";
        case KALMAN_FILTER: return "Kalman Filter";
        case MEAN_SHIFT: return "Mean Shift";
        case CAMSHIFT: return "CamShift";
        case MOSSE: return "MOSSE";
        case CSRT: return "CSRT";
        default: return "Unknown";
    }
}

/**
 * @brief Function to apply template matching
 * @param src Input image
 * @param template Template image
 * @param dst Output image with matches
 * @param params Detection parameters
 * @return vector<Rect> Detected regions
 */
vector<Rect> applyTemplateMatching(const Mat& src, const Mat& template, Mat& dst, 
                                 const DetectionParams& params) {
    vector<Rect> detections;
    
    if (template.empty()) {
        src.copyTo(dst);
        return detections;
    }
    
    Mat result;
    matchTemplate(src, template, result, TM_CCOEFF_NORMED);
    
    // Find matches above threshold
    vector<Point> locations;
    findNonZero(result > params.templateThreshold, locations);
    
    // Group nearby matches
    for (const auto& loc : locations) {
        Rect rect(loc.x, loc.y, template.cols, template.rows);
        detections.push_back(rect);
    }
    
    // Draw detections
    src.copyTo(dst);
    for (const auto& rect : detections) {
        rectangle(dst, rect, Scalar(0, 255, 0), 2);
    }
    
    return detections;
}

/**
 * @brief Function to apply contour detection
 * @param src Input image
 * @param dst Output image with contours
 * @param params Detection parameters
 * @return vector<Rect> Detected regions
 */
vector<Rect> applyContourDetection(const Mat& src, Mat& dst, const DetectionParams& params) {
    vector<Rect> detections;
    
    // Convert to grayscale
    Mat gray;
    cvtColor(src, gray, COLOR_BGR2GRAY);
    
    // Apply threshold
    Mat binary;
    threshold(gray, binary, 127, 255, THRESH_BINARY);
    
    // Find contours
    vector<vector<Point>> contours;
    vector<Vec4i> hierarchy;
    findContours(binary, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
    
    // Filter contours by area
    for (const auto& contour : contours) {
        double area = contourArea(contour);
        if (area > params.contourAreaThreshold) {
            Rect rect = boundingRect(contour);
            detections.push_back(rect);
        }
    }
    
    // Draw detections
    src.copyTo(dst);
    for (const auto& rect : detections) {
        rectangle(dst, rect, Scalar(0, 255, 0), 2);
    }
    
    return detections;
}

/**
 * @brief Function to apply color detection
 * @param src Input image
 * @param dst Output image with detections
 * @param params Detection parameters
 * @return vector<Rect> Detected regions
 */
vector<Rect> applyColorDetection(const Mat& src, Mat& dst, const DetectionParams& params) {
    vector<Rect> detections;
    
    // Convert to HSV
    Mat hsv;
    cvtColor(src, hsv, COLOR_BGR2HSV);
    
    // Create mask
    Mat mask;
    inRange(hsv, params.colorLower, params.colorUpper, mask);
    
    // Find contours
    vector<vector<Point>> contours;
    vector<Vec4i> hierarchy;
    findContours(mask, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
    
    // Filter contours by area
    for (const auto& contour : contours) {
        double area = contourArea(contour);
        if (area > params.contourAreaThreshold) {
            Rect rect = boundingRect(contour);
            detections.push_back(rect);
        }
    }
    
    // Draw detections
    src.copyTo(dst);
    for (const auto& rect : detections) {
        rectangle(dst, rect, Scalar(0, 255, 0), 2);
    }
    
    return detections;
}

/**
 * @brief Function to apply motion detection
 * @param src Input image
 * @param prevFrame Previous frame
 * @param dst Output image with detections
 * @param params Detection parameters
 * @return vector<Rect> Detected regions
 */
vector<Rect> applyMotionDetection(const Mat& src, const Mat& prevFrame, Mat& dst, 
                                 const DetectionParams& params) {
    vector<Rect> detections;
    
    if (prevFrame.empty()) {
        src.copyTo(dst);
        return detections;
    }
    
    // Convert to grayscale
    Mat gray, prevGray;
    cvtColor(src, gray, COLOR_BGR2GRAY);
    cvtColor(prevFrame, prevGray, COLOR_BGR2GRAY);
    
    // Compute difference
    Mat diff;
    absdiff(gray, prevGray, diff);
    
    // Apply threshold
    Mat binary;
    threshold(diff, binary, params.motionThreshold, 255, THRESH_BINARY);
    
    // Find contours
    vector<vector<Point>> contours;
    vector<Vec4i> hierarchy;
    findContours(binary, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
    
    // Filter contours by area
    for (const auto& contour : contours) {
        double area = contourArea(contour);
        if (area > params.contourAreaThreshold) {
            Rect rect = boundingRect(contour);
            detections.push_back(rect);
        }
    }
    
    // Draw detections
    src.copyTo(dst);
    for (const auto& rect : detections) {
        rectangle(dst, rect, Scalar(0, 255, 0), 2);
    }
    
    return detections;
}

/**
 * @brief Function to apply corner detection
 * @param src Input image
 * @param dst Output image with corners
 * @param params Detection parameters
 * @return vector<Rect> Detected regions
 */
vector<Rect> applyCornerDetection(const Mat& src, Mat& dst, const DetectionParams& params) {
    vector<Rect> detections;
    
    // Convert to grayscale
    Mat gray;
    cvtColor(src, gray, COLOR_BGR2GRAY);
    
    // Detect corners
    vector<Point2f> corners;
    goodFeaturesToTrack(gray, corners, params.cornerMaxCorners, 
                       params.cornerQualityLevel, params.cornerMinDistance);
    
    // Draw corners
    src.copyTo(dst);
    for (const auto& corner : corners) {
        circle(dst, corner, 5, Scalar(0, 255, 0), -1);
    }
    
    return detections;
}

/**
 * @brief Function to apply blob detection
 * @param src Input image
 * @param dst Output image with blobs
 * @param params Detection parameters
 * @return vector<Rect> Detected regions
 */
vector<Rect> applyBlobDetection(const Mat& src, Mat& dst, const DetectionParams& params) {
    vector<Rect> detections;
    
    // Convert to grayscale
    Mat gray;
    cvtColor(src, gray, COLOR_BGR2GRAY);
    
    // Create blob detector
    SimpleBlobDetector::Params blobParams;
    blobParams.minArea = params.blobMinArea;
    blobParams.maxArea = params.blobMaxArea;
    blobParams.filterByArea = true;
    blobParams.filterByCircularity = false;
    blobParams.filterByConvexity = false;
    blobParams.filterByInertia = false;
    
    Ptr<SimpleBlobDetector> detector = SimpleBlobDetector::create(blobParams);
    
    // Detect blobs
    vector<KeyPoint> keypoints;
    detector->detect(gray, keypoints);
    
    // Convert keypoints to rectangles
    for (const auto& kp : keypoints) {
        int size = static_cast<int>(kp.size);
        Rect rect(kp.pt.x - size/2, kp.pt.y - size/2, size, size);
        detections.push_back(rect);
    }
    
    // Draw detections
    src.copyTo(dst);
    for (const auto& rect : detections) {
        rectangle(dst, rect, Scalar(0, 255, 0), 2);
    }
    
    return detections;
}

/**
 * @brief Function to apply selected detection method
 * @param src Input image
 * @param template Template image (for template matching)
 * @param prevFrame Previous frame (for motion detection)
 * @param dst Output image
 * @param method Detection method
 * @param params Detection parameters
 * @return vector<Rect> Detected regions
 */
vector<Rect> applyDetection(const Mat& src, const Mat& template, const Mat& prevFrame, 
                           Mat& dst, DetectionMethod method, const DetectionParams& params) {
    switch (method) {
        case TEMPLATE_MATCHING:
            return applyTemplateMatching(src, template, dst, params);
        case CONTOUR_DETECTION:
            return applyContourDetection(src, dst, params);
        case COLOR_DETECTION:
            return applyColorDetection(src, dst, params);
        case MOTION_DETECTION:
            return applyMotionDetection(src, prevFrame, dst, params);
        case CORNER_DETECTION:
            return applyCornerDetection(src, dst, params);
        case BLOB_DETECTION:
            return applyBlobDetection(src, dst, params);
        default:
            src.copyTo(dst);
            return vector<Rect>();
    }
}

/**
 * @brief Function to send detection data to MATLAB
 * @param matlabPtr MATLAB engine pointer
 * @param src Original image
 * @param dst Detected image
 * @param detections Detected regions
 * @param method Detection method
 * @param params Detection parameters
 */
void sendDetectionToMATLAB(std::unique_ptr<matlab::engine::MATLABEngine>& matlabPtr, 
                          const Mat& src, const Mat& dst, const vector<Rect>& detections,
                          DetectionMethod method, const DetectionParams& params) {
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
        
        // Detected image
        auto dimsDst = factory.createArray<std::size_t>({1, 3}, 
            {static_cast<std::size_t>(rgbDst.rows), 
             static_cast<std::size_t>(rgbDst.cols), 
             static_cast<std::size_t>(rgbDst.channels())});
        auto matlabDst = factory.createArray<uint8_t>(dimsDst);
        auto dstPtr = matlabDst.release();
        memcpy(dstPtr, rgbDst.data, rgbDst.total() * rgbDst.elemSize());
        
        // Set variables in MATLAB workspace
        matlabPtr->setVariable(u"originalImage", matlabSrc);
        matlabPtr->setVariable(u"detectedImage", matlabDst);
        
        // Execute MATLAB commands
        string methodName = getDetectionMethodName(method);
        string matlabCmd = "figure; subplot(1,2,1); imshow(originalImage); title('Original'); "
                          "subplot(1,2,2); imshow(detectedImage); title('" + methodName + "');";
        matlabPtr->eval(matlab::engine::convertUTF8StringToUTF16String(matlabCmd));
        
        // Display detection information
        matlabPtr->eval(u"fprintf('Detection Method: " + matlab::engine::convertUTF8StringToUTF16String(methodName) + "\\n');");
        matlabPtr->eval(u"fprintf('Number of detections: %d\\n', " + to_string(detections.size()) + u");");
        
        cout << "Detection data sent to MATLAB successfully!" << endl;
        
    } catch (const std::exception& e) {
        cerr << "Error sending detection data to MATLAB: " << e.what() << endl;
    }
}

/**
 * @brief Main function for object detection and tracking
 * @return int Exit status
 */
int main() {
    cout << "=== Object Detection and Tracking - Intermediate Level 13 ===" << endl;
    cout << "This program demonstrates object detection and tracking techniques." << endl;
    
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
        
        // Initialize detection parameters
        DetectionParams detParams;
        detParams.templateThreshold = 0.8;
        detParams.contourAreaThreshold = 1000.0;
        detParams.colorLower = Scalar(0, 50, 50);
        detParams.colorUpper = Scalar(10, 255, 255);
        detParams.motionThreshold = 30.0;
        detParams.cornerMaxCorners = 100;
        detParams.cornerQualityLevel = 0.01;
        detParams.cornerMinDistance = 10.0;
        detParams.blobMinArea = 100.0;
        detParams.blobMaxArea = 10000.0;
        
        // Initialize tracking parameters
        TrackingParams trackParams;
        trackParams.kalmanProcessNoise = 0.03;
        trackParams.kalmanMeasurementNoise = 0.3;
        trackParams.meanShiftMaxIterations = 10;
        trackParams.meanShiftThreshold = 1.0;
        trackParams.camshiftMaxIterations = 10;
        trackParams.camshiftThreshold = 1.0;
        trackParams.mosseLearningRate = 0.125;
        trackParams.csrtLearningRate = 0.01;
        
        // Initialize detection and tracking methods
        DetectionMethod currentDetection = TEMPLATE_MATCHING;
        TrackingMethod currentTracking = NO_TRACKING;
        
        // Create Mat objects for frame processing
        Mat frame, prevFrame, template, detectedFrame, displayFrame;
        vector<Rect> detections;
        
        cout << "\nStarting camera feed with object detection..." << endl;
        cout << "Controls:" << endl;
        cout << "  'q' - Quit" << endl;
        cout << "  '0' - Template Matching" << endl;
        cout << "  '1' - Contour Detection" << endl;
        cout << "  '2' - Color Detection" << endl;
        cout << "  '3' - Motion Detection" << endl;
        cout << "  '4' - Corner Detection" << endl;
        cout << "  '5' - Blob Detection" << endl;
        cout << "  't' - Capture template" << endl;
        cout << "  'm' - Send to MATLAB" << endl;
        cout << "  's' - Save current detection" << endl;
        
        // Main capture loop
        while (true) {
            // Capture frame from camera
            cap >> frame;
            
            // Check if frame was captured successfully
            if (frame.empty()) {
                cerr << "Warning: Could not capture frame!" << endl;
                continue;
            }
            
            // Apply selected detection method
            detections = applyDetection(frame, template, prevFrame, detectedFrame, 
                                     currentDetection, detParams);
            
            // Create display frame
            displayFrame = detectedFrame;
            
            // Create side-by-side comparison
            Mat comparison;
            hconcat(frame, displayFrame, comparison);
            
            // Add labels
            string methodName = getDetectionMethodName(currentDetection);
            putText(comparison, "Original", Point(10, 30), 
                   FONT_HERSHEY_SIMPLEX, 0.7, Scalar(0, 255, 0), 2);
            putText(comparison, methodName, Point(frame.cols + 10, 30), 
                   FONT_HERSHEY_SIMPLEX, 0.7, Scalar(0, 255, 0), 2);
            
            // Add detection information
            stringstream ss;
            ss << "Detections: " << detections.size();
            putText(comparison, ss.str(), Point(10, 60), 
                   FONT_HERSHEY_SIMPLEX, 0.5, Scalar(255, 255, 255), 1);
            
            // Display the comparison
            imshow("Object Detection and Tracking", comparison);
            
            // Handle keyboard input
            char key = waitKey(1) & 0xFF;
            
            if (key == 'q' || key == 27) { // 'q' or ESC to quit
                cout << "Quitting..." << endl;
                break;
            }
            else if (key >= '0' && key <= '5') { // Detection method selection
                currentDetection = static_cast<DetectionMethod>(key - '0');
                cout << "Selected detection method: " << getDetectionMethodName(currentDetection) << endl;
            }
            else if (key == 't') { // Capture template
                template = frame.clone();
                cout << "Template captured!" << endl;
            }
            else if (key == 'm') { // Send to MATLAB
                sendDetectionToMATLAB(matlabPtr, frame, displayFrame, detections, currentDetection, detParams);
            }
            else if (key == 's') { // Save current detection
                string filename = "detection_" + methodName + ".jpg";
                imwrite(filename, displayFrame);
                cout << "Detection saved as: " << filename << endl;
            }
            
            // Store current frame for next iteration
            frame.copyTo(prevFrame);
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
 * g++ -std=c++17 camera_intermediate_13.cpp -o camera_intermediate_13 \
 *     `pkg-config --cflags --libs opencv4` \
 *     -I/Applications/MATLAB_R2023b.app/extern/include \
 *     -L/Applications/MATLAB_R2023b.app/bin/maci64 \
 *     -lMatlabDataArray -lMatlabEngine
 * 
 * @brief Usage:
 * 1. Make sure your camera is connected and working
 * 2. Run the executable: ./camera_intermediate_13
 * 3. Use keyboard controls to switch between detection methods
 * 4. Press 't' to capture a template for template matching
 * 5. Press 'm' to send data to MATLAB
 * 6. Press 's' to save current detection
 * 
 * @brief Learning Objectives:
 * - Understand object detection techniques
 * - Learn template matching and contour detection
 * - Understand color-based and motion-based detection
 * - Learn corner and blob detection
 * - Understand detection parameters and their effects
 * - Learn MATLAB integration for detection analysis
 * - Understand object detection applications
 * - Learn to choose appropriate detection methods
 */
