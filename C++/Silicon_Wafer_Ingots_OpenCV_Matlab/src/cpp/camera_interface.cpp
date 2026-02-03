#include "camera_interface.h"
#include <iostream>
#include <sstream>
#include <iomanip>
#include <ctime>
#include <filesystem>

/**
 * Standard optical camera implementation using OpenCV VideoCapture
 */
class OpticalCamera : public CameraInterface {
private:
    cv::VideoCapture cap;
    CameraConfig config;
    bool is_initialized = false;
    cv::Mat camera_matrix;
    cv::Mat distortion_coeffs;
    bool calibration_loaded = false;

public:
    ~OpticalCamera() override {
        if (cap.isOpened()) {
            cap.release();
        }
    }

    bool initialize(const CameraConfig& cfg) override {
        config = cfg;
        
        // Try to open camera
        cap.open(config.device_id);
        if (!cap.isOpened()) {
            std::cerr << "Error: Could not open camera " << config.device_id << std::endl;
            return false;
        }

        // Set camera properties
        cap.set(cv::CAP_PROP_FRAME_WIDTH, config.width);
        cap.set(cv::CAP_PROP_FRAME_HEIGHT, config.height);
        cap.set(cv::CAP_PROP_FPS, config.fps);
        
        if (config.exposure_time > 0) {
            cap.set(cv::CAP_PROP_EXPOSURE, config.exposure_time);
        }
        if (config.gain > 0) {
            cap.set(cv::CAP_PROP_GAIN, config.gain);
        }

        // Verify settings
        double actual_width = cap.get(cv::CAP_PROP_FRAME_WIDTH);
        double actual_height = cap.get(cv::CAP_PROP_FRAME_HEIGHT);
        std::cout << "Camera initialized: " << actual_width << "x" << actual_height << std::endl;

        is_initialized = true;
        return true;
    }

    bool capture(cv::Mat& image, ImageMetadata& metadata) override {
        if (!is_initialized) {
            std::cerr << "Camera not initialized" << std::endl;
            return false;
        }

        cv::Mat frame;
        if (!cap.read(frame)) {
            std::cerr << "Failed to capture frame" << std::endl;
            return false;
        }

        // Convert to appropriate format
        if (frame.channels() == 3) {
            cv::cvtColor(frame, image, cv::COLOR_BGR2GRAY);
        } else {
            image = frame.clone();
        }

        // Fill metadata
        metadata.timestamp = CameraUtils::getCurrentTimestamp();
        metadata.camera_type = CameraType::OPTICAL;
        metadata.config = config;
        metadata.sample_id = "sample_" + metadata.timestamp;

        // Apply calibration if available
        if (calibration_loaded) {
            applyCalibration(image, metadata);
        }

        return true;
    }

    bool startCapture() override {
        return is_initialized;
    }

    void stopCapture() override {
        // For continuous capture, this would stop the capture loop
        // Implementation depends on specific requirements
    }

    bool isReady() const override {
        return is_initialized && cap.isOpened();
    }

    std::string getCameraInfo() const override {
        std::ostringstream oss;
        oss << "Optical Camera (Device " << config.device_id << ")\n";
        oss << "Resolution: " << config.width << "x" << config.height << "\n";
        oss << "FPS: " << config.fps << "\n";
        oss << "Status: " << (isReady() ? "Ready" : "Not Ready");
        return oss.str();
    }

    bool loadCalibration(const std::string& calibration_file) override {
        if (calibration_file.empty()) {
            return false;
        }

        cv::FileStorage fs(calibration_file, cv::FileStorage::READ);
        if (!fs.isOpened()) {
            std::cerr << "Could not open calibration file: " << calibration_file << std::endl;
            return false;
        }

        fs["camera_matrix"] >> camera_matrix;
        fs["distortion_coefficients"] >> distortion_coeffs;
        fs.release();

        calibration_loaded = true;
        std::cout << "Calibration loaded from: " << calibration_file << std::endl;
        return true;
    }

    void applyCalibration(cv::Mat& image, const ImageMetadata& metadata) override {
        if (!calibration_loaded) {
            return;
        }

        cv::Mat undistorted;
        cv::undistort(image, undistorted, camera_matrix, distortion_coeffs);
        image = undistorted;
    }
};

/**
 * Infrared camera implementation (placeholder for specialized IR cameras)
 */
class InfraredCamera : public CameraInterface {
private:
    cv::VideoCapture cap;
    CameraConfig config;
    bool is_initialized = false;

public:
    ~InfraredCamera() override {
        if (cap.isOpened()) {
            cap.release();
        }
    }

