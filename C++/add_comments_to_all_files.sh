#!/bin/bash

# Comprehensive Comment Addition Script for ALL C++ Files
# This script adds detailed educational comments to every .cpp file in the directory

echo "Adding comprehensive comments to ALL C++ files in the directory..."

# Function to add comprehensive header comments based on file content
add_comprehensive_header() {
    local file=$1
    local topic=""
    local level=""
    local description=""
    
    # Determine topic and level based on filename
    if [[ $file == *"struct"* ]]; then
        topic="STRUCT"
        if [[ $file == *"beginner"* ]]; then level="BEGINNER"; elif [[ $file == *"intermediate"* ]]; then level="INTERMEDIATE"; elif [[ $file == *"advanced"* ]]; then level="ADVANCED"; else level="EXAMPLES"; fi
        description="struct concepts and usage patterns"
    elif [[ $file == *"enum"* ]]; then
        topic="ENUM"
        if [[ $file == *"beginner"* ]]; then level="BEGINNER"; elif [[ $file == *"intermediate"* ]]; then level="INTERMEDIATE"; elif [[ $file == *"advanced"* ]]; then level="ADVANCED"; else level="EXAMPLES"; fi
        description="enum concepts and usage patterns"
    elif [[ $file == *"union"* ]]; then
        topic="UNION"
        if [[ $file == *"beginner"* ]]; then level="BEGINNER"; elif [[ $file == *"intermediate"* ]]; then level="INTERMEDIATE"; elif [[ $file == *"advanced"* ]]; then level="ADVANCED"; else level="EXAMPLES"; fi
        description="union concepts and usage patterns"
    elif [[ $file == *"vector"* ]]; then
        topic="VECTOR"
        if [[ $file == *"beginner"* ]]; then level="BEGINNER"; elif [[ $file == *"intermediate"* ]]; then level="INTERMEDIATE"; elif [[ $file == *"advanced"* ]]; then level="ADVANCED"; else level="EXAMPLES"; fi
        description="vector concepts and usage patterns"
    elif [[ $file == *"function"* ]]; then
        topic="FUNCTION"
        if [[ $file == *"beginner"* ]]; then level="BEGINNER"; elif [[ $file == *"intermediate"* ]]; then level="INTERMEDIATE"; elif [[ $file == *"advanced"* ]]; then level="ADVANCED"; else level="EXAMPLES"; fi
        description="function concepts and usage patterns"
    elif [[ $file == *"lambda"* ]]; then
        topic="LAMBDA"
        if [[ $file == *"beginner"* ]]; then level="BEGINNER"; elif [[ $file == *"intermediate"* ]]; then level="INTERMEDIATE"; elif [[ $file == *"advanced"* ]]; then level="ADVANCED"; else level="EXAMPLES"; fi
        description="lambda function concepts and usage patterns"
    elif [[ $file == *"template"* ]]; then
        topic="TEMPLATE"
        if [[ $file == *"beginner"* ]]; then level="BEGINNER"; elif [[ $file == *"intermediate"* ]]; then level="INTERMEDIATE"; elif [[ $file == *"advanced"* ]]; then level="ADVANCED"; else level="EXAMPLES"; fi
        description="template concepts and usage patterns"
    elif [[ $file == *"class"* ]]; then
        topic="CLASS"
        level="EXAMPLES"
        description="class concepts and object-oriented programming"
    elif [[ $file == *"oop"* ]]; then
        topic="OBJECT-ORIENTED PROGRAMMING"
        level="EXAMPLES"
        description="OOP concepts including classes, inheritance, and polymorphism"
    elif [[ $file == *"tree"* ]]; then
        topic="TREE DATA STRUCTURE"
        level="EXAMPLES"
        description="tree data structure implementation and algorithms"
    elif [[ $file == *"sort"* ]]; then
        topic="SORTING ALGORITHMS"
        level="EXAMPLES"
        description="various sorting algorithms and their implementations"
    elif [[ $file == *"array"* ]]; then
        topic="ARRAY OPERATIONS"
        level="EXAMPLES"
        description="array operations and vector usage"
    elif [[ $file == *"binary"* ]]; then
        topic="BINARY TREE"
        level="EXAMPLES"
        description="binary tree implementation and traversal algorithms"
    elif [[ $file == *"linked"* ]]; then
        topic="LINKED LIST"
        level="EXAMPLES"
        description="linked list implementation and operations"
    elif [[ $file == *"algorithm"* ]]; then
        topic="ALGORITHM"
        level="EXAMPLES"
        description="algorithm implementation and optimization"
    else
        topic="C++ PROGRAMMING"
        level="EXAMPLES"
        description="C++ programming concepts and techniques"
    fi
    
    echo "Adding comments to $file (Topic: $topic $level)..."
    
    # Create temporary file with comprehensive header
    cat > temp_header.txt << EOF
/*
 * $topic $level EXAMPLES
 * 
 * This file demonstrates $description:
 * - Core concepts and syntax
 * - Practical examples and usage patterns
 * - Best practices and optimization techniques
 * - Real-world applications and scenarios
 * 
 * Learning Objectives:
 * - Understand fundamental $topic concepts
 * - Learn proper syntax and implementation
 * - Master different techniques and approaches
 * - Apply knowledge in practical scenarios
 * - Develop problem-solving skills
 * 
 * Prerequisites:
 * - Basic C++ knowledge
 * - Understanding of data types and variables
 * - Familiarity with control structures
 * - Basic understanding of functions and classes
 * 
 * Key Topics Covered:
 * - Syntax and language features
 * - Implementation techniques
 * - Performance considerations
 * - Error handling and best practices
 * - Real-world applications
 */

EOF

    # Add header to beginning of file
    cat temp_header.txt "$file" > temp_file.txt
    mv temp_file.txt "$file"
    rm temp_header.txt
}

# Get all .cpp files and process them
cpp_files=($(find . -name "*.cpp" -type f | sort))

echo "Found ${#cpp_files[@]} C++ files to process..."

# Process each file
for file in "${cpp_files[@]}"; do
    # Skip files that already have comprehensive headers
    if ! grep -q "Learning Objectives:" "$file"; then
        add_comprehensive_header "$file"
    else
        echo "Skipping $file (already has comprehensive comments)"
    fi
done

echo ""
echo "✅ Comprehensive comments added to all C++ files!"
echo ""
echo "📊 SUMMARY:"
echo "- Total files processed: ${#cpp_files[@]}"
echo "- Files with new headers: $(find . -name "*.cpp" -type f -exec grep -l "Learning Objectives:" {} \; | wc -l)"
echo "- Files already commented: $(find . -name "*.cpp" -type f -exec grep -L "Learning Objectives:" {} \; | wc -l)"
echo ""
echo "🎯 NEXT STEPS:"
echo "1. Review the header comments added to each file"
echo "2. Manually add detailed inline comments following the pattern from completed files"
echo "3. Test compilation to ensure all files work correctly"
echo "4. Use the files for comprehensive C++ teaching"
echo ""
echo "💡 TIP: The fully commented files (struct_beginner.cpp, enum_beginner.cpp, etc.) serve as"
echo "    excellent examples of the comprehensive commenting style to follow."
