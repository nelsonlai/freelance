/*
 * Lesson 10.1: Classes Deep Dive
 * 
 * This file demonstrates advanced class design, encapsulation,
 * static members, nested classes, and modern class features.
 */

#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <algorithm>
#include <numeric>
#include <cmath>

// Advanced class with proper encapsulation
class BankAccount {
private:
    std::string account_holder_;
    std::string account_number_;
    double balance_;
    static int total_accounts_;
    static double total_balance_;
    
    // Private helper methods
    bool validateAmount(double amount) const {
        return amount > 0 && std::isfinite(amount);
    }
    
    void logTransaction(const std::string& type, double amount) const {
        std::cout << "Transaction: " << type << " $" << amount 
                  << " (Account: " << account_number_ << ")" << std::endl;
    }
    
public:
    // Constructor
    BankAccount(const std::string& holder, const std::string& number, double initial_balance = 0.0)
        : account_holder_(holder), account_number_(number), balance_(initial_balance) {
        total_accounts_++;
        total_balance_ += initial_balance;
        std::cout << "Account created: " << holder << " (" << number << ")" << std::endl;
    }
    
    // Destructor
    ~BankAccount() {
        total_accounts_--;
        total_balance_ -= balance_;
        std::cout << "Account closed: " << account_holder_ << std::endl;
    }
    
    // Copy constructor
    BankAccount(const BankAccount& other)
        : account_holder_(other.account_holder_ + " (Copy)"),
          account_number_(other.account_number_ + "_copy"),
          balance_(other.balance_) {
        total_accounts_++;
        total_balance_ += balance_;
        std::cout << "Account copied: " << account_holder_ << std::endl;
    }
    
    // Copy assignment operator
    BankAccount& operator=(const BankAccount& other) {
        if (this != &other) {
            total_balance_ -= balance_;
            account_holder_ = other.account_holder_ + " (Assigned)";
            account_number_ = other.account_number_ + "_assigned";
            balance_ = other.balance_;
            total_balance_ += balance_;
        }
        return *this;
    }
    
    // Move constructor
    BankAccount(BankAccount&& other) noexcept
        : account_holder_(std::move(other.account_holder_)),
          account_number_(std::move(other.account_number_)),
          balance_(other.balance_) {
        other.balance_ = 0.0;
        std::cout << "Account moved: " << account_holder_ << std::endl;
    }
    
    // Move assignment operator
    BankAccount& operator=(BankAccount&& other) noexcept {
        if (this != &other) {
            total_balance_ -= balance_;
            account_holder_ = std::move(other.account_holder_);
            account_number_ = std::move(other.account_number_);
            balance_ = other.balance_;
            other.balance_ = 0.0;
            total_balance_ += balance_;
        }
        return *this;
    }
    
    // Public interface methods
    void deposit(double amount) {
        if (validateAmount(amount)) {
            balance_ += amount;
            total_balance_ += amount;
            logTransaction("DEPOSIT", amount);
        } else {
            std::cout << "Invalid deposit amount: $" << amount << std::endl;
        }
    }
    
    bool withdraw(double amount) {
        if (validateAmount(amount) && amount <= balance_) {
            balance_ -= amount;
            total_balance_ -= amount;
            logTransaction("WITHDRAWAL", amount);
            return true;
        } else {
            std::cout << "Invalid withdrawal amount: $" << amount << std::endl;
            return false;
        }
    }
    
    void transfer(BankAccount& other, double amount) {
        if (withdraw(amount)) {
            other.deposit(amount);
            logTransaction("TRANSFER OUT", amount);
        }
    }
    
    // Const member functions (getters)
    double getBalance() const { return balance_; }
    const std::string& getAccountHolder() const { return account_holder_; }
    const std::string& getAccountNumber() const { return account_number_; }
    
    // Static member functions
    static int getTotalAccounts() { return total_accounts_; }
    static double getTotalBalance() { return total_balance_; }
    static double getAverageBalance() {
        return total_accounts_ > 0 ? total_balance_ / total_accounts_ : 0.0;
    }
    
