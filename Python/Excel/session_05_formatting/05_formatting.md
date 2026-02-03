# Session 5: Excel Formatting and Styling - Comprehensive Guide

## Introduction

Creating professional-looking Excel reports is essential for presenting data effectively. This session teaches you how to format Excel files with colors, fonts, borders, number formats, and conditional formatting to create reports that look as good as they are informative.

## Why Formatting Matters

1. **Professional Appearance** - Well-formatted reports inspire confidence
2. **Readability** - Proper formatting makes data easier to understand
3. **Emphasis** - Draw attention to important information
4. **Branding** - Match company colors and styles
5. **Accessibility** - Improve readability for all users

## Libraries for Formatting

### openpyxl - Complete Control
- **Best for**: Complex formatting, modifying existing files
- **Pros**: Full Excel feature support
- **Cons**: More verbose syntax

### xlsxwriter - High Performance
- **Best for**: Creating new formatted files
- **Pros**: Fast, excellent documentation
- **Cons**: Cannot read or modify existing files

## Basic Cell Formatting with openpyxl

### Font Styling

```python
from openpyxl import Workbook
from openpyxl.styles import Font

wb = Workbook()
ws = wb.active

# Basic font properties
ws['A1'] = 'Bold Text'
ws['A1'].font = Font(bold=True)

ws['A2'] = 'Italic Text'
ws['A2'].font = Font(italic=True)

ws['A3'] = 'Bold and Italic'
ws['A3'].font = Font(bold=True, italic=True)

# Font size and color
ws['B1'] = 'Large Text'
ws['B1'].font = Font(size=16)

ws['B2'] = 'Red Text'
ws['B2'].font = Font(color='FF0000')

ws['B3'] = 'Blue Bold Large'
ws['B3'].font = Font(bold=True, size=14, color='0000FF')

# Font family
ws['C1'] = 'Arial'
ws['C1'].font = Font(name='Arial', size=12)

ws['C2'] = 'Calibri'
ws['C2'].font = Font(name='Calibri', size=12)

ws['C3'] = 'Times New Roman'
ws['C3'].font = Font(name='Times New Roman', size=12)

wb.save('font_styling.xlsx')
```

### Cell Fill (Background Color)

```python
from openpyxl import Workbook
from openpyxl.styles import PatternFill

wb = Workbook()
ws = wb.active

# Solid fills
ws['A1'] = 'Light Blue'
ws['A1'].fill = PatternFill(start_color='ADD8E6', end_color='ADD8E6', fill_type='solid')

ws['A2'] = 'Light Green'
ws['A2'].fill = PatternFill(start_color='90EE90', end_color='90EE90', fill_type='solid')

ws['A3'] = 'Light Yellow'
ws['A3'].fill = PatternFill(start_color='FFFFE0', end_color='FFFFE0', fill_type='solid')

# Corporate colors
ws['B1'] = 'Primary Blue'
ws['B1'].fill = PatternFill(start_color='4472C4', end_color='4472C4', fill_type='solid')
ws['B1'].font = Font(color='FFFFFF', bold=True)

ws['B2'] = 'Secondary Gray'
ws['B2'].fill = PatternFill(start_color='808080', end_color='808080', fill_type='solid')
ws['B2'].font = Font(color='FFFFFF')

wb.save('cell_fills.xlsx')
```

### Cell Borders

```python
from openpyxl import Workbook
from openpyxl.styles import Border, Side

wb = Workbook()
ws = wb.active

# Define border styles
thin_border = Border(
    left=Side(style='thin'),
    right=Side(style='thin'),
    top=Side(style='thin'),
    bottom=Side(style='thin')
)

thick_border = Border(
    left=Side(style='thick'),
    right=Side(style='thick'),
    top=Side(style='thick'),
    bottom=Side(style='thick')
)

# Apply borders
ws['A1'] = 'Thin Border'
ws['A1'].border = thin_border

ws['B1'] = 'Thick Border'
ws['B1'].border = thick_border

# Different styles on different sides
custom_border = Border(
    top=Side(style='thick', color='FF0000'),
    bottom=Side(style='double'),
    left=Side(style='thin'),
    right=Side(style='thin')
)

ws['C1'] = 'Custom Border'
ws['C1'].border = custom_border

wb.save('borders.xlsx')
```

### Cell Alignment

