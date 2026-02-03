/**
 * @file camera_advanced_22.cpp
 * @brief Advanced Image Stitching and Panorama - Advanced Level 22
 * @description This program demonstrates advanced image stitching techniques
 *              for creating panoramas using feature matching, homography,
 *              and blending algorithms with OpenCV and MATLAB integration.
 * @author Educational C++ MATLAB Integration Project
 * @date 2024
 * @version 1.0
 */

#include <opencv2/opencv.hpp>
#include <opencv2/features2d.hpp>
#include <opencv2/calib3d.hpp>
#include <opencv2/stitching.hpp>
#include <iostream>
#include <matlab/engine.hpp>
#include <memory>
#include <vector>
#include <algorithm>

using namespace cv;
using namespace std;

/**
 * @brief Enumeration for different stitching methods
 */
enum StitchingMethod {
    FEATURE_BASED = 0,
    HOMOGRAPHY_BASED = 1,
    AFFINE_BASED = 2,
    SIMILARITY_BASED = 3,
    TRANSLATION_BASED = 4,
    ROTATION_BASED = 5,
    BLEND_AVERAGE = 6,
    BLEND_MULTIBAND = 7,
    BLEND_FEATHER = 8,
    BLEND_NO_BLEND = 9
};

/**
 * @brief Structure to hold stitching parameters
 */
struct StitchingParams {
    double featureThreshold;
    int maxFeatures;
    double matchThreshold;
    double ransacThreshold;
    int maxIterations;
    double homographyThreshold;
    double affineThreshold;
    double similarityThreshold;
    double translationThreshold;
    double rotationThreshold;
    double blendAlpha;
    int blendLevels;
    double featherSigma;
    bool useMultiBandBlending;
    bool useFeatherBlending;
    bool useAverageBlending;
};

/**
 * @brief Function to get stitching method name
 * @param method Stitching method
 * @return string Method name
 */
string getStitchingMethodName(StitchingMethod method) {
    switch (method) {
        case FEATURE_BASED: return "Feature Based";
        case HOMOGRAPHY_BASED: return "Homography Based";
        case AFFINE_BASED: return "Affine Based";
        case SIMILARITY_BASED: return "Similarity Based";
        case TRANSLATION_BASED: return "Translation Based";
        case ROTATION_BASED: return "Rotation Based";
        case BLEND_AVERAGE: return "Average Blending";
        case BLEND_MULTIBAND: return "Multi-Band Blending";
        case BLEND_FEATHER: return "Feather Blending";
        case BLEND_NO_BLEND: return "No Blending";
        default: return "Unknown";
    }
}

/**
 * @brief Function to detect and match features
 * @param img1 First image
 * @param img2 Second image
 * @param keypoints1 Keypoints from first image
 * @param keypoints2 Keypoints from second image
 * @param matches Matches between images
 * @param params Stitching parameters
 */
void detectAndMatchFeatures(const Mat& img1, const Mat& img2, 
                           vector<KeyPoint>& keypoints1, vector<KeyPoint>& keypoints2,
                           vector<DMatch>& matches, const StitchingParams& params) {
    // Convert to grayscale
    Mat gray1, gray2;
    cvtColor(img1, gray1, COLOR_BGR2GRAY);
    cvtColor(img2, gray2, COLOR_BGR2GRAY);
    
    // Detect features
    Ptr<SIFT> detector = SIFT::create(params.maxFeatures);
    Mat descriptors1, descriptors2;
    
    detector->detectAndCompute(gray1, noArray(), keypoints1, descriptors1);
    detector->detectAndCompute(gray2, noArray(), keypoints2, descriptors2);
    
    if (descriptors1.empty() || descriptors2.empty()) {
        return;
    }
    
    // Match features
    Ptr<BFMatcher> matcher = BFMatcher::create(NORM_L2);
    vector<vector<DMatch>> knnMatches;
    matcher->knnMatch(descriptors1, descriptors2, knnMatches, 2);
    
    // Filter matches using ratio test
    for (const auto& match : knnMatches) {
        if (match.size() == 2 && match[0].distance < params.matchThreshold * match[1].distance) {
            matches.push_back(match[0]);
        }
    }
}

/**
 * @brief Function to find homography transformation
 * @param keypoints1 Keypoints from first image
 * @param keypoints2 Keypoints from second image
 * @param matches Matches between images
 * @param homography Output homography matrix
 * @param params Stitching parameters
 * @return bool Success status
 */
