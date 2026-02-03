# Week 16, Lesson 2: Advanced Software Architecture

## 1. Learning Objectives

- Understand advanced software architecture patterns and their applications.
- Explore microservices architecture and service-oriented design.
- Learn event-driven architecture and asynchronous communication.
- Understand CQRS (Command Query Responsibility Segregation) pattern.
- Explore hexagonal architecture (ports and adapters).
- Learn system design patterns for scalability and reliability.
- Understand the principles of modern software architecture.
- Learn to design systems for maintainability and evolution.

## 2. Prerequisites

- Understanding of object-oriented programming principles
- Knowledge of design patterns and software architecture
- Familiarity with concurrent programming concepts
- Understanding of distributed systems concepts
- Knowledge of modern C++ features (C++17/20)

## 3. Architecture Patterns Overview

### 3.1 Microservices Architecture

Microservices architecture is an architectural style that structures an application as a collection of loosely coupled services.

**Key Characteristics:**
- Services are independently deployable
- Services communicate over well-defined APIs
- Each service has its own database
- Services are organized around business capabilities

**Benefits:**
- Scalability
- Technology diversity
- Fault isolation
- Team autonomy

**Challenges:**
- Complexity
- Data consistency
- Network latency
- Service discovery

### 3.2 Event-Driven Architecture

Event-driven architecture is a software architecture pattern that promotes the production, detection, consumption of, and reaction to events.

**Key Components:**
- Event producers
- Event consumers
- Event bus/message broker
- Event store

**Benefits:**
- Loose coupling
- Scalability
- Flexibility
- Real-time processing

**Challenges:**
- Eventual consistency
- Debugging complexity
- Event ordering
- Error handling

### 3.3 CQRS (Command Query Responsibility Segregation)

CQRS is a pattern that separates read and write operations for a data store.

**Key Concepts:**
- Command side: handles write operations
- Query side: handles read operations
- Event sourcing: storing events instead of state
- Separate models for commands and queries

**Benefits:**
- Performance optimization
- Scalability
- Complexity isolation
- Technology diversity

**Challenges:**
- Complexity
- Data synchronization
- Learning curve
- Eventual consistency

## 4. Microservices Architecture Implementation

### 4.1 Service Interface Design

```cpp
// Service Interface
class Service {
public:
    virtual ~Service() = default;
    virtual std::string process_request(const std::string& request) = 0;
    virtual std::string get_service_name() const = 0;
};
```

### 4.2 Service Registry

```cpp
class ServiceRegistry {
private:
    std::unordered_map<std::string, std::shared_ptr<Service>> services_;
    std::mutex mutex_;
    
public:
    void register_service(std::shared_ptr<Service> service);
    std::shared_ptr<Service> get_service(const std::string& service_name);
    std::vector<std::string> list_services();
};
```

### 4.3 API Gateway

```cpp
class APIGateway {
private:
    ServiceRegistry& registry_;
    
public:
    APIGateway(ServiceRegistry& registry) : registry_(registry) {}
    
    std::string route_request(const std::string& service_name, 
                             const std::string& request);
};
```

### 4.4 Service Implementation

```cpp
class UserService : public Service {
private:
    std::unordered_map<std::string, std::string> users_;
    
public:
    std::string process_request(const std::string& request) override;
    std::string get_service_name() const override;
};
```

## 5. Event-Driven Architecture Implementation

### 5.1 Event Base Class

```cpp
class Event {
public:
    virtual ~Event() = default;
    virtual std::string get_type() const = 0;
    virtual std::string get_data() const = 0;
};
```

### 5.2 Event Handler Interface

```cpp
class EventHandler {
public:
    virtual ~EventHandler() = default;
    virtual void handle_event(std::shared_ptr<Event> event) = 0;
    virtual std::string get_handler_name() const = 0;
};
```

### 5.3 Event Bus

```cpp
class EventBus {
private:
    std::unordered_map<std::string, std::vector<std::shared_ptr<EventHandler>>> handlers_;
    std::queue<std::shared_ptr<Event>> event_queue_;
    std::mutex queue_mutex_;
    std::condition_variable cv_;
    std::atomic<bool> running_{true};
    std::thread worker_thread_;
    
public:
    void subscribe(const std::string& event_type, std::shared_ptr<EventHandler> handler);
    void publish(std::shared_ptr<Event> event);
};
```

### 5.4 Specific Events

