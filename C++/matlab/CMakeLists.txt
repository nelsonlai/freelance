cmake_minimum_required(VERSION 3.10)
project(CameraMATLABProject)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find OpenCV
find_package(OpenCV REQUIRED)

# Find MATLAB
find_package(MATLAB REQUIRED)

# Include directories
include_directories(${OpenCV_INCLUDE_DIRS})
include_directories(${MATLAB_INCLUDE_DIRS})

# Source files
set(BEGINNER_SOURCES
    camera_basic_01.cpp
    camera_basic_02.cpp
    camera_basic_03.cpp
    camera_basic_04.cpp
    camera_basic_05.cpp
    camera_basic_06.cpp
    camera_basic_07.cpp
    camera_basic_08.cpp
    camera_basic_09.cpp
    camera_basic_10.cpp
)

set(INTERMEDIATE_SOURCES
    camera_intermediate_11.cpp
    camera_intermediate_12.cpp
    camera_intermediate_13.cpp
    camera_intermediate_14.cpp
    camera_intermediate_15.cpp
    camera_intermediate_16.cpp
    camera_intermediate_17.cpp
    camera_intermediate_18.cpp
    camera_intermediate_19.cpp
    camera_intermediate_20.cpp
)

set(ADVANCED_SOURCES
    camera_advanced_21.cpp
    camera_advanced_22.cpp
    camera_advanced_23.cpp
    camera_advanced_24.cpp
    camera_advanced_25.cpp
    camera_advanced_26.cpp
    camera_advanced_27.cpp
    camera_advanced_28.cpp
    camera_advanced_29.cpp
    camera_advanced_30.cpp
)

# Create executables for beginner programs
foreach(source ${BEGINNER_SOURCES})
    get_filename_component(name ${source} NAME_WE)
    add_executable(${name} ${source})
    target_link_libraries(${name} ${OpenCV_LIBS})
    target_link_libraries(${name} ${MATLAB_LIBRARIES})
endforeach()

# Create executables for intermediate programs
foreach(source ${INTERMEDIATE_SOURCES})
    get_filename_component(name ${source} NAME_WE)
    add_executable(${name} ${source})
    target_link_libraries(${name} ${OpenCV_LIBS})
    target_link_libraries(${name} ${MATLAB_LIBRARIES})
endforeach()

# Create executables for advanced programs
foreach(source ${ADVANCED_SOURCES})
    get_filename_component(name ${source} NAME_WE)
    add_executable(${name} ${source})
    target_link_libraries(${name} ${OpenCV_LIBS})
    target_link_libraries(${name} ${MATLAB_LIBRARIES})
endforeach()

# Compiler flags
if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -O2")
endif()

# Installation
install(TARGETS camera_basic_01 camera_basic_02 camera_basic_03 camera_basic_04 camera_basic_05
              camera_basic_06 camera_basic_07 camera_basic_08 camera_basic_09 camera_basic_10
              camera_intermediate_11 camera_intermediate_12 camera_intermediate_13 camera_intermediate_14 camera_intermediate_15
              camera_intermediate_16 camera_intermediate_17 camera_intermediate_18 camera_intermediate_19 camera_intermediate_20
              camera_advanced_21 camera_advanced_22 camera_advanced_23 camera_advanced_24 camera_advanced_25
              camera_advanced_26 camera_advanced_27 camera_advanced_28 camera_advanced_29 camera_advanced_30
        RUNTIME DESTINATION bin)
