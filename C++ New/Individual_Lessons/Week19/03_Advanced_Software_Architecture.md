# Week 19, Lesson 3: Advanced Software Architecture

## 1. Learning Objectives

- Understand advanced software architecture patterns and their applications.
- Learn microservices architecture and service-oriented design.
- Explore event-driven architecture and asynchronous communication.
- Understand CQRS (Command Query Responsibility Segregation) pattern.
- Learn hexagonal architecture and ports/adapters pattern.
- Explore system design patterns and architectural principles.
- Understand service discovery and load balancing concepts.
- Learn best practices for scalable and maintainable software architecture.

## 2. Prerequisites

- Understanding of basic software architecture concepts
- Knowledge of design patterns and architectural principles
- Familiarity with distributed systems concepts
- Understanding of service-oriented architecture
- Knowledge of event-driven programming

## 3. Microservices Architecture

### 3.1 Microservices Concepts

**Microservices Benefits:**
- Independent development and deployment
- Technology diversity
- Fault isolation
- Scalability
- Team autonomy

**Microservices Challenges:**
- Distributed system complexity
- Data consistency
- Network latency
- Service discovery
- Monitoring and debugging

### 3.2 Service Interface

```cpp
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
```

### 3.3 Service Registry

```cpp
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
```

### 3.4 Service Discovery

```cpp
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
```

### 3.5 Example Services

```cpp
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
```

## 4. Event-Driven Architecture

### 4.1 Event-Driven Concepts

**Event-Driven Benefits:**
- Loose coupling
- Scalability
- Asynchronous processing
- Event sourcing
- Reactive systems

**Event-Driven Patterns:**
- **Event Sourcing**: Store events instead of state
- **CQRS**: Separate read and write models
- **Saga Pattern**: Manage distributed transactions
- **Event Streaming**: Process continuous event streams

### 4.2 Event Interface

```cpp
// Event base class
class IEvent {
public:
    virtual ~IEvent() = default;
    virtual std::string get_type() const = 0;
    virtual std::string get_source() const = 0;
    virtual std::chrono::steady_clock::time_point get_timestamp() const = 0;
};
```

### 4.3 Event Handler Interface

```cpp
// Event handler interface
class IEventHandler {
public:
    virtual ~IEventHandler() = default;
    virtual void handle_event(const IEvent& event) = 0;
    virtual std::string get_handler_name() const = 0;
};
```

### 4.4 Event Bus

```cpp
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
```

### 4.5 Example Events

```cpp
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
```

## 5. CQRS (Command Query Responsibility Segregation)

### 5.1 CQRS Concepts

**CQRS Benefits:**
- Separation of concerns
- Performance optimization
- Scalability
- Event sourcing
- Independent scaling

**CQRS Patterns:**
- **Command Side**: Write operations, business logic
- **Query Side**: Read operations, optimized views
- **Event Sourcing**: Store events instead of state
- **Saga Pattern**: Manage distributed transactions

### 5.2 Command and Query Interfaces

```cpp
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
```

### 5.3 Command Bus

```cpp
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
```

### 5.4 Query Bus

```cpp
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
```

### 5.5 Example Commands and Queries

```cpp
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
```

## 6. Hexagonal Architecture

### 6.1 Hexagonal Architecture Concepts

**Hexagonal Architecture Benefits:**
- Testability
- Independence from external systems
- Flexibility
- Maintainability
- Clear separation of concerns

**Hexagonal Architecture Components:**
- **Domain**: Business logic and entities
- **Ports**: Interfaces for external interactions
- **Adapters**: Implementations of ports
- **Application Services**: Orchestrate domain operations

### 6.2 Domain Entities

```cpp
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
```

### 6.3 Ports (Interfaces)

```cpp
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
```

### 6.4 Adapters (Implementations)

```cpp
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
```

### 6.5 Application Service

```cpp
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
```

## 7. Best Practices

### 7.1 Architecture Design Principles

**SOLID Principles:**
- **Single Responsibility**: Each class has one reason to change
- **Open/Closed**: Open for extension, closed for modification
- **Liskov Substitution**: Derived classes must be substitutable for base classes
- **Interface Segregation**: Clients shouldn't depend on interfaces they don't use
- **Dependency Inversion**: Depend on abstractions, not concretions

**Architectural Principles:**
- **Separation of Concerns**: Different aspects of functionality should be separated
- **Loose Coupling**: Components should have minimal dependencies on each other
- **High Cohesion**: Related functionality should be grouped together
- **Single Source of Truth**: Each piece of data should have one authoritative source

### 7.2 Microservices Best Practices

**Service Design:**
- Design services around business capabilities
- Keep services small and focused
- Use appropriate communication patterns
- Implement proper error handling
- Design for failure

**Service Communication:**
- Use asynchronous communication when possible
- Implement circuit breakers
- Use service mesh for complex communication
- Implement proper timeout handling
- Use event-driven communication

### 7.3 Event-Driven Best Practices

