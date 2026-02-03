# Development Environment Setup Guide
## C Programming Curriculum

---

## SYSTEM REQUIREMENTS

### Minimum Hardware Requirements
- **Processor**: 1 GHz or faster
- **RAM**: 2 GB minimum, 4 GB recommended
- **Storage**: 5 GB free space for development tools and projects
- **Display**: 1024x768 resolution minimum

### Supported Operating Systems
- **Windows**: Windows 10/11 (64-bit recommended)
- **macOS**: macOS 10.14 or later
- **Linux**: Ubuntu 18.04+, CentOS 7+, Fedora 30+, or equivalent

---

## COMPILER INSTALLATION

### Windows Setup

#### Option 1: MinGW-w64 (Recommended)
```bash
# Download from: https://www.mingw-w64.org/downloads/
# Or use package manager (if available):
winget install mingw-w64

# Verify installation
gcc --version
```

#### Option 2: Microsoft Visual Studio Build Tools
```bash
# Download Visual Studio Community (free)
# Include "Desktop development with C++" workload
# Provides MSVC compiler

# Command line usage:
cl.exe program.c
```

#### Option 3: Windows Subsystem for Linux (WSL)
```bash
# Enable WSL in Windows Features
# Install Ubuntu from Microsoft Store
# Then follow Linux setup instructions
```

### macOS Setup

#### Using Xcode Command Line Tools (Recommended)
```bash
# Install Xcode Command Line Tools
xcode-select --install

# Verify installation
gcc --version
clang --version
```

#### Using Homebrew
```bash
# Install Homebrew (if not already installed)
/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"

# Install GCC
brew install gcc

# Verify installation
gcc-13 --version  # Version number may vary
```

### Linux Setup

#### Ubuntu/Debian
```bash
# Update package list
sudo apt update

# Install build essentials
sudo apt install build-essential

# Install additional tools
sudo apt install gdb valgrind

# Verify installation
gcc --version
gdb --version
```

#### CentOS/RHEL/Fedora
```bash
# CentOS/RHEL
sudo yum groupinstall "Development Tools"
sudo yum install gdb valgrind

# Fedora
sudo dnf groupinstall "Development Tools"
sudo dnf install gdb valgrind

# Verify installation
gcc --version
```

#### Arch Linux
```bash
# Install base development tools
sudo pacman -S base-devel

# Install debugging tools
sudo pacman -S gdb valgrind

# Verify installation
gcc --version
```

---

## INTEGRATED DEVELOPMENT ENVIRONMENTS (IDEs)

### Beginner-Friendly IDEs

#### Code::Blocks (Cross-platform, Free)
**Installation:**
- **Windows**: Download from http://codeblocks.org/
- **macOS**: Download from official website or use Homebrew: `brew install --cask codeblocks`
- **Linux**: `sudo apt install codeblocks` (Ubuntu) or equivalent

**Configuration:**
1. Open Code::Blocks
2. Go to Settings → Compiler
3. Select GNU GCC Compiler
4. Verify compiler path is correct
5. Test with a simple "Hello World" program

#### Dev-C++ (Windows only, Free)
**Installation:**
1. Download from https://sourceforge.net/projects/orwelldevcpp/
2. Run installer and follow prompts
3. Launch and create new C project

### Professional IDEs

#### Visual Studio Code (Cross-platform, Free)
**Installation:**
```bash
# Windows
winget install Microsoft.VisualStudioCode

# macOS
brew install --cask visual-studio-code

# Linux (Ubuntu)
sudo snap install code --classic
```

**C/C++ Extension Setup:**
1. Install "C/C++" extension by Microsoft
2. Install "Code Runner" extension (optional)
3. Configure compiler path in settings.json:

```json
{
    "C_Cpp.default.compilerPath": "/usr/bin/gcc",
    "C_Cpp.default.cStandard": "c17",
    "C_Cpp.default.intelliSenseMode": "gcc-x64"
}
```

