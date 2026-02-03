/**
 * @file camera_intermediate_15.cpp
 * @brief Advanced Image Enhancement - Intermediate Level 15
 * @description This program demonstrates advanced image enhancement techniques
 *              including unsharp masking, gamma correction, tone mapping,
 *              and advanced filtering using OpenCV and MATLAB integration.
 * @author Educational C++ MATLAB Integration Project
 * @date 2024
 * @version 1.0
 */

#include <opencv2/opencv.hpp>
#include <iostream>
#include <matlab/engine.hpp>
#include <memory>
#include <vector>
#include <cmath>

using namespace cv;
using namespace std;

/**
 * @brief Enumeration for different enhancement methods
 */
enum EnhancementMethod {
    UNSHARP_MASKING = 0,
    GAMMA_CORRECTION = 1,
    TONE_MAPPING = 2,
    HISTOGRAM_EQUALIZATION = 3,
    CLAHE = 4,
    BILATERAL_FILTER = 5,
    NON_LOCAL_MEANS = 6,
    EDGE_PRESERVING = 7,
    DETAIL_ENHANCEMENT = 8,
    CONTRAST_LIMITING = 9
};

/**
 * @brief Structure to hold enhancement parameters
 */
struct EnhancementParams {
    double unsharpAmount;
    double unsharpRadius;
    double gammaValue;
    double toneMappingAlpha;
    double toneMappingBeta;
    double claheClipLimit;
    Size claheTileGridSize;
    double bilateralSigmaColor;
    double bilateralSigmaSpace;
    int bilateralDiameter;
    double nlmH;
    int nlmTemplateWindowSize;
    int nlmSearchWindowSize;
    double edgePreservingSigmaS;
    double edgePreservingSigmaR;
    double detailEnhancementAlpha;
    double contrastLimit;
};

/**
 * @brief Function to get enhancement method name
 * @param method Enhancement method
 * @return string Method name
 */
string getEnhancementMethodName(EnhancementMethod method) {
    switch (method) {
        case UNSHARP_MASKING: return "Unsharp Masking";
        case GAMMA_CORRECTION: return "Gamma Correction";
        case TONE_MAPPING: return "Tone Mapping";
        case HISTOGRAM_EQUALIZATION: return "Histogram Equalization";
        case CLAHE: return "CLAHE";
        case BILATERAL_FILTER: return "Bilateral Filter";
        case NON_LOCAL_MEANS: return "Non-Local Means";
        case EDGE_PRESERVING: return "Edge Preserving";
        case DETAIL_ENHANCEMENT: return "Detail Enhancement";
        case CONTRAST_LIMITING: return "Contrast Limiting";
        default: return "Unknown";
    }
}

/**
 * @brief Function to apply unsharp masking
 * @param src Input image
 * @param dst Output enhanced image
 * @param params Enhancement parameters
 */
void applyUnsharpMasking(const Mat& src, Mat& dst, const EnhancementParams& params) {
    // Create Gaussian blur
    Mat blurred;
    GaussianBlur(src, blurred, Size(0, 0), params.unsharpRadius);
    
    // Create unsharp mask
    Mat mask;
    subtract(src, blurred, mask);
    
    // Apply unsharp masking
    addWeighted(src, 1.0, mask, params.unsharpAmount, 0, dst);
}

/**
 * @brief Function to apply gamma correction
 * @param src Input image
 * @param dst Output enhanced image
 * @param params Enhancement parameters
 */
void applyGammaCorrection(const Mat& src, Mat& dst, const EnhancementParams& params) {
    // Create lookup table
    Mat lookupTable(1, 256, CV_8U);
    uchar* p = lookupTable.ptr();
    for (int i = 0; i < 256; i++) {
        p[i] = saturate_cast<uchar>(pow(i / 255.0, params.gammaValue) * 255.0);
    }
    
    // Apply gamma correction
    LUT(src, lookupTable, dst);
}

/**
 * @brief Function to apply tone mapping
 * @param src Input image
 * @param dst Output enhanced image
 * @param params Enhancement parameters
 */
