/*
 * Lesson 2.1: Classes and Objects
 * 
 * This file demonstrates class definition, object creation,
 * access specifiers, encapsulation, and member functions.
 */

#include <iostream>
#include <string>
#include <vector>

// Example 1: BankAccount class demonstrating basic OOP concepts
class BankAccount {
private:
    std::string accountNumber;
    std::string ownerName;
    double balance;
    
public:
    // Constructor
    BankAccount(const std::string& accNum, const std::string& name, double initialBalance = 0.0)
        : accountNumber(accNum), ownerName(name), balance(initialBalance) {
        std::cout << "BankAccount created for " << name << std::endl;
    }
    
    // Member functions
    void deposit(double amount) {
        if (amount > 0) {
            balance += amount;
            std::cout << "Deposited $" << amount << " to account " << accountNumber << std::endl;
        } else {
            std::cout << "Invalid deposit amount!" << std::endl;
        }
    }
    
    bool withdraw(double amount) {
        if (amount > 0 && amount <= balance) {
            balance -= amount;
            std::cout << "Withdrew $" << amount << " from account " << accountNumber << std::endl;
            return true;
        } else {
            std::cout << "Insufficient funds or invalid amount!" << std::endl;
            return false;
        }
    }
    
    // Getter methods (const functions that don't modify state)
    double getBalance() const {
        return balance;
    }
    
    const std::string& getAccountNumber() const {
        return accountNumber;
    }
    
    const std::string& getOwnerName() const {
        return ownerName;
    }
    
    // Display method
    void displayInfo() const {
        std::cout << "\n=== Account Information ===" << std::endl;
        std::cout << "Account Number: " << accountNumber << std::endl;
        std::cout << "Owner: " << ownerName << std::endl;
        std::cout << "Balance: $" << balance << std::endl;
    }
};

// Example 2: Student class with grade management
class Student {
private:
    std::string name;
    int studentId;
    std::vector<double> grades;
    
public:
    // Constructor
    Student(const std::string& n, int id) : name(n), studentId(id) {
        std::cout << "Student " << name << " (ID: " << id << ") enrolled" << std::endl;
    }
    
    // Grade management methods
    void addGrade(double grade) {
        if (grade >= 0.0 && grade <= 100.0) {
            grades.push_back(grade);
            std::cout << "Grade " << grade << " added for " << name << std::endl;
        } else {
            std::cout << "Invalid grade! Must be between 0 and 100." << std::endl;
        }
    }
    
    double getAverage() const {
        if (grades.empty()) {
            return 0.0;
        }
        
        double sum = 0.0;
        for (double grade : grades) {
            sum += grade;
        }
        return sum / grades.size();
    }
    
    char getLetterGrade() const {
        double average = getAverage();
        if (average >= 90) return 'A';
        else if (average >= 80) return 'B';
        else if (average >= 70) return 'C';
        else if (average >= 60) return 'D';
        else return 'F';
    }
    
    // Getter methods
    const std::string& getName() const { return name; }
    int getStudentId() const { return studentId; }
    const std::vector<double>& getGrades() const { return grades; }
    
    // Display method
    void displayInfo() const {
        std::cout << "\n=== Student Information ===" << std::endl;
        std::cout << "Name: " << name << std::endl;
        std::cout << "Student ID: " << studentId << std::endl;
        
        if (!grades.empty()) {
            std::cout << "Grades: ";
            for (size_t i = 0; i < grades.size(); ++i) {
                std::cout << grades[i];
                if (i < grades.size() - 1) std::cout << ", ";
            }
            std::cout << std::endl;
            std::cout << "Average: " << getAverage() << std::endl;
            std::cout << "Letter Grade: " << getLetterGrade() << std::endl;
        } else {
            std::cout << "No grades recorded yet." << std::endl;
        }
    }
};

// Example 3: Rectangle class demonstrating geometric calculations
class Rectangle {
private:
    double width;
    double height;
    
public:
    // Constructor with validation
    Rectangle(double w, double h) : width(w), height(h) {
        if (width <= 0 || height <= 0) {
            std::cout << "Warning: Invalid dimensions! Setting to default values." << std::endl;
            width = 1.0;
            height = 1.0;
        }
        std::cout << "Rectangle created with dimensions " << width << " x " << height << std::endl;
    }
    
