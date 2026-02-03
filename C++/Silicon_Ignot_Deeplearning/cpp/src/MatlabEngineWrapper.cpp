#include "MatlabEngineWrapper.h"
#include <iostream>
#include <sstream>
#include <filesystem>

MatlabEngineWrapper::MatlabEngineWrapper(const std::string& matlab_script_path, const std::string& model_file)
    : matlab_script_path_(matlab_script_path), model_file_(model_file),
      initialized_(false), model_loaded_(false) {
}

MatlabEngineWrapper::~MatlabEngineWrapper() {
    if (engine_) {
        try {
            engine_->quit();
        } catch (const matlab::engine::EngineException& e) {
            std::cerr << "Error shutting down MATLAB Engine: " << e.what() << std::endl;
        }
    }
}

bool MatlabEngineWrapper::initialize() {
    try {
        // Start MATLAB Engine
        engine_ = matlab::engine::startMATLAB();
        
        if (!engine_) {
            std::cerr << "Error: Failed to start MATLAB Engine" << std::endl;
            return false;
        }
        
        // Add MATLAB script path
        addMatlabPath();
        
        // Load model
        if (!loadModel()) {
            std::cerr << "Error: Failed to load MATLAB model" << std::endl;
            return false;
        }
        
        initialized_ = true;
        std::cout << "MATLAB Engine initialized successfully" << std::endl;
        std::cout << "Model file: " << model_file_ << std::endl;
        
        return true;
        
    } catch (const matlab::engine::EngineException& e) {
        std::cerr << "MATLAB Engine Exception: " << handleMatlabException(e) << std::endl;
        return false;
    } catch (const std::exception& e) {
        std::cerr << "Error initializing MATLAB Engine: " << e.what() << std::endl;
        return false;
    }
}

bool MatlabEngineWrapper::classifyDefect(const cv::Mat& image, std::string& class_label, double& confidence) {
    if (!initialized_ || !model_loaded_) {
        std::cerr << "Error: MATLAB Engine not initialized or model not loaded" << std::endl;
        return false;
    }
    
    try {
        // Convert OpenCV Mat to MATLAB array
        matlab::data::Array matlab_image = convertCvMatToMatlabArray(image);
        
        // Call MATLAB classification function
        std::vector<matlab::data::Array> args = {matlab_image};
        std::vector<matlab::data::Array> result = engine_->feval(u"classify_defect", args);
        
        if (result.empty()) {
            std::cerr << "Error: MATLAB function returned empty result" << std::endl;
            return false;
        }
        
        // Convert result to C++ data types
        convertMatlabResultToCpp(result[0], class_label, confidence);
        
        return true;
        
    } catch (const matlab::engine::EngineException& e) {
        std::cerr << "MATLAB Engine Exception during classification: " << handleMatlabException(e) << std::endl;
        return false;
    } catch (const std::exception& e) {
        std::cerr << "Error during classification: " << e.what() << std::endl;
        return false;
    }
}

bool MatlabEngineWrapper::isReady() const {
    return initialized_ && model_loaded_;
}

std::string MatlabEngineWrapper::getStatus() const {
    std::ostringstream oss;
    oss << "MATLAB Engine: " << (initialized_ ? "Ready" : "Not Ready") << ", "
        << "Model: " << (model_loaded_ ? "Loaded" : "Not Loaded") << ", "
        << "Script Path: " << matlab_script_path_ << ", "
        << "Model File: " << model_file_;
    return oss.str();
}

void MatlabEngineWrapper::setMatlabScriptPath(const std::string& path) {
    matlab_script_path_ = path;
    if (initialized_) {
        addMatlabPath();
    }
}

void MatlabEngineWrapper::setModelFile(const std::string& model_file) {
    model_file_ = model_file;
    if (initialized_) {
        loadModel();
    }
}

