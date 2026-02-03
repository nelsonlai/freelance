-- ===================================================================
-- Solution 3: Database Design and Normalization - Complete Solutions
-- ===================================================================
-- This file contains complete, commented solutions for all exercises
-- in exercise_03_database_design.sql. Each solution demonstrates:
-- 1. Proper normalization techniques (1NF, 2NF, 3NF, BCNF)
-- 2. Appropriate data type selection
-- 3. Indexing strategies for performance
-- 4. Design patterns and best practices
-- 5. Real-world database design scenarios
-- ===================================================================

-- ===================================================================
-- EXERCISE 3.1: NORMALIZATION PRACTICE - SOLUTIONS
-- ===================================================================

-- Step 1: Create departments table (eliminates transitive dependency)
-- This table stores department information separately to avoid redundancy
CREATE TABLE departments (
    dept_id INT PRIMARY KEY AUTO_INCREMENT,
    dept_name VARCHAR(100) NOT NULL UNIQUE,
    dept_location VARCHAR(100) NOT NULL,
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP
);

-- Step 2: Create employees table (eliminates partial dependency)
-- This table stores employee information with proper foreign key relationships
CREATE TABLE employees (
    emp_id INT PRIMARY KEY AUTO_INCREMENT,
    emp_name VARCHAR(100) NOT NULL,
    dept_id INT NOT NULL,
    manager_id INT NULL, -- Self-referencing foreign key
    hourly_rate DECIMAL(10,2) NOT NULL CHECK (hourly_rate > 0),
    hire_date DATE NOT NULL,
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    FOREIGN KEY (dept_id) REFERENCES departments(dept_id),
    FOREIGN KEY (manager_id) REFERENCES employees(emp_id)
);

-- Step 3: Create projects table (eliminates partial dependency)
-- This table stores project information separately
CREATE TABLE projects (
    project_id INT PRIMARY KEY AUTO_INCREMENT,
    project_name VARCHAR(100) NOT NULL UNIQUE,
    project_start_date DATE NOT NULL,
    project_end_date DATE,
    budget DECIMAL(12,2),
    status ENUM('planning', 'active', 'completed', 'cancelled') DEFAULT 'planning',
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP
);

-- Step 4: Create employee_projects junction table (many-to-many relationship)
-- This table resolves the many-to-many relationship between employees and projects
CREATE TABLE employee_projects (
    emp_id INT NOT NULL,
    project_id INT NOT NULL,
    hours_worked INT NOT NULL DEFAULT 0 CHECK (hours_worked >= 0),
    role VARCHAR(50),
    assigned_date DATE DEFAULT (CURRENT_DATE),
    PRIMARY KEY (emp_id, project_id),
    FOREIGN KEY (emp_id) REFERENCES employees(emp_id) ON DELETE CASCADE,
    FOREIGN KEY (project_id) REFERENCES projects(project_id) ON DELETE CASCADE
);

-- ===================================================================
-- EXERCISE 3.2: LIBRARY MANAGEMENT SYSTEM DESIGN - SOLUTIONS
-- ===================================================================

-- 1. Create books table with proper normalization
CREATE TABLE books (
    book_id INT PRIMARY KEY AUTO_INCREMENT,
    isbn VARCHAR(13) UNIQUE NOT NULL,
    title VARCHAR(255) NOT NULL,
    author VARCHAR(100) NOT NULL,
    publication_year YEAR NOT NULL,
    genre VARCHAR(50) NOT NULL,
    total_copies INT NOT NULL DEFAULT 1 CHECK (total_copies > 0),
    available_copies INT NOT NULL DEFAULT 1 CHECK (available_copies >= 0),
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    updated_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP,
    CHECK (available_copies <= total_copies)
);

-- 2. Create members table with membership types
CREATE TABLE members (
    member_id INT PRIMARY KEY AUTO_INCREMENT,
    first_name VARCHAR(50) NOT NULL,
    last_name VARCHAR(50) NOT NULL,
    email VARCHAR(100) UNIQUE NOT NULL,
    phone VARCHAR(20),
    membership_type ENUM('student', 'regular', 'premium') DEFAULT 'regular',
    join_date DATE NOT NULL DEFAULT (CURRENT_DATE),
    expiry_date DATE,
    is_active BOOLEAN DEFAULT TRUE,
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP
);

