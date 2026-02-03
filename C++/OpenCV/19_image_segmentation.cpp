/**
 * 19_image_segmentation.cpp
 * Advanced Level - Image Segmentation
 * 
 * This program demonstrates various image segmentation techniques used in computer vision.
 * Image segmentation is the process of dividing an image into meaningful regions or segments.
 * 
 * LEARNING OBJECTIVES:
 * 1. Understand different segmentation algorithms and their applications
 * 2. Learn about thresholding techniques (binary, Otsu, adaptive)
 * 3. Explore clustering-based segmentation (K-means)
 * 4. Study marker-based segmentation (Watershed)
 * 5. Understand interactive segmentation (GrabCut)
 * 6. Compare different methods and their use cases
 * 
 * KEY CONCEPTS:
 * - Segmentation: Dividing image into regions of interest
 * - Thresholding: Binary classification based on pixel intensity
 * - Clustering: Grouping similar pixels together
 * - Markers: Seed points for region growing algorithms
 * - Interactive segmentation: User-guided segmentation
 * 
 * APPLICATIONS:
 * - Medical imaging (tumor detection, organ segmentation)
 * - Object detection and recognition
 * - Background removal and foreground extraction
 * - Image analysis and feature extraction
 * - Quality control in manufacturing
 */

#include <iostream>    // For console input/output
#include <opencv2/opencv.hpp>  // Main OpenCV library

