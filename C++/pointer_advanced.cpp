/*
 * POINTER ADVANCED EXAMPLES
 * 
 * This file demonstrates advanced pointer concepts:
 * - Smart pointers (unique_ptr, shared_ptr, weak_ptr)
 * - Custom memory allocators
 * - Pointer aliasing and strict aliasing
 * - Memory alignment
 * - Cache-friendly pointer usage
 * - Advanced function pointers and callbacks
 * - Pointer-based data structures
 * - RAII (Resource Acquisition Is Initialization)
 * - Move semantics with pointers
 * - Advanced pointer arithmetic
 * 
 * Learning Objectives:
 * - Master smart pointers for automatic memory management
 * - Understand memory optimization techniques
 * - Learn advanced pointer patterns
 * - Implement complex data structures
 * - Write production-quality pointer code
 * 
 * Prerequisites:
 * - Completed pointer_beginner.cpp and pointer_intermediate.cpp
 * - Understanding of C++ classes and objects
 * - Familiarity with templates
 * - Understanding of move semantics
 * 
 * Key Topics Covered:
 * - Smart pointers (C++11/14/17)
 * - Memory pooling
 * - Custom allocators
 * - Intrusive data structures
 * - Type-safe function pointers
 */

#include <iostream>
#include <memory>      // For smart pointers
#include <vector>
#include <string>
#include <functional>  // For std::function
#include <algorithm>
#include <chrono>
using namespace std;

// ==============================================================================
// SECTION 1: SMART POINTERS - unique_ptr
// ==============================================================================
/*
 * UNIQUE_PTR:
 * 
 * A smart pointer that owns and manages another object through a pointer.
 * Automatically deletes the object when unique_ptr goes out of scope.
 * 
 * Key features:
 * - Exclusive ownership (cannot be copied, only moved)
 * - Zero overhead compared to raw pointer
 * - Automatic memory cleanup
 * - Exception safe
 * 
 * Use when: You need exclusive ownership of a resource
 */

class Resource {
public:
    Resource(string n) : name(n) {
        cout << "   Resource '" << name << "' created" << endl;
    }
    
    ~Resource() {
        cout << "   Resource '" << name << "' destroyed" << endl;
    }
    
    void doWork() {
        cout << "   Resource '" << name << "' is working" << endl;
    }
    
private:
    string name;
};

void uniquePtrDemo() {
    cout << "=== SMART POINTERS - unique_ptr ===" << endl << endl;
    
    // Creating unique_ptr
    cout << "1. Creating unique_ptr:" << endl;
    {
        unique_ptr<Resource> ptr1(new Resource("R1"));
        ptr1->doWork();
        // Automatically deleted when going out of scope
    }
    cout << "   (ptr1 went out of scope, resource auto-deleted)" << endl;
    cout << endl;
    
    // Using make_unique (C++14, preferred way)
    cout << "2. Using make_unique (C++14, preferred):" << endl;
    {
        auto ptr2 = make_unique<Resource>("R2");
        ptr2->doWork();
    }
    cout << "   (ptr2 went out of scope)" << endl;
    cout << endl;
    
    // Moving unique_ptr
    cout << "3. Moving unique_ptr (transfer ownership):" << endl;
    {
        auto ptr3 = make_unique<Resource>("R3");
        auto ptr4 = move(ptr3);  // Transfer ownership to ptr4
        
        if (ptr3 == nullptr) {
            cout << "   ptr3 is now nullptr (ownership transferred)" << endl;
        }
        
        ptr4->doWork();
    }
    cout << endl;
    
    // unique_ptr with arrays
    cout << "4. unique_ptr with Arrays:" << endl;
    {
        auto arr = make_unique<int[]>(5);
        for (int i = 0; i < 5; i++) {
            arr[i] = (i + 1) * 10;
        }
        
        cout << "   Array: ";
        for (int i = 0; i < 5; i++) {
            cout << arr[i] << " ";
        }
        cout << endl;
    }
    cout << "   (Array auto-deleted)" << endl;
    cout << endl;
    
    // Custom deleter
    cout << "5. Custom Deleter:" << endl;
    {
        auto deleter = [](Resource* r) {
            cout << "   Custom deleter called" << endl;
            delete r;
        };
        
        unique_ptr<Resource, decltype(deleter)> ptr5(new Resource("R5"), deleter);
    }
    cout << endl;
}

