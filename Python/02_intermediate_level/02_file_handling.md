# 2. File Handling - Reading, Writing, and Managing Data

File handling is essential for persistent data storage and retrieval. This lesson covers reading from and writing to files, working with different file formats, and managing file operations safely.

## Basic File Operations

### Reading Files

```python
# Reading a text file
def read_text_file(filename):
    """Read content from a text file."""
    try:
        with open(filename, 'r', encoding='utf-8') as file:
            content = file.read()
        return content
    except FileNotFoundError:
        print(f"File '{filename}' not found")
        return None
    except Exception as e:
        print(f"Error reading file: {e}")
        return None

# Reading line by line
def read_file_lines(filename):
    """Read file content line by line."""
    try:
        with open(filename, 'r', encoding='utf-8') as file:
            lines = file.readlines()  # Returns list of lines
        return lines
    except FileNotFoundError:
        print(f"File '{filename}' not found")
        return None

# Reading with iteration (memory efficient for large files)
def read_file_iteratively(filename):
    """Read large file line by line without loading all into memory."""
    try:
        with open(filename, 'r', encoding='utf-8') as file:
            for line_num, line in enumerate(file, 1):
                print(f"Line {line_num}: {line.strip()}")
                # Process line here
                # For large files, process one line at a time
    except FileNotFoundError:
        print(f"File '{filename}' not found")
    except Exception as e:
        print(f"Error reading file: {e}")

# Example usage
content = read_text_file("example.txt")
if content:
    print(f"File content:\n{content}")
```

### Writing Files

```python
# Writing to a text file
def write_text_file(filename, content):
    """Write content to a text file."""
    try:
        with open(filename, 'w', encoding='utf-8') as file:
            file.write(content)
        print(f"Content written to '{filename}' successfully")
        return True
    except Exception as e:
        print(f"Error writing to file: {e}")
        return False

# Appending to a file
def append_to_file(filename, content):
    """Append content to an existing file."""
    try:
        with open(filename, 'a', encoding='utf-8') as file:
            file.write(content)
        print(f"Content appended to '{filename}' successfully")
        return True
    except Exception as e:
        print(f"Error appending to file: {e}")
        return False

# Writing multiple lines
def write_multiple_lines(filename, lines):
    """Write multiple lines to a file."""
    try:
        with open(filename, 'w', encoding='utf-8') as file:
            for line in lines:
                file.write(line + '\n')
        print(f"Multiple lines written to '{filename}' successfully")
        return True
    except Exception as e:
        print(f"Error writing lines to file: {e}")
        return False

# Example usage
lines = ["Line 1", "Line 2", "Line 3"]
write_multiple_lines("output.txt", lines)
```

### File Modes and Operations

```python
# Different file modes
def demonstrate_file_modes():
    """Demonstrate different file opening modes."""
    
    filename = "demo.txt"
    
    # Write mode ('w') - creates new file or overwrites existing
    with open(filename, 'w') as file:
        file.write("This is written in write mode\n")
    
    # Read mode ('r') - read-only
    with open(filename, 'r') as file:
        content = file.read()
        print(f"Read content: {content}")
    
    # Append mode ('a') - append to end of file
    with open(filename, 'a') as file:
        file.write("This is appended\n")
    
    # Read and write mode ('r+') - read and write
    with open(filename, 'r+') as file:
        content = file.read()
        print(f"Content before write: {content}")
        file.write("This is added with r+ mode\n")
    
    # Binary mode ('rb', 'wb', 'ab')
    # For reading/writing binary data (images, videos, etc.)
    
    # Text mode with encoding
    with open(filename, 'w', encoding='utf-8') as file:
        file.write("UTF-8 encoded text with émojis 🐍\n")

# demonstrate_file_modes()
```

## Working with CSV Files

### Reading CSV Files

