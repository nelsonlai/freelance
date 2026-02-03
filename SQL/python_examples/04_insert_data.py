"""
====================================================================
Lesson 4: Inserting Data - Flask + SQLAlchemy ORM Examples
====================================================================
This module demonstrates how to insert data into MySQL tables using Flask and SQLAlchemy ORM.
It covers:
1. Single record insertion using ORM models
2. Bulk data insertion with ORM
3. Data validation at the ORM level
4. Error handling for duplicate data
5. JSON data handling with ORM
6. Transaction management using ORM sessions

Key Concepts:
- SQLAlchemy ORM Models: Insert data using Python objects
- Flask-SQLAlchemy: Session management and transaction handling
- Model Validation: Data validation at the ORM level
- Bulk Operations: Efficient data insertion methods
- Error Handling: Graceful handling of database errors
====================================================================
"""

# Import required libraries
from flask import Flask
from flask_sqlalchemy import SQLAlchemy
from sqlalchemy import text
from datetime import date, datetime
import json
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
# DATABASE MODELS
# ===================================================================

class Department(db.Model):
    """Department model for the school management system"""
    __tablename__ = 'departments'
    
    dept_id = db.Column(db.Integer, primary_key=True, autoincrement=True)
    dept_name = db.Column(db.String(100), nullable=False, unique=True)
    budget = db.Column(db.Numeric(12, 2), default=0.00)
    established_date = db.Column(db.Date)
    created_at = db.Column(db.DateTime, default=db.func.current_timestamp())
    
    # Relationships
    courses = db.relationship('Course', back_populates='department', cascade='all, delete-orphan')
    
    def __repr__(self):
        return f'<Department {self.dept_name}>'

class Student(db.Model):
    """Student model for the school management system"""
    __tablename__ = 'students'
    
    student_id = db.Column(db.Integer, primary_key=True, autoincrement=True)
    first_name = db.Column(db.String(50), nullable=False)
    last_name = db.Column(db.String(50), nullable=False)
    email = db.Column(db.String(100), nullable=False, unique=True)
    phone = db.Column(db.String(20))
    enrollment_date = db.Column(db.Date, nullable=False, default=date.today)
    gpa = db.Column(db.Numeric(3, 2))
    status = db.Column(db.Enum('active', 'inactive', 'graduated'), default='active')
    created_at = db.Column(db.DateTime, default=db.func.current_timestamp())
    updated_at = db.Column(db.DateTime, default=db.func.current_timestamp(), onupdate=db.func.current_timestamp())
    
    # Relationships
    enrollments = db.relationship('Enrollment', back_populates='student', cascade='all, delete-orphan')
    
    def __repr__(self):
        return f'<Student {self.first_name} {self.last_name}>'

class Course(db.Model):
    """Course model for the school management system"""
    __tablename__ = 'courses'
    
    course_id = db.Column(db.Integer, primary_key=True, autoincrement=True)
    course_code = db.Column(db.String(10), nullable=False, unique=True)
    course_name = db.Column(db.String(100), nullable=False)
    credits = db.Column(db.Integer, nullable=False)
    dept_id = db.Column(db.Integer, db.ForeignKey('departments.dept_id', ondelete='SET NULL'))
    description = db.Column(db.Text)
    created_at = db.Column(db.DateTime, default=db.func.current_timestamp())
    
    # Relationships
    department = db.relationship('Department', back_populates='courses')
    enrollments = db.relationship('Enrollment', back_populates='course', cascade='all, delete-orphan')
    
    def __repr__(self):
        return f'<Course {self.course_code}: {self.course_name}>'

class Enrollment(db.Model):
    """Enrollment model for the school management system"""
    __tablename__ = 'enrollments'
    
    enrollment_id = db.Column(db.Integer, primary_key=True, autoincrement=True)
    student_id = db.Column(db.Integer, db.ForeignKey('students.student_id', ondelete='CASCADE'), nullable=False)
    course_id = db.Column(db.Integer, db.ForeignKey('courses.course_id', ondelete='CASCADE'), nullable=False)
    enrollment_date = db.Column(db.Date, nullable=False, default=date.today)
    grade = db.Column(db.Numeric(5, 2))
    status = db.Column(db.Enum('enrolled', 'completed', 'dropped'), default='enrolled')
    created_at = db.Column(db.DateTime, default=db.func.current_timestamp())
    
    # Relationships
    student = db.relationship('Student', back_populates='enrollments')
    course = db.relationship('Course', back_populates='enrollments')
    
    def __repr__(self):
        return f'<Enrollment Student:{self.student_id} Course:{self.course_id}>'

