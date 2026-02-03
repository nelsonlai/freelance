/**
 * @file camera_advanced_29.cpp
 * @brief Advanced Image Quality Assessment - Advanced Level 29
 * @description This program demonstrates advanced image quality assessment
 *              including PSNR, SSIM, MSE, and other quality metrics
 *              with OpenCV and MATLAB integration.
 * @author Educational C++ MATLAB Integration Project
 * @date 2024
 * @version 1.0
 */

#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include <matlab/engine.hpp>
#include <memory>
#include <vector>
#include <cmath>

using namespace cv;
using namespace std;

/**
 * @brief Function to calculate PSNR
 * @param img1 First image
 * @param img2 Second image
 * @return double PSNR value
 */
double calculatePSNR(const Mat& img1, const Mat& img2) {
    Mat diff;
    absdiff(img1, img2, diff);
    diff.convertTo(diff, CV_32F);
    diff = diff.mul(diff);
    
    Scalar s = sum(diff);
    double sse = s.val[0] + s.val[1] + s.val[2];
    
    if (sse <= 1e-10) {
        return 0;
    } else {
        double mse = sse / (double)(img1.channels() * img1.total());
        return 10.0 * log10((255.0 * 255.0) / mse);
    }
}

/**
 * @brief Function to calculate SSIM
 * @param img1 First image
 * @param img2 Second image
 * @return double SSIM value
 */
double calculateSSIM(const Mat& img1, const Mat& img2) {
    const double C1 = 6.5025, C2 = 58.5225;
    
    Mat I1, I2;
    img1.convertTo(I1, CV_32F);
    img2.convertTo(I2, CV_32F);
    
    Mat I2_2 = I2.mul(I2);
    Mat I1_2 = I1.mul(I1);
    Mat I1_I2 = I1.mul(I2);
    
    Mat mu1, mu2;
    GaussianBlur(I1, mu1, Size(11, 11), 1.5);
    GaussianBlur(I2, mu2, Size(11, 11), 1.5);
    
    Mat mu1_2 = mu1.mul(mu1);
    Mat mu2_2 = mu2.mul(mu2);
    Mat mu1_mu2 = mu1.mul(mu2);
    
    Mat sigma1_2, sigma2_2, sigma12;
    GaussianBlur(I1_2, sigma1_2, Size(11, 11), 1.5);
    sigma1_2 -= mu1_2;
    
    GaussianBlur(I2_2, sigma2_2, Size(11, 11), 1.5);
    sigma2_2 -= mu2_2;
    
    GaussianBlur(I1_I2, sigma12, Size(11, 11), 1.5);
    sigma12 -= mu1_mu2;
    
    Mat t1, t2, t3;
    t1 = 2 * mu1_mu2 + C1;
    t2 = 2 * sigma12 + C2;
    t3 = t1.mul(t2);
    
    t1 = mu1_2 + mu2_2 + C1;
    t2 = sigma1_2 + sigma2_2 + C2;
    t1 = t1.mul(t2);
    
    Mat ssim_map;
    divide(t3, t1, ssim_map);
    
    Scalar mssim = mean(ssim_map);
    return (mssim.val[0] + mssim.val[1] + mssim.val[2]) / 3.0;
}

/**
 * @brief Function to calculate MSE
 * @param img1 First image
 * @param img2 Second image
 * @return double MSE value
 */
double calculateMSE(const Mat& img1, const Mat& img2) {
    Mat diff;
    absdiff(img1, img2, diff);
    diff.convertTo(diff, CV_32F);
    diff = diff.mul(diff);
    
    Scalar s = sum(diff);
    double sse = s.val[0] + s.val[1] + s.val[2];
    
    return sse / (double)(img1.channels() * img1.total());
}

/**
 * @brief Main function for advanced image quality assessment
 * @return int Exit status
 */
