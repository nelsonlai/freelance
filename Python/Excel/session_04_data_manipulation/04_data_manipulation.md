# Session 4: Data Manipulation with Pandas - Comprehensive Guide

## Introduction

Data manipulation is the heart of working with Excel files in Python. Real-world Excel data is rarely perfect - it has missing values, duplicates, inconsistent formatting, and requires transformation before analysis. This session teaches you how to clean, filter, group, and transform Excel data like a professional data analyst.

## Why Data Manipulation Matters

1. **Real Data is Messy** - Missing values, duplicates, errors
2. **Analysis Requires Clean Data** - Garbage in, garbage out
3. **Business Insights** - Extract meaningful information
4. **Report Generation** - Transform raw data into presentations
5. **Automation** - Standardize data processing workflows

## Data Cleaning Fundamentals

### Handling Missing Values

```python
import pandas as pd
import numpy as np

# Create DataFrame with missing values
df = pd.DataFrame({
    'Name': ['Alice', 'Bob', None, 'Diana', 'Eve'],
    'Age': [25, 30, np.nan, 28, 32],
    'Salary': [60000, np.nan, 70000, None, 75000],
    'Department': ['Sales', 'IT', 'HR', None, 'IT']
})

# Check for missing values
print(df.isnull().sum())
print(df.isna().sum())  # Alternative

# Check if any missing values
print(df.isnull().any())

# Find rows with any missing values
rows_with_na = df[df.isnull().any(axis=1)]
```

### Dropping Missing Values

```python
# Drop rows with ANY missing values
df_clean = df.dropna()

# Drop rows where ALL values are missing
df_clean = df.dropna(how='all')

# Drop rows with missing values in specific columns
df_clean = df.dropna(subset=['Name', 'Age'])

# Drop columns with any missing values
df_clean = df.dropna(axis=1)
```

### Filling Missing Values

```python
# Fill with a specific value
df_filled = df.fillna(0)
df_filled = df.fillna('Unknown')

# Fill different columns with different values
df_filled = df.fillna({
    'Age': df['Age'].mean(),
    'Salary': df['Salary'].median(),
    'Department': 'Unknown'
})

# Forward fill (use previous value)
df_filled = df.fillna(method='ffill')

# Backward fill (use next value)
df_filled = df.fillna(method='bfill')

# Interpolate (for numeric data)
df['Age'] = df['Age'].interpolate()
```

### Removing Duplicates

```python
# Check for duplicates
print(df.duplicated().sum())

# Show duplicate rows
duplicates = df[df.duplicated()]

# Remove duplicates (keep first occurrence)
df_unique = df.drop_duplicates()

# Remove duplicates based on specific columns
df_unique = df.drop_duplicates(subset=['Name'])

# Keep last occurrence instead of first
df_unique = df.drop_duplicates(keep='last')

# Mark all duplicates (not keeping any)
df_unique = df.drop_duplicates(keep=False)
```

## Data Filtering and Selection

### Boolean Indexing

```python
# Single condition
high_earners = df[df['Salary'] > 65000]
young_employees = df[df['Age'] < 30]
it_dept = df[df['Department'] == 'IT']

# Multiple conditions (AND)
young_high_earners = df[(df['Age'] < 30) & (df['Salary'] > 65000)]

# Multiple conditions (OR)
sales_or_it = df[(df['Department'] == 'Sales') | (df['Department'] == 'IT')]

# NOT condition
not_sales = df[df['Department'] != 'Sales']
not_sales_alt = df[~(df['Department'] == 'Sales')]

# Multiple values (isin)
selected_depts = df[df['Department'].isin(['Sales', 'IT', 'HR'])]

# String contains
names_with_a = df[df['Name'].str.contains('a', case=False, na=False)]

# Between values
mid_age = df[df['Age'].between(28, 35)]
```

### Query Method

