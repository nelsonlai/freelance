-- Exercise 3: Database Design and Normalization
-- Complete the following exercises to practice database design principles

-- ===================================================================
-- EXERCISE 3.1: NORMALIZATION PRACTICE
-- ===================================================================

-- Given the following denormalized table, normalize it to 3NF:

-- BAD: Denormalized table (violates normalization rules)
CREATE TABLE bad_employee_data (
    emp_id INT,
    emp_name VARCHAR(100),
    dept_id INT,
    dept_name VARCHAR(100),
    dept_location VARCHAR(100),
    manager_id INT,
    manager_name VARCHAR(100),
    project_id INT,
    project_name VARCHAR(100),
    project_start_date DATE,
    project_end_date DATE,
    hours_worked INT,
    hourly_rate DECIMAL(10,2)
);

-- Your normalized solution here:
-- Step 1: Create departments table (eliminates transitive dependency)
-- Your CREATE TABLE statement here:

-- Step 2: Create employees table (eliminates partial dependency)
-- Your CREATE TABLE statement here:

-- Step 3: Create projects table (eliminates partial dependency)
-- Your CREATE TABLE statement here:

-- Step 4: Create employee_projects junction table (many-to-many relationship)
-- Your CREATE TABLE statement here:

-- ===================================================================
-- EXERCISE 3.2: LIBRARY MANAGEMENT SYSTEM DESIGN
-- ===================================================================

-- Design a complete database schema for a library management system
-- Requirements:
-- 1. Books: title, author, ISBN, publication year, genre, copies available
-- 2. Members: name, email, phone, membership type, join date
-- 3. Borrowing: member borrows book, due date, return date, fine amount
-- 4. Staff: librarians with different access levels
-- 5. Reservations: members can reserve books

-- Your solution here:

-- 1. Create books table
-- Your CREATE TABLE statement here:

-- 2. Create members table
-- Your CREATE TABLE statement here:

-- 3. Create staff table
-- Your CREATE TABLE statement here:

-- 4. Create borrowings table
-- Your CREATE TABLE statement here:

-- 5. Create reservations table
-- Your CREATE TABLE statement here:

-- 6. Create appropriate indexes
-- Your CREATE INDEX statements here:

-- ===================================================================
-- EXERCISE 3.3: E-COMMERCE DATABASE DESIGN
-- ===================================================================

-- Design a comprehensive e-commerce database with the following entities:
-- - Customers (with multiple addresses)
-- - Products (with categories and variants)
-- - Orders (with order items)
-- - Inventory management
-- - Reviews and ratings
-- - Discounts and coupons

-- Your solution here:

-- 1. Create customers table
-- Your CREATE TABLE statement here:

-- 2. Create customer_addresses table
-- Your CREATE TABLE statement here:

-- 3. Create categories table (hierarchical)
-- Your CREATE TABLE statement here:

-- 4. Create products table
-- Your CREATE TABLE statement here:

-- 5. Create product_variants table
-- Your CREATE TABLE statement here:

-- 6. Create orders table
-- Your CREATE TABLE statement here:

-- 7. Create order_items table
-- Your CREATE TABLE statement here:

-- 8. Create inventory table
-- Your CREATE TABLE statement here:

-- 9. Create reviews table
-- Your CREATE TABLE statement here:

-- 10. Create discounts table
-- Your CREATE TABLE statement here:

-- ===================================================================
-- EXERCISE 3.4: DATA TYPE SELECTION
-- ===================================================================

-- Choose appropriate data types for the following scenarios:

-- 1. User age (0-120 years)
-- Your data type choice and explanation:

-- 2. Product price (with 2 decimal places)
-- Your data type choice and explanation:

-- 3. User email address
-- Your data type choice and explanation:

-- 4. Product description (can be very long)
-- Your data type choice and explanation:

-- 5. Order status (pending, processing, shipped, delivered, cancelled)
-- Your data type choice and explanation:

-- 6. User preferences (flexible key-value pairs)
-- Your data type choice and explanation:

-- 7. Product dimensions (length, width, height)
-- Your data type choice and explanation:

-- 8. Timestamp for when record was created
-- Your data type choice and explanation:

-- ===================================================================
-- EXERCISE 3.5: INDEXING STRATEGIES
-- ===================================================================

-- Design indexes for the following query patterns:

-- 1. Find all orders by customer in date range
-- Query: SELECT * FROM orders WHERE customer_id = ? AND order_date BETWEEN ? AND ?
-- Your CREATE INDEX statement here:

-- 2. Find products by category and price range
-- Query: SELECT * FROM products WHERE category_id = ? AND price BETWEEN ? AND ?
-- Your CREATE INDEX statement here:

-- 3. Find users who haven't logged in recently
-- Query: SELECT * FROM users WHERE last_login < ?
-- Your CREATE INDEX statement here:

-- 4. Generate monthly sales reports
-- Query: SELECT SUM(total_amount) FROM orders WHERE YEAR(order_date) = ? AND MONTH(order_date) = ?
-- Your CREATE INDEX statement here:

-- 5. Find products with low inventory
-- Query: SELECT * FROM products WHERE inventory_count < min_stock_level
-- Your CREATE INDEX statement here:

-- ===================================================================
-- EXERCISE 3.6: DESIGN PATTERNS
-- ===================================================================

-- Implement the following design patterns:

-- 1. Audit Trail Pattern
-- Create an audit log table that can track changes to any entity
-- Your CREATE TABLE statement here:

-- 2. Soft Delete Pattern
-- Modify an existing table to support soft deletes
-- Your ALTER TABLE statement here:

-- 3. Hierarchical Data Pattern
-- Create a table for organizational hierarchy (employees and managers)
-- Your CREATE TABLE statement here:

-- 4. Polymorphic Association Pattern
-- Create a comments table that can reference multiple entity types
-- Your CREATE TABLE statement here:

-- ===================================================================
-- EXERCISE 3.7: PERFORMANCE OPTIMIZATION
-- ===================================================================

-- Optimize the following scenarios:

-- 1. Denormalization for Read-Heavy Application
-- Create a denormalized table for frequently accessed order summary data
-- Your CREATE TABLE statement here:

-- 2. Materialized View Pattern
-- Create a table that pre-calculates daily sales statistics
-- Your CREATE TABLE statement here:

-- 3. Partitioning Strategy
-- Design a partitioning strategy for a large orders table
-- Your partitioning approach explanation here:

-- ===================================================================
-- EXERCISE 3.8: CONSTRAINT DESIGN
-- ===================================================================

-- Add appropriate constraints to ensure data integrity:

-- 1. Check constraints for data validation
-- Add constraints to ensure:
--    - Age is between 0 and 120
--    - Price is positive
--    - Email contains '@' symbol
--    - Phone number format is valid

-- Your ALTER TABLE statements here:

-- 2. Foreign key constraints with appropriate actions
-- Design foreign keys with:
--    - CASCADE delete for dependent records
--    - SET NULL for optional references
--    - RESTRICT for critical references

-- Your ALTER TABLE statements here:

-- 3. Unique constraints
-- Ensure uniqueness for:
--    - User email addresses
--    - Product SKUs
--    - Order numbers

-- Your ALTER TABLE statements here:

-- ===================================================================
-- EXERCISE 3.9: REAL-WORLD SCENARIOS
-- ===================================================================

-- Design databases for the following real-world scenarios:

-- 1. Social Media Platform
-- Entities: Users, Posts, Comments, Likes, Follows, Messages
-- Your CREATE TABLE statements here:

-- 2. Hospital Management System
-- Entities: Patients, Doctors, Appointments, Medical Records, Departments
-- Your CREATE TABLE statements here:

-- 3. School Management System
-- Entities: Students, Teachers, Courses, Grades, Schedules, Fees
-- Your CREATE TABLE statements here:

-- 4. Inventory Management System
-- Entities: Products, Suppliers, Purchase Orders, Stock Movements, Locations
-- Your CREATE TABLE statements here:

-- ===================================================================
-- EXERCISE 3.10: DESIGN REVIEW
-- ===================================================================

-- Review and improve the following poorly designed table:

CREATE TABLE bad_user_data (
    user_id INT,
    name VARCHAR(100),
    email VARCHAR(100),
    phone VARCHAR(20),
    address VARCHAR(255),
    city VARCHAR(50),
    state VARCHAR(50),
    zip VARCHAR(10),
    country VARCHAR(50),
    order_id INT,
    order_date DATE,
    product_name VARCHAR(100),
    product_price DECIMAL(10,2),
    quantity INT,
    total_amount DECIMAL(10,2)
);

-- Identify the problems with this design:
-- Your analysis here:

-- Provide an improved design:
-- Your improved CREATE TABLE statements here:

-- ===================================================================
-- BONUS EXERCISE: COMPREHENSIVE DESIGN
-- ===================================================================

-- Design a complete database for a multi-tenant SaaS application
-- Requirements:
-- 1. Multiple organizations (tenants)
-- 2. User management with roles and permissions
-- 3. Data isolation between tenants
-- 4. Audit logging for all changes
-- 5. Soft deletes for data recovery
-- 6. Hierarchical organization structure
-- 7. Flexible configuration system
-- 8. Performance optimization for large datasets

-- Your comprehensive solution here:

-- 1. Tenants table
-- Your CREATE TABLE statement here:

-- 2. Users table (with tenant isolation)
-- Your CREATE TABLE statement here:

-- 3. Roles and permissions tables
-- Your CREATE TABLE statements here:

-- 4. Audit log table
-- Your CREATE TABLE statement here:

-- 5. Configuration table
-- Your CREATE TABLE statement here:

-- 6. Additional tables as needed
-- Your CREATE TABLE statements here:

-- 7. Indexes for performance
-- Your CREATE INDEX statements here:

-- 8. Constraints for data integrity
-- Your ALTER TABLE statements here:
