#include <iostream>
#include <string>
#include <vector>
#include <memory>

// Demonstrates advanced class design concepts
int main() {
    std::cout << "Advanced Class Design Demonstration" << std::endl;
    std::cout << "====================================" << std::endl;
    
    // 1. RAII (Resource Acquisition Is Initialization)
    std::cout << "\n1. RAII (RESOURCE ACQUISITION IS INITIALIZATION):" << std::endl;
    
    class FileManager {
    private:
        std::string filename;
        bool is_open;
    public:
        FileManager(const std::string& name) : filename(name), is_open(false) {
            std::cout << "  FileManager created for: " << filename << std::endl;
            // Simulate file opening
            is_open = true;
            std::cout << "  File opened: " << filename << std::endl;
        }
        
        ~FileManager() {
            if (is_open) {
                std::cout << "  File closed: " << filename << std::endl;
            }
        }
        
        // Delete copy constructor and assignment
        FileManager(const FileManager&) = delete;
        FileManager& operator=(const FileManager&) = delete;
        
        // Move constructor
        FileManager(FileManager&& other) noexcept 
            : filename(std::move(other.filename)), is_open(other.is_open) {
            other.is_open = false;
            std::cout << "  FileManager moved" << std::endl;
        }
        
        // Move assignment
        FileManager& operator=(FileManager&& other) noexcept {
            if (this != &other) {
                if (is_open) {
                    std::cout << "  Closing previous file: " << filename << std::endl;
                }
                filename = std::move(other.filename);
                is_open = other.is_open;
                other.is_open = false;
                std::cout << "  FileManager move assigned" << std::endl;
            }
            return *this;
        }
        
        void write(const std::string& data) {
            if (is_open) {
                std::cout << "  Writing to file: " << data << std::endl;
            }
        }
        
        std::string getFilename() const { return filename; }
    };
    
    {
        FileManager file1("data.txt");
        file1.write("Hello, World!");
        
        FileManager file2 = std::move(file1);
        file2.write("More data");
    }
    std::cout << "  Files automatically closed when going out of scope" << std::endl;
    
    // 2. Move Semantics
    std::cout << "\n2. MOVE SEMANTICS:" << std::endl;
    
    class MovableResource {
    private:
        std::vector<int> data;
        std::string name;
    public:
        MovableResource(const std::string& n, size_t size) : name(n) {
            data.resize(size);
            std::iota(data.begin(), data.end(), 0);
            std::cout << "  Created MovableResource: " << name << " with " << size << " elements" << std::endl;
        }
        
        // Copy constructor
        MovableResource(const MovableResource& other) : data(other.data), name(other.name + "_copy") {
            std::cout << "  Copy constructor called for: " << name << std::endl;
        }
        
        // Move constructor
        MovableResource(MovableResource&& other) noexcept 
            : data(std::move(other.data)), name(std::move(other.name)) {
            std::cout << "  Move constructor called for: " << name << std::endl;
        }
        
        // Copy assignment
        MovableResource& operator=(const MovableResource& other) {
            if (this != &other) {
                data = other.data;
                name = other.name + "_assigned";
                std::cout << "  Copy assignment called for: " << name << std::endl;
            }
            return *this;
        }
        
        // Move assignment
        MovableResource& operator=(MovableResource&& other) noexcept {
            if (this != &other) {
                data = std::move(other.data);
                name = std::move(other.name);
                std::cout << "  Move assignment called for: " << name << std::endl;
            }
            return *this;
        }
        
        size_t size() const { return data.size(); }
        const std::string& getName() const { return name; }
    };
    
    MovableResource resource1("Resource1", 1000);
    MovableResource resource2 = std::move(resource1);  // Move constructor
    MovableResource resource3("Resource3", 500);
    resource3 = std::move(resource2);  // Move assignment
    
    std::cout << "  Final resource: " << resource3.getName() << " with " << resource3.size() << " elements" << std::endl;
    
    // 3. Exception Safety
    std::cout << "\n3. EXCEPTION SAFETY:" << std::endl;
    
    class ExceptionSafeClass {
    private:
        std::vector<int> data;
        std::string name;
    public:
        ExceptionSafeClass(const std::string& n, size_t size) : name(n) {
            try {
                data.resize(size);
                std::iota(data.begin(), data.end(), 0);
                std::cout << "  ExceptionSafeClass created: " << name << std::endl;
            } catch (const std::exception& e) {
                std::cout << "  Exception during construction: " << e.what() << std::endl;
                throw;
            }
        }
        
        ~ExceptionSafeClass() {
            std::cout << "  ExceptionSafeClass destroyed: " << name << std::endl;
        }
        
        void safeOperation() {
            try {
                if (data.empty()) {
                    throw std::runtime_error("Data is empty");
                }
                std::cout << "  Safe operation completed for: " << name << std::endl;
            } catch (const std::exception& e) {
                std::cout << "  Exception in safe operation: " << e.what() << std::endl;
                throw;
            }
        }
        
        void unsafeOperation() noexcept {
            // This function promises not to throw exceptions
            if (!data.empty()) {
                std::cout << "  Unsafe operation completed for: " << name << std::endl;
            }
        }
    };
    
    try {
        ExceptionSafeClass safe_obj("SafeObject", 100);
        safe_obj.safeOperation();
        safe_obj.unsafeOperation();
    } catch (const std::exception& e) {
        std::cout << "  Caught exception: " << e.what() << std::endl;
    }
    
    // 4. Design Patterns
    std::cout << "\n4. DESIGN PATTERNS:" << std::endl;
    
    // Singleton Pattern
    class Singleton {
    private:
        static std::unique_ptr<Singleton> instance;
        std::string data;
        
        Singleton() : data("Singleton data") {
            std::cout << "  Singleton instance created" << std::endl;
        }
        
    public:
        static Singleton& getInstance() {
            if (!instance) {
                instance = std::unique_ptr<Singleton>(new Singleton());
            }
            return *instance;
        }
        
        const std::string& getData() const { return data; }
        void setData(const std::string& new_data) { data = new_data; }
        
        // Delete copy constructor and assignment
        Singleton(const Singleton&) = delete;
        Singleton& operator=(const Singleton&) = delete;
    };
    
    std::unique_ptr<Singleton> Singleton::instance = nullptr;
    
    Singleton& singleton1 = Singleton::getInstance();
    Singleton& singleton2 = Singleton::getInstance();
    
    std::cout << "  Singleton data: " << singleton1.getData() << std::endl;
    singleton1.setData("Modified data");
    std::cout << "  Modified data: " << singleton2.getData() << std::endl;
    
    // Factory Pattern
    class Shape {
    public:
        virtual ~Shape() = default;
        virtual void draw() const = 0;
        virtual double area() const = 0;
    };
    
    class Circle : public Shape {
    private:
        double radius;
    public:
        Circle(double r) : radius(r) {}
        void draw() const override {
            std::cout << "  Drawing circle with radius " << radius << std::endl;
        }
        double area() const override {
            return 3.14159 * radius * radius;
        }
    };
    
    class Rectangle : public Shape {
    private:
        double width, height;
    public:
        Rectangle(double w, double h) : width(w), height(h) {}
        void draw() const override {
            std::cout << "  Drawing rectangle " << width << "x" << height << std::endl;
        }
        double area() const override {
            return width * height;
        }
    };
    
    class ShapeFactory {
    public:
        static std::unique_ptr<Shape> createShape(const std::string& type, double param1, double param2 = 0) {
            if (type == "circle") {
                return std::make_unique<Circle>(param1);
            } else if (type == "rectangle") {
                return std::make_unique<Rectangle>(param1, param2);
            }
            return nullptr;
        }
    };
    
    auto circle = ShapeFactory::createShape("circle", 5.0);
    auto rectangle = ShapeFactory::createShape("rectangle", 4.0, 6.0);
    
    if (circle) {
        circle->draw();
        std::cout << "  Circle area: " << circle->area() << std::endl;
    }
    
    if (rectangle) {
        rectangle->draw();
        std::cout << "  Rectangle area: " << rectangle->area() << std::endl;
    }
    
    // 5. Smart Pointers and Memory Management
    std::cout << "\n5. SMART POINTERS AND MEMORY MANAGEMENT:" << std::endl;
    
    class ManagedResource {
    private:
        int id;
        std::string data;
    public:
        ManagedResource(int i, const std::string& d) : id(i), data(d) {
            std::cout << "  ManagedResource " << id << " created with data: " << data << std::endl;
        }
        
        ~ManagedResource() {
            std::cout << "  ManagedResource " << id << " destroyed" << std::endl;
        }
        
        int getId() const { return id; }
        const std::string& getData() const { return data; }
    };
    
    // unique_ptr
    auto unique_resource = std::make_unique<ManagedResource>(1, "Unique data");
    std::cout << "  Unique resource ID: " << unique_resource->getId() << std::endl;
    
    // shared_ptr
    auto shared_resource = std::make_shared<ManagedResource>(2, "Shared data");
    auto shared_copy = shared_resource;
    std::cout << "  Shared resource ID: " << shared_resource->getId() << std::endl;
    std::cout << "  Shared copy ID: " << shared_copy->getId() << std::endl;
    
    // weak_ptr
    std::weak_ptr<ManagedResource> weak_resource = shared_resource;
    if (auto locked = weak_resource.lock()) {
        std::cout << "  Weak pointer locked, ID: " << locked->getId() << std::endl;
    }
    
    // 6. Performance Optimization
    std::cout << "\n6. PERFORMANCE OPTIMIZATION:" << std::endl;
    
    class OptimizedContainer {
    private:
        std::vector<int> data;
        mutable std::optional<int> cached_sum;
    public:
        OptimizedContainer(std::initializer_list<int> init) : data(init) {}
        
        // Const correctness
        int get(int index) const {
            return data[index];
        }
        
        // Mutable for caching
        int sum() const {
            if (!cached_sum) {
                cached_sum = std::accumulate(data.begin(), data.end(), 0);
                std::cout << "  Sum calculated and cached" << std::endl;
            }
            return *cached_sum;
        }
        
        void add(int value) {
            data.push_back(value);
            cached_sum.reset();  // Invalidate cache
        }
        
        size_t size() const { return data.size(); }
    };
    
    OptimizedContainer container({1, 2, 3, 4, 5});
    std::cout << "  First sum: " << container.sum() << std::endl;
    std::cout << "  Second sum (cached): " << container.sum() << std::endl;
    
    container.add(6);
    std::cout << "  After adding element, sum: " << container.sum() << std::endl;
    
    std::cout << "\nAdvanced class design demonstration completed!" << std::endl;
    return 0;
}
