// 24_3d_object_detection.cpp
// Advanced Level - 3D Object Detection and Pose Estimation
// This program demonstrates 3D object detection, pose estimation, and AR applications

#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/calib3d.hpp>
#include <opencv2/aruco.hpp>
#include <vector>

class Object3DDetector {
private:
    cv::VideoCapture cap;
    cv::Mat cameraMatrix, distCoeffs;
    cv::Mat frame, gray;
    bool camera_calibrated;
    
    // 3D object points for different shapes
    std::vector<cv::Point3f> cube_points;
    std::vector<cv::Point3f> pyramid_points;
    std::vector<cv::Point3f> plane_points;
    
    // ArUco markers
    cv::Ptr<cv::aruco::Dictionary> aruco_dict;
    cv::Ptr<cv::aruco::DetectorParameters> aruco_params;
    
public:
    Object3DDetector() : cap(0), camera_calibrated(false) {
        if (!cap.isOpened()) {
            std::cout << "Error: Could not open camera" << std::endl;
            exit(-1);
        }
        
        initialize3DPoints();
        initializeArUco();
        estimateCameraParameters();
    }
    
    void initialize3DPoints() {
        // Define 3D points for a cube (8 vertices)
        cube_points = {
            cv::Point3f(-1, -1, 0),  // bottom-left-front
            cv::Point3f(1, -1, 0),   // bottom-right-front
            cv::Point3f(1, 1, 0),    // top-right-front
            cv::Point3f(-1, 1, 0),   // top-left-front
            cv::Point3f(-1, -1, 2),  // bottom-left-back
            cv::Point3f(1, -1, 2),   // bottom-right-back
            cv::Point3f(1, 1, 2),    // top-right-back
            cv::Point3f(-1, 1, 2)    // top-left-back
        };
        
        // Define 3D points for a pyramid (5 vertices)
        pyramid_points = {
            cv::Point3f(-1, -1, 0),  // base corners
            cv::Point3f(1, -1, 0),
            cv::Point3f(1, 1, 0),
            cv::Point3f(-1, 1, 0),
            cv::Point3f(0, 0, 2)     // apex
        };
        
        // Define 3D points for a plane (4 vertices)
        plane_points = {
            cv::Point3f(-2, -1, 0),
            cv::Point3f(2, -1, 0),
            cv::Point3f(2, 1, 0),
            cv::Point3f(-2, 1, 0)
        };
    }
    
    void initializeArUco() {
        // Initialize ArUco dictionary and parameters
        aruco_dict = cv::aruco::getPredefinedDictionary(cv::aruco::DICT_6X6_250);
        aruco_params = cv::aruco::DetectorParameters::create();
    }
    
    void estimateCameraParameters() {
        // In a real application, you would calibrate the camera using a chessboard
        // For this demo, we'll estimate camera parameters based on frame size
        
        cap >> frame;
        if (frame.empty()) return;
        
        int width = frame.cols;
        int height = frame.rows;
        
        // Estimate focal length (typical values for webcams)
        double fx = width * 0.8;  // focal length in x
        double fy = height * 0.8; // focal length in y
        double cx = width / 2.0;  // principal point x
        double cy = height / 2.0; // principal point y
        
        cameraMatrix = (cv::Mat_<double>(3, 3) <<
            fx, 0, cx,
            0, fy, cy,
            0, 0, 1);
        
        // Estimate distortion coefficients (usually close to zero for good cameras)
        distCoeffs = cv::Mat::zeros(4, 1, CV_64F);
        
        camera_calibrated = true;
        std::cout << "Camera parameters estimated:" << std::endl;
        std::cout << "Focal length: " << fx << " x " << fy << std::endl;
        std::cout << "Principal point: " << cx << " x " << cy << std::endl;
    }
    
