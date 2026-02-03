"""
====================================================================
Lesson 7: Joins and Relationships - Flask + SQLAlchemy ORM Examples
====================================================================
This module demonstrates how to perform JOINs using Flask and SQLAlchemy ORM.
It covers:
1. INNER JOIN operations using ORM relationships
2. LEFT JOIN operations using ORM relationships
3. RIGHT JOIN operations using ORM relationships
4. CROSS JOIN operations using ORM
5. SELF JOIN operations using ORM
6. Complex analytical queries with JOINs using ORM
7. Relationship navigation using ORM
8. Pandas integration with JOINs using ORM

Key Concepts:
- SQLAlchemy ORM Relationships: Navigate between related models
- Flask-SQLAlchemy: Relationship-based queries
- JOIN Types: Inner, Left, Right, Cross, Self joins with ORM
- Relationship Navigation: Using relationship properties
- Eager Loading: Optimizing relationship queries
- Complex Queries: Multi-table analysis with ORM
====================================================================
"""

# Import required libraries
from flask import Flask
from flask_sqlalchemy import SQLAlchemy
from sqlalchemy import text, func, and_, or_, desc, asc
from sqlalchemy.orm import joinedload, aliased
import pandas as pd
import os
from dotenv import load_dotenv
from datetime import date, datetime

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

