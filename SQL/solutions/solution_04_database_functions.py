"""
====================================================================
Solution 4: MySQL Database Functions with SQLAlchemy - Complete Solutions
====================================================================
This file contains complete, commented solutions for all exercises
in exercise_04_database_functions.sql. Each solution demonstrates:
1. Proper use of SQLAlchemy functions (not raw SQL)
2. Date and time manipulation functions
3. String manipulation and formatting functions
4. Mathematical and conditional functions
5. Aggregate functions and custom expressions
6. Performance optimization techniques
7. Error handling and validation
8. Real-world function usage scenarios
====================================================================
"""

# Import required libraries
from sqlalchemy import create_engine, Column, Integer, String, Text, DECIMAL, TIMESTAMP, Boolean, ForeignKey, Enum, JSON, Index, func, case, text, and_, or_, desc, asc
from sqlalchemy.ext.declarative import declarative_base
from sqlalchemy.orm import sessionmaker, relationship
from sqlalchemy.sql import func as sql_func
from datetime import datetime, date, timedelta
import os
from dotenv import load_dotenv

# Load environment variables
load_dotenv()

# Create base class for declarative models
Base = declarative_base()

class User(Base):
    """User model for function demonstrations"""
    __tablename__ = 'users'
    
    user_id = Column(Integer, primary_key=True, autoincrement=True)
    username = Column(String(50), unique=True, nullable=False)
    email = Column(String(100), unique=True, nullable=False)
    first_name = Column(String(50), nullable=False)
    last_name = Column(String(50), nullable=False)
    created_at = Column(TIMESTAMP, default=func.current_timestamp())
    is_active = Column(Boolean, default=True)
    
    # Relationships
    orders = relationship("Order", back_populates="user")

class Order(Base):
    """Order model for function demonstrations"""
    __tablename__ = 'orders'
    
    order_id = Column(Integer, primary_key=True, autoincrement=True)
    user_id = Column(Integer, ForeignKey('users.user_id'), nullable=False)
    order_number = Column(String(20), unique=True, nullable=False)
    total_amount = Column(DECIMAL(10, 2), nullable=False)
    status = Column(Enum('pending', 'processing', 'shipped', 'delivered', 'cancelled'), default='pending')
    order_date = Column(TIMESTAMP, default=func.current_timestamp())
    
    # Relationships
    user = relationship("User", back_populates="orders")

def get_session():
    """Create database session for demonstrations"""
    host = os.getenv('DB_HOST', 'localhost')
    port = int(os.getenv('DB_PORT', 3306))
    user = os.getenv('DB_USER', 'student')
    password = os.getenv('DB_PASSWORD', 'password123')
    database = os.getenv('DB_NAME', 'learning_db')
    
    connection_string = f"mysql+pymysql://{user}:{password}@{host}:{port}/{database}"
    engine = create_engine(connection_string)
    Session = sessionmaker(bind=engine)
    return Session()

# ===================================================================
# EXERCISE 4.1: DATE AND TIME FUNCTIONS - SOLUTIONS
# ===================================================================

