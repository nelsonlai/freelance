# Assessment Tests and Projects
## C Programming Curriculum - All Levels

---

## BEGINNER LEVEL ASSESSMENTS

### Week 1-2 Assessment: Basic Programming Concepts

**Time Limit: 60 minutes**
**Total Points: 100**

#### Question 1 (20 points)
Write a C program that:
- Prompts the user to enter their name and age
- Calculates how old they will be in 10 years
- Displays a formatted message with the results

**Expected Output:**
```
Enter your name: John
Enter your age: 25
Hello John! In 10 years, you will be 35 years old.
```

#### Question 2 (25 points)
Create a program that calculates the total cost of items purchased:
- Read the price of 3 items from the user
- Calculate subtotal
- Apply 8.5% tax
- Display itemized receipt

**Expected Output:**
```
Enter price of item 1: $10.50
Enter price of item 2: $25.00
Enter price of item 3: $5.75

--- RECEIPT ---
Subtotal: $41.25
Tax (8.5%): $3.51
Total: $44.76
```

#### Question 3 (30 points)
Write a program that determines letter grades based on numerical scores:
- Read 5 test scores from the user
- Calculate the average
- Assign letter grade (A: 90-100, B: 80-89, C: 70-79, D: 60-69, F: below 60)
- Display results

#### Question 4 (25 points)
Create a number guessing game:
- Generate a random number between 1 and 100
- Allow user 7 attempts to guess
- Provide "higher" or "lower" hints
- Display appropriate win/lose message

---

### Week 3-4 Assessment: Control Flow and Loops

**Time Limit: 90 minutes**
**Total Points: 100**

#### Question 1 (25 points)
Write a program that prints the following pattern:
```
    *
   ***
  *****
 *******
*********
```

#### Question 2 (30 points)
Create a menu-driven calculator that continues until user chooses to exit:
```
CALCULATOR MENU
1. Addition
2. Subtraction
3. Multiplication
4. Division
5. Exit
Enter choice: 
```

#### Question 3 (25 points)
Write a program that finds all perfect numbers between 1 and 1000.
(A perfect number equals the sum of its proper divisors, e.g., 6 = 1 + 2 + 3)

#### Question 4 (20 points)
Create a program that converts a decimal number to binary representation.

---

## INTERMEDIATE LEVEL ASSESSMENTS

### Week 5-6 Assessment: Functions and Arrays

**Time Limit: 120 minutes**
**Total Points: 100**

#### Question 1 (30 points)
Implement a library of mathematical functions:
```c
// Function prototypes
int gcd(int a, int b);           // Greatest common divisor
int lcm(int a, int b);           // Least common multiple
int isPerfectSquare(int n);      // Check if number is perfect square
double power(double base, int exp); // Calculate power recursively
```

Write a main function that demonstrates all functions with user input.

#### Question 2 (35 points)
Create a student grade management system using arrays:
- Store names and grades for up to 50 students
- Implement functions to:
  - Add student record
  - Display all students
  - Find highest and lowest grades
  - Calculate class average
  - Sort students by grade (descending)

#### Question 3 (35 points)
Implement string manipulation functions without using string.h:
```c
int myStrlen(char str[]);
void myStrcpy(char dest[], char src[]);
int myStrcmp(char str1[], char str2[]);
void myStrcat(char dest[], char src[]);
void myStrrev(char str[]);
```

---

### Week 7-8 Assessment: Pointers and Advanced Arrays

**Time Limit: 120 minutes**
**Total Points: 100**

#### Question 1 (40 points)
Implement a dynamic array library:
```c
typedef struct {
    int *data;
    int size;
    int capacity;
} DynamicArray;

DynamicArray* createArray(int initial_capacity);
void destroyArray(DynamicArray* arr);
int append(DynamicArray* arr, int value);
int insert(DynamicArray* arr, int index, int value);
int removeAt(DynamicArray* arr, int index);
int find(DynamicArray* arr, int value);
void printArray(DynamicArray* arr);
```

#### Question 2 (30 points)
Write a program that:
- Reads a text file
- Counts frequency of each character
- Displays results sorted by frequency
- Uses pointers for all string operations

#### Question 3 (30 points)
Implement matrix operations using pointers:
- Matrix addition
- Matrix multiplication
- Matrix transpose
- Display matrix in formatted output

---

## ADVANCED LEVEL ASSESSMENTS

### Week 9-10 Assessment: Structures and File I/O

**Time Limit: 150 minutes**
**Total Points: 100**

