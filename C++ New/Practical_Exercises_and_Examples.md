# C++ Practical Exercises and Examples

## Beginner Level Exercises (Weeks 1-4)

### Exercise 1.1: Hello World Variations
**Objective:** Get comfortable with basic C++ syntax and compilation

**Tasks:**
1. Write a program that asks for your name and age, then displays them
2. Create a program that calculates and displays the area of a rectangle
3. Write a program that converts temperature from Celsius to Fahrenheit

**Example Solution:**
```cpp
#include <iostream>
#include <string>

int main() {
    std::string name;
    int age;
    
    std::cout << "Enter your name: ";
    std::getline(std::cin, name);
    
    std::cout << "Enter your age: ";
    std::cin >> age;
    
    std::cout << "Hello, " << name << "! You are " << age << " years old." << std::endl;
    
    return 0;
}
```

---

### Exercise 1.2: Control Flow Practice
**Objective:** Master if/else statements and loops

**Tasks:**
1. Create a grade calculator that assigns letter grades based on percentage
2. Write a program that finds all prime numbers between 1 and 100
3. Implement a simple calculator with menu-driven interface

**Example Solution - Grade Calculator:**
```cpp
#include <iostream>

char calculateGrade(double percentage) {
    if (percentage >= 90) return 'A';
    else if (percentage >= 80) return 'B';
    else if (percentage >= 70) return 'C';
    else if (percentage >= 60) return 'D';
    else return 'F';
}

bool isPrime(int n) {
    if (n <= 1) return false;
    if (n <= 3) return true;
    if (n % 2 == 0 || n % 3 == 0) return false;
    
    for (int i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0) {
            return false;
        }
    }
    return true;
}

int main() {
    // Grade calculator
    double percentage;
    std::cout << "Enter percentage: ";
    std::cin >> percentage;
    
    char grade = calculateGrade(percentage);
    std::cout << "Grade: " << grade << std::endl;
    
    // Prime numbers
    std::cout << "Prime numbers between 1 and 100:" << std::endl;
    for (int i = 2; i <= 100; ++i) {
        if (isPrime(i)) {
            std::cout << i << " ";
        }
    }
    std::cout << std::endl;
    
    return 0;
}
```

---

### Exercise 1.3: Function Design
**Objective:** Learn function declaration, definition, and usage

**Tasks:**
1. Create functions for basic mathematical operations
2. Write a function that finds the maximum of three numbers
3. Implement a function that calculates factorial recursively

**Example Solution:**
```cpp
#include <iostream>
#include <cmath>

// Function declarations
double add(double a, double b);
double subtract(double a, double b);
double multiply(double a, double b);
double divide(double a, double b);
int maximum(int a, int b, int c);
long long factorial(int n);
void displayMenu();

int main() {
    int choice;
    double num1, num2, result;
    
    do {
        displayMenu();
        std::cout << "Enter your choice (1-5): ";
        std::cin >> choice;
        
        switch (choice) {
            case 1:
                std::cout << "Enter two numbers: ";
                std::cin >> num1 >> num2;
                result = add(num1, num2);
                std::cout << "Result: " << result << std::endl;
                break;
                
            case 2:
                std::cout << "Enter two numbers: ";
                std::cin >> num1 >> num2;
                result = subtract(num1, num2);
                std::cout << "Result: " << result << std::endl;
                break;
                
            case 3:
                std::cout << "Enter two numbers: ";
                std::cin >> num1 >> num2;
                result = multiply(num1, num2);
                std::cout << "Result: " << result << std::endl;
                break;
                
            case 4:
                std::cout << "Enter two numbers: ";
                std::cin >> num1 >> num2;
                if (num2 != 0) {
                    result = divide(num1, num2);
                    std::cout << "Result: " << result << std::endl;
                } else {
                    std::cout << "Error: Division by zero!" << std::endl;
                }
                break;
                
            case 5:
                std::cout << "Goodbye!" << std::endl;
                break;
                
            default:
                std::cout << "Invalid choice!" << std::endl;
        }
    } while (choice != 5);
    
    // Test maximum function
    std::cout << "Maximum of 10, 25, 15: " << maximum(10, 25, 15) << std::endl;
    
    // Test factorial function
    std::cout << "Factorial of 5: " << factorial(5) << std::endl;
    
    return 0;
}

// Function definitions
double add(double a, double b) {
    return a + b;
}

double subtract(double a, double b) {
    return a - b;
}

double multiply(double a, double b) {
    return a * b;
}

double divide(double a, double b) {
    return a / b;
}

int maximum(int a, int b, int c) {
    int max = a;
    if (b > max) max = b;
    if (c > max) max = c;
    return max;
}

long long factorial(int n) {
    if (n <= 1) return 1;
    return n * factorial(n - 1);
}

void displayMenu() {
    std::cout << "\n=== Calculator Menu ===" << std::endl;
    std::cout << "1. Add" << std::endl;
    std::cout << "2. Subtract" << std::endl;
    std::cout << "3. Multiply" << std::endl;
    std::cout << "4. Divide" << std::endl;
    std::cout << "5. Exit" << std::endl;
}
```

