"""
Session 4: Data Manipulation with Pandas - Comprehensive Examples
=================================================================

This script demonstrates comprehensive data manipulation techniques
for cleaning, transforming, and analyzing Excel data.
"""

import pandas as pd
import numpy as np
from pathlib import Path
import sys

print("=" * 80)
print("Session 4: Data Manipulation with Pandas")
print("=" * 80)
print()

# Create output directory
output_dir = Path(__file__).parent / 'sample_files'
output_dir.mkdir(exist_ok=True)

# ==============================================================================
# 1. CREATE SAMPLE MESSY DATA
# ==============================================================================

print("1. CREATING SAMPLE MESSY DATA")
print("-" * 80)

# Create realistic messy dataset
np.random.seed(42)

messy_data = {
    'Employee_ID': [101, 102, 103, 104, 105, 106, 107, 108, 109, 110, 101],  # Duplicate
    'Name': ['Alice Smith', 'bob jones', '  Charlie  ', 'Diana Lee', None, 
             'Eve Wilson', 'Frank Brown', 'Grace Kim', 'Henry Davis', 'Ivy Chen', 'Alice Smith'],
    'Age': [25, 30, None, 28, 32, 27, 35, np.nan, 29, 31, 25],
    'Department': ['Sales', 'IT', 'HR', 'Sales', 'IT', 'HR', None, 'Sales', 'IT', 'HR', 'Sales'],
    'Salary': [60000, 75000, 58000, np.nan, 72000, 55000, 80000, 65000, 70000, 60000, 60000],
    'Join_Date': ['2020-01-15', '2019-03-20', '2021-06-10', '2020-08-05', '2018-11-22',
                  '2021-02-14', '2017-09-30', '2020-05-18', '2019-07-25', '2021-01-08', '2020-01-15']
}

df_messy = pd.DataFrame(messy_data)
messy_file = output_dir / 'messy_employee_data.xlsx'
df_messy.to_excel(messy_file, index=False)

print("Created messy dataset:")
print(df_messy)
print(f"\n✓ Saved to: {messy_file}")
print()

# ==============================================================================
# 2. DATA INSPECTION
# ==============================================================================

print("2. DATA INSPECTION")
print("-" * 80)

print("Basic Information:")
print(df_messy.info())
print()

print("First 5 rows:")
print(df_messy.head())
print()

print("Statistical Summary:")
print(df_messy.describe())
print()

print("Data Types:")
print(df_messy.dtypes)
print()

# ==============================================================================
# 3. HANDLING MISSING VALUES
# ==============================================================================

print("3. HANDLING MISSING VALUES")
print("-" * 80)

print("Missing values per column:")
print(df_messy.isnull().sum())
print()

print("Total missing values:", df_messy.isnull().sum().sum())
print()

# Show rows with missing values
print("Rows with missing values:")
print(df_messy[df_messy.isnull().any(axis=1)])
print()

# Different strategies for handling missing values
df_clean = df_messy.copy()

# Fill numeric columns with mean
df_clean['Age'] = df_clean['Age'].fillna(df_clean['Age'].mean())
df_clean['Salary'] = df_clean['Salary'].fillna(df_clean['Salary'].median())

# Fill categorical columns with mode or 'Unknown'
df_clean['Name'] = df_clean['Name'].fillna('Unknown')
df_clean['Department'] = df_clean['Department'].fillna('Unknown')

print("After filling missing values:")
print(df_clean.isnull().sum())
print()

# ==============================================================================
# 4. REMOVING DUPLICATES
# ==============================================================================

print("4. REMOVING DUPLICATES")
print("-" * 80)

print(f"Original rows: {len(df_clean)}")
print(f"Duplicate rows: {df_clean.duplicated().sum()}")
print()

print("Duplicate rows:")
print(df_clean[df_clean.duplicated(keep=False)])
print()

# Remove duplicates
df_clean = df_clean.drop_duplicates()
print(f"Rows after removing duplicates: {len(df_clean)}")
print()

# ==============================================================================
# 5. STRING CLEANING
# ==============================================================================

print("5. STRING CLEANING")
print("-" * 80)

print("Before cleaning:")
print(df_clean[['Name', 'Department']].head())
print()

# Clean string columns
df_clean['Name'] = df_clean['Name'].str.strip()  # Remove whitespace
df_clean['Name'] = df_clean['Name'].str.title()  # Proper case
df_clean['Department'] = df_clean['Department'].str.upper()  # Uppercase