void applyToneMapping(const Mat& src, Mat& dst, const EnhancementParams& params) {
    // Convert to float
    Mat srcFloat;
    src.convertTo(srcFloat, CV_32F, 1.0/255.0);
    
    // Apply tone mapping
    Mat enhanced;
    srcFloat.convertTo(enhanced, CV_32F);
    
    // Apply alpha and beta parameters
    enhanced = params.toneMappingAlpha * enhanced + params.toneMappingBeta;
    
    // Clamp values
    enhanced = max(0.0, min(1.0, enhanced));
    
    // Convert back to 8-bit
    enhanced.convertTo(dst, CV_8U, 255.0);
}

/**
 * @brief Function to apply histogram equalization
 * @param src Input image
 * @param dst Output enhanced image
 * @param params Enhancement parameters
 */
void applyHistogramEqualization(const Mat& src, Mat& dst, const EnhancementParams& params) {
    if (src.channels() == 1) {
        equalizeHist(src, dst);
    } else {
        vector<Mat> channels;
        split(src, channels);
        
        vector<Mat> equalizedChannels;
        for (const auto& channel : channels) {
            Mat equalized;
            equalizeHist(channel, equalized);
            equalizedChannels.push_back(equalized);
        }
        
        merge(equalizedChannels, dst);
    }
}

/**
 * @brief Function to apply CLAHE
 * @param src Input image
 * @param dst Output enhanced image
 * @param params Enhancement parameters
 */
void applyCLAHE(const Mat& src, Mat& dst, const EnhancementParams& params) {
    if (src.channels() == 1) {
        Ptr<CLAHE> clahe = createCLAHE(params.claheClipLimit, params.claheTileGridSize);
        clahe->apply(src, dst);
    } else {
        vector<Mat> channels;
        split(src, channels);
        
        vector<Mat> claheChannels;
        Ptr<CLAHE> clahe = createCLAHE(params.claheClipLimit, params.claheTileGridSize);
        
        for (const auto& channel : channels) {
            Mat claheChannel;
            clahe->apply(channel, claheChannel);
            claheChannels.push_back(claheChannel);
        }
        
        merge(claheChannels, dst);
    }
}

/**
 * @brief Function to apply bilateral filter
 * @param src Input image
 * @param dst Output enhanced image
 * @param params Enhancement parameters
 */
void applyBilateralFilter(const Mat& src, Mat& dst, const EnhancementParams& params) {
    bilateralFilter(src, dst, params.bilateralDiameter, params.bilateralSigmaColor, params.bilateralSigmaSpace);
}

/**
 * @brief Function to apply non-local means denoising
 * @param src Input image
 * @param dst Output enhanced image
 * @param params Enhancement parameters
 */
void applyNonLocalMeans(const Mat& src, Mat& dst, const EnhancementParams& params) {
    fastNlMeansDenoising(src, dst, params.nlmH, params.nlmTemplateWindowSize, params.nlmSearchWindowSize);
}

/**
 * @brief Function to apply edge preserving filter
 * @param src Input image
 * @param dst Output enhanced image
 * @param params Enhancement parameters
 */
void applyEdgePreservingFilter(const Mat& src, Mat& dst, const EnhancementParams& params) {
    edgePreservingFilter(src, dst, 1, params.edgePreservingSigmaS, params.edgePreservingSigmaR);
}

/**
 * @brief Function to apply detail enhancement
 * @param src Input image
 * @param dst Output enhanced image
 * @param params Enhancement parameters
 */
void applyDetailEnhancement(const Mat& src, Mat& dst, const EnhancementParams& params) {
    detailEnhance(src, dst, params.detailEnhancementAlpha, params.detailEnhancementAlpha);
}

/**
 * @brief Function to apply contrast limiting
 * @param src Input image
 * @param dst Output enhanced image
 * @param params Enhancement parameters
 */
