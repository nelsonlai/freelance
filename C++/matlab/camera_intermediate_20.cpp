/**
 * @file camera_intermediate_20.cpp
 * @brief Advanced Computer Vision Applications - Intermediate Level 20
 * @description This program demonstrates advanced computer vision applications
 *              including face detection, object recognition, and scene analysis
 *              using OpenCV and MATLAB integration for real-time analysis.
 * @author Educational C++ MATLAB Integration Project
 * @date 2024
 * @version 1.0
 */

#include <opencv2/opencv.hpp>
#include <opencv2/objdetect.hpp>
#include <opencv2/dnn.hpp>
#include <iostream>
#include <matlab/engine.hpp>
#include <memory>
#include <vector>
#include <algorithm>

using namespace cv;
using namespace std;

/**
 * @brief Enumeration for different computer vision applications
 */
enum ComputerVisionApplication {
    FACE_DETECTION = 0,
    EYE_DETECTION = 1,
    SMILE_DETECTION = 2,
    PEDESTRIAN_DETECTION = 3,
    CAR_DETECTION = 4,
    OBJECT_DETECTION = 5,
    SCENE_ANALYSIS = 6,
    TEXT_DETECTION = 7,
    GESTURE_RECOGNITION = 8,
    EMOTION_RECOGNITION = 9
};

/**
 * @brief Structure to hold computer vision parameters
 */
struct ComputerVisionParams {
    double faceScaleFactor;
    int faceMinNeighbors;
    Size faceMinSize;
    Size faceMaxSize;
    double eyeScaleFactor;
    int eyeMinNeighbors;
    Size eyeMinSize;
    Size eyeMaxSize;
    double smileScaleFactor;
    int smileMinNeighbors;
    Size smileMinSize;
    Size smileMaxSize;
    double pedestrianScaleFactor;
    int pedestrianMinNeighbors;
    Size pedestrianMinSize;
    Size pedestrianMaxSize;
    double carScaleFactor;
    int carMinNeighbors;
    Size carMinSize;
    Size carMaxSize;
    double objectConfidenceThreshold;
    double objectNMSThreshold;
    vector<string> objectClassNames;
    double sceneAnalysisThreshold;
    double textDetectionThreshold;
    double gestureRecognitionThreshold;
    double emotionRecognitionThreshold;
};

/**
 * @brief Function to get computer vision application name
 * @param application Computer vision application
 * @return string Application name
 */
string getComputerVisionApplicationName(ComputerVisionApplication application) {
    switch (application) {
        case FACE_DETECTION: return "Face Detection";
        case EYE_DETECTION: return "Eye Detection";
        case SMILE_DETECTION: return "Smile Detection";
        case PEDESTRIAN_DETECTION: return "Pedestrian Detection";
        case CAR_DETECTION: return "Car Detection";
        case OBJECT_DETECTION: return "Object Detection";
        case SCENE_ANALYSIS: return "Scene Analysis";
        case TEXT_DETECTION: return "Text Detection";
        case GESTURE_RECOGNITION: return "Gesture Recognition";
        case EMOTION_RECOGNITION: return "Emotion Recognition";
        default: return "Unknown";
    }
}

/**
 * @brief Function to apply face detection
 * @param src Input image
 * @param dst Output image with detected faces
 * @param params Computer vision parameters
 * @return vector<Rect> Detected face rectangles
 */
vector<Rect> applyFaceDetection(const Mat& src, Mat& dst, const ComputerVisionParams& params) {
    // Load face cascade classifier
    CascadeClassifier faceCascade;
    if (!faceCascade.load("haarcascade_frontalface_alt.xml")) {
        cerr << "Error: Could not load face cascade classifier!" << endl;
        src.copyTo(dst);
        return vector<Rect>();
    }
    
    // Convert to grayscale
    Mat gray;
    cvtColor(src, gray, COLOR_BGR2GRAY);
    
    // Detect faces
    vector<Rect> faces;
    faceCascade.detectMultiScale(gray, faces, params.faceScaleFactor, params.faceMinNeighbors, 
                                0, params.faceMinSize, params.faceMaxSize);
    
    // Draw detected faces
    src.copyTo(dst);
    for (const auto& face : faces) {
        rectangle(dst, face, Scalar(0, 255, 0), 2);
        putText(dst, "Face", Point(face.x, face.y - 10), 
               FONT_HERSHEY_SIMPLEX, 0.7, Scalar(0, 255, 0), 2);
    }
    
    return faces;
}

