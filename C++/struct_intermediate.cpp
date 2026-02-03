/*
 * STRUCT INTERMEDIATE EXAMPLES
 * 
 * This file demonstrates intermediate struct concepts in C++:
 * - Constructors and destructors
 * - Access specifiers (private, public)
 * - Static members and methods
 * - Operator overloading
 * - Memory management with smart pointers
 * - Nested structs and composition
 * 
 * Learning Objectives:
 * - Understand object-oriented programming with structs
 * - Learn about constructors, destructors, and RAII
 * - Master access specifiers and encapsulation
 * - Understand static members and their usage
 * - Learn operator overloading and custom behavior
 * - Master memory management and smart pointers
 * 
 * Prerequisites:
 * - Basic C++ knowledge
 * - Understanding of structs and classes
 * - Familiarity with pointers and memory management
 */

#include <iostream>  // For input/output operations (cout, endl)
#include <string>    // For string data type
#include <vector>    // For vector container
#include <memory>    // For smart pointers (unique_ptr, shared_ptr)
using namespace std; // Using standard namespace

/*
 * STRUCT WITH CONSTRUCTORS AND DESTRUCTORS
 * 
 * This struct demonstrates object-oriented programming concepts:
 * - Private members for encapsulation
 * - Constructors for initialization
 * - Destructor for cleanup
 * - Static members for class-wide data
 * - Getter/setter methods for controlled access
 * 
 * Key Concepts:
 * - RAII (Resource Acquisition Is Initialization)
 * - Encapsulation through private members
 * - Static members belong to the class, not instances
 * - Constructors initialize objects
 * - Destructors clean up resources
 */
struct Person {
private:
    string name;        // Private member: person's name
    int age;           // Private member: person's age
    static int personCount;  // Static member: count of all Person objects
    
public:
    /*
     * DEFAULT CONSTRUCTOR
     * 
     * Initializes a Person with default values.
     * Uses member initializer list for efficient initialization.
     */
    Person() : name("Unknown"), age(0) {
        personCount++;  // Increment static counter
        cout << "Default constructor called. Total persons: " << personCount << endl;
    }
    
    /*
     * PARAMETERIZED CONSTRUCTOR
     * 
     * Initializes a Person with provided values.
     * Uses const reference to avoid unnecessary copying.
     * 
     * @param n The person's name
     * @param a The person's age
     */
    Person(const string& n, int a) : name(n), age(a) {
        personCount++;  // Increment static counter
        cout << "Parameterized constructor called. Total persons: " << personCount << endl;
    }
    
    /*
     * COPY CONSTRUCTOR
     * 
     * Creates a new Person as a copy of another Person.
     * Called when passing by value or explicit copying.
     * 
     * @param other The Person to copy from
     */
    Person(const Person& other) : name(other.name), age(other.age) {
        personCount++;  // Increment static counter
        cout << "Copy constructor called. Total persons: " << personCount << endl;
    }
    
    /*
     * DESTRUCTOR
     * 
     * Called when a Person object is destroyed.
     * Used for cleanup and resource management.
     */
    ~Person() {
        personCount--;  // Decrement static counter
        cout << "Destructor called for " << name << ". Remaining persons: " << personCount << endl;
    }
    
    /*
     * GETTER METHODS
     * 
     * Provide read-only access to private members.
     * const methods don't modify the object.
     */
    string getName() const { return name; }  // Get person's name
    int getAge() const { return age; }       // Get person's age
    
    /*
     * SETTER METHODS
     * 
     * Provide controlled access to modify private members.
     * Can include validation logic if needed.
     */
    void setName(const string& n) { name = n; }  // Set person's name
    void setAge(int a) { age = a; }              // Set person's age
    
    /*
     * MEMBER FUNCTION
     * 
     * Performs an action using the object's data.
     * const method doesn't modify the object.
     */
    void introduce() const {
        cout << "Hi, I'm " << name << " and I'm " << age << " years old." << endl;
    }
    
    // Static member function
    static int getPersonCount() { return personCount; }
    
    // Operator overloading
    Person operator+(const Person& other) const {
        return Person(name + " " + other.name, age + other.age);
    }

    // Operator overloading
    Person operator-(const Person& other) const {
        return Person(name + " " + other.name, age - other.age);
    }
    // Operator overloading
    bool operator==(const Person& other) const {
        return name == other.name && age == other.age;
    }
    
    Person& operator=(const Person& other) {
        if (this != &other) {
            name = other.name;
            age = other.age;
        }
        return *this;
    }
    
    // Friend function
    friend ostream& operator<<(ostream& os, const Person& p);
};

// Static member definition
int Person::personCount = 0;

// Friend function implementation
ostream& operator<<(ostream& os, const Person& p) {
    os << "Person{name='" << p.name << "', age=" << p.age << "}";
    return os;
}

Person p1 ("Alice", 25);
Person p2 ("Bob", 30);
Person p3 = p1;  // Copy constructor
p3 = p1 + p2;  // Using overloaded + operator
p3 = p1 - p2;  // Using overloaded - operator

cout << p1 << endl;  // Using overloaded << operator
cout << p2 << endl;  // Using overloaded << operator
// Nested struct
struct Company {
    struct Employee {
        string name;
        string position;
        double salary;
        