---

## Intermediate Level Exercises (Weeks 5-10)

### Exercise 2.1: Class Design - Library Management System
**Objective:** Master class design, encapsulation, and object-oriented principles

**Requirements:**
Create a simple library management system with the following classes:
- `Book`: Represents a book with title, author, ISBN, and availability status
- `Library`: Manages a collection of books and provides operations

**Tasks:**
1. Design the Book class with appropriate member variables and functions
2. Implement the Library class to manage books
3. Add functionality to add, remove, search, and display books
4. Implement book borrowing and returning functionality

**Example Solution:**
```cpp
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

class Book {
private:
    std::string title;
    std::string author;
    std::string isbn;
    bool isAvailable;
    
public:
    // Constructor
    Book(const std::string& t, const std::string& a, const std::string& i)
        : title(t), author(a), isbn(i), isAvailable(true) {}
    
    // Getters
    const std::string& getTitle() const { return title; }
    const std::string& getAuthor() const { return author; }
    const std::string& getISBN() const { return isbn; }
    bool getAvailability() const { return isAvailable; }
    
    // Setters
    void setTitle(const std::string& t) { title = t; }
    void setAuthor(const std::string& a) { author = a; }
    void setISBN(const std::string& i) { isbn = i; }
    
    // Book operations
    void borrow() { isAvailable = false; }
    void returnBook() { isAvailable = true; }
    
    // Display function
    void display() const {
        std::cout << "Title: " << title 
                  << ", Author: " << author 
                  << ", ISBN: " << isbn 
                  << ", Available: " << (isAvailable ? "Yes" : "No") << std::endl;
    }
};

class Library {
private:
    std::vector<Book> books;
    
public:
    // Add a book to the library
    void addBook(const Book& book) {
        books.push_back(book);
        std::cout << "Book added successfully!" << std::endl;
    }
    
    // Remove a book by ISBN
    bool removeBook(const std::string& isbn) {
        auto it = std::find_if(books.begin(), books.end(),
                              [&isbn](const Book& book) { 
                                  return book.getISBN() == isbn; 
                              });
        
        if (it != books.end()) {
            books.erase(it);
            std::cout << "Book removed successfully!" << std::endl;
            return true;
        } else {
            std::cout << "Book not found!" << std::endl;
            return false;
        }
    }
    
    // Search books by title
    std::vector<Book*> searchByTitle(const std::string& title) {
        std::vector<Book*> results;
        for (auto& book : books) {
            if (book.getTitle().find(title) != std::string::npos) {
                results.push_back(&book);
            }
        }
        return results;
    }
    
    // Search books by author
    std::vector<Book*> searchByAuthor(const std::string& author) {
        std::vector<Book*> results;
        for (auto& book : books) {
            if (book.getAuthor().find(author) != std::string::npos) {
                results.push_back(&book);
            }
        }
        return results;
    }
    
    // Borrow a book
    bool borrowBook(const std::string& isbn) {
        for (auto& book : books) {
            if (book.getISBN() == isbn) {
                if (book.getAvailability()) {
                    book.borrow();
                    std::cout << "Book borrowed successfully!" << std::endl;
                    return true;
                } else {
                    std::cout << "Book is not available!" << std::endl;
                    return false;
                }
            }
        }
        std::cout << "Book not found!" << std::endl;
        return false;
    }
    
    // Return a book
    bool returnBook(const std::string& isbn) {
        for (auto& book : books) {
            if (book.getISBN() == isbn) {
                book.returnBook();
                std::cout << "Book returned successfully!" << std::endl;
                return true;
            }
        }
        std::cout << "Book not found!" << std::endl;
        return false;
    }
    
    // Display all books
    void displayAllBooks() const {
        if (books.empty()) {
            std::cout << "No books in library!" << std::endl;
            return;
        }
        
        std::cout << "\n=== Library Catalog ===" << std::endl;
        for (const auto& book : books) {
            book.display();
        }
    }
    
    // Display available books only
    void displayAvailableBooks() const {
        std::cout << "\n=== Available Books ===" << std::endl;
        bool found = false;
        for (const auto& book : books) {
            if (book.getAvailability()) {
                book.display();
                found = true;
            }
        }
        if (!found) {
            std::cout << "No available books!" << std::endl;
        }
    }
};

int main() {
    Library library;
    
    // Add some books
    library.addBook(Book("The Great Gatsby", "F. Scott Fitzgerald", "978-0-7432-7356-5"));
    library.addBook(Book("To Kill a Mockingbird", "Harper Lee", "978-0-06-112008-4"));
    library.addBook(Book("1984", "George Orwell", "978-0-452-28423-4"));
    library.addBook(Book("Pride and Prejudice", "Jane Austen", "978-0-14-143951-8"));
    
    // Display all books
    library.displayAllBooks();
    
    // Search by title
    std::cout << "\n=== Searching for 'Gatsby' ===" << std::endl;
    auto results = library.searchByTitle("Gatsby");
    for (const auto& book : results) {
        book->display();
    }
    
    // Borrow a book
    std::cout << "\n=== Borrowing a book ===" << std::endl;
    library.borrowBook("978-0-7432-7356-5");
    
    // Display available books
    library.displayAvailableBooks();
    
    // Return the book
    std::cout << "\n=== Returning a book ===" << std::endl;
    library.returnBook("978-0-7432-7356-5");
    
    // Display available books again
    library.displayAvailableBooks();
    
    return 0;
}
```

