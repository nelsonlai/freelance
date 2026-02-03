/**
 * @file camera_advanced_21.cpp
 * @brief Deep Learning Object Detection - Advanced Level 21
 * @description This program demonstrates deep learning-based object detection
 *              using YOLO, SSD, and other state-of-the-art models with OpenCV
 *              and MATLAB integration for real-time analysis.
 * @author Educational C++ MATLAB Integration Project
 * @date 2024
 * @version 1.0
 */

#include <opencv2/opencv.hpp>
#include <opencv2/dnn.hpp>
#include <iostream>
#include <matlab/engine.hpp>
#include <memory>
#include <vector>
#include <algorithm>
#include <fstream>

using namespace cv;
using namespace std;

/**
 * @brief Structure to hold detection result
 */
struct Detection {
    int classId;
    float confidence;
    Rect boundingBox;
    string className;
};

/**
 * @brief Enumeration for different deep learning models
 */
enum DeepLearningModel {
    YOLO_V3 = 0,
    YOLO_V4 = 1,
    YOLO_V5 = 2,
    SSD_MOBILENET = 3,
    SSD_INCEPTION = 4,
    RCNN = 5,
    FAST_RCNN = 6,
    FASTER_RCNN = 7,
    MASK_RCNN = 8,
    RETINANET = 9
};

/**
 * @brief Structure to hold deep learning parameters
 */
struct DeepLearningParams {
    float confidenceThreshold;
    float nmsThreshold;
    int inputWidth;
    int inputHeight;
    float scaleFactor;
    Scalar mean;
    bool swapRB;
    bool crop;
    vector<string> classNames;
    string modelPath;
    string configPath;
    string weightsPath;
};

/**
 * @brief Function to get deep learning model name
 * @param model Deep learning model
 * @return string Model name
 */
string getDeepLearningModelName(DeepLearningModel model) {
    switch (model) {
        case YOLO_V3: return "YOLO v3";
        case YOLO_V4: return "YOLO v4";
        case YOLO_V5: return "YOLO v5";
        case SSD_MOBILENET: return "SSD MobileNet";
        case SSD_INCEPTION: return "SSD Inception";
        case RCNN: return "R-CNN";
        case FAST_RCNN: return "Fast R-CNN";
        case FASTER_RCNN: return "Faster R-CNN";
        case MASK_RCNN: return "Mask R-CNN";
        case RETINANET: return "RetinaNet";
        default: return "Unknown";
    }
}

/**
 * @brief Function to load class names
 * @param classNamesFile Path to class names file
 * @return vector<string> Class names
 */
vector<string> loadClassNames(const string& classNamesFile) {
    vector<string> classNames;
    ifstream file(classNamesFile);
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            classNames.push_back(line);
        }
        file.close();
    } else {
        // Default COCO class names
        classNames = {"person", "bicycle", "car", "motorcycle", "airplane", "bus", "train", "truck", "boat",
                     "traffic light", "fire hydrant", "stop sign", "parking meter", "bench", "bird", "cat",
                     "dog", "horse", "sheep", "cow", "elephant", "bear", "zebra", "giraffe", "backpack",
                     "umbrella", "handbag", "tie", "suitcase", "frisbee", "skis", "snowboard", "sports ball",
                     "kite", "baseball bat", "baseball glove", "skateboard", "surfboard", "tennis racket",
                     "bottle", "wine glass", "cup", "fork", "knife", "spoon", "bowl", "banana", "apple",
                     "sandwich", "orange", "broccoli", "carrot", "hot dog", "pizza", "donut", "cake",
                     "chair", "couch", "potted plant", "bed", "dining table", "toilet", "tv", "laptop",
                     "mouse", "remote", "keyboard", "cell phone", "microwave", "oven", "toaster", "sink",
                     "refrigerator", "book", "clock", "vase", "scissors", "teddy bear", "hair drier", "toothbrush"};
    }
    return classNames;
}

/**
 * @brief Function to create YOLO model
 * @param params Deep learning parameters
 * @return Net YOLO model
 */
