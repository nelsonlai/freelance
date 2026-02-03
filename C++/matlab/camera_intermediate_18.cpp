/**
 * @file camera_intermediate_18.cpp
 * @brief Image Registration and Alignment - Intermediate Level 18
 * @description This program demonstrates image registration and alignment techniques
 *              including feature-based registration, template matching, and
 *              geometric transformation using OpenCV and MATLAB integration.
 * @author Educational C++ MATLAB Integration Project
 * @date 2024
 * @version 1.0
 */

#include <opencv2/opencv.hpp>
#include <opencv2/features2d.hpp>
#include <opencv2/calib3d.hpp>
#include <iostream>
#include <matlab/engine.hpp>
#include <memory>
#include <vector>
#include <algorithm>

using namespace cv;
using namespace std;

/**
 * @brief Enumeration for different registration methods
 */
enum RegistrationMethod {
    FEATURE_BASED = 0,
    TEMPLATE_MATCHING = 1,
    PHASE_CORRELATION = 2,
    ECC = 3,
    HOMOGRAPHY = 4,
    AFFINE = 5,
    SIMILARITY = 6,
    TRANSLATION = 7,
    ROTATION = 8
};

/**
 * @brief Structure to hold registration parameters
 */
struct RegistrationParams {
    double featureThreshold;
    int maxFeatures;
    double matchThreshold;
    double ransacThreshold;
    int maxIterations;
    double templateThreshold;
    int phaseCorrelationSize;
    double eccThreshold;
    int eccMaxIterations;
    double homographyThreshold;
    double affineThreshold;
    double similarityThreshold;
    double translationThreshold;
    double rotationThreshold;
};

/**
 * @brief Function to get registration method name
 * @param method Registration method
 * @return string Method name
 */
string getRegistrationMethodName(RegistrationMethod method) {
    switch (method) {
        case FEATURE_BASED: return "Feature Based";
        case TEMPLATE_MATCHING: return "Template Matching";
        case PHASE_CORRELATION: return "Phase Correlation";
        case ECC: return "ECC";
        case HOMOGRAPHY: return "Homography";
        case AFFINE: return "Affine";
        case SIMILARITY: return "Similarity";
        case TRANSLATION: return "Translation";
        case ROTATION: return "Rotation";
        default: return "Unknown";
    }
}

/**
 * @brief Function to apply feature-based registration
 * @param src Source image
 * @param dst Destination image
 * @param registered Output registered image
 * @param params Registration parameters
 * @return bool Success status
 */
bool applyFeatureBasedRegistration(const Mat& src, const Mat& dst, Mat& registered, 
                                  const RegistrationParams& params) {
    // Convert to grayscale
    Mat srcGray, dstGray;
    cvtColor(src, srcGray, COLOR_BGR2GRAY);
    cvtColor(dst, dstGray, COLOR_BGR2GRAY);
    
    // Detect features
    Ptr<ORB> detector = ORB::create(params.maxFeatures);
    vector<KeyPoint> srcKeypoints, dstKeypoints;
    Mat srcDescriptors, dstDescriptors;
    
    detector->detectAndCompute(srcGray, noArray(), srcKeypoints, srcDescriptors);
    detector->detectAndCompute(dstGray, noArray(), dstKeypoints, dstDescriptors);
    
    if (srcDescriptors.empty() || dstDescriptors.empty()) {
        return false;
    }
    
    // Match features
    Ptr<BFMatcher> matcher = BFMatcher::create(NORM_HAMMING);
    vector<vector<DMatch>> knnMatches;
    matcher->knnMatch(srcDescriptors, dstDescriptors, knnMatches, 2);
    
    // Filter matches using ratio test
    vector<DMatch> goodMatches;
    for (const auto& match : knnMatches) {
        if (match.size() == 2 && match[0].distance < params.matchThreshold * match[1].distance) {
            goodMatches.push_back(match[0]);
        }
    }
    
    if (goodMatches.size() < 4) {
        return false;
    }
    
    // Extract matched points
    vector<Point2f> srcPoints, dstPoints;
    for (const auto& match : goodMatches) {
        srcPoints.push_back(srcKeypoints[match.queryIdx].pt);
        dstPoints.push_back(dstKeypoints[match.trainIdx].pt);
    }
    
    // Find homography
    Mat homography = findHomography(srcPoints, dstPoints, RANSAC, params.ransacThreshold);
    
    if (homography.empty()) {
        return false;
    }
    
    // Apply transformation
    warpPerspective(src, registered, homography, dst.size());
    
    return true;
}

