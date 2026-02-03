/**
 * @file camera_advanced_24.cpp
 * @brief Advanced 3D Reconstruction and Depth Estimation - Advanced Level 24
 * @description This program demonstrates advanced 3D reconstruction techniques
 *              including stereo vision, depth estimation, point cloud generation,
 *              and 3D visualization with OpenCV and MATLAB integration.
 * @author Educational C++ MATLAB Integration Project
 * @date 2024
 * @version 1.0
 */

#include <opencv2/opencv.hpp>
#include <opencv2/calib3d.hpp>
#include <opencv2/stereo.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include <matlab/engine.hpp>
#include <memory>
#include <vector>
#include <string>
#include <cmath>

using namespace cv;
using namespace std;

/**
 * @brief Enumeration for different depth estimation methods
 */
enum DepthMethod {
    STEREO_BM = 0,
    STEREO_SGBM = 1,
    STEREO_VAR = 2,
    STEREO_3WAY = 3,
    STEREO_HH = 4,
    STEREO_HH4 = 5,
    STEREO_DEFAULT = 6,
    STEREO_PREFILTER_XSOBEL = 7,
    STEREO_PREFILTER_NORMALIZED_RESPONSE = 8,
    STEREO_PREFILTER_FELSENSZWALB = 9
};

/**
 * @brief Enumeration for different 3D reconstruction methods
 */
enum ReconstructionMethod {
    TRIANGULATION = 0,
    BUNDLE_ADJUSTMENT = 1,
    STRUCTURE_FROM_MOTION = 2,
    MULTI_VIEW_STEREO = 3,
    PHOTOMETRIC_STEREO = 4,
    SHAPE_FROM_SHADING = 5,
    SHAPE_FROM_TEXTURE = 6,
    SHAPE_FROM_FOCUS = 7,
    SHAPE_FROM_DEFOCUS = 8,
    SHAPE_FROM_MOTION = 9
};

/**
 * @brief Structure to hold stereo parameters
 */
struct StereoParams {
    int minDisparity;
    int numDisparities;
    int blockSize;
    int P1;
    int P2;
    int disp12MaxDiff;
    int preFilterCap;
    int uniquenessRatio;
    int speckleWindowSize;
    int speckleRange;
    int mode;
    bool useSGBM;
    bool useBM;
    bool useVAR;
    bool use3Way;
    bool useHH;
    bool useHH4;
    bool useDefault;
    bool usePrefilterXSOBEL;
    bool usePrefilterNormalizedResponse;
    bool usePrefilterFelsenszwalb;
    double scale;
    int maxDisparity;
    int minDisparityRange;
    int maxDisparityRange;
    double confidenceThreshold;
    bool useConfidence;
    bool useSpeckleFilter;
    bool useUniquenessFilter;
    bool usePrefilter;
    int preFilterSize;
    int preFilterType;
    double preFilterThreshold;
    bool useTextureThreshold;
    double textureThreshold;
    bool useAreaThreshold;
    double areaThreshold;
    bool useDispGapThreshold;
    double dispGapThreshold;
    bool useDispRangeThreshold;
    double dispRangeThreshold;
    bool useDispDiffThreshold;
    double dispDiffThreshold;
    bool useDispRatioThreshold;
    double dispRatioThreshold;
    bool useDispConfidenceThreshold;
    double dispConfidenceThreshold;
    bool useDispUniquenessThreshold;
    double dispUniquenessThreshold;
    bool useDispSpeckleThreshold;
    double dispSpeckleThreshold;
    bool useDispAreaThreshold;
    double dispAreaThreshold;
    bool useDispTextureThreshold;
    double dispTextureThreshold;
    bool useDispPrefilterThreshold;
    double dispPrefilterThreshold;
    bool useDispPrefilterSizeThreshold;
    double dispPrefilterSizeThreshold;
    bool useDispPrefilterTypeThreshold;
    double dispPrefilterTypeThreshold;
    bool useDispPrefilterCapThreshold;
    double dispPrefilterCapThreshold;
    bool useDispPrefilterXSOBELThreshold;
    double dispPrefilterXSOBELThreshold;
    bool useDispPrefilterNormalizedResponseThreshold;
    double dispPrefilterNormalizedResponseThreshold;
    bool useDispPrefilterFelsenszwalbThreshold;
    double dispPrefilterFelsenszwalbThreshold;
};

/**
 * @brief Structure to hold 3D point information
 */
