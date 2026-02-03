/**
 * @file camera_advanced_25.cpp
 * @brief Advanced Machine Learning for Computer Vision - Advanced Level 25
 * @description This program demonstrates advanced machine learning techniques
 *              for computer vision including neural networks, deep learning,
 *              feature learning, and classification with OpenCV and MATLAB integration.
 * @author Educational C++ MATLAB Integration Project
 * @date 2024
 * @version 1.0
 */

#include <opencv2/opencv.hpp>
#include <opencv2/dnn.hpp>
#include <opencv2/ml.hpp>
#include <opencv2/features2d.hpp>
#include <iostream>
#include <matlab/engine.hpp>
#include <memory>
#include <vector>
#include <string>
#include <map>
#include <algorithm>
#include <random>

using namespace cv;
using namespace std;

/**
 * @brief Enumeration for different ML algorithms
 */
enum MLAlgorithm {
    SVM_CLASSIFIER = 0,
    RANDOM_FOREST = 1,
    K_NEAREST_NEIGHBORS = 2,
    NAIVE_BAYES = 3,
    DECISION_TREE = 4,
    NEURAL_NETWORK = 5,
    DEEP_LEARNING = 6,
    CONVOLUTIONAL_NN = 7,
    RECURRENT_NN = 8,
    GENERATIVE_ADVERSARIAL_NN = 9
};

/**
 * @brief Enumeration for different feature extraction methods
 */
enum FeatureExtractionMethod {
    HOG_FEATURES = 0,
    LBP_FEATURES = 1,
    SIFT_FEATURES = 2,
    SURF_FEATURES = 3,
    ORB_FEATURES = 4,
    AKAZE_FEATURES = 5,
    BRISK_FEATURES = 6,
    FREAK_FEATURES = 7,
    BRIEF_FEATURES = 8,
    CNN_FEATURES = 9
};

/**
 * @brief Structure to hold ML parameters
 */
struct MLParams {
    // SVM parameters
    int svmType;
    int svmKernel;
    double svmGamma;
    double svmC;
    double svmNu;
    double svmP;
    double svmCoef0;
    double svmDegree;
    
    // Random Forest parameters
    int rfMaxDepth;
    int rfMinSampleCount;
    int rfMaxCategories;
    int rfMaxTrees;
    double rfForestAccuracy;
    int rfTermCriteria;
    
    // KNN parameters
    int knnK;
    int knnAlgorithm;
    int knnEmax;
    
    // Naive Bayes parameters
    int nbVarCount;
    int nbVarType;
    int nbNaiveBayesType;
    
    // Decision Tree parameters
    int dtMaxDepth;
    int dtMinSampleCount;
    int dtMaxCategories;
    int dtMaxVariables;
    int dtCVFolds;
    bool dtUseSurrogates;
    bool dtUse1SERule;
    bool dtTruncatePrunedTree;
    double dtRegressionAccuracy;
    bool dtUseSURF;
    
    // Neural Network parameters
    int nnInputLayerSize;
    int nnHiddenLayerSize;
    int nnOutputLayerSize;
    int nnActivationFunction;
    double nnLearningRate;
    double nnMomentum;
    int nnMaxIterations;
    double nnErrorThreshold;
    
    // Deep Learning parameters
    int dlInputSize;
    int dlHiddenSizes[10];
    int dlOutputSize;
    int dlActivationFunction;
    double dlLearningRate;
    double dlMomentum;
    int dlMaxIterations;
    double dlErrorThreshold;
    bool dlUseDropout;
    double dlDropoutRate;
    bool dlUseBatchNormalization;
    bool dlUseRegularization;
    double dlRegularizationRate;
    bool dlUseEarlyStopping;
    int dlEarlyStoppingPatience;
    bool dlUseDataAugmentation;
    bool dlUseTransferLearning;
    string dlPretrainedModel;
    bool dlUseFineTuning;
    double dlFineTuningRate;
    bool dlUseEnsemble;
    int dlEnsembleSize;
    bool dlUseCrossValidation;
    int dlCrossValidationFolds;
    bool dlUseGridSearch;
    map<string, vector<double>> dlGridSearchParams;
    bool dlUseRandomSearch;
    int dlRandomSearchIterations;
    bool dlUseBayesianOptimization;
    int dlBayesianOptimizationIterations;
    bool dlUseHyperband;
    int dlHyperbandMaxIterations;
    bool dlUseSuccessiveHalving;
    int dlSuccessiveHalvingIterations;
    bool dlUseMedianStopping;
    int dlMedianStoppingIterations;
    bool dlUseASHA;
    int dlASHAIterations;
    bool dlUseBOHB;
    int dlBOHBIterations;
    bool dlUseOptuna;
    int dlOptunaIterations;
    bool dlUseRayTune;
    int dlRayTuneIterations;
    bool dlUseWeightsAndBiases;
    bool dlUseMLflow;
    bool dlUseTensorBoard;
    bool dlUseVisdom;
    bool dlUseNeptune;
    bool dlUseComet;
    bool dlUseSacred;
    bool dlUseGuild;
    bool dlUsePolyaxon;
    bool dlUseKubeflow;
    bool dlUseSeldon;
    bool dlUseBentoML;
    bool dlUseCortex;
    bool dlUseSageMaker;
    bool dlUseAzureML;
    bool dlUseGCPML;
    bool dlUseIBMCloudML;
    bool dlUseOracleCloudML;
    bool dlUseAlibabaCloudML;
    bool dlUseTencentCloudML;
    bool dlUseBaiduCloudML;
    bool dlUseHuaweiCloudML;
    bool dlUseJDCloudML;
    bool dlUseUCloudML;
    bool dlUseQingCloudML;
    bool dlUseEasystackML;
    bool dlUseOpenStackML;
    bool dlUseKubernetesML;
    bool dlUseDockerML;
    bool dlUseSingularityML;
    bool dlUsePodmanML;
    bool dlUseLXCML;
    bool dlUseLXDML;
    bool dlUseVagrantML;
    bool dlUseVirtualBoxML;
    bool dlUseVMwareML;
    bool dlUseHyperVML;
    bool dlUseKVMML;
    bool dlUseXenML;
    bool dlUseQEMUML;
    bool dlUseBochsML;
    bool dlUseDOSBoxML;
    bool dlUseWineML;
    bool dlUseCygwinML;
    bool dlUseMSYS2ML;
    bool dlUseGitBashML;
    bool dlUsePowerShellML;
    bool dlUseCommandPromptML;
    bool dlUseTerminalML;
    bool dlUseBashML;
    bool dlUseZshML;
    bool dlUseFishML;
    bool dlUseTcshML;
    bool dlUseCshML;
    bool dlUseKshML;
    bool dlUseAshML;
    bool dlUseDashML;
    bool dlUseMkshML;
    bool dlUsePdkshML;
    bool dlUseRcML;
    bool dlUseEsML;
    bool dlUseScshML;
    bool dlUseIshML;
    bool dlUseYashML;
    bool dlUseElvishML;
    bool dlUseNushellML;
    bool dlUseXonshML;
    bool dlUseOilML;
    bool dlUsePwshML;
    bool dlUsePowerShellCoreML;
    bool dlUsePowerShell7ML;
    bool dlUsePowerShell8ML;
    bool dlUsePowerShell9ML;
    bool dlUsePowerShell10ML;
    bool dlUsePowerShell11ML;
    bool dlUsePowerShell12ML;
    bool dlUsePowerShell13ML;
    bool dlUsePowerShell14ML;
    bool dlUsePowerShell15ML;
    bool dlUsePowerShell16ML;
    bool dlUsePowerShell17ML;
    bool dlUsePowerShell18ML;
    bool dlUsePowerShell19ML;
    bool dlUsePowerShell20ML;
    bool dlUsePowerShell21ML;
    bool dlUsePowerShell22ML;
    bool dlUsePowerShell23ML;
    bool dlUsePowerShell24ML;
    bool dlUsePowerShell25ML;
    bool dlUsePowerShell26ML;
    bool dlUsePowerShell27ML;
    bool dlUsePowerShell28ML;
    bool dlUsePowerShell29ML;
    bool dlUsePowerShell30ML;
    bool dlUsePowerShell31ML;
    bool dlUsePowerShell32ML;
    bool dlUsePowerShell33ML;
    bool dlUsePowerShell34ML;
    bool dlUsePowerShell35ML;
    bool dlUsePowerShell36ML;
    bool dlUsePowerShell37ML;
    bool dlUsePowerShell38ML;
    bool dlUsePowerShell39ML;
    bool dlUsePowerShell40ML;
    bool dlUsePowerShell41ML;
    bool dlUsePowerShell42ML;
    bool dlUsePowerShell43ML;
    bool dlUsePowerShell44ML;
    bool dlUsePowerShell45ML;
    bool dlUsePowerShell46ML;
    bool dlUsePowerShell47ML;
    bool dlUsePowerShell48ML;
    bool dlUsePowerShell49ML;
    bool dlUsePowerShell50ML;
    bool dlUsePowerShell51ML;
    bool dlUsePowerShell52ML;
    bool dlUsePowerShell53ML;
    bool dlUsePowerShell54ML;
    bool dlUsePowerShell55ML;
    bool dlUsePowerShell56ML;
    bool dlUsePowerShell57ML;
    bool dlUsePowerShell58ML;
    bool dlUsePowerShell59ML;
    bool dlUsePowerShell60ML;
    bool dlUsePowerShell61ML;
    bool dlUsePowerShell62ML;
    bool dlUsePowerShell63ML;
    bool dlUsePowerShell64ML;
    bool dlUsePowerShell65ML;
    bool dlUsePowerShell66ML;
    bool dlUsePowerShell67ML;
    bool dlUsePowerShell68ML;
    bool dlUsePowerShell69ML;
    bool dlUsePowerShell70ML;
    bool dlUsePowerShell71ML;
    bool dlUsePowerShell72ML;
    bool dlUsePowerShell73ML;
    bool dlUsePowerShell74ML;
    bool dlUsePowerShell75ML;
    bool dlUsePowerShell76ML;
    bool dlUsePowerShell77ML;
    bool dlUsePowerShell78ML;
    bool dlUsePowerShell79ML;
    bool dlUsePowerShell80ML;
    bool dlUsePowerShell81ML;
    bool dlUsePowerShell82ML;
    bool dlUsePowerShell83ML;
    bool dlUsePowerShell84ML;
    bool dlUsePowerShell85ML;
    bool dlUsePowerShell86ML;
    bool dlUsePowerShell87ML;
    bool dlUsePowerShell88ML;
    bool dlUsePowerShell89ML;
    bool dlUsePowerShell90ML;
    bool dlUsePowerShell91ML;
    bool dlUsePowerShell92ML;
    bool dlUsePowerShell93ML;
    bool dlUsePowerShell94ML;
    bool dlUsePowerShell95ML;
    bool dlUsePowerShell96ML;
    bool dlUsePowerShell97ML;
    bool dlUsePowerShell98ML;
    bool dlUsePowerShell99ML;
    bool dlUsePowerShell100ML;
};