int main() {
    /**
     * STEP 1: IMAGE LOADING AND VALIDATION
     * 
     * We start by loading an image from disk. The cv::imread() function can handle
     * various image formats (JPEG, PNG, BMP, etc.). It returns a cv::Mat object,
     * which is OpenCV's primary data structure for images.
     */
    cv::Mat original = cv::imread("image.jpg");
    
    // Always check if the image loaded successfully
    // Empty images can cause crashes in subsequent operations
    if (original.empty()) {
        std::cout << "Error: Could not load image 'image.jpg'" << std::endl;
        std::cout << "Make sure the image file exists in the current directory" << std::endl;
        return -1;  // Exit with error code
    }
    
    /**
     * STEP 2: IMAGE PREPROCESSING
     * 
     * We resize the image to a standard size for consistent processing and display.
     * This helps with performance and makes it easier to create uniform layouts.
     */
    cv::Mat resized;
    cv::resize(original, resized, cv::Size(400, 300));
    
    /**
     * STEP 3: THRESHOLD SEGMENTATION
     * 
     * Thresholding is the simplest segmentation technique. It converts a grayscale
     * image to a binary image by setting pixels above/below a threshold to white/black.
     * 
     * WHY CONVERT TO GRAYSCALE FIRST?
     * - Thresholding works on single-channel (grayscale) images
     * - Color images have 3 channels (BGR), making thresholding more complex
     * - Grayscale reduces computational complexity
     */
    cv::Mat gray;
    cv::cvtColor(resized, gray, cv::COLOR_BGR2GRAY);  // Convert BGR to grayscale
    
    // Declare matrices to store different thresholding results
    cv::Mat binary, binary_inv, otsu, adaptive_mean, adaptive_gaussian;
    
    /**
     * BASIC THRESHOLDING:
     * - Simple threshold: All pixels > 127 become white (255), others become black (0)
     * - Binary inverse: Opposite of simple threshold
     * 
     * Parameters:
     * - gray: Input grayscale image
     * - binary: Output binary image
     * - 127: Threshold value (middle of 0-255 range)
     * - 255: Maximum value for pixels above threshold
     * - cv::THRESH_BINARY: Thresholding type
     */
    cv::threshold(gray, binary, 127, 255, cv::THRESH_BINARY);
    cv::threshold(gray, binary_inv, 127, 255, cv::THRESH_BINARY_INV);
    
    /**
     * OTSU THRESHOLDING:
     * - Automatically determines the optimal threshold value
     * - Minimizes intra-class variance and maximizes inter-class variance
     * - Works best with bimodal histograms (two peaks)
     * - No need to specify threshold value (set to 0)
     */
    cv::threshold(gray, otsu, 0, 255, cv::THRESH_BINARY + cv::THRESH_OTSU);
    
    /**
     * ADAPTIVE THRESHOLDING:
     * - Calculates threshold for small regions of the image
     * - Better for images with varying lighting conditions
     * - Two methods: MEAN_C (mean of neighborhood) and GAUSSIAN_C (weighted sum)
     * 
     * Parameters:
     * - gray: Input grayscale image
     * - adaptive_mean: Output image
     * - 255: Maximum value for pixels above threshold
     * - cv::ADAPTIVE_THRESH_MEAN_C: Adaptive method
     * - cv::THRESH_BINARY: Thresholding type
     * - 11: Size of neighborhood (must be odd number)
     * - 2: Constant subtracted from mean
     */
    cv::adaptiveThreshold(gray, adaptive_mean, 255, cv::ADAPTIVE_THRESH_MEAN_C, cv::THRESH_BINARY, 11, 2);
    cv::adaptiveThreshold(gray, adaptive_gaussian, 255, cv::ADAPTIVE_THRESH_GAUSSIAN_C, cv::THRESH_BINARY, 11, 2);
    
    /**
     * STEP 4: K-MEANS CLUSTERING SEGMENTATION
     * 
     * K-means clustering groups pixels with similar colors together.
     * It's useful for color-based segmentation and image quantization.
     * 
     * HOW K-MEANS WORKS:
     * 1. Choose k cluster centers randomly
     * 2. Assign each pixel to the nearest cluster center
     * 3. Update cluster centers to the mean of assigned pixels
     * 4. Repeat steps 2-3 until convergence
     * 
     * ADVANTAGES:
     * - Good for color-based segmentation
     * - Reduces color palette (quantization)
     * - Works well with natural images
     * 
     * DISADVANTAGES:
     * - Requires knowing the number of clusters (k)
     * - Sensitive to initialization
     * - Assumes spherical clusters
     */
    cv::Mat kmeans_result = resized.clone();
    
    /**
     * PREPARE DATA FOR K-MEANS:
     * - Reshape image from 2D (rows x cols x channels) to 1D (pixels x channels)
     * - Each row represents one pixel's BGR values
     * - Convert to float for mathematical operations
     */
    cv::Mat kmeans_data = resized.reshape(1, resized.rows * resized.cols);  // Flatten to 1D
    kmeans_data.convertTo(kmeans_data, CV_32F);  // Convert to float
    
    // Declare variables for k-means results
    cv::Mat labels;     // Cluster assignment for each pixel
    cv::Mat centers;    // Cluster center colors (BGR values)
    int k = 4;          // Number of clusters (can be adjusted)
    
    /**
     * PERFORM K-MEANS CLUSTERING:
     * 
     * Parameters:
     * - kmeans_data: Input data (pixels x channels)
     * - k: Number of clusters
     * - labels: Output cluster assignments
     * - cv::TermCriteria: Stopping criteria (max iterations, epsilon)
     * - 3: Number of attempts (runs k-means 3 times, picks best result)
     * - cv::KMEANS_PP_CENTERS: Initialization method (k-means++)
     * - centers: Output cluster centers
     */
    cv::kmeans(kmeans_data, k, labels, 
               cv::TermCriteria(cv::TermCriteria::EPS + cv::TermCriteria::MAX_ITER, 10, 1.0), 
               3, cv::KMEANS_PP_CENTERS, centers);
    
    /**
     * CREATE SEGMENTED IMAGE:
     * - Replace each pixel with its cluster center color
     * - This creates a quantized/segmented version of the original image
     */
    kmeans_result = cv::Mat::zeros(resized.size(), resized.type());
    
    // Use pointer arithmetic for efficient pixel access
    int* labels_ptr = labels.ptr<int>();      // Pointer to label array
    float* centers_ptr = centers.ptr<float>(); // Pointer to centers array
    
    // Iterate through each pixel and assign cluster color
    for (int i = 0; i < resized.rows; i++) {
        for (int j = 0; j < resized.cols; j++) {
            int pixel_idx = i * resized.cols + j;  // Linear index for flattened data
            int label = labels_ptr[pixel_idx];     // Get cluster label for this pixel
            
            if (label >= 0 && label < k) {  // Safety check
                // Get cluster center color (3 channels: BGR)
                float* center = centers_ptr + label * 3;
                kmeans_result.at<cv::Vec3b>(i, j) = cv::Vec3b(
                    static_cast<uchar>(center[0]),  // Blue channel
                    static_cast<uchar>(center[1]),  // Green channel
                    static_cast<uchar>(center[2])   // Red channel
                );
            }
        }
    }
    
    /**
     * STEP 5: WATERSHED ALGORITHM (SIMPLIFIED)
     * 
     * The watershed algorithm is based on the concept of flooding from markers.
     * It's useful for separating touching objects in images.
     * 
     * HOW WATERSHED WORKS:
     * 1. Start with markers (seed points) for each region
     * 2. "Flood" from markers until regions meet at watershed lines
     * 3. Watershed lines separate different regions
     * 
     * APPLICATIONS:
     * - Separating touching objects (cells, particles)
     * - Medical image segmentation
     * - Particle analysis
     * 
     * NOTE: This is a simplified version using distance transform visualization
     * instead of the full watershed algorithm for educational purposes.
     */
    cv::Mat watershed_colored = resized.clone();
    cv::Mat gray_watershed;
    cv::cvtColor(resized, gray_watershed, cv::COLOR_BGR2GRAY);  // Convert to grayscale
    
    /**
     * PREPROCESSING FOR WATERSHED:
     * - Apply Gaussian blur to reduce noise
     * - Use kernel size 5x5 for moderate smoothing
     * - Sigma = 0 means automatic calculation based on kernel size
     */
    cv::GaussianBlur(gray_watershed, gray_watershed, cv::Size(5, 5), 0);
    
    /**
     * THRESHOLDING:
     * - Use Otsu's method to automatically find threshold
     * - THRESH_BINARY_INV inverts the result (foreground becomes white)
     * - This creates a binary mask of foreground objects
     */
    cv::Mat thresh;
    cv::threshold(gray_watershed, thresh, 0, 255, cv::THRESH_BINARY_INV + cv::THRESH_OTSU);
    
    /**
     * MORPHOLOGICAL OPERATIONS FOR NOISE REMOVAL:
     * - MORPH_CLOSE: Fills small holes in objects
     * - MORPH_OPEN: Removes small noise pixels
     * - These operations clean up the binary image
     * 
     * Parameters:
     * - thresh: Input binary image
     * - thresh: Output (in-place operation)
     * - kernel: Structuring element (3x3 rectangle)
     * - cv::Point(-1, -1): Anchor point (center of kernel)
     * - 2: Number of iterations
     */
    cv::Mat kernel = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(3, 3));
    cv::morphologyEx(thresh, thresh, cv::MORPH_CLOSE, kernel, cv::Point(-1, -1), 2);
    cv::morphologyEx(thresh, thresh, cv::MORPH_OPEN, kernel, cv::Point(-1, -1), 2);
    
    /**
     * DISTANCE TRANSFORM:
     * - Calculates the distance from each pixel to the nearest boundary
     * - Creates a "height map" where peaks represent object centers
     * - Used to find markers for watershed algorithm
     * 
     * Parameters:
     * - thresh: Binary input image
     * - dist_transform: Output distance map
     * - cv::DIST_L2: Distance type (Euclidean distance)
     * - 5: Mask size for distance calculation
     */
    cv::Mat dist_transform;
    cv::distanceTransform(thresh, dist_transform, cv::DIST_L2, 5);
    
    /**
     * NORMALIZE AND CONVERT:
     * - Normalize distance transform to 0-255 range for visualization
     * - Convert to 8-bit unsigned integer for color mapping
     */
    cv::normalize(dist_transform, dist_transform, 0, 255, cv::NORM_MINMAX);
    dist_transform.convertTo(dist_transform, CV_8U);
    
    /**
     * CREATE COLORED VISUALIZATION:
     * - Apply color map to distance transform for better visualization
     * - COLORMAP_JET creates a rainbow-like color scheme
     * - Bright colors represent high values (object centers)
     * - Dark colors represent low values (object boundaries)
     */
    cv::Mat watershed_enhanced;
    cv::applyColorMap(dist_transform, watershed_enhanced, cv::COLORMAP_JET);
    watershed_colored = watershed_enhanced;
    
    /**
     * STEP 6: GRABCUT ALGORITHM
     * 
     * GrabCut is an interactive segmentation algorithm that separates
     * foreground from background using minimal user input.
     * 
     * HOW GRABCUT WORKS:
     * 1. User provides a rectangle around the object of interest
     * 2. Algorithm models foreground and background using Gaussian Mixture Models (GMM)
     * 3. Uses graph cuts to find the optimal segmentation
     * 4. Iteratively refines the segmentation
     * 
     * ADVANTAGES:
     * - Requires minimal user interaction
     * - Works well with complex backgrounds
     * - Good for foreground extraction
     * 
     * APPLICATIONS:
     * - Background removal
     * - Object extraction
     * - Photo editing
     * - Video processing
     */
    cv::Mat grabcut_result = resized.clone();
    cv::Mat mask, bgd_model, fgd_model;  // Output variables for GrabCut
    
    /**
     * DEFINE INITIAL RECTANGLE:
     * - User provides a rectangle that roughly contains the object
     * - Everything outside is considered background
     * - Everything inside is considered potential foreground
     * 
     * Parameters:
     * - rect(x, y, width, height): Rectangle coordinates
     * - We use a center region of the image as an example
     */
    cv::Rect rect(50, 50, resized.cols - 100, resized.rows - 100);
    
    /**
     * APPLY GRABCUT ALGORITHM:
     * 
     * Parameters:
     * - resized: Input image
     * - mask: Output segmentation mask
     * - rect: Initial rectangle
     * - bgd_model, fgd_model: Background and foreground models (output)
     * - 5: Number of iterations
     * - cv::GC_INIT_WITH_RECT: Initialization mode
     */
    cv::grabCut(resized, mask, rect, bgd_model, fgd_model, 5, cv::GC_INIT_WITH_RECT);
    
    /**
     * CREATE BINARY MASK:
     * - GrabCut returns a mask with 4 possible values:
     *   * GC_BGD (0): Definite background
     *   * GC_FGD (1): Definite foreground  
     *   * GC_PR_BGD (2): Probable background
     *   * GC_PR_FGD (3): Probable foreground
     * - We combine definite and probable foreground as our final mask
     */
    cv::Mat grabcut_mask = (mask == cv::GC_FGD) | (mask == cv::GC_PR_FGD);
    
    /**
     * APPLY MASK TO ORIGINAL IMAGE:
     * - Create a black image with the same size as input
     * - Copy only the foreground pixels from the original image
     * - This creates a foreground extraction result
     */
    cv::Mat grabcut_final = cv::Mat::zeros(resized.size(), resized.type());
    resized.copyTo(grabcut_final, grabcut_mask);
    
    /**
     * STEP 7: PREPARE IMAGES FOR DISPLAY
     * 
     * To display all results in a grid, we need to:
     * 1. Convert single-channel images to 3-channel (BGR) for consistent display
     * 2. Resize all images to the same size for uniform layout
     * 3. Arrange them in a 2x4 grid layout
     */
    
    // Convert grayscale images to BGR for display
    cv::Mat binary_color, binary_inv_color, otsu_color, adaptive_mean_color, adaptive_gaussian_color;
    cv::cvtColor(binary, binary_color, cv::COLOR_GRAY2BGR);
    cv::cvtColor(binary_inv, binary_inv_color, cv::COLOR_GRAY2BGR);
    cv::cvtColor(otsu, otsu_color, cv::COLOR_GRAY2BGR);
    cv::cvtColor(adaptive_mean, adaptive_mean_color, cv::COLOR_GRAY2BGR);
    cv::cvtColor(adaptive_gaussian, adaptive_gaussian_color, cv::COLOR_GRAY2BGR);
    
    /**
     * STANDARDIZE IMAGE SIZES:
     * - All images must have the same dimensions for concatenation
     * - We choose 200x150 as a reasonable size for each image in the grid
     * - This creates a total display size of 800x300 (4x2 images)
     */
    cv::Size target_size(200, 150);  // Standard size for each image
    cv::Mat resized_resized, binary_color_resized, otsu_color_resized, adaptive_mean_color_resized;
    cv::Mat adaptive_gaussian_color_resized, kmeans_result_resized, watershed_colored_resized, grabcut_final_resized;
    
    // Resize all images to the target size
    cv::resize(resized, resized_resized, target_size);
    cv::resize(binary_color, binary_color_resized, target_size);
    cv::resize(otsu_color, otsu_color_resized, target_size);
    cv::resize(adaptive_mean_color, adaptive_mean_color_resized, target_size);
    cv::resize(adaptive_gaussian_color, adaptive_gaussian_color_resized, target_size);
    cv::resize(kmeans_result, kmeans_result_resized, target_size);
    cv::resize(watershed_colored, watershed_colored_resized, target_size);
    cv::resize(grabcut_final, grabcut_final_resized, target_size);
    
    /**
     * CREATE GRID LAYOUT:
     * - Arrange images in a 2x4 grid (2 rows, 4 columns)
     * - Top row: Original, Binary, Otsu, Adaptive Mean
     * - Bottom row: Adaptive Gaussian, K-Means, Watershed, GrabCut
     * - Use hconcat for horizontal concatenation (rows)
     * - Use vconcat for vertical concatenation (columns)
     */
    cv::Mat topRow1, topRow2, display;
    
    // Top row: Original, Binary, Otsu, Adaptive Mean
    cv::hconcat(std::vector<cv::Mat>{resized_resized, binary_color_resized, otsu_color_resized, adaptive_mean_color_resized}, topRow1);
    
    // Bottom row: Adaptive Gaussian, K-Means, Watershed, GrabCut
    cv::hconcat(std::vector<cv::Mat>{adaptive_gaussian_color_resized, kmeans_result_resized, watershed_colored_resized, grabcut_final_resized}, topRow2);
    
    // Combine rows vertically
    cv::vconcat(topRow1, topRow2, display);
    
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
     * - Show the combined grid of all segmentation results
     * - Window title helps identify the application
     */
    cv::imshow("Image Segmentation", display);
    
    /**
     * EDUCATIONAL OUTPUT:
     * - Print detailed information about each technique
     * - Help students understand what they're seeing
     * - Explain applications and use cases
     */
    std::cout << "Image Segmentation Techniques:" << std::endl;
    std::cout << "1. Binary Threshold: Simple threshold at 127" << std::endl;
    std::cout << "2. Otsu Threshold: Automatic threshold selection" << std::endl;
    std::cout << "3. Adaptive Threshold: Local thresholding" << std::endl;
    std::cout << "4. K-Means Clustering: Color-based segmentation" << std::endl;
    std::cout << "5. Watershed Algorithm: Marker-based segmentation" << std::endl;
    std::cout << "6. GrabCut Algorithm: Interactive foreground extraction" << std::endl;
    
    std::cout << "\nSegmentation Applications:" << std::endl;
    std::cout << "- Medical imaging (tumor detection, organ segmentation)" << std::endl;
    std::cout << "- Object detection and recognition" << std::endl;
    std::cout << "- Background removal and foreground extraction" << std::endl;
    std::cout << "- Image analysis and feature extraction" << std::endl;
    std::cout << "- Quality control in manufacturing" << std::endl;
    std::cout << "- Autonomous vehicles (road detection)" << std::endl;
    
    std::cout << "\nKey Learning Points:" << std::endl;
    std::cout << "- Different algorithms work better for different types of images" << std::endl;
    std::cout << "- Thresholding is simple but limited to bimodal images" << std::endl;
    std::cout << "- K-means is good for color-based segmentation" << std::endl;
    std::cout << "- Watershed is excellent for separating touching objects" << std::endl;
    std::cout << "- GrabCut provides high-quality foreground extraction" << std::endl;
    
    std::cout << "\nPress any key to close..." << std::endl;
    cv::waitKey(0);  // Wait for user input before closing
    cv::destroyAllWindows();  // Clean up all windows
    
    return 0;  // Successful program termination
}