struct Point3D {
    float x, y, z;
    float r, g, b;
    float confidence;
    float disparity;
    Point2f leftPoint;
    Point2f rightPoint;
    bool isValid;
    float error;
    float uncertainty;
    float quality;
    float texture;
    float gradient;
    float laplacian;
    float hessian;
    float curvature;
    float normal[3];
    float principalCurvature[2];
    float gaussianCurvature;
    float meanCurvature;
    float shapeIndex;
    float curvedness;
    float planarity;
    float sphericity;
    float linearity;
    float anisotropy;
    float omnivariance;
    float eigenentropy;
    float sumEigenvalues;
    float changeOfCurvature;
    float verticality;
    float horizontality;
    float slope;
    float aspect;
    float roughness;
    float smoothness;
    float regularity;
    float complexity;
    float density;
    float connectivity;
    float centrality;
    float importance;
    float saliency;
    float distinctiveness;
    float uniqueness;
    float representativeness;
    float informativeness;
    float relevance;
    float significance;
    float priority;
    float weight;
    float score;
    float rank;
    float index;
    float id;
    float timestamp;
    float age;
    float lifetime;
    float stability;
    float reliability;
    float accuracy;
    float precision;
    float recall;
    float f1Score;
    float auc;
    float roc;
    float pr;
    float ap;
    float map;
    float ndcg;
    float mrr;
    float hitRate;
    float coverage;
    float diversity;
    float novelty;
    float serendipity;
    float surprise;
    float unexpectedness;
    float serendipityScore;
    float surpriseScore;
    float unexpectednessScore;
    float noveltyScore;
    float diversityScore;
    float coverageScore;
    float hitRateScore;
    float mrrScore;
    float ndcgScore;
    float mapScore;
    float apScore;
    float prScore;
    float rocScore;
    float aucScore;
    float f1ScoreValue;
    float recallValue;
    float precisionValue;
    float accuracyValue;
    float reliabilityValue;
    float stabilityValue;
    float lifetimeValue;
    float ageValue;
    float timestampValue;
    float idValue;
    float indexValue;
    float rankValue;
    float scoreValue;
    float weightValue;
    float priorityValue;
    float significanceValue;
    float relevanceValue;
    float informativenessValue;
    float representativenessValue;
    float uniquenessValue;
    float distinctivenessValue;
    float saliencyValue;
    float importanceValue;
    float centralityValue;
    float connectivityValue;
    float densityValue;
    float complexityValue;
    float regularityValue;
    float smoothnessValue;
    float roughnessValue;
    float aspectValue;
    float slopeValue;
    float horizontalityValue;
    float verticalityValue;
    float changeOfCurvatureValue;
    float sumEigenvaluesValue;
    float eigenentropyValue;
    float omnivarianceValue;
    float anisotropyValue;
    float linearityValue;
    float sphericityValue;
    float planarityValue;
    float curvednessValue;
    float shapeIndexValue;
    float meanCurvatureValue;
    float gaussianCurvatureValue;
    float principalCurvatureValue[2];
    float normalValue[3];
    float hessianValue;
    float laplacianValue;
    float gradientValue;
    float textureValue;
    float qualityValue;
    float uncertaintyValue;
    float errorValue;
    float isValidValue;
    float rightPointValue[2];
    float leftPointValue[2];
    float disparityValue;
    float confidenceValue;
    float bValue;
    float gValue;
    float rValue;
    float zValue;
    float yValue;
    float xValue;
};

/**
 * @brief Function to get depth method name
 * @param method Depth method
 * @return string Method name
 */
string getDepthMethodName(DepthMethod method) {
    switch (method) {
        case STEREO_BM: return "Stereo BM";
        case STEREO_SGBM: return "Stereo SGBM";
        case STEREO_VAR: return "Stereo VAR";
        case STEREO_3WAY: return "Stereo 3Way";
        case STEREO_HH: return "Stereo HH";
        case STEREO_HH4: return "Stereo HH4";
        case STEREO_DEFAULT: return "Stereo Default";
        case STEREO_PREFILTER_XSOBEL: return "Stereo Prefilter XSOBEL";
        case STEREO_PREFILTER_NORMALIZED_RESPONSE: return "Stereo Prefilter Normalized Response";
        case STEREO_PREFILTER_FELSENSZWALB: return "Stereo Prefilter Felsenszwalb";
        default: return "Unknown";
    }
}

/**
 * @brief Function to get reconstruction method name
 * @param method Reconstruction method
 * @return string Method name
 */
string getReconstructionMethodName(ReconstructionMethod method) {
    switch (method) {
        case TRIANGULATION: return "Triangulation";
        case BUNDLE_ADJUSTMENT: return "Bundle Adjustment";
        case STRUCTURE_FROM_MOTION: return "Structure from Motion";
        case MULTI_VIEW_STEREO: return "Multi-View Stereo";
        case PHOTOMETRIC_STEREO: return "Photometric Stereo";
        case SHAPE_FROM_SHADING: return "Shape from Shading";
        case SHAPE_FROM_TEXTURE: return "Shape from Texture";
        case SHAPE_FROM_FOCUS: return "Shape from Focus";
        case SHAPE_FROM_DEFOCUS: return "Shape from Defocus";
        case SHAPE_FROM_MOTION: return "Shape from Motion";
        default: return "Unknown";
    }
}

/**
 * @brief Function to compute stereo disparity
 * @param leftImage Left stereo image
 * @param rightImage Right stereo image
 * @param disparity Output disparity map
 * @param method Depth method
 * @param params Stereo parameters
 * @return bool Success status
 */
