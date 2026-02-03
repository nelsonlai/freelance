# Session 8: Advanced Data Operations - Comprehensive Guide

## Introduction

This session covers advanced Excel operations that take your automation to the next level: named ranges, data validation, worksheet protection, Excel tables, freeze panes, and advanced filtering techniques.

## Part 1: Named Ranges

### What are Named Ranges?

Named ranges assign meaningful names to cell ranges instead of using references like "A1:C10". This makes formulas more readable and maintainable.

### Creating Named Ranges with openpyxl

```python
from openpyxl import Workbook
from openpyxl.workbook.defined_name import DefinedName

wb = Workbook()
ws = wb.active

# Add data
data = [
    ['Product', 'Price', 'Quantity'],
    ['Laptop', 1000, 5],
    ['Mouse', 25, 50],
    ['Keyboard', 75, 20]
]

for row in data:
    ws.append(row)

# Create named range
defined_name = DefinedName('ProductPrices', attr_text=f"'{ws.title}'!$B$2:$B$4")
wb.defined_names.append(defined_name)

# Use named range in formula
ws['E2'] = '=SUM(ProductPrices)'

wb.save('named_ranges.xlsx')
```

### Dynamic Named Ranges

```python
from openpyxl import Workbook

wb = Workbook()
ws = wb.active

# Add data
ws.append(['Sales'])
for i in range(10):
    ws.append([i * 1000])

# Create dynamic named range using OFFSET
# =OFFSET(Sheet!$A$2,0,0,COUNTA(Sheet!$A:$A)-1,1)
formula = f"=OFFSET('{ws.title}'!$A$2,0,0,COUNTA('{ws.title}'!$A:$A)-1,1)"

from openpyxl.workbook.defined_name import DefinedName
defined_name = DefinedName('DynamicSales', attr_text=formula)
wb.defined_names.append(defined_name)

wb.save('dynamic_named_ranges.xlsx')
```

### Reading Named Ranges

```python
from openpyxl import load_workbook

wb = load_workbook('named_ranges.xlsx')

# List all named ranges
for name in wb.defined_names:
    print(f"Name: {name.name}")
    print(f"Range: {name.value}")
    print()

# Access data from named range
for name in wb.defined_names:
    if name.name == 'ProductPrices':
        # Parse the range
        sheet_name, cell_range = name.value.split('!')
        sheet_name = sheet_name.strip("'")
        ws = wb[sheet_name]
        
        # Read data from range
        for row in ws[cell_range]:
            for cell in row:
                print(cell.value)
```

## Part 2: Data Validation

### Creating Dropdown Lists

```python
from openpyxl import Workbook
from openpyxl.worksheet.datavalidation import DataValidation

wb = Workbook()
ws = wb.active

# Add header
ws['A1'] = 'Department'
ws['B1'] = 'Employee'

# Create data validation (dropdown)
dv = DataValidation(
    type="list",
    formula1='"Sales,IT,HR,Marketing,Operations"',
    allow_blank=False
)

# Add a prompt message
dv.prompt = "Please select a department"
dv.promptTitle = "Department Selection"

# Add an error message
dv.error = "Invalid department selected"
dv.errorTitle = "Invalid Selection"

# Add validation to worksheet
ws.add_data_validation(dv)

# Apply to range
dv.add('A2:A100')

wb.save('data_validation.xlsx')
```

### Numeric Validation

```python
from openpyxl import Workbook
from openpyxl.worksheet.datavalidation import DataValidation

wb = Workbook()
ws = wb.active

ws['A1'] = 'Age'

# Create numeric validation (18-65 only)
dv = DataValidation(
    type="whole",
    operator="between",
    formula1=18,
    formula2=65,
    allow_blank=False
)

dv.prompt = "Enter age between 18 and 65"
dv.promptTitle = "Age Entry"
dv.error = "Age must be between 18 and 65"
dv.errorTitle = "Invalid Age"

ws.add_data_validation(dv)
dv.add('A2:A100')

wb.save('numeric_validation.xlsx')
```

