#include "ConfigManager.h"
#include <iostream>
#include <sstream>
#include <filesystem>

ConfigManager::ConfigManager(const std::string& config_file)
    : config_file_path_(config_file), loaded_(false) {
}

ConfigManager::~ConfigManager() {
}

bool ConfigManager::loadConfig() {
    try {
        // Check if config file exists
        if (!std::filesystem::exists(config_file_path_)) {
            std::cerr << "Configuration file not found: " << config_file_path_ << std::endl;
            return false;
        }
        
        // Load YAML file
        config_ = YAML::LoadFile(config_file_path_);
        
        // Validate configuration
        if (!validateConfig()) {
            std::cerr << "Configuration validation failed" << std::endl;
            return false;
        }
        
        loaded_ = true;
        std::cout << "Configuration loaded successfully from: " << config_file_path_ << std::endl;
        return true;
        
    } catch (const YAML::Exception& e) {
        std::cerr << "Error loading configuration file: " << e.what() << std::endl;
        return false;
    } catch (const std::exception& e) {
        std::cerr << "Unexpected error loading configuration: " << e.what() << std::endl;
        return false;
    }
}

bool ConfigManager::validateConfig() {
    bool valid = true;
    
    // Validate each section
    if (!validateCameraConfig()) {
        std::cerr << "Camera configuration validation failed" << std::endl;
        valid = false;
    }
    
    if (!validatePreprocessingConfig()) {
        std::cerr << "Preprocessing configuration validation failed" << std::endl;
        valid = false;
    }
    
    if (!validateInferenceConfig()) {
        std::cerr << "Inference configuration validation failed" << std::endl;
        valid = false;
    }
    
    if (!validateLoggingConfig()) {
        std::cerr << "Logging configuration validation failed" << std::endl;
        valid = false;
    }
    
    return valid;
}

std::map<std::string, int> ConfigManager::getCameraConfig() const {
    std::map<std::string, int> camera_config;
    
    if (config_["camera"]) {
        camera_config["device_id"] = config_["camera"]["device_id"].as<int>();
        camera_config["width"] = config_["camera"]["width"].as<int>();
        camera_config["height"] = config_["camera"]["height"].as<int>();
        camera_config["fps"] = config_["camera"]["fps"].as<int>();
    }
    
    return camera_config;
}

std::map<std::string, double> ConfigManager::getPreprocessingConfig() const {
    std::map<std::string, double> preprocessing_config;
    
    if (config_["preprocessing"]) {
        preprocessing_config["roi_x"] = config_["preprocessing"]["roi_x"].as<double>();
        preprocessing_config["roi_y"] = config_["preprocessing"]["roi_y"].as<double>();
        preprocessing_config["roi_width"] = config_["preprocessing"]["roi_width"].as<double>();
        preprocessing_config["roi_height"] = config_["preprocessing"]["roi_height"].as<double>();
        preprocessing_config["target_size"] = config_["preprocessing"]["target_size"].as<double>();
        preprocessing_config["clahe_clip_limit"] = config_["preprocessing"]["clahe_clip_limit"].as<double>();
    }
    
    return preprocessing_config;
}

std::map<std::string, std::string> ConfigManager::getInferenceConfig() const {
    std::map<std::string, std::string> inference_config;
    
    if (config_["inference"]) {
        inference_config["matlab_script_path"] = config_["inference"]["matlab_script_path"].as<std::string>();
        inference_config["model_file"] = config_["inference"]["model_file"].as<std::string>();
        inference_config["confidence_threshold"] = std::to_string(config_["inference"]["confidence_threshold"].as<double>());
        inference_config["process_every_n_frames"] = std::to_string(config_["inference"]["process_every_n_frames"].as<int>());
    }
    
    return inference_config;
}

std::map<std::string, std::string> ConfigManager::getLoggingConfig() const {
    std::map<std::string, std::string> logging_config;
    
    if (config_["logging"]) {
        logging_config["db_path"] = config_["logging"]["db_path"].as<std::string>();
        logging_config["save_images"] = config_["logging"]["save_images"].as<bool>() ? "true" : "false";
        logging_config["image_output_dir"] = config_["logging"]["image_output_dir"].as<std::string>();
    }
    
    return logging_config;
}

