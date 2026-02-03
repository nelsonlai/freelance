/*
 * Lesson 16.2: Advanced Software Architecture
 * 
 * This file demonstrates advanced software architecture patterns,
 * microservices, event-driven architecture, and system design.
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

// Example 1: Microservices Architecture
namespace MicroservicesArchitecture {
    
    // Service Interface
    class Service {
    public:
        virtual ~Service() = default;
        virtual std::string process_request(const std::string& request) = 0;
        virtual std::string get_service_name() const = 0;
    };
    
    // User Service
    class UserService : public Service {
    private:
        std::unordered_map<std::string, std::string> users_;
        
    public:
        UserService() {
            users_["user1"] = "John Doe";
            users_["user2"] = "Jane Smith";
        }
        
        std::string process_request(const std::string& request) override {
            std::istringstream iss(request);
            std::string action, user_id;
            iss >> action >> user_id;
            
            if (action == "GET") {
                auto it = users_.find(user_id);
                if (it != users_.end()) {
                    return "User: " + it->second;
                } else {
                    return "User not found";
                }
            } else if (action == "LIST") {
                std::string result = "Users: ";
                for (const auto& user : users_) {
                    result += user.first + " ";
                }
                return result;
            }
            
            return "Invalid request";
        }
        
        std::string get_service_name() const override {
            return "UserService";
        }
    };
    
    // Order Service
    class OrderService : public Service {
    private:
        std::unordered_map<std::string, std::string> orders_;
        std::atomic<int> order_counter_{1};
        
    public:
        std::string process_request(const std::string& request) override {
            std::istringstream iss(request);
            std::string action, user_id;
            iss >> action >> user_id;
            
            if (action == "CREATE") {
                std::string order_id = "order_" + std::to_string(order_counter_++);
                orders_[order_id] = "Order for user " + user_id;
                return "Created order: " + order_id;
            } else if (action == "GET") {
                auto it = orders_.find(user_id);
                if (it != orders_.end()) {
                    return "Order: " + it->second;
                } else {
                    return "Order not found";
                }
            }
            
            return "Invalid request";
        }
        
        std::string get_service_name() const override {
            return "OrderService";
        }
    };
    
    // Payment Service
    class PaymentService : public Service {
    private:
        std::unordered_map<std::string, double> payments_;
        
    public:
        std::string process_request(const std::string& request) override {
            std::istringstream iss(request);
            std::string action, order_id;
            iss >> action >> order_id;
            
            if (action == "PROCESS") {
                double amount = 100.0; // Simplified
                payments_[order_id] = amount;
                return "Payment processed for " + order_id + ": $" + std::to_string(amount);
            } else if (action == "STATUS") {
                auto it = payments_.find(order_id);
                if (it != payments_.end()) {
                    return "Payment status: Completed, Amount: $" + std::to_string(it->second);
                } else {
                    return "Payment not found";
                }
            }
            
            return "Invalid request";
        }
        
        std::string get_service_name() const override {
            return "PaymentService";
        }
    };
    
    // Service Registry
    class ServiceRegistry {
    private:
        std::unordered_map<std::string, std::shared_ptr<Service>> services_;
        std::mutex mutex_;
        
    public:
        void register_service(std::shared_ptr<Service> service) {
            std::lock_guard<std::mutex> lock(mutex_);
            services_[service->get_service_name()] = service;
        }
        
        std::shared_ptr<Service> get_service(const std::string& service_name) {
            std::lock_guard<std::mutex> lock(mutex_);
            auto it = services_.find(service_name);
            return (it != services_.end()) ? it->second : nullptr;
        }
        
        std::vector<std::string> list_services() {
            std::lock_guard<std::mutex> lock(mutex_);
            std::vector<std::string> service_names;
            for (const auto& service : services_) {
                service_names.push_back(service.first);
            }
            return service_names;
        }
    };
    
    // API Gateway
    class APIGateway {
    private:
        ServiceRegistry& registry_;
        
    public:
        APIGateway(ServiceRegistry& registry) : registry_(registry) {}
        
        std::string route_request(const std::string& service_name, const std::string& request) {
            auto service = registry_.get_service(service_name);
            if (service) {
                return service->process_request(request);
            } else {
                return "Service not found: " + service_name;
            }
        }
    };
    
    void demonstrateMicroservicesArchitecture() {
        std::cout << "=== Microservices Architecture ===" << std::endl;
        
        // Create service registry
        ServiceRegistry registry;
        
        // Register services
        registry.register_service(std::make_shared<UserService>());
        registry.register_service(std::make_shared<OrderService>());
        registry.register_service(std::make_shared<PaymentService>());
        
        // Create API gateway
        APIGateway gateway(registry);
        
        // Demonstrate service interactions
        std::cout << "Available services: ";
        for (const auto& service_name : registry.list_services()) {
            std::cout << service_name << " ";
        }
        std::cout << std::endl;
        
        // User service requests
        std::cout << gateway.route_request("UserService", "GET user1") << std::endl;
        std::cout << gateway.route_request("UserService", "LIST") << std::endl;
        
        // Order service requests
        std::cout << gateway.route_request("OrderService", "CREATE user1") << std::endl;
        std::cout << gateway.route_request("OrderService", "GET order_1") << std::endl;
        
        // Payment service requests
        std::cout << gateway.route_request("PaymentService", "PROCESS order_1") << std::endl;
        std::cout << gateway.route_request("PaymentService", "STATUS order_1") << std::endl;
    }
}

// Example 2: Event-Driven Architecture
namespace EventDrivenArchitecture {
    
    // Event Base Class
    class Event {
    public:
        virtual ~Event() = default;
        virtual std::string get_type() const = 0;
        virtual std::string get_data() const = 0;
    };
    
    // Specific Events
    class UserCreatedEvent : public Event {
    private:
        std::string user_id_;
        std::string user_name_;
        
    public:
        UserCreatedEvent(const std::string& user_id, const std::string& user_name)
            : user_id_(user_id), user_name_(user_name) {}
        
        std::string get_type() const override {
            return "UserCreated";
        }
        
        std::string get_data() const override {
            return "User ID: " + user_id_ + ", Name: " + user_name_;
        }
        
        const std::string& get_user_id() const { return user_id_; }
        const std::string& get_user_name() const { return user_name_; }
    };
    
    class OrderPlacedEvent : public Event {
    private:
        std::string order_id_;
        std::string user_id_;
        double amount_;
        
    public:
        OrderPlacedEvent(const std::string& order_id, const std::string& user_id, double amount)
            : order_id_(order_id), user_id_(user_id), amount_(amount) {}
        
        std::string get_type() const override {
            return "OrderPlaced";
        }
        
        std::string get_data() const override {
            return "Order ID: " + order_id_ + ", User ID: " + user_id_ + ", Amount: $" + std::to_string(amount_);
        }
        
        const std::string& get_order_id() const { return order_id_; }
        const std::string& get_user_id() const { return user_id_; }
        double get_amount() const { return amount_; }
    };
    
    class PaymentProcessedEvent : public Event {
    private:
        std::string payment_id_;
        std::string order_id_;
        double amount_;
        
    public:
        PaymentProcessedEvent(const std::string& payment_id, const std::string& order_id, double amount)
            : payment_id_(payment_id), order_id_(order_id), amount_(amount) {}
        
        std::string get_type() const override {
            return "PaymentProcessed";
        }
        
        std::string get_data() const override {
            return "Payment ID: " + payment_id_ + ", Order ID: " + order_id_ + ", Amount: $" + std::to_string(amount_);
        }
        
        const std::string& get_payment_id() const { return payment_id_; }
        const std::string& get_order_id() const { return order_id_; }
        double get_amount() const { return amount_; }
    };
    
    // Event Handler Interface
    class EventHandler {
    public:
        virtual ~EventHandler() = default;
        virtual void handle_event(std::shared_ptr<Event> event) = 0;
        virtual std::string get_handler_name() const = 0;
    };
    
    // Email Notification Handler
    class EmailNotificationHandler : public EventHandler {
    public:
        void handle_event(std::shared_ptr<Event> event) override {
            std::cout << "EmailNotificationHandler: Sending email for event " << event->get_type() << std::endl;
            
            if (event->get_type() == "UserCreated") {
                auto user_event = std::dynamic_pointer_cast<UserCreatedEvent>(event);
                if (user_event) {
                    std::cout << "  Welcome email sent to user: " << user_event->get_user_name() << std::endl;
                }
            } else if (event->get_type() == "OrderPlaced") {
                auto order_event = std::dynamic_pointer_cast<OrderPlacedEvent>(event);
                if (order_event) {
                    std::cout << "  Order confirmation email sent for order: " << order_event->get_order_id() << std::endl;
                }
            }
        }
        
        std::string get_handler_name() const override {
            return "EmailNotificationHandler";
        }
    };
    
    // Inventory Handler
    class InventoryHandler : public EventHandler {
    public:
        void handle_event(std::shared_ptr<Event> event) override {
            if (event->get_type() == "OrderPlaced") {
                auto order_event = std::dynamic_pointer_cast<OrderPlacedEvent>(event);
                if (order_event) {
                    std::cout << "InventoryHandler: Updating inventory for order " << order_event->get_order_id() << std::endl;
                }
            }
        }
        
        std::string get_handler_name() const override {
            return "InventoryHandler";
        }
    };
    
    // Audit Handler
    class AuditHandler : public EventHandler {
    private:
        std::vector<std::string> audit_log_;
        
    public:
        void handle_event(std::shared_ptr<Event> event) override {
            std::string log_entry = "[" + std::to_string(std::chrono::duration_cast<std::chrono::milliseconds>(
                std::chrono::system_clock::now().time_since_epoch()).count()) + "] " +
                event->get_type() + ": " + event->get_data();
            
            audit_log_.push_back(log_entry);
            std::cout << "AuditHandler: Logged event - " << event->get_type() << std::endl;
        }
        
        std::string get_handler_name() const override {
            return "AuditHandler";
        }
        
        void print_audit_log() {
            std::cout << "Audit Log:" << std::endl;
            for (const auto& entry : audit_log_) {
                std::cout << "  " << entry << std::endl;
            }
        }
    };
    
    // Event Bus
    class EventBus {
    private:
        std::unordered_map<std::string, std::vector<std::shared_ptr<EventHandler>>> handlers_;
        std::queue<std::shared_ptr<Event>> event_queue_;
        std::mutex queue_mutex_;
        std::condition_variable cv_;
        std::atomic<bool> running_{true};
        std::thread worker_thread_;
        
    public:
        EventBus() : worker_thread_(&EventBus::process_events, this) {}
        
        ~EventBus() {
            running_ = false;
            cv_.notify_all();
            if (worker_thread_.joinable()) {
                worker_thread_.join();
            }
        }
        
        void subscribe(const std::string& event_type, std::shared_ptr<EventHandler> handler) {
            handlers_[event_type].push_back(handler);
        }
        
        void publish(std::shared_ptr<Event> event) {
            {
                std::lock_guard<std::mutex> lock(queue_mutex_);
                event_queue_.push(event);
            }
            cv_.notify_one();
        }
        
    private:
        void process_events() {
            while (running_) {
                std::unique_lock<std::mutex> lock(queue_mutex_);
                cv_.wait(lock, [this] { return !event_queue_.empty() || !running_; });
                
                if (!running_) break;
                
                auto event = event_queue_.front();
                event_queue_.pop();
                lock.unlock();
                
                // Notify all handlers for this event type
                auto it = handlers_.find(event->get_type());
                if (it != handlers_.end()) {
                    for (const auto& handler : it->second) {
                        handler->handle_event(event);
                    }
                }
            }
        }
    };
    
    void demonstrateEventDrivenArchitecture() {
        std::cout << "\n=== Event-Driven Architecture ===" << std::endl;
        
        // Create event bus
        EventBus event_bus;
        
        // Create handlers
        auto email_handler = std::make_shared<EmailNotificationHandler>();
        auto inventory_handler = std::make_shared<InventoryHandler>();
        auto audit_handler = std::make_shared<AuditHandler>();
        
        // Subscribe handlers to events
        event_bus.subscribe("UserCreated", email_handler);
        event_bus.subscribe("OrderPlaced", email_handler);
        event_bus.subscribe("OrderPlaced", inventory_handler);
        event_bus.subscribe("UserCreated", audit_handler);
        event_bus.subscribe("OrderPlaced", audit_handler);
        event_bus.subscribe("PaymentProcessed", audit_handler);
        
        // Publish events
        event_bus.publish(std::make_shared<UserCreatedEvent>("user1", "John Doe"));
        event_bus.publish(std::make_shared<OrderPlacedEvent>("order1", "user1", 99.99));
        event_bus.publish(std::make_shared<PaymentProcessedEvent>("payment1", "order1", 99.99));
        
        // Wait for events to be processed
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        
        // Print audit log
        audit_handler->print_audit_log();
    }
}

// Example 3: CQRS (Command Query Responsibility Segregation)
namespace CQRSArchitecture {
    
    // Command Interface
    class Command {
    public:
        virtual ~Command() = default;
        virtual std::string get_type() const = 0;
    };
    
    // Query Interface
    class Query {
    public:
        virtual ~Query() = default;
        virtual std::string get_type() const = 0;
    };
    
    // Specific Commands
    class CreateUserCommand : public Command {
    private:
        std::string user_id_;
        std::string user_name_;
        std::string email_;
        
    public:
        CreateUserCommand(const std::string& user_id, const std::string& user_name, const std::string& email)
            : user_id_(user_id), user_name_(user_name), email_(email) {}
        
        std::string get_type() const override {
            return "CreateUser";
        }
        
        const std::string& get_user_id() const { return user_id_; }
        const std::string& get_user_name() const { return user_name_; }
        const std::string& get_email() const { return email_; }
    };
    
    class UpdateUserCommand : public Command {
    private:
        std::string user_id_;
        std::string new_name_;
        
    public:
        UpdateUserCommand(const std::string& user_id, const std::string& new_name)
            : user_id_(user_id), new_name_(new_name) {}
        
        std::string get_type() const override {
            return "UpdateUser";
        }
        
        const std::string& get_user_id() const { return user_id_; }
        const std::string& get_new_name() const { return new_name_; }
    };
    
    // Specific Queries
    class GetUserQuery : public Query {
    private:
        std::string user_id_;
        
    public:
        GetUserQuery(const std::string& user_id) : user_id_(user_id) {}
        
        std::string get_type() const override {
            return "GetUser";
        }
        
        const std::string& get_user_id() const { return user_id_; }
    };
    
    class ListUsersQuery : public Query {
    public:
        std::string get_type() const override {
            return "ListUsers";
        }
    };
    
    // Command Handler Interface
    class CommandHandler {
    public:
        virtual ~CommandHandler() = default;
        virtual void handle_command(std::shared_ptr<Command> command) = 0;
        virtual std::string get_command_type() const = 0;
    };
    
    // Query Handler Interface
    class QueryHandler {
    public:
        virtual ~QueryHandler() = default;
        virtual std::string handle_query(std::shared_ptr<Query> query) = 0;
        virtual std::string get_query_type() const = 0;
    };
    
    // User Command Handler
    class UserCommandHandler : public CommandHandler {
    private:
        std::unordered_map<std::string, std::pair<std::string, std::string>> users_; // id -> (name, email)
        
    public:
        void handle_command(std::shared_ptr<Command> command) override {
            if (command->get_type() == "CreateUser") {
                auto create_cmd = std::dynamic_pointer_cast<CreateUserCommand>(command);
                if (create_cmd) {
                    users_[create_cmd->get_user_id()] = {create_cmd->get_user_name(), create_cmd->get_email()};
                    std::cout << "UserCommandHandler: Created user " << create_cmd->get_user_name() << std::endl;
                }
            } else if (command->get_type() == "UpdateUser") {
                auto update_cmd = std::dynamic_pointer_cast<UpdateUserCommand>(command);
                if (update_cmd) {
                    auto it = users_.find(update_cmd->get_user_id());
                    if (it != users_.end()) {
                        it->second.first = update_cmd->get_new_name();
                        std::cout << "UserCommandHandler: Updated user " << update_cmd->get_user_id() << std::endl;
                    }
                }
            }
        }
        
        std::string get_command_type() const override {
            return "UserCommand";
        }
        
        // For simplicity, expose data to query handler
        const std::unordered_map<std::string, std::pair<std::string, std::string>>& get_users() const {
            return users_;
        }
    };
    
    // User Query Handler
    class UserQueryHandler : public QueryHandler {
    private:
        UserCommandHandler& command_handler_;
        
    public:
        UserQueryHandler(UserCommandHandler& command_handler) : command_handler_(command_handler) {}
        
        std::string handle_query(std::shared_ptr<Query> query) override {
            if (query->get_type() == "GetUser") {
                auto get_query = std::dynamic_pointer_cast<GetUserQuery>(query);
                if (get_query) {
                    const auto& users = command_handler_.get_users();
                    auto it = users.find(get_query->get_user_id());
                    if (it != users.end()) {
                        return "User: " + it->second.first + " (" + it->second.second + ")";
                    } else {
                        return "User not found";
                    }
                }
            } else if (query->get_type() == "ListUsers") {
                const auto& users = command_handler_.get_users();
                std::string result = "Users: ";
                for (const auto& user : users) {
                    result += user.first + " (" + user.second.first + ") ";
                }
                return result;
            }
            
            return "Invalid query";
        }
        
        std::string get_query_type() const override {
            return "UserQuery";
        }
    };
    
    // Command Bus
    class CommandBus {
    private:
        std::unordered_map<std::string, std::shared_ptr<CommandHandler>> handlers_;
        
    public:
        void register_handler(std::shared_ptr<CommandHandler> handler) {
            handlers_[handler->get_command_type()] = handler;
        }
        
        void send_command(std::shared_ptr<Command> command) {
            // For simplicity, handle all user commands with UserCommandHandler
            auto it = handlers_.find("UserCommand");
            if (it != handlers_.end()) {
                it->second->handle_command(command);
            }
        }
    };
    
    // Query Bus
    class QueryBus {
    private:
        std::unordered_map<std::string, std::shared_ptr<QueryHandler>> handlers_;
        
    public:
        void register_handler(std::shared_ptr<QueryHandler> handler) {
            handlers_[handler->get_query_type()] = handler;
        }
        
        std::string send_query(std::shared_ptr<Query> query) {
            // For simplicity, handle all user queries with UserQueryHandler
            auto it = handlers_.find("UserQuery");
            if (it != handlers_.end()) {
                return it->second->handle_query(query);
            }
            return "No handler found";
        }
    };
    
    void demonstrateCQRSArchitecture() {
        std::cout << "\n=== CQRS Architecture ===" << std::endl;
        
        // Create command handler
        auto user_command_handler = std::make_shared<UserCommandHandler>();
        
        // Create query handler
        auto user_query_handler = std::make_shared<UserQueryHandler>(*user_command_handler);
        
        // Create buses
        CommandBus command_bus;
        QueryBus query_bus;
        
        // Register handlers
        command_bus.register_handler(user_command_handler);
        query_bus.register_handler(user_query_handler);
        
        // Send commands
        command_bus.send_command(std::make_shared<CreateUserCommand>("user1", "John Doe", "john@example.com"));
        command_bus.send_command(std::make_shared<CreateUserCommand>("user2", "Jane Smith", "jane@example.com"));
        command_bus.send_command(std::make_shared<UpdateUserCommand>("user1", "John Updated"));
        
        // Send queries
        std::cout << query_bus.send_query(std::make_shared<GetUserQuery>("user1")) << std::endl;
        std::cout << query_bus.send_query(std::make_shared<ListUsersQuery>()) << std::endl;
    }
}

// Example 4: Hexagonal Architecture (Ports and Adapters)
namespace HexagonalArchitecture {
    
    // Domain Entity
    class User {
    private:
        std::string id_;
        std::string name_;
        std::string email_;
        
    public:
        User(const std::string& id, const std::string& name, const std::string& email)
            : id_(id), name_(name), email_(email) {}
        
        const std::string& get_id() const { return id_; }
        const std::string& get_name() const { return name_; }
        const std::string& get_email() const { return email_; }
        
        void update_name(const std::string& new_name) {
            name_ = new_name;
        }
    };
    
    // Port Interfaces (Domain Layer)
    class UserRepository {
    public:
        virtual ~UserRepository() = default;
        virtual std::shared_ptr<User> find_by_id(const std::string& id) = 0;
        virtual std::vector<std::shared_ptr<User>> find_all() = 0;
        virtual void save(std::shared_ptr<User> user) = 0;
        virtual void delete_by_id(const std::string& id) = 0;
    };
    
    class EmailService {
    public:
        virtual ~EmailService() = default;
        virtual void send_email(const std::string& to, const std::string& subject, const std::string& body) = 0;
    };
    
    // Application Service (Application Layer)
    class UserApplicationService {
    private:
        std::shared_ptr<UserRepository> user_repository_;
        std::shared_ptr<EmailService> email_service_;
        
    public:
        UserApplicationService(std::shared_ptr<UserRepository> user_repo, std::shared_ptr<EmailService> email_svc)
            : user_repository_(user_repo), email_service_(email_svc) {}
        
        std::shared_ptr<User> create_user(const std::string& id, const std::string& name, const std::string& email) {
            auto user = std::make_shared<User>(id, name, email);
            user_repository_->save(user);
            
            email_service_->send_email(email, "Welcome", "Welcome to our service!");
            
            return user;
        }
        
        std::shared_ptr<User> get_user(const std::string& id) {
            return user_repository_->find_by_id(id);
        }
        
        void update_user_name(const std::string& id, const std::string& new_name) {
            auto user = user_repository_->find_by_id(id);
            if (user) {
                user->update_name(new_name);
                user_repository_->save(user);
                
                email_service_->send_email(user->get_email(), "Profile Updated", "Your profile has been updated.");
            }
        }
        
        std::vector<std::shared_ptr<User>> list_users() {
            return user_repository_->find_all();
        }
    };
    
    // Adapters (Infrastructure Layer)
    class InMemoryUserRepository : public UserRepository {
    private:
        std::unordered_map<std::string, std::shared_ptr<User>> users_;
        
    public:
        std::shared_ptr<User> find_by_id(const std::string& id) override {
            auto it = users_.find(id);
            return (it != users_.end()) ? it->second : nullptr;
        }
        
        std::vector<std::shared_ptr<User>> find_all() override {
            std::vector<std::shared_ptr<User>> result;
            for (const auto& pair : users_) {
                result.push_back(pair.second);
            }
            return result;
        }
        
        void save(std::shared_ptr<User> user) override {
            users_[user->get_id()] = user;
        }
        
        void delete_by_id(const std::string& id) override {
            users_.erase(id);
        }
    };
    
    class ConsoleEmailService : public EmailService {
    public:
        void send_email(const std::string& to, const std::string& subject, const std::string& body) override {
            std::cout << "Email sent to: " << to << std::endl;
            std::cout << "Subject: " << subject << std::endl;
            std::cout << "Body: " << body << std::endl;
        }
    };
    
    // Primary Adapter (Driving Port)
    class UserController {
    private:
        UserApplicationService& user_service_;
        
    public:
        UserController(UserApplicationService& user_service) : user_service_(user_service) {}
        
        void handle_create_user(const std::string& id, const std::string& name, const std::string& email) {
            std::cout << "UserController: Creating user " << name << std::endl;
            auto user = user_service_.create_user(id, name, email);
            std::cout << "UserController: User created with ID " << user->get_id() << std::endl;
        }
        
        void handle_get_user(const std::string& id) {
            std::cout << "UserController: Getting user " << id << std::endl;
            auto user = user_service_.get_user(id);
            if (user) {
                std::cout << "UserController: Found user " << user->get_name() << " (" << user->get_email() << ")" << std::endl;
            } else {
                std::cout << "UserController: User not found" << std::endl;
            }
        }
        
        void handle_update_user(const std::string& id, const std::string& new_name) {
            std::cout << "UserController: Updating user " << id << " to " << new_name << std::endl;
            user_service_.update_user_name(id, new_name);
        }
    };
    
    void demonstrateHexagonalArchitecture() {
        std::cout << "\n=== Hexagonal Architecture ===" << std::endl;
        
        // Create adapters
        auto user_repository = std::make_shared<InMemoryUserRepository>();
        auto email_service = std::make_shared<ConsoleEmailService>();
        
        // Create application service
        UserApplicationService user_service(user_repository, email_service);
        
        // Create primary adapter
        UserController controller(user_service);
        
        // Demonstrate use cases
        controller.handle_create_user("user1", "John Doe", "john@example.com");
        controller.handle_create_user("user2", "Jane Smith", "jane@example.com");
        
        controller.handle_get_user("user1");
        controller.handle_get_user("user3"); // Non-existent user
        
        controller.handle_update_user("user1", "John Updated");
        controller.handle_get_user("user1");
    }
}

// Example 5: System Design Patterns
namespace SystemDesignPatterns {
    
    // Load Balancer
    class LoadBalancer {
    private:
        std::vector<std::string> servers_;
        std::atomic<int> current_server_{0};
        
    public:
        void add_server(const std::string& server) {
            servers_.push_back(server);
        }
        
        std::string get_server() {
            if (servers_.empty()) {
                return "No servers available";
            }
            
            int index = current_server_.fetch_add(1) % servers_.size();
            return servers_[index];
        }
        
        void remove_server(const std::string& server) {
            servers_.erase(std::remove(servers_.begin(), servers_.end(), server), servers_.end());
        }
        
        size_t server_count() const {
            return servers_.size();
        }
    };
    
    // Circuit Breaker
    class CircuitBreaker {
    private:
        enum class State { CLOSED, OPEN, HALF_OPEN };
        
        State state_;
        int failure_count_;
        int failure_threshold_;
        std::chrono::steady_clock::time_point last_failure_time_;
        std::chrono::milliseconds timeout_;
        
    public:
        CircuitBreaker(int threshold = 5, std::chrono::milliseconds timeout = std::chrono::milliseconds(1000))
            : state_(State::CLOSED), failure_count_(0), failure_threshold_(threshold), timeout_(timeout) {}
        
        bool can_execute() {
            if (state_ == State::CLOSED) {
                return true;
            } else if (state_ == State::OPEN) {
                if (std::chrono::steady_clock::now() - last_failure_time_ > timeout_) {
                    state_ = State::HALF_OPEN;
                    return true;
                }
                return false;
            } else { // HALF_OPEN
                return true;
            }
        }
        
        void record_success() {
            failure_count_ = 0;
            state_ = State::CLOSED;
        }
        
        void record_failure() {
            failure_count_++;
            last_failure_time_ = std::chrono::steady_clock::now();
            
            if (failure_count_ >= failure_threshold_) {
                state_ = State::OPEN;
            }
        }
        
        std::string get_state() const {
            switch (state_) {
                case State::CLOSED: return "CLOSED";
                case State::OPEN: return "OPEN";
                case State::HALF_OPEN: return "HALF_OPEN";
                default: return "UNKNOWN";
            }
        }
    };
    
    // Cache with TTL
    template<typename K, typename V>
    class TTLCache {
    private:
        struct CacheEntry {
            V value;
            std::chrono::steady_clock::time_point expiry_time;
        };
        
        std::unordered_map<K, CacheEntry> cache_;
        std::mutex mutex_;
        std::chrono::milliseconds ttl_;
        
    public:
        TTLCache(std::chrono::milliseconds ttl = std::chrono::milliseconds(5000)) : ttl_(ttl) {}
        
        void put(const K& key, const V& value) {
            std::lock_guard<std::mutex> lock(mutex_);
            cache_[key] = {value, std::chrono::steady_clock::now() + ttl_};
        }
        
        std::optional<V> get(const K& key) {
            std::lock_guard<std::mutex> lock(mutex_);
            auto it = cache_.find(key);
            if (it != cache_.end()) {
                if (std::chrono::steady_clock::now() < it->second.expiry_time) {
                    return it->second.value;
                } else {
                    cache_.erase(it);
                }
            }
            return std::nullopt;
        }
        
        void remove(const K& key) {
            std::lock_guard<std::mutex> lock(mutex_);
            cache_.erase(key);
        }
        
        void clear() {
            std::lock_guard<std::mutex> lock(mutex_);
            cache_.clear();
        }
        
        size_t size() const {
            std::lock_guard<std::mutex> lock(mutex_);
            return cache_.size();
        }
    };
    
    void demonstrateSystemDesignPatterns() {
        std::cout << "\n=== System Design Patterns ===" << std::endl;
        
        // Load Balancer
        LoadBalancer load_balancer;
        load_balancer.add_server("server1.example.com");
        load_balancer.add_server("server2.example.com");
        load_balancer.add_server("server3.example.com");
        
        std::cout << "Load balancer distributing requests:" << std::endl;
        for (int i = 0; i < 10; ++i) {
            std::cout << "Request " << i + 1 << " -> " << load_balancer.get_server() << std::endl;
        }
        
        // Circuit Breaker
        CircuitBreaker circuit_breaker(3, std::chrono::milliseconds(1000));
        
        std::cout << "\nCircuit breaker test:" << std::endl;
        for (int i = 0; i < 5; ++i) {
            if (circuit_breaker.can_execute()) {
                std::cout << "Request " << i + 1 << " executed, state: " << circuit_breaker.get_state() << std::endl;
                circuit_breaker.record_failure(); // Simulate failures
            } else {
                std::cout << "Request " << i + 1 << " blocked, state: " << circuit_breaker.get_state() << std::endl;
            }
        }
        
        // TTL Cache
        TTLCache<std::string, std::string> cache(std::chrono::milliseconds(2000));
        
        cache.put("key1", "value1");
        cache.put("key2", "value2");
        
        auto value = cache.get("key1");
        if (value) {
            std::cout << "\nCache hit: " << *value << std::endl;
        }
        
        std::cout << "Cache size: " << cache.size() << std::endl;
        
        // Wait for cache to expire
        std::this_thread::sleep_for(std::chrono::milliseconds(2500));
        
        value = cache.get("key1");
        if (!value) {
            std::cout << "Cache miss (expired)" << std::endl;
        }
        
        std::cout << "Cache size after expiry: " << cache.size() << std::endl;
    }
}

int main() {
    std::cout << "=== Advanced Software Architecture Demonstration ===" << std::endl;
    std::cout << "This program demonstrates advanced software architecture patterns,\n"
              << "microservices, event-driven architecture, and system design.\n" << std::endl;
    
    // Demonstrate various advanced architecture patterns
    MicroservicesArchitecture::demonstrateMicroservicesArchitecture();
    EventDrivenArchitecture::demonstrateEventDrivenArchitecture();
    CQRSArchitecture::demonstrateCQRSArchitecture();
    HexagonalArchitecture::demonstrateHexagonalArchitecture();
    SystemDesignPatterns::demonstrateSystemDesignPatterns();
    
    std::cout << "\n=== Key Takeaways ===" << std::endl;
    std::cout << "1. Microservices architecture enables scalable and maintainable systems" << std::endl;
    std::cout << "2. Event-driven architecture provides loose coupling and flexibility" << std::endl;
    std::cout << "3. CQRS separates command and query responsibilities for better performance" << std::endl;
    std::cout << "4. Hexagonal architecture isolates business logic from infrastructure" << std::endl;
    std::cout << "5. System design patterns address scalability and reliability challenges" << std::endl;
    std::cout << "6. Proper architecture enables system evolution and maintenance" << std::endl;
    std::cout << "7. Architecture patterns should be chosen based on system requirements" << std::endl;
    std::cout << "8. Modern systems require sophisticated architectural approaches" << std::endl;
    
    std::cout << "\nProgram completed successfully!" << std::endl;
    return 0;
}

/*
 * Compilation Instructions:
 * 
 * Using GCC:
 * g++ -std=c++17 -Wall -Wextra -O2 -pthread -o advanced_software_architecture 02_Advanced_Software_Architecture.cpp
 * 
 * Using Clang:
 * clang++ -std=c++17 -Wall -Wextra -O2 -pthread -o advanced_software_architecture 02_Advanced_Software_Architecture.cpp
 * 
 * Using MSVC (Visual Studio):
 * cl /std:c++17 /EHsc /O2 02_Advanced_Software_Architecture.cpp
 * 
 * Running:
 * ./advanced_software_architecture (Linux/macOS)
 * advanced_software_architecture.exe (Windows)
 * 
 * Note: This lesson requires C++17 or later for some features.
 * C++20 is recommended for best architecture support.
 * 
 * Advanced Software Architecture Notes:
 * - Microservices architecture enables scalable and maintainable systems
 * - Event-driven architecture provides loose coupling and flexibility
 * - CQRS separates command and query responsibilities for better performance
 * - Hexagonal architecture isolates business logic from infrastructure
 * - System design patterns address scalability and reliability challenges
 * - Proper architecture enables system evolution and maintenance
 * - Architecture patterns should be chosen based on system requirements
 * - Modern systems require sophisticated architectural approaches
 */"""