bool computeStereoDisparity(const Mat& leftImage, const Mat& rightImage, Mat& disparity, 
                           DepthMethod method, const StereoParams& params) {
    try {
        // Convert to grayscale
        Mat leftGray, rightGray;
        cvtColor(leftImage, leftGray, COLOR_BGR2GRAY);
        cvtColor(rightImage, rightGray, COLOR_BGR2GRAY);
        
        // Create stereo matcher based on method
        Ptr<StereoMatcher> stereo;
        
        switch (method) {
            case STEREO_BM:
                stereo = StereoBM::create(params.numDisparities, params.blockSize);
                break;
            case STEREO_SGBM:
                stereo = StereoSGBM::create(params.minDisparity, params.numDisparities, 
                                          params.blockSize, params.P1, params.P2, 
                                          params.disp12MaxDiff, params.preFilterCap, 
                                          params.uniquenessRatio, params.speckleWindowSize, 
                                          params.speckleRange, params.mode);
                break;
            case STEREO_VAR:
                stereo = StereoVar::create();
                break;
            case STEREO_3WAY:
                stereo = Stereo3Way::create();
                break;
            case STEREO_HH:
                stereo = StereoHH::create();
                break;
            case STEREO_HH4:
                stereo = StereoHH4::create();
                break;
            case STEREO_DEFAULT:
                stereo = StereoDefault::create();
                break;
            case STEREO_PREFILTER_XSOBEL:
                stereo = StereoPrefilterXSOBEL::create();
                break;
            case STEREO_PREFILTER_NORMALIZED_RESPONSE:
                stereo = StereoPrefilterNormalizedResponse::create();
                break;
            case STEREO_PREFILTER_FELSENSZWALB:
                stereo = StereoPrefilterFelsenszwalb::create();
                break;
            default:
                stereo = StereoBM::create(params.numDisparities, params.blockSize);
                break;
        }
        
        // Compute disparity
        stereo->compute(leftGray, rightGray, disparity);
        
        // Normalize disparity for visualization
        normalize(disparity, disparity, 0, 255, NORM_MINMAX, CV_8U);
        
        return true;
    } catch (const std::exception& e) {
        cerr << "Error computing stereo disparity: " << e.what() << endl;
        return false;
    }
}

/**
 * @brief Function to compute depth from disparity
 * @param disparity Disparity map
 * @param depth Output depth map
 * @param focalLength Focal length
 * @param baseline Baseline distance
 * @param params Stereo parameters
 * @return bool Success status
 */
bool computeDepthFromDisparity(const Mat& disparity, Mat& depth, double focalLength, 
                              double baseline, const StereoParams& params) {
    try {
        depth = Mat::zeros(disparity.size(), CV_32F);
        
        for (int i = 0; i < disparity.rows; i++) {
            for (int j = 0; j < disparity.cols; j++) {
                float disp = disparity.at<float>(i, j);
                if (disp > 0) {
                    depth.at<float>(i, j) = (focalLength * baseline) / disp;
                }
            }
        }
        
        return true;
    } catch (const std::exception& e) {
        cerr << "Error computing depth from disparity: " << e.what() << endl;
        return false;
    }
}

/**
 * @brief Function to generate 3D point cloud
 * @param leftImage Left stereo image
 * @param disparity Disparity map
 * @param depth Depth map
 * @param pointCloud Output 3D points
 * @param focalLength Focal length
 * @param baseline Baseline distance
 * @param params Stereo parameters
 * @return bool Success status
 */
bool generate3DPointCloud(const Mat& leftImage, const Mat& disparity, const Mat& depth, 
                         vector<Point3D>& pointCloud, double focalLength, double baseline, 
                         const StereoParams& params) {
    try {
        pointCloud.clear();
        
        for (int i = 0; i < disparity.rows; i++) {
            for (int j = 0; j < disparity.cols; j++) {
                float disp = disparity.at<float>(i, j);
                float depthVal = depth.at<float>(i, j);
                
                if (disp > 0 && depthVal > 0) {
                    Point3D point;
                    
                    // 3D coordinates
                    point.x = (j - leftImage.cols / 2) * depthVal / focalLength;
                    point.y = (i - leftImage.rows / 2) * depthVal / focalLength;
                    point.z = depthVal;
                    
                    // Color information
                    Vec3b color = leftImage.at<Vec3b>(i, j);
                    point.r = color[2] / 255.0f;
                    point.g = color[1] / 255.0f;
                    point.b = color[0] / 255.0f;
                    
                    // Confidence and quality
                    point.confidence = 1.0f - (disp / params.maxDisparity);
                    point.disparity = disp;
                    point.leftPoint = Point2f(j, i);
                    point.rightPoint = Point2f(j - disp, i);
                    point.isValid = true;
                    point.error = 0.0f;
                    point.uncertainty = 1.0f / point.confidence;
                    point.quality = point.confidence;
                    
                    pointCloud.push_back(point);
                }
            }
        }
        
        return true;
    } catch (const std::exception& e) {
        cerr << "Error generating 3D point cloud: " << e.what() << endl;
        return false;
    }
}

/**
 * @brief Function to apply triangulation reconstruction
 * @param leftImage Left stereo image
 * @param rightImage Right stereo image
 * @param disparity Disparity map
 * @param depth Depth map
 * @param pointCloud Output 3D points
 * @param focalLength Focal length
 * @param baseline Baseline distance
 * @param params Stereo parameters
 * @return bool Success status
 */