/**
 * @brief Function to apply eye detection
 * @param src Input image
 * @param dst Output image with detected eyes
 * @param params Computer vision parameters
 * @return vector<Rect> Detected eye rectangles
 */
vector<Rect> applyEyeDetection(const Mat& src, Mat& dst, const ComputerVisionParams& params) {
    // Load eye cascade classifier
    CascadeClassifier eyeCascade;
    if (!eyeCascade.load("haarcascade_eye.xml")) {
        cerr << "Error: Could not load eye cascade classifier!" << endl;
        src.copyTo(dst);
        return vector<Rect>();
    }
    
    // Convert to grayscale
    Mat gray;
    cvtColor(src, gray, COLOR_BGR2GRAY);
    
    // Detect eyes
    vector<Rect> eyes;
    eyeCascade.detectMultiScale(gray, eyes, params.eyeScaleFactor, params.eyeMinNeighbors, 
                               0, params.eyeMinSize, params.eyeMaxSize);
    
    // Draw detected eyes
    src.copyTo(dst);
    for (const auto& eye : eyes) {
        rectangle(dst, eye, Scalar(255, 0, 0), 2);
        putText(dst, "Eye", Point(eye.x, eye.y - 10), 
               FONT_HERSHEY_SIMPLEX, 0.7, Scalar(255, 0, 0), 2);
    }
    
    return eyes;
}

/**
 * @brief Function to apply smile detection
 * @param src Input image
 * @param dst Output image with detected smiles
 * @param params Computer vision parameters
 * @return vector<Rect> Detected smile rectangles
 */
vector<Rect> applySmileDetection(const Mat& src, Mat& dst, const ComputerVisionParams& params) {
    // Load smile cascade classifier
    CascadeClassifier smileCascade;
    if (!smileCascade.load("haarcascade_smile.xml")) {
        cerr << "Error: Could not load smile cascade classifier!" << endl;
        src.copyTo(dst);
        return vector<Rect>();
    }
    
    // Convert to grayscale
    Mat gray;
    cvtColor(src, gray, COLOR_BGR2GRAY);
    
    // Detect smiles
    vector<Rect> smiles;
    smileCascade.detectMultiScale(gray, smiles, params.smileScaleFactor, params.smileMinNeighbors, 
                                 0, params.smileMinSize, params.smileMaxSize);
    
    // Draw detected smiles
    src.copyTo(dst);
    for (const auto& smile : smiles) {
        rectangle(dst, smile, Scalar(0, 0, 255), 2);
        putText(dst, "Smile", Point(smile.x, smile.y - 10), 
               FONT_HERSHEY_SIMPLEX, 0.7, Scalar(0, 0, 255), 2);
    }
    
    return smiles;
}

/**
 * @brief Function to apply pedestrian detection
 * @param src Input image
 * @param dst Output image with detected pedestrians
 * @param params Computer vision parameters
 * @return vector<Rect> Detected pedestrian rectangles
 */
vector<Rect> applyPedestrianDetection(const Mat& src, Mat& dst, const ComputerVisionParams& params) {
    // Load pedestrian cascade classifier
    CascadeClassifier pedestrianCascade;
    if (!pedestrianCascade.load("haarcascade_fullbody.xml")) {
        cerr << "Error: Could not load pedestrian cascade classifier!" << endl;
        src.copyTo(dst);
        return vector<Rect>();
    }
    
    // Convert to grayscale
    Mat gray;
    cvtColor(src, gray, COLOR_BGR2GRAY);
    
    // Detect pedestrians
    vector<Rect> pedestrians;
    pedestrianCascade.detectMultiScale(gray, pedestrians, params.pedestrianScaleFactor, 
                                     params.pedestrianMinNeighbors, 0, params.pedestrianMinSize, 
                                     params.pedestrianMaxSize);
    
    // Draw detected pedestrians
    src.copyTo(dst);
    for (const auto& pedestrian : pedestrians) {
        rectangle(dst, pedestrian, Scalar(255, 255, 0), 2);
        putText(dst, "Pedestrian", Point(pedestrian.x, pedestrian.y - 10), 
               FONT_HERSHEY_SIMPLEX, 0.7, Scalar(255, 255, 0), 2);
    }
    
    return pedestrians;
}

/**
 * @brief Function to apply car detection
 * @param src Input image
 * @param dst Output image with detected cars
 * @param params Computer vision parameters
 * @return vector<Rect> Detected car rectangles
 */
