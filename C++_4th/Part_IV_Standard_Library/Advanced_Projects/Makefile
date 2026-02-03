# Makefile for Advanced Projects

# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2 -g -pthread
INCLUDES = -I.

# Directories
SRC_DIR = .
BUILD_DIR = build

# Source files
SOURCES = advanced_projects_demo.cpp
OBJECTS = $(SOURCES:%.cpp=$(BUILD_DIR)/%.o)
TARGET = $(BUILD_DIR)/advanced_projects

# Default target
all: $(TARGET)

# Create build directory
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Build target
$(TARGET): $(BUILD_DIR) $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(OBJECTS) -o $(TARGET)

# Compile source files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

# Clean build files
clean:
	rm -rf $(BUILD_DIR)

# Run the program
run: $(TARGET)
	./$(TARGET)

# Debug build
debug: CXXFLAGS += -DDEBUG -g3
debug: $(TARGET)

# Release build
release: CXXFLAGS += -DNDEBUG -O3
release: clean $(TARGET)

# Test the advanced projects
test: $(TARGET)
	./$(TARGET)

# Performance test
perf: $(TARGET)
	./$(TARGET) | grep "Performance" -A 5

# Memory check with valgrind
memcheck: $(TARGET)
	valgrind --leak-check=full --show-leak-kinds=all ./$(TARGET)

# Thread safety test
thread_test: $(TARGET)
	./$(TARGET) | grep "Thread" -A 10

# Show help
help:
	@echo "Available targets:"
	@echo "  all         - Build the advanced projects demo (default)"
	@echo "  clean       - Remove build files"
	@echo "  run         - Build and run the advanced projects demo"
	@echo "  debug       - Build with debug information"
	@echo "  release     - Build optimized release version"
	@echo "  test        - Run the advanced projects tests"
	@echo "  perf        - Run performance tests"
	@echo "  memcheck    - Run memory check with valgrind"
	@echo "  thread_test - Run thread safety tests"
	@echo "  help        - Show this help message"

# Phony targets
.PHONY: all clean run debug release test perf memcheck thread_test help

# Dependencies
$(BUILD_DIR)/advanced_projects_demo.o: thread_pool.h lock_free_queue.h