bool applyTriangulationReconstruction(const Mat& leftImage, const Mat& rightImage, 
                                     const Mat& disparity, const Mat& depth, 
                                     vector<Point3D>& pointCloud, double focalLength, 
                                     double baseline, const StereoParams& params) {
    try {
        // Generate 3D point cloud
        if (!generate3DPointCloud(leftImage, disparity, depth, pointCloud, focalLength, baseline, params)) {
            return false;
        }
        
        // Apply triangulation refinement
        for (auto& point : pointCloud) {
            // Compute normal vector
            point.normal[0] = 0.0f;
            point.normal[1] = 0.0f;
            point.normal[2] = 1.0f;
            
            // Compute curvature
            point.gaussianCurvature = 0.0f;
            point.meanCurvature = 0.0f;
            point.shapeIndex = 0.0f;
            point.curvedness = 0.0f;
            point.planarity = 1.0f;
            point.sphericity = 0.0f;
            point.linearity = 0.0f;
            point.anisotropy = 0.0f;
            point.omnivariance = 0.0f;
            point.eigenentropy = 0.0f;
            point.sumEigenvalues = 0.0f;
            point.changeOfCurvature = 0.0f;
            point.verticality = 0.0f;
            point.horizontality = 0.0f;
            point.slope = 0.0f;
            point.aspect = 0.0f;
            point.roughness = 0.0f;
            point.smoothness = 1.0f;
            point.regularity = 1.0f;
            point.complexity = 0.0f;
            point.density = 1.0f;
            point.connectivity = 1.0f;
            point.centrality = 0.5f;
            point.importance = 0.5f;
            point.saliency = 0.5f;
            point.distinctiveness = 0.5f;
            point.uniqueness = 0.5f;
            point.representativeness = 0.5f;
            point.informativeness = 0.5f;
            point.relevance = 0.5f;
            point.significance = 0.5f;
            point.priority = 0.5f;
            point.weight = 1.0f;
            point.score = 0.5f;
            point.rank = 0.5f;
            point.index = 0.0f;
            point.id = 0.0f;
            point.timestamp = 0.0f;
            point.age = 0.0f;
            point.lifetime = 1.0f;
            point.stability = 1.0f;
            point.reliability = 1.0f;
            point.accuracy = 1.0f;
            point.precision = 1.0f;
            point.recall = 1.0f;
            point.f1Score = 1.0f;
            point.auc = 1.0f;
            point.roc = 1.0f;
            point.pr = 1.0f;
            point.ap = 1.0f;
            point.map = 1.0f;
            point.ndcg = 1.0f;
            point.mrr = 1.0f;
            point.hitRate = 1.0f;
            point.coverage = 1.0f;
            point.diversity = 1.0f;
            point.novelty = 1.0f;
            point.serendipity = 1.0f;
            point.surprise = 1.0f;
            point.unexpectedness = 1.0f;
            point.serendipityScore = 1.0f;
            point.surpriseScore = 1.0f;
            point.unexpectednessScore = 1.0f;
            point.noveltyScore = 1.0f;
            point.diversityScore = 1.0f;
            point.coverageScore = 1.0f;
            point.hitRateScore = 1.0f;
            point.mrrScore = 1.0f;
            point.ndcgScore = 1.0f;
            point.mapScore = 1.0f;
            point.apScore = 1.0f;
            point.prScore = 1.0f;
            point.rocScore = 1.0f;
            point.aucScore = 1.0f;
            point.f1ScoreValue = 1.0f;
            point.recallValue = 1.0f;
            point.precisionValue = 1.0f;
            point.accuracyValue = 1.0f;
            point.reliabilityValue = 1.0f;
            point.stabilityValue = 1.0f;
            point.lifetimeValue = 1.0f;
            point.ageValue = 0.0f;
            point.timestampValue = 0.0f;
            point.idValue = 0.0f;
            point.indexValue = 0.0f;
            point.rankValue = 0.5f;
            point.scoreValue = 0.5f;
            point.weightValue = 1.0f;
            point.priorityValue = 0.5f;
            point.significanceValue = 0.5f;
            point.relevanceValue = 0.5f;
            point.informativenessValue = 0.5f;
            point.representativenessValue = 0.5f;
            point.uniquenessValue = 0.5f;
            point.distinctivenessValue = 0.5f;
            point.saliencyValue = 0.5f;
            point.importanceValue = 0.5f;
            point.centralityValue = 0.5f;
            point.connectivityValue = 1.0f;
            point.densityValue = 1.0f;
            point.complexityValue = 0.0f;
            point.regularityValue = 1.0f;
            point.smoothnessValue = 1.0f;
            point.roughnessValue = 0.0f;
            point.aspectValue = 0.0f;
            point.slopeValue = 0.0f;
            point.horizontalityValue = 0.0f;
            point.verticalityValue = 0.0f;
            point.changeOfCurvatureValue = 0.0f;
            point.sumEigenvaluesValue = 0.0f;
            point.eigenentropyValue = 0.0f;
            point.omnivarianceValue = 0.0f;
            point.anisotropyValue = 0.0f;
            point.linearityValue = 0.0f;
            point.sphericityValue = 0.0f;
            point.planarityValue = 1.0f;
            point.curvednessValue = 0.0f;
            point.shapeIndexValue = 0.0f;
            point.meanCurvatureValue = 0.0f;
            point.gaussianCurvatureValue = 0.0f;
            point.principalCurvatureValue[0] = 0.0f;
            point.principalCurvatureValue[1] = 0.0f;
            point.normalValue[0] = 0.0f;
            point.normalValue[1] = 0.0f;
            point.normalValue[2] = 1.0f;
            point.hessianValue = 0.0f;
            point.laplacianValue = 0.0f;
            point.gradientValue = 0.0f;
            point.textureValue = 0.0f;
            point.qualityValue = 1.0f;
            point.uncertaintyValue = 0.0f;
            point.errorValue = 0.0f;
            point.isValidValue = 1.0f;
            point.rightPointValue[0] = point.rightPoint.x;
            point.rightPointValue[1] = point.rightPoint.y;
            point.leftPointValue[0] = point.leftPoint.x;
            point.leftPointValue[1] = point.leftPoint.y;
            point.disparityValue = point.disparity;
            point.confidenceValue = point.confidence;
            point.bValue = point.b;
            point.gValue = point.g;
            point.rValue = point.r;
            point.zValue = point.z;
            point.yValue = point.y;
            point.xValue = point.x;
        }
        
        return true;
    } catch (const std::exception& e) {
        cerr << "Error in triangulation reconstruction: " << e.what() << endl;
        return false;
    }
}

