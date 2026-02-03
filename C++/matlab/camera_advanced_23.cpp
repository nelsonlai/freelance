/**
 * @file camera_advanced_23.cpp
 * @brief Advanced Object Detection and Recognition - Advanced Level 23
 * @description This program demonstrates advanced object detection and recognition
 *              using deep learning models, feature matching, and classification
 *              with OpenCV and MATLAB integration.
 * @author Educational C++ MATLAB Integration Project
 * @date 2024
 * @version 1.0
 */

#include <opencv2/opencv.hpp>
#include <opencv2/dnn.hpp>
#include <opencv2/features2d.hpp>
#include <opencv2/ml.hpp>
#include <iostream>
#include <matlab/engine.hpp>
#include <memory>
#include <vector>
#include <string>
#include <map>
#include <algorithm>

using namespace cv;
using namespace std;

/**
 * @brief Enumeration for different detection methods
 */
enum DetectionMethod {
    YOLO_V3 = 0,
    YOLO_V4 = 1,
    YOLO_V5 = 2,
    SSD_MOBILENET = 3,
    RCNN = 4,
    FAST_RCNN = 5,
    FASTER_RCNN = 6,
    MASK_RCNN = 7,
    RETINANET = 8,
    CENTERNET = 9
};

/**
 * @brief Enumeration for different recognition methods
 */
enum RecognitionMethod {
    SIFT_RECOGNITION = 0,
    SURF_RECOGNITION = 1,
    ORB_RECOGNITION = 2,
    AKAZE_RECOGNITION = 3,
    BRISK_RECOGNITION = 4,
    FREAK_RECOGNITION = 5,
    BRIEF_RECOGNITION = 6,
    LBP_RECOGNITION = 7,
    HOG_RECOGNITION = 8,
    CNN_RECOGNITION = 9
};

/**
 * @brief Structure to hold detection parameters
 */
struct DetectionParams {
    double confidenceThreshold;
    double nmsThreshold;
    int inputWidth;
    int inputHeight;
    double scaleFactor;
    Scalar mean;
    bool swapRB;
    bool crop;
    int backend;
    int target;
    bool useOpenVINO;
    bool useCUDA;
    bool useCPU;
    int maxDetections;
    double iouThreshold;
    double scoreThreshold;
    bool useSoftNMS;
    double softNMSThreshold;
    double softNMSSigma;
    bool useMultiScale;
    vector<double> scales;
    bool useFlip;
    bool useRotation;
    vector<double> rotationAngles;
};

/**
 * @brief Structure to hold recognition parameters
 */
struct RecognitionParams {
    int maxFeatures;
    double featureThreshold;
    double matchThreshold;
    int nOctaves;
    int nOctaveLayers;
    double contrastThreshold;
    double edgeThreshold;
    double sigma;
    bool useOrientation;
    bool useScale;
    bool useAffine;
    double affineThreshold;
    int affineIterations;
    bool useDescriptor;
    int descriptorSize;
    int descriptorChannels;
    bool useKeypoint;
    bool useDescriptorMatch;
    double descriptorThreshold;
    int maxMatches;
    bool useRatioTest;
    double ratioThreshold;
    bool useCrossCheck;
    bool useKNNMatch;
    int knnMatches;
    bool useFlannMatch;
    int flannTrees;
    int flannChecks;
    bool useBruteForceMatch;
    bool useHammingMatch;
    bool useL2Match;
    bool useL1Match;
};

/**
 * @brief Structure to hold detected object information
 */
struct DetectedObject {
    string className;
    int classId;
    float confidence;
    Rect boundingBox;
    Point2f center;
    float width;
    float height;
    float area;
    float aspectRatio;
    vector<KeyPoint> keypoints;
    Mat descriptor;
    vector<DMatch> matches;
    bool isRecognized;
    string recognizedClass;
    float recognitionConfidence;
};

/**
 * @brief Function to get detection method name
 * @param method Detection method
 * @return string Method name
 */
string getDetectionMethodName(DetectionMethod method) {
    switch (method) {
        case YOLO_V3: return "YOLO v3";
        case YOLO_V4: return "YOLO v4";
        case YOLO_V5: return "YOLO v5";
        case SSD_MOBILENET: return "SSD MobileNet";
        case RCNN: return "R-CNN";
        case FAST_RCNN: return "Fast R-CNN";
        case FASTER_RCNN: return "Faster R-CNN";
        case MASK_RCNN: return "Mask R-CNN";
        case RETINANET: return "RetinaNet";
        case CENTERNET: return "CenterNet";
        default: return "Unknown";
    }
}

