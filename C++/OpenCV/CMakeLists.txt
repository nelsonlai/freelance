cmake_minimum_required(VERSION 3.10)
project(OpenCV_Examples)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find OpenCV with all required modules
find_package(OpenCV REQUIRED COMPONENTS 
    core imgproc imgcodecs videoio highgui calib3d features2d 
    objdetect photo stitching aruco ml dnn)

# Include directories
include_directories(${OpenCV_INCLUDE_DIRS})

# Add all C++ files as executables
# This includes 30 OpenCV programs covering:
# - Basic operations (01-10): Image loading, camera capture, color spaces, drawing, resizing, filters, mouse interaction, operations, contours, histograms
# - Intermediate operations (11-20): Morphological operations, feature detection, template matching, video processing, geometric transforms, object tracking, face detection, optical flow, segmentation, advanced filters
# - Advanced operations (21-30): Image stitching, color tracking, edge detection, 3D object detection, image blending, machine learning, camera calibration, AR overlay, video stabilization, deep learning
file(GLOB CPP_FILES "*.cpp")

foreach(CPP_FILE ${CPP_FILES})
    get_filename_component(EXECUTABLE_NAME ${CPP_FILE} NAME_WE)
    add_executable(${EXECUTABLE_NAME} ${CPP_FILE})
    target_link_libraries(${EXECUTABLE_NAME} ${OpenCV_LIBS})
endforeach()

# Print OpenCV information
message(STATUS "OpenCV version: ${OpenCV_VERSION}")
message(STATUS "OpenCV include dirs: ${OpenCV_INCLUDE_DIRS}")
message(STATUS "OpenCV libraries: ${OpenCV_LIBS}")

# Set output directory
set_target_properties(${EXECUTABLE_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)
