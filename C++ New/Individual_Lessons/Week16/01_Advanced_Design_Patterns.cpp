/*
 * Lesson 16.1: Advanced Design Patterns
 * 
 * This file demonstrates advanced design patterns, modern C++ patterns,
 * and architectural patterns for complex systems.
 */

#include <iostream>
#include <memory>
#include <vector>
#include <map>
#include <unordered_map>
#include <functional>
#include <type_traits>
#include <any>
#include <variant>
#include <optional>
#include <string>
#include <sstream>
#include <chrono>
#include <thread>
#include <mutex>
#include <atomic>
#include <queue>
#include <stack>
#include <algorithm>
#include <numeric>

// Example 1: Modern C++ Patterns
namespace ModernCppPatterns {
    
    // Type Erasure Pattern
    class Drawable {
    private:
        struct Concept {
            virtual ~Concept() = default;
            virtual void draw() const = 0;
            virtual std::unique_ptr<Concept> clone() const = 0;
        };
        
        template<typename T>
        struct Model : Concept {
            T object_;
            
            Model(T object) : object_(std::move(object)) {}
            
            void draw() const override {
                object_.draw();
            }
            
            std::unique_ptr<Concept> clone() const override {
                return std::make_unique<Model<T>>(object_);
            }
        };
        
        std::unique_ptr<Concept> object_;
        
    public:
        template<typename T>
        Drawable(T object) : object_(std::make_unique<Model<T>>(std::move(object))) {}
        
        Drawable(const Drawable& other) : object_(other.object_->clone()) {}
        Drawable& operator=(const Drawable& other) {
            if (this != &other) {
                object_ = other.object_->clone();
            }
            return *this;
        }
        
        Drawable(Drawable&&) = default;
        Drawable& operator=(Drawable&&) = default;
        
        void draw() const {
            object_->draw();
        }
    };
    
    // CRTP (Curiously Recurring Template Pattern)
    template<typename Derived>
    class Base {
    public:
        void interface() {
            static_cast<Derived*>(this)->implementation();
        }
        
        void common_implementation() {
            std::cout << "Common implementation in base class" << std::endl;
        }
    };
    
    class Derived1 : public Base<Derived1> {
    public:
        void implementation() {
            std::cout << "Derived1 implementation" << std::endl;
        }
    };
    
    class Derived2 : public Base<Derived2> {
    public:
        void implementation() {
            std::cout << "Derived2 implementation" << std::endl;
        }
    };
    
    // SFINAE Pattern
    template<typename T>
    typename std::enable_if_t<std::is_integral_v<T>, void>
    process_integral(T value) {
        std::cout << "Processing integral: " << value << std::endl;
    }
    
    template<typename T>
    typename std::enable_if_t<std::is_floating_point_v<T>, void>
    process_floating_point(T value) {
        std::cout << "Processing floating point: " << value << std::endl;
    }
    
    template<typename T>
    typename std::enable_if_t<!std::is_arithmetic_v<T>, void>
    process_other(T value) {
        std::cout << "Processing other type" << std::endl;
    }
    
    // Tag Dispatch Pattern
    struct integral_tag {};
    struct floating_point_tag {};
    struct other_tag {};
    
    template<typename T>
    struct tag_dispatch {
        using type = std::conditional_t<std::is_integral_v<T>, integral_tag,
                      std::conditional_t<std::is_floating_point_v<T>, floating_point_tag, other_tag>>;
    };
    
    template<typename T>
    void process_with_tag(T value, integral_tag) {
        std::cout << "Tag dispatch - integral: " << value << std::endl;
    }
    
    template<typename T>
    void process_with_tag(T value, floating_point_tag) {
        std::cout << "Tag dispatch - floating point: " << value << std::endl;
    }
    
    template<typename T>
    void process_with_tag(T value, other_tag) {
        std::cout << "Tag dispatch - other type" << std::endl;
    }
    
    template<typename T>
    void process_tag_dispatch(T value) {
        process_with_tag(value, typename tag_dispatch<T>::type{});
    }
    
