/*
 * Lesson 19.3: Advanced Software Architecture
 * 
 * This file demonstrates advanced software architecture patterns including
 * microservices, event-driven architecture, CQRS, hexagonal architecture,
 * and system design patterns.
 */

#include <iostream>
#include <memory>
#include <vector>
#include <map>
#include <unordered_map>
#include <functional>
#include <string>
#include <sstream>
#include <chrono>
#include <thread>
#include <mutex>
#include <atomic>
#include <queue>
#include <future>
#include <condition_variable>
#include <random>
#include <algorithm>
#include <exception>
#include <stdexcept>
#include <cassert>
#include <limits>
#include <array>
#include <tuple>
#include <type_traits>
#include <variant>
#include <any>

// Example 1: Microservices Architecture
namespace Microservices {
    
    // Service interface
    class IService {
    public:
        virtual ~IService() = default;
        virtual std::string get_name() const = 0;
        virtual std::string get_version() const = 0;
        virtual bool is_healthy() const = 0;
        virtual void start() = 0;
        virtual void stop() = 0;
    };
    
    // Service registry
    class ServiceRegistry {
    private:
        std::map<std::string, std::shared_ptr<IService>> services_;
        std::mutex services_mutex_;
        
    public:
        // Register service
        void register_service(std::shared_ptr<IService> service) {
            std::lock_guard<std::mutex> lock(services_mutex_);
            services_[service->get_name()] = service;
        }
        
        // Unregister service
        void unregister_service(const std::string& name) {
            std::lock_guard<std::mutex> lock(services_mutex_);
            services_.erase(name);
        }
        
        // Get service
        std::shared_ptr<IService> get_service(const std::string& name) {
            std::lock_guard<std::mutex> lock(services_mutex_);
            auto it = services_.find(name);
            return it != services_.end() ? it->second : nullptr;
        }
        
        // Get all services
        std::vector<std::shared_ptr<IService>> get_all_services() {
            std::lock_guard<std::mutex> lock(services_mutex_);
            std::vector<std::shared_ptr<IService>> result;
            for (const auto& [name, service] : services_) {
                result.push_back(service);
            }
            return result;
        }
        
        // Check service health
        bool is_service_healthy(const std::string& name) {
            auto service = get_service(name);
            return service && service->is_healthy();
        }
    };
    
    // Service discovery
    class ServiceDiscovery {
    private:
        ServiceRegistry& registry_;
        
    public:
        ServiceDiscovery(ServiceRegistry& registry) : registry_(registry) {}
        
        // Discover services by name
        std::vector<std::shared_ptr<IService>> discover_services(const std::string& name_pattern) {
            auto all_services = registry_.get_all_services();
            std::vector<std::shared_ptr<IService>> result;
            
            for (const auto& service : all_services) {
                if (service->get_name().find(name_pattern) != std::string::npos) {
                    result.push_back(service);
                }
            }
            
            return result;
        }
        
        // Discover healthy services
        std::vector<std::shared_ptr<IService>> discover_healthy_services() {
            auto all_services = registry_.get_all_services();
            std::vector<std::shared_ptr<IService>> result;
            
            for (const auto& service : all_services) {
                if (service->is_healthy()) {
                    result.push_back(service);
                }
            }
            
            return result;
        }
    };
    
    // Example user service
    class UserService : public IService {
    private:
        std::map<int, std::string> users_;
        std::mutex users_mutex_;
        std::atomic<bool> healthy_;
        
    public:
        UserService() : healthy_(true) {
            // Initialize with some test data
            users_[1] = "Alice";
            users_[2] = "Bob";
            users_[3] = "Charlie";
        }
        
        std::string get_name() const override {
            return "user-service";
        }
        
        std::string get_version() const override {
            return "1.0.0";
        }
        
        bool is_healthy() const override {
            return healthy_.load();
        }
        
        void start() override {
            std::cout << "Starting " << get_name() << " v" << get_version() << std::endl;
        }
        
        void stop() override {
            std::cout << "Stopping " << get_name() << std::endl;
        }
        
        // Service-specific methods
        std::string get_user(int id) {
            std::lock_guard<std::mutex> lock(users_mutex_);
            auto it = users_.find(id);
            return it != users_.end() ? it->second : "";
        }
        
        void add_user(int id, const std::string& name) {
            std::lock_guard<std::mutex> lock(users_mutex_);
            users_[id] = name;
        }
        
        void set_healthy(bool healthy) {
            healthy_.store(healthy);
        }
    };
    
    // Example order service
    class OrderService : public IService {
    private:
        std::map<int, std::string> orders_;
        std::mutex orders_mutex_;
        std::atomic<bool> healthy_;
        
    public:
        OrderService() : healthy_(true) {
            // Initialize with some test data
            orders_[1] = "Order 1";
            orders_[2] = "Order 2";
            orders_[3] = "Order 3";
        }
        
        std::string get_name() const override {
            return "order-service";
        }
        
        std::string get_version() const override {
            return "1.0.0";
        }
        
        bool is_healthy() const override {
            return healthy_.load();
        }
        
        void start() override {
            std::cout << "Starting " << get_name() << " v" << get_version() << std::endl;
        }
        
        void stop() override {
            std::cout << "Stopping " << get_name() << std::endl;
        }
        
        // Service-specific methods
        std::string get_order(int id) {
            std::lock_guard<std::mutex> lock(orders_mutex_);
            auto it = orders_.find(id);
            return it != orders_.end() ? it->second : "";
        }
        
        void add_order(int id, const std::string& description) {
            std::lock_guard<std::mutex> lock(orders_mutex_);
            orders_[id] = description;
        }
        
        void set_healthy(bool healthy) {
            healthy_.store(healthy);
        }
    };
    
    void demonstrateMicroservices() {
        std::cout << "=== Microservices Architecture ===" << std::endl;
        
        // Create service registry
        ServiceRegistry registry;
        
        // Create services
        auto user_service = std::make_shared<UserService>();
        auto order_service = std::make_shared<OrderService>();
        
        // Register services
        registry.register_service(user_service);
        registry.register_service(order_service);
        
        // Start services
        user_service->start();
        order_service->start();
        
        // Create service discovery
        ServiceDiscovery discovery(registry);
        
        // Discover services
        auto user_services = discovery.discover_services("user");
        std::cout << "Discovered " << user_services.size() << " user services" << std::endl;
        
        auto healthy_services = discovery.discover_healthy_services();
        std::cout << "Discovered " << healthy_services.size() << " healthy services" << std::endl;
        
        // Test service functionality
        std::cout << "User 1: " << user_service->get_user(1) << std::endl;
        std::cout << "Order 1: " << order_service->get_order(1) << std::endl;
        
        // Simulate service failure
        user_service->set_healthy(false);
        std::cout << "User service healthy: " << user_service->is_healthy() << std::endl;
        
        // Stop services
        user_service->stop();
        order_service->stop();
    }
}

// Example 2: Event-Driven Architecture
namespace EventDriven {
    
    // Event base class
    class IEvent {
    public:
        virtual ~IEvent() = default;
        virtual std::string get_type() const = 0;
        virtual std::string get_source() const = 0;
        virtual std::chrono::steady_clock::time_point get_timestamp() const = 0;
    };
    
    // Event handler interface
    class IEventHandler {
    public:
        virtual ~IEventHandler() = default;
        virtual void handle_event(const IEvent& event) = 0;
        virtual std::string get_handler_name() const = 0;
    };
    
    // Event bus
    class EventBus {
    private:
        std::map<std::string, std::vector<std::shared_ptr<IEventHandler>>> handlers_;
        std::mutex handlers_mutex_;
        std::queue<std::shared_ptr<IEvent>> event_queue_;
        std::mutex queue_mutex_;
        std::condition_variable queue_cv_;
        std::atomic<bool> running_;
        std::thread event_thread_;
        
    public:
        EventBus() : running_(false) {}
        
        ~EventBus() {
            stop();
        }
        
        // Subscribe to event type
        void subscribe(const std::string& event_type, std::shared_ptr<IEventHandler> handler) {
            std::lock_guard<std::mutex> lock(handlers_mutex_);
            handlers_[event_type].push_back(handler);
        }
        
