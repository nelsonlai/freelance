#pragma once

#include <opencv2/opencv.hpp>
#include <string>
#include <memory>

/**
 * CameraCapture class handles video stream acquisition from camera
 * Supports configuration of resolution, FPS, and camera calibration
 */
class CameraCapture {
public:
    /**
     * Constructor
     * @param device_id Camera device ID (usually 0 for default camera)
     * @param width Desired frame width
     * @param height Desired frame height
     * @param fps Desired frames per second
     */
    CameraCapture(int device_id = 0, int width = 1920, int height = 1080, int fps = 30);
    
    /**
     * Destructor
     */
    ~CameraCapture();
    
    /**
     * Initialize camera with specified parameters
     * @return true if initialization successful, false otherwise
     */
    bool initialize();
    
    /**
     * Capture a frame from the camera
     * @param frame Output frame
     * @return true if frame captured successfully, false otherwise
     */
    bool captureFrame(cv::Mat& frame);
    
    /**
     * Check if camera is opened and ready
     * @return true if camera is ready, false otherwise
     */
    bool isReady() const;
    
    /**
     * Get current camera properties
     * @return Camera properties as a string
     */
    std::string getCameraInfo() const;
    
    /**
     * Set camera calibration parameters (optional)
     * @param camera_matrix Camera intrinsic matrix
     * @param distortion_coeffs Distortion coefficients
     */
    void setCalibration(const cv::Mat& camera_matrix, const cv::Mat& distortion_coeffs);
    
    /**
     * Undistort captured frame using calibration parameters
     * @param src Input frame
     * @param dst Output undistorted frame
     */
    void undistortFrame(const cv::Mat& src, cv::Mat& dst);

private:
    cv::VideoCapture cap_;
    int device_id_;
    int width_;
    int height_;
    int fps_;
    bool initialized_;
    bool calibration_available_;
    cv::Mat camera_matrix_;
    cv::Mat distortion_coeffs_;
    
    /**
     * Apply camera settings
     */
    void applyCameraSettings();
};