-- 3. Create staff table with access levels
CREATE TABLE staff (
    staff_id INT PRIMARY KEY AUTO_INCREMENT,
    first_name VARCHAR(50) NOT NULL,
    last_name VARCHAR(50) NOT NULL,
    email VARCHAR(100) UNIQUE NOT NULL,
    phone VARCHAR(20),
    access_level ENUM('librarian', 'senior_librarian', 'admin') DEFAULT 'librarian',
    hire_date DATE NOT NULL DEFAULT (CURRENT_DATE),
    is_active BOOLEAN DEFAULT TRUE,
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP
);

-- 4. Create borrowings table for book loans
CREATE TABLE borrowings (
    borrowing_id INT PRIMARY KEY AUTO_INCREMENT,
    member_id INT NOT NULL,
    book_id INT NOT NULL,
    borrowed_date DATE NOT NULL DEFAULT (CURRENT_DATE),
    due_date DATE NOT NULL,
    returned_date DATE NULL,
    fine_amount DECIMAL(8,2) DEFAULT 0.00 CHECK (fine_amount >= 0),
    status ENUM('borrowed', 'returned', 'overdue') DEFAULT 'borrowed',
    processed_by INT NOT NULL,
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    FOREIGN KEY (member_id) REFERENCES members(member_id),
    FOREIGN KEY (book_id) REFERENCES books(book_id),
    FOREIGN KEY (processed_by) REFERENCES staff(staff_id),
    CHECK (returned_date IS NULL OR returned_date >= borrowed_date),
    CHECK (due_date > borrowed_date)
);

-- 5. Create reservations table for book reservations
CREATE TABLE reservations (
    reservation_id INT PRIMARY KEY AUTO_INCREMENT,
    member_id INT NOT NULL,
    book_id INT NOT NULL,
    reservation_date DATE NOT NULL DEFAULT (CURRENT_DATE),
    expiry_date DATE NOT NULL,
    status ENUM('active', 'fulfilled', 'expired', 'cancelled') DEFAULT 'active',
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    FOREIGN KEY (member_id) REFERENCES members(member_id),
    FOREIGN KEY (book_id) REFERENCES books(book_id),
    UNIQUE KEY unique_active_reservation (member_id, book_id, status),
    CHECK (expiry_date > reservation_date)
);

-- 6. Create appropriate indexes for performance
CREATE INDEX idx_books_isbn ON books(isbn);
CREATE INDEX idx_books_title ON books(title);
CREATE INDEX idx_books_author ON books(author);
CREATE INDEX idx_books_genre ON books(genre);
CREATE INDEX idx_members_email ON members(email);
CREATE INDEX idx_members_type ON members(membership_type);
CREATE INDEX idx_borrowings_member ON borrowings(member_id);
CREATE INDEX idx_borrowings_book ON borrowings(book_id);
CREATE INDEX idx_borrowings_status ON borrowings(status);
CREATE INDEX idx_borrowings_due_date ON borrowings(due_date);
CREATE INDEX idx_reservations_member ON reservations(member_id);
CREATE INDEX idx_reservations_book ON reservations(book_id);

-- ===================================================================
-- EXERCISE 3.3: E-COMMERCE DATABASE DESIGN - SOLUTIONS
-- ===================================================================

-- 1. Create customers table
CREATE TABLE customers (
    customer_id INT PRIMARY KEY AUTO_INCREMENT,
    first_name VARCHAR(50) NOT NULL,
    last_name VARCHAR(50) NOT NULL,
    email VARCHAR(100) UNIQUE NOT NULL,
    phone VARCHAR(20),
    date_of_birth DATE,
    registration_date DATE NOT NULL DEFAULT (CURRENT_DATE),
    is_active BOOLEAN DEFAULT TRUE,
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    updated_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP
);

