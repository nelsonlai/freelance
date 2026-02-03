# Databases Examples
import sqlite3
import json
from sqlalchemy import create_engine, Column, Integer, String, Float, DateTime, ForeignKey
from sqlalchemy.ext.declarative import declarative_base
from sqlalchemy.orm import sessionmaker, relationship
from datetime import datetime
from typing import List, Dict, Any

print("Databases Examples")
print("=" * 20)

# 1. SQLite with sqlite3
print("1. SQLite with sqlite3")
print("-" * 20)

def create_sqlite_database():
    """Create a SQLite database with sample tables."""
    
    # Connect to database (creates if doesn't exist)
    conn = sqlite3.connect('sample.db')
    cursor = conn.cursor()
    
    # Create users table
    cursor.execute('''
        CREATE TABLE IF NOT EXISTS users (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            name TEXT NOT NULL,
            email TEXT UNIQUE NOT NULL,
            age INTEGER,
            created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP
        )
    ''')
    
    # Create posts table
    cursor.execute('''
        CREATE TABLE IF NOT EXISTS posts (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            title TEXT NOT NULL,
            content TEXT,
            user_id INTEGER,
            created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
            FOREIGN KEY (user_id) REFERENCES users (id)
        )
    ''')
    
    # Create comments table
    cursor.execute('''
        CREATE TABLE IF NOT EXISTS comments (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            content TEXT NOT NULL,
            post_id INTEGER,
            user_id INTEGER,
            created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
            FOREIGN KEY (post_id) REFERENCES posts (id),
            FOREIGN KEY (user_id) REFERENCES users (id)
        )
    ''')
    
    conn.commit()
    return conn

def insert_sample_data(conn):
    """Insert sample data into the database."""
    cursor = conn.cursor()
    
    # Insert users
    users = [
        ('Alice Johnson', 'alice@example.com', 25),
        ('Bob Smith', 'bob@example.com', 30),
        ('Charlie Brown', 'charlie@example.com', 35),
        ('Diana Prince', 'diana@example.com', 28)
    ]
    
    cursor.executemany('''
        INSERT INTO users (name, email, age) VALUES (?, ?, ?)
    ''', users)
    
    # Insert posts
    posts = [
        ('First Post', 'This is the first post content', 1),
        ('Second Post', 'This is the second post content', 2),
        ('Third Post', 'This is the third post content', 1),
        ('Fourth Post', 'This is the fourth post content', 3)
    ]
    
    cursor.executemany('''
        INSERT INTO posts (title, content, user_id) VALUES (?, ?, ?)
    ''', posts)
    
    # Insert comments
    comments = [
        ('Great post!', 1, 2),
        ('I agree with this', 1, 3),
        ('Very informative', 2, 1),
        ('Thanks for sharing', 3, 2)
    ]
    
    cursor.executemany('''
        INSERT INTO comments (content, post_id, user_id) VALUES (?, ?, ?)
    ''', comments)
    
    conn.commit()

def query_database(conn):
    """Query the database with various operations."""
    cursor = conn.cursor()
    
    # Select all users
    cursor.execute('SELECT * FROM users')
    users = cursor.fetchall()
    print(f"All users: {users}")
    
    # Select users with age > 25
    cursor.execute('SELECT * FROM users WHERE age > ?', (25,))
    older_users = cursor.fetchall()
    print(f"Users older than 25: {older_users}")
    
    # Join users and posts
    cursor.execute('''
        SELECT u.name, p.title, p.content 
        FROM users u 
        JOIN posts p ON u.id = p.user_id
    ''')
    user_posts = cursor.fetchall()
    print(f"Users and their posts: {user_posts}")
    
    # Count posts per user
    cursor.execute('''
        SELECT u.name, COUNT(p.id) as post_count
        FROM users u
        LEFT JOIN posts p ON u.id = p.user_id
        GROUP BY u.id, u.name
    ''')
    post_counts = cursor.fetchall()
    print(f"Post counts per user: {post_counts}")
    
    # Update user age
    cursor.execute('UPDATE users SET age = ? WHERE id = ?', (26, 1))
    conn.commit()
    
    # Delete a comment
    cursor.execute('DELETE FROM comments WHERE id = ?', (1,))
    conn.commit()
    
    # Select with ORDER BY and LIMIT
    cursor.execute('''
        SELECT * FROM posts 
        ORDER BY created_at DESC 
        LIMIT 2
    ''')
    recent_posts = cursor.fetchall()
    print(f"Recent posts: {recent_posts}")