    // Getter methods
    double getWidth() const { return width; }
    double getHeight() const { return height; }
    
    // Setter methods with validation
    void setWidth(double w) {
        if (w > 0) {
            width = w;
        } else {
            std::cout << "Invalid width! Must be positive." << std::endl;
        }
    }
    
    void setHeight(double h) {
        if (h > 0) {
            height = h;
        } else {
            std::cout << "Invalid height! Must be positive." << std::endl;
        }
    }
    
    // Calculation methods
    double getArea() const {
        return width * height;
    }
    
    double getPerimeter() const {
        return 2 * (width + height);
    }
    
    // Display method
    void displayInfo() const {
        std::cout << "\n=== Rectangle Information ===" << std::endl;
        std::cout << "Width: " << width << std::endl;
        std::cout << "Height: " << height << std::endl;
        std::cout << "Area: " << getArea() << std::endl;
        std::cout << "Perimeter: " << getPerimeter() << std::endl;
    }
};

// Example 4: Car class with fuel management
class Car {
private:
    std::string make;
    std::string model;
    int year;
    double mileage;
    double fuelLevel;
    double fuelCapacity;
    
public:
    // Constructor
    Car(const std::string& carMake, const std::string& carModel, int carYear, double capacity = 50.0)
        : make(carMake), model(carModel), year(carYear), mileage(0.0), 
          fuelLevel(capacity), fuelCapacity(capacity) {
        std::cout << "Car created: " << year << " " << make << " " << model << std::endl;
    }
    
    // Driving method
    bool drive(double distance) {
        if (distance <= 0) {
            std::cout << "Invalid distance!" << std::endl;
            return false;
        }
        
        double fuelNeeded = distance / 25.0; // Assume 25 mpg
        if (fuelNeeded <= fuelLevel) {
            mileage += distance;
            fuelLevel -= fuelNeeded;
            std::cout << "Drove " << distance << " miles. Fuel remaining: " << fuelLevel << " gallons" << std::endl;
            return true;
        } else {
            std::cout << "Not enough fuel to drive " << distance << " miles!" << std::endl;
            return false;
        }
    }
    
    // Refuel method
    void refuel(double amount) {
        if (amount > 0) {
            fuelLevel += amount;
            if (fuelLevel > fuelCapacity) {
                fuelLevel = fuelCapacity;
            }
            std::cout << "Refueled. Current fuel level: " << fuelLevel << " gallons" << std::endl;
        } else {
            std::cout << "Invalid fuel amount!" << std::endl;
        }
    }
    
    // Getter methods
    const std::string& getMake() const { return make; }
    const std::string& getModel() const { return model; }
    int getYear() const { return year; }
    double getMileage() const { return mileage; }
    double getFuelLevel() const { return fuelLevel; }
    double getFuelCapacity() const { return fuelCapacity; }
    
    // Display method
    void displayInfo() const {
        std::cout << "\n=== Car Information ===" << std::endl;
        std::cout << "Make: " << make << std::endl;
        std::cout << "Model: " << model << std::endl;
        std::cout << "Year: " << year << std::endl;
        std::cout << "Mileage: " << mileage << " miles" << std::endl;
        std::cout << "Fuel: " << fuelLevel << "/" << fuelCapacity << " gallons" << std::endl;
    }
};

// Function to demonstrate object creation and usage
void demonstrateBankAccount() {
    std::cout << "\n=== Bank Account Demo ===" << std::endl;
    
    // Create bank account objects
    BankAccount account1("12345", "Alice Johnson", 1000.0);
    BankAccount account2("67890", "Bob Smith");
    
    // Use the objects
    account1.displayInfo();
    account1.deposit(500.0);
    account1.withdraw(200.0);
    account1.displayInfo();
    
    std::cout << "\n---" << std::endl;
    account2.displayInfo();
    account2.deposit(2000.0);
    account2.displayInfo();
}

