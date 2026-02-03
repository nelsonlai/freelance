# 7. Databases and ORMs - Data Persistence

Databases are essential for storing and managing data in applications. This lesson covers SQLite, SQLAlchemy ORM, database design, and advanced database operations for professional Python development.

## SQLite Fundamentals

### Basic SQLite Operations

```python
import sqlite3
import json
from datetime import datetime
from contextlib import contextmanager

@contextmanager
def get_db_connection(db_path='example.db'):
    """Context manager for database connections."""
    conn = sqlite3.connect(db_path)
    conn.row_factory = sqlite3.Row  # Enable dict-like access
    try:
        yield conn
    finally:
        conn.close()

def create_tables():
    """Create database tables."""
    with get_db_connection() as conn:
        cursor = conn.cursor()
        
        # Users table
        cursor.execute('''
            CREATE TABLE IF NOT EXISTS users (
                id INTEGER PRIMARY KEY AUTOINCREMENT,
                username TEXT UNIQUE NOT NULL,
                email TEXT UNIQUE NOT NULL,
                created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP
            )
        ''')
        
        # Posts table
        cursor.execute('''
            CREATE TABLE IF NOT EXISTS posts (
                id INTEGER PRIMARY KEY AUTOINCREMENT,
                title TEXT NOT NULL,
                content TEXT NOT NULL,
                author_id INTEGER,
                created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
                FOREIGN KEY (author_id) REFERENCES users (id)
            )
        ''')
        
        # Comments table
        cursor.execute('''
            CREATE TABLE IF NOT EXISTS comments (
                id INTEGER PRIMARY KEY AUTOINCREMENT,
                content TEXT NOT NULL,
                post_id INTEGER,
                author_id INTEGER,
                created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
                FOREIGN KEY (post_id) REFERENCES posts (id),
                FOREIGN KEY (author_id) REFERENCES users (id)
            )
        ''')
        
        conn.commit()
        print("Tables created successfully")

def insert_sample_data():
    """Insert sample data into tables."""
    with get_db_connection() as conn:
        cursor = conn.cursor()
        
        # Insert users
        users = [
            ('alice', 'alice@example.com'),
            ('bob', 'bob@example.com'),
            ('charlie', 'charlie@example.com')
        ]
        
        cursor.executemany(
            'INSERT OR IGNORE INTO users (username, email) VALUES (?, ?)',
            users
        )
        
        # Insert posts
        posts = [
            ('Python Programming', 'Python is a great programming language.', 1),
            ('Web Development', 'Building web applications with Python.', 2),
            ('Data Science', 'Using Python for data analysis.', 1),
            ('Machine Learning', 'Introduction to ML with Python.', 3)
        ]
        
        cursor.executemany(
            'INSERT OR IGNORE INTO posts (title, content, author_id) VALUES (?, ?, ?)',
            posts
        )
        
        # Insert comments
        comments = [
            ('Great post!', 1, 2),
            ('Very informative.', 1, 3),
            ('Thanks for sharing.', 2, 1),
            ('Looking forward to more.', 3, 2)
        ]
        
        cursor.executemany(
            'INSERT OR IGNORE INTO comments (content, post_id, author_id) VALUES (?, ?, ?)',
            comments
        )
        
        conn.commit()
        print("Sample data inserted successfully")

def basic_queries():
    """Demonstrate basic SQL queries."""
    print("\n=== Basic SQL Queries ===")
    
    with get_db_connection() as conn:
        cursor = conn.cursor()
        
        # Select all users
        cursor.execute('SELECT * FROM users')
        users = cursor.fetchall()
        print("All users:")
        for user in users:
            print(f"  {dict(user)}")
        
        # Select users with posts
        cursor.execute('''
            SELECT u.username, COUNT(p.id) as post_count
            FROM users u
            LEFT JOIN posts p ON u.id = p.author_id
            GROUP BY u.id, u.username
            ORDER BY post_count DESC
        ''')
        
        user_stats = cursor.fetchall()
        print("\nUsers with post counts:")
        for stat in user_stats:
            print(f"  {dict(stat)}")
        
        # Complex query with joins
        cursor.execute('''
            SELECT p.title, u.username, COUNT(c.id) as comment_count
            FROM posts p
            JOIN users u ON p.author_id = u.id
            LEFT JOIN comments c ON p.id = c.post_id
            GROUP BY p.id, p.title, u.username
            ORDER BY comment_count DESC
        ''')
        
        post_stats = cursor.fetchall()
        print("\nPosts with comment counts:")
        for stat in post_stats:
            print(f"  {dict(stat)}")

def advanced_queries():
    """Demonstrate advanced SQL queries."""
    print("\n=== Advanced SQL Queries ===")
    
    with get_db_connection() as conn:
        cursor = conn.cursor()
        
        # Subquery example
        cursor.execute('''
            SELECT username, email
            FROM users
            WHERE id IN (
                SELECT DISTINCT author_id
                FROM posts
                WHERE created_at > date('now', '-30 days')
            )
        ''')
        
        active_users = cursor.fetchall()
        print("Active users (posted in last 30 days):")
        for user in active_users:
            print(f"  {dict(user)}")
        
        # Window function example
        cursor.execute('''
            SELECT 
                title,
                username,
                created_at,
                ROW_NUMBER() OVER (PARTITION BY author_id ORDER BY created_at) as post_number
            FROM posts p
            JOIN users u ON p.author_id = u.id
            ORDER BY u.username, post_number
        ''')
        
        numbered_posts = cursor.fetchall()
        print("\nPosts with row numbers:")
        for post in numbered_posts:
            print(f"  {dict(post)}")
        
        # Common Table Expression (CTE)
        cursor.execute('''
            WITH user_activity AS (
                SELECT 
                    u.id,
                    u.username,
                    COUNT(p.id) as posts,
                    COUNT(c.id) as comments
                FROM users u
                LEFT JOIN posts p ON u.id = p.author_id
                LEFT JOIN comments c ON u.id = c.author_id
                GROUP BY u.id, u.username
            )
            SELECT username, posts, comments, (posts + comments) as total_activity
            FROM user_activity
            ORDER BY total_activity DESC
        ''')
        
        activity_stats = cursor.fetchall()
        print("\nUser activity summary:")
        for stat in activity_stats:
            print(f"  {dict(stat)}")

# Run SQLite examples
create_tables()
insert_sample_data()
basic_queries()
advanced_queries()
```

