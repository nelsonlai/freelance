# Advanced OpenCV C++ Programs Collection

This repository contains 30 comprehensive C++ programs demonstrating the power and capabilities of OpenCV, from beginner to advanced levels. Each program focuses on different aspects of computer vision and image processing.

## 🚀 Quick Start

### Prerequisites
- OpenCV 4.x installed on your system
- CMake 3.10 or higher
- C++17 compatible compiler
- Camera (for real-time programs)

### Building
```bash
mkdir build && cd build
cmake ..
make -j4
```

### Running Programs
```bash
# Run individual programs
./build/bin/01_basic_image_load
./build/bin/22_realtime_color_tracking

# Or use the provided scripts
./compile_all.sh
```

## 📚 Program Overview

### 🔰 Beginner Level (Programs 01-10)

#### 01_basic_image_load.cpp
- **Focus**: Basic image loading and display
- **Key Features**: File I/O, error handling, image information display
- **Learning**: Fundamental OpenCV operations

#### 02_camera_capture.cpp
- **Focus**: Real-time camera capture
- **Key Features**: Video capture, frame processing, real-time display
- **Learning**: Video input/output basics

#### 03_color_spaces.cpp
- **Focus**: Color space conversions
- **Key Features**: BGR, HSV, LAB conversions, color channel separation
- **Learning**: Color theory and conversions

#### 04_basic_drawing.cpp
- **Focus**: Drawing operations on images
- **Key Features**: Shapes, text, lines, filled objects
- **Learning**: Graphics primitives

#### 05_image_resize.cpp
- **Focus**: Image resizing and scaling
- **Key Features**: Interpolation methods, aspect ratio preservation
- **Learning**: Image geometry transformations

#### 06_basic_filters.cpp
- **Focus**: Basic image filtering
- **Key Features**: Blur, sharpen, edge detection
- **Learning**: Convolution and filtering

#### 07_mouse_interaction.cpp
- **Focus**: Mouse event handling
- **Key Features**: Interactive drawing, event callbacks
- **Learning**: User interaction

#### 08_image_operations.cpp
- **Focus**: Pixel-level operations
- **Key Features**: Arithmetic operations, bitwise operations
- **Learning**: Image algebra

#### 09_contour_detection.cpp
- **Focus**: Contour detection and analysis
- **Key Features**: Edge detection, contour finding, shape analysis
- **Learning**: Shape recognition basics

#### 10_histogram_analysis.cpp
- **Focus**: Histogram analysis
- **Key Features**: Histogram calculation, equalization, analysis
- **Learning**: Image statistics and enhancement

### 🔶 Intermediate Level (Programs 11-20)

#### 11_morphological_operations.cpp
- **Focus**: Morphological image processing
- **Key Features**: Erosion, dilation, opening, closing, gradient
- **Learning**: Binary image processing

#### 12_feature_detection.cpp
- **Focus**: Feature detection and description
- **Key Features**: Corner detection, SIFT, SURF, ORB features
- **Learning**: Feature extraction

#### 13_template_matching.cpp
- **Focus**: Template matching
- **Key Features**: Pattern recognition, similarity measures
- **Learning**: Object recognition basics

#### 14_video_processing.cpp
- **Focus**: Video analysis and processing
- **Key Features**: Frame analysis, motion detection, video effects
- **Learning**: Temporal analysis

#### 15_geometric_transforms.cpp
- **Focus**: Geometric transformations
- **Key Features**: Rotation, translation, scaling, perspective transforms
- **Learning**: 2D transformations

#### 16_object_tracking.cpp
- **Focus**: Object tracking algorithms
- **Key Features**: Kalman filter, mean shift, camshift tracking
- **Learning**: Motion tracking

#### 17_face_detection.cpp
- **Focus**: Face detection and recognition
- **Key Features**: Haar cascades, face landmarks, recognition
- **Learning**: Biometric analysis

#### 18_optical_flow.cpp
- **Focus**: Optical flow calculation
- **Key Features**: Lucas-Kanade, Farneback optical flow
- **Learning**: Motion estimation

#### 19_image_segmentation.cpp
- **Focus**: Image segmentation techniques
- **Key Features**: Watershed, grabcut, k-means segmentation
- **Learning**: Region analysis

#### 20_advanced_filters.cpp
- **Focus**: Advanced filtering techniques
- **Key Features**: Bilateral filter, non-local means, edge-preserving filters
- **Learning**: Advanced image enhancement

### 🔥 Advanced Level (Programs 21-30)

#### 21_advanced_image_stitching.cpp
- **Focus**: Image stitching and panorama creation
- **Key Features**: Feature matching, homography estimation, blending
- **Learning**: Multi-image fusion

#### 22_realtime_color_tracking.cpp
- **Focus**: Real-time color detection and tracking
- **Key Features**: HSV color space, morphological operations, trail visualization
- **Learning**: Real-time object tracking

