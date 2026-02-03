# Session 11: Advanced Excel Features - Comprehensive Guide

## Introduction

This final advanced session covers specialized Excel features: working with macros, inserting images, managing hyperlinks, adding comments, working with metadata, and integrating with other file formats like CSV, JSON, and SQL databases.

## Part 1: Working with Macros

### Reading Macro-Enabled Files

```python
from openpyxl import load_workbook

# Read .xlsm file (macro-enabled)
wb = load_workbook('file_with_macros.xlsm', keep_vba=True)
ws = wb.active

# Read data normally
data = []
for row in ws.iter_rows(values_only=True):
    data.append(row)

# Save (preserves macros)
wb.save('file_with_macros.xlsm')
```

### Important Notes About Macros

**What openpyxl can do:**
- Read macro-enabled files (.xlsm)
- Preserve existing macros when saving
- Read data from sheets with macros

**What openpyxl CANNOT do:**
- Create new macros
- Execute macros
- Modify existing macros

**For macro execution, use:**
- `pywin32` (Windows only)
- `xlwings` (Windows/Mac)

### Running Macros with xlwings

```python
import xlwings as xw

# Open workbook
wb = xw.Book('file_with_macros.xlsm')

# Run macro
macro = wb.macro('MacroName')
macro()

# Read results
sheet = wb.sheets['Sheet1']
value = sheet.range('A1').value

# Close
wb.close()
```

## Part 2: Working with Images

### Inserting Images with openpyxl

```python
from openpyxl import Workbook
from openpyxl.drawing.image import Image

wb = Workbook()
ws = wb.active

# Add data
ws['A1'] = 'Company Logo'

# Insert image
img = Image('logo.png')

# Resize image (optional)
img.width = 200
img.height = 100

# Position image
ws.add_image(img, 'B2')  # Insert at cell B2

wb.save('with_image.xlsx')
```

### Insert Multiple Images

```python
from openpyxl import Workbook
from openpyxl.drawing.image import Image
from pathlib import Path

wb = Workbook()
ws = wb.active

# Headers
ws['A1'] = 'Product'
ws['B1'] = 'Image'
ws['C1'] = 'Price'

# Add products with images
products = [
    ('Laptop', 'laptop.png', 1000),
    ('Mouse', 'mouse.png', 25),
    ('Keyboard', 'keyboard.png', 75)
]

row = 2
for product, image_file, price in products:
    ws[f'A{row}'] = product
    ws[f'C{row}'] = price
    
    # Insert image
    if Path(image_file).exists():
        img = Image(image_file)
        img.width = 100
        img.height = 100
        ws.add_image(img, f'B{row}')
    
    row += 1
    ws.row_dimensions[row].height = 75  # Make row tall enough

wb.save('product_catalog.xlsx')
```

### Reading Images from Excel

```python
from openpyxl import load_workbook

wb = load_workbook('with_image.xlsx')
ws = wb.active

# Access images
for image in ws._images:
    print(f"Image at: {image.anchor}")
    # image.ref contains the cell reference
    # image._data() contains the binary data
```

### Using xlsxwriter for Images

```python
import xlsxwriter

workbook = xlsxwriter.Workbook('images_xlsxwriter.xlsx')
worksheet = workbook.add_worksheet()

# Insert image
worksheet.insert_image('B2', 'logo.png')

# Insert image with options
worksheet.insert_image('B10', 'chart.png', {
    'x_scale': 0.5,      # Scale width
    'y_scale': 0.5,      # Scale height
    'x_offset': 10,      # Horizontal offset in pixels
    'y_offset': 10       # Vertical offset in pixels
})

workbook.close()
```

## Part 3: Working with Hyperlinks

### Adding Hyperlinks

```python
from openpyxl import Workbook

wb = Workbook()
ws = wb.active

# Hyperlink to website
ws['A1'] = 'Visit Google'
ws['A1'].hyperlink = 'https://www.google.com'

# Hyperlink to another sheet
ws2 = wb.create_sheet('Sheet2')
ws['A2'] = 'Go to Sheet2'
ws['A2'].hyperlink = '#Sheet2!A1'

# Hyperlink to email
ws['A3'] = 'Send Email'
ws['A3'].hyperlink = 'mailto:contact@example.com'

# Hyperlink to file
ws['A4'] = 'Open Document'
ws['A4'].hyperlink = 'file:///C:/Documents/report.pdf'

wb.save('with_hyperlinks.xlsx')
```

### Styling Hyperlinks

