#!/bin/bash
# OpenCV compilation script for Apple Silicon Macs
# This script compiles OpenCV programs using Rosetta (x86_64) to match the OpenCV library architecture

if [ $# -eq 0 ]; then
    echo "Usage: $0 <source_file.cpp> [output_name]"
    echo "Example: $0 opencv001.cpp opencv001"
    exit 1
fi

SOURCE_FILE="$1"
OUTPUT_NAME="${2:-${SOURCE_FILE%.cpp}}"

echo "Compiling $SOURCE_FILE with OpenCV..."
arch -x86_64 clang++ -std=c++17 "$SOURCE_FILE" $(pkg-config --cflags --libs opencv4) -o "$OUTPUT_NAME"

if [ $? -eq 0 ]; then
    echo "Compilation successful! Executable created: $OUTPUT_NAME"
    echo "To run: arch -x86_64 ./$OUTPUT_NAME"
else
    echo "Compilation failed!"
    exit 1
fi
