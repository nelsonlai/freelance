# Relational Database Learning Course

## Course Overview

This comprehensive course teaches relational database concepts using MySQL and Python SQLAlchemy. Students will learn SQL from beginner to advanced levels, with practical examples and hands-on exercises.

## Prerequisites

- Basic understanding of programming concepts
- Python 3.7+ installed
- MySQL Server installed locally
- Basic command line knowledge

## Course Structure

### Module 1: Database Fundamentals
- [Lesson 1: Database Setup and Connection](lessons/01_database_setup.md)
- [Lesson 2: Creating Databases and Tables](lessons/02_create_database_tables.md)
- [Lesson 3: Data Types and Constraints](lessons/03_data_types_constraints.md)

### Module 2: Basic SQL Operations
- [Lesson 4: Inserting Data](lessons/04_insert_data.md)
- [Lesson 5: Querying Data (SELECT)](lessons/05_select_queries.md)
- [Lesson 6: Updating and Deleting Data](lessons/06_update_delete.md)

### Module 3: Intermediate SQL
- [Lesson 7: Joins and Relationships](lessons/07_joins.md)
- [Lesson 8: Aggregation Functions](lessons/08_aggregation.md)
- [Lesson 9: Subqueries](lessons/09_subqueries.md)

### Module 4: Advanced SQL
- [Lesson 10: Views and Indexes](lessons/10_views_indexes.md)
- [Lesson 11: Stored Procedures and Functions](lessons/11_stored_procedures.md)
- [Lesson 12: Triggers](lessons/12_triggers.md)
- [Lesson 13: Performance Optimization](lessons/13_optimization.md)

### Module 5: Python SQLAlchemy Integration
- [Lesson 14: SQLAlchemy ORM Basics](lessons/14_sqlalchemy_orm.md)
- [Lesson 15: Advanced SQLAlchemy](lessons/15_advanced_sqlalchemy.md)

## Setup Instructions

1. **Install MySQL Server**
   ```bash
   # macOS (using Homebrew)
   brew install mysql
   brew services start mysql
   
   # Ubuntu/Debian
   sudo apt update
   sudo apt install mysql-server
   
   # Windows - Download from MySQL website
   ```

2. **Install Python Dependencies**
   ```bash
   pip install -r requirements.txt
   ```

3. **Create MySQL User and Database**
   ```sql
   CREATE USER 'student'@'localhost' IDENTIFIED BY 'password123';
   GRANT ALL PRIVILEGES ON *.* TO 'student'@'localhost';
   FLUSH PRIVILEGES;
   ```

## Learning Path

1. Start with Module 1 to understand database fundamentals
2. Progress through each lesson sequentially
3. Complete the exercises at the end of each lesson
4. Practice with the provided sample datasets
5. Use the Python SQLAlchemy examples to understand programmatic database access

## Sample Datasets

- `sample_data/` - Contains sample SQL files and CSV data for practice
- `exercises/` - Practice exercises for each lesson
- `solutions/` - Solutions to exercises

## Getting Help

- Check the troubleshooting guide in each lesson
- Review the common SQL patterns reference
- Practice with the interactive exercises

## Course Completion

Upon completing this course, students will be able to:
- Design and create relational databases
- Write complex SQL queries
- Use Python SQLAlchemy for database operations
- Optimize database performance
- Implement advanced database features

Happy learning! 🎓