### Database Transactions and Error Handling

```python
def transaction_example():
    """Demonstrate database transactions."""
    print("\n=== Database Transactions ===")
    
    with get_db_connection() as conn:
        try:
            cursor = conn.cursor()
            
            # Start transaction
            conn.execute('BEGIN TRANSACTION')
            
            # Insert user
            cursor.execute(
                'INSERT INTO users (username, email) VALUES (?, ?)',
                ('david', 'david@example.com')
            )
            user_id = cursor.lastrowid
            
            # Insert post for the user
            cursor.execute(
                'INSERT INTO posts (title, content, author_id) VALUES (?, ?, ?)',
                ('Database Design', 'Best practices for database design.', user_id)
            )
            
            # Commit transaction
            conn.commit()
            print("Transaction committed successfully")
            
        except sqlite3.Error as e:
            # Rollback on error
            conn.rollback()
            print(f"Transaction rolled back due to error: {e}")

def error_handling_example():
    """Demonstrate error handling."""
    print("\n=== Error Handling ===")
    
    with get_db_connection() as conn:
        cursor = conn.cursor()
        
        # Try to insert duplicate user
        try:
            cursor.execute(
                'INSERT INTO users (username, email) VALUES (?, ?)',
                ('alice', 'alice@example.com')  # Duplicate username
            )
            conn.commit()
        except sqlite3.IntegrityError as e:
            print(f"Integrity error: {e}")
        
        # Try to insert invalid data
        try:
            cursor.execute(
                'INSERT INTO posts (title, content, author_id) VALUES (?, ?, ?)',
                ('Test Post', 'Content', 999)  # Invalid author_id
            )
            conn.commit()
        except sqlite3.IntegrityError as e:
            print(f"Foreign key constraint error: {e}")

transaction_example()
error_handling_example()
```

