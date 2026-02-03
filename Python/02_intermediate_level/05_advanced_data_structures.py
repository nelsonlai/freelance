"""
Advanced Data Structures - Beyond the Basics
This file contains all the example code from the Advanced Data Structures lesson.
"""

# Stacks LIFO - Last In First Out

class Stack:
    """A simple stack implementation using a list."""
    
    def __init__(self):
        """Initialize an empty stack."""
        self.items = []
    
    def push(self, item):
        """Add an item to the top of the stack."""
        self.items.append(item)
    
    def pop(self):
        """Remove and return the top item from the stack."""
        if self.is_empty():
            raise IndexError("Stack is empty")
        return self.items.pop()
    
    def peek(self):
        """Return the top item without removing it."""
        if self.is_empty():
            raise IndexError("Stack is empty")
        return self.items[-1]
    
    def is_empty(self):
        """Check if the stack is empty."""
        return len(self.items) == 0
    
    def size(self):
        """Return the number of items in the stack."""
        return len(self.items)
    
    def __str__(self):
        """String representation of the stack."""
        return f"Stack({self.items})"

# Using the Stack
print("=== Stack Demo ===")
stack = Stack()

# Push items
stack.push(1)
stack.push(2)
stack.push(3)
print(f"Stack after pushing 1, 2, 3: {stack}")
print(f"Top item: {stack.peek()}")
print(f"Stack size: {stack.size()}")

# Pop items
print(f"Popped: {stack.pop()}")
print(f"Popped: {stack.pop()}")
print(f"Stack after popping: {stack}")

# Practical Stack Applications

def is_balanced_parentheses(expression):
    """Check if parentheses are balanced using a stack."""
    stack = Stack()
    opening_brackets = "([{"
    closing_brackets = ")]}"
    
    for char in expression:
        if char in opening_brackets:
            stack.push(char)
        elif char in closing_brackets:
            if stack.is_empty():
                return False
            
            # Get the corresponding opening bracket
            opening_index = closing_brackets.index(char)
            expected_opening = opening_brackets[opening_index]
            
            if stack.pop() != expected_opening:
                return False
    
    return stack.is_empty()

def evaluate_postfix(expression):
    """Evaluate a postfix expression using a stack."""
    stack = Stack()
    operators = {'+', '-', '*', '/'}
    
    for token in expression.split():
        if token not in operators:
            # It's a number
            stack.push(float(token))
        else:
            # It's an operator
            if stack.size() < 2:
                raise ValueError("Invalid postfix expression")
            
            b = stack.pop()
            a = stack.pop()
            
            if token == '+':
                result = a + b
            elif token == '-':
                result = a - b
            elif token == '*':
                result = a * b
            elif token == '/':
                if b == 0:
                    raise ValueError("Division by zero")
                result = a / b
            
            stack.push(result)
    
    if stack.size() != 1:
        raise ValueError("Invalid postfix expression")
    
    return stack.pop()

# Test stack applications
print("\n=== Stack Applications ===")

# Test balanced parentheses
test_expressions = [
    "()",
    "()[]{}",
    "([{}])",
    "([)]",
    "((())",
    ""
]

for expr in test_expressions:
    result = is_balanced_parentheses(expr)
    print(f"'{expr}' is balanced: {result}")

# Test postfix evaluation
postfix_expressions = [
    "3 4 +",
    "3 4 + 2 *",
    "15 7 1 1 + - / 3 * 2 1 1 + + -",
    "5 1 2 + 4 * + 3 -"
]

for expr in postfix_expressions:
    try:
        result = evaluate_postfix(expr)
        print(f"'{expr}' = {result}")
    except ValueError as e:
        print(f"Error evaluating '{expr}': {e}")

# Queues

class Queue:
    """A simple queue implementation using a list."""
    
    def __init__(self):
        """Initialize an empty queue."""
        self.items = []
    
    def enqueue(self, item):
        """Add an item to the rear of the queue."""
        self.items.append(item)
    
    def dequeue(self):
        """Remove and return the front item from the queue."""
        if self.is_empty():
            raise IndexError("Queue is empty")
        return self.items.pop(0)
    
    def front(self):
        """Return the front item without removing it."""
        if self.is_empty():
            raise IndexError("Queue is empty")
        return self.items[0]
    
    def is_empty(self):
        """Check if the queue is empty."""
        return len(self.items) == 0
    
    def size(self):
        """Return the number of items in the queue."""
        return len(self.items)
    
    def __str__(self):
        """String representation of the queue."""
        return f"Queue({self.items})"