#### CLion (JetBrains, Paid)
**Features:**
- Advanced debugging
- Code analysis
- Refactoring tools
- CMake integration

**Setup:**
1. Download from https://www.jetbrains.com/clion/
2. 30-day free trial, student licenses available
3. Create new C project
4. Configure toolchain (usually auto-detected)

### Text Editors with C Support

#### Vim/Neovim
**Basic C Configuration (.vimrc):**
```vim
" Enable syntax highlighting
syntax on

" Enable line numbers
set number

" Set tab width for C
autocmd FileType c setlocal tabstop=4 shiftwidth=4 expandtab

" Compile shortcut
autocmd FileType c nnoremap <F5> :!gcc % -o %< && ./%< <CR>
```

#### Emacs
**Basic C Configuration:**
```elisp
;; In .emacs or init.el
(add-hook 'c-mode-hook
          (lambda ()
            (setq c-basic-offset 4)
            (setq indent-tabs-mode nil)))

;; Compile command
(global-set-key (kbd "<f5>") 'compile)
```

---

## BUILD TOOLS AND AUTOMATION

### Make Utility

#### Installation
```bash
# Windows (MinGW)
mingw-get install msys-make

# macOS (included with Xcode tools)
# Linux (usually pre-installed)
sudo apt install make  # Ubuntu
```

#### Sample Makefile
```makefile
# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -g

# Target executable
TARGET = program

# Source files
SOURCES = main.c utils.c student.c

# Object files
OBJECTS = $(SOURCES:.c=.o)

# Default target
all: $(TARGET)

# Link object files to create executable
$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(TARGET)

# Compile source files to object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean build files
clean:
	rm -f $(OBJECTS) $(TARGET)

# Install target
install: $(TARGET)
	cp $(TARGET) /usr/local/bin/

# Phony targets
.PHONY: all clean install
```

### CMake (Advanced)

#### Installation
```bash
# Windows
winget install Kitware.CMake

# macOS
brew install cmake

# Linux
sudo apt install cmake  # Ubuntu
```

#### Sample CMakeLists.txt
```cmake
cmake_minimum_required(VERSION 3.10)
project(MyProject C)

# Set C standard
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Compiler flags
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra")
set(CMAKE_C_FLAGS_DEBUG "-g -O0")
set(CMAKE_C_FLAGS_RELEASE "-O3 -DNDEBUG")

# Include directories
include_directories(include)

# Source files
set(SOURCES
    src/main.c
    src/utils.c
    src/student.c
)

# Create executable
add_executable(program ${SOURCES})

# Link libraries (if needed)
# target_link_libraries(program m)  # Math library
```

---

## DEBUGGING TOOLS

### GDB (GNU Debugger)

#### Basic Setup
```bash
# Compile with debug symbols
gcc -g -o program program.c

# Start GDB
gdb ./program
```

#### GDB Configuration (.gdbinit)
```gdb
# Enable pretty printing
set print pretty on
set print array on
set print array-indexes on

# History
set history save on
set history size 10000

# Auto-load symbols
set auto-load safe-path /

# Custom commands
define parray
    if $argc == 2
        set $i = 0
        while $i < $arg1
            printf "[%d] = %d\n", $i, $arg0[$i]
            set $i = $i + 1
        end
    else
        printf "Usage: parray <array> <size>\n"
    end
end
```

### Valgrind (Memory Debugging)

#### Installation
```bash
# Linux
sudo apt install valgrind  # Ubuntu
sudo yum install valgrind  # CentOS

# macOS (limited support)
# Not officially supported, use alternatives like AddressSanitizer
```

#### Usage Examples
```bash
# Memory leak detection
valgrind --leak-check=full --show-leak-kinds=all ./program

# Memory error detection
valgrind --tool=memcheck ./program

# Cache profiling
valgrind --tool=cachegrind ./program

# Call graph profiling
valgrind --tool=callgrind ./program
```

