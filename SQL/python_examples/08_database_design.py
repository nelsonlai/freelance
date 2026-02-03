"""
====================================================================
Lesson 8: Database Design Principles - Flask + SQLAlchemy ORM Examples
====================================================================
This module demonstrates database design principles using Flask and SQLAlchemy ORM.
It covers:
1. Entity-Relationship modeling with Flask-SQLAlchemy ORM
2. Database normalization examples using ORM models
3. Index creation and optimization with ORM
4. Design patterns implementation using ORM
5. Performance considerations with ORM
6. Real-world database schema creation using ORM

Key Concepts:
- Flask-SQLAlchemy ORM: Object-Relational Mapping for Python
- Database normalization: 1NF, 2NF, 3NF, BCNF with ORM models
- Indexing strategies: Primary, unique, composite, partial indexes
- Design patterns: Audit trail, soft delete, hierarchical data
- Performance optimization: Query optimization and denormalization
- ORM Relationships: One-to-many, many-to-many, self-referencing
====================================================================
"""

# Import required libraries
from flask import Flask
from flask_sqlalchemy import SQLAlchemy
from sqlalchemy import text, Index, UniqueConstraint, CheckConstraint, func, and_, or_
from sqlalchemy.orm import relationship, backref
from sqlalchemy.sql import func as sql_func
from datetime import datetime, date
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
# EXAMPLE 1: NORMALIZED E-COMMERCE DATABASE DESIGN
# ===================================================================
# This example demonstrates proper normalization and relationship design using ORM

class User(db.Model):
    """
    User entity - represents customers in the e-commerce system using ORM.
    
    Demonstrates:
    - Primary key design with ORM
    - Unique constraints with ORM
    - Data validation with ORM
    - Audit fields (created_at, updated_at) with ORM
    - One-to-many relationships with ORM
    """
    __tablename__ = 'users'
    
    # Primary key with auto-increment
    user_id = db.Column(db.Integer, primary_key=True, autoincrement=True)
    
    # User identification fields with constraints
    username = db.Column(db.String(50), unique=True, nullable=False, index=True)
    email = db.Column(db.String(100), unique=True, nullable=False, index=True)
    password_hash = db.Column(db.String(255), nullable=False)
    
    # Personal information
    first_name = db.Column(db.String(50), nullable=False)
    last_name = db.Column(db.String(50), nullable=False)
    phone = db.Column(db.String(20))
    date_of_birth = db.Column(db.String(10))  # Using String for simplicity
    
    # Status and audit fields
    is_active = db.Column(db.Boolean, default=True, nullable=False)
    created_at = db.Column(db.DateTime, default=sql_func.current_timestamp())
    updated_at = db.Column(db.DateTime, default=sql_func.current_timestamp(), onupdate=sql_func.current_timestamp())
    
    # Relationships (one-to-many) using ORM
    addresses = db.relationship("UserAddress", back_populates="user", cascade="all, delete-orphan")
    orders = db.relationship("Order", back_populates="user")
    
    def __repr__(self):
        return f"<User(username='{self.username}', email='{self.email}')>"

class UserAddress(db.Model):
    """
    UserAddress entity - represents user addresses using ORM.
    
    Demonstrates:
    - Foreign key relationships with ORM
    - ENUM usage with ORM
    - Composite unique constraints with ORM
    - Cascade delete behavior with ORM
    """
    __tablename__ = 'user_addresses'
    
    address_id = db.Column(db.Integer, primary_key=True, autoincrement=True)
    
    # Foreign key to users table
    user_id = db.Column(db.Integer, db.ForeignKey('users.user_id', ondelete='CASCADE'), nullable=False)
    
    # Address information
    address_type = db.Column(db.Enum('billing', 'shipping'), default='shipping', nullable=False)
    street_address = db.Column(db.String(255), nullable=False)
    city = db.Column(db.String(100), nullable=False)
    state = db.Column(db.String(50), nullable=False)
    postal_code = db.Column(db.String(20), nullable=False)
    country = db.Column(db.String(50), nullable=False, default='USA')
    is_default = db.Column(db.Boolean, default=False, nullable=False)
    
    # Relationship (many-to-one) using ORM
    user = db.relationship("User", back_populates="addresses")
    
    # Composite unique constraint: one default address per type per user
    __table_args__ = (
        UniqueConstraint('user_id', 'address_type', 'is_default', 
                        name='unique_default_address_per_type'),
    )
    
    def __repr__(self):
        return f"<UserAddress(user_id={self.user_id}, type='{self.address_type}')>"