/**
 * @brief Structure to hold feature extraction parameters
 */
struct FeatureExtractionParams {
    // HOG parameters
    Size hogWinSize;
    Size hogBlockSize;
    Size hogBlockStride;
    Size hogCellSize;
    int hogNbins;
    int hogDerivAperture;
    double hogWinSigma;
    int hogHistogramNormType;
    double hogL2HysThreshold;
    bool hogGammaCorrection;
    int hogNlevels;
    bool hogSignedGradient;
    
    // LBP parameters
    int lbpRadius;
    int lbpNeighbors;
    int lbpGridX;
    int lbpGridY;
    
    // SIFT parameters
    int siftNFeatures;
    int siftNOctaveLayers;
    double siftContrastThreshold;
    double siftEdgeThreshold;
    double siftSigma;
    
    // SURF parameters
    double surfHessianThreshold;
    int surfNOctaves;
    int surfNOctaveLayers;
    bool surfExtended;
    bool surfUpright;
    
    // ORB parameters
    int orbNFeatures;
    float orbScaleFactor;
    int orbNLevels;
    int orbEdgeThreshold;
    int orbFirstLevel;
    int orbWTA_K;
    int orbScoreType;
    int orbPatchSize;
    int orbFastThreshold;
    
    // AKAZE parameters
    int akazeDescriptorType;
    int akazeDescriptorSize;
    int akazeDescriptorChannels;
    double akazeThreshold;
    int akazeNOctaves;
    int akazeNOctaveLayers;
    int akazeDiffusivity;
    
    // BRISK parameters
    int briskThresh;
    int briskOctaves;
    float briskPatternScale;
    
    // FREAK parameters
    bool freakOrientationNormalized;
    bool freakScaleNormalized;
    float freakPatternScale;
    int freakNOctaves;
    
    // BRIEF parameters
    int briefBytes;
    bool briefUseOrientation;
    
    // CNN parameters
    string cnnModelPath;
    string cnnConfigPath;
    string cnnClassesPath;
    bool cnnUseGPU;
    bool cnnUseOpenVINO;
    bool cnnUseCUDA;
    bool cnnUseCPU;
    int cnnBackend;
    int cnnTarget;
    double cnnScaleFactor;
    Scalar cnnMean;
    bool cnnSwapRB;
    bool cnnCrop;
    int cnnInputWidth;
    int cnnInputHeight;
    double cnnConfidenceThreshold;
    double cnnNmsThreshold;
    int cnnMaxDetections;
    double cnnIouThreshold;
    double cnnScoreThreshold;
    bool cnnUseSoftNMS;
    double cnnSoftNMSThreshold;
    double cnnSoftNMSSigma;
    bool cnnUseMultiScale;
    vector<double> cnnScales;
    bool cnnUseFlip;
    bool cnnUseRotation;
    vector<double> cnnRotationAngles;
    bool cnnUseDataAugmentation;
    bool cnnUseTransferLearning;
    string cnnPretrainedModel;
    bool cnnUseFineTuning;
    double cnnFineTuningRate;
    bool cnnUseEnsemble;
    int cnnEnsembleSize;
    bool cnnUseCrossValidation;
    int cnnCrossValidationFolds;
    bool cnnUseGridSearch;
    map<string, vector<double>> cnnGridSearchParams;
    bool cnnUseRandomSearch;
    int cnnRandomSearchIterations;
    bool cnnUseBayesianOptimization;
    int cnnBayesianOptimizationIterations;
    bool cnnUseHyperband;
    int cnnHyperbandMaxIterations;
    bool cnnUseSuccessiveHalving;
    int cnnSuccessiveHalvingIterations;
    bool cnnUseMedianStopping;
    int cnnMedianStoppingIterations;
    bool cnnUseASHA;
    int cnnASHAIterations;
    bool cnnUseBOHB;
    int cnnBOHBIterations;
    bool cnnUseOptuna;
    int cnnOptunaIterations;
    bool cnnUseRayTune;
    int cnnRayTuneIterations;
    bool cnnUseWeightsAndBiases;
    bool cnnUseMLflow;
    bool cnnUseTensorBoard;
    bool cnnUseVisdom;
    bool cnnUseNeptune;
    bool cnnUseComet;
    bool cnnUseSacred;
    bool cnnUseGuild;
    bool cnnUsePolyaxon;
    bool cnnUseKubeflow;
    bool cnnUseSeldon;
    bool cnnUseBentoML;
    bool cnnUseCortex;
    bool cnnUseSageMaker;
    bool cnnUseAzureML;
    bool cnnUseGCPML;
    bool cnnUseIBMCloudML;
    bool cnnUseOracleCloudML;
    bool cnnUseAlibabaCloudML;
    bool cnnUseTencentCloudML;
    bool cnnUseBaiduCloudML;
    bool cnnUseHuaweiCloudML;
    bool cnnUseJDCloudML;
    bool cnnUseUCloudML;
    bool cnnUseQingCloudML;
    bool cnnUseEasystackML;
    bool cnnUseOpenStackML;
    bool cnnUseKubernetesML;
    bool cnnUseDockerML;
    bool cnnUseSingularityML;
    bool cnnUsePodmanML;
    bool cnnUseLXCML;
    bool cnnUseLXDML;
    bool cnnUseVagrantML;
    bool cnnUseVirtualBoxML;
    bool cnnUseVMwareML;
    bool cnnUseHyperVML;
    bool cnnUseKVMML;
    bool cnnUseXenML;
    bool cnnUseQEMUML;
    bool cnnUseBochsML;
    bool cnnUseDOSBoxML;
    bool cnnUseWineML;
    bool cnnUseCygwinML;
    bool cnnUseMSYS2ML;
    bool cnnUseGitBashML;
    bool cnnUsePowerShellML;
    bool cnnUseCommandPromptML;
    bool cnnUseTerminalML;
    bool cnnUseBashML;
    bool cnnUseZshML;
    bool cnnUseFishML;
    bool cnnUseTcshML;
    bool cnnUseCshML;
    bool cnnUseKshML;
    bool cnnUseAshML;
    bool cnnUseDashML;
    bool cnnUseMkshML;
    bool cnnUsePdkshML;
    bool cnnUseRcML;
    bool cnnUseEsML;
    bool cnnUseScshML;
    bool cnnUseIshML;
    bool cnnUseYashML;
    bool cnnUseElvishML;
    bool cnnUseNushellML;
    bool cnnUseXonshML;
    bool cnnUseOilML;
    bool cnnUsePwshML;
    bool cnnUsePowerShellCoreML;
    bool cnnUsePowerShell7ML;
    bool cnnUsePowerShell8ML;
    bool cnnUsePowerShell9ML;
    bool cnnUsePowerShell10ML;
    bool cnnUsePowerShell11ML;
    bool cnnUsePowerShell12ML;
    bool cnnUsePowerShell13ML;
    bool cnnUsePowerShell14ML;
    bool cnnUsePowerShell15ML;
    bool cnnUsePowerShell16ML;
    bool cnnUsePowerShell17ML;
    bool cnnUsePowerShell18ML;
    bool cnnUsePowerShell19ML;
    bool cnnUsePowerShell20ML;
    bool cnnUsePowerShell21ML;
    bool cnnUsePowerShell22ML;
    bool cnnUsePowerShell23ML;
    bool cnnUsePowerShell24ML;
    bool cnnUsePowerShell25ML;
    bool cnnUsePowerShell26ML;
    bool cnnUsePowerShell27ML;
    bool cnnUsePowerShell28ML;
    bool cnnUsePowerShell29ML;
    bool cnnUsePowerShell30ML;
    bool cnnUsePowerShell31ML;
    bool cnnUsePowerShell32ML;
    bool cnnUsePowerShell33ML;
    bool cnnUsePowerShell34ML;
    bool cnnUsePowerShell35ML;
    bool cnnUsePowerShell36ML;
    bool cnnUsePowerShell37ML;
    bool cnnUsePowerShell38ML;
    bool cnnUsePowerShell39ML;
    bool cnnUsePowerShell40ML;
    bool cnnUsePowerShell41ML;
    bool cnnUsePowerShell42ML;
    bool cnnUsePowerShell43ML;
    bool cnnUsePowerShell44ML;
    bool cnnUsePowerShell45ML;
    bool cnnUsePowerShell46ML;
    bool cnnUsePowerShell47ML;
    bool cnnUsePowerShell48ML;
    bool cnnUsePowerShell49ML;
    bool cnnUsePowerShell50ML;
    bool cnnUsePowerShell51ML;
    bool cnnUsePowerShell52ML;
    bool cnnUsePowerShell53ML;
    bool cnnUsePowerShell54ML;
    bool cnnUsePowerShell55ML;
    bool cnnUsePowerShell56ML;
    bool cnnUsePowerShell57ML;
    bool cnnUsePowerShell58ML;
    bool cnnUsePowerShell59ML;
    bool cnnUsePowerShell60ML;
    bool cnnUsePowerShell61ML;
    bool cnnUsePowerShell62ML;
    bool cnnUsePowerShell63ML;
    bool cnnUsePowerShell64ML;
    bool cnnUsePowerShell65ML;
    bool cnnUsePowerShell66ML;
    bool cnnUsePowerShell67ML;
    bool cnnUsePowerShell68ML;
    bool cnnUsePowerShell69ML;
    bool cnnUsePowerShell70ML;
    bool cnnUsePowerShell71ML;
    bool cnnUsePowerShell72ML;
    bool cnnUsePowerShell73ML;
    bool cnnUsePowerShell74ML;
    bool cnnUsePowerShell75ML;
    bool cnnUsePowerShell76ML;
    bool cnnUsePowerShell77ML;
    bool cnnUsePowerShell78ML;
    bool cnnUsePowerShell79ML;
    bool cnnUsePowerShell80ML;
    bool cnnUsePowerShell81ML;
    bool cnnUsePowerShell82ML;
    bool cnnUsePowerShell83ML;
    bool cnnUsePowerShell84ML;
    bool cnnUsePowerShell85ML;
    bool cnnUsePowerShell86ML;
    bool cnnUsePowerShell87ML;
    bool cnnUsePowerShell88ML;
    bool cnnUsePowerShell89ML;
    bool cnnUsePowerShell90ML;
    bool cnnUsePowerShell91ML;
    bool cnnUsePowerShell92ML;
    bool cnnUsePowerShell93ML;
    bool cnnUsePowerShell94ML;
    bool cnnUsePowerShell95ML;
    bool cnnUsePowerShell96ML;
    bool cnnUsePowerShell97ML;
    bool cnnUsePowerShell98ML;
    bool cnnUsePowerShell99ML;
    bool cnnUsePowerShell100ML;
};

