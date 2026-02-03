/**
 * @file camera_intermediate_14.cpp
 * @brief Image Segmentation Techniques - Intermediate Level 14
 * @description This program demonstrates various image segmentation techniques
 *              including watershed, grabcut, k-means clustering, and region
 *              growing using OpenCV and MATLAB integration.
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
 * @brief Enumeration for different segmentation methods
 */
enum SegmentationMethod {
    WATERSHED = 0,
    GRABCUT = 1,
    KMEANS = 2,
    REGION_GROWING = 3,
    MEAN_SHIFT = 4,
    FLOOD_FILL = 5,
    THRESHOLD_SEGMENTATION = 6,
    ADAPTIVE_THRESHOLD = 7,
    OTSU_SEGMENTATION = 8
};

/**
 * @brief Structure to hold segmentation parameters
 */
struct SegmentationParams {
    int watershedMarkers;
    int grabcutIterations;
    int kmeansClusters;
    double regionGrowingThreshold;
    int meanShiftSpatialRadius;
    int meanShiftColorRadius;
    int floodFillLoDiff;
    int floodFillUpDiff;
    double thresholdValue;
    int adaptiveBlockSize;
    double adaptiveConstant;
    int otsuThreshold;
};

/**
 * @brief Function to get segmentation method name
 * @param method Segmentation method
 * @return string Method name
 */
string getSegmentationMethodName(SegmentationMethod method) {
    switch (method) {
        case WATERSHED: return "Watershed";
        case GRABCUT: return "GrabCut";
        case KMEANS: return "K-Means";
        case REGION_GROWING: return "Region Growing";
        case MEAN_SHIFT: return "Mean Shift";
        case FLOOD_FILL: return "Flood Fill";
        case THRESHOLD_SEGMENTATION: return "Threshold";
        case ADAPTIVE_THRESHOLD: return "Adaptive Threshold";
        case OTSU_SEGMENTATION: return "Otsu";
        default: return "Unknown";
    }
}

/**
 * @brief Function to apply watershed segmentation
 * @param src Input image
 * @param dst Output segmented image
 * @param params Segmentation parameters
 */
void applyWatershedSegmentation(const Mat& src, Mat& dst, const SegmentationParams& params) {
    // Convert to grayscale
    Mat gray;
    cvtColor(src, gray, COLOR_BGR2GRAY);
    
    // Apply threshold
    Mat binary;
    threshold(gray, binary, 0, 255, THRESH_BINARY_INV + THRESH_OTSU);
    
    // Remove noise
    Mat kernel = getStructuringElement(MORPH_ELLIPSE, Size(3, 3));
    morphologyEx(binary, binary, MORPH_OPEN, kernel);
    
    // Find sure background
    Mat sureBg;
    dilate(binary, sureBg, kernel, Point(-1, -1), 3);
    
    // Find sure foreground
    Mat sureFg;
    distanceTransform(binary, sureFg, DIST_L2, 5);
    threshold(sureFg, sureFg, 0.7 * sureFg, 255, THRESH_BINARY);
    sureFg.convertTo(sureFg, CV_8U);
    
    // Find unknown region
    Mat unknown;
    subtract(sureBg, sureFg, unknown);
    
    // Create markers
    Mat markers;
    connectedComponents(sureFg, markers);
    markers = markers + 1;
    markers.setTo(0, unknown == 255);
    
    // Apply watershed
    watershed(src, markers);
    
    // Create output image
    dst = Mat::zeros(src.size(), CV_8UC3);
    for (int i = 0; i < markers.rows; i++) {
        for (int j = 0; j < markers.cols; j++) {
            int label = markers.at<int>(i, j);
            if (label > 1) {
                dst.at<Vec3b>(i, j) = Vec3b((label * 50) % 255, (label * 100) % 255, (label * 150) % 255);
            }
        }
    }
}

/**
 * @brief Function to apply GrabCut segmentation
 * @param src Input image
 * @param dst Output segmented image
 * @param params Segmentation parameters
 */
