#!/bin/bash

# Compilation script for C++ with MATLAB Camera Capture and Image Processing Project
# This script compiles all 30 programs in the project

echo "=== C++ with MATLAB Camera Capture and Image Processing Project ==="
echo "Compiling all programs..."

# Check if OpenCV is installed
if ! pkg-config --exists opencv4; then
    echo "Error: OpenCV4 not found. Please install OpenCV4 first."
    exit 1
fi

# Check if MATLAB is installed
MATLAB_PATH="/Applications/MATLAB_R2023b.app"
if [ ! -d "$MATLAB_PATH" ]; then
    echo "Error: MATLAB not found at $MATLAB_PATH"
    echo "Please update the MATLAB_PATH variable in this script to point to your MATLAB installation."
    exit 1
fi

# Set compilation flags
CXX_FLAGS="-std=c++17 -Wall -Wextra -O2"
OPENCV_FLAGS=$(pkg-config --cflags --libs opencv4)
MATLAB_INCLUDE="-I$MATLAB_PATH/extern/include"
MATLAB_LIB="-L$MATLAB_PATH/bin/maci64 -lMatlabDataArray -lMatlabEngine"

# Create build directory
mkdir -p build
cd build

# Compile beginner programs
echo "Compiling beginner programs..."
for i in {1..10}; do
    printf "%02d" $i
    echo " - Compiling camera_basic_$i.cpp..."
    g++ $CXX_FLAGS ../camera_basic_$i.cpp -o camera_basic_$i $OPENCV_FLAGS $MATLAB_INCLUDE $MATLAB_LIB
    if [ $? -eq 0 ]; then
        echo "  ✓ Success"
    else
        echo "  ✗ Failed"
    fi
done

# Compile intermediate programs
echo "Compiling intermediate programs..."
for i in {11..20}; do
    printf "%02d" $i
    echo " - Compiling camera_intermediate_$i.cpp..."
    g++ $CXX_FLAGS ../camera_intermediate_$i.cpp -o camera_intermediate_$i $OPENCV_FLAGS $MATLAB_INCLUDE $MATLAB_LIB
    if [ $? -eq 0 ]; then
        echo "  ✓ Success"
    else
        echo "  ✗ Failed"
    fi
done

# Compile advanced programs
echo "Compiling advanced programs..."
for i in {21..30}; do
    printf "%02d" $i
    echo " - Compiling camera_advanced_$i.cpp..."
    g++ $CXX_FLAGS ../camera_advanced_$i.cpp -o camera_advanced_$i $OPENCV_FLAGS $MATLAB_INCLUDE $MATLAB_LIB
    if [ $? -eq 0 ]; then
        echo "  ✓ Success"
    else
        echo "  ✗ Failed"
    fi
done

echo ""
echo "=== Compilation Complete ==="
echo "All executables are in the build/ directory"
echo ""
echo "To run a program:"
echo "  cd build"
echo "  ./camera_basic_01"
echo "  ./camera_intermediate_11"
echo "  ./camera_advanced_21"
echo ""
echo "Make sure your camera is connected and MATLAB is running!"