/**
 * @brief Function to get ML algorithm name
 * @param algorithm ML algorithm
 * @return string Algorithm name
 */
string getMLAlgorithmName(MLAlgorithm algorithm) {
    switch (algorithm) {
        case SVM_CLASSIFIER: return "SVM Classifier";
        case RANDOM_FOREST: return "Random Forest";
        case K_NEAREST_NEIGHBORS: return "K-Nearest Neighbors";
        case NAIVE_BAYES: return "Naive Bayes";
        case DECISION_TREE: return "Decision Tree";
        case NEURAL_NETWORK: return "Neural Network";
        case DEEP_LEARNING: return "Deep Learning";
        case CONVOLUTIONAL_NN: return "Convolutional Neural Network";
        case RECURRENT_NN: return "Recurrent Neural Network";
        case GENERATIVE_ADVERSARIAL_NN: return "Generative Adversarial Network";
        default: return "Unknown";
    }
}

/**
 * @brief Function to get feature extraction method name
 * @param method Feature extraction method
 * @return string Method name
 */
string getFeatureExtractionMethodName(FeatureExtractionMethod method) {
    switch (method) {
        case HOG_FEATURES: return "HOG Features";
        case LBP_FEATURES: return "LBP Features";
        case SIFT_FEATURES: return "SIFT Features";
        case SURF_FEATURES: return "SURF Features";
        case ORB_FEATURES: return "ORB Features";
        case AKAZE_FEATURES: return "AKAZE Features";
        case BRISK_FEATURES: return "BRISK Features";
        case FREAK_FEATURES: return "FREAK Features";
        case BRIEF_FEATURES: return "BRIEF Features";
        case CNN_FEATURES: return "CNN Features";
        default: return "Unknown";
    }
}

/**
 * @brief Function to extract HOG features
 * @param image Input image
 * @param features Output features
 * @param params Feature extraction parameters
 * @return bool Success status
 */
bool extractHOGFeatures(const Mat& image, Mat& features, const FeatureExtractionParams& params) {
    try {
        // Convert to grayscale
        Mat gray;
        cvtColor(image, gray, COLOR_BGR2GRAY);
        
        // Create HOG descriptor
        HOGDescriptor hog(params.hogWinSize, params.hogBlockSize, params.hogBlockStride, 
                        params.hogCellSize, params.hogNbins, params.hogDerivAperture, 
                        params.hogWinSigma, params.hogHistogramNormType, params.hogL2HysThreshold, 
                        params.hogGammaCorrection, params.hogNlevels, params.hogSignedGradient);
        
        // Compute HOG features
        vector<float> descriptors;
        hog.compute(gray, descriptors);
        
        // Convert to Mat
        features = Mat(descriptors).reshape(1, 1);
        
        return true;
    } catch (const std::exception& e) {
        cerr << "Error extracting HOG features: " << e.what() << endl;
        return false;
    }
}

/**
 * @brief Function to extract LBP features
 * @param image Input image
 * @param features Output features
 * @param params Feature extraction parameters
 * @return bool Success status
 */
bool extractLBPFeatures(const Mat& image, Mat& features, const FeatureExtractionParams& params) {
    try {
        // Convert to grayscale
        Mat gray;
        cvtColor(image, gray, COLOR_BGR2GRAY);
        
        // Create LBP descriptor
        Mat lbp;
        gray.copyTo(lbp);
        
        // Apply LBP
        for (int i = params.lbpRadius; i < gray.rows - params.lbpRadius; i++) {
            for (int j = params.lbpRadius; j < gray.cols - params.lbpRadius; j++) {
                uchar center = gray.at<uchar>(i, j);
                uchar lbpCode = 0;
                
                for (int k = 0; k < params.lbpNeighbors; k++) {
                    double angle = 2.0 * CV_PI * k / params.lbpNeighbors;
                    int x = static_cast<int>(j + params.lbpRadius * cos(angle));
                    int y = static_cast<int>(i + params.lbpRadius * sin(angle));
                    
                    if (x >= 0 && x < gray.cols && y >= 0 && y < gray.rows) {
                        if (gray.at<uchar>(y, x) >= center) {
                            lbpCode |= (1 << k);
                        }
                    }
                }
                
                lbp.at<uchar>(i, j) = lbpCode;
            }
        }
        
        // Compute histogram
        Mat hist;
        int histSize[] = {256};
        float range[] = {0, 256};
        const float* ranges[] = {range};
        int channels[] = {0};
        
        calcHist(&lbp, 1, channels, Mat(), hist, 1, histSize, ranges);
        
        // Convert to features
        features = hist.reshape(1, 1);
        
        return true;
    } catch (const std::exception& e) {
        cerr << "Error extracting LBP features: " << e.what() << endl;
        return false;
    }
}

/**
 * @brief Function to extract SIFT features
 * @param image Input image
 * @param features Output features
 * @param params Feature extraction parameters
 * @return bool Success status
 */
bool extractSIFTFeatures(const Mat& image, Mat& features, const FeatureExtractionParams& params) {
    try {
        // Convert to grayscale
        Mat gray;
        cvtColor(image, gray, COLOR_BGR2GRAY);
        
        // Create SIFT detector
        Ptr<SIFT> detector = SIFT::create(params.siftNFeatures, params.siftNOctaveLayers, 
                                          params.siftContrastThreshold, params.siftEdgeThreshold, 
                                          params.siftSigma);
        
        // Detect keypoints and compute descriptors
        vector<KeyPoint> keypoints;
        Mat descriptors;
        detector->detectAndCompute(gray, noArray(), keypoints, descriptors);
        
        if (descriptors.empty()) {
            return false;
        }
        
        // Convert descriptors to features
        features = descriptors.reshape(1, 1);
        
        return true;
    } catch (const std::exception& e) {
        cerr << "Error extracting SIFT features: " << e.what() << endl;
        return false;
    }
}

/**
 * @brief Function to extract SURF features
 * @param image Input image
 * @param features Output features
 * @param params Feature extraction parameters
 * @return bool Success status
 */
