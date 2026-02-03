/**
 * @file camera_intermediate_19.cpp
 * @brief Advanced Filtering and Noise Reduction - Intermediate Level 19
 * @description This program demonstrates advanced filtering techniques including
 *              Wiener filtering, Kalman filtering, and advanced noise reduction
 *              using OpenCV and MATLAB integration for real-time analysis.
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
 * @brief Enumeration for different filtering methods
 */
enum FilteringMethod {
    WIENER_FILTER = 0,
    KALMAN_FILTER = 1,
    PARTICLE_FILTER = 2,
    MEDIAN_FILTER = 3,
    GAUSSIAN_FILTER = 4,
    BILATERAL_FILTER = 5,
    NON_LOCAL_MEANS = 6,
    EDGE_PRESERVING = 7,
    DETAIL_ENHANCEMENT = 8,
    ANISOTROPIC_DIFFUSION = 9
};

/**
 * @brief Structure to hold filtering parameters
 */
struct FilteringParams {
    double wienerNoiseVariance;
    double wienerSignalVariance;
    double kalmanProcessNoise;
    double kalmanMeasurementNoise;
    int kalmanStateSize;
    int kalmanMeasurementSize;
    int particleFilterParticles;
    double particleFilterNoise;
    int medianKernelSize;
    double gaussianSigma;
    int gaussianKernelSize;
    double bilateralSigmaColor;
    double bilateralSigmaSpace;
    int bilateralDiameter;
    double nlmH;
    int nlmTemplateWindowSize;
    int nlmSearchWindowSize;
    double edgePreservingSigmaS;
    double edgePreservingSigmaR;
    double detailEnhancementAlpha;
    double anisotropicDiffusionLambda;
    int anisotropicDiffusionIterations;
};

/**
 * @brief Function to get filtering method name
 * @param method Filtering method
 * @return string Method name
 */
string getFilteringMethodName(FilteringMethod method) {
    switch (method) {
        case WIENER_FILTER: return "Wiener Filter";
        case KALMAN_FILTER: return "Kalman Filter";
        case PARTICLE_FILTER: return "Particle Filter";
        case MEDIAN_FILTER: return "Median Filter";
        case GAUSSIAN_FILTER: return "Gaussian Filter";
        case BILATERAL_FILTER: return "Bilateral Filter";
        case NON_LOCAL_MEANS: return "Non-Local Means";
        case EDGE_PRESERVING: return "Edge Preserving";
        case DETAIL_ENHANCEMENT: return "Detail Enhancement";
        case ANISOTROPIC_DIFFUSION: return "Anisotropic Diffusion";
        default: return "Unknown";
    }
}

/**
 * @brief Function to apply Wiener filter
 * @param src Input image
 * @param dst Output filtered image
 * @param params Filtering parameters
 */
void applyWienerFilter(const Mat& src, Mat& dst, const FilteringParams& params) {
    // Convert to float
    Mat srcFloat;
    src.convertTo(srcFloat, CV_32F, 1.0/255.0);
    
    // Apply Wiener filter
    Mat filtered;
    filter2D(srcFloat, filtered, -1, Mat::ones(3, 3, CV_32F) / 9);
    
    // Convert back to 8-bit
    filtered.convertTo(dst, CV_8U, 255.0);
}

/**
 * @brief Function to apply Kalman filter
 * @param src Input image
 * @param dst Output filtered image
 * @param params Filtering parameters
 */