class Category(db.Model):
    """
    Category entity - represents product categories with hierarchical structure using ORM.
    
    Demonstrates:
    - Self-referencing foreign key (hierarchical data) with ORM
    - Materialized path pattern with ORM
    - Recursive relationships with ORM
    """
    __tablename__ = 'categories'
    
    category_id = db.Column(db.Integer, primary_key=True, autoincrement=True)
    
    # Category information
    name = db.Column(db.String(100), nullable=False, unique=True)
    description = db.Column(db.Text)
    slug = db.Column(db.String(100), nullable=False, unique=True, index=True)
    
    # Hierarchical structure
    parent_id = db.Column(db.Integer, db.ForeignKey('categories.category_id'), nullable=True)
    level = db.Column(db.Integer, nullable=False, default=0)
    path = db.Column(db.String(500), nullable=False, default='')  # Materialized path
    
    # Status
    is_active = db.Column(db.Boolean, default=True, nullable=False)
    created_at = db.Column(db.DateTime, default=sql_func.current_timestamp())
    
    # Self-referencing relationships using ORM
    parent = db.relationship("Category", remote_side=[category_id], backref="children")
    products = db.relationship("Product", back_populates="category")
    
    def __repr__(self):
        return f"<Category(name='{self.name}', level={self.level})>"

class Product(db.Model):
    """
    Product entity - represents products in the e-commerce system using ORM.
    
    Demonstrates:
    - Complex data types (JSON for flexible attributes) with ORM
    - Check constraints with ORM
    - Multiple indexes for performance with ORM
    - Denormalized fields for performance with ORM
    """
    __tablename__ = 'products'
    
    product_id = db.Column(db.Integer, primary_key=True, autoincrement=True)
    
    # Product identification
    sku = db.Column(db.String(50), unique=True, nullable=False, index=True)
    name = db.Column(db.String(200), nullable=False, index=True)
    description = db.Column(db.Text)
    short_description = db.Column(db.String(500))
    
    # Category relationship
    category_id = db.Column(db.Integer, db.ForeignKey('categories.category_id'), nullable=True)
    
    # Product details
    brand = db.Column(db.String(100), index=True)
    price = db.Column(db.Numeric(10, 2), nullable=False, index=True)
    cost = db.Column(db.Numeric(10, 2))
    weight = db.Column(db.Numeric(8, 3))
    
    # Flexible attributes using JSON
    dimensions = db.Column(db.JSON)  # {length, width, height}
    images = db.Column(db.JSON)      # Array of image URLs
    specifications = db.Column(db.JSON)  # Flexible product specifications
    
    # Inventory management
    inventory_count = db.Column(db.Integer, default=0, nullable=False)
    min_stock_level = db.Column(db.Integer, default=5, nullable=False)
    
    # Status fields
    is_active = db.Column(db.Boolean, default=True, nullable=False, index=True)
    is_featured = db.Column(db.Boolean, default=False, nullable=False, index=True)
    
    # Audit fields
    created_at = db.Column(db.DateTime, default=sql_func.current_timestamp())
    updated_at = db.Column(db.DateTime, default=sql_func.current_timestamp(), onupdate=sql_func.current_timestamp())
    
    # Relationships using ORM
    category = db.relationship("Category", back_populates="products")
    order_items = db.relationship("OrderItem", back_populates="product")
    
    # Table constraints
    __table_args__ = (
        CheckConstraint('price >= 0', name='check_price_positive'),
        CheckConstraint('inventory_count >= 0', name='check_inventory_positive'),
        CheckConstraint('min_stock_level >= 0', name='check_min_stock_positive'),
    )
    
    def __repr__(self):
        return f"<Product(sku='{self.sku}', name='{self.name}')>"