class UserProfile(db.Model):
    """UserProfile model for demonstrating JSON data handling"""
    __tablename__ = 'user_profiles'
    
    id = db.Column(db.Integer, primary_key=True, autoincrement=True)
    username = db.Column(db.String(50), unique=True, nullable=False)
    profile_data = db.Column(db.JSON)
    preferences = db.Column(db.JSON)
    created_at = db.Column(db.DateTime, default=db.func.current_timestamp())
    
    def __repr__(self):
        return f'<UserProfile {self.username}>'

class DataInserter:
    """
    DataInserter class demonstrates data insertion using Flask-SQLAlchemy ORM.
    
    This class shows how to:
    - Insert single records using ORM models
    - Insert multiple records efficiently
    - Handle different data types
    - Manage transactions and error handling
    """
    
    def __init__(self):
        """Initialize with Flask app and database instance"""
        self.app = app
        self.db = db
    
    def insert_single_record(self):
        """
        Insert a single record using SQLAlchemy ORM.
        
        Returns:
            int: ID of inserted student, None if failed
        """
        try:
            with self.app.app_context():
                # Create a student instance
                student = Student(
                    first_name='John',
                    last_name='Doe',
                    email='john.doe@university.edu',
                    phone='555-0101',
                    enrollment_date=date(2024, 1, 15),
                    gpa=3.75,
                    status='active'
                )
                
                # Add to session
                self.db.session.add(student)
                self.db.session.commit()
                
                print(f"✅ Inserted student with ID: {student.student_id}")
                return student.student_id
                
        except Exception as e:
            print(f"❌ Failed to insert student: {e}")
            self.db.session.rollback()
            return None
    
    def insert_multiple_records(self):
        """
        Insert multiple records in one operation using ORM.
        
        Returns:
            int: Number of records inserted
        """
        try:
            with self.app.app_context():
                # Create multiple student instances
                students_data = [
                    {
                        'first_name': 'Jane',
                        'last_name': 'Smith',
                        'email': 'jane.smith@university.edu',
                        'phone': '555-0102',
                        'enrollment_date': date(2024, 1, 16),
                        'gpa': 3.85,
                        'status': 'active'
                    },
                    {
                        'first_name': 'Bob',
                        'last_name': 'Johnson',
                        'email': 'bob.johnson@university.edu',
                        'phone': '555-0103',
                        'enrollment_date': date(2024, 1, 17),
                        'gpa': 3.45,
                        'status': 'active'
                    },
                    {
                        'first_name': 'Alice',
                        'last_name': 'Brown',
                        'email': 'alice.brown@university.edu',
                        'phone': '555-0104',
                        'enrollment_date': date(2024, 1, 18),
                        'gpa': 3.95,
                        'status': 'active'
                    }
                ]
                
                # Create student instances and add to session
                students = [Student(**data) for data in students_data]
                self.db.session.add_all(students)
                self.db.session.commit()
                
                print(f"✅ Inserted {len(students)} students using ORM")
                return len(students)
                
        except Exception as e:
            print(f"❌ Failed to insert students: {e}")
            self.db.session.rollback()
            return 0
    
    def insert_with_different_data_types(self):
        """
        Demonstrate inserting various data types using ORM.
        
        Returns:
            bool: True if successful, False otherwise
        """
        try:
            with self.app.app_context():
                # Insert department with decimal and date
                dept = Department(
                    dept_name='Computer Science',
                    budget=500000.00,
                    established_date=date(1990, 9, 1)
                )
                self.db.session.add(dept)
                self.db.session.flush()  # Get the dept_id
                
                # Insert course with text and foreign key
                course = Course(
                    course_code='CS101',
                    course_name='Introduction to Programming',
                    credits=3,
                    dept_id=dept.dept_id,
                    description='Basic programming concepts using Python and Java'
                )
                self.db.session.add(course)
                self.db.session.flush()  # Get the course_id
                
                # Insert enrollment with current date
                enrollment = Enrollment(
                    student_id=1,  # Assuming student with ID 1 exists
                    course_id=course.course_id,
                    status='enrolled'
                )
                self.db.session.add(enrollment)
                
                # Commit all changes
                self.db.session.commit()
                print("✅ Inserted records with various data types using ORM")
                return True
                
        except Exception as e:
            print(f"❌ Failed to insert records: {e}")
            self.db.session.rollback()
            return False
    
    def insert_json_data(self):
        """
        Demonstrate inserting JSON data using ORM.
        
        Returns:
            bool: True if successful, False otherwise
        """
        try:
            with self.app.app_context():
                # Ensure the user_profiles table exists
                self.db.create_all()
                
                # Prepare JSON data
                profile_data = {
                    "age": 25,
                    "location": "New York",
                    "interests": ["technology", "music", "travel"],
                    "social_media": {
                        "twitter": "@johndoe",
                        "linkedin": "john-doe"
                    }
                }
                
                preferences = [
                    "email_notifications",
                    "dark_mode",
                    "newsletter",
                    "push_notifications"
                ]
                
                # Create user profile instance
                user_profile = UserProfile(
                    username='john_doe',
                    profile_data=profile_data,
                    preferences=preferences
                )
                
                # Add to session and commit
                self.db.session.add(user_profile)
                self.db.session.commit()
                
                print("✅ Inserted JSON data successfully using ORM")
                return True
                
        except Exception as e:
            print(f"❌ Failed to insert JSON data: {e}")
            self.db.session.rollback()
            return False
    
    def insert_with_error_handling(self):
        """
        Demonstrate error handling during insertion using ORM.
        
        Returns:
            bool: True if successful, False otherwise
        """
        try:
            with self.app.app_context():
                # Try to insert duplicate email (should fail)
                try:
                    duplicate_student = Student(
                        first_name='Duplicate',
                        last_name='User',
                        email='john.doe@university.edu',  # This email already exists
                        enrollment_date=date(2024, 1, 20)
                    )
                    self.db.session.add(duplicate_student)
                    self.db.session.commit()
                    print("❌ Duplicate email was allowed - constraint failed")
                except Exception as e:
                    self.db.session.rollback()
                    print(f"✅ Caught expected error for duplicate email: {str(e)[:50]}...")
                
                # Try to insert with invalid data (should fail)
                try:
                    invalid_student = Student(
                        first_name='Invalid',
                        last_name='Student',
                        email='invalid@university.edu',
                        gpa=5.0  # Invalid GPA > 4.0
                    )
                    self.db.session.add(invalid_student)
                    self.db.session.commit()
                    print("❌ Invalid GPA was allowed - constraint failed")
                except Exception as e:
                    self.db.session.rollback()
                    print(f"✅ Caught expected error for invalid GPA: {str(e)[:50]}...")
                
                # Try to insert valid data (should succeed)
                try:
                    valid_student = Student(
                        first_name='Valid',
                        last_name='Student',
                        email='valid@university.edu',
                        gpa=3.5,
                        enrollment_date=date(2024, 1, 21)
                    )
                    self.db.session.add(valid_student)
                    self.db.session.commit()
                    print(f"✅ Valid student inserted successfully with ID: {valid_student.student_id}")
                except Exception as e:
                    self.db.session.rollback()
                    print(f"❌ Unexpected error inserting valid student: {e}")
                
                return True
                
        except Exception as e:
            print(f"❌ Error handling failed: {e}")
            self.db.session.rollback()
            return False
    
    def bulk_insert_sample_data(self):
        """
        Insert comprehensive sample data for the school management system using ORM.
        
        Returns:
            bool: True if successful, False otherwise
        """
        try:
            with self.app.app_context():
                # Create departments
                departments_data = [
                    {'dept_name': 'Computer Science', 'budget': 500000.00, 'established_date': date(1990, 9, 1)},
                    {'dept_name': 'Mathematics', 'budget': 300000.00, 'established_date': date(1985, 9, 1)},
                    {'dept_name': 'Physics', 'budget': 400000.00, 'established_date': date(1988, 9, 1)},
                    {'dept_name': 'Chemistry', 'budget': 350000.00, 'established_date': date(1987, 9, 1)},
                    {'dept_name': 'Biology', 'budget': 450000.00, 'established_date': date(1989, 9, 1)}
                ]
                
                # Create department instances
                departments = []
                for dept_data in departments_data:
                    # Check if department already exists
                    existing_dept = Department.query.filter_by(dept_name=dept_data['dept_name']).first()
                    if not existing_dept:
                        dept = Department(**dept_data)
                        departments.append(dept)
                        self.db.session.add(dept)
                
                self.db.session.flush()  # Get department IDs
                
                # Create courses
                courses_data = [
                    {'course_code': 'CS101', 'course_name': 'Introduction to Programming', 'credits': 3, 'dept_id': 1, 'description': 'Basic programming concepts using Python'},
                    {'course_code': 'CS201', 'course_name': 'Data Structures', 'credits': 3, 'dept_id': 1, 'description': 'Fundamental data structures and algorithms'},
                    {'course_code': 'CS301', 'course_name': 'Database Systems', 'credits': 3, 'dept_id': 1, 'description': 'Relational database design and SQL'},
                    {'course_code': 'MATH101', 'course_name': 'Calculus I', 'credits': 4, 'dept_id': 2, 'description': 'Differential and integral calculus'},
                    {'course_code': 'MATH201', 'course_name': 'Linear Algebra', 'credits': 3, 'dept_id': 2, 'description': 'Vector spaces and linear transformations'},
                    {'course_code': 'PHYS101', 'course_name': 'General Physics I', 'credits': 4, 'dept_id': 3, 'description': 'Mechanics and thermodynamics'},
                    {'course_code': 'CHEM101', 'course_name': 'General Chemistry I', 'credits': 4, 'dept_id': 4, 'description': 'Atomic structure and chemical bonding'},
                    {'course_code': 'BIO101', 'course_name': 'General Biology I', 'credits': 4, 'dept_id': 5, 'description': 'Cell biology and genetics'}
                ]
                
                # Create course instances
                courses = []
                for course_data in courses_data:
                    # Check if course already exists
                    existing_course = Course.query.filter_by(course_code=course_data['course_code']).first()
                    if not existing_course:
                        course = Course(**course_data)
                        courses.append(course)
                        self.db.session.add(course)
                
                self.db.session.flush()  # Get course IDs
                
                # Create more students
                students_data = [
                    {'first_name': 'Charlie', 'last_name': 'Wilson', 'email': 'charlie.wilson@university.edu', 'phone': '555-0105', 'enrollment_date': date(2023, 9, 1), 'gpa': 3.25, 'status': 'active'},
                    {'first_name': 'Diana', 'last_name': 'Davis', 'email': 'diana.davis@university.edu', 'phone': '555-0106', 'enrollment_date': date(2022, 9, 1), 'gpa': 3.65, 'status': 'graduated'},
                    {'first_name': 'Eve', 'last_name': 'Miller', 'email': 'eve.miller@university.edu', 'phone': '555-0107', 'enrollment_date': date(2023, 9, 1), 'gpa': 3.55, 'status': 'active'},
                    {'first_name': 'Frank', 'last_name': 'Garcia', 'email': 'frank.garcia@university.edu', 'phone': '555-0108', 'enrollment_date': date(2023, 9, 1), 'gpa': 3.15, 'status': 'active'},
                    {'first_name': 'Grace', 'last_name': 'Martinez', 'email': 'grace.martinez@university.edu', 'phone': '555-0109', 'enrollment_date': date(2023, 9, 1), 'gpa': 3.85, 'status': 'active'}
                ]
                
                # Create student instances
                students = []
                for student_data in students_data:
                    # Check if student already exists
                    existing_student = Student.query.filter_by(email=student_data['email']).first()
                    if not existing_student:
                        student = Student(**student_data)
                        students.append(student)
                        self.db.session.add(student)
                
                self.db.session.flush()  # Get student IDs
                
                # Create enrollments
                enrollments_data = [
                    {'student_id': 1, 'course_id': 1, 'enrollment_date': date(2023, 9, 1), 'grade': 85.5, 'status': 'completed'},
                    {'student_id': 1, 'course_id': 2, 'enrollment_date': date(2024, 1, 15), 'grade': None, 'status': 'enrolled'},
                    {'student_id': 2, 'course_id': 1, 'enrollment_date': date(2023, 9, 1), 'grade': 92.0, 'status': 'completed'},
                    {'student_id': 2, 'course_id': 3, 'enrollment_date': date(2024, 1, 15), 'grade': None, 'status': 'enrolled'},
                    {'student_id': 3, 'course_id': 4, 'enrollment_date': date(2023, 9, 1), 'grade': 78.5, 'status': 'completed'},
                    {'student_id': 3, 'course_id': 5, 'enrollment_date': date(2024, 1, 15), 'grade': None, 'status': 'enrolled'},
                    {'student_id': 4, 'course_id': 6, 'enrollment_date': date(2023, 9, 1), 'grade': 88.0, 'status': 'completed'},
                    {'student_id': 4, 'course_id': 7, 'enrollment_date': date(2024, 1, 15), 'grade': None, 'status': 'enrolled'},
                    {'student_id': 5, 'course_id': 8, 'enrollment_date': date(2023, 9, 1), 'grade': 82.5, 'status': 'completed'},
                    {'student_id': 5, 'course_id': 1, 'enrollment_date': date(2024, 1, 15), 'grade': None, 'status': 'enrolled'}
                ]
                
                # Create enrollment instances
                enrollments = []
                for enrollment_data in enrollments_data:
                    # Check if enrollment already exists
                    existing_enrollment = Enrollment.query.filter_by(
                        student_id=enrollment_data['student_id'],
                        course_id=enrollment_data['course_id']
                    ).first()
                    if not existing_enrollment:
                        enrollment = Enrollment(**enrollment_data)
                        enrollments.append(enrollment)
                        self.db.session.add(enrollment)
                
                # Commit all changes
                self.db.session.commit()
                print("✅ Bulk sample data inserted successfully using ORM")
                return True
                
        except Exception as e:
            print(f"❌ Failed to insert bulk data: {e}")
            self.db.session.rollback()
            return False
    
    def demonstrate_transaction_management(self):
        """
        Demonstrate transaction management using ORM sessions.
        
        Returns:
            bool: True if successful, False otherwise
        """
        try:
            with self.app.app_context():
                print("=== Transaction Management Demonstration ===\n")
                
                # Start a transaction
                print("1. Starting transaction...")
                
                try:
                    # Create a student
                    student = Student(
                        first_name='Transaction',
                        last_name='Test',
                        email='transaction.test@university.edu',
                        gpa=3.8
                    )
                    self.db.session.add(student)
                    self.db.session.flush()  # Get the student_id
                    
                    # Create a course
                    course = Course(
                        course_code='TRANS001',
                        course_name='Transaction Management',
                        credits=3,
                        dept_id=1,
                        description='Learn about database transactions'
                    )
                    self.db.session.add(course)
                    self.db.session.flush()  # Get the course_id
                    
                    # Create an enrollment
                    enrollment = Enrollment(
                        student_id=student.student_id,
                        course_id=course.course_id,
                        grade=95.0,
                        status='completed'
                    )
                    self.db.session.add(enrollment)
                    
                    # Commit the transaction
                    self.db.session.commit()
                    print("✅ Transaction committed successfully")
                    
                    # Verify the data was inserted
                    inserted_student = Student.query.filter_by(email='transaction.test@university.edu').first()
                    if inserted_student:
                        print(f"   Verified: Student {inserted_student.first_name} {inserted_student.last_name} was inserted")
                    
                    return True
                    
                except Exception as e:
                    # Rollback on error
                    self.db.session.rollback()
                    print(f"❌ Transaction rolled back due to error: {e}")
                    return False
                
        except Exception as e:
            print(f"❌ Transaction management failed: {e}")
            return False

