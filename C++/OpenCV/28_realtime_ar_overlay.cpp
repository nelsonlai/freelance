// 28_realtime_ar_overlay.cpp
// Advanced Level - Real-time Augmented Reality Overlay
// This program demonstrates real-time AR applications including virtual object placement and tracking

#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/calib3d.hpp>
#include <opencv2/aruco.hpp>
#include <vector>

class AugmentedRealityDemo {
private:
    cv::VideoCapture cap;
    cv::Mat cameraMatrix, distCoeffs;
    cv::Mat frame, gray;
    
    // AR Components
    std::vector<cv::Point3f> virtual_cube;
    std::vector<cv::Point3f> virtual_pyramid;
    std::vector<cv::Point3f> virtual_plane;
    cv::Mat virtual_texture;
    
    // Tracking
    cv::Ptr<cv::aruco::Dictionary> aruco_dict;
    cv::Ptr<cv::aruco::DetectorParameters> aruco_params;
    
    // AR Modes
    enum ARMode {
        FACE_DETECTION,
        ARUCO_TRACKING,
        VIRTUAL_OBJECTS,
        TEXT_OVERLAY,
        VIRTUAL_PAINTING,
        DEPTH_ESTIMATION
    };
    ARMode current_mode;
    
    // Face detection
    cv::CascadeClassifier face_cascade;
    cv::CascadeClassifier eye_cascade;
    
public:
    AugmentedRealityDemo() : current_mode(FACE_DETECTION) {
        if (!cap.isOpened()) {
            std::cout << "Error: Could not open camera" << std::endl;
            exit(-1);
        }
        
        initializeVirtualObjects();
        initializeTracking();
        initializeCameraParameters();
        loadFaceCascades();
        
        std::cout << "Augmented Reality Demo initialized!" << std::endl;
    }
    
    void initializeVirtualObjects() {
        // Define virtual cube vertices
        virtual_cube = {
            cv::Point3f(-1, -1, 0),   // bottom-left-front
            cv::Point3f(1, -1, 0),    // bottom-right-front
            cv::Point3f(1, 1, 0),     // top-right-front
            cv::Point3f(-1, 1, 0),    // top-left-front
            cv::Point3f(-1, -1, 2),   // bottom-left-back
            cv::Point3f(1, -1, 2),    // bottom-right-back
            cv::Point3f(1, 1, 2),     // top-right-back
            cv::Point3f(-1, 1, 2)     // top-left-back
        };
        
        // Define virtual pyramid vertices
        virtual_pyramid = {
            cv::Point3f(-1, -1, 0),   // base corners
            cv::Point3f(1, -1, 0),
            cv::Point3f(1, 1, 0),
            cv::Point3f(-1, 1, 0),
            cv::Point3f(0, 0, 2)      // apex
        };
        
        // Define virtual plane
        virtual_plane = {
            cv::Point3f(-2, -1, 0),
            cv::Point3f(2, -1, 0),
            cv::Point3f(2, 1, 0),
            cv::Point3f(-2, 1, 0)
        };
        
        // Create virtual texture
        createVirtualTexture();
        
        std::cout << "Virtual objects initialized." << std::endl;
    }
    
    void createVirtualTexture() {
        virtual_texture = cv::Mat::zeros(200, 200, CV_8UC3);
        
        // Create a colorful pattern
        cv::rectangle(virtual_texture, cv::Point(0, 0), cv::Point(100, 100), cv::Scalar(255, 0, 0), -1);
        cv::rectangle(virtual_texture, cv::Point(100, 0), cv::Point(200, 100), cv::Scalar(0, 255, 0), -1);
        cv::rectangle(virtual_texture, cv::Point(0, 100), cv::Point(100, 200), cv::Scalar(0, 0, 255), -1);
        cv::rectangle(virtual_texture, cv::Point(100, 100), cv::Point(200, 200), cv::Scalar(255, 255, 0), -1);
        
        // Add some text
        cv::putText(virtual_texture, "AR", cv::Point(80, 120), 
                   cv::FONT_HERSHEY_SIMPLEX, 2, cv::Scalar(255, 255, 255), 3);
    }
    