    // Virtual function for polymorphism
    virtual void displayInfo() const {
        std::cout << "Account Holder: " << account_holder_ << std::endl;
        std::cout << "Account Number: " << account_number_ << std::endl;
        std::cout << "Balance: $" << balance_ << std::endl;
    }
    
    // Virtual destructor for proper inheritance
    virtual ~BankAccount() = default;
};

// Static member definitions
int BankAccount::total_accounts_ = 0;
double BankAccount::total_balance_ = 0.0;

// Derived class demonstrating inheritance
class SavingsAccount : public BankAccount {
private:
    double interest_rate_;
    double minimum_balance_;
    
public:
    SavingsAccount(const std::string& holder, const std::string& number, 
                   double initial_balance, double interest_rate, double minimum_balance)
        : BankAccount(holder, number, initial_balance),
          interest_rate_(interest_rate), minimum_balance_(minimum_balance) {
        std::cout << "Savings account created with interest rate: " << interest_rate_ << "%" << std::endl;
    }
    
    void applyInterest() {
        double interest = getBalance() * interest_rate_ / 100.0;
        deposit(interest);
        std::cout << "Interest applied: $" << interest << std::endl;
    }
    
    bool withdraw(double amount) {
        if (getBalance() - amount < minimum_balance_) {
            std::cout << "Withdrawal would violate minimum balance requirement" << std::endl;
            return false;
        }
        return BankAccount::withdraw(amount);
    }
    
    void displayInfo() const override {
        BankAccount::displayInfo();
        std::cout << "Interest Rate: " << interest_rate_ << "%" << std::endl;
        std::cout << "Minimum Balance: $" << minimum_balance_ << std::endl;
    }
    
    double getInterestRate() const { return interest_rate_; }
    double getMinimumBalance() const { return minimum_balance_; }
};

// Class with nested classes
class LinkedList {
public:
    class Node {
    private:
        int data_;
        std::unique_ptr<Node> next_;
        
    public:
        Node(int data) : data_(data), next_(nullptr) {}
        
        int getData() const { return data_; }
        void setData(int data) { data_ = data; }
        
        Node* getNext() const { return next_.get(); }
        void setNext(std::unique_ptr<Node> next) { next_ = std::move(next); }
        void setNext(Node* next) { next_ = std::make_unique<Node>(*next); }
        
        void display() const {
            std::cout << "Node data: " << data_ << std::endl;
        }
    };
    
private:
    std::unique_ptr<Node> head_;
    size_t size_;
    
public:
    LinkedList() : head_(nullptr), size_(0) {}
    
    ~LinkedList() {
        clear();
    }
    
    // Move constructor
    LinkedList(LinkedList&& other) noexcept
        : head_(std::move(other.head_)), size_(other.size_) {
        other.size_ = 0;
    }
    
    // Move assignment
    LinkedList& operator=(LinkedList&& other) noexcept {
        if (this != &other) {
            clear();
            head_ = std::move(other.head_);
            size_ = other.size_;
            other.size_ = 0;
        }
        return *this;
    }
    
    void add(int data) {
        auto new_node = std::make_unique<Node>(data);
        new_node->setNext(std::move(head_));
        head_ = std::move(new_node);
        size_++;
    }
    
    bool remove(int data) {
        if (!head_) return false;
        
        if (head_->getData() == data) {
            head_ = std::move(head_->next_);
            size_--;
            return true;
        }
        
        Node* current = head_.get();
        while (current->getNext()) {
            if (current->getNext()->getData() == data) {
                current->setNext(current->getNext()->getNext());
                size_--;
                return true;
            }
            current = current->getNext();
        }
        
        return false;
    }
    
    bool contains(int data) const {
        Node* current = head_.get();
        while (current) {
            if (current->getData() == data) {
                return true;
            }
            current = current->getNext();
        }
        return false;
    }
    
    void display() const {
        std::cout << "LinkedList (size: " << size_ << "): ";
        Node* current = head_.get();
        while (current) {
            std::cout << current->getData() << " ";
            current = current->getNext();
        }
        std::cout << std::endl;
    }
    
    size_t size() const { return size_; }
    bool empty() const { return size_ == 0; }
    
private:
    void clear() {
        while (head_) {
            head_ = std::move(head_->next_);
        }
        size_ = 0;
    }
};

