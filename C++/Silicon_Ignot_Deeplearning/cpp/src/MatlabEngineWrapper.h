#pragma once

#include <opencv2/opencv.hpp>
#include <matlab/engine.hpp>
#include <matlab/data.hpp>
#include <string>
#include <vector>
#include <memory>

/**
 * MatlabEngineWrapper class handles communication between C++ and MATLAB Engine API
 * Converts OpenCV Mat to MATLAB arrays and calls MATLAB functions for inference
 */
class MatlabEngineWrapper {
public:
    /**
     * Constructor
     * @param matlab_script_path Path to MATLAB inference scripts
     * @param model_file Name of the trained model file
     */
    MatlabEngineWrapper(const std::string& matlab_script_path, const std::string& model_file);
    
    /**
     * Destructor
     */
    ~MatlabEngineWrapper();
    
    /**
     * Initialize MATLAB Engine and load model
     * @return true if initialization successful, false otherwise
     */
    bool initialize();
    
    /**
     * Classify defect in the given image
     * @param image Input image (OpenCV Mat)
     * @param class_label Output class label
     * @param confidence Output confidence score
     * @return true if classification successful, false otherwise
     */
    bool classifyDefect(const cv::Mat& image, std::string& class_label, double& confidence);
    
    /**
     * Check if MATLAB Engine is ready
     * @return true if ready, false otherwise
     */
    bool isReady() const;
    
    /**
     * Get MATLAB Engine status
     * @return Status string
     */
    std::string getStatus() const;
    
    /**
     * Set MATLAB script path
     * @param path Path to MATLAB scripts
     */
    void setMatlabScriptPath(const std::string& path);
    
    /**
     * Set model file name
     * @param model_file Model file name
     */
    void setModelFile(const std::string& model_file);

private:
    std::unique_ptr<matlab::engine::MATLABEngine> engine_;
    std::string matlab_script_path_;
    std::string model_file_;
    bool initialized_;
    bool model_loaded_;
    
    /**
     * Convert OpenCV Mat to MATLAB array
     * @param cv_image OpenCV image
     * @return MATLAB array
     */
    matlab::data::Array convertCvMatToMatlabArray(const cv::Mat& cv_image);
    
    /**
     * Convert MATLAB array to C++ data types
     * @param matlab_result MATLAB result array
     * @param class_label Output class label
     * @param confidence Output confidence score
     */
    void convertMatlabResultToCpp(const matlab::data::Array& matlab_result,
                                 std::string& class_label, double& confidence);
    
    /**
     * Load MATLAB model
     * @return true if model loaded successfully, false otherwise
     */
    bool loadModel();
    
    /**
     * Add MATLAB script path to MATLAB path
     */
    void addMatlabPath();
    
    /**
     * Handle MATLAB exceptions
     * @param e MATLAB exception
     * @return Error message
     */
    std::string handleMatlabException(const matlab::engine::EngineException& e);
};