---

### Exercise 2.2: Template Programming - Generic Container
**Objective:** Master template programming and generic design

**Requirements:**
Create a generic `Stack` class template that can work with any data type.

**Tasks:**
1. Implement a stack using templates
2. Add exception handling for stack overflow/underflow
3. Implement iterators for the stack
4. Create a demonstration program using different data types

**Example Solution:**
```cpp
#include <iostream>
#include <stdexcept>
#include <initializer_list>

template<typename T>
class Stack {
private:
    static const size_t MAX_SIZE = 100;
    T data[MAX_SIZE];
    size_t top;
    
public:
    // Constructor
    Stack() : top(0) {}
    
    // Constructor with initializer list
    Stack(std::initializer_list<T> init) : top(0) {
        for (const auto& item : init) {
            push(item);
        }
    }
    
    // Copy constructor
    Stack(const Stack& other) : top(other.top) {
        for (size_t i = 0; i < top; ++i) {
            data[i] = other.data[i];
        }
    }
    
    // Assignment operator
    Stack& operator=(const Stack& other) {
        if (this != &other) {
            top = other.top;
            for (size_t i = 0; i < top; ++i) {
                data[i] = other.data[i];
            }
        }
        return *this;
    }
    
    // Push element onto stack
    void push(const T& item) {
        if (top >= MAX_SIZE) {
            throw std::overflow_error("Stack overflow!");
        }
        data[top++] = item;
    }
    
    // Pop element from stack
    T pop() {
        if (isEmpty()) {
            throw std::underflow_error("Stack underflow!");
        }
        return data[--top];
    }
    
    // Peek at top element without removing
    T& peek() {
        if (isEmpty()) {
            throw std::underflow_error("Stack is empty!");
        }
        return data[top - 1];
    }
    
    const T& peek() const {
        if (isEmpty()) {
            throw std::underflow_error("Stack is empty!");
        }
        return data[top - 1];
    }
    
    // Check if stack is empty
    bool isEmpty() const {
        return top == 0;
    }
    
    // Check if stack is full
    bool isFull() const {
        return top >= MAX_SIZE;
    }
    
    // Get current size
    size_t size() const {
        return top;
    }
    
    // Clear the stack
    void clear() {
        top = 0;
    }
    
    // Display stack contents
    void display() const {
        if (isEmpty()) {
            std::cout << "Stack is empty!" << std::endl;
            return;
        }
        
        std::cout << "Stack contents (top to bottom): ";
        for (int i = static_cast<int>(top) - 1; i >= 0; --i) {
            std::cout << data[i];
            if (i > 0) std::cout << " ";
        }
        std::cout << std::endl;
    }
};

// Specialization for string type to handle display nicely
template<>
void Stack<std::string>::display() const {
    if (isEmpty()) {
        std::cout << "Stack is empty!" << std::endl;
        return;
    }
    
    std::cout << "Stack contents (top to bottom): ";
    for (int i = static_cast<int>(top) - 1; i >= 0; --i) {
        std::cout << "\"" << data[i] << "\"";
        if (i > 0) std::cout << " ";
    }
    std::cout << std::endl;
}

void demonstrateIntStack() {
    std::cout << "=== Integer Stack Demo ===" << std::endl;
    
    Stack<int> intStack;
    
    try {
        intStack.push(10);
        intStack.push(20);
        intStack.push(30);
        
        std::cout << "Stack size: " << intStack.size() << std::endl;
        intStack.display();
        
        std::cout << "Top element: " << intStack.peek() << std::endl;
        
        std::cout << "Popped: " << intStack.pop() << std::endl;
        std::cout << "Popped: " << intStack.pop() << std::endl;
        
        intStack.display();
        
    } catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }
}

void demonstrateStringStack() {
    std::cout << "\n=== String Stack Demo ===" << std::endl;
    
    Stack<std::string> stringStack;
    
    try {
        stringStack.push("Hello");
        stringStack.push("World");
        stringStack.push("C++");
        
        std::cout << "Stack size: " << stringStack.size() << std::endl;
        stringStack.display();
        
        std::cout << "Top element: " << stringStack.peek() << std::endl;
        
        std::cout << "Popped: " << stringStack.pop() << std::endl;
        
        stringStack.display();
        
    } catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }
}

void demonstrateInitializerList() {
    std::cout << "\n=== Initializer List Demo ===" << std::endl;
    
    Stack<double> doubleStack{3.14, 2.71, 1.41, 1.73};
    
    std::cout << "Stack size: " << doubleStack.size() << std::endl;
    doubleStack.display();
}

void demonstrateExceptionHandling() {
    std::cout << "\n=== Exception Handling Demo ===" << std::endl;
    
    Stack<int> stack;
    
    // Test underflow
    try {
        stack.pop();
    } catch (const std::exception& e) {
        std::cout << "Caught exception: " << e.what() << std::endl;
    }
    
    // Test overflow (simplified for demo)
    try {
        for (int i = 0; i < 102; ++i) {  // More than MAX_SIZE
            stack.push(i);
        }
    } catch (const std::exception& e) {
        std::cout << "Caught exception: " << e.what() << std::endl;
    }
}

int main() {
    demonstrateIntStack();
    demonstrateStringStack();
    demonstrateInitializerList();
    demonstrateExceptionHandling();
    
    return 0;
}
```