```python
# Using query() for more readable filtering
high_earners = df.query('Salary > 65000')
young_it = df.query('Age < 30 and Department == "IT"')
sales_or_hr = df.query('Department in ["Sales", "HR"]')

# Using variables in queries
min_salary = 60000
filtered = df.query('Salary > @min_salary')
```

### Selecting Columns

```python
# Select single column (returns Series)
names = df['Name']

# Select single column (returns DataFrame)
names_df = df[['Name']]

# Select multiple columns
subset = df[['Name', 'Age', 'Salary']]

# Select columns by data type
numeric_cols = df.select_dtypes(include=[np.number])
object_cols = df.select_dtypes(include=['object'])

# Select columns by name pattern
cols_with_a = df.filter(like='a')
cols_regex = df.filter(regex='^S')  # Starts with S
```

### loc and iloc

```python
# loc: label-based selection
df.loc[0, 'Name']  # Single value
df.loc[0:2, 'Name':'Age']  # Slice
df.loc[df['Age'] > 30, ['Name', 'Salary']]  # Conditional

# iloc: integer position-based selection
df.iloc[0, 0]  # First row, first column
df.iloc[0:3, 0:2]  # First 3 rows, first 2 columns
df.iloc[[0, 2, 4], :]  # Specific rows, all columns
```

## Data Sorting

### Sort by Single Column

```python
# Sort by Age (ascending)
df_sorted = df.sort_values('Age')

# Sort by Age (descending)
df_sorted = df.sort_values('Age', ascending=False)

# Sort in place
df.sort_values('Age', inplace=True)
```

### Sort by Multiple Columns

```python
# Sort by Department, then by Age
df_sorted = df.sort_values(['Department', 'Age'])

# Different sort orders for different columns
df_sorted = df.sort_values(
    ['Department', 'Age'],
    ascending=[True, False]
)
```

### Sort by Index

```python
# Sort by row index
df_sorted = df.sort_index()

# Sort by column names
df_sorted = df.sort_index(axis=1)
```

## Grouping and Aggregation

### Basic GroupBy

```python
# Group by single column
dept_groups = df.groupby('Department')

# Get group sizes
print(dept_groups.size())

# Aggregate specific column
avg_salary = df.groupby('Department')['Salary'].mean()
total_employees = df.groupby('Department').size()
```

### Multiple Aggregations

```python
# Multiple statistics for one column
dept_stats = df.groupby('Department')['Salary'].agg([
    'count',
    'mean',
    'median',
    'min',
    'max',
    'std'
])

# Different aggregations for different columns
summary = df.groupby('Department').agg({
    'Age': ['mean', 'min', 'max'],
    'Salary': ['sum', 'mean'],
    'Name': 'count'
})

# Custom aggregation functions
def salary_range(x):
    return x.max() - x.min()

dept_range = df.groupby('Department')['Salary'].agg(salary_range)
```

### Named Aggregations (pandas 0.25+)

```python
summary = df.groupby('Department').agg(
    avg_salary=('Salary', 'mean'),
    total_employees=('Name', 'count'),
    max_age=('Age', 'max')
).reset_index()
```

### Group by Multiple Columns

```python
# Create multi-level grouping
df['Seniority'] = pd.cut(df['Age'], bins=[0, 28, 35, 100], 
                         labels=['Junior', 'Mid', 'Senior'])

multi_group = df.groupby(['Department', 'Seniority']).agg({
    'Salary': 'mean',
    'Name': 'count'
})
```

### Transform and Apply

```python
# Transform: returns same shape as input
df['Salary_Normalized'] = df.groupby('Department')['Salary'].transform(
    lambda x: (x - x.mean()) / x.std()
)

# Apply: can return different shape
def top_two(group):
    return group.nlargest(2, 'Salary')

top_earners = df.groupby('Department').apply(top_two)
```

## Pivot Tables

### Basic Pivot Table

```python
# Create pivot table
pivot = pd.pivot_table(
    df,
    values='Salary',
    index='Department',
    aggfunc='mean'
)
```