std::string ConfigManager::getParameter(const std::string& section, const std::string& key) const {
    if (!loaded_ || !config_[section] || !config_[section][key]) {
        return "";
    }
    
    try {
        return config_[section][key].as<std::string>();
    } catch (const YAML::Exception& e) {
        std::cerr << "Error getting parameter [" << section << "][" << key << "]: " << e.what() << std::endl;
        return "";
    }
}

int ConfigManager::getIntParameter(const std::string& section, const std::string& key, int default_value) const {
    if (!loaded_ || !config_[section] || !config_[section][key]) {
        return default_value;
    }
    
    try {
        return config_[section][key].as<int>();
    } catch (const YAML::Exception& e) {
        std::cerr << "Error getting int parameter [" << section << "][" << key << "]: " << e.what() << std::endl;
        return default_value;
    }
}

double ConfigManager::getDoubleParameter(const std::string& section, const std::string& key, double default_value) const {
    if (!loaded_ || !config_[section] || !config_[section][key]) {
        return default_value;
    }
    
    try {
        return config_[section][key].as<double>();
    } catch (const YAML::Exception& e) {
        std::cerr << "Error getting double parameter [" << section << "][" << key << "]: " << e.what() << std::endl;
        return default_value;
    }
}

bool ConfigManager::getBoolParameter(const std::string& section, const std::string& key, bool default_value) const {
    if (!loaded_ || !config_[section] || !config_[section][key]) {
        return default_value;
    }
    
    try {
        return config_[section][key].as<bool>();
    } catch (const YAML::Exception& e) {
        std::cerr << "Error getting bool parameter [" << section << "][" << key << "]: " << e.what() << std::endl;
        return default_value;
    }
}

bool ConfigManager::isLoaded() const {
    return loaded_;
}

std::string ConfigManager::getConfigFilePath() const {
    return config_file_path_;
}

void ConfigManager::printConfigSummary() const {
    if (!loaded_) {
        std::cout << "Configuration not loaded" << std::endl;
        return;
    }
    
    std::cout << "\n=== Configuration Summary ===" << std::endl;
    
    // Camera configuration
    if (config_["camera"]) {
        std::cout << "Camera:" << std::endl;
        std::cout << "  Device ID: " << config_["camera"]["device_id"].as<int>() << std::endl;
        std::cout << "  Resolution: " << config_["camera"]["width"].as<int>() 
                  << "x" << config_["camera"]["height"].as<int>() << std::endl;
        std::cout << "  FPS: " << config_["camera"]["fps"].as<int>() << std::endl;
    }
    
    // Preprocessing configuration
    if (config_["preprocessing"]) {
        std::cout << "Preprocessing:" << std::endl;
        std::cout << "  ROI: (" << config_["preprocessing"]["roi_x"].as<int>() 
                  << ", " << config_["preprocessing"]["roi_y"].as<int>() 
                  << ", " << config_["preprocessing"]["roi_width"].as<int>() 
                  << ", " << config_["preprocessing"]["roi_height"].as<int>() << ")" << std::endl;
        std::cout << "  Target Size: " << config_["preprocessing"]["target_size"].as<int>() << std::endl;
        std::cout << "  CLAHE Clip Limit: " << config_["preprocessing"]["clahe_clip_limit"].as<double>() << std::endl;
    }
    
    // Inference configuration
    if (config_["inference"]) {
        std::cout << "Inference:" << std::endl;
        std::cout << "  MATLAB Script Path: " << config_["inference"]["matlab_script_path"].as<std::string>() << std::endl;
        std::cout << "  Model File: " << config_["inference"]["model_file"].as<std::string>() << std::endl;
        std::cout << "  Confidence Threshold: " << config_["inference"]["confidence_threshold"].as<double>() << std::endl;
        std::cout << "  Process Every N Frames: " << config_["inference"]["process_every_n_frames"].as<int>() << std::endl;
    }
    
    // Logging configuration
    if (config_["logging"]) {
        std::cout << "Logging:" << std::endl;
        std::cout << "  Database Path: " << config_["logging"]["db_path"].as<std::string>() << std::endl;
        std::cout << "  Save Images: " << (config_["logging"]["save_images"].as<bool>() ? "Yes" : "No") << std::endl;
        std::cout << "  Image Output Dir: " << config_["logging"]["image_output_dir"].as<std::string>() << std::endl;
    }
    
    std::cout << "===============================" << std::endl;
}