### Date Validation

```python
from openpyxl import Workbook
from openpyxl.worksheet.datavalidation import DataValidation
from datetime import datetime

wb = Workbook()
ws = wb.active

ws['A1'] = 'Start Date'

# Only allow dates after today
dv = DataValidation(
    type="date",
    operator="greaterThan",
    formula1=datetime.now().date()
)

dv.prompt = "Enter a future date"
dv.error = "Date must be in the future"

ws.add_data_validation(dv)
dv.add('A2:A100')

wb.save('date_validation.xlsx')
```

### Validation Using Cell References

```python
from openpyxl import Workbook
from openpyxl.worksheet.datavalidation import DataValidation

wb = Workbook()
ws = wb.active

# Create list of valid values in a separate area
ws['F1'] = 'Valid Departments'
departments = ['Sales', 'IT', 'HR', 'Marketing', 'Operations']
for i, dept in enumerate(departments, 2):
    ws[f'F{i}'] = dept

# Create validation using the range
dv = DataValidation(type="list", formula1='$F$2:$F$6')
dv.prompt = "Select from the list"

ws.add_data_validation(dv)
dv.add('A2:A100')

wb.save('validation_cell_reference.xlsx')
```

## Part 3: Worksheet Protection

### Protect Worksheet

```python
from openpyxl import Workbook

wb = Workbook()
ws = wb.active

# Add data
ws['A1'] = 'Protected Data'
ws['A2'] = 100

# Protect worksheet with password
ws.protection.sheet = True
ws.protection.password = 'secret123'

# Optionally allow specific actions
ws.protection.formatCells = False  # Allow formatting
ws.protection.insertRows = False   # Prevent row insertion
ws.protection.deleteRows = False   # Prevent row deletion

wb.save('protected_worksheet.xlsx')
```

### Unlock Specific Cells

```python
from openpyxl import Workbook
from openpyxl.styles import Protection

wb = Workbook()
ws = wb.active

# Add headers (protected)
ws['A1'] = 'ID'
ws['B1'] = 'Name'
ws['C1'] = 'Editable Field'

# Add data
ws['A2'] = 1
ws['B2'] = 'Alice'
ws['C2'] = 'Edit me'

# Unlock specific cells (C column)
for row in range(2, 100):
    ws[f'C{row}'].protection = Protection(locked=False)

# Protect worksheet
ws.protection.sheet = True
ws.protection.password = 'secret123'

wb.save('partially_protected.xlsx')
```

### Protect Workbook

```python
from openpyxl import Workbook

wb = Workbook()
ws = wb.active

ws['A1'] = 'Data'

# Protect workbook structure (prevent adding/deleting sheets)
wb.security.workbookPassword = 'workbook123'
wb.security.lockStructure = True

wb.save('protected_workbook.xlsx')
```

## Part 4: Excel Tables

### Creating Excel Tables

```python
from openpyxl import Workbook
from openpyxl.worksheet.table import Table, TableStyleInfo

wb = Workbook()
ws = wb.active

# Add data
data = [
    ['ID', 'Name', 'Department', 'Salary'],
    [1, 'Alice', 'Sales', 60000],
    [2, 'Bob', 'IT', 75000],
    [3, 'Charlie', 'HR', 58000],
    [4, 'Diana', 'Sales', 62000]
]

for row in data:
    ws.append(row)

# Create table
tab = Table(displayName="EmployeeTable", ref="A1:D5")

# Add a built-in style
style = TableStyleInfo(
    name="TableStyleMedium9",
    showFirstColumn=False,
    showLastColumn=False,
    showRowStripes=True,
    showColumnStripes=False
)
tab.tableStyleInfo = style

ws.add_table(tab)

wb.save('excel_table.xlsx')
```

### Table with Totals Row