class Order(db.Model):
    """
    Order entity - represents customer orders using ORM.
    
    Demonstrates:
    - Complex ENUM usage with ORM
    - Calculated fields with ORM
    - JSON storage for flexible data with ORM
    - Audit trail pattern with ORM
    """
    __tablename__ = 'orders'
    
    order_id = db.Column(db.Integer, primary_key=True, autoincrement=True)
    order_number = db.Column(db.String(20), unique=True, nullable=False, index=True)
    
    # Customer relationship
    user_id = db.Column(db.Integer, db.ForeignKey('users.user_id'), nullable=False)
    
    # Order status and payment
    status = db.Column(db.Enum('pending', 'processing', 'shipped', 'delivered', 'cancelled', 'refunded'), 
                       default='pending', nullable=False, index=True)
    payment_status = db.Column(db.Enum('pending', 'paid', 'failed', 'refunded'), 
                              default='pending', nullable=False, index=True)
    payment_method = db.Column(db.String(50))
    
    # Financial information
    subtotal = db.Column(db.Numeric(10, 2), nullable=False)
    tax_amount = db.Column(db.Numeric(10, 2), default=0.00, nullable=False)
    shipping_amount = db.Column(db.Numeric(10, 2), default=0.00, nullable=False)
    discount_amount = db.Column(db.Numeric(10, 2), default=0.00, nullable=False)
    total_amount = db.Column(db.Numeric(10, 2), nullable=False, index=True)
    
    # Address information (denormalized for historical accuracy)
    shipping_address = db.Column(db.JSON)
    billing_address = db.Column(db.JSON)
    
    # Additional information
    notes = db.Column(db.Text)
    shipped_at = db.Column(db.DateTime, nullable=True)
    delivered_at = db.Column(db.DateTime, nullable=True)
    
    # Audit fields
    created_at = db.Column(db.DateTime, default=sql_func.current_timestamp(), index=True)
    updated_at = db.Column(db.DateTime, default=sql_func.current_timestamp(), onupdate=sql_func.current_timestamp())
    
    # Relationships using ORM
    user = db.relationship("User", back_populates="orders")
    order_items = db.relationship("OrderItem", back_populates="order", cascade="all, delete-orphan")
    
    # Table constraints
    __table_args__ = (
        CheckConstraint('subtotal >= 0', name='check_subtotal_positive'),
        CheckConstraint('total_amount >= 0', name='check_total_positive'),
    )
    
    def __repr__(self):
        return f"<Order(order_number='{self.order_number}', status='{self.status}')>"

class OrderItem(db.Model):
    """
    OrderItem entity - represents individual items within an order using ORM.
    
    Demonstrates:
    - Composite primary key with ORM
    - Denormalized fields for historical accuracy with ORM
    - Calculated fields with ORM
    """
    __tablename__ = 'order_items'
    
    # Composite primary key
    order_item_id = db.Column(db.Integer, primary_key=True, autoincrement=True)
    order_id = db.Column(db.Integer, db.ForeignKey('orders.order_id', ondelete='CASCADE'), nullable=False)
    product_id = db.Column(db.Integer, db.ForeignKey('products.product_id'), nullable=False)
    
    # Denormalized product information (for historical accuracy)
    product_name = db.Column(db.String(200), nullable=False)
    sku = db.Column(db.String(50), nullable=False)
    quantity = db.Column(db.Integer, nullable=False)
    unit_price = db.Column(db.Numeric(10, 2), nullable=False)
    total_price = db.Column(db.Numeric(10, 2), nullable=False)
    
    # Relationships using ORM
    order = db.relationship("Order", back_populates="order_items")
    product = db.relationship("Product", back_populates="order_items")
    
    # Table constraints
    __table_args__ = (
        CheckConstraint('quantity > 0', name='check_quantity_positive'),
        CheckConstraint('unit_price >= 0', name='check_unit_price_positive'),
        CheckConstraint('total_price >= 0', name='check_total_price_positive'),
    )
    
    def __repr__(self):
        return f"<OrderItem(product='{self.product_name}', quantity={self.quantity})>"

