#include "CameraCapture.h"
#include <iostream>
#include <sstream>

CameraCapture::CameraCapture(int device_id, int width, int height, int fps)
    : device_id_(device_id), width_(width), height_(height), fps_(fps),
      initialized_(false), calibration_available_(false) {
}

CameraCapture::~CameraCapture() {
    if (cap_.isOpened()) {
        cap_.release();
    }
}

bool CameraCapture::initialize() {
    // Open camera
    cap_.open(device_id_);
    
    if (!cap_.isOpened()) {
        std::cerr << "Error: Could not open camera with device ID " << device_id_ << std::endl;
        return false;
    }
    
    // Apply camera settings
    applyCameraSettings();
    
    // Verify settings were applied correctly
    int actual_width = static_cast<int>(cap_.get(cv::CAP_PROP_FRAME_WIDTH));
    int actual_height = static_cast<int>(cap_.get(cv::CAP_PROP_FRAME_HEIGHT));
    int actual_fps = static_cast<int>(cap_.get(cv::CAP_PROP_FPS));
    
    std::cout << "Camera initialized successfully:" << std::endl;
    std::cout << "  Device ID: " << device_id_ << std::endl;
    std::cout << "  Resolution: " << actual_width << "x" << actual_height << std::endl;
    std::cout << "  FPS: " << actual_fps << std::endl;
    
    initialized_ = true;
    return true;
}

bool CameraCapture::captureFrame(cv::Mat& frame) {
    if (!initialized_) {
        std::cerr << "Error: Camera not initialized" << std::endl;
        return false;
    }
    
    bool success = cap_.read(frame);
    
    if (!success) {
        std::cerr << "Error: Failed to capture frame" << std::endl;
        return false;
    }
    
    // Apply undistortion if calibration is available
    if (calibration_available_) {
        cv::Mat undistorted_frame;
        undistortFrame(frame, undistorted_frame);
        frame = undistorted_frame;
    }
    
    return true;
}

bool CameraCapture::isReady() const {
    return initialized_ && cap_.isOpened();
}

std::string CameraCapture::getCameraInfo() const {
    if (!initialized_) {
        return "Camera not initialized";
    }
    
    std::ostringstream oss;
    oss << "Device ID: " << device_id_ << ", "
        << "Resolution: " << width_ << "x" << height_ << ", "
        << "FPS: " << fps_;
    
    if (calibration_available_) {
        oss << ", Calibration: Available";
    }
    
    return oss.str();
}

void CameraCapture::setCalibration(const cv::Mat& camera_matrix, const cv::Mat& distortion_coeffs) {
    camera_matrix_ = camera_matrix.clone();
    distortion_coeffs_ = distortion_coeffs.clone();
    calibration_available_ = true;
    
    std::cout << "Camera calibration parameters set" << std::endl;
}

void CameraCapture::undistortFrame(const cv::Mat& src, cv::Mat& dst) {
    if (!calibration_available_) {
        src.copyTo(dst);
        return;
    }
    
    cv::undistort(src, dst, camera_matrix_, distortion_coeffs_);
}

void CameraCapture::applyCameraSettings() {
    // Set resolution
    cap_.set(cv::CAP_PROP_FRAME_WIDTH, width_);
    cap_.set(cv::CAP_PROP_FRAME_HEIGHT, height_);
    
    // Set FPS
    cap_.set(cv::CAP_PROP_FPS, fps_);
    
    // Set buffer size to reduce latency
    cap_.set(cv::CAP_PROP_BUFFERSIZE, 1);
    
    // Set auto exposure (optional)
    cap_.set(cv::CAP_PROP_AUTO_EXPOSURE, 0.25); // Manual exposure
    
    // Set brightness (optional)
    cap_.set(cv::CAP_PROP_BRIGHTNESS, 0.5);
    
    // Set contrast (optional)
    cap_.set(cv::CAP_PROP_CONTRAST, 0.5);
}