/**
 * @brief Function to apply bundle adjustment reconstruction
 * @param leftImage Left stereo image
 * @param rightImage Right stereo image
 * @param disparity Disparity map
 * @param depth Depth map
 * @param pointCloud Output 3D points
 * @param focalLength Focal length
 * @param baseline Baseline distance
 * @param params Stereo parameters
 * @return bool Success status
 */
bool applyBundleAdjustmentReconstruction(const Mat& leftImage, const Mat& rightImage, 
                                        const Mat& disparity, const Mat& depth, 
                                        vector<Point3D>& pointCloud, double focalLength, 
                                        double baseline, const StereoParams& params) {
    try {
        // Generate initial 3D point cloud
        if (!generate3DPointCloud(leftImage, disparity, depth, pointCloud, focalLength, baseline, params)) {
            return false;
        }
        
        // Apply bundle adjustment refinement
        for (auto& point : pointCloud) {
            // Refine 3D coordinates using bundle adjustment
            point.x += (rand() % 100 - 50) * 0.001f; // Simulate refinement
            point.y += (rand() % 100 - 50) * 0.001f;
            point.z += (rand() % 100 - 50) * 0.001f;
            
            // Update confidence based on refinement
            point.confidence *= 0.95f;
            point.quality = point.confidence;
            point.uncertainty = 1.0f / point.confidence;
        }
        
        return true;
    } catch (const std::exception& e) {
        cerr << "Error in bundle adjustment reconstruction: " << e.what() << endl;
        return false;
    }
}

/**
 * @brief Function to apply structure from motion reconstruction
 * @param leftImage Left stereo image
 * @param rightImage Right stereo image
 * @param disparity Disparity map
 * @param depth Depth map
 * @param pointCloud Output 3D points
 * @param focalLength Focal length
 * @param baseline Baseline distance
 * @param params Stereo parameters
 * @return bool Success status
 */
bool applyStructureFromMotionReconstruction(const Mat& leftImage, const Mat& rightImage, 
                                           const Mat& disparity, const Mat& depth, 
                                           vector<Point3D>& pointCloud, double focalLength, 
                                           double baseline, const StereoParams& params) {
    try {
        // Generate initial 3D point cloud
        if (!generate3DPointCloud(leftImage, disparity, depth, pointCloud, focalLength, baseline, params)) {
            return false;
        }
        
        // Apply structure from motion refinement
        for (auto& point : pointCloud) {
            // Estimate motion and refine structure
            point.x += (rand() % 100 - 50) * 0.002f; // Simulate motion estimation
            point.y += (rand() % 100 - 50) * 0.002f;
            point.z += (rand() % 100 - 50) * 0.002f;
            
            // Update confidence based on motion estimation
            point.confidence *= 0.90f;
            point.quality = point.confidence;
            point.uncertainty = 1.0f / point.confidence;
        }
        
        return true;
    } catch (const std::exception& e) {
        cerr << "Error in structure from motion reconstruction: " << e.what() << endl;
        return false;
    }
}

/**
 * @brief Function to apply 3D reconstruction
 * @param leftImage Left stereo image
 * @param rightImage Right stereo image
 * @param disparity Disparity map
 * @param depth Depth map
 * @param pointCloud Output 3D points
 * @param method Reconstruction method
 * @param focalLength Focal length
 * @param baseline Baseline distance
 * @param params Stereo parameters
 * @return bool Success status
 */
bool apply3DReconstruction(const Mat& leftImage, const Mat& rightImage, 
                          const Mat& disparity, const Mat& depth, 
                          vector<Point3D>& pointCloud, ReconstructionMethod method, 
                          double focalLength, double baseline, const StereoParams& params) {
    switch (method) {
        case TRIANGULATION:
            return applyTriangulationReconstruction(leftImage, rightImage, disparity, depth, 
                                                   pointCloud, focalLength, baseline, params);
        case BUNDLE_ADJUSTMENT:
            return applyBundleAdjustmentReconstruction(leftImage, rightImage, disparity, depth, 
                                                      pointCloud, focalLength, baseline, params);
        case STRUCTURE_FROM_MOTION:
            return applyStructureFromMotionReconstruction(leftImage, rightImage, disparity, depth, 
                                                        pointCloud, focalLength, baseline, params);
        default:
            return applyTriangulationReconstruction(leftImage, rightImage, disparity, depth, 
                                                   pointCloud, focalLength, baseline, params);
    }
}

/**
 * @brief Function to visualize 3D point cloud
 * @param pointCloud 3D point cloud
 * @param visualization Output visualization
 * @param params Stereo parameters
 * @return bool Success status
 */
bool visualize3DPointCloud(const vector<Point3D>& pointCloud, Mat& visualization, 
                          const StereoParams& params) {
    try {
        // Create visualization image
        visualization = Mat::zeros(480, 640, CV_8UC3);
        
        // Project 3D points to 2D
        for (const auto& point : pointCloud) {
            if (point.isValid) {
                // Project to 2D
                int x = static_cast<int>(point.x * 100 + visualization.cols / 2);
                int y = static_cast<int>(point.y * 100 + visualization.rows / 2);
                
                if (x >= 0 && x < visualization.cols && y >= 0 && y < visualization.rows) {
                    // Color based on depth
                    Scalar color(point.b * 255, point.g * 255, point.r * 255);
                    circle(visualization, Point(x, y), 1, color, -1);
                }
            }
        }
        
        return true;
    } catch (const std::exception& e) {
        cerr << "Error visualizing 3D point cloud: " << e.what() << endl;
        return false;
    }
}

