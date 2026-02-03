/**
 * @file camera_intermediate_12.cpp
 * @brief Feature Detection and Matching - Intermediate Level 12
 * @description This program demonstrates feature detection and matching using
 *              SIFT, SURF, ORB, and other feature detectors with OpenCV
 *              and MATLAB integration for real-time analysis.
 * @author Educational C++ MATLAB Integration Project
 * @date 2024
 * @version 1.0
 */

#include <opencv2/opencv.hpp>
#include <opencv2/features2d.hpp>
#include <opencv2/xfeatures2d.hpp>
#include <iostream>
#include <matlab/engine.hpp>
#include <memory>
#include <vector>
#include <algorithm>

using namespace cv;
using namespace std;

/**
 * @brief Enumeration for different feature detection methods
 */
enum FeatureDetectionMethod {
    SIFT = 0,
    SURF = 1,
    ORB = 2,
    BRISK = 3,
    AKAZE = 4,
    KAZE = 5,
    FAST = 6,
    HARRIS = 7,
    MSER = 8,
    GFTT = 9
};

/**
 * @brief Structure to hold feature detection parameters
 */
struct FeatureDetectionParams {
    int siftFeatures;
    double surfHessianThreshold;
    int orbFeatures;
    int briskThreshold;
    int akazeThreshold;
    double kazeThreshold;
    int fastThreshold;
    double harrisThreshold;
    int mserDelta;
    int gfttMaxCorners;
};

/**
 * @brief Function to get feature detection method name
 * @param method Feature detection method
 * @return string Method name
 */
string getFeatureDetectionMethodName(FeatureDetectionMethod method) {
    switch (method) {
        case SIFT: return "SIFT";
        case SURF: return "SURF";
        case ORB: return "ORB";
        case BRISK: return "BRISK";
        case AKAZE: return "AKAZE";
        case KAZE: return "KAZE";
        case FAST: return "FAST";
        case HARRIS: return "Harris";
        case MSER: return "MSER";
        case GFTT: return "GFTT";
        default: return "Unknown";
    }
}

/**
 * @brief Function to create SIFT detector
 * @param params Feature detection parameters
 * @return Ptr<SIFT> SIFT detector
 */
Ptr<SIFT> createSIFTDetector(const FeatureDetectionParams& params) {
    return SIFT::create(params.siftFeatures);
}

/**
 * @brief Function to create SURF detector
 * @param params Feature detection parameters
 * @return Ptr<SURF> SURF detector
 */
Ptr<SURF> createSURFDetector(const FeatureDetectionParams& params) {
    return SURF::create(params.surfHessianThreshold);
}

/**
 * @brief Function to create ORB detector
 * @param params Feature detection parameters
 * @return Ptr<ORB> ORB detector
 */
Ptr<ORB> createORBDetector(const FeatureDetectionParams& params) {
    return ORB::create(params.orbFeatures);
}

/**
 * @brief Function to create BRISK detector
 * @param params Feature detection parameters
 * @return Ptr<BRISK> BRISK detector
 */
Ptr<BRISK> createBRISKDetector(const FeatureDetectionParams& params) {
    return BRISK::create(params.briskThreshold);
}

/**
 * @brief Function to create AKAZE detector
 * @param params Feature detection parameters
 * @return Ptr<AKAZE> AKAZE detector
 */
Ptr<AKAZE> createAKAZEDetector(const FeatureDetectionParams& params) {
    return AKAZE::create(params.akazeThreshold);
}

/**
 * @brief Function to create KAZE detector
 * @param params Feature detection parameters
 * @return Ptr<KAZE> KAZE detector
 */
Ptr<KAZE> createKAZEDetector(const FeatureDetectionParams& params) {
    return KAZE::create(false, false, params.kazeThreshold);
}

/**
 * @brief Function to create FAST detector
 * @param params Feature detection parameters
 * @return Ptr<FastFeatureDetector> FAST detector
 */
Ptr<FastFeatureDetector> createFASTDetector(const FeatureDetectionParams& params) {
    return FastFeatureDetector::create(params.fastThreshold);
}

/**
 * @brief Function to create Harris detector
 * @param params Feature detection parameters
 * @return Ptr<HarrisDetector> Harris detector
 */
Ptr<HarrisDetector> createHarrisDetector(const FeatureDetectionParams& params) {
    return HarrisDetector::create(params.harrisThreshold);
}

