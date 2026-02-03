#include <opencv2/opencv.hpp>
#include <iostream>
#include <memory>
#include <signal.h>
#include <yaml-cpp/yaml.h>
#include <fstream>
#include <chrono>
#include <thread>
#include <filesystem>

#include "CameraCapture.h"
#include "ImagePreprocessor.h"
#include "MatlabEngineWrapper.h"
#include "DefectClassifier.h"
#include "DatabaseLogger.h"
#include "ConfigManager.h"

// Global variables for graceful shutdown
volatile bool g_running = true;
std::unique_ptr<CameraCapture> g_camera;
std::unique_ptr<DefectClassifier> g_classifier;
std::unique_ptr<DatabaseLogger> g_logger;
std::unique_ptr<ConfigManager> g_config;

// Signal handler for graceful shutdown
void signalHandler(int signal) {
    std::cout << "\nReceived signal " << signal << ". Shutting down gracefully..." << std::endl;
    g_running = false;
}


// Draw overlay on image
void drawOverlay(cv::Mat& image, const DefectResult& result, const ConfigManager& config) {
    // Define colors
    cv::Scalar normal_color(0, 255, 0);    // Green for normal
    cv::Scalar defect_color(0, 0, 255);    // Red for defect
    cv::Scalar text_color(255, 255, 255);  // White text
    
    // Choose color based on detection result
    cv::Scalar border_color = result.is_defect ? defect_color : normal_color;
    
    // Draw border around ROI
    cv::Rect roi(config.getIntParameter("preprocessing", "roi_x", 200),
                 config.getIntParameter("preprocessing", "roi_y", 150),
                 config.getIntParameter("preprocessing", "roi_width", 1520),
                 config.getIntParameter("preprocessing", "roi_height", 780));
    cv::rectangle(image, roi, border_color, 3);
    
    // Draw confidence bar
    int bar_width = 200;
    int bar_height = 20;
    int bar_x = 10;
    int bar_y = 10;
    
    cv::Rect bar_bg(bar_x, bar_y, bar_width, bar_height);
    cv::rectangle(image, bar_bg, cv::Scalar(50, 50, 50), -1);
    
    cv::Rect bar_fill(bar_x, bar_y, static_cast<int>(bar_width * result.confidence), bar_height);
    cv::rectangle(image, bar_fill, border_color, -1);
    
    // Draw text information
    std::ostringstream oss;
    oss << result.class_label << " (" << std::fixed << std::setprecision(1) 
        << result.confidence * 100 << "%)";
    
    cv::putText(image, oss.str(), cv::Point(bar_x, bar_y - 5), 
                cv::FONT_HERSHEY_SIMPLEX, 0.6, text_color, 2);
    
    // Draw status
    std::string status = result.is_defect ? "DEFECT" : "NORMAL";
    cv::putText(image, status, cv::Point(bar_x, bar_y + bar_height + 25), 
                cv::FONT_HERSHEY_SIMPLEX, 0.7, border_color, 2);
    
    // Draw processing time
    std::ostringstream time_oss;
    time_oss << "Time: " << std::fixed << std::setprecision(1) 
             << result.processing_time_ms << " ms";
    cv::putText(image, time_oss.str(), cv::Point(bar_x, bar_y + bar_height + 50), 
                cv::FONT_HERSHEY_SIMPLEX, 0.5, text_color, 1);
}

// Save detection image
void saveDetectionImage(const cv::Mat& image, const DefectResult& result, const ConfigManager& config) {
    if (!config.getBoolParameter("logging", "save_images", true)) return;
    
    // Create output directory if it doesn't exist
    std::filesystem::create_directories(config.getParameter("logging", "image_output_dir"));
    
    // Generate filename with timestamp
    auto now = std::chrono::system_clock::now();
    auto time_t = std::chrono::system_clock::to_time_t(now);
    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(
        now.time_since_epoch()) % 1000;
    
    std::ostringstream filename;
    filename << config.getParameter("logging", "image_output_dir") << "/detection_" 
             << std::put_time(std::localtime(&time_t), "%Y%m%d_%H%M%S")
             << "_" << std::setfill('0') << std::setw(3) << ms.count()
             << "_" << result.class_label << ".jpg";
    
    cv::imwrite(filename.str(), image);
}

