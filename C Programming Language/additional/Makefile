# Makefile for Additional Advanced C Programming Topics
# Comprehensive build system for all advanced implementations

# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -g
OPTFLAGS = -O2
DEBUGFLAGS = -O0 -DDEBUG
LDFLAGS = -lm

# Directories
POINTERS_DIR = pointers_arrays
MEMORY_DIR = memory_management
STRUCTURES_DIR = data_structures
ALGORITHMS_DIR = algorithms
ADVANCED_DIR = advanced_topics

# Source files
POINTERS_SOURCES = $(wildcard $(POINTERS_DIR)/*.c)
MEMORY_SOURCES = $(wildcard $(MEMORY_DIR)/*.c)
STRUCTURES_SOURCES = $(wildcard $(STRUCTURES_DIR)/*.c)
ALGORITHMS_SOURCES = $(wildcard $(ALGORITHMS_DIR)/*.c)
ADVANCED_SOURCES = $(wildcard $(ADVANCED_DIR)/*.c)

ALL_SOURCES = $(POINTERS_SOURCES) $(MEMORY_SOURCES) $(STRUCTURES_SOURCES) $(ALGORITHMS_SOURCES) $(ADVANCED_SOURCES)

# Executable targets
POINTERS_TARGETS = $(POINTERS_SOURCES:.c=)
MEMORY_TARGETS = $(MEMORY_SOURCES:.c=)
STRUCTURES_TARGETS = $(STRUCTURES_SOURCES:.c=)
ALGORITHMS_TARGETS = $(ALGORITHMS_SOURCES:.c=)
ADVANCED_TARGETS = $(ADVANCED_SOURCES:.c=)

ALL_TARGETS = $(ALL_SOURCES:.c=)

# Default target
all: pointers memory structures algorithms advanced

# Category targets
pointers: $(POINTERS_TARGETS)
memory: $(MEMORY_TARGETS)
structures: $(STRUCTURES_TARGETS)
algorithms: $(ALGORITHMS_TARGETS)
advanced: $(ADVANCED_TARGETS)

# Individual targets for easy access
pointers-arrays: $(POINTERS_DIR)/advanced_pointers_arrays
stack-memory: $(MEMORY_DIR)/stack_memory_management
structures-comp: $(STRUCTURES_DIR)/structures_comprehensive
linked-lists: $(STRUCTURES_DIR)/linked_lists_complete
stacks-queues: $(STRUCTURES_DIR)/stacks_queues_complete
binary-trees: $(STRUCTURES_DIR)/binary_trees_complete
recursion: $(ALGORITHMS_DIR)/recursion_advanced
sorting: $(ALGORITHMS_DIR)/sorting_algorithms_complete
huffman: $(ADVANCED_DIR)/huffman_coding_complete
bitwise: $(ADVANCED_DIR)/bitwise_operations_advanced

# Generic compilation rule
%: %.c
	@echo "Compiling $< -> $@"
	@$(CC) $(CFLAGS) $< -o $@ $(LDFLAGS)

# Special compilation rules for specific files
$(ALGORITHMS_DIR)/sorting_algorithms_complete: $(ALGORITHMS_DIR)/sorting_algorithms_complete.c
	@echo "Compiling sorting algorithms with optimizations"
	@$(CC) $(CFLAGS) $(OPTFLAGS) $< -o $@ $(LDFLAGS)

$(ADVANCED_DIR)/huffman_coding_complete: $(ADVANCED_DIR)/huffman_coding_complete.c
	@echo "Compiling Huffman coding with math library"
	@$(CC) $(CFLAGS) $< -o $@ $(LDFLAGS)

# Debug builds
debug: CFLAGS += $(DEBUGFLAGS)
debug: all

# Release builds
release: CFLAGS += $(OPTFLAGS) -DNDEBUG
release: CFLAGS := $(filter-out -g,$(CFLAGS))
release: all

# Test target
test: all
	@echo "Running basic functionality tests..."
	@echo "Testing Pointers and Arrays:"
	@echo "" | ./$(POINTERS_DIR)/advanced_pointers_arrays || true
	@echo "\nTesting Memory Management:"
	@echo "" | ./$(MEMORY_DIR)/stack_memory_management || true
	@echo "\nTesting Structures:"
	@echo "" | ./$(STRUCTURES_DIR)/structures_comprehensive || true
	@echo "\nTesting Linked Lists:"
	@echo "" | ./$(STRUCTURES_DIR)/linked_lists_complete || true
	@echo "\nTesting Binary Trees:"
	@echo "" | ./$(STRUCTURES_DIR)/binary_trees_complete || true
	@echo "\nTesting Recursion:"
	@echo "" | ./$(ALGORITHMS_DIR)/recursion_advanced || true
	@echo "\nTesting Huffman Coding:"
	@echo "" | ./$(ADVANCED_DIR)/huffman_coding_complete || true
	@echo "\nTesting Bitwise Operations:"
	@echo "" | ./$(ADVANCED_DIR)/bitwise_operations_advanced || true
	@echo "Basic tests completed!"

# Memory check target (requires valgrind)
memcheck: all
	@echo "Running memory checks..."
	@if command -v valgrind >/dev/null 2>&1; then \
		echo "Checking memory management:"; \
		echo "" | valgrind --leak-check=full --error-exitcode=1 ./$(MEMORY_DIR)/stack_memory_management; \
		echo "Checking linked lists:"; \
		echo "" | valgrind --leak-check=full --error-exitcode=1 ./$(STRUCTURES_DIR)/linked_lists_complete; \
		echo "Checking Huffman coding:"; \
		echo "" | valgrind --leak-check=full --error-exitcode=1 ./$(ADVANCED_DIR)/huffman_coding_complete; \
		echo "Memory checks completed!"; \
	else \
		echo "valgrind not found. Please install it for memory checking."; \
	fi

# Static analysis
analyze:
	@echo "Running static analysis..."
	@if command -v cppcheck >/dev/null 2>&1; then \
		cppcheck --enable=all --std=c99 --suppress=missingIncludeSystem $(ALL_SOURCES); \
	else \
		echo "cppcheck not found. Please install it for static analysis."; \
	fi

# Performance benchmarks
benchmark: release
	@echo "Running performance benchmarks..."
	@echo "Sorting algorithms benchmark:"
	@./$(ALGORITHMS_DIR)/sorting_algorithms_complete
	@echo "\nBinary tree operations benchmark:"
	@./$(STRUCTURES_DIR)/binary_trees_complete
	@echo "\nHuffman coding compression benchmark:"
	@./$(ADVANCED_DIR)/huffman_coding_complete

# Clean target
clean:
	@echo "Cleaning compiled files..."
	@find . -name "advanced_pointers_arrays" -delete
	@find . -name "stack_memory_management" -delete
	@find . -name "structures_comprehensive" -delete
	@find . -name "linked_lists_complete" -delete
	@find . -name "stacks_queues_complete" -delete
	@find . -name "binary_trees_complete" -delete
	@find . -name "recursion_advanced" -delete
	@find . -name "sorting_algorithms_complete" -delete
	@find . -name "huffman_coding_complete" -delete
	@find . -name "bitwise_operations_advanced" -delete
	@find . -name "*.o" -delete
	@find . -name "*.exe" -delete
	@find . -name "a.out" -delete
	@echo "Clean completed!"

# Install target
install: all
	@echo "Installing executables to ./bin/"
	@mkdir -p bin
	@cp $(ALL_TARGETS) bin/
	@echo "Installation completed!"

# Documentation generation
docs:
	@echo "Generating documentation..."
	@echo "Advanced C Programming Topics" > TOPICS_INDEX.txt
	@echo "=============================" >> TOPICS_INDEX.txt
	@echo "" >> TOPICS_INDEX.txt
	@echo "POINTERS AND ARRAYS:" >> TOPICS_INDEX.txt
	@find $(POINTERS_DIR) -name "*.c" | sort >> TOPICS_INDEX.txt
	@echo "" >> TOPICS_INDEX.txt
	@echo "MEMORY MANAGEMENT:" >> TOPICS_INDEX.txt
	@find $(MEMORY_DIR) -name "*.c" | sort >> TOPICS_INDEX.txt
	@echo "" >> TOPICS_INDEX.txt
	@echo "DATA STRUCTURES:" >> TOPICS_INDEX.txt
	@find $(STRUCTURES_DIR) -name "*.c" | sort >> TOPICS_INDEX.txt
	@echo "" >> TOPICS_INDEX.txt
	@echo "ALGORITHMS:" >> TOPICS_INDEX.txt
	@find $(ALGORITHMS_DIR) -name "*.c" | sort >> TOPICS_INDEX.txt
	@echo "" >> TOPICS_INDEX.txt
	@echo "ADVANCED TOPICS:" >> TOPICS_INDEX.txt
	@find $(ADVANCED_DIR) -name "*.c" | sort >> TOPICS_INDEX.txt
	@echo "Documentation generated: TOPICS_INDEX.txt"

# Help target
help:
	@echo "Advanced C Programming Topics Makefile"
	@echo "======================================"
	@echo ""
	@echo "Available targets:"
	@echo "  all          - Compile all programs"
	@echo "  pointers     - Compile pointer/array programs"
	@echo "  memory       - Compile memory management programs"
	@echo "  structures   - Compile data structure programs"
	@echo "  algorithms   - Compile algorithm programs"
	@echo "  advanced     - Compile advanced topic programs"
	@echo ""
	@echo "Individual program targets:"
	@echo "  pointers-arrays    - Advanced pointers and arrays"
	@echo "  stack-memory       - Stack memory management"
	@echo "  structures-comp    - Comprehensive structures"
	@echo "  linked-lists       - Complete linked lists"
	@echo "  stacks-queues      - Stacks and queues"
	@echo "  binary-trees       - Binary trees and BST"
	@echo "  recursion          - Advanced recursion"
	@echo "  sorting            - Sorting algorithms"
	@echo "  huffman            - Huffman coding"
	@echo "  bitwise            - Bitwise operations"
	@echo ""
	@echo "Build variants:"
	@echo "  debug        - Compile with debug flags"
	@echo "  release      - Compile with optimizations"
	@echo ""
	@echo "Testing and analysis:"
	@echo "  test         - Run basic functionality tests"
	@echo "  memcheck     - Run memory leak detection"
	@echo "  analyze      - Run static code analysis"
	@echo "  benchmark    - Run performance benchmarks"
	@echo ""
	@echo "Utilities:"
	@echo "  clean        - Remove compiled files"
	@echo "  install      - Copy executables to bin/"
	@echo "  docs         - Generate documentation index"
	@echo "  help         - Show this help message"
	@echo ""
	@echo "Example usage:"
	@echo "  make huffman     # Compile Huffman coding"
	@echo "  make test        # Run all tests"
	@echo "  make memcheck    # Check for memory leaks"
	@echo "  make benchmark   # Run performance tests"

# Phony targets
.PHONY: all pointers memory structures algorithms advanced
.PHONY: pointers-arrays stack-memory structures-comp linked-lists stacks-queues
.PHONY: binary-trees recursion sorting huffman bitwise
.PHONY: debug release test memcheck analyze benchmark clean install docs help

