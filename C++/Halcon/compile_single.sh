#!/bin/bash

# Individual Program Compilation Script
# This script compiles individual Halcon C++ programs

if [ $# -eq 0 ]; then
    echo "Usage: $0 <program_name>"
    echo "Example: $0 halcon_basic_01"
    echo ""
    echo "Available programs:"
    echo "Beginner:"
    echo "  halcon_basic_01 - Basic Image Loading and Display"
    echo "  halcon_basic_02 - Image Conversion and Color Spaces"
    echo "  halcon_basic_03 - Basic Image Filtering"
    echo "  halcon_basic_04 - Image Thresholding and Binary Operations"
    echo "  halcon_basic_05 - Basic Geometric Operations"
    echo "  halcon_basic_06 - Image Statistics and Analysis"
    echo "  halcon_basic_07 - Image Saving and File Operations"
    echo ""
    echo "Intermediate:"
    echo "  halcon_intermediate_01 - Camera Acquisition and Live Display"
    echo "  halcon_intermediate_02 - Advanced Image Segmentation"
    echo "  halcon_intermediate_03 - Template Matching and Object Detection"
    echo "  halcon_intermediate_04 - Blob Analysis and Feature Extraction"
    echo "  halcon_intermediate_05 - Camera Calibration"
    echo "  halcon_intermediate_06 - OCR and Text Recognition"
    echo "  halcon_intermediate_07 - Image Registration and Alignment"
    echo ""
    echo "Advanced:"
    echo "  halcon_advanced_01 - 3D Vision and Stereo Reconstruction"
    echo "  halcon_advanced_02 - Machine Learning and Classification"
    echo "  halcon_advanced_03 - Deep Learning Integration"
    echo "  halcon_advanced_04 - Advanced Morphology and Topology"
    echo "  halcon_advanced_05 - Real-time Processing Pipeline"
    echo "  halcon_advanced_06 - Industrial Vision System"
    exit 1
fi

PROGRAM_NAME=$1
SOURCE_FILE="${PROGRAM_NAME}.cpp"

# Check if source file exists
if [ ! -f "$SOURCE_FILE" ]; then
    echo "Error: Source file $SOURCE_FILE not found"
    exit 1
fi

# Set Halcon paths
HALCON_ROOT="/Library/Application Support/HALCON-22.11"
HALCON_INCLUDE="$HALCON_ROOT/include"
HALCON_LIB="$HALCON_ROOT/lib"

# Check if Halcon is installed
if [ ! -d "$HALCON_ROOT" ]; then
    echo "Error: Halcon not found at $HALCON_ROOT"
    echo "Please install Halcon 22.11 or update the HALCON_ROOT path"
    exit 1
fi

# Check if development files are available
if [ ! -f "$HALCON_INCLUDE/HalconCpp.h" ]; then
    echo "Error: Halcon development files not found"
    echo "The Halcon C++ headers are missing. This usually means:"
    echo "1. Only the runtime package is installed"
    echo "2. The development package needs to be installed separately"
    echo ""
    echo "To fix this:"
    echo "1. Download the Halcon 22.11 development package from MVTec"
    echo "2. Install it alongside the runtime package"
    echo "3. Or use the programs with a valid Halcon license for runtime execution"
    echo ""
    echo "For now, the programs are created and ready to compile once Halcon development files are available."
    exit 1
fi

echo "Compiling $PROGRAM_NAME..."

# Compiler flags
CXX_FLAGS="-std=c++11 -O2 -Wall"
INCLUDE_FLAGS="-I$HALCON_INCLUDE"
LIB_FLAGS="-L$HALCON_LIB -lhalcon"

# Special case for advanced_05 (needs pthread)
if [ "$PROGRAM_NAME" = "halcon_advanced_05" ]; then
    LIB_FLAGS="$LIB_FLAGS -lpthread"
fi

# Compile the program
if g++ $CXX_FLAGS $INCLUDE_FLAGS -o $PROGRAM_NAME $SOURCE_FILE $LIB_FLAGS; then
    echo "✓ Successfully compiled $PROGRAM_NAME"
    echo "To run: ./$PROGRAM_NAME"
else
    echo "✗ Failed to compile $PROGRAM_NAME"
    exit 1
fi