/**
 * @brief Function to get recognition method name
 * @param method Recognition method
 * @return string Method name
 */
string getRecognitionMethodName(RecognitionMethod method) {
    switch (method) {
        case SIFT_RECOGNITION: return "SIFT";
        case SURF_RECOGNITION: return "SURF";
        case ORB_RECOGNITION: return "ORB";
        case AKAZE_RECOGNITION: return "AKAZE";
        case BRISK_RECOGNITION: return "BRISK";
        case FREAK_RECOGNITION: return "FREAK";
        case BRIEF_RECOGNITION: return "BRIEF";
        case LBP_RECOGNITION: return "LBP";
        case HOG_RECOGNITION: return "HOG";
        case CNN_RECOGNITION: return "CNN";
        default: return "Unknown";
    }
}

/**
 * @brief Function to load YOLO model
 * @param net Output network
 * @param method Detection method
 * @return bool Success status
 */
bool loadYOLOModel(dnn::Net& net, DetectionMethod method) {
    try {
        string configFile, weightsFile;
        
        switch (method) {
            case YOLO_V3:
                configFile = "yolov3.cfg";
                weightsFile = "yolov3.weights";
                break;
            case YOLO_V4:
                configFile = "yolov4.cfg";
                weightsFile = "yolov4.weights";
                break;
            case YOLO_V5:
                configFile = "yolov5s.onnx";
                weightsFile = "";
                break;
            default:
                return false;
        }
        
        if (method == YOLO_V5) {
            net = dnn::readNetFromONNX(configFile);
        } else {
            net = dnn::readNetFromDarknet(configFile, weightsFile);
        }
        
        return !net.empty();
    } catch (const std::exception& e) {
        cerr << "Error loading YOLO model: " << e.what() << endl;
        return false;
    }
}

/**
 * @brief Function to load SSD model
 * @param net Output network
 * @param method Detection method
 * @return bool Success status
 */
bool loadSSDModel(dnn::Net& net, DetectionMethod method) {
    try {
        string configFile, weightsFile;
        
        switch (method) {
            case SSD_MOBILENET:
                configFile = "ssd_mobilenet_v2_coco.pbtxt";
                weightsFile = "ssd_mobilenet_v2_coco.pb";
                break;
            default:
                return false;
        }
        
        net = dnn::readNetFromTensorflow(weightsFile, configFile);
        
        return !net.empty();
    } catch (const std::exception& e) {
        cerr << "Error loading SSD model: " << e.what() << endl;
        return false;
    }
}

/**
 * @brief Function to load R-CNN model
 * @param net Output network
 * @param method Detection method
 * @return bool Success status
 */
bool loadRCNNModel(dnn::Net& net, DetectionMethod method) {
    try {
        string configFile, weightsFile;
        
        switch (method) {
            case RCNN:
                configFile = "rcnn.pbtxt";
                weightsFile = "rcnn.pb";
                break;
            case FAST_RCNN:
                configFile = "fast_rcnn.pbtxt";
                weightsFile = "fast_rcnn.pb";
                break;
            case FASTER_RCNN:
                configFile = "faster_rcnn.pbtxt";
                weightsFile = "faster_rcnn.pb";
                break;
            case MASK_RCNN:
                configFile = "mask_rcnn.pbtxt";
                weightsFile = "mask_rcnn.pb";
                break;
            default:
                return false;
        }
        
        net = dnn::readNetFromTensorflow(weightsFile, configFile);
        
        return !net.empty();
    } catch (const std::exception& e) {
        cerr << "Error loading R-CNN model: " << e.what() << endl;
        return false;
    }
}

/**
 * @brief Function to load detection model
 * @param net Output network
 * @param method Detection method
 * @return bool Success status
 */
bool loadDetectionModel(dnn::Net& net, DetectionMethod method) {
    switch (method) {
        case YOLO_V3:
        case YOLO_V4:
        case YOLO_V5:
            return loadYOLOModel(net, method);
        case SSD_MOBILENET:
            return loadSSDModel(net, method);
        case RCNN:
        case FAST_RCNN:
        case FASTER_RCNN:
        case MASK_RCNN:
            return loadRCNNModel(net, method);
        default:
            return false;
    }
}

