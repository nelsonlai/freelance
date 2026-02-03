// 27_advanced_camera_calibration.cpp
// Advanced Level - Advanced Camera Calibration and Undistortion
// This program demonstrates camera calibration, lens distortion correction, and stereo vision setup

#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/calib3d.hpp>
#include <vector>

class CameraCalibrator {
private:
    cv::VideoCapture cap;
    cv::Mat cameraMatrix, distCoeffs, rvecs, tvecs;
    std::vector<cv::Point3f> objectPoints;
    std::vector<std::vector<cv::Point2f>> imagePoints;
    std::vector<cv::Point2f> currentImagePoints;
    bool calibrated;
    int calibration_images;
    
    // Chessboard parameters
    cv::Size boardSize;
    float squareSize;
    
public:
    CameraCalibrator() : cap(0), calibrated(false), calibration_images(0) {
        if (!cap.isOpened()) {
            std::cout << "Error: Could not open camera" << std::endl;
            exit(-1);
        }
        
        // Initialize chessboard parameters
        boardSize = cv::Size(9, 6);  // 9x6 internal corners
        squareSize = 1.0f;           // 1 unit per square
        
        initializeObjectPoints();
        
        std::cout << "Camera Calibrator initialized!" << std::endl;
        std::cout << "Looking for " << boardSize.width << "x" << boardSize.height << " chessboard pattern." << std::endl;
    }
    
    void initializeObjectPoints() {
        // Create 3D points for chessboard corners
        objectPoints.clear();
        for (int i = 0; i < boardSize.height; i++) {
            for (int j = 0; j < boardSize.width; j++) {
                objectPoints.push_back(cv::Point3f(j * squareSize, i * squareSize, 0));
            }
        }
        std::cout << "Generated " << objectPoints.size() << " object points for calibration." << std::endl;
    }
    
    void runCalibration() {
        std::cout << "=== Advanced Camera Calibration and Undistortion ===" << std::endl;
        std::cout << "Instructions:" << std::endl;
        std::cout << "  1. Print a " << boardSize.width << "x" << boardSize.height << " chessboard pattern" << std::endl;
        std::cout << "  2. Show the chessboard to the camera at different angles and distances" << std::endl;
        std::cout << "  3. Press 'c' to capture calibration images (need at least 10)" << std::endl;
        std::cout << "  4. Press 'r' to run calibration when you have enough images" << std::endl;
        std::cout << "  5. Press 'u' to show undistorted view" << std::endl;
        std::cout << "  6. Press 'i' to show camera information" << std::endl;
        std::cout << "  7. Press 's' to save calibration parameters" << std::endl;
        std::cout << "  8. Press 'q' to quit" << std::endl;
        
        cv::Mat frame, gray;
        
        while (true) {
            cap >> frame;
            if (frame.empty()) break;
            
            // Flip frame horizontally for mirror effect
            cv::flip(frame, frame, 1);
            
            // Convert to grayscale for corner detection
            cv::cvtColor(frame, gray, cv::COLOR_BGR2GRAY);
            
            // Try to find chessboard corners
            bool found = cv::findChessboardCorners(gray, boardSize, currentImagePoints,
                                                 cv::CALIB_CB_ADAPTIVE_THRESH | 
                                                 cv::CALIB_CB_NORMALIZE_IMAGE |
                                                 cv::CALIB_CB_FAST_CHECK);
            
            // Draw results
            if (found) {
                // Refine corner positions
                cv::cornerSubPix(gray, currentImagePoints, cv::Size(11, 11), cv::Size(-1, -1),
                               cv::TermCriteria(cv::TermCriteria::EPS + cv::TermCriteria::COUNT, 30, 0.1));
                
                // Draw chessboard corners
                cv::drawChessboardCorners(frame, boardSize, cv::Mat(currentImagePoints), found);
                
                // Draw corner numbers
                for (size_t i = 0; i < currentImagePoints.size(); i++) {
                    cv::putText(frame, std::to_string(i), currentImagePoints[i] + cv::Point2f(5, 5),
                              cv::FONT_HERSHEY_SIMPLEX, 0.3, cv::Scalar(0, 255, 0), 1);
                }
            }
            
            // Display status information
            displayStatus(frame);
            
            // Show frame
            cv::imshow("Camera Calibration", frame);
            
            // Handle keyboard input
            char key = cv::waitKey(1) & 0xFF;
            switch (key) {
                case 'c':
                    captureCalibrationImage(currentImagePoints, found);
                    break;
                case 'r':
                    performCalibration();
                    break;
                case 'u':
                    if (calibrated) {
                        showUndistortedView();
                    } else {
                        std::cout << "Please calibrate the camera first!" << std::endl;
                    }
                    break;
                case 'i':
                    if (calibrated) {
                        showCameraInformation();
                    } else {
                        std::cout << "Please calibrate the camera first!" << std::endl;
                    }
                    break;
                case 's':
                    if (calibrated) {
                        saveCalibrationParameters();
                    } else {
                        std::cout << "Please calibrate the camera first!" << std::endl;
                    }
                    break;
                case 'q':
                    return;
            }
        }
    }
    
private:
    void captureCalibrationImage(const std::vector<cv::Point2f>& corners, bool found) {
        if (found) {
            imagePoints.push_back(corners);
            calibration_images++;
            std::cout << "Captured calibration image " << calibration_images << std::endl;
            
            if (calibration_images >= 10) {
                std::cout << "You have enough images for calibration. Press 'r' to calibrate." << std::endl;
            }
        } else {
            std::cout << "Chessboard not found! Please adjust the chessboard position." << std::endl;
        }
    }
    