bool findHomographyTransformation(const vector<KeyPoint>& keypoints1, const vector<KeyPoint>& keypoints2,
                                 const vector<DMatch>& matches, Mat& homography, 
                                 const StitchingParams& params) {
    if (matches.size() < 4) {
        return false;
    }
    
    // Extract matched points
    vector<Point2f> points1, points2;
    for (const auto& match : matches) {
        points1.push_back(keypoints1[match.queryIdx].pt);
        points2.push_back(keypoints2[match.trainIdx].pt);
    }
    
    // Find homography
    homography = findHomography(points1, points2, RANSAC, params.ransacThreshold);
    
    return !homography.empty();
}

/**
 * @brief Function to find affine transformation
 * @param keypoints1 Keypoints from first image
 * @param keypoints2 Keypoints from second image
 * @param matches Matches between images
 * @param affine Output affine matrix
 * @param params Stitching parameters
 * @return bool Success status
 */
bool findAffineTransformation(const vector<KeyPoint>& keypoints1, const vector<KeyPoint>& keypoints2,
                             const vector<DMatch>& matches, Mat& affine, 
                             const StitchingParams& params) {
    if (matches.size() < 3) {
        return false;
    }
    
    // Extract matched points
    vector<Point2f> points1, points2;
    for (const auto& match : matches) {
        points1.push_back(keypoints1[match.queryIdx].pt);
        points2.push_back(keypoints2[match.trainIdx].pt);
    }
    
    // Find affine transformation
    affine = getAffineTransform(points1.data(), points2.data());
    
    return !affine.empty();
}

/**
 * @brief Function to find similarity transformation
 * @param keypoints1 Keypoints from first image
 * @param keypoints2 Keypoints from second image
 * @param matches Matches between images
 * @param similarity Output similarity matrix
 * @param params Stitching parameters
 * @return bool Success status
 */
bool findSimilarityTransformation(const vector<KeyPoint>& keypoints1, const vector<KeyPoint>& keypoints2,
                                 const vector<DMatch>& matches, Mat& similarity, 
                                 const StitchingParams& params) {
    if (matches.size() < 2) {
        return false;
    }
    
    // Extract matched points
    vector<Point2f> points1, points2;
    for (const auto& match : matches) {
        points1.push_back(keypoints1[match.queryIdx].pt);
        points2.push_back(keypoints2[match.trainIdx].pt);
    }
    
    // Find similarity transformation
    similarity = estimateAffinePartial2D(points1, points2);
    
    return !similarity.empty();
}

/**
 * @brief Function to find translation transformation
 * @param keypoints1 Keypoints from first image
 * @param keypoints2 Keypoints from second image
 * @param matches Matches between images
 * @param translation Output translation matrix
 * @param params Stitching parameters
 * @return bool Success status
 */
bool findTranslationTransformation(const vector<KeyPoint>& keypoints1, const vector<KeyPoint>& keypoints2,
                                  const vector<DMatch>& matches, Mat& translation, 
                                  const StitchingParams& params) {
    if (matches.size() < 1) {
        return false;
    }
    
    // Extract matched points
    vector<Point2f> points1, points2;
    for (const auto& match : matches) {
        points1.push_back(keypoints1[match.queryIdx].pt);
        points2.push_back(keypoints2[match.trainIdx].pt);
    }
    
    // Calculate average translation
    Point2f avgTranslation(0, 0);
    for (size_t i = 0; i < points1.size(); i++) {
        avgTranslation += points2[i] - points1[i];
    }
    avgTranslation /= points1.size();
    
    // Create translation matrix
    translation = Mat::eye(2, 3, CV_32F);
    translation.at<float>(0, 2) = avgTranslation.x;
    translation.at<float>(1, 2) = avgTranslation.y;
    
    return true;
}

/**
 * @brief Function to find rotation transformation
 * @param keypoints1 Keypoints from first image
 * @param keypoints2 Keypoints from second image
 * @param matches Matches between images
 * @param rotation Output rotation matrix
 * @param params Stitching parameters
 * @return bool Success status
 */