```python
import csv

def read_csv_file(filename):
    """Read data from a CSV file."""
    try:
        with open(filename, 'r', newline='', encoding='utf-8') as file:
            reader = csv.reader(file)
            data = list(reader)
        return data
    except FileNotFoundError:
        print(f"CSV file '{filename}' not found")
        return None
    except Exception as e:
        print(f"Error reading CSV file: {e}")
        return None

def read_csv_as_dict(filename):
    """Read CSV file and return as list of dictionaries."""
    try:
        with open(filename, 'r', newline='', encoding='utf-8') as file:
            reader = csv.DictReader(file)
            data = list(reader)
        return data
    except FileNotFoundError:
        print(f"CSV file '{filename}' not found")
        return None
    except Exception as e:
        print(f"Error reading CSV file: {e}")
        return None

# Example CSV data
def create_sample_csv():
    """Create a sample CSV file for demonstration."""
    data = [
        ['Name', 'Age', 'City', 'Salary'],
        ['Alice', '25', 'New York', '50000'],
        ['Bob', '30', 'London', '60000'],
        ['Charlie', '35', 'Paris', '55000']
    ]
    
    with open('employees.csv', 'w', newline='', encoding='utf-8') as file:
        writer = csv.writer(file)
        writer.writerows(data)
    
    print("Sample CSV file created: employees.csv")

# create_sample_csv()

# Read and display CSV data
def display_csv_data(filename):
    """Display CSV data in a formatted way."""
    data = read_csv_as_dict(filename)
    if data:
        print(f"\nData from {filename}:")
        for row in data:
            print(f"Name: {row['Name']}, Age: {row['Age']}, City: {row['City']}, Salary: {row['Salary']}")

# display_csv_data('employees.csv')
```

### Writing CSV Files

```python
def write_csv_file(filename, data, headers=None):
    """Write data to a CSV file."""
    try:
        with open(filename, 'w', newline='', encoding='utf-8') as file:
            writer = csv.writer(file)
            
            # Write headers if provided
            if headers:
                writer.writerow(headers)
            
            # Write data
            writer.writerows(data)
        
        print(f"Data written to '{filename}' successfully")
        return True
    except Exception as e:
        print(f"Error writing CSV file: {e}")
        return False

def write_csv_from_dict(filename, data, fieldnames=None):
    """Write list of dictionaries to CSV file."""
    try:
        if not data:
            print("No data to write")
            return False
        
        # Get fieldnames from first dictionary if not provided
        if not fieldnames:
            fieldnames = data[0].keys()
        
        with open(filename, 'w', newline='', encoding='utf-8') as file:
            writer = csv.DictWriter(file, fieldnames=fieldnames)
            writer.writeheader()
            writer.writerows(data)
        
        print(f"Dictionary data written to '{filename}' successfully")
        return True
    except Exception as e:
        print(f"Error writing CSV file: {e}")
        return False

# Example: Create employee data
def create_employee_csv():
    """Create employee data and save to CSV."""
    employees = [
        {'Name': 'Alice Johnson', 'Age': 28, 'Department': 'IT', 'Salary': 65000},
        {'Name': 'Bob Smith', 'Age': 32, 'Department': 'HR', 'Salary': 55000},
        {'Name': 'Charlie Brown', 'Age': 29, 'Department': 'Finance', 'Salary': 60000},
        {'Name': 'Diana Prince', 'Age': 31, 'Department': 'IT', 'Salary': 70000}
    ]
    
    write_csv_from_dict('employees_detailed.csv', employees)
    return employees

# employees = create_employee_csv()
```

## Working with JSON Files

### Reading JSON Files

```python
import json

def read_json_file(filename):
    """Read data from a JSON file."""
    try:
        with open(filename, 'r', encoding='utf-8') as file:
            data = json.load(file)
        return data
    except FileNotFoundError:
        print(f"JSON file '{filename}' not found")
        return None
    except json.JSONDecodeError as e:
        print(f"Error decoding JSON: {e}")
        return None
    except Exception as e:
        print(f"Error reading JSON file: {e}")
        return None

# Create sample JSON data
def create_sample_json():
    """Create a sample JSON file for demonstration."""
    data = {
        "company": "TechCorp",
        "employees": [
            {
                "id": 1,
                "name": "Alice Johnson",
                "position": "Software Engineer",
                "salary": 75000,
                "skills": ["Python", "JavaScript", "SQL"]
            },
            {
                "id": 2,
                "name": "Bob Smith",
                "position": "Data Scientist",
                "salary": 85000,
                "skills": ["Python", "R", "Machine Learning"]
            },
            {
                "id": 3,
                "name": "Charlie Brown",
                "position": "DevOps Engineer",
                "salary": 80000,
                "skills": ["Docker", "Kubernetes", "AWS"]
            }
        ],
        "departments": {
            "IT": {"budget": 500000, "manager": "Alice Johnson"},
            "Data": {"budget": 300000, "manager": "Bob Smith"},
            "Infrastructure": {"budget": 200000, "manager": "Charlie Brown"}
        }
    }
    
    with open('company_data.json', 'w', encoding='utf-8') as file:
        json.dump(data, file, indent=4, ensure_ascii=False)
    
    print("Sample JSON file created: company_data.json")
    return data

# company_data = create_sample_json()

def display_json_data(filename):
    """Display JSON data in a formatted way."""
    data = read_json_file(filename)
    if data:
        print(f"\nData from {filename}:")
        print(f"Company: {data['company']}")
        print("\nEmployees:")
        for employee in data['employees']:
            print(f"  - {employee['name']} ({employee['position']}) - ${employee['salary']:,}")
            print(f"    Skills: {', '.join(employee['skills'])}")
        
        print("\nDepartments:")
        for dept, info in data['departments'].items():
            print(f"  - {dept}: Budget ${info['budget']:,}, Manager: {info['manager']}")

# display_json_data('company_data.json')
```