// Utility class with static members
class MathUtils {
public:
    static const double PI;
    static const double E;
    
    static double square(double x) { return x * x; }
    static double cube(double x) { return x * x * x; }
    static double power(double base, double exponent) { return std::pow(base, exponent); }
    static double sqrt(double x) { return std::sqrt(x); }
    static double factorial(int n) {
        if (n <= 1) return 1.0;
        return n * factorial(n - 1);
    }
    static bool isPrime(int n) {
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
};

// Static member definitions
const double MathUtils::PI = 3.14159265359;
const double MathUtils::E = 2.71828182846;

// Class demonstrating composition
class Engine {
private:
    std::string type_;
    double horsepower_;
    bool running_;
    
public:
    Engine(const std::string& type, double horsepower)
        : type_(type), horsepower_(horsepower), running_(false) {}
    
    void start() {
        running_ = true;
        std::cout << type_ << " engine started (" << horsepower_ << " HP)" << std::endl;
    }
    
    void stop() {
        running_ = false;
        std::cout << type_ << " engine stopped" << std::endl;
    }
    
    bool isRunning() const { return running_; }
    const std::string& getType() const { return type_; }
    double getHorsepower() const { return horsepower_; }
};

class Car {
private:
    std::string make_;
    std::string model_;
    int year_;
    Engine engine_;
    double fuel_level_;
    static int total_cars_;
    
public:
    Car(const std::string& make, const std::string& model, int year,
        const std::string& engine_type, double horsepower, double fuel_level = 100.0)
        : make_(make), model_(model), year_(year),
          engine_(engine_type, horsepower), fuel_level_(fuel_level) {
        total_cars_++;
        std::cout << "Car created: " << year_ << " " << make_ << " " << model_ << std::endl;
    }
    
    ~Car() {
        total_cars_--;
        std::cout << "Car destroyed: " << make_ << " " << model_ << std::endl;
    }
    
    void start() {
        if (fuel_level_ > 0) {
            engine_.start();
            std::cout << make_ << " " << model_ << " is ready to drive" << std::endl;
        } else {
            std::cout << "No fuel! Cannot start " << make_ << " " << model_ << std::endl;
        }
    }
    
    void stop() {
        engine_.stop();
        std::cout << make_ << " " << model_ << " stopped" << std::endl;
    }
    
    void drive(double distance) {
        if (engine_.isRunning()) {
            double fuel_consumed = distance * 0.1;  // 0.1 gallons per mile
            if (fuel_consumed <= fuel_level_) {
                fuel_level_ -= fuel_consumed;
                std::cout << "Drove " << distance << " miles. Fuel remaining: " 
                          << fuel_level_ << " gallons" << std::endl;
            } else {
                std::cout << "Not enough fuel to drive " << distance << " miles" << std::endl;
            }
        } else {
            std::cout << "Engine is not running. Cannot drive." << std::endl;
        }
    }
    
    void refuel(double amount) {
        fuel_level_ += amount;
        std::cout << "Refueled " << amount << " gallons. Total fuel: " 
                  << fuel_level_ << " gallons" << std::endl;
    }
    
    void displayInfo() const {
        std::cout << "Car: " << year_ << " " << make_ << " " << model_ << std::endl;
        std::cout << "Engine: " << engine_.getType() << " (" << engine_.getHorsepower() << " HP)" << std::endl;
        std::cout << "Fuel Level: " << fuel_level_ << " gallons" << std::endl;
        std::cout << "Engine Status: " << (engine_.isRunning() ? "Running" : "Stopped") << std::endl;
    }
    
