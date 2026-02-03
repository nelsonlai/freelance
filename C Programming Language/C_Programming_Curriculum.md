# Comprehensive C Programming Curriculum
## Based on "The C Programming Language" by Kernighan & Ritchie

### Course Overview
This curriculum is designed to take students from complete beginners to advanced C programmers, following the structure of the classic K&R book while incorporating modern teaching practices and additional resources.

### Learning Levels
- **Beginner (Weeks 1-4)**: Basic syntax, data types, simple I/O
- **Intermediate (Weeks 5-8)**: Functions, arrays, pointers basics
- **Advanced (Weeks 9-12)**: Complex data structures, file I/O, memory management
- **Expert (Weeks 13-16)**: System programming, optimization, large projects

---

## BEGINNER LEVEL (Weeks 1-4)

### Week 1: Introduction to C Programming
**Based on K&R Chapter 1: A Tutorial Introduction**

#### Learning Objectives
- Understand the history and importance of C
- Set up development environment
- Write and compile first C program
- Understand basic program structure

#### Topics Covered
1. History of C programming language
2. Setting up compiler (GCC/Clang)
3. Basic program structure
4. Hello World program
5. Comments in C
6. Basic compilation process

#### Code Examples

**Example 1.1: Hello World**
```c
#include <stdio.h>

int main() {
    printf("Hello, World!\n");
    return 0;
}
```

**Example 1.2: Simple Output**
```c
#include <stdio.h>

int main() {
    printf("Welcome to C Programming!\n");
    printf("This is line 2\n");
    printf("Number: %d\n", 42);
    return 0;
}
```

#### Exercises (Beginner Level)
1. **Exercise 1.1**: Modify the hello world program to print your name
2. **Exercise 1.2**: Write a program that prints a simple pattern using asterisks
3. **Exercise 1.3**: Create a program that prints the numbers 1 through 10

#### Solutions
```c
// Solution 1.1
#include <stdio.h>

int main() {
    printf("Hello, my name is [Student Name]!\n");
    return 0;
}

// Solution 1.2
#include <stdio.h>

int main() {
    printf("*****\n");
    printf("*   *\n");
    printf("*   *\n");
    printf("*****\n");
    return 0;
}

// Solution 1.3
#include <stdio.h>

int main() {
    for(int i = 1; i <= 10; i++) {
        printf("%d\n", i);
    }
    return 0;
}
```

---

### Week 2: Variables, Data Types, and Operators
**Based on K&R Chapter 2: Types, Operators, and Expressions**

#### Learning Objectives
- Understand different data types in C
- Learn variable declaration and initialization
- Master arithmetic, relational, and logical operators
- Understand type conversions

#### Topics Covered
1. Basic data types (int, float, double, char)
2. Variable declaration and initialization
3. Constants and literals
4. Arithmetic operators (+, -, *, /, %)
5. Relational operators (<, >, <=, >=, ==, !=)
6. Logical operators (&&, ||, !)
7. Assignment operators
8. Type conversions and casting

#### Code Examples

**Example 2.1: Variable Declarations**
```c
#include <stdio.h>

int main() {
    int age = 25;
    float height = 5.9;
    char grade = 'A';
    double pi = 3.14159;
    
    printf("Age: %d\n", age);
    printf("Height: %.1f\n", height);
    printf("Grade: %c\n", grade);
    printf("Pi: %.5f\n", pi);
    
    return 0;
}
```

**Example 2.2: Arithmetic Operations**
```c
#include <stdio.h>

int main() {
    int a = 10, b = 3;
    
    printf("a + b = %d\n", a + b);
    printf("a - b = %d\n", a - b);
    printf("a * b = %d\n", a * b);
    printf("a / b = %d\n", a / b);
    printf("a %% b = %d\n", a % b);
    
    return 0;
}
```

#### Exercises (Beginner Level)
1. **Exercise 2.1**: Calculate the area of a rectangle given length and width
2. **Exercise 2.2**: Convert temperature from Fahrenheit to Celsius
3. **Exercise 2.3**: Calculate simple interest given principal, rate, and time
4. **Exercise 2.4**: Swap two numbers without using a third variable

---

### Week 3: Input/Output and Control Flow Basics
**Based on K&R Chapter 3: Control Flow (Part 1)**

#### Learning Objectives
- Master input/output functions
- Understand conditional statements
- Learn basic loop structures
- Handle user input validation

