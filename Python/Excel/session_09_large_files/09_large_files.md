# Session 9: Working with Large Excel Files - Comprehensive Guide

## Introduction

Large Excel files (10MB+, 100K+ rows) require special techniques to handle efficiently. This session teaches you memory-efficient reading, chunking, streaming, optimization, and best practices for production environments.

## Understanding the Challenge

### Why Large Files Are Different

**Memory Issues:**
- pandas loads entire file into RAM
- 1GB Excel file can use 5GB+ memory
- Can crash Python or system

**Performance Issues:**
- Slow loading (minutes vs seconds)
- Slow processing
- Poor user experience

**Solutions:**
- Chunking (process in pieces)
- Streaming (read row-by-row)
- Optimization (efficient code)
- Alternative formats (CSV, Parquet)

## Part 1: Measuring File Size and Memory

### Check File Size

```python
from pathlib import Path

file_path = Path('large_file.xlsx')

# File size in bytes
size_bytes = file_path.stat().st_size

# Convert to MB
size_mb = size_bytes / (1024 * 1024)

print(f"File size: {size_mb:.2f} MB")

# Categorize
if size_mb < 10:
    print("Small file - normal processing OK")
elif size_mb < 50:
    print("Medium file - consider chunking")
elif size_mb < 200:
    print("Large file - use chunking/streaming")
else:
    print("Very large file - use optimized strategies")
```

### Measure Memory Usage

```python
import pandas as pd
import psutil
import os

def measure_memory_usage(func):
    """Decorator to measure memory usage"""
    def wrapper(*args, **kwargs):
        process = psutil.Process(os.getpid())
        mem_before = process.memory_info().rss / 1024 / 1024  # MB
        
        result = func(*args, **kwargs)
        
        mem_after = process.memory_info().rss / 1024 / 1024  # MB
        print(f"Memory used: {mem_after - mem_before:.2f} MB")
        
        return result
    return wrapper

@measure_memory_usage
def load_file(filename):
    return pd.read_excel(filename)

df = load_file('large_file.xlsx')
```

## Part 2: Chunking - Processing in Pieces

### Read Specific Rows

```python
import pandas as pd

# Read first 10,000 rows only
df = pd.read_excel('large_file.xlsx', nrows=10000)

# Read rows 10000-20000
df = pd.read_excel('large_file.xlsx', skiprows=range(1, 10000), nrows=10000)
```

### Process File in Chunks

```python
import pandas as pd

def process_in_chunks(file_path, chunk_size=10000):
    """
    Process large file in chunks
    """
    results = []
    
    # Read file info to get total rows
    df_sample = pd.read_excel(file_path, nrows=1)
    
    skip_rows = 0
    chunk_num = 0
    
    while True:
        # Read chunk
        if skip_rows > 0:
            df_chunk = pd.read_excel(
                file_path,
                skiprows=range(1, skip_rows + 1),
                nrows=chunk_size
            )
        else:
            df_chunk = pd.read_excel(file_path, nrows=chunk_size)
        
        if df_chunk.empty:
            break
        
        chunk_num += 1
        print(f"Processing chunk {chunk_num}: {len(df_chunk)} rows")
        
        # Process chunk
        result = df_chunk['Value'].sum()  # Example processing
        results.append(result)
        
        skip_rows += chunk_size
        
        if len(df_chunk) < chunk_size:
            break
    
    return sum(results)

# Usage
total = process_in_chunks('large_file.xlsx', chunk_size=10000)
print(f"Total: {total}")
```

### Write in Chunks

