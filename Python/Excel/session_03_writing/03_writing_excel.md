# Session 3: Writing Excel Files - Comprehensive Guide

## Introduction

Writing Excel files is as important as reading them. In this session, you'll learn how to create Excel files from scratch, write DataFrames to Excel, format outputs, and handle multiple sheets. You'll also learn performance optimization techniques for writing large files.

## Why Write Excel Files with Python?

1. **Automated Reports** - Generate reports automatically without manual work
2. **Data Export** - Share Python analysis results in Excel format
3. **Template Generation** - Create standardized reports with consistent formatting
4. **Batch Processing** - Generate hundreds of reports in minutes
5. **Integration** - Connect Python applications with Excel-based workflows

## Basic Writing with Pandas

### Simple DataFrame to Excel

The easiest way to write an Excel file:

```python
import pandas as pd

# Create DataFrame
df = pd.DataFrame({
    'Name': ['Alice', 'Bob', 'Charlie'],
    'Age': [25, 30, 35],
    'Salary': [60000, 75000, 70000]
})

# Write to Excel
df.to_excel('output.xlsx', index=False)
```

### Controlling Output Format

```python
# With index
df.to_excel('with_index.xlsx', index=True)

# Custom index name
df.to_excel('custom_index.xlsx', index=True, index_label='ID')

# Without headers
df.to_excel('no_headers.xlsx', header=False, index=False)

# Custom sheet name
df.to_excel('custom_sheet.xlsx', sheet_name='Employee_Data', index=False)
```

### Writing Specific Columns

```python
# Write only selected columns
df[['Name', 'Salary']].to_excel('selected_columns.xlsx', index=False)

# Reorder columns while writing
df[['Salary', 'Name', 'Age']].to_excel('reordered.xlsx', index=False)
```

## Writing Multiple Sheets

### Using ExcelWriter Context Manager

The recommended way to write multiple sheets:

```python
import pandas as pd

# Create multiple DataFrames
df_employees = pd.DataFrame({
    'Name': ['Alice', 'Bob', 'Charlie'],
    'Department': ['Sales', 'IT', 'HR']
})

df_sales = pd.DataFrame({
    'Product': ['A', 'B', 'C'],
    'Revenue': [10000, 15000, 12000]
})

# Write to multiple sheets
with pd.ExcelWriter('multi_sheet.xlsx', engine='openpyxl') as writer:
    df_employees.to_excel(writer, sheet_name='Employees', index=False)
    df_sales.to_excel(writer, sheet_name='Sales', index=False)
```

### Why Use Context Manager?

```python
# Without context manager (must close manually)
writer = pd.ExcelWriter('output.xlsx')
df.to_excel(writer, sheet_name='Data')
writer.close()  # Don't forget this!

# With context manager (auto-closes)
with pd.ExcelWriter('output.xlsx') as writer:
    df.to_excel(writer, sheet_name='Data')
# Automatically closed here
```

## Appending to Existing Files

### Adding New Sheets to Existing Workbook

```python
import pandas as pd

# Create initial file
df1 = pd.DataFrame({'A': [1, 2, 3]})
df1.to_excel('existing.xlsx', sheet_name='Sheet1', index=False)

# Append new sheet (mode='a' for append)
df2 = pd.DataFrame({'B': [4, 5, 6]})
with pd.ExcelWriter('existing.xlsx', mode='a', engine='openpyxl') as writer:
    df2.to_excel(writer, sheet_name='Sheet2', index=False)
```

### Important: Cannot Overwrite Specific Sheets

```python
# This will REPLACE the entire file, not just one sheet
df.to_excel('file.xlsx', sheet_name='Sheet1')

# To update one sheet, you must:
# 1. Read all sheets
# 2. Modify the one you want
# 3. Write all sheets back
```

## Writing with Openpyxl

### Basic Cell Writing

```python
from openpyxl import Workbook

# Create workbook
wb = Workbook()
ws = wb.active
ws.title = "My Sheet"

# Write to cells
ws['A1'] = 'Name'
ws['B1'] = 'Age'
ws['A2'] = 'Alice'
ws['B2'] = 25

# Or use cell() method
ws.cell(row=3, column=1, value='Bob')
ws.cell(row=3, column=2, value=30)

# Save workbook
wb.save('openpyxl_output.xlsx')
```

### Writing Rows

