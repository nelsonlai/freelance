/**
 * @file camera_basic_04.cpp
 * @brief Image Saving and Loading - Beginner Level 4
 * @description This program demonstrates how to save captured images in different
 *              formats and load them back for processing using OpenCV and MATLAB.
 * @author Educational C++ MATLAB Integration Project
 * @date 2024
 * @version 1.0
 */

#include <opencv2/opencv.hpp>
#include <iostream>
#include <matlab/engine.hpp>
#include <memory>
#include <filesystem>
#include <iomanip>
#include <sstream>

using namespace cv;
using namespace std;

/**
 * @brief Function to save image in multiple formats
 * @param image Input image to save
 * @param baseName Base name for the saved files
 * @return vector<string> Vector of saved filenames
 */
vector<string> saveImageInMultipleFormats(const Mat& image, const string& baseName) {
    vector<string> savedFiles;
    vector<string> extensions = {".jpg", ".png", ".bmp", ".tiff", ".webp"};
    vector<int> compressionParams;
    
    cout << "Saving image in multiple formats..." << endl;
    
    for (const auto& ext : extensions) {
        string filename = baseName + ext;
        
        // Set compression parameters based on format
        if (ext == ".jpg") {
            compressionParams = {IMWRITE_JPEG_QUALITY, 95};
        } else if (ext == ".png") {
            compressionParams = {IMWRITE_PNG_COMPRESSION, 3};
        } else if (ext == ".webp") {
            compressionParams = {IMWRITE_WEBP_QUALITY, 90};
        } else {
            compressionParams = {};
        }
        
        bool success = imwrite(filename, image, compressionParams);
        if (success) {
            savedFiles.push_back(filename);
            cout << "Saved: " << filename << endl;
            
            // Get file size
            if (filesystem::exists(filename)) {
                auto fileSize = filesystem::file_size(filename);
                cout << "  File size: " << fileSize << " bytes" << endl;
            }
        } else {
            cerr << "Failed to save: " << filename << endl;
        }
    }
    
    return savedFiles;
}

/**
 * @brief Function to load and display saved images
 * @param filenames Vector of filenames to load
 * @return vector<Mat> Vector of loaded images
 */
vector<Mat> loadAndDisplayImages(const vector<string>& filenames) {
    vector<Mat> loadedImages;
    
    cout << "\nLoading saved images..." << endl;
    
    for (const auto& filename : filenames) {
        if (filesystem::exists(filename)) {
            Mat image = imread(filename);
            if (!image.empty()) {
                loadedImages.push_back(image);
                cout << "Loaded: " << filename << endl;
                cout << "  Dimensions: " << image.cols << " x " << image.rows << endl;
                cout << "  Channels: " << image.channels() << endl;
                cout << "  Data type: " << image.type() << endl;
            } else {
                cerr << "Failed to load: " << filename << endl;
            }
        } else {
            cerr << "File not found: " << filename << endl;
        }
    }
    
    return loadedImages;
}

/**
 * @brief Function to send image data to MATLAB for analysis
 * @param matlabPtr MATLAB engine pointer
 * @param image Input image
 * @param imageName Name for the MATLAB variable
 */
void sendImageToMATLAB(std::unique_ptr<matlab::engine::MATLABEngine>& matlabPtr, 
                      const Mat& image, const string& imageName) {
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
        matlabPtr->setVariable(matlab::engine::convertUTF8StringToUTF16String(imageName), matlabImage);
        
        // Execute MATLAB commands for analysis
        string matlabCmd = "figure; imshow(" + imageName + "); title('" + imageName + " loaded in MATLAB');";
        matlabPtr->eval(matlab::engine::convertUTF8StringToUTF16String(matlabCmd));
        
        // Get image statistics
        string statsCmd = "fprintf('Image Statistics for " + imageName + ":\\n');";
        matlabPtr->eval(matlab::engine::convertUTF8StringToUTF16String(statsCmd));
        
        string sizeCmd = "fprintf('Size: %d x %d x %d\\n', size(" + imageName + ",1), size(" + imageName + ",2), size(" + imageName + ",3));";
        matlabPtr->eval(matlab::engine::convertUTF8StringToUTF16String(sizeCmd));
        
        string meanCmd = "fprintf('Mean values: R=%.2f, G=%.2f, B=%.2f\\n', mean(mean(" + imageName + "(:,:,1))), mean(mean(" + imageName + "(:,:,2))), mean(mean(" + imageName + "(:,:,3))));";
        matlabPtr->eval(matlab::engine::convertUTF8StringToUTF16String(meanCmd));
        
        cout << "Image " << imageName << " sent to MATLAB successfully!" << endl;
        
    } catch (const std::exception& e) {
        cerr << "Error sending image to MATLAB: " << e.what() << endl;
    }
}

/**
 * @brief Main function for image saving and loading
 * @return int Exit status
 */