    void demonstrateModernCppPatterns() {
        std::cout << "=== Modern C++ Patterns ===" << std::endl;
        
        // Type Erasure
        struct Circle {
            void draw() const { std::cout << "Drawing circle" << std::endl; }
        };
        
        struct Rectangle {
            void draw() const { std::cout << "Drawing rectangle" << std::endl; }
        };
        
        std::vector<Drawable> drawables;
        drawables.emplace_back(Circle{});
        drawables.emplace_back(Rectangle{});
        
        for (const auto& drawable : drawables) {
            drawable.draw();
        }
        
        // CRTP
        Derived1 d1;
        Derived2 d2;
        
        d1.interface();
        d2.interface();
        
        // SFINAE
        process_integral(42);
        process_floating_point(3.14);
        process_other(std::string("hello"));
        
        // Tag Dispatch
        process_tag_dispatch(42);
        process_tag_dispatch(3.14);
        process_tag_dispatch(std::string("hello"));
    }
}

// Example 2: Architectural Patterns
namespace ArchitecturalPatterns {
    
    // MVC Pattern
    class Model {
    private:
        std::string data_;
        std::vector<std::function<void(const std::string&)>> observers_;
        
    public:
        void set_data(const std::string& data) {
            data_ = data;
            notify_observers();
        }
        
        const std::string& get_data() const {
            return data_;
        }
        
        void add_observer(std::function<void(const std::string&)> observer) {
            observers_.push_back(observer);
        }
        
    private:
        void notify_observers() {
            for (const auto& observer : observers_) {
                observer(data_);
            }
        }
    };
    
    class View {
    private:
        std::string name_;
        
    public:
        View(const std::string& name) : name_(name) {}
        
        void update(const std::string& data) {
            std::cout << "View " << name_ << " updated with: " << data << std::endl;
        }
    };
    
    class Controller {
    private:
        Model& model_;
        View& view_;
        
    public:
        Controller(Model& model, View& view) : model_(model), view_(view) {
            model_.add_observer([this](const std::string& data) {
                view_.update(data);
            });
        }
        
        void set_data(const std::string& data) {
            model_.set_data(data);
        }
    };
    
    // Repository Pattern
    template<typename T>
    class Repository {
    private:
        std::unordered_map<int, T> data_;
        std::atomic<int> next_id_{1};
        
    public:
        int create(T item) {
            int id = next_id_++;
            data_[id] = std::move(item);
            return id;
        }
        
        std::optional<T> read(int id) const {
            auto it = data_.find(id);
            if (it != data_.end()) {
                return it->second;
            }
            return std::nullopt;
        }
        
        bool update(int id, T item) {
            auto it = data_.find(id);
            if (it != data_.end()) {
                it->second = std::move(item);
                return true;
            }
            return false;
        }
        
        bool remove(int id) {
            return data_.erase(id) > 0;
        }
        
        std::vector<T> read_all() const {
            std::vector<T> result;
            for (const auto& pair : data_) {
                result.push_back(pair.second);
            }
            return result;
        }
    };
    
    // Unit of Work Pattern
    template<typename T>
    class UnitOfWork {
    private:
        Repository<T>& repository_;
        std::vector<std::function<void()>> operations_;
        
    public:
        UnitOfWork(Repository<T>& repository) : repository_(repository) {}
        
        void add_create(T item) {
            operations_.push_back([this, item = std::move(item)]() {
                repository_.create(item);
            });
        }
        
        void add_update(int id, T item) {
            operations_.push_back([this, id, item = std::move(item)]() {
                repository_.update(id, item);
            });
        }
        
        void add_delete(int id) {
            operations_.push_back([this, id]() {
                repository_.remove(id);
            });
        }
        
        void commit() {
            for (const auto& operation : operations_) {
                operation();
            }
            operations_.clear();
        }
        
        void rollback() {
            operations_.clear();
        }
    };
    
    void demonstrateArchitecturalPatterns() {
        std::cout << "\n=== Architectural Patterns ===" << std::endl;
        
        // MVC Pattern
        Model model;
        View view("MainView");
        Controller controller(model, view);
        
        controller.set_data("Hello, MVC!");
        
        // Repository Pattern
        Repository<std::string> string_repo;
        
        int id1 = string_repo.create("Item 1");
        int id2 = string_repo.create("Item 2");
        
        auto item = string_repo.read(id1);
        if (item) {
            std::cout << "Retrieved: " << *item << std::endl;
        }
        
        string_repo.update(id1, "Updated Item 1");
        
        auto all_items = string_repo.read_all();
        std::cout << "All items: ";
        for (const auto& item : all_items) {
            std::cout << item << " ";
        }
        std::cout << std::endl;
        
        // Unit of Work Pattern
        UnitOfWork<std::string> unit_of_work(string_repo);
        
        unit_of_work.add_create("Item 3");
        unit_of_work.add_create("Item 4");
        unit_of_work.add_update(id2, "Updated Item 2");
        unit_of_work.add_delete(id1);
        
        unit_of_work.commit();
        
        auto final_items = string_repo.read_all();
        std::cout << "Final items: ";
        for (const auto& item : final_items) {
            std::cout << item << " ";
        }
        std::cout << std::endl;
    }
}