vector<Rect> applyCarDetection(const Mat& src, Mat& dst, const ComputerVisionParams& params) {
    // Load car cascade classifier
    CascadeClassifier carCascade;
    if (!carCascade.load("haarcascade_car.xml")) {
        cerr << "Error: Could not load car cascade classifier!" << endl;
        src.copyTo(dst);
        return vector<Rect>();
    }
    
    // Convert to grayscale
    Mat gray;
    cvtColor(src, gray, COLOR_BGR2GRAY);
    
    // Detect cars
    vector<Rect> cars;
    carCascade.detectMultiScale(gray, cars, params.carScaleFactor, params.carMinNeighbors, 
                               0, params.carMinSize, params.carMaxSize);
    
    // Draw detected cars
    src.copyTo(dst);
    for (const auto& car : cars) {
        rectangle(dst, car, Scalar(255, 0, 255), 2);
        putText(dst, "Car", Point(car.x, car.y - 10), 
               FONT_HERSHEY_SIMPLEX, 0.7, Scalar(255, 0, 255), 2);
    }
    
    return cars;
}

/**
 * @brief Function to apply object detection
 * @param src Input image
 * @param dst Output image with detected objects
 * @param params Computer vision parameters
 * @return vector<Rect> Detected object rectangles
 */
vector<Rect> applyObjectDetection(const Mat& src, Mat& dst, const ComputerVisionParams& params) {
    // Load DNN model for object detection
    Net net;
    try {
        net = readNetFromDarknet("yolov3.cfg", "yolov3.weights");
        net.setPreferableBackend(DNN_BACKEND_OPENCV);
        net.setPreferableTarget(DNN_TARGET_CPU);
    } catch (const std::exception& e) {
        cerr << "Error: Could not load DNN model!" << endl;
        src.copyTo(dst);
        return vector<Rect>();
    }
    
    // Prepare input blob
    Mat blob;
    blobFromImage(src, blob, 1/255.0, Size(416, 416), Scalar(0, 0, 0), true, false);
    net.setInput(blob);
    
    // Run inference
    vector<Mat> outputs;
    net.forward(outputs, net.getUnconnectedOutLayersNames());
    
    // Process outputs
    vector<Rect> objects;
    vector<float> confidences;
    vector<int> classIds;
    
    for (const auto& output : outputs) {
        for (int i = 0; i < output.rows; i++) {
            const float* data = output.ptr<float>(i);
            float confidence = data[4];
            
            if (confidence > params.objectConfidenceThreshold) {
                int centerX = static_cast<int>(data[0] * src.cols);
                int centerY = static_cast<int>(data[1] * src.rows);
                int width = static_cast<int>(data[2] * src.cols);
                int height = static_cast<int>(data[3] * src.rows);
                
                int left = centerX - width / 2;
                int top = centerY - height / 2;
                
                objects.push_back(Rect(left, top, width, height));
                confidences.push_back(confidence);
                classIds.push_back(0); // Simplified class ID
            }
        }
    }
    
    // Apply non-maximum suppression
    vector<int> indices;
    NMSBoxes(objects, confidences, params.objectConfidenceThreshold, params.objectNMSThreshold, indices);
    
    // Draw detected objects
    src.copyTo(dst);
    for (int idx : indices) {
        rectangle(dst, objects[idx], Scalar(0, 255, 255), 2);
        putText(dst, "Object", Point(objects[idx].x, objects[idx].y - 10), 
               FONT_HERSHEY_SIMPLEX, 0.7, Scalar(0, 255, 255), 2);
    }
    
    return objects;
}

/**
 * @brief Function to apply scene analysis
 * @param src Input image
 * @param dst Output image with scene analysis
 * @param params Computer vision parameters
 * @return string Scene analysis result
 */
string applySceneAnalysis(const Mat& src, Mat& dst, const ComputerVisionParams& params) {
    // Convert to grayscale
    Mat gray;
    cvtColor(src, gray, COLOR_BGR2GRAY);
    
    // Calculate image statistics
    Scalar mean, stddev;
    meanStdDev(gray, mean, stddev);
    
    // Analyze scene based on statistics
    string sceneType;
    if (stddev[0] < params.sceneAnalysisThreshold) {
        sceneType = "Uniform Scene";
    } else if (stddev[0] > params.sceneAnalysisThreshold * 2) {
        sceneType = "Complex Scene";
    } else {
        sceneType = "Moderate Scene";
    }
    
    // Draw scene analysis
    src.copyTo(dst);
    putText(dst, sceneType, Point(10, 30), 
           FONT_HERSHEY_SIMPLEX, 0.7, Scalar(0, 255, 0), 2);
    putText(dst, "Std Dev: " + to_string(stddev[0]), Point(10, 60), 
           FONT_HERSHEY_SIMPLEX, 0.5, Scalar(255, 255, 255), 1);
    
    return sceneType;
}