// ==============================================================================
// SECTION 2: SMART POINTERS - shared_ptr
// ==============================================================================
/*
 * SHARED_PTR:
 * 
 * A smart pointer that retains shared ownership of an object.
 * Multiple shared_ptr instances can own the same object.
 * Object is destroyed when the last shared_ptr is destroyed.
 * 
 * Key features:
 * - Reference counting
 * - Shared ownership
 * - Thread-safe reference counting
 * - Can be copied
 * 
 * Use when: Multiple owners need to share an object
 */

class DataObject {
public:
    DataObject(int v) : value(v) {
        cout << "   DataObject(" << value << ") created" << endl;
    }
    
    ~DataObject() {
        cout << "   DataObject(" << value << ") destroyed" << endl;
    }
    
    int getValue() const { return value; }
    
private:
    int value;
};

void sharedPtrDemo() {
    cout << "=== SMART POINTERS - shared_ptr ===" << endl << endl;
    
    // Creating shared_ptr
    cout << "1. Creating shared_ptr:" << endl;
    {
        shared_ptr<DataObject> ptr1 = make_shared<DataObject>(100);
        cout << "   Use count: " << ptr1.use_count() << endl;
        
        {
            shared_ptr<DataObject> ptr2 = ptr1;  // Copy, increases reference count
            cout << "   Use count after copy: " << ptr1.use_count() << endl;
            cout << "   ptr1 value: " << ptr1->getValue() << endl;
            cout << "   ptr2 value: " << ptr2->getValue() << endl;
        }
        
        cout << "   Use count after ptr2 destroyed: " << ptr1.use_count() << endl;
    }
    cout << "   (Last shared_ptr destroyed, object deleted)" << endl;
    cout << endl;
    
    // Shared ownership example
    cout << "2. Shared Ownership Example:" << endl;
    vector<shared_ptr<DataObject>> vec;
    {
        auto obj = make_shared<DataObject>(200);
        vec.push_back(obj);
        vec.push_back(obj);
        vec.push_back(obj);
        cout << "   Use count: " << obj.use_count() << endl;
    }
    cout << "   Original pointer destroyed, but object still alive" << endl;
    cout << "   Use count: " << vec[0].use_count() << endl;
    vec.clear();
    cout << "   (Vector cleared, object finally deleted)" << endl;
    cout << endl;
    
    // Aliasing constructor
    cout << "3. Shared_ptr Aliasing:" << endl;
    {
        struct Pair {
            int first;
            int second;
        };
        
        auto pairPtr = make_shared<Pair>();
        pairPtr->first = 10;
        pairPtr->second = 20;
        
        // Create shared_ptr that shares ownership but points to member
        shared_ptr<int> firstPtr(pairPtr, &pairPtr->first);
        cout << "   First value: " << *firstPtr << endl;
        cout << "   Use count: " << firstPtr.use_count() << endl;
    }
    cout << endl;
}

// ==============================================================================
// SECTION 3: SMART POINTERS - weak_ptr
// ==============================================================================
/*
 * WEAK_PTR:
 * 
 * A smart pointer that holds a non-owning reference to an object
 * managed by shared_ptr.
 * 
 * Key features:
 * - Doesn't increase reference count
 * - Can detect if object still exists
 * - Breaks circular references
 * - Must be converted to shared_ptr to access object
 * 
 * Use when: You need to observe an object without owning it
 */

class Node {
public:
    int value;
    shared_ptr<Node> next;      // Strong reference
    weak_ptr<Node> prev;        // Weak reference (breaks cycle)
    
    Node(int v) : value(v) {
        cout << "   Node(" << value << ") created" << endl;
    }
    
    ~Node() {
        cout << "   Node(" << value << ") destroyed" << endl;
    }
};

