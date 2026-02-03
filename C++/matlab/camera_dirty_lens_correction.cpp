/**
 * @file camera_dirty_lens_correction.cpp
 * @brief Dirty Camera Lens Correction - Advanced Image Processing
 * @description This program demonstrates various image processing algorithms
 *              to correct issues caused by dirty camera lenses including
 *              deblurring, spot removal, contrast enhancement, and illumination correction.
 * @author Educational C++ MATLAB Integration Project
 * @date 2024
 * @version 1.0
 */

#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/photo.hpp>
#include <iostream>
#include <matlab/engine.hpp>
#include <memory>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace cv;
using namespace std;

/**
 * @brief Enumeration for different correction methods
 */
enum CorrectionMethod {
    DEBLUR_WIENER = 0,
    DEBLUR_RICHARDSON_LUCY = 1,
    SPOT_REMOVAL_MEDIAN = 2,
    SPOT_REMOVAL_MORPHOLOGY = 3,
    SPOT_REMOVAL_INPAINTING = 4,
    CONTRAST_HISTOGRAM_EQ = 5,
    CONTRAST_CLAHE = 6,
    CONTRAST_UNSHARP_MASK = 7,
    ILLUMINATION_CORRECTION = 8,
    COMBINED_CORRECTION = 9
};

/**
 * @brief Structure to hold correction parameters
 */
struct CorrectionParams {
    // Deblurring parameters
    float wienerNoiseLevel;
    int richardsonLucyIterations;
    
    // Spot removal parameters
    int medianKernelSize;
    int morphologyKernelSize;
    int inpaintingRadius;
    
    // Contrast enhancement parameters
    float claheClipLimit;
    Size claheTileGridSize;
    float unsharpMaskAmount;
    float unsharpMaskRadius;
    
    // Illumination correction parameters
    int illuminationBlurKernelSize;
    float illuminationGamma;
};

/**
 * @brief Function to get correction method name
 * @param method Correction method
 * @return string Method name
 */
string getCorrectionMethodName(CorrectionMethod method) {
    switch (method) {
        case DEBLUR_WIENER: return "Wiener Deblurring";
        case DEBLUR_RICHARDSON_LUCY: return "Richardson-Lucy Deconvolution";
        case SPOT_REMOVAL_MEDIAN: return "Median Filter Spot Removal";
        case SPOT_REMOVAL_MORPHOLOGY: return "Morphological Spot Removal";
        case SPOT_REMOVAL_INPAINTING: return "Inpainting Spot Removal";
        case CONTRAST_HISTOGRAM_EQ: return "Histogram Equalization";
        case CONTRAST_CLAHE: return "CLAHE Contrast Enhancement";
        case CONTRAST_UNSHARP_MASK: return "Unsharp Masking";
        case ILLUMINATION_CORRECTION: return "Illumination Correction";
        case COMBINED_CORRECTION: return "Combined Correction";
        default: return "Unknown";
    }
}

/**
 * @brief Function to apply Wiener deblurring
 * @param src Input image
 * @param dst Output image
 * @param params Correction parameters
 */
void applyWienerDeblur(const Mat& src, Mat& dst, const CorrectionParams& params) {
    // Create a simple motion blur kernel (horizontal)
    Mat kernel = Mat::zeros(1, 15, CV_32F);
    kernel.at<float>(0, 7) = 1.0f;
    kernel.at<float>(0, 8) = 1.0f;
    kernel.at<float>(0, 9) = 1.0f;
    kernel /= 3.0f;
    
    // Apply Wiener filter
    Mat srcFloat;
    src.convertTo(srcFloat, CV_32F, 1.0/255.0);
    
    // Convert to frequency domain
    Mat srcFreq, kernelFreq;
    dft(srcFloat, srcFreq, DFT_COMPLEX_OUTPUT);
    dft(kernel, kernelFreq, DFT_COMPLEX_OUTPUT);
    
    // Wiener filter in frequency domain
    Mat wienerFilter;
    Mat kernelMagnitude;
    magnitude(kernelFreq, Mat::zeros(kernelFreq.size(), CV_32F), kernelMagnitude);
    
    // Avoid division by zero
    kernelMagnitude += params.wienerNoiseLevel;
    
    divide(kernelFreq, kernelMagnitude, wienerFilter);
    
    // Apply filter
    Mat filteredFreq;
    mulSpectrums(srcFreq, wienerFilter, filteredFreq, 0);
    
    // Convert back to spatial domain
    Mat filteredFloat;
    idft(filteredFreq, filteredFloat, DFT_SCALE | DFT_REAL_OUTPUT);
    
    // Convert back to 8-bit
    filteredFloat.convertTo(dst, CV_8U, 255.0);
}