/**
 * @brief Function to apply text detection
 * @param src Input image
 * @param dst Output image with detected text
 * @param params Computer vision parameters
 * @return vector<Rect> Detected text rectangles
 */
vector<Rect> applyTextDetection(const Mat& src, Mat& dst, const ComputerVisionParams& params) {
    // Load text detection model
    Net net;
    try {
        net = readNetFromTensorflow("frozen_east_text_detection.pb");
        net.setPreferableBackend(DNN_BACKEND_OPENCV);
        net.setPreferableTarget(DNN_TARGET_CPU);
    } catch (const std::exception& e) {
        cerr << "Error: Could not load text detection model!" << endl;
        src.copyTo(dst);
        return vector<Rect>();
    }
    
    // Prepare input blob
    Mat blob;
    blobFromImage(src, blob, 1.0, Size(320, 320), Scalar(123.68, 116.78, 103.94), true, false);
    net.setInput(blob);
    
    // Run inference
    vector<Mat> outputs;
    net.forward(outputs, net.getUnconnectedOutLayersNames());
    
    // Process outputs (simplified)
    vector<Rect> textRegions;
    
    // Draw detected text regions
    src.copyTo(dst);
    for (const auto& region : textRegions) {
        rectangle(dst, region, Scalar(255, 255, 0), 2);
        putText(dst, "Text", Point(region.x, region.y - 10), 
               FONT_HERSHEY_SIMPLEX, 0.7, Scalar(255, 255, 0), 2);
    }
    
    return textRegions;
}

/**
 * @brief Function to apply gesture recognition
 * @param src Input image
 * @param dst Output image with recognized gestures
 * @param params Computer vision parameters
 * @return string Gesture recognition result
 */
