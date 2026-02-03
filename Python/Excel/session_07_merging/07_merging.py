"""
Session 7: Merging and Combining Excel Files - Comprehensive Examples
======================================================================

This script demonstrates comprehensive techniques for merging and consolidating
Excel files from multiple sources.
"""

import pandas as pd
import numpy as np
from pathlib import Path
from datetime import datetime, timedelta

print("=" * 80)
print("Session 7: Merging and Combining Excel Files")
print("=" * 80)
print()

# Create output directory
output_dir = Path(__file__).parent / 'sample_files'
output_dir.mkdir(exist_ok=True)

# ==============================================================================
# 1. CREATE SAMPLE FILES FOR MERGING
# ==============================================================================

print("1. CREATING SAMPLE FILES FOR MERGING")
print("-" * 80)

# Create quarterly sales files
np.random.seed(42)

for quarter, months in [('Q1', ['Jan', 'Feb', 'Mar']), 
                        ('Q2', ['Apr', 'May', 'Jun']),
                        ('Q3', ['Jul', 'Aug', 'Sep']),
                        ('Q4', ['Oct', 'Nov', 'Dec'])]:
    
    data = {
        'Product': np.random.choice(['Laptop', 'Mouse', 'Keyboard', 'Monitor'], 30),
        'Region': np.random.choice(['North', 'South', 'East', 'West'], 30),
        'Sales': np.random.randint(1000, 10000, 30),
        'Quantity': np.random.randint(10, 100, 30)
    }
    df = pd.DataFrame(data)
    filename = output_dir / f'{quarter}_2024.xlsx'
    df.to_excel(filename, index=False)
    print(f"✓ Created: {filename.name}")

print()

# Create regional files
for region in ['North', 'South', 'East', 'West']:
    data = {
        'Date': pd.date_range('2024-01-01', periods=20, freq='D'),
        'Product': np.random.choice(['Product A', 'Product B', 'Product C'], 20),
        'Sales': np.random.randint(5000, 15000, 20),
        'Region': region
    }
    df = pd.DataFrame(data)
    filename = output_dir / f'{region}_region.xlsx'
    df.to_excel(filename, index=False)
    print(f"✓ Created: {filename.name}")

print()

# ==============================================================================
# 2. SIMPLE VERTICAL CONCATENATION
# ==============================================================================

print("2. SIMPLE VERTICAL CONCATENATION (STACKING)")
print("-" * 80)

# Read quarterly files
df_q1 = pd.read_excel(output_dir / 'Q1_2024.xlsx')
df_q2 = pd.read_excel(output_dir / 'Q2_2024.xlsx')
df_q3 = pd.read_excel(output_dir / 'Q3_2024.xlsx')
df_q4 = pd.read_excel(output_dir / 'Q4_2024.xlsx')

print(f"Q1: {len(df_q1)} rows")
print(f"Q2: {len(df_q2)} rows")
print(f"Q3: {len(df_q3)} rows")
print(f"Q4: {len(df_q4)} rows")
print()

# Concatenate
df_annual = pd.concat([df_q1, df_q2, df_q3, df_q4], ignore_index=True)
print(f"Combined annual data: {len(df_annual)} rows")
print(df_annual.head())
print()

annual_file = output_dir / 'annual_2024.xlsx'
df_annual.to_excel(annual_file, index=False)
print(f"✓ Saved: {annual_file.name}")
print()

# ==============================================================================
# 3. CONCATENATION WITH SOURCE TRACKING
# ==============================================================================

print("3. CONCATENATION WITH SOURCE TRACKING")
print("-" * 80)

# Add source information
df_q1['Quarter'] = 'Q1'
df_q2['Quarter'] = 'Q2'
df_q3['Quarter'] = 'Q3'
df_q4['Quarter'] = 'Q4'

df_annual_tracked = pd.concat([df_q1, df_q2, df_q3, df_q4], ignore_index=True)
print("Combined with quarter tracking:")
print(df_annual_tracked.head())
print()
print("Records per quarter:")
print(df_annual_tracked['Quarter'].value_counts())
print()

# ==============================================================================
# 4. BATCH CONCATENATION FROM DIRECTORY
# ==============================================================================

print("4. BATCH CONCATENATION FROM DIRECTORY")
print("-" * 80)