void applyGrabCutSegmentation(const Mat& src, Mat& dst, const SegmentationParams& params) {
    // Create mask
    Mat mask = Mat::zeros(src.size(), CV_8UC1);
    
    // Define rectangle for foreground
    Rect rect(50, 50, src.cols - 100, src.rows - 100);
    
    // Apply GrabCut
    Mat bgdModel, fgdModel;
    grabCut(src, mask, rect, bgdModel, fgdModel, params.grabcutIterations, GC_INIT_WITH_RECT);
    
    // Create output image
    dst = Mat::zeros(src.size(), CV_8UC3);
    src.copyTo(dst, mask & 1);
}

/**
 * @brief Function to apply K-means segmentation
 * @param src Input image
 * @param dst Output segmented image
 * @param params Segmentation parameters
 */
void applyKMeansSegmentation(const Mat& src, Mat& dst, const SegmentationParams& params) {
    // Reshape image to 2D
    Mat data = src.reshape(1, src.total());
    data.convertTo(data, CV_32F);
    
    // Apply K-means
    Mat labels, centers;
    kmeans(data, params.kmeansClusters, labels, TermCriteria(TermCriteria::EPS + TermCriteria::COUNT, 10, 1.0), 
           3, KMEANS_PP_CENTERS, centers);
    
    // Reshape labels back to image
    labels = labels.reshape(1, src.rows);
    labels.convertTo(labels, CV_8U);
    
    // Create output image
    dst = Mat::zeros(src.size(), CV_8UC3);
    for (int i = 0; i < src.rows; i++) {
        for (int j = 0; j < src.cols; j++) {
            int label = labels.at<uchar>(i, j);
            dst.at<Vec3b>(i, j) = Vec3b((label * 50) % 255, (label * 100) % 255, (label * 150) % 255);
        }
    }
}

/**
 * @brief Function to apply region growing segmentation
 * @param src Input image
 * @param dst Output segmented image
 * @param params Segmentation parameters
 */
void applyRegionGrowingSegmentation(const Mat& src, Mat& dst, const SegmentationParams& params) {
    // Convert to grayscale
    Mat gray;
    cvtColor(src, gray, COLOR_BGR2GRAY);
    
    // Initialize output
    dst = Mat::zeros(src.size(), CV_8UC3);
    
    // Define seed points
    vector<Point> seeds = {Point(src.cols/4, src.rows/4), 
                          Point(3*src.cols/4, src.rows/4),
                          Point(src.cols/4, 3*src.rows/4),
                          Point(3*src.cols/4, 3*src.rows/4)};
    
    // Apply region growing for each seed
    for (size_t i = 0; i < seeds.size(); i++) {
        Mat visited = Mat::zeros(gray.size(), CV_8UC1);
        queue<Point> queue;
        queue.push(seeds[i]);
        visited.at<uchar>(seeds[i]) = 255;
        
        while (!queue.empty()) {
            Point current = queue.front();
            queue.pop();
            
            // Check neighbors
            for (int dx = -1; dx <= 1; dx++) {
                for (int dy = -1; dy <= 1; dy++) {
                    Point neighbor(current.x + dx, current.y + dy);
                    
                    if (neighbor.x >= 0 && neighbor.x < gray.cols &&
                        neighbor.y >= 0 && neighbor.y < gray.rows &&
                        visited.at<uchar>(neighbor) == 0) {
                        
                        int diff = abs(gray.at<uchar>(current) - gray.at<uchar>(neighbor));
                        if (diff < params.regionGrowingThreshold) {
                            visited.at<uchar>(neighbor) = 255;
                            queue.push(neighbor);
                        }
                    }
                }
            }
        }
        
        // Color the region
        Vec3b color((i * 50) % 255, (i * 100) % 255, (i * 150) % 255);
        dst.setTo(color, visited);
    }
}

/**
 * @brief Function to apply mean shift segmentation
 * @param src Input image
 * @param dst Output segmented image
 * @param params Segmentation parameters
 */
