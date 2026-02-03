# Lesson 17: Advanced SQLAlchemy

## 📚 Learning Objectives

By the end of this lesson, you will be able to:
- Use advanced SQLAlchemy features and patterns
- Implement complex relationships and inheritance
- Work with hybrid properties and methods
- Use SQLAlchemy events and hooks
- Implement database migrations with Alembic
- Optimize performance with advanced techniques
- Handle complex queries and subqueries

## 🎯 Prerequisites

- Completed Lessons 1-16
- Strong understanding of SQLAlchemy ORM basics
- Knowledge of Python decorators and metaclasses
- Understanding of database design patterns

## 📖 Table of Contents

1. [Advanced Relationships](#advanced-relationships)
2. [Hybrid Properties and Methods](#hybrid-properties-and-methods)
3. [SQLAlchemy Events](#sqlalchemy-events)
4. [Database Migrations with Alembic](#database-migrations-with-alembic)
5. [Advanced Querying Techniques](#advanced-querying-techniques)
6. [Performance Optimization](#performance-optimization)
7. [Custom Types and Serializers](#custom-types-and-serializers)
8. [Advanced Patterns](#advanced-patterns)
9. [Best Practices](#best-practices)

---

## 1. Advanced Relationships

### Self-Referential Relationships

```python
from sqlalchemy import Column, Integer, String, ForeignKey, Table
from sqlalchemy.orm import relationship

class Category(Base):
    __tablename__ = 'categories'
    
    category_id = Column(Integer, primary_key=True)
    name = Column(String(100), nullable=False)
    parent_id = Column(Integer, ForeignKey('categories.category_id'))
    
    # Self-referential relationship
    children = relationship("Category", backref="parent", remote_side=[category_id])
    
    def __repr__(self):
        return f"<Category(id={self.category_id}, name='{self.name}')>"

# Example usage
def create_category_hierarchy():
    with get_session() as session:
        # Create parent categories
        programming = Category(name="Programming")
        database = Category(name="Database")
        
        session.add_all([programming, database])
        session.flush()
        
        # Create child categories
        python = Category(name="Python", parent_id=programming.category_id)
        sql = Category(name="SQL", parent_id=database.category_id)
        
        session.add_all([python, sql])
        session.commit()
```

### Many-to-Many with Additional Columns

```python
# Association table with additional columns
student_course_association = Table(
    'student_course_details',
    Base.metadata,
    Column('student_id', Integer, ForeignKey('students.student_id'), primary_key=True),
    Column('course_id', Integer, ForeignKey('courses.course_id'), primary_key=True),
    Column('enrollment_date', Date, nullable=False),
    Column('completion_date', Date),
    Column('final_grade', Integer),
    Column('notes', String(500))
)

class Student(Base):
    __tablename__ = 'students'
    
    student_id = Column(Integer, primary_key=True)
    first_name = Column(String(50), nullable=False)
    last_name = Column(String(50), nullable=False)
    
    # Many-to-many with additional columns
    courses = relationship("Course", secondary=student_course_association, back_populates="students")

class Course(Base):
    __tablename__ = 'courses'
    
    course_id = Column(Integer, primary_key=True)
    course_code = Column(String(10), nullable=False)
    
    students = relationship("Student", secondary=student_course_association, back_populates="courses")

# Working with association objects
def enroll_student_in_course(student_id, course_id, notes=None):
    with get_session() as session:
        # Insert into association table with additional data
        session.execute(
            student_course_association.insert().values(
                student_id=student_id,
                course_id=course_id,
                enrollment_date=date.today(),
                notes=notes
            )
        )
        session.commit()
```

### Polymorphic Associations

```python
from sqlalchemy import Column, Integer, String, ForeignKey, Text, DateTime, func
from sqlalchemy.ext.declarative import declared_attr
from sqlalchemy.orm import with_polymorphic

class CommentableMixin:
    @declared_attr
    def comments(cls):
        return relationship("Comment", back_populates="commentable")

class Comment(Base):
    __tablename__ = 'comments'
    
    comment_id = Column(Integer, primary_key=True)
    content = Column(Text, nullable=False)
    created_at = Column(DateTime, default=func.now())
    
    # Polymorphic foreign key
    commentable_type = Column(String(50), nullable=False)
    commentable_id = Column(Integer, nullable=False)
    
    @property
    def commentable(self):
        if self.commentable_type == 'Student':
            return get_session().query(Student).filter(Student.student_id == self.commentable_id).first()
        elif self.commentable_type == 'Course':
            return get_session().query(Course).filter(Course.course_id == self.commentable_id).first()
        return None

class Student(Base, CommentableMixin):
    __tablename__ = 'students'
    
    student_id = Column(Integer, primary_key=True)
    first_name = Column(String(50), nullable=False)
    
    # Comments relationship
    comments = relationship("Comment", 
                          primaryjoin="and_(Student.student_id == Comment.commentable_id, Comment.commentable_type == 'Student')",
                          back_populates="commentable")

class Course(Base, CommentableMixin):
    __tablename__ = 'courses'
    
    course_id = Column(Integer, primary_key=True)
    course_code = Column(String(10), nullable=False)
    
    comments = relationship("Comment",
                          primaryjoin="and_(Course.course_id == Comment.commentable_id, Comment.commentable_type == 'Course')",
                          back_populates="commentable")
```

---

## 2. Hybrid Properties and Methods

### Hybrid Properties

```python
from sqlalchemy.ext.hybrid import hybrid_property, hybrid_method
from sqlalchemy import case, func

class Student(Base):
    __tablename__ = 'students'
    
    student_id = Column(Integer, primary_key=True)
    first_name = Column(String(50), nullable=False)
    last_name = Column(String(50), nullable=False)
    gpa = Column(Float)
    
    @hybrid_property
    def full_name(self):
        return f"{self.first_name} {self.last_name}"
    
    @full_name.expression
    def full_name(cls):
        return func.concat(cls.first_name, ' ', cls.last_name)
    
    @hybrid_property
    def academic_status(self):
        if self.gpa is None:
            return "Unknown"
        elif self.gpa >= 3.5:
            return "Honor Roll"
        elif self.gpa >= 3.0:
            return "Good Standing"
        elif self.gpa >= 2.0:
            return "Satisfactory"
        else:
            return "Academic Probation"
    
    @academic_status.expression
    def academic_status(cls):
        return case(
            [
                (cls.gpa >= 3.5, "Honor Roll"),
                (cls.gpa >= 3.0, "Good Standing"),
                (cls.gpa >= 2.0, "Satisfactory"),
                (cls.gpa.isnot(None), "Academic Probation")
            ],
            else_="Unknown"
        )
    
    @hybrid_method
    def has_gpa_above(self, threshold):
        return self.gpa is not None and self.gpa >= threshold
    
    @has_gpa_above.expression
    def has_gpa_above(cls, threshold):
        return and_(cls.gpa.isnot(None), cls.gpa >= threshold)

# Usage examples
def get_honor_roll_students():
    session = SessionLocal()
    try:
        return session.query(Student)\
            .filter(Student.academic_status == "Honor Roll")\
            .all()
    finally:
        session.close()

def get_students_above_threshold(threshold):
    session = SessionLocal()
    try:
        return session.query(Student)\
            .filter(Student.has_gpa_above(threshold))\
            .all()
    finally:
        session.close()
```

### Hybrid Methods with Complex Logic

```python
class Enrollment(Base):
    __tablename__ = 'enrollments'
    
    enrollment_id = Column(Integer, primary_key=True)
    student_id = Column(Integer, ForeignKey('students.student_id'))
    course_id = Column(Integer, ForeignKey('courses.course_id'))
    grade = Column(Integer)
    semester = Column(String(20))
    
    student = relationship("Student")
    course = relationship("Course")
    
    @hybrid_method
    def is_passing(self, passing_grade=70):
        return self.grade is not None and self.grade >= passing_grade
    
    @is_passing.expression
    def is_passing(cls, passing_grade=70):
        return and_(cls.grade.isnot(None), cls.grade >= passing_grade)
    
    @hybrid_property
    def letter_grade(self):
        if self.grade is None:
            return None
        elif self.grade >= 90:
            return "A"
        elif self.grade >= 80:
            return "B"
        elif self.grade >= 70:
            return "C"
        elif self.grade >= 60:
            return "D"
        else:
            return "F"
    
    @letter_grade.expression
    def letter_grade(cls):
        return case(
            [
                (cls.grade >= 90, "A"),
                (cls.grade >= 80, "B"),
                (cls.grade >= 70, "C"),
                (cls.grade >= 60, "D"),
                (cls.grade.isnot(None), "F")
            ],
            else_=None
        )
```

---

## 3. SQLAlchemy Events

### Model Events

```python
from sqlalchemy import event
from datetime import datetime

class AuditMixin:
    created_at = Column(DateTime, default=datetime.utcnow)
    updated_at = Column(DateTime, default=datetime.utcnow, onupdate=datetime.utcnow)
    created_by = Column(String(100))
    updated_by = Column(String(100))

class Student(Base, AuditMixin):
    __tablename__ = 'students'
    
    student_id = Column(Integer, primary_key=True)
    first_name = Column(String(50), nullable=False)
    last_name = Column(String(50), nullable=False)
    email = Column(String(100), unique=True)

# Event listeners
@event.listens_for(Student, 'before_insert')
def receive_before_insert(mapper, connection, target):
    """Called before a Student is inserted"""
    target.created_by = get_current_user()
    target.updated_by = get_current_user()

@event.listens_for(Student, 'before_update')
def receive_before_update(mapper, connection, target):
    """Called before a Student is updated"""
    target.updated_by = get_current_user()

@event.listens_for(Student, 'after_insert')
def receive_after_insert(mapper, connection, target):
    """Called after a Student is inserted"""
    log_activity(f"Student {target.full_name} was created")

@event.listens_for(Student, 'after_update')
def receive_after_update(mapper, connection, target):
    """Called after a Student is updated"""
    log_activity(f"Student {target.full_name} was updated")

def get_current_user():
    """Get current user from context (simplified)"""
    return "system"

def log_activity(message):
    """Log activity (simplified)"""
    print(f"[LOG] {message}")
```

### Session Events

```python
from sqlalchemy.orm import Session

@event.listens_for(Session, 'before_bulk_update')
def receive_before_bulk_update(update_context):
    """Called before bulk update operations"""
    print("Bulk update operation starting...")

@event.listens_for(Session, 'after_bulk_update')
def receive_after_bulk_update(update_context):
    """Called after bulk update operations"""
    print("Bulk update operation completed")

# Connection events
@event.listens_for(engine, 'connect')
def receive_connect(dbapi_connection, connection_record):
    """Called when a connection is established"""
    print("Database connection established")

@event.listens_for(engine, 'checkout')
def receive_checkout(dbapi_connection, connection_record, connection_proxy):
    """Called when a connection is checked out from the pool"""
    print("Connection checked out from pool")
```

---

## 4. Database Migrations with Alembic

### Setting Up Alembic

```python
# Install Alembic
# pip install alembic

# Initialize Alembic in your project
# alembic init alembic

# alembic/env.py configuration
from sqlalchemy import engine_from_config
from sqlalchemy import pool
from alembic import context
from your_app.models import Base  # Import your models

# this is the Alembic Config object
config = context.config

# Interpret the config file for Python logging
if config.config_file_name is not None:
    fileConfig(config.config_file_name)

# add your model's MetaData object here for 'autogenerate' support
target_metadata = Base.metadata

def run_migrations_offline():
    """Run migrations in 'offline' mode."""
    url = config.get_main_option("sqlalchemy.url")
    context.configure(
        url=url,
        target_metadata=target_metadata,
        literal_binds=True,
        dialect_opts={"paramstyle": "named"},
    )

    with context.begin_transaction():
        context.run_migrations()

def run_migrations_online():
    """Run migrations in 'online' mode."""
    connectable = engine_from_config(
        config.get_section(config.config_ini_section),
        prefix="sqlalchemy.",
        poolclass=pool.NullPool,
    )

    with connectable.connect() as connection:
        context.configure(
            connection=connection, target_metadata=target_metadata
        )

        with context.begin_transaction():
            context.run_migrations()

if context.is_offline_mode():
    run_migrations_offline()
else:
    run_migrations_online()
```

### Creating and Running Migrations

```bash
# Create a new migration
alembic revision --autogenerate -m "Add student table"

# Apply migrations
alembic upgrade head

# Rollback migrations
alembic downgrade -1

# Show migration history
alembic history

# Show current revision
alembic current
```

### Custom Migration Operations

```python
# Custom migration example
from alembic import op
import sqlalchemy as sa

def upgrade():
    # Create new table
    op.create_table(
        'student_achievements',
        sa.Column('achievement_id', sa.Integer(), nullable=False),
        sa.Column('student_id', sa.Integer(), nullable=False),
        sa.Column('achievement_type', sa.String(50), nullable=False),
        sa.Column('description', sa.String(500), nullable=True),
        sa.Column('earned_date', sa.Date(), nullable=False),
        sa.PrimaryKeyConstraint('achievement_id'),
        sa.ForeignKeyConstraint(['student_id'], ['students.student_id'])
    )
    
    # Add new column to existing table
    op.add_column('students', sa.Column('graduation_date', sa.Date(), nullable=True))
    
    # Create index
    op.create_index('idx_student_achievements_student', 'student_achievements', ['student_id'])

def downgrade():
    # Drop index
    op.drop_index('idx_student_achievements_student', table_name='student_achievements')
    
    # Drop column
    op.drop_column('students', 'graduation_date')
    
    # Drop table
    op.drop_table('student_achievements')
```

---

## 5. Advanced Querying Techniques

### Window Functions

```python
from sqlalchemy import func, over

def get_student_rankings():
    """Get student rankings within their departments"""
    session = SessionLocal()
    try:
        return session.query(
            Student.student_id,
            Student.first_name,
            Student.last_name,
            Department.name.label('department_name'),
            Student.gpa,
            func.rank().over(
                partition_by=Student.department_id,
                order_by=Student.gpa.desc()
            ).label('department_rank'),
            func.rank().over(order_by=Student.gpa.desc()).label('overall_rank')
        )\
        .join(Department)\
        .filter(Student.gpa.isnot(None))\
        .all()
    finally:
        session.close()

def get_course_statistics():
    """Get course statistics with window functions"""
    session = SessionLocal()
    try:
        return session.query(
            Course.course_code,
            Course.name,
            func.count(Enrollment.enrollment_id).label('enrollment_count'),
            func.avg(Enrollment.grade).label('average_grade'),
            func.stddev(Enrollment.grade).label('grade_stddev'),
            func.avg(func.avg(Enrollment.grade)).over().label('overall_average')
        )\
        .outerjoin(Enrollment)\
        .group_by(Course.course_id, Course.course_code, Course.name)\
        .all()
    finally:
        session.close()
```

### Common Table Expressions (CTEs)

```python
def get_student_academic_progress():
    """Get student academic progress using CTEs"""
    session = SessionLocal()
    try:
        # Define CTEs
        student_stats = session.query(
            Enrollment.student_id,
            func.count(Enrollment.enrollment_id).label('total_courses'),
            func.avg(Enrollment.grade).label('average_grade'),
            func.count(case([(Enrollment.grade >= 85, 1)], else_=None)).label('passing_courses')
        )\
        .filter(Enrollment.grade.isnot(None))\
        .group_by(Enrollment.student_id)\
        .cte('student_stats')
        
        # Main query using CTE
        return session.query(
            Student.student_id,
            Student.first_name,
            Student.last_name,
            Student.gpa,
            student_stats.c.total_courses,
            student_stats.c.average_grade,
            student_stats.c.passing_courses,
            (student_stats.c.passing_courses / student_stats.c.total_courses * 100).label('pass_rate')
        )\
        .join(student_stats, Student.student_id == student_stats.c.student_id)\
        .all()
    finally:
        session.close()
```

### Complex Subqueries

```python
def get_departments_with_top_students():
    """Get departments that have students in top 10%"""
    session = SessionLocal()
    try:
        # Subquery for top 10% GPA threshold
        top_gpa_threshold = session.query(
            func.percentile_cont(0.9).within_group(Student.gpa.desc())
        ).filter(Student.gpa.isnot(None)).scalar_subquery()
        
        # Main query
        return session.query(
            Department.name,
            func.count(Student.student_id).label('total_students'),
            func.count(
                case([(Student.gpa >= top_gpa_threshold, 1)], else_=None)
            ).label('top_students'),
            func.avg(Student.gpa).label('average_gpa')
        )\
        .join(Student)\
        .filter(Student.gpa.isnot(None))\
        .group_by(Department.department_id, Department.name)\
        .having(func.count(Student.student_id) > 0)\
        .all()
    finally:
        session.close()
```

---

## 6. Performance Optimization

### Connection Pooling

```python
from sqlalchemy.pool import QueuePool

# Configure connection pooling
engine = create_engine(
    f'mysql+pymysql://{DB_USER}:{DB_PASSWORD}@{DB_HOST}/{DB_NAME}',
    poolclass=QueuePool,
    pool_size=20,          # Number of connections to maintain
    max_overflow=30,       # Additional connections beyond pool_size
    pool_pre_ping=True,    # Validate connections before use
    pool_recycle=3600      # Recycle connections after 1 hour
)

# Connection pool monitoring
def get_pool_status():
    pool = engine.pool
    return {
        'size': pool.size(),
        'checked_in': pool.checkedin(),
        'checked_out': pool.checkedout(),
        'overflow': pool.overflow(),
        'invalid': pool.invalid()
    }
```

### Query Optimization

```python
# Eager loading strategies
def get_students_with_relationships():
    session = SessionLocal()
    try:
        return session.query(Student)\
            .options(
                joinedload(Student.department),
                selectinload(Student.enrollments).joinedload(Enrollment.course)
            )\
            .filter(Student.status == 'Active')\
            .all()
    finally:
        session.close()

# Bulk operations
def bulk_insert_students(student_data_list):
    """Bulk insert students for better performance"""
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

# Bulk updates
def bulk_update_student_status(student_ids, new_status):
    """Bulk update student status"""
    session = SessionLocal()
    try:
        updated_count = session.query(Student)\
            .filter(Student.student_id.in_(student_ids))\
            .update({Student.status: new_status}, synchronize_session=False)
        session.commit()
        return updated_count
    except Exception as e:
        session.rollback()
        raise e
    finally:
        session.close()
```

### Caching Strategies

```python
from functools import lru_cache
from sqlalchemy.orm import Query

class CachedQuery:
    def __init__(self, session):
        self.session = session
    
    @lru_cache(maxsize=100)
    def get_department_by_id(self, department_id):
        """Cache department lookups"""
        return self.session.query(Department)\
            .filter(Department.department_id == department_id)\
            .first()
    
    @lru_cache(maxsize=50)
    def get_course_by_code(self, course_code):
        """Cache course lookups"""
        return self.session.query(Course)\
            .filter(Course.course_code == course_code)\
            .first()

# Usage
def get_student_with_cached_data(student_id):
    session = SessionLocal()
    try:
        cached_query = CachedQuery(session)
        student = session.query(Student).filter(Student.student_id == student_id).first()
        
        if student:
            # Use cached department lookup
            department = cached_query.get_department_by_id(student.department_id)
            student.department = department
        
        return student
    finally:
        session.close()
```

---

## 7. Custom Types and Serializers

### Custom Column Types

```python
from sqlalchemy import TypeDecorator, String
import json

class JSONType(TypeDecorator):
    """Custom JSON type for storing JSON data"""
    impl = String
    cache_ok = True
    
    def process_bind_param(self, value, dialect):
        if value is not None:
            return json.dumps(value)
        return value
    
    def process_result_value(self, value, dialect):
        if value is not None:
            return json.loads(value)
        return value

class Student(Base):
    __tablename__ = 'students'
    
    student_id = Column(Integer, primary_key=True)
    first_name = Column(String(50), nullable=False)
    last_name = Column(String(50), nullable=False)
    
    # Custom JSON type for storing additional data
    metadata = Column(JSONType)
    
    def set_metadata(self, key, value):
        """Helper method to set metadata"""
        if self.metadata is None:
            self.metadata = {}
        self.metadata[key] = value
    
    def get_metadata(self, key, default=None):
        """Helper method to get metadata"""
        if self.metadata is None:
            return default
        return self.metadata.get(key, default)
```

### Custom Serializers

```python
from marshmallow import Schema, fields
from marshmallow_sqlalchemy import SQLAlchemyAutoSchema

class StudentSchema(SQLAlchemyAutoSchema):
    class Meta:
        model = Student
        load_instance = True
    
    full_name = fields.Method("get_full_name")
    academic_status = fields.Method("get_academic_status")
    
    def get_full_name(self, obj):
        return obj.full_name
    
    def get_academic_status(self, obj):
        return obj.academic_status

class DepartmentSchema(SQLAlchemyAutoSchema):
    class Meta:
        model = Department
        load_instance = True
    
    student_count = fields.Method("get_student_count")
    
    def get_student_count(self, obj):
        return len(obj.students)

# Usage
def serialize_student(student):
    """Serialize student to JSON"""
    schema = StudentSchema()
    return schema.dump(student)

def serialize_students(students):
    """Serialize multiple students to JSON"""
    schema = StudentSchema(many=True)
    return schema.dump(students)
```

---

## 8. Advanced Patterns

### Repository Pattern

```python
from abc import ABC, abstractmethod
from typing import List, Optional, TypeVar, Generic

T = TypeVar('T')

class Repository(ABC, Generic[T]):
    def __init__(self, session):
        self.session = session
    
    @abstractmethod
    def get_by_id(self, id: int) -> Optional[T]:
        pass
    
    @abstractmethod
    def get_all(self) -> List[T]:
        pass
    
    @abstractmethod
    def create(self, entity: T) -> T:
        pass
    
    @abstractmethod
    def update(self, entity: T) -> T:
        pass
    
    @abstractmethod
    def delete(self, id: int) -> bool:
        pass

class StudentRepository(Repository[Student]):
    def get_by_id(self, student_id: int) -> Optional[Student]:
        return self.session.query(Student).filter(Student.student_id == student_id).first()
    
    def get_all(self) -> List[Student]:
        return self.session.query(Student).all()
    
    def get_by_department(self, department_id: int) -> List[Student]:
        return self.session.query(Student)\
            .filter(Student.department_id == department_id)\
            .all()
    
    def get_by_gpa_range(self, min_gpa: float, max_gpa: float) -> List[Student]:
        return self.session.query(Student)\
            .filter(Student.gpa.between(min_gpa, max_gpa))\
            .all()
    
    def create(self, student: Student) -> Student:
        self.session.add(student)
        self.session.commit()
        self.session.refresh(student)
        return student
    
    def update(self, student: Student) -> Student:
        self.session.commit()
        self.session.refresh(student)
        return student
    
    def delete(self, student_id: int) -> bool:
        student = self.get_by_id(student_id)
        if student:
            self.session.delete(student)
            self.session.commit()
            return True
        return False

# Usage
def get_honor_roll_students():
    with get_session() as session:
        repo = StudentRepository(session)
        return repo.get_by_gpa_range(3.5, 4.0)
```

### Unit of Work Pattern

```python
class UnitOfWork:
    def __init__(self):
        self.session = SessionLocal()
        self.students = StudentRepository(self.session)
        self.courses = CourseRepository(self.session)
        self.departments = DepartmentRepository(self.session)
    
    def __enter__(self):
        return self
    
    def __exit__(self, exc_type, exc_val, exc_tb):
        if exc_type is not None:
            self.session.rollback()
        else:
            self.session.commit()
        self.session.close()
    
    def commit(self):
        self.session.commit()
    
    def rollback(self):
        self.session.rollback()

# Usage
def transfer_student_to_department(student_id: int, new_department_id: int):
    with UnitOfWork() as uow:
        student = uow.students.get_by_id(student_id)
        if not student:
            raise ValueError("Student not found")
        
        department = uow.departments.get_by_id(new_department_id)
        if not department:
            raise ValueError("Department not found")
        
        student.department_id = new_department_id
        uow.students.update(student)
        
        # Additional operations...
        # uow.commit() - automatically called on exit
```

---

## 9. Best Practices

### Code Organization

```python
# models/__init__.py
from .student import Student
from .course import Course
from .department import Department
from .enrollment import Enrollment

__all__ = ['Student', 'Course', 'Department', 'Enrollment']

# repositories/__init__.py
from .student_repository import StudentRepository
from .course_repository import CourseRepository

__all__ = ['StudentRepository', 'CourseRepository']

# services/student_service.py
class StudentService:
    def __init__(self, session):
        self.session = session
        self.repository = StudentRepository(session)
    
    def create_student(self, data):
        # Business logic validation
        if not data.get('email'):
            raise ValueError("Email is required")
        
        # Create student
        student = Student(**data)
        return self.repository.create(student)
    
    def get_student_statistics(self, department_id=None):
        query = self.session.query(Student)
        
        if department_id:
            query = query.filter(Student.department_id == department_id)
        
        return {
            'total_count': query.count(),
            'average_gpa': query.filter(Student.gpa.isnot(None)).with_entities(func.avg(Student.gpa)).scalar(),
            'honor_roll_count': query.filter(Student.gpa >= 3.5).count()
        }
```

### Error Handling and Logging

```python
import logging
from sqlalchemy.exc import IntegrityError, SQLAlchemyError

logger = logging.getLogger(__name__)

class DatabaseService:
    def __init__(self, session):
        self.session = session
    
    def safe_create(self, entity, entity_type="entity"):
        """Safely create an entity with proper error handling"""
        try:
            self.session.add(entity)
            self.session.commit()
            self.session.refresh(entity)
            logger.info(f"Successfully created {entity_type}: {entity}")
            return entity
        except IntegrityError as e:
            self.session.rollback()
            logger.error(f"Integrity error creating {entity_type}: {e}")
            raise ValueError(f"Data integrity violation: {e}")
        except SQLAlchemyError as e:
            self.session.rollback()
            logger.error(f"Database error creating {entity_type}: {e}")
            raise RuntimeError(f"Database operation failed: {e}")
        except Exception as e:
            self.session.rollback()
            logger.error(f"Unexpected error creating {entity_type}: {e}")
            raise
    
    def safe_bulk_operation(self, operation_func, *args, **kwargs):
        """Safely execute bulk operations"""
        try:
            result = operation_func(*args, **kwargs)
            self.session.commit()
            logger.info(f"Bulk operation completed successfully")
            return result
        except SQLAlchemyError as e:
            self.session.rollback()
            logger.error(f"Bulk operation failed: {e}")
            raise RuntimeError(f"Bulk operation failed: {e}")
```

### Testing with SQLAlchemy

```python
import pytest
from sqlalchemy import create_engine
from sqlalchemy.orm import sessionmaker
from sqlalchemy.pool import StaticPool

# Test database setup
@pytest.fixture(scope="function")
def test_db():
    # Create in-memory SQLite database for testing
    engine = create_engine(
        "sqlite:///:memory:",
        connect_args={"check_same_thread": False},
        poolclass=StaticPool,
    )
    
    Base.metadata.create_all(engine)
    TestingSessionLocal = sessionmaker(autocommit=False, autoflush=False, bind=engine)
    
    session = TestingSessionLocal()
    yield session
    session.close()

@pytest.fixture
def student_repository(test_db):
    return StudentRepository(test_db)

def test_create_student(student_repository):
    """Test creating a student"""
    student_data = {
        'first_name': 'John',
        'last_name': 'Doe',
        'email': 'john.doe@test.com',
        'department_id': 1
    }
    
    student = Student(**student_data)
    created_student = student_repository.create(student)
    
    assert created_student.student_id is not None
    assert created_student.first_name == 'John'
    assert created_student.email == 'john.doe@test.com'

def test_get_students_by_department(student_repository, test_db):
    """Test getting students by department"""
    # Create test data
    dept = Department(name="Test Department")
    test_db.add(dept)
    test_db.flush()
    
    student1 = Student(first_name="John", last_name="Doe", email="john@test.com", department_id=dept.department_id)
    student2 = Student(first_name="Jane", last_name="Smith", email="jane@test.com", department_id=dept.department_id)
    
    student_repository.create(student1)
    student_repository.create(student2)
    
    # Test query
    students = student_repository.get_by_department(dept.department_id)
    assert len(students) == 2
    assert all(s.department_id == dept.department_id for s in students)
```

---

## 🎯 Summary

Advanced SQLAlchemy techniques provide powerful tools for building robust, scalable applications:

### Key Advanced Features
- **Complex Relationships**: Self-referential, polymorphic, and many-to-many with additional columns
- **Hybrid Properties**: Python properties that work in both Python and SQL contexts
- **Events and Hooks**: Automatic behavior on database operations
- **Migrations**: Database schema versioning with Alembic
- **Advanced Queries**: Window functions, CTEs, and complex subqueries
- **Performance Optimization**: Connection pooling, caching, and bulk operations

### Advanced Patterns
- **Repository Pattern**: Abstract data access layer
- **Unit of Work**: Transaction management pattern
- **Custom Types**: Specialized column types for complex data
- **Service Layer**: Business logic separation

### Best Practices
1. **Organize code** into logical modules and layers
2. **Handle errors** gracefully with proper logging
3. **Test thoroughly** with isolated test databases
4. **Optimize performance** with appropriate strategies
5. **Use migrations** for schema changes
6. **Implement patterns** for maintainable code

## 🔄 Next Steps

- Practice implementing advanced SQLAlchemy patterns
- Set up Alembic for database migrations
- Build a complete application with all advanced features
- Explore SQLAlchemy's extensive ecosystem and extensions

## 📚 Additional Resources

- SQLAlchemy Documentation: [Advanced Usage](https://docs.sqlalchemy.org/en/14/orm/advanced.html)
- SQLAlchemy Documentation: [Hybrid Attributes](https://docs.sqlalchemy.org/en/14/orm/extensions/hybrid.html)
- Alembic Documentation: [Migration Tutorial](https://alembic.sqlalchemy.org/en/latest/tutorial.html)
- SQLAlchemy Documentation: [Events](https://docs.sqlalchemy.org/en/14/core/events.html)