class JoinQuerier:
    """
    JoinQuerier class demonstrates JOIN operations using Flask-SQLAlchemy ORM.
    
    This class shows how to:
    - Perform various types of JOINs using ORM relationships
    - Navigate between related models
    - Use eager loading for optimization
    - Create complex analytical queries
    - Handle relationship-based data analysis
    """
    
    def __init__(self):
        """Initialize with Flask app and database instance"""
        self.app = app
        self.db = db
    
    def inner_join_examples(self):
        """
        Demonstrate INNER JOIN operations using ORM relationships.
        
        Returns:
            bool: True if successful, False otherwise
        """
        try:
            with self.app.app_context():
                # Basic INNER JOIN: Students with enrollments using ORM
                print("1. Students with their enrollments (INNER JOIN using ORM):")
                
                # Method 1: Using relationship navigation
                students_with_enrollments = Student.query.filter(
                    Student.enrollments.any()
                ).options(joinedload(Student.enrollments)).all()
                
                for student in students_with_enrollments:
                    print(f"  {student.first_name} {student.last_name}:")
                    for enrollment in student.enrollments:
                        grade_str = f"{enrollment.grade:.1f}" if enrollment.grade else "N/A"
                        print(f"    - {enrollment.enrollment_date} - Grade: {grade_str} - {enrollment.status}")
                
                # Method 2: Using explicit JOIN
                print("\n2. Students, courses, and departments (Multiple JOINs using ORM):")
                enrollments_with_details = db.session.query(Enrollment).join(
                    Student, Enrollment.student_id == Student.student_id
                ).join(
                    Course, Enrollment.course_id == Course.course_id
                ).join(
                    Department, Course.dept_id == Department.dept_id
                ).options(
                    joinedload(Enrollment.student),
                    joinedload(Enrollment.course).joinedload(Course.department)
                ).all()
                
                for enrollment in enrollments_with_details:
                    grade_str = f"{enrollment.grade:.1f}" if enrollment.grade else "N/A"
                    print(f"  {enrollment.student.first_name} {enrollment.student.last_name} - "
                          f"{enrollment.course.course_code} ({enrollment.course.department.dept_name}) - "
                          f"Grade: {grade_str}")
                
                return True
                
        except Exception as e:
            print(f"❌ INNER JOIN examples failed: {e}")
            return False
    
    def left_join_examples(self):
        """
        Demonstrate LEFT JOIN operations using ORM relationships.
        
        Returns:
            bool: True if successful, False otherwise
        """
        try:
            with self.app.app_context():
                # LEFT JOIN: All students, even without enrollments using ORM
                print("1. All students with their enrollments (LEFT JOIN using ORM):")
                
                # Get all students with their enrollments (if any)
                all_students = Student.query.options(joinedload(Student.enrollments)).all()
                
                for student in all_students:
                    print(f"  {student.first_name} {student.last_name}:")
                    if student.enrollments:
                        for enrollment in student.enrollments:
                            grade_str = f"{enrollment.grade:.1f}" if enrollment.grade else "N/A"
                            print(f"    - {enrollment.enrollment_date} - Grade: {grade_str} - {enrollment.status}")
                    else:
                        print(f"    - No Enrollments")
                
                # Find students with no enrollments using ORM
                print("\n2. Students with no enrollments using ORM:")
                students_without_enrollments = Student.query.filter(
                    ~Student.enrollments.any()
                ).all()
                
                for student in students_without_enrollments:
                    print(f"  {student.first_name} {student.last_name} - Enrolled: {student.enrollment_date}")
                
                # Courses with enrollment counts using ORM
                print("\n3. All courses with enrollment counts using ORM:")
                courses_with_counts = db.session.query(
                    Course.course_code,
                    Course.course_name,
                    Department.dept_name,
                    func.count(Enrollment.student_id).label('enrolled_students')
                ).outerjoin(Enrollment).join(Department).group_by(
                    Course.course_id, Course.course_code, Course.course_name, Department.dept_name
                ).order_by(desc('enrolled_students')).all()
                
                for course in courses_with_counts:
                    print(f"  {course.course_code} - {course.course_name} ({course.dept_name}) - "
                          f"{course.enrolled_students} students")
                
                return True
                
        except Exception as e:
            print(f"❌ LEFT JOIN examples failed: {e}")
            return False
    
    def right_join_examples(self):
        """
        Demonstrate RIGHT JOIN operations using ORM relationships.
        
        Returns:
            bool: True if successful, False otherwise
        """
        try:
            with self.app.app_context():
                # RIGHT JOIN: All enrollments, even if student doesn't exist using ORM
                print("1. All enrollments with student info (RIGHT JOIN using ORM):")
                
                # Get all enrollments with their student info
                all_enrollments = Enrollment.query.options(joinedload(Enrollment.student)).all()
                
                for enrollment in all_enrollments:
                    if enrollment.student:
                        grade_str = f"{enrollment.grade:.1f}" if enrollment.grade else "N/A"
                        print(f"  {enrollment.student.first_name} {enrollment.student.last_name} - "
                              f"{enrollment.enrollment_date} - Grade: {grade_str} - {enrollment.status}")
                    else:
                        print(f"  [Student not found] - {enrollment.enrollment_date} - "
                              f"Grade: {enrollment.grade} - {enrollment.status}")
                
                return True
                
        except Exception as e:
            print(f"❌ RIGHT JOIN examples failed: {e}")
            return False
    
    def cross_join_examples(self):
        """
        Demonstrate CROSS JOIN operations using ORM.
        
        Returns:
            bool: True if successful, False otherwise
        """
        try:
            with self.app.app_context():
                # CROSS JOIN: All possible student-course combinations using ORM
                print("1. All possible student-course combinations (CROSS JOIN using ORM):")
                
                # Get all students and courses
                students = Student.query.all()
                courses = Course.query.all()
                
                # Create cross join manually (ORM doesn't have direct CROSS JOIN)
                combinations = []
                for student in students[:3]:  # Limit for demonstration
                    for course in courses[:3]:  # Limit for demonstration
                        # Check if enrollment exists
                        existing_enrollment = Enrollment.query.filter_by(
                            student_id=student.student_id,
                            course_id=course.course_id
                        ).first()
                        
                        enrollment_status = 'Enrolled' if existing_enrollment else 'Not Enrolled'
                        combinations.append({
                            'student': f"{student.first_name} {student.last_name}",
                            'course': course.course_code,
                            'status': enrollment_status
                        })
                
                for combo in combinations[:20]:  # Limit output
                    print(f"  {combo['student']} - {combo['course']} - {combo['status']}")
                
                return True
                
        except Exception as e:
            print(f"❌ CROSS JOIN examples failed: {e}")
            return False
    
    def self_join_examples(self):
        """
        Demonstrate SELF JOIN operations using ORM.
        
        Returns:
            bool: True if successful, False otherwise
        """
        try:
            with self.app.app_context():
                # Self JOIN: Find students with similar GPAs using ORM
                print("1. Students with similar GPAs (SELF JOIN using ORM):")
                
                # Create aliases for self join
                Student1 = aliased(Student)
                Student2 = aliased(Student)
                
                similar_gpa_students = db.session.query(
                    Student1.first_name.label('student1_first'),
                    Student1.last_name.label('student1_last'),
                    Student2.first_name.label('student2_first'),
                    Student2.last_name.label('student2_last'),
                    Student1.gpa
                ).join(
                    Student2, and_(
                        Student1.gpa == Student2.gpa,
                        Student1.student_id < Student2.student_id
                    )
                ).order_by(desc(Student1.gpa)).all()
                
                for result in similar_gpa_students:
                    print(f"  {result.student1_first} {result.student1_last} and "
                          f"{result.student2_first} {result.student2_last} - GPA: {result.gpa}")
                
                # Students enrolled in multiple courses using ORM
                print("\n2. Students enrolled in multiple courses using ORM:")
                students_with_multiple_courses = db.session.query(
                    Student.first_name,
                    Student.last_name,
                    func.count(Enrollment.course_id).label('course_count')
                ).join(Enrollment).group_by(
                    Student.student_id, Student.first_name, Student.last_name
                ).having(func.count(Enrollment.course_id) > 1).order_by(desc('course_count')).all()
                
                for student in students_with_multiple_courses:
                    print(f"  {student.first_name} {student.last_name} - {student.course_count} courses")
                
                return True
                
        except Exception as e:
            print(f"❌ SELF JOIN examples failed: {e}")
            return False
    
    def complex_join_analysis(self):
        """
        Demonstrate complex analytical queries with JOINs using ORM.
        
        Returns:
            bool: True if successful, False otherwise
        """
        try:
            with self.app.app_context():
                # Student performance analysis using ORM
                print("1. Student performance analysis using ORM:")
                
                student_performance = db.session.query(
                    Student.student_id,
                    func.concat(Student.first_name, ' ', Student.last_name).label('full_name'),
                    Student.gpa.label('student_gpa'),
                    func.count(Enrollment.course_id).label('courses_taken'),
                    func.avg(Enrollment.grade).label('average_grade'),
                    func.count(case((Enrollment.grade >= 90, 1))).label('A_grades'),
                    func.count(case((and_(Enrollment.grade >= 80, Enrollment.grade < 90), 1))).label('B_grades'),
                    func.count(case((and_(Enrollment.grade >= 70, Enrollment.grade < 80), 1))).label('C_grades'),
                    func.count(case((Enrollment.grade < 70, 1))).label('failing_grades')
                ).outerjoin(
                    Enrollment, and_(
                        Student.student_id == Enrollment.student_id,
                        Enrollment.status == 'completed'
                    )
                ).group_by(
                    Student.student_id, Student.first_name, Student.last_name, Student.gpa
                ).order_by(desc('average_grade')).all()
                
                for result in student_performance:
                    avg_grade = f"{result.average_grade:.1f}" if result.average_grade else "N/A"
                    print(f"  {result.full_name} - GPA: {result.student_gpa} - "
                          f"Courses: {result.courses_taken} - Avg Grade: {avg_grade}")
                    print(f"    A: {result.A_grades}, B: {result.B_grades}, "
                          f"C: {result.C_grades}, F: {result.failing_grades}")
                
                # Department analysis using ORM
                print("\n2. Department performance metrics using ORM:")
                
                dept_performance = db.session.query(
                    Department.dept_name,
                    func.count(func.distinct(Course.course_id)).label('total_courses'),
                    func.count(func.distinct(Enrollment.student_id)).label('total_students'),
                    func.count(Enrollment.enrollment_id).label('total_enrollments'),
                    func.avg(Enrollment.grade).label('average_grade'),
                    func.count(case((Enrollment.status == 'completed', 1))).label('completed_enrollments')
                ).outerjoin(Course).outerjoin(Enrollment).group_by(
                    Department.dept_id, Department.dept_name
                ).order_by(desc('total_enrollments')).all()
                
                for result in dept_performance:
                    avg_grade = f"{result.average_grade:.1f}" if result.average_grade else "N/A"
                    print(f"  {result.dept_name}: {result.total_courses} courses, "
                          f"{result.total_students} students, {result.total_enrollments} enrollments")
                    print(f"    Average grade: {avg_grade}, Completed: {result.completed_enrollments}")
                
                # Course popularity analysis using ORM
                print("\n3. Course popularity analysis using ORM:")
                
                course_popularity = db.session.query(
                    Course.course_code,
                    Course.course_name,
                    Department.dept_name,
                    func.count(Enrollment.student_id).label('enrollment_count'),
                    func.avg(Enrollment.grade).label('average_grade'),
                    func.count(case((Enrollment.grade >= 90, 1))).label('A_students'),
                    func.count(case((Enrollment.grade < 70, 1))).label('failing_students'),
                    func.round(
                        func.count(case((Enrollment.grade >= 70, 1))) * 100.0 / 
                        func.count(Enrollment.student_id), 2
                    ).label('pass_rate')
                ).join(Department).outerjoin(Enrollment).group_by(
                    Course.course_id, Course.course_code, Course.course_name, Department.dept_name
                ).having(func.count(Enrollment.student_id) > 0).order_by(
                    desc('enrollment_count'), desc('average_grade')
                ).all()
                
                for result in course_popularity:
                    avg_grade = f"{result.average_grade:.1f}" if result.average_grade else "N/A"
                    pass_rate = f"{result.pass_rate:.1f}%" if result.pass_rate else "N/A"
                    print(f"  {result.course_code} - {result.course_name} ({result.dept_name})")
                    print(f"    Enrollments: {result.enrollment_count}, Avg Grade: {avg_grade}, "
                          f"Pass Rate: {pass_rate}")
                    print(f"    A Students: {result.A_students}, Failing: {result.failing_students}")
                
                return True
                
        except Exception as e:
            print(f"❌ Complex join analysis failed: {e}")
            return False
    
    def relationship_navigation_examples(self):
        """
        Demonstrate relationship navigation using ORM.
        
        Returns:
            bool: True if successful, False otherwise
        """
        try:
            with self.app.app_context():
                print("=== Relationship Navigation Examples ===\n")
                
                # Navigate from Student to Enrollments
                print("1. Navigate from Student to Enrollments:")
                students = Student.query.options(joinedload(Student.enrollments)).limit(3).all()
                
                for student in students:
                    print(f"  Student: {student.first_name} {student.last_name}")
                    print(f"    Enrollments: {len(student.enrollments)}")
                    for enrollment in student.enrollments:
                        print(f"      - {enrollment.course.course_name} (Grade: {enrollment.grade})")
                
                # Navigate from Course to Department
                print("\n2. Navigate from Course to Department:")
                courses = Course.query.options(joinedload(Course.department)).limit(3).all()
                
                for course in courses:
                    print(f"  Course: {course.course_name}")
                    print(f"    Department: {course.department.dept_name if course.department else 'No Department'}")
                
                # Navigate from Department to Courses to Enrollments
                print("\n3. Navigate from Department to Courses to Enrollments:")
                departments = Department.query.options(
                    joinedload(Department.courses).joinedload(Course.enrollments)
                ).limit(2).all()
                
                for dept in departments:
                    print(f"  Department: {dept.dept_name}")
                    print(f"    Courses: {len(dept.courses)}")
                    for course in dept.courses:
                        print(f"      - {course.course_name} ({len(course.enrollments)} enrollments)")
                
                return True
                
        except Exception as e:
            print(f"❌ Relationship navigation failed: {e}")
            return False
    
    def join_with_pandas(self):
        """
        Demonstrate JOINs using pandas for data analysis with ORM.
        
        Returns:
            bool: True if successful, False otherwise
        """
        try:
            with self.app.app_context():
                # Load data into pandas DataFrames using ORM
                print("1. Loading data into pandas DataFrames using ORM...")
                
                # Method 1: Direct SQL query with ORM session
                students_df = pd.read_sql(
                    "SELECT * FROM students",
                    db.engine
                )
                
                enrollments_df = pd.read_sql(
                    "SELECT * FROM enrollments",
                    db.engine
                )
                
                courses_df = pd.read_sql(
                    "SELECT * FROM courses",
                    db.engine
                )
                
                departments_df = pd.read_sql(
                    "SELECT * FROM departments",
                    db.engine
                )
                
                print(f"  Students: {len(students_df)} records")
                print(f"  Enrollments: {len(enrollments_df)} records")
                print(f"  Courses: {len(courses_df)} records")
                print(f"  Departments: {len(departments_df)} records")
                
                # Method 2: Using ORM queries
                print("\n2. Loading data using ORM queries...")
                
                # Get students with their enrollments using ORM
                students_with_enrollments = Student.query.options(
                    joinedload(Student.enrollments)
                ).all()
                
                # Convert to DataFrame
                orm_data = []
                for student in students_with_enrollments:
                    for enrollment in student.enrollments:
                        orm_data.append({
                            'student_id': student.student_id,
                            'student_name': f"{student.first_name} {student.last_name}",
                            'student_gpa': float(student.gpa) if student.gpa else None,
                            'enrollment_id': enrollment.enrollment_id,
                            'course_id': enrollment.course_id,
                            'grade': float(enrollment.grade) if enrollment.grade else None,
                            'enrollment_status': enrollment.status
                        })
                
                orm_df = pd.DataFrame(orm_data)
                print(f"  ORM-based dataset: {len(orm_df)} records")
                
                # Perform JOINs using pandas
                print("\n3. Performing JOINs with pandas...")
                
                # Merge students with enrollments
                student_enrollments = students_df.merge(
                    enrollments_df, 
                    on='student_id', 
                    how='left'
                )
                print(f"  Students-Enrollments merge: {len(student_enrollments)} records")
                
                # Merge with courses
                student_course_enrollments = student_enrollments.merge(
                    courses_df, 
                    on='course_id', 
                    how='left'
                )
                print(f"  Students-Courses-Enrollments merge: {len(student_course_enrollments)} records")
                
                # Merge with departments
                full_data = student_course_enrollments.merge(
                    departments_df, 
                    on='dept_id', 
                    how='left'
                )
                print(f"  Full dataset merge: {len(full_data)} records")
                
                # Analysis with pandas
                print("\n4. Analysis with pandas...")
                
                # Student performance by department
                dept_performance = full_data.groupby('dept_name').agg({
                    'student_id': 'nunique',
                    'grade': 'mean',
                    'course_id': 'nunique'
                }).round(2)
                dept_performance.columns = ['Unique Students', 'Avg Grade', 'Unique Courses']
                print("  Performance by Department:")
                print(dept_performance)
                
                # Course popularity
                course_popularity = full_data.groupby(['course_code', 'course_name']).agg({
                    'student_id': 'count',
                    'grade': 'mean'
                }).round(2)
                course_popularity.columns = ['Enrollments', 'Avg Grade']
                course_popularity = course_popularity.sort_values('Enrollments', ascending=False)
                print("\n  Course Popularity:")
                print(course_popularity.head())
                
                return True
                
        except Exception as e:
            print(f"❌ Pandas JOIN analysis failed: {e}")
            return False

