/**
 * 10_histogram_analysis.cpp
 * Intermediate Level - Histogram Analysis
 * 
 * This program demonstrates histogram calculation and analysis in computer vision.
 * Histograms are fundamental tools for understanding image characteristics,
 * analyzing pixel intensity distributions, and improving image contrast.
 * 
 * LEARNING OBJECTIVES:
 * 1. Understand what histograms are and how they represent image data
 * 2. Learn to calculate histograms for grayscale and color images
 * 3. Explore histogram equalization for contrast enhancement
 * 4. Study histogram statistics (mean, standard deviation)
 * 5. Understand histogram visualization techniques
 * 6. Learn about color channel analysis
 * 
 * KEY CONCEPTS:
 * - Histogram: Graphical representation of pixel intensity distribution
 * - Bins: Discrete intervals that group pixel values
 * - Histogram Equalization: Technique to improve image contrast
 * - Color Channels: Separate intensity distributions for each color component
 * - Statistics: Mean, standard deviation, and other descriptive measures
 * - Normalization: Scaling histogram values for visualization
 * 
 * HISTOGRAM APPLICATIONS:
 * - Image quality assessment
 * - Contrast enhancement
 * - Image segmentation
 * - Feature extraction
 * - Color analysis
 * - Threshold selection
 * - Image matching and comparison
 * 
 * MATHEMATICAL FOUNDATION:
 * - Histogram: H(i) = number of pixels with intensity value i
 * - Cumulative Distribution Function (CDF): CDF(i) = Σ H(j) for j=0 to i
 * - Histogram Equalization: s = T(r) = (L-1) * CDF(r)
 * - Statistics: Mean = Σ(i * H(i)) / total_pixels, Variance = Σ(i-μ)² * H(i)
 */

#include <iostream>    // For console input/output
#include <opencv2/opencv.hpp>  // Main OpenCV library

/**
 * DRAW HISTOGRAM FUNCTION:
 * 
 * This function visualizes a histogram by drawing bars on an image.
 * It normalizes the histogram values to fit within the image dimensions
 * and draws lines to represent the histogram bars.
 * 
 * Parameters:
 * - hist: Input histogram data (1D array of bin counts)
 * - histImage: Output image where histogram will be drawn
 * - color: Color to use for drawing the histogram bars
 */
