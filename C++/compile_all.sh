#!/bin/bash

# C++ Teaching Material Compilation Script
# This script compiles all the C++ examples from beginner to advanced levels

echo "=== C++ Teaching Material Compilation Script ==="
echo "Compiling all examples from beginner to advanced levels..."
echo

# Set compiler and flags
CXX=g++
CXXFLAGS="-std=c++17 -Wall -Wextra -O2"

# Create output directory
mkdir -p compiled_examples

# Function to compile and run
compile_and_run() {
    local source_file=$1
    local output_name=$2
    local description=$3
    
    echo "Compiling $description..."
    if $CXX $CXXFLAGS -o "compiled_examples/$output_name" "$source_file"; then
        echo "✓ Successfully compiled $description"
        echo "  Output: compiled_examples/$output_name"
        echo
    else
        echo "✗ Failed to compile $description"
        echo
    fi
}

# Beginner level examples
echo "=== BEGINNER LEVEL ==="
compile_and_run "struct_beginner.cpp" "struct_beginner" "Struct Beginner"
compile_and_run "enum_beginner.cpp" "enum_beginner" "Enum Beginner"
compile_and_run "union_beginner.cpp" "union_beginner" "Union Beginner"
compile_and_run "vector_beginner.cpp" "vector_beginner" "Vector Beginner"
compile_and_run "function_beginner.cpp" "function_beginner" "Function Beginner"
compile_and_run "lambda_beginner.cpp" "lambda_beginner" "Lambda Beginner"
compile_and_run "template_beginner.cpp" "template_beginner" "Template Beginner"

# Intermediate level examples
echo "=== INTERMEDIATE LEVEL ==="
compile_and_run "struct_intermediate.cpp" "struct_intermediate" "Struct Intermediate"
compile_and_run "enum_intermediate.cpp" "enum_intermediate" "Enum Intermediate"
compile_and_run "union_intermediate.cpp" "union_intermediate" "Union Intermediate"
compile_and_run "vector_intermediate.cpp" "vector_intermediate" "Vector Intermediate"
compile_and_run "function_intermediate.cpp" "function_intermediate" "Function Intermediate"
compile_and_run "lambda_intermediate.cpp" "lambda_intermediate" "Lambda Intermediate"
compile_and_run "template_intermediate.cpp" "template_intermediate" "Template Intermediate"

# Advanced level examples
echo "=== ADVANCED LEVEL ==="
compile_and_run "struct_advanced.cpp" "struct_advanced" "Struct Advanced"
compile_and_run "enum_advanced.cpp" "enum_advanced" "Enum Advanced"
compile_and_run "union_advanced.cpp" "union_advanced" "Union Advanced"
compile_and_run "vector_advanced.cpp" "vector_advanced" "Vector Advanced"
compile_and_run "function_advanced.cpp" "function_advanced" "Function Advanced"
compile_and_run "lambda_advanced.cpp" "lambda_advanced" "Lambda Advanced"
compile_and_run "template_advanced.cpp" "template_advanced" "Template Advanced"

echo "=== COMPILATION COMPLETE ==="
echo "All examples have been compiled to the 'compiled_examples' directory."
echo "You can run them individually, for example:"
echo "  ./compiled_examples/struct_beginner"
echo "  ./compiled_examples/enum_intermediate"
echo "  ./compiled_examples/lambda_advanced"
echo
echo "Or run all examples with:"
echo "  for file in compiled_examples/*; do echo \"=== \$file ===\"; ./\$file; echo; done"
