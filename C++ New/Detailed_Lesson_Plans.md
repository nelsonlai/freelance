# Detailed C++ Lesson Plans

## Week 1: Introduction and C++ Basics

### Lesson 1.1: C++ Philosophy and Modern Programming (90 minutes)

**Learning Objectives:**
- Understand C++ as a systems programming language
- Learn about modern C++ (C++11/14/17/20) features
- Set up development environment

**Activities:**

1. **Lecture (30 minutes)**
   - C++ history and evolution
   - Modern C++ vs legacy C++
   - Zero-cost abstractions principle
   - RAII (Resource Acquisition Is Initialization)

2. **Environment Setup (30 minutes)**
   - Install compiler (GCC, Clang, or MSVC)
   - Set up IDE (Visual Studio, CLion, or VS Code)
   - Configure build system (CMake basics)
   - Test installation with simple program

3. **Hands-on Practice (30 minutes)**
   ```cpp
   // hello_modern.cpp
   #include <iostream>
   #include <string>
   
   int main() {
       std::string name;
       std::cout << "Enter your name: ";
       std::getline(std::cin, name);
       std::cout << "Hello, " << name << "!" << std::endl;
       return 0;
   }
   ```

**Assessment:** Environment setup verification and first program compilation

---

### Lesson 1.2: Basic Program Structure and Variables (90 minutes)

**Learning Objectives:**
- Understand C++ program structure
- Learn fundamental data types
- Master variable declaration and initialization

**Activities:**

1. **Lecture (25 minutes)**
   - Program structure (includes, main function)
   - Fundamental types: int, double, char, bool
   - Variable declaration vs initialization
   - auto keyword introduction

2. **Demonstration (25 minutes)**
   ```cpp
   #include <iostream>
   #include <typeinfo>
   
   int main() {
       // Traditional declaration
       int age = 25;
       double height = 5.9;
       char grade = 'A';
       bool isStudent = true;
       
       // Modern initialization
       auto name = std::string{"Alice"};
       auto salary = 50000.0;  // double
       auto count = 10;        // int
       
       // Display types
       std::cout << "Type of name: " << typeid(name).name() << std::endl;
       std::cout << "Type of salary: " << typeid(salary).name() << std::endl;
       
       return 0;
   }
   ```

3. **Practice Session (40 minutes)**
   - Create variables for personal information
   - Practice different initialization methods
   - Experiment with auto keyword

**Assessment:** Variable declaration and type quiz

---

### Lesson 1.3: Control Structures (90 minutes)

**Learning Objectives:**
- Master if/else statements
- Learn loop constructs
- Understand switch statements

**Activities:**

1. **Lecture (30 minutes)**
   - Conditional statements (if, else if, else)
   - Loop constructs (for, while, do-while)
   - Switch statements and break/continue
   - Range-based for loops (C++11)

2. **Interactive Coding (60 minutes)**
   ```cpp
   #include <iostream>
   #include <vector>
   
   int main() {
       // Grade calculator
       int score;
       std::cout << "Enter your score (0-100): ";
       std::cin >> score;
       
       if (score >= 90) {
           std::cout << "Grade: A" << std::endl;
       } else if (score >= 80) {
           std::cout << "Grade: B" << std::endl;
       } else if (score >= 70) {
           std::cout << "Grade: C" << std::endl;
       } else if (score >= 60) {
           std::cout << "Grade: D" << std::endl;
       } else {
           std::cout << "Grade: F" << std::endl;
       }
       
       // Loop examples
       std::vector<int> numbers = {1, 2, 3, 4, 5};
       
       // Traditional for loop
       for (size_t i = 0; i < numbers.size(); ++i) {
           std::cout << numbers[i] << " ";
       }
       std::cout << std::endl;
       
       // Range-based for loop (C++11)
       for (const auto& num : numbers) {
           std::cout << num << " ";
       }
       std::cout << std::endl;
       
       return 0;
   }
   ```

**Assessment:** Control structure programming exercise

---

### Lesson 1.4: Functions and Basic I/O (90 minutes)

**Learning Objectives:**
- Learn function declaration and definition
- Master parameter passing
- Understand basic I/O operations

**Activities:**

1. **Lecture (30 minutes)**
   - Function syntax and structure
   - Parameter passing (by value, by reference)
   - Return types and return statements
   - Function prototypes

