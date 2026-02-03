# Session 2: Reading Excel Files - Comprehensive Guide

## Introduction

Reading Excel files effectively is the foundation of Excel automation. This session covers all the techniques you need to read Excel files with various structures, handle different data types, and extract exactly the data you need.

## Reading Single Sheets

### Basic Reading

The simplest way to read an Excel file:

```python
import pandas as pd

# Read the first sheet
df = pd.read_excel('sales_data.xlsx')
print(df.head())
```

### Specifying Sheets

You can specify which sheet to read:

```python
# By sheet name
df = pd.read_excel('sales_data.xlsx', sheet_name='January')

# By sheet index (0-based)
df = pd.read_excel('sales_data.xlsx', sheet_name=0)

# Read multiple specific sheets
sheets_dict = pd.read_excel('sales_data.xlsx', sheet_name=['January', 'February'])

# Read all sheets
all_sheets = pd.read_excel('sales_data.xlsx', sheet_name=None)
```

## Reading Specific Ranges

### Skip Rows and Headers

```python
# Skip first 3 rows
df = pd.read_excel('file.xlsx', skiprows=3)

# Skip specific rows (0-indexed)
df = pd.read_excel('file.xlsx', skiprows=[0, 2, 5])

# Specify header row
df = pd.read_excel('file.xlsx', header=2)

# No header
df = pd.read_excel('file.xlsx', header=None)
```

### Select Specific Columns

```python
# Read specific columns by name
df = pd.read_excel('file.xlsx', usecols=['Name', 'Age', 'Salary'])

# Read specific columns by index
df = pd.read_excel('file.xlsx', usecols=[0, 2, 3])

# Read columns A, C, and D
df = pd.read_excel('file.xlsx', usecols='A,C:D')

# Using a function
df = pd.read_excel('file.xlsx', usecols=lambda x: x.upper() in ['NAME', 'AGE'])
```

### Limit Number of Rows

```python
# Read only first 100 rows
df = pd.read_excel('file.xlsx', nrows=100)

# Combine with skiprows
df = pd.read_excel('file.xlsx', skiprows=10, nrows=100)
```

## Handling Data Types

### Automatic Type Inference

Pandas automatically infers data types, but you can control this:

```python
# Specify data types
df = pd.read_excel('file.xlsx', dtype={
    'ID': str,
    'Age': int,
    'Salary': float,
    'Active': bool
})

# Convert all to string
df = pd.read_excel('file.xlsx', dtype=str)
```

### Date Handling

```python
# Parse dates automatically
df = pd.read_excel('file.xlsx', parse_dates=['Date_Column'])

# Parse multiple date columns
df = pd.read_excel('file.xlsx', parse_dates=['Start_Date', 'End_Date'])

# Custom date format
df = pd.read_excel('file.xlsx', parse_dates=['Date'], 
                   date_parser=lambda x: pd.to_datetime(x, format='%d/%m/%Y'))
```

### Missing Values

```python
# Specify what represents missing values
df = pd.read_excel('file.xlsx', na_values=['N/A', 'NA', ''])

# Keep default NA values and add custom ones
df = pd.read_excel('file.xlsx', na_values=['Missing'], keep_default_na=True)
```

## Working with Headers

### No Header Row

```python
# File has no headers
df = pd.read_excel('file.xlsx', header=None)

# Assign custom column names
df = pd.read_excel('file.xlsx', header=None, 
                   names=['Col1', 'Col2', 'Col3'])
```

### Multi-Level Headers

```python
# Read multi-level headers
df = pd.read_excel('file.xlsx', header=[0, 1])

# Access multi-level columns
print(df.columns)
```

## Reading with Openpyxl

### Basic Cell Reading

```python
from openpyxl import load_workbook

wb = load_workbook('file.xlsx')
ws = wb['Sheet1']

# Read single cell
value = ws['A1'].value

# Read cell by row and column
value = ws.cell(row=1, column=1).value

# Read range
for row in ws['A1:C10']:
    for cell in row:
        print(cell.value)
```

### Iterating Efficiently

```python
# Iterate by rows
for row in ws.iter_rows(min_row=2, max_row=10, min_col=1, max_col=3, values_only=True):
    print(row)

# Iterate by columns
for col in ws.iter_cols(min_row=1, max_row=10, min_col=1, max_col=3, values_only=True):
    print(col)

# Get all values as list of lists
data = [[cell.value for cell in row] for row in ws.iter_rows()]
```

### Reading with Formulas

```python
# Read formula results (default)
value = ws['A1'].value

# Read actual formula
formula = ws['A1'].value  # Returns formula if cell contains one

# Load with formulas preserved
wb = load_workbook('file.xlsx', data_only=False)

# Load with formula results only
wb = load_workbook('file.xlsx', data_only=True)
```