/**
 * @brief Function to apply template matching registration
 * @param src Source image
 * @param dst Destination image
 * @param registered Output registered image
 * @param params Registration parameters
 * @return bool Success status
 */
bool applyTemplateMatchingRegistration(const Mat& src, const Mat& dst, Mat& registered, 
                                     const RegistrationParams& params) {
    // Convert to grayscale
    Mat srcGray, dstGray;
    cvtColor(src, srcGray, COLOR_BGR2GRAY);
    cvtColor(dst, dstGray, COLOR_BGR2GRAY);
    
    // Resize source to be smaller than destination
    if (srcGray.cols >= dstGray.cols || srcGray.rows >= dstGray.rows) {
        double scale = min((double)dstGray.cols / srcGray.cols, (double)dstGray.rows / srcGray.rows) * 0.8;
        resize(srcGray, srcGray, Size(), scale, scale);
    }
    
    // Template matching
    Mat result;
    matchTemplate(dstGray, srcGray, result, TM_CCOEFF_NORMED);
    
    // Find best match
    double minVal, maxVal;
    Point minLoc, maxLoc;
    minMaxLoc(result, &minVal, &maxVal, &minLoc, &maxLoc);
    
    if (maxVal < params.templateThreshold) {
        return false;
    }
    
    // Create transformation matrix
    Mat transform = Mat::eye(2, 3, CV_32F);
    transform.at<float>(0, 2) = maxLoc.x;
    transform.at<float>(1, 2) = maxLoc.y;
    
    // Apply transformation
    warpAffine(src, registered, transform, dst.size());
    
    return true;
}

/**
 * @brief Function to apply phase correlation registration
 * @param src Source image
 * @param dst Destination image
 * @param registered Output registered image
 * @param params Registration parameters
 * @return bool Success status
 */
bool applyPhaseCorrelationRegistration(const Mat& src, const Mat& dst, Mat& registered, 
                                     const RegistrationParams& params) {
    // Convert to grayscale
    Mat srcGray, dstGray;
    cvtColor(src, srcGray, COLOR_BGR2GRAY);
    cvtColor(dst, dstGray, COLOR_BGR2GRAY);
    
    // Resize images to same size
    Size targetSize(params.phaseCorrelationSize, params.phaseCorrelationSize);
    resize(srcGray, srcGray, targetSize);
    resize(dstGray, dstGray, targetSize);
    
    // Phase correlation
    Mat result;
    phaseCorrelate(srcGray, dstGray, result);
    
    // Extract translation
    Point2f translation = result;
    
    // Create transformation matrix
    Mat transform = Mat::eye(2, 3, CV_32F);
    transform.at<float>(0, 2) = translation.x;
    transform.at<float>(1, 2) = translation.y;
    
    // Apply transformation
    warpAffine(src, registered, transform, dst.size());
    
    return true;
}

/**
 * @brief Function to apply ECC registration
 * @param src Source image
 * @param dst Destination image
 * @param registered Output registered image
 * @param params Registration parameters
 * @return bool Success status
 */
