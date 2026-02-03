#ifndef IMAGE_CAPTURE_H
#define IMAGE_CAPTURE_H

#include "camera_interface.h"
#include <vector>
#include <memory>

/**
 * Multi-modal image capture system for silicon wafer defect detection
 */
class ImageCapture {
private:
    std::vector<std::unique_ptr<CameraInterface>> cameras;
    std::vector<CameraConfig> camera_configs;
    std::string output_directory;
    std::string sample_id;
    bool synchronized_capture;

public:
    /**
     * Constructor
     * @param output_dir Directory to save captured images
     * @param sync_capture Whether to synchronize multi-camera capture
     */
    ImageCapture(const std::string& output_dir = "data/output", 
                bool sync_capture = true);

    /**
     * Destructor
     */
    ~ImageCapture() = default;

    /**
     * Add a camera to the capture system
     * @param config Camera configuration
     * @return true if camera added successfully
     */
    bool addCamera(const CameraConfig& config);

    /**
     * Initialize all cameras
     * @return true if all cameras initialized successfully
     */
    bool initializeAllCameras();

    /**
     * Capture images from all cameras
     * @param sample_id Sample identifier
     * @return vector of captured image filenames
     */
    std::vector<std::string> captureAllImages(const std::string& sample_id = "");

    /**
     * Capture single image from specific camera
     * @param camera_index Index of camera in the cameras vector
     * @param sample_id Sample identifier
     * @return filename of captured image
     */
    std::string captureSingleImage(int camera_index, const std::string& sample_id = "");

    /**
     * Start continuous capture mode for all cameras
     * @return true if started successfully
     */
    bool startContinuousCapture();

    /**
     * Stop continuous capture mode
     */
    void stopContinuousCapture();

    /**
     * Get number of cameras
     * @return number of cameras
     */
    size_t getCameraCount() const;

    /**
     * Get camera information
     * @param camera_index Index of camera
     * @return camera information string
     */
    std::string getCameraInfo(int camera_index) const;

    /**
     * Set output directory
     * @param output_dir New output directory
     */
    void setOutputDirectory(const std::string& output_dir);

    /**
     * Load calibration for specific camera
     * @param camera_index Index of camera
     * @param calibration_file Path to calibration file
     * @return true if calibration loaded successfully
     */
    bool loadCameraCalibration(int camera_index, const std::string& calibration_file);

    /**
     * Test all camera connections
     * @return true if all cameras are ready
     */
    bool testAllCameras();

private:
    /**
     * Generate unique sample ID if not provided
     * @return generated sample ID
     */
    std::string generateSampleId();

    /**
     * Create output directory structure
     */
    void createOutputDirectories();

    /**
     * Synchronize capture timing across cameras
     * @param images Output vector for captured images
     * @param metadata Output vector for metadata
     * @return true if synchronized capture successful
     */
    bool synchronizedCapture(std::vector<cv::Mat>& images, 
                           std::vector<ImageMetadata>& metadata);
};

#endif // IMAGE_CAPTURE_H