/**
 * @brief Function to perform YOLO detection
 * @param net Network
 * @param frame Input frame
 * @param detections Output detections
 * @param params Detection parameters
 * @return bool Success status
 */
bool performYOLODetection(dnn::Net& net, const Mat& frame, vector<DetectedObject>& detections, 
                         const DetectionParams& params) {
    try {
        // Create blob from frame
        Mat blob = dnn::blobFromImage(frame, params.scaleFactor, 
                                     Size(params.inputWidth, params.inputHeight), 
                                     params.mean, params.swapRB, params.crop);
        
        // Set input
        net.setInput(blob);
        
        // Forward pass
        vector<Mat> outputs;
        net.forward(outputs, net.getUnconnectedOutLayersNames());
        
        // Parse outputs
        vector<int> classIds;
        vector<float> confidences;
        vector<Rect> boxes;
        
        for (const auto& output : outputs) {
            float* data = (float*)output.data;
            
            for (int i = 0; i < output.rows; i++) {
                float confidence = data[i * output.cols + 4];
                
                if (confidence > params.confidenceThreshold) {
                    // Get class scores
                    Mat scores = output.row(i).colRange(5, output.cols);
                    Point classIdPoint;
                    double maxClassScore;
                    minMaxLoc(scores, nullptr, &maxClassScore, nullptr, &classIdPoint);
                    
                    if (maxClassScore > params.scoreThreshold) {
                        // Get bounding box
                        float centerX = data[i * output.cols + 0] * frame.cols;
                        float centerY = data[i * output.cols + 1] * frame.rows;
                        float width = data[i * output.cols + 2] * frame.cols;
                        float height = data[i * output.cols + 3] * frame.rows;
                        
                        int left = static_cast<int>(centerX - width / 2);
                        int top = static_cast<int>(centerY - height / 2);
                        
                        classIds.push_back(classIdPoint.x);
                        confidences.push_back(static_cast<float>(maxClassScore));
                        boxes.push_back(Rect(left, top, static_cast<int>(width), static_cast<int>(height)));
                    }
                }
            }
        }
        
        // Apply NMS
        vector<int> indices;
        dnn::NMSBoxes(boxes, confidences, params.confidenceThreshold, params.nmsThreshold, indices);
        
        // Create detections
        detections.clear();
        for (int idx : indices) {
            DetectedObject obj;
            obj.classId = classIds[idx];
            obj.confidence = confidences[idx];
            obj.boundingBox = boxes[idx];
            obj.center = Point2f(boxes[idx].x + boxes[idx].width / 2, 
                                boxes[idx].y + boxes[idx].height / 2);
            obj.width = boxes[idx].width;
            obj.height = boxes[idx].height;
            obj.area = boxes[idx].area();
            obj.aspectRatio = static_cast<float>(boxes[idx].width) / boxes[idx].height;
            obj.isRecognized = false;
            
            detections.push_back(obj);
        }
        
        return true;
    } catch (const std::exception& e) {
        cerr << "Error in YOLO detection: " << e.what() << endl;
        return false;
    }
}

/**
 * @brief Function to perform SSD detection
 * @param net Network
 * @param frame Input frame
 * @param detections Output detections
 * @param params Detection parameters
 * @return bool Success status
 */
bool performSSDDetection(dnn::Net& net, const Mat& frame, vector<DetectedObject>& detections, 
                        const DetectionParams& params) {
    try {
        // Create blob from frame
        Mat blob = dnn::blobFromImage(frame, params.scaleFactor, 
                                     Size(params.inputWidth, params.inputHeight), 
                                     params.mean, params.swapRB, params.crop);
        
        // Set input
        net.setInput(blob);
        
        // Forward pass
        Mat output = net.forward();
        
        // Parse output
        detections.clear();
        for (int i = 0; i < output.rows; i++) {
            float confidence = output.at<float>(i, 2);
            
            if (confidence > params.confidenceThreshold) {
                int classId = static_cast<int>(output.at<float>(i, 1));
                
                // Get bounding box
                float left = output.at<float>(i, 3) * frame.cols;
                float top = output.at<float>(i, 4) * frame.rows;
                float right = output.at<float>(i, 5) * frame.cols;
                float bottom = output.at<float>(i, 6) * frame.rows;
                
                DetectedObject obj;
                obj.classId = classId;
                obj.confidence = confidence;
                obj.boundingBox = Rect(static_cast<int>(left), static_cast<int>(top),
                                      static_cast<int>(right - left), static_cast<int>(bottom - top));
                obj.center = Point2f(left + (right - left) / 2, top + (bottom - top) / 2);
                obj.width = right - left;
                obj.height = bottom - top;
                obj.area = obj.width * obj.height;
                obj.aspectRatio = obj.width / obj.height;
                obj.isRecognized = false;
                
                detections.push_back(obj);
            }
        }
        
        return true;
    } catch (const std::exception& e) {
        cerr << "Error in SSD detection: " << e.what() << endl;
        return false;
    }
}

