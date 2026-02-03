# Session 6: Working with Formulas and Charts - Comprehensive Guide

## Introduction

Excel formulas and charts are essential for creating dynamic, interactive reports. This session teaches you how to write Excel formulas from Python and create professional charts that visualize your data effectively.

## Why Use Formulas and Charts?

1. **Dynamic Calculations** - Formulas update automatically when data changes
2. **Visual Communication** - Charts convey trends instantly
3. **Professional Reports** - Combination creates compelling dashboards
4. **Interactive Analysis** - Users can modify and explore data
5. **Standard Excel Experience** - Recipients can use normal Excel features

## Part 1: Working with Formulas

### Understanding Formula Approaches

**Two main strategies:**
1. **Calculate in Python** - Use pandas, write results
2. **Write Excel Formulas** - Formulas calculate in Excel

**When to use each:**
- **Python calculation**: Better for complex logic, faster for large datasets
- **Excel formulas**: Better for user interaction, updating data

### Writing Basic Formulas with openpyxl

```python
from openpyxl import Workbook

wb = Workbook()
ws = wb.active

# Add data
ws['A1'] = 'Price'
ws['A2'] = 100
ws['A3'] = 200
ws['A4'] = 300

ws['B1'] = 'Quantity'
ws['B2'] = 5
ws['B3'] = 3
ws['B4'] = 7

# Write formulas
ws['C1'] = 'Total'
ws['C2'] = '=A2*B2'  # Simple formula
ws['C3'] = '=A3*B3'
ws['C4'] = '=A4*B4'

# Sum formula
ws['C5'] = '=SUM(C2:C4)'

wb.save('simple_formulas.xlsx')
```

### Dynamic Formula Generation

```python
from openpyxl import Workbook

wb = Workbook()
ws = wb.active

# Headers
headers = ['Product', 'Price', 'Quantity', 'Total']
ws.append(headers)

# Data
products = [
    ('Laptop', 1000, 5),
    ('Mouse', 25, 50),
    ('Keyboard', 75, 20),
    ('Monitor', 300, 10)
]

# Write data and formulas
for row_idx, (product, price, qty) in enumerate(products, 2):
    ws[f'A{row_idx}'] = product
    ws[f'B{row_idx}'] = price
    ws[f'C{row_idx}'] = qty
    ws[f'D{row_idx}'] = f'=B{row_idx}*C{row_idx}'  # Dynamic formula

# Add totals row
last_row = len(products) + 2
ws[f'A{last_row}'] = 'TOTAL'
ws[f'B{last_row}'] = f'=SUM(B2:B{last_row-1})'
ws[f'C{last_row}'] = f'=SUM(C2:C{last_row-1})'
ws[f'D{last_row}'] = f'=SUM(D2:D{last_row-1})'

wb.save('dynamic_formulas.xlsx')
```

### Common Excel Functions

#### SUM, AVERAGE, COUNT

```python
ws['A1'] = '=SUM(B1:B10)'
ws['A2'] = '=AVERAGE(B1:B10)'
ws['A3'] = '=COUNT(B1:B10)'
ws['A4'] = '=COUNTA(B1:B10)'  # Count non-empty cells
ws['A5'] = '=COUNTBLANK(B1:B10)'  # Count blank cells
```

#### MAX, MIN

```python
ws['A1'] = '=MAX(B1:B10)'
ws['A2'] = '=MIN(B1:B10)'
```

#### IF Statements

```python
# Simple IF
ws['C2'] = '=IF(B2>100, "High", "Low")'

# Nested IF
ws['C2'] = '=IF(B2>=90, "A", IF(B2>=80, "B", "C"))'

# IF with calculation
ws['C2'] = '=IF(B2>100, B2*0.1, B2*0.05)'
```

#### VLOOKUP and XLOOKUP

```python
# VLOOKUP
ws['E2'] = '=VLOOKUP(D2, A2:B10, 2, FALSE)'

# XLOOKUP (Excel 365)
ws['E2'] = '=XLOOKUP(D2, A2:A10, B2:B10)'
```

#### TEXT Functions

```python
# Concatenation
ws['C2'] = '=A2&" "&B2'  # Or: =CONCAT(A2, " ", B2)

# Text manipulation
ws['C2'] = '=UPPER(A2)'  # Convert to uppercase
ws['C2'] = '=LOWER(A2)'  # Convert to lowercase
ws['C2'] = '=PROPER(A2)'  # Title Case
ws['C2'] = '=LEFT(A2, 5)'  # First 5 characters
ws['C2'] = '=RIGHT(A2, 3)'  # Last 3 characters
```