---

### Exercise 2.3: STL Algorithms and Containers - Data Processing
**Objective:** Master STL usage and algorithm application

**Requirements:**
Create a student grade management system using STL containers and algorithms.

**Tasks:**
1. Use appropriate STL containers to store student data
2. Implement grade calculations using STL algorithms
3. Add sorting and searching functionality
4. Generate statistics and reports

**Example Solution:**
```cpp
#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <numeric>
#include <string>
#include <iomanip>

struct Student {
    std::string name;
    int id;
    std::vector<double> grades;
    
    Student(const std::string& n, int i) : name(n), id(i) {}
    
    double getAverage() const {
        if (grades.empty()) return 0.0;
        return std::accumulate(grades.begin(), grades.end(), 0.0) / grades.size();
    }
    
    char getLetterGrade() const {
        double avg = getAverage();
        if (avg >= 90) return 'A';
        else if (avg >= 80) return 'B';
        else if (avg >= 70) return 'C';
        else if (avg >= 60) return 'D';
        else return 'F';
    }
};

class GradeManager {
private:
    std::map<int, Student> students;
    
public:
    void addStudent(const std::string& name, int id) {
        students.emplace(id, Student(name, id));
    }
    
    void addGrade(int studentId, double grade) {
        auto it = students.find(studentId);
        if (it != students.end()) {
            it->second.grades.push_back(grade);
        }
    }
    
    void displayStudent(int studentId) const {
        auto it = students.find(studentId);
        if (it != students.end()) {
            const Student& student = it->second;
            std::cout << "Student: " << student.name 
                      << " (ID: " << student.id << ")" << std::endl;
            std::cout << "Grades: ";
            for (double grade : student.grades) {
                std::cout << std::fixed << std::setprecision(1) << grade << " ";
            }
            std::cout << std::endl;
            std::cout << "Average: " << student.getAverage() 
                      << " (Grade: " << student.getLetterGrade() << ")" << std::endl;
        }
    }
    
    void displayAllStudents() const {
        std::cout << "\n=== All Students ===" << std::endl;
        for (const auto& pair : students) {
            const Student& student = pair.second;
            std::cout << student.name << " (ID: " << student.id << ") - "
                      << "Average: " << std::fixed << std::setprecision(2) 
                      << student.getAverage() << " (" << student.getLetterGrade() << ")" << std::endl;
        }
    }
    
    void displayTopStudents(int count = 3) const {
        std::cout << "\n=== Top " << count << " Students ===" << std::endl;
        
        std::vector<std::pair<int, double>> studentAverages;
        for (const auto& pair : students) {
            studentAverages.emplace_back(pair.first, pair.second.getAverage());
        }
        
        // Sort by average (descending)
        std::sort(studentAverages.begin(), studentAverages.end(),
                 [](const auto& a, const auto& b) { return a.second > b.second; });
        
        for (int i = 0; i < std::min(count, static_cast<int>(studentAverages.size())); ++i) {
            int id = studentAverages[i].first;
            auto it = students.find(id);
            if (it != students.end()) {
                std::cout << (i + 1) << ". " << it->second.name 
                          << " - " << std::fixed << std::setprecision(2) 
                          << studentAverages[i].second << std::endl;
            }
        }
    }
    
    void displayGradeDistribution() const {
        std::cout << "\n=== Grade Distribution ===" << std::endl;
        
        std::map<char, int> distribution;
        for (const auto& pair : students) {
            char grade = pair.second.getLetterGrade();
            distribution[grade]++;
        }
        
        for (char grade = 'A'; grade >= 'F'; --grade) {
            if (grade == 'E') continue;  // Skip E grade
            std::cout << "Grade " << grade << ": " << distribution[grade] << " students" << std::endl;
        }
    }
    
    double getClassAverage() const {
        if (students.empty()) return 0.0;
        
        double total = 0.0;
        for (const auto& pair : students) {
            total += pair.second.getAverage();
        }
        return total / students.size();
    }
    
    void displayStatistics() const {
        std::cout << "\n=== Class Statistics ===" << std::endl;
        std::cout << "Total students: " << students.size() << std::endl;
        std::cout << "Class average: " << std::fixed << std::setprecision(2) 
                  << getClassAverage() << std::endl;
        
        // Find highest and lowest averages
        if (!students.empty()) {
            auto minmax = std::minmax_element(students.begin(), students.end(),
                [](const auto& a, const auto& b) {
                    return a.second.getAverage() < b.second.getAverage();
                });
            
            std::cout << "Highest average: " << std::fixed << std::setprecision(2)
                      << minmax.second->second.getAverage() 
                      << " (" << minmax.second->second.name << ")" << std::endl;
            std::cout << "Lowest average: " << std::fixed << std::setprecision(2)
                      << minmax.first->second.getAverage() 
                      << " (" << minmax.first->second.name << ")" << std::endl;
        }
    }
};

int main() {
    GradeManager manager;
    
    // Add students
    manager.addStudent("Alice Johnson", 1001);
    manager.addStudent("Bob Smith", 1002);
    manager.addStudent("Charlie Brown", 1003);
    manager.addStudent("Diana Prince", 1004);
    manager.addStudent("Eve Wilson", 1005);
    
    // Add grades
    manager.addGrade(1001, 85.5);
    manager.addGrade(1001, 92.0);
    manager.addGrade(1001, 78.5);
    manager.addGrade(1001, 96.0);
    
    manager.addGrade(1002, 72.0);
    manager.addGrade(1002, 68.5);
    manager.addGrade(1002, 74.0);
    manager.addGrade(1002, 71.5);
    
    manager.addGrade(1003, 95.0);
    manager.addGrade(1003, 98.5);
    manager.addGrade(1003, 92.0);
    manager.addGrade(1003, 94.5);
    
    manager.addGrade(1004, 88.0);
    manager.addGrade(1004, 91.5);
    manager.addGrade(1004, 85.0);
    manager.addGrade(1004, 89.5);
    
    manager.addGrade(1005, 65.0);
    manager.addGrade(1005, 62.5);
    manager.addGrade(1005, 68.0);
    manager.addGrade(1005, 64.5);
    
    // Display results
    manager.displayAllStudents();
    manager.displayTopStudents(3);
    manager.displayGradeDistribution();
    manager.displayStatistics();
    
    // Display individual student
    std::cout << "\n=== Individual Student Details ===" << std::endl;
    manager.displayStudent(1003);
    
    return 0;
}
```