        // Unsubscribe from event type
        void unsubscribe(const std::string& event_type, const std::string& handler_name) {
            std::lock_guard<std::mutex> lock(handlers_mutex_);
            auto it = handlers_.find(event_type);
            if (it != handlers_.end()) {
                auto& handlers = it->second;
                handlers.erase(
                    std::remove_if(handlers.begin(), handlers.end(),
                        [&handler_name](const std::shared_ptr<IEventHandler>& handler) {
                            return handler->get_handler_name() == handler_name;
                        }),
                    handlers.end()
                );
            }
        }
        
        // Publish event
        void publish(std::shared_ptr<IEvent> event) {
            if (!running_) {
                return;
            }
            
            {
                std::lock_guard<std::mutex> lock(queue_mutex_);
                event_queue_.push(event);
            }
            queue_cv_.notify_one();
        }
        
        // Start event bus
        void start() {
            if (running_) {
                return;
            }
            
            running_ = true;
            event_thread_ = std::thread(&EventBus::event_loop, this);
        }
        
        // Stop event bus
        void stop() {
            if (running_) {
                running_ = false;
                queue_cv_.notify_all();
                if (event_thread_.joinable()) {
                    event_thread_.join();
                }
            }
        }
        
    private:
        void event_loop() {
            while (running_) {
                std::shared_ptr<IEvent> event;
                
                {
                    std::unique_lock<std::mutex> lock(queue_mutex_);
                    queue_cv_.wait(lock, [this] { return !event_queue_.empty() || !running_; });
                    
                    if (!running_) {
                        break;
                    }
                    
                    if (!event_queue_.empty()) {
                        event = event_queue_.front();
                        event_queue_.pop();
                    }
                }
                
                if (event) {
                    handle_event(event);
                }
            }
        }
        
        void handle_event(std::shared_ptr<IEvent> event) {
            std::lock_guard<std::mutex> lock(handlers_mutex_);
            
            auto it = handlers_.find(event->get_type());
            if (it != handlers_.end()) {
                for (const auto& handler : it->second) {
                    try {
                        handler->handle_event(*event);
                    } catch (const std::exception& e) {
                        std::cout << "Error handling event: " << e.what() << std::endl;
                    }
                }
            }
        }
    };
    
    // Example events
    class UserCreatedEvent : public IEvent {
    private:
        int user_id_;
        std::string username_;
        std::chrono::steady_clock::time_point timestamp_;
        
    public:
        UserCreatedEvent(int user_id, const std::string& username) 
            : user_id_(user_id), username_(username), timestamp_(std::chrono::steady_clock::now()) {}
        
        std::string get_type() const override {
            return "user_created";
        }
        
        std::string get_source() const override {
            return "user-service";
        }
        
        std::chrono::steady_clock::time_point get_timestamp() const override {
            return timestamp_;
        }
        
        int get_user_id() const { return user_id_; }
        const std::string& get_username() const { return username_; }
    };
    
    class OrderPlacedEvent : public IEvent {
    private:
        int order_id_;
        int user_id_;
        std::string product_;
        std::chrono::steady_clock::time_point timestamp_;
        
    public:
        OrderPlacedEvent(int order_id, int user_id, const std::string& product) 
            : order_id_(order_id), user_id_(user_id), product_(product), 
              timestamp_(std::chrono::steady_clock::now()) {}
        
        std::string get_type() const override {
            return "order_placed";
        }
        
        std::string get_source() const override {
            return "order-service";
        }
        
        std::chrono::steady_clock::time_point get_timestamp() const override {
            return timestamp_;
        }
        
        int get_order_id() const { return order_id_; }
        int get_user_id() const { return user_id_; }
        const std::string& get_product() const { return product_; }
    };
    
    // Example event handlers
    class UserEventHandler : public IEventHandler {
    public:
        void handle_event(const IEvent& event) override {
            if (event.get_type() == "user_created") {
                const auto& user_event = static_cast<const UserCreatedEvent&>(event);
                std::cout << "UserEventHandler: User " << user_event.get_user_id() 
                          << " (" << user_event.get_username() << ") created" << std::endl;
            }
        }
        
        std::string get_handler_name() const override {
            return "UserEventHandler";
        }
    };
    