bool applyECCRegistration(const Mat& src, const Mat& dst, Mat& registered, 
                         const RegistrationParams& params) {
    // Convert to grayscale
    Mat srcGray, dstGray;
    cvtColor(src, srcGray, COLOR_BGR2GRAY);
    cvtColor(dst, dstGray, COLOR_BGR2GRAY);
    
    // Initialize transformation matrix
    Mat transform = Mat::eye(2, 3, CV_32F);
    
    // ECC registration
    double correlation = findTransformECC(dstGray, srcGray, transform, MOTION_AFFINE, 
                                        TermCriteria(TermCriteria::COUNT + TermCriteria::EPS, 
                                                   params.eccMaxIterations, params.eccThreshold));
    
    if (correlation < 0.5) {
        return false;
    }
    
    // Apply transformation
    warpAffine(src, registered, transform, dst.size());
    
    return true;
}

/**
 * @brief Function to apply homography registration
 * @param src Source image
 * @param dst Destination image
 * @param registered Output registered image
 * @param params Registration parameters
 * @return bool Success status
 */
bool applyHomographyRegistration(const Mat& src, const Mat& dst, Mat& registered, 
                                const RegistrationParams& params) {
    // Convert to grayscale
    Mat srcGray, dstGray;
    cvtColor(src, srcGray, COLOR_BGR2GRAY);
    cvtColor(dst, dstGray, COLOR_BGR2GRAY);
    
    // Detect features
    Ptr<SIFT> detector = SIFT::create();
    vector<KeyPoint> srcKeypoints, dstKeypoints;
    Mat srcDescriptors, dstDescriptors;
    
    detector->detectAndCompute(srcGray, noArray(), srcKeypoints, srcDescriptors);
    detector->detectAndCompute(dstGray, noArray(), dstKeypoints, dstDescriptors);
    
    if (srcDescriptors.empty() || dstDescriptors.empty()) {
        return false;
    }
    
    // Match features
    Ptr<BFMatcher> matcher = BFMatcher::create(NORM_L2);
    vector<vector<DMatch>> knnMatches;
    matcher->knnMatch(srcDescriptors, dstDescriptors, knnMatches, 2);
    
    // Filter matches using ratio test
    vector<DMatch> goodMatches;
    for (const auto& match : knnMatches) {
        if (match.size() == 2 && match[0].distance < params.matchThreshold * match[1].distance) {
            goodMatches.push_back(match[0]);
        }
    }
    
    if (goodMatches.size() < 4) {
        return false;
    }
    
    // Extract matched points
    vector<Point2f> srcPoints, dstPoints;
    for (const auto& match : goodMatches) {
        srcPoints.push_back(srcKeypoints[match.queryIdx].pt);
        dstPoints.push_back(dstKeypoints[match.trainIdx].pt);
    }
    
    // Find homography
    Mat homography = findHomography(srcPoints, dstPoints, RANSAC, params.homographyThreshold);
    
    if (homography.empty()) {
        return false;
    }
    
    // Apply transformation
    warpPerspective(src, registered, homography, dst.size());
    
    return true;
}

/**
 * @brief Function to apply affine registration
 * @param src Source image
 * @param dst Destination image
 * @param registered Output registered image
 * @param params Registration parameters
 * @return bool Success status
 */