#### Date Functions

```python
# Current date/time
ws['A1'] = '=TODAY()'
ws['A2'] = '=NOW()'

# Date calculations
ws['A3'] = '=YEAR(A1)'
ws['A4'] = '=MONTH(A1)'
ws['A5'] = '=DAY(A1)'

# Date difference
ws['A6'] = '=DATEDIF(A1, B1, "D")'  # Days between dates
```

### Advanced Formula Patterns

#### Conditional Aggregation (SUMIF, COUNTIF)

```python
# SUMIF
ws['E2'] = '=SUMIF(A2:A10, "Sales", B2:B10)'

# COUNTIF
ws['E3'] = '=COUNTIF(A2:A10, ">100")'

# SUMIFS (multiple conditions)
ws['E4'] = '=SUMIFS(C2:C10, A2:A10, "Sales", B2:B10, ">100")'
```

#### Array Formulas

```python
# Array formula (requires special handling)
ws['C2'] = '{=SUM(A2:A10*B2:B10)}'
```

### Using xlsxwriter for Formulas

```python
import xlsxwriter

workbook = xlsxwriter.Workbook('formulas_xlsxwriter.xlsx')
worksheet = workbook.add_worksheet()

# Write data
worksheet.write('A1', 'Price')
worksheet.write('B1', 'Quantity')
worksheet.write('C1', 'Total')

prices = [100, 200, 300]
quantities = [5, 3, 7]

for row, (price, qty) in enumerate(zip(prices, quantities), 1):
    worksheet.write(row, 0, price)
    worksheet.write(row, 1, qty)
    worksheet.write_formula(row, 2, f'=A{row+1}*B{row+1}')

# Add total
worksheet.write_formula(4, 2, '=SUM(C2:C4)')

workbook.close()
```

## Part 2: Creating Charts

### Chart Types Overview

| Chart Type | Best For | Example Use |
|------------|----------|-------------|
| Line | Trends over time | Sales trends, stock prices |
| Bar/Column | Comparing categories | Regional sales, product comparison |
| Pie | Part-to-whole | Market share, budget allocation |
| Scatter | Correlation | Price vs sales, height vs weight |
| Area | Cumulative data | Stacked revenue streams |

### Creating Charts with openpyxl

#### Basic Column Chart

```python
from openpyxl import Workbook
from openpyxl.chart import BarChart, Reference

wb = Workbook()
ws = wb.active

# Add data
data = [
    ['Product', 'Sales'],
    ['Laptop', 120000],
    ['Mouse', 35000],
    ['Keyboard', 45000],
    ['Monitor', 78000]
]

for row in data:
    ws.append(row)

# Create chart
chart = BarChart()
chart.type = 'col'  # Column chart
chart.title = 'Product Sales'
chart.x_axis.title = 'Product'
chart.y_axis.title = 'Sales ($)'

# Define data range
data_ref = Reference(ws, min_col=2, min_row=1, max_row=5)
categories_ref = Reference(ws, min_col=1, min_row=2, max_row=5)

chart.add_data(data_ref, titles_from_data=True)
chart.set_categories(categories_ref)

# Add chart to worksheet
ws.add_chart(chart, 'D2')

wb.save('column_chart.xlsx')
```

#### Line Chart

```python
from openpyxl import Workbook
from openpyxl.chart import LineChart, Reference

wb = Workbook()
ws = wb.active

# Add data
data = [
    ['Month', 'Sales'],
    ['Jan', 45000],
    ['Feb', 52000],
    ['Mar', 48000],
    ['Apr', 61000],
    ['May', 55000],
    ['Jun', 58000]
]

for row in data:
    ws.append(row)

# Create line chart
chart = LineChart()
chart.title = 'Monthly Sales Trend'
chart.style = 10
chart.x_axis.title = 'Month'
chart.y_axis.title = 'Sales ($)'

data_ref = Reference(ws, min_col=2, min_row=1, max_row=7)
categories_ref = Reference(ws, min_col=1, min_row=2, max_row=7)

chart.add_data(data_ref, titles_from_data=True)
chart.set_categories(categories_ref)

ws.add_chart(chart, 'D2')

wb.save('line_chart.xlsx')
```

#### Pie Chart

