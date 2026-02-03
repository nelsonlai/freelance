"""
====================================================================
Lesson 9: MySQL Database Functions with Flask + SQLAlchemy ORM - Python Examples
====================================================================
This module demonstrates how to use MySQL database functions through
Flask and SQLAlchemy ORM without writing raw SQL. It covers:
1. SQLAlchemy Core functions (func, case, text) with ORM
2. SQLAlchemy ORM function usage
3. Date and time functions with ORM
4. String manipulation functions with ORM
5. Mathematical functions with ORM
6. Aggregate functions with ORM
7. Conditional functions with ORM
8. Custom function creation with ORM

Key Concepts:
- Flask-SQLAlchemy: ORM integration with database functions
- SQLAlchemy Core: Low-level SQL construction with ORM
- SQLAlchemy ORM: High-level object mapping with functions
- Database functions: Built-in MySQL functions through ORM
- Function composition: Combining multiple functions with ORM
- Performance optimization: Efficient function usage with ORM
====================================================================
"""

# Import required libraries
from flask import Flask
from flask_sqlalchemy import SQLAlchemy
from sqlalchemy import text, func, case, and_, or_, desc, asc
from sqlalchemy.orm import joinedload
from datetime import datetime, date, timedelta
import os
from dotenv import load_dotenv

# Load environment variables
load_dotenv()

# Initialize Flask application
app = Flask(__name__)

# Configure database connection
app.config['SQLALCHEMY_DATABASE_URI'] = (
    f"mysql+pymysql://{os.getenv('DB_USER', 'student')}:"
    f"{os.getenv('DB_PASSWORD', 'password123')}@"
    f"{os.getenv('DB_HOST', 'localhost')}:"
    f"{os.getenv('DB_PORT', 3306)}/"
    f"{os.getenv('DB_NAME', 'learning_db')}"
)

app.config['SQLALCHEMY_TRACK_MODIFICATIONS'] = False
app.config['SQLALCHEMY_ENGINE_OPTIONS'] = {
    'pool_pre_ping': True,
    'pool_recycle': 300,
    'connect_args': {'charset': 'utf8mb4'}
}

# Initialize SQLAlchemy with Flask app
db = SQLAlchemy(app)

# ===================================================================
# DATABASE MODELS FOR DEMONSTRATION
# ===================================================================

class User(db.Model):
    """User model for demonstrating database functions with ORM"""
    __tablename__ = 'users'
    
    user_id = db.Column(db.Integer, primary_key=True, autoincrement=True)
    username = db.Column(db.String(50), unique=True, nullable=False)
    email = db.Column(db.String(100), unique=True, nullable=False)
    first_name = db.Column(db.String(50), nullable=False)
    last_name = db.Column(db.String(50), nullable=False)
    birth_date = db.Column(db.String(10))  # Using String for simplicity
    created_at = db.Column(db.DateTime, default=func.current_timestamp())
    updated_at = db.Column(db.DateTime, default=func.current_timestamp(), onupdate=func.current_timestamp())
    is_active = db.Column(db.Boolean, default=True)
    
    # Relationships
    orders = db.relationship("Order", back_populates="user")
    
    def __repr__(self):
        return f"<User(username='{self.username}', email='{self.email}')>"

class Order(db.Model):
    """Order model for demonstrating database functions with ORM"""
    __tablename__ = 'orders'
    
    order_id = db.Column(db.Integer, primary_key=True, autoincrement=True)
    user_id = db.Column(db.Integer, db.ForeignKey('users.user_id'), nullable=False)
    order_number = db.Column(db.String(20), unique=True, nullable=False)
    total_amount = db.Column(db.Numeric(10, 2), nullable=False)
    status = db.Column(db.Enum('pending', 'processing', 'shipped', 'delivered', 'cancelled'), default='pending')
    order_date = db.Column(db.DateTime, default=func.current_timestamp())
    
    # Relationships
    user = db.relationship("User", back_populates="orders")
    
    def __repr__(self):
        return f"<Order(order_number='{self.order_number}', total_amount={self.total_amount})>"