print("After cleaning:")
print(df_clean[['Name', 'Department']].head())
print()

# ==============================================================================
# 6. DATA TYPE CONVERSION
# ==============================================================================

print("6. DATA TYPE CONVERSION")
print("-" * 80)

print("Before conversion:")
print(df_clean.dtypes)
print()

# Convert Join_Date to datetime
df_clean['Join_Date'] = pd.to_datetime(df_clean['Join_Date'])

# Ensure numeric types
df_clean['Age'] = df_clean['Age'].astype(int)
df_clean['Salary'] = df_clean['Salary'].astype(float)

print("After conversion:")
print(df_clean.dtypes)
print()

# ==============================================================================
# 7. FILTERING DATA
# ==============================================================================

print("7. FILTERING DATA")
print("-" * 80)

# Single condition
high_earners = df_clean[df_clean['Salary'] > 65000]
print(f"Employees earning > $65,000: {len(high_earners)}")
print(high_earners[['Name', 'Salary']])
print()

# Multiple conditions (AND)
young_high_earners = df_clean[(df_clean['Age'] < 30) & (df_clean['Salary'] > 65000)]
print(f"Young high earners (Age < 30 AND Salary > 65000): {len(young_high_earners)}")
print(young_high_earners[['Name', 'Age', 'Salary']])
print()

# Multiple conditions (OR)
sales_or_it = df_clean[(df_clean['Department'] == 'SALES') | (df_clean['Department'] == 'IT')]
print(f"Sales or IT employees: {len(sales_or_it)}")
print(sales_or_it[['Name', 'Department']])
print()

# Using isin
selected_depts = df_clean[df_clean['Department'].isin(['SALES', 'IT'])]
print(f"Selected departments (using isin): {len(selected_depts)}")
print()

# String contains
names_with_n = df_clean[df_clean['Name'].str.contains('n', case=False, na=False)]
print(f"Names containing 'n': {len(names_with_n)}")
print(names_with_n[['Name']])
print()

# ==============================================================================
# 8. SORTING DATA
# ==============================================================================

print("8. SORTING DATA")
print("-" * 80)

# Sort by single column
sorted_by_age = df_clean.sort_values('Age')
print("Sorted by Age (ascending):")
print(sorted_by_age[['Name', 'Age']].head())
print()

# Sort descending
sorted_by_salary = df_clean.sort_values('Salary', ascending=False)
print("Sorted by Salary (descending):")
print(sorted_by_salary[['Name', 'Salary']].head())
print()

# Sort by multiple columns
sorted_multi = df_clean.sort_values(['Department', 'Age'])
print("Sorted by Department, then Age:")
print(sorted_multi[['Name', 'Department', 'Age']])
print()

# ==============================================================================
# 9. GROUPING AND AGGREGATION
# ==============================================================================

print("9. GROUPING AND AGGREGATION")
print("-" * 80)

# Simple groupby
dept_counts = df_clean.groupby('Department').size()
print("Employees per department:")
print(dept_counts)
print()

# Aggregate specific column
avg_salary_by_dept = df_clean.groupby('Department')['Salary'].mean().round(2)
print("Average salary by department:")
print(avg_salary_by_dept)
print()

# Multiple aggregations
dept_summary = df_clean.groupby('Department').agg({
    'Salary': ['mean', 'min', 'max', 'count'],
    'Age': ['mean', 'min', 'max']
}).round(2)
print("Department summary:")
print(dept_summary)
print()

# Named aggregations
dept_stats = df_clean.groupby('Department').agg(
    avg_salary=('Salary', 'mean'),
    total_employees=('Employee_ID', 'count'),
    avg_age=('Age', 'mean')
).round(2)
print("Department statistics (named):")
print(dept_stats)
print()

# ==============================================================================
# 10. CREATING CALCULATED COLUMNS
# ==============================================================================

print("10. CREATING CALCULATED COLUMNS")
print("-" * 80)

# Simple calculation
df_clean['Salary_K'] = (df_clean['Salary'] / 1000).round(1)
print("Added Salary_K column:")
print(df_clean[['Name', 'Salary', 'Salary_K']].head())
print()