```cpp
class UserCreatedEvent : public Event {
private:
    std::string user_id_;
    std::string user_name_;
    
public:
    UserCreatedEvent(const std::string& user_id, const std::string& user_name);
    std::string get_type() const override;
    std::string get_data() const override;
};
```

## 6. CQRS Implementation

### 6.1 Command and Query Interfaces

```cpp
class Command {
public:
    virtual ~Command() = default;
    virtual std::string get_type() const = 0;
};

class Query {
public:
    virtual ~Query() = default;
    virtual std::string get_type() const = 0;
};
```

### 6.2 Command and Query Handlers

```cpp
class CommandHandler {
public:
    virtual ~CommandHandler() = default;
    virtual void handle_command(std::shared_ptr<Command> command) = 0;
    virtual std::string get_command_type() const = 0;
};

class QueryHandler {
public:
    virtual ~QueryHandler() = default;
    virtual std::string handle_query(std::shared_ptr<Query> query) = 0;
    virtual std::string get_query_type() const = 0;
};
```

### 6.3 Command and Query Buses

```cpp
class CommandBus {
private:
    std::unordered_map<std::string, std::shared_ptr<CommandHandler>> handlers_;
    
public:
    void register_handler(std::shared_ptr<CommandHandler> handler);
    void send_command(std::shared_ptr<Command> command);
};

class QueryBus {
private:
    std::unordered_map<std::string, std::shared_ptr<QueryHandler>> handlers_;
    
public:
    void register_handler(std::shared_ptr<QueryHandler> handler);
    std::string send_query(std::shared_ptr<Query> query);
};
```

## 7. Hexagonal Architecture Implementation

### 7.1 Domain Layer

```cpp
// Domain Entity
class User {
private:
    std::string id_;
    std::string name_;
    std::string email_;
    
public:
    User(const std::string& id, const std::string& name, const std::string& email);
    const std::string& get_id() const;
    const std::string& get_name() const;
    const std::string& get_email() const;
    void update_name(const std::string& new_name);
};

// Port Interfaces
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
    virtual void send_email(const std::string& to, const std::string& subject, 
                           const std::string& body) = 0;
};
```

### 7.2 Application Layer

```cpp
class UserApplicationService {
private:
    std::shared_ptr<UserRepository> user_repository_;
    std::shared_ptr<EmailService> email_service_;
    
public:
    UserApplicationService(std::shared_ptr<UserRepository> user_repo, 
                          std::shared_ptr<EmailService> email_svc);
    
    std::shared_ptr<User> create_user(const std::string& id, const std::string& name, 
                                     const std::string& email);
    std::shared_ptr<User> get_user(const std::string& id);
    void update_user_name(const std::string& id, const std::string& new_name);
    std::vector<std::shared_ptr<User>> list_users();
};
```

### 7.3 Infrastructure Layer (Adapters)

```cpp
class InMemoryUserRepository : public UserRepository {
private:
    std::unordered_map<std::string, std::shared_ptr<User>> users_;
    
public:
    std::shared_ptr<User> find_by_id(const std::string& id) override;
    std::vector<std::shared_ptr<User>> find_all() override;
    void save(std::shared_ptr<User> user) override;
    void delete_by_id(const std::string& id) override;
};

class ConsoleEmailService : public EmailService {
public:
    void send_email(const std::string& to, const std::string& subject, 
                   const std::string& body) override;
};
```

### 7.4 Primary Adapter

```cpp
class UserController {
private:
    UserApplicationService& user_service_;
    
public:
    UserController(UserApplicationService& user_service) : user_service_(user_service) {}
    
    void handle_create_user(const std::string& id, const std::string& name, 
                           const std::string& email);
    void handle_get_user(const std::string& id);
    void handle_update_user(const std::string& id, const std::string& new_name);
};
```

## 8. System Design Patterns

### 8.1 Load Balancer

```cpp
class LoadBalancer {
private:
    std::vector<std::string> servers_;
    std::atomic<int> current_server_{0};
    
public:
    void add_server(const std::string& server);
    std::string get_server();
    void remove_server(const std::string& server);
    size_t server_count() const;
};
```

### 8.2 Circuit Breaker

```cpp
class CircuitBreaker {
private:
    enum class State { CLOSED, OPEN, HALF_OPEN };
    
    State state_;
    int failure_count_;
    int failure_threshold_;
    std::chrono::steady_clock::time_point last_failure_time_;
    std::chrono::milliseconds timeout_;
    
public:
    CircuitBreaker(int threshold = 5, std::chrono::milliseconds timeout = std::chrono::milliseconds(1000));
    
    bool can_execute();
    void record_success();
    void record_failure();
    std::string get_state() const;
};
```