/**
 * @brief Function to perform object detection
 * @param net Network
 * @param frame Input frame
 * @param detections Output detections
 * @param method Detection method
 * @param params Detection parameters
 * @return bool Success status
 */
bool performObjectDetection(dnn::Net& net, const Mat& frame, vector<DetectedObject>& detections, 
                           DetectionMethod method, const DetectionParams& params) {
    switch (method) {
        case YOLO_V3:
        case YOLO_V4:
        case YOLO_V5:
            return performYOLODetection(net, frame, detections, params);
        case SSD_MOBILENET:
            return performSSDDetection(net, frame, detections, params);
        default:
            return false;
    }
}

/**
 * @brief Function to extract features for recognition
 * @param frame Input frame
 * @param keypoints Output keypoints
 * @param descriptors Output descriptors
 * @param method Recognition method
 * @param params Recognition parameters
 * @return bool Success status
 */
bool extractFeatures(const Mat& frame, vector<KeyPoint>& keypoints, Mat& descriptors, 
                    RecognitionMethod method, const RecognitionParams& params) {
    try {
        // Convert to grayscale
        Mat gray;
        cvtColor(frame, gray, COLOR_BGR2GRAY);
        
        // Create detector based on method
        Ptr<Feature2D> detector;
        
        switch (method) {
            case SIFT_RECOGNITION:
                detector = SIFT::create(params.maxFeatures, params.nOctaves, 
                                      params.contrastThreshold, params.edgeThreshold, params.sigma);
                break;
            case SURF_RECOGNITION:
                detector = SURF::create(params.featureThreshold, params.nOctaves, 
                                      params.nOctaveLayers, params.useOrientation, params.useScale);
                break;
            case ORB_RECOGNITION:
                detector = ORB::create(params.maxFeatures, params.scaleFactor, 
                                      params.nOctaves, params.edgeThreshold, 0, 2, 
                                      ORB::HARRIS_SCORE, params.descriptorSize, 20);
                break;
            case AKAZE_RECOGNITION:
                detector = AKAZE::create(params.featureThreshold, params.nOctaves, 
                                       params.nOctaveLayers, params.contrastThreshold, 
                                       params.edgeThreshold, params.sigma, params.descriptorSize, 
                                       params.descriptorChannels);
                break;
            case BRISK_RECOGNITION:
                detector = BRISK::create(params.featureThreshold, params.nOctaves, params.contrastThreshold);
                break;
            case FREAK_RECOGNITION:
                detector = FREAK::create(params.useOrientation, params.useScale, 
                                       params.descriptorSize, params.descriptorChannels);
                break;
            case BRIEF_RECOGNITION:
                detector = BriefDescriptorExtractor::create(params.descriptorSize);
                break;
            default:
                detector = SIFT::create();
                break;
        }
        
        // Detect and compute
        detector->detectAndCompute(gray, noArray(), keypoints, descriptors);
        
        return !keypoints.empty() && !descriptors.empty();
    } catch (const std::exception& e) {
        cerr << "Error extracting features: " << e.what() << endl;
        return false;
    }
}

/**
 * @brief Function to match features
 * @param descriptors1 First descriptor set
 * @param descriptors2 Second descriptor set
 * @param matches Output matches
 * @param method Recognition method
 * @param params Recognition parameters
 * @return bool Success status
 */