### Writing JSON Files

```python
def write_json_file(filename, data, indent=4):
    """Write data to a JSON file."""
    try:
        with open(filename, 'w', encoding='utf-8') as file:
            json.dump(data, file, indent=indent, ensure_ascii=False)
        print(f"Data written to '{filename}' successfully")
        return True
    except Exception as e:
        print(f"Error writing JSON file: {e}")
        return False

def update_json_file(filename, new_data, merge=True):
    """Update JSON file with new data."""
    try:
        # Read existing data
        existing_data = read_json_file(filename)
        if existing_data is None:
            existing_data = {}
        
        # Merge or replace data
        if merge and isinstance(existing_data, dict) and isinstance(new_data, dict):
            existing_data.update(new_data)
            data_to_write = existing_data
        else:
            data_to_write = new_data
        
        # Write updated data
        write_json_file(filename, data_to_write)
        return True
    except Exception as e:
        print(f"Error updating JSON file: {e}")
        return False

# Example: Update employee data
def add_employee_to_json():
    """Add a new employee to the JSON file."""
    new_employee = {
        "id": 4,
        "name": "Diana Prince",
        "position": "Product Manager",
        "salary": 90000,
        "skills": ["Product Strategy", "Agile", "User Research"]
    }
    
    # Read current data
    data = read_json_file('company_data.json')
    if data:
        # Add new employee
        data['employees'].append(new_employee)
        
        # Write back to file
        write_json_file('company_data.json', data)
        print(f"Added new employee: {new_employee['name']}")
    
    return new_employee

# add_employee_to_json()
```

## File Management and Utilities

### File Information and Operations

```python
import os
import shutil
from datetime import datetime

def get_file_info(filename):
    """Get detailed information about a file."""
    try:
        if not os.path.exists(filename):
            print(f"File '{filename}' does not exist")
            return None
        
        stat_info = os.stat(filename)
        
        info = {
            'filename': filename,
            'size': stat_info.st_size,
            'size_mb': round(stat_info.st_size / (1024 * 1024), 2),
            'created': datetime.fromtimestamp(stat_info.st_ctime),
            'modified': datetime.fromtimestamp(stat_info.st_mtime),
            'accessed': datetime.fromtimestamp(stat_info.st_atime),
            'is_file': os.path.isfile(filename),
            'is_directory': os.path.isdir(filename),
            'absolute_path': os.path.abspath(filename)
        }
        
        return info
    except Exception as e:
        print(f"Error getting file info: {e}")
        return None

def display_file_info(filename):
    """Display file information in a readable format."""
    info = get_file_info(filename)
    if info:
        print(f"\nFile Information for: {info['filename']}")
        print(f"Size: {info['size']} bytes ({info['size_mb']} MB)")
        print(f"Created: {info['created']}")
        print(f"Modified: {info['modified']}")
        print(f"Accessed: {info['accessed']}")
        print(f"Type: {'File' if info['is_file'] else 'Directory'}")
        print(f"Absolute Path: {info['absolute_path']}")

# display_file_info('company_data.json')
```

### File Operations