bool applyAffineRegistration(const Mat& src, const Mat& dst, Mat& registered, 
                           const RegistrationParams& params) {
    // Convert to grayscale
    Mat srcGray, dstGray;
    cvtColor(src, srcGray, COLOR_BGR2GRAY);
    cvtColor(dst, dstGray, COLOR_BGR2GRAY);
    
    // Detect features
    Ptr<ORB> detector = ORB::create(params.maxFeatures);
    vector<KeyPoint> srcKeypoints, dstKeypoints;
    Mat srcDescriptors, dstDescriptors;
    
    detector->detectAndCompute(srcGray, noArray(), srcKeypoints, srcDescriptors);
    detector->detectAndCompute(dstGray, noArray(), dstKeypoints, dstDescriptors);
    
    if (srcDescriptors.empty() || dstDescriptors.empty()) {
        return false;
    }
    
    // Match features
    Ptr<BFMatcher> matcher = BFMatcher::create(NORM_HAMMING);
    vector<vector<DMatch>> knnMatches;
    matcher->knnMatch(srcDescriptors, dstDescriptors, knnMatches, 2);
    
    // Filter matches using ratio test
    vector<DMatch> goodMatches;
    for (const auto& match : knnMatches) {
        if (match.size() == 2 && match[0].distance < params.matchThreshold * match[1].distance) {
            goodMatches.push_back(match[0]);
        }
    }
    
    if (goodMatches.size() < 3) {
        return false;
    }
    
    // Extract matched points
    vector<Point2f> srcPoints, dstPoints;
    for (const auto& match : goodMatches) {
        srcPoints.push_back(srcKeypoints[match.queryIdx].pt);
        dstPoints.push_back(dstKeypoints[match.trainIdx].pt);
    }
    
    // Find affine transformation
    Mat affine = getAffineTransform(srcPoints.data(), dstPoints.data());
    
    if (affine.empty()) {
        return false;
    }
    
    // Apply transformation
    warpAffine(src, registered, affine, dst.size());
    
    return true;
}

/**
 * @brief Function to apply similarity registration
 * @param src Source image
 * @param dst Destination image
 * @param registered Output registered image
 * @param params Registration parameters
 * @return bool Success status
 */
bool applySimilarityRegistration(const Mat& src, const Mat& dst, Mat& registered, 
                               const RegistrationParams& params) {
    // Convert to grayscale
    Mat srcGray, dstGray;
    cvtColor(src, srcGray, COLOR_BGR2GRAY);
    cvtColor(dst, dstGray, COLOR_BGR2GRAY);
    
    // Detect features
    Ptr<ORB> detector = ORB::create(params.maxFeatures);
    vector<KeyPoint> srcKeypoints, dstKeypoints;
    Mat srcDescriptors, dstDescriptors;
    
    detector->detectAndCompute(srcGray, noArray(), srcKeypoints, srcDescriptors);
    detector->detectAndCompute(dstGray, noArray(), dstKeypoints, dstDescriptors);
    
    if (srcDescriptors.empty() || dstDescriptors.empty()) {
        return false;
    }
    
    // Match features
    Ptr<BFMatcher> matcher = BFMatcher::create(NORM_HAMMING);
    vector<vector<DMatch>> knnMatches;
    matcher->knnMatch(srcDescriptors, dstDescriptors, knnMatches, 2);
    
    // Filter matches using ratio test
    vector<DMatch> goodMatches;
    for (const auto& match : knnMatches) {
        if (match.size() == 2 && match[0].distance < params.matchThreshold * match[1].distance) {
            goodMatches.push_back(match[0]);
        }
    }
    
    if (goodMatches.size() < 2) {
        return false;
    }
    
    // Extract matched points
    vector<Point2f> srcPoints, dstPoints;
    for (const auto& match : goodMatches) {
        srcPoints.push_back(srcKeypoints[match.queryIdx].pt);
        dstPoints.push_back(dstKeypoints[match.trainIdx].pt);
    }
    
    // Find similarity transformation
    Mat similarity = estimateAffinePartial2D(srcPoints, dstPoints);
    
    if (similarity.empty()) {
        return false;
    }
    
    // Apply transformation
    warpAffine(src, registered, similarity, dst.size());
    
    return true;
}

/**
 * @brief Function to apply translation registration
 * @param src Source image
 * @param dst Destination image
 * @param registered Output registered image
 * @param params Registration parameters
 * @return bool Success status
 */