void weakPtrDemo() {
    cout << "=== SMART POINTERS - weak_ptr ===" << endl << endl;
    
    // Basic weak_ptr usage
    cout << "1. Basic weak_ptr Usage:" << endl;
    weak_ptr<DataObject> weakPtr;
    {
        auto sharedPtr = make_shared<DataObject>(300);
        weakPtr = sharedPtr;  // weak_ptr observes the object
        
        cout << "   Shared use count: " << sharedPtr.use_count() << endl;
        cout << "   Weak use count: " << weakPtr.use_count() << endl;
        
        // Access object through weak_ptr
        if (auto tempPtr = weakPtr.lock()) {  // Convert to shared_ptr
            cout << "   Value: " << tempPtr->getValue() << endl;
        }
    }
    
    // Object is destroyed, weak_ptr knows it
    cout << "   After shared_ptr destroyed:" << endl;
    if (weakPtr.expired()) {
        cout << "   weak_ptr: Object no longer exists" << endl;
    }
    cout << endl;
    
    // Breaking circular references
    cout << "2. Breaking Circular References:" << endl;
    {
        auto node1 = make_shared<Node>(1);
        auto node2 = make_shared<Node>(2);
        
        node1->next = node2;  // node1 -> node2 (strong)
        node2->prev = node1;  // node2 -> node1 (weak, breaks cycle)
        
        cout << "   Node 1 use count: " << node1.use_count() << endl;
        cout << "   Node 2 use count: " << node2.use_count() << endl;
    }
    cout << "   (Both nodes properly destroyed, no memory leak)" << endl;
    cout << endl;
    
    // Observer pattern with weak_ptr
    cout << "3. Observer Pattern:" << endl;
    {
        auto subject = make_shared<DataObject>(400);
        vector<weak_ptr<DataObject>> observers;
        
        observers.push_back(subject);
        observers.push_back(subject);
        
        cout << "   Subject use count: " << subject.use_count() << endl;
        cout << "   Observers don't increase reference count" << endl;
    }
    cout << endl;
}

// ==============================================================================
// SECTION 4: COMPARISON OF SMART POINTERS
// ==============================================================================
/*
 * WHEN TO USE WHICH SMART POINTER:
 * 
 * unique_ptr:
 * - Default choice for ownership
 * - No overhead
 * - Cannot be copied, only moved
 * - Use: Single ownership
 * 
 * shared_ptr:
 * - Multiple owners
 * - Reference counting overhead
 * - Thread-safe counting
 * - Use: Shared ownership
 * 
 * weak_ptr:
 * - Non-owning reference
 * - Breaks circular references
 * - Can check if object exists
 * - Use: Observers, caches
 * 
 * Raw pointer:
 * - Non-owning reference (modern C++)
 * - No overhead
 * - No cleanup responsibility
 * - Use: Just observing, not owning
 */

void smartPointerComparison() {
    cout << "=== SMART POINTER COMPARISON ===" << endl << endl;
    
    cout << "Memory Overhead:" << endl;
    cout << "   Raw pointer: " << sizeof(int*) << " bytes" << endl;
    cout << "   unique_ptr: " << sizeof(unique_ptr<int>) << " bytes" << endl;
    cout << "   shared_ptr: " << sizeof(shared_ptr<int>) << " bytes" << endl;
    cout << "   weak_ptr: " << sizeof(weak_ptr<int>) << " bytes" << endl;
    cout << endl;
    
    cout << "Decision Tree:" << endl;
    cout << "   1. Need to own? No -> Use raw pointer (observer)" << endl;
    cout << "   2. Need to own? Yes -> Continue..." << endl;
    cout << "   3. Single owner? Yes -> Use unique_ptr" << endl;
    cout << "   4. Single owner? No -> Use shared_ptr" << endl;
    cout << "   5. Need weak reference? -> Use weak_ptr with shared_ptr" << endl;
    cout << endl;
}

// ==============================================================================
// SECTION 5: ADVANCED FUNCTION POINTERS - std::function
// ==============================================================================
/*
 * STD::FUNCTION:
 * 
 * A general-purpose polymorphic function wrapper.
 * Can store, copy, and invoke any callable target.
 * 
 * Can hold:
 * - Function pointers
 * - Lambda expressions
 * - Function objects (functors)
 * - Member function pointers
 * 
 * Preferred over raw function pointers in modern C++
 */

// Regular function
int addNumbers(int a, int b) {
    return a + b;
}

// Functor (function object)
class Multiplier {
public:
    int operator()(int a, int b) const {
        return a * b;
    }
};