bool findRotationTransformation(const vector<KeyPoint>& keypoints1, const vector<KeyPoint>& keypoints2,
                               const vector<DMatch>& matches, Mat& rotation, 
                               const StitchingParams& params) {
    if (matches.size() < 2) {
        return false;
    }
    
    // Extract matched points
    vector<Point2f> points1, points2;
    for (const auto& match : matches) {
        points1.push_back(keypoints1[match.queryIdx].pt);
        points2.push_back(keypoints2[match.trainIdx].pt);
    }
    
    // Calculate rotation angle
    double angle = 0;
    for (size_t i = 0; i < points1.size(); i++) {
        Point2f srcVec = points1[i] - Point2f(keypoints1[0].pt);
        Point2f dstVec = points2[i] - Point2f(keypoints2[0].pt);
        angle += atan2(dstVec.y, dstVec.x) - atan2(srcVec.y, srcVec.x);
    }
    angle /= points1.size();
    
    // Create rotation matrix
    Point2f center(keypoints1[0].pt);
    rotation = getRotationMatrix2D(center, angle * 180 / CV_PI, 1.0);
    
    return true;
}

/**
 * @brief Function to apply average blending
 * @param img1 First image
 * @param img2 Second image
 * @param mask1 Mask for first image
 * @param mask2 Mask for second image
 * @param result Output blended image
 * @param params Stitching parameters
 */
void applyAverageBlending(const Mat& img1, const Mat& img2, const Mat& mask1, const Mat& mask2,
                         Mat& result, const StitchingParams& params) {
    result = Mat::zeros(img1.size(), img1.type());
    
    for (int i = 0; i < img1.rows; i++) {
        for (int j = 0; j < img1.cols; j++) {
            Vec3b pixel1 = img1.at<Vec3b>(i, j);
            Vec3b pixel2 = img2.at<Vec3b>(i, j);
            uchar mask1Val = mask1.at<uchar>(i, j);
            uchar mask2Val = mask2.at<uchar>(i, j);
            
            if (mask1Val > 0 && mask2Val > 0) {
                // Both images have valid pixels - average them
                result.at<Vec3b>(i, j) = (pixel1 + pixel2) / 2;
            } else if (mask1Val > 0) {
                // Only first image has valid pixel
                result.at<Vec3b>(i, j) = pixel1;
            } else if (mask2Val > 0) {
                // Only second image has valid pixel
                result.at<Vec3b>(i, j) = pixel2;
            }
        }
    }
}

/**
 * @brief Function to apply feather blending
 * @param img1 First image
 * @param img2 Second image
 * @param mask1 Mask for first image
 * @param mask2 Mask for second image
 * @param result Output blended image
 * @param params Stitching parameters
 */
void applyFeatherBlending(const Mat& img1, const Mat& img2, const Mat& mask1, const Mat& mask2,
                         Mat& result, const StitchingParams& params) {
    result = Mat::zeros(img1.size(), img1.type());
    
    // Create feather masks
    Mat featherMask1, featherMask2;
    GaussianBlur(mask1, featherMask1, Size(0, 0), params.featherSigma);
    GaussianBlur(mask2, featherMask2, Size(0, 0), params.featherSigma);
    
    for (int i = 0; i < img1.rows; i++) {
        for (int j = 0; j < img1.cols; j++) {
            Vec3b pixel1 = img1.at<Vec3b>(i, j);
            Vec3b pixel2 = img2.at<Vec3b>(i, j);
            float weight1 = featherMask1.at<float>(i, j) / 255.0f;
            float weight2 = featherMask2.at<float>(i, j) / 255.0f;
            
            if (weight1 > 0 || weight2 > 0) {
                float totalWeight = weight1 + weight2;
                if (totalWeight > 0) {
                    weight1 /= totalWeight;
                    weight2 /= totalWeight;
                }
                
                Vec3b blendedPixel;
                for (int c = 0; c < 3; c++) {
                    blendedPixel[c] = saturate_cast<uchar>(pixel1[c] * weight1 + pixel2[c] * weight2);
                }
                result.at<Vec3b>(i, j) = blendedPixel;
            }
        }
    }
}

/**
 * @brief Function to apply multi-band blending
 * @param img1 First image
 * @param img2 Second image
 * @param mask1 Mask for first image
 * @param mask2 Mask for second image
 * @param result Output blended image
 * @param params Stitching parameters
 */
void applyMultiBandBlending(const Mat& img1, const Mat& img2, const Mat& mask1, const Mat& mask2,
                           Mat& result, const StitchingParams& params) {
    // Simplified multi-band blending
    result = Mat::zeros(img1.size(), img1.type());
    
    for (int level = 0; level < params.blendLevels; level++) {
        Mat level1, level2, levelMask1, levelMask2;
        
        if (level == 0) {
            img1.copyTo(level1);
            img2.copyTo(level2);
            mask1.copyTo(levelMask1);
            mask2.copyTo(levelMask2);
        } else {
            pyrDown(level1, level1);
            pyrDown(level2, level2);
            pyrDown(levelMask1, levelMask1);
            pyrDown(levelMask2, levelMask2);
        }
        
        // Apply blending at this level
        Mat levelResult;
        applyFeatherBlending(level1, level2, levelMask1, levelMask2, levelResult, params);
        
        // Upsample and add to result
        if (level == 0) {
            levelResult.copyTo(result);
        } else {
            Mat upsampled;
            pyrUp(levelResult, upsampled, result.size());
            result += upsampled;
        }
    }
}