bool matchFeatures(const Mat& descriptors1, const Mat& descriptors2, vector<DMatch>& matches, 
                  RecognitionMethod method, const RecognitionParams& params) {
    try {
        // Create matcher based on method
        Ptr<DescriptorMatcher> matcher;
        
        switch (method) {
            case SIFT_RECOGNITION:
            case SURF_RECOGNITION:
                matcher = BFMatcher::create(NORM_L2);
                break;
            case ORB_RECOGNITION:
            case BRISK_RECOGNITION:
            case FREAK_RECOGNITION:
            case BRIEF_RECOGNITION:
                matcher = BFMatcher::create(NORM_HAMMING);
                break;
            case AKAZE_RECOGNITION:
                matcher = BFMatcher::create(NORM_L2);
                break;
            default:
                matcher = BFMatcher::create();
                break;
        }
        
        // Match features
        if (params.useKNNMatch) {
            vector<vector<DMatch>> knnMatches;
            matcher->knnMatch(descriptors1, descriptors2, knnMatches, params.knnMatches);
            
            // Apply ratio test
            for (const auto& match : knnMatches) {
                if (match.size() == 2 && match[0].distance < params.ratioThreshold * match[1].distance) {
                    matches.push_back(match[0]);
                }
            }
        } else {
            matcher->match(descriptors1, descriptors2, matches);
        }
        
        // Filter matches by distance
        sort(matches.begin(), matches.end());
        if (matches.size() > params.maxMatches) {
            matches.resize(params.maxMatches);
        }
        
        return !matches.empty();
    } catch (const std::exception& e) {
        cerr << "Error matching features: " << e.what() << endl;
        return false;
    }
}

/**
 * @brief Function to perform object recognition
 * @param frame Input frame
 * @param detections Detected objects
 * @param method Recognition method
 * @param params Recognition parameters
 * @return bool Success status
 */
bool performObjectRecognition(const Mat& frame, vector<DetectedObject>& detections, 
                             RecognitionMethod method, const RecognitionParams& params) {
    try {
        // Extract features from entire frame
        vector<KeyPoint> frameKeypoints;
        Mat frameDescriptors;
        
        if (!extractFeatures(frame, frameKeypoints, frameDescriptors, method, params)) {
            return false;
        }
        
        // Process each detection
        for (auto& detection : detections) {
            // Extract features from detection region
            Mat roi = frame(detection.boundingBox);
            vector<KeyPoint> roiKeypoints;
            Mat roiDescriptors;
            
            if (!extractFeatures(roi, roiKeypoints, roiDescriptors, method, params)) {
                continue;
            }
            
            // Match features
            vector<DMatch> matches;
            if (!matchFeatures(roiDescriptors, frameDescriptors, matches, method, params)) {
                continue;
            }
            
            // Update detection with recognition info
            detection.keypoints = roiKeypoints;
            detection.descriptor = roiDescriptors;
            detection.matches = matches;
            detection.isRecognized = true;
            detection.recognitionConfidence = static_cast<float>(matches.size()) / roiKeypoints.size();
        }
        
        return true;
    } catch (const std::exception& e) {
        cerr << "Error in object recognition: " << e.what() << endl;
        return false;
    }
}

/**
 * @brief Function to draw detection results
 * @param frame Input frame
 * @param detections Detected objects
 * @param method Detection method
 * @return Mat Output frame with detections
 */
Mat drawDetectionResults(const Mat& frame, const vector<DetectedObject>& detections, 
                        DetectionMethod method) {
    Mat result = frame.clone();
    
    for (const auto& detection : detections) {
        // Draw bounding box
        rectangle(result, detection.boundingBox, Scalar(0, 255, 0), 2);
        
        // Draw label
        string label = "Class " + to_string(detection.classId) + 
                      " (" + to_string(detection.confidence) + ")";
        
        if (detection.isRecognized) {
            label += " [R:" + to_string(detection.recognitionConfidence) + "]";
        }
        
        int baseline;
        Size textSize = getTextSize(label, FONT_HERSHEY_SIMPLEX, 0.5, 1, &baseline);
        
        Point labelPos(detection.boundingBox.x, detection.boundingBox.y - 10);
        if (labelPos.y < textSize.height) {
            labelPos.y = detection.boundingBox.y + textSize.height + 10;
        }
        
        rectangle(result, Point(labelPos.x, labelPos.y - textSize.height - 5),
                 Point(labelPos.x + textSize.width, labelPos.y + 5),
                 Scalar(0, 255, 0), -1);
        
        putText(result, label, labelPos, FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0, 0, 0), 1);
        
        // Draw center point
        circle(result, detection.center, 3, Scalar(255, 0, 0), -1);
        
        // Draw keypoints if available
        if (detection.isRecognized && !detection.keypoints.empty()) {
            for (const auto& kp : detection.keypoints) {
                Point2f pt = kp.pt + Point2f(detection.boundingBox.x, detection.boundingBox.y);
                circle(result, pt, 2, Scalar(0, 0, 255), -1);
            }
        }
    }
    
    return result;
}