# ===================================================================
# EXAMPLE 2: DESIGN PATTERNS IMPLEMENTATION
# ===================================================================

class AuditLog(db.Model):
    """
    AuditLog entity - implements audit trail pattern using ORM.
    
    Demonstrates:
    - Audit trail pattern with ORM
    - Polymorphic associations with ORM
    - JSON storage for flexible data with ORM
    """
    __tablename__ = 'audit_logs'
    
    audit_id = db.Column(db.Integer, primary_key=True, autoincrement=True)
    
    # Polymorphic association fields
    entity_type = db.Column(db.String(50), nullable=False, index=True)  # 'User', 'Product', etc.
    entity_id = db.Column(db.Integer, nullable=False, index=True)
    
    # Audit information
    action = db.Column(db.Enum('INSERT', 'UPDATE', 'DELETE'), nullable=False, index=True)
    old_values = db.Column(db.JSON)  # Previous values
    new_values = db.Column(db.JSON)  # New values
    
    # User and timestamp
    changed_by = db.Column(db.Integer, db.ForeignKey('users.user_id'), nullable=True)
    changed_at = db.Column(db.DateTime, default=sql_func.current_timestamp(), nullable=False, index=True)
    
    def __repr__(self):
        return f"<AuditLog(entity='{self.entity_type}', action='{self.action}')>"

# Mixin class for soft delete pattern
class SoftDeleteMixin:
    """
    Mixin class for soft delete pattern using ORM.
    
    Demonstrates:
    - Mixin pattern for reusable functionality with ORM
    - Soft delete implementation with ORM
    """
    is_deleted = db.Column(db.Boolean, default=False, nullable=False, index=True)
    deleted_at = db.Column(db.DateTime, nullable=True)
    deleted_by = db.Column(db.Integer, db.ForeignKey('users.user_id'), nullable=True)

class ProductReview(db.Model, SoftDeleteMixin):
    """
    ProductReview entity - implements soft delete pattern using ORM.
    
    Demonstrates:
    - Soft delete pattern with ORM
    - Rating constraints with ORM
    - Verification patterns with ORM
    """
    __tablename__ = 'product_reviews'
    
    review_id = db.Column(db.Integer, primary_key=True, autoincrement=True)
    
    # Relationships
    product_id = db.Column(db.Integer, db.ForeignKey('products.product_id', ondelete='CASCADE'), nullable=False)
    user_id = db.Column(db.Integer, db.ForeignKey('users.user_id', ondelete='CASCADE'), nullable=False)
    order_id = db.Column(db.Integer, db.ForeignKey('orders.order_id', ondelete='SET NULL'), nullable=True)
    
    # Review content
    rating = db.Column(db.Integer, nullable=False, index=True)
    title = db.Column(db.String(200))
    content = db.Column(db.Text)
    
    # Verification and approval
    is_verified_purchase = db.Column(db.Boolean, default=False, nullable=False)
    is_approved = db.Column(db.Boolean, default=False, nullable=False, index=True)
    helpful_count = db.Column(db.Integer, default=0, nullable=False)
    
    # Audit fields
    created_at = db.Column(db.DateTime, default=sql_func.current_timestamp())
    updated_at = db.Column(db.DateTime, default=sql_func.current_timestamp(), onupdate=sql_func.current_timestamp())
    
    # Table constraints
    __table_args__ = (
        CheckConstraint('rating >= 1 AND rating <= 5', name='check_rating_range'),
        CheckConstraint('helpful_count >= 0', name='check_helpful_count_positive'),
        UniqueConstraint('user_id', 'product_id', name='unique_user_product_review'),
    )
    
    def __repr__(self):
        return f"<ProductReview(rating={self.rating}, product_id={self.product_id})>"

