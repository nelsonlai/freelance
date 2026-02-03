// 20_advanced_filters.cpp
// Advanced Level - Advanced Image Filters and Effects
// This program demonstrates advanced image filtering techniques

#include <iostream>
#include <opencv2/opencv.hpp>

int main() {
    // Load an image
    cv::Mat original = cv::imread("image.jpg");
    
    if (original.empty()) {
        std::cout << "Error: Could not load image 'image.jpg'" << std::endl;
        return -1;
    }
    
    // Resize for better processing
    cv::Mat resized;
    cv::resize(original, resized, cv::Size(400, 300));
    
    // 1. Bilateral Filter (Edge-preserving smoothing)
    cv::Mat bilateral;
    cv::bilateralFilter(resized, bilateral, 9, 75, 75);
    
    // 2. Non-local Means Denoising
    cv::Mat nlm;
    cv::fastNlMeansDenoisingColored(resized, nlm, 10, 10, 7, 21);
    
    // 3. Gaussian Pyramid
    cv::Mat gaussian_pyramid;
    cv::pyrDown(resized, gaussian_pyramid);
    cv::resize(gaussian_pyramid, gaussian_pyramid, resized.size());
    
    // 4. Laplacian Pyramid
    cv::Mat laplacian_pyramid;
    cv::Mat temp;
    cv::pyrDown(resized, temp);
    cv::pyrUp(temp, temp, resized.size());
    cv::subtract(resized, temp, laplacian_pyramid);
    
    // 5. Unsharp Masking (Sharpening)
    cv::Mat blurred, unsharp_mask;
    cv::GaussianBlur(resized, blurred, cv::Size(0, 0), 3);
    cv::addWeighted(resized, 1.5, blurred, -0.5, 0, unsharp_mask);
    
    // 6. High Pass Filter
    cv::Mat high_pass;
    cv::Mat kernel_hp = (cv::Mat_<float>(3, 3) << 
        0, -1, 0,
        -1, 5, -1,
        0, -1, 0);
    cv::filter2D(resized, high_pass, -1, kernel_hp);
    
    // 7. Emboss Effect
    cv::Mat emboss;
    cv::Mat kernel_emboss = (cv::Mat_<float>(3, 3) << 
        -2, -1, 0,
        -1, 1, 1,
        0, 1, 2);
    cv::filter2D(resized, emboss, -1, kernel_emboss);
    
    // 8. Oil Painting Effect
    cv::Mat oil_painting;
    cv::Mat gray;
    cv::cvtColor(resized, gray, cv::COLOR_BGR2GRAY);
    
    oil_painting = resized.clone();
    int kernel_size = 5;
    
    for (int i = kernel_size/2; i < gray.rows - kernel_size/2; i++) {
        for (int j = kernel_size/2; j < gray.cols - kernel_size/2; j++) {
            // Get local histogram
            std::vector<int> histogram(256, 0);
            cv::Vec3b sum_color(0, 0, 0);
            
            for (int ki = -kernel_size/2; ki <= kernel_size/2; ki++) {
                for (int kj = -kernel_size/2; kj <= kernel_size/2; kj++) {
                    int pixel_value = gray.at<uchar>(i + ki, j + kj);
                    histogram[pixel_value]++;
                    sum_color += resized.at<cv::Vec3b>(i + ki, j + kj);
                }
            }
            
            // Find most frequent intensity
            int max_count = 0;
            int dominant_intensity = 0;
            for (int h = 0; h < 256; h++) {
                if (histogram[h] > max_count) {
                    max_count = histogram[h];
                    dominant_intensity = h;
                }
            }
            
            // Set pixel to dominant color
            oil_painting.at<cv::Vec3b>(i, j) = cv::Vec3b(dominant_intensity, dominant_intensity, dominant_intensity);
        }
    }
    
    // 9. Sketch Effect
    cv::Mat sketch;
    cv::Mat gray_sketch;
    cv::cvtColor(resized, gray_sketch, cv::COLOR_BGR2GRAY);
    cv::Mat inverted = 255 - gray_sketch;
    cv::GaussianBlur(inverted, inverted, cv::Size(21, 21), 0);
    cv::divide(gray_sketch, 255 - inverted, sketch, 256);
    cv::cvtColor(sketch, sketch, cv::COLOR_GRAY2BGR);
    
    // 10. Cartoon Effect (Advanced)
    cv::Mat cartoon;
    cv::Mat temp1, temp2;
    cv::bilateralFilter(resized, temp1, 9, 75, 75);
    cv::cvtColor(temp1, temp2, cv::COLOR_BGR2GRAY);
    cv::adaptiveThreshold(temp2, temp2, 255, cv::ADAPTIVE_THRESH_MEAN_C, cv::THRESH_BINARY, 9, 9);
    cv::cvtColor(temp2, temp2, cv::COLOR_GRAY2BGR);
    cv::bitwise_and(temp1, temp2, cartoon);
    
    // Create display layout
    cv::Mat topRow1, topRow2, middleRow, bottomRow, display;
    
    // Top row 1: Original, Bilateral, NLM, Gaussian Pyramid
    cv::hconcat(std::vector<cv::Mat>{resized, bilateral, nlm, gaussian_pyramid}, topRow1);
    
    // Top row 2: Laplacian Pyramid, Unsharp Mask, High Pass, Emboss
    cv::hconcat(std::vector<cv::Mat>{laplacian_pyramid, unsharp_mask, high_pass, emboss}, topRow2);
    
    // Bottom row: Oil Painting, Sketch, Cartoon, (empty)
    cv::Mat empty = cv::Mat::zeros(resized.size(), resized.type());
    cv::hconcat(std::vector<cv::Mat>{oil_painting, sketch, cartoon, empty}, bottomRow);
    
    // Combine rows
    cv::vconcat(std::vector<cv::Mat>{topRow1, topRow2, bottomRow}, display);
    
    // Resize if too large
    if (display.cols > 1400 || display.rows > 1000) {
        double scale = std::min(1400.0 / display.cols, 1000.0 / display.rows);
        cv::resize(display, display, cv::Size(), scale, scale);
    }
    
    cv::imshow("Advanced Image Filters", display);
    
    std::cout << "Advanced Image Filters and Effects:" << std::endl;
    std::cout << "1. Bilateral Filter: Edge-preserving smoothing" << std::endl;
    std::cout << "2. Non-local Means: Advanced denoising" << std::endl;
    std::cout << "3. Gaussian Pyramid: Multi-scale representation" << std::endl;
    std::cout << "4. Laplacian Pyramid: Edge enhancement" << std::endl;
    std::cout << "5. Unsharp Masking: Professional sharpening" << std::endl;
    std::cout << "6. High Pass Filter: Edge detection" << std::endl;
    std::cout << "7. Emboss Effect: 3D-like appearance" << std::endl;
    std::cout << "8. Oil Painting: Artistic effect" << std::endl;
    std::cout << "9. Sketch Effect: Pencil drawing style" << std::endl;
    std::cout << "10. Cartoon Effect: Stylized appearance" << std::endl;
    
    std::cout << "\nFilter Applications:" << std::endl;
    std::cout << "- Image enhancement" << std::endl;
    std::cout << "- Noise reduction" << std::endl;
    std::cout << "- Artistic effects" << std::endl;
    std::cout << "- Computer vision preprocessing" << std::endl;
    
    std::cout << "\nPress any key to close..." << std::endl;
    cv::waitKey(0);
    cv::destroyAllWindows();
    
    return 0;
}
