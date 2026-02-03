/**
 * @file camera_basic_07.cpp
 * @brief Basic Geometric Transformations - Beginner Level 7
 * @description This program demonstrates basic geometric transformations like
 *              rotation, scaling, translation, and flipping using OpenCV
 *              and MATLAB integration for real-time processing.
 * @author Educational C++ MATLAB Integration Project
 * @date 2024
 * @version 1.0
 */

#include <opencv2/opencv.hpp>
#include <iostream>
#include <matlab/engine.hpp>
#include <memory>
#include <cmath>

using namespace cv;
using namespace std;

/**
 * @brief Enumeration for different transformation types
 */
enum TransformationType {
    ORIGINAL = 0,
    ROTATE_90 = 1,
    ROTATE_180 = 2,
    ROTATE_270 = 3,
    SCALE_UP = 4,
    SCALE_DOWN = 5,
    FLIP_HORIZONTAL = 6,
    FLIP_VERTICAL = 7,
    FLIP_BOTH = 8,
    TRANSLATE = 9,
    SHEAR = 10
};

/**
 * @brief Structure to hold transformation parameters
 */
struct TransformationParams {
    double rotationAngle;
    double scaleX;
    double scaleY;
    double translateX;
    double translateY;
    double shearX;
    double shearY;
};

/**
 * @brief Function to get transformation name
 * @param type Transformation type
 * @return string Transformation name
 */
string getTransformationName(TransformationType type) {
    switch (type) {
        case ORIGINAL: return "Original";
        case ROTATE_90: return "Rotate 90°";
        case ROTATE_180: return "Rotate 180°";
        case ROTATE_270: return "Rotate 270°";
        case SCALE_UP: return "Scale Up";
        case SCALE_DOWN: return "Scale Down";
        case FLIP_HORIZONTAL: return "Flip Horizontal";
        case FLIP_VERTICAL: return "Flip Vertical";
        case FLIP_BOTH: return "Flip Both";
        case TRANSLATE: return "Translate";
        case SHEAR: return "Shear";
        default: return "Unknown";
    }
}

/**
 * @brief Function to apply rotation transformation
 * @param src Input image
 * @param dst Output image
 * @param angle Rotation angle in degrees
 */
void applyRotation(const Mat& src, Mat& dst, double angle) {
    Point2f center(src.cols / 2.0, src.rows / 2.0);
    Mat rotationMatrix = getRotationMatrix2D(center, angle, 1.0);
    warpAffine(src, dst, rotationMatrix, src.size());
}

/**
 * @brief Function to apply scaling transformation
 * @param src Input image
 * @param dst Output image
 * @param scaleX X-axis scale factor
 * @param scaleY Y-axis scale factor
 */
void applyScaling(const Mat& src, Mat& dst, double scaleX, double scaleY) {
    resize(src, dst, Size(), scaleX, scaleY, INTER_LINEAR);
}

/**
 * @brief Function to apply translation transformation
 * @param src Input image
 * @param dst Output image
 * @param translateX X translation
 * @param translateY Y translation
 */
void applyTranslation(const Mat& src, Mat& dst, double translateX, double translateY) {
    Mat translationMatrix = (Mat_<double>(2, 3) << 1, 0, translateX, 0, 1, translateY);
    warpAffine(src, dst, translationMatrix, src.size());
}

/**
 * @brief Function to apply shear transformation
 * @param src Input image
 * @param dst Output image
 * @param shearX X shear factor
 * @param shearY Y shear factor
 */
void applyShear(const Mat& src, Mat& dst, double shearX, double shearY) {
    Point2f srcTri[3];
    Point2f dstTri[3];
    
    srcTri[0] = Point2f(0, 0);
    srcTri[1] = Point2f(src.cols - 1, 0);
    srcTri[2] = Point2f(0, src.rows - 1);
    
    dstTri[0] = Point2f(0, 0);
    dstTri[1] = Point2f(src.cols - 1 + shearX * src.rows, 0);
    dstTri[2] = Point2f(0, src.rows - 1 + shearY * src.cols);
    
    Mat warpMatrix = getAffineTransform(srcTri, dstTri);
    warpAffine(src, dst, warpMatrix, src.size());
}

/**
 * @brief Function to apply selected transformation
 * @param src Input image
 * @param dst Output image
 * @param type Transformation type
 * @param params Transformation parameters
 */
void applyTransformation(const Mat& src, Mat& dst, TransformationType type, const TransformationParams& params) {
    switch (type) {
        case ORIGINAL:
            src.copyTo(dst);
            break;
        case ROTATE_90:
            applyRotation(src, dst, 90);
            break;
        case ROTATE_180:
            applyRotation(src, dst, 180);
            break;
        case ROTATE_270:
            applyRotation(src, dst, 270);
            break;
        case SCALE_UP:
            applyScaling(src, dst, 1.5, 1.5);
            break;
        case SCALE_DOWN:
            applyScaling(src, dst, 0.7, 0.7);
            break;
        case FLIP_HORIZONTAL:
            flip(src, dst, 1);
            break;
        case FLIP_VERTICAL:
            flip(src, dst, 0);
            break;
        case FLIP_BOTH:
            flip(src, dst, -1);
            break;
        case TRANSLATE:
            applyTranslation(src, dst, params.translateX, params.translateY);
            break;
        case SHEAR:
            applyShear(src, dst, params.shearX, params.shearY);
            break;
    }
}