-- 2. Create customer_addresses table
CREATE TABLE customer_addresses (
    address_id INT PRIMARY KEY AUTO_INCREMENT,
    customer_id INT NOT NULL,
    address_type ENUM('billing', 'shipping') DEFAULT 'shipping',
    street_address VARCHAR(255) NOT NULL,
    city VARCHAR(100) NOT NULL,
    state VARCHAR(50) NOT NULL,
    postal_code VARCHAR(20) NOT NULL,
    country VARCHAR(50) NOT NULL DEFAULT 'USA',
    is_default BOOLEAN DEFAULT FALSE,
    FOREIGN KEY (customer_id) REFERENCES customers(customer_id) ON DELETE CASCADE
);

-- 3. Create categories table (hierarchical)
CREATE TABLE categories (
    category_id INT PRIMARY KEY AUTO_INCREMENT,
    name VARCHAR(100) NOT NULL UNIQUE,
    description TEXT,
    parent_id INT NULL,
    level INT NOT NULL DEFAULT 0,
    path VARCHAR(500),
    is_active BOOLEAN DEFAULT TRUE,
    FOREIGN KEY (parent_id) REFERENCES categories(category_id)
);

-- 4. Create products table
CREATE TABLE products (
    product_id INT PRIMARY KEY AUTO_INCREMENT,
    sku VARCHAR(50) UNIQUE NOT NULL,
    name VARCHAR(200) NOT NULL,
    description TEXT,
    category_id INT,
    brand VARCHAR(100),
    price DECIMAL(10,2) NOT NULL CHECK (price >= 0),
    cost DECIMAL(10,2) CHECK (cost >= 0),
    weight DECIMAL(8,3),
    dimensions JSON,
    is_active BOOLEAN DEFAULT TRUE,
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    FOREIGN KEY (category_id) REFERENCES categories(category_id)
);

-- 5. Create product_variants table
CREATE TABLE product_variants (
    variant_id INT PRIMARY KEY AUTO_INCREMENT,
    product_id INT NOT NULL,
    sku VARCHAR(50) UNIQUE NOT NULL,
    variant_name VARCHAR(100) NOT NULL,
    attributes JSON,
    price_adjustment DECIMAL(10,2) DEFAULT 0.00,
    inventory_count INT DEFAULT 0 CHECK (inventory_count >= 0),
    is_active BOOLEAN DEFAULT TRUE,
    FOREIGN KEY (product_id) REFERENCES products(product_id) ON DELETE CASCADE
);

-- 6. Create orders table
CREATE TABLE orders (
    order_id INT PRIMARY KEY AUTO_INCREMENT,
    order_number VARCHAR(20) UNIQUE NOT NULL,
    customer_id INT NOT NULL,
    status ENUM('pending', 'processing', 'shipped', 'delivered', 'cancelled') DEFAULT 'pending',
    subtotal DECIMAL(10,2) NOT NULL CHECK (subtotal >= 0),
    tax_amount DECIMAL(10,2) DEFAULT 0.00 CHECK (tax_amount >= 0),
    shipping_amount DECIMAL(10,2) DEFAULT 0.00 CHECK (shipping_amount >= 0),
    total_amount DECIMAL(10,2) NOT NULL CHECK (total_amount >= 0),
    shipping_address JSON,
    billing_address JSON,
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    FOREIGN KEY (customer_id) REFERENCES customers(customer_id)
);

-- 7. Create order_items table
CREATE TABLE order_items (
    order_item_id INT PRIMARY KEY AUTO_INCREMENT,
    order_id INT NOT NULL,
    product_id INT NOT NULL,
    variant_id INT NULL,
    product_name VARCHAR(200) NOT NULL,
    sku VARCHAR(50) NOT NULL,
    quantity INT NOT NULL CHECK (quantity > 0),
    unit_price DECIMAL(10,2) NOT NULL CHECK (unit_price >= 0),
    total_price DECIMAL(10,2) NOT NULL CHECK (total_price >= 0),
    FOREIGN KEY (order_id) REFERENCES orders(order_id) ON DELETE CASCADE,
    FOREIGN KEY (product_id) REFERENCES products(product_id),
    FOREIGN KEY (variant_id) REFERENCES product_variants(variant_id)
);