    void detectAndTrack3D() {
        std::cout << "=== 3D Object Detection and Pose Estimation ===" << std::endl;
        std::cout << "Controls:" << std::endl;
        std::cout << "  '1' - Draw 3D Cube" << std::endl;
        std::cout << "  '2' - Draw 3D Pyramid" << std::endl;
        std::cout << "  '3' - Draw 3D Plane" << std::endl;
        std::cout << "  'a' - Detect ArUco markers" << std::endl;
        std::cout << "  'c' - Show camera calibration info" << std::endl;
        std::cout << "  'q' - Quit" << std::endl;
        
        char mode = '1'; // Default to cube
        
        while (true) {
            cap >> frame;
            if (frame.empty()) break;
            
            // Flip frame horizontally for mirror effect
            cv::flip(frame, frame, 1);
            
            // Convert to grayscale for some operations
            cv::cvtColor(frame, gray, cv::COLOR_BGR2GRAY);
            
            // Process based on current mode
            switch (mode) {
                case '1':
                    draw3DObject(cube_points, "Cube");
                    break;
                case '2':
                    draw3DObject(pyramid_points, "Pyramid");
                    break;
                case '3':
                    draw3DObject(plane_points, "Plane");
                    break;
                case 'a':
                    detectArUcoMarkers();
                    break;
                case 'c':
                    showCameraInfo();
                    break;
            }
            
            // Display frame
            cv::imshow("3D Object Detection", frame);
            
            // Handle keyboard input
            char key = cv::waitKey(1) & 0xFF;
            if (key == 'q') break;
            if (key >= '1' && key <= '3') mode = key;
            if (key == 'a') mode = 'a';
            if (key == 'c') mode = 'c';
        }
    }
    
private:
    void draw3DObject(const std::vector<cv::Point3f>& object_points, const std::string& object_name) {
        // Find corners of a virtual rectangle in the image
        std::vector<cv::Point2f> image_points = findVirtualRectangle();
        
        if (image_points.size() == 4) {
            // Solve PnP to get rotation and translation vectors
            cv::Mat rvec, tvec;
            bool success = cv::solvePnP(
                cv::Mat(plane_points), // Use plane points as reference
                image_points,
                cameraMatrix,
                distCoeffs,
                rvec,
                tvec
            );
            
            if (success) {
                // Project 3D points to 2D image points
                std::vector<cv::Point2f> projected_points;
                cv::projectPoints(
                    object_points,
                    rvec,
                    tvec,
                    cameraMatrix,
                    distCoeffs,
                    projected_points
                );
                
                // Draw the 3D object
                drawObjectWireframe(projected_points, object_name);
                
                // Display pose information
                displayPoseInfo(rvec, tvec);
            }
        }
        
        // Draw the virtual rectangle for reference
        drawVirtualRectangle();
    }
    
    std::vector<cv::Point2f> findVirtualRectangle() {
        // Create a virtual rectangle in the center of the frame
        int center_x = frame.cols / 2;
        int center_y = frame.rows / 2;
        int rect_size = 100;
        
        std::vector<cv::Point2f> corners = {
            cv::Point2f(center_x - rect_size, center_y - rect_size),
            cv::Point2f(center_x + rect_size, center_y - rect_size),
            cv::Point2f(center_x + rect_size, center_y + rect_size),
            cv::Point2f(center_x - rect_size, center_y + rect_size)
        };
        
        return corners;
    }
    
    void drawVirtualRectangle() {
        std::vector<cv::Point2f> corners = findVirtualRectangle();
        
        // Draw rectangle corners
        for (const auto& corner : corners) {
            cv::circle(frame, corner, 5, cv::Scalar(0, 255, 0), -1);
        }
        
        // Draw rectangle outline
        for (size_t i = 0; i < corners.size(); i++) {
            cv::line(frame, corners[i], corners[(i + 1) % corners.size()], 
                    cv::Scalar(0, 255, 0), 2);
        }
    }
    
