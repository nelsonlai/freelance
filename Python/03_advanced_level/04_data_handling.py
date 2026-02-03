# Data Handling Examples
import numpy as np
import pandas as pd
from typing import List, Dict, Any
import matplotlib.pyplot as plt

print("Data Handling Examples")
print("=" * 25)

# 1. NumPy Basics
print("1. NumPy Basics")
print("-" * 15)

# Array creation
arr1 = np.array([1, 2, 3, 4, 5])
arr2 = np.array([[1, 2, 3], [4, 5, 6]])
arr3 = np.zeros((3, 4))
arr4 = np.ones((2, 3))
arr5 = np.random.random((2, 3))

print(f"1D Array: {arr1}")
print(f"2D Array:\n{arr2}")
print(f"Zeros array:\n{arr3}")
print(f"Ones array:\n{arr4}")
print(f"Random array:\n{arr5}")

# Array properties
print(f"\nArray shape: {arr2.shape}")
print(f"Array size: {arr2.size}")
print(f"Array dtype: {arr2.dtype}")
print(f"Array ndim: {arr2.ndim}")

# Array operations
arr_a = np.array([1, 2, 3, 4])
arr_b = np.array([5, 6, 7, 8])

print(f"\nArray A: {arr_a}")
print(f"Array B: {arr_b}")
print(f"A + B: {arr_a + arr_b}")
print(f"A - B: {arr_a - arr_b}")
print(f"A * B: {arr_a * arr_b}")
print(f"A / B: {arr_a / arr_b}")

# Array indexing and slicing
arr = np.array([[1, 2, 3, 4], [5, 6, 7, 8], [9, 10, 11, 12]])
print(f"\nOriginal array:\n{arr}")
print(f"Element at [1, 2]: {arr[1, 2]}")
print(f"First row: {arr[0, :]}")
print(f"Second column: {arr[:, 1]}")
print(f"Subarray [1:3, 1:3]:\n{arr[1:3, 1:3]}")

# Array reshaping
arr_flat = np.array([1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12])
arr_reshaped = arr_flat.reshape(3, 4)
print(f"\nReshaped array:\n{arr_reshaped}")

# Array concatenation
arr1 = np.array([[1, 2], [3, 4]])
arr2 = np.array([[5, 6], [7, 8]])
arr_concat = np.concatenate([arr1, arr2], axis=0)
print(f"\nConcatenated arrays:\n{arr_concat}")

# Array statistics
arr_stats = np.array([1, 2, 3, 4, 5, 6, 7, 8, 9, 10])
print(f"\nArray: {arr_stats}")
print(f"Mean: {np.mean(arr_stats)}")
print(f"Median: {np.median(arr_stats)}")
print(f"Standard deviation: {np.std(arr_stats)}")
print(f"Min: {np.min(arr_stats)}")
print(f"Max: {np.max(arr_stats)}")
print(f"Sum: {np.sum(arr_stats)}")

# 2. Pandas Basics
print("\n2. Pandas Basics")
print("-" * 15)

# Series creation
series = pd.Series([1, 2, 3, 4, 5], index=['a', 'b', 'c', 'd', 'e'])
print(f"Series:\n{series}")

# DataFrame creation
data = {
    'Name': ['Alice', 'Bob', 'Charlie', 'David'],
    'Age': [25, 30, 35, 28],
    'City': ['New York', 'London', 'Paris', 'Tokyo'],
    'Salary': [50000, 60000, 70000, 55000]
}
df = pd.DataFrame(data)
print(f"\nDataFrame:\n{df}")

# DataFrame properties
print(f"\nDataFrame shape: {df.shape}")
print(f"DataFrame columns: {df.columns.tolist()}")
print(f"DataFrame index: {df.index.tolist()}")
print(f"DataFrame dtypes:\n{df.dtypes}")

# DataFrame operations
print(f"\nFirst 2 rows:\n{df.head(2)}")
print(f"Last 2 rows:\n{df.tail(2)}")
print(f"Basic statistics:\n{df.describe()}")

# DataFrame indexing
print(f"\nSelect column 'Name':\n{df['Name']}")
print(f"Select multiple columns:\n{df[['Name', 'Age']]}")
print(f"Select rows by index:\n{df.iloc[0:2]}")
print(f"Select rows by condition:\n{df[df['Age'] > 30]}")

# DataFrame operations
df['Age_Group'] = df['Age'].apply(lambda x: 'Young' if x < 30 else 'Old')
print(f"\nDataFrame with Age_Group:\n{df}")

# Groupby operations
grouped = df.groupby('Age_Group')['Salary'].mean()
print(f"\nAverage salary by age group:\n{grouped}")

# 3. Data Cleaning
print("\n3. Data Cleaning")
print("-" * 15)