-- 8. Create inventory table
CREATE TABLE inventory (
    inventory_id INT PRIMARY KEY AUTO_INCREMENT,
    product_id INT NOT NULL,
    variant_id INT NULL,
    location VARCHAR(100) NOT NULL,
    quantity INT NOT NULL DEFAULT 0 CHECK (quantity >= 0),
    reserved_quantity INT DEFAULT 0 CHECK (reserved_quantity >= 0),
    available_quantity INT GENERATED ALWAYS AS (quantity - reserved_quantity) STORED,
    last_updated TIMESTAMP DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP,
    FOREIGN KEY (product_id) REFERENCES products(product_id),
    FOREIGN KEY (variant_id) REFERENCES product_variants(variant_id),
    UNIQUE KEY unique_product_location (product_id, variant_id, location)
);

-- 9. Create reviews table
CREATE TABLE reviews (
    review_id INT PRIMARY KEY AUTO_INCREMENT,
    product_id INT NOT NULL,
    customer_id INT NOT NULL,
    order_id INT NULL,
    rating TINYINT NOT NULL CHECK (rating >= 1 AND rating <= 5),
    title VARCHAR(200),
    content TEXT,
    is_verified_purchase BOOLEAN DEFAULT FALSE,
    is_approved BOOLEAN DEFAULT FALSE,
    helpful_count INT DEFAULT 0 CHECK (helpful_count >= 0),
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    FOREIGN KEY (product_id) REFERENCES products(product_id) ON DELETE CASCADE,
    FOREIGN KEY (customer_id) REFERENCES customers(customer_id) ON DELETE CASCADE,
    FOREIGN KEY (order_id) REFERENCES orders(order_id) ON DELETE SET NULL,
    UNIQUE KEY unique_customer_product_review (customer_id, product_id)
);

-- 10. Create discounts table
CREATE TABLE discounts (
    discount_id INT PRIMARY KEY AUTO_INCREMENT,
    code VARCHAR(50) UNIQUE NOT NULL,
    name VARCHAR(100) NOT NULL,
    description TEXT,
    discount_type ENUM('percentage', 'fixed_amount') NOT NULL,
    discount_value DECIMAL(10,2) NOT NULL CHECK (discount_value > 0),
    min_order_amount DECIMAL(10,2) DEFAULT 0.00,
    max_discount_amount DECIMAL(10,2),
    usage_limit INT,
    used_count INT DEFAULT 0,
    start_date DATE NOT NULL,
    end_date DATE NOT NULL,
    is_active BOOLEAN DEFAULT TRUE,
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    CHECK (end_date > start_date),
    CHECK (used_count <= usage_limit)
);

-- ===================================================================
-- EXERCISE 3.4: DATA TYPE SELECTION - SOLUTIONS
-- ===================================================================

-- 1. User age (0-120 years)
-- Answer: TINYINT UNSIGNED
-- Explanation: Age ranges from 0-120, fits in 1 byte, unsigned for positive values only
CREATE TABLE user_age_example (
    user_id INT PRIMARY KEY,
    age TINYINT UNSIGNED CHECK (age <= 120)
);

-- 2. Product price (with 2 decimal places)
-- Answer: DECIMAL(10,2)
-- Explanation: Exact precision for money, 10 total digits with 2 after decimal
CREATE TABLE product_price_example (
    product_id INT PRIMARY KEY,
    price DECIMAL(10,2) CHECK (price >= 0)
);

-- 3. User email address
-- Answer: VARCHAR(255)
-- Explanation: Variable length, email addresses can be up to 254 characters
CREATE TABLE user_email_example (
    user_id INT PRIMARY KEY,
    email VARCHAR(255) UNIQUE NOT NULL
);

-- 4. Product description (can be very long)
-- Answer: TEXT or LONGTEXT
-- Explanation: TEXT for up to 65KB, LONGTEXT for larger content
CREATE TABLE product_description_example (
    product_id INT PRIMARY KEY,
    description TEXT
);

-- 5. Order status (pending, processing, shipped, delivered, cancelled)
-- Answer: ENUM
-- Explanation: Predefined values, efficient storage, data validation
CREATE TABLE order_status_example (
    order_id INT PRIMARY KEY,
    status ENUM('pending', 'processing', 'shipped', 'delivered', 'cancelled') DEFAULT 'pending'
);

