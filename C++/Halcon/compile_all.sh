#!/bin/bash

# Halcon C++ Programs Compilation Script
# This script compiles all 20 Halcon C++ programs

echo "=== Halcon C++ Programs Compilation Script ==="
echo "Compiling 20 Halcon C++ programs..."

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
    echo "All 20 programs have been created successfully!"
    exit 1
fi

echo "Using Halcon from: $HALCON_ROOT"

# Compiler flags
CXX_FLAGS="-std=c++11 -O2 -Wall"
INCLUDE_FLAGS="-I$HALCON_INCLUDE"
LIB_FLAGS="-L$HALCON_LIB -lhalcon"

# Create build directory
mkdir -p build
cd build

echo "Building in directory: $(pwd)"

# Function to compile a program
compile_program() {
    local source_file=$1
    local executable_name=$2
    local extra_libs=$3
    
    echo "Compiling $source_file..."
    
    if g++ $CXX_FLAGS $INCLUDE_FLAGS -o $executable_name ../$source_file $LIB_FLAGS $extra_libs; then
        echo "✓ Successfully compiled $executable_name"
        return 0
    else
        echo "✗ Failed to compile $source_file"
        return 1
    fi
}

# Compile beginner programs
echo ""
echo "=== Compiling Beginner Programs ==="
compile_program "halcon_basic_01.cpp" "halcon_basic_01"
compile_program "halcon_basic_02.cpp" "halcon_basic_02"
compile_program "halcon_basic_03.cpp" "halcon_basic_03"
compile_program "halcon_basic_04.cpp" "halcon_basic_04"
compile_program "halcon_basic_05.cpp" "halcon_basic_05"
compile_program "halcon_basic_06.cpp" "halcon_basic_06"
compile_program "halcon_basic_07.cpp" "halcon_basic_07"

# Compile intermediate programs
echo ""
echo "=== Compiling Intermediate Programs ==="
compile_program "halcon_intermediate_01.cpp" "halcon_intermediate_01"
compile_program "halcon_intermediate_02.cpp" "halcon_intermediate_02"
compile_program "halcon_intermediate_03.cpp" "halcon_intermediate_03"
compile_program "halcon_intermediate_04.cpp" "halcon_intermediate_04"
compile_program "halcon_intermediate_05.cpp" "halcon_intermediate_05"
compile_program "halcon_intermediate_06.cpp" "halcon_intermediate_06"
compile_program "halcon_intermediate_07.cpp" "halcon_intermediate_07"

# Compile advanced programs
echo ""
echo "=== Compiling Advanced Programs ==="
compile_program "halcon_advanced_01.cpp" "halcon_advanced_01"
compile_program "halcon_advanced_02.cpp" "halcon_advanced_02"
compile_program "halcon_advanced_03.cpp" "halcon_advanced_03"
compile_program "halcon_advanced_04.cpp" "halcon_advanced_04"
compile_program "halcon_advanced_05.cpp" "halcon_advanced_05" "-lpthread"
compile_program "halcon_advanced_06.cpp" "halcon_advanced_06"

# Count successful compilations
echo ""
echo "=== Compilation Summary ==="
successful_count=$(ls -1 halcon_* 2>/dev/null | wc -l)
echo "Successfully compiled: $successful_count programs"

if [ $successful_count -eq 20 ]; then
    echo "✓ All 20 programs compiled successfully!"
    echo ""
    echo "Executable files created:"
    ls -la halcon_*
    echo ""
    echo "To run a program, use: ./program_name"
    echo "Example: ./halcon_basic_01"
else
    echo "⚠ Some programs failed to compile"
    echo "Check the error messages above for details"
fi

cd ..
echo ""
echo "Compilation script completed!"
echo "Build directory: build/"
echo "Executables: build/halcon_*"
