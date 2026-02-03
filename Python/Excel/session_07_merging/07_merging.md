# Session 7: Merging and Combining Excel Files - Comprehensive Guide

## Introduction

One of the most powerful features of Python Excel automation is the ability to merge and consolidate data from multiple Excel files. This session teaches you how to combine files vertically and horizontally, handle different structures, and create comprehensive summary reports.

## Why Merge Excel Files?

1. **Data Consolidation** - Combine regional or departmental reports
2. **Historical Analysis** - Merge monthly/quarterly data
3. **Multi-source Integration** - Combine data from different systems
4. **Reporting** - Create master files from distributed sources
5. **Efficiency** - Automate what takes hours manually

## Types of Merging Operations

### 1. Vertical Concatenation (Stacking)
Combine files with **same structure**, stacking rows on top of each other.

**Use case**: Monthly reports with identical columns

### 2. Horizontal Merging (Joining)
Combine files with **related data**, adding columns side-by-side.

**Use case**: Adding customer details to transaction data

### 3. Multi-sheet Consolidation
Combine multiple sheets from one or more workbooks.

**Use case**: Consolidating department data into one master file

## Vertical Concatenation (Stacking)

### Simple Concatenation

```python
import pandas as pd

# Read multiple files
df1 = pd.read_excel('january.xlsx')
df2 = pd.read_excel('february.xlsx')
df3 = pd.read_excel('march.xlsx')

# Concatenate vertically
df_combined = pd.concat([df1, df2, df3], ignore_index=True)

# Save result
df_combined.to_excel('q1_combined.xlsx', index=False)
```

### Concatenating All Files in Directory

```python
import pandas as pd
from pathlib import Path

# Get all Excel files
files = Path('monthly_reports/').glob('*.xlsx')

# Read and concatenate
dataframes = []
for file in files:
    df = pd.read_excel(file)
    df['Source_File'] = file.name  # Track source
    dataframes.append(df)

# Combine all
df_all = pd.concat(dataframes, ignore_index=True)

# Save
df_all.to_excel('all_months.xlsx', index=False)
```

### Handling Different Column Orders

```python
import pandas as pd

# Files have same columns but different order
df1 = pd.read_excel('file1.xlsx')  # Columns: A, B, C
df2 = pd.read_excel('file2.xlsx')  # Columns: B, C, A

# Concatenate (pandas aligns by column name automatically)
df_combined = pd.concat([df1, df2], ignore_index=True)

# Reorder columns if needed
desired_order = ['A', 'B', 'C']
df_combined = df_combined[desired_order]
```

### Handling Missing Columns

```python
import pandas as pd

# File1 has columns: A, B, C
# File2 has columns: A, B, D

df1 = pd.read_excel('file1.xlsx')
df2 = pd.read_excel('file2.xlsx')

# Concatenate (missing columns filled with NaN)
df_combined = pd.concat([df1, df2], ignore_index=True)

# Fill missing values
df_combined = df_combined.fillna(0)  # or other appropriate value
```

## Horizontal Merging (Joining)

### Inner Join

```python
import pandas as pd

# File1: Customer IDs and Orders
df_orders = pd.DataFrame({
    'Order_ID': [101, 102, 103, 104],
    'Customer_ID': [1, 2, 1, 3],
    'Amount': [100, 150, 200, 120]
})

# File2: Customer Details
df_customers = pd.DataFrame({
    'Customer_ID': [1, 2, 3],
    'Name': ['Alice', 'Bob', 'Charlie'],
    'City': ['NYC', 'LA', 'Chicago']
})

# Inner join (only matching records)
df_merged = pd.merge(df_orders, df_customers, on='Customer_ID', how='inner')
```

### Left Join

```python
# Keep all orders, add customer info where available
df_merged = pd.merge(df_orders, df_customers, on='Customer_ID', how='left')

# Orders without customer info will have NaN in customer columns
```

### Right Join

```python
# Keep all customers, add order info where available
df_merged = pd.merge(df_orders, df_customers, on='Customer_ID', how='right')

# Customers without orders will have NaN in order columns
```

### Outer Join (Full Join)

```python
# Keep all records from both files
df_merged = pd.merge(df_orders, df_customers, on='Customer_ID', how='outer')

# Non-matching records will have NaN in respective columns
```

### Merge on Multiple Keys

```python
# Merge on multiple columns
df_merged = pd.merge(
    df1, df2,
    on=['Customer_ID', 'Year'],
    how='inner'
)
```

### Merge on Different Column Names

```python
# When key columns have different names
df_merged = pd.merge(
    df1, df2,
    left_on='EmployeeID',
    right_on='EmpID',
    how='inner'
)
```

## Combining Multiple Files with Pattern Matching

### Read All Files with Same Pattern