### Multi-Level Pivot Tables

```python
# Multiple row indices
pivot = pd.pivot_table(
    df,
    values='Salary',
    index=['Department', 'Seniority'],
    aggfunc='mean'
)

# With columns
pivot = pd.pivot_table(
    df,
    values='Salary',
    index='Department',
    columns='Seniority',
    aggfunc='mean',
    fill_value=0
)
```

### Multiple Aggregations in Pivot

```python
pivot = pd.pivot_table(
    df,
    values='Salary',
    index='Department',
    aggfunc=['mean', 'sum', 'count'],
    margins=True  # Add totals row
)
```

## Data Transformation

### Adding Calculated Columns

```python
# Simple calculation
df['Salary_K'] = df['Salary'] / 1000

# Conditional calculations
df['Bonus'] = df['Salary'] * 0.10
df.loc[df['Department'] == 'Sales', 'Bonus'] = df['Salary'] * 0.15

# Using apply with lambda
df['Tax'] = df['Salary'].apply(lambda x: x * 0.25)

# Using apply with custom function
def calculate_grade(age):
    if age < 25:
        return 'Junior'
    elif age < 35:
        return 'Mid'
    else:
        return 'Senior'

df['Grade'] = df['Age'].apply(calculate_grade)
```

### String Operations

```python
# Convert case
df['Name_Upper'] = df['Name'].str.upper()
df['Name_Lower'] = df['Name'].str.lower()
df['Name_Title'] = df['Name'].str.title()

# String length
df['Name_Length'] = df['Name'].str.len()

# Contains
has_a = df[df['Name'].str.contains('a', case=False, na=False)]

# Replace
df['Name_Clean'] = df['Name'].str.replace('Dr.', '')

# Split
df[['First', 'Last']] = df['Full_Name'].str.split(' ', expand=True)

# Strip whitespace
df['Name'] = df['Name'].str.strip()
```

### Binning and Categorizing

```python
# Create bins
df['Age_Group'] = pd.cut(
    df['Age'],
    bins=[0, 25, 35, 50, 100],
    labels=['<25', '25-35', '35-50', '50+']
)

# Quantile-based binning
df['Salary_Quartile'] = pd.qcut(
    df['Salary'],
    q=4,
    labels=['Q1', 'Q2', 'Q3', 'Q4']
)
```

### Date Operations

```python
# Convert to datetime
df['Date'] = pd.to_datetime(df['Date'])

# Extract date components
df['Year'] = df['Date'].dt.year
df['Month'] = df['Date'].dt.month
df['Day'] = df['Date'].dt.day
df['DayOfWeek'] = df['Date'].dt.dayofweek
df['DayName'] = df['Date'].dt.day_name()

# Date arithmetic
df['Days_Since'] = (pd.Timestamp.now() - df['Date']).dt.days
```

## Merging and Joining

### Merge DataFrames

```python
# Inner join (default)
merged = pd.merge(df1, df2, on='ID')

# Left join
merged = pd.merge(df1, df2, on='ID', how='left')

# Right join
merged = pd.merge(df1, df2, on='ID', how='right')

# Outer join (full outer)
merged = pd.merge(df1, df2, on='ID', how='outer')

# Merge on multiple keys
merged = pd.merge(df1, df2, on=['ID', 'Year'])

# Merge on different column names
merged = pd.merge(
    df1, df2,
    left_on='EmployeeID',
    right_on='EmpID'
)
```

### Concatenating DataFrames

```python
# Vertical concatenation (stack rows)
combined = pd.concat([df1, df2], ignore_index=True)

# Horizontal concatenation (side by side)
combined = pd.concat([df1, df2], axis=1)

# Concatenate with keys
combined = pd.concat([df1, df2], keys=['Q1', 'Q2'])
```

## Reshaping Data

### Melt (Wide to Long)

