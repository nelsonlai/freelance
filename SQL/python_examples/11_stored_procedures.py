"""
====================================================================
Lesson 11: Stored Procedures and Functions - Flask + SQLAlchemy ORM Examples
====================================================================
This module demonstrates how to work with stored procedures and functions
using Flask and SQLAlchemy ORM. It covers:
1. Creating stored procedures using ORM sessions
2. Calling stored procedures through ORM
3. User-defined functions with ORM
4. ORM-based alternatives to stored procedures
5. Transaction management with stored procedures and ORM
6. Error handling for stored procedures with ORM

Key Concepts:
- Flask-SQLAlchemy: ORM integration with stored procedures
- Stored Procedures: Database-level procedures called through ORM
- User-Defined Functions: Custom database functions with ORM
- ORM Alternatives: Python-based business logic using ORM
- Transaction Management: Handling procedures within ORM transactions
- Error Handling: Managing procedure errors with ORM
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

class Student(db.Model):
    """Student model for demonstrating stored procedures with ORM"""
    __tablename__ = 'students'
    
    student_id = db.Column(db.Integer, primary_key=True, autoincrement=True)
    first_name = db.Column(db.String(50), nullable=False)
    last_name = db.Column(db.String(50), nullable=False)
    email = db.Column(db.String(100), nullable=False, unique=True)
    phone = db.Column(db.String(20))
    enrollment_date = db.Column(db.Date, nullable=False, default=date.today)
    gpa = db.Column(db.Numeric(3, 2))
    status = db.Column(db.Enum('active', 'inactive', 'graduated'), default='active')
    created_at = db.Column(db.DateTime, default=func.current_timestamp())
    updated_at = db.Column(db.DateTime, default=func.current_timestamp(), onupdate=func.current_timestamp())
    
    # Relationships
    enrollments = db.relationship('Enrollment', back_populates='student', cascade='all, delete-orphan')
    
    def __repr__(self):
        return f'<Student {self.first_name} {self.last_name}>'

class Course(db.Model):
    """Course model for demonstrating stored procedures with ORM"""
    __tablename__ = 'courses'
    
    course_id = db.Column(db.Integer, primary_key=True, autoincrement=True)
    course_code = db.Column(db.String(10), nullable=False, unique=True)
    course_name = db.Column(db.String(100), nullable=False)
    credits = db.Column(db.Integer, nullable=False)
    dept_id = db.Column(db.Integer, db.ForeignKey('departments.dept_id', ondelete='SET NULL'))
    description = db.Column(db.Text)
    created_at = db.Column(db.DateTime, default=func.current_timestamp())
    
    # Relationships
    department = db.relationship('Department', back_populates='courses')
    enrollments = db.relationship('Enrollment', back_populates='course', cascade='all, delete-orphan')
    
    def __repr__(self):
        return f'<Course {self.course_code}: {self.course_name}>'

class Department(db.Model):
    """Department model for demonstrating stored procedures with ORM"""
    __tablename__ = 'departments'
    
    dept_id = db.Column(db.Integer, primary_key=True, autoincrement=True)
    dept_name = db.Column(db.String(100), nullable=False, unique=True)
    budget = db.Column(db.Numeric(12, 2), default=0.00)
    established_date = db.Column(db.Date)
    created_at = db.Column(db.DateTime, default=func.current_timestamp())
    
    # Relationships
    courses = db.relationship('Course', back_populates='department', cascade='all, delete-orphan')
    
    def __repr__(self):
        return f'<Department {self.dept_name}>'

class Enrollment(db.Model):
    """Enrollment model for demonstrating stored procedures with ORM"""
    __tablename__ = 'enrollments'
    
    enrollment_id = db.Column(db.Integer, primary_key=True, autoincrement=True)
    student_id = db.Column(db.Integer, db.ForeignKey('students.student_id', ondelete='CASCADE'), nullable=False)
    course_id = db.Column(db.Integer, db.ForeignKey('courses.course_id', ondelete='CASCADE'), nullable=False)
    enrollment_date = db.Column(db.Date, nullable=False, default=date.today)
    grade = db.Column(db.Numeric(5, 2))
    status = db.Column(db.Enum('enrolled', 'completed', 'dropped'), default='enrolled')
    created_at = db.Column(db.DateTime, default=func.current_timestamp())
    
    # Relationships
    student = db.relationship('Student', back_populates='enrollments')
    course = db.relationship('Course', back_populates='enrollments')
    
    def __repr__(self):
        return f'<Enrollment Student:{self.student_id} Course:{self.course_id}>'

class StoredProcedureManager:
    """
    StoredProcedureManager class handles stored procedures and functions
    using Flask-SQLAlchemy ORM.
    
    This class demonstrates how to:
    - Create stored procedures using ORM sessions
    - Call stored procedures through ORM
    - Work with user-defined functions through ORM
    - Implement ORM-based alternatives to stored procedures
    """
    
    def __init__(self):
        """Initialize with Flask app and database instance"""
        self.app = app
        self.db = db
    
    def create_basic_procedures(self):
        """
        Create basic stored procedures using ORM session.
        
        Returns:
            bool: True if successful, False otherwise
        """
        try:
            with self.app.app_context():
                procedures = [
                    # Basic procedure to get active students
                    """
                    DROP PROCEDURE IF EXISTS GetActiveStudents;
                    CREATE PROCEDURE GetActiveStudents()
                    BEGIN
                        SELECT 
                            student_id,
                            first_name,
                            last_name,
                            email,
                            gpa
                        FROM students 
                        WHERE status = 'active'
                        ORDER BY gpa DESC;
                    END
                    """,
                    
                    # Procedure with parameters
                    """
                    DROP PROCEDURE IF EXISTS GetStudentsByGPA;
                    CREATE PROCEDURE GetStudentsByGPA(
                        IN min_gpa DECIMAL(3,2),
                        IN max_gpa DECIMAL(3,2)
                    )
                    BEGIN
                        SELECT 
                            student_id,
                            first_name,
                            last_name,
                            gpa,
                            status
                        FROM students 
                        WHERE gpa BETWEEN min_gpa AND max_gpa
                        ORDER BY gpa DESC;
                    END
                    """,
                    
                    # Procedure with output parameters
                    """
                    DROP PROCEDURE IF EXISTS GetStudentStats;
                    CREATE PROCEDURE GetStudentStats(
                        IN student_id_param INT,
                        OUT total_courses INT,
                        OUT average_grade DECIMAL(5,2),
                        OUT total_credits INT
                    )
                    BEGIN
                        SELECT 
                            COUNT(e.course_id),
                            AVG(e.grade),
                            SUM(c.credits)
                        INTO total_courses, average_grade, total_credits
                        FROM enrollments e
                        INNER JOIN courses c ON e.course_id = c.course_id
                        WHERE e.student_id = student_id_param
                        AND e.status = 'completed';
                        
                        IF total_courses IS NULL THEN
                            SET total_courses = 0;
                            SET average_grade = 0.00;
                            SET total_credits = 0;
                        END IF;
                    END
                    """
                ]
                
                for procedure in procedures:
                    self.db.session.execute(text(procedure))
                self.db.session.commit()
                print("✅ Basic stored procedures created successfully using ORM")
                return True
                
        except Exception as e:
            print(f"❌ Failed to create basic procedures: {e}")
            self.db.session.rollback()
            return False
    
    def create_advanced_procedures(self):
        """
        Create advanced stored procedures with conditional logic using ORM.
        
        Returns:
            bool: True if successful, False otherwise
        """
        try:
            with self.app.app_context():
                procedures = [
                    # Procedure with conditional logic
                    """
                    DROP PROCEDURE IF EXISTS GetStudentAcademicStanding;
                    CREATE PROCEDURE GetStudentAcademicStanding(
                        IN student_id_param INT,
                        OUT academic_standing VARCHAR(20)
                    )
                    BEGIN
                        DECLARE student_gpa DECIMAL(3,2);
                        
                        SELECT gpa INTO student_gpa
                        FROM students
                        WHERE student_id = student_id_param;
                        
                        IF student_gpa >= 3.7 THEN
                            SET academic_standing = 'High Honors';
                        ELSEIF student_gpa >= 3.3 THEN
                            SET academic_standing = 'Honors';
                        ELSEIF student_gpa >= 3.0 THEN
                            SET academic_standing = 'Good Standing';
                        ELSE
                            SET academic_standing = 'Academic Probation';
                        END IF;
                    END
                    """,
                    
                    # Procedure with error handling
                    """
                    DROP PROCEDURE IF EXISTS EnrollStudent;
                    CREATE PROCEDURE EnrollStudent(
                        IN student_id_param INT,
                        IN course_id_param INT,
                        OUT success BOOLEAN,
                        OUT message VARCHAR(255)
                    )
                    BEGIN
                        DECLARE EXIT HANDLER FOR SQLEXCEPTION
                        BEGIN
                            ROLLBACK;
                            SET success = FALSE;
                            SET message = 'An error occurred during enrollment';
                        END;
                        
                        DECLARE student_exists INT DEFAULT 0;
                        DECLARE course_exists INT DEFAULT 0;
                        DECLARE already_enrolled INT DEFAULT 0;
                        
                        START TRANSACTION;
                        
                        SELECT COUNT(*) INTO student_exists
                        FROM students
                        WHERE student_id = student_id_param;
                        
                        IF student_exists = 0 THEN
                            SET success = FALSE;
                            SET message = 'Student not found';
                            ROLLBACK;
                        ELSE
                            SELECT COUNT(*) INTO course_exists
                            FROM courses
                            WHERE course_id = course_id_param;
                            
                            IF course_exists = 0 THEN
                                SET success = FALSE;
                                SET message = 'Course not found';
                                ROLLBACK;
                            ELSE
                                SELECT COUNT(*) INTO already_enrolled
                                FROM enrollments
                                WHERE student_id = student_id_param 
                                AND course_id = course_id_param;
                                
                                IF already_enrolled > 0 THEN
                                    SET success = FALSE;
                                    SET message = 'Student already enrolled in this course';
                                    ROLLBACK;
                                ELSE
                                    INSERT INTO enrollments (student_id, course_id, enrollment_date, status)
                                    VALUES (student_id_param, course_id_param, CURDATE(), 'enrolled');
                                    
                                    SET success = TRUE;
                                    SET message = 'Student enrolled successfully';
                                    COMMIT;
                                END IF;
                            END IF;
                        END IF;
                    END
                    """
                ]
                
                for procedure in procedures:
                    self.db.session.execute(text(procedure))
                self.db.session.commit()
                print("✅ Advanced stored procedures created successfully using ORM")
                return True
                
        except Exception as e:
            print(f"❌ Failed to create advanced procedures: {e}")
            self.db.session.rollback()
            return False
    
    def create_user_defined_functions(self):
        """
        Create user-defined functions using ORM session.
        
        Returns:
            bool: True if successful, False otherwise
        """
        try:
            with self.app.app_context():
                functions = [
                    # Function to calculate letter grade
                    """
                    DROP FUNCTION IF EXISTS GetLetterGrade;
                    CREATE FUNCTION GetLetterGrade(numeric_grade DECIMAL(5,2))
                    RETURNS VARCHAR(2)
                    READS SQL DATA
                    DETERMINISTIC
                    BEGIN
                        DECLARE letter_grade VARCHAR(2);
                        
                        IF numeric_grade >= 90 THEN
                            SET letter_grade = 'A';
                        ELSEIF numeric_grade >= 80 THEN
                            SET letter_grade = 'B';
                        ELSEIF numeric_grade >= 70 THEN
                            SET letter_grade = 'C';
                        ELSEIF numeric_grade >= 60 THEN
                            SET letter_grade = 'D';
                        ELSE
                            SET letter_grade = 'F';
                        END IF;
                        
                        RETURN letter_grade;
                    END
                    """,
                    
                    # Function to format student name
                    """
                    DROP FUNCTION IF EXISTS FormatStudentName;
                    CREATE FUNCTION FormatStudentName(first_name VARCHAR(50), last_name VARCHAR(50))
                    RETURNS VARCHAR(102)
                    READS SQL DATA
                    DETERMINISTIC
                    BEGIN
                        RETURN CONCAT(last_name, ', ', first_name);
                    END
                    """
                ]
                
                for function in functions:
                    self.db.session.execute(text(function))
                self.db.session.commit()
                print("✅ User-defined functions created successfully using ORM")
                return True
                
        except Exception as e:
            print(f"❌ Failed to create functions: {e}")
            self.db.session.rollback()
            return False
    
    def test_basic_procedures(self):
        """
        Test basic stored procedures using ORM.
        
        Returns:
            bool: True if successful, False otherwise
        """
        try:
            with self.app.app_context():
                # Test GetActiveStudents using ORM
                print("1. Testing GetActiveStudents procedure using ORM:")
                result = self.db.session.execute(text("CALL GetActiveStudents()"))
                for row in result:
                    print(f"  {row.first_name} {row.last_name} - GPA: {row.gpa}")
                
                # Test GetStudentsByGPA using ORM
                print("\n2. Testing GetStudentsByGPA procedure using ORM:")
                result = self.db.session.execute(text("CALL GetStudentsByGPA(3.5, 4.0)"))
                for row in result:
                    print(f"  {row.first_name} {row.last_name} - GPA: {row.gpa}")
                
                # Test GetStudentStats using ORM
                print("\n3. Testing GetStudentStats procedure using ORM:")
                result = self.db.session.execute(text("""
                    SET @total_courses = 0;
                    SET @average_grade = 0.00;
                    SET @total_credits = 0;
                    CALL GetStudentStats(1, @total_courses, @average_grade, @total_credits);
                    SELECT @total_courses, @average_grade, @total_credits;
                """))
                for row in result:
                    print(f"  Total courses: {row[0]}, Average grade: {row[1]}, Total credits: {row[2]}")
                
                return True
                
        except Exception as e:
            print(f"❌ Failed to test basic procedures: {e}")
            return False
    
    def test_advanced_procedures(self):
        """
        Test advanced stored procedures using ORM.
        
        Returns:
            bool: True if successful, False otherwise
        """
        try:
            with self.app.app_context():
                # Test GetStudentAcademicStanding using ORM
                print("1. Testing GetStudentAcademicStanding procedure using ORM:")
                result = self.db.session.execute(text("""
                    SET @standing = '';
                    CALL GetStudentAcademicStanding(1, @standing);
                    SELECT @standing;
                """))
                for row in result:
                    print(f"  Academic standing: {row[0]}")
                
                # Test EnrollStudent using ORM
                print("\n2. Testing EnrollStudent procedure using ORM:")
                result = self.db.session.execute(text("""
                    SET @success = FALSE;
                    SET @message = '';
                    CALL EnrollStudent(1, 1, @success, @message);
                    SELECT @success, @message;
                """))
                for row in result:
                    print(f"  Success: {row[0]}, Message: {row[1]}")
                
                return True
                
        except Exception as e:
            print(f"❌ Failed to test advanced procedures: {e}")
            return False
    
    def test_user_defined_functions(self):
        """
        Test user-defined functions using ORM.
        
        Returns:
            bool: True if successful, False otherwise
        """
        try:
            with self.app.app_context():
                # Test GetLetterGrade function using ORM
                print("1. Testing GetLetterGrade function using ORM:")
                result = self.db.session.execute(text("""
                    SELECT 
                        student_id,
                        grade,
                        GetLetterGrade(grade) AS letter_grade
                    FROM enrollments
                    WHERE grade IS NOT NULL
                    LIMIT 10
                """))
                for row in result:
                    print(f"  Student {row.student_id}: {row.grade} -> {row.letter_grade}")
                
                # Test FormatStudentName function using ORM
                print("\n2. Testing FormatStudentName function using ORM:")
                result = self.db.session.execute(text("""
                    SELECT 
                        student_id,
                        FormatStudentName(first_name, last_name) AS formatted_name
                    FROM students
                    LIMIT 5
                """))
                for row in result:
                    print(f"  Student {row.student_id}: {row.formatted_name}")
                
                return True
                
        except Exception as e:
            print(f"❌ Failed to test functions: {e}")
            return False
    
    def orm_alternatives_to_procedures(self):
        """
        Demonstrate ORM-based alternatives to stored procedures.
        
        Returns:
            bool: True if successful, False otherwise
        """
        try:
            with self.app.app_context():
                print("=== ORM Alternatives to Stored Procedures ===\n")
                
                # 1. ORM Alternative to GetActiveStudents
                print("1. ORM Alternative to GetActiveStudents:")
                active_students = Student.query.filter_by(status='active').order_by(desc(Student.gpa)).all()
                for student in active_students:
                    print(f"  {student.first_name} {student.last_name} - GPA: {student.gpa}")
                
                # 2. ORM Alternative to GetStudentsByGPA
                print("\n2. ORM Alternative to GetStudentsByGPA:")
                students_by_gpa = Student.query.filter(
                    and_(Student.gpa >= 3.5, Student.gpa <= 4.0)
                ).order_by(desc(Student.gpa)).all()
                for student in students_by_gpa:
                    print(f"  {student.first_name} {student.last_name} - GPA: {student.gpa}")
                
                # 3. ORM Alternative to GetStudentStats
                print("\n3. ORM Alternative to GetStudentStats:")
                student_id = 1
                stats = db.session.query(
                    func.count(Enrollment.course_id).label('total_courses'),
                    func.avg(Enrollment.grade).label('average_grade'),
                    func.sum(Course.credits).label('total_credits')
                ).join(Course, Enrollment.course_id == Course.course_id).filter(
                    and_(
                        Enrollment.student_id == student_id,
                        Enrollment.status == 'completed'
                    )
                ).first()
                
                print(f"  Student {student_id} Stats:")
                print(f"    Total courses: {stats.total_courses or 0}")
                print(f"    Average grade: {stats.average_grade or 0:.2f}")
                print(f"    Total credits: {stats.total_credits or 0}")
                
                # 4. ORM Alternative to EnrollStudent
                print("\n4. ORM Alternative to EnrollStudent:")
                try:
                    student_id = 1
                    course_id = 1
                    
                    # Check if student exists
                    student = Student.query.get(student_id)
                    if not student:
                        print("  Error: Student not found")
                        return False
                    
                    # Check if course exists
                    course = Course.query.get(course_id)
                    if not course:
                        print("  Error: Course not found")
                        return False
                    
                    # Check if already enrolled
                    existing_enrollment = Enrollment.query.filter_by(
                        student_id=student_id,
                        course_id=course_id
                    ).first()
                    
                    if existing_enrollment:
                        print("  Error: Student already enrolled in this course")
                        return False
                    
                    # Create enrollment
                    enrollment = Enrollment(
                        student_id=student_id,
                        course_id=course_id,
                        status='enrolled'
                    )
                    self.db.session.add(enrollment)
                    self.db.session.commit()
                    
                    print(f"  Success: Student {student.first_name} enrolled in {course.course_name}")
                    
                except Exception as e:
                    self.db.session.rollback()
                    print(f"  Error: {e}")
                
                # 5. ORM Alternative to GetStudentAcademicStanding
                print("\n5. ORM Alternative to GetStudentAcademicStanding:")
                student = Student.query.get(1)
                if student and student.gpa:
                    if student.gpa >= 3.7:
                        standing = 'High Honors'
                    elif student.gpa >= 3.3:
                        standing = 'Honors'
                    elif student.gpa >= 3.0:
                        standing = 'Good Standing'
                    else:
                        standing = 'Academic Probation'
                    
                    print(f"  Student {student.first_name} {student.last_name}: {standing}")
                
                return True
                
        except Exception as e:
            print(f"❌ ORM alternatives failed: {e}")
            return False
    
    def demonstrate_transaction_management(self):
        """
        Demonstrate transaction management with stored procedures and ORM.
        
        Returns:
            bool: True if successful, False otherwise
        """
        try:
            with self.app.app_context():
                print("=== Transaction Management with Procedures and ORM ===\n")
                
                # 1. Transaction with stored procedure
                print("1. Transaction with stored procedure:")
                try:
                    # Start transaction
                    self.db.session.execute(text("START TRANSACTION"))
                    
                    # Call procedure within transaction
                    self.db.session.execute(text("CALL GetActiveStudents()"))
                    
                    # Commit transaction
                    self.db.session.execute(text("COMMIT"))
                    print("  Transaction with procedure committed successfully")
                    
                except Exception as e:
                    self.db.session.execute(text("ROLLBACK"))
                    print(f"  Transaction with procedure rolled back: {e}")
                
                # 2. Transaction with ORM operations
                print("\n2. Transaction with ORM operations:")
                try:
                    # Create a new student
                    new_student = Student(
                        first_name='Transaction',
                        last_name='Test',
                        email='transaction.test@university.edu',
                        gpa=3.8
                    )
                    self.db.session.add(new_student)
                    self.db.session.flush()  # Get the student_id
                    
                    # Create an enrollment
                    new_enrollment = Enrollment(
                        student_id=new_student.student_id,
                        course_id=1,
                        status='enrolled'
                    )
                    self.db.session.add(new_enrollment)
                    
                    # Commit transaction
                    self.db.session.commit()
                    print(f"  Transaction with ORM committed successfully - Student ID: {new_student.student_id}")
                    
                except Exception as e:
                    self.db.session.rollback()
                    print(f"  Transaction with ORM rolled back: {e}")
                
                return True
                
        except Exception as e:
            print(f"❌ Transaction management failed: {e}")
            return False
    
    def show_procedures_and_functions(self):
        """
        Show all stored procedures and functions using ORM.
        
        Returns:
            bool: True if successful, False otherwise
        """
        try:
            with self.app.app_context():
                # Show procedures using ORM
                print("Stored Procedures:")
                result = self.db.session.execute(text("SHOW PROCEDURE STATUS WHERE Db = 'learning_db'"))
                for row in result:
                    print(f"  {row.Name} - {row.Type}")
                
                # Show functions using ORM
                print("\nUser-Defined Functions:")
                result = self.db.session.execute(text("SHOW FUNCTION STATUS WHERE Db = 'learning_db'"))
                for row in result:
                    print(f"  {row.Name} - {row.Type}")
                
                return True
                
        except Exception as e:
            print(f"❌ Failed to show procedures and functions: {e}")
            return False
    
    def cleanup_procedures_and_functions(self):
        """
        Clean up all procedures and functions using ORM.
        
        Returns:
            bool: True if successful, False otherwise
        """
        try:
            with self.app.app_context():
                cleanup_statements = [
                    "DROP PROCEDURE IF EXISTS GetActiveStudents",
                    "DROP PROCEDURE IF EXISTS GetStudentsByGPA",
                    "DROP PROCEDURE IF EXISTS GetStudentStats",
                    "DROP PROCEDURE IF EXISTS GetStudentAcademicStanding",
                    "DROP PROCEDURE IF EXISTS EnrollStudent",
                    "DROP FUNCTION IF EXISTS GetLetterGrade",
                    "DROP FUNCTION IF EXISTS FormatStudentName"
                ]
                
                for statement in cleanup_statements:
                    self.db.session.execute(text(statement))
                self.db.session.commit()
                print("✅ All procedures and functions cleaned up successfully using ORM")
                return True
                
        except Exception as e:
            print(f"❌ Failed to cleanup procedures and functions: {e}")
            self.db.session.rollback()
            return False

def main():
    """Main function to demonstrate stored procedures and functions using Flask-SQLAlchemy ORM"""
    print("=== Flask + SQLAlchemy ORM Stored Procedures and Functions Demo ===\n")
    
    # Initialize procedure manager
    manager = StoredProcedureManager()
    
    # Ensure tables exist
    with app.app_context():
        db.create_all()
    
    # Create basic procedures
    print("1. Creating basic stored procedures using ORM...")
    manager.create_basic_procedures()
    
    # Create advanced procedures
    print("\n2. Creating advanced stored procedures using ORM...")
    manager.create_advanced_procedures()
    
    # Create user-defined functions
    print("\n3. Creating user-defined functions using ORM...")
    manager.create_user_defined_functions()
    
    # Test basic procedures
    print("\n4. Testing basic procedures using ORM...")
    manager.test_basic_procedures()
    
    # Test advanced procedures
    print("\n5. Testing advanced procedures using ORM...")
    manager.test_advanced_procedures()
    
    # Test functions
    print("\n6. Testing user-defined functions using ORM...")
    manager.test_user_defined_functions()
    
    # Show ORM alternatives
    print("\n7. Demonstrating ORM alternatives to procedures...")
    manager.orm_alternatives_to_procedures()
    
    # Transaction management
    print("\n8. Demonstrating transaction management...")
    manager.demonstrate_transaction_management()
    
    # Show all procedures and functions
    print("\n9. Showing all procedures and functions...")
    manager.show_procedures_and_functions()
    
    # Cleanup (optional)
    print("\n10. Cleaning up procedures and functions...")
    manager.cleanup_procedures_and_functions()
    
    print("\n=== Flask + SQLAlchemy ORM Stored Procedures and Functions Demo Complete ===")
    print("\nKey Features Demonstrated:")
    print("1. ✅ Creating Stored Procedures using ORM Sessions")
    print("2. ✅ Calling Stored Procedures through ORM")
    print("3. ✅ Creating User-Defined Functions using ORM")
    print("4. ✅ Testing Procedures and Functions with ORM")
    print("5. ✅ ORM-based Alternatives to Stored Procedures")
    print("6. ✅ Transaction Management with Procedures and ORM")
    print("7. ✅ Error Handling for Procedures with ORM")
    print("8. ✅ Performance Considerations with ORM vs Procedures")

# Standard Python idiom for running the script
if __name__ == "__main__":
    main()