2. **Coding Practice (60 minutes)**
   ```cpp
   #include <iostream>
   #include <string>
   
   // Function declarations
   int add(int a, int b);
   void greet(const std::string& name);
   double calculateArea(double length, double width);
   
   int main() {
       // Input/Output
       std::string userName;
       std::cout << "Enter your name: ";
       std::getline(std::cin, userName);
       
       greet(userName);
       
       // Function calls
       int sum = add(10, 20);
       std::cout << "Sum: " << sum << std::endl;
       
       double area = calculateArea(5.5, 3.2);
       std::cout << "Area: " << area << std::endl;
       
       return 0;
   }
   
   // Function definitions
   int add(int a, int b) {
       return a + b;
   }
   
   void greet(const std::string& name) {
       std::cout << "Hello, " << name << "!" << std::endl;
   }
   
   double calculateArea(double length, double width) {
       return length * width;
   }
   ```

**Assessment:** Function design and implementation exercise

---

## Week 2: C++ Abstraction Mechanisms

### Lesson 2.1: Classes and Objects (90 minutes)

**Learning Objectives:**
- Understand object-oriented programming concepts
- Learn class definition and object creation
- Master access specifiers

**Activities:**

1. **Lecture (35 minutes)**
   - OOP principles (encapsulation, inheritance, polymorphism)
   - Class vs object
   - Member variables and functions
   - Access specifiers (public, private, protected)

2. **Hands-on Implementation (55 minutes)**
   ```cpp
   #include <iostream>
   #include <string>
   
   class BankAccount {
   private:
       std::string accountNumber;
       double balance;
       
   public:
       // Constructor
       BankAccount(const std::string& accNum, double initialBalance) 
           : accountNumber(accNum), balance(initialBalance) {}
       
       // Member functions
       void deposit(double amount) {
           if (amount > 0) {
               balance += amount;
               std::cout << "Deposited $" << amount << std::endl;
           }
       }
       
       bool withdraw(double amount) {
           if (amount > 0 && amount <= balance) {
               balance -= amount;
               std::cout << "Withdrew $" << amount << std::endl;
               return true;
           }
           std::cout << "Insufficient funds!" << std::endl;
           return false;
       }
       
       double getBalance() const {
           return balance;
       }
       
       const std::string& getAccountNumber() const {
           return accountNumber;
       }
   };
   
   int main() {
       BankAccount account("12345", 1000.0);
       
       std::cout << "Account: " << account.getAccountNumber() << std::endl;
       std::cout << "Initial balance: $" << account.getBalance() << std::endl;
       
       account.deposit(500.0);
       account.withdraw(200.0);
       
       std::cout << "Final balance: $" << account.getBalance() << std::endl;
       
       return 0;
   }
   ```

**Assessment:** Class design and implementation project

---

### Lesson 2.2: Constructors and Destructors (90 minutes)

**Learning Objectives:**
- Master constructor types and usage
- Understand destructor behavior
- Learn initialization lists

**Activities:**

1. **Lecture (30 minutes)**
   - Default constructors
   - Parameterized constructors
   - Copy constructors
   - Destructors and RAII
   - Initialization lists

2. **Implementation Practice (60 minutes)**
   ```cpp
   #include <iostream>
   #include <string>
   
   class Student {
   private:
       std::string name;
       int studentId;
       double gpa;
       
   public:
       // Default constructor
       Student() : name("Unknown"), studentId(0), gpa(0.0) {
           std::cout << "Default constructor called" << std::endl;
       }
       
       // Parameterized constructor
       Student(const std::string& n, int id, double g) 
           : name(n), studentId(id), gpa(g) {
           std::cout << "Parameterized constructor called for " << name << std::endl;
       }
       
       // Copy constructor
       Student(const Student& other) 
           : name(other.name), studentId(other.studentId), gpa(other.gpa) {
           std::cout << "Copy constructor called for " << name << std::endl;
       }
       
       // Destructor
       ~Student() {
           std::cout << "Destructor called for " << name << std::endl;
       }
       
       // Getters
       const std::string& getName() const { return name; }
       int getStudentId() const { return studentId; }
       double getGpa() const { return gpa; }
       
       // Setters
       void setName(const std::string& n) { name = n; }
       void setStudentId(int id) { studentId = id; }
       void setGpa(double g) { gpa = g; }
   };
   
   int main() {
       Student s1;  // Default constructor
       Student s2("Alice", 12345, 3.8);  // Parameterized constructor
       Student s3 = s2;  // Copy constructor
       
       std::cout << "Student: " << s2.getName() 
                 << ", ID: " << s2.getStudentId() 
                 << ", GPA: " << s2.getGpa() << std::endl;
       
       return 0;  // Destructors called automatically
   }
   ```