void applyContrastLimiting(const Mat& src, Mat& dst, const EnhancementParams& params) {
    // Convert to float
    Mat srcFloat;
    src.convertTo(srcFloat, CV_32F, 1.0/255.0);
    
    // Apply contrast limiting
    Mat enhanced;
    srcFloat.convertTo(enhanced, CV_32F);
    
    // Limit contrast
    enhanced = min(enhanced, params.contrastLimit);
    
    // Convert back to 8-bit
    enhanced.convertTo(dst, CV_8U, 255.0);
}

/**
 * @brief Function to apply selected enhancement method
 * @param src Input image
 * @param dst Output enhanced image
 * @param method Enhancement method
 * @param params Enhancement parameters
 */
void applyEnhancement(const Mat& src, Mat& dst, EnhancementMethod method, 
                     const EnhancementParams& params) {
    switch (method) {
        case UNSHARP_MASKING:
            applyUnsharpMasking(src, dst, params);
            break;
        case GAMMA_CORRECTION:
            applyGammaCorrection(src, dst, params);
            break;
        case TONE_MAPPING:
            applyToneMapping(src, dst, params);
            break;
        case HISTOGRAM_EQUALIZATION:
            applyHistogramEqualization(src, dst, params);
            break;
        case CLAHE:
            applyCLAHE(src, dst, params);
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
        case CONTRAST_LIMITING:
            applyContrastLimiting(src, dst, params);
            break;
    }
}

/**
 * @brief Function to send enhancement data to MATLAB
 * @param matlabPtr MATLAB engine pointer
 * @param src Original image
 * @param dst Enhanced image
 * @param method Enhancement method
 * @param params Enhancement parameters
 */
void sendEnhancementToMATLAB(std::unique_ptr<matlab::engine::MATLABEngine>& matlabPtr, 
                            const Mat& src, const Mat& dst, EnhancementMethod method, 
                            const EnhancementParams& params) {
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
        
        // Enhanced image
        auto dimsDst = factory.createArray<std::size_t>({1, 3}, 
            {static_cast<std::size_t>(rgbDst.rows), 
             static_cast<std::size_t>(rgbDst.cols), 
             static_cast<std::size_t>(rgbDst.channels())});
        auto matlabDst = factory.createArray<uint8_t>(dimsDst);
        auto dstPtr = matlabDst.release();
        memcpy(dstPtr, rgbDst.data, rgbDst.total() * rgbDst.elemSize());
        
        // Set variables in MATLAB workspace
        matlabPtr->setVariable(u"originalImage", matlabSrc);
        matlabPtr->setVariable(u"enhancedImage", matlabDst);
        
        // Execute MATLAB commands
        string methodName = getEnhancementMethodName(method);
        string matlabCmd = "figure; subplot(1,2,1); imshow(originalImage); title('Original'); "
                          "subplot(1,2,2); imshow(enhancedImage); title('" + methodName + "');";
        matlabPtr->eval(matlab::engine::convertUTF8StringToUTF16String(matlabCmd));
        
        // Display enhancement information
        matlabPtr->eval(u"fprintf('Enhancement Method: " + matlab::engine::convertUTF8StringToUTF16String(methodName) + "\\n');");
        
        if (method == GAMMA_CORRECTION) {
            matlabPtr->eval(u"fprintf('Gamma Value: %.2f\\n', " + to_string(params.gammaValue) + u");");
        }
        
        cout << "Enhancement data sent to MATLAB successfully!" << endl;
        
    } catch (const std::exception& e) {
        cerr << "Error sending enhancement data to MATLAB: " << e.what() << endl;
    }
}

/**
 * @brief Main function for advanced image enhancement
 * @return int Exit status
 */
