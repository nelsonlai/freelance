# Silicon Ingot Defect Detection System - Setup Instructions

## Overview

This system uses C++ with OpenCV for real-time video capture and preprocessing, integrated with MATLAB Engine API for deep learning-based defect classification of silicon ingot surfaces.

## System Requirements

### Hardware
- **Camera**: USB camera or industrial camera with OpenCV support
- **CPU**: Multi-core processor (Intel i5 or equivalent minimum)
- **RAM**: 8GB minimum, 16GB recommended
- **GPU**: CUDA-capable GPU recommended for MATLAB training (optional for inference)
- **Storage**: 10GB free space for datasets and models

### Software Dependencies

#### C++ Dependencies
- **OpenCV 4.x**: Computer vision library
- **MATLAB Engine API**: For C++ ↔ MATLAB communication
- **yaml-cpp**: YAML configuration file parsing
- **CMake 3.15+**: Build system
- **C++17 compatible compiler**: GCC 7+, Clang 5+, or MSVC 2017+

#### MATLAB Dependencies
- **MATLAB R2020b or later**
- **Deep Learning Toolbox**: Required for neural network training
- **Computer Vision Toolbox**: Image processing functions
- **Image Processing Toolbox**: Additional image operations
- **Parallel Computing Toolbox**: Optional, for GPU acceleration

## Installation Steps

### 1. Install System Dependencies

#### Ubuntu/Debian
```bash
# Update package list
sudo apt update

# Install OpenCV and development tools
sudo apt install libopencv-dev cmake build-essential

# Install yaml-cpp
sudo apt install libyaml-cpp-dev

# Install MATLAB Engine API (requires MATLAB installation)
# Follow MATLAB installation instructions
```

#### macOS
```bash
# Install using Homebrew
brew install opencv cmake yaml-cpp

# Install MATLAB Engine API
# Follow MATLAB installation instructions
```

#### Windows
- Install Visual Studio 2019 or later with C++ development tools
- Install OpenCV using vcpkg or pre-built binaries
- Install yaml-cpp using vcpkg
- Install MATLAB with Engine API

### 2. MATLAB Setup

1. **Install MATLAB** with required toolboxes
2. **Set MATLAB_ROOT environment variable**:
   ```bash
   export MATLAB_ROOT=/path/to/matlab
   ```
3. **Verify MATLAB Engine API**:
   ```matlab
   % In MATLAB command window
   matlab.engine.shareEngine
   ```

### 3. Build the Project

```bash
# Navigate to project directory
cd Silicon_Ignot_Deeplearning

# Create build directory
mkdir build && cd build

# Configure with CMake
cmake ../cpp

# Build the project
make -j$(nproc)  # Linux/macOS
# or
cmake --build . --config Release  # Windows
```

### 4. Prepare Dataset

1. **Create labeled dataset**:
   ```bash
   # Place images in appropriate class directories
   data/labeled/class_1_oxygen/
   data/labeled/class_2_dislocations/
   data/labeled/class_3_vacancy/
   data/labeled/class_4_interstitial/
   data/labeled/class_5_microvoids/
   data/labeled/class_6_slip_cracks/
   data/labeled/class_7_dopant/
   data/labeled/class_8_normal/
   ```

2. **Run dataset preparation**:
   ```matlab
   % In MATLAB
   cd matlab/training
   prepare_dataset
   ```

### 5. Train the Model

```matlab
% In MATLAB
cd matlab/training
train_defect_classifier
```

This will:
- Create train/validation/test splits
- Generate synthetic data for minority classes
- Train ResNet-18 model with transfer learning
- Save trained model to `matlab/models/`

### 6. Configure the System

Edit `cpp/config.yaml` to match your setup:

```yaml
camera:
  device_id: 0          # Camera device ID
  width: 1920           # Camera resolution
  height: 1080
  fps: 30

preprocessing:
  roi_x: 200            # Region of interest
  roi_y: 150
  roi_width: 1520
  roi_height: 780
  target_size: 224      # Neural network input size
  clahe_clip_limit: 2.0

inference:
  matlab_script_path: "../matlab/inference"
  model_file: "defect_classifier_v1.mat"
  confidence_threshold: 0.75
  process_every_n_frames: 3

logging:
  db_path: "./defects.db"
  save_images: true
  image_output_dir: "./detections"
```

## Running the System

### 1. Start the Detection System

```bash
# From build directory
./bin/SiliconIngotDefectDetection

# Or with custom config
./bin/SiliconIngotDefectDetection /path/to/config.yaml
```

### 2. Camera Calibration (Optional)

For better accuracy, calibrate your camera:

```cpp
// In CameraCapture.cpp
cv::Mat camera_matrix, distortion_coeffs;
// Load calibration parameters
camera.setCalibration(camera_matrix, distortion_coeffs);
```

### 3. Monitor Output

The system displays:
- Live video feed with defect overlay
- Confidence bar
- Processing statistics
- Defect detection alerts

## Troubleshooting

### Common Issues

1. **MATLAB Engine not found**:
   - Verify MATLAB_ROOT environment variable
   - Check MATLAB Engine API installation
   - Ensure MATLAB is in system PATH

2. **Camera not detected**:
   - Check camera permissions
   - Verify device ID in config
   - Test with `cv::VideoCapture` directly

3. **Model loading fails**:
   - Ensure model file exists in `matlab/models/`
   - Check MATLAB path includes inference scripts
   - Verify model was trained successfully

4. **Poor detection accuracy**:
   - Increase training dataset size
   - Adjust confidence threshold
   - Check image preprocessing parameters
   - Verify ROI covers ingot surface

### Performance Optimization

1. **Reduce processing frequency**:
   ```yaml
   inference:
     process_every_n_frames: 5  # Process every 5th frame
   ```

2. **Optimize ROI**:
   - Set ROI to focus on ingot surface only
   - Reduce ROI size for faster processing

3. **GPU acceleration**:
   - Install CUDA toolkit
   - Enable GPU in MATLAB training options
   - Use Parallel Computing Toolbox

## Data Collection Guidelines

### Image Quality Requirements
- **Resolution**: Minimum 1920x1080
- **Lighting**: Uniform, shadow-free illumination
- **Focus**: Sharp focus on ingot surface
- **Stability**: Minimal camera vibration

### Labeling Guidelines
- **Oxygen precipitation**: Visible stacking faults, oxide precipitates
- **Dislocations**: Linear defects, slip lines
- **Vacancy defects**: Pits, voids, surface irregularities
- **Interstitial defects**: Dislocation loops, point defects
- **Microvoids/COPs**: Small circular defects, crystal-originated particles
- **Slip lines/cracks**: Linear cracks, mechanical damage
- **Dopant nonuniformity**: Color variations, resistivity changes
- **Normal**: Clean, defect-free surface

### Dataset Size Recommendations
- **Minimum**: 200 images per class
- **Recommended**: 500+ images per class
- **Training split**: 70%
- **Validation split**: 15%
- **Test split**: 15%

## Maintenance

### Regular Tasks
1. **Retrain model** with new production data (monthly)
2. **Update calibration** if camera position changes
3. **Monitor performance** metrics and adjust thresholds
4. **Clean camera lens** and lighting system
5. **Backup trained models** and configuration files

### System Updates
1. **Update OpenCV** for latest features and bug fixes
2. **Update MATLAB** toolboxes for improved algorithms
3. **Monitor system logs** for error patterns
4. **Performance profiling** to identify bottlenecks

## Support

For technical support:
1. Check system logs in `./detections/` directory
2. Verify all dependencies are correctly installed
3. Test individual components (camera, MATLAB Engine, model)
4. Review configuration parameters
5. Consult MATLAB and OpenCV documentation

## License

This system is designed for industrial silicon ingot defect detection. Ensure compliance with your organization's software licensing requirements for MATLAB and other dependencies.