#### 23_advanced_edge_detection.cpp
- **Focus**: Advanced edge detection algorithms
- **Key Features**: Canny, Sobel, Laplacian, Scharr, LoG, zero-crossing
- **Learning**: Edge analysis techniques

#### 24_3d_object_detection.cpp
- **Focus**: 3D object detection and pose estimation
- **Key Features**: PnP solving, ArUco markers, 3D rendering, camera calibration
- **Learning**: 3D computer vision

#### 25_advanced_image_blending.cpp
- **Focus**: Advanced image blending and composition
- **Key Features**: Alpha blending, pyramid blending, Poisson blending, seamless cloning
- **Learning**: Image composition

#### 26_machine_learning_kmeans.cpp
- **Focus**: Machine learning with OpenCV
- **Key Features**: K-means, SVM, Random Forest, KNN, Naive Bayes, Linear Regression
- **Learning**: ML integration

#### 27_advanced_camera_calibration.cpp
- **Focus**: Camera calibration and undistortion
- **Key Features**: Chessboard detection, intrinsic parameters, distortion correction
- **Learning**: Camera modeling

#### 28_realtime_ar_overlay.cpp
- **Focus**: Real-time augmented reality
- **Key Features**: Face detection AR, ArUco tracking, virtual objects, depth estimation
- **Learning**: AR applications

#### 29_advanced_video_stabilization.cpp
- **Focus**: Video stabilization techniques
- **Key Features**: Optical flow stabilization, feature-based, gyroscope simulation
- **Learning**: Video enhancement

#### 30_deep_learning_dnn.cpp
- **Focus**: Deep learning integration
- **Key Features**: YOLO, SSD, classification, segmentation, style transfer, pose estimation
- **Learning**: Neural network integration

## 🎯 Learning Path

### For Beginners
Start with programs 01-10 to understand basic OpenCV concepts:
1. Image loading and display
2. Camera capture
3. Color space conversions
4. Basic drawing and filtering

### For Intermediate Users
Progress to programs 11-20 for advanced techniques:
1. Feature detection and matching
2. Object tracking
3. Face detection
4. Video processing

### For Advanced Users
Explore programs 21-30 for cutting-edge applications:
1. Image stitching and AR
2. Machine learning integration
3. Deep learning applications
4. 3D computer vision

## 🛠️ Technical Features

### Real-time Processing
- Camera-based programs with live video feed
- Interactive controls and parameter adjustment
- Performance optimization techniques

### Advanced Algorithms
- State-of-the-art computer vision algorithms
- Machine learning integration
- Deep learning model deployment

### Comprehensive Documentation
- Detailed code comments
- Algorithm explanations
- Parameter descriptions
- Usage examples

## 📊 Performance Considerations

### Optimization Tips
- Use appropriate data types (CV_8U vs CV_32F)
- Minimize memory allocations in loops
- Utilize OpenCV's parallel processing
- Consider GPU acceleration for large datasets

### Hardware Requirements
- **Minimum**: 4GB RAM, integrated graphics
- **Recommended**: 8GB+ RAM, dedicated GPU
- **Optimal**: 16GB+ RAM, CUDA-compatible GPU

## 🔧 Troubleshooting

### Common Issues
1. **Camera not detected**: Check camera permissions and drivers
2. **Compilation errors**: Ensure OpenCV is properly installed
3. **Performance issues**: Reduce image resolution or use optimized algorithms

### Dependencies
- OpenCV modules: core, imgproc, imgcodecs, videoio, highgui, calib3d, features2d, objdetect, photo, stitching, aruco, ml, dnn
- Optional: CUDA for GPU acceleration

## 📈 Advanced Usage

### Customization
Each program is designed to be easily customizable:
- Modify parameters for different scenarios
- Add new features and algorithms
- Integrate with other libraries

### Integration
Programs can be combined for complex applications:
- Pipeline multiple algorithms
- Create real-time processing systems
- Build complete computer vision applications

## 🤝 Contributing

This collection is designed to be educational and extensible. Feel free to:
- Add new programs
- Improve existing implementations
- Fix bugs and optimize performance
- Add documentation and examples

## 📄 License

This educational collection is provided for learning purposes. Please respect OpenCV's license and any third-party model licenses when using pre-trained models.

## 🎓 Educational Value

This collection provides:
- **Progressive learning**: From basic to advanced concepts
- **Practical examples**: Real-world applications
- **Comprehensive coverage**: All major OpenCV capabilities
- **Best practices**: Clean, documented, efficient code
- **Interactive learning**: Hands-on experimentation

---

**Happy Learning! 🚀**

Explore the power of OpenCV and computer vision through these comprehensive examples. Each program is designed to teach specific concepts while building towards advanced applications in computer vision, machine learning, and artificial intelligence.