    class OrderEventHandler : public IEventHandler {
    public:
        void handle_event(const IEvent& event) override {
            if (event.get_type() == "order_placed") {
                const auto& order_event = static_cast<const OrderPlacedEvent&>(event);
                std::cout << "OrderEventHandler: Order " << order_event.get_order_id() 
                          << " placed by user " << order_event.get_user_id() 
                          << " for product " << order_event.get_product() << std::endl;
            }
        }
        
        std::string get_handler_name() const override {
            return "OrderEventHandler";
        }
    };
    
    void demonstrateEventDriven() {
        std::cout << "\n=== Event-Driven Architecture ===" << std::endl;
        
        // Create event bus
        EventBus event_bus;
        
        // Create event handlers
        auto user_handler = std::make_shared<UserEventHandler>();
        auto order_handler = std::make_shared<OrderEventHandler>();
        
        // Subscribe to events
        event_bus.subscribe("user_created", user_handler);
        event_bus.subscribe("order_placed", order_handler);
        
        // Start event bus
        event_bus.start();
        
        // Publish events
        event_bus.publish(std::make_shared<UserCreatedEvent>(1, "Alice"));
        event_bus.publish(std::make_shared<UserCreatedEvent>(2, "Bob"));
        event_bus.publish(std::make_shared<OrderPlacedEvent>(1, 1, "Laptop"));
        event_bus.publish(std::make_shared<OrderPlacedEvent>(2, 2, "Mouse"));
        
        // Wait for events to be processed
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        
        // Stop event bus
        event_bus.stop();
    }
}

// Example 3: CQRS (Command Query Responsibility Segregation)
namespace CQRS {
    
    // Command interface
    class ICommand {
    public:
        virtual ~ICommand() = default;
        virtual std::string get_type() const = 0;
    };
    
    // Query interface
    class IQuery {
    public:
        virtual ~IQuery() = default;
        virtual std::string get_type() const = 0;
    };
    
    // Command handler interface
    class ICommandHandler {
    public:
        virtual ~ICommandHandler() = default;
        virtual void handle_command(const ICommand& command) = 0;
        virtual std::string get_command_type() const = 0;
    };
    
    // Query handler interface
    class IQueryHandler {
    public:
        virtual ~IQueryHandler() = default;
        virtual std::any handle_query(const IQuery& query) = 0;
        virtual std::string get_query_type() const = 0;
    };
    
    // Command bus
    class CommandBus {
    private:
        std::map<std::string, std::shared_ptr<ICommandHandler>> handlers_;
        std::mutex handlers_mutex_;
        
    public:
        // Register command handler
        void register_handler(std::shared_ptr<ICommandHandler> handler) {
            std::lock_guard<std::mutex> lock(handlers_mutex_);
            handlers_[handler->get_command_type()] = handler;
        }
        
        // Execute command
        void execute(const ICommand& command) {
            std::lock_guard<std::mutex> lock(handlers_mutex_);
            
            auto it = handlers_.find(command.get_type());
            if (it != handlers_.end()) {
                try {
                    it->second->handle_command(command);
                } catch (const std::exception& e) {
                    std::cout << "Error executing command: " << e.what() << std::endl;
                }
            } else {
                std::cout << "No handler found for command type: " << command.get_type() << std::endl;
            }
        }
    };
    
    // Query bus
    class QueryBus {
    private:
        std::map<std::string, std::shared_ptr<IQueryHandler>> handlers_;
        std::mutex handlers_mutex_;
        
    public:
        // Register query handler
        void register_handler(std::shared_ptr<IQueryHandler> handler) {
            std::lock_guard<std::mutex> lock(handlers_mutex_);
            handlers_[handler->get_query_type()] = handler;
        }
        
        // Execute query
        std::any execute(const IQuery& query) {
            std::lock_guard<std::mutex> lock(handlers_mutex_);
            
            auto it = handlers_.find(query.get_type());
            if (it != handlers_.end()) {
                try {
                    return it->second->handle_query(query);
                } catch (const std::exception& e) {
                    std::cout << "Error executing query: " << e.what() << std::endl;
                    return std::any();
                }
            } else {
                std::cout << "No handler found for query type: " << query.get_type() << std::endl;
                return std::any();
            }
        }
    };
    
    // Example commands
    class CreateUserCommand : public ICommand {
    private:
        int user_id_;
        std::string username_;
        