## SQLAlchemy ORM

### Basic SQLAlchemy Setup

```python
from sqlalchemy import create_engine, Column, Integer, String, DateTime, ForeignKey, Text
from sqlalchemy.ext.declarative import declarative_base
from sqlalchemy.orm import sessionmaker, relationship, joinedload
from sqlalchemy.exc import IntegrityError
from datetime import datetime

# Database setup
engine = create_engine('sqlite:///sqlalchemy_example.db', echo=True)
Base = declarative_base()
Session = sessionmaker(bind=engine)

# Models
class User(Base):
    __tablename__ = 'users'
    
    id = Column(Integer, primary_key=True)
    username = Column(String(50), unique=True, nullable=False)
    email = Column(String(100), unique=True, nullable=False)
    created_at = Column(DateTime, default=datetime.utcnow)
    
    # Relationships
    posts = relationship("Post", back_populates="author", cascade="all, delete-orphan")
    comments = relationship("Comment", back_populates="author")
    
    def __repr__(self):
        return f"<User(username='{self.username}', email='{self.email}')>"

class Post(Base):
    __tablename__ = 'posts'
    
    id = Column(Integer, primary_key=True)
    title = Column(String(200), nullable=False)
    content = Column(Text, nullable=False)
    author_id = Column(Integer, ForeignKey('users.id'), nullable=False)
    created_at = Column(DateTime, default=datetime.utcnow)
    
    # Relationships
    author = relationship("User", back_populates="posts")
    comments = relationship("Comment", back_populates="post", cascade="all, delete-orphan")
    
    def __repr__(self):
        return f"<Post(title='{self.title}', author='{self.author.username if self.author else None}')>"

class Comment(Base):
    __tablename__ = 'comments'
    
    id = Column(Integer, primary_key=True)
    content = Column(Text, nullable=False)
    post_id = Column(Integer, ForeignKey('posts.id'), nullable=False)
    author_id = Column(Integer, ForeignKey('users.id'), nullable=False)
    created_at = Column(DateTime, default=datetime.utcnow)
    
    # Relationships
    post = relationship("Post", back_populates="comments")
    author = relationship("User", back_populates="comments")
    
    def __repr__(self):
        return f"<Comment(author='{self.author.username if self.author else None}', post='{self.post.title if self.post else None}')>"

# Create tables
Base.metadata.create_all(engine)

def sqlalchemy_basic_operations():
    """Demonstrate basic SQLAlchemy operations."""
    print("\n=== SQLAlchemy Basic Operations ===")
    
    session = Session()
    
    try:
        # Create users
        user1 = User(username='alice', email='alice@example.com')
        user2 = User(username='bob', email='bob@example.com')
        
        session.add(user1)
        session.add(user2)
        session.commit()
        
        print("Users created successfully")
        
        # Create posts
        post1 = Post(title='Python Basics', content='Introduction to Python programming.', author=user1)
        post2 = Post(title='Web Development', content='Building web apps with Flask.', author=user2)
        
        session.add(post1)
        session.add(post2)
        session.commit()
        
        print("Posts created successfully")
        
        # Query users
        users = session.query(User).all()
        print(f"\nAll users: {users}")
        
        # Query posts with authors
        posts = session.query(Post).options(joinedload(Post.author)).all()
        print(f"\nAll posts with authors:")
        for post in posts:
            print(f"  {post}")
        
        # Query with filters
        alice_posts = session.query(Post).join(User).filter(User.username == 'alice').all()
        print(f"\nAlice's posts: {alice_posts}")
        
    except IntegrityError as e:
        session.rollback()
        print(f"Integrity error: {e}")
    finally:
        session.close()

def sqlalchemy_relationships():
    """Demonstrate SQLAlchemy relationships."""
    print("\n=== SQLAlchemy Relationships ===")
    
    session = Session()
    
    try:
        # Get user with posts
        user = session.query(User).options(joinedload(User.posts)).filter(User.username == 'alice').first()
        if user:
            print(f"User: {user}")
            print(f"Posts: {user.posts}")
            
            # Create comment
            if user.posts:
                comment = Comment(
                    content='Great post!',
                    post=user.posts[0],
                    author=user
                )
                session.add(comment)
                session.commit()
                print(f"Comment created: {comment}")
        
        # Get post with comments and author
        post = session.query(Post).options(
            joinedload(Post.author),
            joinedload(Post.comments).joinedload(Comment.author)
        ).first()
        
        if post:
            print(f"\nPost: {post}")
            print(f"Author: {post.author}")
            print(f"Comments: {post.comments}")
        
    except Exception as e:
        session.rollback()
        print(f"Error: {e}")
    finally:
        session.close()

def sqlalchemy_advanced_queries():
    """Demonstrate advanced SQLAlchemy queries."""
    print("\n=== Advanced SQLAlchemy Queries ===")
    
    session = Session()
    
    try:
        # Aggregate queries
        from sqlalchemy import func
        
        # Count posts per user
        post_counts = session.query(
            User.username,
            func.count(Post.id).label('post_count')
        ).outerjoin(Post).group_by(User.id, User.username).all()
        
        print("Posts per user:")
        for username, count in post_counts:
            print(f"  {username}: {count} posts")
        
        # Complex query with subquery
        subquery = session.query(Post.author_id).filter(
            Post.created_at > datetime.utcnow().replace(day=1)
        ).subquery()
        
        active_users = session.query(User).filter(User.id.in_(subquery)).all()
        print(f"\nActive users this month: {active_users}")
        
        # Update operations
        session.query(Post).filter(Post.title.like('%Python%')).update({
            'content': Post.content + ' [Updated]'
        })
        session.commit()
        print("Posts updated successfully")
        
        # Delete operations
        deleted_count = session.query(Comment).filter(
            Comment.content == 'Great post!'
        ).delete()
        session.commit()
        print(f"Deleted {deleted_count} comments")
        
    except Exception as e:
        session.rollback()
        print(f"Error: {e}")
    finally:
        session.close()

# Run SQLAlchemy examples
sqlalchemy_basic_operations()
sqlalchemy_relationships()
sqlalchemy_advanced_queries()
```

