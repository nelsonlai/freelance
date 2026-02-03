# Chapter 3: User-Defined Types

## 📘 Learning Objectives

After completing this chapter, you will:
- Master classes and objects in C++
- Understand constructors and destructors
- Learn about member functions and data members
- Understand access control (public, private, protected)
- Master operator overloading basics
- Learn about copy semantics and move semantics
- Understand the RAII principle

## 🎯 Key Concepts

### 1. Classes vs Structures

- **Classes**: Default private access, used for complex objects
- **Structures**: Default public access, used for simple data containers
- Both can have member functions and constructors

### 2. Constructors and Destructors

- **Constructors**: Initialize objects
- **Destructors**: Clean up resources
- **Copy constructor**: Create copies of objects
- **Move constructor**: Efficiently transfer ownership

### 3. Access Control

- **Public**: Accessible from anywhere
- **Private**: Accessible only within the class
- **Protected**: Accessible within class and derived classes

### 4. Member Functions

- **const member functions**: Don't modify object state
- **Static member functions**: Belong to class, not instance
- **Inline functions**: Defined in header for performance

### 5. Operator Overloading

- Overload operators for custom types
- Maintain intuitive semantics
- Use const references for parameters

## 🧩 Practice Exercises

### Exercise 3.1: Basic Class Design
Create a `BankAccount` class with balance, deposit, and withdraw functionality.

### Exercise 3.2: Constructor Overloading
Design a `Date` class with multiple constructors.

### Exercise 3.3: Operator Overloading
Implement a `Complex` number class with arithmetic operators.

### Exercise 3.4: RAII Pattern
Create a `FileHandler` class that manages file resources.

## 💻 Code Examples

### Basic Class Definition
```cpp
class BankAccount {
private:
    double balance;
    std::string account_number;
    
public:
    // Constructor
    BankAccount(const std::string& account_number, double initial_balance = 0.0);
    
    // Member functions
    void deposit(double amount);
    bool withdraw(double amount);
    double get_balance() const;
    void display_info() const;
};
```

### Constructor Implementation
```cpp
BankAccount::BankAccount(const std::string& account_number, double initial_balance)
    : account_number(account_number), balance(initial_balance) {
    std::cout << "Account " << account_number << " created with balance: $" << balance << std::endl;
}

void BankAccount::deposit(double amount) {
    if (amount > 0) {
        balance += amount;
        std::cout << "Deposited $" << amount << ". New balance: $" << balance << std::endl;
    }
}
```

## 🎓 Key Takeaways

1. **Encapsulation**: Hide implementation details, expose interface
2. **RAII**: Resource management through object lifetime
3. **Const correctness**: Use const to prevent unintended modifications
4. **Operator overloading**: Make custom types behave like built-in types
5. **Copy semantics**: Understand when and how objects are copied

## 🔗 Next Steps

After mastering user-defined types, proceed to Chapter 4 to learn about computation and control flow in the context of classes.

## 📚 Additional Resources

- C++ Core Guidelines: Classes
- Effective C++ by Scott Meyers
- RAII Pattern Documentation
