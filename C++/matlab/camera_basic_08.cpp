/**
 * @file camera_basic_08.cpp
 * @brief Histogram Analysis - Beginner Level 8
 * @description This program demonstrates histogram calculation, analysis, and
 *              equalization using OpenCV and MATLAB integration for real-time
 *              image processing and analysis.
 * @author Educational C++ MATLAB Integration Project
 * @date 2024
 * @version 1.0
 */

#include <opencv2/opencv.hpp>
#include <iostream>
#include <matlab/engine.hpp>
#include <memory>
#include <vector>
#include <iomanip>

using namespace cv;
using namespace std;

/**
 * @brief Structure to hold histogram data
 */
struct HistogramData {
    Mat histogram;
    Mat normalizedHistogram;
    Mat cumulativeHistogram;
    double minVal;
    double maxVal;
    double meanVal;
    double stdDev;
};

/**
 * @brief Function to calculate histogram for a single channel
 * @param src Input image (single channel)
 * @param hist Output histogram
 * @param bins Number of bins
 */
void calculateHistogram(const Mat& src, Mat& hist, int bins = 256) {
    int histSize[] = {bins};
    float range[] = {0, 256};
    const float* ranges[] = {range};
    int channels[] = {0};
    
    calcHist(&src, 1, channels, Mat(), hist, 1, histSize, ranges, true, false);
}

/**
 * @brief Function to calculate histogram for all channels
 * @param src Input image (3-channel)
 * @param histograms Vector of histograms for each channel
 * @param bins Number of bins
 */
void calculateMultiChannelHistogram(const Mat& src, vector<Mat>& histograms, int bins = 256) {
    histograms.clear();
    histograms.resize(3);
    
    vector<Mat> channels;
    split(src, channels);
    
    for (int i = 0; i < 3; i++) {
        calculateHistogram(channels[i], histograms[i], bins);
    }
}

/**
 * @brief Function to normalize histogram
 * @param hist Input histogram
 * @param normalized Output normalized histogram
 */
void normalizeHistogram(const Mat& hist, Mat& normalized) {
    normalize(hist, normalized, 0, 255, NORM_MINMAX);
}

/**
 * @brief Function to calculate cumulative histogram
 * @param hist Input histogram
 * @param cumulative Output cumulative histogram
 */
void calculateCumulativeHistogram(const Mat& hist, Mat& cumulative) {
    cumulative = Mat::zeros(hist.size(), hist.type());
    cumulative.at<float>(0) = hist.at<float>(0);
    
    for (int i = 1; i < hist.rows; i++) {
        cumulative.at<float>(i) = cumulative.at<float>(i-1) + hist.at<float>(i);
    }
}

/**
 * @brief Function to calculate histogram statistics
 * @param hist Input histogram
 * @param data Output histogram data structure
 */
void calculateHistogramStatistics(const Mat& hist, HistogramData& data) {
    // Calculate basic statistics
    minMaxLoc(hist, &data.minVal, &data.maxVal);
    
    // Calculate mean
    data.meanVal = 0;
    for (int i = 0; i < hist.rows; i++) {
        data.meanVal += i * hist.at<float>(i);
    }
    data.meanVal /= sum(hist)[0];
    
    // Calculate standard deviation
    data.stdDev = 0;
    for (int i = 0; i < hist.rows; i++) {
        double diff = i - data.meanVal;
        data.stdDev += diff * diff * hist.at<float>(i);
    }
    data.stdDev = sqrt(data.stdDev / sum(hist)[0]);
    
    // Store histogram data
    hist.copyTo(data.histogram);
    normalizeHistogram(hist, data.normalizedHistogram);
    calculateCumulativeHistogram(hist, data.cumulativeHistogram);
}

/**
 * @brief Function to create histogram visualization
 * @param histograms Vector of histograms
 * @param colors Vector of colors for each channel
 * @param width Width of the histogram image
 * @param height Height of the histogram image
 * @return Mat Histogram visualization
 */
Mat createHistogramVisualization(const vector<Mat>& histograms, const vector<Scalar>& colors, 
                                int width = 512, int height = 400) {
    Mat histImage = Mat::zeros(height, width, CV_8UC3);
    
    // Find maximum value for scaling
    double maxVal = 0;
    for (const auto& hist : histograms) {
        double tempMax;
        minMaxLoc(hist, nullptr, &tempMax);
        maxVal = max(maxVal, tempMax);
    }
    
    // Draw histograms
    for (size_t i = 0; i < histograms.size(); i++) {
        const Mat& hist = histograms[i];
        Scalar color = colors[i];
        
        for (int j = 0; j < hist.rows; j++) {
            int binVal = cvRound(hist.at<float>(j) * height / maxVal);
            rectangle(histImage, Point(j * width / hist.rows, height - binVal),
                     Point((j + 1) * width / hist.rows, height), color, -1);
        }
    }
    
    return histImage;
}

/**
 * @brief Function to apply histogram equalization
 * @param src Input image
 * @param dst Output equalized image
 */