```python
from openpyxl import Workbook
from openpyxl.worksheet.table import Table, TableStyleInfo

wb = Workbook()
ws = wb.active

data = [
    ['Product', 'Q1', 'Q2', 'Q3', 'Q4'],
    ['Laptop', 100, 120, 110, 130],
    ['Mouse', 500, 550, 520, 580],
    ['Keyboard', 300, 320, 310, 340]
]

for row in data:
    ws.append(row)

# Create table with totals row
tab = Table(displayName="SalesTable", ref="A1:E4")
tab.totalsRowCount = 1  # Enable totals row

style = TableStyleInfo(
    name="TableStyleMedium2",
    showRowStripes=True
)
tab.tableStyleInfo = style

ws.add_table(tab)

wb.save('table_with_totals.xlsx')
```

## Part 5: Freeze Panes and Split Views

### Freeze Top Row

```python
from openpyxl import Workbook

wb = Workbook()
ws = wb.active

# Add headers
headers = ['ID', 'Name', 'Department', 'Salary', 'Bonus', 'Total']
ws.append(headers)

# Add data
for i in range(1, 101):
    ws.append([i, f'Employee{i}', 'Sales', 50000, 5000, 55000])

# Freeze top row (freeze row 1, start from row 2)
ws.freeze_panes = 'A2'

wb.save('freeze_top_row.xlsx')
```

### Freeze First Column

```python
from openpyxl import Workbook

wb = Workbook()
ws = wb.active

# Add data with many columns
for i in range(1, 101):
    row = [f'Row{i}'] + list(range(1, 21))  # 20 columns
    ws.append(row)

# Freeze first column (freeze column A, start from column B)
ws.freeze_panes = 'B1'

wb.save('freeze_first_column.xlsx')
```

### Freeze Both Row and Column

```python
from openpyxl import Workbook

wb = Workbook()
ws = wb.active

# Add headers
headers = ['ID'] + [f'Col{i}' for i in range(1, 21)]
ws.append(headers)

# Add data
for i in range(1, 101):
    ws.append([f'Row{i}'] + list(range(1, 21)))

# Freeze first row and first column (B2 means freeze everything above and left)
ws.freeze_panes = 'B2'

wb.save('freeze_both.xlsx')
```

## Part 6: Advanced Filtering

### AutoFilter

```python
from openpyxl import Workbook

wb = Workbook()
ws = wb.active

# Add data
data = [
    ['Name', 'Department', 'Salary', 'Status'],
    ['Alice', 'Sales', 60000, 'Active'],
    ['Bob', 'IT', 75000, 'Active'],
    ['Charlie', 'HR', 58000, 'Active'],
    ['Diana', 'Sales', 62000, 'Inactive'],
    ['Eve', 'IT', 72000, 'Active']
]

for row in data:
    ws.append(row)

# Add autofilter
ws.auto_filter.ref = 'A1:D6'

wb.save('autofilter.xlsx')
```

### Filter Criteria (Reading)

```python
from openpyxl import load_workbook

wb = load_workbook('data.xlsx')
ws = wb.active

# Apply filter manually in Excel, then read
if ws.auto_filter:
    print(f"AutoFilter range: {ws.auto_filter.ref}")
    
    # Access filter column
    for filter_col in ws.auto_filter.filterColumn:
        print(f"Column {filter_col.colId} has filters")
```

## Part 7: Working with Comments and Notes

### Adding Comments (Legacy)

```python
from openpyxl import Workbook
from openpyxl.comments import Comment

wb = Workbook()
ws = wb.active

ws['A1'] = 'Important Data'

# Add comment
comment = Comment('This is a critical value. Do not change without approval.', 'John Doe')
ws['A1'].comment = comment

wb.save('with_comments.xlsx')
```

### Reading Comments