/**
 * @brief Function to create MSER detector
 * @param params Feature detection parameters
 * @return Ptr<MSER> MSER detector
 */
Ptr<MSER> createMSERDetector(const FeatureDetectionParams& params) {
    return MSER::create(params.mserDelta);
}

/**
 * @brief Function to create GFTT detector
 * @param params Feature detection parameters
 * @return Ptr<GFTTDetector> GFTT detector
 */
Ptr<GFTTDetector> createGFTTDetector(const FeatureDetectionParams& params) {
    return GFTTDetector::create(params.gfttMaxCorners);
}

/**
 * @brief Function to detect features using selected method
 * @param src Input image
 * @param keypoints Output keypoints
 * @param descriptors Output descriptors
 * @param method Feature detection method
 * @param params Feature detection parameters
 */
void detectFeatures(const Mat& src, vector<KeyPoint>& keypoints, Mat& descriptors, 
                   FeatureDetectionMethod method, const FeatureDetectionParams& params) {
    Ptr<Feature2D> detector;
    
    switch (method) {
        case SIFT:
            detector = createSIFTDetector(params);
            break;
        case SURF:
            detector = createSURFDetector(params);
            break;
        case ORB:
            detector = createORBDetector(params);
            break;
        case BRISK:
            detector = createBRISKDetector(params);
            break;
        case AKAZE:
            detector = createAKAZEDetector(params);
            break;
        case KAZE:
            detector = createKAZEDetector(params);
            break;
        case FAST:
            detector = createFASTDetector(params);
            break;
        case HARRIS:
            detector = createHarrisDetector(params);
            break;
        case MSER:
            detector = createMSERDetector(params);
            break;
        case GFTT:
            detector = createGFTTDetector(params);
            break;
    }
    
    detector->detectAndCompute(src, noArray(), keypoints, descriptors);
}

/**
 * @brief Function to match features between two images
 * @param descriptors1 Descriptors from first image
 * @param descriptors2 Descriptors from second image
 * @param matches Output matches
 * @param method Feature detection method
 */
void matchFeatures(const Mat& descriptors1, const Mat& descriptors2, 
                  vector<DMatch>& matches, FeatureDetectionMethod method) {
    Ptr<DescriptorMatcher> matcher;
    
    switch (method) {
        case SIFT:
        case SURF:
            matcher = BFMatcher::create(NORM_L2);
            break;
        case ORB:
        case BRISK:
        case AKAZE:
        case KAZE:
        case FAST:
        case HARRIS:
        case MSER:
        case GFTT:
            matcher = BFMatcher::create(NORM_HAMMING);
            break;
    }
    
    matcher->match(descriptors1, descriptors2, matches);
}

/**
 * @brief Function to filter matches using ratio test
 * @param matches Input matches
 * @param goodMatches Output filtered matches
 * @param ratioThreshold Ratio threshold for filtering
 */
void filterMatches(const vector<DMatch>& matches, vector<DMatch>& goodMatches, 
                  double ratioThreshold = 0.75) {
    goodMatches.clear();
    
    for (size_t i = 0; i < matches.size(); i++) {
        if (matches[i].distance < ratioThreshold * matches[i].distance) {
            goodMatches.push_back(matches[i]);
        }
    }
}

/**
 * @brief Function to draw features and matches
 * @param src1 First image
 * @param keypoints1 Keypoints from first image
 * @param src2 Second image
 * @param keypoints2 Keypoints from second image
 * @param matches Matches between images
 * @param dst Output image with drawn features and matches
 */
void drawFeaturesAndMatches(const Mat& src1, const vector<KeyPoint>& keypoints1,
                           const Mat& src2, const vector<KeyPoint>& keypoints2,
                           const vector<DMatch>& matches, Mat& dst) {
    drawMatches(src1, keypoints1, src2, keypoints2, matches, dst, 
                Scalar::all(-1), Scalar::all(-1), vector<char>(), 
                DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS);
}

/**
 * @brief Function to draw keypoints on image
 * @param src Input image
 * @param keypoints Input keypoints
 * @param dst Output image with drawn keypoints
 */
void drawKeypoints(const Mat& src, const vector<KeyPoint>& keypoints, Mat& dst) {
    drawKeypoints(src, keypoints, dst, Scalar::all(-1), DrawMatchesFlags::DRAW_RICH_KEYPOINTS);
}