    void initializeTracking() {
        // Initialize ArUco tracking
        aruco_dict = cv::aruco::getPredefinedDictionary(cv::aruco::DICT_6X6_250);
        aruco_params = cv::aruco::DetectorParameters::create();
        
        std::cout << "Tracking systems initialized." << std::endl;
    }
    
    void initializeCameraParameters() {
        // Estimate camera parameters (in real application, these would be calibrated)
        cap >> frame;
        if (frame.empty()) return;
        
        int width = frame.cols;
        int height = frame.rows;
        
        double fx = width * 0.8;
        double fy = height * 0.8;
        double cx = width / 2.0;
        double cy = height / 2.0;
        
        cameraMatrix = (cv::Mat_<double>(3, 3) <<
            fx, 0, cx,
            0, fy, cy,
            0, 0, 1);
        
        distCoeffs = cv::Mat::zeros(4, 1, CV_64F);
        
        std::cout << "Camera parameters estimated." << std::endl;
    }
    
    void loadFaceCascades() {
        // Try to load face cascade
        if (!face_cascade.load("haarcascade_frontalface_alt.xml")) {
            std::cout << "Warning: Could not load face cascade. Face detection will be disabled." << std::endl;
        }
        
        if (!eye_cascade.load("haarcascade_eye_tree_eyeglasses.xml")) {
            std::cout << "Warning: Could not load eye cascade. Eye detection will be disabled." << std::endl;
        }
    }
    
    void runAR() {
        std::cout << "=== Real-time Augmented Reality Overlay ===" << std::endl;
        std::cout << "Controls:" << std::endl;
        std::cout << "  '1' - Face Detection AR" << std::endl;
        std::cout << "  '2' - ArUco Marker Tracking" << std::endl;
        std::cout << "  '3' - Virtual Objects" << std::endl;
        std::cout << "  '4' - Text Overlay" << std::endl;
        std::cout << "  '5' - Virtual Painting" << std::endl;
        std::cout << "  '6' - Depth Estimation" << std::endl;
        std::cout << "  'q' - Quit" << std::endl;
        
        while (true) {
            cap >> frame;
            if (frame.empty()) break;
            
            cv::flip(frame, frame, 1);
            cv::cvtColor(frame, gray, cv::COLOR_BGR2GRAY);
            
            // Process based on current mode
            switch (current_mode) {
                case FACE_DETECTION:
                    processFaceDetectionAR();
                    break;
                case ARUCO_TRACKING:
                    processArUcoTracking();
                    break;
                case VIRTUAL_OBJECTS:
                    processVirtualObjects();
                    break;
                case TEXT_OVERLAY:
                    processTextOverlay();
                    break;
                case VIRTUAL_PAINTING:
                    processVirtualPainting();
                    break;
                case DEPTH_ESTIMATION:
                    processDepthEstimation();
                    break;
            }
            
            // Display mode information
            displayModeInfo();
            
            cv::imshow("Augmented Reality Demo", frame);
            
            char key = cv::waitKey(1) & 0xFF;
            if (key == 'q') break;
            if (key >= '1' && key <= '6') {
                current_mode = static_cast<ARMode>(key - '1');
                std::cout << "Switched to mode: " << getModeName(current_mode) << std::endl;
            }
        }
    }
    
private:
    void processFaceDetectionAR() {
        if (face_cascade.empty()) {
            cv::putText(frame, "Face cascade not loaded", cv::Point(10, 30), 
                       cv::FONT_HERSHEY_SIMPLEX, 1, cv::Scalar(0, 0, 255), 2);
            return;
        }
        
        std::vector<cv::Rect> faces;
        face_cascade.detectMultiScale(gray, faces, 1.1, 3, 0, cv::Size(30, 30));
        
        for (const auto& face : faces) {
            // Draw face rectangle
            cv::rectangle(frame, face, cv::Scalar(0, 255, 0), 2);
            
            // Add virtual sunglasses
            cv::Rect sunglasses(face.x + face.width/4, face.y + face.height/3, 
                               face.width/2, face.height/4);
            cv::rectangle(frame, sunglasses, cv::Scalar(0, 0, 0), -1);
            cv::rectangle(frame, sunglasses, cv::Scalar(255, 255, 255), 2);
            
            // Add virtual mustache
            cv::Rect mustache(face.x + face.width/3, face.y + 2*face.height/3, 
                             face.width/3, face.height/6);
            cv::rectangle(frame, mustache, cv::Scalar(0, 0, 0), -1);
            
            // Add virtual hat
            cv::Rect hat(face.x - face.width/4, face.y - face.height/4, 
                        face.width + face.width/2, face.height/2);
            cv::ellipse(frame, cv::Point(face.x + face.width/2, face.y + face.height/4), 
                       cv::Size(hat.width/2, hat.height/2), 0, 0, 180, cv::Scalar(255, 0, 0), -1);
            
            // Add face information
            std::string info = "Face detected!";
            cv::putText(frame, info, cv::Point(face.x, face.y - 10), 
                       cv::FONT_HERSHEY_SIMPLEX, 0.6, cv::Scalar(255, 255, 255), 2);
        }
        
        if (faces.empty()) {
            cv::putText(frame, "No face detected", cv::Point(10, 30), 
                       cv::FONT_HERSHEY_SIMPLEX, 1, cv::Scalar(0, 0, 255), 2);
        }
    }
    