int main(int argc, char* argv[]) {
    std::cout << "Silicon Ingot Defect Detection System" << std::endl;
    std::cout << "=====================================" << std::endl;
    
    // Set up signal handlers
    signal(SIGINT, signalHandler);
    signal(SIGTERM, signalHandler);
    
    // Load configuration
    std::string config_file = "config.yaml";
    if (argc > 1) {
        config_file = argv[1];
    }
    
    g_config = std::make_unique<ConfigManager>(config_file);
    if (!g_config->loadConfig()) {
        std::cerr << "Failed to load configuration. Using default settings." << std::endl;
    }
    
    g_config->printConfigSummary();
    
    // Initialize camera
    std::cout << "Initializing camera..." << std::endl;
    g_camera = std::make_unique<CameraCapture>(
        g_config->getIntParameter("camera", "device_id", 0),
        g_config->getIntParameter("camera", "width", 1920),
        g_config->getIntParameter("camera", "height", 1080),
        g_config->getIntParameter("camera", "fps", 30)
    );
    
    if (!g_camera->initialize()) {
        std::cerr << "Failed to initialize camera" << std::endl;
        return -1;
    }
    
    // Initialize image preprocessor
    std::cout << "Initializing image preprocessor..." << std::endl;
    auto preprocessor = std::make_shared<ImagePreprocessor>(
        g_config->getIntParameter("preprocessing", "roi_x", 200),
        g_config->getIntParameter("preprocessing", "roi_y", 150),
        g_config->getIntParameter("preprocessing", "roi_width", 1520),
        g_config->getIntParameter("preprocessing", "roi_height", 780),
        g_config->getIntParameter("preprocessing", "target_size", 224),
        g_config->getDoubleParameter("preprocessing", "clahe_clip_limit", 2.0)
    );
    
    // Initialize MATLAB wrapper
    std::cout << "Initializing MATLAB Engine..." << std::endl;
    auto matlab_wrapper = std::make_shared<MatlabEngineWrapper>(
        g_config->getParameter("inference", "matlab_script_path"),
        g_config->getParameter("inference", "model_file")
    );
    
    if (!matlab_wrapper->initialize()) {
        std::cerr << "Failed to initialize MATLAB Engine" << std::endl;
        return -1;
    }
    
    // Initialize database logger
    std::cout << "Initializing database logger..." << std::endl;
    g_logger = std::make_unique<DatabaseLogger>(
        g_config->getParameter("logging", "db_path")
    );
    
    if (!g_logger->initialize()) {
        std::cerr << "Failed to initialize database logger" << std::endl;
        return -1;
    }
    
    // Initialize defect classifier
    std::cout << "Initializing defect classifier..." << std::endl;
    g_classifier = std::make_unique<DefectClassifier>(
        g_config->getDoubleParameter("inference", "confidence_threshold", 0.75)
    );
    
    if (!g_classifier->initialize(preprocessor, matlab_wrapper)) {
        std::cerr << "Failed to initialize defect classifier" << std::endl;
        return -1;
    }
    
    std::cout << "System initialized successfully!" << std::endl;
    std::cout << "Press Ctrl+C to stop the system" << std::endl;
    std::cout << "Processing every " << g_config->getIntParameter("inference", "process_every_n_frames", 3) << " frames" << std::endl;
    
    // Main processing loop
    cv::Mat frame;
    int frame_count = 0;
    int defect_count = 0;
    auto start_time = std::chrono::steady_clock::now();
    
    while (g_running) {
        // Capture frame
        if (!g_camera->captureFrame(frame)) {
            std::cerr << "Failed to capture frame" << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            continue;
        }
        
        frame_count++;
        
        // Process every Nth frame
        if (frame_count % g_config->getIntParameter("inference", "process_every_n_frames", 3) == 0) {
            DefectResult result;
            
            if (g_classifier->classifyDefect(frame, result)) {
                // Draw overlay
                drawOverlay(frame, result, *g_config);
                
                // Save image if defect detected
                if (result.is_defect) {
                    defect_count++;
                    saveDetectionImage(frame, result, *g_config);
                    std::cout << "DEFECT DETECTED: " << result.report << std::endl;
                    
                    // Log to database
                    std::string image_path = "";
                    if (g_config->getBoolParameter("logging", "save_images", true)) {
                        // Generate image path for database
                        auto now = std::chrono::system_clock::now();
                        auto time_t = std::chrono::system_clock::to_time_t(now);
                        auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(
                            now.time_since_epoch()) % 1000;
                        
                        std::ostringstream filename;
                        filename << g_config->getParameter("logging", "image_output_dir") << "/detection_" 
                                 << std::put_time(std::localtime(&time_t), "%Y%m%d_%H%M%S")
                                 << "_" << std::setfill('0') << std::setw(3) << ms.count()
                                 << "_" << result.class_label << ".jpg";
                        image_path = filename.str();
                    }
                    
                    g_logger->logDefect(result.class_label, result.confidence, 
                                       result.processing_time_ms, image_path);
                }
                
                // Display statistics every 100 frames
                if (frame_count % 100 == 0) {
                    auto current_time = std::chrono::steady_clock::now();
                    auto elapsed = std::chrono::duration_cast<std::chrono::seconds>(
                        current_time - start_time).count();
                    
                    double fps = frame_count / static_cast<double>(elapsed);
                    double avg_processing_time = g_classifier->getAverageProcessingTime();
                    
                    std::cout << "Frame: " << frame_count 
                              << ", FPS: " << std::fixed << std::setprecision(1) << fps
                              << ", Defects: " << defect_count
                              << ", Avg Processing Time: " << avg_processing_time << " ms" << std::endl;
                }
            } else {
                std::cerr << "Classification failed for frame " << frame_count << std::endl;
            }
        }
        
        // Display frame
        cv::imshow("Silicon Ingot Defect Detection", frame);
        
        // Check for key press
        char key = cv::waitKey(1) & 0xFF;
        if (key == 'q' || key == 27) { // 'q' or ESC
            break;
        }
    }
    
    // Cleanup
    std::cout << "Shutting down..." << std::endl;
    cv::destroyAllWindows();
    
    // Display final statistics
    auto end_time = std::chrono::steady_clock::now();
    auto total_time = std::chrono::duration_cast<std::chrono::seconds>(
        end_time - start_time).count();
    
    std::cout << "\n=== Final Statistics ===" << std::endl;
    std::cout << "Total frames processed: " << frame_count << std::endl;
    std::cout << "Total defects detected: " << defect_count << std::endl;
    std::cout << "Total runtime: " << total_time << " seconds" << std::endl;
    std::cout << "Average FPS: " << frame_count / static_cast<double>(total_time) << std::endl;
    
    auto stats = g_classifier->getStatistics();
    if (!stats.empty()) {
        std::cout << "Class distribution:" << std::endl;
        for (const auto& pair : stats) {
            std::cout << "  " << pair.first << ": " << pair.second << std::endl;
        }
    }
    
    std::cout << "System shutdown complete." << std::endl;
    return 0;
}
