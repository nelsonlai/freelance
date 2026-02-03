// 25_advanced_image_blending.cpp
// Advanced Level - Advanced Image Blending and Composition
// This program demonstrates various advanced image blending techniques and seamless composition

#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/photo.hpp>
#include <vector>

class AdvancedImageBlender {
private:
    cv::Mat source1, source2, mask, result;
    std::vector<cv::Mat> blend_results;
    std::vector<std::string> blend_names;
    
public:
    AdvancedImageBlender() {
        blend_names = {
            "Alpha Blending",
            "Gaussian Pyramid Blending",
            "Laplacian Pyramid Blending",
            "Poisson Blending",
            "Seamless Cloning",
            "Multi-band Blending",
            "Gradient Domain Blending",
            "Texture Synthesis Blending"
        };
    }
    
    void loadImages() {
        // Try to load images, create samples if not available
        source1 = cv::imread("image.jpg");
        source2 = cv::imread("image.jpg"); // In real scenario, this would be a different image
        
        if (source1.empty()) {
            std::cout << "Creating sample images for blending demonstration..." << std::endl;
            createSampleImages();
        } else {
            // Create a second image by applying transformations
            createSecondImage();
        }
        
        // Ensure both images are the same size
        cv::resize(source1, source1, cv::Size(400, 300));
        cv::resize(source2, source2, cv::Size(400, 300));
        
        std::cout << "Images loaded successfully!" << std::endl;
    }
    
    void createSampleImages() {
        // Create first sample image (landscape)
        source1 = cv::Mat::zeros(300, 400, CV_8UC3);
        
        // Draw a simple landscape
        cv::rectangle(source1, cv::Point(0, 200), cv::Point(400, 300), cv::Scalar(34, 139, 34), -1); // Ground
        cv::rectangle(source1, cv::Point(0, 0), cv::Point(400, 200), cv::Scalar(135, 206, 235), -1); // Sky
        cv::rectangle(source1, cv::Point(100, 150), cv::Point(200, 250), cv::Scalar(139, 69, 19), -1); // Tree trunk
        cv::circle(source1, cv::Point(150, 120), 40, cv::Scalar(0, 100, 0), -1); // Tree crown
        cv::circle(source1, cv::Point(300, 100), 20, cv::Scalar(255, 255, 0), -1); // Sun
        
        // Create second sample image (objects)
        source2 = cv::Mat::zeros(300, 400, CV_8UC3);
        cv::rectangle(source2, cv::Point(0, 0), cv::Point(400, 300), cv::Scalar(50, 50, 50), -1); // Background
        cv::rectangle(source2, cv::Point(50, 50), cv::Point(150, 150), cv::Scalar(255, 0, 0), -1); // Blue rectangle
        cv::circle(source2, cv::Point(250, 100), 30, cv::Scalar(0, 255, 0), -1); // Green circle
        cv::rectangle(source2, cv::Point(300, 200), cv::Point(380, 280), cv::Scalar(0, 0, 255), -1); // Red rectangle
        
        // Add some text
        cv::putText(source1, "Landscape", cv::Point(10, 30), cv::FONT_HERSHEY_SIMPLEX, 1, cv::Scalar(255, 255, 255), 2);
        cv::putText(source2, "Objects", cv::Point(10, 30), cv::FONT_HERSHEY_SIMPLEX, 1, cv::Scalar(255, 255, 255), 2);
    }
    
    void createSecondImage() {
        // Create a modified version of the first image
        source2 = source1.clone();
        
        // Apply some transformations
        cv::Mat transform = cv::getRotationMatrix2D(cv::Point2f(source1.cols/2, source1.rows/2), 45, 0.8);
        cv::warpAffine(source1, source2, transform, source1.size());
        
        // Change colors
        cv::Mat hsv;
        cv::cvtColor(source2, hsv, cv::COLOR_BGR2HSV);
        cv::Mat channels[3];
        cv::split(hsv, channels);
        channels[0] += 60; // Shift hue
        cv::merge(channels, 3, hsv);
        cv::cvtColor(hsv, source2, cv::COLOR_HSV2BGR);
        
        cv::putText(source1, "Original", cv::Point(10, 30), cv::FONT_HERSHEY_SIMPLEX, 0.8, cv::Scalar(255, 255, 255), 2);
        cv::putText(source2, "Modified", cv::Point(10, 30), cv::FONT_HERSHEY_SIMPLEX, 0.8, cv::Scalar(255, 255, 255), 2);
    }
    