Net createYOLOModel(const DeepLearningParams& params) {
    Net net;
    try {
        net = readNetFromDarknet(params.configPath, params.weightsPath);
        net.setPreferableBackend(DNN_BACKEND_OPENCV);
        net.setPreferableTarget(DNN_TARGET_CPU);
    } catch (const std::exception& e) {
        cerr << "Error loading YOLO model: " << e.what() << endl;
    }
    return net;
}

/**
 * @brief Function to create SSD model
 * @param params Deep learning parameters
 * @return Net SSD model
 */
Net createSSDModel(const DeepLearningParams& params) {
    Net net;
    try {
        net = readNetFromTensorflow(params.weightsPath, params.configPath);
        net.setPreferableBackend(DNN_BACKEND_OPENCV);
        net.setPreferableTarget(DNN_TARGET_CPU);
    } catch (const std::exception& e) {
        cerr << "Error loading SSD model: " << e.what() << endl;
    }
    return net;
}

/**
 * @brief Function to create deep learning model
 * @param model Deep learning model type
 * @param params Deep learning parameters
 * @return Net Deep learning model
 */
Net createDeepLearningModel(DeepLearningModel model, const DeepLearningParams& params) {
    switch (model) {
        case YOLO_V3:
        case YOLO_V4:
        case YOLO_V5:
            return createYOLOModel(params);
        case SSD_MOBILENET:
        case SSD_INCEPTION:
            return createSSDModel(params);
        default:
            return Net();
    }
}

/**
 * @brief Function to preprocess image for deep learning
 * @param src Input image
 * @param blob Output blob
 * @param params Deep learning parameters
 */
void preprocessImage(const Mat& src, Mat& blob, const DeepLearningParams& params) {
    blobFromImage(src, blob, params.scaleFactor, Size(params.inputWidth, params.inputHeight), 
                 params.mean, params.swapRB, params.crop);
}

/**
 * @brief Function to postprocess YOLO outputs
 * @param outputs Model outputs
 * @param src Input image
 * @param detections Output detections
 * @param params Deep learning parameters
 */
void postprocessYOLO(const vector<Mat>& outputs, const Mat& src, vector<Detection>& detections, 
                    const DeepLearningParams& params) {
    detections.clear();
    
    for (const auto& output : outputs) {
        for (int i = 0; i < output.rows; i++) {
            const float* data = output.ptr<float>(i);
            float confidence = data[4];
            
            if (confidence > params.confidenceThreshold) {
                // Find class with highest confidence
                int classId = 0;
                float maxClassConfidence = 0;
                for (int j = 5; j < output.cols; j++) {
                    float classConfidence = data[j];
                    if (classConfidence > maxClassConfidence) {
                        maxClassConfidence = classConfidence;
                        classId = j - 5;
                    }
                }
                
                float finalConfidence = confidence * maxClassConfidence;
                if (finalConfidence > params.confidenceThreshold) {
                    // Calculate bounding box
                    int centerX = static_cast<int>(data[0] * src.cols);
                    int centerY = static_cast<int>(data[1] * src.rows);
                    int width = static_cast<int>(data[2] * src.cols);
                    int height = static_cast<int>(data[3] * src.rows);
                    
                    int left = centerX - width / 2;
                    int top = centerY - height / 2;
                    
                    Detection detection;
                    detection.classId = classId;
                    detection.confidence = finalConfidence;
                    detection.boundingBox = Rect(left, top, width, height);
                    detection.className = (classId < params.classNames.size()) ? 
                                         params.classNames[classId] : "Unknown";
                    
                    detections.push_back(detection);
                }
            }
        }
    }
}

/**
 * @brief Function to postprocess SSD outputs
 * @param outputs Model outputs
 * @param src Input image
 * @param detections Output detections
 * @param params Deep learning parameters
 */