/**
 * @brief Function to apply image stitching
 * @param img1 First image
 * @param img2 Second image
 * @param result Output stitched image
 * @param method Stitching method
 * @param params Stitching parameters
 * @return bool Success status
 */
bool applyImageStitching(const Mat& img1, const Mat& img2, Mat& result, 
                        StitchingMethod method, const StitchingParams& params) {
    // Detect and match features
    vector<KeyPoint> keypoints1, keypoints2;
    vector<DMatch> matches;
    detectAndMatchFeatures(img1, img2, keypoints1, keypoints2, matches, params);
    
    if (matches.size() < 4) {
        return false;
    }
    
    // Find transformation based on method
    Mat transformation;
    bool success = false;
    
    switch (method) {
        case HOMOGRAPHY_BASED:
            success = findHomographyTransformation(keypoints1, keypoints2, matches, transformation, params);
            break;
        case AFFINE_BASED:
            success = findAffineTransformation(keypoints1, keypoints2, matches, transformation, params);
            break;
        case SIMILARITY_BASED:
            success = findSimilarityTransformation(keypoints1, keypoints2, matches, transformation, params);
            break;
        case TRANSLATION_BASED:
            success = findTranslationTransformation(keypoints1, keypoints2, matches, transformation, params);
            break;
        case ROTATION_BASED:
            success = findRotationTransformation(keypoints1, keypoints2, matches, transformation, params);
            break;
        default:
            success = findHomographyTransformation(keypoints1, keypoints2, matches, transformation, params);
            break;
    }
    
    if (!success) {
        return false;
    }
    
    // Apply transformation
    Mat transformedImg2;
    if (method == HOMOGRAPHY_BASED) {
        warpPerspective(img2, transformedImg2, transformation, img1.size());
    } else {
        warpAffine(img2, transformedImg2, transformation, img1.size());
    }
    
    // Create masks
    Mat mask1 = Mat::ones(img1.size(), CV_8UC1) * 255;
    Mat mask2 = Mat::ones(img2.size(), CV_8UC1) * 255;
    Mat transformedMask2;
    
    if (method == HOMOGRAPHY_BASED) {
        warpPerspective(mask2, transformedMask2, transformation, img1.size());
    } else {
        warpAffine(mask2, transformedMask2, transformation, img1.size());
    }
    
    // Apply blending
    switch (method) {
        case BLEND_AVERAGE:
            applyAverageBlending(img1, transformedImg2, mask1, transformedMask2, result, params);
            break;
        case BLEND_FEATHER:
            applyFeatherBlending(img1, transformedImg2, mask1, transformedMask2, result, params);
            break;
        case BLEND_MULTIBAND:
            applyMultiBandBlending(img1, transformedImg2, mask1, transformedMask2, result, params);
            break;
        case BLEND_NO_BLEND:
            img1.copyTo(result);
            transformedImg2.copyTo(result, transformedMask2);
            break;
        default:
            applyAverageBlending(img1, transformedImg2, mask1, transformedMask2, result, params);
            break;
    }
    
    return true;
}

/**
 * @brief Function to send stitching data to MATLAB
 * @param matlabPtr MATLAB engine pointer
 * @param img1 First image
 * @param img2 Second image
 * @param result Stitched image
 * @param method Stitching method
 * @param params Stitching parameters
 */