**Assessment:** Constructor/destructor implementation exercise

---

### Lesson 2.3: Introduction to Templates (90 minutes)

**Learning Objectives:**
- Understand generic programming concepts
- Learn function templates
- Introduction to class templates

**Activities:**

1. **Lecture (35 minutes)**
   - Generic programming philosophy
   - Template syntax and instantiation
   - Template parameter deduction
   - Type safety with templates

2. **Template Implementation (55 minutes)**
   ```cpp
   #include <iostream>
   #include <string>
   
   // Function template
   template<typename T>
   T maximum(T a, T b) {
       return (a > b) ? a : b;
   }
   
   // Function template with multiple parameters
   template<typename T, typename U>
   void printPair(T first, U second) {
       std::cout << "(" << first << ", " << second << ")" << std::endl;
   }
   
   // Simple class template
   template<typename T>
   class Stack {
   private:
       static const size_t MAX_SIZE = 100;
       T data[MAX_SIZE];
       size_t top;
       
   public:
       Stack() : top(0) {}
       
       void push(const T& item) {
           if (top < MAX_SIZE) {
               data[top++] = item;
           }
       }
       
       bool pop(T& item) {
           if (top > 0) {
               item = data[--top];
               return true;
           }
           return false;
       }
       
       bool isEmpty() const {
           return top == 0;
       }
       
       size_t size() const {
           return top;
       }
   };
   
   int main() {
       // Function template usage
       std::cout << "Max of 10 and 20: " << maximum(10, 20) << std::endl;
       std::cout << "Max of 3.5 and 2.1: " << maximum(3.5, 2.1) << std::endl;
       std::cout << "Max of 'a' and 'z': " << maximum('a', 'z') << std::endl;
       
       printPair(42, "Hello");
       printPair(3.14, true);
       
       // Class template usage
       Stack<int> intStack;
       intStack.push(10);
       intStack.push(20);
       intStack.push(30);
       
       int value;
       while (intStack.pop(value)) {
           std::cout << "Popped: " << value << std::endl;
       }
       
       return 0;
   }
   ```

**Assessment:** Template programming exercise

---

## Week 3: Containers and Algorithms

### Lesson 3.1: STL Containers - Sequential (90 minutes)

**Learning Objectives:**
- Learn vector, list, and deque
- Understand container selection criteria
- Master container operations

**Activities:**

1. **Lecture (30 minutes)**
   - STL philosophy and design
   - Sequential containers overview
   - Container performance characteristics
   - Iterator concepts

2. **Container Practice (60 minutes)**
   ```cpp
   #include <iostream>
   #include <vector>
   #include <list>
   #include <deque>
   #include <algorithm>
   
   void demonstrateVector() {
       std::cout << "\n=== Vector Demo ===" << std::endl;
       std::vector<int> vec;
       
       // Insert elements
       for (int i = 1; i <= 5; ++i) {
           vec.push_back(i * 10);
       }
       
       // Access elements
       std::cout << "Elements: ";
       for (const auto& elem : vec) {
           std::cout << elem << " ";
       }
       std::cout << std::endl;
       
       // Random access
       std::cout << "Element at index 2: " << vec[2] << std::endl;
       std::cout << "Size: " << vec.size() << std::endl;
       std::cout << "Capacity: " << vec.capacity() << std::endl;
       
       // Insert in middle
       vec.insert(vec.begin() + 2, 99);
       std::cout << "After insert: ";
       for (const auto& elem : vec) {
           std::cout << elem << " ";
       }
       std::cout << std::endl;
   }
   
   void demonstrateList() {
       std::cout << "\n=== List Demo ===" << std::endl;
       std::list<int> lst;
       
       // Insert elements
       for (int i = 1; i <= 5; ++i) {
           lst.push_back(i * 10);
       }
       
       std::cout << "Elements: ";
       for (const auto& elem : lst) {
           std::cout << elem << " ";
       }
       std::cout << std::endl;
       
       // Insert in middle (efficient)
       auto it = lst.begin();
       std::advance(it, 2);
       lst.insert(it, 99);
       
       std::cout << "After insert: ";
       for (const auto& elem : lst) {
           std::cout << elem << " ";
       }
       std::cout << std::endl;
       
       // Remove elements
       lst.remove(30);
       std::cout << "After remove 30: ";
       for (const auto& elem : lst) {
           std::cout << elem << " ";
       }
       std::cout << std::endl;
   }
   
   int main() {
       demonstrateVector();
       demonstrateList();
       
       return 0;
   }
   ```