```python
from openpyxl import Workbook
from openpyxl.styles import Alignment

wb = Workbook()
ws = wb.active

# Horizontal alignment
ws['A1'] = 'Left'
ws['A1'].alignment = Alignment(horizontal='left')

ws['B1'] = 'Center'
ws['B1'].alignment = Alignment(horizontal='center')

ws['C1'] = 'Right'
ws['C1'].alignment = Alignment(horizontal='right')

# Vertical alignment
ws.row_dimensions[3].height = 30

ws['A3'] = 'Top'
ws['A3'].alignment = Alignment(vertical='top')

ws['B3'] = 'Center'
ws['B3'].alignment = Alignment(vertical='center')

ws['C3'] = 'Bottom'
ws['C3'].alignment = Alignment(vertical='bottom')

# Text wrap
ws['A5'] = 'This is a long text that will wrap to multiple lines'
ws['A5'].alignment = Alignment(wrap_text=True)
ws.column_dimensions['A'].width = 20

# Text rotation
ws['B5'] = 'Rotated Text'
ws['B5'].alignment = Alignment(text_rotation=45)

wb.save('alignment.xlsx')
```

## Number Formatting

### Currency, Percentage, and Date Formats

```python
from openpyxl import Workbook
from datetime import datetime

wb = Workbook()
ws = wb.active

# Currency formats
ws['A1'] = 'Currency'
ws['B1'] = 1234.56
ws['B1'].number_format = '$#,##0.00'

ws['A2'] = 'Accounting'
ws['B2'] = 1234.56
ws['B2'].number_format = '_($* #,##0.00_);_($* (#,##0.00);_($* "-"??_);_(@_)'

# Percentage formats
ws['A3'] = 'Percentage'
ws['B3'] = 0.856
ws['B3'].number_format = '0.00%'

ws['A4'] = 'One decimal'
ws['B4'] = 0.856
ws['B4'].number_format = '0.0%'

# Date formats
ws['A5'] = 'Date Short'
ws['B5'] = datetime(2024, 3, 15)
ws['B5'].number_format = 'MM/DD/YYYY'

ws['A6'] = 'Date Long'
ws['B6'] = datetime(2024, 3, 15)
ws['B6'].number_format = 'MMMM DD, YYYY'

ws['A7'] = 'Date and Time'
ws['B7'] = datetime(2024, 3, 15, 14, 30, 0)
ws['B7'].number_format = 'MM/DD/YYYY HH:MM:SS'

# Number formats
ws['A8'] = 'Thousands Separator'
ws['B8'] = 1234567.89
ws['B8'].number_format = '#,##0.00'

ws['A9'] = 'Scientific'
ws['B9'] = 1234567.89
ws['B9'].number_format = '0.00E+00'

# Custom format
ws['A10'] = 'Positive/Negative'
ws['B10'] = -1234.56
ws['B10'].number_format = '#,##0.00_);[Red](#,##0.00)'

wb.save('number_formats.xlsx')
```

## Column Width and Row Height

### Manual Sizing

```python
from openpyxl import Workbook

wb = Workbook()
ws = wb.active

# Set specific column widths
ws.column_dimensions['A'].width = 20
ws.column_dimensions['B'].width = 15
ws.column_dimensions['C'].width = 30

# Set specific row heights
ws.row_dimensions[1].height = 30
ws.row_dimensions[2].height = 20

# Add data
ws['A1'] = 'Wide Column'
ws['B1'] = 'Medium'
ws['C1'] = 'Extra Wide Column'

wb.save('column_widths.xlsx')
```

### Auto-fit Columns

```python
from openpyxl import Workbook

wb = Workbook()
ws = wb.active

# Add data
data = [
    ['Name', 'Email', 'Department'],
    ['Alice Smith', 'alice@company.com', 'Sales'],
    ['Bob', 'bob@company.com', 'IT'],
    ['Charlie Brown', 'charlie.brown@company.com', 'Human Resources']
]

for row in data:
    ws.append(row)

# Auto-fit columns based on content
for column in ws.columns:
    max_length = 0
    column_letter = column[0].column_letter
    
    for cell in column:
        if cell.value:
            cell_length = len(str(cell.value))
            max_length = max(max_length, cell_length)
    
    # Add padding
    adjusted_width = max_length + 2
    ws.column_dimensions[column_letter].width = adjusted_width

wb.save('auto_fit.xlsx')
```

## Conditional Formatting

### Basic Rules

```python
from openpyxl import Workbook
from openpyxl.formatting.rule import CellIsRule
from openpyxl.styles import PatternFill, Font

wb = Workbook()
ws = wb.active

# Add data
ws['A1'] = 'Value'
for i in range(2, 12):
    ws[f'A{i}'] = i * 10

# Highlight cells greater than 50
red_fill = PatternFill(start_color='FFC7CE', end_color='FFC7CE', fill_type='solid')
red_font = Font(color='9C0006')

rule1 = CellIsRule(
    operator='greaterThan',
    formula=['50'],
    fill=red_fill,
    font=red_font
)
ws.conditional_formatting.add('A2:A11', rule1)

# Highlight cells less than 30
green_fill = PatternFill(start_color='C6EFCE', end_color='C6EFCE', fill_type='solid')
green_font = Font(color='006100')

rule2 = CellIsRule(
    operator='lessThan',
    formula=['30'],
    fill=green_fill,
    font=green_font
)
ws.conditional_formatting.add('A2:A11', rule2)

wb.save('conditional_formatting.xlsx')
```

