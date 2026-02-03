# Chapter 17: Classes and Constructors

## 📘 Learning Objectives

After completing this chapter, you will:
- Master advanced class design principles
- Understand constructor types and initialization
- Learn about copy and move semantics
- Master RAII and resource management
- Understand class hierarchies and inheritance

## 🎯 Key Concepts

### 1. Advanced Class Design

- **Class members**: Data members and member functions
- **Access control**: public, private, protected
- **Static members**: Class-level data and functions
- **Friend functions**: Access to private members
- **Nested classes**: Classes within classes

### 2. Constructors

- **Default constructor**: No arguments
- **Parameterized constructor**: With arguments
- **Copy constructor**: Copy initialization
- **Move constructor**: Move initialization
- **Delegating constructor**: Calls other constructor
- **Constructor initialization lists**: Member initialization

### 3. Destructors

- **Destructor**: Cleanup when object is destroyed
- **Virtual destructors**: For inheritance hierarchies
- **RAII**: Resource Acquisition Is Initialization
- **Smart pointers**: Automatic resource management

### 4. Copy and Move Semantics

- **Copy constructor**: Deep vs shallow copy
- **Copy assignment operator**: Assignment semantics
- **Move constructor**: Efficient transfer of resources
- **Move assignment operator**: Move assignment
- **Rule of Five**: Complete copy/move semantics

### 5. Operator Overloading

- **Arithmetic operators**: +, -, *, /, %
- **Comparison operators**: ==, !=, <, >, <=, >=
- **Assignment operators**: =, +=, -=, *=, /=
- **Stream operators**: <<, >>
- **Function call operator**: ()

## 🧩 Practice Exercises

### Exercise 17.1: Advanced Class Design
Create classes with complex member relationships.

### Exercise 17.2: Constructor Implementation
Implement various constructor types.

### Exercise 17.3: Copy and Move Semantics
Demonstrate efficient resource management.

### Exercise 17.4: Operator Overloading
Implement intuitive operator behavior.

## 💻 Code Examples

### Advanced Class Design
```cpp
#include <iostream>
#include <string>
#include <vector>

class BankAccount {
private:
    std::string account_number;
    double balance;
    std::vector<std::string> transaction_history;
    
public:
    // Constructors
    BankAccount(const std::string& number, double initial_balance = 0.0);
    BankAccount(const BankAccount& other);  // Copy constructor
    BankAccount(BankAccount&& other) noexcept;  // Move constructor
    
    // Destructor
    ~BankAccount() = default;
    
    // Assignment operators
    BankAccount& operator=(const BankAccount& other);  // Copy assignment
    BankAccount& operator=(BankAccount&& other) noexcept;  // Move assignment
    
    // Member functions
    void deposit(double amount);
    void withdraw(double amount);
    double get_balance() const { return balance; }
    const std::string& get_account_number() const { return account_number; }
    
    // Operator overloading
    BankAccount& operator+=(double amount);
    BankAccount& operator-=(double amount);
    bool operator==(const BankAccount& other) const;
    
    // Friend function
    friend std::ostream& operator<<(std::ostream& os, const BankAccount& account);
};

int main() {
    BankAccount account1("12345", 1000.0);
    BankAccount account2 = account1;  // Copy constructor
    BankAccount account3 = std::move(account1);  // Move constructor
    
    account2 += 500.0;  // Operator overloading
    std::cout << account2 << std::endl;
    
    return 0;
}
```

## 🎓 Key Takeaways

1. **Design for RAII**: Automatic resource management
2. **Implement Rule of Five**: Complete copy/move semantics
3. **Use constructor initialization lists**: Efficient initialization
4. **Prefer move semantics**: For performance optimization
5. **Design intuitive operators**: Natural class behavior

## 🔗 Next Steps

After mastering classes and constructors, proceed to Chapter 18 to learn about inheritance and polymorphism.

## 📚 Additional Resources

- C++ Reference: Classes
- C++ Core Guidelines: Classes
- Practice with complex class hierarchies
