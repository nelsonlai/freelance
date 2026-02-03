// 29_advanced_video_stabilization.cpp
// Advanced Level - Advanced Video Stabilization
// This program demonstrates various video stabilization techniques including optical flow and feature-based stabilization

#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/video.hpp>
#include <vector>
#include <deque>

class VideoStabilizer {
private:
    cv::VideoCapture cap;
    cv::Mat frame, prev_frame, stabilized_frame;
    cv::Mat prev_gray, curr_gray;
    
    // Stabilization parameters
    std::deque<cv::Mat> frame_buffer;
    std::deque<cv::Mat> transform_buffer;
    int buffer_size;
    
    // Feature detection
    std::vector<cv::Point2f> prev_points, curr_points;
    cv::Ptr<cv::FeatureDetector> detector;
    cv::Ptr<cv::DescriptorExtractor> extractor;
    cv::Ptr<cv::DescriptorMatcher> matcher;
    
    // Stabilization modes
    enum StabilizationMode {
        OPTICAL_FLOW,
        FEATURE_BASED,
        GYROSCOPE_SIMULATION,
        HYBRID_STABILIZATION,
        TEMPORAL_FILTERING,
        MOTION_COMPENSATION
    };
    StabilizationMode current_mode;
    
    // Motion tracking
    cv::Mat cumulative_transform;
    std::vector<cv::Mat> motion_history;
    
public:
    VideoStabilizer() : buffer_size(10), current_mode(OPTICAL_FLOW) {
        if (!cap.isOpened()) {
            std::cout << "Error: Could not open camera" << std::endl;
            exit(-1);
        }
        
        initializeFeatureDetection();
        cumulative_transform = cv::Mat::eye(3, 3, CV_64F);
        
        std::cout << "Video Stabilizer initialized!" << std::endl;
    }
    
    void initializeFeatureDetection() {
        // Initialize feature detection components
        detector = cv::ORB::create(1000);
        extractor = cv::ORB::create();
        matcher = cv::BFMatcher::create(cv::NORM_HAMMING);
        
        std::cout << "Feature detection components initialized." << std::endl;
    }
    
    void runStabilization() {
        std::cout << "=== Advanced Video Stabilization ===" << std::endl;
        std::cout << "Controls:" << std::endl;
        std::cout << "  '1' - Optical Flow Stabilization" << std::endl;
        std::cout << "  '2' - Feature-based Stabilization" << std::endl;
        std::cout << "  '3' - Gyroscope Simulation" << std::endl;
        std::cout << "  '4' - Hybrid Stabilization" << std::endl;
        std::cout << "  '5' - Temporal Filtering" << std::endl;
        std::cout << "  '6' - Motion Compensation" << std::endl;
        std::cout << "  'r' - Reset stabilization" << std::endl;
        std::cout << "  's' - Save stabilized video" << std::endl;
        std::cout << "  'q' - Quit" << std::endl;
        
        cv::VideoWriter stabilized_writer;
        bool recording = false;
        
        while (true) {
            cap >> frame;
            if (frame.empty()) break;
            
            // Flip frame horizontally for mirror effect
            cv::flip(frame, frame, 1);
            
            // Convert to grayscale
            cv::cvtColor(frame, curr_gray, cv::COLOR_BGR2GRAY);
            
            // Apply stabilization based on current mode
            switch (current_mode) {
                case OPTICAL_FLOW:
                    stabilizeOpticalFlow();
                    break;
                case FEATURE_BASED:
                    stabilizeFeatureBased();
                    break;
                case GYROSCOPE_SIMULATION:
                    stabilizeGyroscopeSimulation();
                    break;
                case HYBRID_STABILIZATION:
                    stabilizeHybrid();
                    break;
                case TEMPORAL_FILTERING:
                    stabilizeTemporalFiltering();
                    break;
                case MOTION_COMPENSATION:
                    stabilizeMotionCompensation();
                    break;
            }
            
            // Display results
            displayStabilizedVideo(recording, stabilized_writer);
            
            // Update for next iteration
            prev_gray = curr_gray.clone();
            prev_frame = frame.clone();
            
            char key = cv::waitKey(1) & 0xFF;
            if (key == 'q') break;
            if (key >= '1' && key <= '6') {
                current_mode = static_cast<StabilizationMode>(key - '1');
                resetStabilization();
                std::cout << "Switched to mode: " << getModeName(current_mode) << std::endl;
            }
            if (key == 'r') {
                resetStabilization();
                std::cout << "Stabilization reset!" << std::endl;
            }
            if (key == 's') {
                recording = !recording;
                if (recording) {
                    startRecording(stabilized_writer);
                    std::cout << "Started recording stabilized video." << std::endl;
                } else {
                    stopRecording(stabilized_writer);
                    std::cout << "Stopped recording." << std::endl;
                }
            }
        }
        
        if (recording) {
            stopRecording(stabilized_writer);
        }
    }
    
private:
    void stabilizeOpticalFlow() {
        if (prev_gray.empty()) {
            stabilized_frame = frame.clone();
            return;
        }
        
        // Calculate optical flow
        std::vector<cv::Point2f> flow_points;
        std::vector<uchar> status;
        std::vector<float> errors;
        
        // Detect good features to track
        cv::goodFeaturesToTrack(prev_gray, prev_points, 100, 0.01, 10);
        
        if (prev_points.empty()) {
            stabilized_frame = frame.clone();
            return;
        }
        
        // Calculate optical flow
        cv::calcOpticalFlowPyrLK(prev_gray, curr_gray, prev_points, curr_points, 
                                status, errors);
        
        // Filter valid points
        std::vector<cv::Point2f> valid_prev, valid_curr;
        for (size_t i = 0; i < status.size(); i++) {
            if (status[i] && cv::norm(prev_points[i] - curr_points[i]) < 50) {
                valid_prev.push_back(prev_points[i]);
                valid_curr.push_back(curr_points[i]);
            }
        }
        
        if (valid_prev.size() < 4) {
            stabilized_frame = frame.clone();
            return;
        }
        
        // Estimate transformation matrix
        cv::Mat transform = cv::estimateAffinePartial2D(valid_prev, valid_curr);
        
        if (!transform.empty()) {
            // Extract translation and rotation
            double dx = transform.at<double>(0, 2);
            double dy = transform.at<double>(1, 2);
            double rotation = atan2(transform.at<double>(1, 0), transform.at<double>(0, 0));
            
            // Apply smoothing to reduce jitter
            dx *= 0.3;  // Reduce translation
            dy *= 0.3;
            rotation *= 0.5;  // Reduce rotation
            
            // Create smoothed transformation
            cv::Mat smoothed_transform = (cv::Mat_<double>(2, 3) <<
                cos(rotation), -sin(rotation), -dx,
                sin(rotation), cos(rotation), -dy);
            
            // Apply transformation
            cv::warpAffine(frame, stabilized_frame, smoothed_transform, frame.size());
        } else {
            stabilized_frame = frame.clone();
        }
    }
    