# Test SQLite operations
conn = create_sqlite_database()
insert_sample_data(conn)
query_database(conn)
conn.close()

# 2. ORM with SQLAlchemy
print("\n2. ORM with SQLAlchemy")
print("-" * 20)

# Create SQLAlchemy engine
engine = create_engine('sqlite:///sample_orm.db', echo=True)
Base = declarative_base()

# Define models
class User(Base):
    __tablename__ = 'users'
    
    id = Column(Integer, primary_key=True)
    name = Column(String(100), nullable=False)
    email = Column(String(100), unique=True, nullable=False)
    age = Column(Integer)
    created_at = Column(DateTime, default=datetime.utcnow)
    
    # Relationship
    posts = relationship("Post", back_populates="author")
    comments = relationship("Comment", back_populates="author")

class Post(Base):
    __tablename__ = 'posts'
    
    id = Column(Integer, primary_key=True)
    title = Column(String(200), nullable=False)
    content = Column(String(1000))
    user_id = Column(Integer, ForeignKey('users.id'))
    created_at = Column(DateTime, default=datetime.utcnow)
    
    # Relationships
    author = relationship("User", back_populates="posts")
    comments = relationship("Comment", back_populates="post")

class Comment(Base):
    __tablename__ = 'comments'
    
    id = Column(Integer, primary_key=True)
    content = Column(String(500), nullable=False)
    post_id = Column(Integer, ForeignKey('posts.id'))
    user_id = Column(Integer, ForeignKey('users.id'))
    created_at = Column(DateTime, default=datetime.utcnow)
    
    # Relationships
    post = relationship("Post", back_populates="comments")
    author = relationship("User", back_populates="comments")

# Create tables
Base.metadata.create_all(engine)

# Create session
Session = sessionmaker(bind=engine)
session = Session()

def create_sample_data():
    """Create sample data using ORM."""
    
    # Create users
    users = [
        User(name='Alice Johnson', email='alice@example.com', age=25),
        User(name='Bob Smith', email='bob@example.com', age=30),
        User(name='Charlie Brown', email='charlie@example.com', age=35),
        User(name='Diana Prince', email='diana@example.com', age=28)
    ]
    
    for user in users:
        session.add(user)
    
    session.commit()
    
    # Create posts
    posts = [
        Post(title='First Post', content='This is the first post content', user_id=1),
        Post(title='Second Post', content='This is the second post content', user_id=2),
        Post(title='Third Post', content='This is the third post content', user_id=1),
        Post(title='Fourth Post', content='This is the fourth post content', user_id=3)
    ]
    
    for post in posts:
        session.add(post)
    
    session.commit()
    
    # Create comments
    comments = [
        Comment(content='Great post!', post_id=1, user_id=2),
        Comment(content='I agree with this', post_id=1, user_id=3),
        Comment(content='Very informative', post_id=2, user_id=1),
        Comment(content='Thanks for sharing', post_id=3, user_id=2)
    ]
    
    for comment in comments:
        session.add(comment)
    
    session.commit()

def query_with_orm():
    """Query the database using ORM."""
    
    # Get all users
    users = session.query(User).all()
    print(f"All users: {[(u.name, u.email, u.age) for u in users]}")
    
    # Get user by ID
    user = session.query(User).filter(User.id == 1).first()
    print(f"User with ID 1: {user.name if user else 'Not found'}")
    
    # Get users with age > 25
    older_users = session.query(User).filter(User.age > 25).all()
    print(f"Users older than 25: {[(u.name, u.age) for u in older_users]}")
    
    # Get user with posts
    user_with_posts = session.query(User).filter(User.id == 1).first()
    if user_with_posts:
        print(f"Posts by {user_with_posts.name}: {[(p.title, p.content) for p in user_with_posts.posts]}")
    
    # Get posts with comments
    posts_with_comments = session.query(Post).all()
    for post in posts_with_comments:
        print(f"Post '{post.title}' has {len(post.comments)} comments")
    
    # Update user
    user_to_update = session.query(User).filter(User.id == 1).first()
    if user_to_update:
        user_to_update.age = 26
        session.commit()
        print(f"Updated user age: {user_to_update.age}")
    
    # Delete comment
    comment_to_delete = session.query(Comment).filter(Comment.id == 1).first()
    if comment_to_delete:
        session.delete(comment_to_delete)
        session.commit()
        print("Comment deleted")
    
    # Complex query with joins
    result = session.query(User.name, Post.title).join(Post).all()
    print(f"Users and their posts: {result}")
    
    # Aggregation
    post_counts = session.query(User.name, session.query(Post).filter(Post.user_id == User.id).count().label('post_count')).all()
    print(f"Post counts per user: {post_counts}")

