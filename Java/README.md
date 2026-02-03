# Comprehensive Java Training Materials

Welcome to a comprehensive Java training program designed for students learning Java from beginner to advanced levels. This curriculum covers everything from basic syntax to advanced topics, data structures, and multi-file project development.

## 📚 Table of Contents

1. [Learning Path](#learning-path)
2. [Beginner Level](#beginner-level)
3. [Medium Level](#medium-level)
4. [Advanced Level](#advanced-level)
5. [Data Structures](#data-structures)
6. [Projects](#projects)
7. [How to Use This Material](#how-to-use-this-material)

## 🎯 Learning Path

### Recommended Learning Sequence:

1. **Week 1-2: Beginner Level**
   - Variables and Data Types
   - Operators
   - Control Flow
   - Methods
   - Arrays

2. **Week 3-4: Medium Level**
   - Classes and Objects
   - Inheritance
   - Polymorphism
   - Interfaces
   - Abstract Classes

3. **Week 5-6: Advanced Level**
   - Generics
   - Collections Framework
   - Streams API
   - Exception Handling
   - Concurrency

4. **Week 7-8: Data Structures**
   - Linked Lists
   - Stacks and Queues
   - Binary Trees
   - Hash Tables

5. **Week 9-10: Projects**
   - Multi-file Projects
   - Package Structure
   - Real-world Applications

## 📖 Beginner Level

Location: `beginner/`

### Topics Covered:

1. **01_VariablesAndDataTypes.java**
   - Primitive data types (int, double, boolean, char)
   - Variable declaration and initialization
   - Type conversion (casting)
   - Constants (final keyword)
   - String basics

2. **02_Operators.java**
   - Arithmetic operators (+, -, *, /, %)
   - Comparison operators (==, !=, <, >, <=, >=)
   - Logical operators (&&, ||, !)
   - Assignment operators (=, +=, -=, *=, /=, %=)
   - Increment/Decrement operators (++, --)
   - Ternary operator (? :)
   - Operator precedence

3. **03_ControlFlow.java**
   - if, else if, else statements
   - switch statements
   - for loops
   - while loops
   - do-while loops
   - break and continue statements
   - Nested loops

4. **04_Methods.java**
   - Method declaration and definition
   - Method parameters and arguments
   - Return types and return statements
   - Method overloading
   - Static vs instance methods
   - Recursive methods
   - Varargs (variable arguments)

5. **05_Arrays.java**
   - Array declaration and initialization
   - Accessing array elements
   - Array length
   - Multi-dimensional arrays
   - Array manipulation
   - Common array operations

## 📘 Medium Level

Location: `medium/`

### Topics Covered:

1. **01_ClassesAndObjects.java**
   - Class definition
   - Object creation
   - Instance variables (fields)
   - Instance methods
   - Constructors
   - this keyword
   - Access modifiers (public, private, protected)
   - Getter and Setter methods

2. **02_Inheritance.java**
   - Class inheritance (extends keyword)
   - Method overriding
   - super keyword
   - Constructor chaining
   - Access modifiers in inheritance
   - instanceof operator
   - Multi-level inheritance

3. **03_Polymorphism.java**
   - Runtime polymorphism (method overriding)
   - Compile-time polymorphism (method overloading)
   - Dynamic method dispatch
   - Virtual method invocation
   - Upcasting and downcasting
   - Polymorphism with arrays

4. **04_Interfaces.java**
   - Interface definition
   - Implementing interfaces
   - Multiple interface implementation
   - Default methods in interfaces
   - Static methods in interfaces
   - Functional interfaces
   - Interface inheritance
   - Lambda expressions

5. **05_AbstractClasses.java**
   - Abstract class definition
   - Abstract methods
   - Concrete methods in abstract classes
   - Abstract class vs Interface
   - When to use abstract classes
   - Final methods

## 📗 Advanced Level

Location: `advanced/`

### Topics Covered:

1. **01_Generics.java**
   - Generic classes
   - Generic methods
   - Bounded type parameters
   - Wildcards (?, ? extends, ? super)
   - Generic interfaces
   - Type erasure
   - Multiple type parameters

2. **02_Collections.java**
   - List (ArrayList, LinkedList)
   - Set (HashSet, TreeSet, LinkedHashSet)
   - Map (HashMap, TreeMap, LinkedHashMap)
   - Queue and Deque
   - Iterator and ListIterator
   - Collections utility class
   - Converting between collections

3. **03_Streams.java**
   - Creating streams
   - Intermediate operations (filter, map, sorted, distinct, etc.)
   - Terminal operations (forEach, collect, reduce, etc.)
   - Parallel streams
   - Optional class
   - Grouping and partitioning
   - Chaining operations

4. **04_Exceptions.java**
   - Try-catch-finally blocks
   - Multiple catch blocks
   - Checked vs Unchecked exceptions
   - Custom exceptions
   - Try-with-resources
   - Exception propagation
   - Best practices

5. **05_Concurrency.java**
   - Thread creation and management
   - Synchronization
   - Thread pools (ExecutorService)
   - Future and CompletableFuture
   - Concurrent collections
   - Atomic classes
   - Thread states

## 📊 Data Structures

Location: `data_structures/`

### Topics Covered:

1. **01_LinkedList.java**
   - Singly Linked List implementation
   - Doubly Linked List implementation
   - Basic operations (insert, delete, search, traverse)
   - Reversing a linked list

2. **02_StackAndQueue.java**
   - Stack implementation (Array and Linked List)
   - Queue implementation (Array and Linked List)
   - Applications of Stack and Queue
   - Balanced parentheses checker
   - String reversal using stack

3. **03_BinaryTree.java**
   - Binary Tree implementation
   - Tree traversal (Inorder, Preorder, Postorder, Level-order)
   - Binary Search Tree (BST)
   - Tree operations (insert, delete, search)
   - Finding min/max in BST
   - Tree height and node count

4. **04_HashTable.java**
   - Hash Table implementation
   - Hash functions
   - Collision handling (Chaining, Linear Probing)
   - Hash Map operations
   - Java's HashMap usage

## 🏗️ Projects

Location: `projects/`

### Library Management System

A complete multi-file Java project demonstrating:

- **Package Structure**: Proper organization using packages
- **Model Classes**: Book and Member entities
- **Service Layer**: Business logic separation
- **Utility Classes**: Reusable validation functions
- **Main Application**: Entry point with demonstration

**Project Structure:**
```
src/com/example/library/
├── model/
│   ├── Book.java
│   └── Member.java
├── service/
│   └── LibraryService.java
├── util/
│   └── ValidationUtil.java
└── main/
    └── LibraryApp.java
```

**Features:**
- Add/Remove books and members
- Search books by title or author
- Borrow and return books
- Track member borrowing history
- Validation of ISBN and email
- Statistics and reporting

## 🚀 How to Use This Material

### Prerequisites

- Java JDK 8 or higher installed
- A text editor or IDE (IntelliJ IDEA, Eclipse, VS Code)
- Basic understanding of programming concepts

### Getting Started

1. **For Beginners:**
   - Start with `beginner/01_VariablesAndDataTypes.java`
   - Compile and run each file to see the output
   - Modify the code to experiment
   - Progress sequentially through all beginner files

2. **For Intermediate Learners:**
   - Review beginner materials if needed
   - Start with `medium/01_ClassesAndObjects.java`
   - Understand OOP concepts thoroughly
   - Practice by creating your own classes

3. **For Advanced Learners:**
   - Review medium-level materials
   - Start with `advanced/01_Generics.java`
   - Focus on understanding complex concepts
   - Practice with real-world scenarios

4. **Data Structures:**
   - Study each data structure implementation
   - Understand time and space complexity
   - Practice implementing from scratch
   - Solve problems using these structures

5. **Projects:**
   - Study the Library Management System
   - Understand package structure
   - Learn separation of concerns
   - Create your own projects following the pattern

### Compiling and Running

**Single File:**
```bash
javac FileName.java
java FileName
```

**Multi-file Project:**
```bash
# Navigate to project directory
cd projects

# Compile all files
javac -d bin src/com/example/library/**/*.java

# Run the application
java -cp bin com.example.library.main.LibraryApp
```

### Learning Tips

1. **Practice Regularly**: Code along with examples
2. **Experiment**: Modify code to see what happens
3. **Build Projects**: Apply concepts in real projects
4. **Read Documentation**: Refer to Java official documentation
5. **Solve Problems**: Practice on coding platforms (LeetCode, HackerRank)
6. **Review**: Regularly review previous concepts
7. **Ask Questions**: Join Java communities for help

### Additional Resources

- [Oracle Java Documentation](https://docs.oracle.com/javase/)
- [Java Tutorials by Oracle](https://docs.oracle.com/javase/tutorial/)
- [Java Programming on Coursera](https://www.coursera.org/)
- [Java on Stack Overflow](https://stackoverflow.com/questions/tagged/java)

## 📝 Notes

- All code examples are well-commented
- Each file is self-contained and can be run independently
- Examples progress from simple to complex
- Real-world scenarios are included where applicable
- Best practices are demonstrated throughout

## 🎓 Assessment

After completing each level, test your knowledge by:

1. **Beginner**: Create a calculator program
2. **Medium**: Build a simple banking system with classes
3. **Advanced**: Implement a task management system with collections
4. **Data Structures**: Solve problems using different data structures
5. **Projects**: Build a complete application from scratch

## 🤝 Contributing

Feel free to:
- Add more examples
- Improve existing code
- Fix any errors
- Add more projects
- Enhance documentation

## 📄 License

This educational material is free to use for learning purposes.

---

**Happy Learning! 🎉**

Start your Java journey today and become a proficient Java developer!

