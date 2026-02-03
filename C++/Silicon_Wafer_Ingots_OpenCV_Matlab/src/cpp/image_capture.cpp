#include "image_capture.h"
#include <iostream>
#include <filesystem>
#include <chrono>
#include <thread>

ImageCapture::ImageCapture(const std::string& output_dir, bool sync_capture)
    : output_directory(output_dir), synchronized_capture(sync_capture) {
    createOutputDirectories();
}

bool ImageCapture::addCamera(const CameraConfig& config) {
    auto camera = createCamera(config.type);
    if (!camera) {
        std::cerr << "Failed to create camera of type " << static_cast<int>(config.type) << std::endl;
        return false;
    }

    cameras.push_back(std::move(camera));
    camera_configs.push_back(config);
    
    std::cout << "Added camera " << cameras.size() - 1 << " (Type: " 
              << (config.type == CameraType::OPTICAL ? "Optical" : "Infrared") 
              << ")" << std::endl;
    
    return true;
}

bool ImageCapture::initializeAllCameras() {
    if (cameras.empty()) {
        std::cerr << "No cameras added to the system" << std::endl;
        return false;
    }

    bool all_initialized = true;
    for (size_t i = 0; i < cameras.size(); ++i) {
        std::cout << "Initializing camera " << i << "..." << std::endl;
        
        if (!cameras[i]->initialize(camera_configs[i])) {
            std::cerr << "Failed to initialize camera " << i << std::endl;
            all_initialized = false;
        } else {
            std::cout << "Camera " << i << " initialized successfully" << std::endl;
        }
    }

    return all_initialized;
}

std::vector<std::string> ImageCapture::captureAllImages(const std::string& sample_id) {
    std::vector<std::string> captured_files;
    
    if (cameras.empty()) {
        std::cerr << "No cameras available for capture" << std::endl;
        return captured_files;
    }

    std::string current_sample_id = sample_id.empty() ? generateSampleId() : sample_id;
    
    if (synchronized_capture) {
        std::vector<cv::Mat> images;
        std::vector<ImageMetadata> metadata;
        
        if (synchronizedCapture(images, metadata)) {
            for (size_t i = 0; i < images.size(); ++i) {
                std::string filename = CameraUtils::saveImageWithMetadata(
                    images[i], metadata[i], output_directory);
                if (!filename.empty()) {
                    captured_files.push_back(filename);
                }
            }
        }
    } else {
        // Sequential capture
        for (size_t i = 0; i < cameras.size(); ++i) {
            std::string filename = captureSingleImage(i, current_sample_id);
            if (!filename.empty()) {
                captured_files.push_back(filename);
            }
        }
    }

    std::cout << "Captured " << captured_files.size() << " images for sample " 
              << current_sample_id << std::endl;
    
    return captured_files;
}

std::string ImageCapture::captureSingleImage(int camera_index, const std::string& sample_id) {
    if (camera_index < 0 || camera_index >= static_cast<int>(cameras.size())) {
        std::cerr << "Invalid camera index: " << camera_index << std::endl;
        return "";
    }

    cv::Mat image;
    ImageMetadata metadata;
    
    if (!cameras[camera_index]->capture(image, metadata)) {
        std::cerr << "Failed to capture from camera " << camera_index << std::endl;
        return "";
    }

    std::string current_sample_id = sample_id.empty() ? generateSampleId() : sample_id;
    metadata.sample_id = current_sample_id;

    std::string filename = CameraUtils::saveImageWithMetadata(
        image, metadata, output_directory);
    
    if (!filename.empty()) {
        std::cout << "Captured image from camera " << camera_index 
                  << ": " << filename << std::endl;
    }

    return filename;
}

bool ImageCapture::startContinuousCapture() {
    bool all_started = true;
    for (size_t i = 0; i < cameras.size(); ++i) {
        if (!cameras[i]->startCapture()) {
            std::cerr << "Failed to start continuous capture for camera " << i << std::endl;
            all_started = false;
        }
    }
    
    if (all_started) {
        std::cout << "Continuous capture started for all cameras" << std::endl;
    }
    
    return all_started;
}

void ImageCapture::stopContinuousCapture() {
    for (auto& camera : cameras) {
        camera->stopCapture();
    }
    std::cout << "Continuous capture stopped for all cameras" << std::endl;
}

size_t ImageCapture::getCameraCount() const {
    return cameras.size();
}

std::string ImageCapture::getCameraInfo(int camera_index) const {
    if (camera_index < 0 || camera_index >= static_cast<int>(cameras.size())) {
        return "Invalid camera index";
    }
    
    return cameras[camera_index]->getCameraInfo();
}

void ImageCapture::setOutputDirectory(const std::string& output_dir) {
    output_directory = output_dir;
    createOutputDirectories();
}

bool ImageCapture::loadCameraCalibration(int camera_index, const std::string& calibration_file) {
    if (camera_index < 0 || camera_index >= static_cast<int>(cameras.size())) {
        std::cerr << "Invalid camera index: " << camera_index << std::endl;
        return false;
    }

    return cameras[camera_index]->loadCalibration(calibration_file);
}

bool ImageCapture::testAllCameras() {
    if (cameras.empty()) {
        std::cerr << "No cameras to test" << std::endl;
        return false;
    }

    bool all_ready = true;
    for (size_t i = 0; i < cameras.size(); ++i) {
        if (!cameras[i]->isReady()) {
            std::cerr << "Camera " << i << " is not ready" << std::endl;
            all_ready = false;
        } else {
            std::cout << "Camera " << i << " is ready" << std::endl;
        }
    }

    return all_ready;
}

std::string ImageCapture::generateSampleId() {
    auto now = std::chrono::system_clock::now();
    auto time_t = std::chrono::system_clock::to_time_t(now);
    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(
        now.time_since_epoch()) % 1000;
    
    std::ostringstream oss;
    oss << "sample_" << time_t << "_" << ms.count();
    return oss.str();
}

void ImageCapture::createOutputDirectories() {
    std::filesystem::create_directories(output_directory);
    std::filesystem::create_directories(output_directory + "/optical");
    std::filesystem::create_directories(output_directory + "/infrared");
    std::filesystem::create_directories(output_directory + "/processed");
}

bool ImageCapture::synchronizedCapture(std::vector<cv::Mat>& images, 
                                      std::vector<ImageMetadata>& metadata) {
    images.clear();
    metadata.clear();
    
    images.resize(cameras.size());
    metadata.resize(cameras.size());
    
    // Capture from all cameras simultaneously
    std::vector<bool> capture_results(cameras.size());
    
    // Use threads for simultaneous capture (simplified approach)
    std::vector<std::thread> capture_threads;
    
    for (size_t i = 0; i < cameras.size(); ++i) {
        capture_threads.emplace_back([this, i, &images, &metadata, &capture_results]() {
            capture_results[i] = cameras[i]->capture(images[i], metadata[i]);
        });
    }
    
    // Wait for all captures to complete
    for (auto& thread : capture_threads) {
        thread.join();
    }
    
    // Check if all captures were successful
    bool all_successful = true;
    for (size_t i = 0; i < capture_results.size(); ++i) {
        if (!capture_results[i]) {
            std::cerr << "Synchronized capture failed for camera " << i << std::endl;
            all_successful = false;
        }
    }
    
    if (all_successful) {
        std::cout << "Synchronized capture completed successfully" << std::endl;
    }
    
    return all_successful;
}