/**
 * @brief Function to apply Richardson-Lucy deconvolution
 * @param src Input image
 * @param dst Output image
 * @param params Correction parameters
 */
void applyRichardsonLucyDeblur(const Mat& src, Mat& dst, const CorrectionParams& params) {
    // Create a simple motion blur kernel
    Mat kernel = Mat::zeros(1, 9, CV_32F);
    kernel.at<float>(0, 3) = 0.2f;
    kernel.at<float>(0, 4) = 0.6f;
    kernel.at<float>(0, 5) = 0.2f;
    
    // Convert to float
    Mat srcFloat;
    src.convertTo(srcFloat, CV_32F, 1.0/255.0);
    
    // Initialize estimate
    Mat estimate = srcFloat.clone();
    
    // Richardson-Lucy iterations
    for (int i = 0; i < params.richardsonLucyIterations; i++) {
        Mat blurred;
        filter2D(estimate, blurred, -1, kernel);
        
        // Avoid division by zero
        blurred += 1e-10;
        
        Mat ratio;
        divide(srcFloat, blurred, ratio);
        
        Mat correction;
        filter2D(ratio, correction, -1, kernel);
        
        multiply(estimate, correction, estimate);
    }
    
    // Convert back to 8-bit
    estimate.convertTo(dst, CV_8U, 255.0);
}

/**
 * @brief Function to apply median filter for spot removal
 * @param src Input image
 * @param dst Output image
 * @param params Correction parameters
 */
void applyMedianSpotRemoval(const Mat& src, Mat& dst, const CorrectionParams& params) {
    medianBlur(src, dst, params.medianKernelSize);
}

/**
 * @brief Function to apply morphological operations for spot removal
 * @param src Input image
 * @param dst Output image
 * @param params Correction parameters
 */
void applyMorphologicalSpotRemoval(const Mat& src, Mat& dst, const CorrectionParams& params) {
    Mat gray;
    if (src.channels() == 3) {
        cvtColor(src, gray, COLOR_BGR2GRAY);
    } else {
        gray = src.clone();
    }
    
    // Create morphological kernel
    Mat kernel = getStructuringElement(MORPH_ELLIPSE, 
        Size(params.morphologyKernelSize, params.morphologyKernelSize));
    
    // Apply opening to remove small spots
    Mat opened;
    morphologyEx(gray, opened, MORPH_OPEN, kernel);
    
    // Apply closing to fill small holes
    Mat closed;
    morphologyEx(opened, closed, MORPH_CLOSE, kernel);
    
    if (src.channels() == 3) {
        // Convert back to color
        cvtColor(closed, dst, COLOR_GRAY2BGR);
    } else {
        dst = closed.clone();
    }
}

/**
 * @brief Function to apply inpainting for spot removal
 * @param src Input image
 * @param dst Output image
 * @param params Correction parameters
 */
void applyInpaintingSpotRemoval(const Mat& src, Mat& dst, const CorrectionParams& params) {
    Mat gray;
    if (src.channels() == 3) {
        cvtColor(src, gray, COLOR_BGR2GRAY);
    } else {
        gray = src.clone();
    }
    
    // Create mask for spots (threshold to find dark spots)
    Mat mask;
    threshold(gray, mask, 50, 255, THRESH_BINARY_INV);
    
    // Apply morphological operations to clean up mask
    Mat kernel = getStructuringElement(MORPH_ELLIPSE, Size(3, 3));
    morphologyEx(mask, mask, MORPH_CLOSE, kernel);
    
    // Apply inpainting
    if (src.channels() == 3) {
        inpaint(src, mask, dst, params.inpaintingRadius, INPAINT_TELEA);
    } else {
        inpaint(gray, mask, dst, params.inpaintingRadius, INPAINT_TELEA);
    }
}