-- 6. User preferences (flexible key-value pairs)
-- Answer: JSON
-- Explanation: Flexible structure, native JSON support in MySQL 5.7+
CREATE TABLE user_preferences_example (
    user_id INT PRIMARY KEY,
    preferences JSON
);

-- 7. Product dimensions (length, width, height)
-- Answer: JSON or separate DECIMAL columns
-- Explanation: JSON for flexibility, separate columns for structured data
CREATE TABLE product_dimensions_example (
    product_id INT PRIMARY KEY,
    dimensions JSON -- {"length": 10.5, "width": 8.0, "height": 2.0}
);

-- 8. Timestamp for when record was created
-- Answer: TIMESTAMP DEFAULT CURRENT_TIMESTAMP
-- Explanation: Automatic timestamp, timezone aware, efficient storage
CREATE TABLE timestamp_example (
    record_id INT PRIMARY KEY,
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP
);

-- ===================================================================
-- EXERCISE 3.5: INDEXING STRATEGIES - SOLUTIONS
-- ===================================================================

-- 1. Find all orders by customer in date range
CREATE INDEX idx_orders_customer_date ON orders(customer_id, created_at);

-- 2. Find products by category and price range
CREATE INDEX idx_products_category_price ON products(category_id, price);

-- 3. Find users who haven't logged in recently
CREATE INDEX idx_customers_registration ON customers(registration_date);

-- 4. Generate monthly sales reports
CREATE INDEX idx_orders_date_total ON orders(created_at, total_amount);

-- 5. Find products with low inventory
CREATE INDEX idx_inventory_quantity ON inventory(quantity, reserved_quantity);

-- ===================================================================
-- EXERCISE 3.6: DESIGN PATTERNS - SOLUTIONS
-- ===================================================================

-- 1. Audit Trail Pattern
CREATE TABLE audit_logs (
    audit_id INT PRIMARY KEY AUTO_INCREMENT,
    entity_type VARCHAR(50) NOT NULL,
    entity_id INT NOT NULL,
    action ENUM('INSERT', 'UPDATE', 'DELETE') NOT NULL,
    old_values JSON,
    new_values JSON,
    changed_by INT,
    changed_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    INDEX idx_audit_entity (entity_type, entity_id),
    INDEX idx_audit_action (action),
    INDEX idx_audit_timestamp (changed_at)
);

-- 2. Soft Delete Pattern
ALTER TABLE products ADD COLUMN is_deleted BOOLEAN DEFAULT FALSE;
ALTER TABLE products ADD COLUMN deleted_at TIMESTAMP NULL;
ALTER TABLE products ADD COLUMN deleted_by INT NULL;
CREATE INDEX idx_products_deleted ON products(is_deleted);

-- 3. Hierarchical Data Pattern
CREATE TABLE organizational_hierarchy (
    employee_id INT PRIMARY KEY,
    name VARCHAR(100) NOT NULL,
    manager_id INT NULL,
    level INT NOT NULL DEFAULT 0,
    path VARCHAR(500),
    FOREIGN KEY (manager_id) REFERENCES organizational_hierarchy(employee_id),
    INDEX idx_hierarchy_manager (manager_id),
    INDEX idx_hierarchy_level (level),
    INDEX idx_hierarchy_path (path)
);

-- 4. Polymorphic Association Pattern
CREATE TABLE comments (
    comment_id INT PRIMARY KEY AUTO_INCREMENT,
    content TEXT NOT NULL,
    commentable_type ENUM('post', 'photo', 'video', 'product') NOT NULL,
    commentable_id INT NOT NULL,
    author_id INT NOT NULL,
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    INDEX idx_commentable (commentable_type, commentable_id),
    INDEX idx_comments_author (author_id)
);

-- ===================================================================
-- EXERCISE 3.7: PERFORMANCE OPTIMIZATION - SOLUTIONS
-- ===================================================================

-- 1. Denormalization for Read-Heavy Application
CREATE TABLE order_summary (
    order_id INT PRIMARY KEY,
    customer_name VARCHAR(100),
    customer_email VARCHAR(100),
    total_amount DECIMAL(10,2),
    item_count INT,
    order_date DATE,
    status VARCHAR(20),
    INDEX idx_summary_customer (customer_name),
    INDEX idx_summary_date (order_date),
    INDEX idx_summary_status (status)
);

