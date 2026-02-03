/**
 * @file camera_basic_05.cpp
 * @brief Basic Image Filters - Beginner Level 5
 * @description This program demonstrates basic image filtering operations like
 *              blur, sharpen, edge detection, and noise reduction using OpenCV
 *              and MATLAB integration for real-time processing.
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
 * @brief Enumeration for different filter types
 */
enum FilterType {
    ORIGINAL = 0,
    GAUSSIAN_BLUR = 1,
    MEDIAN_BLUR = 2,
    BILATERAL_FILTER = 3,
    SHARPEN = 4,
    EDGE_DETECTION = 5,
    NOISE_REDUCTION = 6,
    EMBOSS = 7,
    SOBEL = 8,
    LAPLACIAN = 9
};

/**
 * @brief Structure to hold filter parameters
 */
struct FilterParams {
    int kernelSize;
    double sigma;
    int medianKernelSize;
    int bilateralD;
    double bilateralSigmaColor;
    double bilateralSigmaSpace;
    double sharpenStrength;
    int sobelKernelSize;
    int laplacianKernelSize;
};

/**
 * @brief Function to apply Gaussian blur filter
 * @param src Input image
 * @param dst Output image
 * @param params Filter parameters
 */
void applyGaussianBlur(const Mat& src, Mat& dst, const FilterParams& params) {
    GaussianBlur(src, dst, Size(params.kernelSize, params.kernelSize), params.sigma);
}

/**
 * @brief Function to apply median blur filter
 * @param src Input image
 * @param dst Output image
 * @param params Filter parameters
 */
void applyMedianBlur(const Mat& src, Mat& dst, const FilterParams& params) {
    medianBlur(src, dst, params.medianKernelSize);
}

/**
 * @brief Function to apply bilateral filter
 * @param src Input image
 * @param dst Output image
 * @param params Filter parameters
 */
void applyBilateralFilter(const Mat& src, Mat& dst, const FilterParams& params) {
    bilateralFilter(src, dst, params.bilateralD, params.bilateralSigmaColor, params.bilateralSigmaSpace);
}

/**
 * @brief Function to apply sharpen filter
 * @param src Input image
 * @param dst Output image
 * @param params Filter parameters
 */
void applySharpen(const Mat& src, Mat& dst, const FilterParams& params) {
    Mat kernel = (Mat_<float>(3, 3) << 
        0, -params.sharpenStrength, 0,
        -params.sharpenStrength, 1 + 4 * params.sharpenStrength, -params.sharpenStrength,
        0, -params.sharpenStrength, 0);
    
    filter2D(src, dst, -1, kernel);
}

/**
 * @brief Function to apply edge detection filter
 * @param src Input image
 * @param dst Output image
 * @param params Filter parameters
 */
void applyEdgeDetection(const Mat& src, Mat& dst, const FilterParams& params) {
    Mat gray, edges;
    cvtColor(src, gray, COLOR_BGR2GRAY);
    Canny(gray, edges, 50, 150);
    cvtColor(edges, dst, COLOR_GRAY2BGR);
}

/**
 * @brief Function to apply noise reduction filter
 * @param src Input image
 * @param dst Output image
 * @param params Filter parameters
 */
void applyNoiseReduction(const Mat& src, Mat& dst, const FilterParams& params) {
    Mat temp;
    GaussianBlur(src, temp, Size(3, 3), 0);
    addWeighted(src, 0.7, temp, 0.3, 0, dst);
}

/**
 * @brief Function to apply emboss filter
 * @param src Input image
 * @param dst Output image
 * @param params Filter parameters
 */
void applyEmboss(const Mat& src, Mat& dst, const FilterParams& params) {
    Mat kernel = (Mat_<float>(3, 3) << 
        -2, -1, 0,
        -1, 1, 1,
        0, 1, 2);
    
    filter2D(src, dst, -1, kernel);
    dst = dst + Scalar(128, 128, 128); // Add offset
}

/**
 * @brief Function to apply Sobel filter
 * @param src Input image
 * @param dst Output image
 * @param params Filter parameters
 */
void applySobel(const Mat& src, Mat& dst, const FilterParams& params) {
    Mat gray, grad_x, grad_y, grad;
    cvtColor(src, gray, COLOR_BGR2GRAY);
    
    Sobel(gray, grad_x, CV_64F, 1, 0, params.sobelKernelSize);
    Sobel(gray, grad_y, CV_64F, 0, 1, params.sobelKernelSize);
    
    magnitude(grad_x, grad_y, grad);
    grad.convertTo(grad, CV_8U);
    cvtColor(grad, dst, COLOR_GRAY2BGR);
}

/**
 * @brief Function to apply Laplacian filter
 * @param src Input image
 * @param dst Output image
 * @param params Filter parameters
 */
void applyLaplacian(const Mat& src, Mat& dst, const FilterParams& params) {
    Mat gray, laplacian;
    cvtColor(src, gray, COLOR_BGR2GRAY);
    Laplacian(gray, laplacian, CV_64F, params.laplacianKernelSize);
    laplacian.convertTo(laplacian, CV_8U);
    cvtColor(laplacian, dst, COLOR_GRAY2BGR);
}