/**
 * @brief Function to apply histogram equalization
 * @param src Input image
 * @param dst Output image
 * @param params Correction parameters
 */
void applyHistogramEqualization(const Mat& src, Mat& dst, const CorrectionParams& params) {
    if (src.channels() == 3) {
        vector<Mat> channels;
        split(src, channels);
        
        for (int i = 0; i < 3; i++) {
            equalizeHist(channels[i], channels[i]);
        }
        
        merge(channels, dst);
    } else {
        equalizeHist(src, dst);
    }
}

/**
 * @brief Function to apply CLAHE contrast enhancement
 * @param src Input image
 * @param dst Output image
 * @param params Correction parameters
 */
void applyCLAHE(const Mat& src, Mat& dst, const CorrectionParams& params) {
    Ptr<CLAHE> clahe = createCLAHE(params.claheClipLimit, params.claheTileGridSize);
    
    if (src.channels() == 3) {
        vector<Mat> channels;
        split(src, channels);
        
        for (int i = 0; i < 3; i++) {
            clahe->apply(channels[i], channels[i]);
        }
        
        merge(channels, dst);
    } else {
        clahe->apply(src, dst);
    }
}

/**
 * @brief Function to apply unsharp masking
 * @param src Input image
 * @param dst Output image
 * @param params Correction parameters
 */
void applyUnsharpMask(const Mat& src, Mat& dst, const CorrectionParams& params) {
    Mat blurred;
    GaussianBlur(src, blurred, Size(0, 0), params.unsharpMaskRadius);
    
    Mat sharpened;
    addWeighted(src, 1.0 + params.unsharpMaskAmount, blurred, -params.unsharpMaskAmount, 0, sharpened);
    
    dst = sharpened;
}

/**
 * @brief Function to apply illumination correction
 * @param src Input image
 * @param dst Output image
 * @param params Correction parameters
 */
void applyIlluminationCorrection(const Mat& src, Mat& dst, const CorrectionParams& params) {
    Mat gray;
    if (src.channels() == 3) {
        cvtColor(src, gray, COLOR_BGR2GRAY);
    } else {
        gray = src.clone();
    }
    
    // Estimate illumination by blurring the image
    Mat illumination;
    GaussianBlur(gray, illumination, Size(params.illuminationBlurKernelSize, 
                                          params.illuminationBlurKernelSize), 0);
    
    // Avoid division by zero
    illumination += 1;
    
    // Correct illumination
    Mat corrected;
    divide(gray, illumination, corrected, 255.0);
    
    // Apply gamma correction
    Mat gammaCorrected;
    pow(corrected / 255.0, params.illuminationGamma, gammaCorrected);
    gammaCorrected *= 255.0;
    gammaCorrected.convertTo(gammaCorrected, CV_8U);
    
    if (src.channels() == 3) {
        cvtColor(gammaCorrected, dst, COLOR_GRAY2BGR);
    } else {
        dst = gammaCorrected.clone();
    }
}

/**
 * @brief Function to apply combined correction
 * @param src Input image
 * @param dst Output image
 * @param params Correction parameters
 */
void applyCombinedCorrection(const Mat& src, Mat& dst, const CorrectionParams& params) {
    Mat temp1, temp2, temp3, temp4;
    
    // Step 1: Remove spots
    applyMedianSpotRemoval(src, temp1, params);
    
    // Step 2: Correct illumination
    applyIlluminationCorrection(temp1, temp2, params);
    
    // Step 3: Enhance contrast
    applyCLAHE(temp2, temp3, params);
    
    // Step 4: Apply unsharp masking
    applyUnsharpMask(temp3, temp4, params);
    
    // Step 5: Final deblurring
    applyRichardsonLucyDeblur(temp4, dst, params);
}

