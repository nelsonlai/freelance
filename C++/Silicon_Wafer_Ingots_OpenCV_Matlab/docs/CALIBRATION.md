# Silicon Wafer Defect Detection - Camera Calibration Guide

## Overview

Camera calibration is essential for accurate defect detection and measurement in the Silicon Wafer Defect Detection System. This guide provides detailed procedures for calibrating both optical and infrared cameras.

## Calibration Types

### 1. Intrinsic Calibration
- **Purpose**: Correct for lens distortion and focal length variations
- **Parameters**: Camera matrix, distortion coefficients
- **Method**: Checkerboard pattern calibration

### 2. Extrinsic Calibration
- **Purpose**: Align multiple cameras or establish coordinate systems
- **Parameters**: Rotation and translation matrices
- **Method**: Multi-camera calibration with known reference points

### 3. Multi-Modal Calibration
- **Purpose**: Align optical and infrared images
- **Parameters**: Homography matrix
- **Method**: Feature-based alignment

## Prerequisites

### Hardware Requirements
- **Calibration Target**: Checkerboard pattern (printed or displayed)
- **Stable Mounting**: Secure camera mounting system
- **Good Lighting**: Consistent illumination conditions
- **Reference Objects**: Known size objects for scale calibration

### Software Requirements
- **OpenCV**: For camera calibration functions
- **MATLAB**: For calibration analysis and validation
- **Calibration Images**: Multiple images of calibration target

## Intrinsic Calibration Procedure

### Step 1: Prepare Calibration Target

1. **Checkerboard Pattern**:
   - Size: 8×6 or 10×7 squares
   - Square size: 25mm (adjust based on camera resolution)
   - High contrast: Black and white squares
   - Flat surface: No wrinkles or distortions

2. **Print Quality**:
   - High resolution printing (300+ DPI)
   - Matte finish to avoid reflections
   - Mount on rigid board

### Step 2: Capture Calibration Images

1. **Image Requirements**:
   - Minimum 20 images per camera
   - Different orientations and positions
   - Cover entire field of view
   - Include corners and edges

2. **Capture Settings**:
   - Fixed exposure and gain
   - Consistent lighting
   - Sharp focus
   - No motion blur

3. **Image Variations**:
   - Different distances (near/far)
   - Different angles (tilted views)
   - Different positions (corners, center)
   - Different rotations

### Step 3: Run Calibration

#### C++ Calibration Code

```cpp
#include <opencv2/opencv.hpp>
#include <opencv2/calib3d.hpp>

void calibrateCamera() {
    // Calibration parameters
    cv::Size boardSize(8, 6);
    float squareSize = 25.0f; // mm
    
    // Prepare object points
    std::vector<std::vector<cv::Point3f>> objectPoints;
    std::vector<std::vector<cv::Point2f>> imagePoints;
    
    // Generate 3D object points
    std::vector<cv::Point3f> objp;
    for (int i = 0; i < boardSize.height; i++) {
        for (int j = 0; j < boardSize.width; j++) {
            objp.push_back(cv::Point3f(j * squareSize, i * squareSize, 0));
        }
    }
    
    // Process calibration images
    std::vector<cv::String> imageFiles;
    cv::glob("calibration_images/*.png", imageFiles);
    
    for (const auto& filename : imageFiles) {
        cv::Mat image = cv::imread(filename);
        cv::Mat gray;
        cv::cvtColor(image, gray, cv::COLOR_BGR2GRAY);
        
        std::vector<cv::Point2f> corners;
        bool found = cv::findChessboardCorners(gray, boardSize, corners);
        
        if (found) {
            // Refine corner positions
            cv::cornerSubPix(gray, corners, cv::Size(11, 11), 
                            cv::Size(-1, -1), 
                            cv::TermCriteria(cv::TermCriteria::EPS + cv::TermCriteria::MAX_ITER, 30, 0.1));
            
            objectPoints.push_back(objp);
            imagePoints.push_back(corners);
        }
    }
    
    // Perform calibration
    cv::Mat cameraMatrix, distCoeffs;
    std::vector<cv::Mat> rvecs, tvecs;
    
    double rms = cv::calibrateCamera(objectPoints, imagePoints, 
                                   cv::Size(image.cols, image.rows),
                                   cameraMatrix, distCoeffs, rvecs, tvecs);
    
    // Save calibration results
    cv::FileStorage fs("camera_calibration.yml", cv::FileStorage::WRITE);
    fs << "camera_matrix" << cameraMatrix;
    fs << "distortion_coefficients" << distCoeffs;
    fs << "rms_error" << rms;
    fs.release();
    
    std::cout << "Calibration RMS error: " << rms << std::endl;
}
```

#### MATLAB Calibration Code

```matlab
function calibrateCameraMATLAB()
    % Calibration parameters
    boardSize = [8, 6];
    squareSize = 25; % mm
    
    % Load calibration images
    imageFiles = dir('calibration_images/*.png');
    
    % Prepare object points
    objPoints = generateCheckerboardPoints(boardSize, squareSize);
    
    % Detect corners in all images
    imagePoints = [];
    validImages = [];
    
    for i = 1:length(imageFiles)
        filename = fullfile('calibration_images', imageFiles(i).name);
        image = imread(filename);
        
        if size(image, 3) == 3
            image = rgb2gray(image);
        end
        
        [corners, isValid] = detectCheckerboardPoints(image, boardSize);
        
        if isValid
            imagePoints = [imagePoints; corners];
            validImages = [validImages; i];
        end
    end
    
    % Perform calibration
    [cameraParams, ~, ~] = estimateCameraParameters(imagePoints, objPoints, ...
        'ImageSize', size(image));
    
    % Save calibration results
    save('camera_calibration.mat', 'cameraParams');
    
    % Display results
    fprintf('Calibration RMS error: %.3f pixels\n', cameraParams.MeanReprojectionError);
    fprintf('Valid images: %d/%d\n', length(validImages), length(imageFiles));
end
```

### Step 4: Validate Calibration

1. **Reprojection Error**:
   - RMS error < 1.0 pixels (good)
   - RMS error < 0.5 pixels (excellent)

2. **Visual Inspection**:
   - Undistort test images
   - Check for straight lines
   - Verify corner accuracy

3. **Measurement Accuracy**:
   - Measure known objects
   - Compare with actual dimensions
   - Calculate measurement error

## Multi-Modal Calibration

### Purpose
Align optical and infrared cameras for coordinated defect detection.

### Procedure

1. **Capture Synchronized Images**:
   - Same scene with both cameras
   - Include reference markers
   - Ensure good contrast in both modalities

2. **Feature Detection**:
   - Detect common features in both images
   - Use corner detection or template matching
   - Ensure sufficient feature points

3. **Homography Calculation**:
   - Calculate transformation matrix
   - Validate transformation accuracy
   - Test with multiple image pairs

#### MATLAB Multi-Modal Calibration

```matlab
function calibrateMultiModal()
    % Load image pairs
    opticalImage = imread('optical_reference.png');
    infraredImage = imread('infrared_reference.png');
    
    % Detect features
    opticalPoints = detectSURFFeatures(opticalImage);
    infraredPoints = detectSURFFeatures(infraredImage);
    
    % Extract features
    [opticalFeatures, opticalValidPoints] = extractFeatures(opticalImage, opticalPoints);
    [infraredFeatures, infraredValidPoints] = extractFeatures(infraredImage, infraredPoints);
    
    % Match features
    indexPairs = matchFeatures(opticalFeatures, infraredFeatures);
    
    % Extract matched points
    opticalMatchedPoints = opticalValidPoints(indexPairs(:, 1));
    infraredMatchedPoints = infraredValidPoints(indexPairs(:, 2));
    
    % Calculate homography
    [homography, inlierIndex] = estimateGeometricTransform(...
        infraredMatchedPoints, opticalMatchedPoints, 'projective');
    
    % Save calibration
    save('multi_modal_calibration.mat', 'homography');
    
    % Validate calibration
    validateMultiModalCalibration(opticalImage, infraredImage, homography);
end
```

## Scale Calibration

### Purpose
Establish pixel-to-millimeter conversion for accurate measurements.

### Procedure

1. **Reference Object**:
   - Use object with known dimensions
   - High contrast edges
   - Stable positioning

2. **Measurement**:
   - Measure object in pixels
   - Calculate conversion factor
   - Validate with multiple objects

#### Scale Calibration Code

