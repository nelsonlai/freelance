# Halcon C++ Programming Examples

This repository contains 20 comprehensive C++ programs demonstrating Halcon machine vision capabilities, organized by difficulty level:

## Programs Overview

### Beginner Level (7 programs)
1. **halcon_basic_01** - Basic Image Loading and Display
2. **halcon_basic_02** - Image Conversion and Color Spaces  
3. **halcon_basic_03** - Basic Image Filtering
4. **halcon_basic_04** - Image Thresholding and Binary Operations
5. **halcon_basic_05** - Basic Geometric Operations
6. **halcon_basic_06** - Image Statistics and Analysis
7. **halcon_basic_07** - Image Saving and File Operations

### Intermediate Level (7 programs)
1. **halcon_intermediate_01** - Camera Acquisition and Live Display
2. **halcon_intermediate_02** - Advanced Image Segmentation
3. **halcon_intermediate_03** - Template Matching and Object Detection
4. **halcon_intermediate_04** - Blob Analysis and Feature Extraction
5. **halcon_intermediate_05** - Camera Calibration
6. **halcon_intermediate_06** - OCR and Text Recognition
7. **halcon_intermediate_07** - Image Registration and Alignment

### Advanced Level (6 programs)
1. **halcon_advanced_01** - 3D Vision and Stereo Reconstruction
2. **halcon_advanced_02** - Machine Learning and Classification
3. **halcon_advanced_03** - Deep Learning Integration
4. **halcon_advanced_04** - Advanced Morphology and Topology
5. **halcon_advanced_05** - Real-time Processing Pipeline
6. **halcon_advanced_06** - Industrial Vision System

## Prerequisites

- **Halcon 22.11** installed on your system (both runtime and development packages)
- **Valid Halcon license** (30-day trial or full license)
- **C++ compiler** (g++, clang++, or Visual Studio)
- **CMake** (optional, for CMake-based builds)

### Important Note
Halcon installations typically come in two packages:
1. **Runtime package** - for running Halcon applications
2. **Development package** - for compiling C++ programs with Halcon

Both packages are required for compilation. If you only have the runtime package, you'll need to install the development package separately.

## Installation

1. Install Halcon 22.11 from MVTec (both runtime and development packages)
2. Obtain a valid license file
3. Clone or download this repository
4. Ensure Halcon is properly installed and licensed

### Verifying Installation
Run the compilation script to check if everything is set up correctly:
```bash
./compile_single.sh halcon_basic_01
```

If you get an error about missing development files, you need to install the Halcon development package.

## Compilation

### Method 1: Using the compilation script (Recommended)
```bash
# Compile all programs
./compile_all.sh

# Compile individual program
./compile_single.sh halcon_basic_01
```

### Method 2: Using CMake
```bash
mkdir build
cd build
cmake ..
make
```

### Method 3: Manual compilation
```bash
g++ -std=c++11 -I"/Library/Application Support/HALCON-22.11/include" \
    -o halcon_basic_01 halcon_basic_01.cpp \
    -L"/Library/Application Support/HALCON-22.11/lib" -lhalcon
```

## Running the Programs

After compilation, run any program:
```bash
./halcon_basic_01
./halcon_intermediate_01
./halcon_advanced_01
```

## Program Features

### Beginner Programs
- Basic image I/O operations
- Image format conversions
- Simple filtering and enhancement
- Thresholding and binary operations
- Geometric transformations
- Statistical analysis
- File operations

### Intermediate Programs
- Camera integration and live capture
- Advanced segmentation techniques
- Template matching algorithms
- Feature extraction and analysis
- Camera calibration procedures
- OCR and text recognition
- Image registration methods

### Advanced Programs
- 3D vision and stereo reconstruction
- Machine learning integration
- Deep learning workflows
- Advanced morphological operations
- Real-time processing pipelines
- Complete industrial vision systems

## Troubleshooting

### Common Issues

1. **Halcon not found**
   - Ensure Halcon 22.11 is installed
   - Check the HALCON_ROOT path in scripts
   - Verify library and include paths

2. **License errors**
   - Ensure valid Halcon license is installed
   - Check license file permissions
   - Verify license is not expired

3. **Compilation errors**
   - Check C++ compiler version (C++11 required)
   - Verify Halcon library linking
   - Ensure all dependencies are installed

4. **Runtime errors**
   - Check image file paths
   - Verify camera connections (for camera programs)
   - Ensure proper permissions

### Getting Help

- Check Halcon documentation: `/Library/Application Support/HALCON-22.11/doc_en_US`
- Visit MVTec support: https://www.mvtec.com/support
- Review program comments for specific requirements

## License

These programs are provided as educational examples. Halcon software requires a valid license from MVTec.

## Contributing

Feel free to modify and extend these programs for your specific needs. Each program includes comprehensive comments explaining the Halcon operations used.