    void stabilizeFeatureBased() {
        if (prev_gray.empty()) {
            stabilized_frame = frame.clone();
            return;
        }
        
        // Detect features
        std::vector<cv::KeyPoint> prev_keypoints, curr_keypoints;
        cv::Mat prev_descriptors, curr_descriptors;
        
        detector->detect(prev_gray, prev_keypoints);
        detector->detect(curr_gray, curr_keypoints);
        
        if (prev_keypoints.empty() || curr_keypoints.empty()) {
            stabilized_frame = frame.clone();
            return;
        }
        
        // Extract descriptors
        extractor->compute(prev_gray, prev_keypoints, prev_descriptors);
        extractor->compute(curr_gray, curr_keypoints, curr_descriptors);
        
        // Match features
        std::vector<std::vector<cv::DMatch>> knn_matches;
        matcher->knnMatch(prev_descriptors, curr_descriptors, knn_matches, 2);
        
        // Filter good matches using ratio test
        std::vector<cv::DMatch> good_matches;
        for (const auto& match : knn_matches) {
            if (match.size() == 2 && match[0].distance < 0.7 * match[1].distance) {
                good_matches.push_back(match[0]);
            }
        }
        
        if (good_matches.size() < 4) {
            stabilized_frame = frame.clone();
            return;
        }
        
        // Extract matched points
        std::vector<cv::Point2f> matched_prev, matched_curr;
        for (const auto& match : good_matches) {
            matched_prev.push_back(prev_keypoints[match.queryIdx].pt);
            matched_curr.push_back(curr_keypoints[match.trainIdx].pt);
        }
        
        // Estimate homography
        cv::Mat homography = cv::findHomography(matched_prev, matched_curr, cv::RANSAC);
        
        if (!homography.empty()) {
            // Decompose homography to get rotation and translation
            std::vector<cv::Mat> rotations, translations, normals;
            cv::decomposeHomographyMat(homography, cameraMatrix, rotations, translations, normals);
            
            if (!rotations.empty() && !translations.empty()) {
                // Use the first solution
                cv::Mat R = rotations[0];
                cv::Mat t = translations[0];
                
                // Create stabilization transform
                cv::Mat stabilization_transform = cv::Mat::eye(3, 3, CV_64F);
                stabilization_transform(cv::Rect(0, 0, 3, 3)) = R.inv() * 0.8;
                stabilization_transform.at<double>(0, 2) = -t.at<double>(0) * 0.5;
                stabilization_transform.at<double>(1, 2) = -t.at<double>(1) * 0.5;
                
                // Apply transformation
                cv::warpPerspective(frame, stabilized_frame, stabilization_transform, frame.size());
            } else {
                stabilized_frame = frame.clone();
            }
        } else {
            stabilized_frame = frame.clone();
        }
    }
    