#### Topics Covered
1. printf() and scanf() functions
2. Input validation
3. if, else if, else statements
4. Nested conditionals
5. Basic for loops
6. Basic while loops
7. do-while loops

#### Code Examples

**Example 3.1: User Input**
```c
#include <stdio.h>

int main() {
    int number;
    float decimal;
    char character;
    
    printf("Enter an integer: ");
    scanf("%d", &number);
    
    printf("Enter a decimal number: ");
    scanf("%f", &decimal);
    
    printf("Enter a character: ");
    scanf(" %c", &character);  // Note the space before %c
    
    printf("You entered: %d, %.2f, %c\n", number, decimal, character);
    
    return 0;
}
```

**Example 3.2: Conditional Statements**
```c
#include <stdio.h>

int main() {
    int score;
    
    printf("Enter your score: ");
    scanf("%d", &score);
    
    if (score >= 90) {
        printf("Grade: A\n");
    } else if (score >= 80) {
        printf("Grade: B\n");
    } else if (score >= 70) {
        printf("Grade: C\n");
    } else if (score >= 60) {
        printf("Grade: D\n");
    } else {
        printf("Grade: F\n");
    }
    
    return 0;
}
```

#### Exercises (Beginner Level)
1. **Exercise 3.1**: Check if a number is even or odd
2. **Exercise 3.2**: Find the largest of three numbers
3. **Exercise 3.3**: Create a simple calculator for two numbers
4. **Exercise 3.4**: Print multiplication table for a given number

---

### Week 4: Loops and Problem Solving
**Based on K&R Chapter 3: Control Flow (Part 2)**

#### Learning Objectives
- Master different types of loops
- Understand nested loops
- Learn break and continue statements
- Solve problems using loops

#### Topics Covered
1. Advanced for loop usage
2. Nested loops
3. while vs do-while loops
4. break and continue statements
5. Infinite loops and how to avoid them
6. Loop optimization basics

#### Code Examples

**Example 4.1: Nested Loops - Pattern Printing**
```c
#include <stdio.h>

int main() {
    int rows = 5;
    
    // Print triangle pattern
    for (int i = 1; i <= rows; i++) {
        for (int j = 1; j <= i; j++) {
            printf("* ");
        }
        printf("\n");
    }
    
    return 0;
}
```

**Example 4.2: Prime Number Checker**
```c
#include <stdio.h>

int main() {
    int num, i, isPrime = 1;
    
    printf("Enter a number: ");
    scanf("%d", &num);
    
    if (num <= 1) {
        isPrime = 0;
    } else {
        for (i = 2; i * i <= num; i++) {
            if (num % i == 0) {
                isPrime = 0;
                break;
            }
        }
    }
    
    if (isPrime) {
        printf("%d is a prime number.\n", num);
    } else {
        printf("%d is not a prime number.\n", num);
    }
    
    return 0;
}
```

#### Exercises (Beginner Level)
1. **Exercise 4.1**: Print Fibonacci series up to n terms
2. **Exercise 4.2**: Calculate factorial of a number
3. **Exercise 4.3**: Check if a number is palindrome
4. **Exercise 4.4**: Print all prime numbers between 1 and 100

---

## INTERMEDIATE LEVEL (Weeks 5-8)

### Week 5: Functions and Modular Programming
**Based on K&R Chapter 4: Functions and Program Structure**

#### Learning Objectives
- Understand function declaration and definition
- Learn parameter passing mechanisms
- Master return values and void functions
- Understand scope and lifetime of variables

#### Topics Covered
1. Function declaration and definition
2. Function prototypes
3. Parameter passing (pass by value)
4. Return statements
5. Local vs global variables
6. Static variables
7. Recursive functions

#### Code Examples

**Example 5.1: Basic Functions**
```c
#include <stdio.h>

// Function prototype
int add(int a, int b);
void printGreeting(void);

int main() {
    int result = add(5, 3);
    printf("5 + 3 = %d\n", result);
    
    printGreeting();
    
    return 0;
}

// Function definition
int add(int a, int b) {
    return a + b;
}

void printGreeting(void) {
    printf("Hello from function!\n");
}
```

**Example 5.2: Recursive Function**
```c
#include <stdio.h>

int factorial(int n) {
    if (n == 0 || n == 1) {
        return 1;
    } else {
        return n * factorial(n - 1);
    }
}

int main() {
    int num = 5;
    printf("Factorial of %d is %d\n", num, factorial(num));
    return 0;
}
```