### Color Scales

```python
from openpyxl import Workbook
from openpyxl.formatting.rule import ColorScaleRule

wb = Workbook()
ws = wb.active

# Add data
ws.append(['Score'])
for i in range(1, 21):
    ws.append([i * 5])

# Add color scale (red to yellow to green)
color_scale = ColorScaleRule(
    start_type='min',
    start_color='FF0000',  # Red
    mid_type='percentile',
    mid_value=50,
    mid_color='FFFF00',  # Yellow
    end_type='max',
    end_color='00FF00'  # Green
)

ws.conditional_formatting.add('A2:A21', color_scale)

wb.save('color_scale.xlsx')
```

### Data Bars

```python
from openpyxl import Workbook
from openpyxl.formatting.rule import DataBarRule

wb = Workbook()
ws = wb.active

# Add data
ws.append(['Revenue'])
revenues = [45000, 52000, 48000, 61000, 55000, 58000]
for revenue in revenues:
    ws.append([revenue])

# Add data bars
data_bar = DataBarRule(
    start_type='min',
    end_type='max',
    color='4472C4'
)

ws.conditional_formatting.add('A2:A7', data_bar)

wb.save('data_bars.xlsx')
```

## Formatting with xlsxwriter

### Complete Example

```python
import xlsxwriter

# Create workbook
workbook = xlsxwriter.Workbook('xlsxwriter_formatted.xlsx')
worksheet = workbook.add_worksheet('Report')

# Define formats
title_format = workbook.add_format({
    'bold': True,
    'font_size': 16,
    'align': 'center',
    'valign': 'vcenter',
    'fg_color': '#4472C4',
    'font_color': 'white'
})

header_format = workbook.add_format({
    'bold': True,
    'font_size': 11,
    'align': 'center',
    'valign': 'vcenter',
    'fg_color': '#D9E1F2',
    'border': 1
})

currency_format = workbook.add_format({
    'num_format': '$#,##0.00',
    'align': 'right',
    'border': 1
})

percent_format = workbook.add_format({
    'num_format': '0.0%',
    'align': 'right',
    'border': 1
})

text_format = workbook.add_format({
    'align': 'left',
    'border': 1
})

# Write title
worksheet.merge_range('A1:E1', 'Q1 2024 Sales Report', title_format)
worksheet.set_row(0, 30)

# Write headers
headers = ['Region', 'Sales', 'Target', 'Achievement', 'Status']
for col, header in enumerate(headers):
    worksheet.write(1, col, header, header_format)

# Write data
data = [
    ['North', 125000, 100000, 1.25, 'Above Target'],
    ['South', 98000, 110000, 0.891, 'Below Target'],
    ['East', 142000, 130000, 1.092, 'Above Target'],
    ['West', 115000, 105000, 1.095, 'Above Target']
]

for row_idx, row_data in enumerate(data, 2):
    worksheet.write(row_idx, 0, row_data[0], text_format)
    worksheet.write(row_idx, 1, row_data[1], currency_format)
    worksheet.write(row_idx, 2, row_data[2], currency_format)
    worksheet.write(row_idx, 3, row_data[3], percent_format)
    worksheet.write(row_idx, 4, row_data[4], text_format)

# Set column widths
worksheet.set_column('A:A', 15)
worksheet.set_column('B:C', 12)
worksheet.set_column('D:D', 12)
worksheet.set_column('E:E', 15)

workbook.close()
```

## Combining Pandas and Formatting

### Complete Workflow

```python
import pandas as pd
from openpyxl import load_workbook
from openpyxl.styles import Font, PatternFill, Border, Side, Alignment

# Step 1: Create and manipulate data with pandas
df = pd.DataFrame({
    'Product': ['Laptop', 'Mouse', 'Keyboard', 'Monitor', 'Webcam'],
    'Q1': [45, 120, 85, 32, 67],
    'Q2': [52, 135, 90, 38, 71],
    'Q3': [48, 128, 88, 35, 69],
    'Q4': [56, 142, 95, 41, 75]
})

df['Total'] = df[['Q1', 'Q2', 'Q3', 'Q4']].sum(axis=1)
df['Average'] = df[['Q1', 'Q2', 'Q3', 'Q4']].mean(axis=1).round(1)

# Step 2: Write to Excel with pandas
output_file = 'formatted_report.xlsx'
df.to_excel(output_file, index=False, sheet_name='Sales')

# Step 3: Format with openpyxl
wb = load_workbook(output_file)
ws = wb['Sales']

# Define styles
header_font = Font(bold=True, size=12, color='FFFFFF')
header_fill = PatternFill(start_color='366092', end_color='366092', fill_type='solid')
header_alignment = Alignment(horizontal='center', vertical='center')
border = Border(
    left=Side(style='thin'),
    right=Side(style='thin'),
    top=Side(style='thin'),
    bottom=Side(style='thin')
)

# Format headers
for cell in ws[1]:
    cell.font = header_font
    cell.fill = header_fill
    cell.alignment = header_alignment
    cell.border = border

# Format data cells
for row in ws.iter_rows(min_row=2, max_row=ws.max_row, min_col=1, max_col=ws.max_column):
    for cell in row:
        cell.border = border
        if cell.column > 1:  # Numeric columns
            cell.alignment = Alignment(horizontal='right')

# Auto-fit columns
for column in ws.columns:
    max_length = 0
    column_letter = column[0].column_letter
    for cell in column:
        if cell.value:
            max_length = max(max_length, len(str(cell.value)))
    ws.column_dimensions[column_letter].width = max_length + 3

# Highlight totals column
total_fill = PatternFill(start_color='FFE699', end_color='FFE699', fill_type='solid')
for row in range(2, ws.max_row + 1):
    ws.cell(row=row, column=6).fill = total_fill
    ws.cell(row=row, column=6).font = Font(bold=True)

wb.save(output_file)
```

## Professional Report Template

### Complete Example

```python
import pandas as pd
from openpyxl import Workbook
from openpyxl.styles import Font, PatternFill, Border, Side, Alignment
from openpyxl.utils.dataframe import dataframe_to_rows
from datetime import datetime

# Create data
df = pd.DataFrame({
    'Department': ['Sales', 'Marketing', 'IT', 'HR', 'Operations'],
    'Budget': [500000, 200000, 350000, 150000, 400000],
    'Actual': [480000, 195000, 340000, 148000, 395000],
    'Employees': [45, 12, 28, 8, 35]
})

df['Variance'] = df['Budget'] - df['Actual']
df['Variance_%'] = ((df['Variance'] / df['Budget']) * 100).round(1)

# Create workbook
wb = Workbook()
ws = wb.active
ws.title = "Budget Report"

# Company header
ws['A1'] = 'COMPANY NAME'
ws['A1'].font = Font(bold=True, size=18, color='003366')
ws.merge_range('A1:F1')

ws['A2'] = f'Budget Report - {datetime.now().strftime("%B %Y")}'
ws['A2'].font = Font(size=12, color='666666')
ws.merge_range('A2:F2')

# Write DataFrame starting from row 4
start_row = 4
for r_idx, row in enumerate(dataframe_to_rows(df, index=False, header=True), start_row):
    for c_idx, value in enumerate(row, 1):
        cell = ws.cell(row=r_idx, column=c_idx, value=value)
        
        # Header row
        if r_idx == start_row:
            cell.font = Font(bold=True, color='FFFFFF')
            cell.fill = PatternFill(start_color='4472C4', end_color='4472C4', fill_type='solid')
            cell.alignment = Alignment(horizontal='center')
        else:
            # Currency format for budget columns
            if c_idx in [2, 3, 5]:
                cell.number_format = '$#,##0'
            # Percentage format
            if c_idx == 6:
                cell.number_format = '0.0%'
        
        # Apply border
        cell.border = Border(
            left=Side(style='thin'),
            right=Side(style='thin'),
            top=Side(style='thin'),
            bottom=Side(style='thin')
        )

# Auto-fit columns
for column in ws.columns:
    max_length = 0
    column_letter = column[0].column_letter
    for cell in column:
        if cell.value:
            max_length = max(max_length, len(str(cell.value)))
    ws.column_dimensions[column_letter].width = max_length + 3

wb.save('professional_report.xlsx')
```

## Best Practices

1. **Consistent Styling** - Use same colors and fonts throughout
2. **Readable Fonts** - Stick to Arial, Calibri, or similar
3. **Appropriate Colors** - Use color to emphasize, not decorate
4. **White Space** - Don't overcrowd cells
5. **Alignment** - Left for text, right for numbers, center for headers
6. **Borders** - Use sparingly, avoid heavy borders
7. **Number Formats** - Always format currency, percentages, dates
8. **Column Widths** - Auto-fit or set appropriate widths
9. **Professional Colors** - Use corporate colors or professional palette
10. **Accessibility** - Ensure good contrast, avoid red-green only indicators

## Summary

You've learned how to:
- ✅ Apply fonts, colors, and borders
- ✅ Format numbers (currency, percentage, dates)
- ✅ Adjust column widths and row heights
- ✅ Use conditional formatting
- ✅ Format with openpyxl and xlsxwriter
- ✅ Combine pandas with formatting
- ✅ Create professional report templates

## Next Steps

In Session 6, you'll learn how to add Excel formulas and create charts to make your reports even more powerful and informative.

