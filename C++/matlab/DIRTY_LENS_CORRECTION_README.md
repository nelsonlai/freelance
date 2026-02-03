# Dirty Camera Lens Correction - Image Processing Algorithms

This project provides comprehensive solutions for correcting issues caused by dirty camera lenses using various image processing algorithms implemented in C++ with OpenCV and MATLAB integration.

## Table of Contents
- [Problem Description](#problem-description)
- [Algorithms Implemented](#algorithms-implemented)
- [Compilation Instructions](#compilation-instructions)
- [Usage](#usage)
- [MATLAB Analysis](#matlab-analysis)
- [Algorithm Details](#algorithm-details)
- [Performance Considerations](#performance-considerations)
- [Examples](#examples)

## Problem Description

Dirty camera lenses can cause several issues in captured images:

1. **Blur/Defocus**: Dust particles create soft focus effects
2. **Spots/Artifacts**: Visible dirt particles appear as dark spots
3. **Reduced Contrast**: Overall image quality degradation
4. **Uneven Illumination**: Dirt can cause vignetting or uneven lighting

## Algorithms Implemented

### 1. Deblurring Techniques
- **Wiener Filter**: Optimal restoration for known blur kernels
- **Richardson-Lucy Deconvolution**: Iterative restoration method

### 2. Spot/Artifact Removal
- **Median Filter**: Removes salt-and-pepper noise
- **Morphological Operations**: Opening/closing for spot removal
- **Inpainting**: Fill in missing/damaged regions

### 3. Contrast Enhancement
- **Histogram Equalization**: Improves overall contrast
- **CLAHE**: Contrast Limited Adaptive Histogram Equalization
- **Unsharp Masking**: Sharpens edges while preserving details

### 4. Illumination Correction
- **Background Subtraction**: Remove uneven illumination
- **Gamma Correction**: Adjust brightness distribution

### 5. Combined Correction
- **Multi-step Pipeline**: Combines multiple techniques for comprehensive correction

## Compilation Instructions

### Prerequisites
- OpenCV 4.x (with photo module)
- MATLAB Engine API for C++
- C++17 compatible compiler

### Compilation Command
```bash
g++ -std=c++17 camera_dirty_lens_correction.cpp -o camera_dirty_lens_correction \
    `pkg-config --cflags --libs opencv4` \
    -I/Applications/MATLAB_R2023b.app/extern/include \
    -L/Applications/MATLAB_R2023b.app/bin/maci64 \
    -lMatlabDataArray -lMatlabEngine
```

### Alternative Compilation (Linux)
```bash
g++ -std=c++17 camera_dirty_lens_correction.cpp -o camera_dirty_lens_correction \
    `pkg-config --cflags --libs opencv4` \
    -I/usr/local/MATLAB/R2023b/extern/include \
    -L/usr/local/MATLAB/R2023b/bin/glnxa64 \
    -lMatlabDataArray -lMatlabEngine
```

## Usage

### Basic Usage
```bash
./camera_dirty_lens_correction
```

### Keyboard Controls
- `q` or `ESC`: Quit the program
- `0`: Wiener Deblurring
- `1`: Richardson-Lucy Deconvolution
- `2`: Median Filter Spot Removal
- `3`: Morphological Spot Removal
- `4`: Inpainting Spot Removal
- `5`: Histogram Equalization
- `6`: CLAHE Contrast Enhancement
- `7`: Unsharp Masking
- `8`: Illumination Correction
- `9`: Combined Correction (Recommended)
- `m`: Send current frame to MATLAB for analysis
- `s`: Save current corrected image

### Program Output
The program displays:
- Real-time corrected video feed
- Current correction method
- Quality metrics (PSNR, MSE)
- Performance statistics

## MATLAB Analysis

### Running MATLAB Analysis
1. Run the C++ program
2. Press `m` to send data to MATLAB
3. Run the MATLAB analysis script:
```matlab
dirty_lens_correction_analysis()
```

### MATLAB Features
- **Comprehensive Visualization**: Side-by-side comparison, difference images, edge analysis
- **Quality Metrics**: PSNR, SSIM, MSE calculations
- **Histogram Analysis**: RGB channel analysis, contrast improvement
- **Frequency Domain Analysis**: Power spectral density, frequency response
- **Noise Analysis**: Laplacian-based noise estimation
- **Sharpness Metrics**: Various sharpness measurements

## Algorithm Details

### Wiener Filter
```cpp
// Optimal restoration for known blur kernels
// Formula: H_wiener = H* / (|H|² + N/S)
// Where H is blur kernel, N is noise power, S is signal power
```

### Richardson-Lucy Deconvolution
```cpp
// Iterative restoration method
// Formula: f^(n+1) = f^(n) * (h^T * (g / (h * f^(n))))
// Where f is estimate, h is blur kernel, g is observed image
```

### CLAHE (Contrast Limited Adaptive Histogram Equalization)
```cpp
// Local contrast enhancement with clipping
// Prevents over-amplification of noise
// Parameters: clip limit, tile grid size
```

### Unsharp Masking
```cpp
// Sharpening technique
// Formula: sharpened = original + amount * (original - blurred)
// Parameters: amount, radius
```

## Performance Considerations

### Real-time Performance
- **Combined Correction**: ~30-60 FPS on modern hardware
- **Individual Methods**: 60+ FPS
- **MATLAB Analysis**: Offline processing

### Parameter Tuning
- **Wiener Noise Level**: 0.01-0.1 (higher for more noise)
- **Richardson-Lucy Iterations**: 5-20 (more iterations = better quality, slower)
- **CLAHE Clip Limit**: 1.0-4.0 (higher = more contrast enhancement)
- **Unsharp Mask Amount**: 0.5-2.0 (higher = more sharpening)

### Memory Usage
- **Frame Buffer**: ~1.5MB for 640x480 frames
- **Processing Buffers**: ~10-20MB additional
- **MATLAB Integration**: ~50-100MB

## Examples

### Example 1: Basic Spot Removal
```cpp
// Apply median filter for spot removal
CorrectionParams params;
params.medianKernelSize = 5;
applyDirtyLensCorrection(frame, corrected, SPOT_REMOVAL_MEDIAN, params);
```

### Example 2: Contrast Enhancement
```cpp
// Apply CLAHE for contrast enhancement
CorrectionParams params;
params.claheClipLimit = 2.0;
params.claheTileGridSize = Size(8, 8);
applyDirtyLensCorrection(frame, corrected, CONTRAST_CLAHE, params);
```

### Example 3: Combined Correction
```cpp
// Apply comprehensive correction pipeline
CorrectionParams params;
// Set all parameters...
applyDirtyLensCorrection(frame, corrected, COMBINED_CORRECTION, params);
```

### Example 4: MATLAB Analysis
```matlab
% Run comprehensive analysis
dirty_lens_correction_analysis();

% Analyze specific aspects
analyze_color_channels(originalImage, 'Original Color Analysis');
calculate_sharpness_metrics(correctedImage);
```

## Quality Metrics

### PSNR (Peak Signal-to-Noise Ratio)
- **Range**: 0-100 dB
- **Good**: >30 dB
- **Excellent**: >40 dB

### SSIM (Structural Similarity Index)
- **Range**: 0-1
- **Good**: >0.8
- **Excellent**: >0.9

### MSE (Mean Squared Error)
- **Range**: 0-65025 (for 8-bit images)
- **Lower is better**

## Troubleshooting

### Common Issues
1. **Camera not opening**: Check camera permissions and connections
2. **MATLAB not responding**: Ensure MATLAB Engine is properly installed
3. **Poor correction quality**: Adjust parameters based on specific lens issues
4. **Low performance**: Reduce image resolution or use simpler algorithms

### Parameter Guidelines
- **Heavy blur**: Use Richardson-Lucy with more iterations
- **Many spots**: Use morphological operations with larger kernels
- **Low contrast**: Use CLAHE with higher clip limits
- **Uneven lighting**: Use illumination correction

## Advanced Usage

### Custom Parameter Sets
```cpp
// Create custom parameter set for specific scenarios
CorrectionParams customParams;
customParams.richardsonLucyIterations = 15;  // More iterations for heavy blur
customParams.medianKernelSize = 7;           // Larger kernel for bigger spots
customParams.claheClipLimit = 3.0;           // Higher contrast enhancement
customParams.unsharpMaskAmount = 2.0;         // More sharpening
```

### Batch Processing
```cpp
// Process multiple images
vector<string> imageFiles = {"image1.jpg", "image2.jpg", "image3.jpg"};
for (const auto& filename : imageFiles) {
    Mat image = imread(filename);
    Mat corrected;
    applyDirtyLensCorrection(image, corrected, COMBINED_CORRECTION, params);
    imwrite("corrected_" + filename, corrected);
}
```

## Future Enhancements

### Planned Features
- **Deep Learning**: CNN-based deblurring
- **Adaptive Parameters**: Automatic parameter adjustment
- **Multi-scale Processing**: Pyramid-based correction
- **Real-time Optimization**: GPU acceleration

### Research Directions
- **Blind Deconvolution**: Unknown blur kernel estimation
- **Perceptual Metrics**: Human visual system-based quality assessment
- **Adaptive Algorithms**: Scene-dependent correction strategies

## References

1. Gonzalez, R.C. & Woods, R.E. "Digital Image Processing" (4th Edition)
2. Richardson, W.H. "Bayesian-Based Iterative Method of Image Restoration"
3. Lucy, L.B. "An Iterative Technique for the Rectification of Observed Distributions"
4. Zuiderveld, K. "Contrast Limited Adaptive Histogram Equalization"

## License

This project is part of the Educational C++ MATLAB Integration Project.
Use for educational and research purposes.

## Contact

For questions or contributions, please refer to the main project documentation.