/**
 * @brief Function to apply dirty lens correction
 * @param src Input image
 * @param dst Output image
 * @param method Correction method
 * @param params Correction parameters
 */
void applyDirtyLensCorrection(const Mat& src, Mat& dst, CorrectionMethod method, 
                            const CorrectionParams& params) {
    switch (method) {
        case DEBLUR_WIENER:
            applyWienerDeblur(src, dst, params);
            break;
        case DEBLUR_RICHARDSON_LUCY:
            applyRichardsonLucyDeblur(src, dst, params);
            break;
        case SPOT_REMOVAL_MEDIAN:
            applyMedianSpotRemoval(src, dst, params);
            break;
        case SPOT_REMOVAL_MORPHOLOGY:
            applyMorphologicalSpotRemoval(src, dst, params);
            break;
        case SPOT_REMOVAL_INPAINTING:
            applyInpaintingSpotRemoval(src, dst, params);
            break;
        case CONTRAST_HISTOGRAM_EQ:
            applyHistogramEqualization(src, dst, params);
            break;
        case CONTRAST_CLAHE:
            applyCLAHE(src, dst, params);
            break;
        case CONTRAST_UNSHARP_MASK:
            applyUnsharpMask(src, dst, params);
            break;
        case ILLUMINATION_CORRECTION:
            applyIlluminationCorrection(src, dst, params);
            break;
        case COMBINED_CORRECTION:
            applyCombinedCorrection(src, dst, params);
            break;
        default:
            src.copyTo(dst);
            break;
    }
}

/**
 * @brief Function to calculate image quality metrics
 * @param original Original image
 * @param corrected Corrected image
 * @return vector<double> Quality metrics [PSNR, SSIM, MSE]
 */
vector<double> calculateQualityMetrics(const Mat& original, const Mat& corrected) {
    vector<double> metrics(3);
    
    // Convert to float for calculations
    Mat origFloat, corrFloat;
    original.convertTo(origFloat, CV_32F);
    corrected.convertTo(corrFloat, CV_32F);
    
    // Calculate MSE
    Mat diff;
    absdiff(origFloat, corrFloat, diff);
    Mat diffSquared;
    multiply(diff, diff, diffSquared);
    Scalar mseScalar = sum(diffSquared) / (original.total() * original.channels());
    double mse = mseScalar[0];
    
    // Calculate PSNR
    if (mse > 0) {
        metrics[0] = 20 * log10(255.0 / sqrt(mse)); // PSNR
    } else {
        metrics[0] = 100.0; // Perfect match
    }
    
    metrics[1] = 0.0; // SSIM placeholder (would need separate implementation)
    metrics[2] = mse; // MSE
    
    return metrics;
}

/**
 * @brief Function to send correction data to MATLAB
 * @param matlabPtr MATLAB engine pointer
 * @param original Original image
 * @param corrected Corrected image
 * @param method Correction method
 * @param params Correction parameters
 * @param metrics Quality metrics
 */