    void drawObjectWireframe(const std::vector<cv::Point2f>& points, const std::string& object_name) {
        cv::Scalar color(0, 0, 255); // Red color
        
        if (object_name == "Cube") {
            // Draw cube edges
            // Bottom face
            for (int i = 0; i < 4; i++) {
                cv::line(frame, points[i], points[(i + 1) % 4], color, 2);
            }
            // Top face
            for (int i = 4; i < 8; i++) {
                cv::line(frame, points[i], points[4 + (i - 4 + 1) % 4], color, 2);
            }
            // Vertical edges
            for (int i = 0; i < 4; i++) {
                cv::line(frame, points[i], points[i + 4], color, 2);
            }
        }
        else if (object_name == "Pyramid") {
            // Draw pyramid edges
            // Base
            for (int i = 0; i < 4; i++) {
                cv::line(frame, points[i], points[(i + 1) % 4], color, 2);
            }
            // Apex to base corners
            for (int i = 0; i < 4; i++) {
                cv::line(frame, points[4], points[i], color, 2);
            }
        }
        else if (object_name == "Plane") {
            // Draw plane edges
            for (int i = 0; i < 4; i++) {
                cv::line(frame, points[i], points[(i + 1) % 4], color, 2);
            }
        }
        
        // Draw vertices
        for (const auto& point : points) {
            cv::circle(frame, point, 3, color, -1);
        }
        
        // Add object name
        cv::putText(frame, object_name, cv::Point(10, 30), 
                   cv::FONT_HERSHEY_SIMPLEX, 1, color, 2);
    }
    
    void displayPoseInfo(const cv::Mat& rvec, const cv::Mat& tvec) {
        // Convert rotation vector to rotation matrix
        cv::Mat rotation_matrix;
        cv::Rodrigues(rvec, rotation_matrix);
        
        // Extract Euler angles (simplified)
        double roll = atan2(rotation_matrix.at<double>(2, 1), rotation_matrix.at<double>(2, 2));
        double pitch = asin(-rotation_matrix.at<double>(2, 0));
        double yaw = atan2(rotation_matrix.at<double>(1, 0), rotation_matrix.at<double>(0, 0));
        
        // Display pose information
        std::string info = "Translation: [" + 
                          std::to_string((int)tvec.at<double>(0)) + ", " +
                          std::to_string((int)tvec.at<double>(1)) + ", " +
                          std::to_string((int)tvec.at<double>(2)) + "]";
        cv::putText(frame, info, cv::Point(10, frame.rows - 80), 
                   cv::FONT_HERSHEY_SIMPLEX, 0.6, cv::Scalar(255, 255, 255), 2);
        
        std::string angles = "Rotation: R:" + std::to_string((int)(roll * 180 / CV_PI)) + 
                           " P:" + std::to_string((int)(pitch * 180 / CV_PI)) + 
                           " Y:" + std::to_string((int)(yaw * 180 / CV_PI));
        cv::putText(frame, angles, cv::Point(10, frame.rows - 50), 
                   cv::FONT_HERSHEY_SIMPLEX, 0.6, cv::Scalar(255, 255, 255), 2);
    }
    