void postprocessSSD(const vector<Mat>& outputs, const Mat& src, vector<Detection>& detections, 
                   const DeepLearningParams& params) {
    detections.clear();
    
    Mat detectionMat = outputs[0];
    for (int i = 0; i < detectionMat.rows; i++) {
        const float* data = detectionMat.ptr<float>(i);
        float confidence = data[2];
        
        if (confidence > params.confidenceThreshold) {
            int classId = static_cast<int>(data[1]);
            
            // Calculate bounding box
            int left = static_cast<int>(data[3] * src.cols);
            int top = static_cast<int>(data[4] * src.rows);
            int right = static_cast<int>(data[5] * src.cols);
            int bottom = static_cast<int>(data[6] * src.rows);
            
            Detection detection;
            detection.classId = classId;
            detection.confidence = confidence;
            detection.boundingBox = Rect(left, top, right - left, bottom - top);
            detection.className = (classId < params.classNames.size()) ? 
                                 params.classNames[classId] : "Unknown";
            
            detections.push_back(detection);
        }
    }
}

/**
 * @brief Function to apply non-maximum suppression
 * @param detections Input detections
 * @param params Deep learning parameters
 * @return vector<Detection> Filtered detections
 */
vector<Detection> applyNMS(const vector<Detection>& detections, const DeepLearningParams& params) {
    vector<Detection> filteredDetections;
    
    // Extract bounding boxes and confidences
    vector<Rect> boxes;
    vector<float> confidences;
    vector<int> classIds;
    
    for (const auto& detection : detections) {
        boxes.push_back(detection.boundingBox);
        confidences.push_back(detection.confidence);
        classIds.push_back(detection.classId);
    }
    
    // Apply NMS
    vector<int> indices;
    NMSBoxes(boxes, confidences, params.confidenceThreshold, params.nmsThreshold, indices);
    
    // Create filtered detections
    for (int idx : indices) {
        filteredDetections.push_back(detections[idx]);
    }
    
    return filteredDetections;
}

/**
 * @brief Function to draw detections on image
 * @param src Input image
 * @param dst Output image with detections
 * @param detections Detected objects
 */
void drawDetections(const Mat& src, Mat& dst, const vector<Detection>& detections) {
    src.copyTo(dst);
    
    for (const auto& detection : detections) {
        // Draw bounding box
        rectangle(dst, detection.boundingBox, Scalar(0, 255, 0), 2);
        
        // Draw label
        string label = detection.className + ": " + to_string(detection.confidence);
        int baseline;
        Size textSize = getTextSize(label, FONT_HERSHEY_SIMPLEX, 0.5, 2, &baseline);
        
        Point labelPoint(detection.boundingBox.x, detection.boundingBox.y - 10);
        if (labelPoint.y < textSize.height) {
            labelPoint.y = detection.boundingBox.y + textSize.height;
        }
        
        rectangle(dst, Point(labelPoint.x, labelPoint.y - textSize.height - baseline),
                 Point(labelPoint.x + textSize.width, labelPoint.y + baseline),
                 Scalar(0, 255, 0), -1);
        
        putText(dst, label, labelPoint, FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0, 0, 0), 2);
    }
}

/**
 * @brief Function to apply deep learning object detection
 * @param src Input image
 * @param dst Output image with detections
 * @param model Deep learning model
 * @param net Neural network
 * @param params Deep learning parameters
 * @return vector<Detection> Detected objects
 */
vector<Detection> applyDeepLearningDetection(const Mat& src, Mat& dst, DeepLearningModel model, 
                                           Net& net, const DeepLearningParams& params) {
    vector<Detection> detections;
    
    if (net.empty()) {
        src.copyTo(dst);
        return detections;
    }
    
    // Preprocess image
    Mat blob;
    preprocessImage(src, blob, params);
    
    // Set input
    net.setInput(blob);
    
    // Run inference
    vector<Mat> outputs;
    net.forward(outputs, net.getUnconnectedOutLayersNames());
    
    // Postprocess outputs
    switch (model) {
        case YOLO_V3:
        case YOLO_V4:
        case YOLO_V5:
            postprocessYOLO(outputs, src, detections, params);
            break;
        case SSD_MOBILENET:
        case SSD_INCEPTION:
            postprocessSSD(outputs, src, detections, params);
            break;
        default:
            break;
    }
    
    // Apply NMS
    detections = applyNMS(detections, params);
    
    // Draw detections
    drawDetections(src, dst, detections);
    
    return detections;
}