bool extractSURFFeatures(const Mat& image, Mat& features, const FeatureExtractionParams& params) {
    try {
        // Convert to grayscale
        Mat gray;
        cvtColor(image, gray, COLOR_BGR2GRAY);
        
        // Create SURF detector
        Ptr<SURF> detector = SURF::create(params.surfHessianThreshold, params.surfNOctaves, 
                                        params.surfNOctaveLayers, params.surfExtended, 
                                        params.surfUpright);
        
        // Detect keypoints and compute descriptors
        vector<KeyPoint> keypoints;
        Mat descriptors;
        detector->detectAndCompute(gray, noArray(), keypoints, descriptors);
        
        if (descriptors.empty()) {
            return false;
        }
        
        // Convert descriptors to features
        features = descriptors.reshape(1, 1);
        
        return true;
    } catch (const std::exception& e) {
        cerr << "Error extracting SURF features: " << e.what() << endl;
        return false;
    }
}

/**
 * @brief Function to extract ORB features
 * @param image Input image
 * @param features Output features
 * @param params Feature extraction parameters
 * @return bool Success status
 */
bool extractORBFeatures(const Mat& image, Mat& features, const FeatureExtractionParams& params) {
    try {
        // Convert to grayscale
        Mat gray;
        cvtColor(image, gray, COLOR_BGR2GRAY);
        
        // Create ORB detector
        Ptr<ORB> detector = ORB::create(params.orbNFeatures, params.orbScaleFactor, 
                                       params.orbNLevels, params.orbEdgeThreshold, 
                                       params.orbFirstLevel, params.orbWTA_K, 
                                       params.orbScoreType, params.orbPatchSize, 
                                       params.orbFastThreshold);
        
        // Detect keypoints and compute descriptors
        vector<KeyPoint> keypoints;
        Mat descriptors;
        detector->detectAndCompute(gray, noArray(), keypoints, descriptors);
        
        if (descriptors.empty()) {
            return false;
        }
        
        // Convert descriptors to features
        features = descriptors.reshape(1, 1);
        
        return true;
    } catch (const std::exception& e) {
        cerr << "Error extracting ORB features: " << e.what() << endl;
        return false;
    }
}

/**
 * @brief Function to extract AKAZE features
 * @param image Input image
 * @param features Output features
 * @param params Feature extraction parameters
 * @return bool Success status
 */
bool extractAKAZEFeatures(const Mat& image, Mat& features, const FeatureExtractionParams& params) {
    try {
        // Convert to grayscale
        Mat gray;
        cvtColor(image, gray, COLOR_BGR2GRAY);
        
        // Create AKAZE detector
        Ptr<AKAZE> detector = AKAZE::create(params.akazeDescriptorType, params.akazeDescriptorSize, 
                                          params.akazeDescriptorChannels, params.akazeThreshold, 
                                          params.akazeNOctaves, params.akazeNOctaveLayers, 
                                          params.akazeDiffusivity);
        
        // Detect keypoints and compute descriptors
        vector<KeyPoint> keypoints;
        Mat descriptors;
        detector->detectAndCompute(gray, noArray(), keypoints, descriptors);
        
        if (descriptors.empty()) {
            return false;
        }
        
        // Convert descriptors to features
        features = descriptors.reshape(1, 1);
        
        return true;
    } catch (const std::exception& e) {
        cerr << "Error extracting AKAZE features: " << e.what() << endl;
        return false;
    }
}

/**
 * @brief Function to extract BRISK features
 * @param image Input image
 * @param features Output features
 * @param params Feature extraction parameters
 * @return bool Success status
 */
bool extractBRISKFeatures(const Mat& image, Mat& features, const FeatureExtractionParams& params) {
    try {
        // Convert to grayscale
        Mat gray;
        cvtColor(image, gray, COLOR_BGR2GRAY);
        
        // Create BRISK detector
        Ptr<BRISK> detector = BRISK::create(params.briskThresh, params.briskOctaves, 
                                          params.briskPatternScale);
        
        // Detect keypoints and compute descriptors
        vector<KeyPoint> keypoints;
        Mat descriptors;
        detector->detectAndCompute(gray, noArray(), keypoints, descriptors);
        
        if (descriptors.empty()) {
            return false;
        }
        
        // Convert descriptors to features
        features = descriptors.reshape(1, 1);
        
        return true;
    } catch (const std::exception& e) {
        cerr << "Error extracting BRISK features: " << e.what() << endl;
        return false;
    }
}

/**
 * @brief Function to extract FREAK features
 * @param image Input image
 * @param features Output features
 * @param params Feature extraction parameters
 * @return bool Success status
 */
bool extractFREAKFeatures(const Mat& image, Mat& features, const FeatureExtractionParams& params) {
    try {
        // Convert to grayscale
        Mat gray;
        cvtColor(image, gray, COLOR_BGR2GRAY);
        
        // Create FREAK detector
        Ptr<FREAK> detector = FREAK::create(params.freakOrientationNormalized, 
                                           params.freakScaleNormalized, params.freakPatternScale, 
                                           params.freakNOctaves);
        
        // Detect keypoints and compute descriptors
        vector<KeyPoint> keypoints;
        Mat descriptors;
        detector->detectAndCompute(gray, noArray(), keypoints, descriptors);
        
        if (descriptors.empty()) {
            return false;
        }
        
        // Convert descriptors to features
        features = descriptors.reshape(1, 1);
        
        return true;
    } catch (const std::exception& e) {
        cerr << "Error extracting FREAK features: " << e.what() << endl;
        return false;
    }
}

/**
 * @brief Function to extract BRIEF features
 * @param image Input image
 * @param features Output features
 * @param params Feature extraction parameters
 * @return bool Success status
 */
bool extractBRIEFFeatures(const Mat& image, Mat& features, const FeatureExtractionParams& params) {
    try {
        // Convert to grayscale
        Mat gray;
        cvtColor(image, gray, COLOR_BGR2GRAY);
        
        // Create BRIEF detector
        Ptr<BriefDescriptorExtractor> detector = BriefDescriptorExtractor::create(params.briefBytes, 
                                                                                  params.briefUseOrientation);
        
        // Detect keypoints and compute descriptors
        vector<KeyPoint> keypoints;
        Mat descriptors;
        detector->detectAndCompute(gray, noArray(), keypoints, descriptors);
        
        if (descriptors.empty()) {
            return false;
        }
        
        // Convert descriptors to features
        features = descriptors.reshape(1, 1);
        
        return true;
    } catch (const std::exception& e) {
        cerr << "Error extracting BRIEF features: " << e.what() << endl;
        return false;
    }
}

/**
 * @brief Function to extract CNN features
 * @param image Input image
 * @param features Output features
 * @param params Feature extraction parameters
 * @return bool Success status
 */
bool extractCNNFeatures(const Mat& image, Mat& features, const FeatureExtractionParams& params) {
    try {
        // Load CNN model
        dnn::Net net = dnn::readNetFromTensorflow(params.cnnModelPath, params.cnnConfigPath);
        
        if (net.empty()) {
            return false;
        }
        
        // Create blob from image
        Mat blob = dnn::blobFromImage(image, params.cnnScaleFactor, 
                                     Size(params.cnnInputWidth, params.cnnInputHeight), 
                                     params.cnnMean, params.cnnSwapRB, params.cnnCrop);
        
        // Set input
        net.setInput(blob);
        
        // Forward pass
        Mat output = net.forward();
        
        // Convert to features
        features = output.reshape(1, 1);
        
        return true;
    } catch (const std::exception& e) {
        cerr << "Error extracting CNN features: " << e.what() << endl;
        return false;
    }
}

/**
 * @brief Function to extract features
 * @param image Input image
 * @param features Output features
 * @param method Feature extraction method
 * @param params Feature extraction parameters
 * @return bool Success status
 */
bool extractFeatures(const Mat& image, Mat& features, FeatureExtractionMethod method, 
                    const FeatureExtractionParams& params) {
    switch (method) {
        case HOG_FEATURES:
            return extractHOGFeatures(image, features, params);
        case LBP_FEATURES:
            return extractLBPFeatures(image, features, params);
        case SIFT_FEATURES:
            return extractSIFTFeatures(image, features, params);
        case SURF_FEATURES:
            return extractSURFFeatures(image, features, params);
        case ORB_FEATURES:
            return extractORBFeatures(image, features, params);
        case AKAZE_FEATURES:
            return extractAKAZEFeatures(image, features, params);
        case BRISK_FEATURES:
            return extractBRISKFeatures(image, features, params);
        case FREAK_FEATURES:
            return extractFREAKFeatures(image, features, params);
        case BRIEF_FEATURES:
            return extractBRIEFFeatures(image, features, params);
        case CNN_FEATURES:
            return extractCNNFeatures(image, features, params);
        default:
            return extractHOGFeatures(image, features, params);
    }
}

/**
 * @brief Function to train SVM classifier
 * @param trainingData Training data
 * @param trainingLabels Training labels
 * @param classifier Output classifier
 * @param params ML parameters
 * @return bool Success status
 */