# Test ORM operations
create_sample_data()
query_with_orm()
session.close()

# 3. Database Transactions
print("\n3. Database Transactions")
print("-" * 25)

def demonstrate_transactions():
    """Demonstrate database transactions."""
    
    # SQLite transaction example
    conn = sqlite3.connect('transaction_test.db')
    cursor = conn.cursor()
    
    # Create table
    cursor.execute('''
        CREATE TABLE IF NOT EXISTS accounts (
            id INTEGER PRIMARY KEY,
            name TEXT NOT NULL,
            balance REAL NOT NULL
        )
    ''')
    
    # Insert sample data
    cursor.execute('INSERT INTO accounts (name, balance) VALUES (?, ?)', ('Alice', 1000.0))
    cursor.execute('INSERT INTO accounts (name, balance) VALUES (?, ?)', ('Bob', 500.0))
    conn.commit()
    
    def transfer_money(from_account, to_account, amount):
        """Transfer money between accounts using transactions."""
        try:
            # Start transaction
            conn.execute('BEGIN TRANSACTION')
            
            # Check if from_account has enough balance
            cursor.execute('SELECT balance FROM accounts WHERE id = ?', (from_account,))
            from_balance = cursor.fetchone()[0]
            
            if from_balance < amount:
                raise ValueError("Insufficient balance")
            
            # Update balances
            cursor.execute('UPDATE accounts SET balance = balance - ? WHERE id = ?', (amount, from_account))
            cursor.execute('UPDATE accounts SET balance = balance + ? WHERE id = ?', (amount, to_account))
            
            # Commit transaction
            conn.commit()
            print(f"Successfully transferred ${amount} from account {from_account} to account {to_account}")
            
        except Exception as e:
            # Rollback transaction
            conn.rollback()
            print(f"Transaction failed: {e}")
    
    # Test successful transfer
    transfer_money(1, 2, 200.0)
    
    # Test failed transfer (insufficient balance)
    transfer_money(2, 1, 1000.0)
    
    # Check final balances
    cursor.execute('SELECT name, balance FROM accounts')
    balances = cursor.fetchall()
    print(f"Final balances: {balances}")
    
    conn.close()

# Test transactions
demonstrate_transactions()

# 4. Database Migrations
print("\n4. Database Migrations")
print("-" * 22)