void applyHistogramEqualization(const Mat& src, Mat& dst) {
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
 * @brief Function to apply CLAHE (Contrast Limited Adaptive Histogram Equalization)
 * @param src Input image
 * @param dst Output CLAHE image
 * @param clipLimit Clip limit for CLAHE
 * @param tileGridSize Tile grid size for CLAHE
 */
void applyCLAHE(const Mat& src, Mat& dst, double clipLimit = 2.0, Size tileGridSize = Size(8, 8)) {
    if (src.channels() == 1) {
        Ptr<CLAHE> clahe = createCLAHE(clipLimit, tileGridSize);
        clahe->apply(src, dst);
    } else {
        vector<Mat> channels;
        split(src, channels);
        
        vector<Mat> claheChannels;
        Ptr<CLAHE> clahe = createCLAHE(clipLimit, tileGridSize);
        
        for (const auto& channel : channels) {
            Mat claheChannel;
            clahe->apply(channel, claheChannel);
            claheChannels.push_back(claheChannel);
        }
        
        merge(claheChannels, dst);
    }
}

/**
 * @brief Function to send histogram data to MATLAB
 * @param matlabPtr MATLAB engine pointer
 * @param src Original image
 * @param equalized Equalized image
 * @param histograms Vector of histograms
 * @param colors Vector of colors
 */
void sendHistogramToMATLAB(std::unique_ptr<matlab::engine::MATLABEngine>& matlabPtr, 
                          const Mat& src, const Mat& equalized, 
                          const vector<Mat>& histograms, const vector<Scalar>& colors) {
    try {
        // Convert BGR to RGB for MATLAB
        Mat rgbSrc, rgbEqualized;
        cvtColor(src, rgbSrc, COLOR_BGR2RGB);
        cvtColor(equalized, rgbEqualized, COLOR_BGR2RGB);
        
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
        
        // Equalized image
        auto dimsEq = factory.createArray<std::size_t>({1, 3}, 
            {static_cast<std::size_t>(rgbEqualized.rows), 
             static_cast<std::size_t>(rgbEqualized.cols), 
             static_cast<std::size_t>(rgbEqualized.channels())});
        auto matlabEq = factory.createArray<uint8_t>(dimsEq);
        auto eqPtr = matlabEq.release();
        memcpy(eqPtr, rgbEqualized.data, rgbEqualized.total() * rgbEqualized.elemSize());
        
        // Set variables in MATLAB workspace
        matlabPtr->setVariable(u"originalImage", matlabSrc);
        matlabPtr->setVariable(u"equalizedImage", matlabEq);
        
        // Execute MATLAB commands
        matlabPtr->eval(u"figure; subplot(2,2,1); imshow(originalImage); title('Original');");
        matlabPtr->eval(u"subplot(2,2,2); imshow(equalizedImage); title('Histogram Equalized');");
        
        // Calculate and display histograms in MATLAB
        matlabPtr->eval(u"[r_hist, r_bins] = imhist(originalImage(:,:,1));");
        matlabPtr->eval(u"[g_hist, g_bins] = imhist(originalImage(:,:,2));");
        matlabPtr->eval(u"[b_hist, b_bins] = imhist(originalImage(:,:,3));");
        
        matlabPtr->eval(u"subplot(2,2,3); plot(r_bins, r_hist, 'r', g_bins, g_hist, 'g', b_bins, b_hist, 'b');");
        matlabPtr->eval(u"title('Original Histograms'); xlabel('Intensity'); ylabel('Count');");
        matlabPtr->eval(u"legend('Red', 'Green', 'Blue');");
        
        matlabPtr->eval(u"[r_hist_eq, r_bins_eq] = imhist(equalizedImage(:,:,1));");
        matlabPtr->eval(u"[g_hist_eq, g_bins_eq] = imhist(equalizedImage(:,:,2));");
        matlabPtr->eval(u"[b_hist_eq, b_bins_eq] = imhist(equalizedImage(:,:,3));");
        
        matlabPtr->eval(u"subplot(2,2,4); plot(r_bins_eq, r_hist_eq, 'r', g_bins_eq, g_hist_eq, 'g', b_bins_eq, b_hist_eq, 'b');");
        matlabPtr->eval(u"title('Equalized Histograms'); xlabel('Intensity'); ylabel('Count');");
        matlabPtr->eval(u"legend('Red', 'Green', 'Blue');");
        
        cout << "Histogram data sent to MATLAB successfully!" << endl;
        
    } catch (const std::exception& e) {
        cerr << "Error sending histogram data to MATLAB: " << e.what() << endl;
    }
}

/**
 * @brief Main function for histogram analysis
 * @return int Exit status
 */
int main() {
    cout << "=== Histogram Analysis - Beginner Level 8 ===" << endl;
    cout << "This program demonstrates histogram calculation, analysis, and equalization." << endl;
    
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
        
        // Initialize histogram data
        vector<Mat> histograms;
        vector<Scalar> colors = {Scalar(0, 0, 255), Scalar(0, 255, 0), Scalar(255, 0, 0)}; // BGR colors
        HistogramData histData;
        
        // Create Mat objects for frame processing
        Mat frame, equalizedFrame, claheFrame, histogramImage;
        
        cout << "\nStarting camera feed with histogram analysis..." << endl;
        cout << "Controls:" << endl;
        cout << "  'q' - Quit" << endl;
        cout << "  'h' - Show histogram" << endl;
        cout << "  'e' - Apply histogram equalization" << endl;
        cout << "  'c' - Apply CLAHE" << endl;
        cout << "  'm' - Send to MATLAB" << endl;
        cout << "  's' - Save current frame and histogram" << endl;
        
        bool showHistogram = false;
        bool showEqualized = false;
        bool showCLAHE = false;
        
        // Main capture loop
        while (true) {
            // Capture frame from camera
            cap >> frame;
            
            // Check if frame was captured successfully
            if (frame.empty()) {
                cerr << "Warning: Could not capture frame!" << endl;
                continue;
            }
            
            // Calculate histograms
            calculateMultiChannelHistogram(frame, histograms);
            
            // Apply histogram equalization
            applyHistogramEqualization(frame, equalizedFrame);
            
            // Apply CLAHE
            applyCLAHE(frame, claheFrame);
            
            // Create display frame
            Mat displayFrame = frame.clone();
            
            if (showHistogram) {
                histogramImage = createHistogramVisualization(histograms, colors);
                imshow("Histogram", histogramImage);
            }
            
            if (showEqualized) {
                displayFrame = equalizedFrame.clone();
            }
            
            if (showCLAHE) {
                displayFrame = claheFrame.clone();
            }
            
            // Add information overlay
            string info = "Original";
            if (showEqualized) info = "Histogram Equalized";
            if (showCLAHE) info = "CLAHE";
            
            putText(displayFrame, info, Point(10, 30), 
                   FONT_HERSHEY_SIMPLEX, 0.7, Scalar(0, 255, 0), 2);
            
            putText(displayFrame, "Press 'h' for histogram, 'e' for equalization, 'c' for CLAHE", 
                   Point(10, displayFrame.rows - 20), 
                   FONT_HERSHEY_SIMPLEX, 0.5, Scalar(255, 255, 255), 1);
            
            // Display the frame
            imshow("Histogram Analysis", displayFrame);
            
            // Handle keyboard input
            char key = waitKey(1) & 0xFF;
            
            if (key == 'q' || key == 27) { // 'q' or ESC to quit
                cout << "Quitting..." << endl;
                break;
            }
            else if (key == 'h') { // Toggle histogram display
                showHistogram = !showHistogram;
                if (!showHistogram) {
                    destroyWindow("Histogram");
                }
                cout << "Histogram display: " << (showHistogram ? "ON" : "OFF") << endl;
            }
            else if (key == 'e') { // Toggle histogram equalization
                showEqualized = !showEqualized;
                showCLAHE = false; // Turn off CLAHE
                cout << "Histogram equalization: " << (showEqualized ? "ON" : "OFF") << endl;
            }
            else if (key == 'c') { // Toggle CLAHE
                showCLAHE = !showCLAHE;
                showEqualized = false; // Turn off equalization
                cout << "CLAHE: " << (showCLAHE ? "ON" : "OFF") << endl;
            }
            else if (key == 'm') { // Send to MATLAB
                sendHistogramToMATLAB(matlabPtr, frame, equalizedFrame, histograms, colors);
            }
            else if (key == 's') { // Save current frame and histogram
                string filename = "histogram_analysis.jpg";
                imwrite(filename, displayFrame);
                cout << "Frame saved as: " << filename << endl;
                
                if (showHistogram) {
                    string histFilename = "histogram_plot.jpg";
                    imwrite(histFilename, histogramImage);
                    cout << "Histogram saved as: " << histFilename << endl;
                }
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
 * g++ -std=c++17 camera_basic_08.cpp -o camera_basic_08 \
 *     `pkg-config --cflags --libs opencv4` \
 *     -I/Applications/MATLAB_R2023b.app/extern/include \
 *     -L/Applications/MATLAB_R2023b.app/bin/maci64 \
 *     -lMatlabDataArray -lMatlabEngine
 * 
 * @brief Usage:
 * 1. Make sure your camera is connected and working
 * 2. Run the executable: ./camera_basic_08
 * 3. Use keyboard controls:
 *    - 'h': Toggle histogram display
 *    - 'e': Toggle histogram equalization
 *    - 'c': Toggle CLAHE
 *    - 'm': Send data to MATLAB
 *    - 's': Save current frame and histogram
 * 
 * @brief Learning Objectives:
 * - Understand histogram calculation and analysis
 * - Learn histogram equalization techniques
 * - Understand CLAHE (Contrast Limited Adaptive Histogram Equalization)
 * - Learn histogram visualization methods
 * - Understand histogram statistics
 * - Learn MATLAB integration for histogram analysis
 * - Understand contrast enhancement techniques
 * - Learn to analyze image quality using histograms
 */