void sendCorrectionToMATLAB(std::unique_ptr<matlab::engine::MATLABEngine>& matlabPtr,
                          const Mat& original, const Mat& corrected, CorrectionMethod method,
                          const CorrectionParams& params, const vector<double>& metrics) {
    try {
        // Convert BGR to RGB for MATLAB
        Mat rgbOriginal, rgbCorrected;
        cvtColor(original, rgbOriginal, COLOR_BGR2RGB);
        cvtColor(corrected, rgbCorrected, COLOR_BGR2RGB);
        
        // Create MATLAB arrays
        matlab::data::ArrayFactory factory;
        
        // Original image
        auto dimsOrig = factory.createArray<std::size_t>({1, 3}, 
            {static_cast<std::size_t>(rgbOriginal.rows), 
             static_cast<std::size_t>(rgbOriginal.cols), 
             static_cast<std::size_t>(rgbOriginal.channels())});
        auto matlabOrig = factory.createArray<uint8_t>(dimsOrig);
        auto origPtr = matlabOrig.release();
        memcpy(origPtr, rgbOriginal.data, rgbOriginal.total() * rgbOriginal.elemSize());
        
        // Corrected image
        auto dimsCorr = factory.createArray<std::size_t>({1, 3}, 
            {static_cast<std::size_t>(rgbCorrected.rows), 
             static_cast<std::size_t>(rgbCorrected.cols), 
             static_cast<std::size_t>(rgbCorrected.channels())});
        auto matlabCorr = factory.createArray<uint8_t>(dimsCorr);
        auto corrPtr = matlabCorr.release();
        memcpy(corrPtr, rgbCorrected.data, rgbCorrected.total() * rgbCorrected.elemSize());
        
        // Quality metrics
        auto matlabMetrics = factory.createArray<double>({1, 3}, metrics.data());
        
        // Set variables in MATLAB workspace
        matlabPtr->setVariable(u"originalImage", matlabOrig);
        matlabPtr->setVariable(u"correctedImage", matlabCorr);
        matlabPtr->setVariable(u"qualityMetrics", matlabMetrics);
        
        // Execute MATLAB commands
        string methodName = getCorrectionMethodName(method);
        string matlabCmd = "figure; subplot(1,3,1); imshow(originalImage); title('Original'); "
                          "subplot(1,3,2); imshow(correctedImage); title('" + methodName + "'); "
                          "subplot(1,3,3); imshowpair(originalImage, correctedImage, 'montage'); title('Comparison');";
        matlabPtr->eval(matlab::engine::convertUTF8StringToUTF16String(matlabCmd));
        
        // Display correction information
        matlabPtr->eval(u"fprintf('Correction Method: " + matlab::engine::convertUTF8StringToUTF16String(methodName) + "\\n');");
        matlabPtr->eval(u"fprintf('PSNR: %.2f dB\\n', qualityMetrics(1));");
        matlabPtr->eval(u"fprintf('MSE: %.2f\\n', qualityMetrics(3));");
        
        cout << "Correction data sent to MATLAB successfully!" << endl;
        
    } catch (const std::exception& e) {
        cerr << "Error sending correction data to MATLAB: " << e.what() << endl;
    }
}

/**
 * @brief Main function for dirty lens correction
 * @return int Exit status
 */