class DatabaseFunctionDemo:
    """
    DatabaseFunctionDemo class demonstrates MySQL database functions
    using Flask-SQLAlchemy ORM without writing raw SQL.
    
    This class shows how to:
    - Use built-in MySQL functions through ORM
    - Create custom function expressions with ORM
    - Combine multiple functions with ORM
    - Optimize function usage for performance with ORM
    """
    
    def __init__(self):
        """Initialize with Flask app and database instance"""
        self.app = app
        self.db = db
    
    def demonstrate_date_functions(self):
        """
        Demonstrate MySQL date and time functions using ORM.
        
        Shows how to use:
        - CURRENT_DATE, CURRENT_TIME, CURRENT_TIMESTAMP with ORM
        - DATE functions (YEAR, MONTH, DAY) with ORM
        - DATE arithmetic (DATE_ADD, DATE_SUB) with ORM
        - Date formatting (DATE_FORMAT) with ORM
        """
        try:
            with self.app.app_context():
                print("=== Date and Time Functions Demo using ORM ===\n")
                
                # 1. Get current date and time using ORM
                print("1. Current Date and Time Functions using ORM:")
                
                # Using SQLAlchemy Core func with ORM
                current_date_result = db.session.query(func.current_date()).first()
                print(f"   Current Date: {current_date_result[0]}")
                
                current_time_result = db.session.query(func.current_time()).first()
                print(f"   Current Time: {current_time_result[0]}")
                
                current_timestamp_result = db.session.query(func.current_timestamp()).first()
                print(f"   Current Timestamp: {current_timestamp_result[0]}")
                
                # 2. Date extraction functions using ORM
                print("\n2. Date Extraction Functions using ORM:")
                
                # Extract year from order_date using ORM
                year_result = db.session.query(
                    Order.order_id,
                    Order.order_date,
                    func.year(Order.order_date).label('order_year')
                ).limit(3).all()
                
                for order in year_result:
                    print(f"   Order {order.order_id}: {order.order_date} -> Year: {order.order_year}")
                
                # Extract month and day using ORM
                month_day_result = db.session.query(
                    Order.order_id,
                    func.month(Order.order_date).label('order_month'),
                    func.day(Order.order_date).label('order_day'),
                    func.dayofweek(Order.order_date).label('day_of_week')
                ).limit(3).all()
                
                for order in month_day_result:
                    print(f"   Order {order.order_id}: Month {order.order_month}, Day {order.order_day}, Day of Week {order.day_of_week}")
                
                # 3. Date arithmetic using ORM
                print("\n3. Date Arithmetic Functions using ORM:")
                
                # Calculate days between dates using ORM
                days_ago_result = db.session.query(
                    Order.order_id,
                    Order.order_date,
                    func.datediff(func.current_date(), Order.order_date).label('days_ago')
                ).limit(3).all()
                
                for order in days_ago_result:
                    print(f"   Order {order.order_id}: {order.days_ago} days ago")
                
                # Add days to date using ORM
                future_date_result = db.session.query(
                    Order.order_id,
                    Order.order_date,
                    func.date_add(Order.order_date, text("INTERVAL 30 DAY")).label('future_date')
                ).limit(3).all()
                
                for order in future_date_result:
                    print(f"   Order {order.order_id}: Future date: {order.future_date}")
                
                # 4. Date formatting using ORM
                print("\n4. Date Formatting Functions using ORM:")
                
                # Format date in different ways using ORM
                formatted_dates = db.session.query(
                    Order.order_id,
                    Order.order_date,
                    func.date_format(Order.order_date, '%Y-%m-%d').label('formatted_date'),
                    func.date_format(Order.order_date, '%M %d, %Y').label('readable_date'),
                    func.date_format(Order.order_date, '%W').label('day_name')
                ).limit(3).all()
                
                for order in formatted_dates:
                    print(f"   Order {order.order_id}: {order.formatted_date} | {order.readable_date} | {order.day_name}")
                
                print("\n✅ Date and Time Functions Demo Completed using ORM")
                
        except Exception as e:
            print(f"❌ Error in date functions demo: {e}")
    
    def demonstrate_string_functions(self):
        """
        Demonstrate MySQL string manipulation functions using ORM.
        
        Shows how to use:
        - CONCAT, CONCAT_WS with ORM
        - UPPER, LOWER, LENGTH with ORM
        - SUBSTRING, LEFT, RIGHT with ORM
        - TRIM, LTRIM, RTRIM with ORM
        - REPLACE, LOCATE with ORM
        """
        try:
            with self.app.app_context():
                print("\n=== String Manipulation Functions Demo using ORM ===\n")
                
                # 1. String concatenation using ORM
                print("1. String Concatenation Functions using ORM:")
                
                # CONCAT function using ORM
                concat_result = db.session.query(
                    User.user_id,
                    User.first_name,
                    User.last_name,
                    func.concat(User.first_name, ' ', User.last_name).label('full_name')
                ).limit(3).all()
                
                for user in concat_result:
                    print(f"   User {user.user_id}: {user.full_name}")
                
                # CONCAT_WS (with separator) using ORM
                concat_ws_result = db.session.query(
                    User.user_id,
                    User.email,
                    func.concat_ws('@', User.username, 'company.com').label('company_email')
                ).limit(3).all()
                
                for user in concat_ws_result:
                    print(f"   User {user.user_id}: {user.company_email}")
                
                # 2. String case functions using ORM
                print("\n2. String Case Functions using ORM:")
                
                case_result = db.session.query(
                    User.user_id,
                    User.username,
                    func.upper(User.username).label('upper_username'),
                    func.lower(User.username).label('lower_username')
                ).limit(3).all()
                
                for user in case_result:
                    print(f"   User {user.user_id}: {user.username} -> {user.upper_username} / {user.lower_username}")
                
                # 3. String length and substring using ORM
                print("\n3. String Length and Substring Functions using ORM:")
                
                substring_result = db.session.query(
                    User.user_id,
                    User.email,
                    func.length(User.email).label('email_length'),
                    func.substring(User.email, 1, 5).label('email_start'),
                    func.left(User.email, 10).label('email_left'),
                    func.right(User.email, 10).label('email_right')
                ).limit(3).all()
                
                for user in substring_result:
                    print(f"   User {user.user_id}: Length {user.email_length}, Start: {user.email_start}")
                    print(f"      Left: {user.email_left}, Right: {user.email_right}")
                
                # 4. String trimming using ORM
                print("\n4. String Trimming Functions using ORM:")
                
                # Create sample data with spaces
                sample_text = "   Hello World   "
                
                trim_result = db.session.query(
                    func.trim(sample_text).label('trimmed'),
                    func.ltrim(sample_text).label('left_trimmed'),
                    func.rtrim(sample_text).label('right_trimmed')
                ).first()
                
                print(f"   Original: '{sample_text}'")
                print(f"   Trimmed: '{trim_result.trimmed}'")
                print(f"   Left Trimmed: '{trim_result.left_trimmed}'")
                print(f"   Right Trimmed: '{trim_result.right_trimmed}'")
                
                # 5. String replacement and location using ORM
                print("\n5. String Replacement and Location Functions using ORM:")
                
                replace_result = db.session.query(
                    User.user_id,
                    User.email,
                    func.replace(User.email, '@', ' [at] ').label('replaced_email'),
                    func.locate('@', User.email).label('at_position')
                ).limit(3).all()
                
                for user in replace_result:
                    print(f"   User {user.user_id}: {user.replaced_email} (position: {user.at_position})")
                
                print("\n✅ String Manipulation Functions Demo Completed using ORM")
                
        except Exception as e:
            print(f"❌ Error in string functions demo: {e}")
    
    def demonstrate_math_functions(self):
        """
        Demonstrate MySQL mathematical functions using ORM.
        
        Shows how to use:
        - ROUND, CEIL, FLOOR with ORM
        - ABS, SIGN with ORM
        - POWER, SQRT with ORM
        - MOD, RAND with ORM
        - MIN, MAX, AVG, SUM with ORM
        """
        try:
            with self.app.app_context():
                print("\n=== Mathematical Functions Demo using ORM ===\n")
                
                # 1. Rounding functions using ORM
                print("1. Rounding Functions using ORM:")
                
                rounding_result = db.session.query(
                    Order.order_id,
                    Order.total_amount,
                    func.round(Order.total_amount, 1).label('rounded_1'),
                    func.round(Order.total_amount, 0).label('rounded_0'),
                    func.ceil(Order.total_amount).label('ceiling'),
                    func.floor(Order.total_amount).label('floor')
                ).limit(3).all()
                
                for order in rounding_result:
                    print(f"   Order {order.order_id}: {order.total_amount}")
                    print(f"      Rounded(1): {order.rounded_1}, Rounded(0): {order.rounded_0}")
                    print(f"      Ceiling: {order.ceiling}, Floor: {order.floor}")
                
                # 2. Absolute value and sign using ORM
                print("\n2. Absolute Value and Sign Functions using ORM:")
                
                # Create sample negative values
                sample_values = [-15.5, 10.2, -3.7, 0]
                
                for value in sample_values:
                    abs_sign_result = db.session.query(
                        func.abs(value).label('absolute'),
                        func.sign(value).label('sign')
                    ).first()
                    
                    print(f"   Value: {value} -> Absolute: {abs_sign_result.absolute}, Sign: {abs_sign_result.sign}")
                
                # 3. Power and square root using ORM
                print("\n3. Power and Square Root Functions using ORM:")
                
                power_result = db.session.query(
                    func.power(2, 3).label('power_2_3'),
                    func.power(Order.total_amount, 2).label('amount_squared')
                ).first()
                
                print(f"   2^3 = {power_result.power_2_3}")
                
                # Get square of first order amount
                first_order = Order.query.first()
                if first_order:
                    print(f"   First order amount: {first_order.total_amount}")
                    print(f"   Amount squared: {power_result.amount_squared}")
                
                # 4. Modulo and random using ORM
                print("\n4. Modulo and Random Functions using ORM:")
                
                modulo_result = db.session.query(
                    func.mod(10, 3).label('mod_10_3'),
                    func.mod(15, 4).label('mod_15_4'),
                    func.rand().label('random_number')
                ).first()
                
                print(f"   10 MOD 3 = {modulo_result.mod_10_3}")
                print(f"   15 MOD 4 = {modulo_result.mod_15_4}")
                print(f"   Random number: {modulo_result.random_number:.6f}")
                
                # 5. Aggregate functions using ORM
                print("\n5. Aggregate Functions using ORM:")
                
                aggregate_result = db.session.query(
                    func.count(Order.order_id).label('total_orders'),
                    func.sum(Order.total_amount).label('total_amount'),
                    func.avg(Order.total_amount).label('average_amount'),
                    func.min(Order.total_amount).label('min_amount'),
                    func.max(Order.total_amount).label('max_amount')
                ).first()
                
                print(f"   Total Orders: {aggregate_result.total_orders}")
                print(f"   Total Amount: {aggregate_result.total_amount}")
                print(f"   Average Amount: {aggregate_result.average_amount:.2f}")
                print(f"   Min Amount: {aggregate_result.min_amount}")
                print(f"   Max Amount: {aggregate_result.max_amount}")
                
                print("\n✅ Mathematical Functions Demo Completed using ORM")
                
        except Exception as e:
            print(f"❌ Error in math functions demo: {e}")
    
    def demonstrate_conditional_functions(self):
        """
        Demonstrate MySQL conditional functions using ORM.
        
        Shows how to use:
        - IF, IFNULL, NULLIF with ORM
        - CASE statements with ORM
        - COALESCE with ORM
        """
        try:
            with self.app.app_context():
                print("\n=== Conditional Functions Demo using ORM ===\n")
                
                # 1. IF function using ORM
                print("1. IF Function using ORM:")
                
                if_result = db.session.query(
                    Order.order_id,
                    Order.total_amount,
                    Order.status,
                    func.if_(Order.total_amount > 100, 'High Value', 'Low Value').label('value_category'),
                    func.if_(Order.status == 'delivered', 'Completed', 'In Progress').label('completion_status')
                ).limit(5).all()
                
                for order in if_result:
                    print(f"   Order {order.order_id}: {order.total_amount} -> {order.value_category}")
                    print(f"      Status: {order.status} -> {order.completion_status}")
                
                # 2. IFNULL and NULLIF functions using ORM
                print("\n2. IFNULL and NULLIF Functions using ORM:")
                
                # Create sample data with NULL values
                sample_data = [None, '', 'Hello', 'World']
                
                for data in sample_data:
                    ifnull_result = db.session.query(
                        func.ifnull(data, 'NULL_VALUE').label('ifnull_result'),
                        func.nullif(data, '').label('nullif_result')
                    ).first()
                    
                    print(f"   Input: {repr(data)}")
                    print(f"      IFNULL: {repr(ifnull_result.ifnull_result)}")
                    print(f"      NULLIF: {repr(ifnull_result.nullif_result)}")
                
                # 3. CASE statements using ORM
                print("\n3. CASE Statements using ORM:")
                
                case_result = db.session.query(
                    Order.order_id,
                    Order.total_amount,
                    case(
                        (Order.total_amount < 50, 'Low'),
                        (Order.total_amount < 100, 'Medium'),
                        (Order.total_amount < 200, 'High'),
                        else_='Very High'
                    ).label('amount_category'),
                    case(
                        (Order.status == 'pending', 'Waiting'),
                        (Order.status == 'processing', 'In Progress'),
                        (Order.status == 'shipped', 'On the Way'),
                        (Order.status == 'delivered', 'Delivered'),
                        else_='Unknown'
                    ).label('status_description')
                ).limit(5).all()
                
                for order in case_result:
                    print(f"   Order {order.order_id}: {order.total_amount} -> {order.amount_category}")
                    print(f"      Status: {order.status} -> {order.status_description}")
                
                # 4. COALESCE function using ORM
                print("\n4. COALESCE Function using ORM:")
                
                # COALESCE returns the first non-NULL value
                coalesce_result = db.session.query(
                    User.user_id,
                    User.first_name,
                    User.last_name,
                    func.coalesce(User.first_name, User.last_name, 'Unknown').label('display_name')
                ).limit(3).all()
                
                for user in coalesce_result:
                    print(f"   User {user.user_id}: {user.display_name}")
                
                print("\n✅ Conditional Functions Demo Completed using ORM")
                
        except Exception as e:
            print(f"❌ Error in conditional functions demo: {e}")
    
    def demonstrate_custom_functions(self):
        """
        Demonstrate creating custom functions using ORM.
        
        Shows how to:
        - Create custom function expressions with ORM
        - Combine multiple functions with ORM
        - Use function aliases with ORM
        """
        try:
            with self.app.app_context():
                print("\n=== Custom Functions Demo using ORM ===\n")
                
                # 1. Custom function expressions using ORM
                print("1. Custom Function Expressions using ORM:")
                
                # Create a custom function to calculate order age in days
                order_age_days = func.datediff(func.current_date(), Order.order_date)
                
                # Create a custom function to format currency
                formatted_amount = func.concat('$', func.format(Order.total_amount, 2))
                
                custom_result = db.session.query(
                    Order.order_id,
                    Order.order_date,
                    Order.total_amount,
                    order_age_days.label('age_days'),
                    formatted_amount.label('formatted_amount')
                ).limit(3).all()
                
                for order in custom_result:
                    print(f"   Order {order.order_id}: {order.age_days} days old, Amount: {order.formatted_amount}")
                
                # 2. Complex function combinations using ORM
                print("\n2. Complex Function Combinations using ORM:")
                
                # Create a complex function to generate order summary
                order_summary = func.concat(
                    'Order #', Order.order_number, ' - $', 
                    func.format(Order.total_amount, 2), ' - ',
                    func.upper(Order.status)
                )
                
                complex_result = db.session.query(
                    Order.order_id,
                    order_summary.label('order_summary')
                ).limit(3).all()
                
                for order in complex_result:
                    print(f"   {order.order_summary}")
                
                # 3. Function with conditional logic using ORM
                print("\n3. Function with Conditional Logic using ORM:")
                
                # Create a function that categorizes orders based on multiple criteria
                order_category = case(
                    (and_(Order.total_amount > 200, Order.status == 'delivered'), 'Premium Delivered'),
                    (Order.total_amount > 100, 'High Value'),
                    (Order.status == 'delivered', 'Delivered'),
                    else_='Standard'
                )
                
                category_result = db.session.query(
                    Order.order_id,
                    Order.total_amount,
                    Order.status,
                    order_category.label('category')
                ).limit(5).all()
                
                for order in category_result:
                    print(f"   Order {order.order_id}: {order.total_amount}, {order.status} -> {order.category}")
                
                print("\n✅ Custom Functions Demo Completed using ORM")
                
        except Exception as e:
            print(f"❌ Error in custom functions demo: {e}")
    
    def demonstrate_performance_optimization(self):
        """
        Demonstrate performance optimization techniques with database functions using ORM.
        
        Shows how to:
        - Use functions efficiently in queries with ORM
        - Avoid function calls in WHERE clauses when possible with ORM
        - Use indexed columns with functions with ORM
        """
        try:
            with self.app.app_context():
                print("\n=== Performance Optimization Demo using ORM ===\n")
                
                # 1. Efficient function usage using ORM
                print("1. Efficient Function Usage using ORM:")
                
                # Good: Use functions in SELECT, not WHERE
                efficient_result = db.session.query(
                    Order.order_id,
                    Order.order_date,
                    func.year(Order.order_date).label('order_year')
                ).filter(
                    Order.order_date >= '2023-01-01'  # Use indexed column in WHERE
                ).limit(3).all()
                
                for order in efficient_result:
                    print(f"   Order {order.order_id}: {order.order_date} -> Year {order.order_year}")
                
                # 2. Function-based calculations using ORM
                print("\n2. Function-based Calculations using ORM:")
                
                # Calculate running totals and percentages
                total_amount = db.session.query(func.sum(Order.total_amount)).scalar()
                
                percentage_result = db.session.query(
                    Order.order_id,
                    Order.total_amount,
                    func.round(
                        (Order.total_amount / total_amount) * 100, 2
                    ).label('percentage_of_total')
                ).limit(3).all()
                
                for order in percentage_result:
                    print(f"   Order {order.order_id}: {order.total_amount} ({order.percentage_of_total}% of total)")
                
                # 3. Window functions (if supported) using ORM
                print("\n3. Window Functions using ORM:")
                
                # Rank orders by amount
                ranked_result = db.session.query(
                    Order.order_id,
                    Order.total_amount,
                    func.rank().over(order_by=desc(Order.total_amount)).label('rank_by_amount')
                ).limit(5).all()
                
                for order in ranked_result:
                    print(f"   Rank {order.rank_by_amount}: Order {order.order_id} - {order.total_amount}")
                
                print("\n✅ Performance Optimization Demo Completed using ORM")
                
        except Exception as e:
            print(f"❌ Error in performance optimization demo: {e}")