    void createBlendMask() {
        // Create a mask for blending
        mask = cv::Mat::zeros(source1.size(), CV_8UC1);
        
        // Create a smooth transition mask
        int center_x = mask.cols / 2;
        int center_y = mask.rows / 2;
        
        for (int y = 0; y < mask.rows; y++) {
            for (int x = 0; x < mask.cols; x++) {
                // Create a gradient mask from left to right
                double alpha = (double)x / mask.cols;
                
                // Apply smooth transition
                alpha = 0.5 * (1 + sin(CV_PI * (alpha - 0.5)));
                
                mask.at<uchar>(y, x) = cv::saturate_cast<uchar>(255 * alpha);
            }
        }
        
        // Apply Gaussian blur for smoother transitions
        cv::GaussianBlur(mask, mask, cv::Size(21, 21), 5);
    }
    
    void performAllBlending() {
        std::cout << "=== Advanced Image Blending and Composition ===" << std::endl;
        
        // Clear previous results
        blend_results.clear();
        
        // Create blend mask
        createBlendMask();
        
        // 1. Alpha Blending
        cv::Mat alpha_blend;
        alphaBlending(source1, source2, mask, alpha_blend);
        blend_results.push_back(alpha_blend.clone());
        
        // 2. Gaussian Pyramid Blending
        cv::Mat gaussian_blend;
        gaussianPyramidBlending(source1, source2, gaussian_blend);
        blend_results.push_back(gaussian_blend.clone());
        
        // 3. Laplacian Pyramid Blending
        cv::Mat laplacian_blend;
        laplacianPyramidBlending(source1, source2, laplacian_blend);
        blend_results.push_back(laplacian_blend.clone());
        
        // 4. Poisson Blending
        cv::Mat poisson_blend;
        poissonBlending(source1, source2, poisson_blend);
        blend_results.push_back(poisson_blend.clone());
        
        // 5. Seamless Cloning
        cv::Mat seamless_clone;
        seamlessCloning(source1, source2, seamless_clone);
        blend_results.push_back(seamless_clone.clone());
        
        // 6. Multi-band Blending
        cv::Mat multiband_blend;
        multibandBlending(source1, source2, multiband_blend);
        blend_results.push_back(multiband_blend.clone());
        
        // 7. Gradient Domain Blending
        cv::Mat gradient_blend;
        gradientDomainBlending(source1, source2, gradient_blend);
        blend_results.push_back(gradient_blend.clone());
        
        // 8. Texture Synthesis Blending
        cv::Mat texture_blend;
        textureSynthesisBlending(source1, source2, texture_blend);
        blend_results.push_back(texture_blend.clone());
        
        std::cout << "All blending techniques completed!" << std::endl;
    }
    
    void alphaBlending(const cv::Mat& img1, const cv::Mat& img2, const cv::Mat& alpha_mask, cv::Mat& result) {
        result = cv::Mat::zeros(img1.size(), img1.type());
        
        for (int y = 0; y < img1.rows; y++) {
            for (int x = 0; x < img1.cols; x++) {
                double alpha = alpha_mask.at<uchar>(y, x) / 255.0;
                
                for (int c = 0; c < 3; c++) {
                    result.at<cv::Vec3b>(y, x)[c] = cv::saturate_cast<uchar>(
                        alpha * img1.at<cv::Vec3b>(y, x)[c] + (1 - alpha) * img2.at<cv::Vec3b>(y, x)[c]
                    );
                }
            }
        }
    }
    
