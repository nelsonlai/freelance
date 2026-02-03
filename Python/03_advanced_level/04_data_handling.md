# 4. Data Handling - Pandas, NumPy, and Data Analysis

Data handling is crucial for modern applications. This lesson covers Pandas for data manipulation, NumPy for numerical computing, and practical data analysis techniques used in professional Python development.

## NumPy Fundamentals

### Basic NumPy Operations

```python
import numpy as np

# Creating arrays
arr1 = np.array([1, 2, 3, 4, 5])
arr2 = np.array([[1, 2, 3], [4, 5, 6]])
arr3 = np.zeros((3, 4))
arr4 = np.ones((2, 3))
arr5 = np.arange(0, 10, 2)
arr6 = np.linspace(0, 1, 5)

print("=== NumPy Array Creation ===")
print(f"1D Array: {arr1}")
print(f"2D Array:\n{arr2}")
print(f"Zeros array:\n{arr3}")
print(f"Ones array:\n{arr4}")
print(f"Arange: {arr5}")
print(f"Linspace: {arr6}")

# Array properties
print(f"\nArray shape: {arr2.shape}")
print(f"Array dtype: {arr2.dtype}")
print(f"Array size: {arr2.size}")
print(f"Array ndim: {arr2.ndim}")

# Array operations
print("\n=== NumPy Operations ===")
a = np.array([1, 2, 3, 4])
b = np.array([5, 6, 7, 8])

print(f"Addition: {a + b}")
print(f"Multiplication: {a * b}")
print(f"Dot product: {np.dot(a, b)}")
print(f"Sum: {np.sum(a)}")
print(f"Mean: {np.mean(a)}")
print(f"Standard deviation: {np.std(a)}")

# Broadcasting
print("\n=== Broadcasting ===")
matrix = np.array([[1, 2, 3], [4, 5, 6]])
scalar = 10
vector = np.array([1, 2, 3])

print(f"Matrix + scalar:\n{matrix + scalar}")
print(f"Matrix + vector:\n{matrix + vector}")

# Array indexing and slicing
print("\n=== Array Indexing ===")
arr = np.array([[1, 2, 3, 4], [5, 6, 7, 8], [9, 10, 11, 12]])

print(f"Original array:\n{arr}")
print(f"arr[0, 1]: {arr[0, 1]}")
print(f"arr[:, 2]: {arr[:, 2]}")
print(f"arr[1:, :2]:\n{arr[1:, :2]}")

# Boolean indexing
print("\n=== Boolean Indexing ===")
mask = arr > 5
print(f"Mask (arr > 5):\n{mask}")
print(f"Values > 5: {arr[mask]}")

# Array reshaping
print("\n=== Array Reshaping ===")
flat_arr = np.arange(12)
print(f"Original: {flat_arr}")
print(f"Reshaped to (3, 4):\n{flat_arr.reshape(3, 4)}")
print(f"Reshaped to (2, 6):\n{flat_arr.reshape(2, 6)}")
```

### Advanced NumPy Operations

```python
# Linear algebra
print("\n=== Linear Algebra ===")
A = np.array([[1, 2], [3, 4]])
B = np.array([[5, 6], [7, 8]])

print(f"Matrix A:\n{A}")
print(f"Matrix B:\n{B}")
print(f"Matrix multiplication:\n{np.dot(A, B)}")
print(f"Matrix transpose:\n{A.T}")
print(f"Matrix determinant: {np.linalg.det(A)}")
print(f"Matrix inverse:\n{np.linalg.inv(A)}")

# Random numbers
print("\n=== Random Numbers ===")
np.random.seed(42)  # For reproducibility

random_arr = np.random.random((3, 3))
normal_arr = np.random.normal(0, 1, (3, 3))
integers_arr = np.random.randint(1, 10, (3, 3))

print(f"Random (0,1):\n{random_arr}")
print(f"Normal distribution:\n{normal_arr}")
print(f"Random integers:\n{integers_arr}")

# Statistical operations
print("\n=== Statistical Operations ===")
data = np.random.normal(100, 15, 1000)

print(f"Mean: {np.mean(data):.2f}")
print(f"Median: {np.median(data):.2f}")
print(f"Standard deviation: {np.std(data):.2f}")
print(f"Variance: {np.var(data):.2f}")
print(f"Min: {np.min(data):.2f}")
print(f"Max: {np.max(data):.2f}")
print(f"25th percentile: {np.percentile(data, 25):.2f}")
print(f"75th percentile: {np.percentile(data, 75):.2f}")
```