def exercise_4_1_date_time_functions():
    """
    Complete solutions for date and time function exercises.
    """
    print("=== Exercise 4.1: Date and Time Functions Solutions ===\n")
    
    session = get_session()
    
    try:
        # 1. Get current date, time, and timestamp
        print("1. Current Date, Time, and Timestamp:")
        current_date = session.query(sql_func.current_date()).scalar()
        current_time = session.query(sql_func.current_time()).scalar()
        current_timestamp = session.query(sql_func.current_timestamp()).scalar()
        
        print(f"   Current Date: {current_date}")
        print(f"   Current Time: {current_time}")
        print(f"   Current Timestamp: {current_timestamp}")
        
        # 2. Extract year, month, day from order dates
        print("\n2. Extract Date Components:")
        date_components = session.query(
            Order.order_id,
            Order.order_date,
            sql_func.year(Order.order_date).label('order_year'),
            sql_func.month(Order.order_date).label('order_month'),
            sql_func.day(Order.order_date).label('order_day'),
            sql_func.dayofweek(Order.order_date).label('day_of_week')
        ).limit(5).all()
        
        for order in date_components:
            print(f"   Order {order.order_id}: {order.order_date}")
            print(f"      Year: {order.order_year}, Month: {order.order_month}, Day: {order.order_day}")
            print(f"      Day of Week: {order.day_of_week}")
        
        # 3. Calculate the age of each order in days
        print("\n3. Calculate Order Age in Days:")
        order_ages = session.query(
            Order.order_id,
            Order.order_date,
            sql_func.datediff(sql_func.current_date(), Order.order_date).label('age_days')
        ).limit(5).all()
        
        for order in order_ages:
            print(f"   Order {order.order_id}: {order.age_days} days old")
        
        # 4. Find orders from the last 30 days
        print("\n4. Orders from Last 30 Days:")
        recent_orders = session.query(
            Order.order_id,
            Order.order_date,
            Order.total_amount
        ).filter(
            Order.order_date >= sql_func.current_date() - text('INTERVAL 30 DAY')
        ).limit(5).all()
        
        for order in recent_orders:
            print(f"   Order {order.order_id}: {order.order_date} - ${order.total_amount}")
        
        # 5. Format order dates in different ways
        print("\n5. Formatted Order Dates:")
        formatted_dates = session.query(
            Order.order_id,
            Order.order_date,
            sql_func.date_format(Order.order_date, '%Y-%m-%d').label('iso_date'),
            sql_func.date_format(Order.order_date, '%M %d, %Y').label('readable_date'),
            sql_func.date_format(Order.order_date, '%W').label('day_name')
        ).limit(5).all()
        
        for order in formatted_dates:
            print(f"   Order {order.order_id}: {order.iso_date} | {order.readable_date} | {order.day_name}")
        
        # 6. Add 30 days to order dates
        print("\n6. Future Dates (30 days later):")
        future_dates = session.query(
            Order.order_id,
            Order.order_date,
            sql_func.date_add(Order.order_date, text('INTERVAL 30 DAY')).label('future_date')
        ).limit(5).all()
        
        for order in future_dates:
            print(f"   Order {order.order_id}: {order.order_date} -> {order.future_date}")
        
        # 7. Find orders by day of the week
        print("\n7. Orders by Day of Week:")
        orders_by_day = session.query(
            sql_func.dayofweek(Order.order_date).label('day_of_week'),
            sql_func.count(Order.order_id).label('order_count')
        ).group_by(sql_func.dayofweek(Order.order_date)).all()
        
        for day in orders_by_day:
            print(f"   Day {day.day_of_week}: {day.order_count} orders")
        
        # 8. Calculate business days between dates
        print("\n8. Business Days Calculation:")
        business_days = session.query(
            Order.order_id,
            Order.order_date,
            sql_func.datediff(sql_func.current_date(), Order.order_date).label('total_days'),
            # Approximate business days (excluding weekends)
            sql_func.datediff(sql_func.current_date(), Order.order_date) - 
            sql_func.floor(sql_func.datediff(sql_func.current_date(), Order.order_date) / 7) * 2
        ).label('business_days').limit(5).all()
        
        for order in business_days:
            print(f"   Order {order.order_id}: {order.total_days} total days")
        
        print("\n✅ Date and Time Functions Solutions Completed")
        
    except Exception as e:
        print(f"❌ Error in date/time functions: {e}")
    finally:
        session.close()

# ===================================================================
# EXERCISE 4.2: STRING MANIPULATION FUNCTIONS - SOLUTIONS
# ===================================================================