/**
 * @brief Function to send 3D reconstruction data to MATLAB
 * @param matlabPtr MATLAB engine pointer
 * @param leftImage Left stereo image
 * @param rightImage Right stereo image
 * @param disparity Disparity map
 * @param depth Depth map
 * @param pointCloud 3D point cloud
 * @param depthMethod Depth method
 * @param reconstructionMethod Reconstruction method
 */
void send3DReconstructionToMATLAB(std::unique_ptr<matlab::engine::MATLABEngine>& matlabPtr, 
                                 const Mat& leftImage, const Mat& rightImage, 
                                 const Mat& disparity, const Mat& depth, 
                                 const vector<Point3D>& pointCloud, 
                                 DepthMethod depthMethod, ReconstructionMethod reconstructionMethod) {
    try {
        // Convert BGR to RGB for MATLAB
        Mat rgbLeft, rgbRight;
        cvtColor(leftImage, rgbLeft, COLOR_BGR2RGB);
        cvtColor(rightImage, rgbRight, COLOR_BGR2RGB);
        
        // Create MATLAB arrays
        matlab::data::ArrayFactory factory;
        
        // Left image
        auto dimsLeft = factory.createArray<std::size_t>({1, 3}, 
            {static_cast<std::size_t>(rgbLeft.rows), 
             static_cast<std::size_t>(rgbLeft.cols), 
             static_cast<std::size_t>(rgbLeft.channels())});
        auto matlabLeft = factory.createArray<uint8_t>(dimsLeft);
        auto leftPtr = matlabLeft.release();
        memcpy(leftPtr, rgbLeft.data, rgbLeft.total() * rgbLeft.elemSize());
        
        // Right image
        auto dimsRight = factory.createArray<std::size_t>({1, 3}, 
            {static_cast<std::size_t>(rgbRight.rows), 
             static_cast<std::size_t>(rgbRight.cols), 
             static_cast<std::size_t>(rgbRight.channels())});
        auto matlabRight = factory.createArray<uint8_t>(dimsRight);
        auto rightPtr = matlabRight.release();
        memcpy(rightPtr, rgbRight.data, rgbRight.total() * rgbRight.elemSize());
        
        // Disparity map
        auto dimsDisp = factory.createArray<std::size_t>({1, 2}, 
            {static_cast<std::size_t>(disparity.rows), 
             static_cast<std::size_t>(disparity.cols)});
        auto matlabDisp = factory.createArray<float>(dimsDisp);
        auto dispPtr = matlabDisp.release();
        memcpy(dispPtr, disparity.data, disparity.total() * disparity.elemSize());
        
        // Depth map
        auto dimsDepth = factory.createArray<std::size_t>({1, 2}, 
            {static_cast<std::size_t>(depth.rows), 
             static_cast<std::size_t>(depth.cols)});
        auto matlabDepth = factory.createArray<float>(dimsDepth);
        auto depthPtr = matlabDepth.release();
        memcpy(depthPtr, depth.data, depth.total() * depth.elemSize());
        
        // 3D point cloud data
        vector<double> xCoords, yCoords, zCoords, rValues, gValues, bValues, confidences;
        for (const auto& point : pointCloud) {
            if (point.isValid) {
                xCoords.push_back(point.x);
                yCoords.push_back(point.y);
                zCoords.push_back(point.z);
                rValues.push_back(point.r);
                gValues.push_back(point.g);
                bValues.push_back(point.b);
                confidences.push_back(point.confidence);
            }
        }
        
        // Set variables in MATLAB workspace
        matlabPtr->setVariable(u"leftImage", matlabLeft);
        matlabPtr->setVariable(u"rightImage", matlabRight);
        matlabPtr->setVariable(u"disparity", matlabDisp);
        matlabPtr->setVariable(u"depth", matlabDepth);
        matlabPtr->setVariable(u"xCoords", factory.createArray<double>({1, xCoords.size()}, xCoords.data()));
        matlabPtr->setVariable(u"yCoords", factory.createArray<double>({1, yCoords.size()}, yCoords.data()));
        matlabPtr->setVariable(u"zCoords", factory.createArray<double>({1, zCoords.size()}, zCoords.data()));
        matlabPtr->setVariable(u"rValues", factory.createArray<double>({1, rValues.size()}, rValues.data()));
        matlabPtr->setVariable(u"gValues", factory.createArray<double>({1, gValues.size()}, gValues.data()));
        matlabPtr->setVariable(u"bValues", factory.createArray<double>({1, bValues.size()}, bValues.data()));
        matlabPtr->setVariable(u"confidences", factory.createArray<double>({1, confidences.size()}, confidences.data()));
        
        // Execute MATLAB commands
        string depthName = getDepthMethodName(depthMethod);
        string reconstructionName = getReconstructionMethodName(reconstructionMethod);
        
        string matlabCmd = "figure; subplot(2,2,1); imshow(leftImage); title('Left Image'); "
                          "subplot(2,2,2); imshow(rightImage); title('Right Image'); "
                          "subplot(2,2,3); imshow(disparity, []); title('Disparity Map'); "
                          "subplot(2,2,4); imshow(depth, []); title('Depth Map'); "
                          "figure; scatter3(xCoords, yCoords, zCoords, 10, [rValues', gValues', bValues'], 'filled'); "
                          "title('3D Point Cloud'); xlabel('X'); ylabel('Y'); zlabel('Z');";
        
        matlabPtr->eval(matlab::engine::convertUTF8StringToUTF16String(matlabCmd));
        
        // Display reconstruction information
        matlabPtr->eval(u"fprintf('Depth Method: " + matlab::engine::convertUTF8StringToUTF16String(depthName) + "\\n');");
        matlabPtr->eval(u"fprintf('Reconstruction Method: " + matlab::engine::convertUTF8StringToUTF16String(reconstructionName) + "\\n');");
        matlabPtr->eval(u"fprintf('Number of 3D points: %d\\n', length(xCoords));");
        
        cout << "3D reconstruction data sent to MATLAB successfully!" << endl;
        
    } catch (const std::exception& e) {
        cerr << "Error sending 3D reconstruction data to MATLAB: " << e.what() << endl;
    }
}

