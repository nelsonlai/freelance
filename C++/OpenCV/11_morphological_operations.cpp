/**
 * 11_morphological_operations.cpp
 * Intermediate Level - Morphological Operations
 * 
 * This program demonstrates morphological operations in computer vision.
 * Morphological operations are based on set theory and are used for
 * shape analysis, noise removal, and feature extraction in binary images.
 * 
 * LEARNING OBJECTIVES:
 * 1. Understand the fundamental concepts of mathematical morphology
 * 2. Learn about structuring elements and their role in morphological operations
 * 3. Explore basic operations: erosion and dilation
 * 4. Study compound operations: opening and closing
 * 5. Understand advanced operations: gradient, top-hat, and black-hat
 * 6. Compare different structuring element shapes and sizes
 * 
 * KEY CONCEPTS:
 * - Morphology: Study of shapes and structures
 * - Structuring Element: Small binary image used to probe the input image
 * - Erosion: Shrinks objects and removes small details
 * - Dilation: Expands objects and fills holes
 * - Opening: Erosion followed by dilation (removes noise)
 * - Closing: Dilation followed by erosion (fills gaps)
 * - Gradient: Edge detection using morphological operations
 * 
 * MATHEMATICAL FOUNDATION:
 * - Based on set theory and lattice theory
 * - Uses structuring elements to probe image structures
 * - Operations preserve the essential shape characteristics
 * - Particularly effective on binary images
 * 
 * STRUCTURING ELEMENT TYPES:
 * - Rectangular: Square kernel for general purpose
 * - Elliptical: Circular kernel for isotropic operations
 * - Cross: Cross-shaped kernel for directional operations
 * 
 * APPLICATIONS:
 * - Noise removal and image cleaning
 * - Object detection and segmentation
 * - Feature extraction and shape analysis
 * - Medical image processing
 * - Document analysis and OCR
 * - Quality control in manufacturing
 * - Handwriting recognition
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
     * Morphological operations work best on binary images, so we need to:
     * 1. Convert to grayscale (morphological operations work on single-channel images)
     * 2. Create a binary image using thresholding
     */
    
    // Convert to grayscale for morphological operations
    cv::Mat gray;
    cv::cvtColor(original, gray, cv::COLOR_BGR2GRAY);
    
    /**
     * STEP 3: CREATE BINARY IMAGE
     * 
     * Thresholding converts the grayscale image to binary (black and white).
     * This is essential for morphological operations which work on binary images.
     * 
     * Parameters:
     * - gray: Input grayscale image
     * - binary: Output binary image
     * - 127: Threshold value (middle of 0-255 range)
     * - 255: Maximum value for pixels above threshold
     * - cv::THRESH_BINARY: Thresholding type
     */
    cv::Mat binary;
    cv::threshold(gray, binary, 127, 255, cv::THRESH_BINARY);
    
    /**
     * STEP 4: CREATE STRUCTURING ELEMENTS
     * 
     * Structuring elements are small binary images used to probe the input image.
     * Different shapes and sizes produce different effects.
     * 
     * MORPH_RECT: Rectangular structuring element
     * - Creates square kernels
     * - Good for general purpose operations
     * - Preserves rectangular features
     * 
     * MORPH_ELLIPSE: Elliptical structuring element
     * - Creates circular kernels
     * - Better for isotropic operations
     * - Preserves circular features
     * 
     * MORPH_CROSS: Cross-shaped structuring element
     * - Creates cross-shaped kernels
     * - Useful for directional operations
     * - Preserves linear features
     */
    cv::Mat kernel3x3 = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(3, 3));
    cv::Mat kernel5x5 = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(5, 5));
    cv::Mat kernelEllipse = cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(5, 5));
    cv::Mat kernelCross = cv::getStructuringElement(cv::MORPH_CROSS, cv::Size(5, 5));
    
    /**
     * STEP 5: BASIC MORPHOLOGICAL OPERATIONS
     * 
     * EROSION:
     * - Shrinks objects and removes small details
     * - Removes noise and thin connections
     * - Makes objects smaller
     * - Mathematical definition: (A ⊖ B)(x,y) = min{A(x+i,y+j) | (i,j) ∈ B}
     * 
     * DILATION:
     * - Expands objects and fills holes
     * - Connects broken parts
     * - Makes objects larger
     * - Mathematical definition: (A ⊕ B)(x,y) = max{A(x+i,y+j) | (i,j) ∈ B}
     */
    
    // Erosion with different structuring elements
    cv::Mat eroded3x3, eroded5x5, erodedEllipse, erodedCross;
    cv::erode(binary, eroded3x3, kernel3x3);
    cv::erode(binary, eroded5x5, kernel5x5);
    cv::erode(binary, erodedEllipse, kernelEllipse);
    cv::erode(binary, erodedCross, kernelCross);
    
    // Dilation with different structuring elements
    cv::Mat dilated3x3, dilated5x5, dilatedEllipse, dilatedCross;
    cv::dilate(binary, dilated3x3, kernel3x3);
    cv::dilate(binary, dilated5x5, kernel5x5);
    cv::dilate(binary, dilatedEllipse, kernelEllipse);
    cv::dilate(binary, dilatedCross, kernelCross);
    
    /**
     * STEP 6: COMPOUND MORPHOLOGICAL OPERATIONS
     * 
     * OPENING (Erosion followed by Dilation):
     * - Removes noise and small objects
     * - Breaks thin connections
     * - Preserves the size of larger objects
     * - Mathematical definition: A ○ B = (A ⊖ B) ⊕ B
     * 
     * CLOSING (Dilation followed by Erosion):
     * - Fills holes and gaps
     * - Connects nearby objects
     * - Preserves the size of larger objects
     * - Mathematical definition: A ● B = (A ⊕ B) ⊖ B
     */
    
    // Opening: erosion followed by dilation
    cv::Mat opened;
    cv::morphologyEx(binary, opened, cv::MORPH_OPEN, kernel5x5);
    
    // Closing: dilation followed by erosion
    cv::Mat closed;
    cv::morphologyEx(binary, closed, cv::MORPH_CLOSE, kernel5x5);
    
    /**
     * STEP 7: ADVANCED MORPHOLOGICAL OPERATIONS
     * 
     * MORPHOLOGICAL GRADIENT:
     * - Edge detection using morphological operations
     * - Mathematical definition: Gradient = Dilation - Erosion
     * - Highlights object boundaries
     * 
     * TOP-HAT (White Top-Hat):
     * - Highlights bright objects smaller than the structuring element
     * - Mathematical definition: TopHat = Original - Opening
     * - Useful for detecting small bright features
     * 
     * BLACK-HAT:
     * - Highlights dark objects smaller than the structuring element
     * - Mathematical definition: BlackHat = Closing - Original
     * - Useful for detecting small dark features
     */
    
    // Morphological gradient: dilation - erosion
    cv::Mat gradient;
    cv::morphologyEx(binary, gradient, cv::MORPH_GRADIENT, kernel5x5);
    
    // Top-hat: original - opening
    cv::Mat topHat;
    cv::morphologyEx(binary, topHat, cv::MORPH_TOPHAT, kernel5x5);
    
    // Black-hat: closing - original
    cv::Mat blackHat;
    cv::morphologyEx(binary, blackHat, cv::MORPH_BLACKHAT, kernel5x5);
    
    /**
     * STEP 8: PREPARE IMAGES FOR DISPLAY
     * 
     * To create a uniform display, we need to:
     * 1. Convert single-channel images to 3-channel for consistent display
     * 2. Resize all images to the same dimensions
     * 3. Arrange them in a grid layout
     */
    
    // Convert grayscale images to BGR for display
    cv::Mat binary_color, eroded3x3_color, eroded5x5_color, dilated3x3_color, dilated5x5_color;
    cv::Mat erodedEllipse_color, erodedCross_color, opened_color, closed_color;
    cv::Mat gradient_color, topHat_color, blackHat_color;
    
    cv::cvtColor(binary, binary_color, cv::COLOR_GRAY2BGR);
    cv::cvtColor(eroded3x3, eroded3x3_color, cv::COLOR_GRAY2BGR);
    cv::cvtColor(eroded5x5, eroded5x5_color, cv::COLOR_GRAY2BGR);
    cv::cvtColor(dilated3x3, dilated3x3_color, cv::COLOR_GRAY2BGR);
    cv::cvtColor(dilated5x5, dilated5x5_color, cv::COLOR_GRAY2BGR);
    cv::cvtColor(erodedEllipse, erodedEllipse_color, cv::COLOR_GRAY2BGR);
    cv::cvtColor(erodedCross, erodedCross_color, cv::COLOR_GRAY2BGR);
    cv::cvtColor(opened, opened_color, cv::COLOR_GRAY2BGR);
    cv::cvtColor(closed, closed_color, cv::COLOR_GRAY2BGR);
    cv::cvtColor(gradient, gradient_color, cv::COLOR_GRAY2BGR);
    cv::cvtColor(topHat, topHat_color, cv::COLOR_GRAY2BGR);
    cv::cvtColor(blackHat, blackHat_color, cv::COLOR_GRAY2BGR);
    
    /**
     * STANDARDIZE IMAGE SIZES:
     * - All images must have the same dimensions for concatenation
     * - We choose 300x200 as a reasonable size for each image in the grid
     * - This creates a consistent display layout
     */
    cv::Size target_size(300, 200);  // Standard size for each image
    cv::Mat original_resized, binary_color_resized, eroded3x3_color_resized, eroded5x5_color_resized;
    cv::Mat dilated3x3_color_resized, dilated5x5_color_resized, erodedEllipse_color_resized, erodedCross_color_resized;
    cv::Mat opened_color_resized, closed_color_resized, gradient_color_resized, topHat_color_resized, blackHat_color_resized;
    
    cv::resize(original, original_resized, target_size);
    cv::resize(binary_color, binary_color_resized, target_size);
    cv::resize(eroded3x3_color, eroded3x3_color_resized, target_size);
    cv::resize(eroded5x5_color, eroded5x5_color_resized, target_size);
    cv::resize(dilated3x3_color, dilated3x3_color_resized, target_size);
    cv::resize(dilated5x5_color, dilated5x5_color_resized, target_size);
    cv::resize(erodedEllipse_color, erodedEllipse_color_resized, target_size);
    cv::resize(erodedCross_color, erodedCross_color_resized, target_size);
    cv::resize(opened_color, opened_color_resized, target_size);
    cv::resize(closed_color, closed_color_resized, target_size);
    cv::resize(gradient_color, gradient_color_resized, target_size);
    cv::resize(topHat_color, topHat_color_resized, target_size);
    cv::resize(blackHat_color, blackHat_color_resized, target_size);
    
    // Create display layout - 3x4 grid (12 images total)
    cv::Mat topRow1, topRow2, middleRow, bottomRow, display;
    
    // Top row 1: Original, Binary, Eroded 3x3, Eroded 5x5
    cv::hconcat(std::vector<cv::Mat>{original_resized, binary_color_resized, eroded3x3_color_resized, eroded5x5_color_resized}, topRow1);
    
    // Top row 2: Dilated 3x3, Dilated 5x5, Ellipse Erosion, Cross Erosion
    cv::hconcat(std::vector<cv::Mat>{dilated3x3_color_resized, dilated5x5_color_resized, erodedEllipse_color_resized, erodedCross_color_resized}, topRow2);
    
    // Middle row: Opening, Closing, Gradient, Top Hat
    cv::hconcat(std::vector<cv::Mat>{opened_color_resized, closed_color_resized, gradient_color_resized, topHat_color_resized}, middleRow);
    
    // Bottom row: Black Hat only (center it by adding empty spaces)
    cv::Mat empty = cv::Mat::zeros(target_size, CV_8UC3);
    cv::hconcat(std::vector<cv::Mat>{empty, blackHat_color_resized, empty, empty}, bottomRow);
    
    // Combine all rows
    cv::vconcat(std::vector<cv::Mat>{topRow1, topRow2, middleRow, bottomRow}, display);
    
    // Resize if too large
    if (display.cols > 1400 || display.rows > 1000) {
        double scale = std::min(1400.0 / display.cols, 1000.0 / display.rows);
        cv::resize(display, display, cv::Size(), scale, scale);
    }
    
    /**
     * DISPLAY RESULTS:
     * - Show the combined grid of all morphological operations
     * - Window title helps identify the application
     */
    cv::imshow("Morphological Operations", display);
    
    /**
     * EDUCATIONAL OUTPUT:
     * - Print detailed information about each operation
     * - Help students understand what they're seeing
     * - Explain the mathematical concepts and applications
     */
    std::cout << "Morphological Operations (displayed in 4x4 grid):" << std::endl;
    std::cout << "Row 1: Original, Binary, Erosion (3x3), Erosion (5x5)" << std::endl;
    std::cout << "Row 2: Dilation (3x3), Dilation (5x5), Ellipse Erosion, Cross Erosion" << std::endl;
    std::cout << "Row 3: Opening, Closing, Gradient, Top-Hat" << std::endl;
    std::cout << "Row 4: Black-Hat (with empty spaces for layout)" << std::endl;
    
    std::cout << "\nOperation Effects:" << std::endl;
    std::cout << "1. Erosion: Shrinks objects, removes noise and small details" << std::endl;
    std::cout << "2. Dilation: Expands objects, fills holes and gaps" << std::endl;
    std::cout << "3. Opening: Erosion + Dilation (removes noise, breaks connections)" << std::endl;
    std::cout << "4. Closing: Dilation + Erosion (fills gaps, connects objects)" << std::endl;
    std::cout << "5. Gradient: Edge detection using morphological operations" << std::endl;
    std::cout << "6. Top-Hat: Highlights bright regions smaller than structuring element" << std::endl;
    std::cout << "7. Black-Hat: Highlights dark regions smaller than structuring element" << std::endl;
    
    std::cout << "\nStructuring Element Types:" << std::endl;
    std::cout << "- Rectangular (3x3, 5x5): Square kernel, general purpose operations" << std::endl;
    std::cout << "- Elliptical: Circular kernel, better for isotropic operations" << std::endl;
    std::cout << "- Cross: Cross-shaped kernel, useful for directional operations" << std::endl;
    
    std::cout << "\nMathematical Concepts:" << std::endl;
    std::cout << "- Based on set theory and lattice theory" << std::endl;
    std::cout << "- Erosion: (A ⊖ B)(x,y) = min{A(x+i,y+j) | (i,j) ∈ B}" << std::endl;
    std::cout << "- Dilation: (A ⊕ B)(x,y) = max{A(x+i,y+j) | (i,j) ∈ B}" << std::endl;
    std::cout << "- Opening: A ○ B = (A ⊖ B) ⊕ B" << std::endl;
    std::cout << "- Closing: A ● B = (A ⊕ B) ⊖ B" << std::endl;
    std::cout << "- Gradient: Dilation - Erosion" << std::endl;
    std::cout << "- Top-Hat: Original - Opening" << std::endl;
    std::cout << "- Black-Hat: Closing - Original" << std::endl;
    
    std::cout << "\nKey Learning Points:" << std::endl;
    std::cout << "- Morphological operations preserve essential shape characteristics" << std::endl;
    std::cout << "- Structuring element size affects the degree of operation" << std::endl;
    std::cout << "- Structuring element shape affects the directional properties" << std::endl;
    std::cout << "- Compound operations (opening/closing) are more robust than basic operations" << std::endl;
    std::cout << "- Advanced operations (gradient, top-hat, black-hat) provide specialized functionality" << std::endl;
    std::cout << "- Operations work best on binary images" << std::endl;
    
    std::cout << "\nApplications:" << std::endl;
    std::cout << "- Noise removal and image cleaning" << std::endl;
    std::cout << "- Object detection and segmentation" << std::endl;
    std::cout << "- Feature extraction and shape analysis" << std::endl;
    std::cout << "- Medical image processing (tumor detection)" << std::endl;
    std::cout << "- Document analysis and OCR" << std::endl;
    std::cout << "- Quality control in manufacturing" << std::endl;
    std::cout << "- Handwriting recognition" << std::endl;
    std::cout << "- Fingerprint analysis" << std::endl;
    
    std::cout << "\nPress any key to close..." << std::endl;
    cv::waitKey(0);  // Wait for user input before closing
    cv::destroyAllWindows();  // Clean up all windows
    
    return 0;  // Successful program termination
}