#### Question 1 (50 points)
Design and implement a complete inventory management system:

```c
typedef struct {
    int id;
    char name[50];
    char category[30];
    float price;
    int quantity;
    char supplier[50];
} Product;
```

Requirements:
- File-based storage (binary format)
- Add/Update/Delete products
- Search by ID, name, or category
- Generate low-stock report (quantity < 10)
- Calculate total inventory value
- Sort products by various criteria

#### Question 2 (25 points)
Create a log file analyzer that:
- Reads server log files
- Extracts IP addresses, timestamps, and HTTP status codes
- Generates summary statistics
- Identifies most frequent visitors
- Finds error patterns (4xx, 5xx status codes)

#### Question 3 (25 points)
Implement a simple database system:
- Store records in binary file
- Support basic SQL-like operations (SELECT, INSERT, UPDATE, DELETE)
- Handle multiple record types
- Implement indexing for fast searches

---

### Week 11-12 Assessment: Memory Management and Data Structures

**Time Limit: 180 minutes**
**Total Points: 100**

#### Question 1 (40 points)
Implement a complete linked list library:
```c
typedef struct Node {
    int data;
    struct Node* next;
} Node;

typedef struct {
    Node* head;
    int size;
} LinkedList;

LinkedList* createList();
void destroyList(LinkedList* list);
int insertFront(LinkedList* list, int data);
int insertBack(LinkedList* list, int data);
int insertAt(LinkedList* list, int index, int data);
int removeFront(LinkedList* list);
int removeBack(LinkedList* list);
int removeAt(LinkedList* list, int index);
int find(LinkedList* list, int data);
void printList(LinkedList* list);
void reverseList(LinkedList* list);
```

#### Question 2 (30 points)
Create a memory debugging tool that:
- Tracks all malloc/free calls
- Detects memory leaks
- Identifies double-free errors
- Reports memory usage statistics
- Provides detailed allocation traces

#### Question 3 (30 points)
Implement a hash table with collision handling:
- Dynamic resizing
- Multiple hash functions
- Collision resolution (chaining or open addressing)
- Performance analysis and statistics

---

## EXPERT LEVEL ASSESSMENTS

### Week 13-14 Assessment: System Programming

**Time Limit: 240 minutes**
**Total Points: 100**

#### Question 1 (50 points)
Create a multi-process file processing system:
- Parent process manages worker processes
- Workers process different parts of large files
- Inter-process communication using pipes
- Signal handling for graceful shutdown
- Performance monitoring and statistics

Requirements:
- Handle files larger than available RAM
- Implement load balancing among workers
- Error recovery and fault tolerance
- Detailed logging and monitoring

#### Question 2 (25 points)
Implement a simple network client-server application:
- Server handles multiple concurrent clients
- Protocol for file transfer
- Error handling and recovery
- Security considerations (basic authentication)

#### Question 3 (25 points)
Create a system monitoring utility:
- Monitor CPU usage, memory usage, disk I/O
- Track process statistics
- Generate alerts for threshold violations
- Log data to files with rotation
- Web interface for viewing statistics (optional)

---

### Week 15-16 Assessment: Final Project

**Time Limit: 2 weeks**
**Total Points: 200**

Choose ONE of the following major projects:

#### Project Option 1: Text Editor (200 points)
Implement a full-featured console text editor with:

**Core Features (100 points):**
- File operations (new, open, save, save as)
- Text editing (insert, delete, cut, copy, paste)
- Navigation (cursor movement, goto line, search)
- Multiple file support (tabs/buffers)

**Advanced Features (100 points):**
- Syntax highlighting for C code
- Auto-indentation and bracket matching
- Undo/redo functionality
- Find and replace with regex support
- Configuration system
- Plugin architecture

#### Project Option 2: Database Management System (200 points)

**Core Features (100 points):**
- Table creation and management
- Data insertion, update, deletion
- Basic SELECT queries with WHERE clauses
- Index creation and management
- Transaction support (basic)

**Advanced Features (100 points):**
- JOIN operations
- Aggregate functions (COUNT, SUM, AVG, etc.)
- Query optimization
- Backup and recovery
- User management and permissions
- SQL parser and executor

#### Project Option 3: Operating System Simulator (200 points)

**Core Features (100 points):**
- Process scheduling (FCFS, SJF, Round Robin)
- Memory management (paging, segmentation)
- File system simulation
- Basic shell interface