def exercise_4_2_string_functions():
    """
    Complete solutions for string manipulation function exercises.
    """
    print("\n=== Exercise 4.2: String Manipulation Functions Solutions ===\n")
    
    session = get_session()
    
    try:
        # 1. Concatenate first name and last name
        print("1. Full Name Concatenation:")
        full_names = session.query(
            User.user_id,
            User.first_name,
            User.last_name,
            sql_func.concat(User.first_name, ' ', User.last_name).label('full_name')
        ).limit(5).all()
        
        for user in full_names:
            print(f"   User {user.user_id}: {user.full_name}")
        
        # 2. Extract domain names from email addresses
        print("\n2. Extract Email Domains:")
        email_domains = session.query(
            User.user_id,
            User.email,
            sql_func.substring(User.email, sql_func.locate('@', User.email) + 1).label('domain')
        ).limit(5).all()
        
        for user in email_domains:
            print(f"   User {user.user_id}: {user.email} -> {user.domain}")
        
        # 3. Convert usernames to uppercase and lowercase
        print("\n3. Username Case Conversion:")
        case_conversion = session.query(
            User.user_id,
            User.username,
            sql_func.upper(User.username).label('upper_username'),
            sql_func.lower(User.username).label('lower_username')
        ).limit(5).all()
        
        for user in case_conversion:
            print(f"   User {user.user_id}: {user.username} -> {user.upper_username} / {user.lower_username}")
        
        # 4. Find the length of email addresses
        print("\n4. Email Address Lengths:")
        email_lengths = session.query(
            User.user_id,
            User.email,
            sql_func.length(User.email).label('email_length')
        ).limit(5).all()
        
        for user in email_lengths:
            print(f"   User {user.user_id}: {user.email} (length: {user.email_length})")
        
        # 5. Extract first 5 characters of usernames
        print("\n5. First 5 Characters of Usernames:")
        username_prefixes = session.query(
            User.user_id,
            User.username,
            sql_func.left(User.username, 5).label('username_prefix')
        ).limit(5).all()
        
        for user in username_prefixes:
            print(f"   User {user.user_id}: {user.username} -> {user.username_prefix}")
        
        # 6. Replace underscores with spaces in usernames
        print("\n6. Replace Underscores with Spaces:")
        formatted_usernames = session.query(
            User.user_id,
            User.username,
            sql_func.replace(User.username, '_', ' ').label('formatted_username')
        ).limit(5).all()
        
        for user in formatted_usernames:
            print(f"   User {user.user_id}: {user.username} -> {user.formatted_username}")
        
        # 7. Find the position of '@' symbol in email addresses
        print("\n7. '@' Symbol Position in Emails:")
        at_positions = session.query(
            User.user_id,
            User.email,
            sql_func.locate('@', User.email).label('at_position')
        ).limit(5).all()
        
        for user in at_positions:
            print(f"   User {user.user_id}: {user.email} -> '@' at position {user.at_position}")
        
        # 8. Trim whitespace from user data
        print("\n8. Trim Whitespace:")
        # Create sample data with whitespace
        sample_text = "   Hello World   "
        trim_result = session.query(
            sql_func.trim(sample_text).label('trimmed'),
            sql_func.ltrim(sample_text).label('left_trimmed'),
            sql_func.rtrim(sample_text).label('right_trimmed')
        ).first()
        
        print(f"   Original: '{sample_text}'")
        print(f"   Trimmed: '{trim_result.trimmed}'")
        print(f"   Left Trimmed: '{trim_result.left_trimmed}'")
        print(f"   Right Trimmed: '{trim_result.right_trimmed}'")
        
        # 9. Create formatted usernames (First Last)
        print("\n9. Formatted Usernames (Title Case):")
        title_case_names = session.query(
            User.user_id,
            User.first_name,
            User.last_name,
            sql_func.concat(
                sql_func.upper(sql_func.left(User.first_name, 1)),
                sql_func.lower(sql_func.substring(User.first_name, 2)),
                ' ',
                sql_func.upper(sql_func.left(User.last_name, 1)),
                sql_func.lower(sql_func.substring(User.last_name, 2))
            ).label('title_case_name')
        ).limit(5).all()
        
        for user in title_case_names:
            print(f"   User {user.user_id}: {user.title_case_name}")
        
        # 10. Generate display names using COALESCE
        print("\n10. Display Names with COALESCE:")
        display_names = session.query(
            User.user_id,
            User.first_name,
            User.last_name,
            sql_func.coalesce(User.first_name, User.last_name, 'Unknown').label('display_name')
        ).limit(5).all()
        
        for user in display_names:
            print(f"   User {user.user_id}: {user.display_name}")
        
        print("\n✅ String Manipulation Functions Solutions Completed")
        
    except Exception as e:
        print(f"❌ Error in string functions: {e}")
    finally:
        session.close()

# ===================================================================
# EXERCISE 4.3: MATHEMATICAL FUNCTIONS - SOLUTIONS
# ===================================================================