    void stabilizeGyroscopeSimulation() {
        // Simulate gyroscope-based stabilization
        static cv::Mat gyro_data = cv::Mat::zeros(3, 1, CV_64F);
        
        if (prev_gray.empty()) {
            stabilized_frame = frame.clone();
            return;
        }
        
        // Simulate gyroscope readings (in real implementation, these would come from IMU)
        std::random_device rd;
        std::mt19937 gen(rd());
        std::normal_distribution<double> noise(0, 0.1);
        
        gyro_data.at<double>(0) += noise(gen);  // Roll
        gyro_data.at<double>(1) += noise(gen);  // Pitch
        gyro_data.at<double>(2) += noise(gen);  // Yaw
        
        // Apply smoothing to gyro data
        cv::Mat smoothed_gyro = gyro_data * 0.1;  // Low-pass filter
        
        // Create rotation matrix from gyro data
        cv::Mat R_x = (cv::Mat_<double>(3, 3) <<
            1, 0, 0,
            0, cos(smoothed_gyro.at<double>(0)), -sin(smoothed_gyro.at<double>(0)),
            0, sin(smoothed_gyro.at<double>(0)), cos(smoothed_gyro.at<double>(0)));
        
        cv::Mat R_y = (cv::Mat_<double>(3, 3) <<
            cos(smoothed_gyro.at<double>(1)), 0, sin(smoothed_gyro.at<double>(1)),
            0, 1, 0,
            -sin(smoothed_gyro.at<double>(1)), 0, cos(smoothed_gyro.at<double>(1)));
        
        cv::Mat R_z = (cv::Mat_<double>(3, 3) <<
            cos(smoothed_gyro.at<double>(2)), -sin(smoothed_gyro.at<double>(2)), 0,
            sin(smoothed_gyro.at<double>(2)), cos(smoothed_gyro.at<double>(2)), 0,
            0, 0, 1);
        
        cv::Mat R_total = R_z * R_y * R_x;
        
        // Convert to 2D transformation
        cv::Mat transform_2d = (cv::Mat_<double>(2, 3) <<
            R_total.at<double>(0, 0), R_total.at<double>(0, 1), 0,
            R_total.at<double>(1, 0), R_total.at<double>(1, 1), 0);
        
        // Apply transformation
        cv::warpAffine(frame, stabilized_frame, transform_2d, frame.size());
    }
    
    void stabilizeHybrid() {
        // Combine multiple stabilization methods
        cv::Mat optical_flow_result, feature_result;
        
        // Get optical flow stabilization
        StabilizationMode temp_mode = current_mode;
        current_mode = OPTICAL_FLOW;
        stabilizeOpticalFlow();
        optical_flow_result = stabilized_frame.clone();
        
        // Get feature-based stabilization
        current_mode = FEATURE_BASED;
        stabilizeFeatureBased();
        feature_result = stabilized_frame.clone();
        
        // Combine results with weighted average
        cv::addWeighted(optical_flow_result, 0.6, feature_result, 0.4, 0, stabilized_frame);
        
        current_mode = temp_mode;
    }
    
    void stabilizeTemporalFiltering() {
        // Add frame to buffer
        frame_buffer.push_back(frame.clone());
        if (frame_buffer.size() > buffer_size) {
            frame_buffer.pop_front();
        }
        
        if (frame_buffer.size() < 3) {
            stabilized_frame = frame.clone();
            return;
        }
        
        // Apply temporal filtering
        stabilized_frame = cv::Mat::zeros(frame.size(), frame.type());
        
        for (size_t i = 0; i < frame_buffer.size(); i++) {
            double weight = 1.0 / frame_buffer.size();
            cv::addWeighted(stabilized_frame, 1.0, frame_buffer[i], weight, 0, stabilized_frame);
        }
    }
    
    void stabilizeMotionCompensation() {
        if (prev_gray.empty()) {
            stabilized_frame = frame.clone();
            return;
        }
        
        // Calculate global motion using template matching
        cv::Mat motion = cv::Mat::zeros(2, 3, CV_64F);
        
        // Use template matching to find motion
        cv::Mat result;
        cv::matchTemplate(curr_gray, prev_gray(cv::Rect(50, 50, prev_gray.cols-100, prev_gray.rows-100)), 
                         result, cv::TM_CCOEFF_NORMED);
        
        cv::Point min_loc, max_loc;
        double min_val, max_val;
        cv::minMaxLoc(result, &min_val, &max_val, &min_loc, &max_loc);
        
        if (max_val > 0.8) {  // Good match found
            double dx = max_loc.x - 50;
            double dy = max_loc.y - 50;
            
            // Apply motion compensation
            motion.at<double>(0, 2) = -dx * 0.8;  // Compensate for motion
            motion.at<double>(1, 2) = -dy * 0.8;
            
            cv::warpAffine(frame, stabilized_frame, motion, frame.size());
        } else {
            stabilized_frame = frame.clone();
        }
    }
    
