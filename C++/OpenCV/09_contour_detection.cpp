/**
 * 09_contour_detection.cpp
 * Intermediate Level - Contour Detection and Analysis
 * 
 * This program demonstrates contour detection and shape analysis in computer vision.
 * Contours are the boundaries of objects in images and are fundamental for
 * shape recognition, object detection, and image analysis.
 * 
 * LEARNING OBJECTIVES:
 * 1. Understand what contours are and how they're detected
 * 2. Learn about contour hierarchy and retrieval modes
 * 3. Explore contour properties (area, perimeter, bounding boxes)
 * 4. Study shape analysis techniques (moments, centroids)
 * 5. Understand geometric measurements of objects
 * 6. Learn about contour approximation methods
 * 
 * KEY CONCEPTS:
 * - Contours: Boundaries of objects in binary images
 * - Hierarchy: Parent-child relationships between contours
 * - Moments: Statistical measures of shape distribution
 * - Centroid: Center of mass of a shape
 * - Bounding Box: Smallest rectangle enclosing a contour
 * - Convex Hull: Smallest convex shape containing all points
 * 
 * CONTOUR DETECTION PROCESS:
 * 1. Preprocess image (grayscale, blur, edge detection)
 * 2. Find contours using edge information
 * 3. Analyze contour properties
 * 4. Visualize results with geometric overlays
 * 
 * APPLICATIONS:
 * - Object detection and recognition
 * - Shape analysis and classification
 * - Medical image analysis (tumor detection)
 * - Quality control in manufacturing
 * - Hand gesture recognition
 * - Document analysis and OCR
 * - Robotics and autonomous navigation
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
     * STEP 2: IMAGE PREPROCESSING
     * 
     * Contour detection works on binary (edge) images, so we need to:
     * 1. Convert to grayscale (contours work on single-channel images)
     * 2. Reduce noise with blur
     * 3. Detect edges (contours are found from edge information)
     */
    
    // Convert to grayscale for contour detection
    cv::Mat gray;
    cv::cvtColor(original, gray, cv::COLOR_BGR2GRAY);
    
    /**
     * STEP 3: NOISE REDUCTION
     * 
     * Gaussian blur helps reduce noise that could create false contours.
     * Small kernel size (5x5) provides gentle smoothing without losing important edges.
     */
    cv::Mat blurred;
    cv::GaussianBlur(gray, blurred, cv::Size(5, 5), 0);
    
    /**
     * STEP 4: EDGE DETECTION
     * 
     * Canny edge detection finds the boundaries of objects.
     * Contours are detected from these edge maps.
     * 
     * Parameters:
     * - blurred: Input grayscale image
     * - edges: Output binary edge image
     * - 50: Lower threshold for weak edges
     * - 150: Upper threshold for strong edges
     */
    cv::Mat edges;
    cv::Canny(blurred, edges, 50, 150);
    
    /**
     * STEP 5: CONTOUR DETECTION
     * 
     * This is the core function that finds contours in the binary edge image.
     * 
     * Parameters:
     * - edges: Input binary image (edges)
     * - contours: Output vector of contours (each contour is a vector of points)
     * - hierarchy: Output hierarchy information (parent-child relationships)
     * - cv::RETR_EXTERNAL: Retrieval mode (only external contours)
     * - cv::CHAIN_APPROX_SIMPLE: Approximation method (compresses contours)
     * 
     * RETRIEVAL MODES:
     * - RETR_EXTERNAL: Only outermost contours
     * - RETR_LIST: All contours without hierarchy
     * - RETR_TREE: All contours with full hierarchy
     * 
     * APPROXIMATION METHODS:
     * - CHAIN_APPROX_SIMPLE: Compresses horizontal, vertical, and diagonal segments
     * - CHAIN_APPROX_NONE: Stores all boundary points
     */
    std::vector<std::vector<cv::Point>> contours;
    std::vector<cv::Vec4i> hierarchy;
    cv::findContours(edges, contours, hierarchy, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);
    
    /**
     * STEP 6: CREATE OUTPUT IMAGES
     * 
     * We'll create two output images:
     * 1. contour_image: Shows all detected contours
     * 2. analysis_image: Shows detailed analysis with bounding boxes and centroids
     */
    cv::Mat contour_image = original.clone();
    cv::Mat analysis_image = original.clone();
    
    /**
     * STEP 7: DRAW ALL CONTOURS
     * 
     * Draw all detected contours on the image for visualization.
     * 
     * Parameters:
     * - contour_image: Image to draw on
     * - contours: Vector of contours to draw
     * - -1: Draw all contours (if positive, draws specific contour index)
     * - cv::Scalar(0, 255, 0): Color (green in BGR format)
     * - 2: Thickness of contour lines
     */
    cv::drawContours(contour_image, contours, -1, cv::Scalar(0, 255, 0), 2);
    
    // Print total number of contours found
    std::cout << "Found " << contours.size() << " contours" << std::endl;
    
    /**
     * STEP 8: CONTOUR ANALYSIS
     * 
     * For each detected contour, we'll calculate various geometric properties
     * and draw analysis overlays on the image.
     */
    for (size_t i = 0; i < contours.size(); i++) {
        /**
         * AREA CALCULATION:
         * 
         * Contour area is calculated using the Green's theorem.
         * It's the actual area enclosed by the contour.
         * Useful for filtering out noise and small objects.
         */
        double area = cv::contourArea(contours[i]);
        
        // Skip small contours (likely noise)
        if (area < 100) continue;
        
        /**
         * PERIMETER CALCULATION:
         * 
         * Arc length calculates the perimeter of the contour.
         * The 'true' parameter indicates the contour is closed.
         */
        double perimeter = cv::arcLength(contours[i], true);
        
        /**
         * BOUNDING RECTANGLE:
         * 
         * Returns the smallest upright rectangle that contains the contour.
         * Useful for object localization and collision detection.
         */
        cv::Rect boundingRect = cv::boundingRect(contours[i]);
        
        /**
         * MINIMUM AREA RECTANGLE:
         * 
         * Returns the smallest rotated rectangle that contains the contour.
         * More precise than bounding rectangle, accounts for object orientation.
         */
        cv::RotatedRect minRect = cv::minAreaRect(contours[i]);
        
        /**
         * VISUALIZATION: BOUNDING RECTANGLE
         * 
         * Draw blue rectangle around the object for localization visualization.
         */
        cv::rectangle(analysis_image, boundingRect, cv::Scalar(255, 0, 0), 2);
        
        /**
         * VISUALIZATION: MINIMUM AREA RECTANGLE
         * 
         * Draw red rotated rectangle showing the minimum area bounding box.
         * This accounts for object orientation.
         */
        cv::Point2f rectPoints[4];
        minRect.points(rectPoints);  // Get 4 corner points of rotated rectangle
        for (int j = 0; j < 4; j++) {
            // Draw lines connecting the 4 corners
            cv::line(analysis_image, rectPoints[j], rectPoints[(j + 1) % 4], 
                    cv::Scalar(0, 0, 255), 2);
        }
        
        /**
         * CENTROID CALCULATION USING MOMENTS:
         * 
         * Image moments are statistical measures that describe the shape.
         * They're used to calculate the centroid (center of mass).
         * 
         * Mathematical formulas:
         * - m00: Zero-order moment (area)
         * - m10: First-order moment (x-coordinate weighted by intensity)
         * - m01: First-order moment (y-coordinate weighted by intensity)
         * - Centroid x = m10 / m00
         * - Centroid y = m01 / m00
         */
        cv::Moments moments = cv::moments(contours[i]);
        cv::Point centroid(moments.m10 / moments.m00, moments.m01 / moments.m00);
        
        /**
         * VISUALIZATION: CENTROID
         * 
         * Draw yellow circle at the centroid location.
         * The centroid represents the "center of mass" of the object.
         */
        cv::circle(analysis_image, centroid, 5, cv::Scalar(255, 255, 0), -1);
        
        /**
         * TEXT ANNOTATION:
         * 
         * Add text labels showing the area of each contour.
         * This helps in understanding the size distribution of objects.
         */
        std::string text = "Area: " + std::to_string((int)area);
        cv::putText(analysis_image, text, 
                   cv::Point(boundingRect.x, boundingRect.y - 10),
                   cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(255, 255, 255), 1);
        
        // Print detailed analysis to console
        std::cout << "Contour " << i << ": Area=" << area 
                  << ", Perimeter=" << perimeter << std::endl;
    }
    
    /**
     * STEP 9: PREPARE IMAGES FOR DISPLAY
     * 
     * To create a uniform display, we need to:
     * 1. Convert single-channel images to 3-channel for consistent display
     * 2. Resize all images to the same dimensions
     * 3. Arrange them in a 2x2 grid layout
     */
    
    // Convert grayscale edge image to BGR for display
    cv::Mat edges_color;
    cv::cvtColor(edges, edges_color, cv::COLOR_GRAY2BGR);
    
    /**
     * STANDARDIZE IMAGE SIZES:
     * - All images must have the same dimensions for concatenation
     * - We choose 400x300 as a reasonable size for each image in the grid
     * - This creates a total display size of 800x600 (2x2 images)
     */
    cv::Size target_size(400, 300);  // Standard size for each image
    cv::Mat original_resized, edges_color_resized, contour_image_resized, analysis_image_resized;
    
    // Resize all images to the target size
    cv::resize(original, original_resized, target_size);
    cv::resize(edges_color, edges_color_resized, target_size);
    cv::resize(contour_image, contour_image_resized, target_size);
    cv::resize(analysis_image, analysis_image_resized, target_size);
    
    /**
     * CREATE GRID LAYOUT:
     * - Arrange images in a 2x2 grid (2 rows, 2 columns)
     * - Top row: Original image, Edge detection
     * - Bottom row: Contour detection, Detailed analysis
     * - Use hconcat for horizontal concatenation (rows)
     * - Use vconcat for vertical concatenation (columns)
     */
    cv::Mat topRow, bottomRow, display;
    
    // Top row: original, edges
    cv::hconcat(std::vector<cv::Mat>{original_resized, edges_color_resized}, topRow);
    
    // Bottom row: contours, analysis
    cv::hconcat(std::vector<cv::Mat>{contour_image_resized, analysis_image_resized}, bottomRow);
    
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
     * - Show the combined grid of all contour detection results
     * - Window title helps identify the application
     */
    cv::imshow("Contour Detection and Analysis", display);
    
    /**
     * EDUCATIONAL OUTPUT:
     * - Print detailed information about the display layout
     * - Help students understand what they're seeing
     * - Explain the analysis techniques and color coding
     */
    std::cout << "\nContour Analysis (displayed in 2x2 grid):" << std::endl;
    std::cout << "Top-left: Original image - Reference image before processing" << std::endl;
    std::cout << "Top-right: Edge detection - Canny edge detection results" << std::endl;
    std::cout << "Bottom-left: All contours (green) - Detected object boundaries" << std::endl;
    std::cout << "Bottom-right: Analysis with bounding boxes (blue), min area rects (red), centroids (yellow)" << std::endl;
    
    std::cout << "\nContour Properties Analyzed:" << std::endl;
    std::cout << "- Area: Size of the enclosed region" << std::endl;
    std::cout << "- Perimeter: Length of the boundary" << std::endl;
    std::cout << "- Bounding Rectangle: Upright rectangle containing the object" << std::endl;
    std::cout << "- Minimum Area Rectangle: Rotated rectangle with smallest area" << std::endl;
    std::cout << "- Centroid: Center of mass of the object" << std::endl;
    
    std::cout << "\nColor Coding:" << std::endl;
    std::cout << "- Green: Detected contours (object boundaries)" << std::endl;
    std::cout << "- Blue: Bounding rectangles (object localization)" << std::endl;
    std::cout << "- Red: Minimum area rectangles (orientation-aware bounding)" << std::endl;
    std::cout << "- Yellow: Centroids (center of mass)" << std::endl;
    std::cout << "- White: Area labels (object size information)" << std::endl;
    
    std::cout << "\nKey Learning Points:" << std::endl;
    std::cout << "- Contours are the boundaries of objects in binary images" << std::endl;
    std::cout << "- Edge detection is the first step in contour detection" << std::endl;
    std::cout << "- Area filtering helps remove noise and small artifacts" << std::endl;
    std::cout << "- Geometric properties provide shape descriptors" << std::endl;
    std::cout << "- Moments are powerful tools for shape analysis" << std::endl;
    std::cout << "- Different bounding rectangles serve different purposes" << std::endl;
    
    std::cout << "\nApplications:" << std::endl;
    std::cout << "- Object detection and recognition" << std::endl;
    std::cout << "- Shape analysis and classification" << std::endl;
    std::cout << "- Quality control in manufacturing" << std::endl;
    std::cout << "- Medical image analysis" << std::endl;
    std::cout << "- Hand gesture recognition" << std::endl;
    std::cout << "- Document analysis and OCR" << std::endl;
    
    std::cout << "\nPress any key to close..." << std::endl;
    cv::waitKey(0);  // Wait for user input before closing
    cv::destroyAllWindows();  // Clean up all windows
    
    return 0;  // Successful program termination
}