def create_migration_system():
    """Create a simple migration system."""
    
    class Migration:
        def __init__(self, version, description):
            self.version = version
            self.description = description
        
        def up(self, conn):
            """Apply migration."""
            pass
        
        def down(self, conn):
            """Rollback migration."""
            pass
    
    class CreateUsersTable(Migration):
        def __init__(self):
            super().__init__(1, "Create users table")
        
        def up(self, conn):
            cursor = conn.cursor()
            cursor.execute('''
                CREATE TABLE users (
                    id INTEGER PRIMARY KEY,
                    name TEXT NOT NULL,
                    email TEXT UNIQUE NOT NULL
                )
            ''')
            conn.commit()
        
        def down(self, conn):
            cursor = conn.cursor()
            cursor.execute('DROP TABLE users')
            conn.commit()
    
    class AddAgeToUsers(Migration):
        def __init__(self):
            super().__init__(2, "Add age column to users table")
        
        def up(self, conn):
            cursor = conn.cursor()
            cursor.execute('ALTER TABLE users ADD COLUMN age INTEGER')
            conn.commit()
        
        def down(self, conn):
            cursor = conn.cursor()
            # SQLite doesn't support DROP COLUMN, so we'll recreate the table
            cursor.execute('''
                CREATE TABLE users_backup AS SELECT id, name, email FROM users
            ''')
            cursor.execute('DROP TABLE users')
            cursor.execute('''
                CREATE TABLE users (
                    id INTEGER PRIMARY KEY,
                    name TEXT NOT NULL,
                    email TEXT UNIQUE NOT NULL
                )
            ''')
            cursor.execute('''
                INSERT INTO users SELECT * FROM users_backup
            ''')
            cursor.execute('DROP TABLE users_backup')
            conn.commit()
    
    class MigrationManager:
        def __init__(self, db_path):
            self.db_path = db_path
            self.migrations = [
                CreateUsersTable(),
                AddAgeToUsers()
            ]
        
        def create_migrations_table(self, conn):
            """Create migrations tracking table."""
            cursor = conn.cursor()
            cursor.execute('''
                CREATE TABLE IF NOT EXISTS migrations (
                    version INTEGER PRIMARY KEY,
                    description TEXT,
                    applied_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP
                )
            ''')
            conn.commit()
        
        def get_applied_migrations(self, conn):
            """Get list of applied migrations."""
            cursor = conn.cursor()
            cursor.execute('SELECT version FROM migrations ORDER BY version')
            return [row[0] for row in cursor.fetchall()]
        
        def apply_migration(self, conn, migration):
            """Apply a migration."""
            cursor = conn.cursor()
            migration.up(conn)
            cursor.execute('''
                INSERT INTO migrations (version, description) VALUES (?, ?)
            ''', (migration.version, migration.description))
            conn.commit()
        
        def rollback_migration(self, conn, migration):
            """Rollback a migration."""
            cursor = conn.cursor()
            migration.down(conn)
            cursor.execute('DELETE FROM migrations WHERE version = ?', (migration.version,))
            conn.commit()
        
        def migrate(self):
            """Apply all pending migrations."""
            conn = sqlite3.connect(self.db_path)
            self.create_migrations_table(conn)
            applied = self.get_applied_migrations(conn)
            
            for migration in self.migrations:
                if migration.version not in applied:
                    print(f"Applying migration {migration.version}: {migration.description}")
                    self.apply_migration(conn, migration)
            
            conn.close()
        
        def rollback(self, version):
            """Rollback to a specific version."""
            conn = sqlite3.connect(self.db_path)
            applied = self.get_applied_migrations(conn)
            
            for migration in reversed(self.migrations):
                if migration.version > version and migration.version in applied:
                    print(f"Rolling back migration {migration.version}: {migration.description}")
                    self.rollback_migration(conn, migration)
            
            conn.close()
    
    return MigrationManager

# Test migrations
MigrationManager = create_migration_system()
migration_manager = MigrationManager('migration_test.db')
migration_manager.migrate()

# Check if migrations were applied
conn = sqlite3.connect('migration_test.db')
cursor = conn.cursor()
cursor.execute('SELECT * FROM migrations')
migrations = cursor.fetchall()
print(f"Applied migrations: {migrations}")

cursor.execute('PRAGMA table_info(users)')
users_schema = cursor.fetchall()
print(f"Users table schema: {users_schema}")

conn.close()

# 5. Query Optimization
print("\n5. Query Optimization")
print("-" * 22)