```python
from openpyxl import Workbook
from openpyxl.styles import Font, colors

wb = Workbook()
ws = wb.active

# Add hyperlink with custom style
ws['A1'] = 'Click Here'
ws['A1'].hyperlink = 'https://www.example.com'
ws['A1'].font = Font(
    color=colors.BLUE,
    underline='single',
    bold=True
)

wb.save('styled_hyperlinks.xlsx')
```

### Reading Hyperlinks

```python
from openpyxl import load_workbook

wb = load_workbook('with_hyperlinks.xlsx')
ws = wb.active

# Read all hyperlinks
for row in ws.iter_rows():
    for cell in row:
        if cell.hyperlink:
            print(f"Cell {cell.coordinate}: {cell.value}")
            print(f"  Link: {cell.hyperlink.target}")
```

## Part 4: Cell Comments and Notes

### Adding Comments

```python
from openpyxl import Workbook
from openpyxl.comments import Comment

wb = Workbook()
ws = wb.active

# Add cell with comment
ws['A1'] = 'Important Data'
comment = Comment(
    'This value was verified on 2024-03-15.\nDo not change without approval.',
    'John Doe'
)
ws['A1'].comment = comment

# Add more data with comments
ws['B1'] = 1000
ws['B1'].comment = Comment('Target value for Q1', 'Manager')

wb.save('with_comments.xlsx')
```

### Reading Comments

```python
from openpyxl import load_workbook

wb = load_workbook('with_comments.xlsx')
ws = wb.active

# Extract all comments
comments_data = []
for row in ws.iter_rows():
    for cell in row:
        if cell.comment:
            comments_data.append({
                'Cell': cell.coordinate,
                'Value': cell.value,
                'Comment': cell.comment.text,
                'Author': cell.comment.author
            })

# Display
import pandas as pd
df_comments = pd.DataFrame(comments_data)
print(df_comments)
```

### Removing Comments

```python
from openpyxl import load_workbook

wb = load_workbook('with_comments.xlsx')
ws = wb.active

# Remove specific comment
ws['A1'].comment = None

# Remove all comments
for row in ws.iter_rows():
    for cell in row:
        if cell.comment:
            cell.comment = None

wb.save('without_comments.xlsx')
```

## Part 5: Workbook Properties and Metadata

### Setting Document Properties

```python
from openpyxl import Workbook
from datetime import datetime

wb = Workbook()

# Set properties
wb.properties.title = 'Monthly Sales Report'
wb.properties.subject = 'Sales Data'
wb.properties.creator = 'John Doe'
wb.properties.keywords = 'sales, monthly, report'
wb.properties.description = 'Comprehensive sales analysis for March 2024'
wb.properties.lastModifiedBy = 'Automation System'
wb.properties.created = datetime(2024, 3, 1)
wb.properties.modified = datetime.now()
wb.properties.category = 'Financial Reports'
wb.properties.company = 'Acme Corporation'

# Custom properties
wb.custom_doc_props.append(('Department', 'Sales'))
wb.custom_doc_props.append(('Region', 'North America'))

ws = wb.active
ws['A1'] = 'Data'

wb.save('with_properties.xlsx')
```

### Reading Document Properties

```python
from openpyxl import load_workbook

wb = load_workbook('with_properties.xlsx')

# Read standard properties
print(f"Title: {wb.properties.title}")
print(f"Subject: {wb.properties.subject}")
print(f"Creator: {wb.properties.creator}")
print(f"Created: {wb.properties.created}")
print(f"Modified: {wb.properties.modified}")
print(f"Company: {wb.properties.company}")

# Read custom properties
print("\nCustom Properties:")
for prop in wb.custom_doc_props:
    print(f"  {prop.name}: {prop.value}")
```

## Part 6: Integration with CSV

### Excel to CSV

```python
import pandas as pd

# Read Excel
df = pd.read_excel('data.xlsx', sheet_name='Sales')

# Save as CSV
df.to_csv('data.csv', index=False)

# Multiple sheets to multiple CSVs
xlsx_file = pd.ExcelFile('data.xlsx')
for sheet_name in xlsx_file.sheet_names:
    df = pd.read_excel(xlsx_file, sheet_name=sheet_name)
    df.to_csv(f'{sheet_name}.csv', index=False)
```

### CSV to Excel