    void processArUcoTracking() {
        std::vector<int> marker_ids;
        std::vector<std::vector<cv::Point2f>> marker_corners;
        
        cv::aruco::detectMarkers(gray, aruco_dict, marker_corners, marker_ids, aruco_params);
        
        if (marker_ids.size() > 0) {
            cv::aruco::drawDetectedMarkers(frame, marker_corners, marker_ids);
            
            // Estimate pose for each marker
            std::vector<cv::Vec3d> rvecs, tvecs;
            cv::aruco::estimatePoseSingleMarkers(marker_corners, 0.05, cameraMatrix, distCoeffs, rvecs, tvecs);
            
            for (size_t i = 0; i < marker_ids.size(); i++) {
                // Draw 3D axes
                cv::aruco::drawAxis(frame, cameraMatrix, distCoeffs, rvecs[i], tvecs[i], 0.1);
                
                // Draw virtual cube on marker
                drawVirtualCubeOnMarker(rvecs[i], tvecs[i]);
                
                // Add marker information
                cv::Point2f marker_center = (marker_corners[i][0] + marker_corners[i][2]) / 2;
                std::string marker_info = "Marker ID: " + std::to_string(marker_ids[i]);
                cv::putText(frame, marker_info, marker_center + cv::Point2f(0, -20), 
                           cv::FONT_HERSHEY_SIMPLEX, 0.7, cv::Scalar(0, 255, 255), 2);
            }
        } else {
            cv::putText(frame, "No ArUco markers detected", cv::Point(10, 30), 
                       cv::FONT_HERSHEY_SIMPLEX, 1, cv::Scalar(0, 0, 255), 2);
            cv::putText(frame, "Print ArUco markers from DICT_6X6_250", cv::Point(10, 70), 
                       cv::FONT_HERSHEY_SIMPLEX, 0.7, cv::Scalar(255, 255, 255), 2);
        }
    }
    
    void drawVirtualCubeOnMarker(const cv::Vec3d& rvec, const cv::Vec3d& tvec) {
        // Project virtual cube points to image
        std::vector<cv::Point2f> projected_points;
        cv::projectPoints(virtual_cube, rvec, tvec, cameraMatrix, distCoeffs, projected_points);
        
        // Draw cube wireframe
        cv::Scalar color(0, 255, 255);
        
        // Bottom face
        for (int i = 0; i < 4; i++) {
            cv::line(frame, projected_points[i], projected_points[(i + 1) % 4], color, 2);
        }
        
        // Top face
        for (int i = 4; i < 8; i++) {
            cv::line(frame, projected_points[i], projected_points[4 + (i - 4 + 1) % 4], color, 2);
        }
        
        // Vertical edges
        for (int i = 0; i < 4; i++) {
            cv::line(frame, projected_points[i], projected_points[i + 4], color, 2);
        }
        
        // Draw vertices
        for (const auto& point : projected_points) {
            cv::circle(frame, point, 3, color, -1);
        }
    }
    