void applyMeanShiftSegmentation(const Mat& src, Mat& dst, const SegmentationParams& params) {
    // Apply mean shift filtering
    Mat filtered;
    pyrMeanShiftFiltering(src, filtered, params.meanShiftSpatialRadius, params.meanShiftColorRadius);
    
    // Convert to grayscale
    Mat gray;
    cvtColor(filtered, gray, COLOR_BGR2GRAY);
    
    // Apply threshold
    Mat binary;
    threshold(gray, binary, 0, 255, THRESH_BINARY_INV + THRESH_OTSU);
    
    // Find contours
    vector<vector<Point>> contours;
    vector<Vec4i> hierarchy;
    findContours(binary, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
    
    // Create output image
    dst = Mat::zeros(src.size(), CV_8UC3);
    for (size_t i = 0; i < contours.size(); i++) {
        Vec3b color((i * 50) % 255, (i * 100) % 255, (i * 150) % 255);
        drawContours(dst, contours, i, color, -1);
    }
}

/**
 * @brief Function to apply flood fill segmentation
 * @param src Input image
 * @param dst Output segmented image
 * @param params Segmentation parameters
 */
void applyFloodFillSegmentation(const Mat& src, Mat& dst, const SegmentationParams& params) {
    // Convert to grayscale
    Mat gray;
    cvtColor(src, gray, COLOR_BGR2GRAY);
    
    // Initialize output
    dst = Mat::zeros(src.size(), CV_8UC3);
    
    // Define seed points
    vector<Point> seeds = {Point(src.cols/4, src.rows/4), 
                          Point(3*src.cols/4, src.rows/4),
                          Point(src.cols/4, 3*src.rows/4),
                          Point(3*src.cols/4, 3*src.rows/4)};
    
    // Apply flood fill for each seed
    for (size_t i = 0; i < seeds.size(); i++) {
        Mat mask = Mat::zeros(src.rows + 2, src.cols + 2, CV_8UC1);
        Scalar newVal((i * 50) % 255, (i * 100) % 255, (i * 150) % 255);
        Scalar loDiff(params.floodFillLoDiff, params.floodFillLoDiff, params.floodFillLoDiff);
        Scalar upDiff(params.floodFillUpDiff, params.floodFillUpDiff, params.floodFillUpDiff);
        
        floodFill(src, mask, seeds[i], newVal, nullptr, loDiff, upDiff, FLOODFILL_FIXED_RANGE);
        
        // Copy flood filled region to output
        Mat region = mask(Rect(1, 1, src.cols, src.rows));
        dst.setTo(newVal, region > 0);
    }
}

/**
 * @brief Function to apply threshold segmentation
 * @param src Input image
 * @param dst Output segmented image
 * @param params Segmentation parameters
 */
void applyThresholdSegmentation(const Mat& src, Mat& dst, const SegmentationParams& params) {
    // Convert to grayscale
    Mat gray;
    cvtColor(src, gray, COLOR_BGR2GRAY);
    
    // Apply threshold
    Mat binary;
    threshold(gray, binary, params.thresholdValue, 255, THRESH_BINARY);
    
    // Create output image
    dst = Mat::zeros(src.size(), CV_8UC3);
    dst.setTo(Scalar(0, 255, 0), binary > 0);
    dst.setTo(Scalar(0, 0, 255), binary == 0);
}

/**
 * @brief Function to apply adaptive threshold segmentation
 * @param src Input image
 * @param dst Output segmented image
 * @param params Segmentation parameters
 */
void applyAdaptiveThresholdSegmentation(const Mat& src, Mat& dst, const SegmentationParams& params) {
    // Convert to grayscale
    Mat gray;
    cvtColor(src, gray, COLOR_BGR2GRAY);
    
    // Apply adaptive threshold
    Mat binary;
    adaptiveThreshold(gray, binary, 255, ADAPTIVE_THRESH_GAUSSIAN_C, THRESH_BINARY, 
                      params.adaptiveBlockSize, params.adaptiveConstant);
    
    // Create output image
    dst = Mat::zeros(src.size(), CV_8UC3);
    dst.setTo(Scalar(0, 255, 0), binary > 0);
    dst.setTo(Scalar(0, 0, 255), binary == 0);
}

/**
 * @brief Function to apply Otsu segmentation
 * @param src Input image
 * @param dst Output segmented image
 * @param params Segmentation parameters
 */
void applyOtsuSegmentation(const Mat& src, Mat& dst, const SegmentationParams& params) {
    // Convert to grayscale
    Mat gray;
    cvtColor(src, gray, COLOR_BGR2GRAY);
    
    // Apply Otsu threshold
    Mat binary;
    threshold(gray, binary, 0, 255, THRESH_BINARY + THRESH_OTSU);
    
    // Create output image
    dst = Mat::zeros(src.size(), CV_8UC3);
    dst.setTo(Scalar(0, 255, 0), binary > 0);
    dst.setTo(Scalar(0, 0, 255), binary == 0);
}

/**
 * @brief Function to apply selected segmentation method
 * @param src Input image
 * @param dst Output segmented image
 * @param method Segmentation method
 * @param params Segmentation parameters
 */
void applySegmentation(const Mat& src, Mat& dst, SegmentationMethod method, 
                      const SegmentationParams& params) {
    switch (method) {
        case WATERSHED:
            applyWatershedSegmentation(src, dst, params);
            break;
        case GRABCUT:
            applyGrabCutSegmentation(src, dst, params);
            break;
        case KMEANS:
            applyKMeansSegmentation(src, dst, params);
            break;
        case REGION_GROWING:
            applyRegionGrowingSegmentation(src, dst, params);
            break;
        case MEAN_SHIFT:
            applyMeanShiftSegmentation(src, dst, params);
            break;
        case FLOOD_FILL:
            applyFloodFillSegmentation(src, dst, params);
            break;
        case THRESHOLD_SEGMENTATION:
            applyThresholdSegmentation(src, dst, params);
            break;
        case ADAPTIVE_THRESHOLD:
            applyAdaptiveThresholdSegmentation(src, dst, params);
            break;
        case OTSU_SEGMENTATION:
            applyOtsuSegmentation(src, dst, params);
            break;
    }
}

/**
 * @brief Function to send segmentation data to MATLAB
 * @param matlabPtr MATLAB engine pointer
 * @param src Original image
 * @param dst Segmented image
 * @param method Segmentation method
 * @param params Segmentation parameters
 */
void sendSegmentationToMATLAB(std::unique_ptr<matlab::engine::MATLABEngine>& matlabPtr, 
                             const Mat& src, const Mat& dst, SegmentationMethod method, 
                             const SegmentationParams& params) {
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
        
        // Segmented image
        auto dimsDst = factory.createArray<std::size_t>({1, 3}, 
            {static_cast<std::size_t>(rgbDst.rows), 
             static_cast<std::size_t>(rgbDst.cols), 
             static_cast<std::size_t>(rgbDst.channels())});
        auto matlabDst = factory.createArray<uint8_t>(dimsDst);
        auto dstPtr = matlabDst.release();
        memcpy(dstPtr, rgbDst.data, rgbDst.total() * rgbDst.elemSize());
        
        // Set variables in MATLAB workspace
        matlabPtr->setVariable(u"originalImage", matlabSrc);
        matlabPtr->setVariable(u"segmentedImage", matlabDst);
        
        // Execute MATLAB commands
        string methodName = getSegmentationMethodName(method);
        string matlabCmd = "figure; subplot(1,2,1); imshow(originalImage); title('Original'); "
                          "subplot(1,2,2); imshow(segmentedImage); title('" + methodName + " Segmentation');";
        matlabPtr->eval(matlab::engine::convertUTF8StringToUTF16String(matlabCmd));
        
        // Display segmentation information
        matlabPtr->eval(u"fprintf('Segmentation Method: " + matlab::engine::convertUTF8StringToUTF16String(methodName) + "\\n');");
        
        if (method == KMEANS) {
            matlabPtr->eval(u"fprintf('Number of clusters: %d\\n', " + to_string(params.kmeansClusters) + u");");
        }
        
        cout << "Segmentation data sent to MATLAB successfully!" << endl;
        
    } catch (const std::exception& e) {
        cerr << "Error sending segmentation data to MATLAB: " << e.what() << endl;
    }
}