    void displayStabilizedVideo(bool& recording, cv::VideoWriter& writer) {
        // Create side-by-side comparison
        cv::Mat comparison;
        cv::hconcat(frame, stabilized_frame, comparison);
        
        // Add labels
        cv::putText(comparison, "Original", cv::Point(10, 30), 
                   cv::FONT_HERSHEY_SIMPLEX, 1, cv::Scalar(0, 255, 0), 2);
        cv::putText(comparison, "Stabilized", cv::Point(frame.cols + 10, 30), 
                   cv::FONT_HERSHEY_SIMPLEX, 1, cv::Scalar(0, 255, 0), 2);
        
        // Add mode information
        std::string mode_name = getModeName(current_mode);
        cv::putText(comparison, "Mode: " + mode_name, cv::Point(10, comparison.rows - 50), 
                   cv::FONT_HERSHEY_SIMPLEX, 0.7, cv::Scalar(255, 255, 255), 2);
        
        // Add recording indicator
        if (recording) {
            cv::circle(comparison, cv::Point(comparison.cols - 30, 30), 10, cv::Scalar(0, 0, 255), -1);
            cv::putText(comparison, "REC", cv::Point(comparison.cols - 80, 35), 
                       cv::FONT_HERSHEY_SIMPLEX, 0.6, cv::Scalar(0, 0, 255), 2);
        }
        
        cv::imshow("Video Stabilization", comparison);
        
        // Write to video if recording
        if (recording && writer.isOpened()) {
            writer.write(stabilized_frame);
        }
    }
    
    void startRecording(cv::VideoWriter& writer) {
        int fourcc = cv::VideoWriter::fourcc('M', 'J', 'P', 'G');
        double fps = cap.get(cv::CAP_PROP_FPS);
        cv::Size frame_size(stabilized_frame.cols, stabilized_frame.rows);
        
        writer.open("stabilized_video.avi", fourcc, fps > 0 ? fps : 30.0, frame_size);
    }
    
    void stopRecording(cv::VideoWriter& writer) {
        if (writer.isOpened()) {
            writer.release();
        }
    }
    
    void resetStabilization() {
        frame_buffer.clear();
        transform_buffer.clear();
        prev_points.clear();
        curr_points.clear();
        motion_history.clear();
        cumulative_transform = cv::Mat::eye(3, 3, CV_64F);
        prev_gray.release();
    }
    
    std::string getModeName(StabilizationMode mode) {
        switch (mode) {
            case OPTICAL_FLOW: return "Optical Flow";
            case FEATURE_BASED: return "Feature-based";
            case GYROSCOPE_SIMULATION: return "Gyroscope Simulation";
            case HYBRID_STABILIZATION: return "Hybrid Stabilization";
            case TEMPORAL_FILTERING: return "Temporal Filtering";
            case MOTION_COMPENSATION: return "Motion Compensation";
            default: return "Unknown";
        }
    }
};

// Global camera matrix for homography decomposition
cv::Mat cameraMatrix = (cv::Mat_<double>(3, 3) <<
    800, 0, 320,
    0, 800, 240,
    0, 0, 1);

int main() {
    try {
        VideoStabilizer stabilizer;
        stabilizer.runStabilization();
        
    } catch (const cv::Exception& e) {
        std::cout << "OpenCV Error: " << e.what() << std::endl;
        return -1;
    } catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << std::endl;
        return -1;
    }
    
    std::cout << "\nKey Features Demonstrated:" << std::endl;
    std::cout << "- Optical flow-based video stabilization" << std::endl;
    std::cout << "- Feature-based stabilization using ORB features" << std::endl;
    std::cout << "- Gyroscope simulation for IMU-based stabilization" << std::endl;
    std::cout << "- Hybrid stabilization combining multiple methods" << std::endl;
    std::cout << "- Temporal filtering for noise reduction" << std::endl;
    std::cout << "- Motion compensation using template matching" << std::endl;
    std::cout << "- Real-time stabilization with multiple algorithms" << std::endl;
    std::cout << "- Video recording of stabilized output" << std::endl;
    std::cout << "- Interactive mode switching and parameter adjustment" << std::endl;
    std::cout << "- Side-by-side comparison of original vs stabilized video" << std::endl;
    
    cv::destroyAllWindows();
    return 0;
}
