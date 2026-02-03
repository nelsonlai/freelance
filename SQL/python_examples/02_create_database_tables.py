"""
====================================================================
Lesson 2: Creating Databases and Tables - Flask + SQLAlchemy ORM Examples
====================================================================
This module demonstrates how to create databases and tables using Flask and SQLAlchemy ORM.
It covers:
1. Flask-SQLAlchemy model definition
2. Database schema creation using ORM
3. Relationship modeling between entities
4. Constraints and validation using ORM
5. Index creation for performance optimization
6. Real-world database schema examples

Key Concepts:
- SQLAlchemy ORM Models: Python classes representing database tables
- Flask-SQLAlchemy: Flask extension for SQLAlchemy integration
- Model Relationships: One-to-many, many-to-many relationships
- Database Constraints: Primary keys, foreign keys, unique constraints
- Model Validation: Data validation at the ORM level
====================================================================
"""

# Import required libraries
from flask import Flask
from flask_sqlalchemy import SQLAlchemy
from sqlalchemy import text, Index, UniqueConstraint, CheckConstraint
from sqlalchemy.sql import func
from sqlalchemy.dialects.mysql import ENUM
import os
from dotenv import load_dotenv
from datetime import datetime

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
# SCHOOL MANAGEMENT SYSTEM MODELS
# ===================================================================

class Department(db.Model):
    """
    Department model for the school management system.
    
    Demonstrates:
    - Primary key with auto-increment
    - Unique constraints
    - Default values
    - Timestamp fields
    """
    __tablename__ = 'departments'
    
    dept_id = db.Column(db.Integer, primary_key=True, autoincrement=True)
    dept_name = db.Column(db.String(100), nullable=False, unique=True, index=True)
    budget = db.Column(db.Numeric(12, 2), default=0.00)
    established_date = db.Column(db.Date)
    created_at = db.Column(db.DateTime, default=func.current_timestamp())
    
    # Relationships
    courses = db.relationship('Course', back_populates='department', cascade='all, delete-orphan')
    
    def __repr__(self):
        return f'<Department {self.dept_name}>'
    
    def to_dict(self):
        return {
            'dept_id': self.dept_id,
            'dept_name': self.dept_name,
            'budget': float(self.budget) if self.budget else 0.0,
            'established_date': self.established_date.isoformat() if self.established_date else None,
            'created_at': self.created_at.isoformat() if self.created_at else None
        }

class Student(db.Model):
    """
    Student model for the school management system.
    
    Demonstrates:
    - Complex constraints
    - ENUM fields
    - Check constraints
    - Automatic timestamp updates
    """
    __tablename__ = 'students'
    
    student_id = db.Column(db.Integer, primary_key=True, autoincrement=True)
    first_name = db.Column(db.String(50), nullable=False, index=True)
    last_name = db.Column(db.String(50), nullable=False, index=True)
    email = db.Column(db.String(100), nullable=False, unique=True, index=True)
    phone = db.Column(db.String(20))
    enrollment_date = db.Column(db.Date, nullable=False, default=func.current_date())
    gpa = db.Column(db.Numeric(3, 2))
    status = db.Column(ENUM('active', 'inactive', 'graduated'), default='active', index=True)
    created_at = db.Column(db.DateTime, default=func.current_timestamp())
    updated_at = db.Column(db.DateTime, default=func.current_timestamp(), onupdate=func.current_timestamp())
    
    # Relationships
    enrollments = db.relationship('Enrollment', back_populates='student', cascade='all, delete-orphan')
    
    # Table constraints
    __table_args__ = (
        CheckConstraint('gpa >= 0.0 AND gpa <= 4.0', name='chk_gpa'),
        Index('idx_student_name', 'first_name', 'last_name'),
        Index('idx_student_email_status', 'email', 'status')
    )
    
    def __repr__(self):
        return f'<Student {self.first_name} {self.last_name}>'
    
    def to_dict(self):
        return {
            'student_id': self.student_id,
            'first_name': self.first_name,
            'last_name': self.last_name,
            'email': self.email,
            'phone': self.phone,
            'enrollment_date': self.enrollment_date.isoformat() if self.enrollment_date else None,
            'gpa': float(self.gpa) if self.gpa else None,
            'status': self.status,
            'created_at': self.created_at.isoformat() if self.created_at else None,
            'updated_at': self.updated_at.isoformat() if self.updated_at else None
        }

