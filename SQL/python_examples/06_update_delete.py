"""
====================================================================
Lesson 6: Updating and Deleting Data - Flask + SQLAlchemy ORM Examples
====================================================================
This module demonstrates how to update and delete data using Flask and SQLAlchemy ORM.
It covers:
1. Basic UPDATE operations using ORM
2. UPDATE with JOIN operations using ORM
3. UPDATE with subqueries using ORM
4. Basic DELETE operations using ORM
5. DELETE with JOIN operations using ORM
6. DELETE with subqueries using ORM
7. Transaction management using ORM sessions
8. Safe update and delete practices

Key Concepts:
- SQLAlchemy ORM Updates: Modify data using Python objects
- Flask-SQLAlchemy: Session management for updates and deletes
- Model Updates: Direct attribute modification with ORM
- Bulk Operations: Efficient update and delete methods
- Transaction Safety: Rollback and commit management
- Cascade Operations: Related record handling
====================================================================
"""

# Import required libraries
from flask import Flask
from flask_sqlalchemy import SQLAlchemy
from sqlalchemy import text, func, and_, or_
from datetime import date, datetime
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

class DataModifier:
    """
    DataModifier class demonstrates data modification using Flask-SQLAlchemy ORM.
    
    This class shows how to:
    - Update single and multiple records using ORM
    - Update records with complex conditions
    - Delete records using ORM
    - Handle transactions and rollbacks
    - Implement safe update and delete practices
    """
    
    def __init__(self):
        """Initialize with Flask app and database instance"""
        self.app = app
        self.db = db
    
    def basic_update_examples(self):
        """
        Demonstrate basic UPDATE operations using ORM.
        
        Returns:
            bool: True if successful, False otherwise
        """
        try:
            with self.app.app_context():
                # Update single record using ORM
                print("1. Updating student GPA using ORM:")
                student = Student.query.filter_by(student_id=1).first()
                if student:
                    student.gpa = 3.8
                    self.db.session.commit()
                    print(f"  Updated {student.first_name} {student.last_name}'s GPA to {student.gpa}")
                else:
                    print("  No student found with ID 1")
                
                # Update multiple columns using ORM
                print("\n2. Updating multiple columns using ORM:")
                student = Student.query.filter_by(student_id=1).first()
                if student:
                    student.gpa = 3.9
                    student.status = 'graduated'
                    student.updated_at = datetime.utcnow()
                    self.db.session.commit()
                    print(f"  Updated {student.first_name} {student.last_name}'s status to {student.status}")
                else:
                    print("  No student found with ID 1")
                
                # Update with WHERE conditions using ORM
                print("\n3. Updating based on conditions using ORM:")
                updated_count = Student.query.filter(
                    and_(Student.status == 'active', Student.gpa >= 3.5)
                ).update({Student.status: 'graduated'}, synchronize_session=False)
                
                self.db.session.commit()
                print(f"  Updated {updated_count} student(s) to graduated status")
                
                # Show updated data
                print("\n4. Showing updated students using ORM:")
                updated_students = Student.query.filter_by(student_id=1).all()
                for student in updated_students:
                    print(f"  {student.first_name} {student.last_name} - GPA: {student.gpa} - Status: {student.status}")
                
                return True
                
        except Exception as e:
            print(f"❌ Basic update examples failed: {e}")
            self.db.session.rollback()
            return False
    
    def update_with_join_examples(self):
        """
        Demonstrate UPDATE with JOIN operations using ORM.
        
        Returns:
            bool: True if successful, False otherwise
        """
        try:
            with self.app.app_context():
                # Update students based on course information using ORM
                print("1. Updating students based on course performance using ORM:")
                
                # Find students with high grades in CS101
                high_performing_students = db.session.query(Student).join(
                    Enrollment, Student.student_id == Enrollment.student_id
                ).join(
                    Course, Enrollment.course_id == Course.course_id
                ).filter(
                    and_(
                        Course.course_code == 'CS101',
                        Enrollment.grade >= 90
                    )
                ).all()
                
                for student in high_performing_students:
                    student.status = 'honors'
                    print(f"  Updated {student.first_name} {student.last_name} to honors status")
                
                self.db.session.commit()
                
                # Update course descriptions using ORM
                print("\n2. Updating course descriptions using ORM:")
                cs_courses = Course.query.join(Department).filter(
                    Department.dept_name == 'Computer Science'
                ).all()
                
                for course in cs_courses:
                    course.description = f"{course.description} ({course.department.dept_name} Department)"
                    print(f"  Updated course: {course.course_name}")
                
                self.db.session.commit()
                
                # Show updated courses
                print("\n3. Showing updated courses using ORM:")
                updated_courses = Course.query.join(Department).filter(
                    Department.dept_name == 'Computer Science'
                ).limit(3).all()
                
                for course in updated_courses:
                    print(f"  {course.course_code} - {course.course_name}")
                    print(f"    Description: {course.description}")
                
                return True
                
        except Exception as e:
            print(f"❌ Update with JOIN examples failed: {e}")
            self.db.session.rollback()
            return False
    
    def update_with_subquery_examples(self):
        """
        Demonstrate UPDATE with subqueries using ORM.
        
        Returns:
            bool: True if successful, False otherwise
        """
        try:
            with self.app.app_context():
                # Update GPA based on average grade using ORM
                print("1. Updating GPA based on average grade using ORM:")
                
                # Get students with completed enrollments
                students_with_grades = Student.query.filter(
                    Student.student_id.in_(
                        db.session.query(Enrollment.student_id).filter(
                            Enrollment.status == 'completed'
                        ).distinct()
                    )
                ).all()
                
                for student in students_with_grades:
                    # Calculate average grade for this student
                    avg_grade = db.session.query(func.avg(Enrollment.grade)).filter(
                        and_(
                            Enrollment.student_id == student.student_id,
                            Enrollment.status == 'completed'
                        )
                    ).scalar()
                    
                    if avg_grade:
                        # Convert grade to GPA (assuming 100-point scale to 4.0 scale)
                        new_gpa = avg_grade / 25.0
                        student.gpa = new_gpa
                        print(f"  Updated {student.first_name} {student.last_name}'s GPA to {new_gpa:.2f}")
                
                self.db.session.commit()
                
                # Show updated GPAs
                print("\n2. Showing updated GPAs using ORM:")
                updated_students = Student.query.filter(
                    Student.gpa.isnot(None)
                ).order_by(desc(Student.gpa)).limit(5).all()
                
                for student in updated_students:
                    print(f"  {student.first_name} {student.last_name} - GPA: {student.gpa:.2f}")
                
                return True
                
        except Exception as e:
            print(f"❌ Update with subquery examples failed: {e}")
            self.db.session.rollback()
            return False
    
    def basic_delete_examples(self):
        """
        Demonstrate basic DELETE operations using ORM.
        
        Returns:
            bool: True if successful, False otherwise
        """
        try:
            with self.app.app_context():
                # First, create a test student to delete
                print("1. Creating test student for deletion using ORM:")
                test_student = Student(
                    first_name='Test',
                    last_name='Delete',
                    email='test.delete@university.edu',
                    enrollment_date=date(2024, 1, 1),
                    gpa=2.0,
                    status='inactive'
                )
                self.db.session.add(test_student)
                self.db.session.flush()  # Get the student_id
                test_student_id = test_student.student_id
                print(f"  Created test student with ID: {test_student_id}")
                
                # Delete specific record using ORM
                print("\n2. Deleting test student using ORM:")
                student_to_delete = Student.query.filter_by(student_id=test_student_id).first()
                if student_to_delete:
                    self.db.session.delete(student_to_delete)
                    self.db.session.commit()
                    print(f"  Deleted student: {student_to_delete.first_name} {student_to_delete.last_name}")
                else:
                    print("  Test student not found")
                
                # Delete with conditions using ORM
                print("\n3. Deleting dropped enrollments using ORM:")
                dropped_enrollments = Enrollment.query.filter_by(status='dropped').all()
                deleted_count = len(dropped_enrollments)
                
                for enrollment in dropped_enrollments:
                    self.db.session.delete(enrollment)
                
                self.db.session.commit()
                print(f"  Deleted {deleted_count} enrollment(s)")
                
                return True
                
        except Exception as e:
            print(f"❌ Basic delete examples failed: {e}")
            self.db.session.rollback()
            return False
    
    def delete_with_join_examples(self):
        """
        Demonstrate DELETE with JOIN operations using ORM.
        
        Returns:
            bool: True if successful, False otherwise
        """
        try:
            with self.app.app_context():
                # Delete students with no enrollments using ORM
                print("1. Deleting students with no enrollments using ORM:")
                
                students_without_enrollments = Student.query.filter(
                    ~Student.student_id.in_(
                        db.session.query(Enrollment.student_id).distinct()
                    )
                ).all()
                
                deleted_count = len(students_without_enrollments)
                for student in students_without_enrollments:
                    print(f"  Deleting student: {student.first_name} {student.last_name}")
                    self.db.session.delete(student)
                
                self.db.session.commit()
                print(f"  Deleted {deleted_count} student(s)")
                
                # Delete enrollments for specific courses using ORM
                print("\n2. Deleting enrollments for old courses using ORM:")
                
                old_course_enrollments = Enrollment.query.join(Course).filter(
                    Course.course_code.like('OLD%')
                ).all()
                
                deleted_count = len(old_course_enrollments)
                for enrollment in old_course_enrollments:
                    self.db.session.delete(enrollment)
                
                self.db.session.commit()
                print(f"  Deleted {deleted_count} enrollment(s)")
                
                return True
                
        except Exception as e:
            print(f"❌ Delete with JOIN examples failed: {e}")
            self.db.session.rollback()
            return False
    
    def delete_with_subquery_examples(self):
        """
        Demonstrate DELETE with subqueries using ORM.
        
        Returns:
            bool: True if successful, False otherwise
        """
        try:
            with self.app.app_context():
                # Delete courses with no enrollments using ORM
                print("1. Deleting courses with no enrollments using ORM:")
                
                courses_without_enrollments = Course.query.filter(
                    ~Course.course_id.in_(
                        db.session.query(Enrollment.course_id).distinct()
                    )
                ).all()
                
                deleted_count = len(courses_without_enrollments)
                for course in courses_without_enrollments:
                    print(f"  Deleting course: {course.course_name}")
                    self.db.session.delete(course)
                
                self.db.session.commit()
                print(f"  Deleted {deleted_count} course(s)")
                
                # Delete students with low performance using ORM
                print("\n2. Deleting students with consistently low performance using ORM:")
                
                # Find students with multiple failing grades
                low_performing_students = Student.query.filter(
                    Student.student_id.in_(
                        db.session.query(Enrollment.student_id).filter(
                            Enrollment.grade < 60
                        ).group_by(Enrollment.student_id).having(
                            func.count(Enrollment.enrollment_id) >= 2
                        )
                    )
                ).all()
                
                deleted_count = len(low_performing_students)
                for student in low_performing_students:
                    print(f"  Deleting student: {student.first_name} {student.last_name}")
                    self.db.session.delete(student)
                
                self.db.session.commit()
                print(f"  Deleted {deleted_count} student(s)")
                
                return True
                
        except Exception as e:
            print(f"❌ Delete with subquery examples failed: {e}")
            self.db.session.rollback()
            return False
    
    def transaction_examples(self):
        """
        Demonstrate transaction management using ORM sessions.
        
        Returns:
            bool: True if successful, False otherwise
        """
        try:
            with self.app.app_context():
                print("=== Transaction Management Demonstration ===\n")
                
                # Start transaction
                print("1. Starting transaction using ORM:")
                
                try:
                    # Update student status
                    student = Student.query.filter_by(student_id=1).first()
                    if student:
                        student.status = 'graduated'
                        print(f"  Updated student {student.first_name} {student.last_name} to graduated")
                    
                    # Insert new enrollment
                    if student:
                        new_enrollment = Enrollment(
                            student_id=student.student_id,
                            course_id=1,
                            status='completed'
                        )
                        self.db.session.add(new_enrollment)
                        print(f"  Added new enrollment for student {student.student_id}")
                    
                    # Check if everything looks good
                    print("2. Checking transaction results using ORM:")
                    if student:
                        print(f"  Student status: {student.status}")
                        enrollments = student.enrollments
                        print(f"  Student has {len(enrollments)} enrollments")
                    
                    # Commit transaction
                    print("3. Committing transaction using ORM:")
                    self.db.session.commit()
                    print("  Transaction committed successfully")
                    
                    return True
                    
                except Exception as e:
                    # Rollback on error
                    self.db.session.rollback()
                    print(f"  Transaction rolled back due to error: {e}")
                    return False
                
        except Exception as e:
            print(f"❌ Transaction examples failed: {e}")
            return False
    
    def safe_update_practices(self):
        """
        Demonstrate safe update practices using ORM.
        
        Returns:
            bool: True if successful, False otherwise
        """
        try:
            with self.app.app_context():
                print("=== Safe Update Practices Demonstration ===\n")
                
                # Test with SELECT first using ORM
                print("1. Testing with SELECT first using ORM:")
                students_to_update = Student.query.filter(
                    and_(Student.status == 'active', Student.gpa < 2.0)
                ).all()
                
                print(f"  Found {len(students_to_update)} students to update")
                
                if len(students_to_update) > 0:
                    print("  Students to be updated:")
                    for student in students_to_update:
                        print(f"    {student.first_name} {student.last_name} - GPA: {student.gpa}")
                    
                    # Perform the update
                    for student in students_to_update:
                        student.status = 'inactive'
                    
                    self.db.session.commit()
                    print(f"  Updated {len(students_to_update)} student(s)")
                else:
                    print("  No students found matching criteria")
                
                # Use LIMIT for safety using ORM
                print("\n2. Using LIMIT for safety using ORM:")
                students_to_reactivate = Student.query.filter(
                    Student.status == 'inactive'
                ).limit(5).all()
                
                for student in students_to_reactivate:
                    student.status = 'active'
                
                self.db.session.commit()
                print(f"  Updated {len(students_to_reactivate)} student(s) (limited to 5)")
                
                return True
                
        except Exception as e:
            print(f"❌ Safe update practices failed: {e}")
            self.db.session.rollback()
            return False
    
    def show_data_summary(self):
        """
        Show current data summary using ORM.
        
        Returns:
            bool: True if successful, False otherwise
        """
        try:
            with self.app.app_context():
                print("Current data summary using ORM:")
                
                # Count students by status
                status_counts = db.session.query(
                    Student.status,
                    func.count(Student.student_id).label('count')
                ).group_by(Student.status).all()
                
                print("  Students by status:")
                for status, count in status_counts:
                    print(f"    {status}: {count}")
                
                # Count enrollments by status
                enrollment_counts = db.session.query(
                    Enrollment.status,
                    func.count(Enrollment.enrollment_id).label('count')
                ).group_by(Enrollment.status).all()
                
                print("  Enrollments by status:")
                for status, count in enrollment_counts:
                    print(f"    {status}: {count}")
                
                return True
                
        except Exception as e:
            print(f"❌ Failed to show data summary: {e}")
            return False