```python
import pandas as pd

def write_large_dataframe(df, output_file, chunk_size=10000):
    """
    Write large DataFrame in chunks
    """
    total_rows = len(df)
    
    with pd.ExcelWriter(output_file, engine='xlsxwriter') as writer:
        for start_row in range(0, total_rows, chunk_size):
            end_row = min(start_row + chunk_size, total_rows)
            df_chunk = df.iloc[start_row:end_row]
            
            # Write chunk
            if start_row == 0:
                df_chunk.to_excel(
                    writer,
                    sheet_name='Data',
                    index=False,
                    startrow=0
                )
            else:
                df_chunk.to_excel(
                    writer,
                    sheet_name='Data',
                    index=False,
                    startrow=start_row,
                    header=False
                )
            
            print(f"Wrote rows {start_row} to {end_row}")
```

## Part 3: Streaming with openpyxl

### Read-Only Mode

```python
from openpyxl import load_workbook

# Read-only mode (memory efficient)
wb = load_workbook('large_file.xlsx', read_only=True)
ws = wb.active

# Iterate through rows (streaming)
row_count = 0
total_sum = 0

for row in ws.iter_rows(min_row=2, values_only=True):
    if row[0] is not None:  # Check first column
        row_count += 1
        total_sum += row[2]  # Sum third column
        
        if row_count % 10000 == 0:
            print(f"Processed {row_count} rows...")

print(f"Total rows: {row_count}")
print(f"Sum: {total_sum}")

wb.close()
```

### Write-Only Mode

```python
from openpyxl import Workbook

# Write-only mode (memory efficient)
wb = Workbook(write_only=True)
ws = wb.create_sheet()

# Write header
ws.append(['ID', 'Name', 'Value'])

# Write large amount of data
for i in range(1, 100001):
    ws.append([i, f'Item_{i}', i * 100])
    
    if i % 10000 == 0:
        print(f"Wrote {i} rows...")

wb.save('large_output.xlsx')
print("Done!")
```

## Part 4: Optimization Techniques

### Use Efficient Data Types

```python
import pandas as pd

# Read with default types
df = pd.read_excel('data.xlsx')
print(f"Memory usage (default): {df.memory_usage(deep=True).sum() / 1024 / 1024:.2f} MB")

# Optimize data types
df_optimized = pd.read_excel('data.xlsx')

# Convert to more efficient types
df_optimized['ID'] = df_optimized['ID'].astype('int32')  # Instead of int64
df_optimized['Category'] = df_optimized['Category'].astype('category')  # Instead of object
df_optimized['Value'] = df_optimized['Value'].astype('float32')  # Instead of float64

print(f"Memory usage (optimized): {df_optimized.memory_usage(deep=True).sum() / 1024 / 1024:.2f} MB")
```

### Read Only Needed Columns

```python
import pandas as pd

# Read all columns (slow)
df_all = pd.read_excel('large_file.xlsx')

# Read only specific columns (faster)
df_subset = pd.read_excel(
    'large_file.xlsx',
    usecols=['ID', 'Name', 'Value']  # Only these columns
)

print(f"All columns: {df_all.memory_usage(deep=True).sum() / 1024 / 1024:.2f} MB")
print(f"Subset: {df_subset.memory_usage(deep=True).sum() / 1024 / 1024:.2f} MB")
```

### Use CSV Instead of Excel

```python
import pandas as pd
import time

# Excel (slow)
start = time.time()
df_excel = pd.read_excel('large_file.xlsx')
excel_time = time.time() - start

# Convert to CSV once
df_excel.to_csv('large_file.csv', index=False)

# CSV (fast)
start = time.time()
df_csv = pd.read_csv('large_file.csv')
csv_time = time.time() - start

print(f"Excel: {excel_time:.2f} seconds")
print(f"CSV: {csv_time:.2f} seconds")
print(f"Speedup: {excel_time / csv_time:.1f}x faster")
```

## Part 5: Parallel Processing

### Process Multiple Files Concurrently