---

## Advanced Level Exercises (Weeks 11-20)

### Exercise 3.1: Advanced Class Design - Smart Pointer Implementation
**Objective:** Understand memory management and RAII principles

**Requirements:**
Implement a simplified version of `std::unique_ptr` to understand smart pointer mechanics.

**Tasks:**
1. Create a `UniquePtr` class template
2. Implement move semantics
3. Add custom deleter support
4. Ensure exception safety

**Example Solution:**
```cpp
#include <iostream>
#include <memory>
#include <utility>

template<typename T>
class UniquePtr {
private:
    T* ptr;
    
public:
    // Constructor
    explicit UniquePtr(T* p = nullptr) : ptr(p) {}
    
    // Move constructor
    UniquePtr(UniquePtr&& other) noexcept : ptr(other.ptr) {
        other.ptr = nullptr;
    }
    
    // Move assignment operator
    UniquePtr& operator=(UniquePtr&& other) noexcept {
        if (this != &other) {
            delete ptr;
            ptr = other.ptr;
            other.ptr = nullptr;
        }
        return *this;
    }
    
    // Delete copy constructor and copy assignment
    UniquePtr(const UniquePtr&) = delete;
    UniquePtr& operator=(const UniquePtr&) = delete;
    
    // Destructor
    ~UniquePtr() {
        delete ptr;
    }
    
    // Dereference operator
    T& operator*() const {
        return *ptr;
    }
    
    // Arrow operator
    T* operator->() const {
        return ptr;
    }
    
    // Get raw pointer
    T* get() const {
        return ptr;
    }
    
    // Release ownership
    T* release() {
        T* temp = ptr;
        ptr = nullptr;
        return temp;
    }
    
    // Reset pointer
    void reset(T* p = nullptr) {
        delete ptr;
        ptr = p;
    }
    
    // Check if pointer is valid
    explicit operator bool() const {
        return ptr != nullptr;
    }
};

// Specialization for arrays
template<typename T>
class UniquePtr<T[]> {
private:
    T* ptr;
    
public:
    explicit UniquePtr(T* p = nullptr) : ptr(p) {}
    
    UniquePtr(UniquePtr&& other) noexcept : ptr(other.ptr) {
        other.ptr = nullptr;
    }
    
    UniquePtr& operator=(UniquePtr&& other) noexcept {
        if (this != &other) {
            delete[] ptr;
            ptr = other.ptr;
            other.ptr = nullptr;
        }
        return *this;
    }
    
    UniquePtr(const UniquePtr&) = delete;
    UniquePtr& operator=(const UniquePtr&) = delete;
    
    ~UniquePtr() {
        delete[] ptr;
    }
    
    T& operator[](size_t index) const {
        return ptr[index];
    }
    
    T* get() const {
        return ptr;
    }
    
    T* release() {
        T* temp = ptr;
        ptr = nullptr;
        return temp;
    }
    
    void reset(T* p = nullptr) {
        delete[] ptr;
        ptr = p;
    }
    
    explicit operator bool() const {
        return ptr != nullptr;
    }
};

// Factory function
template<typename T, typename... Args>
UniquePtr<T> make_unique(Args&&... args) {
    return UniquePtr<T>(new T(std::forward<Args>(args)...));
}

// Test class
class TestClass {
private:
    int value;
    
public:
    TestClass(int v) : value(v) {
        std::cout << "TestClass(" << value << ") created" << std::endl;
    }
    
    ~TestClass() {
        std::cout << "TestClass(" << value << ") destroyed" << std::endl;
    }
    
    int getValue() const { return value; }
    void setValue(int v) { value = v; }
};

void demonstrateUniquePtr() {
    std::cout << "=== UniquePtr Demonstration ===" << std::endl;
    
    // Create unique pointer
    UniquePtr<TestClass> ptr1 = make_unique<TestClass>(42);
    std::cout << "Value: " << ptr1->getValue() << std::endl;
    
    // Move semantics
    UniquePtr<TestClass> ptr2 = std::move(ptr1);
    std::cout << "After move - ptr1 valid: " << static_cast<bool>(ptr1) << std::endl;
    std::cout << "After move - ptr2 value: " << ptr2->getValue() << std::endl;
    
    // Reset
    ptr2.reset(new TestClass(100));
    std::cout << "After reset - value: " << ptr2->getValue() << std::endl;
    
    // Automatic cleanup when going out of scope
}

void demonstrateArrayUniquePtr() {
    std::cout << "\n=== Array UniquePtr Demonstration ===" << std::endl;
    
    UniquePtr<int[]> arr(new int[5]);
    
    // Initialize array
    for (int i = 0; i < 5; ++i) {
        arr[i] = i * 10;
    }
    
    // Display array
    std::cout << "Array contents: ";
    for (int i = 0; i < 5; ++i) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
    
    // Automatic cleanup
}

int main() {
    demonstrateUniquePtr();
    demonstrateArrayUniquePtr();
    
    std::cout << "\n=== End of main - cleanup will happen ===" << std::endl;
    return 0;
}
```