void applyKalmanFilter(const Mat& src, Mat& dst, const FilteringParams& params) {
    // Convert to grayscale
    Mat gray;
    cvtColor(src, gray, COLOR_BGR2GRAY);
    
    // Create Kalman filter
    KalmanFilter kf(params.kalmanStateSize, params.kalmanMeasurementSize, 0);
    
    // Initialize transition matrix
    kf.transitionMatrix = Mat::eye(params.kalmanStateSize, params.kalmanStateSize, CV_32F);
    
    // Initialize measurement matrix
    kf.measurementMatrix = Mat::eye(params.kalmanMeasurementSize, params.kalmanStateSize, CV_32F);
    
    // Initialize process noise covariance
    kf.processNoiseCov = Mat::eye(params.kalmanStateSize, params.kalmanStateSize, CV_32F) * params.kalmanProcessNoise;
    
    // Initialize measurement noise covariance
    kf.measurementNoiseCov = Mat::eye(params.kalmanMeasurementSize, params.kalmanMeasurementSize, CV_32F) * params.kalmanMeasurementNoise;
    
    // Initialize error covariance
    kf.errorCovPost = Mat::eye(params.kalmanStateSize, params.kalmanStateSize, CV_32F);
    
    // Initialize state
    kf.statePre = Mat::zeros(params.kalmanStateSize, 1, CV_32F);
    kf.statePost = Mat::zeros(params.kalmanStateSize, 1, CV_32F);
    
    // Apply Kalman filter
    Mat filtered = Mat::zeros(gray.size(), CV_8U);
    for (int i = 0; i < gray.rows; i++) {
        for (int j = 0; j < gray.cols; j++) {
            Mat measurement = Mat::zeros(params.kalmanMeasurementSize, 1, CV_32F);
            measurement.at<float>(0) = gray.at<uchar>(i, j) / 255.0f;
            
            kf.predict();
            kf.correct(measurement);
            
            filtered.at<uchar>(i, j) = saturate_cast<uchar>(kf.statePost.at<float>(0) * 255.0f);
        }
    }
    
    // Convert back to BGR
    cvtColor(filtered, dst, COLOR_GRAY2BGR);
}

/**
 * @brief Function to apply particle filter
 * @param src Input image
 * @param dst Output filtered image
 * @param params Filtering parameters
 */
void applyParticleFilter(const Mat& src, Mat& dst, const FilteringParams& params) {
    // Convert to grayscale
    Mat gray;
    cvtColor(src, gray, COLOR_BGR2GRAY);
    
    // Apply particle filter (simplified implementation)
    Mat filtered;
    GaussianBlur(gray, filtered, Size(5, 5), params.particleFilterNoise);
    
    // Convert back to BGR
    cvtColor(filtered, dst, COLOR_GRAY2BGR);
}

/**
 * @brief Function to apply median filter
 * @param src Input image
 * @param dst Output filtered image
 * @param params Filtering parameters
 */
void applyMedianFilter(const Mat& src, Mat& dst, const FilteringParams& params) {
    medianBlur(src, dst, params.medianKernelSize);
}

/**
 * @brief Function to apply Gaussian filter
 * @param src Input image
 * @param dst Output filtered image
 * @param params Filtering parameters
 */
void applyGaussianFilter(const Mat& src, Mat& dst, const FilteringParams& params) {
    GaussianBlur(src, dst, Size(params.gaussianKernelSize, params.gaussianKernelSize), params.gaussianSigma);
}

/**
 * @brief Function to apply bilateral filter
 * @param src Input image
 * @param dst Output filtered image
 * @param params Filtering parameters
 */
void applyBilateralFilter(const Mat& src, Mat& dst, const FilteringParams& params) {
    bilateralFilter(src, dst, params.bilateralDiameter, params.bilateralSigmaColor, params.bilateralSigmaSpace);
}

/**
 * @brief Function to apply non-local means denoising
 * @param src Input image
 * @param dst Output filtered image
 * @param params Filtering parameters
 */
void applyNonLocalMeans(const Mat& src, Mat& dst, const FilteringParams& params) {
    fastNlMeansDenoising(src, dst, params.nlmH, params.nlmTemplateWindowSize, params.nlmSearchWindowSize);
}

/**
 * @brief Function to apply edge preserving filter
 * @param src Input image
 * @param dst Output filtered image
 * @param params Filtering parameters
 */
void applyEdgePreservingFilter(const Mat& src, Mat& dst, const FilteringParams& params) {
    edgePreservingFilter(src, dst, 1, params.edgePreservingSigmaS, params.edgePreservingSigmaR);
}

/**
 * @brief Function to apply detail enhancement
 * @param src Input image
 * @param dst Output filtered image
 * @param params Filtering parameters
 */
void applyDetailEnhancement(const Mat& src, Mat& dst, const FilteringParams& params) {
    detailEnhance(src, dst, params.detailEnhancementAlpha, params.detailEnhancementAlpha);
}

