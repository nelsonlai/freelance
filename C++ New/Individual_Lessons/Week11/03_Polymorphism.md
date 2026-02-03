# Lesson 11.3: Polymorphism

## Learning Objectives
- Master virtual function mechanisms and dynamic binding
- Understand virtual function tables and runtime dispatch
- Learn runtime type information (RTTI) and dynamic casting
- Practice with virtual destructors and object slicing
- Explore advanced polymorphism patterns and best practices

## Prerequisites
- Completed Lesson 11.2 (Inheritance)
- Understanding of base and derived classes
- Knowledge of virtual functions and inheritance

## Duration
90 minutes

---

## Lecture Content (30 minutes)

### 1. Virtual Function Mechanism

#### Dynamic Binding vs Static Binding
```cpp
class Base {
public:
    // Non-virtual function (static binding)
    void staticFunction() {
        std::cout << "Base::staticFunction" << std::endl;
    }
    
    // Virtual function (dynamic binding)
    virtual void virtualFunction() {
        std::cout << "Base::virtualFunction" << std::endl;
    }
    
    virtual ~Base() = default;
};

class Derived : public Base {
public:
    // Function hiding (not overriding)
    void staticFunction() {
        std::cout << "Derived::staticFunction" << std::endl;
    }
    
    // Function overriding
    void virtualFunction() override {
        std::cout << "Derived::virtualFunction" << std::endl;
    }
};

void demonstrateBinding() {
    Base* ptr = new Derived();
    
    ptr->staticFunction();    // Static binding: Base::staticFunction
    ptr->virtualFunction();   // Dynamic binding: Derived::virtualFunction
    
    delete ptr;
}
```

### 2. Virtual Function Table (VTable)

#### VTable Structure
```cpp
class Shape {
public:
    virtual ~Shape() = default;
    virtual double area() const = 0;
    virtual double perimeter() const = 0;
    virtual void draw() const = 0;
    virtual void move(double x, double y) = 0;
};

class Circle : public Shape {
private:
    double radius_;
    double x_, y_;
    
public:
    Circle(double radius, double x = 0, double y = 0) 
        : radius_(radius), x_(x), y_(y) {}
    
    double area() const override {
        return 3.14159 * radius_ * radius_;
    }
    
    double perimeter() const override {
        return 2 * 3.14159 * radius_;
    }
    
    void draw() const override {
        std::cout << "Drawing circle at (" << x_ << ", " << y_ 
                  << ") with radius " << radius_ << std::endl;
    }
    
    void move(double x, double y) override {
        x_ += x;
        y_ += y;
    }
};

class Rectangle : public Shape {
private:
    double width_, height_;
    double x_, y_;
    
public:
    Rectangle(double width, double height, double x = 0, double y = 0)
        : width_(width), height_(height), x_(x), y_(y) {}
    
    double area() const override {
        return width_ * height_;
    }
    
    double perimeter() const override {
        return 2 * (width_ + height_);
    }
    
    void draw() const override {
        std::cout << "Drawing rectangle at (" << x_ << ", " << y_ 
                  << ") with size " << width_ << "x" << height_ << std::endl;
    }
    
    void move(double x, double y) override {
        x_ += x;
        y_ += y;
    }
};
```

### 3. Runtime Type Information (RTTI)

#### Dynamic Casting and Type Information
```cpp
class Animal {
public:
    virtual ~Animal() = default;
    virtual void makeSound() const = 0;
};

class Dog : public Animal {
public:
    void makeSound() const override {
        std::cout << "Woof!" << std::endl;
    }
    
    void fetch() const {
        std::cout << "Dog is fetching" << std::endl;
    }
};

class Cat : public Animal {
public:
    void makeSound() const override {
        std::cout << "Meow!" << std::endl;
    }
    
    void purr() const {
        std::cout << "Cat is purring" << std::endl;
    }
};

void demonstrateRTTI() {
    std::vector<std::unique_ptr<Animal>> animals;
    animals.push_back(std::make_unique<Dog>());
    animals.push_back(std::make_unique<Cat>());
    
    for (const auto& animal : animals) {
        animal->makeSound();
        
        // Dynamic casting
        if (auto* dog = dynamic_cast<Dog*>(animal.get())) {
            dog->fetch();
        } else if (auto* cat = dynamic_cast<Cat*>(animal.get())) {
            cat->purr();
        }
        
        // Type information
        std::cout << "Type: " << typeid(*animal).name() << std::endl;
    }
}
```