**Event Design:**
- Design events around business events
- Keep events immutable
- Use event versioning
- Implement proper event ordering
- Design for backward compatibility

**Event Handling:**
- Implement idempotent event handlers
- Use event sourcing when appropriate
- Implement proper error handling
- Use event replay for recovery
- Monitor event processing

### 7.4 CQRS Best Practices

**Command Design:**
- Design commands around business operations
- Keep commands simple and focused
- Implement proper validation
- Use command handlers for business logic
- Implement proper error handling

**Query Design:**
- Design queries for specific use cases
- Optimize read models for performance
- Use denormalized data when appropriate
- Implement proper caching
- Use projection patterns

### 7.5 Hexagonal Architecture Best Practices

**Port Design:**
- Design ports around business needs
- Keep ports focused and cohesive
- Use appropriate abstractions
- Implement proper error handling
- Design for testability

**Adapter Implementation:**
- Implement adapters for specific technologies
- Keep adapters thin and focused
- Use dependency injection
- Implement proper error handling
- Design for maintainability

## 8. Common Pitfalls and Solutions

### 8.1 Microservices Pitfalls

**Problem**: Service boundaries not well defined
**Solution**: Design services around business capabilities and bounded contexts

**Problem**: Distributed system complexity
**Solution**: Use appropriate patterns like circuit breakers, retries, and timeouts

**Problem**: Data consistency issues
**Solution**: Use eventual consistency, saga patterns, and event sourcing

### 8.2 Event-Driven Pitfalls

**Problem**: Event ordering issues
**Solution**: Use event versioning, timestamps, and proper event handling

**Problem**: Event processing failures
**Solution**: Implement idempotent handlers, error handling, and event replay

**Problem**: Event schema evolution
**Solution**: Use event versioning and backward compatibility

### 8.3 CQRS Pitfalls

**Problem**: Command and query model divergence
**Solution**: Use event sourcing and proper synchronization

**Problem**: Complex read model updates
**Solution**: Use projection patterns and event handlers

**Problem**: Data consistency issues
**Solution**: Use eventual consistency and proper event handling

### 8.4 Hexagonal Architecture Pitfalls

**Problem**: Over-abstraction
**Solution**: Design ports around business needs, not technical concerns

**Problem**: Adapter complexity
**Solution**: Keep adapters thin and focused on technology-specific concerns

**Problem**: Testing complexity
**Solution**: Use dependency injection and mock adapters for testing

## 9. Advanced Topics

### 9.1 System Design Patterns

**Load Balancing:**
- Round-robin
- Least connections
- Weighted round-robin
- Geographic routing

**Caching Strategies:**
- Cache-aside
- Write-through
- Write-behind
- Refresh-ahead

**Database Patterns:**
- Read replicas
- Sharding
- Event sourcing
- CQRS

### 9.2 Distributed Systems Patterns

**Consistency Patterns:**
- Strong consistency
- Eventual consistency
- BASE (Basically Available, Soft state, Eventual consistency)
- CAP theorem

**Communication Patterns:**
- Request-response
- Publish-subscribe
- Message queues
- Event streaming

### 9.3 Scalability Patterns

**Horizontal Scaling:**
- Load balancing
- Service mesh
- Auto-scaling
- Container orchestration

**Vertical Scaling:**
- Resource optimization
- Performance tuning
- Caching
- Database optimization

## 10. Summary

Advanced software architecture patterns provide powerful tools for building scalable, maintainable, and flexible systems. Key takeaways include:

1. **Microservices architecture** enables independent service development and deployment
2. **Event-driven architecture** provides loose coupling and scalability
3. **CQRS** separates command and query responsibilities for better performance
4. **Hexagonal architecture** isolates business logic from external dependencies
5. **Service discovery** enables dynamic service location and load balancing
6. **Event buses** provide asynchronous communication between components
7. **Command and query buses** enable clean separation of concerns
8. **Ports and adapters pattern** enables testability and flexibility

Effective software architecture requires understanding both the business requirements and the technical constraints, combined with appropriate use of architectural patterns and principles.

## 11. Exercises

### Exercise 1: Microservices System
Implement a microservices system with service registry, discovery, and health checking capabilities.

### Exercise 2: Event-Driven System
Create an event-driven system with event bus, handlers, and event processing capabilities.

### Exercise 3: CQRS Implementation
Implement a CQRS system with command and query buses, handlers, and data synchronization.

### Exercise 4: Hexagonal Architecture
Create a hexagonal architecture system with ports, adapters, and domain services.

### Exercise 5: System Design
Design a scalable system architecture for a specific business domain using appropriate patterns.

## 12. Further Reading

- "Building Microservices" by Sam Newman
- "Microservices Patterns" by Chris Richardson
- "Event-Driven Architecture" by Hugh Taylor
- "CQRS and Event Sourcing" by Greg Young
- "Hexagonal Architecture" by Alistair Cockburn
- "Domain-Driven Design" by Eric Evans
- "Clean Architecture" by Robert C. Martin
- "System Design Interview" by Alex Xu