def exercise_4_3_math_functions():
    """
    Complete solutions for mathematical function exercises.
    """
    print("\n=== Exercise 4.3: Mathematical Functions Solutions ===\n")
    
    session = get_session()
    
    try:
        # 1. Round order amounts to 2 decimal places
        print("1. Round Order Amounts:")
        rounded_amounts = session.query(
            Order.order_id,
            Order.total_amount,
            sql_func.round(Order.total_amount, 2).label('rounded_amount')
        ).limit(5).all()
        
        for order in rounded_amounts:
            print(f"   Order {order.order_id}: {order.total_amount} -> {order.rounded_amount}")
        
        # 2. Calculate ceiling and floor values
        print("\n2. Ceiling and Floor Values:")
        ceiling_floor = session.query(
            Order.order_id,
            Order.total_amount,
            sql_func.ceil(Order.total_amount).label('ceiling'),
            sql_func.floor(Order.total_amount).label('floor')
        ).limit(5).all()
        
        for order in ceiling_floor:
            print(f"   Order {order.order_id}: {order.total_amount} -> Ceiling: {order.ceiling}, Floor: {order.floor}")
        
        # 3. Calculate absolute values
        print("\n3. Absolute Values:")
        sample_values = [-15.5, 10.2, -3.7, 0, 25.8]
        
        for value in sample_values:
            abs_result = session.query(sql_func.abs(value).label('absolute')).first()
            print(f"   |{value}| = {abs_result.absolute}")
        
        # 4. Calculate square root
        print("\n4. Square Root Calculations:")
        sqrt_values = session.query(
            Order.order_id,
            Order.total_amount,
            sql_func.sqrt(Order.total_amount).label('square_root')
        ).limit(5).all()
        
        for order in sqrt_values:
            print(f"   Order {order.order_id}: √{order.total_amount} = {order.square_root:.4f}")
        
        # 5. Calculate power of 2
        print("\n5. Power of 2 Calculations:")
        power_values = session.query(
            Order.order_id,
            Order.total_amount,
            sql_func.power(Order.total_amount, 2).label('squared')
        ).limit(5).all()
        
        for order in power_values:
            print(f"   Order {order.order_id}: {order.total_amount}² = {order.squared}")
        
        # 6. Calculate modulo 10
        print("\n6. Modulo 10 Calculations:")
        modulo_values = session.query(
            Order.order_id,
            Order.total_amount,
            sql_func.mod(Order.total_amount, 10).label('mod_10')
        ).limit(5).all()
        
        for order in modulo_values:
            print(f"   Order {order.order_id}: {order.total_amount} MOD 10 = {order.mod_10}")
        
        # 7. Generate random numbers
        print("\n7. Random Numbers:")
        random_numbers = session.query(
            sql_func.rand().label('random_1'),
            sql_func.rand().label('random_2'),
            sql_func.rand().label('random_3')
        ).first()
        
        print(f"   Random 1: {random_numbers.random_1:.6f}")
        print(f"   Random 2: {random_numbers.random_2:.6f}")
        print(f"   Random 3: {random_numbers.random_3:.6f}")
        
        # 8. Calculate percentage of total
        print("\n8. Percentage of Total:")
        total_amount = session.query(sql_func.sum(Order.total_amount)).scalar()
        
        percentages = session.query(
            Order.order_id,
            Order.total_amount,
            sql_func.round((Order.total_amount / total_amount) * 100, 2).label('percentage')
        ).limit(5).all()
        
        for order in percentages:
            print(f"   Order {order.order_id}: {order.total_amount} ({order.percentage}% of total)")
        
        # 9. Calculate running totals
        print("\n9. Running Totals:")
        running_totals = session.query(
            Order.order_id,
            Order.total_amount,
            sql_func.sum(Order.total_amount).over(order_by=Order.order_id).label('running_total')
        ).limit(5).all()
        
        for order in running_totals:
            print(f"   Order {order.order_id}: {order.total_amount} (Running Total: {order.running_total})")
        
        # 10. Calculate moving averages
        print("\n10. Moving Averages:")
        moving_averages = session.query(
            Order.order_id,
            Order.total_amount,
            sql_func.avg(Order.total_amount).over(
                order_by=Order.order_id,
                rows=(0, 2)  # Current row and 2 preceding rows
            ).label('moving_avg')
        ).limit(5).all()
        
        for order in moving_averages:
            print(f"   Order {order.order_id}: {order.total_amount} (Moving Avg: {order.moving_avg:.2f})")
        
        print("\n✅ Mathematical Functions Solutions Completed")
        
    except Exception as e:
        print(f"❌ Error in math functions: {e}")
    finally:
        session.close()

# ===================================================================
# EXERCISE 4.4: CONDITIONAL FUNCTIONS - SOLUTIONS
# ===================================================================

