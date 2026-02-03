cmake_minimum_required(VERSION 3.15)
project(SiliconIngotDefectDetection)

# Set C++17 standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find required packages
find_package(OpenCV REQUIRED)
find_package(yaml-cpp REQUIRED)
find_package(PkgConfig REQUIRED)
pkg_check_modules(SQLITE3 REQUIRED sqlite3)

# Find MATLAB Engine API
find_library(MATLAB_ENGINE_LIB
    NAMES libMatlabEngine.so libMatlabEngine.dylib MatlabEngine
    PATHS ${MATLAB_ROOT}/bin/glnxa64 ${MATLAB_ROOT}/bin/maci64 ${MATLAB_ROOT}/bin/win64
    NO_DEFAULT_PATH
)

find_library(MATLAB_DATA_ARRAY_LIB
    NAMES libMatlabDataArray.so libMatlabDataArray.dylib MatlabDataArray
    PATHS ${MATLAB_ROOT}/bin/glnxa64 ${MATLAB_ROOT}/bin/maci64 ${MATLAB_ROOT}/bin/win64
    NO_DEFAULT_PATH
)

# Include directories
include_directories(${OpenCV_INCLUDE_DIRS})
include_directories(${MATLAB_ROOT}/extern/include)

# Source files
set(SOURCES
    src/main.cpp
    src/CameraCapture.cpp
    src/ImagePreprocessor.cpp
    src/MatlabEngineWrapper.cpp
    src/DefectClassifier.cpp
    src/DatabaseLogger.cpp
    src/ConfigManager.cpp
)

# Header files
set(HEADERS
    src/CameraCapture.h
    src/ImagePreprocessor.h
    src/MatlabEngineWrapper.h
    src/DefectClassifier.h
    src/DatabaseLogger.h
    src/ConfigManager.h
)

# Create executable
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

# Link libraries
target_link_libraries(${PROJECT_NAME}
    ${OpenCV_LIBS}
    yaml-cpp
    ${MATLAB_ENGINE_LIB}
    ${MATLAB_DATA_ARRAY_LIB}
    ${SQLITE3_LIBRARIES}
)

# Compiler definitions
target_compile_definitions(${PROJECT_NAME} PRIVATE
    MATLAB_ROOT="${MATLAB_ROOT}"
)

# Copy config file to build directory
configure_file(config.yaml ${CMAKE_BINARY_DIR}/config.yaml COPYONLY)

# Set output directory
set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)
