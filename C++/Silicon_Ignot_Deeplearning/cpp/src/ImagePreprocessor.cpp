#include "ImagePreprocessor.h"
#include <iostream>
#include <sstream>

ImagePreprocessor::ImagePreprocessor(int roi_x, int roi_y, int roi_width, int roi_height,
                                   int target_size, double clahe_clip_limit)
    : roi_x_(roi_x), roi_y_(roi_y), roi_width_(roi_width), roi_height_(roi_height),
      target_size_(target_size), clahe_clip_limit_(clahe_clip_limit) {
    initializeCLAHE();
}

bool ImagePreprocessor::processImage(const cv::Mat& input, cv::Mat& output) {
    if (input.empty()) {
        std::cerr << "Error: Input image is empty" << std::endl;
        return false;
    }
    
    cv::Mat processed = input.clone();
    
    // Step 1: Extract ROI
    cv::Mat roi_image;
    if (!extractROI(processed, roi_image)) {
        std::cerr << "Error: Failed to extract ROI" << std::endl;
        return false;
    }
    
    // Step 2: Apply noise reduction
    cv::Mat denoised;
    applyNoiseReduction(roi_image, denoised);
    
    // Step 3: Apply contrast enhancement
    cv::Mat enhanced;
    applyContrastEnhancement(denoised, enhanced);
    
    // Step 4: Normalize image
    cv::Mat normalized;
    normalizeImage(enhanced, normalized);
    
    // Step 5: Resize to target size
    resizeImage(normalized, output);
    
    return true;
}

bool ImagePreprocessor::extractROI(const cv::Mat& input, cv::Mat& output) {
    if (!validateROI(input.cols, input.rows)) {
        std::cerr << "Error: Invalid ROI parameters" << std::endl;
        return false;
    }
    
    cv::Rect roi(roi_x_, roi_y_, roi_width_, roi_height_);
    output = input(roi).clone();
    
    return true;
}

void ImagePreprocessor::applyNoiseReduction(const cv::Mat& input, cv::Mat& output) {
    // Apply bilateral filter for noise reduction while preserving edges
    cv::bilateralFilter(input, output, 9, 75, 75);
    
    // Alternative: Gaussian blur for more aggressive noise reduction
    // cv::GaussianBlur(input, output, cv::Size(5, 5), 0);
}

void ImagePreprocessor::applyContrastEnhancement(const cv::Mat& input, cv::Mat& output) {
    if (input.channels() == 3) {
        // Convert to LAB color space for better contrast enhancement
        cv::Mat lab_image;
        cv::cvtColor(input, lab_image, cv::COLOR_BGR2LAB);
        
        // Split channels
        std::vector<cv::Mat> lab_channels;
        cv::split(lab_image, lab_channels);
        
        // Apply CLAHE to L channel
        clahe_->apply(lab_channels[0], lab_channels[0]);
        
        // Merge channels back
        cv::merge(lab_channels, lab_image);
        
        // Convert back to BGR
        cv::cvtColor(lab_image, output, cv::COLOR_LAB2BGR);
    } else {
        // For grayscale images, apply CLAHE directly
        clahe_->apply(input, output);
    }
}

void ImagePreprocessor::normalizeImage(const cv::Mat& input, cv::Mat& output) {
    // Convert to float and normalize to [0, 1]
    input.convertTo(output, CV_32F, 1.0 / 255.0);
    
    // Alternative: Normalize to [-1, 1] for some models
    // input.convertTo(output, CV_32F, 2.0 / 255.0, -1.0);
}

void ImagePreprocessor::resizeImage(const cv::Mat& input, cv::Mat& output) {
    cv::resize(input, output, cv::Size(target_size_, target_size_), 0, 0, cv::INTER_LINEAR);
}

void ImagePreprocessor::setROI(int x, int y, int width, int height) {
    roi_x_ = x;
    roi_y_ = y;
    roi_width_ = width;
    roi_height_ = height;
}

void ImagePreprocessor::setTargetSize(int size) {
    target_size_ = size;
}

void ImagePreprocessor::setCLAHEClipLimit(double clip_limit) {
    clahe_clip_limit_ = clip_limit;
    initializeCLAHE();
}

std::string ImagePreprocessor::getParameters() const {
    std::ostringstream oss;
    oss << "ROI: (" << roi_x_ << ", " << roi_y_ << ", " << roi_width_ << ", " << roi_height_ << "), "
        << "Target Size: " << target_size_ << ", "
        << "CLAHE Clip Limit: " << clahe_clip_limit_;
    return oss.str();
}

void ImagePreprocessor::initializeCLAHE() {
    clahe_ = cv::createCLAHE(clahe_clip_limit_, cv::Size(8, 8));
}

bool ImagePreprocessor::validateROI(int image_width, int image_height) const {
    return (roi_x_ >= 0 && roi_y_ >= 0 &&
            roi_x_ + roi_width_ <= image_width &&
            roi_y_ + roi_height_ <= image_height &&
            roi_width_ > 0 && roi_height_ > 0);
}