# Create sample data with missing values
data_dirty = {
    'Name': ['Alice', 'Bob', None, 'David', 'Eve'],
    'Age': [25, 30, 35, None, 28],
    'City': ['New York', 'London', 'Paris', 'Tokyo', ''],
    'Salary': [50000, 60000, 70000, 55000, 45000]
}
df_dirty = pd.DataFrame(data_dirty)
print(f"Dirty DataFrame:\n{df_dirty}")

# Check for missing values
print(f"\nMissing values:\n{df_dirty.isnull().sum()}")

# Fill missing values
df_cleaned = df_dirty.copy()
df_cleaned['Name'].fillna('Unknown', inplace=True)
df_cleaned['Age'].fillna(df_cleaned['Age'].mean(), inplace=True)
df_cleaned['City'].replace('', 'Unknown', inplace=True)

print(f"\nCleaned DataFrame:\n{df_cleaned}")

# Remove duplicates
df_duplicates = pd.DataFrame({
    'Name': ['Alice', 'Bob', 'Alice', 'Charlie'],
    'Age': [25, 30, 25, 35],
    'City': ['New York', 'London', 'New York', 'Paris']
})
print(f"\nDataFrame with duplicates:\n{df_duplicates}")
df_no_duplicates = df_duplicates.drop_duplicates()
print(f"DataFrame without duplicates:\n{df_no_duplicates}")

# 4. Data Transformation
print("\n4. Data Transformation")
print("-" * 20)

# Create sample data
data_transform = {
    'Product': ['A', 'B', 'C', 'D', 'E'],
    'Price': [10.5, 25.0, 15.75, 30.0, 12.5],
    'Quantity': [100, 50, 75, 25, 80],
    'Category': ['Electronics', 'Clothing', 'Electronics', 'Clothing', 'Books']
}
df_transform = pd.DataFrame(data_transform)
print(f"Original DataFrame:\n{df_transform}")

# Apply transformations
df_transform['Total_Value'] = df_transform['Price'] * df_transform['Quantity']
df_transform['Price_Category'] = df_transform['Price'].apply(
    lambda x: 'Low' if x < 15 else 'Medium' if x < 25 else 'High'
)

print(f"\nTransformed DataFrame:\n{df_transform}")

# Pivot table
pivot_table = df_transform.pivot_table(
    values='Total_Value',
    index='Category',
    columns='Price_Category',
    aggfunc='sum',
    fill_value=0
)
print(f"\nPivot table:\n{pivot_table}")

# 5. Data Aggregation
print("\n5. Data Aggregation")
print("-" * 18)

# Create sample sales data
sales_data = {
    'Date': pd.date_range('2023-01-01', periods=20, freq='D'),
    'Product': ['A', 'B', 'C', 'D', 'E'] * 4,
    'Sales': np.random.randint(1000, 5000, 20),
    'Region': ['North', 'South', 'East', 'West'] * 5
}
df_sales = pd.DataFrame(sales_data)
print(f"Sales DataFrame:\n{df_sales.head()}")

# Group by operations
sales_by_region = df_sales.groupby('Region')['Sales'].sum()
print(f"\nTotal sales by region:\n{sales_by_region}")

sales_by_product = df_sales.groupby('Product')['Sales'].agg(['sum', 'mean', 'count'])
print(f"\nSales by product:\n{sales_by_product}")

# Multiple groupby
sales_by_region_product = df_sales.groupby(['Region', 'Product'])['Sales'].sum()
print(f"\nSales by region and product:\n{sales_by_region_product}")

# 6. Data Visualization
print("\n6. Data Visualization")
print("-" * 20)

# Create sample data for visualization
np.random.seed(42)
x = np.linspace(0, 10, 100)
y1 = np.sin(x)
y2 = np.cos(x)
y3 = np.sin(x) * np.cos(x)

# Line plot
plt.figure(figsize=(10, 6))
plt.plot(x, y1, label='sin(x)', linewidth=2)
plt.plot(x, y2, label='cos(x)', linewidth=2)
plt.plot(x, y3, label='sin(x) * cos(x)', linewidth=2)
plt.xlabel('x')
plt.ylabel('y')
plt.title('Trigonometric Functions')
plt.legend()
plt.grid(True)
plt.show()

# Scatter plot
plt.figure(figsize=(8, 6))
x_scatter = np.random.randn(100)
y_scatter = 2 * x_scatter + np.random.randn(100)
plt.scatter(x_scatter, y_scatter, alpha=0.6)
plt.xlabel('X')
plt.ylabel('Y')
plt.title('Scatter Plot')
plt.grid(True)
plt.show()

# Histogram
plt.figure(figsize=(8, 6))
data_hist = np.random.normal(0, 1, 1000)
plt.hist(data_hist, bins=30, alpha=0.7, edgecolor='black')
plt.xlabel('Value')
plt.ylabel('Frequency')
plt.title('Histogram of Normal Distribution')
plt.grid(True)
plt.show()