```python
def copy_file(source, destination):
    """Copy a file from source to destination."""
    try:
        shutil.copy2(source, destination)
        print(f"File copied from '{source}' to '{destination}'")
        return True
    except Exception as e:
        print(f"Error copying file: {e}")
        return False

def move_file(source, destination):
    """Move a file from source to destination."""
    try:
        shutil.move(source, destination)
        print(f"File moved from '{source}' to '{destination}'")
        return True
    except Exception as e:
        print(f"Error moving file: {e}")
        return False

def delete_file(filename):
    """Delete a file."""
    try:
        if os.path.exists(filename):
            os.remove(filename)
            print(f"File '{filename}' deleted successfully")
            return True
        else:
            print(f"File '{filename}' does not exist")
            return False
    except Exception as e:
        print(f"Error deleting file: {e}")
        return False

def create_directory(dirname):
    """Create a directory."""
    try:
        os.makedirs(dirname, exist_ok=True)
        print(f"Directory '{dirname}' created successfully")
        return True
    except Exception as e:
        print(f"Error creating directory: {e}")
        return False

def list_directory_contents(dirname="."):
    """List contents of a directory."""
    try:
        contents = os.listdir(dirname)
        print(f"\nContents of '{dirname}':")
        
        files = []
        directories = []
        
        for item in contents:
            item_path = os.path.join(dirname, item)
            if os.path.isfile(item_path):
                files.append(item)
            elif os.path.isdir(item_path):
                directories.append(item)
        
        if directories:
            print("Directories:")
            for directory in sorted(directories):
                print(f"  📁 {directory}")
        
        if files:
            print("Files:")
            for file in sorted(files):
                file_path = os.path.join(dirname, file)
                size = os.path.getsize(file_path)
                print(f"  📄 {file} ({size} bytes)")
        
        return contents
    except Exception as e:
        print(f"Error listing directory: {e}")
        return None

# list_directory_contents()
```

## Practical Examples

### Example 1: Log File Processor

```python
def log_file_processor():
    """Process log files and extract useful information."""
    
    def create_sample_log():
        """Create a sample log file."""
        log_entries = [
            "2024-01-01 10:00:00 INFO User login successful user_id=123",
            "2024-01-01 10:05:00 ERROR Database connection failed error_code=500",
            "2024-01-01 10:10:00 INFO User logout user_id=123",
            "2024-01-01 10:15:00 WARNING High memory usage 85%",
            "2024-01-01 10:20:00 INFO New user registration user_id=124",
            "2024-01-01 10:25:00 ERROR Payment processing failed user_id=124",
            "2024-01-01 10:30:00 INFO User login successful user_id=125"
        ]
        
        with open('application.log', 'w') as file:
            for entry in log_entries:
                file.write(entry + '\n')
        
        print("Sample log file created: application.log")
    
    def analyze_log_file(filename):
        """Analyze log file and extract statistics."""
        try:
            with open(filename, 'r') as file:
                lines = file.readlines()
            
            # Initialize counters
            log_levels = {'INFO': 0, 'ERROR': 0, 'WARNING': 0, 'DEBUG': 0}
            user_activities = {}
            error_messages = []
            
            # Process each line
            for line in lines:
                line = line.strip()
                if not line:
                    continue
                
                # Extract log level
                if ' INFO ' in line:
                    log_levels['INFO'] += 1
                elif ' ERROR ' in line:
                    log_levels['ERROR'] += 1
                    error_messages.append(line)
                elif ' WARNING ' in line:
                    log_levels['WARNING'] += 1
                elif ' DEBUG ' in line:
                    log_levels['DEBUG'] += 1
                
                # Extract user activities
                if 'user_id=' in line:
                    import re
                    user_match = re.search(r'user_id=(\d+)', line)
                    if user_match:
                        user_id = user_match.group(1)
                        if user_id not in user_activities:
                            user_activities[user_id] = []
                        user_activities[user_id].append(line)
            
            # Generate report
            report = f"""
=== Log Analysis Report ===
Total log entries: {len(lines)}

Log Level Distribution:
"""
            for level, count in log_levels.items():
                if count > 0:
                    report += f"  {level}: {count}\n"
            
            report += f"\nActive Users: {len(user_activities)}\n"
            for user_id, activities in user_activities.items():
                report += f"  User {user_id}: {len(activities)} activities\n"
            
            if error_messages:
                report += f"\nError Messages ({len(error_messages)}):\n"
                for error in error_messages[:5]:  # Show first 5 errors
                    report += f"  - {error}\n"
            
            return report
        
        except Exception as e:
            return f"Error analyzing log file: {e}"
    
    # Create sample log and analyze it
    create_sample_log()
    report = analyze_log_file('application.log')
    print(report)
    
    # Save report to file
    with open('log_analysis_report.txt', 'w') as file:
        file.write(report)
    print("Report saved to: log_analysis_report.txt")

# log_file_processor()
```