void drawHistogram(const cv::Mat& hist, cv::Mat& histImage, const cv::Scalar& color) {
    /**
     * NORMALIZE HISTOGRAM:
     * 
     * Scale the histogram values to fit within the image height.
     * This ensures the histogram is visible regardless of the actual
     * pixel count values in the histogram.
     */
    cv::Mat normalizedHist;
    cv::normalize(hist, normalizedHist, 0, histImage.rows, cv::NORM_MINMAX);
    
    /**
     * DRAW HISTOGRAM BARS:
     * 
     * Draw lines connecting consecutive histogram bins to create
     * a bar chart representation of the histogram.
     * 
     * - binWidth: Width of each histogram bar in pixels
     * - For each bin, draw a line from the previous bin to the current bin
     * - Y-coordinate is inverted (image.rows - value) because image origin is top-left
     */
    int binWidth = histImage.cols / hist.rows;
    for (int i = 1; i < hist.rows; i++) {
        cv::line(histImage,
                cv::Point(binWidth * (i - 1), histImage.rows - normalizedHist.at<float>(i - 1)),
                cv::Point(binWidth * i, histImage.rows - normalizedHist.at<float>(i)),
                color, 2, 8, 0);  // color, thickness, line type, shift
    }
}

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
     * STEP 2: PREPARE IMAGE DATA FOR HISTOGRAM ANALYSIS
     * 
     * For comprehensive histogram analysis, we need:
     * 1. Individual color channels (BGR)
     * 2. Grayscale version for intensity analysis
     */
    
    // Split image into individual color channels
    std::vector<cv::Mat> channels;
    cv::split(original, channels);  // channels[0]=Blue, channels[1]=Green, channels[2]=Red
    
    // Convert to grayscale for intensity histogram analysis
    cv::Mat gray;
    cv::cvtColor(original, gray, cv::COLOR_BGR2GRAY);
    
    /**
     * STEP 3: SETUP HISTOGRAM PARAMETERS
     * 
     * These parameters control how the histogram is calculated:
     * - histSize: Number of bins (256 for 8-bit images)
     * - range: Range of pixel values (0-255 for 8-bit images)
     * - uniform: Whether bins are uniformly spaced
     * - accumulate: Whether to accumulate across multiple images
     */
    int histSize = 256;        // Number of histogram bins (one for each intensity level)
    float range[] = {0, 256};  // Range of pixel values
    const float* histRange = {range};
    bool uniform = true;       // Uniform bin spacing
    bool accumulate = false;   // Don't accumulate across multiple images
    
    /**
     * STEP 4: CALCULATE HISTOGRAMS
     * 
     * We'll calculate histograms for:
     * 1. Grayscale image (overall intensity distribution)
     * 2. Individual color channels (B, G, R distributions)
     */
    
    // Calculate grayscale histogram
    cv::Mat grayHist;
    cv::calcHist(&gray, 1, 0, cv::Mat(), grayHist, 1, &histSize, &histRange, uniform, accumulate);
    
    /**
     * CALCULATE COLOR CHANNEL HISTOGRAMS:
     * 
     * Each color channel (Blue, Green, Red) has its own intensity distribution.
     * This helps understand the color composition of the image.
     */
    cv::Mat bHist, gHist, rHist;
    cv::calcHist(&channels[0], 1, 0, cv::Mat(), bHist, 1, &histSize, &histRange, uniform, accumulate);  // Blue channel
    cv::calcHist(&channels[1], 1, 0, cv::Mat(), gHist, 1, &histSize, &histRange, uniform, accumulate);  // Green channel
    cv::calcHist(&channels[2], 1, 0, cv::Mat(), rHist, 1, &histSize, &histRange, uniform, accumulate);  // Red channel
    
    /**
     * STEP 5: CREATE HISTOGRAM VISUALIZATIONS
     * 
     * We'll create images to display the histograms graphically.
     * Each histogram will be drawn with different colors for easy identification.
     */
    
    // Define dimensions for histogram visualization images
    int histWidth = 512, histHeight = 400;
    
    // Create black background images for histogram display
    cv::Mat grayHistImage(histHeight, histWidth, CV_8UC3, cv::Scalar(20, 20, 20));   // Dark background
    cv::Mat colorHistImage(histHeight, histWidth, CV_8UC3, cv::Scalar(20, 20, 20)); // Dark background
    
    /**
     * DRAW HISTOGRAMS:
     * 
     * Use different colors for each histogram:
     * - Grayscale: White (255, 255, 255)
     * - Blue channel: Blue (255, 0, 0) - BGR format
     * - Green channel: Green (0, 255, 0)
     * - Red channel: Red (0, 0, 255)
     */
    drawHistogram(grayHist, grayHistImage, cv::Scalar(255, 255, 255));  // White for grayscale
    drawHistogram(bHist, colorHistImage, cv::Scalar(255, 0, 0));        // Blue for blue channel
    drawHistogram(gHist, colorHistImage, cv::Scalar(0, 255, 0));        // Green for green channel
    drawHistogram(rHist, colorHistImage, cv::Scalar(0, 0, 255));        // Red for red channel
    
    /**
     * ADD DESCRIPTIVE LABELS:
     * 
     * Add text labels to help students understand what each histogram represents.
     */
    cv::putText(grayHistImage, "Grayscale Histogram", cv::Point(10, 30), 
               cv::FONT_HERSHEY_SIMPLEX, 0.7, cv::Scalar(255, 255, 255), 2);
    cv::putText(colorHistImage, "Color Histograms (B-G-R)", cv::Point(10, 30), 
               cv::FONT_HERSHEY_SIMPLEX, 0.7, cv::Scalar(255, 255, 255), 2);
    
    /**
     * STEP 6: HISTOGRAM EQUALIZATION
     * 
     * Histogram equalization is a technique to improve image contrast by
     * redistributing pixel intensities to use the full dynamic range.
     * 
     * How it works:
     * 1. Calculate the cumulative distribution function (CDF) of the histogram
     * 2. Use the CDF as a transformation function to redistribute intensities
     * 3. Result: More uniform distribution of pixel intensities
     */
    cv::Mat equalized;
    cv::equalizeHist(gray, equalized);
    
    /**
     * CALCULATE EQUALIZED HISTOGRAM:
     * 
     * Calculate the histogram of the equalized image to show the
     * difference in intensity distribution after equalization.
     */
    cv::Mat equalizedHist;
    cv::calcHist(&equalized, 1, 0, cv::Mat(), equalizedHist, 1, &histSize, &histRange, uniform, accumulate);
    
    /**
     * VISUALIZE EQUALIZED HISTOGRAM:
     * 
     * Draw the equalized histogram in cyan color to distinguish it
     * from the original histogram.
     */
    cv::Mat equalizedHistImage(histHeight, histWidth, CV_8UC3, cv::Scalar(20, 20, 20));
    drawHistogram(equalizedHist, equalizedHistImage, cv::Scalar(0, 255, 255));  // Cyan for equalized
    cv::putText(equalizedHistImage, "Equalized Histogram", cv::Point(10, 30), 
               cv::FONT_HERSHEY_SIMPLEX, 0.7, cv::Scalar(255, 255, 255), 2);
    
    /**
     * STEP 7: CALCULATE HISTOGRAM STATISTICS
     * 
     * Statistical analysis helps quantify the characteristics of the image
     * and the effects of histogram equalization.
     * 
     * Key statistics:
     * - Mean: Average pixel intensity (indicates overall brightness)
     * - Standard Deviation: Measure of intensity variation (indicates contrast)
     */
    cv::Scalar grayMean, grayStddev;
    cv::meanStdDev(gray, grayMean, grayStddev);
    
    cv::Scalar equalizedMean, equalizedStddev;
    cv::meanStdDev(equalized, equalizedMean, equalizedStddev);
    
    /**
     * STEP 8: PREPARE IMAGES FOR DISPLAY
     * 
     * Convert grayscale images to 3-channel BGR format for consistent
     * display alongside color images and histograms.
     */
    cv::Mat gray_color, equalized_color;
    cv::cvtColor(gray, gray_color, cv::COLOR_GRAY2BGR);
    cv::cvtColor(equalized, equalized_color, cv::COLOR_GRAY2BGR);
    
    /**
     * STEP 9: STANDARDIZE IMAGE SIZES FOR DISPLAY
     * 
     * All images must have the same dimensions for concatenation.
     * We'll resize all images to a consistent size.
     */
    cv::Size target_size(300, 200);  // Standard size for each image
    cv::Mat gray_color_resized, equalized_color_resized, grayHistImage_resized;
    cv::Mat colorHistImage_resized, equalizedHistImage_resized, original_resized;
    
    // Resize all images to the target size
    cv::resize(gray_color, gray_color_resized, target_size);
    cv::resize(equalized_color, equalized_color_resized, target_size);
    cv::resize(grayHistImage, grayHistImage_resized, target_size);
    cv::resize(colorHistImage, colorHistImage_resized, target_size);
    cv::resize(equalizedHistImage, equalizedHistImage_resized, target_size);
    cv::resize(original, original_resized, target_size);
    
    /**
     * STEP 10: CREATE DISPLAY LAYOUT
     * 
     * Arrange images in a 3x2 grid layout:
     * - Top row: Grayscale, Equalized, Grayscale Histogram
     * - Bottom row: Color Histograms, Equalized Histogram, Original
     */
    cv::Mat topRow, bottomRow, display;
    cv::hconcat(std::vector<cv::Mat>{gray_color_resized, equalized_color_resized, grayHistImage_resized}, topRow);
    cv::hconcat(std::vector<cv::Mat>{colorHistImage_resized, equalizedHistImage_resized, original_resized}, bottomRow);
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
     * - Show the combined grid of all histogram analysis results
     * - Window title helps identify the application
     */
    cv::imshow("Histogram Analysis", display);
    
    /**
     * EDUCATIONAL OUTPUT:
     * - Print detailed information about histogram analysis
     * - Help students understand what they're seeing
     * - Explain statistical concepts and histogram interpretation
     */
    std::cout << "Histogram Analysis Results (displayed in 3x2 grid):" << std::endl;
    std::cout << "Top row: Grayscale image, Equalized image, Grayscale histogram" << std::endl;
    std::cout << "Bottom row: Color histograms (B-G-R), Equalized histogram, Original image" << std::endl;
    
    // Print statistical comparison
    std::cout << "\nStatistical Comparison:" << std::endl;
    std::cout << "Original image - Mean: " << grayMean[0] << ", Std Dev: " << grayStddev[0] << std::endl;
    std::cout << "Equalized image - Mean: " << equalizedMean[0] << ", Std Dev: " << equalizedStddev[0] << std::endl;
    
    std::cout << "\nHistogram Interpretation:" << std::endl;
    std::cout << "- Left side (low values): Dark regions of the image" << std::endl;
    std::cout << "- Right side (high values): Bright regions of the image" << std::endl;
    std::cout << "- Peak heights: Number of pixels with that intensity" << std::endl;
    std::cout << "- Histogram shape reveals image characteristics" << std::endl;
    
    std::cout << "\nColor Channel Analysis:" << std::endl;
    std::cout << "- Blue histogram: Distribution of blue channel intensities" << std::endl;
    std::cout << "- Green histogram: Distribution of green channel intensities" << std::endl;
    std::cout << "- Red histogram: Distribution of red channel intensities" << std::endl;
    std::cout << "- Channel dominance can indicate color bias in the image" << std::endl;
    
    std::cout << "\nHistogram Equalization Effects:" << std::endl;
    std::cout << "- Spreads histogram across the full intensity range (0-255)" << std::endl;
    std::cout << "- Improves contrast by using more intensity levels" << std::endl;
    std::cout << "- Makes dark areas lighter and light areas darker" << std::endl;
    std::cout << "- Results in more uniform intensity distribution" << std::endl;
    
    std::cout << "\nMathematical Concepts:" << std::endl;
    std::cout << "- Histogram: H(i) = number of pixels with intensity i" << std::endl;
    std::cout << "- Cumulative Distribution Function: CDF(i) = Σ H(j) for j=0 to i" << std::endl;
    std::cout << "- Equalization: s = T(r) = (L-1) * CDF(r), where L=256" << std::endl;
    std::cout << "- Mean: μ = Σ(i * H(i)) / total_pixels" << std::endl;
    std::cout << "- Standard Deviation: σ = sqrt(Σ(i-μ)² * H(i) / total_pixels)" << std::endl;
    
    std::cout << "\nKey Learning Points:" << std::endl;
    std::cout << "- Histograms reveal the intensity distribution of images" << std::endl;
    std::cout << "- Narrow histograms indicate low contrast" << std::endl;
    std::cout << "- Wide histograms indicate good contrast" << std::endl;
    std::cout << "- Equalization can improve contrast but may over-enhance" << std::endl;
    std::cout << "- Color histograms help understand color composition" << std::endl;
    std::cout << "- Statistics quantify image characteristics numerically" << std::endl;
    
    std::cout << "\nApplications:" << std::endl;
    std::cout << "- Image quality assessment and enhancement" << std::endl;
    std::cout << "- Contrast improvement and normalization" << std::endl;
    std::cout << "- Image segmentation and threshold selection" << std::endl;
    std::cout << "- Feature extraction and image matching" << std::endl;
    std::cout << "- Color analysis and color space conversion" << std::endl;
    std::cout << "- Medical image analysis" << std::endl;
    std::cout << "- Photography and image editing" << std::endl;
    std::cout << "- Computer vision preprocessing" << std::endl;
    
    std::cout << "\nPress any key to close..." << std::endl;
    cv::waitKey(0);  // Wait for user input before closing
    cv::destroyAllWindows();  // Clean up all windows
    
    return 0;  // Successful program termination
}