# ===================================================================
# EXAMPLE 3: PERFORMANCE OPTIMIZATION WITH INDEXES
# ===================================================================

def create_performance_indexes():
    """
    Create various types of indexes for performance optimization using ORM.
    
    Demonstrates:
    - Composite indexes for multi-column queries with ORM
    - Partial indexes for filtered queries with ORM
    - Covering indexes for query optimization with ORM
    """
    
    # Composite index for user queries
    Index('idx_users_name_email', User.first_name, User.last_name, User.email)
    
    # Partial index for active products
    Index('idx_products_active_featured', Product.is_active, Product.is_featured)
    
    # Covering index for order queries
    Index('idx_orders_user_status_date', Order.user_id, Order.status, Order.created_at)
    
    # Index for category hierarchy queries
    Index('idx_categories_parent_level', Category.parent_id, Category.level)
    
    # Index for audit log queries
    Index('idx_audit_entity_action_date', AuditLog.entity_type, AuditLog.action, AuditLog.changed_at)

class DatabaseDesigner:
    """
    DatabaseDesigner class demonstrates various database design principles
    and patterns using Flask-SQLAlchemy ORM.
    
    This class shows how to implement:
    - Normalized database schemas using ORM
    - Proper relationships between entities using ORM
    - Indexing strategies using ORM
    - Design patterns for real-world applications using ORM
    """
    
    def __init__(self):
        """Initialize database connection parameters"""
        self.app = app
        self.db = db
    
    def demonstrate_database_design(self):
        """
        Demonstrate various database design principles and patterns using ORM.
        
        Returns:
            bool: True if successful, False otherwise
        """
        try:
            with self.app.app_context():
                # Create all tables using ORM
                print("1. Creating normalized database schema using ORM...")
                self.db.create_all()
                print("✅ Database schema created successfully using ORM")
                
                # Create performance indexes
                print("\n2. Creating performance indexes...")
                create_performance_indexes()
                print("✅ Performance indexes created")
                
                # Demonstrate data insertion using ORM
                print("\n3. Demonstrating data insertion using ORM...")
                
                # Create a user using ORM
                user = User(
                    username='john_doe',
                    email='john.doe@example.com',
                    password_hash='hashed_password',
                    first_name='John',
                    last_name='Doe',
                    phone='555-0123'
                )
                self.db.session.add(user)
                self.db.session.flush()  # Get the user_id
                
                # Create user address using ORM
                address = UserAddress(
                    user_id=user.user_id,
                    address_type='shipping',
                    street_address='123 Main St',
                    city='Anytown',
                    state='CA',
                    postal_code='12345',
                    country='USA',
                    is_default=True
                )
                self.db.session.add(address)
                
                # Create category using ORM
                category = Category(
                    name='Electronics',
                    description='Electronic devices and accessories',
                    slug='electronics',
                    level=0,
                    path='electronics'
                )
                self.db.session.add(category)
                self.db.session.flush()
                
                # Create product using ORM
                product = Product(
                    sku='ELEC-001',
                    name='Wireless Headphones',
                    description='High-quality wireless headphones',
                    category_id=category.category_id,
                    brand='TechBrand',
                    price=99.99,
                    cost=50.00,
                    inventory_count=100,
                    dimensions={'length': 20, 'width': 15, 'height': 8},
                    images=['headphones1.jpg', 'headphones2.jpg'],
                    specifications={'battery_life': '20 hours', 'connectivity': 'Bluetooth 5.0'}
                )
                self.db.session.add(product)
                self.db.session.flush()
                
                # Create order using ORM
                order = Order(
                    order_number='ORD-001',
                    user_id=user.user_id,
                    status='pending',
                    payment_status='pending',
                    subtotal=99.99,
                    tax_amount=8.00,
                    shipping_amount=5.99,
                    total_amount=113.98,
                    shipping_address={
                        'street': '123 Main St',
                        'city': 'Anytown',
                        'state': 'CA',
                        'zip': '12345'
                    }
                )
                self.db.session.add(order)
                self.db.session.flush()
                
                # Create order item using ORM
                order_item = OrderItem(
                    order_id=order.order_id,
                    product_id=product.product_id,
                    product_name=product.name,
                    sku=product.sku,
                    quantity=1,
                    unit_price=product.price,
                    total_price=product.price
                )
                self.db.session.add(order_item)
                
                # Create product review using ORM
                review = ProductReview(
                    product_id=product.product_id,
                    user_id=user.user_id,
                    order_id=order.order_id,
                    rating=5,
                    title='Excellent headphones!',
                    content='Great sound quality and comfortable fit.',
                    is_verified_purchase=True,
                    is_approved=True
                )
                self.db.session.add(review)
                
                # Create audit log entry using ORM
                audit_log = AuditLog(
                    entity_type='Product',
                    entity_id=product.product_id,
                    action='INSERT',
                    new_values={'name': product.name, 'price': float(product.price)},
                    changed_by=user.user_id
                )
                self.db.session.add(audit_log)
                
                # Commit all changes
                self.db.session.commit()
                print("✅ Sample data inserted successfully using ORM")
                
                # Demonstrate queries using ORM
                print("\n4. Demonstrating optimized queries using ORM...")
                
                # Query with joins and filters using ORM
                result = db.session.query(Order, User, Product).join(
                    User, Order.user_id == User.user_id
                ).join(
                    OrderItem, Order.order_id == OrderItem.order_id
                ).join(
                    Product, OrderItem.product_id == Product.product_id
                ).filter(
                    Order.status == 'pending'
                ).first()
                
                if result:
                    order, user, product = result
                    print(f"   Found pending order: {order.order_number} for {user.username}")
                    print(f"   Product: {product.name} - ${product.price}")
                
                # Query with hierarchical data using ORM
                electronics_category = Category.query.filter(
                    Category.name == 'Electronics'
                ).first()
                
                if electronics_category:
                    print(f"   Category: {electronics_category.name} (Level {electronics_category.level})")
                
                # Query with soft delete using ORM
                active_reviews = ProductReview.query.filter(
                    ProductReview.is_deleted == False,
                    ProductReview.is_approved == True
                ).count()
                
                print(f"   Active approved reviews: {active_reviews}")
                
                # Query audit log using ORM
                recent_audits = AuditLog.query.filter(
                    AuditLog.entity_type == 'Product'
                ).count()
                
                print(f"   Product audit entries: {recent_audits}")
                
                print("\n✅ Database design demonstration completed successfully using ORM")
                return True
                
        except Exception as e:
            print(f"❌ Error during demonstration: {e}")
            self.db.session.rollback()
            return False
    
    def demonstrate_normalization(self):
        """
        Demonstrate database normalization principles using ORM.
        
        Returns:
            bool: True if successful, False otherwise
        """
        try:
            with self.app.app_context():
                # Show normalized structure
                print("1. Normalized Database Structure using ORM:")
                print("   ✅ Users table: Stores user information (1NF)")
                print("   ✅ UserAddresses table: Separate table for addresses (2NF)")
                print("   ✅ Categories table: Hierarchical structure (3NF)")
                print("   ✅ Products table: Product information with JSON for flexibility")
                print("   ✅ Orders table: Order information with denormalized addresses")
                print("   ✅ OrderItems table: Junction table for order-product relationship")
                
                # Show relationship integrity
                print("\n2. Relationship Integrity using ORM:")
                print("   ✅ Foreign key constraints ensure referential integrity")
                print("   ✅ Cascade deletes prevent orphaned records")
                print("   ✅ Unique constraints prevent duplicate data")
                print("   ✅ Check constraints validate data ranges")
                
                # Show performance optimizations
                print("\n3. Performance Optimizations using ORM:")
                print("   ✅ Indexes on frequently queried columns")
                print("   ✅ Composite indexes for multi-column queries")
                print("   ✅ JSON fields for flexible data storage")
                print("   ✅ Denormalized fields for historical accuracy")
                
                # Demonstrate relationship navigation
                print("\n4. Relationship Navigation using ORM:")
                user = User.query.first()
                if user:
                    print(f"   User: {user.username}")
                    print(f"   Addresses: {len(user.addresses)}")
                    print(f"   Orders: {len(user.orders)}")
                    
                    if user.orders:
                        order = user.orders[0]
                        print(f"   Order Items: {len(order.order_items)}")
                
                print("\n✅ Normalization demonstration completed using ORM")
                return True
                
        except Exception as e:
            print(f"❌ Error during normalization demo: {e}")
            return False
    
    def demonstrate_design_patterns(self):
        """
        Demonstrate design patterns implementation using ORM.
        
        Returns:
            bool: True if successful, False otherwise
        """
        try:
            with self.app.app_context():
                print("=== Design Patterns Demonstration using ORM ===\n")
                
                # Audit Trail Pattern
                print("1. Audit Trail Pattern:")
                audit_logs = AuditLog.query.filter(
                    AuditLog.entity_type == 'Product'
                ).all()
                
                for log in audit_logs:
                    print(f"   {log.action} on {log.entity_type} ID {log.entity_id}")
                    print(f"   Changed at: {log.changed_at}")
                
                # Soft Delete Pattern
                print("\n2. Soft Delete Pattern:")
                all_reviews = ProductReview.query.all()
                active_reviews = ProductReview.query.filter(
                    ProductReview.is_deleted == False
                ).all()
                
                print(f"   Total reviews: {len(all_reviews)}")
                print(f"   Active reviews: {len(active_reviews)}")
                
                # Hierarchical Data Pattern
                print("\n3. Hierarchical Data Pattern:")
                categories = Category.query.all()
                for category in categories:
                    print(f"   Category: {category.name} (Level {category.level})")
                    if category.children:
                        for child in category.children:
                            print(f"     - Child: {child.name}")
                
                # JSON Storage Pattern
                print("\n4. JSON Storage Pattern:")
                products = Product.query.filter(Product.specifications.isnot(None)).all()
                for product in products[:2]:  # Show first 2
                    print(f"   Product: {product.name}")
                    print(f"   Specifications: {product.specifications}")
                
                return True
                
        except Exception as e:
            print(f"❌ Error during design patterns demo: {e}")
            return False