bool applyTranslationRegistration(const Mat& src, const Mat& dst, Mat& registered, 
                                const RegistrationParams& params) {
    // Convert to grayscale
    Mat srcGray, dstGray;
    cvtColor(src, srcGray, COLOR_BGR2GRAY);
    cvtColor(dst, dstGray, COLOR_BGR2GRAY);
    
    // Detect features
    Ptr<ORB> detector = ORB::create(params.maxFeatures);
    vector<KeyPoint> srcKeypoints, dstKeypoints;
    Mat srcDescriptors, dstDescriptors;
    
    detector->detectAndCompute(srcGray, noArray(), srcKeypoints, srcDescriptors);
    detector->detectAndCompute(dstGray, noArray(), dstKeypoints, dstDescriptors);
    
    if (srcDescriptors.empty() || dstDescriptors.empty()) {
        return false;
    }
    
    // Match features
    Ptr<BFMatcher> matcher = BFMatcher::create(NORM_HAMMING);
    vector<vector<DMatch>> knnMatches;
    matcher->knnMatch(srcDescriptors, dstDescriptors, knnMatches, 2);
    
    // Filter matches using ratio test
    vector<DMatch> goodMatches;
    for (const auto& match : knnMatches) {
        if (match.size() == 2 && match[0].distance < params.matchThreshold * match[1].distance) {
            goodMatches.push_back(match[0]);
        }
    }
    
    if (goodMatches.size() < 1) {
        return false;
    }
    
    // Extract matched points
    vector<Point2f> srcPoints, dstPoints;
    for (const auto& match : goodMatches) {
        srcPoints.push_back(srcKeypoints[match.queryIdx].pt);
        dstPoints.push_back(dstKeypoints[match.trainIdx].pt);
    }
    
    // Calculate average translation
    Point2f translation(0, 0);
    for (size_t i = 0; i < srcPoints.size(); i++) {
        translation += dstPoints[i] - srcPoints[i];
    }
    translation /= srcPoints.size();
    
    // Create transformation matrix
    Mat transform = Mat::eye(2, 3, CV_32F);
    transform.at<float>(0, 2) = translation.x;
    transform.at<float>(1, 2) = translation.y;
    
    // Apply transformation
    warpAffine(src, registered, transform, dst.size());
    
    return true;
}

/**
 * @brief Function to apply rotation registration
 * @param src Source image
 * @param dst Destination image
 * @param registered Output registered image
 * @param params Registration parameters
 * @return bool Success status
 */
bool applyRotationRegistration(const Mat& src, const Mat& dst, Mat& registered, 
                             const RegistrationParams& params) {
    // Convert to grayscale
    Mat srcGray, dstGray;
    cvtColor(src, srcGray, COLOR_BGR2GRAY);
    cvtColor(dst, dstGray, COLOR_BGR2GRAY);
    
    // Detect features
    Ptr<ORB> detector = ORB::create(params.maxFeatures);
    vector<KeyPoint> srcKeypoints, dstKeypoints;
    Mat srcDescriptors, dstDescriptors;
    
    detector->detectAndCompute(srcGray, noArray(), srcKeypoints, srcDescriptors);
    detector->detectAndCompute(dstGray, noArray(), dstKeypoints, dstDescriptors);
    
    if (srcDescriptors.empty() || dstDescriptors.empty()) {
        return false;
    }
    
    // Match features
    Ptr<BFMatcher> matcher = BFMatcher::create(NORM_HAMMING);
    vector<vector<DMatch>> knnMatches;
    matcher->knnMatch(srcDescriptors, dstDescriptors, knnMatches, 2);
    
    // Filter matches using ratio test
    vector<DMatch> goodMatches;
    for (const auto& match : knnMatches) {
        if (match.size() == 2 && match[0].distance < params.matchThreshold * match[1].distance) {
            goodMatches.push_back(match[0]);
        }
    }
    
    if (goodMatches.size() < 2) {
        return false;
    }
    
    // Extract matched points
    vector<Point2f> srcPoints, dstPoints;
    for (const auto& match : goodMatches) {
        srcPoints.push_back(srcKeypoints[match.queryIdx].pt);
        dstPoints.push_back(dstKeypoints[match.trainIdx].pt);
    }
    
    // Calculate rotation angle
    double angle = 0;
    for (size_t i = 0; i < srcPoints.size(); i++) {
        Point2f srcVec = srcPoints[i] - Point2f(src.cols/2, src.rows/2);
        Point2f dstVec = dstPoints[i] - Point2f(dst.cols/2, dst.rows/2);
        angle += atan2(dstVec.y, dstVec.x) - atan2(srcVec.y, srcVec.x);
    }
    angle /= srcPoints.size();
    
    // Create transformation matrix
    Point2f center(src.cols/2, src.rows/2);
    Mat transform = getRotationMatrix2D(center, angle * 180 / CV_PI, 1.0);
    
    // Apply transformation
    warpAffine(src, registered, transform, dst.size());
    
    return true;
}