class Course(db.Model):
    """
    Course model for the school management system.
    
    Demonstrates:
    - Foreign key relationships
    - Check constraints
    - Text fields for descriptions
    """
    __tablename__ = 'courses'
    
    course_id = db.Column(db.Integer, primary_key=True, autoincrement=True)
    course_code = db.Column(db.String(10), nullable=False, unique=True, index=True)
    course_name = db.Column(db.String(100), nullable=False, index=True)
    credits = db.Column(db.Integer, nullable=False)
    dept_id = db.Column(db.Integer, db.ForeignKey('departments.dept_id', ondelete='SET NULL'))
    description = db.Column(db.Text)
    created_at = db.Column(db.DateTime, default=func.current_timestamp())
    
    # Relationships
    department = db.relationship('Department', back_populates='courses')
    enrollments = db.relationship('Enrollment', back_populates='course', cascade='all, delete-orphan')
    
    # Table constraints
    __table_args__ = (
        CheckConstraint('credits > 0', name='chk_credits'),
        Index('idx_course_code_name', 'course_code', 'course_name'),
        Index('idx_course_dept', 'dept_id', 'credits')
    )
    
    def __repr__(self):
        return f'<Course {self.course_code}: {self.course_name}>'
    
    def to_dict(self):
        return {
            'course_id': self.course_id,
            'course_code': self.course_code,
            'course_name': self.course_name,
            'credits': self.credits,
            'dept_id': self.dept_id,
            'description': self.description,
            'created_at': self.created_at.isoformat() if self.created_at else None
        }

class Enrollment(db.Model):
    """
    Enrollment model for the school management system.
    
    Demonstrates:
    - Composite unique constraints
    - Multiple foreign keys
    - ENUM fields with status
    - Check constraints for grades
    """
    __tablename__ = 'enrollments'
    
    enrollment_id = db.Column(db.Integer, primary_key=True, autoincrement=True)
    student_id = db.Column(db.Integer, db.ForeignKey('students.student_id', ondelete='CASCADE'), nullable=False)
    course_id = db.Column(db.Integer, db.ForeignKey('courses.course_id', ondelete='CASCADE'), nullable=False)
    enrollment_date = db.Column(db.Date, nullable=False, default=func.current_date())
    grade = db.Column(db.Numeric(5, 2))
    status = db.Column(ENUM('enrolled', 'completed', 'dropped'), default='enrolled', index=True)
    created_at = db.Column(db.DateTime, default=func.current_timestamp())
    
    # Relationships
    student = db.relationship('Student', back_populates='enrollments')
    course = db.relationship('Course', back_populates='enrollments')
    
    # Table constraints
    __table_args__ = (
        UniqueConstraint('student_id', 'course_id', name='unique_enrollment'),
        CheckConstraint('grade >= 0.0 AND grade <= 100.0', name='chk_grade'),
        Index('idx_enrollment_student_course', 'student_id', 'course_id'),
        Index('idx_enrollment_status_date', 'status', 'enrollment_date')
    )
    
    def __repr__(self):
        return f'<Enrollment Student:{self.student_id} Course:{self.course_id}>'
    
    def to_dict(self):
        return {
            'enrollment_id': self.enrollment_id,
            'student_id': self.student_id,
            'course_id': self.course_id,
            'enrollment_date': self.enrollment_date.isoformat() if self.enrollment_date else None,
            'grade': float(self.grade) if self.grade else None,
            'status': self.status,
            'created_at': self.created_at.isoformat() if self.created_at else None
        }

# ===================================================================
# LIBRARY MANAGEMENT SYSTEM MODELS
# ===================================================================

class Book(db.Model):
    """
    Book model for the library management system.
    
    Demonstrates:
    - ISBN uniqueness
    - Publication year constraints
    - Inventory management fields
    """
    __tablename__ = 'books'
    
    book_id = db.Column(db.Integer, primary_key=True, autoincrement=True)
    title = db.Column(db.String(200), nullable=False, index=True)
    author = db.Column(db.String(100), nullable=False, index=True)
    isbn = db.Column(db.String(20), unique=True, index=True)
    publication_year = db.Column(db.Integer)
    genre = db.Column(db.String(50), index=True)
    available_copies = db.Column(db.Integer, default=1)
    total_copies = db.Column(db.Integer, default=1)
    created_at = db.Column(db.DateTime, default=func.current_timestamp())
    
    # Relationships
    borrowings = db.relationship('Borrowing', back_populates='book', cascade='all, delete-orphan')
    
    # Table constraints
    __table_args__ = (
        CheckConstraint('publication_year >= 1000 AND publication_year <= 2024', name='chk_publication_year'),
        CheckConstraint('available_copies >= 0', name='chk_available_copies'),
        Index('idx_book_title_author', 'title', 'author'),
        Index('idx_book_genre_year', 'genre', 'publication_year')
    )
    
    def __repr__(self):
        return f'<Book {self.title} by {self.author}>'
    
    def to_dict(self):
        return {
            'book_id': self.book_id,
            'title': self.title,
            'author': self.author,
            'isbn': self.isbn,
            'publication_year': self.publication_year,
            'genre': self.genre,
            'available_copies': self.available_copies,
            'total_copies': self.total_copies,
            'created_at': self.created_at.isoformat() if self.created_at else None
        }