```python
from openpyxl import Workbook

wb = Workbook()
ws = wb.active

# Write header row
headers = ['Product', 'Price', 'Quantity']
ws.append(headers)

# Write data rows
data = [
    ['Laptop', 999.99, 50],
    ['Mouse', 29.99, 200],
    ['Keyboard', 79.99, 150]
]

for row in data:
    ws.append(row)

wb.save('products.xlsx')
```

### Writing from DataFrame

```python
from openpyxl import Workbook
from openpyxl.utils.dataframe import dataframe_to_rows
import pandas as pd

df = pd.DataFrame({
    'Name': ['Alice', 'Bob'],
    'Score': [95, 87]
})

wb = Workbook()
ws = wb.active

# Write DataFrame to worksheet
for r in dataframe_to_rows(df, index=False, header=True):
    ws.append(r)

wb.save('from_dataframe.xlsx')
```

## Adding Formatting with Openpyxl

### Basic Cell Formatting

```python
from openpyxl import Workbook
from openpyxl.styles import Font, PatternFill, Alignment, Border, Side

wb = Workbook()
ws = wb.active

# Write and format header
ws['A1'] = 'Product Name'
ws['A1'].font = Font(bold=True, size=14, color='FFFFFF')
ws['A1'].fill = PatternFill(start_color='4472C4', end_color='4472C4', fill_type='solid')
ws['A1'].alignment = Alignment(horizontal='center', vertical='center')

# Add border
thin_border = Border(
    left=Side(style='thin'),
    right=Side(style='thin'),
    top=Side(style='thin'),
    bottom=Side(style='thin')
)
ws['A1'].border = thin_border

wb.save('formatted.xlsx')
```

### Number Formatting

```python
from openpyxl import Workbook

wb = Workbook()
ws = wb.active

# Write numbers with different formats
ws['A1'] = 'Currency'
ws['B1'] = 1234.56
ws['B1'].number_format = '$#,##0.00'

ws['A2'] = 'Percentage'
ws['B2'] = 0.85
ws['B2'].number_format = '0.00%'

ws['A3'] = 'Date'
ws['B3'] = '2024-01-15'
ws['B3'].number_format = 'MM/DD/YYYY'

ws['A4'] = 'Number'
ws['B4'] = 1234567.89
ws['B4'].number_format = '#,##0.00'

wb.save('number_formats.xlsx')
```

### Column Width and Row Height

```python
from openpyxl import Workbook

wb = Workbook()
ws = wb.active

# Set column width
ws.column_dimensions['A'].width = 20
ws.column_dimensions['B'].width = 15

# Set row height
ws.row_dimensions[1].height = 30

# Auto-fit column width (manual calculation)
for column in ws.columns:
    max_length = 0
    column_letter = column[0].column_letter
    for cell in column:
        if cell.value:
            max_length = max(max_length, len(str(cell.value)))
    ws.column_dimensions[column_letter].width = max_length + 2

wb.save('sized.xlsx')
```

## Writing with xlsxwriter

### Basic xlsxwriter Usage

```python
import xlsxwriter

# Create workbook and worksheet
workbook = xlsxwriter.Workbook('xlsxwriter_output.xlsx')
worksheet = workbook.add_worksheet('Sheet1')

# Write data
worksheet.write('A1', 'Hello')
worksheet.write(0, 1, 'World')  # row, col (0-indexed)

# Write numbers
worksheet.write('A2', 123.45)
worksheet.write('A3', '=SUM(A2:A2)')  # Formula

workbook.close()
```

### Formatting with xlsxwriter

```python
import xlsxwriter

workbook = xlsxwriter.Workbook('formatted_xlsxwriter.xlsx')
worksheet = workbook.add_worksheet()

# Create formats
header_format = workbook.add_format({
    'bold': True,
    'font_size': 12,
    'bg_color': '#4472C4',
    'font_color': 'white',
    'align': 'center',
    'valign': 'vcenter',
    'border': 1
})

currency_format = workbook.add_format({
    'num_format': '$#,##0.00',
    'align': 'right'
})

# Write formatted data
worksheet.write('A1', 'Product', header_format)
worksheet.write('B1', 'Price', header_format)

worksheet.write('A2', 'Laptop')
worksheet.write('B2', 999.99, currency_format)

# Set column widths
worksheet.set_column('A:A', 20)
worksheet.set_column('B:B', 12)

workbook.close()
```