void sendStitchingToMATLAB(std::unique_ptr<matlab::engine::MATLABEngine>& matlabPtr, 
                          const Mat& img1, const Mat& img2, const Mat& result,
                          StitchingMethod method, const StitchingParams& params) {
    try {
        // Convert BGR to RGB for MATLAB
        Mat rgbImg1, rgbImg2, rgbResult;
        cvtColor(img1, rgbImg1, COLOR_BGR2RGB);
        cvtColor(img2, rgbImg2, COLOR_BGR2RGB);
        cvtColor(result, rgbResult, COLOR_BGR2RGB);
        
        // Create MATLAB arrays
        matlab::data::ArrayFactory factory;
        
        // First image
        auto dimsImg1 = factory.createArray<std::size_t>({1, 3}, 
            {static_cast<std::size_t>(rgbImg1.rows), 
             static_cast<std::size_t>(rgbImg1.cols), 
             static_cast<std::size_t>(rgbImg1.channels())});
        auto matlabImg1 = factory.createArray<uint8_t>(dimsImg1);
        auto img1Ptr = matlabImg1.release();
        memcpy(img1Ptr, rgbImg1.data, rgbImg1.total() * rgbImg1.elemSize());
        
        // Second image
        auto dimsImg2 = factory.createArray<std::size_t>({1, 3}, 
            {static_cast<std::size_t>(rgbImg2.rows), 
             static_cast<std::size_t>(rgbImg2.cols), 
             static_cast<std::size_t>(rgbImg2.channels())});
        auto matlabImg2 = factory.createArray<uint8_t>(dimsImg2);
        auto img2Ptr = matlabImg2.release();
        memcpy(img2Ptr, rgbImg2.data, rgbImg2.total() * rgbImg2.elemSize());
        
        // Stitched image
        auto dimsResult = factory.createArray<std::size_t>({1, 3}, 
            {static_cast<std::size_t>(rgbResult.rows), 
             static_cast<std::size_t>(rgbResult.cols), 
             static_cast<std::size_t>(rgbResult.channels())});
        auto matlabResult = factory.createArray<uint8_t>(dimsResult);
        auto resultPtr = matlabResult.release();
        memcpy(resultPtr, rgbResult.data, rgbResult.total() * rgbResult.elemSize());
        
        // Set variables in MATLAB workspace
        matlabPtr->setVariable(u"image1", matlabImg1);
        matlabPtr->setVariable(u"image2", matlabImg2);
        matlabPtr->setVariable(u"stitchedImage", matlabResult);
        
        // Execute MATLAB commands
        string methodName = getStitchingMethodName(method);
        string matlabCmd = "figure; subplot(1,3,1); imshow(image1); title('Image 1'); "
                          "subplot(1,3,2); imshow(image2); title('Image 2'); "
                          "subplot(1,3,3); imshow(stitchedImage); title('" + methodName + " Stitching');";
        matlabPtr->eval(matlab::engine::convertUTF8StringToUTF16String(matlabCmd));
        
        // Display stitching information
        matlabPtr->eval(u"fprintf('Stitching Method: " + matlab::engine::convertUTF8StringToUTF16String(methodName) + "\\n');");
        
        cout << "Stitching data sent to MATLAB successfully!" << endl;
        
    } catch (const std::exception& e) {
        cerr << "Error sending stitching data to MATLAB: " << e.what() << endl;
    }
}

/**
 * @brief Main function for advanced image stitching and panorama
 * @return int Exit status
 */