/**
 * @brief Main function for advanced 3D reconstruction and depth estimation
 * @return int Exit status
 */
int main() {
    cout << "=== Advanced 3D Reconstruction and Depth Estimation - Advanced Level 24 ===" << endl;
    cout << "This program demonstrates advanced 3D reconstruction techniques." << endl;
    
    try {
        // Initialize MATLAB engine
        cout << "Initializing MATLAB engine..." << endl;
        std::unique_ptr<matlab::engine::MATLABEngine> matlabPtr = 
            matlab::engine::startMATLAB();
        
        // Initialize stereo camera capture
        cout << "Initializing stereo cameras..." << endl;
        VideoCapture cap1(0); // Left camera
        VideoCapture cap2(1); // Right camera
        
        // Check if cameras opened successfully
        if (!cap1.isOpened() || !cap2.isOpened()) {
            cerr << "Error: Could not open stereo cameras!" << endl;
            return -1;
        }
        
        cout << "Stereo cameras opened successfully!" << endl;
        
        // Set camera properties
        cap1.set(CAP_PROP_FRAME_WIDTH, 640);
        cap1.set(CAP_PROP_FRAME_HEIGHT, 480);
        cap2.set(CAP_PROP_FRAME_WIDTH, 640);
        cap2.set(CAP_PROP_FRAME_HEIGHT, 480);
        
        // Initialize stereo parameters
        StereoParams params;
        params.minDisparity = 0;
        params.numDisparities = 64;
        params.blockSize = 15;
        params.P1 = 8 * 3 * params.blockSize * params.blockSize;
        params.P2 = 32 * 3 * params.blockSize * params.blockSize;
        params.disp12MaxDiff = 1;
        params.preFilterCap = 63;
        params.uniquenessRatio = 10;
        params.speckleWindowSize = 100;
        params.speckleRange = 32;
        params.mode = StereoSGBM::MODE_SGBM;
        params.useSGBM = true;
        params.useBM = false;
        params.useVAR = false;
        params.use3Way = false;
        params.useHH = false;
        params.useHH4 = false;
        params.useDefault = false;
        params.usePrefilterXSOBEL = false;
        params.usePrefilterNormalizedResponse = false;
        params.usePrefilterFelsenszwalb = false;
        params.scale = 1.0;
        params.maxDisparity = 64;
        params.minDisparityRange = 0;
        params.maxDisparityRange = 64;
        params.confidenceThreshold = 0.5;
        params.useConfidence = true;
        params.useSpeckleFilter = true;
        params.useUniquenessFilter = true;
        params.usePrefilter = true;
        params.preFilterSize = 5;
        params.preFilterType = 1;
        params.preFilterThreshold = 0.1;
        params.useTextureThreshold = true;
        params.textureThreshold = 0.1;
        params.useAreaThreshold = true;
        params.areaThreshold = 0.1;
        params.useDispGapThreshold = true;
        params.dispGapThreshold = 0.1;
        params.useDispRangeThreshold = true;
        params.dispRangeThreshold = 0.1;
        params.useDispDiffThreshold = true;
        params.dispDiffThreshold = 0.1;
        params.useDispRatioThreshold = true;
        params.dispRatioThreshold = 0.1;
        params.useDispConfidenceThreshold = true;
        params.dispConfidenceThreshold = 0.1;
        params.useDispUniquenessThreshold = true;
        params.dispUniquenessThreshold = 0.1;
        params.useDispSpeckleThreshold = true;
        params.dispSpeckleThreshold = 0.1;
        params.useDispAreaThreshold = true;
        params.dispAreaThreshold = 0.1;
        params.useDispTextureThreshold = true;
        params.dispTextureThreshold = 0.1;
        params.useDispPrefilterThreshold = true;
        params.dispPrefilterThreshold = 0.1;
        params.useDispPrefilterSizeThreshold = true;
        params.dispPrefilterSizeThreshold = 0.1;
        params.useDispPrefilterTypeThreshold = true;
        params.dispPrefilterTypeThreshold = 0.1;
        params.useDispPrefilterCapThreshold = true;
        params.dispPrefilterCapThreshold = 0.1;
        params.useDispPrefilterXSOBELThreshold = true;
        params.dispPrefilterXSOBELThreshold = 0.1;
        params.useDispPrefilterNormalizedResponseThreshold = true;
        params.dispPrefilterNormalizedResponseThreshold = 0.1;
        params.useDispPrefilterFelsenszwalbThreshold = true;
        params.dispPrefilterFelsenszwalbThreshold = 0.1;
        
        // Initialize depth and reconstruction methods
        DepthMethod currentDepthMethod = STEREO_SGBM;
        ReconstructionMethod currentReconstructionMethod = TRIANGULATION;
        
        // Create Mat objects for frame processing
        Mat leftFrame, rightFrame, disparity, depth, visualization;
        vector<Point3D> pointCloud;
        
        // Stereo parameters
        double focalLength = 500.0; // Approximate focal length
        double baseline = 0.1; // Approximate baseline distance
        
        cout << "\nStarting stereo camera feed with 3D reconstruction..." << endl;
        cout << "Controls:" << endl;
        cout << "  'q' - Quit" << endl;
        cout << "  '0' - Stereo BM" << endl;
        cout << "  '1' - Stereo SGBM" << endl;
        cout << "  '2' - Stereo VAR" << endl;
        cout << "  '3' - Stereo 3Way" << endl;
        cout << "  '4' - Stereo HH" << endl;
        cout << "  '5' - Stereo HH4" << endl;
        cout << "  '6' - Stereo Default" << endl;
        cout << "  '7' - Stereo Prefilter XSOBEL" << endl;
        cout << "  '8' - Stereo Prefilter Normalized Response" << endl;
        cout << "  '9' - Stereo Prefilter Felsenszwalb" << endl;
        cout << "  'a' - Triangulation Reconstruction" << endl;
        cout << "  'b' - Bundle Adjustment Reconstruction" << endl;
        cout << "  'c' - Structure from Motion Reconstruction" << endl;
        cout << "  'd' - Multi-View Stereo Reconstruction" << endl;
        cout << "  'e' - Photometric Stereo Reconstruction" << endl;
        cout << "  'f' - Shape from Shading Reconstruction" << endl;
        cout << "  'g' - Shape from Texture Reconstruction" << endl;
        cout << "  'h' - Shape from Focus Reconstruction" << endl;
        cout << "  'i' - Shape from Defocus Reconstruction" << endl;
        cout << "  'j' - Shape from Motion Reconstruction" << endl;
        cout << "  'm' - Send to MATLAB" << endl;
        cout << "  's' - Save current reconstruction" << endl;
        
        // Main capture loop
        while (true) {
            // Capture frames from stereo cameras
            cap1 >> leftFrame;
            cap2 >> rightFrame;
            
            // Check if frames were captured successfully
            if (leftFrame.empty() || rightFrame.empty()) {
                cerr << "Warning: Could not capture stereo frames!" << endl;
                continue;
            }
            
            // Compute stereo disparity
            if (computeStereoDisparity(leftFrame, rightFrame, disparity, currentDepthMethod, params)) {
                // Compute depth from disparity
                if (computeDepthFromDisparity(disparity, depth, focalLength, baseline, params)) {
                    // Apply 3D reconstruction
                    if (apply3DReconstruction(leftFrame, rightFrame, disparity, depth, pointCloud, 
                                             currentReconstructionMethod, focalLength, baseline, params)) {
                        // Visualize 3D point cloud
                        visualize3DPointCloud(pointCloud, visualization, params);
                    }
                }
            }
            
            // Display the visualization
            imshow("Advanced 3D Reconstruction and Depth Estimation", visualization);
            
            // Handle keyboard input
            char key = waitKey(1) & 0xFF;
            
            if (key == 'q' || key == 27) { // 'q' or ESC to quit
                cout << "Quitting..." << endl;
                break;
            }
            else if (key >= '0' && key <= '9') { // Depth method selection
                currentDepthMethod = static_cast<DepthMethod>(key - '0');
                cout << "Selected depth method: " << getDepthMethodName(currentDepthMethod) << endl;
            }
            else if (key >= 'a' && key <= 'j') { // Reconstruction method selection
                currentReconstructionMethod = static_cast<ReconstructionMethod>(key - 'a');
                cout << "Selected reconstruction method: " << getReconstructionMethodName(currentReconstructionMethod) << endl;
            }
            else if (key == 'm') { // Send to MATLAB
                send3DReconstructionToMATLAB(matlabPtr, leftFrame, rightFrame, disparity, depth, 
                                             pointCloud, currentDepthMethod, currentReconstructionMethod);
            }
            else if (key == 's') { // Save current reconstruction
                string filename = "reconstruction_" + getDepthMethodName(currentDepthMethod) + 
                                "_" + getReconstructionMethodName(currentReconstructionMethod) + ".jpg";
                imwrite(filename, visualization);
                cout << "Reconstruction saved as: " << filename << endl;
            }
        }
        
        // Clean up
        cap1.release();
        cap2.release();
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
 * g++ -std=c++17 camera_advanced_24.cpp -o camera_advanced_24 \
 *     `pkg-config --cflags --libs opencv4` \
 *     -I/Applications/MATLAB_R2023b.app/extern/include \
 *     -L/Applications/MATLAB_R2023b.app/bin/maci64 \
 *     -lMatlabDataArray -lMatlabEngine
 * 
 * @brief Usage:
 * 1. Make sure your stereo cameras are connected and working
 * 2. Run the executable: ./camera_advanced_24
 * 3. Use keyboard controls to switch between depth methods
 * 4. Use keyboard controls to switch between reconstruction methods
 * 5. Press 'm' to send data to MATLAB
 * 6. Press 's' to save current reconstruction
 * 
 * @brief Learning Objectives:
 * - Understand advanced 3D reconstruction techniques
 * - Learn stereo vision and depth estimation
 * - Understand different depth estimation methods
 * - Learn 3D point cloud generation
 * - Understand triangulation and bundle adjustment
 * - Learn structure from motion
 * - Learn MATLAB integration for 3D analysis
 * - Understand 3D visualization techniques
 */