### Example 2: Data Backup System

```python
def data_backup_system():
    """A simple data backup system."""
    
    def backup_file(source_file, backup_dir="backups"):
        """Backup a single file."""
        try:
            # Create backup directory if it doesn't exist
            os.makedirs(backup_dir, exist_ok=True)
            
            # Generate backup filename with timestamp
            timestamp = datetime.now().strftime("%Y%m%d_%H%M%S")
            filename = os.path.basename(source_file)
            name, ext = os.path.splitext(filename)
            backup_filename = f"{name}_{timestamp}{ext}"
            backup_path = os.path.join(backup_dir, backup_filename)
            
            # Copy file
            shutil.copy2(source_file, backup_path)
            print(f"File backed up: {source_file} -> {backup_path}")
            return backup_path
        
        except Exception as e:
            print(f"Error backing up file: {e}")
            return None
    
    def backup_directory(source_dir, backup_dir="backups"):
        """Backup an entire directory."""
        try:
            # Create backup directory with timestamp
            timestamp = datetime.now().strftime("%Y%m%d_%H%M%S")
            dirname = os.path.basename(source_dir)
            backup_path = os.path.join(backup_dir, f"{dirname}_{timestamp}")
            
            # Copy directory
            shutil.copytree(source_dir, backup_path)
            print(f"Directory backed up: {source_dir} -> {backup_path}")
            return backup_path
        
        except Exception as e:
            print(f"Error backing up directory: {e}")
            return None
    
    def cleanup_old_backups(backup_dir="backups", days_to_keep=7):
        """Clean up backup files older than specified days."""
        try:
            if not os.path.exists(backup_dir):
                print(f"Backup directory '{backup_dir}' does not exist")
                return
            
            current_time = datetime.now()
            deleted_count = 0
            
            for item in os.listdir(backup_dir):
                item_path = os.path.join(backup_dir, item)
                
                # Get file/directory modification time
                mod_time = datetime.fromtimestamp(os.path.getmtime(item_path))
                
                # Calculate age in days
                age_days = (current_time - mod_time).days
                
                if age_days > days_to_keep:
                    if os.path.isfile(item_path):
                        os.remove(item_path)
                        deleted_count += 1
                        print(f"Deleted old backup file: {item}")
                    elif os.path.isdir(item_path):
                        shutil.rmtree(item_path)
                        deleted_count += 1
                        print(f"Deleted old backup directory: {item}")
            
            print(f"Cleanup complete. Deleted {deleted_count} old backup(s)")
        
        except Exception as e:
            print(f"Error during cleanup: {e}")
    
    # Example usage
    print("=== Data Backup System ===")
    
    # Create some test files
    with open('important_data.txt', 'w') as file:
        file.write("This is important data that needs to be backed up.\n")
        file.write("It contains critical information.\n")
    
    # Backup individual file
    backup_file('important_data.txt')
    
    # Backup multiple files
    test_files = ['company_data.json', 'employees.csv']
    for file in test_files:
        if os.path.exists(file):
            backup_file(file)
    
    # List backup directory
    list_directory_contents('backups')
    
    # Cleanup old backups (keep only 0 days for demo)
    cleanup_old_backups(days_to_keep=0)

# data_backup_system()
```

## Key Takeaways

1. **File modes** ('r', 'w', 'a', 'r+') determine how files are opened
2. **Context managers** (with statement) ensure proper file handling
3. **CSV files** are great for tabular data and can be read as lists or dictionaries
4. **JSON files** are perfect for structured data and API responses
5. **File operations** include copy, move, delete, and directory management
6. **Error handling** is crucial when working with files
7. **Large files** should be processed iteratively to avoid memory issues
8. **Backup strategies** help protect important data

## Next Steps

In the next lesson, we'll explore modules and packages - how to organize code into reusable components, create your own modules, and work with Python's extensive library ecosystem.