### Advanced SQLAlchemy Features

```python
from sqlalchemy import event, Index
from sqlalchemy.orm import validates
from sqlalchemy.ext.hybrid import hybrid_property
import re

class AdvancedUser(Base):
    __tablename__ = 'advanced_users'
    
    id = Column(Integer, primary_key=True)
    username = Column(String(50), unique=True, nullable=False)
    email = Column(String(100), unique=True, nullable=False)
    first_name = Column(String(50))
    last_name = Column(String(50))
    created_at = Column(DateTime, default=datetime.utcnow)
    
    @validates('email')
    def validate_email(self, key, address):
        """Validate email format."""
        if not re.match(r'^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}$', address):
            raise ValueError('Invalid email format')
        return address
    
    @validates('username')
    def validate_username(self, key, username):
        """Validate username."""
        if len(username) < 3:
            raise ValueError('Username must be at least 3 characters')
        if not username.isalnum():
            raise ValueError('Username must be alphanumeric')
        return username
    
    @hybrid_property
    def full_name(self):
        """Get full name."""
        if self.first_name and self.last_name:
            return f"{self.first_name} {self.last_name}"
        return self.username
    
    @full_name.expression
    def full_name(cls):
        """SQL expression for full name."""
        return func.concat(cls.first_name, ' ', cls.last_name)
    
    def __repr__(self):
        return f"<AdvancedUser(username='{self.username}', full_name='{self.full_name}')>"

# Create index for better performance
Index('idx_username', AdvancedUser.username)
Index('idx_email', AdvancedUser.email)

# Event listeners
@event.listens_for(AdvancedUser, 'before_insert')
def before_insert(mapper, connection, target):
    """Called before inserting a new user."""
    target.username = target.username.lower()
    target.email = target.email.lower()

@event.listens_for(AdvancedUser, 'after_insert')
def after_insert(mapper, connection, target):
    """Called after inserting a new user."""
    print(f"New user created: {target.username}")

def advanced_sqlalchemy_features():
    """Demonstrate advanced SQLAlchemy features."""
    print("\n=== Advanced SQLAlchemy Features ===")
    
    # Create table
    Base.metadata.create_all(engine)
    
    session = Session()
    
    try:
        # Create user with validation
        user = AdvancedUser(
            username='john_doe',
            email='john.doe@example.com',
            first_name='John',
            last_name='Doe'
        )
        
        session.add(user)
        session.commit()
        print(f"User created: {user}")
        print(f"Full name: {user.full_name}")
        
        # Test validation
        try:
            invalid_user = AdvancedUser(
                username='ab',  # Too short
                email='invalid-email',  # Invalid format
                first_name='Invalid',
                last_name='User'
            )
            session.add(invalid_user)
            session.commit()
        except ValueError as e:
            session.rollback()
            print(f"Validation error: {e}")
        
        # Query with hybrid property
        users = session.query(AdvancedUser).all()
        for user in users:
            print(f"User: {user.full_name}")
        
    except Exception as e:
        session.rollback()
        print(f"Error: {e}")
    finally:
        session.close()

advanced_sqlalchemy_features()
```