class Member(db.Model):
    """
    Member model for the library management system.
    
    Demonstrates:
    - Membership status ENUM
    - Email uniqueness
    - Membership date tracking
    """
    __tablename__ = 'members'
    
    member_id = db.Column(db.Integer, primary_key=True, autoincrement=True)
    first_name = db.Column(db.String(50), nullable=False, index=True)
    last_name = db.Column(db.String(50), nullable=False, index=True)
    email = db.Column(db.String(100), nullable=False, unique=True, index=True)
    phone = db.Column(db.String(20))
    membership_date = db.Column(db.Date, nullable=False, default=func.current_date())
    status = db.Column(ENUM('active', 'inactive', 'suspended'), default='active', index=True)
    created_at = db.Column(db.DateTime, default=func.current_timestamp())
    
    # Relationships
    borrowings = db.relationship('Borrowing', back_populates='member', cascade='all, delete-orphan')
    
    def __repr__(self):
        return f'<Member {self.first_name} {self.last_name}>'
    
    def to_dict(self):
        return {
            'member_id': self.member_id,
            'first_name': self.first_name,
            'last_name': self.last_name,
            'email': self.email,
            'phone': self.phone,
            'membership_date': self.membership_date.isoformat() if self.membership_date else None,
            'status': self.status,
            'created_at': self.created_at.isoformat() if self.created_at else None
        }

class Borrowing(db.Model):
    """
    Borrowing model for the library management system.
    
    Demonstrates:
    - Date arithmetic relationships
    - Fine calculation fields
    - Borrowing status tracking
    """
    __tablename__ = 'borrowings'
    
    borrowing_id = db.Column(db.Integer, primary_key=True, autoincrement=True)
    book_id = db.Column(db.Integer, db.ForeignKey('books.book_id', ondelete='CASCADE'), nullable=False)
    member_id = db.Column(db.Integer, db.ForeignKey('members.member_id', ondelete='CASCADE'), nullable=False)
    borrow_date = db.Column(db.Date, nullable=False, default=func.current_date())
    due_date = db.Column(db.Date, nullable=False)
    return_date = db.Column(db.Date)
    status = db.Column(ENUM('borrowed', 'returned', 'overdue'), default='borrowed', index=True)
    fine_amount = db.Column(db.Numeric(8, 2), default=0.00)
    created_at = db.Column(db.DateTime, default=func.current_timestamp())
    
    # Relationships
    book = db.relationship('Book', back_populates='borrowings')
    member = db.relationship('Member', back_populates='borrowings')
    
    # Table constraints
    __table_args__ = (
        CheckConstraint('fine_amount >= 0', name='chk_fine_amount'),
        Index('idx_borrowing_book_member', 'book_id', 'member_id'),
        Index('idx_borrowing_status_date', 'status', 'due_date')
    )
    
    def __repr__(self):
        return f'<Borrowing Book:{self.book_id} Member:{self.member_id}>'
    
    def to_dict(self):
        return {
            'borrowing_id': self.borrowing_id,
            'book_id': self.book_id,
            'member_id': self.member_id,
            'borrow_date': self.borrow_date.isoformat() if self.borrow_date else None,
            'due_date': self.due_date.isoformat() if self.due_date else None,
            'return_date': self.return_date.isoformat() if self.return_date else None,
            'status': self.status,
            'fine_amount': float(self.fine_amount) if self.fine_amount else 0.0,
            'created_at': self.created_at.isoformat() if self.created_at else None
        }