/**
 * @brief Function to apply selected registration method
 * @param src Source image
 * @param dst Destination image
 * @param registered Output registered image
 * @param method Registration method
 * @param params Registration parameters
 * @return bool Success status
 */
bool applyRegistration(const Mat& src, const Mat& dst, Mat& registered, 
                      RegistrationMethod method, const RegistrationParams& params) {
    switch (method) {
        case FEATURE_BASED:
            return applyFeatureBasedRegistration(src, dst, registered, params);
        case TEMPLATE_MATCHING:
            return applyTemplateMatchingRegistration(src, dst, registered, params);
        case PHASE_CORRELATION:
            return applyPhaseCorrelationRegistration(src, dst, registered, params);
        case ECC:
            return applyECCRegistration(src, dst, registered, params);
        case HOMOGRAPHY:
            return applyHomographyRegistration(src, dst, registered, params);
        case AFFINE:
            return applyAffineRegistration(src, dst, registered, params);
        case SIMILARITY:
            return applySimilarityRegistration(src, dst, registered, params);
        case TRANSLATION:
            return applyTranslationRegistration(src, dst, registered, params);
        case ROTATION:
            return applyRotationRegistration(src, dst, registered, params);
        default:
            return false;
    }
}

/**
 * @brief Function to create registration visualization
 * @param src Source image
 * @param dst Destination image
 * @param registered Registered image
 * @return Mat Registration visualization
 */
Mat createRegistrationVisualization(const Mat& src, const Mat& dst, const Mat& registered) {
    // Create 2x2 grid
    Mat visualization = Mat::zeros(src.rows * 2, src.cols * 2, CV_8UC3);
    
    // Place images in grid
    src.copyTo(visualization(Rect(0, 0, src.cols, src.rows)));
    dst.copyTo(visualization(Rect(src.cols, 0, dst.cols, dst.rows)));
    registered.copyTo(visualization(Rect(0, src.rows, registered.cols, registered.rows)));
    
    // Add labels
    putText(visualization, "Source", Point(10, 30), FONT_HERSHEY_SIMPLEX, 0.7, Scalar(0, 255, 0), 2);
    putText(visualization, "Destination", Point(src.cols + 10, 30), FONT_HERSHEY_SIMPLEX, 0.7, Scalar(0, 255, 0), 2);
    putText(visualization, "Registered", Point(10, src.rows + 30), FONT_HERSHEY_SIMPLEX, 0.7, Scalar(0, 255, 0), 2);
    
    return visualization;
}

/**
 * @brief Function to send registration data to MATLAB
 * @param matlabPtr MATLAB engine pointer
 * @param src Source image
 * @param dst Destination image
 * @param registered Registered image
 * @param method Registration method
 * @param params Registration parameters
 */