### Writing Arrays Efficiently

```python
import xlsxwriter

workbook = xlsxwriter.Workbook('array_data.xlsx')
worksheet = workbook.add_worksheet()

# Write row array
row_data = ['Name', 'Age', 'City']
worksheet.write_row('A1', row_data)

# Write column array
col_data = [25, 30, 35, 28]
worksheet.write_column('B2', col_data)

# Write 2D array
data = [
    ['Alice', 25, 'NYC'],
    ['Bob', 30, 'LA'],
    ['Charlie', 35, 'Chicago']
]
worksheet.write_row('A2', data[0])
worksheet.write_row('A3', data[1])
worksheet.write_row('A4', data[2])

workbook.close()
```

## Combining Pandas and Openpyxl

### Best of Both Worlds

Use pandas for data manipulation and openpyxl for formatting:

```python
import pandas as pd
from openpyxl import load_workbook
from openpyxl.styles import Font, PatternFill, Alignment

# Step 1: Create data with pandas
df = pd.DataFrame({
    'Product': ['Laptop', 'Mouse', 'Keyboard'],
    'Price': [999.99, 29.99, 79.99],
    'Quantity': [50, 200, 150]
})

df['Total'] = df['Price'] * df['Quantity']

# Step 2: Write with pandas
output_file = 'combined_output.xlsx'
df.to_excel(output_file, index=False, sheet_name='Sales')

# Step 3: Format with openpyxl
wb = load_workbook(output_file)
ws = wb['Sales']

# Format header row
header_fill = PatternFill(start_color='366092', end_color='366092', fill_type='solid')
header_font = Font(bold=True, color='FFFFFF')

for cell in ws[1]:
    cell.fill = header_fill
    cell.font = header_font
    cell.alignment = Alignment(horizontal='center')

# Format currency columns
for row in range(2, ws.max_row + 1):
    ws.cell(row=row, column=2).number_format = '$#,##0.00'  # Price
    ws.cell(row=row, column=4).number_format = '$#,##0.00'  # Total

# Adjust column widths
for column in ws.columns:
    max_length = 0
    column_letter = column[0].column_letter
    for cell in column:
        if cell.value:
            max_length = max(max_length, len(str(cell.value)))
    ws.column_dimensions[column_letter].width = max_length + 3

wb.save(output_file)
```

## Writing Custom Start Position

### Writing DataFrame at Specific Location

```python
import pandas as pd
from openpyxl import Workbook
from openpyxl.utils.dataframe import dataframe_to_rows

df = pd.DataFrame({
    'Month': ['Jan', 'Feb', 'Mar'],
    'Sales': [10000, 12000, 11000]
})

wb = Workbook()
ws = wb.active

# Add title at top
ws['A1'] = 'Sales Report 2024'
ws['A2'] = 'Generated: 2024-01-15'

# Write DataFrame starting from row 4
start_row = 4
for r_idx, row in enumerate(dataframe_to_rows(df, index=False, header=True), start_row):
    for c_idx, value in enumerate(row, 1):
        ws.cell(row=r_idx, column=c_idx, value=value)

wb.save('custom_position.xlsx')
```

## Performance Considerations

### Writing Large Files

```python
import pandas as pd
import numpy as np
import time

# Create large dataset
large_df = pd.DataFrame({
    f'Col_{i}': np.random.randn(100000) for i in range(20)
})

# Benchmark pandas
start = time.time()
large_df.to_excel('large_pandas.xlsx', index=False, engine='openpyxl')
pandas_time = time.time() - start
print(f"Pandas: {pandas_time:.2f} seconds")

# For very large files, consider:
# 1. Writing to CSV instead (much faster)
large_df.to_csv('large_data.csv', index=False)

# 2. Using xlsxwriter (faster than openpyxl for writing)
start = time.time()
large_df.to_excel('large_xlsxwriter.xlsx', index=False, engine='xlsxwriter')
xlsxwriter_time = time.time() - start
print(f"xlsxwriter: {xlsxwriter_time:.2f} seconds")
```

### Memory-Efficient Writing