def main():
    """
    Main function to demonstrate MySQL database functions using Flask-SQLAlchemy ORM.
    """
    print("=== MySQL Database Functions with Flask + SQLAlchemy ORM Demo ===\n")
    
    # Initialize database function demo
    demo = DatabaseFunctionDemo()
    
    # Ensure tables exist
    with app.app_context():
        db.create_all()
        
        # Insert sample data if tables are empty
        user_count = User.query.count()
        if user_count == 0:
            print("Inserting sample data...")
            
            # Create sample users
            users = [
                User(username='john_doe', email='john@example.com', first_name='John', last_name='Doe'),
                User(username='jane_smith', email='jane@example.com', first_name='Jane', last_name='Smith'),
                User(username='bob_johnson', email='bob@example.com', first_name='Bob', last_name='Johnson')
            ]
            
            for user in users:
                db.session.add(user)
            
            db.session.flush()  # Get user IDs
            
            # Create sample orders
            orders = [
                Order(user_id=1, order_number='ORD-001', total_amount=150.75, status='delivered'),
                Order(user_id=1, order_number='ORD-002', total_amount=89.50, status='shipped'),
                Order(user_id=2, order_number='ORD-003', total_amount=250.00, status='processing'),
                Order(user_id=2, order_number='ORD-004', total_amount=75.25, status='pending'),
                Order(user_id=3, order_number='ORD-005', total_amount=300.00, status='delivered')
            ]
            
            for order in orders:
                db.session.add(order)
            
            db.session.commit()
            print("✅ Sample data inserted successfully")
    
    # Demonstrate various function categories
    demo.demonstrate_date_functions()
    demo.demonstrate_string_functions()
    demo.demonstrate_math_functions()
    demo.demonstrate_conditional_functions()
    demo.demonstrate_custom_functions()
    demo.demonstrate_performance_optimization()
    
    print("\n=== All Database Functions Demos Completed Successfully using ORM ===")

# Standard Python idiom for running the script
if __name__ == "__main__":
    main()