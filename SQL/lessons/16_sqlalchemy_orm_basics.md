# Lesson 16: SQLAlchemy ORM Basics

## 📚 Learning Objectives

By the end of this lesson, you will be able to:
- Understand Object-Relational Mapping (ORM) concepts
- Create SQLAlchemy models and relationships
- Perform CRUD operations using the ORM
- Handle database sessions and transactions
- Use SQLAlchemy for data validation and constraints
- Understand the benefits and limitations of ORMs

## 🎯 Prerequisites

- Completed Lessons 1-15
- Understanding of Python programming
- Knowledge of database relationships and constraints
- Basic understanding of object-oriented programming

## 📖 Table of Contents

1. [Introduction to SQLAlchemy ORM](#introduction-to-sqlalchemy-orm)
2. [Setting Up SQLAlchemy](#setting-up-sqlalchemy)
3. [Creating Models](#creating-models)
4. [Database Relationships](#database-relationships)
5. [CRUD Operations](#crud-operations)
6. [Sessions and Transactions](#sessions-and-transactions)
7. [Querying with ORM](#querying-with-orm)
8. [Data Validation and Constraints](#data-validation-and-constraints)
9. [Best Practices](#best-practices)

---

## 1. Introduction to SQLAlchemy ORM

**SQLAlchemy ORM** (Object-Relational Mapping) is a Python library that provides a high-level interface for interacting with databases using Python objects instead of raw SQL.

### Benefits of SQLAlchemy ORM

- **Pythonic**: Use Python objects instead of SQL strings
- **Type Safety**: Leverage Python's type system
- **Automatic Mapping**: Map database tables to Python classes
- **Relationship Management**: Handle foreign keys automatically
- **Cross-Database**: Work with multiple database engines
- **Migration Support**: Database schema versioning

### ORM vs Raw SQL

| Aspect | ORM | Raw SQL |
|--------|-----|---------|
| **Learning Curve** | Steeper initially | Simpler for basic queries |
| **Performance** | Slightly slower | Faster for complex queries |
| **Maintainability** | Better for large applications | Can become complex |
| **Database Agnostic** | Yes | No |
| **Type Safety** | Yes | No |

---

## 2. Setting Up SQLAlchemy

### Installation and Basic Setup

```python
# Install SQLAlchemy
# pip install sqlalchemy pymysql

from sqlalchemy import create_engine, Column, Integer, String, Float, Date, ForeignKey
from sqlalchemy.ext.declarative import declarative_base
from sqlalchemy.orm import sessionmaker, relationship
from datetime import date
import os
from dotenv import load_dotenv

# Load environment variables
load_dotenv()

# Database configuration
DB_HOST = os.getenv('DB_HOST', 'localhost')
DB_USER = os.getenv('DB_USER', 'student')
DB_PASSWORD = os.getenv('DB_PASSWORD', 'student_password')
DB_NAME = os.getenv('DB_NAME', 'school_db')

# Create database engine
engine = create_engine(
    f'mysql+pymysql://{DB_USER}:{DB_PASSWORD}@{DB_HOST}/{DB_NAME}',
    echo=True  # Set to False in production
)

# Create base class for models
Base = declarative_base()

# Create session factory
SessionLocal = sessionmaker(autocommit=False, autoflush=False, bind=engine)

# Dependency to get database session
def get_db():
    db = SessionLocal()
    try:
        yield db
    finally:
        db.close()
```

---

## 3. Creating Models

### Basic Model Definition

```python
class Department(Base):
    __tablename__ = 'departments'
    
    department_id = Column(Integer, primary_key=True, autoincrement=True)
    name = Column(String(100), nullable=False)
    description = Column(String(500))
    created_at = Column(Date, default=date.today)
    
    # Relationship
    students = relationship("Student", back_populates="department")
    courses = relationship("Course", back_populates="department")
    
    def __repr__(self):
        return f"<Department(id={self.department_id}, name='{self.name}')>"

class Student(Base):
    __tablename__ = 'students'
    
    student_id = Column(Integer, primary_key=True, autoincrement=True)
    first_name = Column(String(50), nullable=False)
    last_name = Column(String(50), nullable=False)
    email = Column(String(100), unique=True, nullable=False)
    department_id = Column(Integer, ForeignKey('departments.department_id'), nullable=False)
    gpa = Column(Float)
    status = Column(String(20), default='Active')
    enrollment_date = Column(Date, default=date.today)
    
    # Relationships
    department = relationship("Department", back_populates="students")
    enrollments = relationship("Enrollment", back_populates="student")
    
    @property
    def full_name(self):
        return f"{self.first_name} {self.last_name}"
    
    def __repr__(self):
        return f"<Student(id={self.student_id}, name='{self.full_name}')>"
```

### Advanced Model with Constraints

```python
from sqlalchemy import CheckConstraint, Index
from sqlalchemy.orm import validates

class Course(Base):
    __tablename__ = 'courses'
    
    course_id = Column(Integer, primary_key=True, autoincrement=True)
    course_code = Column(String(10), unique=True, nullable=False)
    name = Column(String(100), nullable=False)
    description = Column(String(500))
    credits = Column(Integer, nullable=False)
    department_id = Column(Integer, ForeignKey('departments.department_id'), nullable=False)
    capacity = Column(Integer, default=30)
    created_at = Column(Date, default=date.today)
    
    # Relationships
    department = relationship("Department", back_populates="courses")
    enrollments = relationship("Enrollment", back_populates="course")
    
    # Constraints
    __table_args__ = (
        CheckConstraint('credits > 0', name='check_credits_positive'),
        CheckConstraint('capacity > 0', name='check_capacity_positive'),
        Index('idx_course_code', 'course_code'),
        Index('idx_course_department', 'department_id')
    )
    
    @validates('credits')
    def validate_credits(self, key, credits):
        if credits <= 0:
            raise ValueError("Credits must be positive")
        return credits
    
    @validates('capacity')
    def validate_capacity(self, key, capacity):
        if capacity <= 0:
            raise ValueError("Capacity must be positive")
        return capacity
    
    def __repr__(self):
        return f"<Course(id={self.course_id}, code='{self.course_code}', name='{self.name}')>"

class Enrollment(Base):
    __tablename__ = 'enrollments'
    
    enrollment_id = Column(Integer, primary_key=True, autoincrement=True)
    student_id = Column(Integer, ForeignKey('students.student_id'), nullable=False)
    course_id = Column(Integer, ForeignKey('courses.course_id'), nullable=False)
    enrollment_date = Column(Date, default=date.today)
    grade = Column(Integer)
    semester = Column(String(20))
    
    # Relationships
    student = relationship("Student", back_populates="enrollments")
    course = relationship("Course", back_populates="enrollments")
    
    # Constraints
    __table_args__ = (
        CheckConstraint('grade >= 0 AND grade <= 100', name='check_grade_range'),
        Index('idx_enrollment_student', 'student_id'),
        Index('idx_enrollment_course', 'course_id'),
        Index('idx_enrollment_unique', 'student_id', 'course_id', unique=True)
    )
    
    @validates('grade')
    def validate_grade(self, key, grade):
        if grade is not None and (grade < 0 or grade > 100):
            raise ValueError("Grade must be between 0 and 100")
        return grade
    
    def __repr__(self):
        return f"<Enrollment(id={self.enrollment_id}, student_id={self.student_id}, course_id={self.course_id})>"
```

---

## 4. Database Relationships

### One-to-Many Relationships

```python
# Department -> Students (One-to-Many)
# Department -> Courses (One-to-Many)

class Department(Base):
    __tablename__ = 'departments'
    
    department_id = Column(Integer, primary_key=True)
    name = Column(String(100), nullable=False)
    
    # One-to-Many relationships
    students = relationship("Student", back_populates="department")
    courses = relationship("Course", back_populates="department")

class Student(Base):
    __tablename__ = 'students'
    
    student_id = Column(Integer, primary_key=True)
    first_name = Column(String(50), nullable=False)
    department_id = Column(Integer, ForeignKey('departments.department_id'))
    
    # Many-to-One relationship
    department = relationship("Department", back_populates="students")
```

### Many-to-Many Relationships

```python
# Students <-> Courses (Many-to-Many through Enrollments)

class Student(Base):
    __tablename__ = 'students'
    
    student_id = Column(Integer, primary_key=True)
    first_name = Column(String(50), nullable=False)
    
    # Many-to-Many through Enrollment
    courses = relationship("Course", secondary="enrollments", back_populates="students")

class Course(Base):
    __tablename__ = 'courses'
    
    course_id = Column(Integer, primary_key=True)
    course_code = Column(String(10), nullable=False)
    
    # Many-to-Many through Enrollment
    students = relationship("Student", secondary="enrollments", back_populates="courses")
```

### Relationship Loading Strategies

```python
from sqlalchemy.orm import joinedload, selectinload

# Eager loading - load relationships immediately
def get_department_with_students(department_id):
    session = SessionLocal()
    try:
        department = session.query(Department)\
            .options(joinedload(Department.students))\
            .filter(Department.department_id == department_id)\
            .first()
        return department
    finally:
        session.close()

# Lazy loading - load relationships when accessed
def get_department_lazy(department_id):
    session = SessionLocal()
    try:
        department = session.query(Department)\
            .filter(Department.department_id == department_id)\
            .first()
        
        # Access students - this will trigger a query
        students = department.students
        return department, students
    finally:
        session.close()
```

---

## 5. CRUD Operations

### Create Operations

```python
def create_department(name, description=None):
    """Create a new department"""
    session = SessionLocal()
    try:
        department = Department(
            name=name,
            description=description
        )
        session.add(department)
        session.commit()
        session.refresh(department)
        return department
    except Exception as e:
        session.rollback()
        raise e
    finally:
        session.close()

def create_student(first_name, last_name, email, department_id, gpa=None):
    """Create a new student"""
    session = SessionLocal()
    try:
        student = Student(
            first_name=first_name,
            last_name=last_name,
            email=email,
            department_id=department_id,
            gpa=gpa
        )
        session.add(student)
        session.commit()
        session.refresh(student)
        return student
    except Exception as e:
        session.rollback()
        raise e
    finally:
        session.close()

# Example usage
dept = create_department("Computer Science", "CS Department")
student = create_student("John", "Doe", "john.doe@email.com", dept.department_id, 3.75)
```

### Read Operations

```python
def get_student_by_id(student_id):
    """Get student by ID"""
    session = SessionLocal()
    try:
        return session.query(Student).filter(Student.student_id == student_id).first()
    finally:
        session.close()

def get_students_by_department(department_id):
    """Get all students in a department"""
    session = SessionLocal()
    try:
        return session.query(Student)\
            .filter(Student.department_id == department_id)\
            .all()
    finally:
        session.close()

def get_students_with_high_gpa(min_gpa=3.5):
    """Get students with GPA above threshold"""
    session = SessionLocal()
    try:
        return session.query(Student)\
            .filter(Student.gpa >= min_gpa)\
            .order_by(Student.gpa.desc())\
            .all()
    finally:
        session.close()

def search_students_by_name(name_pattern):
    """Search students by name pattern"""
    session = SessionLocal()
    try:
        return session.query(Student)\
            .filter(
                (Student.first_name.like(f'%{name_pattern}%')) |
                (Student.last_name.like(f'%{name_pattern}%'))
            )\
            .all()
    finally:
        session.close()
```

### Update Operations

```python
def update_student_gpa(student_id, new_gpa):
    """Update student GPA"""
    session = SessionLocal()
    try:
        student = session.query(Student).filter(Student.student_id == student_id).first()
        if student:
            student.gpa = new_gpa
            session.commit()
            return student
        return None
    except Exception as e:
        session.rollback()
        raise e
    finally:
        session.close()

def update_student_status(student_id, new_status):
    """Update student status"""
    session = SessionLocal()
    try:
        student = session.query(Student).filter(Student.student_id == student_id).first()
        if student:
            student.status = new_status
            session.commit()
            return student
        return None
    except Exception as e:
        session.rollback()
        raise e
    finally:
        session.close()

def bulk_update_students_status(student_ids, new_status):
    """Update multiple students' status"""
    session = SessionLocal()
    try:
        session.query(Student)\
            .filter(Student.student_id.in_(student_ids))\
            .update({Student.status: new_status}, synchronize_session=False)
        session.commit()
        return len(student_ids)
    except Exception as e:
        session.rollback()
        raise e
    finally:
        session.close()
```

### Delete Operations

```python
def delete_student(student_id):
    """Delete a student"""
    session = SessionLocal()
    try:
        student = session.query(Student).filter(Student.student_id == student_id).first()
        if student:
            session.delete(student)
            session.commit()
            return True
        return False
    except Exception as e:
        session.rollback()
        raise e
    finally:
        session.close()

def delete_students_by_status(status):
    """Delete students by status"""
    session = SessionLocal()
    try:
        deleted_count = session.query(Student)\
            .filter(Student.status == status)\
            .delete(synchronize_session=False)
        session.commit()
        return deleted_count
    except Exception as e:
        session.rollback()
        raise e
    finally:
        session.close()
```

---

## 6. Sessions and Transactions

### Session Management

```python
from contextlib import contextmanager

@contextmanager
def get_session():
    """Context manager for database sessions"""
    session = SessionLocal()
    try:
        yield session
        session.commit()
    except Exception:
        session.rollback()
        raise
    finally:
        session.close()

# Usage with context manager
def create_student_safe(first_name, last_name, email, department_id):
    """Create student with automatic transaction management"""
    with get_session() as session:
        student = Student(
            first_name=first_name,
            last_name=last_name,
            email=email,
            department_id=department_id
        )
        session.add(student)
        session.flush()  # Get the ID without committing
        return student.student_id
```

### Manual Transaction Control

```python
def transfer_student_to_department(student_id, new_department_id):
    """Transfer student with transaction control"""
    session = SessionLocal()
    try:
        # Start transaction
        session.begin()
        
        # Get student
        student = session.query(Student).filter(Student.student_id == student_id).first()
        if not student:
            raise ValueError("Student not found")
        
        # Update department
        student.department_id = new_department_id
        
        # Create audit log entry
        audit_entry = {
            'table_name': 'students',
            'operation': 'UPDATE',
            'record_id': student_id,
            'changes': {'department_id': new_department_id}
        }
        # Log audit entry (simplified)
        print(f"Audit: {audit_entry}")
        
        # Commit transaction
        session.commit()
        return True
        
    except Exception as e:
        # Rollback on error
        session.rollback()
        raise e
    finally:
        session.close()
```

---

## 7. Querying with ORM

### Basic Queries

```python
def get_all_active_students():
    """Get all active students with their departments"""
    session = SessionLocal()
    try:
        return session.query(Student)\
            .join(Department)\
            .filter(Student.status == 'Active')\
            .all()
    finally:
        session.close()

def get_students_with_courses():
    """Get students and their enrolled courses"""
    session = SessionLocal()
    try:
        return session.query(Student)\
            .join(Enrollment)\
            .join(Course)\
            .filter(Student.status == 'Active')\
            .all()
    finally:
        session.close()
```

### Advanced Queries

```python
from sqlalchemy import func, and_, or_

def get_department_statistics():
    """Get statistics for each department"""
    session = SessionLocal()
    try:
        return session.query(
            Department.name,
            func.count(Student.student_id).label('student_count'),
            func.avg(Student.gpa).label('average_gpa'),
            func.min(Student.gpa).label('min_gpa'),
            func.max(Student.gpa).label('max_gpa')
        )\
        .join(Student, Department.department_id == Student.department_id)\
        .filter(Student.gpa.isnot(None))\
        .group_by(Department.department_id, Department.name)\
        .all()
    finally:
        session.close()

def get_top_students(limit=10):
    """Get top students by GPA"""
    session = SessionLocal()
    try:
        return session.query(Student)\
            .filter(Student.gpa.isnot(None))\
            .order_by(Student.gpa.desc())\
            .limit(limit)\
            .all()
    finally:
        session.close()

def get_students_with_grades_in_range(min_grade=85, max_grade=100):
    """Get students with grades in specified range"""
    session = SessionLocal()
    try:
        return session.query(Student)\
            .join(Enrollment)\
            .filter(
                and_(
                    Enrollment.grade >= min_grade,
                    Enrollment.grade <= max_grade
                )
            )\
            .distinct()\
            .all()
    finally:
        session.close()
```

### Subqueries and Complex Joins

```python
def get_students_with_above_average_gpa():
    """Get students with GPA above department average"""
    session = SessionLocal()
    try:
        # Subquery for department averages
        dept_avg = session.query(
            Student.department_id,
            func.avg(Student.gpa).label('dept_avg')
        )\
        .filter(Student.gpa.isnot(None))\
        .group_by(Student.department_id)\
        .subquery()
        
        # Main query
        return session.query(Student)\
            .join(dept_avg, Student.department_id == dept_avg.c.department_id)\
            .filter(Student.gpa > dept_avg.c.dept_avg)\
            .all()
    finally:
        session.close()

def get_course_enrollment_stats():
    """Get enrollment statistics for each course"""
    session = SessionLocal()
    try:
        return session.query(
            Course.course_code,
            Course.name,
            func.count(Enrollment.enrollment_id).label('enrollment_count'),
            func.avg(Enrollment.grade).label('average_grade'),
            func.count(
                func.case([(Enrollment.grade >= 85, 1)], else_=None)
            ).label('passing_count')
        )\
        .outerjoin(Enrollment, Course.course_id == Enrollment.course_id)\
        .group_by(Course.course_id, Course.course_code, Course.name)\
        .all()
    finally:
        session.close()
```

---

## 8. Data Validation and Constraints

### Model-Level Validation

```python
from sqlalchemy.orm import validates
from sqlalchemy import CheckConstraint

class Student(Base):
    __tablename__ = 'students'
    
    student_id = Column(Integer, primary_key=True)
    first_name = Column(String(50), nullable=False)
    last_name = Column(String(50), nullable=False)
    email = Column(String(100), unique=True, nullable=False)
    gpa = Column(Float)
    
    __table_args__ = (
        CheckConstraint('gpa >= 0 AND gpa <= 4.0', name='check_gpa_range'),
    )
    
    @validates('email')
    def validate_email(self, key, email):
        import re
        pattern = r'^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}$'
        if not re.match(pattern, email):
            raise ValueError("Invalid email format")
        return email.lower()
    
    @validates('gpa')
    def validate_gpa(self, key, gpa):
        if gpa is not None and (gpa < 0 or gpa > 4.0):
            raise ValueError("GPA must be between 0.0 and 4.0")
        return gpa
```

### Custom Validation Functions

```python
def validate_student_data(data):
    """Validate student data before creation"""
    errors = []
    
    # Check required fields
    if not data.get('first_name'):
        errors.append("First name is required")
    if not data.get('last_name'):
        errors.append("Last name is required")
    if not data.get('email'):
        errors.append("Email is required")
    if not data.get('department_id'):
        errors.append("Department ID is required")
    
    # Check email format
    if data.get('email'):
        import re
        pattern = r'^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}$'
        if not re.match(pattern, data['email']):
            errors.append("Invalid email format")
    
    # Check GPA range
    if data.get('gpa') is not None:
        gpa = data['gpa']
        if not isinstance(gpa, (int, float)) or gpa < 0 or gpa > 4.0:
            errors.append("GPA must be between 0.0 and 4.0")
    
    return errors

def create_student_with_validation(data):
    """Create student with validation"""
    errors = validate_student_data(data)
    if errors:
        raise ValueError(f"Validation errors: {', '.join(errors)}")
    
    session = SessionLocal()
    try:
        student = Student(**data)
        session.add(student)
        session.commit()
        session.refresh(student)
        return student
    except Exception as e:
        session.rollback()
        raise e
    finally:
        session.close()
```

---

## 9. Best Practices

### Model Design Best Practices

```python
# 1. Use descriptive table and column names
class Student(Base):
    __tablename__ = 'students'  # Clear, plural table name
    
    student_id = Column(Integer, primary_key=True)  # Clear column names
    first_name = Column(String(50), nullable=False)
    
    # 2. Use appropriate data types
    enrollment_date = Column(Date)  # Use Date for dates
    gpa = Column(Float)  # Use Float for decimals
    
    # 3. Add proper constraints
    __table_args__ = (
        CheckConstraint('gpa >= 0 AND gpa <= 4.0', name='check_gpa_range'),
    )
    
    # 4. Use relationships properly
    department = relationship("Department", back_populates="students")
    
    # 5. Add useful methods
    @property
    def full_name(self):
        return f"{self.first_name} {self.last_name}"
    
    def __repr__(self):
        return f"<Student(id={self.student_id}, name='{self.full_name}')>"
```

### Session Management Best Practices

```python
# 1. Always close sessions
def get_student_safe(student_id):
    session = SessionLocal()
    try:
        return session.query(Student).filter(Student.student_id == student_id).first()
    finally:
        session.close()

# 2. Use context managers
@contextmanager
def get_session():
    session = SessionLocal()
    try:
        yield session
        session.commit()
    except Exception:
        session.rollback()
        raise
    finally:
        session.close()

# 3. Handle exceptions properly
def create_student_robust(data):
    with get_session() as session:
        try:
            student = Student(**data)
            session.add(student)
            session.flush()  # Get ID without committing
            return student
        except Exception as e:
            session.rollback()
            raise ValueError(f"Failed to create student: {str(e)}")
```

### Query Optimization Best Practices

```python
# 1. Use appropriate loading strategies
def get_department_with_students_optimized(department_id):
    session = SessionLocal()
    try:
        return session.query(Department)\
            .options(joinedload(Department.students))\
            .filter(Department.department_id == department_id)\
            .first()
    finally:
        session.close()

# 2. Use bulk operations for large datasets
def bulk_create_students(student_data_list):
    session = SessionLocal()
    try:
        students = [Student(**data) for data in student_data_list]
        session.bulk_save_objects(students)
        session.commit()
        return len(students)
    except Exception as e:
        session.rollback()
        raise e
    finally:
        session.close()

# 3. Use select_related for foreign keys
def get_students_with_department():
    session = SessionLocal()
    try:
        return session.query(Student)\
            .join(Department)\
            .filter(Student.status == 'Active')\
            .all()
    finally:
        session.close()
```

---

## 🎯 Summary

SQLAlchemy ORM provides a powerful and Pythonic way to interact with databases:

### Key Concepts
- **Models**: Python classes representing database tables
- **Relationships**: Automatic handling of foreign keys and associations
- **Sessions**: Transaction management and object lifecycle
- **Queries**: High-level query interface with relationship support
- **Validation**: Built-in and custom data validation

### Benefits
- **Type Safety**: Leverage Python's type system
- **Maintainability**: Clean, readable code
- **Database Agnostic**: Work with multiple database engines
- **Relationship Management**: Automatic handling of associations
- **Migration Support**: Schema versioning capabilities

### Best Practices
1. **Design models thoughtfully** with proper relationships
2. **Manage sessions carefully** to avoid connection leaks
3. **Use appropriate loading strategies** for performance
4. **Validate data** at both model and application levels
5. **Handle exceptions properly** for robust applications

## 🔄 Next Steps

- Practice creating models for your database schema
- Experiment with different relationship types
- Move on to Lesson 17: Advanced SQLAlchemy
- Build a complete application using SQLAlchemy ORM

## 📚 Additional Resources

- SQLAlchemy Documentation: [ORM Tutorial](https://docs.sqlalchemy.org/en/14/orm/tutorial.html)
- SQLAlchemy Documentation: [Relationship Configuration](https://docs.sqlalchemy.org/en/14/orm/relationship_api.html)
- SQLAlchemy Documentation: [Session Management](https://docs.sqlalchemy.org/en/14/orm/session.html)

