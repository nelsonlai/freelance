#pragma once

#include <opencv2/opencv.hpp>
#include <string>
#include <vector>
#include <memory>
#include <chrono>
#include <map>

// Forward declarations
class ImagePreprocessor;
class MatlabEngineWrapper;

/**
 * DefectClassifier class coordinates the entire defect detection pipeline
 * Handles preprocessing, inference, post-processing, and result management
 */
class DefectClassifier {
public:
    /**
     * Constructor
     * @param confidence_threshold Minimum confidence threshold for defect detection
     */
    DefectClassifier(double confidence_threshold = 0.75);
    
    /**
     * Destructor
     */
    ~DefectClassifier();
    
    /**
     * Initialize the classifier with preprocessing and MATLAB components
     * @param preprocessor Shared pointer to ImagePreprocessor
     * @param matlab_wrapper Shared pointer to MatlabEngineWrapper
     * @return true if initialization successful, false otherwise
     */
    bool initialize(std::shared_ptr<ImagePreprocessor> preprocessor,
                   std::shared_ptr<MatlabEngineWrapper> matlab_wrapper);
    
    /**
     * Classify defect in the given image
     * @param input_image Input image from camera
     * @param defect_result Output defect classification result
     * @return true if classification successful, false otherwise
     */
    bool classifyDefect(const cv::Mat& input_image, DefectResult& defect_result);
    
    /**
     * Check if classifier is ready for inference
     * @return true if ready, false otherwise
     */
    bool isReady() const;
    
    /**
     * Set confidence threshold
     * @param threshold New confidence threshold
     */
    void setConfidenceThreshold(double threshold);
    
    /**
     * Get current confidence threshold
     * @return Current confidence threshold
     */
    double getConfidenceThreshold() const;
    
    /**
     * Get classification statistics
     * @return Map of class names to detection counts
     */
    std::map<std::string, int> getStatistics() const;
    
    /**
     * Reset statistics
     */
    void resetStatistics();
    
    /**
     * Get processing time statistics
     * @return Average processing time in milliseconds
     */
    double getAverageProcessingTime() const;

private:
    std::shared_ptr<ImagePreprocessor> preprocessor_;
    std::shared_ptr<MatlabEngineWrapper> matlab_wrapper_;
    double confidence_threshold_;
    bool initialized_;
    
    // Statistics tracking
    std::map<std::string, int> class_counts_;
    std::vector<double> processing_times_;
    static const size_t MAX_PROCESSING_TIMES = 100; // Keep last 100 measurements
    
    /**
     * Update statistics with new classification result
     * @param class_label Detected class label
     * @param processing_time Processing time in milliseconds
     */
    void updateStatistics(const std::string& class_label, double processing_time);
    
    /**
     * Determine if result meets confidence threshold
     * @param confidence Confidence score
     * @return true if above threshold, false otherwise
     */
    bool meetsConfidenceThreshold(double confidence) const;
    
    /**
     * Generate defect report
     * @param class_label Detected class label
     * @param confidence Confidence score
     * @param processing_time Processing time
     * @return Formatted defect report string
     */
    std::string generateDefectReport(const std::string& class_label, 
                                   double confidence, double processing_time) const;
};

/**
 * DefectResult struct contains classification results
 */
struct DefectResult {
    std::string class_label;           // Detected defect class
    double confidence;                 // Confidence score [0, 1]
    bool is_defect;                    // True if defect detected (above threshold)
    double processing_time_ms;          // Processing time in milliseconds
    std::string timestamp;             // Detection timestamp
    std::string report;                // Formatted report string
    
    DefectResult() : confidence(0.0), is_defect(false), processing_time_ms(0.0) {}
};
