#include <iostream>
#include <string>
#include <vector>
#include <memory>

// Demonstrates basic class concepts
int main() {
    std::cout << "Classes Demonstration" << std::endl;
    std::cout << "====================" << std::endl;
    
    // 1. Basic Class Definition
    std::cout << "\n1. BASIC CLASS DEFINITION:" << std::endl;
    
    class Point {
    private:
        double x, y;
        
    public:
        // Constructor
        Point(double x_val = 0.0, double y_val = 0.0) : x(x_val), y(y_val) {
            std::cout << "  Point constructed at (" << x << ", " << y << ")" << std::endl;
        }
        
        // Destructor
        ~Point() {
            std::cout << "  Point destroyed" << std::endl;
        }
        
        // Member functions
        double getX() const { return x; }
        double getY() const { return y; }
        
        void setX(double x_val) { x = x_val; }
        void setY(double y_val) { y = y_val; }
        
        void display() const {
            std::cout << "  Point: (" << x << ", " << y << ")" << std::endl;
        }
        
        double distance() const {
            return std::sqrt(x * x + y * y);
        }
    };

    
    Point p1(3.0, 4.0); // instance of the Point class
    p1.display();
    std::cout << "  Distance from origin: " << p1.distance() << std::endl;
    
    // 2. Access Control
    std::cout << "\n2. ACCESS CONTROL:" << std::endl;
    
    class BankAccount {
    private:
        std::string account_number;
        double balance;
        
    public:
        BankAccount(const std::string& acc_num, double initial_balance = 0.0)      // constructor
            : account_number(acc_num), balance(initial_balance) {
            std::cout << "  Account created: " << account_number << std::endl;
        }
        
        void deposit(double amount) {
            if (amount > 0) {
                balance += amount;
                std::cout << "  Deposited: $" << amount << std::endl;
            }
        }
        
        bool withdraw(double amount) {
            if (amount > 0 && amount <= balance) {
                balance -= amount;
                std::cout << "  Withdrawn: $" << amount << std::endl;
                return true;
            }
            std::cout << "  Withdrawal failed: insufficient funds" << std::endl;
            return false;
        }
        
        double getBalance() const {
            return balance;
        }
        
        const std::string& getAccountNumber() const {
            return account_number;
        }
    };
    
    BankAccount myAccount("12345", 1000.0);
    myAccount.deposit(500.0);
    myAccount.withdraw(200.0);
    std::cout << "  Current balance: $" << myAccount.getBalance() << std::endl;
    
    // 3. Member Initialization
    std::cout << "\n3. MEMBER INITIALIZATION:" << std::endl;
    
    class Rectangle {
    private:
        double width, height;
        
    public:
        // Constructor with member initializer list
        Rectangle(double w, double h) : width(w), height(h) {
            std::cout << "  Rectangle created: " << width << " x " << height << std::endl;
        }
        
        // Default constructor
        Rectangle() : width(1.0), height(1.0) {
            std::cout << "  Default rectangle created: " << width << " x " << height << std::endl;
        }
        
        double area() const {
            return width * height;
        }
        
        double perimeter() const {
            return 2 * (width + height);
        }
        
        void display() const {
            std::cout << "  Rectangle: " << width << " x " << height 
                      << " (area: " << area() << ", perimeter: " << perimeter() << ")" << std::endl;
        }
    };
    
    Rectangle rect1(5.0, 3.0);
    Rectangle rect2;  // Default constructor
    rect1.display();
    rect2.display();
    
    // 4. Static Members
    std::cout << "\n4. STATIC MEMBERS:" << std::endl;
    
    class Counter {
    private:
        int value;
        static int total_objects;
        
    public:
        Counter(int val = 0) : value(val) {
            total_objects++;
            std::cout << "  Counter created, total objects: " << total_objects << std::endl;
        }
        
        ~Counter() {
            total_objects--;
            std::cout << "  Counter destroyed, total objects: " << total_objects << std::endl;
        }
        
        int getValue() const { return value; }
        void setValue(int val) { value = val; }
        
        static int getTotalObjects() {
            return total_objects;
        }
        
        static void resetTotal() {
            total_objects = 0;
        }
    };
    
    int Counter::total_objects = 0;
    
    Counter c1(10);
    Counter c2(20);
    std::cout << "  Total Counter objects: " << Counter::getTotalObjects() << std::endl;
    
    // 5. Const Member Functions
    std::cout << "\n5. CONST MEMBER FUNCTIONS:" << std::endl;
    
    class Book {
    private:
        std::string title;
        std::string author;
        int pages;
        
    public:
        Book(const std::string& t, const std::string& a, int p) 
            : title(t), author(a), pages(p) {}
        
        // Const member functions
        const std::string& getTitle() const { return title; }
        const std::string& getAuthor() const { return author; }
        int getPages() const { return pages; }
        
        // Non-const member function
        void setPages(int p) { pages = p; }
        
        void display() const {
            std::cout << "  Book: \"" << title << "\" by " << author 
                      << " (" << pages << " pages)" << std::endl;
        }
    };
    
    const Book dobule_CPP_book("The C++ Programming Language", "Bjarne Stroustrup", 1376);
    dobule_CPP_book.display();
    // book.setPages(1500);  // This would cause a compilation error
    
    Book effective_CPP_book("Effective C++", "Scott Meyers", 256);
    effective_CPP_book.setPages(300);
    effective_CPP_book.display();
    
    // 6. Friend Functions
    std::cout << "\n6. FRIEND FUNCTIONS:" << std::endl;
    
    class Temperature {
    private:
        double celsius;
        
    public:
        Temperature(double c) : celsius(c) {}
        
        double getCelsius() const { return celsius; }
        
        // Friend function
        friend double celsiusToFahrenheit(const Temperature& temp);
        friend std::ostream& operator<<(std::ostream& os, const Temperature& temp);
    };
    
    double celsiusToFahrenheit(const Temperature& temp) {
        return temp.celsius * 9.0 / 5.0 + 32.0;
    }
    
    std::ostream& operator<<(std::ostream& os, const Temperature& temp) {
        os << temp.celsius << "°C";
        return os;
    }
    
    Temperature temp(25.0);
    std::cout << "  Temperature: " << temp << std::endl;
    std::cout << "  Fahrenheit: " << celsiusToFahrenheit(temp) << "°F" << std::endl;
    
    // 7. Nested Classes
    std::cout << "\n7. NESTED CLASSES:" << std::endl;
    
    class LinkedList {
    private:
        class Node {
        public:
            int data;
            Node* next;
            
            Node(int val) : data(val), next(nullptr) {}
        };
        
        Node* head;
        
    public:
        LinkedList() : head(nullptr) {}
        
        ~LinkedList() {
            while (head) {
                Node* temp = head;
                head = head->next;
                delete temp;
            }
        }
        
        void add(int value) {   // insert a new node at the beginning of the LinkedList
            Node* new_node = new Node(value);
            new_node->next = head;
            head = new_node;
        }
        
        void display() const {
            std::cout << "  List: ";
            Node* current = head;
            while (current) {
                std::cout << current->data << " ";
                current = current->next;
            }
            std::cout << std::endl;
        }
    };
    
    LinkedList list;
    list.add(1);
    list.add(2);
    list.add(3);
    list.display();
    
    // 8. Class Templates
    std::cout << "\n8. CLASS TEMPLATES:" << std::endl;
    
    template<typename T>
    class Stack {
    private:
        std::vector<T> elements;
        
    public:
        void push(const T& element) {
            elements.push_back(element);
        }
        
        T pop() {
            if (elements.empty()) {
                throw std::runtime_error("Stack is empty");
            }
            T top = elements.back();
            elements.pop_back();
            return top;
        }
        
        bool empty() const {
            return elements.empty();
        }
        
        size_t size() const {
            return elements.size();
        }
        
        void display() const {
            std::cout << "  Stack contents: ";
            for (const auto& element : elements) {
                std::cout << element << " ";
            }
            std::cout << std::endl;
        }
    };
    
    Stack<int> int_stack;
    int_stack.push(1);
    int_stack.push(2);
    int_stack.push(3);
    int_stack.display();
    
    Stack<std::string> string_stack;
    string_stack.push("Hello");
    string_stack.push("World");
    string_stack.display();
    
    // 9. RAII (Resource Acquisition Is Initialization)
    std::cout << "\n9. RAII (RESOURCE ACQUISITION IS INITIALIZATION):" << std::endl;
    
    class FileManager {
    private:
        std::string filename;
        bool is_open;
        
    public:
        FileManager(const std::string& name) : filename(name), is_open(false) {
            // Simulate file opening
            is_open = true;
            std::cout << "  File opened: " << filename << std::endl;
        }
        
        ~FileManager() {
            if (is_open) {
                // Simulate file closing
                is_open = false;
                std::cout << "  File closed: " << filename << std::endl;
            }
        }
        
        void write(const std::string& data) {
            if (is_open) {
                std::cout << "  Writing to file: " << data << std::endl;
            }
        }
        
        // Delete copy constructor and assignment
        FileManager(const FileManager&) = delete;
        FileManager& operator=(const FileManager&) = delete;
    };
    
    {
        FileManager file("test.txt");
        file.write("Hello, World!");
        // File automatically closed when going out of scope
    }
    
    // 10. Best Practices
    std::cout << "\n10. BEST PRACTICES:" << std::endl;
    
    class GoodClass {
    private:
        std::string name;
        int value;
        
    public:
        // Use explicit for single-parameter constructors
        explicit GoodClass(const std::string& n) : name(n), value(0) {}
        
        GoodClass(const std::string& n, int v) : name(n), value(v) {}
        
        // Use const for getters
        const std::string& getName() const { return name; }
        int getValue() const { return value; }
        
        // Use references for setters when appropriate
        void setName(const std::string& n) { name = n; }
        void setValue(int v) { value = v; }
        
        // Use noexcept when appropriate
        void display() const noexcept {
            std::cout << "  GoodClass: " << name << " = " << value << std::endl;
        }
        
        // Use default for special member functions when appropriate
        GoodClass(const GoodClass&) = default;
        GoodClass& operator=(const GoodClass&) = default;
        GoodClass(GoodClass&&) = default;
        GoodClass& operator=(GoodClass&&) = default;
        ~GoodClass() = default;
    };
    
    GoodClass good("Example", 42);
    good.display();
    
    std::cout << "\nClasses demonstration completed!" << std::endl;
    return 0;
}
