# Makefile for C Programming Solutions
# Compiles all solution files with appropriate flags

# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -g
LDFLAGS = -lm

# Directories
BEGINNER_DIR = beginner
INTERMEDIATE_DIR = intermediate
ADVANCED_DIR = advanced
EXPERT_DIR = expert

# Find all C source files
BEGINNER_SOURCES = $(shell find $(BEGINNER_DIR) -name "*.c")
INTERMEDIATE_SOURCES = $(shell find $(INTERMEDIATE_DIR) -name "*.c")
ADVANCED_SOURCES = $(shell find $(ADVANCED_DIR) -name "*.c")
EXPERT_SOURCES = $(shell find $(EXPERT_DIR) -name "*.c")

ALL_SOURCES = $(BEGINNER_SOURCES) $(INTERMEDIATE_SOURCES) $(ADVANCED_SOURCES) $(EXPERT_SOURCES)

# Generate executable names (remove .c extension and directory path)
BEGINNER_TARGETS = $(BEGINNER_SOURCES:.c=)
INTERMEDIATE_TARGETS = $(INTERMEDIATE_SOURCES:.c=)
ADVANCED_TARGETS = $(ADVANCED_SOURCES:.c=)
EXPERT_TARGETS = $(EXPERT_SOURCES:.c=)

ALL_TARGETS = $(ALL_SOURCES:.c=)

# Default target
all: beginner intermediate advanced expert

# Level-specific targets
beginner: $(BEGINNER_TARGETS)
intermediate: $(INTERMEDIATE_TARGETS)
advanced: $(ADVANCED_TARGETS)
expert: $(EXPERT_TARGETS)

# Week-specific targets
week1: $(filter %/week1/%,$(BEGINNER_TARGETS))
week2: $(filter %/week2/%,$(BEGINNER_TARGETS))
week3: $(filter %/week3/%,$(BEGINNER_TARGETS))
week4: $(filter %/week4/%,$(BEGINNER_TARGETS))
week5: $(filter %/week5/%,$(INTERMEDIATE_TARGETS))
week6: $(filter %/week6/%,$(INTERMEDIATE_TARGETS))
week7: $(filter %/week7/%,$(INTERMEDIATE_TARGETS))
week8: $(filter %/week8/%,$(INTERMEDIATE_TARGETS))
week9: $(filter %/week9/%,$(ADVANCED_TARGETS))
week10: $(filter %/week10/%,$(ADVANCED_TARGETS))
week11: $(filter %/week11/%,$(ADVANCED_TARGETS))
week13: $(filter %/week13/%,$(EXPERT_TARGETS))
week14: $(filter %/week14/%,$(EXPERT_TARGETS))

# Generic rule to compile C files
%: %.c
	@echo "Compiling $< -> $@"
	@$(CC) $(CFLAGS) $< -o $@ $(LDFLAGS)

# Special compilation rules for system programming examples (Unix/Linux only)
expert/week13/%: expert/week13/%.c
	@echo "Compiling system program $< -> $@"
	@$(CC) $(CFLAGS) -D_GNU_SOURCE $< -o $@ $(LDFLAGS)

# Test target - compile and run simple tests
test: beginner
	@echo "Running basic tests..."
	@echo "Testing Week 1 solutions:"
	@echo "Hello World Test:" && echo "" | ./beginner/week1/solution_1_1_hello_world || true
	@echo "Pattern Test:" && echo "" | ./beginner/week1/solution_1_2_asterisk_pattern || true
	@echo "Numbers Test:" && echo "" | ./beginner/week1/solution_1_3_numbers_1_to_10 || true
	@echo "Testing Week 2 solutions:"
	@echo "Rectangle Area Test:" && echo "5 10" | ./beginner/week2/solution_2_1_rectangle_area || true
	@echo "Temperature Test:" && echo "100" | ./beginner/week2/solution_2_2_temperature_converter || true
	@echo "Basic tests completed!"

# Clean target
clean:
	@echo "Cleaning compiled files..."
	@find . -name "solution_*" -type f ! -name "*.c" -delete
	@find . -name "*.o" -delete
	@find . -name "*.exe" -delete
	@find . -name "a.out" -delete
	@echo "Clean completed!"