def exercise_4_4_conditional_functions():
    """
    Complete solutions for conditional function exercises.
    """
    print("\n=== Exercise 4.4: Conditional Functions Solutions ===\n")
    
    session = get_session()
    
    try:
        # 1. Categorize orders as 'High' or 'Low' value
        print("1. Order Value Categories:")
        value_categories = session.query(
            Order.order_id,
            Order.total_amount,
            sql_func.if_(Order.total_amount > 100, 'High Value', 'Low Value').label('category')
        ).limit(5).all()
        
        for order in value_categories:
            print(f"   Order {order.order_id}: {order.total_amount} -> {order.category}")
        
        # 2. Nested IF functions for tier categories
        print("\n2. Tier Categories with Nested IF:")
        tier_categories = session.query(
            Order.order_id,
            Order.total_amount,
            sql_func.if_(
                Order.total_amount > 200,
                'Premium',
                sql_func.if_(
                    Order.total_amount > 100,
                    'High',
                    sql_func.if_(
                        Order.total_amount > 50,
                        'Medium',
                        'Low'
                    )
                )
            ).label('tier')
        ).limit(5).all()
        
        for order in tier_categories:
            print(f"   Order {order.order_id}: {order.total_amount} -> {order.tier}")
        
        # 3. Handle NULL values with IFNULL
        print("\n3. Handle NULL Values with IFNULL:")
        null_handling = session.query(
            User.user_id,
            User.first_name,
            sql_func.ifnull(User.first_name, 'Unknown').label('safe_name')
        ).limit(5).all()
        
        for user in null_handling:
            print(f"   User {user.user_id}: {user.safe_name}")
        
        # 4. Use COALESCE for first non-NULL value
        print("\n4. COALESCE for First Non-NULL Value:")
        coalesce_values = session.query(
            User.user_id,
            User.first_name,
            User.last_name,
            User.username,
            sql_func.coalesce(User.first_name, User.last_name, User.username, 'No Name').label('display_name')
        ).limit(5).all()
        
        for user in coalesce_values:
            print(f"   User {user.user_id}: {user.display_name}")
        
        # 5. CASE statements for status descriptions
        print("\n5. CASE Statements for Status Descriptions:")
        status_descriptions = session.query(
            Order.order_id,
            Order.status,
            case(
                (Order.status == 'pending', 'Waiting for Processing'),
                (Order.status == 'processing', 'Being Processed'),
                (Order.status == 'shipped', 'On the Way'),
                (Order.status == 'delivered', 'Successfully Delivered'),
                (Order.status == 'cancelled', 'Order Cancelled'),
                else_='Unknown Status'
            ).label('status_description')
        ).limit(5).all()
        
        for order in status_descriptions:
            print(f"   Order {order.order_id}: {order.status} -> {order.status_description}")
        
        # 6. CASE with multiple conditions
        print("\n6. CASE with Multiple Conditions:")
        complex_categories = session.query(
            Order.order_id,
            Order.total_amount,
            Order.status,
            case(
                (and_(Order.total_amount > 200, Order.status == 'delivered'), 'Premium Delivered'),
                (and_(Order.total_amount > 100, Order.status == 'delivered'), 'High Value Delivered'),
                (Order.total_amount > 200, 'Premium'),
                (Order.total_amount > 100, 'High Value'),
                (Order.status == 'delivered', 'Delivered'),
                else_='Standard'
            ).label('complex_category')
        ).limit(5).all()
        
        for order in complex_categories:
            print(f"   Order {order.order_id}: {order.total_amount}, {order.status} -> {order.complex_category}")
        
        # 7. Conditional calculations
        print("\n7. Conditional Calculations:")
        conditional_calculations = session.query(
            Order.order_id,
            Order.total_amount,
            Order.status,
            case(
                (Order.status == 'delivered', Order.total_amount * 1.1),  # 10% bonus for delivered
                (Order.status == 'shipped', Order.total_amount * 1.05),   # 5% bonus for shipped
                else_=Order.total_amount
            ).label('adjusted_amount')
        ).limit(5).all()
        
        for order in conditional_calculations:
            print(f"   Order {order.order_id}: {order.total_amount} -> {order.adjusted_amount}")
        
        # 8. NULLIF to convert empty strings to NULL
        print("\n8. NULLIF for Empty Strings:")
        nullif_examples = session.query(
            User.user_id,
            User.username,
            sql_func.nullif(User.username, '').label('nullified_username')
        ).limit(5).all()
        
        for user in nullif_examples:
            print(f"   User {user.user_id}: {repr(user.username)} -> {repr(user.nullified_username)}")
        
        # 9. Conditional formatting
        print("\n9. Conditional Formatting:")
        conditional_formatting = session.query(
            Order.order_id,
            Order.total_amount,
            case(
                (Order.total_amount > 100, sql_func.concat('$', sql_func.format(Order.total_amount, 2), ' (High Value)')),
                else_=sql_func.concat('$', sql_func.format(Order.total_amount, 2))
            ).label('formatted_amount')
        ).limit(5).all()
        
        for order in conditional_formatting:
            print(f"   Order {order.order_id}: {order.formatted_amount}")
        
        # 10. Priority assignment based on multiple criteria
        print("\n10. Priority Assignment:")
        priority_assignment = session.query(
            Order.order_id,
            Order.total_amount,
            Order.status,
            case(
                (and_(Order.total_amount > 200, Order.status == 'pending'), 'High Priority'),
                (and_(Order.total_amount > 100, Order.status == 'pending'), 'Medium Priority'),
                (Order.status == 'pending', 'Low Priority'),
                else_='No Priority'
            ).label('priority')
        ).limit(5).all()
        
        for order in priority_assignment:
            print(f"   Order {order.order_id}: {order.total_amount}, {order.status} -> {order.priority}")
        
        print("\n✅ Conditional Functions Solutions Completed")
        
    except Exception as e:
        print(f"❌ Error in conditional functions: {e}")
    finally:
        session.close()