void stdFunctionDemo() {
    cout << "=== ADVANCED FUNCTION POINTERS - std::function ===" << endl << endl;
    
    // Function pointer
    cout << "1. Storing Function Pointer:" << endl;
    function<int(int, int)> func1 = addNumbers;
    cout << "   5 + 3 = " << func1(5, 3) << endl;
    cout << endl;
    
    // Lambda
    cout << "2. Storing Lambda:" << endl;
    function<int(int, int)> func2 = [](int a, int b) { return a - b; };
    cout << "   5 - 3 = " << func2(5, 3) << endl;
    cout << endl;
    
    // Functor
    cout << "3. Storing Functor:" << endl;
    function<int(int, int)> func3 = Multiplier();
    cout << "   5 * 3 = " << func3(5, 3) << endl;
    cout << endl;
    
    // Container of functions
    cout << "4. Container of Functions:" << endl;
    vector<function<int(int, int)>> operations;
    operations.push_back(addNumbers);
    operations.push_back([](int a, int b) { return a - b; });
    operations.push_back(Multiplier());
    
    const char* names[] = {"Add", "Subtract", "Multiply"};
    for (size_t i = 0; i < operations.size(); i++) {
        cout << "   " << names[i] << ": 10 and 5 = " << operations[i](10, 5) << endl;
    }
    cout << endl;
    
    // Callback pattern
    cout << "5. Callback Pattern:" << endl;
    auto processData = [](vector<int>& data, function<void(int&)> callback) {
        for (auto& val : data) {
            callback(val);
        }
    };
    
    vector<int> numbers = {1, 2, 3, 4, 5};
    cout << "   Original: ";
    for (int n : numbers) cout << n << " ";
    cout << endl;
    
    processData(numbers, [](int& n) { n *= 2; });
    cout << "   After doubling: ";
    for (int n : numbers) cout << n << " ";
    cout << endl;
    cout << endl;
}

// ==============================================================================
// SECTION 6: CUSTOM MEMORY ALLOCATOR
// ==============================================================================
/*
 * CUSTOM MEMORY ALLOCATOR:
 * 
 * Sometimes you need to control memory allocation for:
 * - Performance (memory pools)
 * - Memory tracking
 * - Special memory regions
 * - Debugging
 * 
 * This is a simple memory pool implementation.
 */

template<typename T, size_t PoolSize>
class MemoryPool {
private:
    union Block {
        T data;
        Block* next;
    };
    
    Block pool[PoolSize];
    Block* freeList;
    size_t allocated;
    
public:
    MemoryPool() : freeList(nullptr), allocated(0) {
        // Initialize free list
        for (size_t i = 0; i < PoolSize - 1; i++) {
            pool[i].next = &pool[i + 1];
        }
        pool[PoolSize - 1].next = nullptr;
        freeList = &pool[0];
    }
    
    T* allocate() {
        if (freeList == nullptr) {
            throw bad_alloc();
        }
        
        Block* block = freeList;
        freeList = freeList->next;
        allocated++;
        
        return reinterpret_cast<T*>(block);
    }
    
    void deallocate(T* ptr) {
        Block* block = reinterpret_cast<Block*>(ptr);
        block->next = freeList;
        freeList = block;
        allocated--;
    }
    
    size_t getAllocatedCount() const {
        return allocated;
    }
    
    size_t getCapacity() const {
        return PoolSize;
    }
};

void customAllocatorDemo() {
    cout << "=== CUSTOM MEMORY ALLOCATOR ===" << endl << endl;
    
    cout << "1. Memory Pool Allocator:" << endl;
    MemoryPool<int, 10> pool;
    
    cout << "   Pool capacity: " << pool.getCapacity() << endl;
    cout << "   Allocated: " << pool.getAllocatedCount() << endl;
    cout << endl;
    
    // Allocate some memory
    cout << "2. Allocating from Pool:" << endl;
    int* ptr1 = pool.allocate();
    int* ptr2 = pool.allocate();
    int* ptr3 = pool.allocate();
    
    *ptr1 = 100;
    *ptr2 = 200;
    *ptr3 = 300;
    
    cout << "   Allocated: " << pool.getAllocatedCount() << endl;
    cout << "   Values: " << *ptr1 << ", " << *ptr2 << ", " << *ptr3 << endl;
    cout << endl;
    
    // Deallocate
    cout << "3. Deallocating:" << endl;
    pool.deallocate(ptr2);
    cout << "   Allocated after deallocation: " << pool.getAllocatedCount() << endl;
    cout << endl;
    
    // Reuse
    cout << "4. Reusing Memory:" << endl;
    int* ptr4 = pool.allocate();
    *ptr4 = 400;
    cout << "   New allocation uses freed memory" << endl;
    cout << "   Allocated: " << pool.getAllocatedCount() << endl;
    cout << endl;
}

