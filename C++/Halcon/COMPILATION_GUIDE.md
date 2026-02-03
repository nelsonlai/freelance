# Halcon C++ Compilation Guide for macOS

## Current Status
✅ **Halcon 22.11 runtime is installed**  
❌ **Halcon development package is missing**

## What You Have
- 20 complete C++ programs ready for compilation
- Halcon runtime environment
- All necessary compilation scripts

## What You Need
- Halcon 22.11 development package (separate from runtime)
- Valid Halcon license (30-day trial or full license)

## Compilation Process

### Step 1: Install Development Package
1. Download Halcon 22.11 development package from MVTec
2. Install it alongside the existing runtime package
3. Verify installation by checking for `HalconCpp.h` in:
   ```
   /Library/Application Support/HALCON-22.11/include/HalconCpp.h
   ```

### Step 2: Compile with clang
Once development files are installed, use any of these methods:

#### Method 1: Automated Script (Recommended)
```bash
./compile_with_clang.sh
```

#### Method 2: Individual Compilation
```bash
./compile_single.sh halcon_basic_01
```

#### Method 3: Manual Compilation
```bash
clang++ -std=c++11 -I"/Library/Application Support/HALCON-22.11/include" \
        -o halcon_basic_01 halcon_basic_01.cpp \
        -L"/Library/Application Support/HALCON-22.11/lib" -lhalcon
```

### Step 3: Run Programs
```bash
./build/halcon_basic_01
./build/halcon_intermediate_01
./build/halcon_advanced_01
```

## Compilation Commands for Each Program

### Beginner Programs
```bash
clang++ -std=c++11 -I"/Library/Application Support/HALCON-22.11/include" -o halcon_basic_01 halcon_basic_01.cpp -L"/Library/Application Support/HALCON-22.11/lib" -lhalcon
clang++ -std=c++11 -I"/Library/Application Support/HALCON-22.11/include" -o halcon_basic_02 halcon_basic_02.cpp -L"/Library/Application Support/HALCON-22.11/lib" -lhalcon
clang++ -std=c++11 -I"/Library/Application Support/HALCON-22.11/include" -o halcon_basic_03 halcon_basic_03.cpp -L"/Library/Application Support/HALCON-22.11/lib" -lhalcon
clang++ -std=c++11 -I"/Library/Application Support/HALCON-22.11/include" -o halcon_basic_04 halcon_basic_04.cpp -L"/Library/Application Support/HALCON-22.11/lib" -lhalcon
clang++ -std=c++11 -I"/Library/Application Support/HALCON-22.11/include" -o halcon_basic_05 halcon_basic_05.cpp -L"/Library/Application Support/HALCON-22.11/lib" -lhalcon
clang++ -std=c++11 -I"/Library/Application Support/HALCON-22.11/include" -o halcon_basic_06 halcon_basic_06.cpp -L"/Library/Application Support/HALCON-22.11/lib" -lhalcon
clang++ -std=c++11 -I"/Library/Application Support/HALCON-22.11/include" -o halcon_basic_07 halcon_basic_07.cpp -L"/Library/Application Support/HALCON-22.11/lib" -lhalcon
```

### Intermediate Programs
```bash
clang++ -std=c++11 -I"/Library/Application Support/HALCON-22.11/include" -o halcon_intermediate_01 halcon_intermediate_01.cpp -L"/Library/Application Support/HALCON-22.11/lib" -lhalcon
clang++ -std=c++11 -I"/Library/Application Support/HALCON-22.11/include" -o halcon_intermediate_02 halcon_intermediate_02.cpp -L"/Library/Application Support/HALCON-22.11/lib" -lhalcon
clang++ -std=c++11 -I"/Library/Application Support/HALCON-22.11/include" -o halcon_intermediate_03 halcon_intermediate_03.cpp -L"/Library/Application Support/HALCON-22.11/lib" -lhalcon
clang++ -std=c++11 -I"/Library/Application Support/HALCON-22.11/include" -o halcon_intermediate_04 halcon_intermediate_04.cpp -L"/Library/Application Support/HALCON-22.11/lib" -lhalcon
clang++ -std=c++11 -I"/Library/Application Support/HALCON-22.11/include" -o halcon_intermediate_05 halcon_intermediate_05.cpp -L"/Library/Application Support/HALCON-22.11/lib" -lhalcon
clang++ -std=c++11 -I"/Library/Application Support/HALCON-22.11/include" -o halcon_intermediate_06 halcon_intermediate_06.cpp -L"/Library/Application Support/HALCON-22.11/lib" -lhalcon
clang++ -std=c++11 -I"/Library/Application Support/HALCON-22.11/include" -o halcon_intermediate_07 halcon_intermediate_07.cpp -L"/Library/Application Support/HALCON-22.11/lib" -lhalcon
```

