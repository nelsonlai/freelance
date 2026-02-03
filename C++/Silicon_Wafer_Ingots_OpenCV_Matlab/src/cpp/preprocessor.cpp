#include "preprocessor.h"
#include <iostream>
#include <filesystem>
#include <opencv2/features2d.hpp>
#include <opencv2/calib3d.hpp>

void Preprocessor::reduceNoise(const cv::Mat& input, cv::Mat& output, const std::string& method) {
    if (method == "gaussian") {
        cv::GaussianBlur(input, output, cv::Size(5, 5), 0);
    } else if (method == "bilateral") {
        cv::bilateralFilter(input, output, 9, 75, 75);
    } else if (method == "median") {
        cv::medianBlur(input, output, 5);
    } else {
        std::cerr << "Unknown noise reduction method: " << method << std::endl;
        output = input.clone();
    }
}

void Preprocessor::enhanceContrast(const cv::Mat& input, cv::Mat& output,
                                  double clip_limit, cv::Size tile_size) {
    // Create CLAHE object
    cv::Ptr<cv::CLAHE> clahe = cv::createCLAHE(clip_limit, tile_size);
    
    // Apply CLAHE
    clahe->apply(input, output);
}

bool Preprocessor::alignImages(const cv::Mat& reference, const cv::Mat& target, cv::Mat& aligned) {
    // Detect features in both images
    std::vector<cv::KeyPoint> keypoints1, keypoints2;
    cv::Mat descriptors1, descriptors2;
    
    detectFeatures(reference, keypoints1, descriptors1);
    detectFeatures(target, keypoints2, descriptors2);
    
    if (keypoints1.empty() || keypoints2.empty()) {
        std::cerr << "No features detected in images" << std::endl;
        return false;
    }
    
    // Match features
    std::vector<cv::DMatch> matches;
    matchFeatures(descriptors1, descriptors2, matches);
    
    if (matches.size() < 10) {
        std::cerr << "Insufficient feature matches: " << matches.size() << std::endl;
        return false;
    }
    
    // Estimate transformation
    cv::Mat transform;
    if (!estimateTransformation(keypoints1, keypoints2, matches, transform)) {
        std::cerr << "Failed to estimate transformation" << std::endl;
        return false;
    }
    
    // Apply transformation
    applyTransformation(target, transform, aligned);
    
    return true;
}

bool Preprocessor::registerMultiModalImages(const cv::Mat& optical_img, const cv::Mat& infrared_img,
                                           cv::Mat& registered_optical, cv::Mat& registered_infrared) {
    // For multi-modal registration, we typically use the optical image as reference
    // since it usually has better feature definition
    
    cv::Mat aligned_infrared;
    if (!alignImages(optical_img, infrared_img, aligned_infrared)) {
        std::cerr << "Failed to register infrared image to optical image" << std::endl;
        return false;
    }
    
    registered_optical = optical_img.clone();
    registered_infrared = aligned_infrared;
    
    std::cout << "Multi-modal image registration completed" << std::endl;
    return true;
}

void Preprocessor::processImage(const cv::Mat& input, cv::Mat& output, const ProcessingConfig& config) {
    cv::Mat temp = input.clone();
    
    // Step 1: Noise reduction
    if (config.enable_noise_reduction) {
        cv::Mat denoised;
        reduceNoise(temp, denoised, config.noise_method);
        temp = denoised;
        
        if (config.save_intermediate) {
            std::filesystem::create_directories(config.intermediate_dir);
            cv::imwrite(config.intermediate_dir + "/denoised.png", temp);
        }
    }
    
    // Step 2: Contrast enhancement
    if (config.enable_contrast_enhancement) {
        cv::Mat enhanced;
        enhanceContrast(temp, enhanced, config.clahe_clip_limit, config.clahe_tile_size);
        temp = enhanced;
        
        if (config.save_intermediate) {
            cv::imwrite(config.intermediate_dir + "/enhanced.png", temp);
        }
    }
    
    // Step 3: Alignment (if reference image provided)
    if (config.enable_alignment && !config.reference_image_path.empty()) {
        cv::Mat reference = cv::imread(config.reference_image_path, cv::IMREAD_GRAYSCALE);
        if (!reference.empty()) {
            cv::Mat aligned;
            if (alignImages(reference, temp, aligned)) {
                temp = aligned;
                
                if (config.save_intermediate) {
                    cv::imwrite(config.intermediate_dir + "/aligned.png", temp);
                }
            } else {
                std::cerr << "Alignment failed, using unaligned image" << std::endl;
            }
        } else {
            std::cerr << "Could not load reference image: " << config.reference_image_path << std::endl;
        }
    }
    
    output = temp;
}