bool ConfigManager::validateCameraConfig() const {
    if (!config_["camera"]) {
        std::cerr << "Camera section not found in configuration" << std::endl;
        return false;
    }
    
    // Check required parameters
    std::vector<std::string> required_params = {"device_id", "width", "height", "fps"};
    for (const auto& param : required_params) {
        if (!config_["camera"][param]) {
            std::cerr << "Required camera parameter missing: " << param << std::endl;
            return false;
        }
    }
    
    // Validate parameter ranges
    int device_id = config_["camera"]["device_id"].as<int>();
    int width = config_["camera"]["width"].as<int>();
    int height = config_["camera"]["height"].as<int>();
    int fps = config_["camera"]["fps"].as<int>();
    
    if (device_id < 0) {
        std::cerr << "Invalid camera device ID: " << device_id << std::endl;
        return false;
    }
    
    if (width <= 0 || height <= 0) {
        std::cerr << "Invalid camera resolution: " << width << "x" << height << std::endl;
        return false;
    }
    
    if (fps <= 0) {
        std::cerr << "Invalid camera FPS: " << fps << std::endl;
        return false;
    }
    
    return true;
}

bool ConfigManager::validatePreprocessingConfig() const {
    if (!config_["preprocessing"]) {
        std::cerr << "Preprocessing section not found in configuration" << std::endl;
        return false;
    }
    
    // Check required parameters
    std::vector<std::string> required_params = {"roi_x", "roi_y", "roi_width", "roi_height", "target_size", "clahe_clip_limit"};
    for (const auto& param : required_params) {
        if (!config_["preprocessing"][param]) {
            std::cerr << "Required preprocessing parameter missing: " << param << std::endl;
            return false;
        }
    }
    
    // Validate parameter ranges
    int roi_x = config_["preprocessing"]["roi_x"].as<int>();
    int roi_y = config_["preprocessing"]["roi_y"].as<int>();
    int roi_width = config_["preprocessing"]["roi_width"].as<int>();
    int roi_height = config_["preprocessing"]["roi_height"].as<int>();
    int target_size = config_["preprocessing"]["target_size"].as<int>();
    double clahe_clip_limit = config_["preprocessing"]["clahe_clip_limit"].as<double>();
    
    if (roi_x < 0 || roi_y < 0 || roi_width <= 0 || roi_height <= 0) {
        std::cerr << "Invalid ROI parameters" << std::endl;
        return false;
    }
    
    if (target_size <= 0) {
        std::cerr << "Invalid target size: " << target_size << std::endl;
        return false;
    }
    
    if (clahe_clip_limit <= 0) {
        std::cerr << "Invalid CLAHE clip limit: " << clahe_clip_limit << std::endl;
        return false;
    }
    
    return true;
}

bool ConfigManager::validateInferenceConfig() const {
    if (!config_["inference"]) {
        std::cerr << "Inference section not found in configuration" << std::endl;
        return false;
    }
    
    // Check required parameters
    std::vector<std::string> required_params = {"matlab_script_path", "model_file", "confidence_threshold", "process_every_n_frames"};
    for (const auto& param : required_params) {
        if (!config_["inference"][param]) {
            std::cerr << "Required inference parameter missing: " << param << std::endl;
            return false;
        }
    }
    
    // Validate parameter ranges
    double confidence_threshold = config_["inference"]["confidence_threshold"].as<double>();
    int process_every_n_frames = config_["inference"]["process_every_n_frames"].as<int>();
    
    if (confidence_threshold < 0.0 || confidence_threshold > 1.0) {
        std::cerr << "Invalid confidence threshold: " << confidence_threshold << std::endl;
        return false;
    }
    
    if (process_every_n_frames <= 0) {
        std::cerr << "Invalid process every N frames: " << process_every_n_frames << std::endl;
        return false;
    }
    
    return true;
}

bool ConfigManager::validateLoggingConfig() const {
    if (!config_["logging"]) {
        std::cerr << "Logging section not found in configuration" << std::endl;
        return false;
    }
    
    // Check required parameters
    std::vector<std::string> required_params = {"db_path", "save_images", "image_output_dir"};
    for (const auto& param : required_params) {
        if (!config_["logging"][param]) {
            std::cerr << "Required logging parameter missing: " << param << std::endl;
            return false;
        }
    }
    
    return true;
}

bool ConfigManager::parameterExists(const std::string& section, const std::string& key) const {
    return loaded_ && config_[section] && config_[section][key];
}