    public:
        CreateUserCommand(int user_id, const std::string& username) 
            : user_id_(user_id), username_(username) {}
        
        std::string get_type() const override {
            return "create_user";
        }
        
        int get_user_id() const { return user_id_; }
        const std::string& get_username() const { return username_; }
    };
    
    class UpdateUserCommand : public ICommand {
    private:
        int user_id_;
        std::string new_username_;
        
    public:
        UpdateUserCommand(int user_id, const std::string& new_username) 
            : user_id_(user_id), new_username_(new_username) {}
        
        std::string get_type() const override {
            return "update_user";
        }
        
        int get_user_id() const { return user_id_; }
        const std::string& get_new_username() const { return new_username_; }
    };
    
    // Example queries
    class GetUserQuery : public IQuery {
    private:
        int user_id_;
        
    public:
        GetUserQuery(int user_id) : user_id_(user_id) {}
        
        std::string get_type() const override {
            return "get_user";
        }
        
        int get_user_id() const { return user_id_; }
    };
    
    class GetAllUsersQuery : public IQuery {
    public:
        std::string get_type() const override {
            return "get_all_users";
        }
    };
    
    // Example command handlers
    class CreateUserCommandHandler : public ICommandHandler {
    private:
        std::map<int, std::string>& users_;
        std::mutex& users_mutex_;
        
    public:
        CreateUserCommandHandler(std::map<int, std::string>& users, std::mutex& users_mutex) 
            : users_(users), users_mutex_(users_mutex) {}
        
        void handle_command(const ICommand& command) override {
            const auto& create_command = static_cast<const CreateUserCommand&>(command);
            
            std::lock_guard<std::mutex> lock(users_mutex_);
            users_[create_command.get_user_id()] = create_command.get_username();
            
            std::cout << "Created user: " << create_command.get_user_id() 
                      << " (" << create_command.get_username() << ")" << std::endl;
        }
        
        std::string get_command_type() const override {
            return "create_user";
        }
    };
    
    class UpdateUserCommandHandler : public ICommandHandler {
    private:
        std::map<int, std::string>& users_;
        std::mutex& users_mutex_;
        
    public:
        UpdateUserCommandHandler(std::map<int, std::string>& users, std::mutex& users_mutex) 
            : users_(users), users_mutex_(users_mutex) {}
        
        void handle_command(const ICommand& command) override {
            const auto& update_command = static_cast<const UpdateUserCommand&>(command);
            
            std::lock_guard<std::mutex> lock(users_mutex_);
            auto it = users_.find(update_command.get_user_id());
            if (it != users_.end()) {
                it->second = update_command.get_new_username();
                std::cout << "Updated user: " << update_command.get_user_id() 
                          << " (" << update_command.get_new_username() << ")" << std::endl;
            }
        }
        
        std::string get_command_type() const override {
            return "update_user";
        }
    };
    
    // Example query handlers
    class GetUserQueryHandler : public IQueryHandler {
    private:
        std::map<int, std::string>& users_;
        std::mutex& users_mutex_;
        
    public:
        GetUserQueryHandler(std::map<int, std::string>& users, std::mutex& users_mutex) 
            : users_(users), users_mutex_(users_mutex) {}
        
        std::any handle_query(const IQuery& query) override {
            const auto& get_query = static_cast<const GetUserQuery&>(query);
            
            std::lock_guard<std::mutex> lock(users_mutex_);
            auto it = users_.find(get_query.get_user_id());
            if (it != users_.end()) {
                return std::make_any<std::string>(it->second);
            }
            return std::make_any<std::string>("");
        }
        
        std::string get_query_type() const override {
            return "get_user";
        }
    };
    
    class GetAllUsersQueryHandler : public IQueryHandler {
    private:
        std::map<int, std::string>& users_;
        std::mutex& users_mutex_;
        
    public:
        GetAllUsersQueryHandler(std::map<int, std::string>& users, std::mutex& users_mutex) 
            : users_(users), users_mutex_(users_mutex) {}
        
        std::any handle_query(const IQuery& query) override {
            std::lock_guard<std::mutex> lock(users_mutex_);
            
            std::vector<std::pair<int, std::string>> result;
            for (const auto& [id, username] : users_) {
                result.emplace_back(id, username);
            }
            return std::make_any<std::vector<std::pair<int, std::string>>>(result);
        }
        