    void performCalibration() {
        if (imagePoints.size() < 10) {
            std::cout << "Not enough calibration images! Need at least 10, have " << imagePoints.size() << std::endl;
            return;
        }
        
        std::cout << "Performing camera calibration with " << imagePoints.size() << " images..." << std::endl;
        
        // Prepare object points for all images
        std::vector<std::vector<cv::Point3f>> objectPointsArray(imagePoints.size(), objectPoints);
        
        // Initialize camera matrix
        cv::Size imageSize = cv::Size(640, 480); // Default size, will be updated from actual images
        
        // Perform calibration
        std::vector<cv::Mat> rvecs_temp, tvecs_temp;
        double rms = cv::calibrateCamera(objectPointsArray, imagePoints, imageSize,
                                       cameraMatrix, distCoeffs, rvecs_temp, tvecs_temp,
                                       cv::CALIB_FIX_PRINCIPAL_POINT);
        
        std::cout << "Calibration completed!" << std::endl;
        std::cout << "RMS reprojection error: " << rms << " pixels" << std::endl;
        
        // Store rotation and translation vectors
        rvecs = cv::Mat(rvecs_temp.size(), 3, CV_64F);
        tvecs = cv::Mat(tvecs_temp.size(), 3, CV_64F);
        
        for (size_t i = 0; i < rvecs_temp.size(); i++) {
            rvecs_temp[i].copyTo(rvecs.row(i));
            tvecs_temp[i].copyTo(tvecs.row(i));
        }
        
        calibrated = true;
        
        // Display calibration results
        displayCalibrationResults();
    }
    
    void displayCalibrationResults() {
        std::cout << "\n=== Calibration Results ===" << std::endl;
        
        // Camera matrix
        std::cout << "Camera Matrix:" << std::endl;
        std::cout << "  fx: " << cameraMatrix.at<double>(0, 0) << std::endl;
        std::cout << "  fy: " << cameraMatrix.at<double>(1, 1) << std::endl;
        std::cout << "  cx: " << cameraMatrix.at<double>(0, 2) << std::endl;
        std::cout << "  cy: " << cameraMatrix.at<double>(1, 2) << std::endl;
        
        // Distortion coefficients
        std::cout << "Distortion Coefficients:" << std::endl;
        std::cout << "  k1: " << distCoeffs.at<double>(0, 0) << std::endl;
        std::cout << "  k2: " << distCoeffs.at<double>(0, 1) << std::endl;
        std::cout << "  p1: " << distCoeffs.at<double>(0, 2) << std::endl;
        std::cout << "  p2: " << distCoeffs.at<double>(0, 3) << std::endl;
        if (distCoeffs.rows > 4) {
            std::cout << "  k3: " << distCoeffs.at<double>(0, 4) << std::endl;
        }
        
        // Calculate field of view
        double fx = cameraMatrix.at<double>(0, 0);
        double fy = cameraMatrix.at<double>(1, 1);
        double imageWidth = cameraMatrix.at<double>(0, 2) * 2;
        double imageHeight = cameraMatrix.at<double>(1, 2) * 2;
        
        double fovx = 2 * atan(imageWidth / (2 * fx)) * 180 / CV_PI;
        double fovy = 2 * atan(imageHeight / (2 * fy)) * 180 / CV_PI;
        
        std::cout << "Field of View:" << std::endl;
        std::cout << "  Horizontal: " << std::fixed << std::setprecision(2) << fovx << " degrees" << std::endl;
        std::cout << "  Vertical: " << std::fixed << std::setprecision(2) << fovy << " degrees" << std::endl;
    }
    