**Assessment:** Container usage and performance analysis

---

### Lesson 3.2: STL Containers - Associative (90 minutes)

**Learning Objectives:**
- Learn set, map, and their unordered versions
- Understand associative container operations
- Master key-value pair handling

**Activities:**

1. **Lecture (30 minutes)**
   - Associative containers overview
   - Ordered vs unordered containers
   - Key requirements and constraints
   - Performance characteristics

2. **Associative Container Practice (60 minutes)**
   ```cpp
   #include <iostream>
   #include <set>
   #include <map>
   #include <unordered_set>
   #include <unordered_map>
   #include <string>
   
   void demonstrateSet() {
       std::cout << "\n=== Set Demo ===" << std::endl;
       std::set<int> s;
       
       // Insert elements
       s.insert(30);
       s.insert(10);
       s.insert(50);
       s.insert(20);
       s.insert(40);
       
       std::cout << "Set elements (sorted): ";
       for (const auto& elem : s) {
           std::cout << elem << " ";
       }
       std::cout << std::endl;
       
       // Search
       auto it = s.find(30);
       if (it != s.end()) {
           std::cout << "Found 30 in set" << std::endl;
       }
       
       // Count
       std::cout << "Count of 20: " << s.count(20) << std::endl;
   }
   
   void demonstrateMap() {
       std::cout << "\n=== Map Demo ===" << std::endl;
       std::map<std::string, int> grades;
       
       // Insert key-value pairs
       grades["Alice"] = 95;
       grades["Bob"] = 87;
       grades["Charlie"] = 92;
       grades["Diana"] = 78;
       
       std::cout << "Student grades:" << std::endl;
       for (const auto& pair : grades) {
           std::cout << pair.first << ": " << pair.second << std::endl;
       }
       
       // Access elements
       std::cout << "Alice's grade: " << grades["Alice"] << std::endl;
       
       // Check if key exists
       if (grades.find("Eve") == grades.end()) {
           std::cout << "Eve not found in grades" << std::endl;
       }
       
       // Update grade
       grades["Bob"] = 89;
       std::cout << "Bob's updated grade: " << grades["Bob"] << std::endl;
   }
   
   void demonstrateUnorderedContainers() {
       std::cout << "\n=== Unordered Containers Demo ===" << std::endl;
       std::unordered_map<std::string, std::string> phoneBook;
       
       phoneBook["Alice"] = "555-1234";
       phoneBook["Bob"] = "555-5678";
       phoneBook["Charlie"] = "555-9012";
       
       std::cout << "Phone book:" << std::endl;
       for (const auto& pair : phoneBook) {
           std::cout << pair.first << ": " << pair.second << std::endl;
       }
       
       // Lookup
       std::cout << "Alice's phone: " << phoneBook["Alice"] << std::endl;
   }
   
   int main() {
       demonstrateSet();
       demonstrateMap();
       demonstrateUnorderedContainers();
       
       return 0;
   }
   ```

**Assessment:** Associative container implementation project

---

### Lesson 3.3: STL Algorithms (90 minutes)

**Learning Objectives:**
- Master common STL algorithms
- Understand algorithm complexity
- Learn to use custom predicates

**Activities:**

1. **Lecture (30 minutes)**
   - Algorithm categories (non-modifying, modifying, sorting)
   - Iterator requirements
   - Algorithm complexity notation
   - Custom predicates and functors