// ==============================================================================
// SECTION 7: INTRUSIVE LINKED LIST
// ==============================================================================
/*
 * INTRUSIVE DATA STRUCTURES:
 * 
 * Instead of having a container manage nodes separately,
 * the nodes contain the linking pointers themselves.
 * 
 * Advantages:
 * - No extra allocations for node structure
 * - Better cache locality
 * - Object can know if it's in a container
 * 
 * Used in: Linux kernel, high-performance systems
 */

class IntrusiveNode {
public:
    int data;
    IntrusiveNode* next;
    IntrusiveNode* prev;
    
    IntrusiveNode(int d) : data(d), next(nullptr), prev(nullptr) {}
};

class IntrusiveList {
private:
    IntrusiveNode* head;
    IntrusiveNode* tail;
    size_t size;
    
public:
    IntrusiveList() : head(nullptr), tail(nullptr), size(0) {}
    
    void pushBack(IntrusiveNode* node) {
        if (tail == nullptr) {
            head = tail = node;
            node->prev = node->next = nullptr;
        } else {
            tail->next = node;
            node->prev = tail;
            node->next = nullptr;
            tail = node;
        }
        size++;
    }
    
    void remove(IntrusiveNode* node) {
        if (node->prev) {
            node->prev->next = node->next;
        } else {
            head = node->next;
        }
        
        if (node->next) {
            node->next->prev = node->prev;
        } else {
            tail = node->prev;
        }
        
        node->prev = node->next = nullptr;
        size--;
    }
    
    void display() const {
        IntrusiveNode* current = head;
        while (current) {
            cout << current->data << " ";
            current = current->next;
        }
        cout << endl;
    }
    
    size_t getSize() const { return size; }
};

void intrusiveDataStructures() {
    cout << "=== INTRUSIVE DATA STRUCTURES ===" << endl << endl;
    
    cout << "1. Intrusive Linked List:" << endl;
    IntrusiveList list;
    
    IntrusiveNode node1(10);
    IntrusiveNode node2(20);
    IntrusiveNode node3(30);
    IntrusiveNode node4(40);
    
    list.pushBack(&node1);
    list.pushBack(&node2);
    list.pushBack(&node3);
    list.pushBack(&node4);
    
    cout << "   List: ";
    list.display();
    cout << "   Size: " << list.getSize() << endl;
    cout << endl;
    
    cout << "2. Removing Node:" << endl;
    list.remove(&node2);
    cout << "   List after removing 20: ";
    list.display();
    cout << "   Size: " << list.getSize() << endl;
    cout << endl;
    
    cout << "Advantages:" << endl;
    cout << "   - No extra node allocation" << endl;
    cout << "   - Better cache locality" << endl;
    cout << "   - Object knows if it's in list" << endl;
    cout << endl;
}

// ==============================================================================
// SECTION 8: RAII (Resource Acquisition Is Initialization)
// ==============================================================================
/*
 * RAII PATTERN:
 * 
 * A programming idiom where resource lifetime is tied to object lifetime.
 * 
 * Principles:
 * - Acquire resources in constructor
 * - Release resources in destructor
 * - Resource is always in valid state
 * - Exception safe
 * 
 * Smart pointers are examples of RAII!
 */

class FileHandle {
private:
    string filename;
    bool isOpen;
    
public:
    FileHandle(const string& fname) : filename(fname), isOpen(false) {
        cout << "   Opening file: " << filename << endl;
        isOpen = true;
        // In real code: open file here
    }
    
    ~FileHandle() {
        if (isOpen) {
            cout << "   Closing file: " << filename << endl;
            // In real code: close file here
            isOpen = false;
        }
    }
    
    // Prevent copying
    FileHandle(const FileHandle&) = delete;
    FileHandle& operator=(const FileHandle&) = delete;
    
    // Allow moving
    FileHandle(FileHandle&& other) noexcept 
        : filename(move(other.filename)), isOpen(other.isOpen) {
        other.isOpen = false;
    }
    