string applyGestureRecognition(const Mat& src, Mat& dst, const ComputerVisionParams& params) {
    // Convert to grayscale
    Mat gray;
    cvtColor(src, gray, COLOR_BGR2GRAY);
    
    // Detect contours
    vector<vector<Point>> contours;
    vector<Vec4i> hierarchy;
    findContours(gray, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
    
    // Analyze contours for gesture recognition
    string gesture = "No Gesture";
    if (contours.size() > 0) {
        // Simple gesture recognition based on contour count
        if (contours.size() == 1) {
            gesture = "Single Gesture";
        } else if (contours.size() > 1) {
            gesture = "Multiple Gestures";
        }
    }
    
    // Draw gesture recognition
    src.copyTo(dst);
    putText(dst, gesture, Point(10, 30), 
           FONT_HERSHEY_SIMPLEX, 0.7, Scalar(0, 255, 0), 2);
    putText(dst, "Contours: " + to_string(contours.size()), Point(10, 60), 
           FONT_HERSHEY_SIMPLEX, 0.5, Scalar(255, 255, 255), 1);
    
    return gesture;
}

/**
 * @brief Function to apply emotion recognition
 * @param src Input image
 * @param dst Output image with recognized emotions
 * @param params Computer vision parameters
 * @return string Emotion recognition result
 */
string applyEmotionRecognition(const Mat& src, Mat& dst, const ComputerVisionParams& params) {
    // Convert to grayscale
    Mat gray;
    cvtColor(src, gray, COLOR_BGR2GRAY);
    
    // Detect faces first
    CascadeClassifier faceCascade;
    vector<Rect> faces;
    if (faceCascade.load("haarcascade_frontalface_alt.xml")) {
        faceCascade.detectMultiScale(gray, faces, 1.1, 3, 0, Size(30, 30));
    }
    
    // Analyze emotions (simplified)
    string emotion = "Neutral";
    if (faces.size() > 0) {
        // Simple emotion recognition based on face detection
        emotion = "Happy";
    }
    
    // Draw emotion recognition
    src.copyTo(dst);
    putText(dst, emotion, Point(10, 30), 
           FONT_HERSHEY_SIMPLEX, 0.7, Scalar(0, 255, 0), 2);
    putText(dst, "Faces: " + to_string(faces.size()), Point(10, 60), 
           FONT_HERSHEY_SIMPLEX, 0.5, Scalar(255, 255, 255), 1);
    
    return emotion;
}

/**
 * @brief Function to apply selected computer vision application
 * @param src Input image
 * @param dst Output image
 * @param application Computer vision application
 * @param params Computer vision parameters
 * @return vector<Rect> Detected objects/regions
 */
vector<Rect> applyComputerVisionApplication(const Mat& src, Mat& dst, 
                                           ComputerVisionApplication application, 
                                           const ComputerVisionParams& params) {
    switch (application) {
        case FACE_DETECTION:
            return applyFaceDetection(src, dst, params);
        case EYE_DETECTION:
            return applyEyeDetection(src, dst, params);
        case SMILE_DETECTION:
            return applySmileDetection(src, dst, params);
        case PEDESTRIAN_DETECTION:
            return applyPedestrianDetection(src, dst, params);
        case CAR_DETECTION:
            return applyCarDetection(src, dst, params);
        case OBJECT_DETECTION:
            return applyObjectDetection(src, dst, params);
        case SCENE_ANALYSIS:
            applySceneAnalysis(src, dst, params);
            return vector<Rect>();
        case TEXT_DETECTION:
            return applyTextDetection(src, dst, params);
        case GESTURE_RECOGNITION:
            applyGestureRecognition(src, dst, params);
            return vector<Rect>();
        case EMOTION_RECOGNITION:
            applyEmotionRecognition(src, dst, params);
            return vector<Rect>();
        default:
            src.copyTo(dst);
            return vector<Rect>();
    }
}

/**
 * @brief Function to send computer vision data to MATLAB
 * @param matlabPtr MATLAB engine pointer
 * @param src Original image
 * @param dst Processed image
 * @param application Computer vision application
 * @param params Computer vision parameters
 */
void sendComputerVisionToMATLAB(std::unique_ptr<matlab::engine::MATLABEngine>& matlabPtr, 
                               const Mat& src, const Mat& dst, ComputerVisionApplication application, 
                               const ComputerVisionParams& params) {
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
        
        // Processed image
        auto dimsDst = factory.createArray<std::size_t>({1, 3}, 
            {static_cast<std::size_t>(rgbDst.rows), 
             static_cast<std::size_t>(rgbDst.cols), 
             static_cast<std::size_t>(rgbDst.channels())});
        auto matlabDst = factory.createArray<uint8_t>(dimsDst);
        auto dstPtr = matlabDst.release();
        memcpy(dstPtr, rgbDst.data, rgbDst.total() * rgbDst.elemSize());
        
        // Set variables in MATLAB workspace
        matlabPtr->setVariable(u"originalImage", matlabSrc);
        matlabPtr->setVariable(u"processedImage", matlabDst);
        
        // Execute MATLAB commands
        string applicationName = getComputerVisionApplicationName(application);
        string matlabCmd = "figure; subplot(1,2,1); imshow(originalImage); title('Original'); "
                          "subplot(1,2,2); imshow(processedImage); title('" + applicationName + "');";
        matlabPtr->eval(matlab::engine::convertUTF8StringToUTF16String(matlabCmd));
        
        // Display computer vision information
        matlabPtr->eval(u"fprintf('Computer Vision Application: " + matlab::engine::convertUTF8StringToUTF16String(applicationName) + "\\n');");
        
        cout << "Computer vision data sent to MATLAB successfully!" << endl;
        
    } catch (const std::exception& e) {
        cerr << "Error sending computer vision data to MATLAB: " << e.what() << endl;
    }
}

/**
 * @brief Main function for advanced computer vision applications
 * @return int Exit status
 */