2. **Algorithm Practice (60 minutes)**
   ```cpp
   #include <iostream>
   #include <vector>
   #include <algorithm>
   #include <numeric>
   #include <functional>
   
   void demonstrateNonModifyingAlgorithms() {
       std::cout << "\n=== Non-Modifying Algorithms ===" << std::endl;
       std::vector<int> vec = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
       
       // Find
       auto it = std::find(vec.begin(), vec.end(), 5);
       if (it != vec.end()) {
           std::cout << "Found 5 at position: " 
                     << std::distance(vec.begin(), it) << std::endl;
       }
       
       // Count
       std::cout << "Count of even numbers: " 
                 << std::count_if(vec.begin(), vec.end(), 
                     [](int n) { return n % 2 == 0; }) << std::endl;
       
       // Accumulate
       int sum = std::accumulate(vec.begin(), vec.end(), 0);
       std::cout << "Sum: " << sum << std::endl;
       
       // All of
       bool allPositive = std::all_of(vec.begin(), vec.end(), 
                                     [](int n) { return n > 0; });
       std::cout << "All positive: " << (allPositive ? "Yes" : "No") << std::endl;
   }
   
   void demonstrateModifyingAlgorithms() {
       std::cout << "\n=== Modifying Algorithms ===" << std::endl;
       std::vector<int> vec = {3, 1, 4, 1, 5, 9, 2, 6};
       
       std::cout << "Original: ";
       for (const auto& elem : vec) {
           std::cout << elem << " ";
       }
       std::cout << std::endl;
       
       // Sort
       std::sort(vec.begin(), vec.end());
       std::cout << "Sorted: ";
       for (const auto& elem : vec) {
           std::cout << elem << " ";
       }
       std::cout << std::endl;
       
       // Reverse
       std::reverse(vec.begin(), vec.end());
       std::cout << "Reversed: ";
       for (const auto& elem : vec) {
           std::cout << elem << " ";
       }
       std::cout << std::endl;
       
       // Transform
       std::vector<int> doubled(vec.size());
       std::transform(vec.begin(), vec.end(), doubled.begin(),
                     [](int n) { return n * 2; });
       std::cout << "Doubled: ";
       for (const auto& elem : doubled) {
           std::cout << elem << " ";
       }
       std::cout << std::endl;
   }
   
   void demonstrateSearchingAlgorithms() {
       std::cout << "\n=== Searching Algorithms ===" << std::endl;
       std::vector<int> vec = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
       
       // Binary search (requires sorted data)
       bool found = std::binary_search(vec.begin(), vec.end(), 5);
       std::cout << "5 found: " << (found ? "Yes" : "No") << std::endl;
       
       // Lower bound
       auto lb = std::lower_bound(vec.begin(), vec.end(), 5);
       std::cout << "Lower bound of 5 at: " 
                 << std::distance(vec.begin(), lb) << std::endl;
       
       // Upper bound
       auto ub = std::upper_bound(vec.begin(), vec.end(), 5);
       std::cout << "Upper bound of 5 at: " 
                 << std::distance(vec.begin(), ub) << std::endl;
   }
   
   int main() {
       demonstrateNonModifyingAlgorithms();
       demonstrateModifyingAlgorithms();
       demonstrateSearchingAlgorithms();
       
       return 0;
   }
   ```

**Assessment:** Algorithm implementation and efficiency analysis

---

## Week 4: Concurrency and Utilities

### Lesson 4.1: Basic Concurrency with std::thread (90 minutes)

**Learning Objectives:**
- Understand threading concepts
- Learn std::thread usage
- Master basic synchronization

**Activities:**

1. **Lecture (35 minutes)**
   - Concurrency vs parallelism
   - Thread creation and management
   - Race conditions and data races
   - Basic synchronization primitives

2. **Threading Practice (55 minutes)**
   ```cpp
   #include <iostream>
   #include <thread>
   #include <vector>
   #include <chrono>
   #include <mutex>
   
   std::mutex printMutex;  // For safe printing
   
   void workerFunction(int id, int iterations) {
       for (int i = 0; i < iterations; ++i) {
           {
               std::lock_guard<std::mutex> lock(printMutex);
               std::cout << "Thread " << id << " iteration " << i << std::endl;
           }
           std::this_thread::sleep_for(std::chrono::milliseconds(100));
       }
   }
   
   void demonstrateBasicThreading() {
       std::cout << "=== Basic Threading Demo ===" << std::endl;
       
       std::vector<std::thread> threads;
       
       // Create multiple threads
       for (int i = 0; i < 3; ++i) {
           threads.emplace_back(workerFunction, i, 3);
       }
       
       // Wait for all threads to complete
       for (auto& t : threads) {
           t.join();
       }
       
       std::cout << "All threads completed!" << std::endl;
   }
   
   void demonstrateAsync() {
       std::cout << "\n=== Async Demo ===" << std::endl;
       
       auto future1 = std::async(std::launch::async, []() {
           std::this_thread::sleep_for(std::chrono::seconds(1));
           return 42;
       });
       
       auto future2 = std::async(std::launch::async, []() {
           std::this_thread::sleep_for(std::chrono::seconds(1));
           return 84;
       });
       
       // Do other work while threads are running
       std::cout << "Doing other work..." << std::endl;
       
       // Get results
       int result1 = future1.get();
       int result2 = future2.get();
       
       std::cout << "Result 1: " << result1 << std::endl;
       std::cout << "Result 2: " << result2 << std::endl;
   }
   
   int main() {
       demonstrateBasicThreading();
       demonstrateAsync();
       
       return 0;
   }
   ```