def main():
    """Main function to demonstrate data modification using Flask-SQLAlchemy ORM"""
    print("=== Flask + SQLAlchemy ORM Data Modification Demo ===\n")
    
    # Initialize data modifier
    modifier = DataModifier()
    
    # Ensure tables exist
    with app.app_context():
        db.create_all()
    
    # Show initial data summary
    print("Initial data summary:")
    modifier.show_data_summary()
    
    # Basic update examples
    print("\n1. Basic UPDATE examples using ORM...")
    modifier.basic_update_examples()
    
    # Update with JOIN examples
    print("\n2. UPDATE with JOIN examples using ORM...")
    modifier.update_with_join_examples()
    
    # Update with subquery examples
    print("\n3. UPDATE with subquery examples using ORM...")
    modifier.update_with_subquery_examples()
    
    # Basic delete examples
    print("\n4. Basic DELETE examples using ORM...")
    modifier.basic_delete_examples()
    
    # Delete with JOIN examples
    print("\n5. DELETE with JOIN examples using ORM...")
    modifier.delete_with_join_examples()
    
    # Delete with subquery examples
    print("\n6. DELETE with subquery examples using ORM...")
    modifier.delete_with_subquery_examples()
    
    # Transaction examples
    print("\n7. Transaction management using ORM...")
    modifier.transaction_examples()
    
    # Safe update practices
    print("\n8. Safe update practices using ORM...")
    modifier.safe_update_practices()
    
    # Show final data summary
    print("\nFinal data summary:")
    modifier.show_data_summary()
    
    print("\n=== Flask + SQLAlchemy ORM Data Modification Demo Complete ===")
    print("\nKey Features Demonstrated:")
    print("1. ✅ Basic UPDATE Operations using ORM")
    print("2. ✅ UPDATE with JOIN Operations using ORM")
    print("3. ✅ UPDATE with Subqueries using ORM")
    print("4. ✅ Basic DELETE Operations using ORM")
    print("5. ✅ DELETE with JOIN Operations using ORM")
    print("6. ✅ DELETE with Subqueries using ORM")
    print("7. ✅ Transaction Management with ORM Sessions")
    print("8. ✅ Safe Update and Delete Practices")

# Standard Python idiom for running the script
if __name__ == "__main__":
    main()