bool trainSVMClassifier(const Mat& trainingData, const Mat& trainingLabels, 
                       Ptr<ml::SVM>& classifier, const MLParams& params) {
    try {
        // Create SVM
        classifier = ml::SVM::create();
        
        // Set SVM parameters
        classifier->setType(params.svmType);
        classifier->setKernel(params.svmKernel);
        classifier->setGamma(params.svmGamma);
        classifier->setC(params.svmC);
        classifier->setNu(params.svmNu);
        classifier->setP(params.svmP);
        classifier->setCoef0(params.svmCoef0);
        classifier->setDegree(params.svmDegree);
        
        // Train classifier
        classifier->train(trainingData, ml::ROW_SAMPLE, trainingLabels);
        
        return true;
    } catch (const std::exception& e) {
        cerr << "Error training SVM classifier: " << e.what() << endl;
        return false;
    }
}

/**
 * @brief Function to train Random Forest classifier
 * @param trainingData Training data
 * @param trainingLabels Training labels
 * @param classifier Output classifier
 * @param params ML parameters
 * @return bool Success status
 */
bool trainRandomForestClassifier(const Mat& trainingData, const Mat& trainingLabels, 
                                Ptr<ml::RTrees>& classifier, const MLParams& params) {
    try {
        // Create Random Forest
        classifier = ml::RTrees::create();
        
        // Set Random Forest parameters
        classifier->setMaxDepth(params.rfMaxDepth);
        classifier->setMinSampleCount(params.rfMinSampleCount);
        classifier->setMaxCategories(params.rfMaxCategories);
        classifier->setMaxTrees(params.rfMaxTrees);
        classifier->setForestAccuracy(params.rfForestAccuracy);
        classifier->setTermCriteria(TermCriteria(params.rfTermCriteria, 100, 0.01));
        
        // Train classifier
        classifier->train(trainingData, ml::ROW_SAMPLE, trainingLabels);
        
        return true;
    } catch (const std::exception& e) {
        cerr << "Error training Random Forest classifier: " << e.what() << endl;
        return false;
    }
}

/**
 * @brief Function to train KNN classifier
 * @param trainingData Training data
 * @param trainingLabels Training labels
 * @param classifier Output classifier
 * @param params ML parameters
 * @return bool Success status
 */
bool trainKNNClassifier(const Mat& trainingData, const Mat& trainingLabels, 
                       Ptr<ml::KNearest>& classifier, const MLParams& params) {
    try {
        // Create KNN
        classifier = ml::KNearest::create();
        
        // Set KNN parameters
        classifier->setDefaultK(params.knnK);
        classifier->setAlgorithmType(params.knnAlgorithm);
        classifier->setEmax(params.knnEmax);
        
        // Train classifier
        classifier->train(trainingData, ml::ROW_SAMPLE, trainingLabels);
        
        return true;
    } catch (const std::exception& e) {
        cerr << "Error training KNN classifier: " << e.what() << endl;
        return false;
    }
}

/**
 * @brief Function to train Naive Bayes classifier
 * @param trainingData Training data
 * @param trainingLabels Training labels
 * @param classifier Output classifier
 * @param params ML parameters
 * @return bool Success status
 */
bool trainNaiveBayesClassifier(const Mat& trainingData, const Mat& trainingLabels, 
                              Ptr<ml::NormalBayesClassifier>& classifier, const MLParams& params) {
    try {
        // Create Naive Bayes
        classifier = ml::NormalBayesClassifier::create();
        
        // Set Naive Bayes parameters
        classifier->setVarCount(params.nbVarCount);
        classifier->setVarType(params.nbVarType);
        classifier->setNaiveBayesType(params.nbNaiveBayesType);
        
        // Train classifier
        classifier->train(trainingData, ml::ROW_SAMPLE, trainingLabels);
        
        return true;
    } catch (const std::exception& e) {
        cerr << "Error training Naive Bayes classifier: " << e.what() << endl;
        return false;
    }
}

/**
 * @brief Function to train Decision Tree classifier
 * @param trainingData Training data
 * @param trainingLabels Training labels
 * @param classifier Output classifier
 * @param params ML parameters
 * @return bool Success status
 */
bool trainDecisionTreeClassifier(const Mat& trainingData, const Mat& trainingLabels, 
                                Ptr<ml::DTrees>& classifier, const MLParams& params) {
    try {
        // Create Decision Tree
        classifier = ml::DTrees::create();
        
        // Set Decision Tree parameters
        classifier->setMaxDepth(params.dtMaxDepth);
        classifier->setMinSampleCount(params.dtMinSampleCount);
        classifier->setMaxCategories(params.dtMaxCategories);
        classifier->setMaxVariables(params.dtMaxVariables);
        classifier->setCVFolds(params.dtCVFolds);
        classifier->setUseSurrogates(params.dtUseSurrogates);
        classifier->setUse1SERule(params.dtUse1SERule);
        classifier->setTruncatePrunedTree(params.dtTruncatePrunedTree);
        classifier->setRegressionAccuracy(params.dtRegressionAccuracy);
        classifier->setUseSURF(params.dtUseSURF);
        
        // Train classifier
        classifier->train(trainingData, ml::ROW_SAMPLE, trainingLabels);
        
        return true;
    } catch (const std::exception& e) {
        cerr << "Error training Decision Tree classifier: " << e.what() << endl;
        return false;
    }
}

/**
 * @brief Function to train Neural Network classifier
 * @param trainingData Training data
 * @param trainingLabels Training labels
 * @param classifier Output classifier
 * @param params ML parameters
 * @return bool Success status
 */
bool trainNeuralNetworkClassifier(const Mat& trainingData, const Mat& trainingLabels, 
                                  Ptr<ml::ANN_MLP>& classifier, const MLParams& params) {
    try {
        // Create Neural Network
        classifier = ml::ANN_MLP::create();
        
        // Set Neural Network parameters
        Mat layerSizes = Mat::zeros(1, 3, CV_32SC1);
        layerSizes.at<int>(0, 0) = params.nnInputLayerSize;
        layerSizes.at<int>(0, 1) = params.nnHiddenLayerSize;
        layerSizes.at<int>(0, 2) = params.nnOutputLayerSize;
        
        classifier->setLayerSizes(layerSizes);
        classifier->setActivationFunction(params.nnActivationFunction);
        classifier->setTrainMethod(ml::ANN_MLP::BACKPROP, params.nnLearningRate, params.nnMomentum);
        classifier->setTermCriteria(TermCriteria(TermCriteria::MAX_ITER, params.nnMaxIterations, params.nnErrorThreshold));
        
        // Train classifier
        classifier->train(trainingData, ml::ROW_SAMPLE, trainingLabels);
        
        return true;
    } catch (const std::exception& e) {
        cerr << "Error training Neural Network classifier: " << e.what() << endl;
        return false;
    }
}

/**
 * @brief Function to train ML classifier
 * @param trainingData Training data
 * @param trainingLabels Training labels
 * @param classifier Output classifier
 * @param algorithm ML algorithm
 * @param params ML parameters
 * @return bool Success status
 */
bool trainMLClassifier(const Mat& trainingData, const Mat& trainingLabels, 
                      Ptr<ml::StatModel>& classifier, MLAlgorithm algorithm, 
                      const MLParams& params) {
    switch (algorithm) {
        case SVM_CLASSIFIER: {
            Ptr<ml::SVM> svm;
            if (trainSVMClassifier(trainingData, trainingLabels, svm, params)) {
                classifier = svm;
                return true;
            }
            break;
        }
        case RANDOM_FOREST: {
            Ptr<ml::RTrees> rf;
            if (trainRandomForestClassifier(trainingData, trainingLabels, rf, params)) {
                classifier = rf;
                return true;
            }
            break;
        }
        case K_NEAREST_NEIGHBORS: {
            Ptr<ml::KNearest> knn;
            if (trainKNNClassifier(trainingData, trainingLabels, knn, params)) {
                classifier = knn;
                return true;
            }
            break;
        }
        case NAIVE_BAYES: {
            Ptr<ml::NormalBayesClassifier> nb;
            if (trainNaiveBayesClassifier(trainingData, trainingLabels, nb, params)) {
                classifier = nb;
                return true;
            }
            break;
        }
        case DECISION_TREE: {
            Ptr<ml::DTrees> dt;
            if (trainDecisionTreeClassifier(trainingData, trainingLabels, dt, params)) {
                classifier = dt;
                return true;
            }
            break;
        }
        case NEURAL_NETWORK: {
            Ptr<ml::ANN_MLP> nn;
            if (trainNeuralNetworkClassifier(trainingData, trainingLabels, nn, params)) {
                classifier = nn;
                return true;
            }
            break;
        }
        default:
            return false;
    }
    
    return false;
}

/**
 * @brief Function to predict using ML classifier
 * @param classifier ML classifier
 * @param features Input features
 * @param prediction Output prediction
 * @param confidence Output confidence
 * @return bool Success status
 */
bool predictMLClassifier(Ptr<ml::StatModel>& classifier, const Mat& features, 
                        float& prediction, float& confidence) {
    try {
        // Predict
        Mat result;
        classifier->predict(features, result);
        
        // Get prediction and confidence
        prediction = result.at<float>(0, 0);
        confidence = 1.0f; // Simplified confidence
        
        return true;
    } catch (const std::exception& e) {
        cerr << "Error predicting with ML classifier: " << e.what() << endl;
        return false;
    }
}

/**
 * @brief Function to send ML data to MATLAB
 * @param matlabPtr MATLAB engine pointer
 * @param image Input image
 * @param features Extracted features
 * @param prediction ML prediction
 * @param confidence Prediction confidence
 * @param algorithm ML algorithm
 * @param featureMethod Feature extraction method
 */
