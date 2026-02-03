/**
 * 06_basic_filters.cpp
 * Beginner Level - Basic Image Filters
 * 
 * This program demonstrates fundamental image filtering operations in computer vision.
 * Image filtering is the process of modifying or enhancing images using mathematical
 * operations on pixel values.
 * 
 * LEARNING OBJECTIVES:
 * 1. Understand different types of image filters and their purposes
 * 2. Learn about blurring operations (noise reduction, smoothing)
 * 3. Explore edge detection techniques (feature extraction)
 * 4. Study image enhancement methods (sharpening, contrast adjustment)
 * 5. Understand noise reduction filters (median filtering)
 * 6. Learn about histogram equalization for contrast enhancement
 * 
 * KEY CONCEPTS:
 * - Convolution: Mathematical operation for applying filters
 * - Kernel/Filter: Small matrix used to process images
 * - Edge Detection: Finding boundaries between different regions
 * - Noise: Unwanted variations in pixel values
 * - Histogram: Distribution of pixel intensity values
 * 
 * FILTER TYPES COVERED:
 * - Gaussian Blur: Smoothing filter for noise reduction
 * - Canny Edge Detection: Multi-stage edge detection algorithm
 * - Laplacian Sharpening: Enhances image details and edges
 * - Brightness/Contrast: Adjusts image intensity and contrast
 * - Histogram Equalization: Improves image contrast automatically
 * - Median Filter: Removes salt-and-pepper noise
 * 
 * APPLICATIONS:
 * - Image preprocessing for computer vision tasks
 * - Noise reduction in photography
 * - Feature extraction for object detection
 * - Image enhancement for better visualization
 * - Medical image processing
 */

#include <iostream>    // For console input/output
#include <opencv2/opencv.hpp>  // Main OpenCV library