# Using the Queue
print("\n=== Queue Demo ===")
queue = Queue()

# Enqueue items
queue.enqueue(1)
queue.enqueue(2)
queue.enqueue(3)
print(f"Queue after enqueueing 1, 2, 3: {queue}")
print(f"Front item: {queue.front()}")
print(f"Queue size: {queue.size()}")

# Dequeue items
print(f"Dequeued: {queue.dequeue()}")
print(f"Dequeued: {queue.dequeue()}")
print(f"Queue after dequeueing: {queue}")

# Advanced Queue Implementations

class CircularQueue:
    """A circular queue implementation."""
    
    def __init__(self, capacity):
        """Initialize a circular queue with given capacity."""
        self.capacity = capacity
        self.queue = [None] * capacity
        self.front = 0
        self.rear = 0
        self.count = 0
    
    def enqueue(self, item):
        """Add an item to the queue."""
        if self.is_full():
            raise OverflowError("Queue is full")
        
        self.queue[self.rear] = item
        self.rear = (self.rear + 1) % self.capacity
        self.count += 1
    
    def dequeue(self):
        """Remove and return an item from the queue."""
        if self.is_empty():
            raise IndexError("Queue is empty")
        
        item = self.queue[self.front]
        self.queue[self.front] = None
        self.front = (self.front + 1) % self.capacity
        self.count -= 1
        return item
    
    def is_empty(self):
        """Check if the queue is empty."""
        return self.count == 0
    
    def is_full(self):
        """Check if the queue is full."""
        return self.count == self.capacity
    
    def size(self):
        """Return the number of items in the queue."""
        return self.count
    
    def __str__(self):
        """String representation of the queue."""
        items = []
        for i in range(self.count):
            index = (self.front + i) % self.capacity
            items.append(str(self.queue[index]))
        return f"CircularQueue([{', '.join(items)}])"

class PriorityQueue:
    """A simple priority queue implementation."""
    
    def __init__(self):
        """Initialize an empty priority queue."""
        self.items = []
    
    def enqueue(self, item, priority):
        """Add an item with given priority."""
        # Insert item maintaining priority order (lower number = higher priority)
        inserted = False
        for i, (existing_item, existing_priority) in enumerate(self.items):
            if priority < existing_priority:
                self.items.insert(i, (item, priority))
                inserted = True
                break
        
        if not inserted:
            self.items.append((item, priority))
    
    def dequeue(self):
        """Remove and return the highest priority item."""
        if self.is_empty():
            raise IndexError("Priority queue is empty")
        
        item, priority = self.items.pop(0)
        return item
    
    def peek(self):
        """Return the highest priority item without removing it."""
        if self.is_empty():
            raise IndexError("Priority queue is empty")
        
        item, priority = self.items[0]
        return item
    
    def is_empty(self):
        """Check if the priority queue is empty."""
        return len(self.items) == 0
    
    def size(self):
        """Return the number of items in the priority queue."""
        return len(self.items)
    
    def __str__(self):
        """String representation of the priority queue."""
        items_str = [f"({item}, {priority})" for item, priority in self.items]
        return f"PriorityQueue([{', '.join(items_str)}])"

# Test advanced queue implementations
print("\n=== Advanced Queue Implementations ===")

# Test circular queue
cq = CircularQueue(3)
print(f"Empty circular queue: {cq}")

cq.enqueue(1)
cq.enqueue(2)
print(f"After enqueueing 1, 2: {cq}")

print(f"Dequeued: {cq.dequeue()}")
cq.enqueue(3)
print(f"After dequeuing and enqueueing 3: {cq}")

# Test priority queue
pq = PriorityQueue()
print(f"Empty priority queue: {pq}")

pq.enqueue("Task A", 3)
pq.enqueue("Task B", 1)
pq.enqueue("Task C", 2)
print(f"After adding tasks: {pq}")

print(f"Highest priority task: {pq.dequeue()}")
print(f"After dequeueing: {pq}")

# List Comprehensions

print("\n=== List Comprehensions ===")

# Basic list comprehensions
# Traditional approach
squares = []
for i in range(10):
    squares.append(i ** 2)