#### Exercises (Intermediate Level)
1. **Exercise 5.1**: Create a function to check if a number is prime
2. **Exercise 5.2**: Write a recursive function for Fibonacci series
3. **Exercise 5.3**: Implement power function (x^y) using recursion
4. **Exercise 5.4**: Create a function to reverse a number

---

### Week 6: Arrays and String Basics
**Based on K&R Chapter 5: Pointers and Arrays (Part 1)**

#### Learning Objectives
- Understand array declaration and initialization
- Learn array indexing and manipulation
- Master string handling basics
- Understand multi-dimensional arrays

#### Topics Covered
1. Array declaration and initialization
2. Array indexing and bounds
3. String as character arrays
4. String input/output
5. Two-dimensional arrays
6. Array processing algorithms

#### Code Examples

**Example 6.1: Array Operations**
```c
#include <stdio.h>

int main() {
    int numbers[5] = {10, 20, 30, 40, 50};
    int sum = 0;
    
    // Print array elements
    printf("Array elements: ");
    for (int i = 0; i < 5; i++) {
        printf("%d ", numbers[i]);
        sum += numbers[i];
    }
    printf("\n");
    
    printf("Sum: %d\n", sum);
    printf("Average: %.2f\n", (float)sum / 5);
    
    return 0;
}
```

**Example 6.2: String Handling**
```c
#include <stdio.h>
#include <string.h>

int main() {
    char name[50];
    char greeting[100];
    
    printf("Enter your name: ");
    fgets(name, sizeof(name), stdin);
    
    // Remove newline character
    name[strcspn(name, "\n")] = '\0';
    
    sprintf(greeting, "Hello, %s!", name);
    printf("%s\n", greeting);
    
    printf("Your name has %lu characters.\n", strlen(name));
    
    return 0;
}
```

#### Exercises (Intermediate Level)
1. **Exercise 6.1**: Find the largest element in an array
2. **Exercise 6.2**: Reverse an array
3. **Exercise 6.3**: Count vowels in a string
4. **Exercise 6.4**: Implement bubble sort for an array

---

### Week 7: Pointers Fundamentals
**Based on K&R Chapter 5: Pointers and Arrays (Part 2)**

#### Learning Objectives
- Understand pointer concepts and syntax
- Learn pointer arithmetic
- Master pointer-array relationships
- Understand pass by reference using pointers

#### Topics Covered
1. Pointer declaration and initialization
2. Address-of (&) and dereference (*) operators
3. Pointer arithmetic
4. Pointers and arrays relationship
5. Pointers as function parameters
6. Pointer to pointer basics

#### Code Examples

**Example 7.1: Basic Pointers**
```c
#include <stdio.h>

int main() {
    int num = 42;
    int *ptr = &num;
    
    printf("Value of num: %d\n", num);
    printf("Address of num: %p\n", (void*)&num);
    printf("Value of ptr: %p\n", (void*)ptr);
    printf("Value pointed by ptr: %d\n", *ptr);
    
    // Modify value through pointer
    *ptr = 100;
    printf("New value of num: %d\n", num);
    
    return 0;
}
```

**Example 7.2: Pointers with Functions**
```c
#include <stdio.h>

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int main() {
    int x = 10, y = 20;
    
    printf("Before swap: x = %d, y = %d\n", x, y);
    swap(&x, &y);
    printf("After swap: x = %d, y = %d\n", x, y);
    
    return 0;
}
```

#### Exercises (Intermediate Level)
1. **Exercise 7.1**: Write a function to find maximum using pointers
2. **Exercise 7.2**: Implement string length function using pointers
3. **Exercise 7.3**: Create a function to reverse a string using pointers
4. **Exercise 7.4**: Sort an array using pointers

---

### Week 8: Advanced Arrays and Strings
**Integration of previous concepts**

#### Learning Objectives
- Master multi-dimensional arrays
- Understand dynamic memory concepts
- Learn advanced string manipulation
- Integrate arrays, pointers, and functions

#### Topics Covered
1. Multi-dimensional arrays
2. Array of strings
3. Command line arguments
4. Advanced string functions
5. Array processing algorithms
6. Memory layout concepts

#### Code Examples

