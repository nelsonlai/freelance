#ifndef CAMERA_INTERFACE_H
#define CAMERA_INTERFACE_H

#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <string>
#include <vector>
#include <memory>

/**
 * Camera types supported by the system
 */
enum class CameraType {
    OPTICAL,    // Standard optical microscopy camera
    INFRARED,   // Infrared imaging camera
    UNKNOWN
};

/**
 * Camera configuration parameters
 */
struct CameraConfig {
    int device_id = 0;                    // Camera device ID
    int width = 1920;                     // Image width
    int height = 1080;                    // Image height
    int fps = 30;                         // Frames per second
    double exposure_time = -1;            // Exposure time (auto if -1)
    double gain = -1;                     // Gain (auto if -1)
    CameraType type = CameraType::OPTICAL; // Camera type
    std::string calibration_file = "";    // Calibration file path
};

/**
 * Image metadata structure
 */
struct ImageMetadata {
    std::string timestamp;                // Capture timestamp
    CameraType camera_type;              // Type of camera used
    std::string sample_id;               // Sample identifier
    CameraConfig config;                  // Camera configuration used
    cv::Point2f calibration_offset;      // Calibration offset
    double scale_factor = 1.0;           // Scale factor for measurements
};

/**
 * Abstract camera interface for different camera types
 */
class CameraInterface {
public:
    virtual ~CameraInterface() = default;
    
    /**
     * Initialize the camera with given configuration
     * @param config Camera configuration parameters
     * @return true if initialization successful
     */
    virtual bool initialize(const CameraConfig& config) = 0;
    
    /**
     * Capture a single image
     * @param image Output image
     * @param metadata Output metadata
     * @return true if capture successful
     */
    virtual bool capture(cv::Mat& image, ImageMetadata& metadata) = 0;
    
    /**
     * Start continuous capture mode
     * @return true if started successfully
     */
    virtual bool startCapture() = 0;
    
    /**
     * Stop continuous capture mode
     */
    virtual void stopCapture() = 0;
    
    /**
     * Check if camera is connected and ready
     * @return true if camera is ready
     */
    virtual bool isReady() const = 0;
    
    /**
     * Get camera information
     * @return string with camera information
     */
    virtual std::string getCameraInfo() const = 0;
    
    /**
     * Load calibration data
     * @param calibration_file Path to calibration file
     * @return true if calibration loaded successfully
     */
    virtual bool loadCalibration(const std::string& calibration_file) = 0;
    
    /**
     * Apply calibration to image
     * @param image Input/output image
     * @param metadata Image metadata
     */
    virtual void applyCalibration(cv::Mat& image, const ImageMetadata& metadata) = 0;
};

/**
 * Factory function to create camera instances
 * @param type Camera type
 * @return unique_ptr to camera interface
 */
std::unique_ptr<CameraInterface> createCamera(CameraType type);

/**
 * Utility functions for camera management
 */
namespace CameraUtils {
    /**
     * List available cameras
     * @return vector of available camera device IDs
     */
    std::vector<int> listAvailableCameras();
    
    /**
     * Test camera connection
     * @param device_id Camera device ID
     * @return true if camera is accessible
     */
    bool testCameraConnection(int device_id);
    
    /**
     * Get current timestamp as string
     * @return timestamp string
     */
    std::string getCurrentTimestamp();
    
    /**
     * Save image with metadata
     * @param image Image to save
     * @param metadata Image metadata
     * @param output_dir Output directory
     * @return filename of saved image
     */
    std::string saveImageWithMetadata(const cv::Mat& image, 
                                    const ImageMetadata& metadata,
                                    const std::string& output_dir);
}

#endif // CAMERA_INTERFACE_H