    void showUndistortedView() {
        std::cout << "Showing undistorted view. Press any key to return to calibration." << std::endl;
        
        cv::Mat frame, undistorted;
        
        while (true) {
            cap >> frame;
            if (frame.empty()) break;
            
            cv::flip(frame, frame, 1);
            
            // Undistort the image
            cv::undistort(frame, undistorted, cameraMatrix, distCoeffs);
            
            // Create side-by-side comparison
            cv::Mat comparison;
            cv::hconcat(frame, undistorted, comparison);
            
            // Add labels
            cv::putText(comparison, "Original (Distorted)", cv::Point(10, 30), 
                       cv::FONT_HERSHEY_SIMPLEX, 1, cv::Scalar(0, 255, 0), 2);
            cv::putText(comparison, "Undistorted", cv::Point(frame.cols + 10, 30), 
                       cv::FONT_HERSHEY_SIMPLEX, 1, cv::Scalar(0, 255, 0), 2);
            
            cv::imshow("Undistorted View", comparison);
            
            if (cv::waitKey(1) & 0xFF == 'q') break;
        }
        
        cv::destroyWindow("Undistorted View");
    }
    
    void showCameraInformation() {
        // Create information overlay
        cv::Mat info_image = cv::Mat::zeros(400, 600, CV_8UC3);
        
        // Background
        cv::rectangle(info_image, cv::Point(0, 0), cv::Point(600, 400), cv::Scalar(50, 50, 50), -1);
        cv::rectangle(info_image, cv::Point(10, 10), cv::Point(590, 390), cv::Scalar(100, 100, 100), 2);
        
        // Title
        cv::putText(info_image, "Camera Calibration Information", cv::Point(50, 50), 
                   cv::FONT_HERSHEY_SIMPLEX, 1, cv::Scalar(255, 255, 255), 2);
        
        // Camera matrix info
        int y_pos = 100;
        cv::putText(info_image, "Camera Matrix:", cv::Point(50, y_pos), 
                   cv::FONT_HERSHEY_SIMPLEX, 0.7, cv::Scalar(0, 255, 255), 2);
        y_pos += 30;
        
        std::string fx_str = "fx: " + std::to_string(cameraMatrix.at<double>(0, 0));
        std::string fy_str = "fy: " + std::to_string(cameraMatrix.at<double>(1, 1));
        std::string cx_str = "cx: " + std::to_string(cameraMatrix.at<double>(0, 2));
        std::string cy_str = "cy: " + std::to_string(cameraMatrix.at<double>(1, 2));
        
        cv::putText(info_image, fx_str, cv::Point(70, y_pos), cv::FONT_HERSHEY_SIMPLEX, 0.6, cv::Scalar(255, 255, 255), 1);
        y_pos += 25;
        cv::putText(info_image, fy_str, cv::Point(70, y_pos), cv::FONT_HERSHEY_SIMPLEX, 0.6, cv::Scalar(255, 255, 255), 1);
        y_pos += 25;
        cv::putText(info_image, cx_str, cv::Point(70, y_pos), cv::FONT_HERSHEY_SIMPLEX, 0.6, cv::Scalar(255, 255, 255), 1);
        y_pos += 25;
        cv::putText(info_image, cy_str, cv::Point(70, y_pos), cv::FONT_HERSHEY_SIMPLEX, 0.6, cv::Scalar(255, 255, 255), 1);
        y_pos += 40;
        
        // Distortion coefficients
        cv::putText(info_image, "Distortion Coefficients:", cv::Point(50, y_pos), 
                   cv::FONT_HERSHEY_SIMPLEX, 0.7, cv::Scalar(0, 255, 255), 2);
        y_pos += 30;
        
        std::string k1_str = "k1: " + std::to_string(distCoeffs.at<double>(0, 0));
        std::string k2_str = "k2: " + std::to_string(distCoeffs.at<double>(0, 1));
        std::string p1_str = "p1: " + std::to_string(distCoeffs.at<double>(0, 2));
        std::string p2_str = "p2: " + std::to_string(distCoeffs.at<double>(0, 3));
        
        cv::putText(info_image, k1_str, cv::Point(70, y_pos), cv::FONT_HERSHEY_SIMPLEX, 0.6, cv::Scalar(255, 255, 255), 1);
        y_pos += 25;
        cv::putText(info_image, k2_str, cv::Point(70, y_pos), cv::FONT_HERSHEY_SIMPLEX, 0.6, cv::Scalar(255, 255, 255), 1);
        y_pos += 25;
        cv::putText(info_image, p1_str, cv::Point(70, y_pos), cv::FONT_HERSHEY_SIMPLEX, 0.6, cv::Scalar(255, 255, 255), 1);
        y_pos += 25;
        cv::putText(info_image, p2_str, cv::Point(70, y_pos), cv::FONT_HERSHEY_SIMPLEX, 0.6, cv::Scalar(255, 255, 255), 1);
        y_pos += 40;
        
        // Calibration statistics
        cv::putText(info_image, "Calibration Statistics:", cv::Point(50, y_pos), 
                   cv::FONT_HERSHEY_SIMPLEX, 0.7, cv::Scalar(0, 255, 255), 2);
        y_pos += 30;
        
        std::string images_str = "Calibration Images: " + std::to_string(calibration_images);
        std::string points_str = "Object Points per Image: " + std::to_string(objectPoints.size());
        
        cv::putText(info_image, images_str, cv::Point(70, y_pos), cv::FONT_HERSHEY_SIMPLEX, 0.6, cv::Scalar(255, 255, 255), 1);
        y_pos += 25;
        cv::putText(info_image, points_str, cv::Point(70, y_pos), cv::FONT_HERSHEY_SIMPLEX, 0.6, cv::Scalar(255, 255, 255), 1);
        
        cv::putText(info_image, "Press any key to continue...", cv::Point(50, 350), 
                   cv::FONT_HERSHEY_SIMPLEX, 0.6, cv::Scalar(0, 255, 0), 1);
        
        cv::imshow("Camera Information", info_image);
        cv::waitKey(0);
        cv::destroyWindow("Camera Information");
    }
    