## Database Design Patterns

### Repository Pattern

```python
from abc import ABC, abstractmethod
from typing import List, Optional

class UserRepository(ABC):
    """Abstract user repository."""
    
    @abstractmethod
    def create(self, user: User) -> User:
        pass
    
    @abstractmethod
    def get_by_id(self, user_id: int) -> Optional[User]:
        pass
    
    @abstractmethod
    def get_by_username(self, username: str) -> Optional[User]:
        pass
    
    @abstractmethod
    def get_all(self) -> List[User]:
        pass
    
    @abstractmethod
    def update(self, user: User) -> User:
        pass
    
    @abstractmethod
    def delete(self, user_id: int) -> bool:
        pass

class SQLAlchemyUserRepository(UserRepository):
    """SQLAlchemy implementation of user repository."""
    
    def __init__(self, session):
        self.session = session
    
    def create(self, user: User) -> User:
        self.session.add(user)
        self.session.commit()
        return user
    
    def get_by_id(self, user_id: int) -> Optional[User]:
        return self.session.query(User).filter(User.id == user_id).first()
    
    def get_by_username(self, username: str) -> Optional[User]:
        return self.session.query(User).filter(User.username == username).first()
    
    def get_all(self) -> List[User]:
        return self.session.query(User).all()
    
    def update(self, user: User) -> User:
        self.session.commit()
        return user
    
    def delete(self, user_id: int) -> bool:
        user = self.get_by_id(user_id)
        if user:
            self.session.delete(user)
            self.session.commit()
            return True
        return False

# Unit of Work pattern
class UnitOfWork:
    """Unit of Work pattern for managing transactions."""
    
    def __init__(self):
        self.session = Session()
        self.user_repository = SQLAlchemyUserRepository(self.session)
    
    def __enter__(self):
        return self
    
    def __exit__(self, exc_type, exc_val, exc_tb):
        if exc_type:
            self.session.rollback()
        else:
            self.session.commit()
        self.session.close()
    
    def commit(self):
        self.session.commit()
    
    def rollback(self):
        self.session.rollback()

def repository_pattern_example():
    """Demonstrate repository pattern."""
    print("\n=== Repository Pattern ===")
    
    with UnitOfWork() as uow:
        # Create user
        user = User(username='repository_user', email='repo@example.com')
        created_user = uow.user_repository.create(user)
        print(f"Created user: {created_user}")
        
        # Get user by ID
        found_user = uow.user_repository.get_by_id(created_user.id)
        print(f"Found user: {found_user}")
        
        # Get user by username
        user_by_username = uow.user_repository.get_by_username('repository_user')
        print(f"User by username: {user_by_username}")
        
        # Get all users
        all_users = uow.user_repository.get_all()
        print(f"All users count: {len(all_users)}")

repository_pattern_example()
```

