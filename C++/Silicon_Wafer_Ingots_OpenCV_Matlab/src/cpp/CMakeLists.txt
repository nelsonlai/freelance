cmake_minimum_required(VERSION 3.16)
project(SiliconWaferDefectDetection)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find OpenCV
find_package(OpenCV REQUIRED)

# Include directories
include_directories(${OpenCV_INCLUDE_DIRS})
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

# Source files
set(SOURCES
    main.cpp
    camera_interface.cpp
    image_capture.cpp
    preprocessor.cpp
)

set(HEADERS
    camera_interface.h
    image_capture.h
    preprocessor.h
)

# Create executable
add_executable(wafer_defect_detection ${SOURCES} ${HEADERS})

# Link OpenCV libraries
target_link_libraries(wafer_defect_detection ${OpenCV_LIBS})

# Compiler flags
if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    target_compile_options(wafer_defect_detection PRIVATE -Wall -Wextra -O2)
endif()

# Output directory
set_target_properties(wafer_defect_detection PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)

# Installation
install(TARGETS wafer_defect_detection
    RUNTIME DESTINATION bin
)

# Print OpenCV version for verification
message(STATUS "OpenCV version: ${OpenCV_VERSION}")
message(STATUS "OpenCV include dirs: ${OpenCV_INCLUDE_DIRS}")
message(STATUS "OpenCV libraries: ${OpenCV_LIBS}")