int main() {
    cout << "=== Dirty Camera Lens Correction - Advanced Image Processing ===" << endl;
    cout << "This program demonstrates various algorithms to correct dirty lens issues." << endl;
    
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
        
        // Initialize correction parameters
        CorrectionParams params;
        params.wienerNoiseLevel = 0.01f;
        params.richardsonLucyIterations = 10;
        params.medianKernelSize = 5;
        params.morphologyKernelSize = 3;
        params.inpaintingRadius = 3;
        params.claheClipLimit = 2.0f;
        params.claheTileGridSize = Size(8, 8);
        params.unsharpMaskAmount = 1.5f;
        params.unsharpMaskRadius = 1.0f;
        params.illuminationBlurKernelSize = 21;
        params.illuminationGamma = 0.8f;
        
        // Initialize correction method
        CorrectionMethod currentMethod = COMBINED_CORRECTION;
        
        // Create Mat objects for frame processing
        Mat frame, correctedFrame;
        vector<double> qualityMetrics;
        
        cout << "\nStarting camera feed with dirty lens correction..." << endl;
        cout << "Controls:" << endl;
        cout << "  'q' - Quit" << endl;
        cout << "  '0' - Wiener Deblurring" << endl;
        cout << "  '1' - Richardson-Lucy Deconvolution" << endl;
        cout << "  '2' - Median Filter Spot Removal" << endl;
        cout << "  '3' - Morphological Spot Removal" << endl;
        cout << "  '4' - Inpainting Spot Removal" << endl;
        cout << "  '5' - Histogram Equalization" << endl;
        cout << "  '6' - CLAHE Contrast Enhancement" << endl;
        cout << "  '7' - Unsharp Masking" << endl;
        cout << "  '8' - Illumination Correction" << endl;
        cout << "  '9' - Combined Correction" << endl;
        cout << "  'm' - Send to MATLAB" << endl;
        cout << "  's' - Save current correction" << endl;
        
        // Main capture loop
        while (true) {
            // Capture frame from camera
            cap >> frame;
            
            // Check if frame was captured successfully
            if (frame.empty()) {
                cerr << "Warning: Could not capture frame!" << endl;
                continue;
            }
            
            // Apply dirty lens correction
            applyDirtyLensCorrection(frame, correctedFrame, currentMethod, params);
            
            // Calculate quality metrics
            qualityMetrics = calculateQualityMetrics(frame, correctedFrame);
            
            // Add information overlay
            string methodInfo = "Method: " + getCorrectionMethodName(currentMethod);
            string psnrInfo = "PSNR: " + to_string(qualityMetrics[0]).substr(0, 5) + " dB";
            string mseInfo = "MSE: " + to_string(qualityMetrics[2]).substr(0, 8);
            
            putText(correctedFrame, methodInfo, Point(10, 30), 
                   FONT_HERSHEY_SIMPLEX, 0.6, Scalar(0, 255, 0), 2);
            putText(correctedFrame, psnrInfo, Point(10, 60), 
                   FONT_HERSHEY_SIMPLEX, 0.6, Scalar(0, 255, 0), 2);
            putText(correctedFrame, mseInfo, Point(10, 90), 
                   FONT_HERSHEY_SIMPLEX, 0.6, Scalar(0, 255, 0), 2);
            
            // Display the corrected frame
            imshow("Dirty Lens Correction", correctedFrame);
            
            // Handle keyboard input
            char key = waitKey(1) & 0xFF;
            
            if (key == 'q' || key == 27) { // 'q' or ESC to quit
                cout << "Quitting..." << endl;
                break;
            }
            else if (key >= '0' && key <= '9') { // Method selection
                currentMethod = static_cast<CorrectionMethod>(key - '0');
                cout << "Selected method: " << getCorrectionMethodName(currentMethod) << endl;
            }
            else if (key == 'm') { // Send to MATLAB
                sendCorrectionToMATLAB(matlabPtr, frame, correctedFrame, currentMethod, params, qualityMetrics);
            }
            else if (key == 's') { // Save current correction
                string filename = "corrected_" + getCorrectionMethodName(currentMethod) + ".jpg";
                imwrite(filename, correctedFrame);
                cout << "Corrected image saved as: " << filename << endl;
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
 * 1. OpenCV library installed (with photo module)
 * 2. MATLAB Engine API for C++ installed
 * 3. Proper linking flags
 * 
 * Compilation command:
 * g++ -std=c++17 camera_dirty_lens_correction.cpp -o camera_dirty_lens_correction \
 *     `pkg-config --cflags --libs opencv4` \
 *     -I/Applications/MATLAB_R2023b.app/extern/include \
 *     -L/Applications/MATLAB_R2023b.app/bin/maci64 \
 *     -lMatlabDataArray -lMatlabEngine
 * 
 * @brief Usage:
 * 1. Make sure your camera is connected and working
 * 2. Run the executable: ./camera_dirty_lens_correction
 * 3. Use keyboard controls to switch between correction methods
 * 4. Press 'm' to send data to MATLAB for analysis
 * 5. Press 's' to save current corrected image
 * 
 * @brief Learning Objectives:
 * - Understand dirty lens problems and solutions
 * - Learn deblurring algorithms (Wiener, Richardson-Lucy)
 * - Learn spot removal techniques (median, morphology, inpainting)
 * - Learn contrast enhancement methods (histogram eq, CLAHE, unsharp mask)
 * - Learn illumination correction
 * - Understand image quality metrics (PSNR, MSE)
 * - Learn MATLAB integration for image analysis
 * - Understand parameter tuning for different scenarios
 */
