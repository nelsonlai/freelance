# Session 1: Setup and Basics - Python Excel Libraries

## Introduction

Welcome to Python Excel Operations! In this session, you'll learn about the powerful Python libraries that enable you to automate Excel tasks, process large datasets, and create professional reports programmatically.

### Why Use Python for Excel?

1. **Automation** - Process hundreds of files in seconds
2. **Consistency** - Eliminate human errors in repetitive tasks
3. **Scalability** - Handle datasets too large for Excel (>1 million rows)
4. **Integration** - Connect Excel with databases, APIs, and other systems
5. **Version Control** - Track changes to your Excel processing logic
6. **Reproducibility** - Share and reproduce analyses easily

## Understanding Excel File Formats

### .xlsx (Excel 2007+)
- **Standard format** for modern Excel
- **XML-based** structure
- Supports up to 1,048,576 rows and 16,384 columns
- Can contain formulas, charts, formatting, macros (if .xlsm)
- **Use with**: pandas, openpyxl, xlsxwriter

### .xls (Excel 97-2003)
- **Legacy format**
- **Binary structure**
- Limited to 65,536 rows and 256 columns
- Still used in some organizations
- **Use with**: xlrd, xlwt

### .xlsm (Excel with Macros)
- Same as .xlsx but **contains VBA macros**
- Requires special handling for security
- **Use with**: openpyxl (with read_only or write_only mode)

### .xlsb (Binary Workbook)
- **Binary format** for faster loading
- **Smaller file size** than .xlsx
- Less common but useful for large files
- **Use with**: pyxlsb

### .csv (Comma-Separated Values)
- **Plain text** format
- No formatting, formulas, or multiple sheets
- **Universal compatibility**
- **Use with**: pandas (very fast)

## Python Excel Libraries Overview

### 1. pandas
**Best for**: Data analysis, simple Excel I/O, data transformation

```python
import pandas as pd

# Read Excel file
df = pd.read_excel('file.xlsx')

# Write Excel file
df.to_excel('output.xlsx', index=False)
```

**Pros**:
- Simple and intuitive API
- Powerful data manipulation
- Fast for large datasets
- Integrated with NumPy and matplotlib

**Cons**:
- Limited formatting capabilities
- Cannot preserve existing Excel formatting
- Basic chart support

### 2. openpyxl
**Best for**: Reading/writing Excel with formatting, formulas, and charts

```python
from openpyxl import load_workbook, Workbook

# Read Excel file
wb = load_workbook('file.xlsx')
ws = wb.active

# Access cell
cell_value = ws['A1'].value

# Write Excel file
wb = Workbook()
ws = wb.active
ws['A1'] = 'Hello'
wb.save('output.xlsx')
```

**Pros**:
- Full Excel feature support (formatting, formulas, charts)
- Can modify existing files
- Preserve formatting
- Read and write formulas

**Cons**:
- Slower than pandas for large datasets
- More verbose syntax
- Memory-intensive

### 3. xlsxwriter
**Best for**: Creating new Excel files with formatting and charts

```python
import xlsxwriter

# Create workbook
workbook = xlsxwriter.Workbook('output.xlsx')
worksheet = workbook.add_worksheet()

# Write data with formatting
bold = workbook.add_format({'bold': True})
worksheet.write('A1', 'Hello', bold)

workbook.close()
```

**Pros**:
- Excellent formatting options
- Great chart capabilities
- Good performance
- Comprehensive documentation

**Cons**:
- **Cannot read or modify** existing files
- Write-only library

### 4. xlrd / xlwt
**Best for**: Legacy .xls file support

```python
import xlrd
import xlwt

# Read .xls file
workbook = xlrd.open_workbook('file.xls')
sheet = workbook.sheet_by_index(0)
value = sheet.cell(0, 0).value

# Write .xls file
workbook = xlwt.Workbook()
worksheet = workbook.add_sheet('Sheet1')
worksheet.write(0, 0, 'Hello')
workbook.save('output.xls')
```

**Pros**:
- Only option for .xls files
- Stable and reliable

**Cons**:
- Legacy format only
- Limited active development
- xlrd dropped .xlsx support in recent versions

## Setting Up Your Environment

### Step 1: Create a Virtual Environment

```bash
# Create virtual environment
python3 -m venv excel_env

# Activate it
# On macOS/Linux:
source excel_env/bin/activate

# On Windows:
excel_env\Scripts\activate
```

### Step 2: Install Required Packages