    void detectArUcoMarkers() {
        std::vector<int> marker_ids;
        std::vector<std::vector<cv::Point2f>> marker_corners;
        
        // Detect ArUco markers
        cv::aruco::detectMarkers(gray, aruco_dict, marker_corners, marker_ids, aruco_params);
        
        if (marker_ids.size() > 0) {
            // Draw detected markers
            cv::aruco::drawDetectedMarkers(frame, marker_corners, marker_ids);
            
            // Estimate pose for each marker
            std::vector<cv::Vec3d> rvecs, tvecs;
            cv::aruco::estimatePoseSingleMarkers(marker_corners, 0.05, cameraMatrix, distCoeffs, rvecs, tvecs);
            
            // Draw 3D axes for each marker
            for (size_t i = 0; i < marker_ids.size(); i++) {
                cv::aruco::drawAxis(frame, cameraMatrix, distCoeffs, rvecs[i], tvecs[i], 0.1);
                
                // Display marker ID and pose info
                cv::Point2f marker_center = (marker_corners[i][0] + marker_corners[i][2]) / 2;
                std::string marker_info = "ID: " + std::to_string(marker_ids[i]);
                cv::putText(frame, marker_info, marker_center, 
                           cv::FONT_HERSHEY_SIMPLEX, 0.8, cv::Scalar(0, 255, 255), 2);
            }
            
            std::string count_info = "ArUco Markers: " + std::to_string(marker_ids.size());
            cv::putText(frame, count_info, cv::Point(10, 30), 
                       cv::FONT_HERSHEY_SIMPLEX, 1, cv::Scalar(0, 255, 255), 2);
        } else {
            cv::putText(frame, "No ArUco markers detected", cv::Point(10, 30), 
                       cv::FONT_HERSHEY_SIMPLEX, 1, cv::Scalar(0, 0, 255), 2);
            cv::putText(frame, "Print ArUco markers from DICT_6X6_250", cv::Point(10, 70), 
                       cv::FONT_HERSHEY_SIMPLEX, 0.7, cv::Scalar(255, 255, 255), 2);
        }
    }
    
    void showCameraInfo() {
        // Create info overlay
        cv::Mat info_overlay = frame.clone();
        
        // Add semi-transparent background
        cv::rectangle(info_overlay, cv::Point(10, 10), cv::Point(400, 200), cv::Scalar(0, 0, 0), -1);
        cv::rectangle(info_overlay, cv::Point(10, 10), cv::Point(400, 200), cv::Scalar(255, 255, 255), 2);
        
        // Display camera matrix
        cv::putText(info_overlay, "Camera Matrix:", cv::Point(20, 40), 
                   cv::FONT_HERSHEY_SIMPLEX, 0.6, cv::Scalar(255, 255, 255), 1);
        
        std::string fx_info = "fx: " + std::to_string(cameraMatrix.at<double>(0, 0));
        std::string fy_info = "fy: " + std::to_string(cameraMatrix.at<double>(1, 1));
        std::string cx_info = "cx: " + std::to_string(cameraMatrix.at<double>(0, 2));
        std::string cy_info = "cy: " + std::to_string(cameraMatrix.at<double>(1, 2));
        
        cv::putText(info_overlay, fx_info, cv::Point(20, 70), 
                   cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(255, 255, 255), 1);
        cv::putText(info_overlay, fy_info, cv::Point(20, 90), 
                   cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(255, 255, 255), 1);
        cv::putText(info_overlay, cx_info, cv::Point(20, 110), 
                   cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(255, 255, 255), 1);
        cv::putText(info_overlay, cy_info, cv::Point(20, 130), 
                   cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(255, 255, 255), 1);
        
        cv::putText(info_overlay, "Press any key to continue", cv::Point(20, 170), 
                   cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(0, 255, 0), 1);
        
        cv::imshow("3D Object Detection", info_overlay);
        cv::waitKey(0);
    }
};

int main() {
    try {
        Object3DDetector detector;
        detector.detectAndTrack3D();
        
    } catch (const cv::Exception& e) {
        std::cout << "OpenCV Error: " << e.what() << std::endl;
        return -1;
    } catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << std::endl;
        return -1;
    }
    
    std::cout << "\nKey Features Demonstrated:" << std::endl;
    std::cout << "- 3D object detection and pose estimation" << std::endl;
    std::cout << "- Camera calibration and parameter estimation" << std::endl;
    std::cout << "- PnP (Perspective-n-Point) solving" << std::endl;
    std::cout << "- 3D wireframe rendering in real-time" << std::endl;
    std::cout << "- ArUco marker detection and pose estimation" << std::endl;
    std::cout << "- Multiple 3D object types (cube, pyramid, plane)" << std::endl;
    std::cout << "- Augmented reality overlay applications" << std::endl;
    std::cout << "- Real-time pose visualization" << std::endl;
    
    cv::destroyAllWindows();
    return 0;
}