## Pandas Fundamentals

### DataFrames and Series

```python
import pandas as pd
import numpy as np

# Creating DataFrames
data = {
    'Name': ['Alice', 'Bob', 'Charlie', 'Diana'],
    'Age': [25, 30, 35, 28],
    'City': ['New York', 'London', 'Tokyo', 'Paris'],
    'Salary': [50000, 60000, 70000, 55000]
}

df = pd.DataFrame(data)
print("=== DataFrame Creation ===")
print(df)
print(f"\nDataFrame shape: {df.shape}")
print(f"DataFrame columns: {df.columns.tolist()}")
print(f"DataFrame index: {df.index.tolist()}")
print(f"DataFrame dtypes:\n{df.dtypes}")

# Creating Series
ages = pd.Series([25, 30, 35, 28], name='Age')
print(f"\nSeries:\n{ages}")

# Reading data from different sources
print("\n=== Reading Data ===")
# CSV example (commented out - would need actual file)
# df_csv = pd.read_csv('data.csv')

# Creating sample data for demonstration
sample_data = pd.DataFrame({
    'date': pd.date_range('2023-01-01', periods=10),
    'sales': np.random.randint(1000, 5000, 10),
    'region': np.random.choice(['North', 'South', 'East', 'West'], 10)
})

print("Sample data:")
print(sample_data)

# Basic DataFrame operations
print("\n=== DataFrame Operations ===")
print(f"First 3 rows:\n{df.head(3)}")
print(f"Last 2 rows:\n{df.tail(2)}")
print(f"Basic info:\n{df.info()}")
print(f"Descriptive statistics:\n{df.describe()}")

# Column operations
print("\n=== Column Operations ===")
df['Salary_K'] = df['Salary'] / 1000
df['Age_Group'] = pd.cut(df['Age'], bins=[0, 25, 35, 100], labels=['Young', 'Middle', 'Senior'])

print("Modified DataFrame:")
print(df)

# Row operations
print("\n=== Row Operations ===")
# Filtering
young_people = df[df['Age'] < 30]
high_earners = df[df['Salary'] > 55000]

print("Young people:")
print(young_people)
print("\nHigh earners:")
print(high_earners)

# Sorting
sorted_by_age = df.sort_values('Age', ascending=False)
print("\nSorted by age (descending):")
print(sorted_by_age)
```

### Data Cleaning and Manipulation