// Example 3: Behavioral Patterns
namespace BehavioralPatterns {
    
    // Command Pattern
    class Command {
    public:
        virtual ~Command() = default;
        virtual void execute() = 0;
        virtual void undo() = 0;
    };
    
    class Light {
    private:
        bool on_ = false;
        
    public:
        void turn_on() {
            on_ = true;
            std::cout << "Light is on" << std::endl;
        }
        
        void turn_off() {
            on_ = false;
            std::cout << "Light is off" << std::endl;
        }
        
        bool is_on() const { return on_; }
    };
    
    class LightOnCommand : public Command {
    private:
        Light& light_;
        
    public:
        LightOnCommand(Light& light) : light_(light) {}
        
        void execute() override {
            light_.turn_on();
        }
        
        void undo() override {
            light_.turn_off();
        }
    };
    
    class LightOffCommand : public Command {
    private:
        Light& light_;
        
    public:
        LightOffCommand(Light& light) : light_(light) {}
        
        void execute() override {
            light_.turn_off();
        }
        
        void undo() override {
            light_.turn_on();
        }
    };
    
    class RemoteControl {
    private:
        std::unique_ptr<Command> on_command_;
        std::unique_ptr<Command> off_command_;
        std::stack<std::unique_ptr<Command>> command_history_;
        
    public:
        void set_commands(std::unique_ptr<Command> on_command, std::unique_ptr<Command> off_command) {
            on_command_ = std::move(on_command);
            off_command_ = std::move(off_command);
        }
        
        void press_on() {
            if (on_command_) {
                on_command_->execute();
                command_history_.push(std::move(on_command_));
            }
        }
        
        void press_off() {
            if (off_command_) {
                off_command_->execute();
                command_history_.push(std::move(off_command_));
            }
        }
        
        void press_undo() {
            if (!command_history_.empty()) {
                command_history_.top()->undo();
                command_history_.pop();
            }
        }
    };
    
    // Strategy Pattern
    template<typename T>
    class SortingStrategy {
    public:
        virtual ~SortingStrategy() = default;
        virtual void sort(std::vector<T>& data) = 0;
    };
    
    template<typename T>
    class QuickSortStrategy : public SortingStrategy<T> {
    public:
        void sort(std::vector<T>& data) override {
            std::sort(data.begin(), data.end());
            std::cout << "Quick sort applied" << std::endl;
        }
    };
    
    template<typename T>
    class MergeSortStrategy : public SortingStrategy<T> {
    public:
        void sort(std::vector<T>& data) override {
            std::sort(data.begin(), data.end());
            std::cout << "Merge sort applied" << std::endl;
        }
    };
    
    template<typename T>
    class Sorter {
    private:
        std::unique_ptr<SortingStrategy<T>> strategy_;
        
    public:
        void set_strategy(std::unique_ptr<SortingStrategy<T>> strategy) {
            strategy_ = std::move(strategy);
        }
        
        void sort(std::vector<T>& data) {
            if (strategy_) {
                strategy_->sort(data);
            }
        }
    };
    
    // Observer Pattern
    class Subject {
    private:
        std::vector<std::function<void()>> observers_;
        
    public:
        void add_observer(std::function<void()> observer) {
            observers_.push_back(observer);
        }
        
        void notify() {
            for (const auto& observer : observers_) {
                observer();
            }
        }
    };
    
    class ConcreteSubject : public Subject {
    private:
        int state_ = 0;
        
    public:
        void set_state(int state) {
            state_ = state;
            notify();
        }
        
        int get_state() const {
            return state_;
        }
    };
    
    class ConcreteObserver {
    private:
        std::string name_;
        
    public:
        ConcreteObserver(const std::string& name) : name_(name) {}
        
        void update() {
            std::cout << "Observer " << name_ << " notified" << std::endl;
        }
    };
    