### 4. Virtual Destructors and Object Slicing

#### Virtual Destructor Importance
```cpp
class Base {
private:
    int* data_;
    
public:
    Base() : data_(new int[100]) {
        std::cout << "Base constructor" << std::endl;
    }
    
    virtual ~Base() {  // Virtual destructor
        delete[] data_;
        std::cout << "Base destructor" << std::endl;
    }
    
    virtual void process() const {
        std::cout << "Base::process" << std::endl;
    }
};

class Derived : public Base {
private:
    std::string* text_;
    
public:
    Derived() : text_(new std::string("Derived data")) {
        std::cout << "Derived constructor" << std::endl;
    }
    
    ~Derived() override {  // Override virtual destructor
        delete text_;
        std::cout << "Derived destructor" << std::endl;
    }
    
    void process() const override {
        std::cout << "Derived::process" << std::endl;
    }
};

void demonstrateVirtualDestructor() {
    Base* ptr = new Derived();
    ptr->process();
    delete ptr;  // Calls both Derived and Base destructors
}
```

#### Object Slicing Problem
```cpp
void processByValue(Animal animal) {  // Object slicing
    animal.makeSound();
}

void processByReference(const Animal& animal) {  // No slicing
    animal.makeSound();
}

void processByPointer(Animal* animal) {  // No slicing
    animal->makeSound();
}

void demonstrateObjectSlicing() {
    Dog dog;
    
    // Object slicing - only Animal part is copied
    processByValue(dog);
    
    // No slicing - polymorphic behavior preserved
    processByReference(dog);
    processByPointer(&dog);
}
```

---

## Demonstration (25 minutes)