        std::string get_query_type() const override {
            return "get_all_users";
        }
    };
    
    void demonstrateCQRS() {
        std::cout << "\n=== CQRS (Command Query Responsibility Segregation) ===" << std::endl;
        
        // Shared data store
        std::map<int, std::string> users;
        std::mutex users_mutex;
        
        // Create command and query buses
        CommandBus command_bus;
        QueryBus query_bus;
        
        // Create handlers
        auto create_handler = std::make_shared<CreateUserCommandHandler>(users, users_mutex);
        auto update_handler = std::make_shared<UpdateUserCommandHandler>(users, users_mutex);
        auto get_handler = std::make_shared<GetUserQueryHandler>(users, users_mutex);
        auto get_all_handler = std::make_shared<GetAllUsersQueryHandler>(users, users_mutex);
        
        // Register handlers
        command_bus.register_handler(create_handler);
        command_bus.register_handler(update_handler);
        query_bus.register_handler(get_handler);
        query_bus.register_handler(get_all_handler);
        
        // Execute commands
        command_bus.execute(CreateUserCommand(1, "Alice"));
        command_bus.execute(CreateUserCommand(2, "Bob"));
        command_bus.execute(CreateUserCommand(3, "Charlie"));
        
        // Execute queries
        auto user1 = std::any_cast<std::string>(query_bus.execute(GetUserQuery(1)));
        std::cout << "User 1: " << user1 << std::endl;
        
        auto all_users = std::any_cast<std::vector<std::pair<int, std::string>>>(
            query_bus.execute(GetAllUsersQuery()));
        std::cout << "All users:" << std::endl;
        for (const auto& [id, username] : all_users) {
            std::cout << "  " << id << ": " << username << std::endl;
        }
        
        // Update user
        command_bus.execute(UpdateUserCommand(1, "Alice Updated"));
        
        // Query updated user
        auto updated_user1 = std::any_cast<std::string>(query_bus.execute(GetUserQuery(1)));
        std::cout << "Updated User 1: " << updated_user1 << std::endl;
    }
}

// Example 4: Hexagonal Architecture
namespace HexagonalArchitecture {
    
    // Domain entities
    class User {
    private:
        int id_;
        std::string username_;
        std::string email_;
        
    public:
        User(int id, const std::string& username, const std::string& email) 
            : id_(id), username_(username), email_(email) {}
        
        int get_id() const { return id_; }
        const std::string& get_username() const { return username_; }
        const std::string& get_email() const { return email_; }
        
        void set_username(const std::string& username) { username_ = username; }
        void set_email(const std::string& email) { email_ = email; }
    };
    
    // Domain services
    class UserService {
    public:
        virtual ~UserService() = default;
        virtual std::unique_ptr<User> create_user(const std::string& username, const std::string& email) = 0;
        virtual std::unique_ptr<User> get_user(int id) = 0;
        virtual void update_user(std::unique_ptr<User> user) = 0;
        virtual void delete_user(int id) = 0;
        virtual std::vector<std::unique_ptr<User>> get_all_users() = 0;
    };
    
    // Ports (interfaces)
    class IUserRepository {
    public:
        virtual ~IUserRepository() = default;
        virtual std::unique_ptr<User> find_by_id(int id) = 0;
        virtual std::unique_ptr<User> find_by_username(const std::string& username) = 0;
        virtual void save(std::unique_ptr<User> user) = 0;
        virtual void delete_by_id(int id) = 0;
        virtual std::vector<std::unique_ptr<User>> find_all() = 0;
    };
    
    class IEmailService {
    public:
        virtual ~IEmailService() = default;
        virtual void send_welcome_email(const std::string& email, const std::string& username) = 0;
        virtual void send_notification_email(const std::string& email, const std::string& message) = 0;
    };
    
    class IUserValidator {
    public:
        virtual ~IUserValidator() = default;
        virtual bool is_valid_username(const std::string& username) = 0;
        virtual bool is_valid_email(const std::string& email) = 0;
        virtual bool is_username_available(const std::string& username) = 0;
    };
    
