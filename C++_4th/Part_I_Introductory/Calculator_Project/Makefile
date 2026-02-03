# Makefile for Calculator Project

# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2 -pthread
DEBUGFLAGS = -std=c++17 -Wall -Wextra -g -DDEBUG -pthread

# Directories
SRCDIR = .
OBJDIR = obj
TESTDIR = tests

# Source files
SOURCES = calculator.cpp main.cpp
OBJECTS = $(SOURCES:%.cpp=$(OBJDIR)/%.o)
TARGET = calculator

# Test files
TEST_SOURCES = $(TESTDIR)/test_calculator.cpp $(TESTDIR)/test_operations.cpp
TEST_OBJECTS = $(TEST_SOURCES:%.cpp=$(OBJDIR)/%.o)
TEST_TARGET = test_calculator

# Header files
HEADERS = calculator.h

# Default target
all: $(TARGET)

# Create object directory
$(OBJDIR):
	mkdir -p $(OBJDIR)

# Build main executable
$(TARGET): $(OBJDIR) $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(OBJECTS) -o $(TARGET)

# Build object files
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Build test executable
test: $(TEST_TARGET)

$(TEST_TARGET): $(OBJDIR) $(OBJECTS) $(TEST_OBJECTS)
	$(CXX) $(CXXFLAGS) $(OBJECTS) $(TEST_OBJECTS) -o $(TEST_TARGET)

# Build test object files
$(OBJDIR)/%.o: $(TESTDIR)/%.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Debug build
debug: CXXFLAGS = $(DEBUGFLAGS)
debug: $(TARGET)

# Clean build artifacts
clean:
	rm -rf $(OBJDIR) $(TARGET) $(TEST_TARGET)

# Run the calculator
run: $(TARGET)
	./$(TARGET)

# Run tests
test-run: $(TEST_TARGET)
	./$(TEST_TARGET)

# Install (copy to /usr/local/bin)
install: $(TARGET)
	sudo cp $(TARGET) /usr/local/bin/

# Uninstall
uninstall:
	sudo rm -f /usr/local/bin/$(TARGET)

# Help target
help:
	@echo "Available targets:"
	@echo "  all       - Build the calculator (default)"
	@echo "  debug     - Build with debug flags"
	@echo "  test      - Build test executable"
	@echo "  clean     - Remove build artifacts"
	@echo "  run       - Build and run the calculator"
	@echo "  test-run  - Build and run tests"
	@echo "  install   - Install calculator to /usr/local/bin"
	@echo "  uninstall - Remove calculator from /usr/local/bin"
	@echo "  help      - Show this help message"

# Phony targets
.PHONY: all clean debug test run test-run install uninstall help

# Dependencies
$(OBJDIR)/calculator.o: calculator.h
$(OBJDIR)/main.o: calculator.h
$(OBJDIR)/test_calculator.o: calculator.h
$(OBJDIR)/test_operations.o: calculator.h