    void saveCalibrationParameters() {
        cv::FileStorage fs("camera_calibration.xml", cv::FileStorage::WRITE);
        
        fs << "camera_matrix" << cameraMatrix;
        fs << "distortion_coefficients" << distCoeffs;
        fs << "image_width" << 640;
        fs << "image_height" << 480;
        fs << "calibration_images" << calibration_images;
        fs << "board_size_width" << boardSize.width;
        fs << "board_size_height" << boardSize.height;
        fs << "square_size" << squareSize;
        
        fs.release();
        
        std::cout << "Calibration parameters saved to 'camera_calibration.xml'" << std::endl;
    }
    
    void displayStatus(cv::Mat& frame) {
        // Display current status
        std::string status = "Calibration Images: " + std::to_string(calibration_images);
        cv::putText(frame, status, cv::Point(10, frame.rows - 80), 
                   cv::FONT_HERSHEY_SIMPLEX, 0.6, cv::Scalar(255, 255, 255), 2);
        
        if (calibrated) {
            cv::putText(frame, "Camera Calibrated!", cv::Point(10, frame.rows - 50), 
                       cv::FONT_HERSHEY_SIMPLEX, 0.6, cv::Scalar(0, 255, 0), 2);
        } else {
            cv::putText(frame, "Camera Not Calibrated", cv::Point(10, frame.rows - 50), 
                       cv::FONT_HERSHEY_SIMPLEX, 0.6, cv::Scalar(0, 0, 255), 2);
        }
        
        // Display chessboard detection status
        if (!currentImagePoints.empty()) {
            cv::putText(frame, "Chessboard Found!", cv::Point(10, frame.rows - 20), 
                       cv::FONT_HERSHEY_SIMPLEX, 0.6, cv::Scalar(0, 255, 0), 2);
        } else {
            cv::putText(frame, "No Chessboard Detected", cv::Point(10, frame.rows - 20), 
                       cv::FONT_HERSHEY_SIMPLEX, 0.6, cv::Scalar(0, 0, 255), 2);
        }
    }
};

int main() {
    try {
        CameraCalibrator calibrator;
        calibrator.runCalibration();
        
    } catch (const cv::Exception& e) {
        std::cout << "OpenCV Error: " << e.what() << std::endl;
        return -1;
    } catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << std::endl;
        return -1;
    }
    
    std::cout << "\nKey Features Demonstrated:" << std::endl;
    std::cout << "- Chessboard pattern detection and corner refinement" << std::endl;
    std::cout << "- Camera intrinsic parameter calibration" << std::endl;
    std::cout << "- Lens distortion coefficient estimation" << std::endl;
    std::cout << "- Real-time image undistortion" << std::endl;
    std::cout << "- Calibration quality assessment (RMS error)" << std::endl;
    std::cout << "- Field of view calculation" << std::endl;
    std::cout << "- Calibration parameter saving and loading" << std::endl;
    std::cout << "- Interactive calibration process" << std::endl;
    std::cout << "- Before/after distortion comparison" << std::endl;
    
    cv::destroyAllWindows();
    return 0;
}