/**
 * @brief Function to send feature detection data to MATLAB
 * @param matlabPtr MATLAB engine pointer
 * @param src Original image
 * @param keypoints Detected keypoints
 * @param descriptors Feature descriptors
 * @param method Feature detection method
 * @param params Feature detection parameters
 */
void sendFeatureDetectionToMATLAB(std::unique_ptr<matlab::engine::MATLABEngine>& matlabPtr, 
                                 const Mat& src, const vector<KeyPoint>& keypoints, 
                                 const Mat& descriptors, FeatureDetectionMethod method, 
                                 const FeatureDetectionParams& params) {
    try {
        // Convert BGR to RGB for MATLAB
        Mat rgbSrc;
        cvtColor(src, rgbSrc, COLOR_BGR2RGB);
        
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
        
        // Set variables in MATLAB workspace
        matlabPtr->setVariable(u"originalImage", matlabSrc);
        
        // Execute MATLAB commands
        string methodName = getFeatureDetectionMethodName(method);
        string matlabCmd = "figure; imshow(originalImage); title('" + methodName + " Feature Detection');";
        matlabPtr->eval(matlab::engine::convertUTF8StringToUTF16String(matlabCmd));
        
        // Display feature detection information
        matlabPtr->eval(u"fprintf('Feature Detection Method: " + matlab::engine::convertUTF8StringToUTF16String(methodName) + "\\n');");
        matlabPtr->eval(u"fprintf('Number of keypoints detected: %d\\n', " + to_string(keypoints.size()) + u");");
        matlabPtr->eval(u"fprintf('Descriptor size: %d x %d\\n', " + to_string(descriptors.rows) + u", " + to_string(descriptors.cols) + u");");
        
        cout << "Feature detection data sent to MATLAB successfully!" << endl;
        
    } catch (const std::exception& e) {
        cerr << "Error sending feature detection data to MATLAB: " << e.what() << endl;
    }
}

/**
 * @brief Main function for feature detection and matching
 * @return int Exit status
 */