```python
import pandas as pd
from pathlib import Path

def merge_quarterly_files(directory, pattern='Q*_2024.xlsx'):
    """
    Merge all quarterly files matching pattern
    """
    files = Path(directory).glob(pattern)
    
    dataframes = []
    for file in sorted(files):
        print(f"Reading: {file.name}")
        df = pd.read_excel(file)
        df['Quarter'] = file.stem.split('_')[0]  # Extract quarter from filename
        dataframes.append(df)
    
    if not dataframes:
        print("No files found!")
        return None
    
    df_combined = pd.concat(dataframes, ignore_index=True)
    print(f"Combined {len(dataframes)} files with {len(df_combined)} total rows")
    
    return df_combined

# Usage
df_year = merge_quarterly_files('sales_data/', 'Q*_2024.xlsx')
df_year.to_excel('annual_2024.xlsx', index=False)
```

## Merging Sheets from Multiple Workbooks

### Consolidate Specific Sheets

```python
import pandas as pd

def consolidate_sheets(files, sheet_name='Sales'):
    """
    Read same sheet from multiple workbooks and combine
    """
    dataframes = []
    
    for file in files:
        try:
            df = pd.read_excel(file, sheet_name=sheet_name)
            df['Source'] = file
            dataframes.append(df)
            print(f"✓ Read {sheet_name} from {file}")
        except Exception as e:
            print(f"✗ Error reading {file}: {e}")
    
    return pd.concat(dataframes, ignore_index=True) if dataframes else None

# Usage
files = ['north.xlsx', 'south.xlsx', 'east.xlsx', 'west.xlsx']
df_all_regions = consolidate_sheets(files, 'Sales')
df_all_regions.to_excel('national_sales.xlsx', index=False)
```

### Consolidate All Sheets from One Workbook

```python
import pandas as pd

def consolidate_all_sheets(file_path):
    """
    Read all sheets from one workbook and combine
    """
    all_sheets = pd.read_excel(file_path, sheet_name=None)
    
    dataframes = []
    for sheet_name, df in all_sheets.items():
        df['Sheet'] = sheet_name
        dataframes.append(df)
        print(f"✓ Read sheet: {sheet_name}")
    
    return pd.concat(dataframes, ignore_index=True)

# Usage
df_combined = consolidate_all_sheets('monthly_data.xlsx')
df_combined.to_excel('all_months_combined.xlsx', index=False)
```

## Handling Different File Structures

### Standardizing Column Names

```python
import pandas as pd

def standardize_columns(df, column_mapping):
    """
    Rename columns to standard names
    """
    return df.rename(columns=column_mapping)

# Different files have different column names
df1 = pd.read_excel('file1.xlsx')  # Has: 'Cust_ID', 'Amt'
df2 = pd.read_excel('file2.xlsx')  # Has: 'CustomerID', 'Amount'

# Standardize
df1 = standardize_columns(df1, {'Cust_ID': 'Customer_ID', 'Amt': 'Amount'})
df2 = standardize_columns(df2, {'CustomerID': 'Customer_ID'})

# Now can merge
df_combined = pd.concat([df1, df2], ignore_index=True)
```

### Adding Missing Columns

```python
import pandas as pd

def ensure_columns(df, required_columns, default_value=None):
    """
    Add missing columns with default value
    """
    for col in required_columns:
        if col not in df.columns:
            df[col] = default_value
    return df

# Files have different columns
df1 = pd.read_excel('file1.xlsx')  # Has: A, B
df2 = pd.read_excel('file2.xlsx')  # Has: A, B, C

# Ensure both have all columns
required = ['A', 'B', 'C']
df1 = ensure_columns(df1, required, default_value=0)
df2 = ensure_columns(df2, required, default_value=0)

# Now can combine
df_combined = pd.concat([df1, df2], ignore_index=True)
```

## Creating Summary Reports

### Aggregate After Merging

```python
import pandas as pd
from pathlib import Path

# Read and combine all regional files
files = Path('regions/').glob('*.xlsx')
dataframes = [pd.read_excel(f) for f in files]
df_all = pd.concat(dataframes, ignore_index=True)

# Create summary reports
summary_by_region = df_all.groupby('Region').agg({
    'Sales': 'sum',
    'Units': 'sum',
    'Profit': 'sum'
}).round(2)

summary_by_product = df_all.groupby('Product').agg({
    'Sales': 'sum',
    'Units': 'sum'
}).sort_values('Sales', ascending=False)

# Write summaries to separate sheets
with pd.ExcelWriter('consolidated_report.xlsx') as writer:
    df_all.to_excel(writer, sheet_name='All_Data', index=False)
    summary_by_region.to_excel(writer, sheet_name='By_Region')
    summary_by_product.to_excel(writer, sheet_name='By_Product')
```

## Real-World Example: Quarterly Sales Consolidation