    void gaussianPyramidBlending(const cv::Mat& img1, const cv::Mat& img2, cv::Mat& result) {
        // Create Gaussian pyramids
        std::vector<cv::Mat> gaussian1, gaussian2, gaussian_mask;
        
        cv::Mat current1 = img1.clone();
        cv::Mat current2 = img2.clone();
        cv::Mat current_mask = mask.clone();
        
        gaussian1.push_back(current1);
        gaussian2.push_back(current2);
        gaussian_mask.push_back(current_mask);
        
        // Build pyramids
        for (int i = 0; i < 4; i++) {
            cv::pyrDown(current1, current1);
            cv::pyrDown(current2, current2);
            cv::pyrDown(current_mask, current_mask);
            
            gaussian1.push_back(current1);
            gaussian2.push_back(current2);
            gaussian_mask.push_back(current_mask);
        }
        
        // Blend at each level and reconstruct
        cv::Mat blended = gaussian1.back();
        
        for (int i = gaussian1.size() - 2; i >= 0; i--) {
            // Blend at current level
            cv::Mat level_blend;
            alphaBlending(gaussian1[i], gaussian2[i], gaussian_mask[i], level_blend);
            
            // Upsample and combine
            cv::Mat upsampled;
            cv::pyrUp(blended, upsampled, gaussian1[i].size());
            cv::add(upsampled, level_blend, blended);
        }
        
        result = blended.clone();
    }
    
    void laplacianPyramidBlending(const cv::Mat& img1, const cv::Mat& img2, cv::Mat& result) {
        // Create Laplacian pyramids
        std::vector<cv::Mat> laplacian1, laplacian2, gaussian1, gaussian2, gaussian_mask;
        
        // Build Gaussian pyramids
        cv::Mat current1 = img1.clone();
        cv::Mat current2 = img2.clone();
        
        gaussian1.push_back(current1);
        gaussian2.push_back(current2);
        
        for (int i = 0; i < 4; i++) {
            cv::Mat down1, down2;
            cv::pyrDown(current1, down1);
            cv::pyrDown(current2, down2);
            
            gaussian1.push_back(down1);
            gaussian2.push_back(down2);
            
            current1 = down1;
            current2 = down2;
        }
        
        // Create Laplacian pyramids
        for (int i = 0; i < gaussian1.size() - 1; i++) {
            cv::Mat up1, up2, lap1, lap2;
            cv::pyrUp(gaussian1[i + 1], up1, gaussian1[i].size());
            cv::pyrUp(gaussian2[i + 1], up2, gaussian2[i].size());
            
            cv::subtract(gaussian1[i], up1, lap1);
            cv::subtract(gaussian2[i], up2, lap2);
            
            laplacian1.push_back(lap1);
            laplacian2.push_back(lap2);
        }
        laplacian1.push_back(gaussian1.back());
        laplacian2.push_back(gaussian2.back());
        
        // Blend Laplacian pyramids
        std::vector<cv::Mat> blended_pyramid;
        cv::Mat current_mask = mask.clone();
        
        for (int i = 0; i < laplacian1.size(); i++) {
            cv::Mat level_blend;
            alphaBlending(laplacian1[i], laplacian2[i], current_mask, level_blend);
            blended_pyramid.push_back(level_blend);
            
            if (i < laplacian1.size() - 1) {
                cv::pyrDown(current_mask, current_mask);
            }
        }
        
        // Reconstruct from Laplacian pyramid
        result = blended_pyramid.back();
        for (int i = blended_pyramid.size() - 2; i >= 0; i--) {
            cv::Mat upsampled;
            cv::pyrUp(result, upsampled, blended_pyramid[i].size());
            cv::add(upsampled, blended_pyramid[i], result);
        }
    }
    
    void poissonBlending(const cv::Mat& img1, const cv::Mat& img2, cv::Mat& result) {
        // Simplified Poisson blending using gradient domain
        cv::Mat gray1, gray2;
        cv::cvtColor(img1, gray1, cv::COLOR_BGR2GRAY);
        cv::cvtColor(img2, gray2, cv::COLOR_BGR2GRAY);
        
        // Calculate gradients
        cv::Mat grad_x1, grad_y1, grad_x2, grad_y2;
        cv::Sobel(gray1, grad_x1, CV_64F, 1, 0, 3);
        cv::Sobel(gray1, grad_y1, CV_64F, 0, 1, 3);
        cv::Sobel(gray2, grad_x2, CV_64F, 1, 0, 3);
        cv::Sobel(gray2, grad_y2, CV_64F, 0, 1, 3);
        
        // Blend gradients
        cv::Mat blended_grad_x, blended_grad_y;
        alphaBlending(grad_x1, grad_x2, mask, blended_grad_x);
        alphaBlending(grad_y1, grad_y2, mask, blended_grad_y);
        
        // Convert back to 8-bit
        cv::convertScaleAbs(blended_grad_x, blended_grad_x);
        cv::convertScaleAbs(blended_grad_y, blended_grad_y);
        
        // Simple reconstruction (in practice, you'd solve the Poisson equation)
        cv::Mat reconstructed;
        cv::magnitude(blended_grad_x, blended_grad_y, reconstructed);
        cv::convertScaleAbs(reconstructed, reconstructed);
        
        // Convert back to color
        cv::cvtColor(reconstructed, result, cv::COLOR_GRAY2BGR);
    }
    
