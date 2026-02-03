# Lesson 9: MySQL Database Functions with SQLAlchemy

## Learning Objectives
- Understand MySQL database functions and their categories
- Learn how to use database functions through SQLAlchemy ORM and Core
- Master date and time manipulation functions
- Practice string manipulation and mathematical functions
- Implement conditional functions and custom expressions
- Optimize function usage for better performance

## Table of Contents
1. [Introduction to Database Functions](#introduction-to-database-functions)
2. [SQLAlchemy Function Usage](#sqlalchemy-function-usage)
3. [Date and Time Functions](#date-and-time-functions)
4. [String Manipulation Functions](#string-manipulation-functions)
5. [Mathematical Functions](#mathematical-functions)
6. [Conditional Functions](#conditional-functions)
7. [Aggregate Functions](#aggregate-functions)
8. [Custom Function Creation](#custom-function-creation)
9. [Performance Optimization](#performance-optimization)
10. [Best Practices](#best-practices)

## Introduction to Database Functions

### What are Database Functions?

Database functions are built-in operations that perform specific tasks on data. They can:
- **Transform data** (format, convert, calculate)
- **Extract information** (dates, substrings, patterns)
- **Perform calculations** (mathematical operations)
- **Make decisions** (conditional logic)
- **Aggregate data** (sum, count, average)

### Benefits of Using Database Functions

1. **Performance**: Functions execute on the database server
2. **Consistency**: Standardized operations across applications
3. **Efficiency**: Reduce data transfer between application and database
4. **Flexibility**: Complex operations in single expressions

### SQLAlchemy Function Categories

```python
from sqlalchemy import func

# Date and Time Functions
func.current_date()
func.current_time()
func.current_timestamp()
func.year(column)
func.month(column)
func.day(column)

# String Functions
func.concat(string1, string2)
func.upper(column)
func.lower(column)
func.length(column)
func.substring(column, start, length)

# Mathematical Functions
func.round(number, decimals)
func.ceil(number)
func.floor(number)
func.abs(number)
func.power(base, exponent)

# Conditional Functions
func.if(condition, true_value, false_value)
func.ifnull(column, default_value)
func.coalesce(value1, value2, ...)
```

## SQLAlchemy Function Usage

### Using SQLAlchemy Core Functions

```python
from sqlalchemy import func, text

# Basic function usage
result = session.query(func.current_date()).first()
print(f"Current date: {result[0]}")

# Function with columns
result = session.query(
    User.username,
    func.upper(User.username).label('upper_username')
).all()

# Complex function expressions
result = session.query(
    Order.order_id,
    func.concat('Order #', Order.order_number).label('order_label')
).all()
```

### Using SQLAlchemy ORM with Functions

```python
# Functions in ORM queries
users = session.query(User).filter(
    func.length(User.username) > 5
).all()

# Functions in select expressions
result = session.query(
    User,
    func.current_timestamp().label('query_time')
).all()
```

### Function Aliases and Labels

```python
# Create function aliases
current_time = func.current_timestamp().label('current_time')
user_count = func.count(User.user_id).label('total_users')

result = session.query(current_time, user_count).first()
print(f"Query executed at: {result.current_time}")
print(f"Total users: {result.total_users}")
```

## Date and Time Functions

### Current Date and Time Functions

```python
# Get current date and time
current_date = session.query(func.current_date()).scalar()
current_time = session.query(func.current_time()).scalar()
current_timestamp = session.query(func.current_timestamp()).scalar()

print(f"Current Date: {current_date}")
print(f"Current Time: {current_time}")
print(f"Current Timestamp: {current_timestamp}")
```

### Date Extraction Functions

```python
# Extract components from dates
result = session.query(
    Order.order_id,
    Order.order_date,
    func.year(Order.order_date).label('order_year'),
    func.month(Order.order_date).label('order_month'),
    func.day(Order.order_date).label('order_day'),
    func.dayofweek(Order.order_date).label('day_of_week'),
    func.weekday(Order.order_date).label('weekday_number')
).limit(5).all()

for order in result:
    print(f"Order {order.order_id}: {order.order_year}-{order.order_month}-{order.order_day}")
    print(f"  Day of week: {order.day_of_week}, Weekday: {order.weekday_number}")
```

### Date Arithmetic Functions

```python
# Calculate differences between dates
result = session.query(
    Order.order_id,
    Order.order_date,
    func.datediff(func.current_date(), Order.order_date).label('days_ago'),
    func.timestampdiff(text('DAY'), Order.order_date, func.current_timestamp()).label('days_ago_alt')
).limit(5).all()

# Add/subtract time intervals
result = session.query(
    Order.order_id,
    Order.order_date,
    func.date_add(Order.order_date, text('INTERVAL 30 DAY')).label('future_date'),
    func.date_sub(Order.order_date, text('INTERVAL 7 DAY')).label('week_ago')
).limit(5).all()
```

### Date Formatting Functions

```python
# Format dates in different ways
result = session.query(
    Order.order_id,
    Order.order_date,
    func.date_format(Order.order_date, '%Y-%m-%d').label('iso_date'),
    func.date_format(Order.order_date, '%M %d, %Y').label('readable_date'),
    func.date_format(Order.order_date, '%W, %M %d').label('day_and_date'),
    func.date_format(Order.order_date, '%H:%i:%s').label('time_only')
).limit(5).all()

for order in result:
    print(f"Order {order.order_id}:")
    print(f"  ISO: {order.iso_date}")
    print(f"  Readable: {order.readable_date}")
    print(f"  Day: {order.day_and_date}")
    print(f"  Time: {order.time_only}")
```

## String Manipulation Functions

### String Concatenation

```python
# Basic concatenation
result = session.query(
    User.user_id,
    User.first_name,
    User.last_name,
    func.concat(User.first_name, ' ', User.last_name).label('full_name')
).limit(5).all()

# Concatenation with separator
result = session.query(
    User.user_id,
    func.concat_ws(' - ', User.first_name, User.last_name, User.email).label('user_info')
).limit(5).all()

# Concatenation with conditions
result = session.query(
    User.user_id,
    func.concat(
        User.first_name,
        ' ',
        User.last_name,
        ' (',
        User.username,
        ')'
    ).label('display_name')
).limit(5).all()
```

### String Case Functions

```python
# Convert case
result = session.query(
    User.user_id,
    User.username,
    func.upper(User.username).label('upper_username'),
    func.lower(User.username).label('lower_username')
).limit(5).all()

# Title case (using combination of functions)
result = session.query(
    User.user_id,
    User.first_name,
    func.concat(
        func.upper(func.left(User.first_name, 1)),
        func.lower(func.substring(User.first_name, 2))
    ).label('title_case_name')
).limit(5).all()
```

### String Length and Substring Functions

```python
# String length and position
result = session.query(
    User.user_id,
    User.email,
    func.length(User.email).label('email_length'),
    func.locate('@', User.email).label('at_position'),
    func.locate('.', User.email).label('dot_position')
).limit(5).all()

# Substring extraction
result = session.query(
    User.user_id,
    User.email,
    func.substring(User.email, 1, 5).label('email_start'),
    func.left(User.email, 10).label('email_left'),
    func.right(User.email, 10).label('email_right'),
    func.substring(User.email, func.locate('@', User.email) + 1).label('domain')
).limit(5).all()
```

### String Trimming and Cleaning

```python
# Trimming functions
sample_text = "   Hello World   "

result = session.query(
    func.trim(sample_text).label('trimmed'),
    func.ltrim(sample_text).label('left_trimmed'),
    func.rtrim(sample_text).label('right_trimmed')
).first()

print(f"Original: '{sample_text}'")
print(f"Trimmed: '{result.trimmed}'")
print(f"Left trimmed: '{result.left_trimmed}'")
print(f"Right trimmed: '{result.right_trimmed}'")
```

### String Replacement Functions

```python
# Replace characters
result = session.query(
    User.user_id,
    User.email,
    func.replace(User.email, '@', ' [at] ').label('replaced_email'),
    func.replace(User.username, '_', ' ').label('formatted_username')
).limit(5).all()

# Replace multiple patterns
result = session.query(
    User.user_id,
    User.email,
    func.replace(
        func.replace(User.email, '@', ' [at] '),
        '.',
        ' [dot] '
    ).label('formatted_email')
).limit(5).all()
```

## Mathematical Functions

### Rounding Functions

```python
# Rounding operations
result = session.query(
    Order.order_id,
    Order.total_amount,
    func.round(Order.total_amount, 1).label('rounded_1_decimal'),
    func.round(Order.total_amount, 0).label('rounded_whole'),
    func.ceil(Order.total_amount).label('ceiling'),
    func.floor(Order.total_amount).label('floor')
).limit(5).all()

for order in result:
    print(f"Order {order.order_id}: {order.total_amount}")
    print(f"  Rounded (1): {order.rounded_1_decimal}")
    print(f"  Rounded (0): {order.rounded_whole}")
    print(f"  Ceiling: {order.ceiling}")
    print(f"  Floor: {order.floor}")
```

### Absolute Value and Sign Functions

```python
# Absolute value and sign
sample_values = [-15.5, 10.2, -3.7, 0, 25.8]

for value in sample_values:
    result = session.query(
        func.abs(value).label('absolute'),
        func.sign(value).label('sign')
    ).first()
    
    print(f"Value: {value} -> Absolute: {result.absolute}, Sign: {result.sign}")
```

### Power and Square Root Functions

```python
# Power and square root operations
result = session.query(
    func.power(2, 3).label('power_2_3'),
    func.power(10, 2).label('power_10_2'),
    func.sqrt(16).label('sqrt_16'),
    func.sqrt(Order.total_amount).label('amount_sqrt')
).limit(3).all()

for row in result:
    print(f"2^3 = {row.power_2_3}")
    print(f"10^2 = {row.power_10_2}")
    print(f"√16 = {row.sqrt_16}")
    print(f"√Amount = {row.amount_sqrt}")
```

### Modulo and Random Functions

```python
# Modulo operations
result = session.query(
    func.mod(10, 3).label('mod_10_3'),
    func.mod(15, 4).label('mod_15_4'),
    func.mod(Order.total_amount, 10).label('amount_mod_10')
).limit(3).all()

# Random numbers
result = session.query(
    func.rand().label('random_1'),
    func.rand().label('random_2'),
    func.rand().label('random_3')
).first()

print(f"10 MOD 3 = {result.mod_10_3}")
print(f"15 MOD 4 = {result.mod_15_4}")
print(f"Random numbers: {result.random_1:.6f}, {result.random_2:.6f}, {result.random_3:.6f}")
```

## Conditional Functions

### IF Function

```python
# Basic IF function
result = session.query(
    Order.order_id,
    Order.total_amount,
    func.if_(Order.total_amount > 100, 'High Value', 'Low Value').label('value_category'),
    func.if_(Order.status == 'delivered', 'Completed', 'In Progress').label('completion_status')
).limit(5).all()

# Nested IF functions
result = session.query(
    Order.order_id,
    Order.total_amount,
    func.if_(
        Order.total_amount > 200,
        'Premium',
        func.if_(
            Order.total_amount > 100,
            'High',
            'Standard'
        )
    ).label('tier')
).limit(5).all()
```

### IFNULL and NULLIF Functions

```python
# IFNULL function (returns default if NULL)
result = session.query(
    User.user_id,
    User.first_name,
    func.ifnull(User.first_name, 'Unknown').label('display_name')
).limit(5).all()

# NULLIF function (returns NULL if values are equal)
result = session.query(
    User.user_id,
    User.username,
    func.nullif(User.username, 'admin').label('nullified_username')
).limit(5).all()
```

### CASE Statements

```python
from sqlalchemy import case

# Simple CASE statement
result = session.query(
    Order.order_id,
    Order.total_amount,
    case(
        (Order.total_amount < 50, 'Low'),
        (Order.total_amount < 100, 'Medium'),
        (Order.total_amount < 200, 'High'),
        else_='Very High'
    ).label('amount_category')
).limit(5).all()

# Complex CASE with multiple conditions
result = session.query(
    Order.order_id,
    Order.total_amount,
    Order.status,
    case(
        (and_(Order.total_amount > 200, Order.status == 'delivered'), 'Premium Delivered'),
        (Order.total_amount > 100, 'High Value'),
        (Order.status == 'delivered', 'Delivered'),
        else_='Standard'
    ).label('order_category')
).limit(5).all()
```

### COALESCE Function

```python
# COALESCE returns first non-NULL value
result = session.query(
    User.user_id,
    User.first_name,
    User.last_name,
    func.coalesce(User.first_name, User.last_name, 'Unknown').label('display_name')
).limit(5).all()

# COALESCE with multiple columns
result = session.query(
    User.user_id,
    func.coalesce(User.email, User.username, 'No Contact').label('contact_info')
).limit(5).all()
```

## Aggregate Functions

### Basic Aggregate Functions

```python
# Standard aggregate functions
result = session.query(
    func.count(Order.order_id).label('total_orders'),
    func.sum(Order.total_amount).label('total_amount'),
    func.avg(Order.total_amount).label('average_amount'),
    func.min(Order.total_amount).label('min_amount'),
    func.max(Order.total_amount).label('max_amount')
).first()

print(f"Total Orders: {result.total_orders}")
print(f"Total Amount: {result.total_amount}")
print(f"Average Amount: {result.average_amount:.2f}")
print(f"Min Amount: {result.min_amount}")
print(f"Max Amount: {result.max_amount}")
```

### Conditional Aggregates

```python
# Count with conditions
result = session.query(
    func.count(Order.order_id).label('total_orders'),
    func.count(func.if_(Order.status == 'delivered', 1, None)).label('delivered_orders'),
    func.sum(func.if_(Order.status == 'delivered', Order.total_amount, 0)).label('delivered_amount')
).first()

print(f"Total Orders: {result.total_orders}")
print(f"Delivered Orders: {result.delivered_orders}")
print(f"Delivered Amount: {result.delivered_amount}")
```

### Grouped Aggregates

```python
# Group by with aggregates
result = session.query(
    Order.status,
    func.count(Order.order_id).label('order_count'),
    func.sum(Order.total_amount).label('total_amount'),
    func.avg(Order.total_amount).label('average_amount')
).group_by(Order.status).all()

for row in result:
    print(f"Status: {row.status}")
    print(f"  Count: {row.order_count}")
    print(f"  Total: {row.total_amount}")
    print(f"  Average: {row.average_amount:.2f}")
```

## Custom Function Creation

### Creating Function Expressions

```python
# Custom function to calculate order age
order_age_days = func.datediff(func.current_date(), Order.order_date)

result = session.query(
    Order.order_id,
    Order.order_date,
    order_age_days.label('age_days')
).limit(5).all()

# Custom function to format currency
formatted_amount = func.concat('$', func.format(Order.total_amount, 2))

result = session.query(
    Order.order_id,
    Order.total_amount,
    formatted_amount.label('formatted_amount')
).limit(5).all()
```

### Complex Function Combinations

```python
# Complex function to generate order summary
order_summary = func.concat(
    'Order #', Order.order_number,
    ' - $', func.format(Order.total_amount, 2),
    ' - ', func.upper(Order.status)
)

result = session.query(
    Order.order_id,
    order_summary.label('order_summary')
).limit(5).all()

# Function with conditional logic
order_category = case(
    (Order.total_amount > 200, 'Premium'),
    (Order.total_amount > 100, 'High'),
    (Order.total_amount > 50, 'Medium'),
    else_='Low'
)

result = session.query(
    Order.order_id,
    Order.total_amount,
    order_category.label('category')
).limit(5).all()
```

### Function Aliases and Reusability

```python
# Create reusable function aliases
def create_currency_formatter(amount_column):
    return func.concat('$', func.format(amount_column, 2))

def create_date_formatter(date_column, format_string='%Y-%m-%d'):
    return func.date_format(date_column, format_string)

# Use the aliases
currency_formatter = create_currency_formatter(Order.total_amount)
date_formatter = create_date_formatter(Order.order_date, '%M %d, %Y')

result = session.query(
    Order.order_id,
    currency_formatter.label('formatted_amount'),
    date_formatter.label('formatted_date')
).limit(5).all()
```

## Performance Optimization

### Efficient Function Usage

```python
# Good: Use functions in SELECT, not WHERE
efficient_query = session.query(
    Order.order_id,
    Order.order_date,
    func.year(Order.order_date).label('order_year')
).filter(
    Order.order_date >= '2023-01-01'  # Use indexed column in WHERE
).limit(10)

# Avoid: Functions in WHERE clauses when possible
# This is less efficient:
# .filter(func.year(Order.order_date) == 2023)

# Better: Use date ranges
# .filter(Order.order_date >= '2023-01-01')
# .filter(Order.order_date < '2024-01-01')
```

### Index-Friendly Function Usage

```python
# Use functions that can utilize indexes
result = session.query(
    Order.order_id,
    Order.total_amount
).filter(
    Order.order_date >= func.current_date() - text('INTERVAL 30 DAY')
).all()

# Avoid functions that prevent index usage
# This prevents index usage on order_date:
# .filter(func.date_format(Order.order_date, '%Y-%m') == '2023-01')
```

### Function Caching and Optimization

```python
# Cache frequently used functions
current_date = func.current_date()
current_timestamp = func.current_timestamp()

# Use cached functions in multiple queries
recent_orders = session.query(Order).filter(
    Order.order_date >= current_date - text('INTERVAL 7 DAY')
).all()

old_orders = session.query(Order).filter(
    Order.order_date < current_date - text('INTERVAL 30 DAY')
).all()
```

## Best Practices

### 1. Function Selection

```python
# Choose appropriate functions for the task
# For date formatting:
formatted_date = func.date_format(Order.order_date, '%Y-%m-%d')

# For string concatenation:
full_name = func.concat(User.first_name, ' ', User.last_name)

# For mathematical operations:
rounded_amount = func.round(Order.total_amount, 2)
```

### 2. Error Handling

```python
# Handle potential NULL values
result = session.query(
    User.user_id,
    func.ifnull(User.first_name, 'Unknown').label('safe_name'),
    func.coalesce(User.email, User.username, 'No Contact').label('contact')
).all()
```

### 3. Performance Considerations

```python
# Use functions efficiently
# Good: Functions in SELECT
result = session.query(
    Order.order_id,
    func.year(Order.order_date).label('year')
).filter(
    Order.status == 'delivered'  # Simple condition in WHERE
).all()

# Avoid: Complex functions in WHERE
# result = session.query(Order).filter(
#     func.year(Order.order_date) == 2023
# ).all()
```

### 4. Documentation and Readability

```python
# Use descriptive labels and aliases
order_age_days = func.datediff(func.current_date(), Order.order_date).label('age_in_days')
formatted_amount = func.concat('$', func.format(Order.total_amount, 2)).label('currency_amount')

result = session.query(
    Order.order_id,
    order_age_days,
    formatted_amount
).limit(5).all()
```

### 5. Testing and Validation

```python
# Test functions with known data
test_result = session.query(
    func.current_date().label('current_date'),
    func.current_timestamp().label('current_timestamp'),
    func.length('Hello World').label('string_length'),
    func.round(3.14159, 2).label('rounded_pi')
).first()

print(f"Current Date: {test_result.current_date}")
print(f"Current Timestamp: {test_result.current_timestamp}")
print(f"String Length: {test_result.string_length}")
print(f"Rounded Pi: {test_result.rounded_pi}")
```

## Hands-on Exercise

### Exercise 1: Date Functions
Create queries that:
1. Find orders from the last 30 days
2. Calculate the age of each order in days
3. Format order dates in different ways
4. Find orders by day of the week

### Exercise 2: String Functions
Create queries that:
1. Generate full names from first and last names
2. Extract domains from email addresses
3. Format usernames in different cases
4. Clean and format user data

### Exercise 3: Mathematical Functions
Create queries that:
1. Calculate order totals with tax
2. Round amounts to different decimal places
3. Calculate percentages and ratios
4. Generate random order numbers

### Exercise 4: Conditional Functions
Create queries that:
1. Categorize orders by amount ranges
2. Handle NULL values gracefully
3. Create complex conditional logic
4. Generate status descriptions

## Key Takeaways

- **Use SQLAlchemy functions** instead of raw SQL for better maintainability
- **Optimize function usage** by placing them in SELECT clauses when possible
- **Handle NULL values** appropriately with IFNULL, COALESCE, or CASE
- **Combine functions** to create complex expressions
- **Test functions** with known data to ensure correctness
- **Document function usage** with descriptive labels and aliases
- **Consider performance** implications of function usage

## Next Steps

In the next lesson, we'll learn about advanced SQL features including views, stored procedures, and triggers.

## Practice Questions

1. How do you use date functions to find records from a specific time period?
2. What's the difference between IFNULL and COALESCE functions?
3. How can you optimize queries that use functions in WHERE clauses?
4. When should you use CASE statements versus IF functions?
5. How do you create reusable function expressions in SQLAlchemy?