    bool initialize(const CameraConfig& cfg) override {
        config = cfg;
        
        // For IR cameras, we might need specialized drivers
        // This is a placeholder implementation
        cap.open(config.device_id);
        if (!cap.isOpened()) {
            std::cerr << "Error: Could not open IR camera " << config.device_id << std::endl;
            return false;
        }

        // Set IR-specific properties
        cap.set(cv::CAP_PROP_FRAME_WIDTH, config.width);
        cap.set(cv::CAP_PROP_FRAME_HEIGHT, config.height);
        cap.set(cv::CAP_PROP_FPS, config.fps);

        is_initialized = true;
        std::cout << "IR Camera initialized" << std::endl;
        return true;
    }

    bool capture(cv::Mat& image, ImageMetadata& metadata) override {
        if (!is_initialized) {
            return false;
        }

        cv::Mat frame;
        if (!cap.read(frame)) {
            return false;
        }

        // IR images are typically grayscale
        if (frame.channels() == 3) {
            cv::cvtColor(frame, image, cv::COLOR_BGR2GRAY);
        } else {
            image = frame.clone();
        }

        metadata.timestamp = CameraUtils::getCurrentTimestamp();
        metadata.camera_type = CameraType::INFRARED;
        metadata.config = config;
        metadata.sample_id = "ir_sample_" + metadata.timestamp;

        return true;
    }

    bool startCapture() override {
        return is_initialized;
    }

    void stopCapture() override {
        // Implementation for continuous capture
    }

    bool isReady() const override {
        return is_initialized && cap.isOpened();
    }

    std::string getCameraInfo() const override {
        std::ostringstream oss;
        oss << "Infrared Camera (Device " << config.device_id << ")\n";
        oss << "Resolution: " << config.width << "x" << config.height << "\n";
        oss << "Status: " << (isReady() ? "Ready" : "Not Ready");
        return oss.str();
    }

    bool loadCalibration(const std::string& calibration_file) override {
        // IR camera calibration implementation
        return true;
    }

    void applyCalibration(cv::Mat& image, const ImageMetadata& metadata) override {
        // IR-specific calibration
    }
};

// Factory function implementation
std::unique_ptr<CameraInterface> createCamera(CameraType type) {
    switch (type) {
        case CameraType::OPTICAL:
            return std::make_unique<OpticalCamera>();
        case CameraType::INFRARED:
            return std::make_unique<InfraredCamera>();
        default:
            std::cerr << "Unknown camera type" << std::endl;
            return nullptr;
    }
}

// Utility functions implementation
namespace CameraUtils {
    std::vector<int> listAvailableCameras() {
        std::vector<int> available_cameras;
        
        // Test cameras 0-9
        for (int i = 0; i < 10; ++i) {
            if (testCameraConnection(i)) {
                available_cameras.push_back(i);
            }
        }
        
        return available_cameras;
    }

    bool testCameraConnection(int device_id) {
        cv::VideoCapture test_cap(device_id);
        bool is_available = test_cap.isOpened();
        test_cap.release();
        return is_available;
    }

    std::string getCurrentTimestamp() {
        auto now = std::time(nullptr);
        auto tm = *std::localtime(&now);
        
        std::ostringstream oss;
        oss << std::put_time(&tm, "%Y%m%d_%H%M%S");
        return oss.str();
    }

    std::string saveImageWithMetadata(const cv::Mat& image, 
                                    const ImageMetadata& metadata,
                                    const std::string& output_dir) {
        // Create output directory if it doesn't exist
        std::filesystem::create_directories(output_dir);
        
        // Generate filename
        std::string camera_type_str = (metadata.camera_type == CameraType::OPTICAL) ? "optical" : "infrared";
        std::string filename = output_dir + "/" + camera_type_str + "_" + metadata.timestamp + ".png";
        
        // Save image
        if (!cv::imwrite(filename, image)) {
            std::cerr << "Failed to save image: " << filename << std::endl;
            return "";
        }
        
        // Save metadata as JSON (simplified)
        std::string metadata_filename = filename + ".meta";
        std::ofstream meta_file(metadata_filename);
        if (meta_file.is_open()) {
            meta_file << "{\n";
            meta_file << "  \"timestamp\": \"" << metadata.timestamp << "\",\n";
            meta_file << "  \"camera_type\": \"" << camera_type_str << "\",\n";
            meta_file << "  \"sample_id\": \"" << metadata.sample_id << "\",\n";
            meta_file << "  \"width\": " << metadata.config.width << ",\n";
            meta_file << "  \"height\": " << metadata.config.height << ",\n";
            meta_file << "  \"fps\": " << metadata.config.fps << "\n";
            meta_file << "}\n";
            meta_file.close();
        }
        
        return filename;
    }
}