def main():
    """
    Main function to demonstrate comprehensive database design principles using Flask-SQLAlchemy ORM.
    """
    print("=== Flask + SQLAlchemy ORM Database Design Principles - Python Examples ===\n")
    
    # Initialize database designer
    designer = DatabaseDesigner()
    
    # Demonstrate database design
    designer.demonstrate_database_design()
    
    # Demonstrate normalization
    designer.demonstrate_normalization()
    
    # Demonstrate design patterns
    designer.demonstrate_design_patterns()
    
    print("\n=== Flask + SQLAlchemy ORM Database Design Demo Complete ===")
    print("\nKey Design Principles Demonstrated:")
    print("1. ✅ Proper normalization (1NF, 2NF, 3NF) using ORM")
    print("2. ✅ Entity-relationship modeling using ORM")
    print("3. ✅ Appropriate data type selection using ORM")
    print("4. ✅ Indexing strategies for performance using ORM")
    print("5. ✅ Design patterns (audit trail, soft delete) using ORM")
    print("6. ✅ Relationship integrity and constraints using ORM")
    print("7. ✅ Flexible data storage with JSON using ORM")
    print("8. ✅ Performance optimization techniques using ORM")
    print("9. ✅ Hierarchical data modeling using ORM")
    print("10. ✅ Mixin patterns for reusable functionality using ORM")

# Standard Python idiom for running the script
if __name__ == "__main__":
    main()