```bash
# Core packages
pip install pandas openpyxl xlsxwriter

# Additional packages
pip install numpy matplotlib

# For legacy support (optional)
pip install xlrd xlwt

# For binary Excel files (optional)
pip install pyxlsb
```

### Step 3: Verify Installation

```python
import pandas as pd
import openpyxl
import xlsxwriter
import numpy as np

print(f"pandas version: {pd.__version__}")
print(f"openpyxl version: {openpyxl.__version__}")
print(f"xlsxwriter version: {xlsxwriter.__version__}")
print("✓ All libraries installed successfully!")
```

## Reading Excel Files with Pandas

### Basic Reading

```python
import pandas as pd

# Read Excel file
df = pd.read_excel('sales_data.xlsx')

# Display first few rows
print(df.head())

# Get basic information
print(df.info())

# Get statistical summary
print(df.describe())
```

### Understanding DataFrames

A DataFrame is a 2-dimensional labeled data structure:

```python
# Create a simple DataFrame
data = {
    'Name': ['Alice', 'Bob', 'Charlie'],
    'Age': [25, 30, 35],
    'Salary': [50000, 60000, 70000]
}
df = pd.DataFrame(data)

print(df)
```

Output:
```
      Name  Age  Salary
0    Alice   25   50000
1      Bob   30   60000
2  Charlie   35   70000
```

### DataFrame Components

1. **Index** - Row labels (0, 1, 2, ...)
2. **Columns** - Column labels ('Name', 'Age', 'Salary')
3. **Values** - The actual data
4. **dtypes** - Data types of each column

### Common DataFrame Operations

```python
# Select a column
ages = df['Age']
print(ages)

# Select multiple columns
subset = df[['Name', 'Salary']]
print(subset)

# Filter rows
high_earners = df[df['Salary'] > 55000]
print(high_earners)

# Add a new column
df['Bonus'] = df['Salary'] * 0.1
print(df)

# Sort data
df_sorted = df.sort_values('Age', ascending=False)
print(df_sorted)

# Group and aggregate
avg_salary = df.groupby('Age')['Salary'].mean()
print(avg_salary)
```

## Reading Excel Files with Openpyxl

### Basic Reading

```python
from openpyxl import load_workbook

# Load workbook
wb = load_workbook('sales_data.xlsx')

# Get sheet names
print(wb.sheetnames)

# Access a sheet
ws = wb['Sheet1']  # By name
# or
ws = wb.active  # Active sheet

# Read cell values
a1_value = ws['A1'].value
b2_value = ws.cell(row=2, column=2).value

print(f"A1: {a1_value}")
print(f"B2: {b2_value}")
```

### Iterating Through Cells

```python
# Iterate through rows
for row in ws.iter_rows(min_row=1, max_row=10, min_col=1, max_col=3):
    for cell in row:
        print(cell.value, end='\t')
    print()

# Iterate through columns
for col in ws.iter_cols(min_row=1, max_row=10, min_col=1, max_col=3):
    for cell in col:
        print(cell.value)
```

### Getting Cell Information

```python
cell = ws['A1']

print(f"Value: {cell.value}")
print(f"Data type: {cell.data_type}")
print(f"Coordinate: {cell.coordinate}")
print(f"Row: {cell.row}")
print(f"Column: {cell.column}")
print(f"Column letter: {cell.column_letter}")
```

## Comparing Pandas and Openpyxl

### When to Use Pandas

- ✅ Reading large datasets quickly
- ✅ Data analysis and transformation
- ✅ Statistical operations
- ✅ Cleaning and preprocessing data
- ✅ Converting between formats (CSV, JSON, SQL)
- ❌ Preserving Excel formatting
- ❌ Working with formulas
- ❌ Creating charts

### When to Use Openpyxl

- ✅ Preserving Excel formatting
- ✅ Working with formulas
- ✅ Creating and modifying charts
- ✅ Cell-level operations
- ✅ Styling and conditional formatting
- ❌ Fast data analysis
- ❌ Statistical operations
- ❌ Large dataset processing

### Combined Approach

Often, the best approach is to **combine both libraries**:

```python
import pandas as pd
from openpyxl import load_workbook
from openpyxl.styles import Font, PatternFill

# Step 1: Use pandas for data processing
df = pd.read_excel('sales_data.xlsx')
df['Total'] = df['Quantity'] * df['Price']
df_summary = df.groupby('Region')['Total'].sum()

# Step 2: Write with pandas
df_summary.to_excel('summary.xlsx')

# Step 3: Use openpyxl for formatting
wb = load_workbook('summary.xlsx')
ws = wb.active

# Apply formatting
for cell in ws['A']:
    cell.font = Font(bold=True)
    cell.fill = PatternFill(start_color='FFFF00', fill_type='solid')

wb.save('summary_formatted.xlsx')
```