```python
from openpyxl import Workbook
from openpyxl.chart import PieChart, Reference

wb = Workbook()
ws = wb.active

# Add data
data = [
    ['Department', 'Budget'],
    ['Sales', 500000],
    ['Marketing', 200000],
    ['IT', 350000],
    ['HR', 150000]
]

for row in data:
    ws.append(row)

# Create pie chart
chart = PieChart()
chart.title = 'Budget Distribution'

data_ref = Reference(ws, min_col=2, min_row=1, max_row=5)
labels_ref = Reference(ws, min_col=1, min_row=2, max_row=5)

chart.add_data(data_ref, titles_from_data=True)
chart.set_categories(labels_ref)

ws.add_chart(chart, 'D2')

wb.save('pie_chart.xlsx')
```

#### Scatter Plot

```python
from openpyxl import Workbook
from openpyxl.chart import ScatterChart, Reference, Series

wb = Workbook()
ws = wb.active

# Add data
ws.append(['Price', 'Units Sold'])
data = [(10, 100), (15, 85), (20, 70), (25, 60), (30, 45)]
for price, units in data:
    ws.append([price, units])

# Create scatter chart
chart = ScatterChart()
chart.title = 'Price vs Units Sold'
chart.x_axis.title = 'Price ($)'
chart.y_axis.title = 'Units Sold'

xvalues = Reference(ws, min_col=1, min_row=2, max_row=6)
yvalues = Reference(ws, min_col=2, min_row=2, max_row=6)

series = Series(yvalues, xvalues, title='Sales Data')
chart.series.append(series)

ws.add_chart(chart, 'D2')

wb.save('scatter_chart.xlsx')
```

### Multiple Series Charts

```python
from openpyxl import Workbook
from openpyxl.chart import LineChart, Reference

wb = Workbook()
ws = wb.active

# Add data with multiple series
data = [
    ['Month', 'Product A', 'Product B', 'Product C'],
    ['Jan', 45, 38, 52],
    ['Feb', 52, 42, 48],
    ['Mar', 48, 45, 55],
    ['Apr', 61, 50, 58],
    ['May', 55, 48, 62]
]

for row in data:
    ws.append(row)

# Create chart with multiple series
chart = LineChart()
chart.title = 'Product Sales Comparison'
chart.style = 10
chart.x_axis.title = 'Month'
chart.y_axis.title = 'Sales (000s)'

data_ref = Reference(ws, min_col=2, max_col=4, min_row=1, max_row=6)
categories_ref = Reference(ws, min_col=1, min_row=2, max_row=6)

chart.add_data(data_ref, titles_from_data=True)
chart.set_categories(categories_ref)

ws.add_chart(chart, 'F2')

wb.save('multiple_series.xlsx')
```

### Chart Styling

```python
from openpyxl import Workbook
from openpyxl.chart import LineChart, Reference
from openpyxl.chart.marker import Marker

wb = Workbook()
ws = wb.active

# Add data
for row in [['Month', 'Sales'], ['Jan', 45], ['Feb', 52], ['Mar', 48]]:
    ws.append(row)

chart = LineChart()
chart.title = 'Styled Chart'
chart.style = 12  # Built-in style
chart.y_axis.title = 'Sales ($)'
chart.x_axis.title = 'Month'

# Customize appearance
chart.height = 10  # Height in cm
chart.width = 20   # Width in cm

# Add data markers
data_ref = Reference(ws, min_col=2, min_row=1, max_row=4)
categories_ref = Reference(ws, min_col=1, min_row=2, max_row=4)

chart.add_data(data_ref, titles_from_data=True)
chart.set_categories(categories_ref)

# Style the series
series = chart.series[0]
series.marker = Marker('circle')
series.marker.size = 7

ws.add_chart(chart, 'D2')

wb.save('styled_chart.xlsx')
```

### Using xlsxwriter for Charts

```python
import xlsxwriter

workbook = xlsxwriter.Workbook('xlsxwriter_chart.xlsx')
worksheet = workbook.add_worksheet()

# Add data
headers = ['Product', 'Q1', 'Q2', 'Q3', 'Q4']
worksheet.write_row('A1', headers)

data = [
    ['Laptop', 45, 52, 48, 56],
    ['Mouse', 120, 135, 128, 142],
    ['Keyboard', 85, 90, 88, 95]
]

for row_idx, row_data in enumerate(data, 1):
    worksheet.write_row(row_idx, 0, row_data)

# Create column chart
chart = workbook.add_chart({'type': 'column'})

# Configure series
for row in range(1, 4):
    chart.add_series({
        'name': ['Sheet1', row, 0],
        'categories': ['Sheet1', 0, 1, 0, 4],
        'values': ['Sheet1', row, 1, row, 4]
    })

# Configure chart
chart.set_title({'name': 'Quarterly Sales'})
chart.set_x_axis({'name': 'Quarter'})
chart.set_y_axis({'name': 'Units Sold'})
chart.set_style(10)

# Insert chart
worksheet.insert_chart('G2', chart, {'x_scale': 1.5, 'y_scale': 1.5})

workbook.close()
```

