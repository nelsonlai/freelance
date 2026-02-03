#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <stdexcept>
#include <algorithm>

// Demonstrates advanced C++ classes and constructors
int main() {
    std::cout << "Advanced Classes and Constructors Demonstration" << std::endl;
    std::cout << "==============================================" << std::endl;
    
    // 1. Basic class with constructors
    std::cout << "\n1. BASIC CLASS WITH CONSTRUCTORS:" << std::endl;
    
    class Person {
    private:
        std::string name;
        int age;
        
    public:
        // Default constructor
        Person() : name("Unknown"), age(0) {
            std::cout << "Default constructor called" << std::endl;
        }
        
        // Parameterized constructor
        Person(const std::string& name, int age) : name(name), age(age) {
            std::cout << "Parameterized constructor called for " << name << std::endl;
        }
        
        // Copy constructor
        Person(const Person& other) : name(other.name), age(other.age) {
            std::cout << "Copy constructor called for " << name << std::endl;
        }
        
        // Move constructor
        Person(Person&& other) noexcept : name(std::move(other.name)), age(other.age) {
            std::cout << "Move constructor called for " << name << std::endl;
            other.age = 0;
        }
        
        // Destructor
        ~Person() {
            std::cout << "Destructor called for " << name << std::endl;
        }
        
        // Assignment operators
        Person& operator=(const Person& other) {
            if (this != &other) {
                name = other.name;
                age = other.age;
                std::cout << "Copy assignment called for " << name << std::endl;
            }
            return *this;
        }
        
        Person& operator=(Person&& other) noexcept {
            if (this != &other) {
                name = std::move(other.name);
                age = other.age;
                other.age = 0;
                std::cout << "Move assignment called for " << name << std::endl;
            }
            return *this;
        }
        
        // Member functions
        const std::string& get_name() const { return name; }
        int get_age() const { return age; }
        
        void set_name(const std::string& new_name) { name = new_name; }
        void set_age(int new_age) { age = new_age; }
        
        void display() const {
            std::cout << "Person: " << name << ", Age: " << age << std::endl;
        }
    };
    
    Person person1("Alice", 25);
    Person person2 = person1;  // Copy constructor
    Person person3 = std::move(person1);  // Move constructor
    
    person2.display();
    person3.display();
    
    // 2. Class with static members
    std::cout << "\n2. CLASS WITH STATIC MEMBERS:" << std::endl;
    
    class Counter {
    private:
        static int count;
        int id;
        
    public:
        Counter() : id(++count) {
            std::cout << "Counter " << id << " created. Total: " << count << std::endl;
        }
        
        ~Counter() {
            --count;
            std::cout << "Counter " << id << " destroyed. Total: " << count << std::endl;
        }
        
        static int get_total_count() { return count; }
        int get_id() const { return id; }
    };
    
    int Counter::count = 0;  // Static member definition
    
    std::cout << "Initial count: " << Counter::get_total_count() << std::endl;
    
    Counter c1, c2, c3;
    std::cout << "Total count: " << Counter::get_total_count() << std::endl;
    
    {
        Counter c4;
        std::cout << "Total count in block: " << Counter::get_total_count() << std::endl;
    }
    
    std::cout << "Total count after block: " << Counter::get_total_count() << std::endl;
    
    // 3. Class with nested class
    std::cout << "\n3. CLASS WITH NESTED CLASS:" << std::endl;
    
    class OuterClass {
    private:
        int outer_value;
        
    public:
        class InnerClass {
        private:
            int inner_value;
            
        public:
            InnerClass(int value) : inner_value(value) {}
            
            int get_value() const { return inner_value; }
            void set_value(int value) { inner_value = value; }
        };
        
        OuterClass(int value) : outer_value(value) {}
        
        InnerClass create_inner(int value) {
            return InnerClass(value);
        }
        
        int get_outer_value() const { return outer_value; }
    };
    
    OuterClass outer(100);
    OuterClass::InnerClass inner = outer.create_inner(50);
    
    std::cout << "Outer value: " << outer.get_outer_value() << std::endl;
    std::cout << "Inner value: " << inner.get_value() << std::endl;
    
    // 4. Class with friend functions
    std::cout << "\n4. CLASS WITH FRIEND FUNCTIONS:" << std::endl;
    
    class FriendClass {
    private:
        int private_value;
        std::string private_string;
        
    public:
        FriendClass(int value, const std::string& str) 
            : private_value(value), private_string(str) {}
        
        friend void display_private_data(const FriendClass& obj);
        friend class FriendClassHelper;
    };
    
    class FriendClassHelper {
    public:
        static void modify_private_data(FriendClass& obj, int new_value, const std::string& new_str) {
            obj.private_value = new_value;
            obj.private_string = new_str;
        }
    };
    
    void display_private_data(const FriendClass& obj) {
        std::cout << "Private data: " << obj.private_value << ", " << obj.private_string << std::endl;
    }
    
    FriendClass friend_obj(42, "secret");
    display_private_data(friend_obj);
    
    FriendClassHelper::modify_private_data(friend_obj, 84, "modified");
    display_private_data(friend_obj);
    
    // 5. Class with operator overloading
    std::cout << "\n5. CLASS WITH OPERATOR OVERLOADING:" << std::endl;
    
    class Complex {
    private:
        double real, imag;
        
    public:
        Complex(double r = 0, double i = 0) : real(r), imag(i) {}
        
        // Arithmetic operators
        Complex operator+(const Complex& other) const {
            return Complex(real + other.real, imag + other.imag);
        }
        
        Complex operator-(const Complex& other) const {
            return Complex(real - other.real, imag - other.imag);
        }
        
        Complex operator*(const Complex& other) const {
            return Complex(real * other.real - imag * other.imag,
                          real * other.imag + imag * other.real);
        }
        
        // Assignment operators
        Complex& operator+=(const Complex& other) {
            real += other.real;
            imag += other.imag;
            return *this;
        }
        
        Complex& operator-=(const Complex& other) {
            real -= other.real;
            imag -= other.imag;
            return *this;
        }
        
        // Comparison operators
        bool operator==(const Complex& other) const {
            return real == other.real && imag == other.imag;
        }
        
        bool operator!=(const Complex& other) const {
            return !(*this == other);
        }
        
        // Unary operators
        Complex operator-() const {
            return Complex(-real, -imag);
        }
        
        Complex operator+() const {
            return *this;
        }
        
        // Function call operator
        double operator()() const {
            return real * real + imag * imag;  // Magnitude squared
        }
        
        // Friend stream operators
        friend std::ostream& operator<<(std::ostream& os, const Complex& c);
        friend std::istream& operator>>(std::istream& is, Complex& c);
        
        // Getters
        double get_real() const { return real; }
        double get_imag() const { return imag; }
    };
    
    std::ostream& operator<<(std::ostream& os, const Complex& c) {
        os << "(" << c.real << " + " << c.imag << "i)";
        return os;
    }
    
    std::istream& operator>>(std::istream& is, Complex& c) {
        std::cout << "Enter real part: ";
        is >> c.real;
        std::cout << "Enter imaginary part: ";
        is >> c.imag;
        return is;
    }
    
    Complex c1(3, 4);
    Complex c2(1, 2);
    
    std::cout << "c1 = " << c1 << std::endl;
    std::cout << "c2 = " << c2 << std::endl;
    std::cout << "c1 + c2 = " << (c1 + c2) << std::endl;
    std::cout << "c1 - c2 = " << (c1 - c2) << std::endl;
    std::cout << "c1 * c2 = " << (c1 * c2) << std::endl;
    std::cout << "c1 == c2: " << std::boolalpha << (c1 == c2) << std::endl;
    std::cout << "c1() = " << c1() << std::endl;
    
    // 6. Class with RAII and resource management
    std::cout << "\n6. CLASS WITH RAII AND RESOURCE MANAGEMENT:" << std::endl;
    
    class ResourceManager {
    private:
        int* data;
        size_t size;
        
    public:
        ResourceManager(size_t size) : size(size) {
            data = new int[size];
            std::fill(data, data + size, 0);
            std::cout << "ResourceManager: Allocated " << size << " integers" << std::endl;
        }
        
        ~ResourceManager() {
            delete[] data;
            std::cout << "ResourceManager: Deallocated " << size << " integers" << std::endl;
        }
        
        // Copy constructor
        ResourceManager(const ResourceManager& other) : size(other.size) {
            data = new int[size];
            std::copy(other.data, other.data + size, data);
            std::cout << "ResourceManager: Copy constructor called" << std::endl;
        }
        
        // Move constructor
        ResourceManager(ResourceManager&& other) noexcept : data(other.data), size(other.size) {
            other.data = nullptr;
            other.size = 0;
            std::cout << "ResourceManager: Move constructor called" << std::endl;
        }
        
        // Copy assignment
        ResourceManager& operator=(const ResourceManager& other) {
            if (this != &other) {
                delete[] data;
                size = other.size;
                data = new int[size];
                std::copy(other.data, other.data + size, data);
                std::cout << "ResourceManager: Copy assignment called" << std::endl;
            }
            return *this;
        }
        
        // Move assignment
        ResourceManager& operator=(ResourceManager&& other) noexcept {
            if (this != &other) {
                delete[] data;
                data = other.data;
                size = other.size;
                other.data = nullptr;
                other.size = 0;
                std::cout << "ResourceManager: Move assignment called" << std::endl;
            }
            return *this;
        }
        
        int& operator[](size_t index) {
            if (index >= size) {
                throw std::out_of_range("Index out of range");
            }
            return data[index];
        }
        
        const int& operator[](size_t index) const {
            if (index >= size) {
                throw std::out_of_range("Index out of range");
            }
            return data[index];
        }
        
        size_t get_size() const { return size; }
    };
    
    {
        ResourceManager rm1(5);
        rm1[0] = 10;
        rm1[1] = 20;
        
        ResourceManager rm2 = rm1;  // Copy constructor
        ResourceManager rm3 = std::move(rm1);  // Move constructor
        
        std::cout << "rm2[0] = " << rm2[0] << std::endl;
        std::cout << "rm3[0] = " << rm3[0] << std::endl;
    }  // Destructors called here
    
    // 7. Class with delegating constructors
    std::cout << "\n7. CLASS WITH DELEGATING CONSTRUCTORS:" << std::endl;
    
    class DelegatingClass {
    private:
        int value;
        std::string name;
        bool initialized;
        
    public:
        // Default constructor
        DelegatingClass() : DelegatingClass(0, "default") {}
        
        // Constructor with value only
        DelegatingClass(int value) : DelegatingClass(value, "unnamed") {}
        
        // Constructor with name only
        DelegatingClass(const std::string& name) : DelegatingClass(0, name) {}
        
        // Main constructor
        DelegatingClass(int value, const std::string& name) 
            : value(value), name(name), initialized(true) {
            std::cout << "DelegatingClass: " << name << " = " << value << std::endl;
        }
        
        void display() const {
            std::cout << "DelegatingClass: " << name << " = " << value << std::endl;
        }
    };
    
    DelegatingClass dc1;  // Uses default constructor
    DelegatingClass dc2(42);  // Uses value-only constructor
    DelegatingClass dc3("test");  // Uses name-only constructor
    DelegatingClass dc4(100, "custom");  // Uses main constructor
    
    dc1.display();
    dc2.display();
    dc3.display();
    dc4.display();
    
    // 8. Class with const methods and mutable members
    std::cout << "\n8. CLASS WITH CONST METHODS AND MUTABLE MEMBERS:" << std::endl;
    
    class ConstClass {
    private:
        int value;
        mutable int access_count;  // Mutable can be modified in const methods
        
    public:
        ConstClass(int val) : value(val), access_count(0) {}
        
        // Const method
        int get_value() const {
            ++access_count;  // OK because access_count is mutable
            return value;
        }
        
        // Non-const method
        void set_value(int val) {
            value = val;
        }
        
        // Const method that returns access count
        int get_access_count() const {
            return access_count;
        }
    };
    
    const ConstClass const_obj(42);
    std::cout << "const_obj.get_value() = " << const_obj.get_value() << std::endl;
    std::cout << "const_obj.get_value() = " << const_obj.get_value() << std::endl;
    std::cout << "Access count: " << const_obj.get_access_count() << std::endl;
    
    // 9. Class with initialization lists
    std::cout << "\n9. CLASS WITH INITIALIZATION LISTS:" << std::endl;
    
    class InitializationClass {
    private:
        const int const_value;
        int& reference_value;
        std::string name;
        
    public:
        InitializationClass(int& ref, const std::string& n) 
            : const_value(100), reference_value(ref), name(n) {
            std::cout << "InitializationClass: " << name << " initialized" << std::endl;
        }
        
        int get_const_value() const { return const_value; }
        int& get_reference_value() const { return reference_value; }
        const std::string& get_name() const { return name; }
    };
    
    int ref_value = 50;
    InitializationClass init_obj(ref_value, "test");
    
    std::cout << "const_value = " << init_obj.get_const_value() << std::endl;
    std::cout << "reference_value = " << init_obj.get_reference_value() << std::endl;
    
    // 10. Class with virtual destructor
    std::cout << "\n10. CLASS WITH VIRTUAL DESTRUCTOR:" << std::endl;
    
    class BaseClass {
    public:
        BaseClass() {
            std::cout << "BaseClass constructor" << std::endl;
        }
        
        virtual ~BaseClass() {
            std::cout << "BaseClass destructor" << std::endl;
        }
        
        virtual void display() const {
            std::cout << "BaseClass display" << std::endl;
        }
    };
    
    class DerivedClass : public BaseClass {
    public:
        DerivedClass() {
            std::cout << "DerivedClass constructor" << std::endl;
        }
        
        ~DerivedClass() override {
            std::cout << "DerivedClass destructor" << std::endl;
        }
        
        void display() const override {
            std::cout << "DerivedClass display" << std::endl;
        }
    };
    
    {
        std::unique_ptr<BaseClass> ptr = std::make_unique<DerivedClass>();
        ptr->display();
    }  // Virtual destructor called correctly
    
    std::cout << "\nAdvanced classes and constructors demonstration completed!" << std::endl;
    return 0;
}