# Install target (copy executables to a bin directory)
install: all
	@echo "Installing executables to ./bin/"
	@mkdir -p bin
	@find . -name "solution_*" -type f ! -name "*.c" -exec cp {} bin/ \;
	@echo "Installation completed!"

# Help target
help:
	@echo "C Programming Solutions Makefile"
	@echo "================================="
	@echo ""
	@echo "Available targets:"
	@echo "  all          - Compile all solutions"
	@echo "  beginner     - Compile beginner level solutions (weeks 1-4)"
	@echo "  intermediate - Compile intermediate level solutions (weeks 5-8)"
	@echo "  advanced     - Compile advanced level solutions (weeks 9-12)"
	@echo "  expert       - Compile expert level solutions (weeks 13-16)"
	@echo ""
	@echo "Week-specific targets:"
	@echo "  week1, week2, week3, week4    - Beginner weeks"
	@echo "  week5, week6, week7, week8    - Intermediate weeks"
	@echo "  week9, week10, week11         - Advanced weeks"
	@echo "  week13, week14                - Expert weeks"
	@echo ""
	@echo "Other targets:"
	@echo "  test         - Compile and run basic tests"
	@echo "  clean        - Remove compiled files"
	@echo "  install      - Copy executables to bin/ directory"
	@echo "  help         - Show this help message"
	@echo ""
	@echo "Example usage:"
	@echo "  make beginner    # Compile all beginner solutions"
	@echo "  make week5       # Compile only week 5 solutions"
	@echo "  make test        # Run basic functionality tests"
	@echo "  make clean       # Clean up compiled files"

# Debug target - compile with extra debugging info
debug: CFLAGS += -DDEBUG -O0 -ggdb3
debug: all

# Release target - compile with optimizations
release: CFLAGS += -O2 -DNDEBUG
release: CFLAGS := $(filter-out -g,$(CFLAGS))
release: all

# Static analysis target (requires cppcheck)
analyze:
	@echo "Running static analysis..."
	@if command -v cppcheck >/dev/null 2>&1; then \
		cppcheck --enable=all --std=c99 --suppress=missingIncludeSystem $(ALL_SOURCES); \
	else \
		echo "cppcheck not found. Please install it for static analysis."; \
	fi

# Memory check target (requires valgrind)
memcheck: beginner
	@echo "Running memory checks on selected programs..."
	@if command -v valgrind >/dev/null 2>&1; then \
		echo "Checking factorial program:"; \
		echo "5" | valgrind --leak-check=full --error-exitcode=1 ./beginner/week4/solution_4_2_factorial_calculator; \
		echo "Memory check completed!"; \
	else \
		echo "valgrind not found. Please install it for memory checking."; \
	fi

# Documentation target
docs:
	@echo "Generating documentation..."
	@echo "Solution files by category:" > SOLUTIONS_INDEX.txt
	@echo "==========================" >> SOLUTIONS_INDEX.txt
	@echo "" >> SOLUTIONS_INDEX.txt
	@echo "BEGINNER LEVEL:" >> SOLUTIONS_INDEX.txt
	@find beginner -name "*.c" | sort >> SOLUTIONS_INDEX.txt
	@echo "" >> SOLUTIONS_INDEX.txt
	@echo "INTERMEDIATE LEVEL:" >> SOLUTIONS_INDEX.txt
	@find intermediate -name "*.c" | sort >> SOLUTIONS_INDEX.txt
	@echo "" >> SOLUTIONS_INDEX.txt
	@echo "ADVANCED LEVEL:" >> SOLUTIONS_INDEX.txt
	@find advanced -name "*.c" | sort >> SOLUTIONS_INDEX.txt
	@echo "" >> SOLUTIONS_INDEX.txt
	@echo "EXPERT LEVEL:" >> SOLUTIONS_INDEX.txt
	@find expert -name "*.c" | sort >> SOLUTIONS_INDEX.txt
	@echo "Documentation generated: SOLUTIONS_INDEX.txt"

# Phony targets
.PHONY: all beginner intermediate advanced expert test clean install help debug release analyze memcheck docs
.PHONY: week1 week2 week3 week4 week5 week6 week7 week8 week9 week10 week11 week13 week14