/**
 * @brief Function to create transformation matrix visualization
 * @param src Input image
 * @param dst Output image
 * @param type Transformation type
 * @param params Transformation parameters
 * @return Mat Visualization of transformation matrix
 */
Mat createTransformationVisualization(const Mat& src, Mat& dst, TransformationType type, const TransformationParams& params) {
    Mat visualization = Mat::zeros(200, 400, CV_8UC3);
    
    // Draw coordinate axes
    line(visualization, Point(50, 100), Point(350, 100), Scalar(255, 255, 255), 2);
    line(visualization, Point(200, 50), Point(200, 150), Scalar(255, 255, 255), 2);
    
    // Draw transformation matrix representation
    string matrixText;
    switch (type) {
        case ORIGINAL:
            matrixText = "Identity Matrix";
            break;
        case ROTATE_90:
            matrixText = "Rotation 90°";
            break;
        case ROTATE_180:
            matrixText = "Rotation 180°";
            break;
        case ROTATE_270:
            matrixText = "Rotation 270°";
            break;
        case SCALE_UP:
            matrixText = "Scale 1.5x";
            break;
        case SCALE_DOWN:
            matrixText = "Scale 0.7x";
            break;
        case FLIP_HORIZONTAL:
            matrixText = "Flip H";
            break;
        case FLIP_VERTICAL:
            matrixText = "Flip V";
            break;
        case FLIP_BOTH:
            matrixText = "Flip Both";
            break;
        case TRANSLATE:
            matrixText = "Translate";
            break;
        case SHEAR:
            matrixText = "Shear";
            break;
    }
    
    putText(visualization, matrixText, Point(10, 30), 
           FONT_HERSHEY_SIMPLEX, 0.6, Scalar(0, 255, 0), 2);
    
    // Draw transformation parameters
    stringstream ss;
    ss << "Params: " << fixed << setprecision(2);
    switch (type) {
        case TRANSLATE:
            ss << "X=" << params.translateX << " Y=" << params.translateY;
            break;
        case SHEAR:
            ss << "X=" << params.shearX << " Y=" << params.shearY;
            break;
        default:
            ss << "N/A";
            break;
    }
    
    putText(visualization, ss.str(), Point(10, 60), 
           FONT_HERSHEY_SIMPLEX, 0.5, Scalar(255, 255, 255), 1);
    
    return visualization;
}

/**
 * @brief Function to send transformation data to MATLAB
 * @param matlabPtr MATLAB engine pointer
 * @param src Original image
 * @param dst Transformed image
 * @param type Transformation type
 * @param params Transformation parameters
 */
void sendTransformationToMATLAB(std::unique_ptr<matlab::engine::MATLABEngine>& matlabPtr, 
                               const Mat& src, const Mat& dst, TransformationType type, 
                               const TransformationParams& params) {
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
        
        // Transformed image
        auto dimsDst = factory.createArray<std::size_t>({1, 3}, 
            {static_cast<std::size_t>(rgbDst.rows), 
             static_cast<std::size_t>(rgbDst.cols), 
             static_cast<std::size_t>(rgbDst.channels())});
        auto matlabDst = factory.createArray<uint8_t>(dimsDst);
        auto dstPtr = matlabDst.release();
        memcpy(dstPtr, rgbDst.data, rgbDst.total() * rgbDst.elemSize());
        
        // Set variables in MATLAB workspace
        matlabPtr->setVariable(u"originalImage", matlabSrc);
        matlabPtr->setVariable(u"transformedImage", matlabDst);
        
        // Execute MATLAB commands
        string transformationName = getTransformationName(type);
        string matlabCmd = "figure; subplot(1,2,1); imshow(originalImage); title('Original'); "
                          "subplot(1,2,2); imshow(transformedImage); title('" + transformationName + "');";
        matlabPtr->eval(matlab::engine::convertUTF8StringToUTF16String(matlabCmd));
        
        // Display transformation information
        matlabPtr->eval(u"fprintf('Transformation: " + matlab::engine::convertUTF8StringToUTF16String(transformationName) + "\\n');");
        matlabPtr->eval(u"fprintf('Original size: %d x %d\\n', size(originalImage,1), size(originalImage,2));");
        matlabPtr->eval(u"fprintf('Transformed size: %d x %d\\n', size(transformedImage,1), size(transformedImage,2));");
        
        cout << "Transformation data sent to MATLAB successfully!" << endl;
        
    } catch (const std::exception& e) {
        cerr << "Error sending transformation data to MATLAB: " << e.what() << endl;
    }
}

