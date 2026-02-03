cmake_minimum_required(VERSION 3.10)
project(HalconCppExamples)

# Set C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find Halcon
find_path(HALCON_INCLUDE_DIR
    NAMES HalconCpp.h
    PATHS /Library/Application\ Support/HALCON-22.11/include
          /opt/halcon/include
          /usr/local/halcon/include
)

find_library(HALCON_LIBRARY
    NAMES halcon
    PATHS /Library/Application\ Support/HALCON-22.11/lib
          /opt/halcon/lib
          /usr/local/halcon/lib
)

if(NOT HALCON_INCLUDE_DIR OR NOT HALCON_LIBRARY)
    message(FATAL_ERROR "Halcon not found. Please install Halcon and set HALCON_ROOT")
endif()

# Include directories
include_directories(${HALCON_INCLUDE_DIR})

# Define all programs
set(BEGINNER_PROGRAMS
    halcon_basic_01
    halcon_basic_02
    halcon_basic_03
    halcon_basic_04
    halcon_basic_05
    halcon_basic_06
    halcon_basic_07
)

set(INTERMEDIATE_PROGRAMS
    halcon_intermediate_01
    halcon_intermediate_02
    halcon_intermediate_03
    halcon_intermediate_04
    halcon_intermediate_05
    halcon_intermediate_06
    halcon_intermediate_07
)

set(ADVANCED_PROGRAMS
    halcon_advanced_01
    halcon_advanced_02
    halcon_advanced_03
    halcon_advanced_04
    halcon_advanced_05
    halcon_advanced_06
)

# Create executables for beginner programs
foreach(program ${BEGINNER_PROGRAMS})
    add_executable(${program} ${program}.cpp)
    target_link_libraries(${program} ${HALCON_LIBRARY})
    target_compile_definitions(${program} PRIVATE HALCON_CPP)
endforeach()

# Create executables for intermediate programs
foreach(program ${INTERMEDIATE_PROGRAMS})
    add_executable(${program} ${program}.cpp)
    target_link_libraries(${program} ${HALCON_LIBRARY})
    target_compile_definitions(${program} PRIVATE HALCON_CPP)
endforeach()

# Create executables for advanced programs
foreach(program ${ADVANCED_PROGRAMS})
    add_executable(${program} ${program}.cpp)
    target_link_libraries(${program} ${HALCON_LIBRARY})
    target_compile_definitions(${program} PRIVATE HALCON_CPP)
endforeach()

# Special case for advanced_05 (needs pthread)
target_link_libraries(halcon_advanced_05 ${HALCON_LIBRARY} pthread)

# Create custom targets for building all programs
add_custom_target(build_all_beginner
    DEPENDS ${BEGINNER_PROGRAMS}
    COMMENT "Building all beginner programs"
)

add_custom_target(build_all_intermediate
    DEPENDS ${INTERMEDIATE_PROGRAMS}
    COMMENT "Building all intermediate programs"
)

add_custom_target(build_all_advanced
    DEPENDS ${ADVANCED_PROGRAMS}
    COMMENT "Building all advanced programs"
)

add_custom_target(build_all
    DEPENDS ${BEGINNER_PROGRAMS} ${INTERMEDIATE_PROGRAMS} ${ADVANCED_PROGRAMS}
    COMMENT "Building all Halcon programs"
)

# Print configuration info
message(STATUS "Halcon Include Directory: ${HALCON_INCLUDE_DIR}")
message(STATUS "Halcon Library: ${HALCON_LIBRARY}")
message(STATUS "Building ${CMAKE_CURRENT_LIST_LENGTH} programs")