int main() {
    cout << "=== Image Saving and Loading - Beginner Level 4 ===" << endl;
    cout << "This program demonstrates image saving, loading, and MATLAB integration." << endl;
    
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
        
        // Create Mat objects for frame processing
        Mat frame, displayFrame;
        
        cout << "\nStarting camera feed..." << endl;
        cout << "Controls:" << endl;
        cout << "  'q' - Quit" << endl;
        cout << "  's' - Save current frame in multiple formats" << endl;
        cout << "  'l' - Load and display saved images" << endl;
        cout << "  'm' - Send current frame to MATLAB" << endl;
        cout << "  'c' - Compare loaded images" << endl;
        
        int frameCount = 0;
        vector<string> savedFiles;
        
        // Main capture loop
        while (true) {
            // Capture frame from camera
            cap >> frame;
            
            // Check if frame was captured successfully
            if (frame.empty()) {
                cerr << "Warning: Could not capture frame!" << endl;
                continue;
            }
            
            frameCount++;
            
            // Create a copy for display
            frame.copyTo(displayFrame);
            
            // Add frame information overlay
            stringstream ss;
            ss << "Frame: " << frameCount;
            putText(displayFrame, ss.str(), Point(10, 30), 
                   FONT_HERSHEY_SIMPLEX, 0.7, Scalar(0, 255, 0), 2);
            
            putText(displayFrame, "Press 's' to save, 'l' to load, 'm' for MATLAB", 
                   Point(10, displayFrame.rows - 20), 
                   FONT_HERSHEY_SIMPLEX, 0.5, Scalar(255, 255, 255), 1);
            
            // Display the frame
            imshow("Image Saving and Loading", displayFrame);
            
            // Handle keyboard input
            char key = waitKey(1) & 0xFF;
            
            if (key == 'q' || key == 27) { // 'q' or ESC to quit
                cout << "Quitting..." << endl;
                break;
            }
            else if (key == 's') { // 's' to save current frame
                stringstream filename;
                filename << "captured_frame_" << setfill('0') << setw(4) << frameCount;
                
                cout << "\nSaving frame " << frameCount << "..." << endl;
                vector<string> files = saveImageInMultipleFormats(frame, filename.str());
                savedFiles.insert(savedFiles.end(), files.begin(), files.end());
            }
            else if (key == 'l') { // 'l' to load saved images
                if (!savedFiles.empty()) {
                    cout << "\nLoading saved images..." << endl;
                    vector<Mat> loadedImages = loadAndDisplayImages(savedFiles);
                    
                    // Display loaded images
                    for (size_t i = 0; i < loadedImages.size(); i++) {
                        string windowName = "Loaded Image " + to_string(i + 1);
                        imshow(windowName, loadedImages[i]);
                    }
                    
                    cout << "Press any key to close loaded image windows..." << endl;
                    waitKey(0);
                    
                    // Close loaded image windows
                    for (size_t i = 0; i < loadedImages.size(); i++) {
                        string windowName = "Loaded Image " + to_string(i + 1);
                        destroyWindow(windowName);
                    }
                } else {
                    cout << "No saved files to load!" << endl;
                }
            }
            else if (key == 'm') { // 'm' to send to MATLAB
                stringstream varName;
                varName << "frame_" << frameCount;
                sendImageToMATLAB(matlabPtr, frame, varName.str());
            }
            else if (key == 'c') { // 'c' to compare loaded images
                if (!savedFiles.empty()) {
                    cout << "\nComparing saved images..." << endl;
                    vector<Mat> loadedImages = loadAndDisplayImages(savedFiles);
                    
                    if (loadedImages.size() >= 2) {
                        // Create comparison image
                        Mat comparison;
                        hconcat(loadedImages[0], loadedImages[1], comparison);
                        
                        // Add labels
                        putText(comparison, "Format 1", Point(10, 30), 
                               FONT_HERSHEY_SIMPLEX, 0.7, Scalar(0, 255, 0), 2);
                        putText(comparison, "Format 2", Point(loadedImages[0].cols + 10, 30), 
                               FONT_HERSHEY_SIMPLEX, 0.7, Scalar(0, 255, 0), 2);
                        
                        imshow("Image Comparison", comparison);
                        cout << "Press any key to close comparison window..." << endl;
                        waitKey(0);
                        destroyWindow("Image Comparison");
                    }
                } else {
                    cout << "No saved files to compare!" << endl;
                }
            }
        }
        
        // Clean up
        cap.release();
        destroyAllWindows();
        
        // Final summary
        cout << "\n=== Session Summary ===" << endl;
        cout << "Total frames captured: " << frameCount << endl;
        cout << "Total files saved: " << savedFiles.size() << endl;
        
        if (!savedFiles.empty()) {
            cout << "Saved files:" << endl;
            for (const auto& file : savedFiles) {
                if (filesystem::exists(file)) {
                    auto fileSize = filesystem::file_size(file);
                    cout << "  " << file << " (" << fileSize << " bytes)" << endl;
                }
            }
        }
        
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
 * 3. C++17 compiler with filesystem support
 * 
 * Compilation command:
 * g++ -std=c++17 camera_basic_04.cpp -o camera_basic_04 \
 *     `pkg-config --cflags --libs opencv4` \
 *     -I/Applications/MATLAB_R2023b.app/extern/include \
 *     -L/Applications/MATLAB_R2023b.app/bin/maci64 \
 *     -lMatlabDataArray -lMatlabEngine
 * 
 * @brief Usage:
 * 1. Make sure your camera is connected and working
 * 2. Run the executable: ./camera_basic_04
 * 3. Use keyboard controls:
 *    - 's': Save current frame in multiple formats
 *    - 'l': Load and display saved images
 *    - 'm': Send current frame to MATLAB
 *    - 'c': Compare loaded images
 * 
 * @brief Learning Objectives:
 * - Understand image saving in different formats
 * - Learn compression parameters and quality settings
 * - Understand file size differences between formats
 * - Learn to load and display saved images
 * - Understand image data types and channels
 * - Learn MATLAB integration for image analysis
 * - Understand image comparison techniques
 * - Learn filesystem operations for image management
 */