/**
 * @brief Function to send detection data to MATLAB
 * @param matlabPtr MATLAB engine pointer
 * @param frame Input frame
 * @param detections Detected objects
 * @param detectionMethod Detection method
 * @param recognitionMethod Recognition method
 */
void sendDetectionToMATLAB(std::unique_ptr<matlab::engine::MATLABEngine>& matlabPtr, 
                          const Mat& frame, const vector<DetectedObject>& detections,
                          DetectionMethod detectionMethod, RecognitionMethod recognitionMethod) {
    try {
        // Convert BGR to RGB for MATLAB
        Mat rgbFrame;
        cvtColor(frame, rgbFrame, COLOR_BGR2RGB);
        
        // Create MATLAB arrays
        matlab::data::ArrayFactory factory;
        
        // Frame
        auto dimsFrame = factory.createArray<std::size_t>({1, 3}, 
            {static_cast<std::size_t>(rgbFrame.rows), 
             static_cast<std::size_t>(rgbFrame.cols), 
             static_cast<std::size_t>(rgbFrame.channels())});
        auto matlabFrame = factory.createArray<uint8_t>(dimsFrame);
        auto framePtr = matlabFrame.release();
        memcpy(framePtr, rgbFrame.data, rgbFrame.total() * rgbFrame.elemSize());
        
        // Detection data
        vector<double> classIds, confidences, xCoords, yCoords, widths, heights;
        vector<double> recognitionConfidences;
        vector<string> recognitionStatus;
        
        for (const auto& detection : detections) {
            classIds.push_back(detection.classId);
            confidences.push_back(detection.confidence);
            xCoords.push_back(detection.boundingBox.x);
            yCoords.push_back(detection.boundingBox.y);
            widths.push_back(detection.boundingBox.width);
            heights.push_back(detection.boundingBox.height);
            recognitionConfidences.push_back(detection.recognitionConfidence);
            recognitionStatus.push_back(detection.isRecognized ? "Recognized" : "Not Recognized");
        }
        
        // Set variables in MATLAB workspace
        matlabPtr->setVariable(u"frame", matlabFrame);
        matlabPtr->setVariable(u"classIds", factory.createArray<double>({1, classIds.size()}, classIds.data()));
        matlabPtr->setVariable(u"confidences", factory.createArray<double>({1, confidences.size()}, confidences.data()));
        matlabPtr->setVariable(u"xCoords", factory.createArray<double>({1, xCoords.size()}, xCoords.data()));
        matlabPtr->setVariable(u"yCoords", factory.createArray<double>({1, yCoords.size()}, yCoords.data()));
        matlabPtr->setVariable(u"widths", factory.createArray<double>({1, widths.size()}, widths.data()));
        matlabPtr->setVariable(u"heights", factory.createArray<double>({1, heights.size()}, heights.data()));
        matlabPtr->setVariable(u"recognitionConfidences", factory.createArray<double>({1, recognitionConfidences.size()}, recognitionConfidences.data()));
        
        // Execute MATLAB commands
        string detectionName = getDetectionMethodName(detectionMethod);
        string recognitionName = getRecognitionMethodName(recognitionMethod);
        
        string matlabCmd = "figure; imshow(frame); hold on; "
                          "for i = 1:length(classIds), "
                          "rectangle('Position', [xCoords(i), yCoords(i), widths(i), heights(i)], "
                          "'EdgeColor', 'g', 'LineWidth', 2); "
                          "text(xCoords(i), yCoords(i)-10, "
                          "sprintf('Class %d (%.2f)', classIds(i), confidences(i)), "
                          "'Color', 'g', 'FontSize', 10); "
                          "if recognitionConfidences(i) > 0, "
                          "text(xCoords(i), yCoords(i)+heights(i)+10, "
                          "sprintf('Recognition: %.2f', recognitionConfidences(i)), "
                          "'Color', 'r', 'FontSize', 8); "
                          "end; "
                          "end; "
                          "title('" + detectionName + " + " + recognitionName + " Detection');";
        
        matlabPtr->eval(matlab::engine::convertUTF8StringToUTF16String(matlabCmd));
        
        // Display detection information
        matlabPtr->eval(u"fprintf('Detection Method: " + matlab::engine::convertUTF8StringToUTF16String(detectionName) + "\\n');");
        matlabPtr->eval(u"fprintf('Recognition Method: " + matlab::engine::convertUTF8StringToUTF16String(recognitionName) + "\\n');");
        matlabPtr->eval(u"fprintf('Number of detections: %d\\n', length(classIds));");
        
        cout << "Detection data sent to MATLAB successfully!" << endl;
        
    } catch (const std::exception& e) {
        cerr << "Error sending detection data to MATLAB: " << e.what() << endl;
    }
}

