# C++ with MATLAB Camera Capture and Image Processing Project

This project contains 30 C++ programs with MATLAB integration for camera capture and image processing, organized from beginner to advanced levels.

## Project Structure

### Beginner Level (Programs 1-10)
- `camera_basic_01.cpp` - Basic camera capture and display
- `camera_basic_02.cpp` - Convert to grayscale
- `camera_basic_03.cpp` - Apply binary thresholding
- `camera_basic_04.cpp` - Perform Canny edge detection
- `camera_basic_05.cpp` - Apply Gaussian blur
- `camera_basic_06.cpp` - Resize an image
- `camera_basic_07.cpp` - Crop a region of interest
- `camera_basic_08.cpp` - Convert color space (BGR to HSV)
- `camera_basic_09.cpp` - Perform histogram equalization
- `camera_basic_10.cpp` - Combine multiple basic operations

### Intermediate Level (Programs 11-20)
- `camera_intermediate_11.cpp` - Perform morphological operations (erosion/dilation)
- `camera_intermediate_12.cpp` - Detect contours
- `camera_intermediate_13.cpp` - Implement feature detection (SIFT/SURF/ORB)
- `camera_intermediate_14.cpp` - Perform image alignment/registration
- `camera_intermediate_15.cpp` - Implement simple object tracking (mean-shift)
- `camera_intermediate_16.cpp` - Perform background subtraction
- `camera_intermediate_17.cpp` - Implement basic image segmentation (K-means)
- `camera_intermediate_18.cpp` - Apply custom convolution filters
- `camera_intermediate_19.cpp` - Perform advanced color manipulation
- `camera_intermediate_20.cpp` - Implement image stitching

### Advanced Level (Programs 21-30)
- `camera_advanced_21.cpp` - Implement real-time facial detection using Haar cascades
- `camera_advanced_22.cpp` - Advanced image stitching and panorama
- `camera_advanced_23.cpp` - Advanced object detection and recognition
- `camera_advanced_24.cpp` - Advanced 3D reconstruction and depth estimation
- `camera_advanced_25.cpp` - Advanced machine learning for computer vision
- `camera_advanced_26.cpp` - Advanced real-time video processing
- `camera_advanced_27.cpp` - Advanced augmented reality
- `camera_advanced_28.cpp` - Advanced motion analysis and tracking
- `camera_advanced_29.cpp` - Advanced image quality assessment
- `camera_advanced_30.cpp` - Advanced computer vision applications

## Prerequisites

### Required Software
1. **OpenCV 4.x** - Computer vision library
2. **MATLAB R2023b or later** - MATLAB Engine API for C++
3. **C++ Compiler** - GCC, Clang, or MSVC with C++17 support
4. **CMake** - Build system (optional)

### Installation Instructions

#### macOS
```bash
# Install OpenCV using Homebrew
brew install opencv

# Install MATLAB Engine API for C++
# Follow MATLAB installation instructions for your version
```

#### Ubuntu/Debian
```bash
# Install OpenCV
sudo apt-get update
sudo apt-get install libopencv-dev

# Install MATLAB Engine API for C++
# Follow MATLAB installation instructions for your version
```

#### Windows
```bash
# Install OpenCV using vcpkg
vcpkg install opencv

# Install MATLAB Engine API for C++
# Follow MATLAB installation instructions for your version
```

## Compilation

### Individual Program Compilation
```bash
# Example for camera_basic_01.cpp
g++ -std=c++17 camera_basic_01.cpp -o camera_basic_01 \
    `pkg-config --cflags --libs opencv4` \
    -I/Applications/MATLAB_R2023b.app/extern/include \
    -L/Applications/MATLAB_R2023b.app/bin/maci64 \
    -lMatlabDataArray -lMatlabEngine
```

### Using CMake
```bash
mkdir build
cd build
cmake ..
make
```

## Usage

### Running Programs
```bash
# Make sure your camera is connected
./camera_basic_01
./camera_intermediate_11
./camera_advanced_21
```

### Controls
Most programs support the following controls:
- `q` or `ESC` - Quit
- `m` - Send data to MATLAB
- `s` - Save current frame
- Additional controls vary by program

## Learning Objectives

### Beginner Level
- Understand basic camera operations
- Learn fundamental image processing techniques
- Understand color space conversions
- Learn basic filtering operations
- Understand MATLAB integration basics

### Intermediate Level
- Learn advanced image processing techniques
- Understand feature detection and matching
- Learn object tracking methods
- Understand image segmentation
- Learn advanced filtering techniques

### Advanced Level
- Understand deep learning applications
- Learn 3D reconstruction techniques
- Understand machine learning for computer vision
- Learn real-time processing optimization
- Understand augmented reality applications

## MATLAB Integration

All programs include MATLAB integration for:
- Data visualization
- Analysis and processing
- Result comparison
- Educational demonstrations

### MATLAB Requirements
- MATLAB R2023b or later
- MATLAB Engine API for C++
- Proper MATLAB installation with C++ support

## Troubleshooting

### Common Issues

1. **Camera not found**
   - Check camera permissions
   - Verify camera is connected
   - Try different camera indices (0, 1, 2, etc.)

2. **MATLAB Engine errors**
   - Verify MATLAB installation
   - Check MATLAB Engine API installation
   - Verify library paths

3. **OpenCV errors**
   - Check OpenCV installation
   - Verify library versions
   - Check linking flags

### Getting Help
- Check program comments for detailed explanations
- Review OpenCV documentation
- Review MATLAB Engine API documentation
- Check system logs for error messages

## Contributing

This is an educational project. Feel free to:
- Add new programs
- Improve existing code
- Add more detailed comments
- Suggest new features

## License

This project is for educational purposes. Please respect the licenses of:
- OpenCV
- MATLAB
- Any other dependencies

## Acknowledgments

- OpenCV community for excellent computer vision library
- MathWorks for MATLAB and Engine API
- Educational institutions for computer vision curriculum
- Contributors and students who use this project

## Contact

For questions or suggestions about this educational project, please refer to the program comments and documentation.