```python
from openpyxl import load_workbook

wb = load_workbook('with_comments.xlsx')
ws = wb.active

# Read all comments
for row in ws.iter_rows():
    for cell in row:
        if cell.comment:
            print(f"Cell {cell.coordinate}: {cell.comment.text}")
            print(f"Author: {cell.comment.author}")
```

## Part 8: Hidden Rows and Columns

### Hide Rows and Columns

```python
from openpyxl import Workbook

wb = Workbook()
ws = wb.active

# Add data
for i in range(1, 11):
    ws.append([f'Row {i}', i * 100, i * 200])

# Hide specific rows
ws.row_dimensions[3].hidden = True
ws.row_dimensions[5].hidden = True

# Hide specific columns
ws.column_dimensions['B'].hidden = True

wb.save('hidden_rows_cols.xlsx')
```

### Unhide All Rows and Columns

```python
from openpyxl import load_workbook

wb = load_workbook('hidden_rows_cols.xlsx')
ws = wb.active

# Unhide all rows
for row in ws.row_dimensions:
    ws.row_dimensions[row].hidden = False

# Unhide all columns
for col in ws.column_dimensions:
    ws.column_dimensions[col].hidden = False

wb.save('unhidden.xlsx')
```

## Part 9: Group Rows and Columns

### Grouping (Outlining)

```python
from openpyxl import Workbook

wb = Workbook()
ws = wb.active

# Add data
ws.append(['Category', 'Subcategory', 'Value'])
ws.append(['Sales', 'Q1', 100])
ws.append(['Sales', 'Q2', 120])
ws.append(['Sales', 'Q3', 110])
ws.append(['Sales', 'Q4', 130])
ws.append(['Marketing', 'Q1', 50])
ws.append(['Marketing', 'Q2', 55])

# Group rows (outline level)
ws.row_dimensions.group(2, 5, outline_level=1)  # Group Q1-Q4 under Sales
ws.row_dimensions.group(6, 7, outline_level=1)  # Group Q1-Q2 under Marketing

wb.save('grouped_rows.xlsx')
```

## Part 10: Advanced Copy Operations

### Copy Ranges

```python
from openpyxl import Workbook
from copy import copy

wb = Workbook()
ws = wb.active

# Add source data
ws['A1'] = 'Source'
ws['A2'] = 100
ws['A3'] = 200

# Copy range
for row in range(1, 4):
    source_cell = ws[f'A{row}']
    target_cell = ws[f'C{row}']
    
    target_cell.value = source_cell.value
    
    # Copy formatting too
    if source_cell.has_style:
        target_cell.font = copy(source_cell.font)
        target_cell.border = copy(source_cell.border)
        target_cell.fill = copy(source_cell.fill)
        target_cell.number_format = copy(source_cell.number_format)
        target_cell.protection = copy(source_cell.protection)
        target_cell.alignment = copy(source_cell.alignment)

wb.save('copied_range.xlsx')
```

## Best Practices

1. **Named Ranges** - Use for frequently referenced ranges
2. **Data Validation** - Prevent data entry errors
3. **Protection** - Protect formulas, allow data entry
4. **Tables** - Automatic range expansion, better formulas
5. **Freeze Panes** - Improve navigation in large sheets
6. **AutoFilter** - Enable easy data filtering
7. **Comments** - Document important cells
8. **Hidden Rows/Cols** - Hide intermediate calculations
9. **Grouping** - Organize hierarchical data
10. **Test in Excel** - Always verify features work

## Summary

You've learned how to:
- ✅ Create and use named ranges
- ✅ Implement data validation (dropdowns, numeric, dates)
- ✅ Protect worksheets and workbooks
- ✅ Create Excel tables with formatting
- ✅ Freeze panes and split views
- ✅ Add autofilters
- ✅ Work with comments and notes
- ✅ Hide/unhide rows and columns
- ✅ Group rows and columns
- ✅ Copy ranges with formatting

## Next Steps

In Session 9, you'll learn how to work with large Excel files efficiently, including chunking, streaming, and optimization techniques.