## Reading Multiple Sheets

### Process All Sheets

```python
# Method 1: Using pandas
all_sheets = pd.read_excel('file.xlsx', sheet_name=None)

for sheet_name, df in all_sheets.items():
    print(f"Processing {sheet_name}")
    print(df.head())

# Method 2: Using openpyxl
wb = load_workbook('file.xlsx')
for sheet_name in wb.sheetnames:
    ws = wb[sheet_name]
    print(f"Sheet: {sheet_name}")
    print(f"Dimensions: {ws.dimensions}")
```

### Combine Multiple Sheets

```python
# Read and concatenate all sheets
all_sheets = pd.read_excel('file.xlsx', sheet_name=None)
combined_df = pd.concat(all_sheets.values(), ignore_index=True)

# Add sheet name as a column
dfs = []
for sheet_name, df in all_sheets.items():
    df['Sheet'] = sheet_name
    dfs.append(df)
combined_df = pd.concat(dfs, ignore_index=True)
```

## Advanced Reading Techniques

### Reading Large Files

```python
# Read in chunks (useful for very large files)
chunk_size = 1000
chunks = []
for i in range(0, 10000, chunk_size):
    df_chunk = pd.read_excel('large_file.xlsx', 
                             skiprows=range(1, i), 
                             nrows=chunk_size)
    chunks.append(df_chunk)

df = pd.concat(chunks, ignore_index=True)

# Use read_only mode with openpyxl
wb = load_workbook('large_file.xlsx', read_only=True)
ws = wb.active
for row in ws.iter_rows(values_only=True):
    process_row(row)  # Process one row at a time
wb.close()
```

### Reading from URLs

```python
# Read from URL
url = 'https://example.com/data.xlsx'
df = pd.read_excel(url)

# Read from file-like object
from io import BytesIO
import requests

response = requests.get(url)
df = pd.read_excel(BytesIO(response.content))
```

### Reading with Encoding Issues

```python
# Specify engine
df = pd.read_excel('file.xlsx', engine='openpyxl')

# For older .xls files
df = pd.read_excel('file.xls', engine='xlrd')
```

## Error Handling

### Common Issues and Solutions

```python
import pandas as pd
from pathlib import Path

def safe_read_excel(file_path, **kwargs):
    """Safely read Excel file with comprehensive error handling"""
    try:
        # Check if file exists
        if not Path(file_path).exists():
            raise FileNotFoundError(f"File not found: {file_path}")
        
        # Check file extension
        if not file_path.endswith(('.xlsx', '.xls', '.xlsm')):
            raise ValueError("Invalid file format. Must be .xlsx, .xls, or .xlsm")
        
        # Try reading
        df = pd.read_excel(file_path, **kwargs)
        
        # Check if DataFrame is empty
        if df.empty:
            print(f"Warning: {file_path} is empty")
            return None
        
        return df
        
    except FileNotFoundError as e:
        print(f"Error: {e}")
        return None
    
    except ValueError as e:
        print(f"Value Error: {e}")
        return None
    
    except Exception as e:
        print(f"Unexpected error: {e}")
        return None

# Usage
df = safe_read_excel('data.xlsx', sheet_name='Sheet1')
if df is not None:
    print(df.head())
```

## Performance Comparison

### Pandas vs Openpyxl

```python
import time

# Test with pandas
start = time.time()
df_pandas = pd.read_excel('large_file.xlsx')
pandas_time = time.time() - start

# Test with openpyxl
start = time.time()
wb = load_workbook('large_file.xlsx', read_only=True)
ws = wb.active
data = [[cell.value for cell in row] for row in ws.iter_rows()]
df_openpyxl = pd.DataFrame(data[1:], columns=data[0])
openpyxl_time = time.time() - start

print(f"Pandas: {pandas_time:.2f}s")
print(f"Openpyxl: {openpyxl_time:.2f}s")
```

## Best Practices

1. **Specify engine explicitly** for better control
2. **Use read_only mode** for large files you're only reading
3. **Limit data reading** with nrows and usecols when possible
4. **Handle errors gracefully** with try-except blocks
5. **Close workbooks** when done (especially in read_only mode)
6. **Use appropriate data types** to save memory
7. **Check for empty DataFrames** after reading
8. **Validate data structure** before processing

## Summary

You now know how to:
- Read single and multiple sheets
- Read specific ranges and columns
- Handle different data types
- Work with headers and indices
- Use both pandas and openpyxl effectively
- Handle errors properly
- Optimize reading performance

## Practice Exercises

See the `exercises/` directory for hands-on practice with these concepts.

## Next Session

In Session 3, you'll learn comprehensive techniques for writing Excel files, including formatting, multiple sheets, and performance optimization.