    void write(const string& data) {
        if (isOpen) {
            cout << "   Writing to " << filename << ": " << data << endl;
        }
    }
};

class ScopedLock {
private:
    string lockName;
    
public:
    ScopedLock(const string& name) : lockName(name) {
        cout << "   Acquiring lock: " << lockName << endl;
    }
    
    ~ScopedLock() {
        cout << "   Releasing lock: " << lockName << endl;
    }
    
    // Prevent copying and moving
    ScopedLock(const ScopedLock&) = delete;
    ScopedLock& operator=(const ScopedLock&) = delete;
};

void raiiPattern() {
    cout << "=== RAII PATTERN ===" << endl << endl;
    
    cout << "1. File Handle (RAII):" << endl;
    {
        FileHandle file("data.txt");
        file.write("Hello, RAII!");
        // File automatically closed when going out of scope
    }
    cout << "   (File handle destroyed, file closed)" << endl;
    cout << endl;
    
    cout << "2. Scoped Lock (RAII):" << endl;
    {
        ScopedLock lock("critical_section");
        cout << "   Doing work in critical section..." << endl;
        // Lock automatically released when going out of scope
    }
    cout << "   (Lock destroyed, lock released)" << endl;
    cout << endl;
    
    cout << "3. Exception Safety:" << endl;
    try {
        FileHandle file("important.dat");
        file.write("Some data");
        // throw runtime_error("Something went wrong!");
        // Even if exception thrown, destructor still runs!
    } catch (...) {
        cout << "   Exception caught, but file still closed properly" << endl;
    }
    cout << endl;
}

// ==============================================================================
// SECTION 9: MOVE SEMANTICS WITH POINTERS
// ==============================================================================
/*
 * MOVE SEMANTICS:
 * 
 * Transfer ownership of resources instead of copying.
 * 
 * Benefits:
 * - Eliminates unnecessary copies
 * - Improves performance
 * - Enables return of heavy objects
 * - Enables transfer of unique ownership
 */

class Buffer {
private:
    int* data;
    size_t size;
    
public:
    // Constructor
    Buffer(size_t s) : size(s), data(new int[s]) {
        cout << "   Buffer(" << size << ") created" << endl;
        for (size_t i = 0; i < size; i++) {
            data[i] = i * 10;
        }
    }
    
    // Destructor
    ~Buffer() {
        if (data) {
            cout << "   Buffer(" << size << ") destroyed" << endl;
            delete[] data;
        }
    }
    
    // Copy constructor (expensive!)
    Buffer(const Buffer& other) : size(other.size), data(new int[other.size]) {
        cout << "   Buffer copied (expensive!)" << endl;
        for (size_t i = 0; i < size; i++) {
            data[i] = other.data[i];
        }
    }
    
    // Move constructor (cheap!)
    Buffer(Buffer&& other) noexcept : size(other.size), data(other.data) {
        cout << "   Buffer moved (cheap!)" << endl;
        other.data = nullptr;
        other.size = 0;
    }
    
    // Copy assignment
    Buffer& operator=(const Buffer& other) {
        if (this != &other) {
            delete[] data;
            size = other.size;
            data = new int[size];
            for (size_t i = 0; i < size; i++) {
                data[i] = other.data[i];
            }
            cout << "   Buffer copy assigned" << endl;
        }
        return *this;
    }
    
    // Move assignment
    Buffer& operator=(Buffer&& other) noexcept {
        if (this != &other) {
            delete[] data;
            size = other.size;
            data = other.data;
            other.data = nullptr;
            other.size = 0;
            cout << "   Buffer move assigned" << endl;
        }
        return *this;
    }
    
    void display() const {
        if (data) {
            cout << "   Buffer: ";
            for (size_t i = 0; i < size; i++) {
                cout << data[i] << " ";
            }
            cout << endl;
        }
    }
};

Buffer createBuffer(size_t size) {
    Buffer buf(size);
    return buf;  // Move semantics used here
}