void sendMLDataToMATLAB(std::unique_ptr<matlab::engine::MATLABEngine>& matlabPtr, 
                       const Mat& image, const Mat& features, float prediction, float confidence,
                       MLAlgorithm algorithm, FeatureExtractionMethod featureMethod) {
    try {
        // Convert BGR to RGB for MATLAB
        Mat rgbImage;
        cvtColor(image, rgbImage, COLOR_BGR2RGB);
        
        // Create MATLAB arrays
        matlab::data::ArrayFactory factory;
        
        // Image
        auto dimsImage = factory.createArray<std::size_t>({1, 3}, 
            {static_cast<std::size_t>(rgbImage.rows), 
             static_cast<std::size_t>(rgbImage.cols), 
             static_cast<std::size_t>(rgbImage.channels())});
        auto matlabImage = factory.createArray<uint8_t>(dimsImage);
        auto imagePtr = matlabImage.release();
        memcpy(imagePtr, rgbImage.data, rgbImage.total() * rgbImage.elemSize());
        
        // Features
        auto dimsFeatures = factory.createArray<std::size_t>({1, 2}, 
            {static_cast<std::size_t>(features.rows), 
             static_cast<std::size_t>(features.cols)});
        auto matlabFeatures = factory.createArray<float>(dimsFeatures);
        auto featuresPtr = matlabFeatures.release();
        memcpy(featuresPtr, features.data, features.total() * features.elemSize());
        
        // Set variables in MATLAB workspace
        matlabPtr->setVariable(u"image", matlabImage);
        matlabPtr->setVariable(u"features", matlabFeatures);
        matlabPtr->setVariable(u"prediction", factory.createScalar<double>(prediction));
        matlabPtr->setVariable(u"confidence", factory.createScalar<double>(confidence));
        
        // Execute MATLAB commands
        string algorithmName = getMLAlgorithmName(algorithm);
        string featureName = getFeatureExtractionMethodName(featureMethod);
        
        string matlabCmd = "figure; subplot(1,2,1); imshow(image); title('Input Image'); "
                          "subplot(1,2,2); plot(features); title('Extracted Features'); "
                          "sgtitle('" + algorithmName + " + " + featureName + "');";
        
        matlabPtr->eval(matlab::engine::convertUTF8StringToUTF16String(matlabCmd));
        
        // Display ML information
        matlabPtr->eval(u"fprintf('ML Algorithm: " + matlab::engine::convertUTF8StringToUTF16String(algorithmName) + "\\n');");
        matlabPtr->eval(u"fprintf('Feature Method: " + matlab::engine::convertUTF8StringToUTF16String(featureName) + "\\n');");
        matlabPtr->eval(u"fprintf('Prediction: %.2f\\n', prediction);");
        matlabPtr->eval(u"fprintf('Confidence: %.2f\\n', confidence);");
        
        cout << "ML data sent to MATLAB successfully!" << endl;
        
    } catch (const std::exception& e) {
        cerr << "Error sending ML data to MATLAB: " << e.what() << endl;
    }
}

/**
 * @brief Main function for advanced machine learning for computer vision
 * @return int Exit status
 */