```python
# Creating sample data with missing values
print("\n=== Data Cleaning ===")
dirty_data = pd.DataFrame({
    'Name': ['Alice', 'Bob', None, 'Diana', 'Eve'],
    'Age': [25, 30, 35, None, 28],
    'City': ['New York', 'London', 'Tokyo', 'Paris', ''],
    'Salary': [50000, 60000, 70000, 55000, None]
})

print("Dirty data:")
print(dirty_data)
print(f"\nMissing values:\n{dirty_data.isnull().sum()}")

# Handling missing values
print("\n=== Handling Missing Values ===")
# Drop rows with any missing values
cleaned_drop = dirty_data.dropna()
print("After dropping rows with missing values:")
print(cleaned_drop)

# Fill missing values
dirty_data_filled = dirty_data.copy()
dirty_data_filled['Age'].fillna(dirty_data_filled['Age'].mean(), inplace=True)
dirty_data_filled['Salary'].fillna(dirty_data_filled['Salary'].median(), inplace=True)
dirty_data_filled['Name'].fillna('Unknown', inplace=True)
dirty_data_filled['City'].replace('', 'Unknown', inplace=True)

print("\nAfter filling missing values:")
print(dirty_data_filled)

# Data transformation
print("\n=== Data Transformation ===")
df_clean = dirty_data_filled.copy()

# String operations
df_clean['Name_Upper'] = df_clean['Name'].str.upper()
df_clean['City_Length'] = df_clean['City'].str.len()

print("With string operations:")
print(df_clean[['Name', 'Name_Upper', 'City', 'City_Length']])

# Groupby operations
print("\n=== GroupBy Operations ===")
sales_data = pd.DataFrame({
    'Region': ['North', 'South', 'North', 'South', 'East', 'West', 'East', 'West'] * 2,
    'Product': ['A', 'A', 'B', 'B', 'A', 'B', 'A', 'B'] * 2,
    'Sales': np.random.randint(1000, 5000, 16),
    'Month': ['Jan', 'Jan', 'Jan', 'Jan', 'Feb', 'Feb', 'Feb', 'Feb'] * 2
})

print("Sales data:")
print(sales_data)

# Group by region
region_summary = sales_data.groupby('Region')['Sales'].agg(['sum', 'mean', 'count'])
print("\nSales by region:")
print(region_summary)

# Group by multiple columns
multi_group = sales_data.groupby(['Region', 'Product'])['Sales'].sum()
print("\nSales by region and product:")
print(multi_group)

# Pivot tables
print("\n=== Pivot Tables ===")
pivot_table = sales_data.pivot_table(
    values='Sales',
    index='Region',
    columns='Product',
    aggfunc='sum',
    fill_value=0
)
print("Pivot table:")
print(pivot_table)
```

### Data Analysis Examples

```python
# Sales analysis example
print("\n=== Sales Analysis Example ===")

# Create comprehensive sales data
np.random.seed(42)
n_customers = 1000

sales_data = pd.DataFrame({
    'customer_id': range(1, n_customers + 1),
    'age': np.random.randint(18, 80, n_customers),
    'income': np.random.normal(50000, 15000, n_customers),
    'region': np.random.choice(['North', 'South', 'East', 'West'], n_customers),
    'product_category': np.random.choice(['Electronics', 'Clothing', 'Books', 'Home'], n_customers),
    'purchase_amount': np.random.exponential(100, n_customers),
    'purchase_date': pd.date_range('2023-01-01', periods=n_customers, freq='H')
})

# Ensure income is positive
sales_data['income'] = np.abs(sales_data['income'])

print(f"Dataset shape: {sales_data.shape}")
print(f"Columns: {sales_data.columns.tolist()}")
print(f"\nFirst 5 rows:")
print(sales_data.head())

# Basic analysis
print("\n=== Basic Analysis ===")
print("Descriptive statistics:")
print(sales_data.describe())

print(f"\nTotal revenue: ${sales_data['purchase_amount'].sum():,.2f}")
print(f"Average purchase: ${sales_data['purchase_amount'].mean():.2f}")
print(f"Number of unique customers: {sales_data['customer_id'].nunique()}")

# Regional analysis
print("\n=== Regional Analysis ===")
regional_stats = sales_data.groupby('region').agg({
    'purchase_amount': ['sum', 'mean', 'count'],
    'income': 'mean',
    'age': 'mean'
}).round(2)

print("Regional statistics:")
print(regional_stats)

# Product category analysis
print("\n=== Product Category Analysis ===")
category_stats = sales_data.groupby('product_category')['purchase_amount'].agg([
    'sum', 'mean', 'count'
]).round(2)

print("Product category statistics:")
print(category_stats)

# Customer segmentation
print("\n=== Customer Segmentation ===")
# Create age groups
sales_data['age_group'] = pd.cut(
    sales_data['age'],
    bins=[0, 25, 35, 50, 100],
    labels=['18-25', '26-35', '36-50', '50+']
)

# Create income groups
sales_data['income_group'] = pd.qcut(
    sales_data['income'],
    q=3,
    labels=['Low', 'Medium', 'High']
)

# Analyze by segments
segment_analysis = sales_data.groupby(['age_group', 'income_group']).agg({
    'purchase_amount': ['mean', 'sum', 'count']
}).round(2)

print("Customer segment analysis:")
print(segment_analysis)

# Time series analysis
print("\n=== Time Series Analysis ===")
# Set purchase_date as index
sales_ts = sales_data.set_index('purchase_date')

# Daily sales
daily_sales = sales_ts['purchase_amount'].resample('D').sum()
print("Daily sales (first 10 days):")
print(daily_sales.head(10))

# Monthly sales by region
monthly_sales = sales_ts.groupby([pd.Grouper(freq='M'), 'region'])['purchase_amount'].sum()
print("\nMonthly sales by region:")
print(monthly_sales.head(10))

# Correlation analysis
print("\n=== Correlation Analysis ===")
numeric_cols = ['age', 'income', 'purchase_amount']
correlation_matrix = sales_data[numeric_cols].corr()
print("Correlation matrix:")
print(correlation_matrix)
```