-- 2. Materialized View Pattern
CREATE TABLE daily_sales_summary (
    date DATE PRIMARY KEY,
    total_orders INT NOT NULL DEFAULT 0,
    total_revenue DECIMAL(12,2) NOT NULL DEFAULT 0.00,
    average_order_value DECIMAL(10,2) NOT NULL DEFAULT 0.00,
    unique_customers INT NOT NULL DEFAULT 0,
    top_product_id INT,
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    INDEX idx_summary_date (date)
);

-- 3. Partitioning Strategy Explanation
-- For large orders table, consider partitioning by date:
-- ALTER TABLE orders PARTITION BY RANGE (YEAR(created_at)) (
--     PARTITION p2023 VALUES LESS THAN (2024),
--     PARTITION p2024 VALUES LESS THAN (2025),
--     PARTITION p2025 VALUES LESS THAN (2026),
--     PARTITION p_future VALUES LESS THAN MAXVALUE
-- );

-- ===================================================================
-- EXERCISE 3.8: CONSTRAINT DESIGN - SOLUTIONS
-- ===================================================================

-- 1. Check constraints for data validation
ALTER TABLE customers ADD CONSTRAINT check_age_valid CHECK (date_of_birth IS NULL OR date_of_birth <= CURRENT_DATE);
ALTER TABLE products ADD CONSTRAINT check_price_positive CHECK (price > 0);
ALTER TABLE customers ADD CONSTRAINT check_email_format CHECK (email LIKE '%@%');
ALTER TABLE customers ADD CONSTRAINT check_phone_format CHECK (phone IS NULL OR phone REGEXP '^[0-9-+() ]+$');

-- 2. Foreign key constraints with appropriate actions
ALTER TABLE customer_addresses ADD CONSTRAINT fk_customer_addresses_customer 
    FOREIGN KEY (customer_id) REFERENCES customers(customer_id) ON DELETE CASCADE;
ALTER TABLE order_items ADD CONSTRAINT fk_order_items_order 
    FOREIGN KEY (order_id) REFERENCES orders(order_id) ON DELETE CASCADE;
ALTER TABLE reviews ADD CONSTRAINT fk_reviews_order 
    FOREIGN KEY (order_id) REFERENCES orders(order_id) ON DELETE SET NULL;

-- 3. Unique constraints
ALTER TABLE customers ADD CONSTRAINT uk_customers_email UNIQUE (email);
ALTER TABLE products ADD CONSTRAINT uk_products_sku UNIQUE (sku);
ALTER TABLE orders ADD CONSTRAINT uk_orders_number UNIQUE (order_number);

-- ===================================================================
-- EXERCISE 3.9: REAL-WORLD SCENARIOS - SOLUTIONS
-- ===================================================================

-- 1. Social Media Platform
CREATE TABLE social_users (
    user_id INT PRIMARY KEY AUTO_INCREMENT,
    username VARCHAR(50) UNIQUE NOT NULL,
    email VARCHAR(100) UNIQUE NOT NULL,
    full_name VARCHAR(100) NOT NULL,
    bio TEXT,
    profile_picture_url VARCHAR(255),
    is_verified BOOLEAN DEFAULT FALSE,
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP
);

CREATE TABLE posts (
    post_id INT PRIMARY KEY AUTO_INCREMENT,
    user_id INT NOT NULL,
    content TEXT NOT NULL,
    image_url VARCHAR(255),
    likes_count INT DEFAULT 0,
    comments_count INT DEFAULT 0,
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    FOREIGN KEY (user_id) REFERENCES social_users(user_id) ON DELETE CASCADE
);

CREATE TABLE follows (
    follower_id INT NOT NULL,
    following_id INT NOT NULL,
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    PRIMARY KEY (follower_id, following_id),
    FOREIGN KEY (follower_id) REFERENCES social_users(user_id) ON DELETE CASCADE,
    FOREIGN KEY (following_id) REFERENCES social_users(user_id) ON DELETE CASCADE
);