```matlab
function calibrateScale()
    % Load reference image
    image = imread('scale_reference.png');
    
    % Known object dimensions (mm)
    knownWidth = 10.0; % mm
    knownHeight = 10.0; % mm
    
    % Measure object in pixels
    % (This would typically involve manual selection or automatic detection)
    pixelWidth = 100; % pixels
    pixelHeight = 100; % pixels
    
    % Calculate scale factors
    scaleX = knownWidth / pixelWidth; % mm/pixel
    scaleY = knownHeight / pixelHeight; % mm/pixel
    
    % Save scale calibration
    scaleCalibration = struct();
    scaleCalibration.scaleX = scaleX;
    scaleCalibration.scaleY = scaleY;
    scaleCalibration.unit = 'mm/pixel';
    
    save('scale_calibration.mat', 'scaleCalibration');
    
    fprintf('Scale calibration:\n');
    fprintf('X scale: %.4f mm/pixel\n', scaleX);
    fprintf('Y scale: %.4f mm/pixel\n', scaleY);
end
```

## Calibration Validation

### 1. Reprojection Error Analysis

```matlab
function validateCalibration()
    % Load calibration results
    load('camera_calibration.mat');
    
    % Test with new images
    testImages = dir('test_images/*.png');
    
    totalError = 0;
    validTests = 0;
    
    for i = 1:length(testImages)
        filename = fullfile('test_images', testImages(i).name);
        image = imread(filename);
        
        % Detect corners
        [corners, isValid] = detectCheckerboardPoints(image, [8, 6]);
        
        if isValid
            % Calculate reprojection error
            reprojectedPoints = projectPoints(objPoints, cameraParams, corners);
            error = sqrt(mean((corners - reprojectedPoints).^2));
            
            totalError = totalError + error;
            validTests = validTests + 1;
            
            fprintf('Image %d: RMS error = %.3f pixels\n', i, error);
        end
    end
    
    if validTests > 0
        averageError = totalError / validTests;
        fprintf('Average RMS error: %.3f pixels\n', averageError);
        
        if averageError < 0.5
            fprintf('Calibration quality: Excellent\n');
        elseif averageError < 1.0
            fprintf('Calibration quality: Good\n');
        else
            fprintf('Calibration quality: Poor - recalibration recommended\n');
        end
    end
end
```

### 2. Measurement Accuracy Test

```matlab
function testMeasurementAccuracy()
    % Load scale calibration
    load('scale_calibration.mat');
    
    % Test objects with known dimensions
    testObjects = [
        5.0, 5.0;   % 5mm x 5mm
        10.0, 10.0; % 10mm x 10mm
        15.0, 15.0; % 15mm x 15mm
    ];
    
    for i = 1:size(testObjects, 1)
        % Load test image
        filename = sprintf('test_object_%d.png', i);
        image = imread(filename);
        
        % Measure object (pixels)
        % (This would involve actual measurement code)
        measuredPixels = [100, 100]; % Example values
        
        % Convert to millimeters
        measuredMM = measuredPixels .* [scaleCalibration.scaleX, scaleCalibration.scaleY];
        
        % Calculate error
        actualMM = testObjects(i, :);
        error = abs(measuredMM - actualMM);
        errorPercent = (error ./ actualMM) * 100;
        
        fprintf('Object %d:\n', i);
        fprintf('  Actual: %.2f x %.2f mm\n', actualMM(1), actualMM(2));
        fprintf('  Measured: %.2f x %.2f mm\n', measuredMM(1), measuredMM(2));
        fprintf('  Error: %.2f x %.2f mm (%.1f%%)\n', error(1), error(2), mean(errorPercent));
    end
end
```

## Troubleshooting

### Common Calibration Issues

1. **High Reprojection Error**:
   - Check image quality and focus
   - Ensure sufficient image variety
   - Verify checkerboard pattern quality
   - Increase number of calibration images

2. **Poor Multi-Modal Alignment**:
   - Ensure good feature detection
   - Use robust feature matching
   - Validate with multiple image pairs
   - Check for camera movement

3. **Inaccurate Measurements**:
   - Verify scale calibration
   - Check reference object dimensions
   - Ensure proper lighting
   - Validate measurement procedure

### Calibration Quality Guidelines

- **RMS Error**: < 0.5 pixels (excellent), < 1.0 pixels (good)
- **Measurement Accuracy**: < 2% error for known objects
- **Multi-Modal Alignment**: < 1 pixel registration error
- **Calibration Images**: Minimum 20 images per camera

## Maintenance

### Regular Calibration Checks

1. **Monthly**: Verify measurement accuracy
2. **Quarterly**: Full recalibration if needed
3. **After Hardware Changes**: Immediate recalibration
4. **When Accuracy Degrades**: Investigate and recalibrate

### Calibration Storage

- Store calibration files in `config/calibration/`
- Include calibration date and camera information
- Maintain backup copies
- Document calibration procedures and results
