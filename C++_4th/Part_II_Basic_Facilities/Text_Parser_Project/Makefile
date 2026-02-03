# Makefile for Text Parser Project

# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2 -g
INCLUDES = -I.

# Directories
SRC_DIR = .
BUILD_DIR = build

# Source files
SOURCES = parser.cpp main.cpp
OBJECTS = $(SOURCES:%.cpp=$(BUILD_DIR)/%.o)
TARGET = $(BUILD_DIR)/text_parser

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

# Install (copy to system)
install: $(TARGET)
	cp $(TARGET) /usr/local/bin/

# Uninstall
uninstall:
	rm -f /usr/local/bin/text_parser

# Test the parser
test: $(TARGET)
	./$(TARGET)

# Create a simple test file
test-file:
	@echo "Creating test file..."
	@echo 'int main() { return 0; }' > test.cpp
	@echo "Test file created: test.cpp"

# Parse test file
test-parse: $(TARGET) test-file
	./$(TARGET) < test.cpp

# Show help
help:
	@echo "Available targets:"
	@echo "  all       - Build the text parser (default)"
	@echo "  clean     - Remove build files"
	@echo "  run       - Build and run the text parser"
	@echo "  debug     - Build with debug information"
	@echo "  release   - Build optimized release version"
	@echo "  install   - Install to system"
	@echo "  uninstall - Remove from system"
	@echo "  test      - Run the parser tests"
	@echo "  test-file - Create a test C++ file"
	@echo "  test-parse- Parse the test file"
	@echo "  help      - Show this help message"

# Phony targets
.PHONY: all clean run debug release install uninstall test test-file test-parse help

# Dependencies
$(BUILD_DIR)/parser.o: parser.h
$(BUILD_DIR)/main.o: parser.h