# List comprehension approach
squares_lc = [i ** 2 for i in range(10)]

print(f"Traditional: {squares}")
print(f"Comprehension: {squares_lc}")

# More examples
even_numbers = [x for x in range(20) if x % 2 == 0]
print(f"Even numbers: {even_numbers}")

words = ["hello", "world", "python", "programming"]
word_lengths = [len(word) for word in words]
print(f"Word lengths: {word_lengths}")

# With conditions
long_words = [word for word in words if len(word) > 5]
print(f"Long words: {long_words}")

# With transformations
upper_words = [word.upper() for word in words]
print(f"Upper case words: {upper_words}")

# Nested comprehensions
matrix = [[i + j for j in range(3)] for i in range(3)]
print(f"Matrix: {matrix}")

# Flattening a nested list
nested_list = [[1, 2, 3], [4, 5, 6], [7, 8, 9]]
flattened = [item for sublist in nested_list for item in sublist]
print(f"Flattened: {flattened}")

# Advanced List Comprehensions

print("\n=== Advanced List Comprehensions ===")

# Multiple conditions
numbers = list(range(20))
filtered = [x for x in numbers if x % 2 == 0 and x % 3 == 0]
print(f"Numbers divisible by 2 and 3: {filtered}")

# Using functions
def is_prime(n):
    """Check if a number is prime."""
    if n < 2:
        return False
    for i in range(2, int(n ** 0.5) + 1):
        if n % i == 0:
            return False
    return True

primes = [x for x in range(2, 50) if is_prime(x)]
print(f"Prime numbers up to 50: {primes}")

# Complex transformations
students = [
    {"name": "Alice", "grades": [85, 90, 78]},
    {"name": "Bob", "grades": [92, 88, 95]},
    {"name": "Charlie", "grades": [76, 82, 80]}
]

student_averages = [
    {"name": student["name"], "average": sum(student["grades"]) / len(student["grades"])}
    for student in students
]
print(f"Student averages: {student_averages}")

# List comprehension with walrus operator (Python 3.8+)
# This creates a list of squares but only includes even squares
even_squares = [y for x in range(10) if (y := x ** 2) % 2 == 0]
print(f"Even squares: {even_squares}")

# Dictionary Comprehensions

print("\n=== Dictionary Comprehensions ===")

# Basic dictionary comprehension
squares_dict = {x: x ** 2 for x in range(10)}
print(f"Squares dictionary: {squares_dict}")

# From existing dictionary
original = {"apple": 1.5, "banana": 0.8, "orange": 2.0}
# Increase prices by 10%
increased_prices = {fruit: price * 1.1 for fruit, price in original.items()}
print(f"Increased prices: {increased_prices}")

# With conditions
expensive_fruits = {fruit: price for fruit, price in original.items() if price > 1.0}
print(f"Expensive fruits: {expensive_fruits}")

# String transformations
words = ["hello", "world", "python"]
word_lengths = {word: len(word) for word in words}
print(f"Word lengths: {word_lengths}")

# From lists
names = ["Alice", "Bob", "Charlie"]
ages = [25, 30, 35]
people = {name: age for name, age in zip(names, ages)}
print(f"People: {people}")

# Complex example
students = ["Alice", "Bob", "Charlie", "Diana"]
grades = [[85, 90, 78], [92, 88, 95], [76, 82, 80], [88, 85, 90]]

student_data = {
    name: {
        "grades": grade_list,
        "average": sum(grade_list) / len(grade_list),
        "highest": max(grade_list),
        "lowest": min(grade_list)
    }
    for name, grade_list in zip(students, grades)
}

print(f"Student data: {student_data}")

# Set Comprehensions

print("\n=== Set Comprehensions ===")

# Basic set comprehension
even_squares_set = {x ** 2 for x in range(10) if x % 2 == 0}
print(f"Even squares set: {even_squares_set}")

# From string
text = "hello world python programming"
unique_vowels = {char for char in text if char in "aeiou"}
print(f"Unique vowels: {unique_vowels}")

# Word length set
words = ["hello", "world", "python", "programming", "code"]
word_lengths_set = {len(word) for word in words}
print(f"Word lengths set: {word_lengths_set}")

# Complex example - find common letters in words
words_list = ["python", "programming", "language", "computer"]
common_letters = set.intersection(*[set(word) for word in words_list])
print(f"Common letters: {common_letters}")