### AddressSanitizer (ASan)

#### Usage
```bash
# Compile with AddressSanitizer
gcc -fsanitize=address -g -o program program.c

# Run program (will detect memory errors automatically)
./program
```

---

## VERSION CONTROL SETUP

### Git Installation and Configuration

#### Installation
```bash
# Windows
winget install Git.Git

# macOS
brew install git

# Linux
sudo apt install git  # Ubuntu
```

#### Initial Configuration
```bash
# Set user information
git config --global user.name "Your Name"
git config --global user.email "your.email@example.com"

# Set default editor
git config --global core.editor "vim"  # or "code" for VS Code

# Set default branch name
git config --global init.defaultBranch main

# Enable colored output
git config --global color.ui auto
```

#### Project Setup
```bash
# Initialize repository
git init

# Create .gitignore for C projects
echo "*.o
*.exe
*.out
a.out
*.so
*.dylib
.DS_Store
Thumbs.db
*.tmp
*.swp
*~" > .gitignore

# Add and commit files
git add .
git commit -m "Initial commit"
```

---

## TESTING FRAMEWORKS

### Unity Test Framework

#### Installation
```bash
# Clone Unity repository
git clone https://github.com/ThrowTheSwitch/Unity.git

# Or download as submodule
git submodule add https://github.com/ThrowTheSwitch/Unity.git Unity
```

#### Sample Test File
```c
// test_math.c
#include "Unity/src/unity.h"
#include "math_functions.h"

void setUp(void) {
    // Set up test fixtures, if any
}

void tearDown(void) {
    // Clean up after tests
}

void test_addition(void) {
    TEST_ASSERT_EQUAL(5, add(2, 3));
    TEST_ASSERT_EQUAL(0, add(-1, 1));
    TEST_ASSERT_EQUAL(-5, add(-2, -3));
}

void test_multiplication(void) {
    TEST_ASSERT_EQUAL(6, multiply(2, 3));
    TEST_ASSERT_EQUAL(0, multiply(0, 5));
    TEST_ASSERT_EQUAL(-10, multiply(-2, 5));
}

int main(void) {
    UNITY_BEGIN();
    
    RUN_TEST(test_addition);
    RUN_TEST(test_multiplication);
    
    return UNITY_END();
}
```

#### Test Makefile
```makefile
# Test configuration
TEST_DIR = tests
UNITY_DIR = Unity/src

# Test sources
TEST_SOURCES = $(wildcard $(TEST_DIR)/*.c)
TEST_OBJECTS = $(TEST_SOURCES:.c=.o)

# Unity source
UNITY_SOURCE = $(UNITY_DIR)/unity.c
UNITY_OBJECT = $(UNITY_SOURCE:.c=.o)

# Test executable
TEST_TARGET = run_tests

# Build tests
test: $(TEST_TARGET)
	./$(TEST_TARGET)

$(TEST_TARGET): $(TEST_OBJECTS) $(UNITY_OBJECT)
	$(CC) $(TEST_OBJECTS) $(UNITY_OBJECT) -o $(TEST_TARGET)

# Clean test files
clean-test:
	rm -f $(TEST_OBJECTS) $(UNITY_OBJECT) $(TEST_TARGET)

.PHONY: test clean-test
```

---

## DOCUMENTATION TOOLS

### Doxygen

#### Installation
```bash
# Windows
winget install doxygen.doxygen

# macOS
brew install doxygen

# Linux
sudo apt install doxygen  # Ubuntu
```

#### Configuration
```bash
# Generate default configuration
doxygen -g Doxyfile

# Edit Doxyfile for your project
# Key settings:
PROJECT_NAME = "My C Project"
INPUT = src include
RECURSIVE = YES
GENERATE_HTML = YES
GENERATE_LATEX = NO
```