int main() {
    cout << "=== Advanced Image Stitching and Panorama - Advanced Level 22 ===" << endl;
    cout << "This program demonstrates advanced image stitching techniques." << endl;
    
    try {
        // Initialize MATLAB engine
        cout << "Initializing MATLAB engine..." << endl;
        std::unique_ptr<matlab::engine::MATLABEngine> matlabPtr = 
            matlab::engine::startMATLAB();
        
        // Initialize camera capture
        cout << "Initializing camera..." << endl;
        VideoCapture cap(0); // 0 = default camera
        
        // Check if camera opened successfully
        if (!cap.isOpened()) {
            cerr << "Error: Could not open camera!" << endl;
            return -1;
        }
        
        cout << "Camera opened successfully!" << endl;
        
        // Set camera properties
        cap.set(CAP_PROP_FRAME_WIDTH, 640);
        cap.set(CAP_PROP_FRAME_HEIGHT, 480);
        
        // Initialize stitching parameters
        StitchingParams params;
        params.featureThreshold = 0.7;
        params.maxFeatures = 1000;
        params.matchThreshold = 0.75;
        params.ransacThreshold = 3.0;
        params.maxIterations = 2000;
        params.homographyThreshold = 3.0;
        params.affineThreshold = 3.0;
        params.similarityThreshold = 3.0;
        params.translationThreshold = 3.0;
        params.rotationThreshold = 3.0;
        params.blendAlpha = 0.5;
        params.blendLevels = 3;
        params.featherSigma = 10.0;
        params.useMultiBandBlending = false;
        params.useFeatherBlending = false;
        params.useAverageBlending = true;
        
        // Initialize stitching method
        StitchingMethod currentMethod = HOMOGRAPHY_BASED;
        
        // Create Mat objects for frame processing
        Mat frame, prevFrame, stitchedFrame, visualization;
        
        cout << "\nStarting camera feed with image stitching..." << endl;
        cout << "Controls:" << endl;
        cout << "  'q' - Quit" << endl;
        cout << "  '0' - Feature Based" << endl;
        cout << "  '1' - Homography Based" << endl;
        cout << "  '2' - Affine Based" << endl;
        cout << "  '3' - Similarity Based" << endl;
        cout << "  '4' - Translation Based" << endl;
        cout << "  '5' - Rotation Based" << endl;
        cout << "  '6' - Average Blending" << endl;
        cout << "  '7' - Multi-Band Blending" << endl;
        cout << "  '8' - Feather Blending" << endl;
        cout << "  '9' - No Blending" << endl;
        cout << "  'c' - Capture reference frame" << endl;
        cout << "  'm' - Send to MATLAB" << endl;
        cout << "  's' - Save current stitching" << endl;
        
        bool hasReference = false;
        
        // Main capture loop
        while (true) {
            // Capture frame from camera
            cap >> frame;
            
            // Check if frame was captured successfully
            if (frame.empty()) {
                cerr << "Warning: Could not capture frame!" << endl;
                continue;
            }
            
            // Apply image stitching if we have a reference frame
            if (hasReference) {
                bool success = applyImageStitching(prevFrame, frame, stitchedFrame, currentMethod, params);
                if (success) {
                    // Create visualization
                    visualization = stitchedFrame;
                } else {
                    // Display original frames if stitching failed
                    Mat comparison;
                    hconcat(prevFrame, frame, comparison);
                    visualization = comparison;
                }
            } else {
                // Display current frame
                visualization = frame;
            }
            
            // Display the visualization
            imshow("Advanced Image Stitching and Panorama", visualization);
            
            // Handle keyboard input
            char key = waitKey(1) & 0xFF;
            
            if (key == 'q' || key == 27) { // 'q' or ESC to quit
                cout << "Quitting..." << endl;
                break;
            }
            else if (key >= '0' && key <= '9') { // Method selection
                currentMethod = static_cast<StitchingMethod>(key - '0');
                cout << "Selected method: " << getStitchingMethodName(currentMethod) << endl;
            }
            else if (key == 'c') { // Capture reference frame
                frame.copyTo(prevFrame);
                hasReference = true;
                cout << "Reference frame captured!" << endl;
            }
            else if (key == 'm') { // Send to MATLAB
                if (hasReference) {
                    sendStitchingToMATLAB(matlabPtr, prevFrame, frame, stitchedFrame, currentMethod, params);
                }
            }
            else if (key == 's') { // Save current stitching
                if (hasReference) {
                    string filename = "stitching_" + getStitchingMethodName(currentMethod) + ".jpg";
                    imwrite(filename, visualization);
                    cout << "Stitching saved as: " << filename << endl;
                }
            }
        }
        
        // Clean up
        cap.release();
        destroyAllWindows();
        
        cout << "Program completed successfully!" << endl;
        
    } catch (const std::exception& e) {
        cerr << "Error: " << e.what() << endl;
        return -1;
    }
    
    return 0;
}

/**
 * @brief Compilation Instructions:
 * 
 * To compile this program, you need:
 * 1. OpenCV library installed
 * 2. MATLAB Engine API for C++ installed
 * 3. Proper linking flags
 * 
 * Compilation command:
 * g++ -std=c++17 camera_advanced_22.cpp -o camera_advanced_22 \
 *     `pkg-config --cflags --libs opencv4` \
 *     -I/Applications/MATLAB_R2023b.app/extern/include \
 *     -L/Applications/MATLAB_R2023b.app/bin/maci64 \
 *     -lMatlabDataArray -lMatlabEngine
 * 
 * @brief Usage:
 * 1. Make sure your camera is connected and working
 * 2. Run the executable: ./camera_advanced_22
 * 3. Press 'c' to capture a reference frame
 * 4. Use keyboard controls to switch between stitching methods
 * 5. Press 'm' to send data to MATLAB
 * 6. Press 's' to save current stitching
 * 
 * @brief Learning Objectives:
 * - Understand advanced image stitching techniques
 * - Learn feature-based stitching
 * - Understand homography and affine transformations
 * - Learn similarity and translation transformations
 * - Understand rotation transformations
 * - Learn different blending methods
 * - Learn MATLAB integration for stitching analysis
 * - Understand panorama creation
 */