# All letters that appear in any word
all_letters = set.union(*[set(word) for word in words_list])
print(f"All letters: {sorted(all_letters)}")

# Nested Data Structures

print("\n=== Nested Data Structures ===")

# Nested lists
matrix = [
    [1, 2, 3, 4],
    [5, 6, 7, 8],
    [9, 10, 11, 12]
]

print(f"Matrix: {matrix}")
print(f"Element at [1][2]: {matrix[1][2]}")

# Transpose matrix using list comprehension
transpose = [[row[i] for row in matrix] for i in range(len(matrix[0]))]
print(f"Transpose: {transpose}")

# Nested dictionaries
company_data = {
    "employees": {
        "engineering": {
            "developers": [
                {"name": "Alice", "experience": 5, "skills": ["Python", "JavaScript"]},
                {"name": "Bob", "experience": 3, "skills": ["Java", "Python"]}
            ],
            "designers": [
                {"name": "Charlie", "experience": 4, "skills": ["UI/UX", "Figma"]}
            ]
        },
        "marketing": {
            "managers": [
                {"name": "Diana", "experience": 7, "skills": ["Strategy", "Analytics"]}
            ]
        }
    },
    "projects": {
        "active": ["Website Redesign", "Mobile App"],
        "completed": ["API Development", "Database Migration"]
    }
}

# Accessing nested data
print(f"First developer: {company_data['employees']['engineering']['developers'][0]}")
print(f"Active projects: {company_data['projects']['active']}")

# Complex nested structure manipulation
def find_employees_by_skill(data, skill):
    """Find all employees with a specific skill."""
    employees = []
    
    for department, roles in data["employees"].items():
        for role, people in roles.items():
            for person in people:
                if skill in person["skills"]:
                    employees.append({
                        "name": person["name"],
                        "department": department,
                        "role": role,
                        "experience": person["experience"]
                    })
    
    return employees

python_developers = find_employees_by_skill(company_data, "Python")
print(f"Python developers: {python_developers}")

# Calculate average experience by department
def calculate_dept_experience(data):
    """Calculate average experience by department."""
    dept_stats = {}
    
    for department, roles in data["employees"].items():
        total_experience = 0
        total_employees = 0
        
        for role, people in roles.items():
            for person in people:
                total_experience += person["experience"]
                total_employees += 1
        
        if total_employees > 0:
            dept_stats[department] = {
                "average_experience": total_experience / total_employees,
                "total_employees": total_employees
            }
    
    return dept_stats

dept_stats = calculate_dept_experience(company_data)
print(f"Department statistics: {dept_stats}")

# Practical Examples

print("\n=== Practical Examples ===")

# Example 1: Task Scheduler

class TaskScheduler:
    """A task scheduler using priority queue and stack."""
    
    def __init__(self):
        self.tasks = PriorityQueue()
        self.completed_tasks = Stack()
        self.current_task = None
    
    def add_task(self, task_name, priority, estimated_time):
        """Add a new task to the scheduler."""
        task = {
            "name": task_name,
            "priority": priority,
            "estimated_time": estimated_time,
            "status": "pending"
        }
        self.tasks.enqueue(task, priority)
        return f"Added task: {task_name}"
    
    def start_next_task(self):
        """Start the highest priority pending task."""
        if self.tasks.is_empty():
            return "No pending tasks"
        
        if self.current_task:
            return f"Cannot start new task. '{self.current_task['name']}' is currently running"
        
        self.current_task = self.tasks.dequeue()
        self.current_task["status"] = "running"
        return f"Started task: {self.current_task['name']}"
    
    def complete_current_task(self):
        """Complete the currently running task."""
        if not self.current_task:
            return "No task is currently running"
        
        self.current_task["status"] = "completed"
        self.completed_tasks.push(self.current_task)
        completed_name = self.current_task["name"]
        self.current_task = None
        
        return f"Completed task: {completed_name}"
    
    def get_status(self):
        """Get current status of the scheduler."""
        status = {
            "current_task": self.current_task["name"] if self.current_task else None,
            "pending_tasks": self.tasks.size(),
            "completed_tasks": self.completed_tasks.size()
        }
        return status
    
    def get_recently_completed(self, n=3):
        """Get recently completed tasks."""
        recent = []
        temp_stack = Stack()
        
        # Pop n items from completed_tasks
        for _ in range(min(n, self.completed_tasks.size())):
            temp_stack.push(self.completed_tasks.pop())
        
        # Collect the items and put them back
        while not temp_stack.is_empty():
            task = temp_stack.pop()
            recent.append(task)
            self.completed_tasks.push(task)
        
        return recent