    void seamlessCloning(const cv::Mat& img1, const cv::Mat& img2, cv::Mat& result) {
        // Create a simple mask for seamless cloning
        cv::Mat clone_mask = cv::Mat::zeros(img1.size(), CV_8UC1);
        cv::rectangle(clone_mask, cv::Point(100, 100), cv::Point(300, 200), cv::Scalar(255), -1);
        
        // Apply Gaussian blur to mask edges
        cv::GaussianBlur(clone_mask, clone_mask, cv::Size(21, 21), 5);
        
        // Use OpenCV's seamless cloning
        cv::Point center(img1.cols / 2, img1.rows / 2);
        cv::seamlessClone(img2, img1, clone_mask, center, result, cv::NORMAL_CLONE);
    }
    
    void multibandBlending(const cv::Mat& img1, const cv::Mat& img2, cv::Mat& result) {
        // Multi-band blending using different frequency bands
        cv::Mat blurred1, blurred2;
        cv::GaussianBlur(img1, blurred1, cv::Size(15, 15), 5);
        cv::GaussianBlur(img2, blurred2, cv::Size(15, 15), 5);
        
        cv::Mat high_freq1, high_freq2;
        cv::subtract(img1, blurred1, high_freq1);
        cv::subtract(img2, blurred2, high_freq2);
        
        cv::Mat low_blend, high_blend;
        alphaBlending(blurred1, blurred2, mask, low_blend);
        alphaBlending(high_freq1, high_freq2, mask, high_blend);
        
        cv::add(low_blend, high_blend, result);
    }
    
    void gradientDomainBlending(const cv::Mat& img1, const cv::Mat& img2, cv::Mat& result) {
        // Gradient domain blending using edge-preserving techniques
        cv::Mat edges1, edges2;
        cv::Canny(cv::cvtColor(img1, edges1, cv::COLOR_BGR2GRAY), edges1, 50, 150);
        cv::Canny(cv::cvtColor(img2, edges2, cv::COLOR_BGR2GRAY), edges2, 50, 150);
        
        cv::Mat edge_mask;
        cv::bitwise_or(edges1, edges2, edge_mask);
        
        // Use edge information for blending
        cv::Mat weighted_mask = mask.clone();
        cv::addWeighted(mask, 0.7, edge_mask, 0.3, 0, weighted_mask);
        
        alphaBlending(img1, img2, weighted_mask, result);
    }
    
    void textureSynthesisBlending(const cv::Mat& img1, const cv::Mat& img2, cv::Mat& result) {
        // Texture synthesis blending using patch-based approach
        cv::Mat patches1, patches2;
        
        // Extract texture patches
        cv::Rect patch_rect(50, 50, 100, 100);
        cv::Mat patch1 = img1(patch_rect);
        cv::Mat patch2 = img2(patch_rect);
        
        // Create texture mask
        cv::Mat texture_mask = cv::Mat::zeros(img1.size(), CV_8UC1);
        cv::rectangle(texture_mask, patch_rect, cv::Scalar(255), -1);
        cv::GaussianBlur(texture_mask, texture_mask, cv::Size(21, 21), 5);
        
        // Blend with texture emphasis
        cv::Mat temp1, temp2;
        cv::addWeighted(img1, 0.8, patch1, 0.2, 0, temp1);
        cv::addWeighted(img2, 0.8, patch2, 0.2, 0, temp2);
        
        alphaBlending(temp1, temp2, texture_mask, result);
    }
    
