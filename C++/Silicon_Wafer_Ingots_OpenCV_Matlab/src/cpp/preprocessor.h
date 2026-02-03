#ifndef PREPROCESSOR_H
#define PREPROCESSOR_H

#include <opencv2/opencv.hpp>
#include <string>
#include <vector>

/**
 * Image preprocessing module for silicon wafer defect detection
 * Handles noise reduction, alignment, and contrast enhancement
 */
class Preprocessor {
public:
    /**
     * Constructor
     */
    Preprocessor() = default;

    /**
     * Destructor
     */
    ~Preprocessor() = default;

    /**
     * Apply noise reduction to image
     * @param input Input image
     * @param output Output image
     * @param method Noise reduction method (gaussian, bilateral, median)
     */
    void reduceNoise(const cv::Mat& input, cv::Mat& output, 
                    const std::string& method = "bilateral");

    /**
     * Apply contrast enhancement using CLAHE
     * @param input Input image
     * @param output Output image
     * @param clip_limit CLAHE clip limit
     * @param tile_size CLAHE tile size
     */
    void enhanceContrast(const cv::Mat& input, cv::Mat& output,
                        double clip_limit = 2.0, cv::Size tile_size = cv::Size(8, 8));

    /**
     * Align two images using feature matching
     * @param reference Reference image
     * @param target Target image to align
     * @param aligned Output aligned image
     * @return true if alignment successful
     */
    bool alignImages(const cv::Mat& reference, const cv::Mat& target, cv::Mat& aligned);

    /**
     * Register multi-modal images (optical + infrared)
     * @param optical_img Optical image
     * @param infrared_img Infrared image
     * @param registered_optical Output registered optical image
     * @param registered_infrared Output registered infrared image
     * @return true if registration successful
     */
    bool registerMultiModalImages(const cv::Mat& optical_img, const cv::Mat& infrared_img,
                                 cv::Mat& registered_optical, cv::Mat& registered_infrared);

    /**
     * Apply preprocessing pipeline to single image
     * @param input Input image
     * @param output Output processed image
     * @param config Processing configuration
     */
    void processImage(const cv::Mat& input, cv::Mat& output, 
                     const ProcessingConfig& config = ProcessingConfig());

    /**
     * Apply preprocessing pipeline to multiple images
     * @param input_images Input images
     * @param output_images Output processed images
     * @param config Processing configuration
     */
    void processImages(const std::vector<cv::Mat>& input_images,
                      std::vector<cv::Mat>& output_images,
                      const ProcessingConfig& config = ProcessingConfig());

    /**
     * Save processed images with metadata
     * @param images Processed images
     * @param output_dir Output directory
     * @param sample_id Sample identifier
     * @return vector of saved filenames
     */
    std::vector<std::string> saveProcessedImages(const std::vector<cv::Mat>& images,
                                                const std::string& output_dir,
                                                const std::string& sample_id);

private:
    /**
     * Detect features in image for alignment
     * @param image Input image
     * @param keypoints Output keypoints
     * @param descriptors Output descriptors
     */
    void detectFeatures(const cv::Mat& image, 
                       std::vector<cv::KeyPoint>& keypoints,
                       cv::Mat& descriptors);

    /**
     * Match features between two images
     * @param desc1 Descriptors from first image
     * @param desc2 Descriptors from second image
     * @param matches Output matches
     */
    void matchFeatures(const cv::Mat& desc1, const cv::Mat& desc2,
                      std::vector<cv::DMatch>& matches);

    /**
     * Estimate transformation matrix from matches
     * @param keypoints1 Keypoints from first image
     * @param keypoints2 Keypoints from second image
     * @param matches Feature matches
     * @param transform Output transformation matrix
     * @return true if transformation estimated successfully
     */
    bool estimateTransformation(const std::vector<cv::KeyPoint>& keypoints1,
                               const std::vector<cv::KeyPoint>& keypoints2,
                               const std::vector<cv::DMatch>& matches,
                               cv::Mat& transform);

    /**
     * Apply transformation to image
     * @param image Input image
     * @param transform Transformation matrix
     * @param output Output transformed image
     */
    void applyTransformation(const cv::Mat& image, const cv::Mat& transform, cv::Mat& output);
};

/**
 * Processing configuration structure
 */
struct ProcessingConfig {
    bool enable_noise_reduction = true;
    std::string noise_method = "bilateral";
    bool enable_contrast_enhancement = true;
    double clahe_clip_limit = 2.0;
    cv::Size clahe_tile_size = cv::Size(8, 8);
    bool enable_alignment = false;
    std::string reference_image_path = "";
    bool save_intermediate = false;
    std::string intermediate_dir = "data/output/intermediate";
};

#endif // PREPROCESSOR_H