void sendRegistrationToMATLAB(std::unique_ptr<matlab::engine::MATLABEngine>& matlabPtr, 
                             const Mat& src, const Mat& dst, const Mat& registered,
                             RegistrationMethod method, const RegistrationParams& params) {
    try {
        // Convert BGR to RGB for MATLAB
        Mat rgbSrc, rgbDst, rgbRegistered;
        cvtColor(src, rgbSrc, COLOR_BGR2RGB);
        cvtColor(dst, rgbDst, COLOR_BGR2RGB);
        cvtColor(registered, rgbRegistered, COLOR_BGR2RGB);
        
        // Create MATLAB arrays
        matlab::data::ArrayFactory factory;
        
        // Source image
        auto dimsSrc = factory.createArray<std::size_t>({1, 3}, 
            {static_cast<std::size_t>(rgbSrc.rows), 
             static_cast<std::size_t>(rgbSrc.cols), 
             static_cast<std::size_t>(rgbSrc.channels())});
        auto matlabSrc = factory.createArray<uint8_t>(dimsSrc);
        auto srcPtr = matlabSrc.release();
        memcpy(srcPtr, rgbSrc.data, rgbSrc.total() * rgbSrc.elemSize());
        
        // Destination image
        auto dimsDst = factory.createArray<std::size_t>({1, 3}, 
            {static_cast<std::size_t>(rgbDst.rows), 
             static_cast<std::size_t>(rgbDst.cols), 
             static_cast<std::size_t>(rgbDst.channels())});
        auto matlabDst = factory.createArray<uint8_t>(dimsDst);
        auto dstPtr = matlabDst.release();
        memcpy(dstPtr, rgbDst.data, rgbDst.total() * rgbDst.elemSize());
        
        // Registered image
        auto dimsReg = factory.createArray<std::size_t>({1, 3}, 
            {static_cast<std::size_t>(rgbRegistered.rows), 
             static_cast<std::size_t>(rgbRegistered.cols), 
             static_cast<std::size_t>(rgbRegistered.channels())});
        auto matlabReg = factory.createArray<uint8_t>(dimsReg);
        auto regPtr = matlabReg.release();
        memcpy(regPtr, rgbRegistered.data, rgbRegistered.total() * rgbRegistered.elemSize());
        
        // Set variables in MATLAB workspace
        matlabPtr->setVariable(u"sourceImage", matlabSrc);
        matlabPtr->setVariable(u"destinationImage", matlabDst);
        matlabPtr->setVariable(u"registeredImage", matlabReg);
        
        // Execute MATLAB commands
        string methodName = getRegistrationMethodName(method);
        string matlabCmd = "figure; subplot(1,3,1); imshow(sourceImage); title('Source'); "
                          "subplot(1,3,2); imshow(destinationImage); title('Destination'); "
                          "subplot(1,3,3); imshow(registeredImage); title('" + methodName + "');";
        matlabPtr->eval(matlab::engine::convertUTF8StringToUTF16String(matlabCmd));
        
        // Display registration information
        matlabPtr->eval(u"fprintf('Registration Method: " + matlab::engine::convertUTF8StringToUTF16String(methodName) + "\\n');");
        
        cout << "Registration data sent to MATLAB successfully!" << endl;
        
    } catch (const std::exception& e) {
        cerr << "Error sending registration data to MATLAB: " << e.what() << endl;
    }
}

/**
 * @brief Main function for image registration and alignment
 * @return int Exit status
 */