## Database Migration and Schema Management

### Alembic Migrations

```python
# This would typically be in separate migration files
# Here we demonstrate the concepts

def migration_example():
    """Demonstrate database migration concepts."""
    print("\n=== Database Migration Example ===")
    
    # Example migration script (conceptual)
    migration_script = '''
    # Migration: Add user profile table
    # Version: 001_add_user_profiles
    
    from alembic import op
    import sqlalchemy as sa
    
    def upgrade():
        # Create user_profiles table
        op.create_table(
            'user_profiles',
            sa.Column('id', sa.Integer(), nullable=False),
            sa.Column('user_id', sa.Integer(), nullable=False),
            sa.Column('bio', sa.Text(), nullable=True),
            sa.Column('avatar_url', sa.String(255), nullable=True),
            sa.Column('created_at', sa.DateTime(), nullable=True),
            sa.ForeignKeyConstraint(['user_id'], ['users.id'], ),
            sa.PrimaryKeyConstraint('id')
        )
        
        # Add index
        op.create_index(op.f('ix_user_profiles_user_id'), 'user_profiles', ['user_id'], unique=False)
    
    def downgrade():
        # Drop table
        op.drop_index(op.f('ix_user_profiles_user_id'), table_name='user_profiles')
        op.drop_table('user_profiles')
    '''
    
    print("Migration script example:")
    print(migration_script)

migration_example()
```

## Performance Optimization

### Database Performance Tips

```python
def performance_optimization_example():
    """Demonstrate database performance optimization."""
    print("\n=== Database Performance Optimization ===")
    
    session = Session()
    
    try:
        # Eager loading to avoid N+1 queries
        print("Eager loading example:")
        posts_with_authors = session.query(Post).options(
            joinedload(Post.author),
            joinedload(Post.comments)
        ).all()
        
        for post in posts_with_authors:
            print(f"Post: {post.title} by {post.author.username}")
            print(f"  Comments: {len(post.comments)}")
        
        # Batch operations
        print("\nBatch operations example:")
        users_to_create = [
            User(username=f'user_{i}', email=f'user{i}@example.com')
            for i in range(100, 110)
        ]
        
        session.add_all(users_to_create)
        session.commit()
        print(f"Created {len(users_to_create)} users in batch")
        
        # Query optimization with select_related
        print("\nOptimized query example:")
        from sqlalchemy.orm import selectinload
        
        users_with_posts = session.query(User).options(
            selectinload(User.posts)
        ).all()
        
        for user in users_with_posts:
            print(f"User: {user.username} has {len(user.posts)} posts")
        
    except Exception as e:
        session.rollback()
        print(f"Error: {e}")
    finally:
        session.close()

performance_optimization_example()
```

## Key Takeaways

1. **SQLite** is a lightweight, serverless database perfect for development and small applications
2. **SQLAlchemy ORM** provides a powerful abstraction layer for database operations
3. **Database design** requires careful consideration of relationships and constraints
4. **Transactions** ensure data consistency and integrity
5. **Repository pattern** separates data access logic from business logic
6. **Migrations** manage database schema changes over time
7. **Performance optimization** is crucial for scalable applications
8. **Error handling** prevents data corruption and improves user experience

## Next Steps

In the next lesson, we'll explore Testing and CI/CD - advanced testing techniques, continuous integration, and deployment practices for professional development.
