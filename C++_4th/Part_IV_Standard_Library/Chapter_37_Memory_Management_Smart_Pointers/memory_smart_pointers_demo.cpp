#include <iostream>
#include <memory>
#include <vector>
#include <string>
#include <fstream>

// Demonstrates memory management and smart pointers
int main() {
    std::cout << "Memory Management and Smart Pointers Demonstration" << std::endl;
    std::cout << "===================================================" << std::endl;
    
    // 1. Smart Pointer Basics
    std::cout << "\n1. SMART POINTER BASICS:" << std::endl;
    
    class Resource {
    private:
        int id;
        std::string data;
    public:
        Resource(int i, const std::string& d) : id(i), data(d) {
            std::cout << "  Resource " << id << " created with data: " << data << std::endl;
        }
        
        ~Resource() {
            std::cout << "  Resource " << id << " destroyed" << std::endl;
        }
        
        int getId() const { return id; }
        const std::string& getData() const { return data; }
        
        void doWork() {
            std::cout << "  Resource " << id << " is working with data: " << data << std::endl;
        }
    };
    
    // unique_ptr
    std::cout << "  Using unique_ptr:" << std::endl;
    auto unique_resource = std::make_unique<Resource>(1, "Unique data");
    unique_resource->doWork();
    std::cout << "    Resource ID: " << unique_resource->getId() << std::endl;
    
    // Transfer ownership
    auto unique_resource2 = std::move(unique_resource);
    if (!unique_resource) {
        std::cout << "    Original unique_ptr is now empty" << std::endl;
    }
    unique_resource2->doWork();
    
    // shared_ptr
    std::cout << "  Using shared_ptr:" << std::endl;
    auto shared_resource = std::make_shared<Resource>(2, "Shared data");
    auto shared_copy = shared_resource;
    std::cout << "    Reference count: " << shared_resource.use_count() << std::endl;
    shared_resource->doWork();
    shared_copy->doWork();
    
    // weak_ptr
    std::cout << "  Using weak_ptr:" << std::endl;
    std::weak_ptr<Resource> weak_resource = shared_resource;
    std::cout << "    Weak pointer reference count: " << weak_resource.use_count() << std::endl;
    
    if (auto locked = weak_resource.lock()) {
        std::cout << "    Weak pointer locked successfully" << std::endl;
        locked->doWork();
    }
    
    // 2. Custom Deleters
    std::cout << "\n2. CUSTOM DELETERS:" << std::endl;
    
    // Custom deleter for FILE*
    struct FileDeleter {
        void operator()(FILE* file) {
            if (file) {
                std::cout << "  Closing file" << std::endl;
                fclose(file);
            }
        }
    };
    
    // Custom deleter with unique_ptr
    auto file = std::unique_ptr<FILE, FileDeleter>(fopen("test.txt", "w"));
    if (file) {
        fprintf(file.get(), "Hello from custom deleter!\n");
        std::cout << "  File written successfully" << std::endl;
    }
    // File automatically closed by custom deleter
    
    // Lambda deleter
    auto lambda_deleter = [](FILE* f) {
        if (f) {
            std::cout << "  Lambda deleter closing file" << std::endl;
            fclose(f);
        }
    };
    
    auto lambda_file = std::unique_ptr<FILE, decltype(lambda_deleter)>(
        fopen("lambda_test.txt", "w"), lambda_deleter);
    if (lambda_file) {
        fprintf(lambda_file.get(), "Lambda deleter test\n");
    }
    
    // 3. RAII with Smart Pointers
    std::cout << "\n3. RAII WITH SMART POINTERS:" << std::endl;
    
    class RAIIManager {
    private:
        std::unique_ptr<Resource> resource;
        std::string name;
    public:
        RAIIManager(const std::string& n, int id, const std::string& data) 
            : name(n) {
            resource = std::make_unique<Resource>(id, data);
            std::cout << "  RAIIManager '" << name << "' created" << std::endl;
        }
        
        ~RAIIManager() {
            std::cout << "  RAIIManager '" << name << "' destroyed" << std::endl;
        }
        
        // Delete copy constructor and assignment
        RAIIManager(const RAIIManager&) = delete;
        RAIIManager& operator=(const RAIIManager&) = delete;
        
        // Move constructor
        RAIIManager(RAIIManager&& other) noexcept 
            : resource(std::move(other.resource)), name(std::move(other.name)) {
            std::cout << "  RAIIManager moved" << std::endl;
        }
        
        // Move assignment
        RAIIManager& operator=(RAIIManager&& other) noexcept {
            if (this != &other) {
                resource = std::move(other.resource);
                name = std::move(other.name);
                std::cout << "  RAIIManager move assigned" << std::endl;
            }
            return *this;
        }
        
        void useResource() {
            if (resource) {
                resource->doWork();
            }
        }
        
        const std::string& getName() const { return name; }
    };
    
    {
        RAIIManager manager("TestManager", 3, "RAII data");
        manager.useResource();
        std::cout << "  Manager name: " << manager.getName() << std::endl;
    }
    std::cout << "  RAIIManager automatically destroyed" << std::endl;
    
    // 4. Exception Safety with Smart Pointers
    std::cout << "\n4. EXCEPTION SAFETY WITH SMART POINTERS:" << std::endl;
    
    auto createResource = [](int id, const std::string& data) -> std::unique_ptr<Resource> {
        if (data.empty()) {
            throw std::invalid_argument("Data cannot be empty");
        }
        return std::make_unique<Resource>(id, data);
    };
    
    try {
        auto safe_resource = createResource(4, "Safe data");
        safe_resource->doWork();
        
        // This will throw an exception
        auto unsafe_resource = createResource(5, "");
    } catch (const std::exception& e) {
        std::cout << "  Exception caught: " << e.what() << std::endl;
        std::cout << "  Resources automatically cleaned up" << std::endl;
    }
    
    // 5. Circular Reference Problem
    std::cout << "\n5. CIRCULAR REFERENCE PROBLEM:" << std::endl;
    
    class Node {
    public:
        std::string name;
        std::shared_ptr<Node> next;
        std::weak_ptr<Node> prev;  // Use weak_ptr to break circular reference
        
        Node(const std::string& n) : name(n) {
            std::cout << "  Node '" << name << "' created" << std::endl;
        }
        
        ~Node() {
            std::cout << "  Node '" << name << "' destroyed" << std::endl;
        }
        
        void setNext(std::shared_ptr<Node> next_node) {
            next = next_node;
            if (next_node) {
                next_node->prev = std::shared_ptr<Node>(this, [](Node*){}); // Weak reference
            }
        }
    };
    
    auto node1 = std::make_shared<Node>("Node1");
    auto node2 = std::make_shared<Node>("Node2");
    auto node3 = std::make_shared<Node>("Node3");
    
    node1->setNext(node2);
    node2->setNext(node3);
    node3->setNext(node1);  // Circular reference
    
    std::cout << "  Circular reference created" << std::endl;
    std::cout << "  Node1 reference count: " << node1.use_count() << std::endl;
    
    // 6. Smart Pointer Arrays
    std::cout << "\n6. SMART POINTER ARRAYS:" << std::endl;
    
    // unique_ptr with array
    auto array_ptr = std::make_unique<int[]>(5);
    for (int i = 0; i < 5; ++i) {
        array_ptr[i] = i * 2;
    }
    
    std::cout << "  Array elements: ";
    for (int i = 0; i < 5; ++i) {
        std::cout << array_ptr[i] << " ";
    }
    std::cout << std::endl;
    
    // shared_ptr with array (C++17)
    auto shared_array = std::shared_ptr<int[]>(new int[5], std::default_delete<int[]>());
    for (int i = 0; i < 5; ++i) {
        shared_array[i] = i * 3;
    }
    
    std::cout << "  Shared array elements: ";
    for (int i = 0; i < 5; ++i) {
        std::cout << shared_array[i] << " ";
    }
    std::cout << std::endl;
    
    // 7. Performance Comparison
    std::cout << "\n7. PERFORMANCE COMPARISON:" << std::endl;
    
    const int num_objects = 10000;
    
    // Raw pointers
    auto start = std::chrono::high_resolution_clock::now();
    std::vector<Resource*> raw_ptrs;
    for (int i = 0; i < num_objects; ++i) {
        raw_ptrs.push_back(new Resource(i, "Raw data"));
    }
    
    for (Resource* ptr : raw_ptrs) {
        delete ptr;
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto raw_time = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    
    // Smart pointers
    start = std::chrono::high_resolution_clock::now();
    std::vector<std::unique_ptr<Resource>> smart_ptrs;
    for (int i = 0; i < num_objects; ++i) {
        smart_ptrs.push_back(std::make_unique<Resource>(i, "Smart data"));
    }
    end = std::chrono::high_resolution_clock::now();
    auto smart_time = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    
    std::cout << "  Raw pointers time: " << raw_time.count() << " microseconds" << std::endl;
    std::cout << "  Smart pointers time: " << smart_time.count() << " microseconds" << std::endl;
    std::cout << "  Smart pointer overhead: " << (double)smart_time.count() / raw_time.count() << "x" << std::endl;
    
    // 8. Advanced Smart Pointer Usage
    std::cout << "\n8. ADVANCED SMART POINTER USAGE:" << std::endl;
    
    // Polymorphic smart pointers
    class Base {
    public:
        virtual ~Base() = default;
        virtual void print() const = 0;
    };
    
    class Derived : public Base {
    private:
        std::string data;
    public:
        Derived(const std::string& d) : data(d) {}
        void print() const override {
            std::cout << "  Derived: " << data << std::endl;
        }
    };
    
    std::vector<std::unique_ptr<Base>> polymorphic_objects;
    polymorphic_objects.push_back(std::make_unique<Derived>("Polymorphic data 1"));
    polymorphic_objects.push_back(std::make_unique<Derived>("Polymorphic data 2"));
    
    for (const auto& obj : polymorphic_objects) {
        obj->print();
    }
    
    // Factory function returning smart pointer
    auto createDerived = [](const std::string& data) -> std::unique_ptr<Base> {
        return std::make_unique<Derived>(data);
    };
    
    auto factory_obj = createDerived("Factory created");
    factory_obj->print();
    
    // 9. Memory Pool with Smart Pointers
    std::cout << "\n9. MEMORY POOL WITH SMART POINTERS:" << std::endl;
    
    class MemoryPool {
    private:
        std::vector<std::unique_ptr<char[]>> blocks;
        std::vector<bool> used;
        size_t block_size;
        
    public:
        MemoryPool(size_t num_blocks, size_t size) : block_size(size), used(num_blocks, false) {
            for (size_t i = 0; i < num_blocks; ++i) {
                blocks.push_back(std::make_unique<char[]>(block_size));
            }
            std::cout << "  Memory pool created with " << num_blocks << " blocks" << std::endl;
        }
        
        std::unique_ptr<char[], std::function<void(char*)>> allocate() {
            for (size_t i = 0; i < blocks.size(); ++i) {
                if (!used[i]) {
                    used[i] = true;
                    return std::unique_ptr<char[], std::function<void(char*)>>(
                        blocks[i].get(),
                        [this, i](char*) { used[i] = false; }
                    );
                }
            }
            return nullptr;
        }
    };
    
    MemoryPool pool(5, 100);
    auto pool_block1 = pool.allocate();
    auto pool_block2 = pool.allocate();
    
    if (pool_block1 && pool_block2) {
        std::cout << "  Allocated 2 blocks from pool" << std::endl;
    }
    
    // 10. Best Practices
    std::cout << "\n10. BEST PRACTICES:" << std::endl;
    
    // Use make_unique/make_shared
    auto best_practice_obj = std::make_unique<Resource>(6, "Best practice data");
    best_practice_obj->doWork();
    
    // Prefer unique_ptr when possible
    auto unique_best = std::make_unique<Resource>(7, "Unique best practice");
    
    // Use shared_ptr only when sharing is needed
    auto shared_best = std::make_shared<Resource>(8, "Shared best practice");
    auto shared_copy_best = shared_best;  // Now sharing is justified
    
    // Use weak_ptr to break circular references
    std::weak_ptr<Resource> weak_best = shared_best;
    
    // Use auto for type deduction
    auto auto_deduced = std::make_unique<Resource>(9, "Auto deduced");
    
    std::cout << "  Best practices demonstrated" << std::endl;
    
    std::cout << "\nMemory management and smart pointers demonstration completed!" << std::endl;
    return 0;
}
