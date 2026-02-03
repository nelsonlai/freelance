#pragma once

#include <opencv2/opencv.hpp>
#include <string>

/**
 * ImagePreprocessor class handles image preprocessing for neural network input
 * Includes ROI extraction, noise reduction, contrast enhancement, and normalization
 */
class ImagePreprocessor {
public:
    /**
     * Constructor
     * @param roi_x X coordinate of ROI top-left corner
     * @param roi_y Y coordinate of ROI top-left corner
     * @param roi_width Width of ROI
     * @param roi_height Height of ROI
     * @param target_size Target size for neural network input (e.g., 224 for ResNet)
     * @param clahe_clip_limit CLAHE clip limit for contrast enhancement
     */
    ImagePreprocessor(int roi_x = 200, int roi_y = 150, int roi_width = 1520, int roi_height = 780,
                     int target_size = 224, double clahe_clip_limit = 2.0);
    
    /**
     * Process image for neural network inference
     * @param input Input image
     * @param output Processed image ready for neural network
     * @return true if processing successful, false otherwise
     */
    bool processImage(const cv::Mat& input, cv::Mat& output);
    
    /**
     * Extract ROI from input image
     * @param input Input image
     * @param output ROI extracted image
     * @return true if ROI extraction successful, false otherwise
     */
    bool extractROI(const cv::Mat& input, cv::Mat& output);
    
    /**
     * Apply noise reduction
     * @param input Input image
     * @param output Denoised image
     */
    void applyNoiseReduction(const cv::Mat& input, cv::Mat& output);
    
    /**
     * Apply contrast enhancement using CLAHE
     * @param input Input image
     * @param output Enhanced image
     */
    void applyContrastEnhancement(const cv::Mat& input, cv::Mat& output);
    
    /**
     * Normalize image for neural network input
     * @param input Input image
     * @param output Normalized image
     */
    void normalizeImage(const cv::Mat& input, cv::Mat& output);
    
    /**
     * Resize image to target size
     * @param input Input image
     * @param output Resized image
     */
    void resizeImage(const cv::Mat& input, cv::Mat& output);
    
    /**
     * Set ROI parameters
     * @param x X coordinate of ROI top-left corner
     * @param y Y coordinate of ROI top-left corner
     * @param width Width of ROI
     * @param height Height of ROI
     */
    void setROI(int x, int y, int width, int height);
    
    /**
     * Set target size for neural network input
     * @param size Target size (width and height)
     */
    void setTargetSize(int size);
    
    /**
     * Set CLAHE clip limit
     * @param clip_limit Clip limit value
     */
    void setCLAHEClipLimit(double clip_limit);
    
    /**
     * Get current preprocessing parameters
     * @return String representation of parameters
     */
    std::string getParameters() const;

private:
    int roi_x_;
    int roi_y_;
    int roi_width_;
    int roi_height_;
    int target_size_;
    double clahe_clip_limit_;
    cv::Ptr<cv::CLAHE> clahe_;
    
    /**
     * Initialize CLAHE
     */
    void initializeCLAHE();
    
    /**
     * Validate ROI parameters
     * @param image_width Input image width
     * @param image_height Input image height
     * @return true if ROI is valid, false otherwise
     */
    bool validateROI(int image_width, int image_height) const;
};