// Function to demonstrate student management
void demonstrateStudent() {
    std::cout << "\n=== Student Demo ===" << std::endl;
    
    Student student1("Charlie Brown", 1001);
    Student student2("Diana Prince", 1002);
    
    // Add grades for student1
    student1.addGrade(85.5);
    student1.addGrade(92.0);
    student1.addGrade(78.5);
    student1.addGrade(96.0);
    student1.displayInfo();
    
    std::cout << "\n---" << std::endl;
    
    // Add grades for student2
    student2.addGrade(88.0);
    student2.addGrade(91.5);
    student2.addGrade(85.0);
    student2.displayInfo();
}

// Function to demonstrate rectangle calculations
void demonstrateRectangle() {
    std::cout << "\n=== Rectangle Demo ===" << std::endl;
    
    Rectangle rect1(5.0, 3.0);
    Rectangle rect2(10.0, 7.5);
    Rectangle rect3(-2.0, 4.0); // Invalid dimensions
    
    rect1.displayInfo();
    rect2.displayInfo();
    rect3.displayInfo();
    
    // Modify dimensions
    std::cout << "\nModifying rectangle dimensions:" << std::endl;
    rect1.setWidth(8.0);
    rect1.setHeight(6.0);
    rect1.displayInfo();
}

// Function to demonstrate car operations
void demonstrateCar() {
    std::cout << "\n=== Car Demo ===" << std::endl;
    
    Car car1("Toyota", "Camry", 2020, 15.0);
    Car car2("Honda", "Civic", 2019);
    
    car1.displayInfo();
    car1.drive(100.0);
    car1.drive(50.0);
    car1.displayInfo();
    
    std::cout << "\n---" << std::endl;
    
    car2.displayInfo();
    car2.drive(200.0);
    car2.refuel(10.0);
    car2.displayInfo();
}

// Function to demonstrate encapsulation
void demonstrateEncapsulation() {
    std::cout << "\n=== Encapsulation Demo ===" << std::endl;
    
    BankAccount account("99999", "Test User", 500.0);
    
    // This demonstrates encapsulation - we can't directly access private members
    // account.balance = 1000000;  // This would cause a compilation error
    
    // Instead, we must use the public interface
    std::cout << "Current balance: $" << account.getBalance() << std::endl;
    account.deposit(1000.0);
    std::cout << "After deposit: $" << account.getBalance() << std::endl;
    
    // The class controls how its data is accessed and modified
    std::cout << "Encapsulation ensures data integrity through controlled access." << std::endl;
}

int main() {
    std::cout << "=== C++ Classes and Objects Demo ===" << std::endl;
    std::cout << "This program demonstrates OOP concepts in C++.\n" << std::endl;
    
    // Demonstrate various classes and objects
    demonstrateBankAccount();
    demonstrateStudent();
    demonstrateRectangle();
    demonstrateCar();
    demonstrateEncapsulation();
    
    std::cout << "\n=== Key Takeaways ===" << std::endl;
    std::cout << "1. Classes are blueprints for creating objects" << std::endl;
    std::cout << "2. Objects are instances of classes with their own data" << std::endl;
    std::cout << "3. Access specifiers control visibility (private, public, protected)" << std::endl;
    std::cout << "4. Encapsulation hides implementation details and ensures data integrity" << std::endl;
    std::cout << "5. Member functions provide controlled access to private data" << std::endl;
    std::cout << "6. const member functions promise not to modify the object's state" << std::endl;
    
    std::cout << "\nProgram completed successfully!" << std::endl;
    return 0;
}

/*
 * Compilation Instructions:
 * 
 * Using GCC:
 * g++ -std=c++17 -Wall -Wextra -o classes_objects 01_Classes_and_Objects.cpp
 * 
 * Using Clang:
 * clang++ -std=c++17 -Wall -Wextra -o classes_objects 01_Classes_and_Objects.cpp
 * 
 * Using MSVC (Visual Studio):
 * cl /std:c++17 /EHsc 01_Classes_and_Objects.cpp
 * 
 * Running:
 * ./classes_objects (Linux/macOS)
 * classes_objects.exe (Windows)
 */