/**
 * @brief Function to apply selected filter
 * @param src Input image
 * @param dst Output image
 * @param filterType Type of filter to apply
 * @param params Filter parameters
 */
void applyFilter(const Mat& src, Mat& dst, FilterType filterType, const FilterParams& params) {
    switch (filterType) {
        case ORIGINAL:
            src.copyTo(dst);
            break;
        case GAUSSIAN_BLUR:
            applyGaussianBlur(src, dst, params);
            break;
        case MEDIAN_BLUR:
            applyMedianBlur(src, dst, params);
            break;
        case BILATERAL_FILTER:
            applyBilateralFilter(src, dst, params);
            break;
        case SHARPEN:
            applySharpen(src, dst, params);
            break;
        case EDGE_DETECTION:
            applyEdgeDetection(src, dst, params);
            break;
        case NOISE_REDUCTION:
            applyNoiseReduction(src, dst, params);
            break;
        case EMBOSS:
            applyEmboss(src, dst, params);
            break;
        case SOBEL:
            applySobel(src, dst, params);
            break;
        case LAPLACIAN:
            applyLaplacian(src, dst, params);
            break;
    }
}

/**
 * @brief Function to get filter name as string
 * @param filterType Filter type
 * @return string Filter name
 */
string getFilterName(FilterType filterType) {
    switch (filterType) {
        case ORIGINAL: return "Original";
        case GAUSSIAN_BLUR: return "Gaussian Blur";
        case MEDIAN_BLUR: return "Median Blur";
        case BILATERAL_FILTER: return "Bilateral Filter";
        case SHARPEN: return "Sharpen";
        case EDGE_DETECTION: return "Edge Detection";
        case NOISE_REDUCTION: return "Noise Reduction";
        case EMBOSS: return "Emboss";
        case SOBEL: return "Sobel";
        case LAPLACIAN: return "Laplacian";
        default: return "Unknown";
    }
}

/**
 * @brief Function to send filtered image to MATLAB
 * @param matlabPtr MATLAB engine pointer
 * @param image Filtered image
 * @param filterName Name of the applied filter
 */
void sendFilteredImageToMATLAB(std::unique_ptr<matlab::engine::MATLABEngine>& matlabPtr, 
                              const Mat& image, const string& filterName) {
    try {
        // Convert BGR to RGB for MATLAB
        Mat rgbImage;
        cvtColor(image, rgbImage, COLOR_BGR2RGB);
        
        // Create MATLAB array from OpenCV Mat
        matlab::data::ArrayFactory factory;
        auto dims = factory.createArray<std::size_t>({1, 3}, 
            {static_cast<std::size_t>(rgbImage.rows), 
             static_cast<std::size_t>(rgbImage.cols), 
             static_cast<std::size_t>(rgbImage.channels())});
        
        // Create MATLAB array with image data
        auto matlabImage = factory.createArray<uint8_t>(dims);
        auto imagePtr = matlabImage.release();
        
        // Copy data from OpenCV Mat to MATLAB array
        memcpy(imagePtr, rgbImage.data, rgbImage.total() * rgbImage.elemSize());
        
        // Set variable in MATLAB workspace
        matlabPtr->setVariable(u"filteredImage", matlabImage);
        
        // Execute MATLAB commands
        string matlabCmd = "figure; imshow(filteredImage); title('" + filterName + " Filter Applied');";
        matlabPtr->eval(matlab::engine::convertUTF8StringToUTF16String(matlabCmd));
        
        // Calculate and display image statistics
        matlabPtr->eval(u"fprintf('Filter: " + matlab::engine::convertUTF8StringToUTF16String(filterName) + "\\n');");
        matlabPtr->eval(u"fprintf('Image size: %d x %d x %d\\n', size(filteredImage,1), size(filteredImage,2), size(filteredImage,3));");
        matlabPtr->eval(u"fprintf('Mean values: R=%.2f, G=%.2f, B=%.2f\\n', mean(mean(filteredImage(:,:,1))), mean(mean(filteredImage(:,:,2))), mean(mean(filteredImage(:,:,3))));");
        
        cout << "Filtered image sent to MATLAB successfully!" << endl;
        
    } catch (const std::exception& e) {
        cerr << "Error sending filtered image to MATLAB: " << e.what() << endl;
    }
}

/**
 * @brief Main function for basic image filters
 * @return int Exit status
 */
