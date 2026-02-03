# Chapter 16: Classes

## 📘 Learning Objectives

After completing this chapter, you will:
- Master advanced class design principles
- Understand constructors, destructors, and assignment operators
- Learn copy/move semantics
- Master operator overloading
- Understand access control and encapsulation
- Learn friend functions and classes

## 🎯 Key Concepts

### 1. Class Design Principles

- **Encapsulation**: Hide implementation details
- **Abstraction**: Provide clean interfaces
- **Single Responsibility**: One class, one purpose
- **Open/Closed**: Open for extension, closed for modification

### 2. Constructors and Destructors

- **Default constructor**: No parameters
- **Parameterized constructor**: With parameters
- **Copy constructor**: Creates copy of object
- **Move constructor**: Efficiently transfers ownership
- **Destructor**: Cleans up resources

### 3. Assignment Operators

- **Copy assignment**: Assigns from another object
- **Move assignment**: Efficiently transfers ownership
- **Self-assignment**: Handle assignment to self
- **Exception safety**: Maintain invariants

### 4. Operator Overloading

- **Arithmetic operators**: +, -, *, /
- **Comparison operators**: ==, !=, <, >, <=, >=
- **Assignment operators**: =, +=, -=, *=, /=
- **Stream operators**: <<, >>
- **Function call operator**: ()

### 5. Access Control

- **Public**: Accessible from anywhere
- **Private**: Accessible only within class
- **Protected**: Accessible within class and derived classes
- **Friend**: Grant access to specific functions/classes

## 🧩 Practice Exercises

### Exercise 16.1: Basic Class Design
Create a class with constructors, destructors, and basic operations.

### Exercise 16.2: Operator Overloading
Implement a class with overloaded operators.

### Exercise 16.3: Copy/Move Semantics
Design a class with proper copy and move operations.

### Exercise 16.4: Friend Functions
Create classes with friend functions and classes.

## 💻 Code Examples

### Basic Class Design
```cpp
#include <iostream>
#include <string>

class BankAccount {
private:
    std::string account_number;
    double balance;
    
public:
    // Constructors
    BankAccount(const std::string& acc_num, double initial_balance = 0.0)
        : account_number(acc_num), balance(initial_balance) {}
    
    // Copy constructor
    BankAccount(const BankAccount& other)
        : account_number(other.account_number), balance(other.balance) {}
    
    // Move constructor
    BankAccount(BankAccount&& other) noexcept
        : account_number(std::move(other.account_number)), balance(other.balance) {
        other.balance = 0.0;
    }
    
    // Destructor
    ~BankAccount() = default;
    
    // Assignment operators
    BankAccount& operator=(const BankAccount& other) {
        if (this != &other) {
            account_number = other.account_number;
            balance = other.balance;
        }
        return *this;
    }
    
    BankAccount& operator=(BankAccount&& other) noexcept {
        if (this != &other) {
            account_number = std::move(other.account_number);
            balance = other.balance;
            other.balance = 0.0;
        }
        return *this;
    }
    
    // Member functions
    void deposit(double amount) {
        if (amount > 0) balance += amount;
    }
    
    bool withdraw(double amount) {
        if (amount > 0 && amount <= balance) {
            balance -= amount;
            return true;
        }
        return false;
    }
    
    double get_balance() const { return balance; }
    const std::string& get_account_number() const { return account_number; }
    
    // Operator overloading
    BankAccount& operator+=(double amount) {
        deposit(amount);
        return *this;
    }
    
    BankAccount& operator-=(double amount) {
        withdraw(amount);
        return *this;
    }
    
    bool operator==(const BankAccount& other) const {
        return account_number == other.account_number;
    }
    
    // Friend function for stream output
    friend std::ostream& operator<<(std::ostream& os, const BankAccount& account);
};

// Friend function implementation
std::ostream& operator<<(std::ostream& os, const BankAccount& account) {
    os << "Account[" << account.account_number << "]: $" << account.balance;
    return os;
}
```

## 🎓 Key Takeaways

1. **RAII**: Resource management through object lifetime
2. **Rule of Three/Five**: Implement copy/move operations consistently
3. **Const correctness**: Use const to prevent unintended modifications
4. **Operator overloading**: Make custom types behave like built-ins
5. **Encapsulation**: Hide implementation details, expose interface

## 🔗 Next Steps

After mastering class design, proceed to Chapter 17 to learn about constructors and initialization.

## 📚 Additional Resources

- C++ Core Guidelines: Classes
- Effective C++ by Scott Meyers
- RAII Pattern Documentation