    static int getTotalCars() { return total_cars_; }
};

int Car::total_cars_ = 0;

// Function to demonstrate advanced class features
void demonstrateAdvancedClasses() {
    std::cout << "=== Advanced Classes Demonstration ===" << std::endl;
    
    // Create bank accounts
    BankAccount account1("Alice Johnson", "ACC001", 1000.0);
    BankAccount account2("Bob Smith", "ACC002", 500.0);
    
    // Perform transactions
    account1.deposit(250.0);
    account1.withdraw(100.0);
    account1.transfer(account2, 200.0);
    
    std::cout << "\nAccount 1 Balance: $" << account1.getBalance() << std::endl;
    std::cout << "Account 2 Balance: $" << account2.getBalance() << std::endl;
    
    // Display static information
    std::cout << "\nTotal Accounts: " << BankAccount::getTotalAccounts() << std::endl;
    std::cout << "Total Balance: $" << BankAccount::getTotalBalance() << std::endl;
    std::cout << "Average Balance: $" << BankAccount::getAverageBalance() << std::endl;
    
    // Test copy and move semantics
    BankAccount account3 = account1;  // Copy constructor
    BankAccount account4(std::move(account2));  // Move constructor
    
    std::cout << "\nAfter copy and move:" << std::endl;
    std::cout << "Total Accounts: " << BankAccount::getTotalAccounts() << std::endl;
}

// Function to demonstrate inheritance
void demonstrateInheritance() {
    std::cout << "\n=== Inheritance Demonstration ===" << std::endl;
    
    SavingsAccount savings("Carol Davis", "SAV001", 2000.0, 2.5, 500.0);
    savings.displayInfo();
    
    savings.applyInterest();
    std::cout << "Balance after interest: $" << savings.getBalance() << std::endl;
    
    savings.withdraw(100.0);
    std::cout << "Balance after withdrawal: $" << savings.getBalance() << std::endl;
    
    // Try to withdraw below minimum balance
    savings.withdraw(1500.0);
    std::cout << "Balance after failed withdrawal: $" << savings.getBalance() << std::endl;
}

// Function to demonstrate nested classes
void demonstrateNestedClasses() {
    std::cout << "\n=== Nested Classes Demonstration ===" << std::endl;
    
    LinkedList list;
    
    // Add elements
    list.add(10);
    list.add(20);
    list.add(30);
    list.add(40);
    list.add(50);
    
    list.display();
    
    // Test operations
    std::cout << "Contains 30: " << (list.contains(30) ? "Yes" : "No") << std::endl;
    std::cout << "Contains 35: " << (list.contains(35) ? "Yes" : "No") << std::endl;
    
    // Remove element
    list.remove(30);
    std::cout << "After removing 30:" << std::endl;
    list.display();
    
    // Test move semantics
    LinkedList list2 = std::move(list);
    std::cout << "After move:" << std::endl;
    std::cout << "Original list size: " << list.size() << std::endl;
    std::cout << "New list size: " << list2.size() << std::endl;
    list2.display();
}

// Function to demonstrate static members
void demonstrateStaticMembers() {
    std::cout << "\n=== Static Members Demonstration ===" << std::endl;
    
    // Use static utility functions
    std::cout << "PI = " << MathUtils::PI << std::endl;
    std::cout << "E = " << MathUtils::E << std::endl;
    std::cout << "Square of 5: " << MathUtils::square(5) << std::endl;
    std::cout << "Cube of 3: " << MathUtils::cube(3) << std::endl;
    std::cout << "2^8 = " << MathUtils::power(2, 8) << std::endl;
    std::cout << "sqrt(16) = " << MathUtils::sqrt(16) << std::endl;
    std::cout << "Factorial of 6: " << MathUtils::factorial(6) << std::endl;
    
    // Test prime numbers
    std::cout << "\nPrime numbers from 1 to 20:" << std::endl;
    for (int i = 1; i <= 20; ++i) {
        if (MathUtils::isPrime(i)) {
            std::cout << i << " ";
        }
    }
    std::cout << std::endl;
}

// Function to demonstrate composition
void demonstrateComposition() {
    std::cout << "\n=== Composition Demonstration ===" << std::endl;
    
    Car car1("Toyota", "Camry", 2023, "V6", 300.0, 15.0);
    Car car2("Honda", "Civic", 2023, "I4", 200.0, 12.0);
    
    std::cout << "\nTotal cars created: " << Car::getTotalCars() << std::endl;
    
    car1.displayInfo();
    std::cout << std::endl;
    
    car1.start();
    car1.drive(50.0);
    car1.drive(30.0);
    car1.stop();
    
    std::cout << std::endl;
    car1.displayInfo();
    
    car1.refuel(5.0);
    std::cout << std::endl;
    car1.displayInfo();
}

// Function to demonstrate encapsulation
void demonstrateEncapsulation() {
    std::cout << "\n=== Encapsulation Demonstration ===" << std::endl;
    
    BankAccount account("David Wilson", "ACC003", 750.0);
    
    // Public interface allows controlled access
    account.deposit(100.0);
    account.withdraw(50.0);
    
    // Can access public getters
    std::cout << "Account holder: " << account.getAccountHolder() << std::endl;
    std::cout << "Account number: " << account.getAccountNumber() << std::endl;
    std::cout << "Current balance: $" << account.getBalance() << std::endl;
    
    // Cannot access private members directly
    // account.balance_ = 10000.0;  // This would cause compilation error
    
    std::cout << "\nEncapsulation ensures:" << std::endl;
    std::cout << "1. Data integrity through controlled access" << std::endl;
    std::cout << "2. Implementation details are hidden" << std::endl;
    std::cout << "3. Interface remains stable even if implementation changes" << std::endl;
}

// Function to demonstrate const correctness
void demonstrateConstCorrectness() {
    std::cout << "\n=== Const Correctness Demonstration ===" << std::endl;
    
    const BankAccount const_account("Eve Brown", "ACC004", 1000.0);
    
    // Can call const member functions
    std::cout << "Const account balance: $" << const_account.getBalance() << std::endl;
    std::cout << "Const account holder: " << const_account.getAccountHolder() << std::endl;
    
    // Cannot call non-const member functions on const object
    // const_account.deposit(100.0);  // This would cause compilation error
    
    std::cout << "\nConst correctness ensures:" << std::endl;
    std::cout << "1. Immutable objects cannot be modified" << std::endl;
    std::cout << "2. Compiler enforces const-correctness" << std::endl;
    std::cout << "3. Clear distinction between read and write operations" << std::endl;
}

int main() {
    std::cout << "=== Classes Deep Dive Demonstration ===" << std::endl;
    std::cout << "This program demonstrates advanced class design, encapsulation,\n"
              << "static members, nested classes, and modern class features.\n" << std::endl;
    
    // Demonstrate various advanced class concepts
    demonstrateAdvancedClasses();
    demonstrateInheritance();
    demonstrateNestedClasses();
    demonstrateStaticMembers();
    demonstrateComposition();
    demonstrateEncapsulation();
    demonstrateConstCorrectness();
    
    std::cout << "\n=== Key Takeaways ===" << std::endl;
    std::cout << "1. Encapsulation protects data and provides controlled access" << std::endl;
    std::cout << "2. Static members are shared across all instances of a class" << std::endl;
    std::cout << "3. Nested classes provide logical grouping and encapsulation" << std::endl;
    std::cout << "4. Const-correctness ensures immutability and type safety" << std::endl;
    std::cout << "5. Composition allows building complex objects from simpler ones" << std::endl;
    std::cout << "6. Move semantics improve performance for resource management" << std::endl;
    std::cout << "7. Proper class design follows single responsibility principle" << std::endl;
    
    std::cout << "\nProgram completed successfully!" << std::endl;
    return 0;
}

/*
 * Compilation Instructions:
 * 
 * Using GCC:
 * g++ -std=c++17 -Wall -Wextra -O2 -o classes_deep_dive 01_Classes_Deep_Dive.cpp
 * 
 * Using Clang:
 * clang++ -std=c++17 -Wall -Wextra -O2 -o classes_deep_dive 01_Classes_Deep_Dive.cpp
 * 
 * Using MSVC (Visual Studio):
 * cl /std:c++17 /EHsc /O2 01_Classes_Deep_Dive.cpp
 * 
 * Running:
 * ./classes_deep_dive (Linux/macOS)
 * classes_deep_dive.exe (Windows)
 * 
 * Note: This lesson requires C++11 or later for smart pointers and move semantics.
 * C++17 is recommended for best class design support.
 * 
 * Class Design Notes:
 * - Use proper encapsulation to protect data
 * - Implement const-correct interfaces
 * - Use static members for shared state
 * - Apply composition over inheritance when possible
 * - Implement move semantics for resource management
 * - Follow single responsibility principle
 * - Use virtual destructors for inheritance hierarchies
 */"""