    void displayResults() {
        // Create a large display canvas
        int cols = 3;
        int rows = 3;
        int cell_width = 200;
        int cell_height = 150;
        
        cv::Mat display(rows * cell_height, cols * cell_width, CV_8UC3, cv::Scalar(0, 0, 0));
        
        // Display original images
        cv::Mat resized1, resized2;
        cv::resize(source1, resized1, cv::Size(cell_width, cell_height));
        cv::resize(source2, resized2, cv::Size(cell_width, cell_height));
        
        cv::Rect roi1(0, 0, cell_width, cell_height);
        cv::Rect roi2(cell_width, 0, cell_width, cell_height);
        resized1.copyTo(display(roi1));
        resized2.copyTo(display(roi2));
        
        cv::putText(display, "Source 1", cv::Point(10, 30), cv::FONT_HERSHEY_SIMPLEX, 0.6, cv::Scalar(255, 255, 255), 2);
        cv::putText(display, "Source 2", cv::Point(cell_width + 10, 30), cv::FONT_HERSHEY_SIMPLEX, 0.6, cv::Scalar(255, 255, 255), 2);
        
        // Display blending results
        for (size_t i = 0; i < blend_results.size() && i < 6; i++) {
            int row = (i + 2) / cols;
            int col = (i + 2) % cols;
            
            cv::Mat resized_result;
            cv::resize(blend_results[i], resized_result, cv::Size(cell_width, cell_height));
            
            cv::Rect roi(col * cell_width, row * cell_height, cell_width, cell_height);
            resized_result.copyTo(display(roi));
            
            // Add algorithm name
            cv::putText(display, blend_names[i], cv::Point(col * cell_width + 10, row * cell_height + 30), 
                       cv::FONT_HERSHEY_SIMPLEX, 0.4, cv::Scalar(255, 255, 255), 1);
        }
        
        cv::imshow("Advanced Image Blending Comparison", display);
        
        // Display mask
        cv::imshow("Blend Mask", mask);
        
        // Display individual results
        displayIndividualResults();
    }
    
    void displayIndividualResults() {
        for (size_t i = 0; i < blend_results.size(); i++) {
            cv::imshow(blend_names[i], blend_results[i]);
        }
    }
    
    void analyzeBlendingQuality() {
        std::cout << "\n=== Blending Quality Analysis ===" << std::endl;
        
        for (size_t i = 0; i < blend_results.size(); i++) {
            // Calculate image statistics
            cv::Scalar mean_val = cv::mean(blend_results[i]);
            cv::Scalar std_val;
            cv::meanStdDev(blend_results[i], mean_val, std_val);
            
            std::cout << blend_names[i] << ":" << std::endl;
            std::cout << "  Mean intensity: " << mean_val[0] << std::endl;
            std::cout << "  Standard deviation: " << std_val[0] << std::endl;
            
            // Calculate gradient magnitude for edge preservation
            cv::Mat gray_result;
            cv::cvtColor(blend_results[i], gray_result, cv::COLOR_BGR2GRAY);
            
            cv::Mat grad_x, grad_y, gradient_magnitude;
            cv::Sobel(gray_result, grad_x, CV_64F, 1, 0, 3);
            cv::Sobel(gray_result, grad_y, CV_64F, 0, 1, 3);
            cv::magnitude(grad_x, grad_y, gradient_magnitude);
            
            cv::Scalar grad_mean = cv::mean(gradient_magnitude);
            std::cout << "  Gradient magnitude: " << grad_mean[0] << std::endl;
            std::cout << std::endl;
        }
    }
};

int main() {
    AdvancedImageBlender blender;
    
    // Load images
    blender.loadImages();
    
    // Perform all blending techniques
    blender.performAllBlending();
    
    // Display results
    blender.displayResults();
    
    // Analyze blending quality
    blender.analyzeBlendingQuality();
    
    std::cout << "\nKey Features Demonstrated:" << std::endl;
    std::cout << "- Alpha blending with smooth transitions" << std::endl;
    std::cout << "- Gaussian pyramid blending for multi-resolution" << std::endl;
    std::cout << "- Laplacian pyramid blending for seamless fusion" << std::endl;
    std::cout << "- Poisson blending for gradient domain fusion" << std::endl;
    std::cout << "- Seamless cloning for object insertion" << std::endl;
    std::cout << "- Multi-band blending for frequency separation" << std::endl;
    std::cout << "- Gradient domain blending for edge preservation" << std::endl;
    std::cout << "- Texture synthesis blending for patch-based fusion" << std::endl;
    std::cout << "- Quality analysis and comparison of blending methods" << std::endl;
    
    std::cout << "\nPress any key to exit..." << std::endl;
    cv::waitKey(0);
    cv::destroyAllWindows();
    
    return 0;
}