# Bar plot
plt.figure(figsize=(8, 6))
categories = ['A', 'B', 'C', 'D', 'E']
values = [23, 45, 56, 78, 32]
plt.bar(categories, values, color=['red', 'green', 'blue', 'orange', 'purple'])
plt.xlabel('Categories')
plt.ylabel('Values')
plt.title('Bar Plot')
plt.grid(True, axis='y')
plt.show()

# 7. Data Export and Import
print("\n7. Data Export and Import")
print("-" * 25)

# Create sample data
data_export = {
    'Name': ['Alice', 'Bob', 'Charlie', 'David'],
    'Age': [25, 30, 35, 28],
    'City': ['New York', 'London', 'Paris', 'Tokyo'],
    'Salary': [50000, 60000, 70000, 55000]
}
df_export = pd.DataFrame(data_export)

# Export to CSV
df_export.to_csv('sample_data.csv', index=False)
print("Data exported to CSV")

# Export to JSON
df_export.to_json('sample_data.json', orient='records')
print("Data exported to JSON")

# Export to Excel
df_export.to_excel('sample_data.xlsx', index=False)
print("Data exported to Excel")

# Read from CSV
df_imported = pd.read_csv('sample_data.csv')
print(f"\nImported data:\n{df_imported}")

# 8. Advanced Data Operations
print("\n8. Advanced Data Operations")
print("-" * 28)

# Create time series data
dates = pd.date_range('2023-01-01', periods=100, freq='D')
ts_data = pd.DataFrame({
    'Date': dates,
    'Value': np.random.randn(100).cumsum(),
    'Volume': np.random.randint(100, 1000, 100)
})
ts_data.set_index('Date', inplace=True)

print(f"Time series data:\n{ts_data.head()}")

# Rolling window operations
ts_data['Rolling_Mean'] = ts_data['Value'].rolling(window=7).mean()
ts_data['Rolling_Std'] = ts_data['Value'].rolling(window=7).std()

print(f"\nData with rolling statistics:\n{ts_data.head(10)}")

# Resampling
monthly_data = ts_data.resample('M').agg({
    'Value': 'mean',
    'Volume': 'sum'
})
print(f"\nMonthly resampled data:\n{monthly_data.head()}")

# 9. Data Validation
print("\n9. Data Validation")
print("-" * 18)

# Create sample data with validation issues
data_validation = {
    'Name': ['Alice', 'Bob', 'Charlie', 'David', 'Eve'],
    'Age': [25, 30, 35, 28, -5],  # Negative age
    'Email': ['alice@email.com', 'bob@email.com', 'invalid-email', 'david@email.com', 'eve@email.com'],
    'Salary': [50000, 60000, 70000, 55000, 45000]
}
df_validation = pd.DataFrame(data_validation)

print(f"Data with validation issues:\n{df_validation}")

# Validation functions
def validate_age(age):
    return 0 <= age <= 120

def validate_email(email):
    return '@' in email and '.' in email

def validate_salary(salary):
    return salary > 0

# Apply validations
df_validation['Valid_Age'] = df_validation['Age'].apply(validate_age)
df_validation['Valid_Email'] = df_validation['Email'].apply(validate_email)
df_validation['Valid_Salary'] = df_validation['Salary'].apply(validate_salary)

print(f"\nData with validation flags:\n{df_validation}")

# Filter valid data
valid_data = df_validation[
    df_validation['Valid_Age'] & 
    df_validation['Valid_Email'] & 
    df_validation['Valid_Salary']
]
print(f"\nValid data only:\n{valid_data}")

# 10. Performance Optimization
print("\n10. Performance Optimization")
print("-" * 28)

# Create large dataset
large_data = {
    'A': np.random.randn(10000),
    'B': np.random.randn(10000),
    'C': np.random.randn(10000),
    'D': np.random.randn(10000)
}
df_large = pd.DataFrame(large_data)

print(f"Large DataFrame shape: {df_large.shape}")

# Vectorized operations (fast)
start_time = time.time()
df_large['Sum'] = df_large['A'] + df_large['B'] + df_large['C'] + df_large['D']
vectorized_time = time.time() - start_time
print(f"Vectorized operation time: {vectorized_time:.4f} seconds")

# Apply operations (slower)
start_time = time.time()
df_large['Sum_Apply'] = df_large.apply(lambda row: row['A'] + row['B'] + row['C'] + row['D'], axis=1)
apply_time = time.time() - start_time
print(f"Apply operation time: {apply_time:.4f} seconds")

# Memory usage optimization
print(f"\nDataFrame memory usage: {df_large.memory_usage(deep=True).sum() / 1024**2:.2f} MB")

# Optimize data types
df_optimized = df_large.copy()
df_optimized['A'] = df_optimized['A'].astype('float32')
df_optimized['B'] = df_optimized['B'].astype('float32')
df_optimized['C'] = df_optimized['C'].astype('float32')
df_optimized['D'] = df_optimized['D'].astype('float32')

print(f"Optimized DataFrame memory usage: {df_optimized.memory_usage(deep=True).sum() / 1024**2:.2f} MB")

print("\nData Handling examples completed!")