**Example 8.1: 2D Arrays**
```c
#include <stdio.h>

int main() {
    int matrix[3][3] = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };
    
    printf("Matrix:\n");
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
    
    return 0;
}
```

**Example 8.2: Command Line Arguments**
```c
#include <stdio.h>

int main(int argc, char *argv[]) {
    printf("Number of arguments: %d\n", argc);
    
    for (int i = 0; i < argc; i++) {
        printf("Argument %d: %s\n", i, argv[i]);
    }
    
    return 0;
}
```

#### Exercises (Intermediate Level)
1. **Exercise 8.1**: Matrix multiplication program
2. **Exercise 8.2**: Word count program using command line arguments
3. **Exercise 8.3**: String tokenizer program
4. **Exercise 8.4**: Tic-tac-toe game using 2D array

---

## ADVANCED LEVEL (Weeks 9-12)

### Week 9: Structures and User-Defined Types
**Based on K&R Chapter 6: Structures**

#### Learning Objectives
- Understand structure definition and usage
- Learn nested structures
- Master structure pointers
- Understand unions and enumerations

#### Topics Covered
1. Structure definition and initialization
2. Structure members access
3. Nested structures
4. Array of structures
5. Pointers to structures
6. Unions and their usage
7. Enumerations (enum)
8. typedef keyword

#### Code Examples

**Example 9.1: Basic Structures**
```c
#include <stdio.h>
#include <string.h>

struct Student {
    int id;
    char name[50];
    float gpa;
};

int main() {
    struct Student student1;
    
    student1.id = 1001;
    strcpy(student1.name, "John Doe");
    student1.gpa = 3.85;
    
    printf("Student ID: %d\n", student1.id);
    printf("Student Name: %s\n", student1.name);
    printf("Student GPA: %.2f\n", student1.gpa);
    
    return 0;
}
```

**Example 9.2: Structure with Pointers**
```c
#include <stdio.h>
#include <string.h>

struct Point {
    int x, y;
};

void printPoint(struct Point *p) {
    printf("Point: (%d, %d)\n", p->x, p->y);
}

int main() {
    struct Point p1 = {10, 20};
    struct Point *ptr = &p1;
    
    printPoint(ptr);
    
    ptr->x = 30;
    ptr->y = 40;
    
    printPoint(&p1);
    
    return 0;
}
```

#### Exercises (Advanced Level)
1. **Exercise 9.1**: Student management system using structures
2. **Exercise 9.2**: Library book management system
3. **Exercise 9.3**: Employee payroll system
4. **Exercise 9.4**: Geometric calculator using structures

---

### Week 10: File Input/Output
**Based on K&R Chapter 7: Input and Output**

#### Learning Objectives
- Master file operations in C
- Understand different file modes
- Learn binary vs text files
- Handle file errors properly

#### Topics Covered
1. File pointers and fopen()
2. File reading functions (fgetc, fgets, fread)
3. File writing functions (fputc, fputs, fwrite)
4. File positioning (fseek, ftell, rewind)
5. Binary file operations
6. Error handling in file operations
7. Command line file processing

#### Code Examples

**Example 10.1: Text File Operations**
```c
#include <stdio.h>

int main() {
    FILE *file;
    char line[100];
    
    // Writing to file
    file = fopen("data.txt", "w");
    if (file == NULL) {
        printf("Error opening file for writing!\n");
        return 1;
    }
    
    fprintf(file, "Hello, File!\n");
    fprintf(file, "This is line 2\n");
    fprintf(file, "Number: %d\n", 42);
    fclose(file);
    
    // Reading from file
    file = fopen("data.txt", "r");
    if (file == NULL) {
        printf("Error opening file for reading!\n");
        return 1;
    }
    
    while (fgets(line, sizeof(line), file) != NULL) {
        printf("%s", line);
    }
    fclose(file);
    
    return 0;
}
```

**Example 10.2: Binary File Operations**
```c
#include <stdio.h>

struct Record {
    int id;
    char name[20];
    float value;
};

int main() {
    FILE *file;
    struct Record records[3] = {
        {1, "Item1", 10.5},
        {2, "Item2", 20.3},
        {3, "Item3", 15.8}
    };
    
    // Write binary data
    file = fopen("records.dat", "wb");
    if (file != NULL) {
        fwrite(records, sizeof(struct Record), 3, file);
        fclose(file);
    }
    
    // Read binary data
    struct Record readRecords[3];
    file = fopen("records.dat", "rb");
    if (file != NULL) {
        fread(readRecords, sizeof(struct Record), 3, file);
        fclose(file);
        
        for (int i = 0; i < 3; i++) {
            printf("ID: %d, Name: %s, Value: %.1f\n", 
                   readRecords[i].id, readRecords[i].name, readRecords[i].value);
        }
    }
    
    return 0;
}
```