# ===================================================================
# EXERCISE 4.5: AGGREGATE FUNCTIONS - SOLUTIONS
# ===================================================================

def exercise_4_5_aggregate_functions():
    """
    Complete solutions for aggregate function exercises.
    """
    print("\n=== Exercise 4.5: Aggregate Functions Solutions ===\n")
    
    session = get_session()
    
    try:
        # 1. Calculate total count of orders
        print("1. Total Order Count:")
        total_count = session.query(sql_func.count(Order.order_id)).scalar()
        print(f"   Total Orders: {total_count}")
        
        # 2. Calculate sum, average, min, max of order amounts
        print("\n2. Order Amount Statistics:")
        amount_stats = session.query(
            sql_func.sum(Order.total_amount).label('total_amount'),
            sql_func.avg(Order.total_amount).label('average_amount'),
            sql_func.min(Order.total_amount).label('min_amount'),
            sql_func.max(Order.total_amount).label('max_amount')
        ).first()
        
        print(f"   Total Amount: ${amount_stats.total_amount}")
        print(f"   Average Amount: ${amount_stats.average_amount:.2f}")
        print(f"   Min Amount: ${amount_stats.min_amount}")
        print(f"   Max Amount: ${amount_stats.max_amount}")
        
        # 3. Count orders by status
        print("\n3. Order Count by Status:")
        status_counts = session.query(
            Order.status,
            sql_func.count(Order.order_id).label('order_count')
        ).group_by(Order.status).all()
        
        for status in status_counts:
            print(f"   {status.status}: {status.order_count} orders")
        
        # 4. Calculate total amount by status
        print("\n4. Total Amount by Status:")
        status_totals = session.query(
            Order.status,
            sql_func.sum(Order.total_amount).label('total_amount'),
            sql_func.avg(Order.total_amount).label('average_amount')
        ).group_by(Order.status).all()
        
        for status in status_totals:
            print(f"   {status.status}: ${status.total_amount} (avg: ${status.average_amount:.2f})")
        
        # 5. Find average order amount by user
        print("\n5. Average Order Amount by User:")
        user_averages = session.query(
            Order.user_id,
            sql_func.count(Order.order_id).label('order_count'),
            sql_func.avg(Order.total_amount).label('average_amount'),
            sql_func.sum(Order.total_amount).label('total_amount')
        ).group_by(Order.user_id).limit(5).all()
        
        for user in user_averages:
            print(f"   User {user.user_id}: {user.order_count} orders, avg: ${user.average_amount:.2f}, total: ${user.total_amount}")
        
        # 6. Calculate percentage of orders by status
        print("\n6. Percentage of Orders by Status:")
        total_orders = session.query(sql_func.count(Order.order_id)).scalar()
        
        status_percentages = session.query(
            Order.status,
            sql_func.count(Order.order_id).label('order_count'),
            sql_func.round((sql_func.count(Order.order_id) / total_orders) * 100, 2).label('percentage')
        ).group_by(Order.status).all()
        
        for status in status_percentages:
            print(f"   {status.status}: {status.order_count} orders ({status.percentage}%)")
        
        # 7. Find top 5 users by total order amount
        print("\n7. Top 5 Users by Total Order Amount:")
        top_users = session.query(
            Order.user_id,
            sql_func.sum(Order.total_amount).label('total_amount'),
            sql_func.count(Order.order_id).label('order_count')
        ).group_by(Order.user_id).order_by(desc(sql_func.sum(Order.total_amount))).limit(5).all()
        
        for user in top_users:
            print(f"   User {user.user_id}: ${user.total_amount} ({user.order_count} orders)")
        
        # 8. Calculate running totals by date
        print("\n8. Running Totals by Date:")
        running_totals = session.query(
            Order.order_id,
            Order.order_date,
            Order.total_amount,
            sql_func.sum(Order.total_amount).over(
                order_by=Order.order_date
            ).label('running_total')
        ).limit(5).all()
        
        for order in running_totals:
            print(f"   Order {order.order_id}: {order.order_date} - ${order.total_amount} (Running Total: ${order.running_total})")
        
        # 9. Find orders above average amount
        print("\n9. Orders Above Average Amount:")
        average_amount = session.query(sql_func.avg(Order.total_amount)).scalar()
        
        above_average = session.query(
            Order.order_id,
            Order.total_amount,
            sql_func.round(Order.total_amount - average_amount, 2).label('above_average')
        ).filter(Order.total_amount > average_amount).limit(5).all()
        
        for order in above_average:
            print(f"   Order {order.order_id}: ${order.total_amount} (${order.above_average} above average)")
        
        # 10. Calculate cumulative percentages
        print("\n10. Cumulative Percentages:")
        cumulative_percentages = session.query(
            Order.order_id,
            Order.total_amount,
            sql_func.round(
                (sql_func.sum(Order.total_amount).over(order_by=Order.order_id) / 
                 sql_func.sum(Order.total_amount).over()) * 100, 2
            ).label('cumulative_percentage')
        ).limit(5).all()
        
        for order in cumulative_percentages:
            print(f"   Order {order.order_id}: ${order.total_amount} ({order.cumulative_percentage}% cumulative)")
        
        print("\n✅ Aggregate Functions Solutions Completed")
        
    except Exception as e:
        print(f"❌ Error in aggregate functions: {e}")
    finally:
        session.close()