```python
import pandas as pd
from pathlib import Path

def consolidate_quarterly_sales():
    """
    Complete workflow for consolidating quarterly sales
    """
    print("Starting quarterly consolidation...")
    
    # 1. Define file locations
    sales_dir = Path('quarterly_sales/')
    quarters = ['Q1_2024.xlsx', 'Q2_2024.xlsx', 'Q3_2024.xlsx', 'Q4_2024.xlsx']
    
    # 2. Read all files
    dataframes = []
    for quarter_file in quarters:
        file_path = sales_dir / quarter_file
        if not file_path.exists():
            print(f"Warning: {quarter_file} not found, skipping")
            continue
        
        df = pd.read_excel(file_path)
        df['Quarter'] = quarter_file.replace('_2024.xlsx', '')
        dataframes.append(df)
        print(f"✓ Read {quarter_file}: {len(df)} rows")
    
    # 3. Combine all quarters
    df_year = pd.concat(dataframes, ignore_index=True)
    print(f"\n✓ Combined data: {len(df_year)} total rows")
    
    # 4. Data cleaning
    df_year = df_year.dropna(subset=['Product', 'Sales'])
    df_year['Sales'] = pd.to_numeric(df_year['Sales'], errors='coerce')
    
    # 5. Create analyses
    quarterly_summary = df_year.groupby('Quarter').agg({
        'Sales': 'sum',
        'Quantity': 'sum'
    }).round(2)
    
    product_summary = df_year.groupby('Product').agg({
        'Sales': ['sum', 'mean', 'count'],
        'Quantity': 'sum'
    }).round(2)
    
    regional_quarterly = pd.pivot_table(
        df_year,
        values='Sales',
        index='Region',
        columns='Quarter',
        aggfunc='sum',
        fill_value=0
    )
    
    # 6. Export everything
    output_file = 'annual_sales_2024.xlsx'
    with pd.ExcelWriter(output_file, engine='openpyxl') as writer:
        df_year.to_excel(writer, sheet_name='All_Data', index=False)
        quarterly_summary.to_excel(writer, sheet_name='Quarterly_Summary')
        product_summary.to_excel(writer, sheet_name='Product_Analysis')
        regional_quarterly.to_excel(writer, sheet_name='Regional_Quarterly')
    
    print(f"\n✓ Consolidation complete: {output_file}")
    return df_year

# Run consolidation
df_annual = consolidate_quarterly_sales()
```

## Error Handling for File Merging

### Robust Merging Function

```python
import pandas as pd
from pathlib import Path

def safe_merge_files(directory, pattern='*.xlsx', output='merged.xlsx'):
    """
    Safely merge multiple files with comprehensive error handling
    """
    try:
        # Find files
        files = list(Path(directory).glob(pattern))
        if not files:
            print(f"No files found matching {pattern} in {directory}")
            return False
        
        print(f"Found {len(files)} files to merge")
        
        # Read files
        dataframes = []
        failed_files = []
        
        for file in files:
            try:
                df = pd.read_excel(file)
                if df.empty:
                    print(f"Warning: {file.name} is empty, skipping")
                    continue
                
                df['Source_File'] = file.name
                df['Merge_Date'] = pd.Timestamp.now()
                dataframes.append(df)
                print(f"✓ {file.name}: {len(df)} rows")
                
            except Exception as e:
                print(f"✗ Error reading {file.name}: {e}")
                failed_files.append((file.name, str(e)))
        
        if not dataframes:
            print("No valid files to merge")
            return False
        
        # Merge
        df_merged = pd.concat(dataframes, ignore_index=True)
        print(f"\n✓ Merged {len(dataframes)} files: {len(df_merged)} total rows")
        
        # Save
        df_merged.to_excel(output, index=False)
        print(f"✓ Saved to: {output}")
        
        # Report any failures
        if failed_files:
            print(f"\n⚠ Failed files ({len(failed_files)}):")
            for filename, error in failed_files:
                print(f"  - {filename}: {error}")
        
        return True
        
    except Exception as e:
        print(f"✗ Fatal error: {e}")
        return False

# Usage
safe_merge_files('monthly_data/', pattern='*.xlsx', output='all_months.xlsx')
```

## Best Practices

1. **Verify Structure** - Check columns match before merging
2. **Track Sources** - Add source filename column
3. **Handle Errors** - Use try-except for each file
4. **Validate Data** - Check for duplicates, missing values
5. **Document Process** - Log what files were merged
6. **Test Small First** - Test logic on few files before all
7. **Backup Originals** - Never overwrite source files
8. **Use Consistent Names** - Standardize column names
9. **Add Timestamps** - Track when merge occurred
10. **Create Summary** - Always include summary sheet

## Summary

You've learned how to:
- ✅ Concatenate files vertically (stacking)
- ✅ Merge files horizontally (joining)
- ✅ Handle different file structures
- ✅ Combine multiple sheets
- ✅ Process files in batch
- ✅ Create summary reports
- ✅ Handle errors gracefully
- ✅ Build robust merging workflows

## Next Steps

In Session 8, you'll learn advanced operations like working with named ranges, data validation, and worksheet protection.