```python
# Wide format
df_wide = pd.DataFrame({
    'Name': ['Alice', 'Bob'],
    'Q1': [100, 150],
    'Q2': [110, 160],
    'Q3': [120, 170]
})

# Convert to long format
df_long = pd.melt(
    df_wide,
    id_vars=['Name'],
    value_vars=['Q1', 'Q2', 'Q3'],
    var_name='Quarter',
    value_name='Sales'
)
```

### Pivot (Long to Wide)

```python
# Convert back to wide format
df_wide_again = df_long.pivot(
    index='Name',
    columns='Quarter',
    values='Sales'
)
```

## Real-World Example: Sales Data Analysis

```python
import pandas as pd
import numpy as np

# Read messy sales data
df = pd.read_excel('sales_data.xlsx')

# Step 1: Data Cleaning
print("Original shape:", df.shape)

# Remove duplicates
df = df.drop_duplicates()

# Handle missing values
df['Amount'] = df['Amount'].fillna(0)
df['Region'] = df['Region'].fillna('Unknown')
df = df.dropna(subset=['Date', 'Product'])

# Clean string columns
df['Product'] = df['Product'].str.strip().str.upper()
df['Region'] = df['Region'].str.title()

# Step 2: Data Transformation
df['Date'] = pd.to_datetime(df['Date'])
df['Month'] = df['Date'].dt.to_period('M')
df['Quarter'] = df['Date'].dt.to_period('Q')

# Step 3: Calculated Fields
df['Revenue'] = df['Quantity'] * df['Price']
df['Cost'] = df['Quantity'] * df['Unit_Cost']
df['Profit'] = df['Revenue'] - df['Cost']
df['Margin'] = (df['Profit'] / df['Revenue'] * 100).round(2)

# Step 4: Aggregation and Analysis
# Monthly summary by region
monthly_summary = df.groupby(['Month', 'Region']).agg({
    'Revenue': 'sum',
    'Profit': 'sum',
    'Quantity': 'sum'
}).reset_index()

# Top products by revenue
top_products = df.groupby('Product').agg({
    'Revenue': 'sum',
    'Quantity': 'sum'
}).sort_values('Revenue', ascending=False).head(10)

# Regional performance
regional = df.groupby('Region').agg({
    'Revenue': 'sum',
    'Profit': 'sum',
    'Margin': 'mean'
}).round(2)

# Step 5: Create pivot table
pivot_sales = pd.pivot_table(
    df,
    values='Revenue',
    index='Product',
    columns='Quarter',
    aggfunc='sum',
    fill_value=0,
    margins=True
)

# Step 6: Export results
with pd.ExcelWriter('sales_analysis.xlsx') as writer:
    monthly_summary.to_excel(writer, sheet_name='Monthly', index=False)
    top_products.to_excel(writer, sheet_name='Top_Products')
    regional.to_excel(writer, sheet_name='Regional')
    pivot_sales.to_excel(writer, sheet_name='Pivot')

print("✓ Analysis complete!")
```

## Best Practices

1. **Always check data first** - Use `df.head()`, `df.info()`, `df.describe()`
2. **Handle missing values explicitly** - Don't ignore NaN values
3. **Verify after operations** - Check shape and content after transformations
4. **Use meaningful names** - Clear column and variable names
5. **Document assumptions** - Comment why you made specific choices
6. **Test on small samples** - Verify logic before processing large files
7. **Save intermediate results** - For debugging and review
8. **Use vectorized operations** - Faster than loops

## Summary

You've learned how to:
- ✅ Clean messy data (missing values, duplicates)
- ✅ Filter and select data effectively
- ✅ Sort data by single and multiple columns
- ✅ Group and aggregate data for insights
- ✅ Create pivot tables
- ✅ Transform data (calculate, categorize, reshape)
- ✅ Merge and concatenate DataFrames
- ✅ Apply real-world data analysis workflows

## Next Steps

In Session 5, you'll learn how to format your cleaned and analyzed data into professional-looking Excel reports with colors, fonts, borders, and conditional formatting.