/**
 * @brief Function to send deep learning data to MATLAB
 * @param matlabPtr MATLAB engine pointer
 * @param src Original image
 * @param dst Detected image
 * @param detections Detected objects
 * @param model Deep learning model
 * @param params Deep learning parameters
 */
void sendDeepLearningToMATLAB(std::unique_ptr<matlab::engine::MATLABEngine>& matlabPtr, 
                             const Mat& src, const Mat& dst, const vector<Detection>& detections,
                             DeepLearningModel model, const DeepLearningParams& params) {
    try {
        // Convert BGR to RGB for MATLAB
        Mat rgbSrc, rgbDst;
        cvtColor(src, rgbSrc, COLOR_BGR2RGB);
        cvtColor(dst, rgbDst, COLOR_BGR2RGB);
        
        // Create MATLAB arrays
        matlab::data::ArrayFactory factory;
        
        // Original image
        auto dimsSrc = factory.createArray<std::size_t>({1, 3}, 
            {static_cast<std::size_t>(rgbSrc.rows), 
             static_cast<std::size_t>(rgbSrc.cols), 
             static_cast<std::size_t>(rgbSrc.channels())});
        auto matlabSrc = factory.createArray<uint8_t>(dimsSrc);
        auto srcPtr = matlabSrc.release();
        memcpy(srcPtr, rgbSrc.data, rgbSrc.total() * rgbSrc.elemSize());
        
        // Detected image
        auto dimsDst = factory.createArray<std::size_t>({1, 3}, 
            {static_cast<std::size_t>(rgbDst.rows), 
             static_cast<std::size_t>(rgbDst.cols), 
             static_cast<std::size_t>(rgbDst.channels())});
        auto matlabDst = factory.createArray<uint8_t>(dimsDst);
        auto dstPtr = matlabDst.release();
        memcpy(dstPtr, rgbDst.data, rgbDst.total() * rgbDst.elemSize());
        
        // Set variables in MATLAB workspace
        matlabPtr->setVariable(u"originalImage", matlabSrc);
        matlabPtr->setVariable(u"detectedImage", matlabDst);
        
        // Execute MATLAB commands
        string modelName = getDeepLearningModelName(model);
        string matlabCmd = "figure; subplot(1,2,1); imshow(originalImage); title('Original'); "
                          "subplot(1,2,2); imshow(detectedImage); title('" + modelName + " Detection');";
        matlabPtr->eval(matlab::engine::convertUTF8StringToUTF16String(matlabCmd));
        
        // Display detection information
        matlabPtr->eval(u"fprintf('Deep Learning Model: " + matlab::engine::convertUTF8StringToUTF16String(modelName) + "\\n');");
        matlabPtr->eval(u"fprintf('Number of detections: %d\\n', " + to_string(detections.size()) + u");");
        matlabPtr->eval(u"fprintf('Confidence threshold: %.2f\\n', " + to_string(params.confidenceThreshold) + u");");
        
        cout << "Deep learning data sent to MATLAB successfully!" << endl;
        
    } catch (const std::exception& e) {
        cerr << "Error sending deep learning data to MATLAB: " << e.what() << endl;
    }
}

/**
 * @brief Main function for deep learning object detection
 * @return int Exit status
 */