# Find all quarterly files
quarterly_files = sorted(output_dir.glob('Q*_2024.xlsx'))
print(f"Found {len(quarterly_files)} quarterly files:")

dataframes = []
for file in quarterly_files:
    df = pd.read_excel(file)
    df['Source_File'] = file.name
    df['Quarter'] = file.stem.split('_')[0]
    dataframes.append(df)
    print(f"  ✓ {file.name}: {len(df)} rows")

df_all_quarters = pd.concat(dataframes, ignore_index=True)
print(f"\nTotal combined: {len(df_all_quarters)} rows")
print()

# ==============================================================================
# 5. HORIZONTAL MERGING (JOINING)
# ==============================================================================

print("5. HORIZONTAL MERGING (JOINING)")
print("-" * 80)

# Create two related datasets
df_orders = pd.DataFrame({
    'Order_ID': [101, 102, 103, 104, 105],
    'Customer_ID': [1, 2, 1, 3, 4],
    'Product': ['Laptop', 'Mouse', 'Keyboard', 'Monitor', 'Webcam'],
    'Amount': [1000, 30, 80, 300, 90]
})

df_customers = pd.DataFrame({
    'Customer_ID': [1, 2, 3, 4, 5],
    'Customer_Name': ['Alice', 'Bob', 'Charlie', 'Diana', 'Eve'],
    'City': ['NYC', 'LA', 'Chicago', 'Houston', 'Phoenix']
})

print("Orders:")
print(df_orders)
print("\nCustomers:")
print(df_customers)
print()

# Inner join
df_inner = pd.merge(df_orders, df_customers, on='Customer_ID', how='inner')
print("Inner Join (only matching records):")
print(df_inner)
print()

# Left join
df_left = pd.merge(df_orders, df_customers, on='Customer_ID', how='left')
print("Left Join (all orders, add customer info where available):")
print(df_left)
print()

# Right join
df_right = pd.merge(df_orders, df_customers, on='Customer_ID', how='right')
print("Right Join (all customers, add order info where available):")
print(df_right)
print()

# Outer join
df_outer = pd.merge(df_orders, df_customers, on='Customer_ID', how='outer')
print("Outer Join (all records from both):")
print(df_outer)
print()

# ==============================================================================
# 6. MERGING WITH DIFFERENT COLUMN NAMES
# ==============================================================================

print("6. MERGING WITH DIFFERENT COLUMN NAMES")
print("-" * 80)

# Datasets with different key column names
df_employees = pd.DataFrame({
    'EmpID': [101, 102, 103],
    'Name': ['Alice', 'Bob', 'Charlie'],
    'Department': ['Sales', 'IT', 'HR']
})

df_salaries = pd.DataFrame({
    'EmployeeID': [101, 102, 103],
    'Salary': [60000, 75000, 58000],
    'Bonus': [6000, 7500, 5800]
})

print("Employees:")
print(df_employees)
print("\nSalaries:")
print(df_salaries)
print()

# Merge on different column names
df_emp_salary = pd.merge(
    df_employees, df_salaries,
    left_on='EmpID',
    right_on='EmployeeID',
    how='inner'
)
print("Merged (on different column names):")
print(df_emp_salary)
print()

# ==============================================================================
# 7. MERGING MULTIPLE FILES
# ==============================================================================

print("7. MERGING ALL REGIONAL FILES")
print("-" * 80)

# Find all regional files
regional_files = sorted(output_dir.glob('*_region.xlsx'))
print(f"Found {len(regional_files)} regional files:")

regional_dataframes = []
for file in regional_files:
    df = pd.read_excel(file)
    print(f"  ✓ {file.name}: {len(df)} rows")
    regional_dataframes.append(df)

df_national = pd.concat(regional_dataframes, ignore_index=True)
print(f"\nNational dataset: {len(df_national)} rows")
print(df_national.head(10))
print()

national_file = output_dir / 'national_sales.xlsx'
df_national.to_excel(national_file, index=False)
print(f"✓ Saved: {national_file.name}")
print()

# ==============================================================================
# 8. CONSOLIDATING WITH AGGREGATION
# ==============================================================================

print("8. CONSOLIDATING WITH AGGREGATION")
print("-" * 80)

