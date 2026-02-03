# Silicon Wafer Defect Detection - Algorithm Reference

## Overview

This document provides detailed technical information about the algorithms used in the Silicon Wafer Defect Detection System. Each detection algorithm is based on traditional computer vision techniques optimized for silicon wafer defect analysis.

## Algorithm Categories

### 1. Oxygen Precipitation Detection

#### Algorithm: `detect_oxygen_precipitation.m`

**Purpose**: Detect oxygen precipitation and stacking faults in infrared images.

**Method**: Threshold-based segmentation with morphological operations

**Algorithm Steps**:
1. **Preprocessing**: Convert to double precision, normalize intensity
2. **Thresholding**: Apply Otsu, adaptive, or manual thresholding
3. **Morphological Operations**: 
   - Opening to remove noise
   - Closing to fill small holes
4. **Connected Component Analysis**: Count and measure precipitates
5. **Edge Detection**: Canny edge detection for stacking faults
6. **Hough Transform**: Detect linear stacking fault patterns

**Key Parameters**:
- `threshold_method`: 'otsu', 'adaptive', 'manual'
- `morphology_size`: Size of morphological kernel
- `min_precipitate_size`: Minimum precipitate size in pixels
- `max_precipitate_size`: Maximum precipitate size in pixels

**Mathematical Foundation**:
- Otsu thresholding: Minimizes intra-class variance
- Morphological operations: Erosion followed by dilation
- Connected components: 8-connected neighborhood analysis

### 2. Dislocation Detection

#### Algorithm: `detect_dislocations.m`

**Purpose**: Detect dislocation lines and slip patterns in optical/IR images.

**Method**: Edge detection with Hough transform

**Algorithm Steps**:
1. **Contrast Enhancement**: Adaptive histogram equalization
2. **Edge Detection**: Canny, Sobel, or Prewitt edge detection
3. **Directional Filtering**: Enhance lines in different orientations
4. **Hough Transform**: Detect linear features
5. **Line Validation**: Filter lines by length and gap
6. **Density Mapping**: Calculate local dislocation density

**Key Parameters**:
- `edge_method`: 'canny', 'sobel', 'prewitt'
- `hough_threshold`: Threshold for Hough line detection
- `min_line_length`: Minimum line length for detection
- `line_gap`: Maximum gap between line segments

**Mathematical Foundation**:
- Canny edge detection: Gradient magnitude and direction
- Hough transform: ρ = x·cos(θ) + y·sin(θ)
- Density calculation: Lines per unit area

### 3. Swirl Defect Detection

#### Algorithm: `detect_swirl_defects.m`

**Purpose**: Detect swirl patterns in infrared images using frequency domain analysis.

**Method**: FFT analysis with Gabor filtering

**Algorithm Steps**:
1. **Preprocessing**: Noise reduction and contrast enhancement
2. **FFT Analysis**: Detect circular/rotational patterns
3. **Gabor Filter Bank**: Multi-scale, multi-orientation filtering
4. **Orientation Field**: Compute local orientation patterns
5. **Template Matching**: Detect swirl patterns
6. **Severity Scoring**: Quantify swirl defect severity

**Key Parameters**:
- `fft_threshold`: Threshold for FFT magnitude analysis
- `gabor_frequencies`: Frequencies for Gabor filter bank
- `gabor_orientations`: Orientations for Gabor filter bank
- `min_swirl_size`: Minimum swirl pattern size

**Mathematical Foundation**:
- FFT: F(u,v) = Σ Σ f(x,y) e^(-j2π(ux+vy))
- Gabor filter: g(x,y) = s(x,y) e^(j2πf(xcosθ+ysinθ))
- Orientation field: θ = arctan(Gy/Gx)

### 4. Void and COP Detection

#### Algorithm: `detect_voids_cops.m`

**Purpose**: Detect voids, microvoids, and COPs using blob detection.

**Method**: Laplacian of Gaussian (LoG) and watershed segmentation

**Algorithm Steps**:
1. **Preprocessing**: Contrast enhancement and noise reduction
2. **LoG Blob Detection**: Detect dark void regions
3. **Watershed Segmentation**: Segment connected regions
4. **High-pass Filtering**: Enhance surface pits (COPs)
5. **Size Filtering**: Filter by minimum/maximum size
6. **Duplicate Removal**: Remove overlapping detections

**Key Parameters**:
- `detection_method`: 'log', 'watershed', 'both'
- `min_void_size`: Minimum void size in pixels
- `max_void_size`: Maximum void size in pixels
- `log_sigma`: Sigma for Laplacian of Gaussian

**Mathematical Foundation**:
- LoG: ∇²G(x,y) = (1/πσ⁴)(1-(x²+y²)/2σ²)e^(-(x²+y²)/2σ²)
- Watershed: Flood-fill algorithm for segmentation
- Blob detection: Local maxima in LoG response

### 5. Crack Detection

#### Algorithm: `detect_cracks.m`

**Purpose**: Detect cracks and analyze crack topology.