/**
 * @brief Main function for advanced object detection and recognition
 * @return int Exit status
 */
int main() {
    cout << "=== Advanced Object Detection and Recognition - Advanced Level 23 ===" << endl;
    cout << "This program demonstrates advanced object detection and recognition." << endl;
    
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
        
        // Initialize detection parameters
        DetectionParams detectionParams;
        detectionParams.confidenceThreshold = 0.5;
        detectionParams.nmsThreshold = 0.4;
        detectionParams.inputWidth = 416;
        detectionParams.inputHeight = 416;
        detectionParams.scaleFactor = 1.0 / 255.0;
        detectionParams.mean = Scalar(0, 0, 0);
        detectionParams.swapRB = true;
        detectionParams.crop = false;
        detectionParams.backend = DNN_BACKEND_OPENCV;
        detectionParams.target = DNN_TARGET_CPU;
        detectionParams.useOpenVINO = false;
        detectionParams.useCUDA = false;
        detectionParams.useCPU = true;
        detectionParams.maxDetections = 100;
        detectionParams.iouThreshold = 0.5;
        detectionParams.scoreThreshold = 0.5;
        detectionParams.useSoftNMS = false;
        detectionParams.softNMSThreshold = 0.5;
        detectionParams.softNMSSigma = 0.5;
        detectionParams.useMultiScale = false;
        detectionParams.scales = {0.5, 1.0, 1.5};
        detectionParams.useFlip = false;
        detectionParams.useRotation = false;
        detectionParams.rotationAngles = {0, 90, 180, 270};
        
        // Initialize recognition parameters
        RecognitionParams recognitionParams;
        recognitionParams.maxFeatures = 1000;
        recognitionParams.featureThreshold = 0.04;
        recognitionParams.matchThreshold = 0.7;
        recognitionParams.nOctaves = 4;
        recognitionParams.nOctaveLayers = 3;
        recognitionParams.contrastThreshold = 0.04;
        recognitionParams.edgeThreshold = 10;
        recognitionParams.sigma = 1.6;
        recognitionParams.useOrientation = true;
        recognitionParams.useScale = true;
        recognitionParams.useAffine = false;
        recognitionParams.affineThreshold = 0.001;
        recognitionParams.affineIterations = 1000;
        recognitionParams.useDescriptor = true;
        recognitionParams.descriptorSize = 32;
        recognitionParams.descriptorChannels = 1;
        recognitionParams.useKeypoint = true;
        recognitionParams.useDescriptorMatch = true;
        recognitionParams.descriptorThreshold = 0.1;
        recognitionParams.maxMatches = 100;
        recognitionParams.useRatioTest = true;
        recognitionParams.ratioThreshold = 0.7;
        recognitionParams.useCrossCheck = false;
        recognitionParams.useKNNMatch = true;
        recognitionParams.knnMatches = 2;
        recognitionParams.useFlannMatch = false;
        recognitionParams.flannTrees = 5;
        recognitionParams.flannChecks = 50;
        recognitionParams.useBruteForceMatch = true;
        recognitionParams.useHammingMatch = false;
        recognitionParams.useL2Match = true;
        recognitionParams.useL1Match = false;
        
        // Initialize detection and recognition methods
        DetectionMethod currentDetectionMethod = YOLO_V3;
        RecognitionMethod currentRecognitionMethod = SIFT_RECOGNITION;
        
        // Load detection model
        dnn::Net detectionNet;
        if (!loadDetectionModel(detectionNet, currentDetectionMethod)) {
            cout << "Warning: Could not load detection model. Using basic detection." << endl;
        }
        
        // Create Mat objects for frame processing
        Mat frame, detectionFrame, recognitionFrame, visualization;
        vector<DetectedObject> detections;
        
        cout << "\nStarting camera feed with object detection and recognition..." << endl;
        cout << "Controls:" << endl;
        cout << "  'q' - Quit" << endl;
        cout << "  '0' - YOLO v3" << endl;
        cout << "  '1' - YOLO v4" << endl;
        cout << "  '2' - YOLO v5" << endl;
        cout << "  '3' - SSD MobileNet" << endl;
        cout << "  '4' - R-CNN" << endl;
        cout << "  '5' - Fast R-CNN" << endl;
        cout << "  '6' - Faster R-CNN" << endl;
        cout << "  '7' - Mask R-CNN" << endl;
        cout << "  '8' - RetinaNet" << endl;
        cout << "  '9' - CenterNet" << endl;
        cout << "  'a' - SIFT Recognition" << endl;
        cout << "  'b' - SURF Recognition" << endl;
        cout << "  'c' - ORB Recognition" << endl;
        cout << "  'd' - AKAZE Recognition" << endl;
        cout << "  'e' - BRISK Recognition" << endl;
        cout << "  'f' - FREAK Recognition" << endl;
        cout << "  'g' - BRIEF Recognition" << endl;
        cout << "  'h' - LBP Recognition" << endl;
        cout << "  'i' - HOG Recognition" << endl;
        cout << "  'j' - CNN Recognition" << endl;
        cout << "  'm' - Send to MATLAB" << endl;
        cout << "  's' - Save current detection" << endl;
        
        // Main capture loop
        while (true) {
            // Capture frame from camera
            cap >> frame;
            
            // Check if frame was captured successfully
            if (frame.empty()) {
                cerr << "Warning: Could not capture frame!" << endl;
                continue;
            }
            
            // Perform object detection
            if (!detectionNet.empty()) {
                performObjectDetection(detectionNet, frame, detections, currentDetectionMethod, detectionParams);
            }
            
            // Perform object recognition
            if (!detections.empty()) {
                performObjectRecognition(frame, detections, currentRecognitionMethod, recognitionParams);
            }
            
            // Draw detection results
            visualization = drawDetectionResults(frame, detections, currentDetectionMethod);
            
            // Display the visualization
            imshow("Advanced Object Detection and Recognition", visualization);
            
            // Handle keyboard input
            char key = waitKey(1) & 0xFF;
            
            if (key == 'q' || key == 27) { // 'q' or ESC to quit
                cout << "Quitting..." << endl;
                break;
            }
            else if (key >= '0' && key <= '9') { // Detection method selection
                currentDetectionMethod = static_cast<DetectionMethod>(key - '0');
                cout << "Selected detection method: " << getDetectionMethodName(currentDetectionMethod) << endl;
                
                // Reload model
                if (!loadDetectionModel(detectionNet, currentDetectionMethod)) {
                    cout << "Warning: Could not load detection model." << endl;
                }
            }
            else if (key >= 'a' && key <= 'j') { // Recognition method selection
                currentRecognitionMethod = static_cast<RecognitionMethod>(key - 'a');
                cout << "Selected recognition method: " << getRecognitionMethodName(currentRecognitionMethod) << endl;
            }
            else if (key == 'm') { // Send to MATLAB
                sendDetectionToMATLAB(matlabPtr, frame, detections, currentDetectionMethod, currentRecognitionMethod);
            }
            else if (key == 's') { // Save current detection
                string filename = "detection_" + getDetectionMethodName(currentDetectionMethod) + 
                                "_" + getRecognitionMethodName(currentRecognitionMethod) + ".jpg";
                imwrite(filename, visualization);
                cout << "Detection saved as: " << filename << endl;
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
 * g++ -std=c++17 camera_advanced_23.cpp -o camera_advanced_23 \
 *     `pkg-config --cflags --libs opencv4` \
 *     -I/Applications/MATLAB_R2023b.app/extern/include \
 *     -L/Applications/MATLAB_R2023b.app/bin/maci64 \
 *     -lMatlabDataArray -lMatlabEngine
 * 
 * @brief Usage:
 * 1. Make sure your camera is connected and working
 * 2. Run the executable: ./camera_advanced_23
 * 3. Use keyboard controls to switch between detection methods
 * 4. Use keyboard controls to switch between recognition methods
 * 5. Press 'm' to send data to MATLAB
 * 6. Press 's' to save current detection
 * 
 * @brief Learning Objectives:
 * - Understand advanced object detection techniques
 * - Learn deep learning-based detection
 * - Understand YOLO, SSD, and R-CNN models
 * - Learn feature-based recognition
 * - Understand SIFT, SURF, ORB, and other features
 * - Learn MATLAB integration for detection analysis
 * - Understand object classification and recognition
 */
