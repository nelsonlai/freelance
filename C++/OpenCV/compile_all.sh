#!/bin/bash
# compile_all.sh
# Compiles all OpenCV examples in the directory

echo "OpenCV C++ Examples Compilation Script"
echo "======================================"

# Check if OpenCV is installed
if ! pkg-config --exists opencv4; then
    echo "Error: OpenCV4 not found. Please install OpenCV first."
    echo "For macOS: brew install opencv"
    echo "For Ubuntu: sudo apt install libopencv-dev"
    exit 1
fi

# Get OpenCV flags
OPENCV_FLAGS=$(pkg-config --cflags --libs opencv4)
echo "Using OpenCV flags: $OPENCV_FLAGS"

# Create output directory
mkdir -p compiled

# Function to compile a single file
compile_file() {
    local file=$1
    local basename=$(basename "$file" .cpp)
    local output="compiled/${basename}"
    
    echo "Compiling $file..."
    
    # Use Rosetta for Apple Silicon compatibility
    if [[ "$OSTYPE" == "darwin"* ]]; then
        arch -x86_64 clang++ -std=c++17 "$file" $OPENCV_FLAGS -o "$output"
    else
        clang++ -std=c++17 "$file" $OPENCV_FLAGS -o "$output"
    fi
    
    if [ $? -eq 0 ]; then
        echo "✓ Successfully compiled: $basename"
    else
        echo "✗ Failed to compile: $basename"
        return 1
    fi
}

# Compile all C++ files
echo ""
echo "Compiling all OpenCV examples..."
echo ""

success_count=0
total_count=0

for file in *.cpp; do
    if [ -f "$file" ]; then
        total_count=$((total_count + 1))
        if compile_file "$file"; then
            success_count=$((success_count + 1))
        fi
        echo ""
    fi
done

echo "======================================"
echo "Compilation Summary:"
echo "Successfully compiled: $success_count/$total_count files"
echo "Output directory: compiled/"
echo ""

if [ $success_count -eq $total_count ]; then
    echo "🎉 All examples compiled successfully!"
    echo ""
    echo "To run an example:"
    echo "  ./compiled/01_basic_image_load"
    echo "  ./compiled/02_camera_capture"
    echo "  etc."
else
    echo "⚠️  Some examples failed to compile. Check the error messages above."
fi

echo ""
echo "Note: For Apple Silicon Macs, you may need to run executables with:"
echo "  arch -x86_64 ./compiled/filename"
