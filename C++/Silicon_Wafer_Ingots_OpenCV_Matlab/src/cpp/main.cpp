#include <iostream>
#include <opencv2/opencv.hpp>
#include "image_capture.h"
#include "preprocessor.h"
#include "camera_interface.h"

int main(int argc, char* argv[]) {
    std::cout << "Silicon Wafer Defect Detection - Image Capture System" << std::endl;
    std::cout << "=====================================================" << std::endl;

    // Parse command line arguments
    std::string output_dir = "data/output";
    std::string sample_id = "";
    bool use_preprocessing = true;
    bool continuous_mode = false;
    
    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        if (arg == "--output" && i + 1 < argc) {
            output_dir = argv[++i];
        } else if (arg == "--sample" && i + 1 < argc) {
            sample_id = argv[++i];
        } else if (arg == "--no-preprocessing") {
            use_preprocessing = false;
        } else if (arg == "--continuous") {
            continuous_mode = true;
        } else if (arg == "--help") {
            std::cout << "Usage: " << argv[0] << " [options]" << std::endl;
            std::cout << "Options:" << std::endl;
            std::cout << "  --output <dir>        Output directory (default: data/output)" << std::endl;
            std::cout << "  --sample <id>         Sample identifier" << std::endl;
            std::cout << "  --no-preprocessing    Skip preprocessing step" << std::endl;
            std::cout << "  --continuous          Continuous capture mode" << std::endl;
            std::cout << "  --help                Show this help message" << std::endl;
            return 0;
        }
    }

    // Create image capture system
    ImageCapture capture_system(output_dir);
    
    // Add cameras (configure based on available hardware)
    CameraConfig optical_config;
    optical_config.device_id = 0;
    optical_config.width = 1920;
    optical_config.height = 1080;
    optical_config.fps = 30;
    optical_config.type = CameraType::OPTICAL;
    
    CameraConfig infrared_config;
    infrared_config.device_id = 1;  // Adjust based on your IR camera
    infrared_config.width = 640;
    infrared_config.height = 480;
    infrared_config.fps = 15;
    infrared_config.type = CameraType::INFRARED;
    
    // Add cameras to the system
    if (!capture_system.addCamera(optical_config)) {
        std::cerr << "Failed to add optical camera" << std::endl;
        return -1;
    }
    
    // Try to add IR camera (may fail if not available)
    if (!capture_system.addCamera(infrared_config)) {
        std::cout << "Warning: Could not add IR camera, continuing with optical only" << std::endl;
    }
    
    // Initialize all cameras
    if (!capture_system.initializeAllCameras()) {
        std::cerr << "Failed to initialize cameras" << std::endl;
        return -1;
    }
    
    // Test camera connections
    if (!capture_system.testAllCameras()) {
        std::cerr << "Camera test failed" << std::endl;
        return -1;
    }
    
    // Display camera information
    std::cout << "\nCamera Information:" << std::endl;
    for (size_t i = 0; i < capture_system.getCameraCount(); ++i) {
        std::cout << "Camera " << i << ":" << std::endl;
        std::cout << capture_system.getCameraInfo(i) << std::endl;
    }
    
    // Create preprocessor if needed
    Preprocessor preprocessor;
    ProcessingConfig proc_config;
    proc_config.enable_noise_reduction = true;
    proc_config.enable_contrast_enhancement = true;
    proc_config.save_intermediate = true;
    proc_config.intermediate_dir = output_dir + "/intermediate";
    
    if (continuous_mode) {
        std::cout << "\nStarting continuous capture mode..." << std::endl;
        std::cout << "Press 'q' to quit, 'c' to capture, 'p' to pause/resume" << std::endl;
        
        if (!capture_system.startContinuousCapture()) {
            std::cerr << "Failed to start continuous capture" << std::endl;
            return -1;
        }
        
        char key;
        bool paused = false;
        
        while (true) {
            key = cv::waitKey(30) & 0xFF;
            
            if (key == 'q') {
                break;
            } else if (key == 'c') {
                // Capture images
                auto captured_files = capture_system.captureAllImages(sample_id);
                
                if (use_preprocessing && !captured_files.empty()) {
                    std::cout << "Processing captured images..." << std::endl;
                    
                    // Load images for processing
                    std::vector<cv::Mat> images;
                    for (const auto& filename : captured_files) {
                        cv::Mat img = cv::imread(filename, cv::IMREAD_GRAYSCALE);
                        if (!img.empty()) {
                            images.push_back(img);
                        }
                    }
                    
                    // Process images
                    std::vector<cv::Mat> processed_images;
                    preprocessor.processImages(images, processed_images, proc_config);
                    
                    // Save processed images
                    std::string processed_dir = output_dir + "/processed";
                    preprocessor.saveProcessedImages(processed_images, processed_dir, sample_id);
                }
                
                std::cout << "Captured " << captured_files.size() << " images" << std::endl;
            } else if (key == 'p') {
                paused = !paused;
                std::cout << (paused ? "Paused" : "Resumed") << std::endl;
            }
        }
        
        capture_system.stopContinuousCapture();
    } else {
        // Single capture mode
        std::cout << "\nCapturing images..." << std::endl;
        
        auto captured_files = capture_system.captureAllImages(sample_id);
        
        if (captured_files.empty()) {
            std::cerr << "No images captured" << std::endl;
            return -1;
        }
        
        std::cout << "Captured " << captured_files.size() << " images" << std::endl;
        
        if (use_preprocessing) {
            std::cout << "Processing captured images..." << std::endl;
            
            // Load images for processing
            std::vector<cv::Mat> images;
            for (const auto& filename : captured_files) {
                cv::Mat img = cv::imread(filename, cv::IMREAD_GRAYSCALE);
                if (!img.empty()) {
                    images.push_back(img);
                }
            }
            
            // Process images
            std::vector<cv::Mat> processed_images;
            preprocessor.processImages(images, processed_images, proc_config);
            
            // Save processed images
            std::string processed_dir = output_dir + "/processed";
            auto processed_files = preprocessor.saveProcessedImages(processed_images, processed_dir, sample_id);
            
            std::cout << "Processed " << processed_files.size() << " images" << std::endl;
            std::cout << "Processed images saved to: " << processed_dir << std::endl;
        }
        
        std::cout << "\nCapture completed successfully!" << std::endl;
        std::cout << "Images saved to: " << output_dir << std::endl;
        std::cout << "Run MATLAB script 'main_defect_detection.m' to analyze the images." << std::endl;
    }
    
    return 0;
}