#### Exercises (Advanced Level)
1. **Exercise 10.1**: File copying utility
2. **Exercise 10.2**: Word frequency counter
3. **Exercise 10.3**: Student grade management with file storage
4. **Exercise 10.4**: Log file analyzer

---

### Week 11: Dynamic Memory Management
**Advanced memory concepts**

#### Learning Objectives
- Understand dynamic memory allocation
- Master malloc, calloc, realloc, free
- Learn memory leak prevention
- Understand linked data structures

#### Topics Covered
1. Dynamic memory allocation (malloc, calloc)
2. Memory deallocation (free)
3. Memory reallocation (realloc)
4. Memory leaks and debugging
5. Dynamic arrays
6. Linked lists implementation
7. Memory management best practices

#### Code Examples

**Example 11.1: Dynamic Arrays**
```c
#include <stdio.h>
#include <stdlib.h>

int main() {
    int n, *arr, sum = 0;
    
    printf("Enter number of elements: ");
    scanf("%d", &n);
    
    // Allocate memory
    arr = (int*)malloc(n * sizeof(int));
    if (arr == NULL) {
        printf("Memory allocation failed!\n");
        return 1;
    }
    
    // Input elements
    printf("Enter %d elements: ", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
        sum += arr[i];
    }
    
    printf("Sum: %d\n", sum);
    printf("Average: %.2f\n", (float)sum / n);
    
    // Free memory
    free(arr);
    
    return 0;
}
```

**Example 11.2: Simple Linked List**
```c
#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

void printList(struct Node* head) {
    struct Node* current = head;
    while (current != NULL) {
        printf("%d -> ", current->data);
        current = current->next;
    }
    printf("NULL\n");
}

int main() {
    struct Node* head = NULL;
    struct Node* second = NULL;
    struct Node* third = NULL;
    
    // Allocate nodes
    head = (struct Node*)malloc(sizeof(struct Node));
    second = (struct Node*)malloc(sizeof(struct Node));
    third = (struct Node*)malloc(sizeof(struct Node));
    
    head->data = 1;
    head->next = second;
    
    second->data = 2;
    second->next = third;
    
    third->data = 3;
    third->next = NULL;
    
    printList(head);
    
    // Free memory
    free(head);
    free(second);
    free(third);
    
    return 0;
}
```

#### Exercises (Advanced Level)
1. **Exercise 11.1**: Dynamic string manipulation
2. **Exercise 11.2**: Resizable array implementation
3. **Exercise 11.3**: Complete linked list with insertion/deletion
4. **Exercise 11.4**: Memory pool allocator

---

### Week 12: Advanced Data Structures
**Complex data structure implementation**

#### Learning Objectives
- Implement stacks and queues
- Understand trees and graphs basics
- Learn hash tables concepts
- Master complex pointer manipulations

#### Topics Covered
1. Stack implementation (array and linked list)
2. Queue implementation
3. Binary trees basics
4. Hash tables introduction
5. Advanced pointer techniques
6. Data structure performance analysis

#### Code Examples

**Example 12.1: Stack Implementation**
```c
#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100

struct Stack {
    int items[MAX_SIZE];
    int top;
};

void initialize(struct Stack* s) {
    s->top = -1;
}

int isEmpty(struct Stack* s) {
    return s->top == -1;
}

int isFull(struct Stack* s) {
    return s->top == MAX_SIZE - 1;
}

void push(struct Stack* s, int value) {
    if (isFull(s)) {
        printf("Stack overflow!\n");
        return;
    }
    s->items[++s->top] = value;
}

int pop(struct Stack* s) {
    if (isEmpty(s)) {
        printf("Stack underflow!\n");
        return -1;
    }
    return s->items[s->top--];
}

int main() {
    struct Stack stack;
    initialize(&stack);
    
    push(&stack, 10);
    push(&stack, 20);
    push(&stack, 30);
    
    printf("Popped: %d\n", pop(&stack));
    printf("Popped: %d\n", pop(&stack));
    
    return 0;
}
```