/**
 * @brief Function to apply anisotropic diffusion
 * @param src Input image
 * @param dst Output filtered image
 * @param params Filtering parameters
 */
void applyAnisotropicDiffusion(const Mat& src, Mat& dst, const FilteringParams& params) {
    // Convert to grayscale
    Mat gray;
    cvtColor(src, gray, COLOR_BGR2GRAY);
    
    // Apply anisotropic diffusion (simplified implementation)
    Mat filtered = gray.clone();
    for (int i = 0; i < params.anisotropicDiffusionIterations; i++) {
        Mat temp;
        GaussianBlur(filtered, temp, Size(3, 3), params.anisotropicDiffusionLambda);
        filtered = temp;
    }
    
    // Convert back to BGR
    cvtColor(filtered, dst, COLOR_GRAY2BGR);
}

/**
 * @brief Function to apply selected filtering method
 * @param src Input image
 * @param dst Output filtered image
 * @param method Filtering method
 * @param params Filtering parameters
 */
void applyFiltering(const Mat& src, Mat& dst, FilteringMethod method, 
                   const FilteringParams& params) {
    switch (method) {
        case WIENER_FILTER:
            applyWienerFilter(src, dst, params);
            break;
        case KALMAN_FILTER:
            applyKalmanFilter(src, dst, params);
            break;
        case PARTICLE_FILTER:
            applyParticleFilter(src, dst, params);
            break;
        case MEDIAN_FILTER:
            applyMedianFilter(src, dst, params);
            break;
        case GAUSSIAN_FILTER:
            applyGaussianFilter(src, dst, params);
            break;
        case BILATERAL_FILTER:
            applyBilateralFilter(src, dst, params);
            break;
        case NON_LOCAL_MEANS:
            applyNonLocalMeans(src, dst, params);
            break;
        case EDGE_PRESERVING:
            applyEdgePreservingFilter(src, dst, params);
            break;
        case DETAIL_ENHANCEMENT:
            applyDetailEnhancement(src, dst, params);
            break;
        case ANISOTROPIC_DIFFUSION:
            applyAnisotropicDiffusion(src, dst, params);
            break;
    }
}

/**
 * @brief Function to create filtering visualization
 * @param src Original image
 * @param dst Filtered image
 * @param method Filtering method
 * @param params Filtering parameters
 * @return Mat Filtering visualization
 */
Mat createFilteringVisualization(const Mat& src, const Mat& dst, FilteringMethod method, 
                                const FilteringParams& params) {
    // Create side-by-side comparison
    Mat comparison;
    hconcat(src, dst, comparison);
    
    // Add labels
    string methodName = getFilteringMethodName(method);
    putText(comparison, "Original", Point(10, 30), 
           FONT_HERSHEY_SIMPLEX, 0.7, Scalar(0, 255, 0), 2);
    putText(comparison, methodName, Point(src.cols + 10, 30), 
           FONT_HERSHEY_SIMPLEX, 0.7, Scalar(0, 255, 0), 2);
    
    // Add parameter information
    stringstream ss;
    switch (method) {
        case WIENER_FILTER:
            ss << "Noise Var: " << params.wienerNoiseVariance;
            break;
        case KALMAN_FILTER:
            ss << "Process Noise: " << params.kalmanProcessNoise;
            break;
        case PARTICLE_FILTER:
            ss << "Particles: " << params.particleFilterParticles;
            break;
        case MEDIAN_FILTER:
            ss << "Kernel Size: " << params.medianKernelSize;
            break;
        case GAUSSIAN_FILTER:
            ss << "Sigma: " << params.gaussianSigma;
            break;
        case BILATERAL_FILTER:
            ss << "Sigma Color: " << params.bilateralSigmaColor;
            break;
        case NON_LOCAL_MEANS:
            ss << "H: " << params.nlmH;
            break;
        case EDGE_PRESERVING:
            ss << "Sigma S: " << params.edgePreservingSigmaS;
            break;
        case DETAIL_ENHANCEMENT:
            ss << "Alpha: " << params.detailEnhancementAlpha;
            break;
        case ANISOTROPIC_DIFFUSION:
            ss << "Lambda: " << params.anisotropicDiffusionLambda;
            break;
    }
    
    putText(comparison, ss.str(), Point(10, 60), 
           FONT_HERSHEY_SIMPLEX, 0.5, Scalar(255, 255, 255), 1);
    
    return comparison;
}

