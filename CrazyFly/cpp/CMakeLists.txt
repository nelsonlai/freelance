# CMakeLists.txt for CrazyFly Quadrotor Control System
# ===================================================
#
# This file configures the build system for the C++ components of the
# quadrotor control system, including high-frequency control loops,
# real-time systems, and hardware interfaces.
#
# Author: [Your Name]
# Date: [Current Date]
# License: MIT

cmake_minimum_required(VERSION 3.16)
project(CrazyFly VERSION 1.0.0 LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set build type
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

# Compiler flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g -O0 -DDEBUG")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3 -DNDEBUG")

# Platform-specific settings
if(UNIX AND NOT APPLE)
    # Linux settings
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
    set(REALTIME_LIBRARIES rt pthread)
    set(PLATFORM_LINUX TRUE)
elseif(APPLE)
    # macOS settings
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
    set(REALTIME_LIBRARIES pthread)
    set(PLATFORM_MACOS TRUE)
elseif(WIN32)
    # Windows settings
    set(PLATFORM_WINDOWS TRUE)
endif()

# Find required packages
find_package(Threads REQUIRED)

# Include directories
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/high_freq_control
    ${CMAKE_CURRENT_SOURCE_DIR}/firmware
    ${CMAKE_CURRENT_SOURCE_DIR}/utils
)

# Source files for high-frequency control
set(HIGH_FREQ_CONTROL_SOURCES
    high_freq_control/real_time_controller.cpp
    high_freq_control/motor_controller.cpp
    high_freq_control/sensor_fusion.cpp
)

# Source files for firmware components
set(FIRMWARE_SOURCES
    firmware/pwm_controller.cpp
    firmware/safety_system.cpp
    firmware/sensor_interface.cpp
)

# Source files for utilities
set(UTILS_SOURCES
    utils/memory_manager.cpp
    utils/thread_pool.cpp
    utils/performance_optimizer.cpp
)

# Create high-frequency control library
add_library(high_freq_control STATIC ${HIGH_FREQ_CONTROL_SOURCES})
target_link_libraries(high_freq_control ${CMAKE_THREAD_LIBS_INIT} ${REALTIME_LIBRARIES})
target_compile_definitions(high_freq_control PRIVATE
    $<$<BOOL:${PLATFORM_LINUX}>:PLATFORM_LINUX>
    $<$<BOOL:${PLATFORM_MACOS}>:PLATFORM_MACOS>
    $<$<BOOL:${PLATFORM_WINDOWS}>:PLATFORM_WINDOWS>
)

# Create firmware library
add_library(firmware STATIC ${FIRMWARE_SOURCES})
target_link_libraries(firmware ${CMAKE_THREAD_LIBS_INIT})

# Create utilities library
add_library(utils STATIC ${UTILS_SOURCES})
target_link_libraries(utils ${CMAKE_THREAD_LIBS_INIT})

# Create main executable
add_executable(crazyfly_control
    main.cpp
)

target_link_libraries(crazyfly_control
    high_freq_control
    firmware
    utils
    ${CMAKE_THREAD_LIBS_INIT}
    ${REALTIME_LIBRARIES}
)

# Create test executable
add_executable(crazyfly_test
    test_main.cpp
)

target_link_libraries(crazyfly_test
    high_freq_control
    firmware
    utils
    ${CMAKE_THREAD_LIBS_INIT}
    ${REALTIME_LIBRARIES}
)

# Installation
install(TARGETS crazyfly_control crazyfly_test
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
)

install(FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/include/*.h
    DESTINATION include/crazyfly
)

# Testing
enable_testing()
add_test(NAME RealTimeControllerTest COMMAND crazyfly_test)

# Documentation
find_package(Doxygen)
if(DOXYGEN_FOUND)
    set(DOXYGEN_IN ${CMAKE_CURRENT_SOURCE_DIR}/docs/Doxyfile.in)
    set(DOXYGEN_OUT ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)
    
    configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)
    
    add_custom_target(docs ALL
        COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        COMMENT "Generating API documentation with Doxygen"
        VERBATIM
    )
endif()

# Print configuration summary
message(STATUS "=== CrazyFly Build Configuration ===")
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")
message(STATUS "C++ standard: ${CMAKE_CXX_STANDARD}")
message(STATUS "Platform: ${CMAKE_SYSTEM_NAME}")
message(STATUS "Compiler: ${CMAKE_CXX_COMPILER_ID}")
message(STATUS "Install prefix: ${CMAKE_INSTALL_PREFIX}")
message(STATUS "=====================================")