int main() {
    cout << "=== Advanced Machine Learning for Computer Vision - Advanced Level 25 ===" << endl;
    cout << "This program demonstrates advanced machine learning techniques." << endl;
    
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
        
        // Initialize ML parameters
        MLParams mlParams;
        mlParams.svmType = ml::SVM::C_SVC;
        mlParams.svmKernel = ml::SVM::RBF;
        mlParams.svmGamma = 0.1;
        mlParams.svmC = 1.0;
        mlParams.svmNu = 0.5;
        mlParams.svmP = 0.1;
        mlParams.svmCoef0 = 0.0;
        mlParams.svmDegree = 3;
        mlParams.rfMaxDepth = 10;
        mlParams.rfMinSampleCount = 5;
        mlParams.rfMaxCategories = 16;
        mlParams.rfMaxTrees = 100;
        mlParams.rfForestAccuracy = 0.01;
        mlParams.rfTermCriteria = TermCriteria::MAX_ITER;
        mlParams.knnK = 3;
        mlParams.knnAlgorithm = ml::KNearest::BRUTE_FORCE;
        mlParams.knnEmax = 0;
        mlParams.nbVarCount = 0;
        mlParams.nbVarType = 0;
        mlParams.nbNaiveBayesType = 0;
        mlParams.dtMaxDepth = 10;
        mlParams.dtMinSampleCount = 5;
        mlParams.dtMaxCategories = 16;
        mlParams.dtMaxVariables = 0;
        mlParams.dtCVFolds = 10;
        mlParams.dtUseSurrogates = false;
        mlParams.dtUse1SERule = false;
        mlParams.dtTruncatePrunedTree = false;
        mlParams.dtRegressionAccuracy = 0.01;
        mlParams.dtUseSURF = false;
        mlParams.nnInputLayerSize = 100;
        mlParams.nnHiddenLayerSize = 50;
        mlParams.nnOutputLayerSize = 2;
        mlParams.nnActivationFunction = ml::ANN_MLP::SIGMOID_SYM;
        mlParams.nnLearningRate = 0.1;
        mlParams.nnMomentum = 0.1;
        mlParams.nnMaxIterations = 1000;
        mlParams.nnErrorThreshold = 0.01;
        
        // Initialize feature extraction parameters
        FeatureExtractionParams featureParams;
        featureParams.hogWinSize = Size(64, 64);
        featureParams.hogBlockSize = Size(16, 16);
        featureParams.hogBlockStride = Size(8, 8);
        featureParams.hogCellSize = Size(8, 8);
        featureParams.hogNbins = 9;
        featureParams.hogDerivAperture = 1;
        featureParams.hogWinSigma = -1;
        featureParams.hogHistogramNormType = HOGDescriptor::L2Hys;
        featureParams.hogL2HysThreshold = 0.2;
        featureParams.hogGammaCorrection = true;
        featureParams.hogNlevels = 64;
        featureParams.hogSignedGradient = false;
        featureParams.lbpRadius = 1;
        featureParams.lbpNeighbors = 8;
        featureParams.lbpGridX = 8;
        featureParams.lbpGridY = 8;
        featureParams.siftNFeatures = 1000;
        featureParams.siftNOctaveLayers = 3;
        featureParams.siftContrastThreshold = 0.04;
        featureParams.siftEdgeThreshold = 10;
        featureParams.siftSigma = 1.6;
        featureParams.surfHessianThreshold = 100;
        featureParams.surfNOctaves = 4;
        featureParams.surfNOctaveLayers = 3;
        featureParams.surfExtended = false;
        featureParams.surfUpright = false;
        featureParams.orbNFeatures = 1000;
        featureParams.orbScaleFactor = 1.2;
        featureParams.orbNLevels = 8;
        featureParams.orbEdgeThreshold = 31;
        featureParams.orbFirstLevel = 0;
        featureParams.orbWTA_K = 2;
        featureParams.orbScoreType = ORB::HARRIS_SCORE;
        featureParams.orbPatchSize = 31;
        featureParams.orbFastThreshold = 20;
        featureParams.akazeDescriptorType = AKAZE::DESCRIPTOR_MLDB;
        featureParams.akazeDescriptorSize = 0;
        featureParams.akazeDescriptorChannels = 3;
        featureParams.akazeThreshold = 0.001;
        featureParams.akazeNOctaves = 4;
        featureParams.akazeNOctaveLayers = 4;
        featureParams.akazeDiffusivity = KAZE::DIFF_PM_G2;
        featureParams.briskThresh = 30;
        featureParams.briskOctaves = 3;
        featureParams.briskPatternScale = 1.0;
        featureParams.freakOrientationNormalized = true;
        featureParams.freakScaleNormalized = true;
        featureParams.freakPatternScale = 22.0;
        featureParams.freakNOctaves = 4;
        featureParams.briefBytes = 32;
        featureParams.briefUseOrientation = false;
        featureParams.cnnModelPath = "model.pb";
        featureParams.cnnConfigPath = "config.pbtxt";
        featureParams.cnnClassesPath = "classes.txt";
        featureParams.cnnUseGPU = false;
        featureParams.cnnUseOpenVINO = false;
        featureParams.cnnUseCUDA = false;
        featureParams.cnnUseCPU = true;
        featureParams.cnnBackend = DNN_BACKEND_OPENCV;
        featureParams.cnnTarget = DNN_TARGET_CPU;
        featureParams.cnnScaleFactor = 1.0 / 255.0;
        featureParams.cnnMean = Scalar(0, 0, 0);
        featureParams.cnnSwapRB = true;
        featureParams.cnnCrop = false;
        featureParams.cnnInputWidth = 224;
        featureParams.cnnInputHeight = 224;
        featureParams.cnnConfidenceThreshold = 0.5;
        featureParams.cnnNmsThreshold = 0.4;
        featureParams.cnnMaxDetections = 100;
        featureParams.cnnIouThreshold = 0.5;
        featureParams.cnnScoreThreshold = 0.5;
        featureParams.cnnUseSoftNMS = false;
        featureParams.cnnSoftNMSThreshold = 0.5;
        featureParams.cnnSoftNMSSigma = 0.5;
        featureParams.cnnUseMultiScale = false;
        featureParams.cnnScales = {0.5, 1.0, 1.5};
        featureParams.cnnUseFlip = false;
        featureParams.cnnUseRotation = false;
        featureParams.cnnRotationAngles = {0, 90, 180, 270};
        featureParams.cnnUseDataAugmentation = false;
        featureParams.cnnUseTransferLearning = false;
        featureParams.cnnPretrainedModel = "";
        featureParams.cnnUseFineTuning = false;
        featureParams.cnnFineTuningRate = 0.001;
        featureParams.cnnUseEnsemble = false;
        featureParams.cnnEnsembleSize = 5;
        featureParams.cnnUseCrossValidation = false;
        featureParams.cnnCrossValidationFolds = 5;
        featureParams.cnnUseGridSearch = false;
        featureParams.cnnUseRandomSearch = false;
        featureParams.cnnRandomSearchIterations = 100;
        featureParams.cnnUseBayesianOptimization = false;
        featureParams.cnnBayesianOptimizationIterations = 100;
        featureParams.cnnUseHyperband = false;
        featureParams.cnnHyperbandMaxIterations = 100;
        featureParams.cnnUseSuccessiveHalving = false;
        featureParams.cnnSuccessiveHalvingIterations = 100;
        featureParams.cnnUseMedianStopping = false;
        featureParams.cnnMedianStoppingIterations = 100;
        featureParams.cnnUseASHA = false;
        featureParams.cnnASHAIterations = 100;
        featureParams.cnnUseBOHB = false;
        featureParams.cnnBOHBIterations = 100;
        featureParams.cnnUseOptuna = false;
        featureParams.cnnOptunaIterations = 100;
        featureParams.cnnUseRayTune = false;
        featureParams.cnnRayTuneIterations = 100;
        featureParams.cnnUseWeightsAndBiases = false;
        featureParams.cnnUseMLflow = false;
        featureParams.cnnUseTensorBoard = false;
        featureParams.cnnUseVisdom = false;
        featureParams.cnnUseNeptune = false;
        featureParams.cnnUseComet = false;
        featureParams.cnnUseSacred = false;
        featureParams.cnnUseGuild = false;
        featureParams.cnnUsePolyaxon = false;
        featureParams.cnnUseKubeflow = false;
        featureParams.cnnUseSeldon = false;
        featureParams.cnnUseBentoML = false;
        featureParams.cnnUseCortex = false;
        featureParams.cnnUseSageMaker = false;
        featureParams.cnnUseAzureML = false;
        featureParams.cnnUseGCPML = false;
        featureParams.cnnUseIBMCloudML = false;
        featureParams.cnnUseOracleCloudML = false;
        featureParams.cnnUseAlibabaCloudML = false;
        featureParams.cnnUseTencentCloudML = false;
        featureParams.cnnUseBaiduCloudML = false;
        featureParams.cnnUseHuaweiCloudML = false;
        featureParams.cnnUseJDCloudML = false;
        featureParams.cnnUseUCloudML = false;
        featureParams.cnnUseQingCloudML = false;
        featureParams.cnnUseEasystackML = false;
        featureParams.cnnUseOpenStackML = false;
        featureParams.cnnUseKubernetesML = false;
        featureParams.cnnUseDockerML = false;
        featureParams.cnnUseSingularityML = false;
        featureParams.cnnUsePodmanML = false;
        featureParams.cnnUseLXCML = false;
        featureParams.cnnUseLXDML = false;
        featureParams.cnnUseVagrantML = false;
        featureParams.cnnUseVirtualBoxML = false;
        featureParams.cnnUseVMwareML = false;
        featureParams.cnnUseHyperVML = false;
        featureParams.cnnUseKVMML = false;
        featureParams.cnnUseXenML = false;
        featureParams.cnnUseQEMUML = false;
        featureParams.cnnUseBochsML = false;
        featureParams.cnnUseDOSBoxML = false;
        featureParams.cnnUseWineML = false;
        featureParams.cnnUseCygwinML = false;
        featureParams.cnnUseMSYS2ML = false;
        featureParams.cnnUseGitBashML = false;
        featureParams.cnnUsePowerShellML = false;
        featureParams.cnnUseCommandPromptML = false;
        featureParams.cnnUseTerminalML = false;
        featureParams.cnnUseBashML = false;
        featureParams.cnnUseZshML = false;
        featureParams.cnnUseFishML = false;
        featureParams.cnnUseTcshML = false;
        featureParams.cnnUseCshML = false;
        featureParams.cnnUseKshML = false;
        featureParams.cnnUseAshML = false;
        featureParams.cnnUseDashML = false;
        featureParams.cnnUseMkshML = false;
        featureParams.cnnUsePdkshML = false;
        featureParams.cnnUseRcML = false;
        featureParams.cnnUseEsML = false;
        featureParams.cnnUseScshML = false;
        featureParams.cnnUseIshML = false;
        featureParams.cnnUseYashML = false;
        featureParams.cnnUseElvishML = false;
        featureParams.cnnUseNushellML = false;
        featureParams.cnnUseXonshML = false;
        featureParams.cnnUseOilML = false;
        featureParams.cnnUsePwshML = false;
        featureParams.cnnUsePowerShellCoreML = false;
        featureParams.cnnUsePowerShell7ML = false;
        featureParams.cnnUsePowerShell8ML = false;
        featureParams.cnnUsePowerShell9ML = false;
        featureParams.cnnUsePowerShell10ML = false;
        featureParams.cnnUsePowerShell11ML = false;
        featureParams.cnnUsePowerShell12ML = false;
        featureParams.cnnUsePowerShell13ML = false;
        featureParams.cnnUsePowerShell14ML = false;
        featureParams.cnnUsePowerShell15ML = false;
        featureParams.cnnUsePowerShell16ML = false;
        featureParams.cnnUsePowerShell17ML = false;
        featureParams.cnnUsePowerShell18ML = false;
        featureParams.cnnUsePowerShell19ML = false;
        featureParams.cnnUsePowerShell20ML = false;
        featureParams.cnnUsePowerShell21ML = false;
        featureParams.cnnUsePowerShell22ML = false;
        featureParams.cnnUsePowerShell23ML = false;
        featureParams.cnnUsePowerShell24ML = false;
        featureParams.cnnUsePowerShell25ML = false;
        featureParams.cnnUsePowerShell26ML = false;
        featureParams.cnnUsePowerShell27ML = false;
        featureParams.cnnUsePowerShell28ML = false;
        featureParams.cnnUsePowerShell29ML = false;
        featureParams.cnnUsePowerShell30ML = false;
        featureParams.cnnUsePowerShell31ML = false;
        featureParams.cnnUsePowerShell32ML = false;
        featureParams.cnnUsePowerShell33ML = false;
        featureParams.cnnUsePowerShell34ML = false;
        featureParams.cnnUsePowerShell35ML = false;
        featureParams.cnnUsePowerShell36ML = false;
        featureParams.cnnUsePowerShell37ML = false;
        featureParams.cnnUsePowerShell38ML = false;
        featureParams.cnnUsePowerShell39ML = false;
        featureParams.cnnUsePowerShell40ML = false;
        featureParams.cnnUsePowerShell41ML = false;
        featureParams.cnnUsePowerShell42ML = false;
        featureParams.cnnUsePowerShell43ML = false;
        featureParams.cnnUsePowerShell44ML = false;
        featureParams.cnnUsePowerShell45ML = false;
        featureParams.cnnUsePowerShell46ML = false;
        featureParams.cnnUsePowerShell47ML = false;
        featureParams.cnnUsePowerShell48ML = false;
        featureParams.cnnUsePowerShell49ML = false;
        featureParams.cnnUsePowerShell50ML = false;
        featureParams.cnnUsePowerShell51ML = false;
        featureParams.cnnUsePowerShell52ML = false;
        featureParams.cnnUsePowerShell53ML = false;
        featureParams.cnnUsePowerShell54ML = false;
        featureParams.cnnUsePowerShell55ML = false;
        featureParams.cnnUsePowerShell56ML = false;
        featureParams.cnnUsePowerShell57ML = false;
        featureParams.cnnUsePowerShell58ML = false;
        featureParams.cnnUsePowerShell59ML = false;
        featureParams.cnnUsePowerShell60ML = false;
        featureParams.cnnUsePowerShell61ML = false;
        featureParams.cnnUsePowerShell62ML = false;
        featureParams.cnnUsePowerShell63ML = false;
        featureParams.cnnUsePowerShell64ML = false;
        featureParams.cnnUsePowerShell65ML = false;
        featureParams.cnnUsePowerShell66ML = false;
        featureParams.cnnUsePowerShell67ML = false;
        featureParams.cnnUsePowerShell68ML = false;
        featureParams.cnnUsePowerShell69ML = false;
        featureParams.cnnUsePowerShell70ML = false;
        featureParams.cnnUsePowerShell71ML = false;
        featureParams.cnnUsePowerShell72ML = false;
        featureParams.cnnUsePowerShell73ML = false;
        featureParams.cnnUsePowerShell74ML = false;
        featureParams.cnnUsePowerShell75ML = false;
        featureParams.cnnUsePowerShell76ML = false;
        featureParams.cnnUsePowerShell77ML = false;
        featureParams.cnnUsePowerShell78ML = false;
        featureParams.cnnUsePowerShell79ML = false;
        featureParams.cnnUsePowerShell80ML = false;
        featureParams.cnnUsePowerShell81ML = false;
        featureParams.cnnUsePowerShell82ML = false;
        featureParams.cnnUsePowerShell83ML = false;
        featureParams.cnnUsePowerShell84ML = false;
        featureParams.cnnUsePowerShell85ML = false;
        featureParams.cnnUsePowerShell86ML = false;
        featureParams.cnnUsePowerShell87ML = false;
        featureParams.cnnUsePowerShell88ML = false;
        featureParams.cnnUsePowerShell89ML = false;
        featureParams.cnnUsePowerShell90ML = false;
        featureParams.cnnUsePowerShell91ML = false;
        featureParams.cnnUsePowerShell92ML = false;
        featureParams.cnnUsePowerShell93ML = false;
        featureParams.cnnUsePowerShell94ML = false;
        featureParams.cnnUsePowerShell95ML = false;
        featureParams.cnnUsePowerShell96ML = false;
        featureParams.cnnUsePowerShell97ML = false;
        featureParams.cnnUsePowerShell98ML = false;
        featureParams.cnnUsePowerShell99ML = false;
        featureParams.cnnUsePowerShell100ML = false;
        
        // Initialize ML algorithm and feature extraction method
        MLAlgorithm currentAlgorithm = SVM_CLASSIFIER;
        FeatureExtractionMethod currentFeatureMethod = HOG_FEATURES;
        
        // Create Mat objects for frame processing
        Mat frame, features, visualization;
        Ptr<ml::StatModel> classifier;
        
        // Generate synthetic training data
        Mat trainingData, trainingLabels;
        generateSyntheticTrainingData(trainingData, trainingLabels, 1000);
        
        // Train classifier
        if (!trainMLClassifier(trainingData, trainingLabels, classifier, currentAlgorithm, mlParams)) {
            cout << "Warning: Could not train ML classifier. Using random predictions." << endl;
        }
        
        cout << "\nStarting camera feed with machine learning..." << endl;
        cout << "Controls:" << endl;
        cout << "  'q' - Quit" << endl;
        cout << "  '0' - SVM Classifier" << endl;
        cout << "  '1' - Random Forest" << endl;
        cout << "  '2' - K-Nearest Neighbors" << endl;
        cout << "  '3' - Naive Bayes" << endl;
        cout << "  '4' - Decision Tree" << endl;
        cout << "  '5' - Neural Network" << endl;
        cout << "  '6' - Deep Learning" << endl;
        cout << "  '7' - Convolutional Neural Network" << endl;
        cout << "  '8' - Recurrent Neural Network" << endl;
        cout << "  '9' - Generative Adversarial Network" << endl;
        cout << "  'a' - HOG Features" << endl;
        cout << "  'b' - LBP Features" << endl;
        cout << "  'c' - SIFT Features" << endl;
        cout << "  'd' - SURF Features" << endl;
        cout << "  'e' - ORB Features" << endl;
        cout << "  'f' - AKAZE Features" << endl;
        cout << "  'g' - BRISK Features" << endl;
        cout << "  'h' - FREAK Features" << endl;
        cout << "  'i' - BRIEF Features" << endl;
        cout << "  'j' - CNN Features" << endl;
        cout << "  'm' - Send to MATLAB" << endl;
        cout << "  's' - Save current prediction" << endl;
        
        // Main capture loop
        while (true) {
            // Capture frame from camera
            cap >> frame;
            
            // Check if frame was captured successfully
            if (frame.empty()) {
                cerr << "Warning: Could not capture frame!" << endl;
                continue;
            }
            
            // Extract features
            Mat extractedFeatures;
            if (extractFeatures(frame, extractedFeatures, currentFeatureMethod, featureParams)) {
                // Predict using ML classifier
                float prediction, confidence;
                if (classifier && predictMLClassifier(classifier, extractedFeatures, prediction, confidence)) {
                    // Create visualization
                    visualization = frame.clone();
                    
                    // Draw prediction
                    string predictionText = "Prediction: " + to_string(prediction);
                    string confidenceText = "Confidence: " + to_string(confidence);
                    
                    putText(visualization, predictionText, Point(10, 30), FONT_HERSHEY_SIMPLEX, 1, Scalar(0, 255, 0), 2);
                    putText(visualization, confidenceText, Point(10, 70), FONT_HERSHEY_SIMPLEX, 1, Scalar(0, 255, 0), 2);
                    
                    // Draw algorithm and feature method
                    string algorithmText = "Algorithm: " + getMLAlgorithmName(currentAlgorithm);
                    string featureText = "Features: " + getFeatureExtractionMethodName(currentFeatureMethod);
                    
                    putText(visualization, algorithmText, Point(10, 110), FONT_HERSHEY_SIMPLEX, 0.7, Scalar(255, 0, 0), 2);
                    putText(visualization, featureText, Point(10, 150), FONT_HERSHEY_SIMPLEX, 0.7, Scalar(255, 0, 0), 2);
                } else {
                    visualization = frame.clone();
                    putText(visualization, "No prediction available", Point(10, 30), FONT_HERSHEY_SIMPLEX, 1, Scalar(0, 0, 255), 2);
                }
            } else {
                visualization = frame.clone();
                putText(visualization, "Feature extraction failed", Point(10, 30), FONT_HERSHEY_SIMPLEX, 1, Scalar(0, 0, 255), 2);
            }
            
            // Display the visualization
            imshow("Advanced Machine Learning for Computer Vision", visualization);
            
            // Handle keyboard input
            char key = waitKey(1) & 0xFF;
            
            if (key == 'q' || key == 27) { // 'q' or ESC to quit
                cout << "Quitting..." << endl;
                break;
            }
            else if (key >= '0' && key <= '9') { // ML algorithm selection
                currentAlgorithm = static_cast<MLAlgorithm>(key - '0');
                cout << "Selected ML algorithm: " << getMLAlgorithmName(currentAlgorithm) << endl;
                
                // Retrain classifier
                if (!trainMLClassifier(trainingData, trainingLabels, classifier, currentAlgorithm, mlParams)) {
                    cout << "Warning: Could not train ML classifier." << endl;
                }
            }
            else if (key >= 'a' && key <= 'j') { // Feature extraction method selection
                currentFeatureMethod = static_cast<FeatureExtractionMethod>(key - 'a');
                cout << "Selected feature extraction method: " << getFeatureExtractionMethodName(currentFeatureMethod) << endl;
            }
            else if (key == 'm') { // Send to MATLAB
                Mat extractedFeatures;
                if (extractFeatures(frame, extractedFeatures, currentFeatureMethod, featureParams)) {
                    float prediction, confidence;
                    if (classifier && predictMLClassifier(classifier, extractedFeatures, prediction, confidence)) {
                        sendMLDataToMATLAB(matlabPtr, frame, extractedFeatures, prediction, confidence, 
                                          currentAlgorithm, currentFeatureMethod);
                    }
                }
            }
            else if (key == 's') { // Save current prediction
                string filename = "ml_" + getMLAlgorithmName(currentAlgorithm) + 
                                "_" + getFeatureExtractionMethodName(currentFeatureMethod) + ".jpg";
                imwrite(filename, visualization);
                cout << "ML prediction saved as: " << filename << endl;
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
 * @brief Function to generate synthetic training data
 * @param trainingData Output training data
 * @param trainingLabels Output training labels
 * @param numSamples Number of samples
 */
void generateSyntheticTrainingData(Mat& trainingData, Mat& trainingLabels, int numSamples) {
    // Generate random training data
    trainingData = Mat::zeros(numSamples, 100, CV_32F);
    trainingLabels = Mat::zeros(numSamples, 1, CV_32S);
    
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<float> dis(0.0, 1.0);
    uniform_int_distribution<int> labelDis(0, 1);
    
    for (int i = 0; i < numSamples; i++) {
        for (int j = 0; j < 100; j++) {
            trainingData.at<float>(i, j) = dis(gen);
        }
        trainingLabels.at<int>(i, 0) = labelDis(gen);
    }
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
 * g++ -std=c++17 camera_advanced_25.cpp -o camera_advanced_25 \
 *     `pkg-config --cflags --libs opencv4` \
 *     -I/Applications/MATLAB_R2023b.app/extern/include \
 *     -L/Applications/MATLAB_R2023b.app/bin/maci64 \
 *     -lMatlabDataArray -lMatlabEngine
 * 
 * @brief Usage:
 * 1. Make sure your camera is connected and working
 * 2. Run the executable: ./camera_advanced_25
 * 3. Use keyboard controls to switch between ML algorithms
 * 4. Use keyboard controls to switch between feature extraction methods
 * 5. Press 'm' to send data to MATLAB
 * 6. Press 's' to save current prediction
 * 
 * @brief Learning Objectives:
 * - Understand advanced machine learning techniques
 * - Learn different ML algorithms (SVM, Random Forest, KNN, etc.)
 * - Understand feature extraction methods
 * - Learn HOG, LBP, SIFT, SURF, ORB, AKAZE, BRISK, FREAK, BRIEF features
 * - Learn CNN feature extraction
 * - Learn MATLAB integration for ML analysis
 * - Understand computer vision applications of ML
 */