### 8.3 TTL Cache

```cpp
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
    TTLCache(std::chrono::milliseconds ttl = std::chrono::milliseconds(5000));
    
    void put(const K& key, const V& value);
    std::optional<V> get(const K& key);
    void remove(const K& key);
    void clear();
    size_t size() const;
};
```

## 9. Architecture Principles

### 9.1 Separation of Concerns

- **Domain Layer**: Contains business logic and entities
- **Application Layer**: Contains use cases and application services
- **Infrastructure Layer**: Contains technical implementations
- **Interface Layer**: Contains user interfaces and external APIs

### 9.2 Dependency Inversion

- High-level modules should not depend on low-level modules
- Both should depend on abstractions
- Abstractions should not depend on details
- Details should depend on abstractions

### 9.3 Single Responsibility Principle

- Each class should have only one reason to change
- Each service should have a single, well-defined responsibility
- Each module should have a single, clear purpose

### 9.4 Open/Closed Principle

- Software entities should be open for extension
- Software entities should be closed for modification
- Use interfaces and abstractions for extensibility

## 10. Best Practices

### 10.1 Microservices Design

- **Service Boundaries**: Design services around business capabilities
- **Data Ownership**: Each service owns its data
- **Communication**: Use asynchronous communication when possible
- **Failure Handling**: Design for failure and implement circuit breakers
- **Monitoring**: Implement comprehensive logging and monitoring

### 10.2 Event-Driven Design

- **Event Design**: Design events to be immutable and self-contained
- **Event Versioning**: Plan for event schema evolution
- **Error Handling**: Implement dead letter queues for failed events
- **Ordering**: Handle event ordering requirements carefully
- **Idempotency**: Design handlers to be idempotent

### 10.3 CQRS Implementation

- **Model Separation**: Keep command and query models separate
- **Event Sourcing**: Consider event sourcing for audit and replay
- **Consistency**: Understand and plan for eventual consistency
- **Performance**: Optimize read and write models independently
- **Complexity**: Balance benefits against implementation complexity

### 10.4 Hexagonal Architecture

- **Port Definition**: Define clear interfaces for external dependencies
- **Adapter Implementation**: Implement adapters for each external system
- **Testing**: Test business logic in isolation from infrastructure
- **Dependency Injection**: Use dependency injection for loose coupling
- **Interface Segregation**: Keep interfaces focused and minimal

## 11. Common Pitfalls and Solutions

### 11.1 Microservices Pitfalls

**Problem**: Service boundaries that are too granular
**Solution**: Design services around business capabilities, not technical concerns

**Problem**: Distributed transactions and data consistency
**Solution**: Use eventual consistency and saga patterns

**Problem**: Network latency and reliability issues
**Solution**: Implement circuit breakers, retries, and timeouts

### 11.2 Event-Driven Pitfalls

**Problem**: Event ordering and consistency issues
**Solution**: Use event sourcing and careful event design

**Problem**: Debugging distributed event flows
**Solution**: Implement comprehensive logging and event tracing

**Problem**: Event schema evolution
**Solution**: Design events with versioning and backward compatibility

### 11.3 CQRS Pitfalls

**Problem**: Data synchronization complexity
**Solution**: Use event sourcing and careful event handling

**Problem**: Query model lag
**Solution**: Implement read model projections and eventual consistency

**Problem**: Over-engineering for simple use cases
**Solution**: Use CQRS only when benefits justify the complexity

### 11.4 Hexagonal Architecture Pitfalls

**Problem**: Over-abstraction and interface proliferation
**Solution**: Keep interfaces focused and only abstract what changes

**Problem**: Complex dependency injection setup
**Solution**: Use dependency injection frameworks and factory patterns

**Problem**: Testing complexity
**Solution**: Use test doubles and mock objects for external dependencies

## 12. Advanced Topics

### 12.1 Distributed Systems Patterns

- **Saga Pattern**: Managing distributed transactions
- **CQRS with Event Sourcing**: Combining patterns for complex systems
- **API Gateway**: Centralized entry point for microservices
- **Service Mesh**: Infrastructure layer for service communication
- **Bulkhead Pattern**: Isolating critical resources

### 12.2 Scalability Patterns

- **Horizontal Scaling**: Adding more instances
- **Vertical Scaling**: Increasing resources per instance
- **Database Sharding**: Distributing data across multiple databases
- **Caching Strategies**: Implementing multi-level caching
- **CDN Integration**: Content delivery network optimization