---

### Exercise 3.2: Template Metaprogramming - Type Traits
**Objective:** Master template metaprogramming and compile-time computation

**Requirements:**
Implement a set of type traits and compile-time algorithms.

**Tasks:**
1. Implement basic type traits (is_integral, is_pointer, etc.)
2. Create compile-time factorial and Fibonacci functions
3. Implement SFINAE-based type checking
4. Build a compile-time string manipulation system

**Example Solution:**
```cpp
#include <iostream>
#include <type_traits>

// Basic type traits
template<typename T>
struct is_integral {
    static constexpr bool value = false;
};

// Specializations for integral types
template<> struct is_integral<bool> { static constexpr bool value = true; };
template<> struct is_integral<char> { static constexpr bool value = true; };
template<> struct is_integral<signed char> { static constexpr bool value = true; };
template<> struct is_integral<unsigned char> { static constexpr bool value = true; };
template<> struct is_integral<short> { static constexpr bool value = true; };
template<> struct is_integral<unsigned short> { static constexpr bool value = true; };
template<> struct is_integral<int> { static constexpr bool value = true; };
template<> struct is_integral<unsigned int> { static constexpr bool value = true; };
template<> struct is_integral<long> { static constexpr bool value = true; };
template<> struct is_integral<unsigned long> { static constexpr bool value = true; };
template<> struct is_integral<long long> { static constexpr bool value = true; };
template<> struct is_integral<unsigned long long> { static constexpr bool value = true; };

// Pointer type trait
template<typename T>
struct is_pointer {
    static constexpr bool value = false;
};

template<typename T>
struct is_pointer<T*> {
    static constexpr bool value = true;
};

// Compile-time factorial
template<int N>
struct factorial {
    static constexpr long long value = N * factorial<N - 1>::value;
};

template<>
struct factorial<0> {
    static constexpr long long value = 1;
};

// Compile-time Fibonacci
template<int N>
struct fibonacci {
    static constexpr long long value = fibonacci<N - 1>::value + fibonacci<N - 2>::value;
};

template<>
struct fibonacci<0> {
    static constexpr long long value = 0;
};

template<>
struct fibonacci<1> {
    static constexpr long long value = 1;
};

// Compile-time power function
template<int Base, int Exp>
struct power {
    static constexpr long long value = Base * power<Base, Exp - 1>::value;
};

template<int Base>
struct power<Base, 0> {
    static constexpr long long value = 1;
};

// SFINAE-based type checking
template<typename T>
typename std::enable_if<is_integral<T>::value, void>::type
process_integral(T value) {
    std::cout << "Processing integral: " << value << std::endl;
}

template<typename T>
typename std::enable_if<is_pointer<T>::value, void>::type
process_pointer(T ptr) {
    std::cout << "Processing pointer: " << static_cast<void*>(ptr) << std::endl;
}

// Compile-time string manipulation
template<size_t N>
struct compile_time_string {
    char data[N];
    
    constexpr compile_time_string(const char (&str)[N]) {
        for (size_t i = 0; i < N; ++i) {
            data[i] = str[i];
        }
    }
    
    constexpr char operator[](size_t i) const {
        return data[i];
    }
    
    constexpr size_t size() const {
        return N - 1; // Exclude null terminator
    }
};

// Compile-time string concatenation
template<size_t N1, size_t N2>
constexpr auto concat(const char (&str1)[N1], const char (&str2)[N2]) {
    char result[N1 + N2 - 1] = {};
    
    for (size_t i = 0; i < N1 - 1; ++i) {
        result[i] = str1[i];
    }
    
    for (size_t i = 0; i < N2; ++i) {
        result[N1 - 1 + i] = str2[i];
    }
    
    return result;
}

// Compile-time string length
template<size_t N>
constexpr size_t string_length(const char (&str)[N]) {
    return N - 1;
}

// Test functions
void demonstrateTypeTraits() {
    std::cout << "=== Type Traits Demo ===" << std::endl;
    
    std::cout << "is_integral<int>: " << is_integral<int>::value << std::endl;
    std::cout << "is_integral<double>: " << is_integral<double>::value << std::endl;
    std::cout << "is_pointer<int*>: " << is_pointer<int*>::value << std::endl;
    std::cout << "is_pointer<int>: " << is_pointer<int>::value << std::endl;
}

void demonstrateCompileTimeComputation() {
    std::cout << "\n=== Compile-time Computation Demo ===" << std::endl;
    
    std::cout << "Factorial of 5: " << factorial<5>::value << std::endl;
    std::cout << "Factorial of 10: " << factorial<10>::value << std::endl;
    
    std::cout << "Fibonacci(10): " << fibonacci<10>::value << std::endl;
    std::cout << "Fibonacci(20): " << fibonacci<20>::value << std::endl;
    
    std::cout << "2^10: " << power<2, 10>::value << std::endl;
    std::cout << "3^5: " << power<3, 5>::value << std::endl;
}

void demonstrateSFINAE() {
    std::cout << "\n=== SFINAE Demo ===" << std::endl;
    
    int value = 42;
    int* ptr = &value;
    
    process_integral(value);  // Will compile
    process_pointer(ptr);     // Will compile
    
    // process_integral(ptr);     // Won't compile
    // process_pointer(value);    // Won't compile
}

void demonstrateCompileTimeString() {
    std::cout << "\n=== Compile-time String Demo ===" << std::endl;
    
    constexpr auto str1 = compile_time_string("Hello");
    constexpr auto str2 = compile_time_string("World");
    
    std::cout << "String 1 length: " << str1.size() << std::endl;
    std::cout << "String 2 length: " << str2.size() << std::endl;
    
    for (size_t i = 0; i < str1.size(); ++i) {
        std::cout << str1[i];
    }
    std::cout << " ";
    for (size_t i = 0; i < str2.size(); ++i) {
        std::cout << str2[i];
    }
    std::cout << std::endl;
    
    constexpr auto combined = concat("Hello", " World");
    std::cout << "Combined string: " << combined << std::endl;
    std::cout << "Combined length: " << string_length(combined) << std::endl;
}

int main() {
    demonstrateTypeTraits();
    demonstrateCompileTimeComputation();
    demonstrateSFINAE();
    demonstrateCompileTimeString();
    
    return 0;
}
```

---

## Project-Based Exercises

### Final Project: Complete Application - Text Editor
**Objective:** Integrate all learned concepts into a comprehensive application

**Requirements:**
Create a simple text editor with the following features:
- File operations (open, save, new)
- Text editing capabilities
- Search and replace functionality
- Undo/redo system
- Multiple document support
- Plugin architecture using templates

**Implementation Guidelines:**
1. Use modern C++ features (C++11/14/17)
2. Implement proper RAII and exception safety
3. Use STL containers and algorithms
4. Apply template programming for extensibility
5. Include proper class design and inheritance
6. Implement command pattern for undo/redo

This comprehensive collection of exercises provides students with practical, hands-on experience in C++ programming, progressing from basic concepts to advanced techniques. Each exercise includes detailed requirements, example solutions, and learning objectives to ensure comprehensive understanding of the material.