/**
 * @brief Function to send filtering data to MATLAB
 * @param matlabPtr MATLAB engine pointer
 * @param src Original image
 * @param dst Filtered image
 * @param method Filtering method
 * @param params Filtering parameters
 */
void sendFilteringToMATLAB(std::unique_ptr<matlab::engine::MATLABEngine>& matlabPtr, 
                          const Mat& src, const Mat& dst, FilteringMethod method, 
                          const FilteringParams& params) {
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
        
        // Filtered image
        auto dimsDst = factory.createArray<std::size_t>({1, 3}, 
            {static_cast<std::size_t>(rgbDst.rows), 
             static_cast<std::size_t>(rgbDst.cols), 
             static_cast<std::size_t>(rgbDst.channels())});
        auto matlabDst = factory.createArray<uint8_t>(dimsDst);
        auto dstPtr = matlabDst.release();
        memcpy(dstPtr, rgbDst.data, rgbDst.total() * rgbDst.elemSize());
        
        // Set variables in MATLAB workspace
        matlabPtr->setVariable(u"originalImage", matlabSrc);
        matlabPtr->setVariable(u"filteredImage", matlabDst);
        
        // Execute MATLAB commands
        string methodName = getFilteringMethodName(method);
        string matlabCmd = "figure; subplot(1,2,1); imshow(originalImage); title('Original'); "
                          "subplot(1,2,2); imshow(filteredImage); title('" + methodName + "');";
        matlabPtr->eval(matlab::engine::convertUTF8StringToUTF16String(matlabCmd));
        
        // Display filtering information
        matlabPtr->eval(u"fprintf('Filtering Method: " + matlab::engine::convertUTF8StringToUTF16String(methodName) + "\\n');");
        
        if (method == GAUSSIAN_FILTER) {
            matlabPtr->eval(u"fprintf('Gaussian Sigma: %.2f\\n', " + to_string(params.gaussianSigma) + u");");
        }
        
        cout << "Filtering data sent to MATLAB successfully!" << endl;
        
    } catch (const std::exception& e) {
        cerr << "Error sending filtering data to MATLAB: " << e.what() << endl;
    }
}

/**
 * @brief Main function for advanced filtering and noise reduction
 * @return int Exit status
 */