**Method**: Edge detection with skeletonization

**Algorithm Steps**:
1. **Edge Detection**: Canny edge detection
2. **Directional Filtering**: Enhance linear features
3. **Skeletonization**: Extract crack topology
4. **Junction Detection**: Find crack intersections
5. **Width Calculation**: Distance transform for crack width
6. **Length Measurement**: Calculate crack lengths

**Key Parameters**:
- `edge_method`: 'canny', 'sobel', 'prewitt'
- `hough_threshold`: Threshold for Hough line detection
- `min_crack_length`: Minimum crack length
- `max_crack_width`: Maximum crack width

**Mathematical Foundation**:
- Skeletonization: Thinning algorithm
- Distance transform: D(x,y) = min{distance to background}
- Crack width: 2 × distance transform value

### 6. Dopant Uniformity Analysis

#### Algorithm: `detect_dopant_variation.m`

**Purpose**: Analyze dopant uniformity using gradient analysis.

**Method**: Gradient analysis with profile extraction

**Algorithm Steps**:
1. **Preprocessing**: Smoothing to reduce noise
2. **Gradient Analysis**: Calculate local gradients
3. **Local Statistics**: Standard deviation and coefficient of variation
4. **Profile Analysis**: Radial and axial profiles
5. **Uniformity Scoring**: Calculate overall uniformity score
6. **Variation Mapping**: Create variation maps

**Key Parameters**:
- `analysis_method`: 'gradient', 'profile', 'both'
- `window_size`: Window size for local analysis
- `gradient_threshold`: Threshold for gradient magnitude
- `profile_direction`: 'radial', 'axial', 'both'

**Mathematical Foundation**:
- Gradient: ∇f = (∂f/∂x, ∂f/∂y)
- Coefficient of variation: CV = σ/μ
- Uniformity score: U = 1 - (gradient_uniformity + profile_uniformity)/2

## Performance Considerations

### Computational Complexity

| Algorithm | Time Complexity | Space Complexity | Notes |
|-----------|----------------|------------------|-------|
| Oxygen Precipitation | O(n²) | O(n²) | n = image size |
| Dislocation Detection | O(n² log n) | O(n²) | Hough transform dominant |
| Swirl Detection | O(n² log n) | O(n²) | FFT dominant |
| Void/COP Detection | O(n²) | O(n²) | LoG filtering |
| Crack Detection | O(n²) | O(n²) | Skeletonization |
| Dopant Analysis | O(n²) | O(n²) | Gradient calculation |

### Memory Requirements

- **Minimum RAM**: 8GB recommended
- **Image Size**: Up to 4K resolution supported
- **Batch Processing**: Process images sequentially for large datasets

### Optimization Tips

1. **Image Resolution**: Use appropriate resolution for defect size
2. **Parameter Tuning**: Optimize parameters for specific defect types
3. **Parallel Processing**: Use MATLAB Parallel Computing Toolbox
4. **Memory Management**: Clear variables between processing steps

## Algorithm Validation

### Ground Truth Comparison

Each algorithm can be validated against:
- Manual defect annotations
- Reference images with known defects
- Cross-validation with multiple images

### Performance Metrics

- **Precision**: True positives / (True positives + False positives)
- **Recall**: True positives / (True positives + False negatives)
- **F1-Score**: 2 × (Precision × Recall) / (Precision + Recall)
- **Processing Time**: Time per image
- **Memory Usage**: Peak memory consumption

## Customization

### Parameter Tuning

Each algorithm provides extensive parameter customization:

```matlab
% Example: Customize oxygen precipitation detection
[precipitate_locations, size_distribution, density_map] = detect_oxygen_precipitation(ir_image, ...
    'threshold_method', 'adaptive', ...
    'morphology_size', 5, ...
    'min_precipitate_size', 20);
```

### Algorithm Extension

The modular design allows for easy extension:

1. **New Detection Methods**: Add new algorithms to the framework
2. **Parameter Optimization**: Implement automatic parameter tuning
3. **Machine Learning**: Integrate ML-based detection methods
4. **Real-time Processing**: Optimize for real-time applications

## References

1. Otsu, N. (1979). "A threshold selection method from gray-level histograms"
2. Canny, J. (1986). "A computational approach to edge detection"
3. Hough, P. (1962). "Method and means for recognizing complex patterns"
4. Gabor, D. (1946). "Theory of communication"
5. Vincent, L. (1991). "Watersheds in digital spaces: an efficient algorithm"

## Troubleshooting

### Common Algorithm Issues

1. **Poor Detection Accuracy**: Adjust threshold parameters
2. **False Positives**: Increase minimum size thresholds
3. **Missed Defects**: Decrease threshold values
4. **Slow Performance**: Reduce image resolution or optimize parameters

### Debugging Tips

1. **Visualize Intermediate Results**: Use built-in visualization functions
2. **Parameter Sensitivity**: Test parameter ranges systematically
3. **Image Quality**: Ensure proper image preprocessing
4. **Algorithm Validation**: Compare with manual annotations