    // Adapters (implementations)
    class InMemoryUserRepository : public IUserRepository {
    private:
        std::map<int, std::unique_ptr<User>> users_;
        std::mutex users_mutex_;
        int next_id_;
        
    public:
        InMemoryUserRepository() : next_id_(1) {}
        
        std::unique_ptr<User> find_by_id(int id) override {
            std::lock_guard<std::mutex> lock(users_mutex_);
            auto it = users_.find(id);
            if (it != users_.end()) {
                return std::make_unique<User>(*it->second);
            }
            return nullptr;
        }
        
        std::unique_ptr<User> find_by_username(const std::string& username) override {
            std::lock_guard<std::mutex> lock(users_mutex_);
            for (const auto& [id, user] : users_) {
                if (user->get_username() == username) {
                    return std::make_unique<User>(*user);
                }
            }
            return nullptr;
        }
        
        void save(std::unique_ptr<User> user) override {
            std::lock_guard<std::mutex> lock(users_mutex_);
            users_[user->get_id()] = std::move(user);
        }
        
        void delete_by_id(int id) override {
            std::lock_guard<std::mutex> lock(users_mutex_);
            users_.erase(id);
        }
        
        std::vector<std::unique_ptr<User>> find_all() override {
            std::lock_guard<std::mutex> lock(users_mutex_);
            std::vector<std::unique_ptr<User>> result;
            for (const auto& [id, user] : users_) {
                result.push_back(std::make_unique<User>(*user));
            }
            return result;
        }
        
        int get_next_id() {
            std::lock_guard<std::mutex> lock(users_mutex_);
            return next_id_++;
        }
    };
    
    class ConsoleEmailService : public IEmailService {
    public:
        void send_welcome_email(const std::string& email, const std::string& username) override {
            std::cout << "Sending welcome email to " << email << " for user " << username << std::endl;
        }
        
        void send_notification_email(const std::string& email, const std::string& message) override {
            std::cout << "Sending notification email to " << email << ": " << message << std::endl;
        }
    };
    
    class SimpleUserValidator : public IUserValidator {
    private:
        IUserRepository* repository_;
        
    public:
        SimpleUserValidator(IUserRepository* repository) : repository_(repository) {}
        
        bool is_valid_username(const std::string& username) override {
            return !username.empty() && username.length() >= 3;
        }
        
        bool is_valid_email(const std::string& email) override {
            return !email.empty() && email.find('@') != std::string::npos;
        }
        
        bool is_username_available(const std::string& username) override {
            return repository_->find_by_username(username) == nullptr;
        }
    };
    
    // Application service
    class UserApplicationService : public UserService {
    private:
        std::unique_ptr<IUserRepository> repository_;
        std::unique_ptr<IEmailService> email_service_;
        std::unique_ptr<IUserValidator> validator_;
        
    public:
        UserApplicationService(std::unique_ptr<IUserRepository> repository,
                              std::unique_ptr<IEmailService> email_service,
                              std::unique_ptr<IUserValidator> validator)
            : repository_(std::move(repository)), email_service_(std::move(email_service)), 
              validator_(std::move(validator)) {}
        
        std::unique_ptr<User> create_user(const std::string& username, const std::string& email) override {
            // Validate input
            if (!validator_->is_valid_username(username)) {
                throw std::invalid_argument("Invalid username");
            }
            
            if (!validator_->is_valid_email(email)) {
                throw std::invalid_argument("Invalid email");
            }
            
            if (!validator_->is_username_available(username)) {
                throw std::invalid_argument("Username already exists");
            }
            
            // Create user
            auto repository = dynamic_cast<InMemoryUserRepository*>(repository_.get());
            int id = repository ? repository->get_next_id() : 1;
            auto user = std::make_unique<User>(id, username, email);
            
            // Save user
            repository_->save(std::make_unique<User>(*user));
            
            // Send welcome email
            email_service_->send_welcome_email(email, username);
            
            return user;
        }
        
        std::unique_ptr<User> get_user(int id) override {
            return repository_->find_by_id(id);
        }
        
        void update_user(std::unique_ptr<User> user) override {
            repository_->save(std::move(user));
        }
        
        void delete_user(int id) override {
            repository_->delete_by_id(id);
        }
        
        std::vector<std::unique_ptr<User>> get_all_users() override {
            return repository_->find_all();
        }
    };
    