-- 2. Hospital Management System
CREATE TABLE patients (
    patient_id INT PRIMARY KEY AUTO_INCREMENT,
    first_name VARCHAR(50) NOT NULL,
    last_name VARCHAR(50) NOT NULL,
    date_of_birth DATE NOT NULL,
    gender ENUM('M', 'F', 'Other'),
    phone VARCHAR(20),
    emergency_contact VARCHAR(100),
    medical_history TEXT,
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP
);

CREATE TABLE doctors (
    doctor_id INT PRIMARY KEY AUTO_INCREMENT,
    first_name VARCHAR(50) NOT NULL,
    last_name VARCHAR(50) NOT NULL,
    specialization VARCHAR(100) NOT NULL,
    license_number VARCHAR(50) UNIQUE NOT NULL,
    phone VARCHAR(20),
    email VARCHAR(100) UNIQUE NOT NULL,
    is_active BOOLEAN DEFAULT TRUE
);

CREATE TABLE appointments (
    appointment_id INT PRIMARY KEY AUTO_INCREMENT,
    patient_id INT NOT NULL,
    doctor_id INT NOT NULL,
    appointment_date DATE NOT NULL,
    appointment_time TIME NOT NULL,
    status ENUM('scheduled', 'completed', 'cancelled', 'no_show') DEFAULT 'scheduled',
    notes TEXT,
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    FOREIGN KEY (patient_id) REFERENCES patients(patient_id),
    FOREIGN KEY (doctor_id) REFERENCES doctors(doctor_id)
);

-- ===================================================================
-- EXERCISE 3.10: DESIGN REVIEW - SOLUTIONS
-- ===================================================================

-- Problems with the bad_user_data table:
-- 1. Violates 1NF: Multiple values in single row (order_id, product_name, etc.)
-- 2. Violates 2NF: Non-key attributes depend on partial key
-- 3. Violates 3NF: Transitive dependencies (address fields depend on user, not order)
-- 4. Redundant data storage
-- 5. Difficult to maintain and query
-- 6. No proper relationships

-- Improved design:
CREATE TABLE users_improved (
    user_id INT PRIMARY KEY AUTO_INCREMENT,
    first_name VARCHAR(50) NOT NULL,
    last_name VARCHAR(50) NOT NULL,
    email VARCHAR(100) UNIQUE NOT NULL,
    phone VARCHAR(20),
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP
);

CREATE TABLE user_addresses_improved (
    address_id INT PRIMARY KEY AUTO_INCREMENT,
    user_id INT NOT NULL,
    address_type ENUM('home', 'work', 'billing') DEFAULT 'home',
    street_address VARCHAR(255) NOT NULL,
    city VARCHAR(50) NOT NULL,
    state VARCHAR(50) NOT NULL,
    postal_code VARCHAR(10) NOT NULL,
    country VARCHAR(50) NOT NULL DEFAULT 'USA',
    is_default BOOLEAN DEFAULT FALSE,
    FOREIGN KEY (user_id) REFERENCES users_improved(user_id) ON DELETE CASCADE
);

CREATE TABLE orders_improved (
    order_id INT PRIMARY KEY AUTO_INCREMENT,
    user_id INT NOT NULL,
    order_date DATE NOT NULL DEFAULT (CURRENT_DATE),
    total_amount DECIMAL(10,2) NOT NULL CHECK (total_amount >= 0),
    status ENUM('pending', 'processing', 'shipped', 'delivered', 'cancelled') DEFAULT 'pending',
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    FOREIGN KEY (user_id) REFERENCES users_improved(user_id)
);

CREATE TABLE order_items_improved (
    order_item_id INT PRIMARY KEY AUTO_INCREMENT,
    order_id INT NOT NULL,
    product_id INT NOT NULL,
    product_name VARCHAR(100) NOT NULL,
    product_price DECIMAL(10,2) NOT NULL CHECK (product_price >= 0),
    quantity INT NOT NULL CHECK (quantity > 0),
    total_amount DECIMAL(10,2) NOT NULL CHECK (total_amount >= 0),
    FOREIGN KEY (order_id) REFERENCES orders_improved(order_id) ON DELETE CASCADE
);