## Combining Pandas, Formulas, and Charts

### Complete Dashboard Example

```python
import pandas as pd
from openpyxl import load_workbook
from openpyxl.chart import LineChart, BarChart, Reference
from openpyxl.styles import Font, PatternFill

# Step 1: Create and process data with pandas
df = pd.DataFrame({
    'Month': ['Jan', 'Feb', 'Mar', 'Apr', 'May', 'Jun'],
    'Sales': [45000, 52000, 48000, 61000, 55000, 58000],
    'Costs': [30000, 34000, 32000, 39000, 36000, 38000]
})

df['Profit'] = df['Sales'] - df['Costs']
df['Profit_Margin'] = (df['Profit'] / df['Sales'] * 100).round(1)

# Step 2: Write to Excel
output_file = 'dashboard.xlsx'
with pd.ExcelWriter(output_file, engine='openpyxl') as writer:
    df.to_excel(writer, sheet_name='Data', index=False)

# Step 3: Add formulas and charts
wb = load_workbook(output_file)
ws = wb['Data']

# Add totals row with formulas
last_row = len(df) + 2
ws[f'A{last_row}'] = 'TOTAL'
ws[f'B{last_row}'] = f'=SUM(B2:B{last_row-1})'
ws[f'C{last_row}'] = f'=SUM(C2:C{last_row-1})'
ws[f'D{last_row}'] = f'=SUM(D2:D{last_row-1})'

# Format totals row
for col in ['A', 'B', 'C', 'D']:
    cell = ws[f'{col}{last_row}']
    cell.font = Font(bold=True)
    cell.fill = PatternFill(start_color='D9E1F2', end_color='D9E1F2', fill_type='solid')

# Create line chart for sales trend
chart1 = LineChart()
chart1.title = 'Monthly Sales and Costs'
chart1.x_axis.title = 'Month'
chart1.y_axis.title = 'Amount ($)'

data_ref = Reference(ws, min_col=2, max_col=3, min_row=1, max_row=7)
categories_ref = Reference(ws, min_col=1, min_row=2, max_row=7)

chart1.add_data(data_ref, titles_from_data=True)
chart1.set_categories(categories_ref)

ws.add_chart(chart1, 'F2')

# Create bar chart for profit
chart2 = BarChart()
chart2.type = 'col'
chart2.title = 'Monthly Profit'
chart2.x_axis.title = 'Month'
chart2.y_axis.title = 'Profit ($)'

profit_ref = Reference(ws, min_col=4, min_row=1, max_row=7)
chart2.add_data(profit_ref, titles_from_data=True)
chart2.set_categories(categories_ref)

ws.add_chart(chart2, 'F18')

wb.save(output_file)
```

## Best Practices

### Formulas
1. **Use Excel formulas for** - User-editable reports, simple calculations
2. **Use Python calculations for** - Complex logic, large datasets
3. **Test formulas** - Verify they calculate correctly in Excel
4. **Use absolute references** - When needed ($A$1)
5. **Document complex formulas** - Add comments in nearby cells

### Charts
1. **Choose appropriate chart type** - Match visualization to data
2. **Label clearly** - Title, axis labels, legends
3. **Keep it simple** - Don't overcrowd charts
4. **Use consistent colors** - Match company branding
5. **Position strategically** - Don't overlap data
6. **Test in Excel** - Ensure charts appear correctly

### Performance
1. **Limit formula complexity** - Nested formulas slow Excel
2. **Avoid volatile functions** - TODAY(), NOW(), RAND()
3. **Use named ranges** - Easier to maintain
4. **Calculate once** - Don't duplicate calculations
5. **Consider calculation mode** - Manual vs automatic

## Summary

You've learned how to:
- ✅ Write Excel formulas from Python
- ✅ Use common Excel functions (SUM, IF, VLOOKUP, etc.)
- ✅ Generate formulas dynamically
- ✅ Create various chart types (line, bar, pie, scatter)
- ✅ Style and customize charts
- ✅ Create multi-series charts
- ✅ Combine pandas, formulas, and charts
- ✅ Build complete dashboards

## Next Steps

In Session 7, you'll learn how to merge and combine data from multiple Excel files - essential for consolidating reports from different sources.