## Advanced Data Manipulation

### Merging and Joining

```python
# Creating sample datasets for merging
print("\n=== Data Merging ===")

customers = pd.DataFrame({
    'customer_id': [1, 2, 3, 4, 5],
    'name': ['Alice', 'Bob', 'Charlie', 'Diana', 'Eve'],
    'city': ['New York', 'London', 'Tokyo', 'Paris', 'Berlin']
})

orders = pd.DataFrame({
    'order_id': [101, 102, 103, 104, 105, 106],
    'customer_id': [1, 2, 1, 3, 4, 5],
    'product': ['Laptop', 'Phone', 'Tablet', 'Laptop', 'Phone', 'Tablet'],
    'amount': [1000, 500, 300, 1200, 600, 350]
})

print("Customers table:")
print(customers)
print("\nOrders table:")
print(orders)

# Inner join
inner_join = pd.merge(customers, orders, on='customer_id', how='inner')
print("\nInner join:")
print(inner_join)

# Left join
left_join = pd.merge(customers, orders, on='customer_id', how='left')
print("\nLeft join:")
print(left_join)

# Right join
right_join = pd.merge(customers, orders, on='customer_id', how='right')
print("\nRight join:")
print(right_join)

# Outer join
outer_join = pd.merge(customers, orders, on='customer_id', how='outer')
print("\nOuter join:")
print(outer_join)

# Concatenation
print("\n=== Data Concatenation ===")
df1 = pd.DataFrame({'A': [1, 2], 'B': [3, 4]})
df2 = pd.DataFrame({'A': [5, 6], 'B': [7, 8]})
df3 = pd.DataFrame({'C': [9, 10], 'D': [11, 12]})

print("DataFrame 1:")
print(df1)
print("\nDataFrame 2:")
print(df2)
print("\nDataFrame 3:")
print(df3)

# Vertical concatenation
vertical_concat = pd.concat([df1, df2], ignore_index=True)
print("\nVertical concatenation:")
print(vertical_concat)

# Horizontal concatenation
horizontal_concat = pd.concat([df1, df3], axis=1)
print("\nHorizontal concatenation:")
print(horizontal_concat)
```

### Data Transformation and Feature Engineering

