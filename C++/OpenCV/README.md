# OpenCV C++ Learning Examples

A comprehensive collection of 20 OpenCV C++ programs designed for teaching computer vision concepts from beginner to advanced levels.

## 📚 Table of Contents

### Beginner Level (8 examples)
- **01_basic_image_load.cpp** - Basic image loading and display
- **02_camera_capture.cpp** - Webcam capture and basic video processing
- **03_color_spaces.cpp** - Color space conversions (BGR, HSV, LAB, YUV)
- **04_basic_drawing.cpp** - Drawing shapes and text on images
- **05_image_resize.cpp** - Image resizing and cropping techniques
- **06_basic_filters.cpp** - Basic image filtering (blur, edge detection, etc.)
- **07_mouse_interaction.cpp** - Mouse event handling and interactive drawing
- **08_image_operations.cpp** - Basic mathematical operations on images

### Intermediate Level (7 examples)
- **09_contour_detection.cpp** - Contour detection and shape analysis
- **10_histogram_analysis.cpp** - Histogram calculation and analysis
- **11_morphological_operations.cpp** - Morphological image processing
- **12_feature_detection.cpp** - Feature detection algorithms (Harris, FAST, ORB, SIFT)
- **13_template_matching.cpp** - Template matching for object detection
- **14_video_processing.cpp** - Real-time video processing with effects
- **15_geometric_transforms.cpp** - Geometric transformations and warping

### Advanced Level (5 examples)
- **16_object_tracking.cpp** - Object tracking using KCF algorithm
- **17_face_detection.cpp** - Face detection using Haar cascades
- **18_optical_flow.cpp** - Motion detection using optical flow
- **19_image_segmentation.cpp** - Advanced segmentation techniques
- **20_advanced_filters.cpp** - Advanced filtering and artistic effects

## 🛠️ Prerequisites

- **OpenCV 4.x** installed on your system
- **C++ Compiler** (GCC, Clang, or MSVC)
- **CMake** (optional, for building)
- **Webcam** (for camera-based examples)

## 📦 Installation

### macOS (Apple Silicon)
```bash
# Install OpenCV using Homebrew
brew install opencv

# For Apple Silicon Macs, you may need to use Rosetta
arch -x86_64 brew install opencv
```

### Ubuntu/Debian
```bash
sudo apt update
sudo apt install libopencv-dev
```

### Windows
1. Download OpenCV from [opencv.org](https://opencv.org/releases/)
2. Extract and set environment variables
3. Configure your IDE to use OpenCV

## 🔧 Compilation

### Method 1: Using the provided script (Recommended)
```bash
# Make the script executable
chmod +x compile.sh

# Compile any example
./compile.sh 01_basic_image_load.cpp

# Run the executable
arch -x86_64 ./01_basic_image_load
```

### Method 2: Manual compilation
```bash
# For Apple Silicon Macs (use Rosetta)
arch -x86_64 clang++ -std=c++17 filename.cpp $(pkg-config --cflags --libs opencv4) -o output

# For other systems
clang++ -std=c++17 filename.cpp $(pkg-config --cflags --libs opencv4) -o output
```

### Method 3: Using CMake
```bash
mkdir build
cd build
cmake ..
make
```

## 🚀 Running the Examples

### Basic Examples
```bash
# Image-based examples (requires image.jpg)
arch -x86_64 ./01_basic_image_load
arch -x86_64 ./03_color_spaces
arch -x86_64 ./05_image_resize

# Camera-based examples
arch -x86_64 ./02_camera_capture
arch -x86_64 ./14_video_processing
arch -x86_64 ./16_object_tracking
```

### Interactive Examples
- **Mouse Interaction**: Click and drag to draw, right-click for circles
- **Camera Examples**: Press number keys to switch between effects
- **Object Tracking**: Press 's' to select region, 'r' to reset

## 📖 Learning Path

### Week 1-2: Beginner Level
1. Start with `01_basic_image_load.cpp` to understand basic OpenCV structure
2. Learn camera capture with `02_camera_capture.cpp`
3. Explore color spaces with `03_color_spaces.cpp`
4. Practice drawing with `04_basic_drawing.cpp`
5. Understand image manipulation with `05_image_resize.cpp`
6. Apply basic filters with `06_basic_filters.cpp`
7. Add interactivity with `07_mouse_interaction.cpp`
8. Learn mathematical operations with `08_image_operations.cpp`

### Week 3-4: Intermediate Level
1. Master contour detection with `09_contour_detection.cpp`
2. Analyze histograms with `10_histogram_analysis.cpp`
3. Apply morphological operations with `11_morphological_operations.cpp`
4. Detect features with `12_feature_detection.cpp`
5. Implement template matching with `13_template_matching.cpp`
6. Process video streams with `14_video_processing.cpp`
7. Transform images geometrically with `15_geometric_transforms.cpp`

### Week 5-6: Advanced Level
1. Track objects with `16_object_tracking.cpp`
2. Detect faces with `17_face_detection.cpp`
3. Analyze motion with `18_optical_flow.cpp`
4. Segment images with `19_image_segmentation.cpp`
5. Apply advanced filters with `20_advanced_filters.cpp`

## 🎯 Key Concepts Covered

### Image Processing
- Loading, saving, and displaying images
- Color space conversions
- Image resizing and cropping
- Mathematical operations

### Computer Vision
- Edge detection and contour analysis
- Feature detection and matching
- Template matching
- Object tracking

### Video Processing
- Real-time camera capture
- Video effects and filters
- Motion detection
- Interactive applications

### Advanced Techniques
- Face detection
- Image segmentation
- Optical flow
- Advanced filtering

## 🐛 Troubleshooting

### Common Issues

1. **Architecture Mismatch (Apple Silicon)**
   ```bash
   # Use Rosetta for compilation and execution
   arch -x86_64 clang++ -std=c++17 file.cpp $(pkg-config --cflags --libs opencv4) -o output
   arch -x86_64 ./output
   ```

2. **OpenCV Not Found**
   ```bash
   # Check OpenCV installation
   pkg-config --cflags --libs opencv4
   
   # If not found, reinstall OpenCV
   brew install opencv
   ```

3. **Camera Not Working**
   - Check camera permissions
   - Try different camera indices (0, 1, 2)
   - Verify camera is not used by other applications

4. **Missing Image File**
   - Place `image.jpg` in the same directory as the executable
   - Or modify the code to use a different image path

### Performance Tips
- Use `cv::Mat::clone()` sparingly (expensive operation)
- Prefer `cv::Mat::copyTo()` for copying data
- Use appropriate data types (CV_8UC3 for color images)
- Consider using `cv::UMat` for GPU acceleration on supported systems

## 📚 Additional Resources

- [OpenCV Documentation](https://docs.opencv.org/)
- [OpenCV Tutorials](https://docs.opencv.org/master/d9/df8/tutorial_root.html)
- [Computer Vision: Algorithms and Applications](http://szeliski.org/Book/)
- [Learning OpenCV 4](https://www.oreilly.com/library/view/learning-opencv-4/9781492040034/)

## 🤝 Contributing

Feel free to contribute by:
- Adding new examples
- Improving existing code
- Fixing bugs
- Adding comments and documentation

## 📄 License

This project is for educational purposes. Feel free to use and modify the code for learning and teaching.

## 🙏 Acknowledgments

- OpenCV team for the excellent computer vision library
- The computer vision community for tutorials and examples
- Students and educators who provide feedback and suggestions

---

**Happy Learning! 🎓**