# Aggregate quarterly data
quarterly_summary = df_all_quarters.groupby('Quarter').agg({
    'Sales': 'sum',
    'Quantity': 'sum'
}).round(2)

print("Quarterly Summary:")
print(quarterly_summary)
print()

# Product performance across all quarters
product_summary = df_all_quarters.groupby('Product').agg({
    'Sales': ['sum', 'mean', 'count'],
    'Quantity': 'sum'
}).round(2)

print("Product Performance:")
print(product_summary)
print()

# Regional performance
regional_summary = df_all_quarters.groupby('Region').agg({
    'Sales': 'sum',
    'Quantity': 'sum'
}).sort_values('Sales', ascending=False)

print("Regional Performance:")
print(regional_summary)
print()

# ==============================================================================
# 9. PIVOT TABLE FROM MERGED DATA
# ==============================================================================

print("9. PIVOT TABLE FROM MERGED DATA")
print("-" * 80)

# Create pivot table
pivot_sales = pd.pivot_table(
    df_all_quarters,
    values='Sales',
    index='Product',
    columns='Quarter',
    aggfunc='sum',
    fill_value=0
)

print("Sales by Product and Quarter:")
print(pivot_sales)
print()

# Regional quarterly pivot
pivot_regional = pd.pivot_table(
    df_all_quarters,
    values='Sales',
    index='Region',
    columns='Quarter',
    aggfunc='sum',
    fill_value=0
)

print("Sales by Region and Quarter:")
print(pivot_regional)
print()

# ==============================================================================
# 10. COMPREHENSIVE CONSOLIDATION REPORT
# ==============================================================================

print("10. COMPREHENSIVE CONSOLIDATION REPORT")
print("-" * 80)

# Create comprehensive report with multiple sheets
report_file = output_dir / 'consolidation_report.xlsx'

with pd.ExcelWriter(report_file, engine='openpyxl') as writer:
    # Raw data
    df_all_quarters.to_excel(writer, sheet_name='All_Data', index=False)
    
    # Summaries
    quarterly_summary.to_excel(writer, sheet_name='Quarterly_Summary')
    product_summary.to_excel(writer, sheet_name='Product_Analysis')
    regional_summary.to_excel(writer, sheet_name='Regional_Performance')
    
    # Pivots
    pivot_sales.to_excel(writer, sheet_name='Product_Quarterly')
    pivot_regional.to_excel(writer, sheet_name='Regional_Quarterly')
    
    # National data
    df_national.to_excel(writer, sheet_name='National_Data', index=False)

print(f"✓ Created comprehensive report: {report_file.name}")
print()

# ==============================================================================
# 11. HANDLING DIFFERENT STRUCTURES
# ==============================================================================

print("11. HANDLING DIFFERENT STRUCTURES")
print("-" * 80)

# Create files with different structures
df_file1 = pd.DataFrame({
    'ID': [1, 2, 3],
    'Name': ['Alice', 'Bob', 'Charlie'],
    'Value': [100, 200, 300]
})

df_file2 = pd.DataFrame({
    'ID': [4, 5, 6],
    'Name': ['Diana', 'Eve', 'Frank'],
    'Value': [400, 500, 600],
    'Extra': ['X', 'Y', 'Z']  # Extra column
})

print("File 1 columns:", df_file1.columns.tolist())
print("File 2 columns:", df_file2.columns.tolist())
print()

# Concatenate (missing columns filled with NaN)
df_combined = pd.concat([df_file1, df_file2], ignore_index=True)
print("Combined (Extra column has NaN for File 1):")
print(df_combined)
print()

# Fill missing values
df_combined['Extra'] = df_combined['Extra'].fillna('N/A')
print("After filling missing values:")
print(df_combined)
print()

# ==============================================================================
# 12. ERROR-SAFE MERGING FUNCTION
# ==============================================================================

print("12. ERROR-SAFE MERGING FUNCTION")
print("-" * 80)