```python
# Feature engineering example
print("\n=== Feature Engineering ===")

# Create sample data
feature_data = pd.DataFrame({
    'date': pd.date_range('2023-01-01', periods=100, freq='D'),
    'sales': np.random.randint(1000, 5000, 100),
    'temperature': np.random.normal(20, 10, 100),
    'rainfall': np.random.exponential(2, 100)
})

print("Original data (first 10 rows):")
print(feature_data.head(10))

# Extract date features
feature_data['year'] = feature_data['date'].dt.year
feature_data['month'] = feature_data['date'].dt.month
feature_data['day_of_week'] = feature_data['date'].dt.dayofweek
feature_data['is_weekend'] = feature_data['day_of_week'].isin([5, 6])

print("\nWith date features:")
print(feature_data[['date', 'year', 'month', 'day_of_week', 'is_weekend']].head())

# Create lag features
feature_data['sales_lag1'] = feature_data['sales'].shift(1)
feature_data['sales_lag7'] = feature_data['sales'].shift(7)

# Rolling window features
feature_data['sales_ma7'] = feature_data['sales'].rolling(window=7).mean()
feature_data['sales_std7'] = feature_data['sales'].rolling(window=7).std()

print("\nWith lag and rolling features:")
print(feature_data[['sales', 'sales_lag1', 'sales_lag7', 'sales_ma7', 'sales_std7']].head(10))

# Create interaction features
feature_data['temp_rain_interaction'] = feature_data['temperature'] * feature_data['rainfall']
feature_data['sales_temp_ratio'] = feature_data['sales'] / (feature_data['temperature'] + 1)

# Create categorical features
feature_data['temp_category'] = pd.cut(
    feature_data['temperature'],
    bins=[-np.inf, 10, 20, 30, np.inf],
    labels=['Cold', 'Cool', 'Warm', 'Hot']
)

feature_data['rain_category'] = pd.cut(
    feature_data['rainfall'],
    bins=[0, 1, 3, np.inf],
    labels=['Light', 'Moderate', 'Heavy']
)

print("\nWith categorical features:")
print(feature_data[['temperature', 'temp_category', 'rainfall', 'rain_category']].head())

# One-hot encoding
categorical_features = pd.get_dummies(
    feature_data[['temp_category', 'rain_category']],
    prefix=['temp', 'rain']
)

print("\nOne-hot encoded features:")
print(categorical_features.head())

# Combine all features
final_features = pd.concat([feature_data, categorical_features], axis=1)
print(f"\nFinal dataset shape: {final_features.shape}")
print(f"Final columns: {final_features.columns.tolist()}")
```

## Data Visualization with Pandas

```python
import matplotlib.pyplot as plt

# Set up plotting
plt.style.use('default')

# Sales trend analysis
print("\n=== Data Visualization ===")

# Create time series data
dates = pd.date_range('2023-01-01', periods=365, freq='D')
trend = np.sin(np.arange(365) * 2 * np.pi / 365) * 1000 + 3000
noise = np.random.normal(0, 200, 365)
sales_trend = trend + noise

sales_df = pd.DataFrame({
    'date': dates,
    'sales': sales_trend
})

# Plot sales trend
plt.figure(figsize=(12, 6))
plt.subplot(2, 2, 1)
sales_df.set_index('date')['sales'].plot(title='Daily Sales Trend')
plt.ylabel('Sales ($)')

# Monthly sales bar chart
monthly_sales = sales_df.set_index('date').resample('M')['sales'].sum()
plt.subplot(2, 2, 2)
monthly_sales.plot(kind='bar', title='Monthly Sales')
plt.xticks(rotation=45)

# Sales distribution histogram
plt.subplot(2, 2, 3)
sales_df['sales'].hist(bins=30, title='Sales Distribution')
plt.xlabel('Sales ($)')
plt.ylabel('Frequency')

# Sales box plot by month
sales_df['month'] = sales_df['date'].dt.month
plt.subplot(2, 2, 4)
sales_df.boxplot(column='sales', by='month', ax=plt.gca())
plt.title('Sales by Month')
plt.suptitle('')  # Remove default title

plt.tight_layout()
plt.show()

# Correlation heatmap
print("\n=== Correlation Analysis ===")
correlation_data = pd.DataFrame({
    'sales': sales_trend,
    'temperature': np.random.normal(20, 10, 365),
    'rainfall': np.random.exponential(2, 365),
    'day_of_week': np.tile(range(7), 53)[:365]
})

correlation_matrix = correlation_data.corr()
print("Correlation matrix:")
print(correlation_matrix)

# Plot correlation heatmap
plt.figure(figsize=(8, 6))
plt.imshow(correlation_matrix, cmap='coolwarm', aspect='auto')
plt.colorbar()
plt.xticks(range(len(correlation_matrix.columns)), correlation_matrix.columns)
plt.yticks(range(len(correlation_matrix.columns)), correlation_matrix.columns)
plt.title('Correlation Heatmap')

# Add correlation values to the plot
for i in range(len(correlation_matrix.columns)):
    for j in range(len(correlation_matrix.columns)):
        plt.text(j, i, f'{correlation_matrix.iloc[i, j]:.2f}',
                ha='center', va='center', color='black')

plt.show()
```