    void processVirtualObjects() {
        // Create virtual objects at fixed positions (simulating plane detection)
        cv::Point2f center(frame.cols / 2, frame.rows / 2);
        
        // Draw virtual cube
        drawVirtualCubeAtPosition(center);
        
        // Draw virtual pyramid
        cv::Point2f pyramid_center(center.x - 100, center.y);
        drawVirtualPyramidAtPosition(pyramid_center);
        
        // Draw virtual plane with texture
        cv::Point2f plane_center(center.x + 100, center.y);
        drawVirtualPlaneAtPosition(plane_center);
        
        // Add interaction instructions
        cv::putText(frame, "Virtual Objects Mode", cv::Point(10, 30), 
                   cv::FONT_HERSHEY_SIMPLEX, 1, cv::Scalar(255, 255, 255), 2);
        cv::putText(frame, "Move camera to see 3D objects", cv::Point(10, 70), 
                   cv::FONT_HERSHEY_SIMPLEX, 0.7, cv::Scalar(255, 255, 255), 2);
    }
    
    void drawVirtualCubeAtPosition(const cv::Point2f& center) {
        // Simplified cube drawing at fixed position
        int size = 50;
        cv::Rect cube_rect(center.x - size/2, center.y - size/2, size, size);
        
        // Draw cube faces with different colors
        cv::rectangle(frame, cube_rect, cv::Scalar(255, 0, 0), -1);  // Front face
        
        // Draw side faces with perspective
        std::vector<cv::Point> front_face = {
            cv::Point(center.x - size/2, center.y - size/2),
            cv::Point(center.x + size/2, center.y - size/2),
            cv::Point(center.x + size/2, center.y + size/2),
            cv::Point(center.x - size/2, center.y + size/2)
        };
        
        std::vector<cv::Point> back_face = {
            cv::Point(center.x - size/4, center.y - size/4),
            cv::Point(center.x + size/4, center.y - size/4),
            cv::Point(center.x + size/4, center.y + size/4),
            cv::Point(center.x - size/4, center.y + size/4)
        };
        
        cv::fillPoly(frame, std::vector<std::vector<cv::Point>>{back_face}, cv::Scalar(0, 255, 0));
        
        // Draw connecting lines
        for (int i = 0; i < 4; i++) {
            cv::line(frame, front_face[i], back_face[i], cv::Scalar(255, 255, 255), 2);
        }
    }
    
    void drawVirtualPyramidAtPosition(const cv::Point2f& center) {
        int size = 40;
        
        // Base of pyramid
        cv::Rect base_rect(center.x - size/2, center.y - size/2, size, size);
        cv::rectangle(frame, base_rect, cv::Scalar(0, 0, 255), -1);
        
        // Apex of pyramid
        cv::Point apex(center.x, center.y - size);
        
        // Draw lines from base corners to apex
        cv::Point corners[4] = {
            cv::Point(center.x - size/2, center.y - size/2),
            cv::Point(center.x + size/2, center.y - size/2),
            cv::Point(center.x + size/2, center.y + size/2),
            cv::Point(center.x - size/2, center.y + size/2)
        };
        
        for (int i = 0; i < 4; i++) {
            cv::line(frame, corners[i], apex, cv::Scalar(255, 255, 255), 2);
        }
        
        // Draw apex
        cv::circle(frame, apex, 3, cv::Scalar(255, 255, 0), -1);
    }
    