    void demonstrateBehavioralPatterns() {
        std::cout << "\n=== Behavioral Patterns ===" << std::endl;
        
        // Command Pattern
        Light light;
        RemoteControl remote;
        
        remote.set_commands(
            std::make_unique<LightOnCommand>(light),
            std::make_unique<LightOffCommand>(light)
        );
        
        remote.press_on();
        remote.press_off();
        remote.press_undo();
        
        // Strategy Pattern
        std::vector<int> data = {5, 2, 8, 1, 9, 3};
        
        Sorter<int> sorter;
        sorter.set_strategy(std::make_unique<QuickSortStrategy<int>>());
        sorter.sort(data);
        
        sorter.set_strategy(std::make_unique<MergeSortStrategy<int>>());
        sorter.sort(data);
        
        // Observer Pattern
        ConcreteSubject subject;
        ConcreteObserver observer1("Observer1");
        ConcreteObserver observer2("Observer2");
        
        subject.add_observer([&observer1]() { observer1.update(); });
        subject.add_observer([&observer2]() { observer2.update(); });
        
        subject.set_state(42);
    }
}

// Example 4: Creational Patterns
namespace CreationalPatterns {
    
    // Abstract Factory Pattern
    class Button {
    public:
        virtual ~Button() = default;
        virtual void render() = 0;
    };
    
    class WindowsButton : public Button {
    public:
        void render() override {
            std::cout << "Rendering Windows button" << std::endl;
        }
    };
    
    class MacButton : public Button {
    public:
        void render() override {
            std::cout << "Rendering Mac button" << std::endl;
        }
    };
    
    class Dialog {
    public:
        virtual ~Dialog() = default;
        virtual void render() = 0;
    };
    
    class WindowsDialog : public Dialog {
    public:
        void render() override {
            std::cout << "Rendering Windows dialog" << std::endl;
        }
    };
    
    class MacDialog : public Dialog {
    public:
        void render() override {
            std::cout << "Rendering Mac dialog" << std::endl;
        }
    };
    
    class UIFactory {
    public:
        virtual ~UIFactory() = default;
        virtual std::unique_ptr<Button> create_button() = 0;
        virtual std::unique_ptr<Dialog> create_dialog() = 0;
    };
    
    class WindowsUIFactory : public UIFactory {
    public:
        std::unique_ptr<Button> create_button() override {
            return std::make_unique<WindowsButton>();
        }
        
        std::unique_ptr<Dialog> create_dialog() override {
            return std::make_unique<WindowsDialog>();
        }
    };
    
    class MacUIFactory : public UIFactory {
    public:
        std::unique_ptr<Button> create_button() override {
            return std::make_unique<MacButton>();
        }
        
        std::unique_ptr<Dialog> create_dialog() override {
            return std::make_unique<MacDialog>();
        }
    };
    
    // Builder Pattern
    class Product {
    private:
        std::string part_a_;
        std::string part_b_;
        std::string part_c_;
        
    public:
        void set_part_a(const std::string& part) { part_a_ = part; }
        void set_part_b(const std::string& part) { part_b_ = part; }
        void set_part_c(const std::string& part) { part_c_ = part; }
        
        void show() const {
            std::cout << "Product parts: " << part_a_ << ", " << part_b_ << ", " << part_c_ << std::endl;
        }
    };
    
    class Builder {
    public:
        virtual ~Builder() = default;
        virtual void build_part_a() = 0;
        virtual void build_part_b() = 0;
        virtual void build_part_c() = 0;
        virtual Product get_product() = 0;
    };
    
    class ConcreteBuilder : public Builder {
    private:
        Product product_;
        
    public:
        void build_part_a() override {
            product_.set_part_a("Part A");
        }
        
        void build_part_b() override {
            product_.set_part_b("Part B");
        }
        
        void build_part_c() override {
            product_.set_part_c("Part C");
        }
        
        Product get_product() override {
            return product_;
        }
    };
    
    class Director {
    private:
        Builder* builder_;
        
    public:
        void set_builder(Builder* builder) {
            builder_ = builder;
        }
        
        Product construct() {
            builder_->build_part_a();
            builder_->build_part_b();
            builder_->build_part_c();
            return builder_->get_product();
        }
    };
    
    // Singleton Pattern
    class Singleton {
    private:
        static std::unique_ptr<Singleton> instance_;
        static std::mutex mutex_;
        
        Singleton() = default;
        
    public:
        static Singleton& get_instance() {
            std::lock_guard<std::mutex> lock(mutex_);
            if (!instance_) {
                instance_ = std::unique_ptr<Singleton>(new Singleton());
            }
            return *instance_;
        }
        