```python
from concurrent.futures import ProcessPoolExecutor
import pandas as pd
from pathlib import Path

def process_file(file_path):
    """Process single file"""
    df = pd.read_excel(file_path)
    result = df['Value'].sum()
    return file_path.name, result

def process_multiple_files(directory):
    """Process multiple files in parallel"""
    files = list(Path(directory).glob('*.xlsx'))
    
    with ProcessPoolExecutor(max_workers=4) as executor:
        results = executor.map(process_file, files)
    
    for filename, result in results:
        print(f"{filename}: {result}")

# Usage
process_multiple_files('data_folder/')
```

## Part 6: Alternative Formats

### Use Parquet (Fastest)

```python
import pandas as pd

# Read Excel
df = pd.read_excel('large_file.xlsx')

# Save as Parquet (compressed, columnar format)
df.to_parquet('large_file.parquet', compression='snappy')

# Read Parquet (much faster)
df_parquet = pd.read_parquet('large_file.parquet')

# File size comparison
from pathlib import Path
excel_size = Path('large_file.xlsx').stat().st_size / 1024 / 1024
parquet_size = Path('large_file.parquet').stat().st_size / 1024 / 1024

print(f"Excel: {excel_size:.2f} MB")
print(f"Parquet: {parquet_size:.2f} MB")
print(f"Compression: {excel_size / parquet_size:.1f}x smaller")
```

### Use HDF5

```python
import pandas as pd

# Save to HDF5
df = pd.read_excel('large_file.xlsx')
df.to_hdf('large_file.h5', key='data', mode='w', complevel=9)

# Read from HDF5 (fast)
df_h5 = pd.read_hdf('large_file.h5', key='data')

# Can also read chunks from HDF5
for df_chunk in pd.read_hdf('large_file.h5', key='data', chunksize=10000):
    # Process chunk
    print(f"Chunk size: {len(df_chunk)}")
```

## Part 7: Progress Tracking

### Progress Bar for Large Operations

```python
import pandas as pd
from tqdm import tqdm

def process_with_progress(file_path, chunk_size=10000):
    """Process file with progress bar"""
    
    # Get total rows
    df_sample = pd.read_excel(file_path, nrows=1)
    # Estimate total rows (you may need to calculate this differently)
    
    results = []
    skip_rows = 0
    
    with tqdm(desc="Processing", unit="rows") as pbar:
        while True:
            if skip_rows > 0:
                df_chunk = pd.read_excel(
                    file_path,
                    skiprows=range(1, skip_rows + 1),
                    nrows=chunk_size
                )
            else:
                df_chunk = pd.read_excel(file_path, nrows=chunk_size)
            
            if df_chunk.empty:
                break
            
            # Process
            result = df_chunk['Value'].sum()
            results.append(result)
            
            pbar.update(len(df_chunk))
            skip_rows += chunk_size
            
            if len(df_chunk) < chunk_size:
                break
    
    return sum(results)
```

## Part 8: Best Practices for Production

### Robust File Processing Function

```python
import pandas as pd
from pathlib import Path
import logging

logging.basicConfig(level=logging.INFO)
logger = logging.getLogger(__name__)

def process_large_file(
    input_file,
    output_file,
    chunk_size=10000,
    max_file_size_mb=200
):
    """
    Production-ready large file processor
    """
    try:
        # Check file exists
        file_path = Path(input_file)
        if not file_path.exists():
            raise FileNotFoundError(f"File not found: {input_file}")
        
        # Check file size
        size_mb = file_path.stat().st_size / 1024 / 1024
        logger.info(f"File size: {size_mb:.2f} MB")
        
        if size_mb > max_file_size_mb:
            logger.warning(f"File exceeds {max_file_size_mb}MB, using chunking")
            use_chunking = True
        else:
            use_chunking = False
        
        # Process
        if use_chunking:
            # Chunked processing
            logger.info("Using chunked processing")
            results = []
            skip_rows = 0
            chunk_num = 0
            
            while True:
                if skip_rows > 0:
                    df_chunk = pd.read_excel(
                        input_file,
                        skiprows=range(1, skip_rows + 1),
                        nrows=chunk_size
                    )
                else:
                    df_chunk = pd.read_excel(input_file, nrows=chunk_size)
                
                if df_chunk.empty:
                    break
                
                chunk_num += 1
                logger.info(f"Processing chunk {chunk_num}: {len(df_chunk)} rows")
                
                # Your processing logic here
                df_processed = df_chunk  # Replace with actual processing
                results.append(df_processed)
                
                skip_rows += chunk_size
                
                if len(df_chunk) < chunk_size:
                    break
            
            # Combine results
            df_final = pd.concat(results, ignore_index=True)
        else:
            # Normal processing
            logger.info("Using normal processing")
            df = pd.read_excel(input_file)
            df_final = df  # Replace with actual processing
        
        # Save result
        logger.info(f"Saving to {output_file}")
        df_final.to_excel(output_file, index=False)
        
        logger.info("Processing complete")
        return True
        
    except Exception as e:
        logger.error(f"Error processing file: {e}")
        return False

# Usage
success = process_large_file(
    'large_input.xlsx',
    'large_output.xlsx',
    chunk_size=10000
)
```