/**
 * @brief Main function for image segmentation techniques
 * @return int Exit status
 */
int main() {
    cout << "=== Image Segmentation Techniques - Intermediate Level 14 ===" << endl;
    cout << "This program demonstrates various image segmentation techniques." << endl;
    
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
        
        // Initialize segmentation parameters
        SegmentationParams params;
        params.watershedMarkers = 10;
        params.grabcutIterations = 5;
        params.kmeansClusters = 4;
        params.regionGrowingThreshold = 30.0;
        params.meanShiftSpatialRadius = 20;
        params.meanShiftColorRadius = 20;
        params.floodFillLoDiff = 20;
        params.floodFillUpDiff = 20;
        params.thresholdValue = 127.0;
        params.adaptiveBlockSize = 11;
        params.adaptiveConstant = 2.0;
        params.otsuThreshold = 0;
        
        // Initialize segmentation method
        SegmentationMethod currentMethod = WATERSHED;
        
        // Create Mat objects for frame processing
        Mat frame, segmentedFrame, displayFrame;
        
        cout << "\nStarting camera feed with image segmentation..." << endl;
        cout << "Controls:" << endl;
        cout << "  'q' - Quit" << endl;
        cout << "  '0' - Watershed" << endl;
        cout << "  '1' - GrabCut" << endl;
        cout << "  '2' - K-Means" << endl;
        cout << "  '3' - Region Growing" << endl;
        cout << "  '4' - Mean Shift" << endl;
        cout << "  '5' - Flood Fill" << endl;
        cout << "  '6' - Threshold" << endl;
        cout << "  '7' - Adaptive Threshold" << endl;
        cout << "  '8' - Otsu" << endl;
        cout << "  'm' - Send to MATLAB" << endl;
        cout << "  's' - Save current segmentation" << endl;
        
        // Main capture loop
        while (true) {
            // Capture frame from camera
            cap >> frame;
            
            // Check if frame was captured successfully
            if (frame.empty()) {
                cerr << "Warning: Could not capture frame!" << endl;
                continue;
            }
            
            // Apply selected segmentation method
            applySegmentation(frame, segmentedFrame, currentMethod, params);
            
            // Create display frame
            displayFrame = segmentedFrame;
            
            // Create side-by-side comparison
            Mat comparison;
            hconcat(frame, displayFrame, comparison);
            
            // Add labels
            string methodName = getSegmentationMethodName(currentMethod);
            putText(comparison, "Original", Point(10, 30), 
                   FONT_HERSHEY_SIMPLEX, 0.7, Scalar(0, 255, 0), 2);
            putText(comparison, methodName, Point(frame.cols + 10, 30), 
                   FONT_HERSHEY_SIMPLEX, 0.7, Scalar(0, 255, 0), 2);
            
            // Add parameter information
            if (currentMethod == KMEANS) {
                stringstream ss;
                ss << "Clusters: " << params.kmeansClusters;
                putText(comparison, ss.str(), Point(10, 60), 
                       FONT_HERSHEY_SIMPLEX, 0.5, Scalar(255, 255, 255), 1);
            }
            
            // Display the comparison
            imshow("Image Segmentation Techniques", comparison);
            
            // Handle keyboard input
            char key = waitKey(1) & 0xFF;
            
            if (key == 'q' || key == 27) { // 'q' or ESC to quit
                cout << "Quitting..." << endl;
                break;
            }
            else if (key >= '0' && key <= '8') { // Method selection
                currentMethod = static_cast<SegmentationMethod>(key - '0');
                cout << "Selected method: " << getSegmentationMethodName(currentMethod) << endl;
            }
            else if (key == 'm') { // Send to MATLAB
                sendSegmentationToMATLAB(matlabPtr, frame, displayFrame, currentMethod, params);
            }
            else if (key == 's') { // Save current segmentation
                string filename = "segmentation_" + methodName + ".jpg";
                imwrite(filename, displayFrame);
                cout << "Segmentation saved as: " << filename << endl;
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
 * g++ -std=c++17 camera_intermediate_14.cpp -o camera_intermediate_14 \
 *     `pkg-config --cflags --libs opencv4` \
 *     -I/Applications/MATLAB_R2023b.app/extern/include \
 *     -L/Applications/MATLAB_R2023b.app/bin/maci64 \
 *     -lMatlabDataArray -lMatlabEngine
 * 
 * @brief Usage:
 * 1. Make sure your camera is connected and working
 * 2. Run the executable: ./camera_intermediate_14
 * 3. Use keyboard controls to switch between segmentation methods
 * 4. Press 'm' to send data to MATLAB
 * 5. Press 's' to save current segmentation
 * 
 * @brief Learning Objectives:
 * - Understand image segmentation techniques
 * - Learn watershed, GrabCut, and K-means segmentation
 * - Understand region growing and mean shift
 * - Learn flood fill and threshold segmentation
 * - Understand segmentation parameters and their effects
 * - Learn MATLAB integration for segmentation analysis
 * - Understand segmentation applications in computer vision
 * - Learn to choose appropriate segmentation methods
 */