int main() {
    /**
     * STEP 1: IMAGE LOADING AND VALIDATION
     * 
     * Always start by loading and validating your input image.
     * This prevents crashes and provides clear error messages.
     */
    cv::Mat original = cv::imread("image.jpg");
    
    // Check if image loaded successfully
    if (original.empty()) {
        std::cout << "Error: Could not load image 'image.jpg'" << std::endl;
        std::cout << "Make sure the image file exists in the current directory" << std::endl;
        return -1;  // Exit with error code
    }
    
    /**
     * STEP 2: CONVERT TO GRAYSCALE
     * 
     * Many image processing operations work on grayscale images.
     * Converting to grayscale reduces computational complexity and
     * makes certain operations (like edge detection) more effective.
     */
    cv::Mat gray;
    cv::cvtColor(original, gray, cv::COLOR_BGR2GRAY);
    
    /**
     * STEP 3: APPLY DIFFERENT FILTERS
     * 
     * We'll apply 6 different types of filters to demonstrate
     * various image processing techniques.
     */
    
    /**
     * FILTER 1: GAUSSIAN BLUR
     * 
     * Purpose: Smoothing and noise reduction
     * How it works: Applies a Gaussian kernel that averages nearby pixels
     * 
     * Parameters:
     * - original: Input image
     * - blurred: Output blurred image
     * - cv::Size(15, 15): Kernel size (15x15 pixels)
     * - 0: Standard deviation (0 = auto-calculate from kernel size)
     * 
     * Applications:
     * - Noise reduction
     * - Preprocessing before edge detection
     * - Creating artistic effects
     */
    cv::Mat blurred;
    cv::GaussianBlur(original, blurred, cv::Size(15, 15), 0);
    
    /**
     * FILTER 2: CANNY EDGE DETECTION
     * 
     * Purpose: Find edges (boundaries) in the image
     * How it works: Multi-stage algorithm that detects strong edges
     * 
     * Algorithm stages:
     * 1. Apply Gaussian blur to reduce noise
     * 2. Find gradients using Sobel operators
     * 3. Apply non-maximum suppression
     * 4. Use double thresholding to detect strong and weak edges
     * 5. Track edges by hysteresis
     * 
     * Parameters:
     * - gray: Input grayscale image
     * - edges: Output binary edge image
     * - 50: Lower threshold (weak edges below this are discarded)
     * - 150: Upper threshold (strong edges above this are kept)
     * 
     * Applications:
     * - Object detection
     * - Feature extraction
     * - Image segmentation
     */
    cv::Mat edges;
    cv::Canny(gray, edges, 50, 150);
    
    /**
     * FILTER 3: LAPLACIAN SHARPENING
     * 
     * Purpose: Enhance image details and make edges more prominent
     * How it works: Laplacian operator detects rapid intensity changes
     * 
     * Mathematical concept:
     * - Laplacian is the second derivative of the image
     * - It highlights areas where intensity changes rapidly (edges)
     * - Adding this to the original image enhances details
     * 
     * Parameters:
     * - gray: Input grayscale image
     * - sharpened: Output sharpened image
     * - CV_64F: Output data type (64-bit float)
     * 
     * Note: We use convertScaleAbs to convert back to displayable format
     */
    cv::Mat sharpened;
    cv::Laplacian(gray, sharpened, CV_64F);
    cv::convertScaleAbs(sharpened, sharpened);  // Convert to absolute values and scale to 0-255
    
    /**
     * FILTER 4: BRIGHTNESS AND CONTRAST ADJUSTMENT
     * 
     * Purpose: Adjust image brightness and contrast
     * How it works: Linear transformation of pixel values
     * 
     * Formula: new_pixel = alpha * old_pixel + beta
     * - alpha: Controls contrast (1.0 = no change, >1.0 = increase contrast)
     * - beta: Controls brightness (>0 = brighter, <0 = darker)
     * 
     * Parameters:
     * - original: Input image
     * - bright_contrast: Output adjusted image
     * - -1: Keep same data type as input
     * - 1.5: Alpha (contrast multiplier)
     * - 30: Beta (brightness offset)
     * 
     * Applications:
     * - Image enhancement
     * - Normalization for computer vision tasks
     * - Artistic effects
     */
    cv::Mat bright_contrast;
    original.convertTo(bright_contrast, -1, 1.5, 30);  // alpha=1.5, beta=30
    
    /**
     * FILTER 5: HISTOGRAM EQUALIZATION
     * 
     * Purpose: Automatically improve image contrast
     * How it works: Redistributes pixel intensities to use full range
     * 
     * Process:
     * 1. Calculate histogram of pixel intensities
     * 2. Create cumulative distribution function
     * 3. Map original intensities to new values
     * 4. Results in more uniform distribution of intensities
     * 
     * Parameters:
     * - gray: Input grayscale image
     * - equalized: Output contrast-enhanced image
     * 
     * Applications:
     * - Medical imaging
     * - Low-contrast image enhancement
     * - Preprocessing for better feature detection
     */
    cv::Mat equalized;
    cv::equalizeHist(gray, equalized);
    
    /**
     * FILTER 6: MEDIAN FILTER
     * 
     * Purpose: Remove salt-and-pepper noise while preserving edges
     * How it works: Replaces each pixel with the median of its neighborhood
     * 
     * Advantages over Gaussian blur:
     * - Better edge preservation
     * - Effective against salt-and-pepper noise
     * - Non-linear filtering (better for impulse noise)
     * 
     * Parameters:
     * - original: Input image
     * - median_filtered: Output filtered image
     * - 5: Kernel size (5x5 neighborhood)
     * 
     * Applications:
     * - Noise reduction in medical images
     * - Removing artifacts in digital photography
     * - Preprocessing for better segmentation
     */
    cv::Mat median_filtered;
    cv::medianBlur(original, median_filtered, 5);
    
    /**
     * STEP 4: PREPARE IMAGES FOR DISPLAY
     * 
     * To create a uniform display, we need to:
     * 1. Convert single-channel images to 3-channel for consistent display
     * 2. Resize all images to the same dimensions
     * 3. Arrange them in a grid layout
     */
    
    // Convert grayscale images back to BGR for consistent display
    cv::Mat edges_color, sharpened_color, equalized_color;
    cv::cvtColor(edges, edges_color, cv::COLOR_GRAY2BGR);
    cv::cvtColor(sharpened, sharpened_color, cv::COLOR_GRAY2BGR);
    cv::cvtColor(equalized, equalized_color, cv::COLOR_GRAY2BGR);
    
    /**
     * STANDARDIZE IMAGE SIZES:
     * - All images must have the same dimensions for concatenation
     * - We choose 300x200 as a reasonable size for each filter result
     * - This creates a total display size of 900x400 (3x2 images)
     */
    cv::Size target_size(300, 200);  // Standard size for each filter result
    cv::Mat original_resized, blurred_resized, edges_color_resized, 
            sharpened_color_resized, bright_contrast_resized, 
            equalized_color_resized, median_filtered_resized;
    
    // Resize all images to the target size
    cv::resize(original, original_resized, target_size);
    cv::resize(blurred, blurred_resized, target_size);
    cv::resize(edges_color, edges_color_resized, target_size);
    cv::resize(sharpened_color, sharpened_color_resized, target_size);
    cv::resize(bright_contrast, bright_contrast_resized, target_size);
    cv::resize(equalized_color, equalized_color_resized, target_size);
    cv::resize(median_filtered, median_filtered_resized, target_size);
    
    /**
     * CREATE GRID LAYOUT:
     * - Arrange images in a 2x3 grid (2 rows, 3 columns)
     * - Top row: Original, Gaussian Blur, Edge Detection
     * - Bottom row: Sharpening, Brightness/Contrast, Histogram Equalization
     * - Use hconcat for horizontal concatenation (rows)
     * - Use vconcat for vertical concatenation (columns)
     */
    cv::Mat topRow, bottomRow, display;
    
    // Top row: original, blurred, edges (3 images)
    cv::hconcat(std::vector<cv::Mat>{original_resized, blurred_resized, edges_color_resized}, topRow);
    
    // Bottom row: sharpened, bright_contrast, equalized (3 images to match top row)
    cv::hconcat(std::vector<cv::Mat>{sharpened_color_resized, bright_contrast_resized, equalized_color_resized}, bottomRow);
    
    // Combine rows vertically
    cv::vconcat(topRow, bottomRow, display);
    
    /**
     * ADAPTIVE DISPLAY SIZING:
     * - If the display is too large for the screen, scale it down
     * - Maintain aspect ratio while fitting within 1400x800 pixels
     * - This ensures the display is visible on different screen sizes
     */
    if (display.cols > 1400 || display.rows > 800) {
        double scale = std::min(1400.0 / display.cols, 800.0 / display.rows);
        cv::resize(display, display, cv::Size(), scale, scale);
    }
    
    /**
     * DISPLAY RESULTS:
     * - Show the combined grid of all filter results
     * - Window title helps identify the application
     */
    cv::imshow("Basic Image Filters", display);
    
    /**
     * EDUCATIONAL OUTPUT:
     * - Print detailed information about each filter
     * - Help students understand what they're seeing
     * - Explain the purpose and applications of each filter
     */
    std::cout << "Applied filters (displayed in 3x2 grid):" << std::endl;
    std::cout << "1. Original Image - Reference image before filtering" << std::endl;
    std::cout << "2. Gaussian Blur - Smoothing and noise reduction" << std::endl;
    std::cout << "3. Canny Edge Detection - Boundary and feature extraction" << std::endl;
    std::cout << "4. Laplacian Sharpening - Detail enhancement and edge highlighting" << std::endl;
    std::cout << "5. Brightness & Contrast - Intensity and contrast adjustment" << std::endl;
    std::cout << "6. Histogram Equalization - Automatic contrast enhancement" << std::endl;
    std::cout << "Note: Median Filter was also applied but not displayed due to layout constraints" << std::endl;
    
    std::cout << "\nFilter Categories:" << std::endl;
    std::cout << "- Smoothing Filters: Gaussian Blur, Median Filter" << std::endl;
    std::cout << "- Edge Detection: Canny Edge Detection" << std::endl;
    std::cout << "- Enhancement: Laplacian Sharpening, Histogram Equalization" << std::endl;
    std::cout << "- Adjustment: Brightness & Contrast" << std::endl;
    
    std::cout << "\nKey Learning Points:" << std::endl;
    std::cout << "- Different filters serve different purposes in image processing" << std::endl;
    std::cout << "- Gaussian blur reduces noise but also smooths details" << std::endl;
    std::cout << "- Edge detection is crucial for object recognition" << std::endl;
    std::cout << "- Histogram equalization improves contrast automatically" << std::endl;
    std::cout << "- Median filter preserves edges better than Gaussian blur" << std::endl;
    
    std::cout << "\nPress any key to close..." << std::endl;
    cv::waitKey(0);  // Wait for user input before closing
    cv::destroyAllWindows();  // Clean up all windows
    
    return 0;  // Successful program termination
}