### Polymorphism Examples
```cpp
#include <iostream>
#include <vector>
#include <memory>
#include <typeinfo>

class Media {
public:
    virtual ~Media() = default;
    
    virtual void play() const = 0;
    virtual void pause() const = 0;
    virtual void stop() const = 0;
    virtual double getDuration() const = 0;
    virtual void displayInfo() const = 0;
};

class Audio : public Media {
private:
    std::string title_;
    std::string artist_;
    double duration_;
    std::string format_;
    
public:
    Audio(const std::string& title, const std::string& artist, 
          double duration, const std::string& format)
        : title_(title), artist_(artist), duration_(duration), format_(format) {}
    
    void play() const override {
        std::cout << "Playing audio: " << title_ << " by " << artist_ << std::endl;
    }
    
    void pause() const override {
        std::cout << "Pausing audio: " << title_ << std::endl;
    }
    
    void stop() const override {
        std::cout << "Stopping audio: " << title_ << std::endl;
    }
    
    double getDuration() const override {
        return duration_;
    }
    
    void displayInfo() const override {
        std::cout << "Audio - Title: " << title_ << ", Artist: " << artist_ 
                  << ", Duration: " << duration_ << "s, Format: " << format_ << std::endl;
    }
    
    const std::string& getTitle() const { return title_; }
    const std::string& getArtist() const { return artist_; }
};

class Video : public Media {
private:
    std::string title_;
    std::string director_;
    double duration_;
    int resolution_;
    
public:
    Video(const std::string& title, const std::string& director,
          double duration, int resolution)
        : title_(title), director_(director), duration_(duration), resolution_(resolution) {}
    
    void play() const override {
        std::cout << "Playing video: " << title_ << " by " << director_ << std::endl;
    }
    
    void pause() const override {
        std::cout << "Pausing video: " << title_ << std::endl;
    }
    
    void stop() const override {
        std::cout << "Stopping video: " << title_ << std::endl;
    }
    
    double getDuration() const override {
        return duration_;
    }
    
    void displayInfo() const override {
        std::cout << "Video - Title: " << title_ << ", Director: " << director_ 
                  << ", Duration: " << duration_ << "s, Resolution: " << resolution_ << "p" << std::endl;
    }
    
    const std::string& getTitle() const { return title_; }
    const std::string& getDirector() const { return director_; }
};

class MediaPlayer {
private:
    std::vector<std::unique_ptr<Media>> playlist_;
    
public:
    void addMedia(std::unique_ptr<Media> media) {
        playlist_.push_back(std::move(media));
    }
    
    void playAll() const {
        std::cout << "=== Playing All Media ===" << std::endl;
        for (const auto& media : playlist_) {
            media->play();
            media->pause();
            media->stop();
            std::cout << std::endl;
        }
    }
    
    void displayPlaylist() const {
        std::cout << "=== Playlist ===" << std::endl;
        for (size_t i = 0; i < playlist_.size(); ++i) {
            std::cout << (i + 1) << ". ";
            playlist_[i]->displayInfo();
        }
    }
    
    double getTotalDuration() const {
        double total = 0.0;
        for (const auto& media : playlist_) {
            total += media->getDuration();
        }
        return total;
    }
};

void demonstratePolymorphism() {
    std::cout << "=== Polymorphism Demonstration ===" << std::endl;
    
    MediaPlayer player;
    
    // Add different types of media
    player.addMedia(std::make_unique<Audio>("Bohemian Rhapsody", "Queen", 355, "MP3"));
    player.addMedia(std::make_unique<Video>("The Matrix", "Wachowskis", 8160, 1080));
    player.addMedia(std::make_unique<Audio>("Hotel California", "Eagles", 391, "FLAC"));
    player.addMedia(std::make_unique<Video>("Inception", "Nolan", 8880, 4));
    
    player.displayPlaylist();
    std::cout << "Total duration: " << player.getTotalDuration() << " seconds" << std::endl;
    
    player.playAll();
}
```

---

## Hands-on Practice (35 minutes)

### Activity 1: Virtual Function Implementation
Implement virtual functions:

**Tasks:**
1. Create polymorphic class hierarchies
2. Implement virtual function tables
3. Test dynamic binding behavior
4. Compare static vs dynamic binding

### Activity 2: RTTI and Dynamic Casting
Use RTTI features:

**Tasks:**
1. Implement dynamic casting
2. Use typeid operator
3. Handle casting failures
4. Create type-safe operations

### Activity 3: Advanced Polymorphism
Apply advanced patterns:

**Tasks:**
1. Implement virtual destructors
2. Handle object slicing
3. Create polymorphic containers
4. Design interface hierarchies

---

## Key Concepts

### 1. Virtual Function Table (VTable)
```cpp
class Base {
public:
    virtual void func1() { std::cout << "Base::func1" << std::endl; }
    virtual void func2() { std::cout << "Base::func2" << std::endl; }
    void func3() { std::cout << "Base::func3" << std::endl; }
};

class Derived : public Base {
public:
    void func1() override { std::cout << "Derived::func1" << std::endl; }
    void func3() { std::cout << "Derived::func3" << std::endl; }
    virtual void func4() { std::cout << "Derived::func4" << std::endl; }
};

// VTable for Base: [Base::func1, Base::func2]
// VTable for Derived: [Derived::func1, Base::func2, Derived::func4]
```

### 2. Dynamic Casting
```cpp
class Base {
public:
    virtual ~Base() = default;
};

class Derived : public Base {
public:
    void specificMethod() const {
        std::cout << "Derived specific method" << std::endl;
    }
};

void demonstrateDynamicCasting() {
    Base* ptr = new Derived();
    
    // Safe downcasting
    Derived* derived_ptr = dynamic_cast<Derived*>(ptr);
    if (derived_ptr) {
        derived_ptr->specificMethod();
    }
    
    // Safe upcasting (always succeeds)
    Base* base_ptr = dynamic_cast<Base*>(derived_ptr);
    
    delete ptr;
}
```