int main() {
    cout << "=== Feature Detection and Matching - Intermediate Level 12 ===" << endl;
    cout << "This program demonstrates feature detection and matching techniques." << endl;
    
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
        
        // Initialize feature detection parameters
        FeatureDetectionParams params;
        params.siftFeatures = 1000;
        params.surfHessianThreshold = 400.0;
        params.orbFeatures = 1000;
        params.briskThreshold = 30;
        params.akazeThreshold = 0.001;
        params.kazeThreshold = 0.001;
        params.fastThreshold = 10;
        params.harrisThreshold = 0.04;
        params.mserDelta = 5;
        params.gfttMaxCorners = 1000;
        
        // Initialize feature detection method
        FeatureDetectionMethod currentMethod = SIFT;
        
        // Create Mat objects for frame processing
        Mat frame, grayFrame, featureImage, displayFrame;
        vector<KeyPoint> keypoints;
        Mat descriptors;
        
        // Store previous frame for matching
        Mat prevFrame, prevGrayFrame;
        vector<KeyPoint> prevKeypoints;
        Mat prevDescriptors;
        vector<DMatch> matches;
        
        cout << "\nStarting camera feed with feature detection..." << endl;
        cout << "Controls:" << endl;
        cout << "  'q' - Quit" << endl;
        cout << "  '0' - SIFT" << endl;
        cout << "  '1' - SURF" << endl;
        cout << "  '2' - ORB" << endl;
        cout << "  '3' - BRISK" << endl;
        cout << "  '4' - AKAZE" << endl;
        cout << "  '5' - KAZE" << endl;
        cout << "  '6' - FAST" << endl;
        cout << "  '7' - Harris" << endl;
        cout << "  '8' - MSER" << endl;
        cout << "  '9' - GFTT" << endl;
        cout << "  'm' - Send to MATLAB" << endl;
        cout << "  's' - Save current feature detection" << endl;
        cout << "  't' - Toggle feature matching" << endl;
        
        bool showMatching = false;
        
        // Main capture loop
        while (true) {
            // Capture frame from camera
            cap >> frame;
            
            // Check if frame was captured successfully
            if (frame.empty()) {
                cerr << "Warning: Could not capture frame!" << endl;
                continue;
            }
            
            // Convert to grayscale for feature detection
            cvtColor(frame, grayFrame, COLOR_BGR2GRAY);
            
            // Detect features
            detectFeatures(grayFrame, keypoints, descriptors, currentMethod, params);
            
            // Create feature visualization
            drawKeypoints(frame, keypoints, featureImage);
            
            // Perform feature matching if enabled
            if (showMatching && !prevFrame.empty()) {
                matchFeatures(prevDescriptors, descriptors, matches, currentMethod);
                
                // Filter matches
                vector<DMatch> goodMatches;
                filterMatches(matches, goodMatches);
                
                // Draw matches
                drawFeaturesAndMatches(prevFrame, prevKeypoints, frame, keypoints, goodMatches, displayFrame);
            } else {
                displayFrame = featureImage;
            }
            
            // Create side-by-side comparison
            Mat comparison;
            hconcat(frame, displayFrame, comparison);
            
            // Add labels
            string methodName = getFeatureDetectionMethodName(currentMethod);
            putText(comparison, "Original", Point(10, 30), 
                   FONT_HERSHEY_SIMPLEX, 0.7, Scalar(0, 255, 0), 2);
            putText(comparison, methodName, Point(frame.cols + 10, 30), 
                   FONT_HERSHEY_SIMPLEX, 0.7, Scalar(0, 255, 0), 2);
            
            // Add feature information
            stringstream ss;
            ss << "Keypoints: " << keypoints.size();
            putText(comparison, ss.str(), Point(10, 60), 
                   FONT_HERSHEY_SIMPLEX, 0.5, Scalar(255, 255, 255), 1);
            
            if (showMatching && !prevFrame.empty()) {
                ss.str("");
                ss << "Matches: " << matches.size();
                putText(comparison, ss.str(), Point(10, 80), 
                       FONT_HERSHEY_SIMPLEX, 0.5, Scalar(255, 255, 255), 1);
            }
            
            // Display the comparison
            imshow("Feature Detection and Matching", comparison);
            
            // Handle keyboard input
            char key = waitKey(1) & 0xFF;
            
            if (key == 'q' || key == 27) { // 'q' or ESC to quit
                cout << "Quitting..." << endl;
                break;
            }
            else if (key >= '0' && key <= '9') { // Method selection
                currentMethod = static_cast<FeatureDetectionMethod>(key - '0');
                cout << "Selected method: " << getFeatureDetectionMethodName(currentMethod) << endl;
            }
            else if (key == 'm') { // Send to MATLAB
                sendFeatureDetectionToMATLAB(matlabPtr, frame, keypoints, descriptors, currentMethod, params);
            }
            else if (key == 's') { // Save current feature detection
                string filename = "feature_detection_" + methodName + ".jpg";
                imwrite(filename, displayFrame);
                cout << "Feature detection saved as: " << filename << endl;
            }
            else if (key == 't') { // Toggle feature matching
                showMatching = !showMatching;
                cout << "Feature matching: " << (showMatching ? "ON" : "OFF") << endl;
            }
            
            // Store current frame for next iteration
            frame.copyTo(prevFrame);
            grayFrame.copyTo(prevGrayFrame);
            keypoints.assign(prevKeypoints.begin(), prevKeypoints.end());
            descriptors.copyTo(prevDescriptors);
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
 * g++ -std=c++17 camera_intermediate_12.cpp -o camera_intermediate_12 \
 *     `pkg-config --cflags --libs opencv4` \
 *     -I/Applications/MATLAB_R2023b.app/extern/include \
 *     -L/Applications/MATLAB_R2023b.app/bin/maci64 \
 *     -lMatlabDataArray -lMatlabEngine
 * 
 * @brief Usage:
 * 1. Make sure your camera is connected and working
 * 2. Run the executable: ./camera_intermediate_12
 * 3. Use keyboard controls to switch between feature detection methods
 * 4. Press 't' to toggle feature matching
 * 5. Press 'm' to send data to MATLAB
 * 6. Press 's' to save current feature detection
 * 
 * @brief Learning Objectives:
 * - Understand feature detection algorithms
 * - Learn SIFT, SURF, ORB, and other feature detectors
 * - Understand feature descriptors and matching
 * - Learn feature matching techniques
 * - Understand feature detection parameters
 * - Learn MATLAB integration for feature analysis
 * - Understand feature detection applications
 * - Learn to choose appropriate feature detectors
 */