## Part 9: Memory Profiling

### Profile Memory Usage

```python
from memory_profiler import profile
import pandas as pd

@profile
def load_and_process(filename):
    """Function with memory profiling"""
    df = pd.read_excel(filename)
    
    # Processing
    df['New_Column'] = df['Value'] * 2
    df_grouped = df.groupby('Category').sum()
    
    return df_grouped

# Run with: python -m memory_profiler script.py
result = load_and_process('data.xlsx')
```

## Part 10: Strategies Summary

### Decision Tree for Large Files

```python
def choose_strategy(file_size_mb, num_columns, memory_available_gb):
    """
    Recommend strategy based on file characteristics
    """
    if file_size_mb < 10:
        return "Normal pandas read_excel"
    
    elif file_size_mb < 50:
        if memory_available_gb > 8:
            return "Normal pandas with optimized dtypes"
        else:
            return "Read only needed columns"
    
    elif file_size_mb < 200:
        if memory_available_gb > 16:
            return "Pandas with chunk processing"
        else:
            return "openpyxl streaming (read-only mode)"
    
    else:
        return "Convert to CSV/Parquet, then use dask or chunking"

# Example
strategy = choose_strategy(file_size_mb=150, num_columns=50, memory_available_gb=8)
print(f"Recommended strategy: {strategy}")
```

## Best Practices Summary

1. **Measure First** - Profile before optimizing
2. **Use Chunking** - For files > 50MB
3. **Stream When Possible** - openpyxl read-only/write-only modes
4. **Optimize Data Types** - Use int32, category, float32
5. **Read Only Needed Columns** - Reduce memory
6. **Consider Alternatives** - CSV, Parquet, HDF5
7. **Monitor Memory** - Use memory profilers
8. **Progress Tracking** - For long operations
9. **Error Handling** - Robust production code
10. **Test with Real Data** - Not just samples

## Performance Comparison

| Operation | Small (5MB) | Medium (50MB) | Large (200MB) |
|-----------|-------------|---------------|---------------|
| Normal pandas | 2s | 20s | 120s |
| Chunked pandas | 3s | 25s | 90s |
| openpyxl streaming | 5s | 40s | 150s |
| CSV + pandas | 1s | 8s | 30s |
| Parquet | 0.5s | 3s | 12s |

## Summary

You've learned how to:
- ✅ Measure file size and memory usage
- ✅ Process files in chunks
- ✅ Use streaming with openpyxl
- ✅ Optimize data types and memory
- ✅ Use parallel processing
- ✅ Work with alternative formats (CSV, Parquet, HDF5)
- ✅ Track progress for long operations
- ✅ Build production-ready file processors
- ✅ Profile and optimize performance

## Next Steps

In Session 10, you'll learn automation and batch processing - how to create workflows that process multiple files automatically.