**Advanced Features (100 points):**
- Virtual memory management
- Deadlock detection and prevention
- Multi-threading support
- Performance analysis tools
- GUI interface for visualization
- Benchmarking suite

#### Project Option 4: Compiler/Interpreter (200 points)

**Core Features (100 points):**
- Lexical analysis (tokenizer)
- Syntax analysis (parser)
- Symbol table management
- Basic code generation

**Advanced Features (100 points):**
- Semantic analysis
- Optimization passes
- Error reporting and recovery
- Debugging support
- Standard library functions
- Cross-platform compatibility

---

## ASSESSMENT RUBRICS

### Code Quality Rubric (applies to all assessments)

**Excellent (90-100%)**
- Clean, readable, well-organized code
- Comprehensive error handling
- Proper memory management
- Extensive comments and documentation
- Follows coding standards consistently
- Efficient algorithms and data structures

**Good (80-89%)**
- Generally clean and readable code
- Basic error handling present
- Mostly proper memory management
- Adequate comments
- Generally follows coding standards
- Reasonable algorithm choices

**Satisfactory (70-79%)**
- Code works but may be messy
- Limited error handling
- Some memory management issues
- Minimal comments
- Inconsistent coding style
- Basic algorithm implementation

**Needs Improvement (60-69%)**
- Code works but difficult to read
- Poor or no error handling
- Memory leaks or other issues
- No meaningful comments
- Poor coding style
- Inefficient implementation

**Unsatisfactory (Below 60%)**
- Code doesn't compile or run correctly
- No error handling
- Significant memory management problems
- No documentation
- Very poor coding practices

---

## PRACTICAL EXAM FORMAT

### Setup Requirements
- Individual workstations with C compiler (GCC/Clang)
- Text editor or IDE (preference)
- Access to standard C documentation
- No internet access during exam
- Provided reference materials only

### Submission Requirements
- All source code files
- Makefile for compilation
- README with compilation/execution instructions
- Test cases and expected outputs
- Brief documentation of design decisions

### Grading Timeline
- Code functionality: 60%
- Code quality and style: 20%
- Documentation and comments: 10%
- Error handling: 10%

---

## TAKE-HOME PROJECT GUIDELINES

### Academic Integrity
- Individual work unless specified as group project
- Cite any external resources used
- No direct copying from online sources
- Collaboration on concepts allowed, not implementation

### Documentation Requirements
- Design document explaining approach
- User manual with examples
- Technical documentation of functions/modules
- Testing strategy and test cases
- Performance analysis (where applicable)

### Submission Format
- Source code with proper organization
- Makefile or build script
- All documentation in markdown format
- Demo video (for complex projects)
- Peer review comments (for group projects)

---

## STUDY GUIDES

### Beginner Level Study Guide

**Key Topics to Review:**
1. Basic syntax and program structure
2. Data types and variable declarations
3. Input/output functions (printf, scanf)
4. Arithmetic and logical operators
5. Conditional statements (if, else, switch)
6. Loop structures (for, while, do-while)
7. Basic debugging techniques

**Practice Problems:**
- Number manipulation programs
- Pattern printing exercises
- Simple calculator implementations
- Basic games (guessing, dice rolling)

### Intermediate Level Study Guide

**Key Topics to Review:**
1. Function declaration and definition
2. Parameter passing and return values
3. Scope and lifetime of variables
4. Array declaration and manipulation
5. String handling and operations
6. Pointer basics and arithmetic
7. Memory addresses and dereferencing

**Practice Problems:**
- Mathematical function libraries
- Array sorting and searching algorithms
- String manipulation without library functions
- Pointer-based data manipulation

### Advanced Level Study Guide

**Key Topics to Review:**
1. Complex data structures (structs, unions)
2. File input/output operations
3. Dynamic memory allocation
4. Linked data structures
5. Error handling strategies
6. Binary file operations
7. Command-line argument processing

**Practice Problems:**
- Database-like applications
- File processing utilities
- Dynamic data structure implementations
- Memory management exercises

### Expert Level Study Guide

**Key Topics to Review:**
1. System calls and low-level programming
2. Process management and IPC
3. Signal handling
4. Network programming basics
5. Performance optimization techniques
6. Memory debugging and profiling
7. Large project organization

**Practice Problems:**
- System utility implementations
- Client-server applications
- Performance benchmarking tools
- Complex algorithm implementations

---

This comprehensive assessment framework provides structured evaluation at each learning level, ensuring students demonstrate mastery of concepts before advancing. The progressive difficulty and practical focus prepare students for real-world C programming challenges.
