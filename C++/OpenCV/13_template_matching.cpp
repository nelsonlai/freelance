/**
 * 13_template_matching.cpp
 * Intermediate Level - Template Matching
 * 
 * This program demonstrates template matching, a fundamental technique in computer vision
 * for finding instances of a template image within a larger image. Template matching is
 * widely used for object detection, tracking, and recognition tasks.
 * 
 * LEARNING OBJECTIVES:
 * 1. Understand the concept of template matching and its applications
 * 2. Learn about different template matching methods and their characteristics
 * 3. Explore correlation-based matching algorithms
 * 4. Study normalization techniques for robust matching
 * 5. Understand thresholding and peak detection for match identification
 * 6. Learn about template matching limitations and improvements
 * 
 * KEY CONCEPTS:
 * - Template: Small image patch used as a reference for matching
 * - Correlation: Mathematical measure of similarity between template and image regions
 * - Normalization: Scaling correlation values to a standard range
 * - Threshold: Minimum similarity score required for a match
 * - Peak Detection: Finding local maxima in correlation maps
 * - Heatmap: Visualization of correlation scores across the image
 * 
 * TEMPLATE MATCHING METHODS:
 * - TM_SQDIFF: Sum of Squared Differences (best match = minimum value)
 * - TM_SQDIFF_NORMED: Normalized Sum of Squared Differences
 * - TM_CCORR: Cross Correlation (best match = maximum value)
 * - TM_CCORR_NORMED: Normalized Cross Correlation
 * - TM_CCOEFF: Cross Correlation Coefficient (best match = maximum value)
 * - TM_CCOEFF_NORMED: Normalized Cross Correlation Coefficient
 * 
 * MATHEMATICAL FOUNDATION:
 * - Template matching is based on correlation and similarity measures
 * - Different methods have different sensitivity to illumination changes
 * - Normalized methods are more robust to lighting variations
 * - Correlation maps show similarity scores for each possible template position
 * 
 * APPLICATIONS:
 * - Object detection and recognition
 * - Face detection and tracking
 * - Medical image analysis
 * - Quality control in manufacturing
 * - Document analysis and OCR
 * - Augmented reality
 * - Robotics and autonomous navigation
 * - Video surveillance
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
    cv::Mat image = cv::imread("image.jpg");
    
    // Check if image loaded successfully
    if (image.empty()) {
        std::cout << "Error: Could not load image 'image.jpg'" << std::endl;
        std::cout << "Make sure the image file exists in the current directory" << std::endl;
        return -1;  // Exit with error code
    }
    
    /**
     * STEP 2: CREATE TEMPLATE
     * 
     * A template is a small image patch that we want to find within the larger image.
     * For demonstration purposes, we'll extract a region from the center of the image.
     * In real applications, templates are usually manually selected or extracted
     * from training data.
     */
    
    // Define template dimensions
    int templateWidth = 50;   // Width of the template in pixels
    int templateHeight = 50;  // Height of the template in pixels
    
    // Calculate center position of the main image
    int centerX = image.cols / 2;  // Center X coordinate
    int centerY = image.rows / 2;  // Center Y coordinate
    
    /**
     * CREATE TEMPLATE RECTANGLE:
     * 
     * We create a rectangle that defines the template region.
     * The rectangle is centered in the image for demonstration purposes.
     * 
     * Parameters:
     * - centerX - templateWidth/2: Left edge of template
     * - centerY - templateHeight/2: Top edge of template
     * - templateWidth: Width of template
     * - templateHeight: Height of template
     */
    cv::Rect templateRect(centerX - templateWidth/2, centerY - templateHeight/2, 
                         templateWidth, templateHeight);
    
    /**
     * EXTRACT TEMPLATE:
     * 
     * Extract the template image from the main image using the rectangle.
     * We use clone() to ensure we have an independent copy.
     */
    cv::Mat template_img = image(templateRect).clone();
    
    /**
     * VISUALIZE TEMPLATE REGION:
     * 
     * Draw a green rectangle around the template region to show where
     * the template was extracted from. This helps students understand
     * the template creation process.
     */
    cv::Mat image_with_template = image.clone();
    cv::rectangle(image_with_template, templateRect, cv::Scalar(0, 255, 0), 2);
    cv::putText(image_with_template, "Template Region", 
               cv::Point(templateRect.x, templateRect.y - 10),
               cv::FONT_HERSHEY_SIMPLEX, 0.6, cv::Scalar(0, 255, 0), 2);
    
    /**
     * STEP 3: CONVERT TO GRAYSCALE
     * 
     * Template matching works on grayscale images for efficiency and simplicity.
     * Converting to grayscale reduces computational complexity and makes
     * the matching process more robust to color variations.
     */
    cv::Mat gray_image, gray_template;
    cv::cvtColor(image, gray_image, cv::COLOR_BGR2GRAY);
    cv::cvtColor(template_img, gray_template, cv::COLOR_BGR2GRAY);
    
    /**
     * STEP 4: PERFORM TEMPLATE MATCHING
     * 
     * Template matching compares the template with every possible position in the image
     * and calculates a similarity score for each position. The result is a correlation
     * map showing how well the template matches at each location.
     * 
     * We'll demonstrate three different matching methods, each with different
     * characteristics and use cases.
     */
    
    // Declare result matrices for different matching methods
    cv::Mat result_ccoeff, result_ccoeff_normed;
    cv::Mat result_ccorr, result_ccorr_normed;
    cv::Mat result_sqdiff, result_sqdiff_normed;
    
    /**
     * METHOD 1: NORMALIZED CROSS CORRELATION (TM_CCORR_NORMED)
     * 
     * This method computes the normalized cross-correlation between the template
     * and image regions. It's robust to linear brightness changes.
     * 
     * Characteristics:
     * - Best match = maximum value (close to 1.0)
     * - Robust to uniform brightness changes
     * - Values range from 0 to 1
     * - Good for general-purpose matching
     * 
     * Mathematical formula: R(u,v) = Σ(T(x,y) * I(x+u, y+v)) / sqrt(ΣT² * ΣI²)
     */
    cv::matchTemplate(gray_image, gray_template, result_ccorr_normed, cv::TM_CCORR_NORMED);
    
    /**
     * METHOD 2: NORMALIZED CROSS CORRELATION COEFFICIENT (TM_CCOEFF_NORMED)
     * 
     * This method computes the normalized cross-correlation coefficient,
     * which is robust to both brightness and contrast changes.
     * 
     * Characteristics:
     * - Best match = maximum value (close to 1.0)
     * - Robust to linear brightness AND contrast changes
     * - Values range from -1 to 1
     * - Best method for general-purpose matching
     * - Most robust to illumination variations
     * 
     * Mathematical formula: R(u,v) = Σ(T'(x,y) * I'(x+u, y+v)) / sqrt(ΣT'² * ΣI'²)
     * where T' = T - mean(T) and I' = I - mean(I)
     */
    cv::matchTemplate(gray_image, gray_template, result_ccoeff_normed, cv::TM_CCOEFF_NORMED);
    
    /**
     * METHOD 3: SUM OF SQUARED DIFFERENCES (TM_SQDIFF and TM_SQDIFF_NORMED)
     * 
     * This method computes the sum of squared differences between
     * the template and image regions. It measures dissimilarity rather than similarity.
     * 
     * We compute both normalized and non-normalized versions:
     * - TM_SQDIFF: Raw sum of squared differences
     * - TM_SQDIFF_NORMED: Normalized version (better for comparison)
     * 
     * Characteristics:
     * - Best match = minimum value (close to 0.0)
     * - Sensitive to exact pixel matches
     * - Good for finding exact matches
     * - Less robust to illumination changes
     * 
     * Mathematical formula: R(u,v) = Σ(T(x,y) - I(x+u, y+v))²
     */
    cv::matchTemplate(gray_image, gray_template, result_sqdiff, cv::TM_SQDIFF);
    cv::matchTemplate(gray_image, gray_template, result_sqdiff_normed, cv::TM_SQDIFF_NORMED);
    
    /**
     * STEP 5: FIND BEST MATCH LOCATIONS
     * 
     * After computing the correlation maps, we need to find the locations
     * with the best match scores. The interpretation depends on the method used:
     * - For TM_SQDIFF methods: lower values = better matches
     * - For TM_CCORR and TM_CCOEFF methods: higher values = better matches
     */
    
    // Variables to store min/max values and their locations
    double minVal, maxVal;
    cv::Point minLoc, maxLoc;
    
    /**
     * FIND BEST MATCH FOR TM_SQDIFF_NORMED:
     * 
     * For Sum of Squared Differences, the best match has the minimum value
     * because we want the smallest difference between template and image region.
     */
    cv::minMaxLoc(result_sqdiff_normed, &minVal, &maxVal, &minLoc, &maxLoc);
    cv::Point sqdiff_match = minLoc;
    
    /**
     * FIND BEST MATCH FOR TM_CCORR_NORMED:
     * 
     * For Cross Correlation methods, the best match has the maximum value
     * because we want the highest correlation between template and image region.
     */
    cv::minMaxLoc(result_ccorr_normed, &minVal, &maxVal, &minLoc, &maxLoc);
    cv::Point ccorr_match = maxLoc;
    
    /**
     * FIND BEST MATCH FOR TM_CCOEFF_NORMED:
     * 
     * Cross Correlation Coefficient also uses maximum value for best match.
     * This method is typically the most robust to illumination changes.
     */
    cv::minMaxLoc(result_ccoeff_normed, &minVal, &maxVal, &minLoc, &maxLoc);
    cv::Point ccoeff_match = maxLoc;
    
    /**
     * STEP 6: VISUALIZE MATCH RESULTS
     * 
     * We'll create visualizations showing where each method found the best match.
     * Each method will be displayed with a different color for easy comparison.
     */
    
    /**
     * VISUALIZE SQDIFF MATCH:
     * 
     * Draw a blue rectangle around the best match found by the Sum of Squared
     * Differences method. This shows where the template was found in the image.
     */
    cv::Mat result_sqdiff_img = image.clone();
    cv::rectangle(result_sqdiff_img, 
                 cv::Rect(sqdiff_match.x, sqdiff_match.y, templateWidth, templateHeight),
                 cv::Scalar(255, 0, 0), 2);  // Blue rectangle
    cv::putText(result_sqdiff_img, "SQDIFF Match", 
               cv::Point(sqdiff_match.x, sqdiff_match.y - 10),
               cv::FONT_HERSHEY_SIMPLEX, 0.6, cv::Scalar(255, 0, 0), 2);
    
    /**
     * VISUALIZE CCORR MATCH:
     * 
     * Draw a green rectangle around the best match found by the Cross Correlation
     * method. Compare this with the SQDIFF result to see differences.
     */
    cv::Mat result_ccorr_img = image.clone();
    cv::rectangle(result_ccorr_img, 
                 cv::Rect(ccorr_match.x, ccorr_match.y, templateWidth, templateHeight),
                 cv::Scalar(0, 255, 0), 2);  // Green rectangle
    cv::putText(result_ccorr_img, "CCORR Match", 
               cv::Point(ccorr_match.x, ccorr_match.y - 10),
               cv::FONT_HERSHEY_SIMPLEX, 0.6, cv::Scalar(0, 255, 0), 2);
    
    /**
     * VISUALIZE CCOEFF MATCH:
     * 
     * Draw a red rectangle around the best match found by the Cross Correlation
     * Coefficient method. This is typically the most robust method.
     */
    cv::Mat result_ccoeff_img = image.clone();
    cv::rectangle(result_ccoeff_img, 
                 cv::Rect(ccoeff_match.x, ccoeff_match.y, templateWidth, templateHeight),
                 cv::Scalar(0, 0, 255), 2);  // Red rectangle
    cv::putText(result_ccoeff_img, "CCOEFF Match", 
               cv::Point(ccoeff_match.x, ccoeff_match.y - 10),
               cv::FONT_HERSHEY_SIMPLEX, 0.6, cv::Scalar(0, 0, 255), 2);
    
    /**
     * STEP 7: CREATE HEATMAPS
     * 
     * Heatmaps visualize the correlation scores across the entire image.
     * Bright areas indicate high correlation (good matches), while dark
     * areas indicate low correlation (poor matches).
     */
    cv::Mat sqdiff_heatmap, ccorr_heatmap, ccoeff_heatmap;
    
    /**
     * NORMALIZE CORRELATION MAPS:
     * 
     * The correlation maps contain floating-point values that need to be
     * normalized to 0-255 range for proper visualization as images.
     * 
     * Parameters:
     * - Input correlation map
     * - Output normalized heatmap
     * - 0, 255: Output range (0 to 255)
     * - cv::NORM_MINMAX: Normalization method (scales to full range)
     * - CV_8UC1: Output data type (8-bit unsigned, single channel)
     */
    cv::normalize(result_sqdiff_normed, sqdiff_heatmap, 0, 255, cv::NORM_MINMAX, CV_8UC1);
    cv::normalize(result_ccorr_normed, ccorr_heatmap, 0, 255, cv::NORM_MINMAX, CV_8UC1);
    cv::normalize(result_ccoeff_normed, ccoeff_heatmap, 0, 255, cv::NORM_MINMAX, CV_8UC1);
    
    /**
     * CONVERT HEATMAPS TO COLOR:
     * 
     * Convert single-channel grayscale heatmaps to 3-channel BGR images
     * for consistent display with other images.
     */
    cv::Mat sqdiff_heatmap_color, ccorr_heatmap_color, ccoeff_heatmap_color;
    cv::cvtColor(sqdiff_heatmap, sqdiff_heatmap_color, cv::COLOR_GRAY2BGR);
    cv::cvtColor(ccorr_heatmap, ccorr_heatmap_color, cv::COLOR_GRAY2BGR);
    cv::cvtColor(ccoeff_heatmap, ccoeff_heatmap_color, cv::COLOR_GRAY2BGR);
    
    /**
     * STEP 8: PREPARE IMAGES FOR DISPLAY
     * 
     * To create a uniform display, we need to:
     * 1. Resize all images to the same dimensions
     * 2. Arrange them in a 2x4 grid layout
     * 3. Show both match results and correlation heatmaps
     */
    
    /**
     * STANDARDIZE IMAGE SIZES:
     * - All images must have the same dimensions for concatenation
     * - We choose 300x200 as a reasonable size for each image in the grid
     * - This creates a total display size of 1200x400 (4x2 images)
     */
    cv::Size target_size(300, 200);  // Standard size for each image
    cv::Mat image_with_template_resized, template_img_resized, result_sqdiff_img_resized, result_ccorr_img_resized;
    cv::Mat result_ccoeff_img_resized, sqdiff_heatmap_color_resized, ccorr_heatmap_color_resized, ccoeff_heatmap_color_resized;
    
    cv::resize(image_with_template, image_with_template_resized, target_size);
    cv::resize(template_img, template_img_resized, target_size);
    cv::resize(result_sqdiff_img, result_sqdiff_img_resized, target_size);
    cv::resize(result_ccorr_img, result_ccorr_img_resized, target_size);
    cv::resize(result_ccoeff_img, result_ccoeff_img_resized, target_size);
    cv::resize(sqdiff_heatmap_color, sqdiff_heatmap_color_resized, target_size);
    cv::resize(ccorr_heatmap_color, ccorr_heatmap_color_resized, target_size);
    cv::resize(ccoeff_heatmap_color, ccoeff_heatmap_color_resized, target_size);
    
    // Create display layout - 2x4 grid (8 images total)
    cv::Mat topRow, bottomRow, display;
    
    // Top row: Original with template, Template, SQDIFF result, CCORR result
    cv::hconcat(std::vector<cv::Mat>{image_with_template_resized, template_img_resized, 
                                    result_sqdiff_img_resized, result_ccorr_img_resized}, topRow);
    
    // Bottom row: CCOEFF result, SQDIFF heatmap, CCORR heatmap, CCOEFF heatmap
    cv::hconcat(std::vector<cv::Mat>{result_ccoeff_img_resized, sqdiff_heatmap_color_resized, 
                                    ccorr_heatmap_color_resized, ccoeff_heatmap_color_resized}, bottomRow);
    
    // Combine rows
    cv::vconcat(topRow, bottomRow, display);
    
    // Resize if too large
    if (display.cols > 1400 || display.rows > 800) {
        double scale = std::min(1400.0 / display.cols, 800.0 / display.rows);
        cv::resize(display, display, cv::Size(), scale, scale);
    }
    
    /**
     * DISPLAY RESULTS:
     * - Show the combined grid of all template matching results
     * - Window title helps identify the application
     */
    cv::imshow("Template Matching", display);
    
    /**
     * EDUCATIONAL OUTPUT:
     * - Print detailed information about each matching method
     * - Help students understand what they're seeing
     * - Explain the correlation concepts and visualization
     */
    std::cout << "Template Matching Results (displayed in 4x2 grid):" << std::endl;
    std::cout << "Top row: Original with template region, Template image, SQDIFF match (blue), CCORR match (green)" << std::endl;
    std::cout << "Bottom row: CCOEFF match (red), SQDIFF heatmap, CCORR heatmap, CCOEFF heatmap" << std::endl;
    
    // Print match quality scores
    std::cout << "\nMatch Quality Scores:" << std::endl;
    std::cout << "SQDIFF_NORMED - Best match at (" << sqdiff_match.x << ", " << sqdiff_match.y 
              << ") with value: " << minVal << " (lower is better)" << std::endl;
    std::cout << "CCORR_NORMED - Best match at (" << ccorr_match.x << ", " << ccorr_match.y 
              << ") with value: " << maxVal << " (higher is better)" << std::endl;
    cv::minMaxLoc(result_ccoeff_normed, &minVal, &maxVal, &minLoc, &maxLoc);
    std::cout << "CCOEFF_NORMED - Best match at (" << ccoeff_match.x << ", " << ccoeff_match.y 
              << ") with value: " << maxVal << " (higher is better)" << std::endl;
    
    std::cout << "\nTemplate Matching Methods:" << std::endl;
    std::cout << "1. TM_SQDIFF_NORMED (Sum of Squared Differences):" << std::endl;
    std::cout << "   - Best for exact pixel matches" << std::endl;
    std::cout << "   - Sensitive to illumination changes" << std::endl;
    std::cout << "   - Lower values indicate better matches" << std::endl;
    
    std::cout << "\n2. TM_CCORR_NORMED (Normalized Cross Correlation):" << std::endl;
    std::cout << "   - Good for similar patterns with brightness changes" << std::endl;
    std::cout << "   - Robust to uniform lighting variations" << std::endl;
    std::cout << "   - Higher values indicate better matches" << std::endl;
    
    std::cout << "\n3. TM_CCOEFF_NORMED (Cross Correlation Coefficient):" << std::endl;
    std::cout << "   - Best overall method for template matching" << std::endl;
    std::cout << "   - Robust to both brightness and contrast changes" << std::endl;
    std::cout << "   - Higher values indicate better matches" << std::endl;
    
    std::cout << "\nHeatmap Visualization:" << std::endl;
    std::cout << "- Bright areas = high correlation (good matches)" << std::endl;
    std::cout << "- Dark areas = low correlation (poor matches)" << std::endl;
    std::cout << "- Shows correlation scores across the entire image" << std::endl;
    std::cout << "- Helps understand where matches are likely to occur" << std::endl;
    
    std::cout << "\nMathematical Concepts:" << std::endl;
    std::cout << "- Correlation: Measures similarity between template and image regions" << std::endl;
    std::cout << "- Normalization: Scales values to standard range for comparison" << std::endl;
    std::cout << "- Peak Detection: Finding maximum/minimum values in correlation maps" << std::endl;
    std::cout << "- Template Matching: Sliding window approach across the entire image" << std::endl;
    
    std::cout << "\nKey Learning Points:" << std::endl;
    std::cout << "- Different methods have different strengths and weaknesses" << std::endl;
    std::cout << "- Normalized methods are more robust to illumination changes" << std::endl;
    std::cout << "- CCOEFF is generally the most reliable method" << std::endl;
    std::cout << "- Template matching is computationally expensive for large images" << std::endl;
    std::cout << "- Heatmaps provide valuable insight into matching performance" << std::endl;
    
    std::cout << "\nApplications:" << std::endl;
    std::cout << "- Object detection and recognition" << std::endl;
    std::cout << "- Face detection and tracking" << std::endl;
    std::cout << "- Medical image analysis" << std::endl;
    std::cout << "- Quality control in manufacturing" << std::endl;
    std::cout << "- Document analysis and OCR" << std::endl;
    std::cout << "- Augmented reality" << std::endl;
    std::cout << "- Robotics and autonomous navigation" << std::endl;
    std::cout << "- Video surveillance" << std::endl;
    
    std::cout << "\nPress any key to close..." << std::endl;
    cv::waitKey(0);  // Wait for user input before closing
    cv::destroyAllWindows();  // Clean up all windows
    
    return 0;  // Successful program termination
}