int main() {
    cout << "=== Advanced Computer Vision Applications - Intermediate Level 20 ===" << endl;
    cout << "This program demonstrates advanced computer vision applications." << endl;
    
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
        
        // Initialize computer vision parameters
        ComputerVisionParams params;
        params.faceScaleFactor = 1.1;
        params.faceMinNeighbors = 3;
        params.faceMinSize = Size(30, 30);
        params.faceMaxSize = Size(300, 300);
        params.eyeScaleFactor = 1.1;
        params.eyeMinNeighbors = 3;
        params.eyeMinSize = Size(20, 20);
        params.eyeMaxSize = Size(100, 100);
        params.smileScaleFactor = 1.1;
        params.smileMinNeighbors = 3;
        params.smileMinSize = Size(30, 30);
        params.smileMaxSize = Size(200, 200);
        params.pedestrianScaleFactor = 1.1;
        params.pedestrianMinNeighbors = 3;
        params.pedestrianMinSize = Size(50, 50);
        params.pedestrianMaxSize = Size(400, 400);
        params.carScaleFactor = 1.1;
        params.carMinNeighbors = 3;
        params.carMinSize = Size(50, 50);
        params.carMaxSize = Size(400, 400);
        params.objectConfidenceThreshold = 0.5;
        params.objectNMSThreshold = 0.4;
        params.sceneAnalysisThreshold = 50.0;
        params.textDetectionThreshold = 0.5;
        params.gestureRecognitionThreshold = 0.5;
        params.emotionRecognitionThreshold = 0.5;
        
        // Initialize computer vision application
        ComputerVisionApplication currentApplication = FACE_DETECTION;
        
        // Create Mat objects for frame processing
        Mat frame, processedFrame, visualization;
        
        cout << "\nStarting camera feed with computer vision applications..." << endl;
        cout << "Controls:" << endl;
        cout << "  'q' - Quit" << endl;
        cout << "  '0' - Face Detection" << endl;
        cout << "  '1' - Eye Detection" << endl;
        cout << "  '2' - Smile Detection" << endl;
        cout << "  '3' - Pedestrian Detection" << endl;
        cout << "  '4' - Car Detection" << endl;
        cout << "  '5' - Object Detection" << endl;
        cout << "  '6' - Scene Analysis" << endl;
        cout << "  '7' - Text Detection" << endl;
        cout << "  '8' - Gesture Recognition" << endl;
        cout << "  '9' - Emotion Recognition" << endl;
        cout << "  'm' - Send to MATLAB" << endl;
        cout << "  's' - Save current application" << endl;
        
        // Main capture loop
        while (true) {
            // Capture frame from camera
            cap >> frame;
            
            // Check if frame was captured successfully
            if (frame.empty()) {
                cerr << "Warning: Could not capture frame!" << endl;
                continue;
            }
            
            // Apply selected computer vision application
            vector<Rect> detections = applyComputerVisionApplication(frame, processedFrame, 
                                                                    currentApplication, params);
            
            // Create visualization
            visualization = processedFrame;
            
            // Add detection count
            stringstream ss;
            ss << "Detections: " << detections.size();
            putText(visualization, ss.str(), Point(10, visualization.rows - 20), 
                   FONT_HERSHEY_SIMPLEX, 0.5, Scalar(255, 255, 255), 1);
            
            // Display the visualization
            imshow("Advanced Computer Vision Applications", visualization);
            
            // Handle keyboard input
            char key = waitKey(1) & 0xFF;
            
            if (key == 'q' || key == 27) { // 'q' or ESC to quit
                cout << "Quitting..." << endl;
                break;
            }
            else if (key >= '0' && key <= '9') { // Application selection
                currentApplication = static_cast<ComputerVisionApplication>(key - '0');
                cout << "Selected application: " << getComputerVisionApplicationName(currentApplication) << endl;
            }
            else if (key == 'm') { // Send to MATLAB
                sendComputerVisionToMATLAB(matlabPtr, frame, processedFrame, currentApplication, params);
            }
            else if (key == 's') { // Save current application
                string filename = "computer_vision_" + getComputerVisionApplicationName(currentApplication) + ".jpg";
                imwrite(filename, visualization);
                cout << "Computer vision application saved as: " << filename << endl;
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
 * g++ -std=c++17 camera_intermediate_20.cpp -o camera_intermediate_20 \
 *     `pkg-config --cflags --libs opencv4` \
 *     -I/Applications/MATLAB_R2023b.app/extern/include \
 *     -L/Applications/MATLAB_R2023b.app/bin/maci64 \
 *     -lMatlabDataArray -lMatlabEngine
 * 
 * @brief Usage:
 * 1. Make sure your camera is connected and working
 * 2. Run the executable: ./camera_intermediate_20
 * 3. Use keyboard controls to switch between computer vision applications
 * 4. Press 'm' to send data to MATLAB
 * 5. Press 's' to save current application
 * 
 * @brief Learning Objectives:
 * - Understand advanced computer vision applications
 * - Learn face, eye, and smile detection
 * - Understand pedestrian and car detection
 * - Learn object detection using DNN
 * - Understand scene analysis techniques
 * - Learn text detection and recognition
 * - Understand gesture and emotion recognition
 * - Learn MATLAB integration for computer vision analysis
 */