int main() {
    cout << "=== Advanced Filtering and Noise Reduction - Intermediate Level 19 ===" << endl;
    cout << "This program demonstrates advanced filtering and noise reduction techniques." << endl;
    
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
        
        // Initialize filtering parameters
        FilteringParams params;
        params.wienerNoiseVariance = 0.01;
        params.wienerSignalVariance = 0.1;
        params.kalmanProcessNoise = 0.03;
        params.kalmanMeasurementNoise = 0.3;
        params.kalmanStateSize = 1;
        params.kalmanMeasurementSize = 1;
        params.particleFilterParticles = 100;
        params.particleFilterNoise = 1.0;
        params.medianKernelSize = 5;
        params.gaussianSigma = 1.0;
        params.gaussianKernelSize = 5;
        params.bilateralSigmaColor = 80.0;
        params.bilateralSigmaSpace = 80.0;
        params.bilateralDiameter = 15;
        params.nlmH = 10.0;
        params.nlmTemplateWindowSize = 7;
        params.nlmSearchWindowSize = 21;
        params.edgePreservingSigmaS = 50.0;
        params.edgePreservingSigmaR = 0.4;
        params.detailEnhancementAlpha = 0.5;
        params.anisotropicDiffusionLambda = 0.1;
        params.anisotropicDiffusionIterations = 10;
        
        // Initialize filtering method
        FilteringMethod currentMethod = GAUSSIAN_FILTER;
        
        // Create Mat objects for frame processing
        Mat frame, filteredFrame, visualization;
        
        cout << "\nStarting camera feed with advanced filtering..." << endl;
        cout << "Controls:" << endl;
        cout << "  'q' - Quit" << endl;
        cout << "  '0' - Wiener Filter" << endl;
        cout << "  '1' - Kalman Filter" << endl;
        cout << "  '2' - Particle Filter" << endl;
        cout << "  '3' - Median Filter" << endl;
        cout << "  '4' - Gaussian Filter" << endl;
        cout << "  '5' - Bilateral Filter" << endl;
        cout << "  '6' - Non-Local Means" << endl;
        cout << "  '7' - Edge Preserving" << endl;
        cout << "  '8' - Detail Enhancement" << endl;
        cout << "  '9' - Anisotropic Diffusion" << endl;
        cout << "  '+' - Increase parameter" << endl;
        cout << "  '-' - Decrease parameter" << endl;
        cout << "  'm' - Send to MATLAB" << endl;
        cout << "  's' - Save current filtering" << endl;
        
        // Main capture loop
        while (true) {
            // Capture frame from camera
            cap >> frame;
            
            // Check if frame was captured successfully
            if (frame.empty()) {
                cerr << "Warning: Could not capture frame!" << endl;
                continue;
            }
            
            // Apply selected filtering method
            applyFiltering(frame, filteredFrame, currentMethod, params);
            
            // Create visualization
            visualization = createFilteringVisualization(frame, filteredFrame, currentMethod, params);
            
            // Display the visualization
            imshow("Advanced Filtering and Noise Reduction", visualization);
            
            // Handle keyboard input
            char key = waitKey(1) & 0xFF;
            
            if (key == 'q' || key == 27) { // 'q' or ESC to quit
                cout << "Quitting..." << endl;
                break;
            }
            else if (key >= '0' && key <= '9') { // Method selection
                currentMethod = static_cast<FilteringMethod>(key - '0');
                cout << "Selected method: " << getFilteringMethodName(currentMethod) << endl;
            }
            else if (key == '+') { // Increase parameter
                switch (currentMethod) {
                    case WIENER_FILTER:
                        params.wienerNoiseVariance = min(1.0, params.wienerNoiseVariance + 0.01);
                        cout << "Wiener noise variance increased to: " << params.wienerNoiseVariance << endl;
                        break;
                    case KALMAN_FILTER:
                        params.kalmanProcessNoise = min(1.0, params.kalmanProcessNoise + 0.01);
                        cout << "Kalman process noise increased to: " << params.kalmanProcessNoise << endl;
                        break;
                    case PARTICLE_FILTER:
                        params.particleFilterParticles = min(1000, params.particleFilterParticles + 50);
                        cout << "Particle filter particles increased to: " << params.particleFilterParticles << endl;
                        break;
                    case MEDIAN_FILTER:
                        params.medianKernelSize = min(31, params.medianKernelSize + 2);
                        cout << "Median kernel size increased to: " << params.medianKernelSize << endl;
                        break;
                    case GAUSSIAN_FILTER:
                        params.gaussianSigma = min(10.0, params.gaussianSigma + 0.5);
                        cout << "Gaussian sigma increased to: " << params.gaussianSigma << endl;
                        break;
                    case BILATERAL_FILTER:
                        params.bilateralSigmaColor = min(200.0, params.bilateralSigmaColor + 10.0);
                        cout << "Bilateral sigma color increased to: " << params.bilateralSigmaColor << endl;
                        break;
                    case NON_LOCAL_MEANS:
                        params.nlmH = min(50.0, params.nlmH + 5.0);
                        cout << "NLM H increased to: " << params.nlmH << endl;
                        break;
                    case EDGE_PRESERVING:
                        params.edgePreservingSigmaS = min(200.0, params.edgePreservingSigmaS + 10.0);
                        cout << "Edge preserving sigma S increased to: " << params.edgePreservingSigmaS << endl;
                        break;
                    case DETAIL_ENHANCEMENT:
                        params.detailEnhancementAlpha = min(2.0, params.detailEnhancementAlpha + 0.1);
                        cout << "Detail enhancement alpha increased to: " << params.detailEnhancementAlpha << endl;
                        break;
                    case ANISOTROPIC_DIFFUSION:
                        params.anisotropicDiffusionLambda = min(1.0, params.anisotropicDiffusionLambda + 0.1);
                        cout << "Anisotropic diffusion lambda increased to: " << params.anisotropicDiffusionLambda << endl;
                        break;
                }
            }
            else if (key == '-') { // Decrease parameter
                switch (currentMethod) {
                    case WIENER_FILTER:
                        params.wienerNoiseVariance = max(0.001, params.wienerNoiseVariance - 0.01);
                        cout << "Wiener noise variance decreased to: " << params.wienerNoiseVariance << endl;
                        break;
                    case KALMAN_FILTER:
                        params.kalmanProcessNoise = max(0.001, params.kalmanProcessNoise - 0.01);
                        cout << "Kalman process noise decreased to: " << params.kalmanProcessNoise << endl;
                        break;
                    case PARTICLE_FILTER:
                        params.particleFilterParticles = max(10, params.particleFilterParticles - 50);
                        cout << "Particle filter particles decreased to: " << params.particleFilterParticles << endl;
                        break;
                    case MEDIAN_FILTER:
                        params.medianKernelSize = max(3, params.medianKernelSize - 2);
                        cout << "Median kernel size decreased to: " << params.medianKernelSize << endl;
                        break;
                    case GAUSSIAN_FILTER:
                        params.gaussianSigma = max(0.1, params.gaussianSigma - 0.5);
                        cout << "Gaussian sigma decreased to: " << params.gaussianSigma << endl;
                        break;
                    case BILATERAL_FILTER:
                        params.bilateralSigmaColor = max(10.0, params.bilateralSigmaColor - 10.0);
                        cout << "Bilateral sigma color decreased to: " << params.bilateralSigmaColor << endl;
                        break;
                    case NON_LOCAL_MEANS:
                        params.nlmH = max(1.0, params.nlmH - 5.0);
                        cout << "NLM H decreased to: " << params.nlmH << endl;
                        break;
                    case EDGE_PRESERVING:
                        params.edgePreservingSigmaS = max(10.0, params.edgePreservingSigmaS - 10.0);
                        cout << "Edge preserving sigma S decreased to: " << params.edgePreservingSigmaS << endl;
                        break;
                    case DETAIL_ENHANCEMENT:
                        params.detailEnhancementAlpha = max(0.1, params.detailEnhancementAlpha - 0.1);
                        cout << "Detail enhancement alpha decreased to: " << params.detailEnhancementAlpha << endl;
                        break;
                    case ANISOTROPIC_DIFFUSION:
                        params.anisotropicDiffusionLambda = max(0.01, params.anisotropicDiffusionLambda - 0.1);
                        cout << "Anisotropic diffusion lambda decreased to: " << params.anisotropicDiffusionLambda << endl;
                        break;
                }
            }
            else if (key == 'm') { // Send to MATLAB
                sendFilteringToMATLAB(matlabPtr, frame, filteredFrame, currentMethod, params);
            }
            else if (key == 's') { // Save current filtering
                string filename = "filtering_" + getFilteringMethodName(currentMethod) + ".jpg";
                imwrite(filename, visualization);
                cout << "Filtering saved as: " << filename << endl;
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
 * g++ -std=c++17 camera_intermediate_19.cpp -o camera_intermediate_19 \
 *     `pkg-config --cflags --libs opencv4` \
 *     -I/Applications/MATLAB_R2023b.app/extern/include \
 *     -L/Applications/MATLAB_R2023b.app/bin/maci64 \
 *     -lMatlabDataArray -lMatlabEngine
 * 
 * @brief Usage:
 * 1. Make sure your camera is connected and working
 * 2. Run the executable: ./camera_intermediate_19
 * 3. Use keyboard controls to switch between filtering methods
 * 4. Adjust parameters with '+'/'-' keys
 * 5. Press 'm' to send data to MATLAB
 * 6. Press 's' to save current filtering
 * 
 * @brief Learning Objectives:
 * - Understand advanced filtering techniques
 * - Learn Wiener and Kalman filtering
 * - Understand particle filtering concepts
 * - Learn median and Gaussian filtering
 * - Understand bilateral and non-local means filtering
 * - Learn edge preserving and detail enhancement
 * - Learn anisotropic diffusion
 * - Learn MATLAB integration for filtering analysis
 */