    void drawVirtualPlaneAtPosition(const cv::Point2f& center) {
        int size = 60;
        
        // Draw textured plane
        cv::Rect plane_rect(center.x - size/2, center.y - size/2, size, size);
        
        // Resize virtual texture to fit plane
        cv::Mat resized_texture;
        cv::resize(virtual_texture, resized_texture, cv::Size(size, size));
        
        // Overlay texture on plane
        cv::Mat roi = frame(plane_rect);
        cv::addWeighted(roi, 0.3, resized_texture, 0.7, 0, roi);
        
        // Draw plane border
        cv::rectangle(frame, plane_rect, cv::Scalar(255, 255, 255), 2);
    }
    
    void processTextOverlay() {
        // Add various text overlays with different effects
        
        // Animated text
        static int frame_count = 0;
        frame_count++;
        
        // Pulsing title
        int alpha = 128 + 127 * sin(frame_count * 0.1);
        cv::Scalar color(0, alpha, 255 - alpha);
        cv::putText(frame, "AUGMENTED REALITY", cv::Point(50, 100), 
                   cv::FONT_HERSHEY_SIMPLEX, 2, color, 3);
        
        // Moving text
        int x_pos = 50 + 100 * sin(frame_count * 0.05);
        cv::putText(frame, "Moving Text", cv::Point(x_pos, 200), 
                   cv::FONT_HERSHEY_SIMPLEX, 1, cv::Scalar(255, 0, 255), 2);
        
        // Rotating text (simulated)
        int y_pos = 300 + 50 * cos(frame_count * 0.08);
        cv::putText(frame, "Rotating Effect", cv::Point(200, y_pos), 
                   cv::FONT_HERSHEY_SIMPLEX, 1.2, cv::Scalar(0, 255, 0), 2);
        
        // Information overlay
        cv::rectangle(frame, cv::Point(10, frame.rows - 100), 
                     cv::Point(400, frame.rows - 10), cv::Scalar(0, 0, 0), -1);
        cv::rectangle(frame, cv::Point(10, frame.rows - 100), 
                     cv::Point(400, frame.rows - 10), cv::Scalar(255, 255, 255), 2);
        
        cv::putText(frame, "Text Overlay Mode", cv::Point(20, frame.rows - 70), 
                   cv::FONT_HERSHEY_SIMPLEX, 0.8, cv::Scalar(255, 255, 255), 2);
        cv::putText(frame, "Various text effects and animations", cv::Point(20, frame.rows - 40), 
                   cv::FONT_HERSHEY_SIMPLEX, 0.6, cv::Scalar(255, 255, 255), 1);
    }
    
    void processVirtualPainting() {
        static std::vector<cv::Point> brush_strokes;
        static cv::Scalar brush_color(0, 255, 0);
        
        // Detect hand/finger movement (simplified using motion detection)
        static cv::Mat prev_gray;
        if (!prev_gray.empty()) {
            cv::Mat diff;
            cv::absdiff(gray, prev_gray, diff);
            
            // Find motion areas
            cv::Mat motion_mask;
            cv::threshold(diff, motion_mask, 30, 255, cv::THRESH_BINARY);
            
            // Find contours of motion
            std::vector<std::vector<cv::Point>> contours;
            cv::findContours(motion_mask, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);
            
            // Draw virtual brush strokes
            for (const auto& contour : contours) {
                if (cv::contourArea(contour) > 100) {
                    cv::Rect bounding_rect = cv::boundingRect(contour);
                    cv::Point center(bounding_rect.x + bounding_rect.width/2, 
                                   bounding_rect.y + bounding_rect.height/2);
                    
                    // Add brush stroke
                    brush_strokes.push_back(center);
                    
                    // Keep only recent strokes (last 1000 points)
                    if (brush_strokes.size() > 1000) {
                        brush_strokes.erase(brush_strokes.begin());
                    }
                }
            }
        }
        
        // Draw all brush strokes
        for (size_t i = 1; i < brush_strokes.size(); i++) {
            // Fade older strokes
            int alpha = 255 * (i / (double)brush_strokes.size());
            cv::Scalar color(0, alpha, 255 - alpha);
            
            cv::line(frame, brush_strokes[i-1], brush_strokes[i], color, 3);
        }
        
        prev_gray = gray.clone();
        
        // Add mode information
        cv::putText(frame, "Virtual Painting Mode", cv::Point(10, 30), 
                   cv::FONT_HERSHEY_SIMPLEX, 1, cv::Scalar(255, 255, 255), 2);
        cv::putText(frame, "Move your hand to paint", cv::Point(10, 70), 
                   cv::FONT_HERSHEY_SIMPLEX, 0.7, cv::Scalar(255, 255, 255), 2);
    }
    