class DatabaseManager:
    """
    DatabaseManager class handles database and table creation using Flask-SQLAlchemy ORM.
    
    This class demonstrates how to:
    - Create databases using ORM
    - Create tables from model definitions
    - Manage database operations without raw SQL
    """
    
    def __init__(self):
        """Initialize with Flask app and database instance"""
        self.app = app
        self.db = db
        
    def create_database(self, db_name):
        """
        Create a new database using SQLAlchemy ORM.
        
        Args:
            db_name (str): Name of the database to create
            
        Returns:
            bool: True if database created successfully, False otherwise
        """
        try:
            with self.app.app_context():
                # Use raw SQL for database creation (not supported by ORM)
                self.db.session.execute(text(f"CREATE DATABASE IF NOT EXISTS {db_name} CHARACTER SET utf8mb4 COLLATE utf8mb4_unicode_ci"))
                self.db.session.commit()
                print(f"✅ Database '{db_name}' created successfully")
                return True
        except Exception as e:
            print(f"❌ Failed to create database: {e}")
            self.db.session.rollback()
            return False
    
    def create_school_management_tables(self):
        """
        Create the complete school management system tables using ORM models.
        
        Returns:
            bool: True if tables created successfully, False otherwise
        """
        try:
            with self.app.app_context():
                # Create all tables defined in models
                self.db.create_all()
                print("✅ School management tables created successfully using ORM")
                return True
        except Exception as e:
            print(f"❌ Failed to create school management tables: {e}")
            return False
    
    def create_library_management_tables(self):
        """
        Create library management system tables using ORM models.
        
        Returns:
            bool: True if tables created successfully, False otherwise
        """
        try:
            with self.app.app_context():
                # Create all tables defined in models
                self.db.create_all()
                print("✅ Library management tables created successfully using ORM")
                return True
        except Exception as e:
            print(f"❌ Failed to create library tables: {e}")
            return False
    
    def show_tables(self):
        """
        Show all tables in the current database using ORM.
        
        Returns:
            list: List of table names, empty list if error occurs
        """
        try:
            with self.app.app_context():
                result = self.db.session.execute(text("SHOW TABLES"))
                tables = [row[0] for row in result.fetchall()]
                print("Tables in current database:")
                for table in tables:
                    print(f"  - {table}")
                return tables
        except Exception as e:
            print(f"Error showing tables: {e}")
            return []
    
    def describe_table(self, table_name):
        """
        Show table structure using ORM.
        
        Args:
            table_name (str): Name of the table to describe
            
        Returns:
            list: List of column information, empty list if error occurs
        """
        try:
            with self.app.app_context():
                result = self.db.session.execute(text(f"DESCRIBE {table_name}"))
                columns = result.fetchall()
                print(f"\nStructure of table '{table_name}':")
                print("-" * 80)
                for col in columns:
                    print(f"{col[0]:<20} {col[1]:<20} {col[2]:<10} {col[3]:<10} {col[4]:<10} {col[5]:<10}")
                return columns
        except Exception as e:
            print(f"Error describing table: {e}")
            return []
    
    def demonstrate_model_relationships(self):
        """
        Demonstrate model relationships using ORM.
        
        Returns:
            bool: True if demonstration successful, False otherwise
        """
        try:
            with self.app.app_context():
                print("=== Model Relationships Demonstration ===\n")
                
                # Create sample data to demonstrate relationships
                # Create a department
                dept = Department(
                    dept_name='Computer Science',
                    budget=500000.00,
                    established_date=datetime(1990, 9, 1).date()
                )
                self.db.session.add(dept)
                self.db.session.flush()  # Get the dept_id
                
                # Create a course in that department
                course = Course(
                    course_code='CS101',
                    course_name='Introduction to Programming',
                    credits=3,
                    dept_id=dept.dept_id,
                    description='Basic programming concepts using Python'
                )
                self.db.session.add(course)
                self.db.session.flush()  # Get the course_id
                
                # Create a student
                student = Student(
                    first_name='John',
                    last_name='Doe',
                    email='john.doe@university.edu',
                    phone='555-0101',
                    gpa=3.75
                )
                self.db.session.add(student)
                self.db.session.flush()  # Get the student_id
                
                # Create an enrollment
                enrollment = Enrollment(
                    student_id=student.student_id,
                    course_id=course.course_id,
                    grade=85.5,
                    status='completed'
                )
                self.db.session.add(enrollment)
                
                # Commit all changes
                self.db.session.commit()
                
                print("✅ Sample data created with relationships")
                
                # Demonstrate relationship navigation
                print("\n1. Department to Courses relationship:")
                dept_courses = dept.courses
                for course in dept_courses:
                    print(f"   Department '{dept.dept_name}' has course: {course.course_name}")
                
                print("\n2. Student to Enrollments relationship:")
                student_enrollments = student.enrollments
                for enrollment in student_enrollments:
                    print(f"   Student '{student.first_name} {student.last_name}' is enrolled in course ID: {enrollment.course_id}")
                
                print("\n3. Course to Enrollments relationship:")
                course_enrollments = course.enrollments
                for enrollment in course_enrollments:
                    print(f"   Course '{course.course_name}' has enrollment from student ID: {enrollment.student_id}")
                
                return True
                
        except Exception as e:
            print(f"❌ Error demonstrating relationships: {e}")
            self.db.session.rollback()
            return False
    
    def demonstrate_model_validation(self):
        """
        Demonstrate model validation and constraints using ORM.
        
        Returns:
            bool: True if demonstration successful, False otherwise
        """
        try:
            with self.app.app_context():
                print("\n=== Model Validation Demonstration ===\n")
                
                # Test unique constraint
                print("1. Testing unique constraint (email):")
                try:
                    duplicate_student = Student(
                        first_name='Jane',
                        last_name='Smith',
                        email='john.doe@university.edu',  # Duplicate email
                        gpa=3.85
                    )
                    self.db.session.add(duplicate_student)
                    self.db.session.commit()
                    print("   ❌ Unique constraint failed - duplicate email allowed")
                except Exception as e:
                    self.db.session.rollback()
                    print(f"   ✅ Unique constraint working - {str(e)[:50]}...")
                
                # Test check constraint
                print("\n2. Testing check constraint (GPA range):")
                try:
                    invalid_gpa_student = Student(
                        first_name='Bob',
                        last_name='Johnson',
                        email='bob.johnson@university.edu',
                        gpa=5.0  # Invalid GPA > 4.0
                    )
                    self.db.session.add(invalid_gpa_student)
                    self.db.session.commit()
                    print("   ❌ Check constraint failed - invalid GPA allowed")
                except Exception as e:
                    self.db.session.rollback()
                    print(f"   ✅ Check constraint working - {str(e)[:50]}...")
                
                # Test foreign key constraint
                print("\n3. Testing foreign key constraint:")
                try:
                    invalid_enrollment = Enrollment(
                        student_id=999,  # Non-existent student
                        course_id=1,
                        grade=90.0
                    )
                    self.db.session.add(invalid_enrollment)
                    self.db.session.commit()
                    print("   ❌ Foreign key constraint failed - invalid student ID allowed")
                except Exception as e:
                    self.db.session.rollback()
                    print(f"   ✅ Foreign key constraint working - {str(e)[:50]}...")
                
                return True
                
        except Exception as e:
            print(f"❌ Error demonstrating validation: {e}")
            self.db.session.rollback()
            return False