#### Exercises (Advanced Level)
1. **Exercise 12.1**: Calculator using stack (infix to postfix)
2. **Exercise 12.2**: Queue-based task scheduler
3. **Exercise 12.3**: Binary search tree implementation
4. **Exercise 12.4**: Simple hash table with collision handling

---

## EXPERT LEVEL (Weeks 13-16)

### Week 13: System Programming Basics
**Based on K&R Chapter 8: The UNIX System Interface**

#### Learning Objectives
- Understand system calls
- Learn process concepts
- Master inter-process communication basics
- Understand signals and error handling

#### Topics Covered
1. System calls vs library functions
2. Process creation and management
3. File system interface
4. Error handling and errno
5. Signal handling basics
6. Environment variables

#### Code Examples

**Example 13.1: System Calls**
```c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid = fork();
    
    if (pid == 0) {
        // Child process
        printf("Child process: PID = %d\n", getpid());
        execl("/bin/ls", "ls", "-l", NULL);
    } else if (pid > 0) {
        // Parent process
        printf("Parent process: PID = %d, Child PID = %d\n", getpid(), pid);
        wait(NULL);  // Wait for child to complete
        printf("Child process completed\n");
    } else {
        perror("fork failed");
        return 1;
    }
    
    return 0;
}
```

#### Exercises (Expert Level)
1. **Exercise 13.1**: File copy using system calls
2. **Exercise 13.2**: Process monitor utility
3. **Exercise 13.3**: Simple shell implementation
4. **Exercise 13.4**: Signal-based communication

---

### Week 14: Advanced Memory Management and Optimization
**Performance and optimization focus**

#### Learning Objectives
- Master memory debugging techniques
- Understand cache optimization
- Learn profiling and optimization
- Understand memory alignment

#### Topics Covered
1. Memory debugging tools (valgrind, etc.)
2. Cache-friendly programming
3. Memory alignment and padding
4. Performance profiling
5. Algorithm optimization
6. Compiler optimizations

#### Code Examples

**Example 14.1: Memory Debugging**
```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Memory leak detection helper
void* safe_malloc(size_t size, const char* file, int line) {
    void* ptr = malloc(size);
    if (ptr == NULL) {
        fprintf(stderr, "Memory allocation failed at %s:%d\n", file, line);
        exit(1);
    }
    printf("Allocated %zu bytes at %p (%s:%d)\n", size, ptr, file, line);
    return ptr;
}

void safe_free(void* ptr, const char* file, int line) {
    if (ptr != NULL) {
        printf("Freed memory at %p (%s:%d)\n", ptr, file, line);
        free(ptr);
    }
}

#define SAFE_MALLOC(size) safe_malloc(size, __FILE__, __LINE__)
#define SAFE_FREE(ptr) safe_free(ptr, __FILE__, __LINE__)

int main() {
    char* buffer = SAFE_MALLOC(100);
    strcpy(buffer, "Hello, Memory Management!");
    printf("Buffer content: %s\n", buffer);
    SAFE_FREE(buffer);
    
    return 0;
}
```

#### Exercises (Expert Level)
1. **Exercise 14.1**: Memory pool allocator with debugging
2. **Exercise 14.2**: Cache-optimized matrix multiplication
3. **Exercise 14.3**: Performance benchmarking suite
4. **Exercise 14.4**: Custom garbage collector (simple)

---

### Week 15: Large Project Development
**Comprehensive project work**

#### Learning Objectives
- Plan and structure large C projects
- Implement modular design
- Use version control effectively
- Create comprehensive documentation

#### Topics Covered
1. Project structure and organization
2. Makefile creation and build systems
3. Header file organization
4. Documentation standards
5. Testing frameworks
6. Version control integration

#### Major Project Options
Choose one of these projects to implement:

**Project Option 1: Text Editor**
- File operations (open, save, create)
- Text manipulation (insert, delete, search, replace)
- Buffer management
- Simple command interface

**Project Option 2: Database System**
- Record storage and retrieval
- Indexing system
- Query processing
- Transaction basics

**Project Option 3: Compiler/Interpreter**
- Lexical analysis
- Syntax parsing
- Symbol table management
- Code generation basics

**Project Option 4: Operating System Simulator**
- Process scheduling
- Memory management simulation
- File system simulation
- Basic shell interface