```python
import xlsxwriter

# For very large datasets, write row by row
workbook = xlsxwriter.Workbook('memory_efficient.xlsx', {'constant_memory': True})
worksheet = workbook.add_worksheet()

# Write header
header = ['Col1', 'Col2', 'Col3']
worksheet.write_row(0, 0, header)

# Write data row by row (doesn't keep everything in memory)
for row_num in range(1, 100001):
    data = [row_num, row_num * 2, row_num * 3]
    worksheet.write_row(row_num, 0, data)

workbook.close()
```

## Error Handling

### Safe Writing Function

```python
import pandas as pd
from pathlib import Path

def safe_write_excel(df, file_path, **kwargs):
    """
    Safely write DataFrame to Excel with error handling
    
    Args:
        df: DataFrame to write
        file_path: Output file path
        **kwargs: Additional arguments for to_excel()
    
    Returns:
        bool: True if successful, False otherwise
    """
    try:
        file_path = Path(file_path)
        
        # Check if DataFrame is empty
        if df.empty:
            print(f"Warning: DataFrame is empty")
            return False
        
        # Create directory if it doesn't exist
        file_path.parent.mkdir(parents=True, exist_ok=True)
        
        # Check if file is open (Windows)
        if file_path.exists():
            try:
                file_path.rename(file_path)
            except OSError:
                print(f"Error: File is open in another program: {file_path}")
                return False
        
        # Write file
        df.to_excel(file_path, **kwargs)
        print(f"✓ Successfully wrote {len(df)} rows to {file_path}")
        return True
        
    except PermissionError:
        print(f"Error: Permission denied: {file_path}")
        return False
    
    except Exception as e:
        print(f"Error: {type(e).__name__}: {e}")
        return False

# Usage
df = pd.DataFrame({'A': [1, 2, 3]})
safe_write_excel(df, 'output.xlsx', index=False)
```

## Best Practices

### 1. Always Use Context Managers

```python
# Good
with pd.ExcelWriter('output.xlsx') as writer:
    df.to_excel(writer, sheet_name='Data')

# Bad - might not close if error occurs
writer = pd.ExcelWriter('output.xlsx')
df.to_excel(writer, sheet_name='Data')
writer.close()
```

### 2. Specify Engine Explicitly

```python
# Good - explicit engine
with pd.ExcelWriter('output.xlsx', engine='openpyxl') as writer:
    df.to_excel(writer)

# Can cause issues if wrong engine installed
with pd.ExcelWriter('output.xlsx') as writer:
    df.to_excel(writer)
```

### 3. Set Index=False for Clean Output

```python
# Good - no index column
df.to_excel('output.xlsx', index=False)

# Bad - adds unnecessary index column
df.to_excel('output.xlsx')
```

### 4. Use Meaningful Sheet Names

```python
# Good
df.to_excel('report.xlsx', sheet_name='Monthly_Sales_2024')

# Bad
df.to_excel('report.xlsx')  # Default name is 'Sheet1'
```

### 5. Handle Large Files Appropriately

```python
# For files > 100MB, consider:
# 1. Writing to CSV instead
df.to_csv('large_data.csv', index=False)

# 2. Using chunked writing
# 3. Compressing the file
# 4. Using binary formats (parquet, feather)
```

## Common Issues and Solutions

### Issue 1: File Already Open

```python
# Error: PermissionError: [Errno 13] Permission denied
# Solution: Close the file in Excel before writing
```

### Issue 2: Invalid Sheet Names

```python
# Excel sheet names must be ≤ 31 characters and not contain: \ / ? * [ ]
# Bad
df.to_excel('file.xlsx', sheet_name='This is a very long sheet name that exceeds limit')

# Good
df.to_excel('file.xlsx', sheet_name='Summary_Report_2024')
```

### Issue 3: Memory Errors with Large Files

```python
# Solution: Use engine='xlsxwriter' with constant_memory option
# Or write to CSV instead
```

## Summary

You've learned:
- ✅ Basic writing with pandas
- ✅ Writing multiple sheets
- ✅ Appending to existing files
- ✅ Writing with openpyxl for more control
- ✅ Formatting Excel output
- ✅ Using xlsxwriter for advanced features
- ✅ Combining pandas and openpyxl
- ✅ Performance optimization
- ✅ Error handling
- ✅ Best practices

## Next Steps

In Session 4, you'll learn data manipulation techniques with pandas to clean, transform, and analyze Excel data before writing it out.

## Practice Exercises

See the `exercises/` directory for hands-on practice with these concepts.