```python
import pandas as pd

# Read CSV
df = pd.read_csv('data.csv')

# Save as Excel
df.to_excel('data.xlsx', index=False, sheet_name='Data')

# Multiple CSVs to one Excel file
from pathlib import Path

csv_files = Path('.').glob('*.csv')

with pd.ExcelWriter('combined.xlsx') as writer:
    for csv_file in csv_files:
        df = pd.read_csv(csv_file)
        sheet_name = csv_file.stem[:31]  # Excel sheet name limit
        df.to_excel(writer, sheet_name=sheet_name, index=False)
```

## Part 7: Integration with JSON

### Excel to JSON

```python
import pandas as pd

# Read Excel
df = pd.read_excel('data.xlsx')

# Convert to JSON (various formats)

# 1. Records format (list of dictionaries)
json_records = df.to_json(orient='records', indent=2)
with open('data_records.json', 'w') as f:
    f.write(json_records)

# 2. Index format
json_index = df.to_json(orient='index', indent=2)
with open('data_index.json', 'w') as f:
    f.write(json_index)

# 3. Columns format
json_columns = df.to_json(orient='columns', indent=2)
with open('data_columns.json', 'w') as f:
    f.write(json_columns)
```

### JSON to Excel

```python
import pandas as pd
import json

# Read JSON
with open('data.json', 'r') as f:
    data = json.load(f)

# Convert to DataFrame
df = pd.DataFrame(data)

# Save as Excel
df.to_excel('from_json.xlsx', index=False)

# Complex nested JSON
with open('nested_data.json', 'r') as f:
    nested_data = json.load(f)

# Normalize nested JSON
from pandas import json_normalize
df_normalized = json_normalize(nested_data)
df_normalized.to_excel('normalized.xlsx', index=False)
```

## Part 8: Integration with SQL Databases

### SQL to Excel

```python
import pandas as pd
import sqlite3

# Connect to database
conn = sqlite3.connect('database.db')

# Query data
query = "SELECT * FROM sales WHERE date >= '2024-01-01'"
df = pd.read_sql_query(query, conn)

# Save to Excel
df.to_excel('sales_data.xlsx', index=False)

# Multiple queries to multiple sheets
queries = {
    'Sales': "SELECT * FROM sales",
    'Products': "SELECT * FROM products",
    'Customers': "SELECT * FROM customers"
}

with pd.ExcelWriter('database_export.xlsx') as writer:
    for sheet_name, query in queries.items():
        df = pd.read_sql_query(query, conn)
        df.to_excel(writer, sheet_name=sheet_name, index=False)

conn.close()
```

### Excel to SQL

```python
import pandas as pd
import sqlite3

# Read Excel
df = pd.read_excel('data.xlsx')

# Connect to database
conn = sqlite3.connect('database.db')

# Write to SQL table
df.to_sql('sales_data', conn, if_exists='replace', index=False)

# Append instead of replace
df_new = pd.read_excel('new_data.xlsx')
df_new.to_sql('sales_data', conn, if_exists='append', index=False)

conn.close()
```

### Working with PostgreSQL

```python
import pandas as pd
from sqlalchemy import create_engine

# Create connection
engine = create_engine('postgresql://user:password@localhost:5432/mydb')

# Read from PostgreSQL
query = "SELECT * FROM sales"
df = pd.read_sql(query, engine)

# Save to Excel
df.to_excel('postgres_data.xlsx', index=False)

# Write Excel to PostgreSQL
df_excel = pd.read_excel('data.xlsx')
df_excel.to_sql('imported_data', engine, if_exists='replace', index=False)
```

## Part 9: Working with Multiple File Formats

### Universal File Converter

```python
import pandas as pd
from pathlib import Path

def convert_file(input_file, output_format):
    """
    Convert between different formats
    
    Supported: xlsx, csv, json, parquet, html, xml
    """
    # Determine input format
    input_path = Path(input_file)
    input_format = input_path.suffix.lower().strip('.')
    
    # Read file
    if input_format == 'xlsx':
        df = pd.read_excel(input_file)
    elif input_format == 'csv':
        df = pd.read_csv(input_file)
    elif input_format == 'json':
        df = pd.read_json(input_file)
    elif input_format == 'parquet':
        df = pd.read_parquet(input_file)
    elif input_format == 'html':
        df = pd.read_html(input_file)[0]
    elif input_format == 'xml':
        df = pd.read_xml(input_file)
    else:
        raise ValueError(f"Unsupported input format: {input_format}")
    
    # Generate output filename
    output_file = input_path.stem + f'.{output_format}'
    
    # Write file
    if output_format == 'xlsx':
        df.to_excel(output_file, index=False)
    elif output_format == 'csv':
        df.to_csv(output_file, index=False)
    elif output_format == 'json':
        df.to_json(output_file, orient='records', indent=2)
    elif output_format == 'parquet':
        df.to_parquet(output_file)
    elif output_format == 'html':
        df.to_html(output_file, index=False)
    elif output_format == 'xml':
        df.to_xml(output_file, index=False)
    else:
        raise ValueError(f"Unsupported output format: {output_format}")
    
    print(f"✓ Converted {input_file} to {output_file}")
    return output_file

# Usage
convert_file('data.xlsx', 'csv')
convert_file('data.csv', 'json')
convert_file('data.json', 'xlsx')
```