def main():
    """Main function to demonstrate JOIN operations using Flask-SQLAlchemy ORM"""
    print("=== Flask + SQLAlchemy ORM JOIN Operations Demo ===\n")
    
    # Initialize join querier
    querier = JoinQuerier()
    
    # Ensure tables exist
    with app.app_context():
        db.create_all()
    
    # INNER JOIN examples
    print("1. INNER JOIN examples using ORM...")
    querier.inner_join_examples()
    
    # LEFT JOIN examples
    print("\n2. LEFT JOIN examples using ORM...")
    querier.left_join_examples()
    
    # RIGHT JOIN examples
    print("\n3. RIGHT JOIN examples using ORM...")
    querier.right_join_examples()
    
    # CROSS JOIN examples
    print("\n4. CROSS JOIN examples using ORM...")
    querier.cross_join_examples()
    
    # SELF JOIN examples
    print("\n5. SELF JOIN examples using ORM...")
    querier.self_join_examples()
    
    # Complex join analysis
    print("\n6. Complex analytical queries using ORM...")
    querier.complex_join_analysis()
    
    # Relationship navigation
    print("\n7. Relationship navigation using ORM...")
    querier.relationship_navigation_examples()
    
    # Pandas integration
    print("\n8. JOINs with pandas using ORM...")
    querier.join_with_pandas()
    
    print("\n=== Flask + SQLAlchemy ORM JOIN Operations Demo Complete ===")
    print("\nKey Features Demonstrated:")
    print("1. ✅ INNER JOIN Operations using ORM Relationships")
    print("2. ✅ LEFT JOIN Operations using ORM Relationships")
    print("3. ✅ RIGHT JOIN Operations using ORM Relationships")
    print("4. ✅ CROSS JOIN Operations using ORM")
    print("5. ✅ SELF JOIN Operations using ORM Aliases")
    print("6. ✅ Complex Analytical Queries with JOINs")
    print("7. ✅ Relationship Navigation using ORM")
    print("8. ✅ Eager Loading for Query Optimization")
    print("9. ✅ Pandas Integration with ORM Queries")

# Standard Python idiom for running the script
if __name__ == "__main__":
    main()