# Using the task scheduler
print("\n=== Task Scheduler Demo ===")

scheduler = TaskScheduler()

# Add tasks
scheduler.add_task("Fix bug in login", 1, 2)
scheduler.add_task("Update documentation", 3, 4)
scheduler.add_task("Implement new feature", 2, 6)
scheduler.add_task("Code review", 4, 1)

print(f"Scheduler status: {scheduler.get_status()}")

# Process tasks
print(scheduler.start_next_task())
print(f"Status: {scheduler.get_status()}")

print(scheduler.complete_current_task())
print(f"Status: {scheduler.get_status()}")

print(scheduler.start_next_task())
print(scheduler.complete_current_task())

print(scheduler.start_next_task())
print(scheduler.complete_current_task())

print(f"Recently completed: {scheduler.get_recently_completed()}")

# Example 2: Data Analysis with Advanced Structures

class DataAnalyzer:
    """A data analyzer using advanced data structures."""
    
    def __init__(self):
        self.data_history = Stack()
        self.current_data = {}
    
    def load_data(self, data):
        """Load new data, saving current data to history."""
        if self.current_data:
            self.data_history.push(self.current_data.copy())
        
        self.current_data = data.copy()
        return f"Loaded {len(data)} records"
    
    def undo_load(self):
        """Restore previous data state."""
        if self.data_history.is_empty():
            return "No previous data to restore"
        
        self.current_data = self.data_history.pop()
        return "Restored previous data"
    
    def analyze_sales_data(self, data):
        """Analyze sales data using comprehensions."""
        if not data:
            return "No data to analyze"
        
        # Calculate total sales using list comprehension
        total_sales = sum(item["amount"] for item in data)
        
        # Find top products using dictionary comprehension
        product_sales = {}
        for item in data:
            product = item["product"]
            product_sales[product] = product_sales.get(product, 0) + item["amount"]
        
        top_products = dict(sorted(product_sales.items(), key=lambda x: x[1], reverse=True)[:3])
        
        # Find sales by month using set and dictionary comprehensions
        months = {item["date"].split("-")[1] for item in data}
        monthly_sales = {
            month: sum(item["amount"] for item in data if item["date"].split("-")[1] == month)
            for month in months
        }
        
        # Find high-value transactions
        high_value = [item for item in data if item["amount"] > 1000]
        
        analysis = {
            "total_sales": total_sales,
            "total_transactions": len(data),
            "average_sale": total_sales / len(data),
            "top_products": top_products,
            "monthly_sales": monthly_sales,
            "high_value_transactions": len(high_value)
        }
        
        return analysis

# Using the data analyzer
print("\n=== Data Analysis Demo ===")

analyzer = DataAnalyzer()

# Sample sales data
sales_data = [
    {"product": "Laptop", "amount": 1200, "date": "2024-01-15"},
    {"product": "Mouse", "amount": 25, "date": "2024-01-16"},
    {"product": "Keyboard", "amount": 75, "date": "2024-02-01"},
    {"product": "Laptop", "amount": 1200, "date": "2024-02-05"},
    {"product": "Monitor", "amount": 300, "date": "2024-02-10"},
    {"product": "Tablet", "amount": 800, "date": "2024-01-20"},
    {"product": "Mouse", "amount": 25, "date": "2024-02-15"},
    {"product": "Desktop", "amount": 1500, "date": "2024-02-20"}
]

print(analyzer.load_data(sales_data))
analysis = analyzer.analyze_sales_data(sales_data)

print("\nSales Analysis Results:")
for key, value in analysis.items():
    print(f"{key}: {value}")

# Load new data and test undo
new_data = [
    {"product": "Phone", "amount": 600, "date": "2024-03-01"},
    {"product": "Case", "amount": 30, "date": "2024-03-02"}
]

print(f"\n{analyzer.load_data(new_data)}")
print(f"Current data size: {len(analyzer.current_data)}")

print(analyzer.undo_load())
print(f"Restored data size: {len(analyzer.current_data)}")

print("\n=== Advanced Data Structures Examples Complete ===")