        void do_something() {
            std::cout << "Singleton doing something" << std::endl;
        }
    };
    
    std::unique_ptr<Singleton> Singleton::instance_ = nullptr;
    std::mutex Singleton::mutex_;
    
    void demonstrateCreationalPatterns() {
        std::cout << "\n=== Creational Patterns ===" << std::endl;
        
        // Abstract Factory Pattern
        std::unique_ptr<UIFactory> factory;
        
        // Simulate platform detection
        bool is_windows = true; // In real code, this would be platform detection
        
        if (is_windows) {
            factory = std::make_unique<WindowsUIFactory>();
        } else {
            factory = std::make_unique<MacUIFactory>();
        }
        
        auto button = factory->create_button();
        auto dialog = factory->create_dialog();
        
        button->render();
        dialog->render();
        
        // Builder Pattern
        ConcreteBuilder builder;
        Director director;
        
        director.set_builder(&builder);
        Product product = director.construct();
        
        product.show();
        
        // Singleton Pattern
        Singleton& singleton1 = Singleton::get_instance();
        Singleton& singleton2 = Singleton::get_instance();
        
        singleton1.do_something();
        singleton2.do_something();
        
        std::cout << "Same instance: " << (&singleton1 == &singleton2 ? "Yes" : "No") << std::endl;
    }
}

// Example 5: Structural Patterns
namespace StructuralPatterns {
    
    // Adapter Pattern
    class LegacyRectangle {
    public:
        void draw(int x, int y, int width, int height) {
            std::cout << "Legacy rectangle: (" << x << ", " << y << ") " << width << "x" << height << std::endl;
        }
    };
    
    class ModernShape {
    public:
        virtual ~ModernShape() = default;
        virtual void draw() = 0;
    };
    
    class RectangleAdapter : public ModernShape {
    private:
        LegacyRectangle legacy_rectangle_;
        int x_, y_, width_, height_;
        
    public:
        RectangleAdapter(int x, int y, int width, int height)
            : x_(x), y_(y), width_(width), height_(height) {}
        
        void draw() override {
            legacy_rectangle_.draw(x_, y_, width_, height_);
        }
    };
    
    // Decorator Pattern
    class Coffee {
    public:
        virtual ~Coffee() = default;
        virtual double cost() = 0;
        virtual std::string description() = 0;
    };
    
    class SimpleCoffee : public Coffee {
    public:
        double cost() override { return 2.0; }
        std::string description() override { return "Simple coffee"; }
    };
    
    class CoffeeDecorator : public Coffee {
    protected:
        std::unique_ptr<Coffee> coffee_;
        
    public:
        CoffeeDecorator(std::unique_ptr<Coffee> coffee) : coffee_(std::move(coffee)) {}
    };
    
    class MilkDecorator : public CoffeeDecorator {
    public:
        MilkDecorator(std::unique_ptr<Coffee> coffee) : CoffeeDecorator(std::move(coffee)) {}
        
        double cost() override {
            return coffee_->cost() + 0.5;
        }
        
        std::string description() override {
            return coffee_->description() + ", milk";
        }
    };
    
    class SugarDecorator : public CoffeeDecorator {
    public:
        SugarDecorator(std::unique_ptr<Coffee> coffee) : CoffeeDecorator(std::move(coffee)) {}
        
        double cost() override {
            return coffee_->cost() + 0.2;
        }
        
        std::string description() override {
            return coffee_->description() + ", sugar";
        }
    };
    
    // Facade Pattern
    class SubsystemA {
    public:
        void operation_a() {
            std::cout << "Subsystem A operation" << std::endl;
        }
    };
    
    class SubsystemB {
    public:
        void operation_b() {
            std::cout << "Subsystem B operation" << std::endl;
        }
    };
    
    class SubsystemC {
    public:
        void operation_c() {
            std::cout << "Subsystem C operation" << std::endl;
        }
    };
    
    class Facade {
    private:
        SubsystemA subsystem_a_;
        SubsystemB subsystem_b_;
        SubsystemC subsystem_c_;
        
    public:
        void operation() {
            subsystem_a_.operation_a();
            subsystem_b_.operation_b();
            subsystem_c_.operation_c();
        }
    };
    
    // Proxy Pattern
    class Image {
    public:
        virtual ~Image() = default;
        virtual void display() = 0;
    };
    
    class RealImage : public Image {
    private:
        std::string filename_;
        
    public:
        RealImage(const std::string& filename) : filename_(filename) {
            load_from_disk();
        }
        