int main() {
    cout << "=== Basic Image Filters - Beginner Level 5 ===" << endl;
    cout << "This program demonstrates basic image filtering operations." << endl;
    
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
        
        // Initialize filter parameters
        FilterParams params;
        params.kernelSize = 15;
        params.sigma = 2.0;
        params.medianKernelSize = 15;
        params.bilateralD = 15;
        params.bilateralSigmaColor = 80.0;
        params.bilateralSigmaSpace = 80.0;
        params.sharpenStrength = 0.5;
        params.sobelKernelSize = 3;
        params.laplacianKernelSize = 3;
        
        // Initialize filter type
        FilterType currentFilter = ORIGINAL;
        
        // Create Mat objects for frame processing
        Mat frame, filteredFrame, displayFrame;
        
        cout << "\nStarting camera feed with real-time filtering..." << endl;
        cout << "Controls:" << endl;
        cout << "  'q' - Quit" << endl;
        cout << "  '0' - Original (no filter)" << endl;
        cout << "  '1' - Gaussian Blur" << endl;
        cout << "  '2' - Median Blur" << endl;
        cout << "  '3' - Bilateral Filter" << endl;
        cout << "  '4' - Sharpen" << endl;
        cout << "  '5' - Edge Detection" << endl;
        cout << "  '6' - Noise Reduction" << endl;
        cout << "  '7' - Emboss" << endl;
        cout << "  '8' - Sobel" << endl;
        cout << "  '9' - Laplacian" << endl;
        cout << "  '+' - Increase kernel size" << endl;
        cout << "  '-' - Decrease kernel size" << endl;
        cout << "  'm' - Send current filtered image to MATLAB" << endl;
        cout << "  's' - Save current filtered image" << endl;
        
        // Main capture loop
        while (true) {
            // Capture frame from camera
            cap >> frame;
            
            // Check if frame was captured successfully
            if (frame.empty()) {
                cerr << "Warning: Could not capture frame!" << endl;
                continue;
            }
            
            // Apply selected filter
            applyFilter(frame, filteredFrame, currentFilter, params);
            
            // Create display frame with side-by-side comparison
            Mat comparison;
            hconcat(frame, filteredFrame, comparison);
            
            // Add labels
            putText(comparison, "Original", Point(10, 30), 
                   FONT_HERSHEY_SIMPLEX, 0.7, Scalar(0, 255, 0), 2);
            putText(comparison, getFilterName(currentFilter), Point(frame.cols + 10, 30), 
                   FONT_HERSHEY_SIMPLEX, 0.7, Scalar(0, 255, 0), 2);
            
            // Add parameter information
            stringstream ss;
            ss << "Kernel Size: " << params.kernelSize;
            putText(comparison, ss.str(), Point(10, 60), 
                   FONT_HERSHEY_SIMPLEX, 0.5, Scalar(255, 255, 255), 1);
            
            // Display the comparison
            imshow("Basic Image Filters", comparison);
            
            // Handle keyboard input
            char key = waitKey(1) & 0xFF;
            
            if (key == 'q' || key == 27) { // 'q' or ESC to quit
                cout << "Quitting..." << endl;
                break;
            }
            else if (key >= '0' && key <= '9') { // Filter selection
                currentFilter = static_cast<FilterType>(key - '0');
                cout << "Selected filter: " << getFilterName(currentFilter) << endl;
            }
            else if (key == '+') { // Increase kernel size
                params.kernelSize = min(31, params.kernelSize + 2);
                params.medianKernelSize = min(31, params.medianKernelSize + 2);
                params.bilateralD = min(31, params.bilateralD + 2);
                cout << "Kernel size increased to: " << params.kernelSize << endl;
            }
            else if (key == '-') { // Decrease kernel size
                params.kernelSize = max(3, params.kernelSize - 2);
                params.medianKernelSize = max(3, params.medianKernelSize - 2);
                params.bilateralD = max(3, params.bilateralD - 2);
                cout << "Kernel size decreased to: " << params.kernelSize << endl;
            }
            else if (key == 'm') { // Send to MATLAB
                sendFilteredImageToMATLAB(matlabPtr, filteredFrame, getFilterName(currentFilter));
            }
            else if (key == 's') { // Save filtered image
                string filename = "filtered_" + getFilterName(currentFilter) + ".jpg";
                imwrite(filename, filteredFrame);
                cout << "Filtered image saved as: " << filename << endl;
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
 * g++ -std=c++17 camera_basic_05.cpp -o camera_basic_05 \
 *     `pkg-config --cflags --libs opencv4` \
 *     -I/Applications/MATLAB_R2023b.app/extern/include \
 *     -L/Applications/MATLAB_R2023b.app/bin/maci64 \
 *     -lMatlabDataArray -lMatlabEngine
 * 
 * @brief Usage:
 * 1. Make sure your camera is connected and working
 * 2. Run the executable: ./camera_basic_05
 * 3. Use keyboard controls to switch between filters
 * 4. Adjust kernel size with '+' and '-' keys
 * 5. Press 'm' to send filtered image to MATLAB
 * 6. Press 's' to save current filtered image
 * 
 * @brief Learning Objectives:
 * - Understand different types of image filters
 * - Learn kernel-based filtering operations
 * - Understand filter parameters and their effects
 * - Learn real-time filter application
 * - Understand side-by-side comparison display
 * - Learn MATLAB integration for filter analysis
 * - Understand filter performance characteristics
 * - Learn to save filtered results
 */
