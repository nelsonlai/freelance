cmake_minimum_required(VERSION 3.10)
project(MiniSTL)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set build type
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

# Compiler flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g -O0 -DDEBUG")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG")

# Include directories
include_directories(include)

# Find required packages
find_package(Threads REQUIRED)

# Source files
set(SOURCES
    src/vector.cpp
    src/map.cpp
    src/algorithm.cpp
    src/thread_pool.cpp
    src/memory.cpp
)

# Header files
set(HEADERS
    include/mini_stl/vector.h
    include/mini_stl/map.h
    include/mini_stl/algorithm.h
    include/mini_stl/iterator.h
    include/mini_stl/thread_pool.h
    include/mini_stl/memory.h
    include/mini_stl/utility.h
)

# Create library
add_library(mini_stl ${SOURCES} ${HEADERS})

# Link libraries
target_link_libraries(mini_stl Threads::Threads)

# Set properties
set_target_properties(mini_stl PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
    POSITION_INDEPENDENT_CODE ON
)

# Examples
set(EXAMPLES
    examples/vector_example.cpp
    examples/map_example.cpp
    examples/algorithm_example.cpp
    examples/thread_pool_example.cpp
)

foreach(example ${EXAMPLES})
    get_filename_component(example_name ${example} NAME_WE)
    add_executable(${example_name} ${example})
    target_link_libraries(${example_name} mini_stl)
endforeach()

# Tests
set(TESTS
    tests/test_vector.cpp
    tests/test_map.cpp
    tests/test_algorithm.cpp
    tests/test_thread_pool.cpp
)

foreach(test ${TESTS})
    get_filename_component(test_name ${test} NAME_WE)
    add_executable(${test_name} ${test})
    target_link_libraries(${test_name} mini_stl)
endforeach()

# Benchmarks
set(BENCHMARKS
    benchmarks/vector_benchmark.cpp
    benchmarks/map_benchmark.cpp
    benchmarks/algorithm_benchmark.cpp
)

foreach(benchmark ${BENCHMARKS})
    get_filename_component(benchmark_name ${benchmark} NAME_WE)
    add_executable(${benchmark_name} ${benchmark})
    target_link_libraries(${benchmark_name} mini_stl)
endforeach()

# Custom targets
add_custom_target(examples
    DEPENDS vector_example map_example algorithm_example thread_pool_example
)

add_custom_target(tests
    DEPENDS test_vector test_map test_algorithm test_thread_pool
)

add_custom_target(benchmarks
    DEPENDS vector_benchmark map_benchmark algorithm_benchmark
)

add_custom_target(all_examples
    DEPENDS examples tests benchmarks
)

# Installation
install(TARGETS mini_stl
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    RUNTIME DESTINATION bin
)

install(DIRECTORY include/mini_stl
    DESTINATION include
)

# Package configuration
set(CPACK_PACKAGE_NAME "MiniSTL")
set(CPACK_PACKAGE_VERSION "1.0.0")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Mini Standard Template Library Implementation")
set(CPACK_PACKAGE_VENDOR "C++ Curriculum Project")

include(CPack)

# Documentation
find_package(Doxygen)
if(DOXYGEN_FOUND)
    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in
                   ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile @ONLY)
    add_custom_target(docs
        COMMAND ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        COMMENT "Generating documentation with Doxygen"
        VERBATIM
    )
endif()

# Print configuration
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")
message(STATUS "C++ standard: ${CMAKE_CXX_STANDARD}")
message(STATUS "Compiler: ${CMAKE_CXX_COMPILER}")
message(STATUS "Compiler flags: ${CMAKE_CXX_FLAGS}")
message(STATUS "Debug flags: ${CMAKE_CXX_FLAGS_DEBUG}")
message(STATUS "Release flags: ${CMAKE_CXX_FLAGS_RELEASE}")

# Add custom commands for running examples and tests
add_custom_target(run_vector_example
    COMMAND vector_example
    DEPENDS vector_example
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
)

add_custom_target(run_map_example
    COMMAND map_example
    DEPENDS map_example
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
)

add_custom_target(run_algorithm_example
    COMMAND algorithm_example
    DEPENDS algorithm_example
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
)

add_custom_target(run_thread_pool_example
    COMMAND thread_pool_example
    DEPENDS thread_pool_example
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
)

add_custom_target(run_all_examples
    DEPENDS run_vector_example run_map_example run_algorithm_example run_thread_pool_example
)

# Help target
add_custom_target(help_targets
    COMMAND ${CMAKE_COMMAND} -E echo "Available targets:"
    COMMAND ${CMAKE_COMMAND} -E echo "  mini_stl          - Build the library"
    COMMAND ${CMAKE_COMMAND} -E echo "  examples          - Build all examples"
    COMMAND ${CMAKE_COMMAND} -E echo "  tests            - Build all tests"
    COMMAND ${CMAKE_COMMAND} -E echo "  benchmarks       - Build all benchmarks"
    COMMAND ${CMAKE_COMMAND} -E echo "  all_examples     - Build examples, tests, and benchmarks"
    COMMAND ${CMAKE_COMMAND} -E echo "  run_vector_example - Run vector example"
    COMMAND ${CMAKE_COMMAND} -E echo "  run_map_example     - Run map example"
    COMMAND ${CMAKE_COMMAND} -E echo "  run_algorithm_example - Run algorithm example"
    COMMAND ${CMAKE_COMMAND} -E echo "  run_thread_pool_example - Run thread pool example"
    COMMAND ${CMAKE_COMMAND} -E echo "  run_all_examples  - Run all examples"
    COMMAND ${CMAKE_COMMAND} -E echo "  docs             - Generate documentation"
    COMMAND ${CMAKE_COMMAND} -E echo "  install          - Install the library"
    COMMAND ${CMAKE_COMMAND} -E echo "  help_targets     - Show this help"
)