matlab::data::Array MatlabEngineWrapper::convertCvMatToMatlabArray(const cv::Mat& cv_image) {
    // Get image dimensions
    int height = cv_image.rows;
    int width = cv_image.cols;
    int channels = cv_image.channels();
    
    // Create MATLAB array factory
    matlab::data::ArrayFactory factory;
    
    // Convert based on number of channels
    if (channels == 1) {
        // Grayscale image
        matlab::data::TypedArray<double> matlab_array = factory.createArray<double>({height, width});
        
        for (int i = 0; i < height; ++i) {
            for (int j = 0; j < width; ++j) {
                matlab_array[i][j] = static_cast<double>(cv_image.at<uchar>(i, j)) / 255.0;
            }
        }
        
        return matlab_array;
    } else if (channels == 3) {
        // Color image (BGR to RGB)
        matlab::data::TypedArray<double> matlab_array = factory.createArray<double>({height, width, channels});
        
        for (int i = 0; i < height; ++i) {
            for (int j = 0; j < width; ++j) {
                cv::Vec3b pixel = cv_image.at<cv::Vec3b>(i, j);
                matlab_array[i][j][0] = static_cast<double>(pixel[2]) / 255.0; // R
                matlab_array[i][j][1] = static_cast<double>(pixel[1]) / 255.0; // G
                matlab_array[i][j][2] = static_cast<double>(pixel[0]) / 255.0; // B
            }
        }
        
        return matlab_array;
    } else {
        throw std::runtime_error("Unsupported number of channels: " + std::to_string(channels));
    }
}

void MatlabEngineWrapper::convertMatlabResultToCpp(const matlab::data::Array& matlab_result,
                                                  std::string& class_label, double& confidence) {
    // Assuming MATLAB function returns a struct with 'class' and 'confidence' fields
    if (matlab_result.getType() == matlab::data::ArrayType::STRUCT) {
        matlab::data::StructArray struct_array = matlab_result;
        
        // Get class label
        if (struct_array.hasField(u"class")) {
            matlab::data::CharArray class_field = struct_array[0][u"class"];
            class_label = class_field.toAscii();
        }
        
        // Get confidence score
        if (struct_array.hasField(u"confidence")) {
            matlab::data::TypedArray<double> conf_field = struct_array[0][u"confidence"];
            confidence = conf_field[0];
        }
    } else {
        // Fallback: assume result is a cell array with [class, confidence]
        matlab::data::CellArray cell_array = matlab_result;
        
        if (cell_array.getNumberOfElements() >= 2) {
            // Get class label
            matlab::data::CharArray class_cell = cell_array[0];
            class_label = class_cell.toAscii();
            
            // Get confidence score
            matlab::data::TypedArray<double> conf_cell = cell_array[1];
            confidence = conf_cell[0];
        }
    }
}

bool MatlabEngineWrapper::loadModel() {
    try {
        // Call MATLAB function to load model
        std::vector<matlab::data::Array> args = {
            matlab::data::ArrayFactory().createCharArray(model_file_)
        };
        
        engine_->feval(u"load_model", args);
        model_loaded_ = true;
        
        return true;
        
    } catch (const matlab::engine::EngineException& e) {
        std::cerr << "Error loading model: " << handleMatlabException(e) << std::endl;
        model_loaded_ = false;
        return false;
    }
}

void MatlabEngineWrapper::addMatlabPath() {
    try {
        // Add script path to MATLAB path
        std::vector<matlab::data::Array> args = {
            matlab::data::ArrayFactory().createCharArray(matlab_script_path_)
        };
        
        engine_->feval(u"addpath", args);
        
    } catch (const matlab::engine::EngineException& e) {
        std::cerr << "Error adding MATLAB path: " << handleMatlabException(e) << std::endl;
    }
}

std::string MatlabEngineWrapper::handleMatlabException(const matlab::engine::EngineException& e) {
    std::ostringstream oss;
    oss << "MATLAB Engine Error: " << e.what();
    return oss.str();
}