---

### Week 16: Advanced Topics and Career Preparation

#### Learning Objectives
- Explore specialized C applications
- Understand industry best practices
- Prepare for technical interviews
- Plan continued learning path

#### Topics Covered
1. Embedded C programming
2. Network programming basics
3. Graphics programming introduction
4. Performance optimization techniques
5. Code review and quality assurance
6. Industry coding standards

#### Code Examples

**Example 16.1: Network Programming Basics**
```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

int main() {
    int server_fd, client_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char buffer[1024] = {0};
    char* hello = "Hello from server";
    
    // Create socket
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }
    
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(8080);
    
    // Bind socket
    if (bind(server_fd, (struct sockaddr*)&address, sizeof(address)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    
    // Listen for connections
    if (listen(server_fd, 3) < 0) {
        perror("listen failed");
        exit(EXIT_FAILURE);
    }
    
    printf("Server listening on port 8080...\n");
    
    // Accept connection
    client_socket = accept(server_fd, (struct sockaddr*)&address, (socklen_t*)&addrlen);
    if (client_socket < 0) {
        perror("accept failed");
        exit(EXIT_FAILURE);
    }
    
    // Read and respond
    read(client_socket, buffer, 1024);
    printf("Message from client: %s\n", buffer);
    send(client_socket, hello, strlen(hello), 0);
    
    close(client_socket);
    close(server_fd);
    
    return 0;
}
```

---

## Assessment and Evaluation

### Weekly Assessments
- **Beginner Level**: Basic syntax and logic tests
- **Intermediate Level**: Function and array manipulation problems
- **Advanced Level**: Complex data structure implementations
- **Expert Level**: System programming and optimization challenges

### Final Projects by Level
1. **Beginner**: Simple calculator with file logging
2. **Intermediate**: Student management system with file storage
3. **Advanced**: Data structure library implementation
4. **Expert**: Choose from major project options

### Grading Criteria
- Code functionality (40%)
- Code quality and style (25%)
- Problem-solving approach (20%)
- Documentation and comments (15%)

---

## Additional Resources

### Recommended Reading
1. "The C Programming Language" by Kernighan & Ritchie (primary text)
2. "C Programming: A Modern Approach" by K.N. King
3. "Expert C Programming" by Peter van der Linden
4. "C Traps and Pitfalls" by Andrew Koenig

### Online Resources
1. C Reference: cppreference.com
2. Practice Problems: HackerRank, LeetCode
3. Code Review: GitHub, Stack Overflow
4. Debugging Tools: GDB, Valgrind documentation

### Development Tools
1. **Compilers**: GCC, Clang
2. **IDEs**: Code::Blocks, Dev-C++, VS Code
3. **Debugging**: GDB, Valgrind
4. **Build Tools**: Make, CMake
5. **Version Control**: Git

---

## Learning Tips and Best Practices

### For Students
1. **Practice Daily**: Write code every day, even if just for 30 minutes
2. **Debug Systematically**: Use debugging tools and techniques
3. **Read Others' Code**: Study well-written C programs
4. **Join Communities**: Participate in programming forums and groups
5. **Build Projects**: Apply concepts in real-world projects

### For Instructors
1. **Emphasize Fundamentals**: Ensure strong foundation before advancing
2. **Use Visual Aids**: Diagrams for pointers and memory concepts
3. **Provide Feedback**: Regular code reviews and constructive criticism
4. **Encourage Experimentation**: Let students explore and make mistakes
5. **Connect to Real World**: Show practical applications of concepts

---

## Troubleshooting Common Issues

### Beginner Issues
- **Compilation Errors**: Missing semicolons, unmatched braces
- **Logic Errors**: Off-by-one errors in loops, incorrect conditions
- **Input/Output**: scanf format specifiers, buffer overflow

### Intermediate Issues
- **Pointer Confusion**: Null pointer dereference, pointer arithmetic
- **Memory Issues**: Array bounds, uninitialized variables
- **Function Issues**: Parameter passing, return value handling

### Advanced Issues
- **Memory Leaks**: Forgetting to free allocated memory
- **Segmentation Faults**: Invalid memory access
- **File Handling**: Proper error checking, file mode issues

---

This curriculum provides a comprehensive pathway from beginner to expert level C programming, following the structure of the classic K&R book while incorporating modern teaching practices and real-world applications.