### Batch Format Converter

```python
from pathlib import Path
import pandas as pd

def batch_convert(directory, from_format, to_format):
    """
    Convert all files of one format to another
    """
    files = Path(directory).glob(f'*.{from_format}')
    
    for file in files:
        try:
            # Read
            if from_format == 'xlsx':
                df = pd.read_excel(file)
            elif from_format == 'csv':
                df = pd.read_csv(file)
            elif from_format == 'json':
                df = pd.read_json(file)
            
            # Write
            output_file = file.stem + f'.{to_format}'
            
            if to_format == 'xlsx':
                df.to_excel(output_file, index=False)
            elif to_format == 'csv':
                df.to_csv(output_file, index=False)
            elif to_format == 'json':
                df.to_json(output_file, orient='records', indent=2)
            
            print(f"✓ {file.name} → {output_file}")
            
        except Exception as e:
            print(f"✗ Error with {file.name}: {e}")

# Usage
batch_convert('data/', 'xlsx', 'csv')
```

## Part 10: Advanced Techniques

### Extract All Data from Complex Workbook

```python
from openpyxl import load_workbook
import pandas as pd

def extract_all_workbook_data(filename):
    """
    Extract everything from workbook: data, properties, comments, images
    """
    wb = load_workbook(filename)
    
    extraction = {
        'properties': {},
        'sheets': {},
        'comments': [],
        'images': []
    }
    
    # Extract properties
    extraction['properties'] = {
        'title': wb.properties.title,
        'creator': wb.properties.creator,
        'created': str(wb.properties.created),
        'modified': str(wb.properties.modified)
    }
    
    # Extract all sheets
    for sheet_name in wb.sheetnames:
        ws = wb[sheet_name]
        
        # Extract data
        data = []
        for row in ws.iter_rows(values_only=True):
            data.append(row)
        
        extraction['sheets'][sheet_name] = {
            'data': data,
            'dimensions': ws.dimensions
        }
        
        # Extract comments
        for row in ws.iter_rows():
            for cell in row:
                if cell.comment:
                    extraction['comments'].append({
                        'sheet': sheet_name,
                        'cell': cell.coordinate,
                        'value': cell.value,
                        'comment': cell.comment.text,
                        'author': cell.comment.author
                    })
        
        # Extract images
        for image in ws._images:
            extraction['images'].append({
                'sheet': sheet_name,
                'position': str(image.anchor)
            })
    
    return extraction

# Usage
data = extract_all_workbook_data('complex_file.xlsx')
print(f"Found {len(data['sheets'])} sheets")
print(f"Found {len(data['comments'])} comments")
print(f"Found {len(data['images'])} images")
```

## Best Practices

1. **Macros** - Use xlwings for execution, openpyxl for preservation
2. **Images** - Optimize size before inserting
3. **Hyperlinks** - Validate URLs before adding
4. **Comments** - Use for important information only
5. **Metadata** - Always set document properties
6. **CSV** - Use for large datasets (faster than Excel)
7. **JSON** - Use for nested/hierarchical data
8. **SQL** - Use for relational data
9. **Format Conversion** - Test with sample data first
10. **Compatibility** - Consider target audience's Excel version

## Summary

You've learned how to:
- ✅ Work with macro-enabled files
- ✅ Insert and manage images
- ✅ Add hyperlinks and style them
- ✅ Work with cell comments
- ✅ Set document properties and metadata
- ✅ Convert between Excel and CSV
- ✅ Convert between Excel and JSON
- ✅ Integrate with SQL databases
- ✅ Build universal file converters
- ✅ Extract complex workbook data

## Next Steps

In Session 12 (Final Session), you'll apply everything you've learned to build complete real-world projects, including financial report generators, data analysis dashboards, and ETL pipelines.