# Conditional calculation
df_clean['Bonus'] = 0
df_clean.loc[df_clean['Department'] == 'SALES', 'Bonus'] = df_clean['Salary'] * 0.15
df_clean.loc[df_clean['Department'] == 'IT', 'Bonus'] = df_clean['Salary'] * 0.10
df_clean.loc[df_clean['Department'] == 'HR', 'Bonus'] = df_clean['Salary'] * 0.08

print("Added Bonus column:")
print(df_clean[['Name', 'Department', 'Salary', 'Bonus']].head())
print()

# Using apply with lambda
df_clean['Tax'] = df_clean['Salary'].apply(lambda x: x * 0.25)
print("Added Tax column:")
print(df_clean[['Name', 'Salary', 'Tax']].head())
print()

# Using apply with function
def categorize_age(age):
    if age < 25:
        return 'Junior'
    elif age < 35:
        return 'Mid'
    else:
        return 'Senior'

df_clean['Seniority'] = df_clean['Age'].apply(categorize_age)
print("Added Seniority column:")
print(df_clean[['Name', 'Age', 'Seniority']])
print()

# ==============================================================================
# 11. BINNING AND CATEGORIZING
# ==============================================================================

print("11. BINNING AND CATEGORIZING")
print("-" * 80)

# Create age groups
df_clean['Age_Group'] = pd.cut(
    df_clean['Age'],
    bins=[0, 28, 32, 100],
    labels=['Young', 'Middle', 'Senior']
)
print("Age groups:")
print(df_clean[['Name', 'Age', 'Age_Group']])
print()

# Quantile-based binning
df_clean['Salary_Quartile'] = pd.qcut(
    df_clean['Salary'],
    q=4,
    labels=['Q1', 'Q2', 'Q3', 'Q4']
)
print("Salary quartiles:")
print(df_clean[['Name', 'Salary', 'Salary_Quartile']])
print()

# ==============================================================================
# 12. DATE OPERATIONS
# ==============================================================================

print("12. DATE OPERATIONS")
print("-" * 80)

# Extract date components
df_clean['Join_Year'] = df_clean['Join_Date'].dt.year
df_clean['Join_Month'] = df_clean['Join_Date'].dt.month
df_clean['Join_Day_Of_Week'] = df_clean['Join_Date'].dt.day_name()

print("Date components:")
print(df_clean[['Name', 'Join_Date', 'Join_Year', 'Join_Month', 'Join_Day_Of_Week']])
print()

# Calculate tenure
today = pd.Timestamp.now()
df_clean['Tenure_Days'] = (today - df_clean['Join_Date']).dt.days
df_clean['Tenure_Years'] = (df_clean['Tenure_Days'] / 365).round(1)

print("Tenure calculation:")
print(df_clean[['Name', 'Join_Date', 'Tenure_Years']])
print()

# ==============================================================================
# 13. PIVOT TABLES
# ==============================================================================

print("13. PIVOT TABLES")
print("-" * 80)

# Simple pivot table
pivot_salary = pd.pivot_table(
    df_clean,
    values='Salary',
    index='Department',
    aggfunc='mean'
).round(2)
print("Average salary by department (pivot):")
print(pivot_salary)
print()

# Multi-level pivot
pivot_multi = pd.pivot_table(
    df_clean,
    values='Salary',
    index='Department',
    columns='Seniority',
    aggfunc='mean',
    fill_value=0
).round(2)
print("Average salary by department and seniority:")
print(pivot_multi)
print()

# Multiple aggregations in pivot
pivot_detailed = pd.pivot_table(
    df_clean,
    values='Salary',
    index='Department',
    aggfunc=['mean', 'count', 'sum'],
    margins=True  # Add totals
).round(2)
print("Detailed salary pivot with totals:")
print(pivot_detailed)
print()

# ==============================================================================
# 14. CROSS-TABULATION
# ==============================================================================

print("14. CROSS-TABULATION")
print("-" * 80)

# Simple crosstab
crosstab = pd.crosstab(df_clean['Department'], df_clean['Seniority'])
print("Employee count by department and seniority:")
print(crosstab)
print()

# Crosstab with percentages
crosstab_pct = pd.crosstab(
    df_clean['Department'],
    df_clean['Seniority'],
    normalize='index'
) * 100
print("Percentage distribution by department:")
print(crosstab_pct.round(1))
print()

# ==============================================================================
# 15. REAL-WORLD EXAMPLE: SALES DATA ANALYSIS
# ==============================================================================

print("15. REAL-WORLD EXAMPLE: SALES DATA ANALYSIS")
print("-" * 80)