/**
 * @brief Main function for basic geometric transformations
 * @return int Exit status
 */
int main() {
    cout << "=== Basic Geometric Transformations - Beginner Level 7 ===" << endl;
    cout << "This program demonstrates basic geometric transformations." << endl;
    
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
        
        // Initialize transformation parameters
        TransformationParams params;
        params.rotationAngle = 0.0;
        params.scaleX = 1.0;
        params.scaleY = 1.0;
        params.translateX = 50.0;
        params.translateY = 50.0;
        params.shearX = 0.2;
        params.shearY = 0.2;
        
        // Initialize transformation type
        TransformationType currentTransformation = ORIGINAL;
        
        // Create Mat objects for frame processing
        Mat frame, transformedFrame, displayFrame;
        
        cout << "\nStarting camera feed with geometric transformations..." << endl;
        cout << "Controls:" << endl;
        cout << "  'q' - Quit" << endl;
        cout << "  '0' - Original" << endl;
        cout << "  '1' - Rotate 90°" << endl;
        cout << "  '2' - Rotate 180°" << endl;
        cout << "  '3' - Rotate 270°" << endl;
        cout << "  '4' - Scale Up" << endl;
        cout << "  '5' - Scale Down" << endl;
        cout << "  '6' - Flip Horizontal" << endl;
        cout << "  '7' - Flip Vertical" << endl;
        cout << "  '8' - Flip Both" << endl;
        cout << "  '9' - Translate" << endl;
        cout << "  'a' - Shear" << endl;
        cout << "  'm' - Send to MATLAB" << endl;
        cout << "  's' - Save current transformation" << endl;
        
        // Main capture loop
        while (true) {
            // Capture frame from camera
            cap >> frame;
            
            // Check if frame was captured successfully
            if (frame.empty()) {
                cerr << "Warning: Could not capture frame!" << endl;
                continue;
            }
            
            // Apply selected transformation
            applyTransformation(frame, transformedFrame, currentTransformation, params);
            
            // Create display frame
            displayFrame = createTransformationVisualization(frame, transformedFrame, currentTransformation, params);
            
            // Create side-by-side comparison
            Mat comparison;
            hconcat(frame, transformedFrame, comparison);
            
            // Add labels
            string transformationName = getTransformationName(currentTransformation);
            putText(comparison, "Original", Point(10, 30), 
                   FONT_HERSHEY_SIMPLEX, 0.7, Scalar(0, 255, 0), 2);
            putText(comparison, transformationName, Point(frame.cols + 10, 30), 
                   FONT_HERSHEY_SIMPLEX, 0.7, Scalar(0, 255, 0), 2);
            
            // Add transformation information
            putText(comparison, "Press number keys to change transformation", Point(10, 60), 
                   FONT_HERSHEY_SIMPLEX, 0.5, Scalar(255, 255, 255), 1);
            
            // Display the comparison
            imshow("Basic Geometric Transformations", comparison);
            
            // Handle keyboard input
            char key = waitKey(1) & 0xFF;
            
            if (key == 'q' || key == 27) { // 'q' or ESC to quit
                cout << "Quitting..." << endl;
                break;
            }
            else if (key >= '0' && key <= '9') { // Transformation selection
                currentTransformation = static_cast<TransformationType>(key - '0');
                cout << "Selected transformation: " << getTransformationName(currentTransformation) << endl;
            }
            else if (key == 'a') { // Shear transformation
                currentTransformation = SHEAR;
                cout << "Selected transformation: " << getTransformationName(currentTransformation) << endl;
            }
            else if (key == 'm') { // Send to MATLAB
                sendTransformationToMATLAB(matlabPtr, frame, transformedFrame, currentTransformation, params);
            }
            else if (key == 's') { // Save current transformation
                string filename = "transformation_" + transformationName + ".jpg";
                imwrite(filename, transformedFrame);
                cout << "Transformation saved as: " << filename << endl;
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
 * g++ -std=c++17 camera_basic_07.cpp -o camera_basic_07 \
 *     `pkg-config --cflags --libs opencv4` \
 *     -I/Applications/MATLAB_R2023b.app/extern/include \
 *     -L/Applications/MATLAB_R2023b.app/bin/maci64 \
 *     -lMatlabDataArray -lMatlabEngine
 * 
 * @brief Usage:
 * 1. Make sure your camera is connected and working
 * 2. Run the executable: ./camera_basic_07
 * 3. Use keyboard controls to switch between transformations
 * 4. Press 'm' to send transformation data to MATLAB
 * 5. Press 's' to save current transformation
 * 
 * @brief Learning Objectives:
 * - Understand basic geometric transformations
 * - Learn rotation, scaling, and translation
 * - Understand flipping and shearing operations
 * - Learn transformation matrix concepts
 * - Understand affine transformations
 * - Learn MATLAB integration for transformation analysis
 * - Understand transformation parameter effects
 * - Learn to visualize transformation results
 */