### 12.3 Reliability Patterns

- **Circuit Breaker**: Preventing cascade failures
- **Retry Pattern**: Handling transient failures
- **Timeout Pattern**: Preventing resource exhaustion
- **Bulkhead Pattern**: Isolating critical resources
- **Health Checks**: Monitoring service health

## 13. Performance Considerations

### 13.1 Microservices Performance

- **Network Latency**: Minimize inter-service communication
- **Data Locality**: Keep related data in the same service
- **Caching**: Implement appropriate caching strategies
- **Connection Pooling**: Reuse database connections
- **Async Processing**: Use asynchronous communication when possible

### 13.2 Event-Driven Performance

- **Event Batching**: Batch events for better throughput
- **Event Partitioning**: Partition events for parallel processing
- **Backpressure**: Implement backpressure handling
- **Event Compression**: Compress large events
- **Event Filtering**: Filter events at the source

### 13.3 CQRS Performance

- **Read Model Optimization**: Optimize read models for queries
- **Write Model Optimization**: Optimize write models for commands
- **Event Store Performance**: Optimize event store operations
- **Projection Performance**: Optimize read model projections
- **Caching**: Cache frequently accessed read models

## 14. Security Considerations

### 14.1 Microservices Security

- **Authentication**: Implement service-to-service authentication
- **Authorization**: Implement fine-grained authorization
- **Network Security**: Use TLS for inter-service communication
- **API Security**: Implement API rate limiting and validation
- **Secrets Management**: Secure management of service secrets

### 14.2 Event-Driven Security

- **Event Encryption**: Encrypt sensitive event data
- **Event Authentication**: Authenticate event publishers
- **Event Authorization**: Authorize event consumers
- **Audit Logging**: Log all security-relevant events
- **Data Privacy**: Implement data privacy controls

### 14.3 CQRS Security

- **Command Validation**: Validate all commands
- **Query Authorization**: Authorize query access
- **Event Security**: Secure event store and projections
- **Data Masking**: Mask sensitive data in read models
- **Audit Trail**: Maintain comprehensive audit trails

## 15. Testing Strategies

### 15.1 Microservices Testing

- **Unit Testing**: Test individual services in isolation
- **Integration Testing**: Test service interactions
- **Contract Testing**: Test service contracts
- **End-to-End Testing**: Test complete user journeys
- **Performance Testing**: Test system performance under load

### 15.2 Event-Driven Testing

- **Event Testing**: Test event production and consumption
- **Handler Testing**: Test event handlers in isolation
- **Flow Testing**: Test complete event flows
- **Replay Testing**: Test event replay scenarios
- **Chaos Testing**: Test system behavior under failure

### 15.3 CQRS Testing

- **Command Testing**: Test command handling
- **Query Testing**: Test query handling
- **Event Testing**: Test event sourcing
- **Projection Testing**: Test read model projections
- **Consistency Testing**: Test eventual consistency

## 16. Monitoring and Observability

### 16.1 Microservices Monitoring

- **Service Health**: Monitor individual service health
- **Performance Metrics**: Track performance metrics
- **Error Rates**: Monitor error rates and types
- **Dependencies**: Monitor service dependencies
- **Business Metrics**: Track business-relevant metrics

### 16.2 Event-Driven Monitoring

- **Event Throughput**: Monitor event production and consumption
- **Event Latency**: Track event processing latency
- **Event Errors**: Monitor event processing errors
- **Event Ordering**: Monitor event ordering issues
- **Backlog Monitoring**: Monitor event processing backlogs

### 16.3 CQRS Monitoring

- **Command Performance**: Monitor command processing
- **Query Performance**: Monitor query performance
- **Event Store Performance**: Monitor event store operations
- **Projection Lag**: Monitor read model projection lag
- **Consistency Monitoring**: Monitor eventual consistency

## 17. Migration Strategies

### 17.1 Monolith to Microservices

- **Strangler Fig Pattern**: Gradually replace monolith functionality
- **Database Per Service**: Migrate to service-specific databases
- **API Gateway**: Introduce API gateway for service access
- **Event-Driven Integration**: Use events for service communication
- **Gradual Migration**: Migrate services incrementally

### 17.2 Event-Driven Migration

- **Event-First Design**: Design new features as event-driven
- **Event Bridge**: Bridge between synchronous and asynchronous systems
- **Gradual Adoption**: Adopt event-driven patterns incrementally
- **Legacy Integration**: Integrate with legacy systems via events
- **Data Synchronization**: Synchronize data between systems

