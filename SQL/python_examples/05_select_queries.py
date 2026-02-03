"""
====================================================================
Lesson 5: Querying Data (SELECT) - Flask + SQLAlchemy ORM Examples
====================================================================
This module demonstrates how to query MySQL tables using Flask and SQLAlchemy ORM.
It covers:
1. Basic SELECT operations using ORM queries
2. WHERE clause filtering with ORM
3. LIKE pattern matching using ORM
4. ORDER BY sorting with ORM
5. LIMIT and pagination using ORM
6. Aggregate functions with ORM
7. Complex analytical queries using ORM
8. Pandas integration with ORM queries

Key Concepts:
- SQLAlchemy ORM Queries: Query data using Python objects
- Flask-SQLAlchemy: Query methods and session management
- Query Filtering: WHERE clauses using ORM methods
- Query Sorting: ORDER BY using ORM methods
- Aggregation: Group functions using ORM
- Query Optimization: Efficient ORM query patterns
====================================================================
"""

# Import required libraries
from flask import Flask
from flask_sqlalchemy import SQLAlchemy
from sqlalchemy import text, func, case, and_, or_, not_, desc, asc
from sqlalchemy.orm import joinedload
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

class DataQuerier:
    """
    DataQuerier class demonstrates data querying using Flask-SQLAlchemy ORM.
    
    This class shows how to:
    - Perform basic SELECT operations using ORM
    - Apply WHERE clause filtering
    - Use LIKE pattern matching
    - Sort results with ORDER BY
    - Implement pagination
    - Use aggregate functions
    - Create complex analytical queries
    """
    
    def __init__(self):
        """Initialize with Flask app and database instance"""
        self.app = app
        self.db = db
    
    def basic_select(self):
        """
        Demonstrate basic SELECT operations using ORM.
        
        Returns:
            bool: True if successful, False otherwise
        """
        try:
            with self.app.app_context():
                # Select all students (equivalent to SELECT * FROM students)
                print("1. All students using ORM:")
                students = Student.query.limit(5).all()
                for student in students:
                    print(f"  {student}")
                
                # Select specific fields using ORM
                print("\n2. Student names and emails using ORM:")
                students_info = db.session.query(
                    Student.first_name,
                    Student.last_name,
                    Student.email
                ).limit(5).all()
                
                for student in students_info:
                    print(f"  {student.first_name} {student.last_name} - {student.email}")
                
                # Select with aliases using ORM
                print("\n3. Students with aliases using ORM:")
                students_with_gpa = db.session.query(
                    Student.first_name.label('First_Name'),
                    Student.last_name.label('Last_Name'),
                    Student.gpa.label('GPA')
                ).limit(5).all()
                
                for student in students_with_gpa:
                    print(f"  {student.First_Name} {student.Last_Name} - GPA: {student.GPA}")
                
                return True
                
        except Exception as e:
            print(f"❌ Basic select failed: {e}")
            return False
    
    def where_clause_examples(self):
        """
        Demonstrate WHERE clause filtering using ORM.
        
        Returns:
            bool: True if successful, False otherwise
        """
        try:
            with self.app.app_context():
                # Filter by status using ORM
                print("1. Active students using ORM:")
                active_students = Student.query.filter_by(status='active').all()
                for student in active_students:
                    print(f"  {student.first_name} {student.last_name} - {student.status}")
                
                # Filter by GPA using ORM
                print("\n2. High GPA students (>= 3.5) using ORM:")
                high_gpa_students = Student.query.filter(Student.gpa >= 3.5).all()
                for student in high_gpa_students:
                    print(f"  {student.first_name} {student.last_name} - GPA: {student.gpa}")
                
                # Multiple conditions using ORM
                print("\n3. Active students with high GPA using ORM:")
                active_high_gpa = Student.query.filter(
                    and_(Student.status == 'active', Student.gpa >= 3.5)
                ).all()
                for student in active_high_gpa:
                    print(f"  {student.first_name} {student.last_name} - GPA: {student.gpa}")
                
                # IN operator using ORM
                print("\n4. Students with specific statuses using ORM:")
                status_students = Student.query.filter(
                    Student.status.in_(['active', 'graduated'])
                ).all()
                for student in status_students:
                    print(f"  {student.first_name} {student.last_name} - {student.status}")
                
                # NULL values using ORM
                print("\n5. Students without phone numbers using ORM:")
                no_phone_students = Student.query.filter(Student.phone.is_(None)).all()
                for student in no_phone_students:
                    print(f"  {student.first_name} {student.last_name}")
                
                return True
                
        except Exception as e:
            print(f"❌ WHERE clause examples failed: {e}")
            return False
    
    def like_pattern_matching(self):
        """
        Demonstrate LIKE pattern matching using ORM.
        
        Returns:
            bool: True if successful, False otherwise
        """
        try:
            with self.app.app_context():
                # Names starting with 'J' using ORM
                print("1. Students with names starting with 'J' using ORM:")
                j_students = Student.query.filter(Student.first_name.like('J%')).all()
                for student in j_students:
                    print(f"  {student.first_name} {student.last_name}")
                
                # Names ending with 'son' using ORM
                print("\n2. Students with last names ending with 'son' using ORM:")
                son_students = Student.query.filter(Student.last_name.like('%son')).all()
                for student in son_students:
                    print(f"  {student.first_name} {student.last_name}")
                
                # Email domain filtering using ORM
                print("\n3. Students with university email using ORM:")
                university_students = Student.query.filter(
                    Student.email.like('%@university.edu')
                ).all()
                for student in university_students:
                    print(f"  {student.first_name} {student.last_name} - {student.email}")
                
                # Multiple patterns using ORM
                print("\n4. Students with names starting with 'J' or 'A' using ORM:")
                ja_students = Student.query.filter(
                    or_(Student.first_name.like('J%'), Student.first_name.like('A%'))
                ).all()
                for student in ja_students:
                    print(f"  {student.first_name} {student.last_name}")
                
                return True
                
        except Exception as e:
            print(f"❌ LIKE pattern matching failed: {e}")
            return False
    
    def order_by_examples(self):
        """
        Demonstrate ORDER BY sorting using ORM.
        
        Returns:
            bool: True if successful, False otherwise
        """
        try:
            with self.app.app_context():
                # Sort by GPA descending using ORM
                print("1. Students sorted by GPA (highest first) using ORM:")
                students_by_gpa = Student.query.order_by(desc(Student.gpa)).limit(5).all()
                for student in students_by_gpa:
                    print(f"  {student.first_name} {student.last_name} - GPA: {student.gpa}")
                
                # Sort by multiple columns using ORM
                print("\n2. Students sorted by status, then GPA using ORM:")
                students_by_status_gpa = Student.query.order_by(
                    Student.status, desc(Student.gpa)
                ).all()
                for student in students_by_status_gpa:
                    print(f"  {student.first_name} {student.last_name} - {student.status} - GPA: {student.gpa}")
                
                # Sort by expression using ORM
                print("\n3. Students sorted by full name using ORM:")
                students_by_name = db.session.query(
                    Student.first_name,
                    Student.last_name,
                    func.concat(Student.first_name, ' ', Student.last_name).label('full_name')
                ).order_by('full_name').limit(5).all()
                
                for student in students_by_name:
                    print(f"  {student.full_name}")
                
                return True
                
        except Exception as e:
            print(f"❌ ORDER BY examples failed: {e}")
            return False
    
    def limit_pagination(self):
        """
        Demonstrate LIMIT and pagination using ORM.
        
        Returns:
            bool: True if successful, False otherwise
        """
        try:
            with self.app.app_context():
                # Basic limit using ORM
                print("1. First 3 students using ORM:")
                first_students = Student.query.limit(3).all()
                for student in first_students:
                    print(f"  {student.first_name} {student.last_name}")
                
                # Pagination - page 1 using ORM
                print("\n2. Page 1 (students 1-3) using ORM:")
                page1_students = Student.query.order_by(Student.last_name).limit(3).all()
                for student in page1_students:
                    print(f"  {student.first_name} {student.last_name}")
                
                # Pagination - page 2 using ORM
                print("\n3. Page 2 (students 4-6) using ORM:")
                page2_students = Student.query.order_by(Student.last_name).offset(3).limit(3).all()
                for student in page2_students:
                    print(f"  {student.first_name} {student.last_name}")
                
                # Pagination helper function
                def get_students_page(page, per_page=3):
                    """Helper function for pagination"""
                    offset = (page - 1) * per_page
                    return Student.query.order_by(Student.last_name).offset(offset).limit(per_page).all()
                
                print("\n4. Using pagination helper function:")
                page3_students = get_students_page(3, 2)  # Page 3, 2 students per page
                for student in page3_students:
                    print(f"  {student.first_name} {student.last_name}")
                
                return True
                
        except Exception as e:
            print(f"❌ LIMIT pagination failed: {e}")
            return False
    
    def aggregate_functions(self):
        """
        Demonstrate aggregate functions using ORM.
        
        Returns:
            bool: True if successful, False otherwise
        """
        try:
            with self.app.app_context():
                # Basic aggregates using ORM
                print("1. Student statistics using ORM:")
                stats = db.session.query(
                    func.count(Student.student_id).label('total_students'),
                    func.avg(Student.gpa).label('average_gpa'),
                    func.min(Student.gpa).label('min_gpa'),
                    func.max(Student.gpa).label('max_gpa')
                ).first()
                
                print(f"  Total students: {stats.total_students}")
                print(f"  Average GPA: {stats.average_gpa:.2f}")
                print(f"  Min GPA: {stats.min_gpa}")
                print(f"  Max GPA: {stats.max_gpa}")
                
                # Group by status using ORM
                print("\n2. Students by status using ORM:")
                status_stats = db.session.query(
                    Student.status,
                    func.count(Student.student_id).label('count'),
                    func.avg(Student.gpa).label('avg_gpa')
                ).group_by(Student.status).all()
                
                for stat in status_stats:
                    print(f"  {stat.status}: {stat.count} students, avg GPA: {stat.avg_gpa:.2f}")
                
                # Group by enrollment year using ORM
                print("\n3. Students by enrollment year using ORM:")
                year_stats = db.session.query(
                    func.year(Student.enrollment_date).label('enrollment_year'),
                    func.count(Student.student_id).label('count'),
                    func.avg(Student.gpa).label('avg_gpa')
                ).group_by(func.year(Student.enrollment_date)).order_by('enrollment_year').all()
                
                for stat in year_stats:
                    print(f"  {stat.enrollment_year}: {stat.count} students, avg GPA: {stat.avg_gpa:.2f}")
                
                return True
                
        except Exception as e:
            print(f"❌ Aggregate functions failed: {e}")
            return False
    
    def complex_queries(self):
        """
        Demonstrate complex analytical queries using ORM.
        
        Returns:
            bool: True if successful, False otherwise
        """
        try:
            with self.app.app_context():
                # Student analysis with academic standing using ORM
                print("1. Student academic analysis using ORM:")
                academic_analysis = db.session.query(
                    Student.student_id,
                    func.concat(Student.first_name, ' ', Student.last_name).label('full_name'),
                    Student.gpa,
                    Student.status,
                    case(
                        (Student.gpa >= 3.7, 'High Honors'),
                        (Student.gpa >= 3.3, 'Honors'),
                        (Student.gpa >= 3.0, 'Good Standing'),
                        else_='Academic Probation'
                    ).label('academic_standing')
                ).filter(Student.status == 'active').order_by(desc(Student.gpa)).all()
                
                for student in academic_analysis:
                    print(f"  {student.full_name} - GPA: {student.gpa} - {student.academic_standing}")
                
                # Course enrollment statistics using ORM
                print("\n2. Course enrollment statistics using ORM:")
                course_stats = db.session.query(
                    Course.course_code,
                    Course.course_name,
                    func.count(Enrollment.student_id).label('enrolled_students'),
                    func.avg(Enrollment.grade).label('average_grade')
                ).outerjoin(Enrollment).group_by(
                    Course.course_id, Course.course_code, Course.course_name
                ).order_by(desc('enrolled_students')).all()
                
                for course in course_stats:
                    avg_grade = course.average_grade if course.average_grade else 0
                    print(f"  {course.course_code} - {course.course_name}: {course.enrolled_students} students, avg grade: {avg_grade:.1f}")
                
                # Department statistics using ORM
                print("\n3. Department statistics using ORM:")
                dept_stats = db.session.query(
                    Department.dept_name,
                    func.count(func.distinct(Course.course_id)).label('total_courses'),
                    func.count(func.distinct(Enrollment.student_id)).label('total_enrollments')
                ).outerjoin(Course).outerjoin(Enrollment).group_by(
                    Department.dept_id, Department.dept_name
                ).order_by(desc('total_enrollments')).all()
                
                for dept in dept_stats:
                    print(f"  {dept.dept_name}: {dept.total_courses} courses, {dept.total_enrollments} enrollments")
                
                return True
                
        except Exception as e:
            print(f"❌ Complex queries failed: {e}")
            return False
    
    def query_with_pandas(self):
        """
        Demonstrate querying with pandas for data analysis using ORM.
        
        Returns:
            bool: True if successful, False otherwise
        """
        try:
            with self.app.app_context():
                # Load data into pandas DataFrame using ORM
                print("1. Loading student data into pandas using ORM:")
                
                # Method 1: Using raw SQL with ORM session
                df = pd.read_sql(
                    "SELECT student_id, first_name, last_name, gpa, status, enrollment_date FROM students",
                    db.engine
                )
                
                print(f"  Loaded {len(df)} students")
                print(f"  Columns: {list(df.columns)}")
                
                # Method 2: Using ORM query and converting to DataFrame
                students_query = Student.query.with_entities(
                    Student.student_id,
                    Student.first_name,
                    Student.last_name,
                    Student.gpa,
                    Student.status,
                    Student.enrollment_date
                ).all()
                
                # Convert to DataFrame
                df_from_orm = pd.DataFrame([
                    {
                        'student_id': s.student_id,
                        'first_name': s.first_name,
                        'last_name': s.last_name,
                        'gpa': float(s.gpa) if s.gpa else None,
                        'status': s.status,
                        'enrollment_date': s.enrollment_date
                    }
                    for s in students_query
                ])
                
                print(f"  Loaded {len(df_from_orm)} students using ORM")
                
                # Basic statistics
                print("\n2. Basic statistics:")
                print(f"  Average GPA: {df['gpa'].mean():.2f}")
                print(f"  GPA standard deviation: {df['gpa'].std():.2f}")
                print(f"  Students by status:")
                print(df['status'].value_counts())
                
                # Filtering with pandas
                print("\n3. High GPA students (pandas filtering):")
                high_gpa = df[df['gpa'] >= 3.5]
                print(f"  Found {len(high_gpa)} students with GPA >= 3.5")
                print(high_gpa[['first_name', 'last_name', 'gpa']].head())
                
                # Grouping with pandas
                print("\n4. GPA by status (pandas grouping):")
                gpa_by_status = df.groupby('status')['gpa'].agg(['count', 'mean', 'std'])
                print(gpa_by_status)
                
                return True
                
        except Exception as e:
            print(f"❌ Pandas query failed: {e}")
            return False
    
    def demonstrate_query_optimization(self):
        """
        Demonstrate query optimization techniques using ORM.
        
        Returns:
            bool: True if successful, False otherwise
        """
        try:
            with self.app.app_context():
                print("=== Query Optimization Demonstration ===\n")
                
                # 1. Lazy loading vs Eager loading
                print("1. Lazy Loading (default):")
                # This will execute N+1 queries
                students = Student.query.limit(3).all()
                for student in students:
                    print(f"  Student: {student.first_name} {student.last_name}")
                    # This triggers a separate query for each student
                    enrollments = student.enrollments
                    print(f"    Enrollments: {len(enrollments)}")
                
                print("\n2. Eager Loading (optimized):")
                # This will execute only 1 query with JOIN
                students_optimized = Student.query.options(
                    joinedload(Student.enrollments)
                ).limit(3).all()
                
                for student in students_optimized:
                    print(f"  Student: {student.first_name} {student.last_name}")
                    # This doesn't trigger additional queries
                    enrollments = student.enrollments
                    print(f"    Enrollments: {len(enrollments)}")
                
                # 2. Using select_related for single foreign key
                print("\n3. Single Query with JOIN:")
                enrollments_with_details = db.session.query(Enrollment).join(
                    Student
                ).join(Course).options(
                    joinedload(Enrollment.student),
                    joinedload(Enrollment.course)
                ).limit(5).all()
                
                for enrollment in enrollments_with_details:
                    print(f"  {enrollment.student.first_name} enrolled in {enrollment.course.course_name}")
                
                # 3. Using exists() for efficient existence checks
                print("\n4. Efficient existence checks:")
                students_with_enrollments = Student.query.filter(
                    Student.enrollments.any()
                ).limit(3).all()
                
                for student in students_with_enrollments:
                    print(f"  {student.first_name} {student.last_name} has enrollments")
                
                return True
                
        except Exception as e:
            print(f"❌ Query optimization failed: {e}")
            return False