def demonstrate_query_optimization():
    """Demonstrate query optimization techniques."""
    
    conn = sqlite3.connect('optimization_test.db')
    cursor = conn.cursor()
    
    # Create tables with indexes
    cursor.execute('''
        CREATE TABLE IF NOT EXISTS products (
            id INTEGER PRIMARY KEY,
            name TEXT NOT NULL,
            category TEXT NOT NULL,
            price REAL NOT NULL,
            created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP
        )
    ''')
    
    cursor.execute('''
        CREATE TABLE IF NOT EXISTS orders (
            id INTEGER PRIMARY KEY,
            product_id INTEGER NOT NULL,
            quantity INTEGER NOT NULL,
            order_date TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
            FOREIGN KEY (product_id) REFERENCES products (id)
        )
    ''')
    
    # Create indexes for better performance
    cursor.execute('CREATE INDEX IF NOT EXISTS idx_products_category ON products (category)')
    cursor.execute('CREATE INDEX IF NOT EXISTS idx_products_price ON products (price)')
    cursor.execute('CREATE INDEX IF NOT EXISTS idx_orders_product_id ON orders (product_id)')
    cursor.execute('CREATE INDEX IF NOT EXISTS idx_orders_date ON orders (order_date)')
    
    # Insert sample data
    products = [
        ('Laptop', 'Electronics', 999.99),
        ('Mouse', 'Electronics', 29.99),
        ('Keyboard', 'Electronics', 79.99),
        ('Book', 'Education', 19.99),
        ('Pen', 'Education', 2.99)
    ]
    
    cursor.executemany('''
        INSERT INTO products (name, category, price) VALUES (?, ?, ?)
    ''', products)
    
    orders = [
        (1, 2),  # 2 laptops
        (2, 5),  # 5 mice
        (3, 1),  # 1 keyboard
        (4, 3),  # 3 books
        (5, 10)  # 10 pens
    ]
    
    cursor.executemany('''
        INSERT INTO orders (product_id, quantity) VALUES (?, ?)
    ''', orders)
    
    conn.commit()
    
    # Optimized queries
    print("Optimized queries:")
    
    # Use EXPLAIN QUERY PLAN to analyze queries
    cursor.execute('EXPLAIN QUERY PLAN SELECT * FROM products WHERE category = ?', ('Electronics',))
    explain_result = cursor.fetchall()
    print(f"Query plan for category filter: {explain_result}")
    
    # Use LIMIT for pagination
    cursor.execute('SELECT * FROM products ORDER BY price DESC LIMIT 3')
    top_products = cursor.fetchall()
    print(f"Top 3 products by price: {top_products}")
    
    # Use JOIN instead of subqueries
    cursor.execute('''
        SELECT p.name, p.price, o.quantity, (p.price * o.quantity) as total
        FROM products p
        JOIN orders o ON p.id = o.product_id
        ORDER BY total DESC
    ''')
    order_totals = cursor.fetchall()
    print(f"Order totals: {order_totals}")
    
    # Use prepared statements
    def get_products_by_category(category):
        cursor.execute('SELECT * FROM products WHERE category = ?', (category,))
        return cursor.fetchall()
    
    electronics = get_products_by_category('Electronics')
    print(f"Electronics products: {electronics}")
    
    conn.close()

# Test query optimization
demonstrate_query_optimization()

# 6. Database Connection Pooling
print("\n6. Database Connection Pooling")
print("-" * 30)

def create_connection_pool():
    """Create a simple connection pool."""
    
    import threading
    import queue
    
    class ConnectionPool:
        def __init__(self, db_path, max_connections=5):
            self.db_path = db_path
            self.max_connections = max_connections
            self.pool = queue.Queue(maxsize=max_connections)
            self.lock = threading.Lock()
            
            # Initialize connections
            for _ in range(max_connections):
                conn = sqlite3.connect(db_path)
                self.pool.put(conn)
        
        def get_connection(self):
            """Get a connection from the pool."""
            return self.pool.get()
        
        def return_connection(self, conn):
            """Return a connection to the pool."""
            self.pool.put(conn)
        
        def close_all(self):
            """Close all connections in the pool."""
            while not self.pool.empty():
                conn = self.pool.get()
                conn.close()
    
    return ConnectionPool

# Test connection pooling
ConnectionPool = create_connection_pool()
pool = ConnectionPool('pool_test.db', max_connections=3)

# Create table
conn = pool.get_connection()
cursor = conn.cursor()
cursor.execute('''
    CREATE TABLE IF NOT EXISTS test_table (
        id INTEGER PRIMARY KEY,
        data TEXT
    )
''')
conn.commit()
pool.return_connection(conn)

# Use connections from pool
def use_connection():
    conn = pool.get_connection()
    cursor = conn.cursor()
    cursor.execute('INSERT INTO test_table (data) VALUES (?)', ('test data',))
    conn.commit()
    pool.return_connection(conn)

# Test with multiple threads
import threading

threads = []
for i in range(5):
    thread = threading.Thread(target=use_connection)
    threads.append(thread)
    thread.start()

for thread in threads:
    thread.join()

# Check results
conn = pool.get_connection()
cursor = conn.cursor()
cursor.execute('SELECT COUNT(*) FROM test_table')
count = cursor.fetchone()[0]
print(f"Records in test_table: {count}")
pool.return_connection(conn)

pool.close_all()

print("\nDatabases examples completed!")