void moveSemanticsWithPointers() {
    cout << "=== MOVE SEMANTICS WITH POINTERS ===" << endl << endl;
    
    cout << "1. Copy vs Move:" << endl;
    Buffer buf1(5);
    Buffer buf2 = buf1;           // Copy (expensive)
    Buffer buf3 = move(buf1);     // Move (cheap)
    cout << endl;
    
    cout << "2. Return Value Optimization:" << endl;
    Buffer buf4 = createBuffer(3);  // Move, not copy
    buf4.display();
    cout << endl;
    
    cout << "3. Moving into Container:" << endl;
    vector<Buffer> buffers;
    buffers.push_back(Buffer(4));  // Move, not copy
    cout << endl;
}

// ==============================================================================
// SECTION 10: POINTER BEST PRACTICES SUMMARY
// ==============================================================================
/*
 * MODERN C++ POINTER BEST PRACTICES:
 * 
 * 1. Prefer smart pointers over raw pointers
 * 2. Use unique_ptr as default
 * 3. Use shared_ptr when you need shared ownership
 * 4. Use weak_ptr to break cycles
 * 5. Use raw pointers only for observation (non-owning)
 * 6. Never use 'new' directly, use make_unique/make_shared
 * 7. Follow RAII principles
 * 8. Use move semantics to transfer ownership
 * 9. Use std::function for callbacks
 * 10. Avoid manual memory management when possible
 */

void bestPracticesSummary() {
    cout << "=== POINTER BEST PRACTICES SUMMARY ===" << endl << endl;
    
    cout << "Modern C++ Pointer Guidelines:" << endl;
    cout << endl;
    
    cout << "1. DEFAULT CHOICE - unique_ptr:" << endl;
    auto ptr = make_unique<int>(42);
    cout << "   auto ptr = make_unique<int>(42);" << endl;
    cout << endl;
    
    cout << "2. SHARED OWNERSHIP - shared_ptr:" << endl;
    auto shared = make_shared<string>("shared data");
    auto copy = shared;
    cout << "   auto shared = make_shared<string>(\"data\");" << endl;
    cout << "   Use count: " << shared.use_count() << endl;
    cout << endl;
    
    cout << "3. OBSERVATION - raw pointer:" << endl;
    int value = 100;
    int* observer = &value;  // Just observing, not owning
    cout << "   int* observer = &value;  // Non-owning" << endl;
    cout << endl;
    
    cout << "4. CONTAINERS:" << endl;
    vector<unique_ptr<int>> vec;
    vec.push_back(make_unique<int>(1));
    vec.push_back(make_unique<int>(2));
    cout << "   vector<unique_ptr<int>> vec;" << endl;
    cout << "   vec.push_back(make_unique<int>(1));" << endl;
    cout << endl;
    
    cout << "Key Principles:" << endl;
    cout << "   ✓ Use smart pointers" << endl;
    cout << "   ✓ Follow RAII" << endl;
    cout << "   ✓ Prefer unique_ptr" << endl;
    cout << "   ✓ Use move semantics" << endl;
    cout << "   ✓ Avoid manual memory management" << endl;
    cout << "   ✓ Make ownership explicit" << endl;
    cout << "   ✓ Use const correctness" << endl;
    cout << "   ✓ Write exception-safe code" << endl;
    cout << endl;
}

// ==============================================================================
// MAIN FUNCTION - RUNS ALL EXAMPLES
// ==============================================================================

int main() {
    cout << "\n";
    cout << "╔════════════════════════════════════════════════════════════╗" << endl;
    cout << "║        POINTER ADVANCED TUTORIAL - C++                     ║" << endl;
    cout << "║                                                            ║" << endl;
    cout << "║  Master modern C++ pointer techniques and best practices  ║" << endl;
    cout << "╚════════════════════════════════════════════════════════════╝" << endl;
    cout << "\n";
    
    uniquePtrDemo();
    sharedPtrDemo();
    weakPtrDemo();
    smartPointerComparison();
    stdFunctionDemo();
    customAllocatorDemo();
    intrusiveDataStructures();
    raiiPattern();
    moveSemanticsWithPointers();
    bestPracticesSummary();
    
    cout << "╔════════════════════════════════════════════════════════════╗" << endl;
    cout << "║  End of Pointer Advanced Tutorial                          ║" << endl;
    cout << "║                                                            ║" << endl;
    cout << "║  You now have mastery of C++ pointers!                     ║" << endl;
    cout << "║  Practice these concepts in real projects.                 ║" << endl;
    cout << "╚════════════════════════════════════════════════════════════╝" << endl;
    
    return 0;
}