## Performance Optimization

```python
# Performance comparison
print("\n=== Performance Optimization ===")

# Create large dataset
large_df = pd.DataFrame({
    'A': np.random.randn(100000),
    'B': np.random.randn(100000),
    'C': np.random.randn(100000),
    'D': np.random.randn(100000)
})

print(f"Large dataset shape: {large_df.shape}")

# Vectorized operations vs loops
import time

# Vectorized operation
start_time = time.time()
vectorized_result = large_df['A'] + large_df['B'] + large_df['C']
vectorized_time = time.time() - start_time

# Loop operation (slower)
start_time = time.time()
loop_result = []
for i in range(len(large_df)):
    loop_result.append(large_df['A'].iloc[i] + large_df['B'].iloc[i] + large_df['C'].iloc[i])
loop_time = time.time() - start_time

print(f"Vectorized operation time: {vectorized_time:.4f} seconds")
print(f"Loop operation time: {loop_time:.4f} seconds")
print(f"Speedup: {loop_time / vectorized_time:.2f}x")

# Memory optimization
print("\n=== Memory Optimization ===")
print(f"Original memory usage: {large_df.memory_usage(deep=True).sum() / 1024**2:.2f} MB")

# Optimize data types
optimized_df = large_df.copy()
for col in optimized_df.columns:
    if optimized_df[col].dtype == 'float64':
        optimized_df[col] = pd.to_numeric(optimized_df[col], downcast='float')
    elif optimized_df[col].dtype == 'int64':
        optimized_df[col] = pd.to_numeric(optimized_df[col], downcast='integer')

print(f"Optimized memory usage: {optimized_df.memory_usage(deep=True).sum() / 1024**2:.2f} MB")
print(f"Memory reduction: {(1 - optimized_df.memory_usage(deep=True).sum() / large_df.memory_usage(deep=True).sum()) * 100:.1f}%")

# Chunk processing for large files
print("\n=== Chunk Processing ===")
def process_chunk(chunk):
    """Process a chunk of data."""
    return chunk.groupby('A')['B'].sum()

# Simulate chunk processing
chunk_size = 10000
chunks_processed = 0
total_result = 0

for chunk in pd.read_csv('large_file.csv', chunksize=chunk_size):
    result = process_chunk(chunk)
    total_result += result.sum()
    chunks_processed += 1
    
    if chunks_processed >= 5:  # Limit for demo
        break

print(f"Processed {chunks_processed} chunks")
print(f"Total result: {total_result}")
```

## Key Takeaways

1. **NumPy** provides efficient numerical computing with arrays
2. **Pandas** offers powerful data manipulation and analysis tools
3. **Data cleaning** is essential for reliable analysis
4. **GroupBy operations** enable powerful data aggregation
5. **Merging and joining** combine datasets effectively
6. **Feature engineering** creates meaningful variables for analysis
7. **Vectorized operations** are much faster than loops
8. **Memory optimization** improves performance with large datasets

## Next Steps

In the next lesson, we'll explore Algorithms and Problem Solving - sorting algorithms, searching techniques, recursion, and dynamic programming for efficient problem-solving.