void Preprocessor::processImages(const std::vector<cv::Mat>& input_images,
                               std::vector<cv::Mat>& output_images,
                               const ProcessingConfig& config) {
    output_images.clear();
    output_images.reserve(input_images.size());
    
    for (size_t i = 0; i < input_images.size(); ++i) {
        cv::Mat processed;
        processImage(input_images[i], processed, config);
        output_images.push_back(processed);
        
        std::cout << "Processed image " << i + 1 << "/" << input_images.size() << std::endl;
    }
}

std::vector<std::string> Preprocessor::saveProcessedImages(const std::vector<cv::Mat>& images,
                                                          const std::string& output_dir,
                                                          const std::string& sample_id) {
    std::vector<std::string> saved_files;
    
    // Create output directory
    std::filesystem::create_directories(output_dir);
    
    for (size_t i = 0; i < images.size(); ++i) {
        std::string filename = output_dir + "/processed_" + sample_id + "_" + 
                              std::to_string(i) + ".png";
        
        if (cv::imwrite(filename, images[i])) {
            saved_files.push_back(filename);
            std::cout << "Saved processed image: " << filename << std::endl;
        } else {
            std::cerr << "Failed to save image: " << filename << std::endl;
        }
    }
    
    return saved_files;
}

void Preprocessor::detectFeatures(const cv::Mat& image, 
                                 std::vector<cv::KeyPoint>& keypoints,
                                 cv::Mat& descriptors) {
    // Use ORB detector for feature detection
    cv::Ptr<cv::ORB> detector = cv::ORB::create(1000);
    detector->detectAndCompute(image, cv::noArray(), keypoints, descriptors);
}

void Preprocessor::matchFeatures(const cv::Mat& desc1, const cv::Mat& desc2,
                                std::vector<cv::DMatch>& matches) {
    // Use BFMatcher for feature matching
    cv::BFMatcher matcher(cv::NORM_HAMMING);
    std::vector<std::vector<cv::DMatch>> knn_matches;
    
    matcher.knnMatch(desc1, desc2, knn_matches, 2);
    
    // Apply Lowe's ratio test
    const float ratio_thresh = 0.7f;
    for (size_t i = 0; i < knn_matches.size(); i++) {
        if (knn_matches[i].size() == 2) {
            if (knn_matches[i][0].distance < ratio_thresh * knn_matches[i][1].distance) {
                matches.push_back(knn_matches[i][0]);
            }
        }
    }
}

bool Preprocessor::estimateTransformation(const std::vector<cv::KeyPoint>& keypoints1,
                                        const std::vector<cv::KeyPoint>& keypoints2,
                                        const std::vector<cv::DMatch>& matches,
                                        cv::Mat& transform) {
    if (matches.size() < 4) {
        return false;
    }
    
    // Extract matched points
    std::vector<cv::Point2f> points1, points2;
    for (const auto& match : matches) {
        points1.push_back(keypoints1[match.queryIdx].pt);
        points2.push_back(keypoints2[match.trainIdx].pt);
    }
    
    // Estimate homography using RANSAC
    std::vector<uchar> mask;
    transform = cv::findHomography(points2, points1, cv::RANSAC, 5.0, mask);
    
    // Check if enough inliers
    int inliers = cv::sum(mask)[0];
    return inliers >= 10;
}

void Preprocessor::applyTransformation(const cv::Mat& image, const cv::Mat& transform, cv::Mat& output) {
    cv::warpPerspective(image, output, transform, image.size());
}