## Practical Example: Sales Data Analysis

Let's put it all together with a complete example:

```python
import pandas as pd
from openpyxl import load_workbook
from openpyxl.styles import Font, Alignment

# 1. Read and analyze data with pandas
df = pd.read_excel('sales_data.xlsx', sheet_name='Daily_Sales')

# 2. Calculate summary statistics
summary = df.groupby('Region').agg({
    'Units_Sold': 'sum',
    'Total_Sales': 'sum'
}).reset_index()

summary['Avg_Price'] = summary['Total_Sales'] / summary['Units_Sold']
summary = summary.round(2)

# 3. Write to Excel
output_file = 'sales_summary.xlsx'
summary.to_excel(output_file, index=False, sheet_name='Summary')

# 4. Format with openpyxl
wb = load_workbook(output_file)
ws = wb['Summary']

# Format header row
for cell in ws[1]:
    cell.font = Font(bold=True, size=12)
    cell.alignment = Alignment(horizontal='center')

# Adjust column widths
for column in ws.columns:
    max_length = 0
    column_letter = column[0].column_letter
    for cell in column:
        if cell.value:
            max_length = max(max_length, len(str(cell.value)))
    ws.column_dimensions[column_letter].width = max_length + 2

wb.save(output_file)
print(f"✓ Summary report created: {output_file}")
```

## Best Practices

### 1. Always Use Context Managers or Close Files

```python
# Good - with context manager
with pd.ExcelWriter('output.xlsx') as writer:
    df.to_excel(writer, sheet_name='Data')

# Also good - explicit close
writer = pd.ExcelWriter('output.xlsx')
df.to_excel(writer, sheet_name='Data')
writer.close()
```

### 2. Handle Errors Gracefully

```python
try:
    df = pd.read_excel('file.xlsx')
except FileNotFoundError:
    print("Error: File not found")
except Exception as e:
    print(f"Error reading file: {e}")
```

### 3. Specify Engine When Needed

```python
# For .xlsx files
df = pd.read_excel('file.xlsx', engine='openpyxl')

# For .xls files
df = pd.read_excel('file.xls', engine='xlrd')
```

### 4. Use Appropriate Data Types

```python
# Specify dtypes for better performance and accuracy
df = pd.read_excel('file.xlsx', dtype={
    'ID': str,
    'Amount': float,
    'Date': 'datetime64'
})
```

### 5. Check File Existence Before Reading

```python
from pathlib import Path

file_path = Path('sales_data.xlsx')
if file_path.exists():
    df = pd.read_excel(file_path)
else:
    print(f"Error: {file_path} does not exist")
```

## Common Issues and Solutions

### Issue 1: Module Not Found
```python
# Error: No module named 'openpyxl'
# Solution: Install the package
# pip install openpyxl
```

### Issue 2: Excel File Locked
```python
# Error: Permission denied
# Solution: Close the Excel file in Excel application
# Or use a different filename
```

### Issue 3: Reading Wrong Sheet
```python
# Problem: Reading wrong sheet
# Solution: Specify sheet name or index
df = pd.read_excel('file.xlsx', sheet_name='Sheet2')
# or
df = pd.read_excel('file.xlsx', sheet_name=1)  # 0-indexed
```

### Issue 4: Memory Error with Large Files
```python
# Problem: Memory error with large files
# Solution: Read in chunks or use openpyxl's read_only mode
df = pd.read_excel('large_file.xlsx', nrows=10000)  # Read first 10000 rows
```

## Summary

In this session, you learned:

✅ Different Excel file formats and their characteristics  
✅ When to use pandas, openpyxl, and xlsxwriter  
✅ How to set up your Python environment  
✅ Basic Excel file reading with pandas  
✅ Understanding DataFrames  
✅ Basic Excel file reading with openpyxl  
✅ Best practices for Excel operations  

## Next Steps

In the next session, you'll learn:
- Advanced reading techniques
- Reading specific ranges and cells
- Handling multiple sheets
- Working with different data types
- Error handling for Excel operations

## Practice Exercises

1. Install all required libraries and verify the installation
2. Read the sample sales data file and display basic statistics
3. Create a simple DataFrame and write it to Excel
4. Read an Excel file with openpyxl and print all cell values
5. Compare the performance of pandas vs openpyxl for reading large files

---

**Continue to `01_setup_and_basics.py` for executable examples!**

