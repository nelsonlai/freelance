#!/bin/bash

# Halcon C++ Compilation Script for macOS with clang
# This script demonstrates how to compile Halcon C++ programs once development files are available

echo "=== Halcon C++ Compilation with clang ==="
echo "Compiling all 20 Halcon C++ programs..."

# Set Halcon paths (update these when development package is installed)
HALCON_ROOT="/Library/Application Support/HALCON-22.11"
HALCON_INCLUDE="$HALCON_ROOT/include"
HALCON_LIB="$HALCON_ROOT/lib"

# Check if development files are available
if [ ! -f "$HALCON_INCLUDE/HalconCpp.h" ]; then
    echo "❌ Halcon development files not found!"
    echo ""
    echo "Current situation:"
    echo "  ✓ Halcon 22.11 runtime is installed"
    echo "  ✗ Halcon development headers are missing"
    echo ""
    echo "To compile these programs, you need to:"
    echo "1. Download Halcon 22.11 development package from MVTec"
    echo "2. Install it alongside the runtime package"
    echo "3. Ensure HalconCpp.h is available in $HALCON_INCLUDE/"
    echo ""
    echo "Once development files are available, this script will compile all programs."
    echo ""
    echo "For now, demonstrating the compilation process..."
    echo ""
fi

# Create build directory
mkdir -p build
cd build

echo "Build directory: $(pwd)"

# Compiler settings for clang
CXX="clang++"
CXX_FLAGS="-std=c++11 -O2 -Wall -Wextra"
INCLUDE_FLAGS="-I$HALCON_INCLUDE"
LIB_FLAGS="-L$HALCON_LIB -lhalcon"

# Function to demonstrate compilation
demonstrate_compilation() {
    local source_file=$1
    local executable_name=$2
    local extra_libs=$3
    
    echo "📝 Would compile: $source_file"
    
    if [ -f "$HALCON_INCLUDE/HalconCpp.h" ]; then
        echo "   Command: $CXX $CXX_FLAGS $INCLUDE_FLAGS -o $executable_name ../$source_file $LIB_FLAGS $extra_libs"
        
        if $CXX $CXX_FLAGS $INCLUDE_FLAGS -o $executable_name ../$source_file $LIB_FLAGS $extra_libs 2>/dev/null; then
            echo "   ✅ Successfully compiled $executable_name"
            return 0
        else
            echo "   ❌ Failed to compile $source_file"
            return 1
        fi
    else
        echo "   ⏸️  Skipped (development files not available)"
        return 0
    fi
}

# Compile all programs
echo ""
echo "=== Compilation Process ==="

# Beginner programs
echo ""
echo "🔰 Beginner Programs:"
demonstrate_compilation "halcon_basic_01.cpp" "halcon_basic_01"
demonstrate_compilation "halcon_basic_02.cpp" "halcon_basic_02"
demonstrate_compilation "halcon_basic_03.cpp" "halcon_basic_03"
demonstrate_compilation "halcon_basic_04.cpp" "halcon_basic_04"
demonstrate_compilation "halcon_basic_05.cpp" "halcon_basic_05"
demonstrate_compilation "halcon_basic_06.cpp" "halcon_basic_06"
demonstrate_compilation "halcon_basic_07.cpp" "halcon_basic_07"

# Intermediate programs
echo ""
echo "🔧 Intermediate Programs:"
demonstrate_compilation "halcon_intermediate_01.cpp" "halcon_intermediate_01"
demonstrate_compilation "halcon_intermediate_02.cpp" "halcon_intermediate_02"
demonstrate_compilation "halcon_intermediate_03.cpp" "halcon_intermediate_03"
demonstrate_compilation "halcon_intermediate_04.cpp" "halcon_intermediate_04"
demonstrate_compilation "halcon_intermediate_05.cpp" "halcon_intermediate_05"
demonstrate_compilation "halcon_intermediate_06.cpp" "halcon_intermediate_06"
demonstrate_compilation "halcon_intermediate_07.cpp" "halcon_intermediate_07"

# Advanced programs
echo ""
echo "🚀 Advanced Programs:"
demonstrate_compilation "halcon_advanced_01.cpp" "halcon_advanced_01"
demonstrate_compilation "halcon_advanced_02.cpp" "halcon_advanced_02"
demonstrate_compilation "halcon_advanced_03.cpp" "halcon_advanced_03"
demonstrate_compilation "halcon_advanced_04.cpp" "halcon_advanced_04"
demonstrate_compilation "halcon_advanced_05.cpp" "halcon_advanced_05" "-lpthread"
demonstrate_compilation "halcon_advanced_06.cpp" "halcon_advanced_06"

# Summary
echo ""
echo "=== Summary ==="
if [ -f "$HALCON_INCLUDE/HalconCpp.h" ]; then
    successful_count=$(ls -1 halcon_* 2>/dev/null | wc -l)
    echo "✅ Successfully compiled: $successful_count programs"
    echo ""
    echo "Executable files:"
    ls -la halcon_* 2>/dev/null || echo "No executables found"
else
    echo "📋 All 20 programs are ready for compilation"
    echo "📁 Source files are in: $(pwd)/.."
    echo "🔧 Install Halcon development package to enable compilation"
fi

echo ""
echo "=== Next Steps ==="
echo "1. Install Halcon 22.11 development package"
echo "2. Run this script again: ./compile_with_clang.sh"
echo "3. Execute programs: ./build/halcon_basic_01"
echo ""
echo "Programs created:"
echo "  • 7 Beginner programs (basic image operations)"
echo "  • 7 Intermediate programs (camera, segmentation, matching)"
echo "  • 6 Advanced programs (3D vision, ML, industrial systems)"

cd ..
echo ""
echo "Compilation demonstration completed!"