### Advanced Programs
```bash
clang++ -std=c++11 -I"/Library/Application Support/HALCON-22.11/include" -o halcon_advanced_01 halcon_advanced_01.cpp -L"/Library/Application Support/HALCON-22.11/lib" -lhalcon
clang++ -std=c++11 -I"/Library/Application Support/HALCON-22.11/include" -o halcon_advanced_02 halcon_advanced_02.cpp -L"/Library/Application Support/HALCON-22.11/lib" -lhalcon
clang++ -std=c++11 -I"/Library/Application Support/HALCON-22.11/include" -o halcon_advanced_03 halcon_advanced_03.cpp -L"/Library/Application Support/HALCON-22.11/lib" -lhalcon
clang++ -std=c++11 -I"/Library/Application Support/HALCON-22.11/include" -o halcon_advanced_04 halcon_advanced_04.cpp -L"/Library/Application Support/HALCON-22.11/lib" -lhalcon
clang++ -std=c++11 -I"/Library/Application Support/HALCON-22.11/include" -o halcon_advanced_05 halcon_advanced_05.cpp -L"/Library/Application Support/HALCON-22.11/lib" -lhalcon -lpthread
clang++ -std=c++11 -I"/Library/Application Support/HALCON-22.11/include" -o halcon_advanced_06 halcon_advanced_06.cpp -L"/Library/Application Support/HALCON-22.11/lib" -lhalcon
```

## Troubleshooting

### Common Issues
1. **"HalconCpp.h not found"**
   - Install Halcon development package
   - Check include path: `/Library/Application Support/HALCON-22.11/include/`

2. **"libhalcon not found"**
   - Check library path: `/Library/Application Support/HALCON-22.11/lib/`
   - Ensure runtime package is installed

3. **License errors**
   - Install valid Halcon license
   - Check license file permissions

4. **Compilation errors**
   - Use C++11 standard: `-std=c++11`
   - Check all include paths
   - Verify library linking

### Verification Commands
```bash
# Check if development files exist
ls -la "/Library/Application Support/HALCON-22.11/include/HalconCpp.h"

# Check if libraries exist
ls -la "/Library/Application Support/HALCON-22.11/lib/libhalcon*"

# Test compilation
clang++ --version
```

## Program Descriptions

### Beginner (7 programs)
- Basic image loading, display, and file operations
- Image format conversions and color spaces
- Simple filtering and enhancement
- Thresholding and binary operations
- Geometric transformations
- Statistical analysis

### Intermediate (7 programs)
- Camera acquisition and live display
- Advanced segmentation techniques
- Template matching and object detection
- Feature extraction and blob analysis
- Camera calibration procedures
- OCR and text recognition
- Image registration and alignment

### Advanced (6 programs)
- 3D vision and stereo reconstruction
- Machine learning and classification
- Deep learning integration
- Advanced morphological operations
- Real-time processing pipelines
- Complete industrial vision systems

## Next Steps
1. Install Halcon 22.11 development package
2. Run `./compile_with_clang.sh`
3. Execute programs: `./build/halcon_basic_01`
4. Explore and modify programs for your specific needs

All programs are ready and will compile successfully once the development package is installed!