    void demonstrateHexagonalArchitecture() {
        std::cout << "\n=== Hexagonal Architecture ===" << std::endl;
        
        // Create adapters
        auto repository = std::make_unique<InMemoryUserRepository>();
        auto email_service = std::make_unique<ConsoleEmailService>();
        auto validator = std::make_unique<SimpleUserValidator>(repository.get());
        
        // Create application service
        auto user_service = std::make_unique<UserApplicationService>(
            std::move(repository), std::move(email_service), std::move(validator));
        
        // Use the service
        try {
            auto user1 = user_service->create_user("alice", "alice@example.com");
            std::cout << "Created user: " << user1->get_username() << " (" << user1->get_email() << ")" << std::endl;
            
            auto user2 = user_service->create_user("bob", "bob@example.com");
            std::cout << "Created user: " << user2->get_username() << " (" << user2->get_email() << ")" << std::endl;
            
            // Get user
            auto retrieved_user = user_service->get_user(user1->get_id());
            if (retrieved_user) {
                std::cout << "Retrieved user: " << retrieved_user->get_username() << std::endl;
            }
            
            // Get all users
            auto all_users = user_service->get_all_users();
            std::cout << "All users:" << std::endl;
            for (const auto& user : all_users) {
                std::cout << "  " << user->get_id() << ": " << user->get_username() << " (" << user->get_email() << ")" << std::endl;
            }
            
        } catch (const std::exception& e) {
            std::cout << "Error: " << e.what() << std::endl;
        }
    }
}

int main() {
    std::cout << "=== Advanced Software Architecture Demonstration ===" << std::endl;
    std::cout << "This program demonstrates advanced software architecture patterns including\n"
              << "microservices, event-driven architecture, CQRS, hexagonal architecture,\n"
              << "and system design patterns.\n" << std::endl;
    
    // Demonstrate various architecture patterns
    Microservices::demonstrateMicroservices();
    EventDriven::demonstrateEventDriven();
    CQRS::demonstrateCQRS();
    HexagonalArchitecture::demonstrateHexagonalArchitecture();
    
    std::cout << "\n=== Key Takeaways ===" << std::endl;
    std::cout << "1. Microservices architecture enables independent service development and deployment" << std::endl;
    std::cout << "2. Event-driven architecture provides loose coupling and scalability" << std::endl;
    std::cout << "3. CQRS separates command and query responsibilities for better performance" << std::endl;
    std::cout << "4. Hexagonal architecture isolates business logic from external dependencies" << std::endl;
    std::cout << "5. Service discovery enables dynamic service location and load balancing" << std::endl;
    std::cout << "6. Event buses provide asynchronous communication between components" << std::endl;
    std::cout << "7. Command and query buses enable clean separation of concerns" << std::endl;
    std::cout << "8. Ports and adapters pattern enables testability and flexibility" << std::endl;
    
    std::cout << "\nProgram completed successfully!" << std::endl;
    return 0;
}

/*
 * Compilation Instructions:
 * 
 * Using GCC:
 * g++ -std=c++17 -Wall -Wextra -O2 -pthread -o advanced_software_architecture 03_Advanced_Software_Architecture.cpp
 * 
 * Using Clang:
 * clang++ -std=c++17 -Wall -Wextra -O2 -pthread -o advanced_software_architecture 03_Advanced_Software_Architecture.cpp
 * 
 * Using MSVC (Visual Studio):
 * cl /std:c++17 /EHsc /O2 03_Advanced_Software_Architecture.cpp
 * 
 * Running:
 * ./advanced_software_architecture (Linux/macOS)
 * advanced_software_architecture.exe (Windows)
 * 
 * Note: This lesson requires C++17 for some features.
 * 
 * Advanced Software Architecture Notes:
 * - Microservices architecture enables independent service development and deployment
 * - Event-driven architecture provides loose coupling and scalability
 * - CQRS separates command and query responsibilities for better performance
 * - Hexagonal architecture isolates business logic from external dependencies
 * - Service discovery enables dynamic service location and load balancing
 * - Event buses provide asynchronous communication between components
 * - Command and query buses enable clean separation of concerns
 * - Ports and adapters pattern enables testability and flexibility
 */"""