        Employee(const string& n, const string& pos, double sal) 
            : name(n), position(pos), salary(sal) {}
        
        void displayInfo() const {
            cout << "Employee: " << name << ", Position: " << position 
                 << ", Salary: $" << salary << endl;
        }
    };
    
    string companyName;
    vector<Employee> employees;
    
    Company(const string& name) : companyName(name) {}
    
    void addEmployee(const Employee& emp) {
        employees.push_back(emp);
    }
    
    void displayAllEmployees() const {
        cout << "Company: " << companyName << endl;
        cout << "Employees:" << endl;
        for (const auto& emp : employees) {
            emp.displayInfo();
        }
    }
};

// Struct with templates
template<typename T>
struct Point {
    T x, y;
    
    Point(T x = 0, T y = 0) : x(x), y(y) {}
    
    Point operator+(const Point& other) const {
        return Point(x + other.x, y + other.y);
    }
    
    Point operator-(const Point& other) const {
        return Point(x - other.x, y - other.y);
    }
    
    T distance() const {
        return sqrt(x * x + y * y);
    }
    
    void display() const {
        cout << "Point(" << x << ", " << y << ")" << endl;
    }
};

int main() {
    cout << "=== STRUCT INTERMEDIATE EXAMPLES ===" << endl << endl;
    
    // Example 1: Constructors and destructors
    cout << "1. Constructors and Destructors:" << endl;
    {
        Person p1;  // Default constructor
        Person p2("Alice", 25);  // Parameterized constructor
        Person p3 = p2;  // Copy constructor
        
        p1.introduce();
        p2.introduce();
        p3.introduce();
        
        cout << "Total persons: " << Person::getPersonCount() << endl;
    }  // Destructors called here
    cout << "After scope exit, total persons: " << Person::getPersonCount() << endl;
    cout << endl;
    
    // Example 2: Operator overloading
    cout << "2. Operator Overloading:" << endl;
    Person person1("Bob", 30);
    Person person2("Bob", 30);
    Person person3("Charlie", 25);
    
    cout << "Person1: " << person1 << endl;
    cout << "Person2: " << person2 << endl;
    cout << "Person3: " << person3 << endl;
    
    if (person1 == person2) {
        cout << "Person1 and Person2 are equal" << endl;
    }
    
    if (person1 == person3) {
        cout << "Person1 and Person3 are equal" << endl;
    } else {
        cout << "Person1 and Person3 are not equal" << endl;
    }
    cout << endl;
    
    // Example 3: Nested structs
    cout << "3. Nested Structs:" << endl;
    Company techCorp("TechCorp Inc.");
    
    Company::Employee emp1("John Doe", "Software Engineer", 75000);
    Company::Employee emp2("Jane Smith", "Project Manager", 85000);
    Company::Employee emp3("Mike Johnson", "Data Scientist", 80000);
    
    techCorp.addEmployee(emp1);
    techCorp.addEmployee(emp2);
    techCorp.addEmployee(emp3);
    
    techCorp.displayAllEmployees();
    cout << endl;
    
    // Example 4: Template structs
    cout << "4. Template Structs:" << endl;
    Point<int> intPoint(3, 4);
    Point<double> doublePoint(2.5, 3.7);
    
    cout << "Integer point: ";
    intPoint.display();
    cout << "Distance from origin: " << intPoint.distance() << endl;
    
    cout << "Double point: ";
    doublePoint.display();
    cout << "Distance from origin: " << doublePoint.distance() << endl;
    
    Point<int> point1(1, 2);
    Point<int> point2(3, 4);
    Point<int> sum = point1 + point2;
    Point<int> diff = point2 - point1;
    
    cout << "Point1: ";
    point1.display();
    cout << "Point2: ";
    point2.display();
    cout << "Sum: ";
    sum.display();
    cout << "Difference: ";
    diff.display();
    cout << endl;
    
    // Example 5: Struct with dynamic memory
    cout << "5. Struct with Dynamic Memory:" << endl;
    struct DynamicArray {
        int* data;
        size_t size;
        
        DynamicArray(size_t s) : size(s) {
            data = new int[size];
            cout << "Dynamic array created with size " << size << endl;
        }
        
        ~DynamicArray() {
            delete[] data;
            cout << "Dynamic array destroyed" << endl;
        }
        
        void fill(int value) {
            for (size_t i = 0; i < size; i++) {
                data[i] = value;
            }
        }
        
        void display() const {
            cout << "Array contents: ";
            for (size_t i = 0; i < size; i++) {
                cout << data[i] << " ";
            }
            cout << endl;
        }
    };
    
    DynamicArray arr(5);
    arr.fill(42);
    arr.display();
    cout << endl;
    
    // Example 6: Struct with function pointers
    cout << "6. Struct with Function Pointers:" << endl;
    struct Calculator {
        double (*operation)(double, double);
        
        Calculator(double (*op)(double, double)) : operation(op) {}
        
        double calculate(double a, double b) {
            return operation(a, b);
        }
    };
    
    auto add = [](double a, double b) { return a + b; };
    auto multiply = [](double a, double b) { return a * b; };
    
    Calculator calc1(add);
    Calculator calc2(multiply);
    
    cout << "5 + 3 = " << calc1.calculate(5, 3) << endl;
    cout << "5 * 3 = " << calc2.calculate(5, 3) << endl;
    
    return 0;
}
