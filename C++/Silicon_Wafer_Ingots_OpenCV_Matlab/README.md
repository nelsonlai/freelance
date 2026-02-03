# Silicon Wafer Defect Detection System

A comprehensive solution for detecting and analyzing defects in silicon wafer ingots produced using the Czochralski (CZ) method.

## 🎯 Overview

This system combines C++ image capture capabilities with MATLAB-based traditional computer vision algorithms to provide detailed defect analysis for silicon wafer ingots.

## 🏗️ System Architecture

- **C++ Image Acquisition Module**: Captures optical microscopy and infrared images using OpenCV
- **MATLAB Processing Module**: Performs defect detection and classification using traditional computer vision

## 🔍 Supported Defect Types

1. **Oxygen-Related Defects**: Precipitation clusters, stacking faults, thermal donors
2. **Thermal Stress Defects**: Dislocations, swirl patterns, warpage analysis
3. **Vacancy/Interstitial Defects**: Voids, microvoids, COPs
4. **Metallic Impurities**: Contamination site detection
5. **Slip Lines & Cracks**: Linear defect identification and topology analysis
6. **Dopant Nonuniformity**: Uniformity scoring and variation mapping

## 🚀 Quick Start

### 1. Build C++ Components
```bash
cd src/cpp
mkdir build
cd build
cmake ..
make
```

### 2. Configure Cameras
Edit `config/camera_config.json` to match your camera setup.

### 3. Capture Images
```bash
./wafer_defect_detection --output data/output --sample sample_001
```

### 4. Run Defect Detection
In MATLAB:
```matlab
main_defect_detection();
```

## 📁 Project Structure

```
Silicon_Wafer_Ingots/
├── src/
│   ├── cpp/                    # C++ image capture components
│   │   ├── CMakeLists.txt
│   │   ├── main.cpp
│   │   ├── camera_interface.h/cpp
│   │   ├── image_capture.h/cpp
│   │   └── preprocessor.h/cpp
│   └── matlab/                 # MATLAB detection algorithms
│       ├── main_defect_detection.m
│       ├── detect_*.m         # Individual detection functions
│       └── utils/             # Utility functions
├── config/                    # Configuration files
│   ├── detection_params.m
│   └── camera_config.json
├── docs/                      # Documentation
│   ├── USER_GUIDE.md
│   ├── ALGORITHM_REFERENCE.md
│   └── CALIBRATION.md
├── data/                      # Data directories
│   ├── sample_images/
│   └── output/
└── verify_system.sh          # System verification script
```

## 🔧 Requirements

### C++ Components
- OpenCV 4.x
- CMake 3.16+
- C++17 Compiler
- Camera drivers

### MATLAB Components
- MATLAB R2019b+
- Image Processing Toolbox
- Computer Vision Toolbox
- Signal Processing Toolbox

## 📊 Features

- **Multi-Modal Imaging**: Optical and infrared image processing
- **Traditional Computer Vision**: Classical CV algorithms optimized for silicon wafer analysis
- **Comprehensive Analysis**: Detailed defect characterization and visualization
- **Automated Reporting**: HTML/PDF report generation
- **Modular Design**: Easy to extend and customize
- **Robust Error Handling**: Graceful handling of edge cases

## 📖 Documentation

- **[User Guide](docs/USER_GUIDE.md)**: Complete usage instructions
- **[Algorithm Reference](docs/ALGORITHM_REFERENCE.md)**: Technical algorithm details
- **[Calibration Guide](docs/CALIBRATION.md)**: Camera calibration procedures

## ✅ Verification

Run the verification script to ensure all components are properly installed:

```bash
./verify_system.sh
```

## 🎉 Status

**All to-do items completed!** The system is ready for production use.

## 📝 License

This software is provided for research and educational purposes. Please refer to the license file for detailed terms and conditions.

---

**Silicon Wafer Defect Detection System** - Comprehensive defect analysis for Czochralski-grown silicon ingots.