### 17.3 CQRS Migration

- **Read Model Migration**: Migrate to separate read models
- **Command Migration**: Migrate to command-based operations
- **Event Sourcing**: Introduce event sourcing gradually
- **Legacy Integration**: Integrate with legacy systems
- **Data Migration**: Migrate existing data to new models

## 18. Tools and Technologies

### 18.1 Microservices Tools

- **Service Discovery**: Consul, Eureka, etcd
- **API Gateway**: Kong, Zuul, AWS API Gateway
- **Load Balancer**: NGINX, HAProxy, AWS ELB
- **Container Orchestration**: Kubernetes, Docker Swarm
- **Service Mesh**: Istio, Linkerd, Consul Connect

### 18.2 Event-Driven Tools

- **Message Brokers**: Apache Kafka, RabbitMQ, AWS SQS
- **Event Streaming**: Apache Kafka, Apache Pulsar
- **Event Sourcing**: EventStore, Apache Kafka
- **CQRS Frameworks**: Axon Framework, EventFlow
- **Monitoring**: Prometheus, Grafana, ELK Stack

### 18.3 Development Tools

- **API Documentation**: Swagger/OpenAPI, RAML
- **Testing Tools**: TestContainers, WireMock, Pact
- **Monitoring Tools**: Jaeger, Zipkin, OpenTelemetry
- **Development Frameworks**: Spring Boot, .NET Core, Node.js
- **Database Tools**: PostgreSQL, MongoDB, Redis

## 19. Future Trends

### 19.1 Architecture Evolution

- **Serverless Architecture**: Function-as-a-Service evolution
- **Edge Computing**: Distributed computing at the edge
- **AI/ML Integration**: Machine learning in architecture
- **Quantum Computing**: Preparing for quantum systems
- **Blockchain Integration**: Distributed ledger integration

### 19.2 Technology Trends

- **GraphQL**: Modern API query language
- **gRPC**: High-performance RPC framework
- **WebAssembly**: High-performance web applications
- **Cloud Native**: Cloud-first architecture
- **GitOps**: Git-based operations

### 19.3 Development Trends

- **Infrastructure as Code**: Programmable infrastructure
- **Observability**: Enhanced monitoring and debugging
- **Developer Experience**: Improved development workflows
- **Automation**: Increased automation in development
- **Collaboration**: Enhanced team collaboration tools

## 20. Summary

Advanced software architecture patterns provide powerful tools for building scalable, maintainable, and reliable systems. Key takeaways include:

1. **Microservices Architecture** enables scalable and maintainable systems through service decomposition
2. **Event-Driven Architecture** provides loose coupling and flexibility through asynchronous communication
3. **CQRS** separates command and query responsibilities for better performance and scalability
4. **Hexagonal Architecture** isolates business logic from infrastructure concerns
5. **System Design Patterns** address scalability and reliability challenges
6. **Proper architecture** enables system evolution and maintenance
7. **Architecture patterns** should be chosen based on system requirements
8. **Modern systems** require sophisticated architectural approaches

Understanding these patterns and their appropriate application is essential for building enterprise-grade software systems that can evolve and scale with changing requirements.

## 21. Exercises

### Exercise 1: Microservices Design
Design a microservices architecture for an e-commerce system with the following services:
- User Service
- Product Service
- Order Service
- Payment Service
- Notification Service

### Exercise 2: Event-Driven System
Implement an event-driven system for a library management system with events for:
- Book checked out
- Book returned
- Book overdue
- Fine calculated

### Exercise 3: CQRS Implementation
Implement a CQRS system for a blog platform with commands and queries for:
- Creating posts
- Updating posts
- Getting posts
- Listing posts

### Exercise 4: Hexagonal Architecture
Design a hexagonal architecture for a banking system with:
- Account management
- Transaction processing
- Notification services
- Audit logging

### Exercise 5: System Design Patterns
Implement system design patterns for a social media platform:
- Load balancer for API requests
- Circuit breaker for external services
- TTL cache for user sessions
- Rate limiter for API endpoints

## 22. Further Reading

- "Building Microservices" by Sam Newman
- "Microservices Patterns" by Chris Richardson
- "Event-Driven Architecture" by Hugh Beyer and Karen Holtzblatt
- "Implementing Domain-Driven Design" by Vaughn Vernon
- "Patterns of Enterprise Application Architecture" by Martin Fowler
- "Clean Architecture" by Robert C. Martin
- "Architecture Patterns with Python" by Harry Percival and Bob Gregory