int main() {
    cout << "=== Advanced Image Enhancement - Intermediate Level 15 ===" << endl;
    cout << "This program demonstrates advanced image enhancement techniques." << endl;
    
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
        
        // Initialize enhancement parameters
        EnhancementParams params;
        params.unsharpAmount = 1.5;
        params.unsharpRadius = 1.0;
        params.gammaValue = 1.2;
        params.toneMappingAlpha = 1.0;
        params.toneMappingBeta = 0.0;
        params.claheClipLimit = 2.0;
        params.claheTileGridSize = Size(8, 8);
        params.bilateralSigmaColor = 80.0;
        params.bilateralSigmaSpace = 80.0;
        params.bilateralDiameter = 15;
        params.nlmH = 10.0;
        params.nlmTemplateWindowSize = 7;
        params.nlmSearchWindowSize = 21;
        params.edgePreservingSigmaS = 50.0;
        params.edgePreservingSigmaR = 0.4;
        params.detailEnhancementAlpha = 0.5;
        params.contrastLimit = 0.8;
        
        // Initialize enhancement method
        EnhancementMethod currentMethod = UNSHARP_MASKING;
        
        // Create Mat objects for frame processing
        Mat frame, enhancedFrame, displayFrame;
        
        cout << "\nStarting camera feed with image enhancement..." << endl;
        cout << "Controls:" << endl;
        cout << "  'q' - Quit" << endl;
        cout << "  '0' - Unsharp Masking" << endl;
        cout << "  '1' - Gamma Correction" << endl;
        cout << "  '2' - Tone Mapping" << endl;
        cout << "  '3' - Histogram Equalization" << endl;
        cout << "  '4' - CLAHE" << endl;
        cout << "  '5' - Bilateral Filter" << endl;
        cout << "  '6' - Non-Local Means" << endl;
        cout << "  '7' - Edge Preserving" << endl;
        cout << "  '8' - Detail Enhancement" << endl;
        cout << "  '9' - Contrast Limiting" << endl;
        cout << "  '+' - Increase parameter" << endl;
        cout << "  '-' - Decrease parameter" << endl;
        cout << "  'm' - Send to MATLAB" << endl;
        cout << "  's' - Save current enhancement" << endl;
        
        // Main capture loop
        while (true) {
            // Capture frame from camera
            cap >> frame;
            
            // Check if frame was captured successfully
            if (frame.empty()) {
                cerr << "Warning: Could not capture frame!" << endl;
                continue;
            }
            
            // Apply selected enhancement method
            applyEnhancement(frame, enhancedFrame, currentMethod, params);
            
            // Create display frame
            displayFrame = enhancedFrame;
            
            // Create side-by-side comparison
            Mat comparison;
            hconcat(frame, displayFrame, comparison);
            
            // Add labels
            string methodName = getEnhancementMethodName(currentMethod);
            putText(comparison, "Original", Point(10, 30), 
                   FONT_HERSHEY_SIMPLEX, 0.7, Scalar(0, 255, 0), 2);
            putText(comparison, methodName, Point(frame.cols + 10, 30), 
                   FONT_HERSHEY_SIMPLEX, 0.7, Scalar(0, 255, 0), 2);
            
            // Add parameter information
            stringstream ss;
            switch (currentMethod) {
                case UNSHARP_MASKING:
                    ss << "Amount: " << params.unsharpAmount;
                    break;
                case GAMMA_CORRECTION:
                    ss << "Gamma: " << params.gammaValue;
                    break;
                case TONE_MAPPING:
                    ss << "Alpha: " << params.toneMappingAlpha;
                    break;
                case CLAHE:
                    ss << "Clip Limit: " << params.claheClipLimit;
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
                case CONTRAST_LIMITING:
                    ss << "Limit: " << params.contrastLimit;
                    break;
                default:
                    ss << "N/A";
                    break;
            }
            
            putText(comparison, ss.str(), Point(10, 60), 
                   FONT_HERSHEY_SIMPLEX, 0.5, Scalar(255, 255, 255), 1);
            
            // Display the comparison
            imshow("Advanced Image Enhancement", comparison);
            
            // Handle keyboard input
            char key = waitKey(1) & 0xFF;
            
            if (key == 'q' || key == 27) { // 'q' or ESC to quit
                cout << "Quitting..." << endl;
                break;
            }
            else if (key >= '0' && key <= '9') { // Method selection
                currentMethod = static_cast<EnhancementMethod>(key - '0');
                cout << "Selected method: " << getEnhancementMethodName(currentMethod) << endl;
            }
            else if (key == '+') { // Increase parameter
                switch (currentMethod) {
                    case UNSHARP_MASKING:
                        params.unsharpAmount = min(5.0, params.unsharpAmount + 0.1);
                        cout << "Unsharp amount increased to: " << params.unsharpAmount << endl;
                        break;
                    case GAMMA_CORRECTION:
                        params.gammaValue = min(3.0, params.gammaValue + 0.1);
                        cout << "Gamma value increased to: " << params.gammaValue << endl;
                        break;
                    case TONE_MAPPING:
                        params.toneMappingAlpha = min(2.0, params.toneMappingAlpha + 0.1);
                        cout << "Tone mapping alpha increased to: " << params.toneMappingAlpha << endl;
                        break;
                    case CLAHE:
                        params.claheClipLimit = min(10.0, params.claheClipLimit + 0.5);
                        cout << "CLAHE clip limit increased to: " << params.claheClipLimit << endl;
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
                    case CONTRAST_LIMITING:
                        params.contrastLimit = min(1.0, params.contrastLimit + 0.1);
                        cout << "Contrast limit increased to: " << params.contrastLimit << endl;
                        break;
                }
            }
            else if (key == '-') { // Decrease parameter
                switch (currentMethod) {
                    case UNSHARP_MASKING:
                        params.unsharpAmount = max(0.1, params.unsharpAmount - 0.1);
                        cout << "Unsharp amount decreased to: " << params.unsharpAmount << endl;
                        break;
                    case GAMMA_CORRECTION:
                        params.gammaValue = max(0.1, params.gammaValue - 0.1);
                        cout << "Gamma value decreased to: " << params.gammaValue << endl;
                        break;
                    case TONE_MAPPING:
                        params.toneMappingAlpha = max(0.1, params.toneMappingAlpha - 0.1);
                        cout << "Tone mapping alpha decreased to: " << params.toneMappingAlpha << endl;
                        break;
                    case CLAHE:
                        params.claheClipLimit = max(0.1, params.claheClipLimit - 0.5);
                        cout << "CLAHE clip limit decreased to: " << params.claheClipLimit << endl;
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
                    case CONTRAST_LIMITING:
                        params.contrastLimit = max(0.1, params.contrastLimit - 0.1);
                        cout << "Contrast limit decreased to: " << params.contrastLimit << endl;
                        break;
                }
            }
            else if (key == 'm') { // Send to MATLAB
                sendEnhancementToMATLAB(matlabPtr, frame, displayFrame, currentMethod, params);
            }
            else if (key == 's') { // Save current enhancement
                string filename = "enhancement_" + methodName + ".jpg";
                imwrite(filename, displayFrame);
                cout << "Enhancement saved as: " << filename << endl;
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
 * g++ -std=c++17 camera_intermediate_15.cpp -o camera_intermediate_15 \
 *     `pkg-config --cflags --libs opencv4` \
 *     -I/Applications/MATLAB_R2023b.app/extern/include \
 *     -L/Applications/MATLAB_R2023b.app/bin/maci64 \
 *     -lMatlabDataArray -lMatlabEngine
 * 
 * @brief Usage:
 * 1. Make sure your camera is connected and working
 * 2. Run the executable: ./camera_intermediate_15
 * 3. Use keyboard controls to switch between enhancement methods
 * 4. Adjust parameters with '+'/'-' keys
 * 5. Press 'm' to send data to MATLAB
 * 6. Press 's' to save current enhancement
 * 
 * @brief Learning Objectives:
 * - Understand advanced image enhancement techniques
 * - Learn unsharp masking and gamma correction
 * - Understand tone mapping and histogram equalization
 * - Learn CLAHE and bilateral filtering
 * - Understand non-local means and edge preserving filters
 * - Learn detail enhancement and contrast limiting
 * - Learn MATLAB integration for enhancement analysis
 * - Understand enhancement parameters and their effects
 */