# Create comprehensive sales dataset
sales_data = {
    'Date': pd.date_range('2024-01-01', periods=100, freq='D'),
    'Region': np.random.choice(['North', 'South', 'East', 'West'], 100),
    'Product': np.random.choice(['Laptop', 'Phone', 'Tablet', 'Monitor'], 100),
    'Quantity': np.random.randint(1, 20, 100),
    'Price': np.random.choice([999, 599, 399, 299], 100),
    'Salesperson': np.random.choice(['Alice', 'Bob', 'Charlie', 'Diana'], 100)
}

df_sales = pd.DataFrame(sales_data)

# Calculate revenue
df_sales['Revenue'] = df_sales['Quantity'] * df_sales['Price']

# Add time-based columns
df_sales['Month'] = df_sales['Date'].dt.month
df_sales['Week'] = df_sales['Date'].dt.isocalendar().week
df_sales['Day_Of_Week'] = df_sales['Date'].dt.day_name()

print("Sales data preview:")
print(df_sales.head(10))
print()

# Analysis 1: Total revenue by region
regional_revenue = df_sales.groupby('Region')['Revenue'].sum().sort_values(ascending=False)
print("Total revenue by region:")
print(regional_revenue)
print()

# Analysis 2: Top products
product_performance = df_sales.groupby('Product').agg({
    'Revenue': 'sum',
    'Quantity': 'sum'
}).sort_values('Revenue', ascending=False)
print("Product performance:")
print(product_performance)
print()

# Analysis 3: Best salespeople
salesperson_stats = df_sales.groupby('Salesperson').agg({
    'Revenue': 'sum',
    'Quantity': 'sum',
    'Date': 'count'
}).rename(columns={'Date': 'Transactions'}).sort_values('Revenue', ascending=False)
print("Salesperson performance:")
print(salesperson_stats)
print()

# Analysis 4: Monthly trends
monthly_trend = df_sales.groupby('Month').agg({
    'Revenue': 'sum',
    'Quantity': 'sum'
})
print("Monthly sales trend:")
print(monthly_trend)
print()

# Analysis 5: Regional product preferences
regional_product_pivot = pd.pivot_table(
    df_sales,
    values='Revenue',
    index='Region',
    columns='Product',
    aggfunc='sum',
    fill_value=0
)
print("Revenue by region and product:")
print(regional_product_pivot)
print()

# ==============================================================================
# 16. EXPORT CLEANED DATA
# ==============================================================================

print("16. EXPORT CLEANED DATA")
print("-" * 80)

# Save cleaned employee data
clean_employee_file = output_dir / 'clean_employee_data.xlsx'
df_clean.to_excel(clean_employee_file, index=False)
print(f"✓ Cleaned employee data saved to: {clean_employee_file}")

# Save sales analysis
sales_analysis_file = output_dir / 'sales_analysis.xlsx'
with pd.ExcelWriter(sales_analysis_file) as writer:
    df_sales.to_excel(writer, sheet_name='Raw_Data', index=False)
    regional_revenue.to_excel(writer, sheet_name='Regional_Revenue')
    product_performance.to_excel(writer, sheet_name='Product_Performance')
    salesperson_stats.to_excel(writer, sheet_name='Salesperson_Stats')
    monthly_trend.to_excel(writer, sheet_name='Monthly_Trend')
    regional_product_pivot.to_excel(writer, sheet_name='Regional_Product')

print(f"✓ Sales analysis saved to: {sales_analysis_file}")
print()

# ==============================================================================
# SUMMARY
# ==============================================================================

print("=" * 80)
print("SESSION 4 COMPLETE!")
print("=" * 80)
print()
print("What you learned:")
print("✓ Inspect and understand data")
print("✓ Handle missing values effectively")
print("✓ Remove duplicates")
print("✓ Clean string data")
print("✓ Convert data types")
print("✓ Filter and select data")
print("✓ Sort data by multiple columns")
print("✓ Group and aggregate data")
print("✓ Create calculated columns")
print("✓ Bin and categorize values")
print("✓ Work with dates")
print("✓ Create pivot tables")
print("✓ Perform cross-tabulation")
print("✓ Analyze real-world sales data")
print()
print("Files created:")
for file in sorted(output_dir.glob('*.xlsx')):
    print(f"  - {file.name}")
print()
print("Next: Session 5 - Excel Formatting and Styling")
print("=" * 80)