def main():
    """Main function to demonstrate database and table creation using Flask-SQLAlchemy ORM"""
    print("=== Flask + SQLAlchemy ORM Database and Table Creation Demo ===\n")
    
    # Initialize database manager
    db_manager = DatabaseManager()
    
    # Create learning database
    print("1. Creating learning database...")
    db_manager.create_database('learning_db')
    
    # Create school management tables
    print("\n2. Creating school management system tables using ORM...")
    db_manager.create_school_management_tables()
    
    # Show all tables
    print("\n3. Showing all tables...")
    db_manager.show_tables()
    
    # Describe a table
    print("\n4. Describing students table...")
    db_manager.describe_table('students')
    
    # Demonstrate model relationships
    print("\n5. Demonstrating model relationships...")
    db_manager.demonstrate_model_relationships()
    
    # Demonstrate model validation
    print("\n6. Demonstrating model validation...")
    db_manager.demonstrate_model_validation()
    
    # Create library management tables
    print("\n7. Creating library management system tables using ORM...")
    db_manager.create_library_management_tables()
    
    # Show all tables again
    print("\n8. Showing all tables after library creation...")
    db_manager.show_tables()
    
    print("\n=== Flask + SQLAlchemy ORM Database and Table Creation Demo Complete ===")
    print("\nKey Features Demonstrated:")
    print("1. ✅ ORM Model Definition with Flask-SQLAlchemy")
    print("2. ✅ Database Table Creation from Models")
    print("3. ✅ Model Relationships (One-to-Many)")
    print("4. ✅ Database Constraints (Unique, Check, Foreign Key)")
    print("5. ✅ Model Validation at ORM Level")
    print("6. ✅ Index Creation for Performance")
    print("7. ✅ ENUM Fields and Data Types")
    print("8. ✅ Automatic Timestamp Management")

# Standard Python idiom for running the script
if __name__ == "__main__":
    main()