int main() {
    cout << "=== Deep Learning Object Detection - Advanced Level 21 ===" << endl;
    cout << "This program demonstrates deep learning-based object detection." << endl;
    
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
        
        // Initialize deep learning parameters
        DeepLearningParams params;
        params.confidenceThreshold = 0.5;
        params.nmsThreshold = 0.4;
        params.inputWidth = 416;
        params.inputHeight = 416;
        params.scaleFactor = 1.0/255.0;
        params.mean = Scalar(0, 0, 0);
        params.swapRB = true;
        params.crop = false;
        params.classNames = loadClassNames("coco.names");
        params.modelPath = "yolov3.weights";
        params.configPath = "yolov3.cfg";
        params.weightsPath = "yolov3.weights";
        
        // Initialize deep learning model
        DeepLearningModel currentModel = YOLO_V3;
        Net net = createDeepLearningModel(currentModel, params);
        
        // Create Mat objects for frame processing
        Mat frame, detectedFrame;
        vector<Detection> detections;
        
        cout << "\nStarting camera feed with deep learning object detection..." << endl;
        cout << "Controls:" << endl;
        cout << "  'q' - Quit" << endl;
        cout << "  '0' - YOLO v3" << endl;
        cout << "  '1' - YOLO v4" << endl;
        cout << "  '2' - YOLO v5" << endl;
        cout << "  '3' - SSD MobileNet" << endl;
        cout << "  '4' - SSD Inception" << endl;
        cout << "  '+' - Increase confidence threshold" << endl;
        cout << "  '-' - Decrease confidence threshold" << endl;
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
            
            // Apply deep learning object detection
            detections = applyDeepLearningDetection(frame, detectedFrame, currentModel, net, params);
            
            // Add detection count
            stringstream ss;
            ss << "Detections: " << detections.size();
            putText(detectedFrame, ss.str(), Point(10, 30), 
                   FONT_HERSHEY_SIMPLEX, 0.7, Scalar(0, 255, 0), 2);
            
            // Display the detection
            imshow("Deep Learning Object Detection", detectedFrame);
            
            // Handle keyboard input
            char key = waitKey(1) & 0xFF;
            
            if (key == 'q' || key == 27) { // 'q' or ESC to quit
                cout << "Quitting..." << endl;
                break;
            }
            else if (key >= '0' && key <= '4') { // Model selection
                currentModel = static_cast<DeepLearningModel>(key - '0');
                net = createDeepLearningModel(currentModel, params);
                cout << "Selected model: " << getDeepLearningModelName(currentModel) << endl;
            }
            else if (key == '+') { // Increase confidence threshold
                params.confidenceThreshold = min(1.0f, params.confidenceThreshold + 0.05f);
                cout << "Confidence threshold increased to: " << params.confidenceThreshold << endl;
            }
            else if (key == '-') { // Decrease confidence threshold
                params.confidenceThreshold = max(0.1f, params.confidenceThreshold - 0.05f);
                cout << "Confidence threshold decreased to: " << params.confidenceThreshold << endl;
            }
            else if (key == 'm') { // Send to MATLAB
                sendDeepLearningToMATLAB(matlabPtr, frame, detectedFrame, detections, currentModel, params);
            }
            else if (key == 's') { // Save current detection
                string filename = "deep_learning_" + getDeepLearningModelName(currentModel) + ".jpg";
                imwrite(filename, detectedFrame);
                cout << "Deep learning detection saved as: " << filename << endl;
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
 * g++ -std=c++17 camera_advanced_21.cpp -o camera_advanced_21 \
 *     `pkg-config --cflags --libs opencv4` \
 *     -I/Applications/MATLAB_R2023b.app/extern/include \
 *     -L/Applications/MATLAB_R2023b.app/bin/maci64 \
 *     -lMatlabDataArray -lMatlabEngine
 * 
 * @brief Usage:
 * 1. Make sure your camera is connected and working
 * 2. Run the executable: ./camera_advanced_21
 * 3. Use keyboard controls to switch between deep learning models
 * 4. Adjust confidence threshold with '+'/'-' keys
 * 5. Press 'm' to send data to MATLAB
 * 6. Press 's' to save current detection
 * 
 * @brief Learning Objectives:
 * - Understand deep learning object detection
 * - Learn YOLO, SSD, and other state-of-the-art models
 * - Understand model preprocessing and postprocessing
 * - Learn non-maximum suppression
 * - Understand confidence thresholds and NMS
 * - Learn MATLAB integration for deep learning analysis
 * - Understand real-time object detection
 * - Learn to choose appropriate deep learning models
 */