# ===================================================================
# EXERCISE 4.6: CUSTOM FUNCTION CREATION - SOLUTIONS
# ===================================================================

def exercise_4_6_custom_functions():
    """
    Complete solutions for custom function creation exercises.
    """
    print("\n=== Exercise 4.6: Custom Function Creation Solutions ===\n")
    
    session = get_session()
    
    try:
        # 1. Create a custom function to format currency
        print("1. Custom Currency Formatting:")
        def format_currency(amount_column):
            return sql_func.concat('$', sql_func.format(amount_column, 2))
        
        currency_formatted = session.query(
            Order.order_id,
            Order.total_amount,
            format_currency(Order.total_amount).label('formatted_amount')
        ).limit(5).all()
        
        for order in currency_formatted:
            print(f"   Order {order.order_id}: {order.formatted_amount}")
        
        # 2. Create a custom function to calculate order age in weeks
        print("\n2. Custom Order Age in Weeks:")
        def calculate_age_weeks(date_column):
            return sql_func.round(sql_func.datediff(sql_func.current_date(), date_column) / 7, 1)
        
        age_weeks = session.query(
            Order.order_id,
            Order.order_date,
            calculate_age_weeks(Order.order_date).label('age_weeks')
        ).limit(5).all()
        
        for order in age_weeks:
            print(f"   Order {order.order_id}: {order.age_weeks} weeks old")
        
        # 3. Create a custom function to generate order summaries
        print("\n3. Custom Order Summaries:")
        def generate_order_summary():
            return sql_func.concat(
                'Order #', Order.order_number,
                ' - $', sql_func.format(Order.total_amount, 2),
                ' - ', sql_func.upper(Order.status)
            )
        
        order_summaries = session.query(
            Order.order_id,
            generate_order_summary().label('order_summary')
        ).limit(5).all()
        
        for order in order_summaries:
            print(f"   {order.order_summary}")
        
        # 4. Create a custom function to categorize orders by multiple criteria
        print("\n4. Custom Order Categorization:")
        def categorize_order():
            return case(
                (and_(Order.total_amount > 200, Order.status == 'delivered'), 'Premium Delivered'),
                (and_(Order.total_amount > 100, Order.status == 'delivered'), 'High Value Delivered'),
                (Order.total_amount > 200, 'Premium'),
                (Order.total_amount > 100, 'High Value'),
                (Order.status == 'delivered', 'Delivered'),
                else_='Standard'
            )
        
        order_categories = session.query(
            Order.order_id,
            Order.total_amount,
            Order.status,
            categorize_order().label('category')
        ).limit(5).all()
        
        for order in order_categories:
            print(f"   Order {order.order_id}: {order.total_amount}, {order.status} -> {order.category}")
        
        # 5. Create a custom function to format user display names
        print("\n5. Custom User Display Names:")
        def format_display_name():
            return sql_func.concat(
                sql_func.upper(sql_func.left(User.first_name, 1)),
                sql_func.lower(sql_func.substring(User.first_name, 2)),
                ' ',
                sql_func.upper(sql_func.left(User.last_name, 1)),
                sql_func.lower(sql_func.substring(User.last_name, 2))
            )
        
        display_names = session.query(
            User.user_id,
            format_display_name().label('display_name')
        ).limit(5).all()
        
        for user in display_names:
            print(f"   User {user.user_id}: {user.display_name}")
        
        # 6. Create a custom function to calculate order priority scores
        print("\n6. Custom Order Priority Scores:")
        def calculate_priority_score():
            return case(
                (and_(Order.total_amount > 200, Order.status == 'pending'), 100),
                (and_(Order.total_amount > 100, Order.status == 'pending'), 75),
                (Order.total_amount > 200, 50),
                (Order.status == 'pending', 25),
                else_=0
            )
        
        priority_scores = session.query(
            Order.order_id,
            Order.total_amount,
            Order.status,
            calculate_priority_score().label('priority_score')
        ).limit(5).all()
        
        for order in priority_scores:
            print(f"   Order {order.order_id}: {order.total_amount}, {order.status} -> Score: {order.priority_score}")
        
        # 7. Create a custom function to generate status descriptions
        print("\n7. Custom Status Descriptions:")
        def generate_status_description():
            return case(
                (Order.status == 'pending', 'Waiting for Processing'),
                (Order.status == 'processing', 'Being Processed'),
                (Order.status == 'shipped', 'On the Way'),
                (Order.status == 'delivered', 'Successfully Delivered'),
                (Order.status == 'cancelled', 'Order Cancelled'),
                else_='Unknown Status'
            )
        
        status_descriptions = session.query(
            Order.order_id,
            Order.status,
            generate_status_description().label('status_description')
        ).limit(5).all()
        
        for order in status_descriptions:
            print(f"   Order {order.order_id}: {order.status} -> {order.status_description}")
        
        # 8. Create a custom function to calculate business metrics
        print("\n8. Custom Business Metrics:")
        def calculate_business_metrics():
            return sql_func.concat(
                'Orders: ', sql_func.count(Order.order_id),
                ' | Total: $', sql_func.format(sql_func.sum(Order.total_amount), 2),
                ' | Avg: $', sql_func.format(sql_func.avg(Order.total_amount), 2)
            )
        
        business_metrics = session.query(calculate_business_metrics().label('metrics')).first()
        print(f"   Business Metrics: {business_metrics.metrics}")
        
        # 9. Create a custom function to format dates in multiple ways
        print("\n9. Custom Date Formatting:")
        def format_date_multiple_ways():
            return sql_func.concat(
                sql_func.date_format(Order.order_date, '%Y-%m-%d'), ' | ',
                sql_func.date_format(Order.order_date, '%M %d, %Y'), ' | ',
                sql_func.date_format(Order.order_date, '%W')
            )
        
        formatted_dates = session.query(
            Order.order_id,
            format_date_multiple_ways().label('formatted_date')
        ).limit(5).all()
        
        for order in formatted_dates:
            print(f"   Order {order.order_id}: {order.formatted_date}")
        
        # 10. Create a custom function to generate report headers
        print("\n10. Custom Report Headers:")
        def generate_report_header():
            return sql_func.concat(
                'Order Report - Generated on ',
                sql_func.date_format(sql_func.current_timestamp(), '%M %d, %Y at %H:%i:%s')
            )
        
        report_header = session.query(generate_report_header().label('header')).first()
        print(f"   {report_header.header}")
        
        print("\n✅ Custom Function Creation Solutions Completed")
        
    except Exception as e:
        print(f"❌ Error in custom functions: {e}")
    finally:
        session.close()

# ===================================================================
# MAIN FUNCTION TO RUN ALL SOLUTIONS
# ===================================================================

def main():
    """
    Main function to run all database function exercise solutions.
    """
    print("=== MySQL Database Functions with SQLAlchemy - Complete Solutions ===\n")
    
    try:
        # Run all exercise solutions
        exercise_4_1_date_time_functions()
        exercise_4_2_string_functions()
        exercise_4_3_math_functions()
        exercise_4_4_conditional_functions()
        exercise_4_5_aggregate_functions()
        exercise_4_6_custom_functions()
        
        print("\n=== All Database Function Solutions Completed Successfully ===")
        
    except Exception as e:
        print(f"❌ Error running solutions: {e}")

# Standard Python idiom for running the script
if __name__ == "__main__":
    main()