def main():
    """Main function to demonstrate data insertion using Flask-SQLAlchemy ORM"""
    print("=== Flask + SQLAlchemy ORM Data Insertion Demo ===\n")
    
    # Initialize data inserter
    inserter = DataInserter()
    
    # Ensure tables exist
    with app.app_context():
        db.create_all()
    
    # Test single record insertion
    print("1. Inserting single record using ORM...")
    inserter.insert_single_record()
    
    # Test multiple records insertion
    print("\n2. Inserting multiple records using ORM...")
    inserter.insert_multiple_records()
    
    # Test different data types
    print("\n3. Inserting records with different data types using ORM...")
    inserter.insert_with_different_data_types()
    
    # Test JSON data insertion
    print("\n4. Inserting JSON data using ORM...")
    inserter.insert_json_data()
    
    # Test error handling
    print("\n5. Testing error handling using ORM...")
    inserter.insert_with_error_handling()
    
    # Test transaction management
    print("\n6. Testing transaction management using ORM...")
    inserter.demonstrate_transaction_management()
    
    # Insert comprehensive sample data
    print("\n7. Inserting comprehensive sample data using ORM...")
    inserter.bulk_insert_sample_data()
    
    print("\n=== Flask + SQLAlchemy ORM Data Insertion Demo Complete ===")
    print("\nKey Features Demonstrated:")
    print("1. ✅ Single Record Insertion using ORM Models")
    print("2. ✅ Bulk Data Insertion with add_all()")
    print("3. ✅ Data Type Handling (Date, Decimal, Enum)")
    print("4. ✅ JSON Data Storage and Retrieval")
    print("5. ✅ Error Handling and Validation")
    print("6. ✅ Transaction Management")
    print("7. ✅ Relationship-based Data Insertion")
    print("8. ✅ Duplicate Data Prevention")

# Standard Python idiom for running the script
if __name__ == "__main__":
    main()