#### Sample Documented Code
```c
/**
 * @file math_functions.h
 * @brief Mathematical utility functions
 * @author Your Name
 * @date 2024
 */

#ifndef MATH_FUNCTIONS_H
#define MATH_FUNCTIONS_H

/**
 * @brief Adds two integers
 * @param a First integer
 * @param b Second integer
 * @return Sum of a and b
 */
int add(int a, int b);

/**
 * @brief Calculates factorial of a number
 * @param n Non-negative integer
 * @return Factorial of n, or -1 if n is negative
 * @warning This function does not handle large numbers well
 */
long factorial(int n);

#endif // MATH_FUNCTIONS_H
```

---

## PERFORMANCE PROFILING TOOLS

### gprof (GNU Profiler)

#### Usage
```bash
# Compile with profiling enabled
gcc -pg -o program program.c

# Run program to generate profile data
./program

# Generate profile report
gprof program gmon.out > profile.txt
```

### perf (Linux Performance Tools)
```bash
# Install perf
sudo apt install linux-tools-common linux-tools-generic

# Profile program execution
perf record ./program
perf report

# CPU profiling
perf stat ./program
```

---

## CONTINUOUS INTEGRATION SETUP

### GitHub Actions for C Projects

#### .github/workflows/ci.yml
```yaml
name: C/C++ CI

on:
  push:
    branches: [ main, develop ]
  pull_request:
    branches: [ main ]

jobs:
  build:
    runs-on: ubuntu-latest
    
    steps:
    - uses: actions/checkout@v3
    
    - name: Install dependencies
      run: |
        sudo apt-get update
        sudo apt-get install -y build-essential valgrind
    
    - name: Build
      run: make
    
    - name: Run tests
      run: make test
    
    - name: Memory check
      run: valgrind --leak-check=full --error-exitcode=1 ./program
    
    - name: Static analysis
      run: |
        sudo apt-get install -y cppcheck
        cppcheck --error-exitcode=1 src/
```

---

## TROUBLESHOOTING COMMON SETUP ISSUES

### Windows Issues

#### MinGW Path Problems
```bash
# Add MinGW to PATH environment variable
# Typical paths:
C:\MinGW\bin
C:\msys64\mingw64\bin

# Verify in Command Prompt
echo %PATH%
gcc --version
```

#### Visual Studio Integration
```bash
# Use Developer Command Prompt for VS
# Or set environment variables:
call "C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Auxiliary\Build\vcvars64.bat"
```

### macOS Issues

#### Command Line Tools Missing
```bash
# Reinstall Xcode Command Line Tools
sudo xcode-select --reset
xcode-select --install
```

#### Homebrew Issues
```bash
# Update Homebrew
brew update
brew doctor

# Fix permissions
sudo chown -R $(whoami) /usr/local/var/homebrew
```

### Linux Issues

#### Missing Development Packages
```bash
# Ubuntu/Debian
sudo apt install build-essential libc6-dev

# CentOS/RHEL
sudo yum groupinstall "Development Tools"
sudo yum install glibc-devel
```

#### Permission Issues
```bash
# Fix executable permissions
chmod +x program

# Fix directory permissions
chmod 755 project_directory
```

---

## RECOMMENDED LEARNING RESOURCES

### Online Compilers (for Quick Testing)
- **Repl.it**: https://replit.com/
- **OnlineGDB**: https://www.onlinegdb.com/
- **Compiler Explorer**: https://godbolt.org/

### Documentation and References
- **C Reference**: https://en.cppreference.com/w/c
- **GNU C Library**: https://www.gnu.org/software/libc/manual/
- **POSIX Standards**: https://pubs.opengroup.org/onlinepubs/9699919799/

### Practice Platforms
- **LeetCode**: C programming challenges
- **HackerRank**: C domain problems
- **Codeforces**: Programming contests
- **Project Euler**: Mathematical problems

---

This setup guide provides comprehensive instructions for establishing a complete C programming development environment across all major platforms, ensuring students have access to professional-grade tools and resources for their learning journey.