        void display() override {
            std::cout << "Displaying " << filename_ << std::endl;
        }
        
    private:
        void load_from_disk() {
            std::cout << "Loading " << filename_ << " from disk" << std::endl;
        }
    };
    
    class ImageProxy : public Image {
    private:
        std::string filename_;
        std::unique_ptr<RealImage> real_image_;
        
    public:
        ImageProxy(const std::string& filename) : filename_(filename) {}
        
        void display() override {
            if (!real_image_) {
                real_image_ = std::make_unique<RealImage>(filename_);
            }
            real_image_->display();
        }
    };
    
    void demonstrateStructuralPatterns() {
        std::cout << "\n=== Structural Patterns ===" << std::endl;
        
        // Adapter Pattern
        RectangleAdapter adapter(10, 20, 100, 50);
        adapter.draw();
        
        // Decorator Pattern
        auto coffee = std::make_unique<SimpleCoffee>();
        std::cout << coffee->description() << " costs $" << coffee->cost() << std::endl;
        
        auto milk_coffee = std::make_unique<MilkDecorator>(std::move(coffee));
        std::cout << milk_coffee->description() << " costs $" << milk_coffee->cost() << std::endl;
        
        auto milk_sugar_coffee = std::make_unique<SugarDecorator>(std::move(milk_coffee));
        std::cout << milk_sugar_coffee->description() << " costs $" << milk_sugar_coffee->cost() << std::endl;
        
        // Facade Pattern
        Facade facade;
        facade.operation();
        
        // Proxy Pattern
        ImageProxy proxy("test.jpg");
        proxy.display(); // Loads and displays
        proxy.display(); // Just displays (already loaded)
    }
}

int main() {
    std::cout << "=== Advanced Design Patterns Demonstration ===" << std::endl;
    std::cout << "This program demonstrates advanced design patterns, modern C++ patterns,\n"
              << "and architectural patterns for complex systems.\n" << std::endl;
    
    // Demonstrate various advanced design patterns
    ModernCppPatterns::demonstrateModernCppPatterns();
    ArchitecturalPatterns::demonstrateArchitecturalPatterns();
    BehavioralPatterns::demonstrateBehavioralPatterns();
    CreationalPatterns::demonstrateCreationalPatterns();
    StructuralPatterns::demonstrateStructuralPatterns();
    
    std::cout << "\n=== Key Takeaways ===" << std::endl;
    std::cout << "1. Modern C++ patterns leverage language features for better design" << std::endl;
    std::cout << "2. Architectural patterns provide structure for complex systems" << std::endl;
    std::cout << "3. Behavioral patterns define communication between objects" << std::endl;
    std::cout << "4. Creational patterns control object creation and initialization" << std::endl;
    std::cout << "5. Structural patterns compose objects into larger structures" << std::endl;
    std::cout << "6. Design patterns provide proven solutions to common problems" << std::endl;
    std::cout << "7. Pattern selection depends on specific requirements and constraints" << std::endl;
    std::cout << "8. Modern C++ enables more elegant and efficient pattern implementations" << std::endl;
    
    std::cout << "\nProgram completed successfully!" << std::endl;
    return 0;
}

/*
 * Compilation Instructions:
 * 
 * Using GCC:
 * g++ -std=c++17 -Wall -Wextra -O2 -o advanced_design_patterns 01_Advanced_Design_Patterns.cpp
 * 
 * Using Clang:
 * clang++ -std=c++17 -Wall -Wextra -O2 -o advanced_design_patterns 01_Advanced_Design_Patterns.cpp
 * 
 * Using MSVC (Visual Studio):
 * cl /std:c++17 /EHsc /O2 01_Advanced_Design_Patterns.cpp
 * 
 * Running:
 * ./advanced_design_patterns (Linux/macOS)
 * advanced_design_patterns.exe (Windows)
 * 
 * Note: This lesson requires C++17 or later for some features.
 * C++20 is recommended for best pattern support.
 * 
 * Advanced Design Patterns Notes:
 * - Modern C++ patterns leverage language features for better design
 * - Architectural patterns provide structure for complex systems
 * - Behavioral patterns define communication between objects
 * - Creational patterns control object creation and initialization
 * - Structural patterns compose objects into larger structures
 * - Design patterns provide proven solutions to common problems
 * - Pattern selection depends on specific requirements and constraints
 * - Modern C++ enables more elegant and efficient pattern implementations
 */"""