def safe_merge_files(directory, pattern='*.xlsx', output='merged.xlsx'):
    """
    Safely merge multiple files with error handling
    """
    try:
        files = list(Path(directory).glob(pattern))
        if not files:
            print(f"No files found matching {pattern}")
            return False
        
        print(f"Found {len(files)} files to merge:")
        
        dataframes = []
        failed_files = []
        
        for file in files:
            try:
                df = pd.read_excel(file)
                if df.empty:
                    print(f"  ⚠ {file.name}: empty, skipping")
                    continue
                
                df['Source_File'] = file.name
                df['Merge_Date'] = datetime.now()
                dataframes.append(df)
                print(f"  ✓ {file.name}: {len(df)} rows")
                
            except Exception as e:
                print(f"  ✗ {file.name}: {e}")
                failed_files.append((file.name, str(e)))
        
        if not dataframes:
            print("No valid files to merge")
            return False
        
        # Merge
        df_merged = pd.concat(dataframes, ignore_index=True)
        print(f"\n✓ Merged {len(dataframes)} files: {len(df_merged)} total rows")
        
        # Save
        output_path = Path(directory) / output
        df_merged.to_excel(output_path, index=False)
        print(f"✓ Saved to: {output}")
        
        if failed_files:
            print(f"\n⚠ Failed files ({len(failed_files)}):")
            for filename, error in failed_files:
                print(f"  - {filename}: {error}")
        
        return True
        
    except Exception as e:
        print(f"✗ Fatal error: {e}")
        return False

# Test the function
print("\nTesting safe merge function:")
success = safe_merge_files(output_dir, pattern='Q*_2024.xlsx', output='safe_merged.xlsx')
print()

# ==============================================================================
# 13. REAL-WORLD EXAMPLE: MULTI-DEPARTMENT CONSOLIDATION
# ==============================================================================

print("13. REAL-WORLD EXAMPLE: MULTI-DEPARTMENT CONSOLIDATION")
print("-" * 80)

# Simulate department reports
departments = ['Sales', 'Marketing', 'IT', 'HR']
dept_files = {}

for dept in departments:
    data = {
        'Employee': [f'{dept}_Emp_{i}' for i in range(1, 6)],
        'Department': dept,
        'Budget': np.random.randint(50000, 150000, 5),
        'Actual': np.random.randint(40000, 140000, 5)
    }
    df_dept = pd.DataFrame(data)
    dept_file = output_dir / f'{dept}_budget.xlsx'
    df_dept.to_excel(dept_file, index=False)
    dept_files[dept] = dept_file
    print(f"✓ Created {dept} budget file")

# Consolidate all department budgets
dept_dataframes = []
for dept, file in dept_files.items():
    df = pd.read_excel(file)
    dept_dataframes.append(df)

df_company_budget = pd.concat(dept_dataframes, ignore_index=True)
df_company_budget['Variance'] = df_company_budget['Budget'] - df_company_budget['Actual']
df_company_budget['Variance_%'] = (df_company_budget['Variance'] / df_company_budget['Budget'] * 100).round(1)

print(f"\nConsolidated company budget: {len(df_company_budget)} employees")
print(df_company_budget.head(10))
print()

# Department summary
dept_summary = df_company_budget.groupby('Department').agg({
    'Budget': 'sum',
    'Actual': 'sum',
    'Variance': 'sum'
}).round(2)

print("Department Budget Summary:")
print(dept_summary)
print()

# Save consolidated budget
budget_report = output_dir / 'company_budget_consolidated.xlsx'
with pd.ExcelWriter(budget_report, engine='openpyxl') as writer:
    df_company_budget.to_excel(writer, sheet_name='All_Employees', index=False)
    dept_summary.to_excel(writer, sheet_name='Department_Summary')

print(f"✓ Saved: {budget_report.name}")
print()

# ==============================================================================
# SUMMARY
# ==============================================================================

print("=" * 80)
print("SESSION 7 COMPLETE!")
print("=" * 80)
print()
print("What you learned:")
print("✓ Vertical concatenation (stacking files)")
print("✓ Horizontal merging (joining related data)")
print("✓ Track source files during merging")
print("✓ Batch process entire directories")
print("✓ Handle different file structures")
print("✓ Create aggregated summaries")
print("✓ Build pivot tables from merged data")
print("✓ Generate comprehensive reports")
print("✓ Implement error-safe merging")
print("✓ Consolidate multi-department data")
print()
print("Files created:")
for file in sorted(output_dir.glob('*.xlsx')):
    print(f"  - {file.name}")
print()
print("Next: Session 8 - Advanced Data Operations")
print("=" * 80)

