#include "DefectClassifier.h"
#include "ImagePreprocessor.h"
#include "MatlabEngineWrapper.h"
#include <iostream>
#include <sstream>
#include <iomanip>
#include <algorithm>

DefectClassifier::DefectClassifier(double confidence_threshold)
    : confidence_threshold_(confidence_threshold), initialized_(false) {
}

DefectClassifier::~DefectClassifier() {
}

bool DefectClassifier::initialize(std::shared_ptr<ImagePreprocessor> preprocessor,
                                 std::shared_ptr<MatlabEngineWrapper> matlab_wrapper) {
    if (!preprocessor) {
        std::cerr << "Error: ImagePreprocessor is null" << std::endl;
        return false;
    }
    
    if (!matlab_wrapper) {
        std::cerr << "Error: MatlabEngineWrapper is null" << std::endl;
        return false;
    }
    
    if (!matlab_wrapper->isReady()) {
        std::cerr << "Error: MatlabEngineWrapper is not ready" << std::endl;
        return false;
    }
    
    preprocessor_ = preprocessor;
    matlab_wrapper_ = matlab_wrapper;
    initialized_ = true;
    
    std::cout << "DefectClassifier initialized successfully" << std::endl;
    std::cout << "Confidence threshold: " << confidence_threshold_ << std::endl;
    
    return true;
}

bool DefectClassifier::classifyDefect(const cv::Mat& input_image, DefectResult& defect_result) {
    if (!initialized_) {
        std::cerr << "Error: DefectClassifier not initialized" << std::endl;
        return false;
    }
    
    if (input_image.empty()) {
        std::cerr << "Error: Input image is empty" << std::endl;
        return false;
    }
    
    // Start timing
    auto start_time = std::chrono::high_resolution_clock::now();
    
    try {
        // Step 1: Preprocess image
        cv::Mat processed_image;
        if (!preprocessor_->processImage(input_image, processed_image)) {
            std::cerr << "Error: Image preprocessing failed" << std::endl;
            return false;
        }
        
        // Step 2: Run MATLAB inference
        std::string class_label;
        double confidence;
        if (!matlab_wrapper_->classifyDefect(processed_image, class_label, confidence)) {
            std::cerr << "Error: MATLAB classification failed" << std::endl;
            return false;
        }
        
        // Step 3: Post-process results
        auto end_time = std::chrono::high_resolution_clock::now();
        auto processing_time = std::chrono::duration<double, std::milli>(end_time - start_time).count();
        
        // Determine if defect is detected
        bool is_defect = meetsConfidenceThreshold(confidence);
        
        // Fill result structure
        defect_result.class_label = class_label;
        defect_result.confidence = confidence;
        defect_result.is_defect = is_defect;
        defect_result.processing_time_ms = processing_time;
        
        // Generate timestamp
        auto now = std::chrono::system_clock::now();
        auto time_t = std::chrono::system_clock::to_time_t(now);
        std::ostringstream oss;
        oss << std::put_time(std::localtime(&time_t), "%Y-%m-%d %H:%M:%S");
        defect_result.timestamp = oss.str();
        
        // Generate report
        defect_result.report = generateDefectReport(class_label, confidence, processing_time);
        
        // Update statistics
        updateStatistics(class_label, processing_time);
        
        return true;
        
    } catch (const std::exception& e) {
        std::cerr << "Error during classification: " << e.what() << std::endl;
        return false;
    }
}

bool DefectClassifier::isReady() const {
    return initialized_ && preprocessor_ && matlab_wrapper_ && matlab_wrapper_->isReady();
}

void DefectClassifier::setConfidenceThreshold(double threshold) {
    confidence_threshold_ = std::max(0.0, std::min(1.0, threshold));
    std::cout << "Confidence threshold set to: " << confidence_threshold_ << std::endl;
}

double DefectClassifier::getConfidenceThreshold() const {
    return confidence_threshold_;
}

std::map<std::string, int> DefectClassifier::getStatistics() const {
    return class_counts_;
}

void DefectClassifier::resetStatistics() {
    class_counts_.clear();
    processing_times_.clear();
    std::cout << "Statistics reset" << std::endl;
}

double DefectClassifier::getAverageProcessingTime() const {
    if (processing_times_.empty()) {
        return 0.0;
    }
    
    double sum = 0.0;
    for (double time : processing_times_) {
        sum += time;
    }
    
    return sum / processing_times_.size();
}

void DefectClassifier::updateStatistics(const std::string& class_label, double processing_time) {
    // Update class counts
    class_counts_[class_label]++;
    
    // Update processing times (keep only last MAX_PROCESSING_TIMES)
    processing_times_.push_back(processing_time);
    if (processing_times_.size() > MAX_PROCESSING_TIMES) {
        processing_times_.erase(processing_times_.begin());
    }
}

bool DefectClassifier::meetsConfidenceThreshold(double confidence) const {
    return confidence >= confidence_threshold_;
}

std::string DefectClassifier::generateDefectReport(const std::string& class_label,
                                                  double confidence, double processing_time) const {
    std::ostringstream oss;
    oss << "Defect Detection Report\n";
    oss << "======================\n";
    oss << "Class: " << class_label << "\n";
    oss << "Confidence: " << std::fixed << std::setprecision(3) << confidence << "\n";
    oss << "Processing Time: " << std::fixed << std::setprecision(2) << processing_time << " ms\n";
    oss << "Threshold: " << std::fixed << std::setprecision(3) << confidence_threshold_ << "\n";
    oss << "Status: " << (meetsConfidenceThreshold(confidence) ? "DEFECT DETECTED" : "NORMAL") << "\n";
    
    return oss.str();
}