    void processDepthEstimation() {
        // Simplified depth estimation using stereo vision simulation
        static cv::Mat disparity_map = cv::Mat::zeros(frame.size(), CV_8UC1);
        
        // Simulate depth using edge information
        cv::Mat edges;
        cv::Canny(gray, edges, 50, 150);
        
        // Create depth map based on edge density
        cv::Mat depth_map;
        cv::distanceTransform(edges, depth_map, cv::DIST_L2, 5);
        
        // Normalize depth map
        cv::normalize(depth_map, disparity_map, 0, 255, cv::NORM_MINMAX, CV_8UC1);
        
        // Apply color map for visualization
        cv::Mat colored_depth;
        cv::applyColorMap(disparity_map, colored_depth, cv::COLORMAP_JET);
        
        // Overlay depth information on original frame
        cv::addWeighted(frame, 0.7, colored_depth, 0.3, 0, frame);
        
        // Add depth information
        cv::putText(frame, "Depth Estimation Mode", cv::Point(10, 30), 
                   cv::FONT_HERSHEY_SIMPLEX, 1, cv::Scalar(255, 255, 255), 2);
        cv::putText(frame, "Closer objects appear brighter", cv::Point(10, 70), 
                   cv::FONT_HERSHEY_SIMPLEX, 0.7, cv::Scalar(255, 255, 255), 2);
        
        // Show depth map in separate window
        cv::imshow("Depth Map", colored_depth);
    }
    
    void displayModeInfo() {
        // Display current mode
        std::string mode_name = getModeName(current_mode);
        cv::putText(frame, "Mode: " + mode_name, cv::Point(10, frame.rows - 30), 
                   cv::FONT_HERSHEY_SIMPLEX, 0.7, cv::Scalar(255, 255, 255), 2);
        
        // Display instructions
        cv::putText(frame, "Press 1-6 to switch modes, 'q' to quit", 
                   cv::Point(10, frame.rows - 10), cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(255, 255, 255), 1);
    }
    
    std::string getModeName(ARMode mode) {
        switch (mode) {
            case FACE_DETECTION: return "Face Detection AR";
            case ARUCO_TRACKING: return "ArUco Tracking";
            case VIRTUAL_OBJECTS: return "Virtual Objects";
            case TEXT_OVERLAY: return "Text Overlay";
            case VIRTUAL_PAINTING: return "Virtual Painting";
            case DEPTH_ESTIMATION: return "Depth Estimation";
            default: return "Unknown";
        }
    }
};

int main() {
    try {
        AugmentedRealityDemo ar_demo;
        ar_demo.runAR();
        
    } catch (const cv::Exception& e) {
        std::cout << "OpenCV Error: " << e.what() << std::endl;
        return -1;
    } catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << std::endl;
        return -1;
    }
    
    std::cout << "\nKey Features Demonstrated:" << std::endl;
    std::cout << "- Real-time face detection with virtual accessories" << std::endl;
    std::cout << "- ArUco marker tracking and 3D object placement" << std::endl;
    std::cout << "- Virtual 3D objects (cube, pyramid, plane) rendering" << std::endl;
    std::cout << "- Dynamic text overlays with animations" << std::endl;
    std::cout << "- Virtual painting using motion detection" << std::endl;
    std::cout << "- Depth estimation and visualization" << std::endl;
    std::cout << "- Multiple AR modes with real-time switching" << std::endl;
    std::cout << "- Camera parameter estimation for 3D rendering" << std::endl;
    std::cout << "- Interactive AR experience with user controls" << std::endl;
    
    cv::destroyAllWindows();
    return 0;
}