### 3. Type Information
```cpp
void demonstrateTypeInfo() {
    std::vector<std::unique_ptr<Base>> objects;
    objects.push_back(std::make_unique<Derived>());
    objects.push_back(std::make_unique<Base>());
    
    for (const auto& obj : objects) {
        std::cout << "Type: " << typeid(*obj).name() << std::endl;
        
        if (typeid(*obj) == typeid(Derived)) {
            std::cout << "This is a Derived object" << std::endl;
        } else if (typeid(*obj) == typeid(Base)) {
            std::cout << "This is a Base object" << std::endl;
        }
    }
}
```

---

## Best Practices

### 1. Virtual Function Design
- Use virtual functions for polymorphic behavior
- Make destructors virtual in base classes
- Use override keyword for clarity
- Consider performance implications

### 2. RTTI Usage
- Use dynamic_cast for safe downcasting
- Prefer virtual functions over RTTI when possible
- Handle casting failures gracefully
- Use typeid for type identification

### 3. Polymorphism Patterns
- Design interfaces with pure virtual functions
- Use smart pointers for polymorphic objects
- Avoid object slicing by using references/pointers
- Implement proper virtual destructors

---

## Common Pitfalls

### 1. Missing Virtual Destructor
```cpp
// Wrong: non-virtual destructor
class Base {
public:
    ~Base() { std::cout << "Base destructor" << std::endl; }
};

class Derived : public Base {
private:
    int* data_;
public:
    Derived() : data_(new int[100]) {}
    ~Derived() { 
        delete[] data_;
        std::cout << "Derived destructor" << std::endl; 
    }
};

Base* ptr = new Derived();
delete ptr;  // Only Base destructor called - memory leak!

// Correct: virtual destructor
class Base {
public:
    virtual ~Base() { std::cout << "Base destructor" << std::endl; }
};
```

### 2. Object Slicing
```cpp
// Wrong: object slicing
void processByValue(Base obj) {  // Only Base part is copied
    obj.process();
}

Derived derived;
processByValue(derived);  // Derived behavior lost

// Correct: use references or pointers
void processByReference(const Base& obj) {  // No slicing
    obj.process();
}

void processByPointer(Base* obj) {  // No slicing
    obj->process();
}
```

### 3. Function Hiding
```cpp
class Base {
public:
    virtual void func(int x) { std::cout << "Base::func(int)" << std::endl; }
};

class Derived : public Base {
public:
    void func(double x) { std::cout << "Derived::func(double)" << std::endl; }
    // This hides Base::func(int)
};

Derived d;
d.func(5);    // Calls Derived::func(double) - unexpected!
d.Base::func(5);  // Explicitly call Base version
```

---

## Assessment

### Quiz Questions
1. What is the difference between static and dynamic binding?
2. How does the virtual function table work?
3. When should you use dynamic_cast vs static_cast?
4. Why are virtual destructors important?

### Practical Assessment
- Implement polymorphic class hierarchies
- Use virtual functions correctly
- Apply RTTI features appropriately
- Handle object slicing issues

---

## Homework Assignment

### Task 1: Polymorphic Graphics System
Implement:
1. A base Shape class with virtual functions
2. Multiple derived shape classes
3. A polymorphic drawing system
4. Virtual destructors and proper cleanup

### Task 2: RTTI-Based Object Factory
Create:
1. A factory pattern using RTTI
2. Dynamic object creation
3. Type-safe object management
4. Error handling for invalid types

### Task 3: Advanced Polymorphism
Design:
1. A complex inheritance hierarchy
2. Virtual function tables
3. Multiple inheritance with virtual functions
4. Performance comparison of virtual vs non-virtual calls

---

## Next Lesson Preview

In the next lesson, we'll learn about templates:
- Function templates and class templates
- Template specialization and instantiation
- Template metaprogramming basics
- Modern template features

Make sure you understand polymorphism before moving on!