**Assessment:** Multi-threaded programming exercise

---

### Lesson 4.2: Smart Pointers and Modern Utilities (90 minutes)

**Learning Objectives:**
- Master smart pointer usage
- Learn RAII principles
- Understand modern C++ utilities

**Activities:**

1. **Lecture (30 minutes)**
   - Memory management problems
   - RAII (Resource Acquisition Is Initialization)
   - Smart pointer types (unique_ptr, shared_ptr, weak_ptr)
   - Lambda expressions

2. **Smart Pointer Practice (60 minutes)**
   ```cpp
   #include <iostream>
   #include <memory>
   #include <vector>
   #include <functional>
   
   class Resource {
   private:
       std::string name;
       
   public:
       Resource(const std::string& n) : name(n) {
           std::cout << "Resource '" << name << "' created" << std::endl;
       }
       
       ~Resource() {
           std::cout << "Resource '" << name << "' destroyed" << std::endl;
       }
       
       void use() {
           std::cout << "Using resource '" << name << "'" << std::endl;
       }
   };
   
   void demonstrateUniquePtr() {
       std::cout << "\n=== Unique Pointer Demo ===" << std::endl;
       
       // Create unique pointer
       std::unique_ptr<Resource> ptr = std::make_unique<Resource>("Unique Resource");
       ptr->use();
       
       // Transfer ownership
       std::unique_ptr<Resource> ptr2 = std::move(ptr);
       if (ptr == nullptr) {
           std::cout << "Original pointer is now null" << std::endl;
       }
       ptr2->use();
       
       // Automatic cleanup when ptr2 goes out of scope
   }
   
   void demonstrateSharedPtr() {
       std::cout << "\n=== Shared Pointer Demo ===" << std::endl;
       
       std::shared_ptr<Resource> ptr1 = std::make_shared<Resource>("Shared Resource");
       std::cout << "Reference count: " << ptr1.use_count() << std::endl;
       
       {
           std::shared_ptr<Resource> ptr2 = ptr1;
           std::cout << "Reference count: " << ptr1.use_count() << std::endl;
           ptr2->use();
       }
       
       std::cout << "Reference count: " << ptr1.use_count() << std::endl;
       ptr1->use();
       
       // Automatic cleanup when last shared_ptr is destroyed
   }
   
   void demonstrateLambdaExpressions() {
       std::cout << "\n=== Lambda Expressions Demo ===" << std::endl;
       
       std::vector<int> numbers = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
       
       // Lambda with capture
       int threshold = 5;
       auto isGreaterThan = [threshold](int n) { return n > threshold; };
       
       std::cout << "Numbers greater than " << threshold << ": ";
       for (const auto& num : numbers) {
           if (isGreaterThan(num)) {
               std::cout << num << " ";
           }
       }
       std::cout << std::endl;
       
       // Lambda with mutable capture
       auto counter = [count = 0]() mutable { return ++count; };
       std::cout << "Counter: " << counter() << std::endl;
       std::cout << "Counter: " << counter() << std::endl;
       std::cout << "Counter: " << counter() << std::endl;
       
       // Lambda with algorithm
       auto sum = std::accumulate(numbers.begin(), numbers.end(), 0,
                                 [](int acc, int n) { return acc + n; });
       std::cout << "Sum: " << sum << std::endl;
   }
   
   int main() {
       demonstrateUniquePtr();
       demonstrateSharedPtr();
       demonstrateLambdaExpressions();
       
       return 0;
   }
   ```

**Assessment:** Smart pointer and lambda expression project

---

## Additional Lesson Plans Structure

The remaining weeks follow a similar detailed structure with:

1. **Clear Learning Objectives** for each lesson
2. **Balanced Lecture/Practice Time** (typically 30-35 minutes lecture, 55-60 minutes hands-on)
3. **Comprehensive Code Examples** with detailed comments
4. **Progressive Difficulty** building on previous concepts
5. **Practical Exercises** that reinforce learning
6. **Assessment Methods** appropriate for each topic

Each lesson plan includes:
- **Prerequisites** from previous lessons
- **Materials needed** (compiler, IDE, examples)
- **Time allocation** for different activities
- **Assessment criteria** and methods
- **Homework assignments** to reinforce learning
- **Additional resources** for further study

This structure ensures students receive comprehensive, hands-on learning experiences that build progressively from basic concepts to advanced C++ programming techniques.