int main() {
    cout << "=== Advanced Image Quality Assessment - Advanced Level 29 ===" << endl;
    cout << "This program demonstrates advanced image quality assessment." << endl;
    
    try {
        // Initialize MATLAB engine
        cout << "Initializing MATLAB engine..." << endl;
        std::unique_ptr<matlab::engine::MATLABEngine> matlabPtr = 
            matlab::engine::startMATLAB();
        
        // Initialize camera capture
        cout << "Initializing camera..." << endl;
        VideoCapture cap(0);
        
        if (!cap.isOpened()) {
            cerr << "Error: Could not open camera!" << endl;
            return -1;
        }
        
        cout << "Camera opened successfully!" << endl;
        
        // Set camera properties
        cap.set(CAP_PROP_FRAME_WIDTH, 640);
        cap.set(CAP_PROP_FRAME_HEIGHT, 480);
        
        // Create Mat objects for frame processing
        Mat frame, referenceFrame, processedFrame, visualization;
        bool hasReference = false;
        
        cout << "\nStarting image quality assessment..." << endl;
        cout << "Controls:" << endl;
        cout << "  'q' - Quit" << endl;
        cout << "  'r' - Capture reference frame" << endl;
        cout << "  'm' - Send to MATLAB" << endl;
        cout << "  's' - Save current frame" << endl;
        
        // Main capture loop
        while (true) {
            // Capture frame from camera
            cap >> frame;
            
            if (frame.empty()) {
                cerr << "Warning: Could not capture frame!" << endl;
                continue;
            }
            
            // Create visualization
            visualization = frame.clone();
            
            if (hasReference) {
                // Calculate quality metrics
                double psnr = calculatePSNR(referenceFrame, frame);
                double ssim = calculateSSIM(referenceFrame, frame);
                double mse = calculateMSE(referenceFrame, frame);
                
                // Draw quality metrics
                string psnrText = "PSNR: " + to_string(psnr) + " dB";
                string ssimText = "SSIM: " + to_string(ssim);
                string mseText = "MSE: " + to_string(mse);
                
                putText(visualization, psnrText, Point(10, 30), FONT_HERSHEY_SIMPLEX, 0.7, Scalar(0, 255, 0), 2);
                putText(visualization, ssimText, Point(10, 60), FONT_HERSHEY_SIMPLEX, 0.7, Scalar(0, 255, 0), 2);
                putText(visualization, mseText, Point(10, 90), FONT_HERSHEY_SIMPLEX, 0.7, Scalar(0, 255, 0), 2);
                
                // Draw reference frame indicator
                putText(visualization, "Reference captured", Point(10, 120), FONT_HERSHEY_SIMPLEX, 0.7, Scalar(255, 0, 0), 2);
            } else {
                putText(visualization, "Press 'r' to capture reference", Point(10, 30), FONT_HERSHEY_SIMPLEX, 0.7, Scalar(0, 0, 255), 2);
            }
            
            // Display the visualization
            imshow("Advanced Image Quality Assessment", visualization);
            
            // Handle keyboard input
            char key = waitKey(1) & 0xFF;
            
            if (key == 'q' || key == 27) {
                cout << "Quitting..." << endl;
                break;
            }
            else if (key == 'r') {
                frame.copyTo(referenceFrame);
                hasReference = true;
                cout << "Reference frame captured!" << endl;
            }
            else if (key == 'm') {
                // Send to MATLAB
                Mat rgbFrame;
                cvtColor(visualization, rgbFrame, COLOR_BGR2RGB);
                
                matlab::data::ArrayFactory factory;
                auto dims = factory.createArray<std::size_t>({1, 3}, 
                    {static_cast<std::size_t>(rgbFrame.rows), 
                     static_cast<std::size_t>(rgbFrame.cols), 
                     static_cast<std::size_t>(rgbFrame.channels())});
                auto matlabFrame = factory.createArray<uint8_t>(dims);
                auto framePtr = matlabFrame.release();
                memcpy(framePtr, rgbFrame.data, rgbFrame.total() * rgbFrame.elemSize());
                
                matlabPtr->setVariable(u"frame", matlabFrame);
                matlabPtr->eval(u"figure; imshow(frame); title('Image Quality Assessment');");
                
                cout << "Quality assessment frame sent to MATLAB successfully!" << endl;
            }
            else if (key == 's') {
                string filename = "quality_frame_" + to_string(time(nullptr)) + ".jpg";
                imwrite(filename, visualization);
                cout << "Quality assessment frame saved as: " << filename << endl;
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
 * g++ -std=c++17 camera_advanced_29.cpp -o camera_advanced_29 \
 *     `pkg-config --cflags --libs opencv4` \
 *     -I/Applications/MATLAB_R2023b.app/extern/include \
 *     -L/Applications/MATLAB_R2023b.app/bin/maci64 \
 *     -lMatlabDataArray -lMatlabEngine
 * 
 * @brief Usage:
 * 1. Make sure your camera is connected and working
 * 2. Run the executable: ./camera_advanced_29
 * 3. Press 'r' to capture reference frame
 * 4. Press 'm' to send data to MATLAB
 * 5. Press 's' to save current frame
 * 
 * @brief Learning Objectives:
 * - Understand advanced image quality assessment
 * - Learn PSNR calculation
 * - Learn SSIM calculation
 * - Learn MSE calculation
 * - Learn MATLAB integration for quality analysis
 * - Understand computer vision in quality assessment
 */