int main() {
    cout << "=== Image Registration and Alignment - Intermediate Level 18 ===" << endl;
    cout << "This program demonstrates image registration and alignment techniques." << endl;
    
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
        
        // Initialize registration parameters
        RegistrationParams params;
        params.featureThreshold = 0.7;
        params.maxFeatures = 1000;
        params.matchThreshold = 0.75;
        params.ransacThreshold = 3.0;
        params.maxIterations = 2000;
        params.templateThreshold = 0.8;
        params.phaseCorrelationSize = 256;
        params.eccThreshold = 1e-6;
        params.eccMaxIterations = 50;
        params.homographyThreshold = 3.0;
        params.affineThreshold = 3.0;
        params.similarityThreshold = 3.0;
        params.translationThreshold = 3.0;
        params.rotationThreshold = 3.0;
        
        // Initialize registration method
        RegistrationMethod currentMethod = FEATURE_BASED;
        
        // Create Mat objects for frame processing
        Mat frame, prevFrame, registered, visualization;
        
        cout << "\nStarting camera feed with image registration..." << endl;
        cout << "Controls:" << endl;
        cout << "  'q' - Quit" << endl;
        cout << "  '0' - Feature Based" << endl;
        cout << "  '1' - Template Matching" << endl;
        cout << "  '2' - Phase Correlation" << endl;
        cout << "  '3' - ECC" << endl;
        cout << "  '4' - Homography" << endl;
        cout << "  '5' - Affine" << endl;
        cout << "  '6' - Similarity" << endl;
        cout << "  '7' - Translation" << endl;
        cout << "  '8' - Rotation" << endl;
        cout << "  'c' - Capture reference frame" << endl;
        cout << "  'm' - Send to MATLAB" << endl;
        cout << "  's' - Save current registration" << endl;
        
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
            
            // Apply registration if we have a reference frame
            if (hasReference) {
                bool success = applyRegistration(prevFrame, frame, registered, currentMethod, params);
                if (success) {
                    // Create visualization
                    visualization = createRegistrationVisualization(prevFrame, frame, registered);
                    
                    // Display the visualization
                    imshow("Image Registration and Alignment", visualization);
                } else {
                    // Display original frames if registration failed
                    Mat comparison;
                    hconcat(prevFrame, frame, comparison);
                    imshow("Image Registration and Alignment", comparison);
                }
            } else {
                // Display current frame
                imshow("Image Registration and Alignment", frame);
            }
            
            // Handle keyboard input
            char key = waitKey(1) & 0xFF;
            
            if (key == 'q' || key == 27) { // 'q' or ESC to quit
                cout << "Quitting..." << endl;
                break;
            }
            else if (key >= '0' && key <= '8') { // Method selection
                currentMethod = static_cast<RegistrationMethod>(key - '0');
                cout << "Selected method: " << getRegistrationMethodName(currentMethod) << endl;
            }
            else if (key == 'c') { // Capture reference frame
                frame.copyTo(prevFrame);
                hasReference = true;
                cout << "Reference frame captured!" << endl;
            }
            else if (key == 'm') { // Send to MATLAB
                if (hasReference) {
                    sendRegistrationToMATLAB(matlabPtr, prevFrame, frame, registered, currentMethod, params);
                }
            }
            else if (key == 's') { // Save current registration
                if (hasReference) {
                    string filename = "registration_" + getRegistrationMethodName(currentMethod) + ".jpg";
                    imwrite(filename, visualization);
                    cout << "Registration saved as: " << filename << endl;
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
 * g++ -std=c++17 camera_intermediate_18.cpp -o camera_intermediate_18 \
 *     `pkg-config --cflags --libs opencv4` \
 *     -I/Applications/MATLAB_R2023b.app/extern/include \
 *     -L/Applications/MATLAB_R2023b.app/bin/maci64 \
 *     -lMatlabDataArray -lMatlabEngine
 * 
 * @brief Usage:
 * 1. Make sure your camera is connected and working
 * 2. Run the executable: ./camera_intermediate_18
 * 3. Press 'c' to capture a reference frame
 * 4. Use keyboard controls to switch between registration methods
 * 5. Press 'm' to send data to MATLAB
 * 6. Press 's' to save current registration
 * 
 * @brief Learning Objectives:
 * - Understand image registration principles
 * - Learn feature-based registration techniques
 * - Understand template matching and phase correlation
 * - Learn ECC and geometric transformation registration
 * - Understand homography and affine registration
 * - Learn similarity and translation registration
 * - Learn MATLAB integration for registration analysis
 * - Understand registration applications in computer vision
 */
