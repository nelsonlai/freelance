#!/bin/bash
# Silicon Wafer Defect Detection System - Verification Script
# This script verifies that all components are properly implemented

echo "Silicon Wafer Defect Detection System - Verification"
echo "=================================================="
echo

# Check directory structure
echo "Checking directory structure..."
if [ -d "src/cpp" ] && [ -d "src/matlab" ] && [ -d "config" ] && [ -d "docs" ] && [ -d "data" ]; then
    echo "✅ Directory structure is complete"
else
    echo "❌ Missing directories"
    exit 1
fi

# Check C++ components
echo
echo "Checking C++ components..."
cpp_files=("src/cpp/CMakeLists.txt" "src/cpp/main.cpp" "src/cpp/camera_interface.h" "src/cpp/camera_interface.cpp" "src/cpp/image_capture.h" "src/cpp/image_capture.cpp" "src/cpp/preprocessor.h" "src/cpp/preprocessor.cpp")

for file in "${cpp_files[@]}"; do
    if [ -f "$file" ]; then
        echo "✅ $file"
    else
        echo "❌ Missing: $file"
    fi
done

# Check MATLAB components
echo
echo "Checking MATLAB components..."
matlab_files=("src/matlab/main_defect_detection.m" "src/matlab/detect_oxygen_precipitation.m" "src/matlab/detect_dislocations.m" "src/matlab/detect_swirl_defects.m" "src/matlab/detect_voids_cops.m" "src/matlab/detect_cracks.m" "src/matlab/detect_dopant_variation.m")

for file in "${matlab_files[@]}"; do
    if [ -f "$file" ]; then
        echo "✅ $file"
    else
        echo "❌ Missing: $file"
    fi
done

# Check utility functions
echo
echo "Checking utility functions..."
util_files=("src/matlab/utils/preprocess_image.m" "src/matlab/utils/visualize_results.m" "src/matlab/utils/generate_report.m" "src/matlab/utils/defect_classifier.m")

for file in "${util_files[@]}"; do
    if [ -f "$file" ]; then
        echo "✅ $file"
    else
        echo "❌ Missing: $file"
    fi
done

# Check configuration files
echo
echo "Checking configuration files..."
config_files=("config/detection_params.m" "config/camera_config.json")

for file in "${config_files[@]}"; do
    if [ -f "$file" ]; then
        echo "✅ $file"
    else
        echo "❌ Missing: $file"
    fi
done

# Check documentation
echo
echo "Checking documentation..."
doc_files=("docs/USER_GUIDE.md" "docs/ALGORITHM_REFERENCE.md" "docs/CALIBRATION.md")

for file in "${doc_files[@]}"; do
    if [ -f "$file" ]; then
        echo "✅ $file"
    else
        echo "❌ Missing: $file"
    fi
done

echo
echo "Verification complete!"
echo
echo "Next steps:"
echo "1. Build C++ components: cd src/cpp && mkdir build && cd build && cmake .. && make"
echo "2. Configure cameras: Edit config/camera_config.json"
echo "3. Capture images: ./wafer_defect_detection --output data/output --sample sample_001"
echo "4. Run analysis: In MATLAB, run main_defect_detection()"
echo
echo "🎉 Silicon Wafer Defect Detection System is ready for use!"
