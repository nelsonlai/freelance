# Silicon Ingot Defect Detection - Algorithms Documentation

## Table of Contents
1. [Overview](#overview)
2. [Image Preprocessing Algorithms](#image-preprocessing-algorithms)
3. [Deep Learning Model Architecture](#deep-learning-model-architecture)
4. [Defect Classification Algorithms](#defect-classification-algorithms)
5. [Real-time Processing Pipeline](#real-time-processing-pipeline)
6. [Data Augmentation Strategies](#data-augmentation-strategies)
7. [Performance Optimization Techniques](#performance-optimization-techniques)
8. [Mathematical Foundations](#mathematical-foundations)

## Overview

This document provides detailed algorithmic descriptions for the silicon ingot defect detection system. The system combines computer vision preprocessing with deep learning classification to identify 8 different types of defects in silicon wafer ingots in real-time.

### System Architecture Flow
```
Camera Input → Preprocessing → MATLAB Inference → Post-processing → Visualization
     ↓              ↓              ↓              ↓              ↓
  Raw Frame → Enhanced Image → CNN Classification → Defect Report → Live Display
```

## Image Preprocessing Algorithms

### 1. Region of Interest (ROI) Extraction

**Algorithm**: Rectangular ROI Selection
```cpp
// ROI extraction algorithm
cv::Rect roi(roi_x, roi_y, roi_width, roi_height);
cv::Mat roi_image = input_image(roi).clone();
```

**Purpose**: Focus processing on the ingot surface area, reducing computational load and improving accuracy.

**Mathematical Foundation**:
- ROI coordinates: `(x, y, width, height)`
- Validation: `x ≥ 0, y ≥ 0, x + width ≤ image_width, y + height ≤ image_height`

### 2. Noise Reduction - Bilateral Filter

**Algorithm**: Bilateral Filtering
```cpp
cv::bilateralFilter(input, output, d=9, sigmaColor=75, sigmaSpace=75);
```

**Mathematical Formula**:
```
BF[I]p = (1/Wp) * Σ(q∈S) Gr(||I(p) - I(q)||) * Gs(||p - q||) * I(q)
```

Where:
- `Gr(||I(p) - I(q)||) = exp(-||I(p) - I(q)||²/(2σr²))` - Range kernel
- `Gs(||p - q||) = exp(-||p - q||²/(2σs²))` - Spatial kernel
- `Wp = Σ(q∈S) Gr(||I(p) - I(q)||) * Gs(||p - q||)` - Normalization factor

**Advantages**:
- Preserves edges while reducing noise
- Non-linear filtering approach
- Adaptive to local image characteristics

### 3. Contrast Enhancement - CLAHE (Contrast Limited Adaptive Histogram Equalization)

**Algorithm**: CLAHE Implementation
```cpp
cv::Ptr<cv::CLAHE> clahe = cv::createCLAHE(clip_limit=2.0, tileGridSize=(8,8));
clahe->apply(input_image, output_image);
```

**Mathematical Process**:

1. **Image Tiling**: Divide image into 8×8 tiles
2. **Histogram Calculation**: Compute histogram for each tile
3. **Clipping**: Limit histogram bins to `clip_limit * (total_pixels / num_bins)`
4. **Redistribution**: Redistribute clipped pixels across all bins
5. **Cumulative Distribution Function (CDF)**:
   ```
   CDF(i) = Σ(j=0 to i) histogram[j]
   ```
6. **Normalization**: 
   ```
   normalized_CDF(i) = CDF(i) / total_pixels * max_intensity
   ```
7. **Interpolation**: Bilinear interpolation between tile boundaries

**Advantages**:
- Prevents over-amplification of noise
- Maintains local contrast characteristics
- Better than global histogram equalization

### 4. Image Normalization

**Algorithm**: Min-Max Normalization
```cpp
// Convert to float and normalize to [0, 1]
input.convertTo(output, CV_32F, 1.0 / 255.0);
```

**Mathematical Formula**:
```
I_normalized = (I - I_min) / (I_max - I_min)
```

**For Neural Network Input**:
```
I_nn = I_normalized * 2.0 - 1.0  // Normalize to [-1, 1] for some models
```

### 5. Image Resizing

**Algorithm**: Bilinear Interpolation
```cpp
cv::resize(input, output, cv::Size(224, 224), 0, 0, cv::INTER_LINEAR);
```

**Mathematical Formula**:
For resizing from `(W₁, H₁)` to `(W₂, H₂)`:

```
x_ratio = W₁ / W₂
y_ratio = H₁ / H₂

for each pixel (i, j) in output:
    x = i * x_ratio
    y = j * y_ratio
    
    x₁ = floor(x), x₂ = ceil(x)
    y₁ = floor(y), y₂ = ceil(y)
    
    // Bilinear interpolation
    f(x,y) = f(x₁,y₁)(x₂-x)(y₂-y) + f(x₂,y₁)(x-x₁)(y₂-y) +
             f(x₁,y₂)(x₂-x)(y-y₁) + f(x₂,y₂)(x-x₁)(y-y₁)
```

## Deep Learning Model Architecture

### 1. ResNet-18 Transfer Learning

**Base Architecture**: ResNet-18
```matlab
net = resnet18('Weights', 'imagenet');
```

**ResNet Block Structure**:
```
Input → Conv → BatchNorm → ReLU → Conv → BatchNorm → Add → ReLU → Output
  ↓                                                                    ↑
  └─────────────────── Skip Connection ──────────────────────────────┘
```

**Mathematical Representation**:
```
y = F(x, {Wi}) + x
```

Where:
- `F(x, {Wi})` represents the residual mapping
- `x` is the identity mapping (skip connection)
- `Wi` are the weights of the residual block

### 2. Modified Classification Head

**Algorithm**: Layer Replacement
```matlab
% Replace final layers for defect classification
newFCLayer = fullyConnectedLayer(numClasses, 'Name', 'fc_defects');
newSoftmaxLayer = softmaxLayer('Name', 'softmax');
newClassLayer = classificationLayer('Name', 'classoutput');
```

**Mathematical Process**:

1. **Feature Extraction**: ResNet-18 extracts 512-dimensional features
2. **Fully Connected Layer**:
   ```
   z = W * x + b
   ```
   Where `W` is 8×512 weight matrix, `b` is bias vector
3. **Softmax Activation**:
   ```
   P(class_i) = exp(z_i) / Σ(j=1 to 8) exp(z_j)
   ```
4. **Classification**: `predicted_class = argmax(P(class_i))`

### 3. Transfer Learning Strategy

**Frozen Layers**: Early layers (conv1, res2a, res2b, res3a, res3b, res4a, res4b)
**Trainable Layers**: res4b, res5a, res5b, fc_defects, softmax, classoutput

**Learning Rate Strategy**:
```
lr_frozen = 0
lr_trainable = 0.001
lr_fc = 0.01  // Higher learning rate for new classification layer
```

## Defect Classification Algorithms

### 1. Multi-Class Classification

**Defect Classes**:
1. Oxygen precipitation / stacking faults
2. Dislocations
3. Vacancy defects (voids/pits)
4. Interstitial defects (dislocation loops)
5. Microvoids / COPs
6. Slip lines / cracks
7. Dopant nonuniformity
8. Normal (no defect)

**Classification Algorithm**:
```matlab
function [classLabel, confidence] = classify_defect(imgArray)
    % Preprocess image
    img = preprocess_image(imgArray);
    
    % Run inference
    [label, scores] = classify(trainedModel, img);
    
    % Return results
    classLabel = string(label);
    confidence = max(scores);
end
```

### 2. Confidence Threshold Filtering

**Algorithm**: Binary Decision Making
```cpp
bool is_defect = confidence >= confidence_threshold;
```

**Mathematical Formula**:
```
Decision = {
    Defect Detected,    if max(P(class_i)) ≥ threshold
    Normal,            if max(P(class_i)) < threshold
}
```

**Threshold Optimization**:
- Default: 0.75
- Adjustable based on precision/recall requirements
- ROC curve analysis for optimal threshold selection

### 3. Defect-Specific Feature Detection

#### Oxygen Precipitation Detection
**Visual Features**:
- Dark circular/irregular spots
- Clustered distribution
- Size range: 1-50 μm

**Detection Algorithm**:
```cpp
// Blob detection for oxygen precipitates
cv::SimpleBlobDetector detector;
std::vector<cv::KeyPoint> keypoints;
detector.detect(image, keypoints);
```

#### Dislocation Detection
**Visual Features**:
- Linear features with consistent width
- Random orientation
- High contrast edges

**Detection Algorithm**:
```cpp
// Line detection using Hough transform
cv::HoughLinesP(image, lines, 1, CV_PI/180, threshold, minLineLength, maxLineGap);
```

**Mathematical Foundation**:
```
ρ = x*cos(θ) + y*sin(θ)
```

Where:
- `ρ` is the distance from origin to line
- `θ` is the angle of the line normal

#### Vacancy Defect Detection
**Visual Features**:
- Dark circular pits
- Well-defined boundaries
- Shadow effects

**Detection Algorithm**:
```cpp
// Circular Hough transform for vacancy detection
cv::HoughCircles(image, circles, CV_HOUGH_GRADIENT, 1, minDist, param1, param2, minRadius, maxRadius);
```

## Real-time Processing Pipeline

### 1. Frame Processing Strategy

**Algorithm**: Selective Frame Processing
```cpp
if (frame_count % process_every_n_frames == 0) {
    // Process frame for defect detection
    classifyDefect(frame, result);
}
```

**Performance Optimization**:
- Process every Nth frame to maintain real-time performance
- Default: N = 3 (process every 3rd frame)
- Configurable based on system performance

### 2. Asynchronous Processing Pipeline

**Pipeline Stages**:
1. **Capture**: Camera frame acquisition
2. **Preprocessing**: Image enhancement and normalization
3. **Inference**: MATLAB deep learning classification
4. **Post-processing**: Result interpretation and logging
5. **Visualization**: Overlay rendering and display

**Timing Analysis**:
```
Total Processing Time = T_capture + T_preprocess + T_inference + T_postprocess + T_visualize
Target: < 100ms per frame
```

### 3. Memory Management

**Algorithm**: Circular Buffer for Processing Times
```cpp
processing_times_.push_back(processing_time);
if (processing_times_.size() > MAX_PROCESSING_TIMES) {
    processing_times_.erase(processing_times_.begin());
}
```

**Memory Optimization**:
- Reuse image buffers
- Limit processing time history to last 100 measurements
- Efficient MATLAB array conversion

## Data Augmentation Strategies

### 1. Geometric Transformations

**Rotation**:
```matlab
imageAugmenter = imageDataAugmenter('RandRotation', [-15, 15]);
```

**Mathematical Transformation**:
```
[x']   [cos(θ) -sin(θ)] [x]
[y'] = [sin(θ)  cos(θ)] [y]
```

**Translation**:
```matlab
imageAugmenter = imageDataAugmenter('RandXTranslation', [-10, 10], 'RandYTranslation', [-10, 10]);
```

**Scaling**:
```matlab
imageAugmenter = imageDataAugmenter('RandXScale', [0.9, 1.1], 'RandYScale', [0.9, 1.1]);
```

### 2. Photometric Transformations

**Brightness Adjustment**:
```matlab
imageAugmenter = imageDataAugmenter('RandBrightness', [-0.1, 0.1]);
```

**Mathematical Formula**:
```
I_new = I_original + brightness_offset
I_new = clamp(I_new, 0, 1)  // Ensure valid range
```

**Contrast Adjustment**:
```matlab
imageAugmenter = imageDataAugmenter('RandContrast', [0.8, 1.2]);
```

**Mathematical Formula**:
```
I_new = contrast_factor * (I_original - 0.5) + 0.5
```

### 3. Synthetic Data Generation

**Algorithm**: Augmentation for Minority Classes
```matlab
for genIdx = 1:numToGenerate
    % Randomly select existing image
    randImgIdx = randi(length(existingFiles));
    srcImgPath = fullfile(trainPath, className, existingFiles(randImgIdx).name);
    
    % Load and augment image
    img = imread(srcImgPath);
    img = imrotate(img, randi([-15, 15]));
    img = imresize(img, [224, 224]);
    
    % Random brightness/contrast adjustment
    img = img * (0.8 + 0.4 * rand()) + (0.1 * rand() - 0.05) * 255;
    img = max(0, min(255, img));
end
```

## Performance Optimization Techniques

### 1. GPU Acceleration

**MATLAB GPU Support**:
```matlab
options = trainingOptions('sgdm', ...
    'ExecutionEnvironment', 'gpu', ...
    'UseParallel', true);
```

**CUDA Integration**:
- Automatic GPU memory management
- Batch processing optimization
- Parallel computation for multiple images

### 2. Model Optimization

**Quantization**:
- Reduce model precision from FP32 to FP16
- Maintain accuracy while reducing memory usage
- Faster inference on compatible hardware

**Pruning**:
- Remove redundant connections
- Reduce model complexity
- Maintain performance with smaller model size

### 3. Pipeline Optimization

**Frame Skipping**:
```cpp
if (frame_count % process_every_n_frames == 0) {
    // Process frame
}
```

**Asynchronous Processing**:
- Separate capture and processing threads
- Queue-based frame management
- Non-blocking inference calls

## Mathematical Foundations

### 1. Convolutional Neural Networks

**Convolution Operation**:
```
(f * g)(t) = ∫ f(τ)g(t-τ)dτ
```

**Discrete 2D Convolution**:
```
(I * K)(i,j) = Σ(m)Σ(n) I(i-m, j-n)K(m,n)
```

### 2. Backpropagation Algorithm

**Gradient Calculation**:
```
∂L/∂w = ∂L/∂z * ∂z/∂w
```

**Weight Update**:
```
w_new = w_old - α * ∂L/∂w
```

Where `α` is the learning rate.

### 3. Loss Functions

**Cross-Entropy Loss**:
```
L = -Σ(i=1 to C) y_i * log(p_i)
```

Where:
- `y_i` is the true label (one-hot encoded)
- `p_i` is the predicted probability for class i
- `C` is the number of classes

### 4. Optimization Algorithms

**Stochastic Gradient Descent with Momentum (SGDM)**:
```
v_t = β * v_{t-1} + (1-β) * ∇L(θ_t)
θ_{t+1} = θ_t - α * v_t
```

Where:
- `β` is the momentum coefficient (typically 0.9)
- `α` is the learning rate
- `v_t` is the velocity at time t

### 5. Learning Rate Scheduling

**Piecewise Learning Rate**:
```
lr(t) = {
    lr_initial,           if t < T1
    lr_initial * 0.1,     if T1 ≤ t < T2
    lr_initial * 0.01,    if t ≥ T2
}
```

### 6. Batch Normalization

**Normalization**:
```
x̂ = (x - μ) / √(σ² + ε)
```

**Scale and Shift**:
```
y = γ * x̂ + β
```

Where:
- `μ` and `σ²` are batch mean and variance
- `γ` and `β` are learnable parameters
- `ε` is a small constant for numerical stability

## Implementation Notes

### 1. Error Handling

**MATLAB Engine Exception Handling**:
```cpp
try {
    matlab::data::Array result = engine->feval(u"classify_defect", args);
} catch (const matlab::engine::EngineException& e) {
    std::cerr << "MATLAB Engine Exception: " << e.what() << std::endl;
}
```

### 2. Memory Management

**Smart Pointer Usage**:
```cpp
std::unique_ptr<CameraCapture> camera;
std::shared_ptr<ImagePreprocessor> preprocessor;
```

**RAII (Resource Acquisition Is Initialization)**:
- Automatic resource cleanup
- Exception-safe code
- No memory leaks

### 3. Configuration Management

**YAML Configuration Validation**:
```cpp
bool validateParameter(const std::string& section, const std::string& key) {
    return config_[section] && config_[section][key];
}
```

### 4. Logging and Monitoring

**SQLite Database Schema**:
```sql
CREATE TABLE defects (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    timestamp TEXT NOT NULL,
    class_label TEXT NOT NULL,
    confidence REAL NOT NULL,
    processing_time_ms REAL NOT NULL,
    image_path TEXT
);
```

**Performance Metrics**:
- Processing time per frame
- Defect detection rate
- System throughput (FPS)
- Memory usage statistics

## Conclusion

This comprehensive algorithmic documentation covers all major components of the silicon ingot defect detection system. The combination of advanced computer vision preprocessing, deep learning classification, and real-time optimization techniques provides a robust solution for industrial defect detection applications.

The system's modular design allows for easy adaptation to different defect types and production environments, while the mathematical foundations ensure reliable and accurate performance in real-world applications.