def main():
    """Main function to demonstrate data querying using Flask-SQLAlchemy ORM"""
    print("=== Flask + SQLAlchemy ORM Data Querying Demo ===\n")
    
    # Initialize data querier
    querier = DataQuerier()
    
    # Ensure tables exist
    with app.app_context():
        db.create_all()
    
    # Basic select operations
    print("1. Basic SELECT operations using ORM...")
    querier.basic_select()
    
    # WHERE clause examples
    print("\n2. WHERE clause filtering using ORM...")
    querier.where_clause_examples()
    
    # LIKE pattern matching
    print("\n3. LIKE pattern matching using ORM...")
    querier.like_pattern_matching()
    
    # ORDER BY examples
    print("\n4. ORDER BY sorting using ORM...")
    querier.order_by_examples()
    
    # LIMIT and pagination
    print("\n5. LIMIT and pagination using ORM...")
    querier.limit_pagination()
    
    # Aggregate functions
    print("\n6. Aggregate functions using ORM...")
    querier.aggregate_functions()
    
    # Complex queries
    print("\n7. Complex analytical queries using ORM...")
    querier.complex_queries()
    
    # Pandas integration
    print("\n8. Pandas data analysis using ORM...")
    querier.query_with_pandas()
    
    # Query optimization
    print("\n9. Query optimization techniques...")
    querier.demonstrate_query_optimization()
    
    print("\n=== Flask + SQLAlchemy ORM Data Querying Demo Complete ===")
    print("\nKey Features Demonstrated:")
    print("1. ✅ Basic SELECT Operations using ORM")
    print("2. ✅ WHERE Clause Filtering with ORM Methods")
    print("3. ✅ LIKE Pattern Matching using ORM")
    print("4. ✅ ORDER BY Sorting with ORM")
    print("5. ✅ LIMIT and Pagination using ORM")
    print("6. ✅ Aggregate Functions with ORM")
    print("7. ✅ Complex Analytical Queries using ORM")
    print("8. ✅ Pandas Integration with ORM Queries")
    print("9. ✅ Query Optimization Techniques")

# Standard Python idiom for running the script
if __name__ == "__main__":
    main()