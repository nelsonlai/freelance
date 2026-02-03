# Silicon Wafer Defect Detection System - User Guide

## Overview

The Silicon Wafer Defect Detection System is a comprehensive solution for detecting and analyzing various types of defects in silicon wafer ingots produced using the Czochralski (CZ) method. The system combines C++ image capture capabilities with MATLAB-based traditional computer vision algorithms to provide detailed defect analysis.

## System Architecture

The system consists of two main components:

1. **C++ Image Acquisition Module** - Captures optical microscopy and infrared images using OpenCV
2. **MATLAB Processing Module** - Performs defect detection and classification using traditional computer vision

## Supported Defect Types

The system can detect and analyze the following defect types:

### 1. Oxygen-Related Defects
- **Oxygen Precipitation**: Dark precipitate clusters in IR images
- **Stacking Faults**: Linear fault patterns
- **Thermal Donors**: Indirect detection through resistivity variations

### 2. Thermal Stress-Induced Defects
- **Dislocations**: Slip lines and dislocation networks
- **Swirl Defects**: Rotational/circular patterns in IR images
- **Warpage/Bowing**: Surface deformation analysis

### 3. Vacancy & Interstitial Defects
- **Voids/Microvoids**: Dark void regions
- **COPs (Crystal-Originated Particles)**: Surface pits

### 4. Metallic Impurities
- **Contamination Sites**: Oxidation and contamination detection

### 5. Slip Lines & Cracks
- **Macro Defects**: Linear crack identification and analysis

### 6. Dopant Nonuniformity
- **Resistivity Variations**: Uniformity analysis and mapping

## Installation Requirements

### C++ Components
- **OpenCV 4.x**: Computer vision library
- **CMake 3.16+**: Build system
- **C++17 Compiler**: GCC, Clang, or MSVC
- **Camera Drivers**: For optical and IR cameras

### MATLAB Components
- **MATLAB R2019b+**: Image Processing Toolbox
- **Computer Vision Toolbox**: For advanced algorithms
- **Signal Processing Toolbox**: For FFT analysis

## Quick Start Guide

### 1. Build C++ Components

```bash
cd src/cpp
mkdir build
cd build
cmake ..
make
```

### 2. Configure Cameras

Edit `config/camera_config.json` to match your camera setup:

```json
{
  "camera_config": {
    "optical_camera": {
      "device_id": 0,
      "width": 1920,
      "height": 1080,
      "fps": 30
    },
    "infrared_camera": {
      "device_id": 1,
      "width": 640,
      "height": 480,
      "fps": 15
    }
  }
}
```

### 3. Capture Images

```bash
./wafer_defect_detection --output data/output --sample sample_001
```

### 4. Run Defect Detection

In MATLAB:

```matlab
% Load configuration
params = detection_params();

% Run detection
main_defect_detection('input_dir', 'data/output/processed', ...
                     'output_dir', 'data/output/results');
```

## Detailed Usage

### Image Capture

The C++ application supports several capture modes:

#### Single Capture Mode
```bash
./wafer_defect_detection --output data/output --sample sample_001
```

#### Continuous Capture Mode
```bash
./wafer_defect_detection --continuous --output data/output
```

#### Command Line Options
- `--output <dir>`: Output directory for captured images
- `--sample <id>`: Sample identifier
- `--no-preprocessing`: Skip preprocessing step
- `--continuous`: Continuous capture mode
- `--help`: Show help message

### MATLAB Defect Detection

#### Basic Usage
```matlab
main_defect_detection();
```

#### Advanced Usage
```matlab
main_defect_detection('input_dir', 'data/output/processed', ...
                     'output_dir', 'data/output/results', ...
                     'image_types', {'optical', 'infrared'}, ...
                     'detection_modules', {'oxygen', 'dislocation', 'swirl', 'void', 'crack', 'dopant'}, ...
                     'generate_report', true, ...
                     'save_results', true, ...
                     'visualize_results', true);
```

#### Individual Detection Functions

You can also run individual detection functions:

```matlab
% Oxygen precipitation detection
[precipitate_locations, size_distribution, density_map] = detect_oxygen_precipitation(ir_image);

% Dislocation detection
[dislocation_lines, dislocation_density, slip_patterns] = detect_dislocations(image);

% Swirl defect detection
[swirl_patterns, severity_score, orientation_field] = detect_swirl_defects(ir_image);

% Void and COP detection
[void_locations, void_sizes, cop_locations, cop_sizes] = detect_voids_cops(image);

% Crack detection
[crack_topology, crack_widths, crack_lengths] = detect_cracks(image);

% Dopant uniformity analysis
[uniformity_score, variation_maps, resistivity_profiles] = detect_dopant_variation(image);
```

## Configuration

### Detection Parameters

Edit `config/detection_params.m` to customize detection algorithms:

```matlab
params = detection_params();

% Modify oxygen precipitation detection
params.oxygen_precipitation.threshold_method = 'adaptive';
params.oxygen_precipitation.min_precipitate_size = 20;

% Modify dislocation detection
params.dislocation.edge_method = 'sobel';
params.dislocation.min_line_length = 15;
```

### Camera Configuration

Edit `config/camera_config.json` for camera settings:

```json
{
  "camera_config": {
    "optical_camera": {
      "device_id": 0,
      "width": 1920,
      "height": 1080,
      "fps": 30,
      "exposure_time": 100,
      "gain": 50
    }
  }
}
```

## Output Files

The system generates several types of output files:

### Image Files
- `data/output/optical/`: Optical microscopy images
- `data/output/infrared/`: Infrared images
- `data/output/processed/`: Preprocessed images
- `data/output/visualizations/`: Detection result overlays

### Results Files
- `data/output/results/detection_results_YYYYMMDD_HHMMSS.mat`: Complete detection results
- `data/output/results/defect_report_YYYYMMDD_HHMMSS.html`: HTML report
- `data/output/results/defect_report_YYYYMMDD_HHMMSS.pdf`: PDF report

### Log Files
- `data/output/logs/capture.log`: Capture system logs

## Troubleshooting

### Common Issues

#### Camera Not Detected
1. Check camera connections
2. Verify camera drivers are installed
3. Test camera with other applications
4. Check device IDs in configuration

#### Poor Detection Results
1. Verify image quality and resolution
2. Adjust detection parameters
3. Check lighting conditions
4. Ensure proper sample preparation

#### MATLAB Errors
1. Verify MATLAB toolbox licenses
2. Check file paths and permissions
3. Ensure sufficient memory available
4. Verify image file formats

### Performance Optimization

#### C++ Performance
- Use SSD storage for image capture
- Ensure sufficient RAM (8GB+ recommended)
- Use high-performance cameras
- Optimize camera settings

#### MATLAB Performance
- Use parallel processing for large datasets
- Optimize memory usage
- Use GPU acceleration if available
- Process images in batches

## Support

For technical support and questions:

1. Check the documentation in `docs/`
2. Review the algorithm reference in `docs/ALGORITHM_REFERENCE.md`
3. Check calibration procedures in `docs/CALIBRATION.md`
4. Contact the development team

## License

This software is provided for research and educational purposes. Please refer to the license file for detailed terms and conditions.
