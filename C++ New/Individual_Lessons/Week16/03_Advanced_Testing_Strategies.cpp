/*
 * Lesson 16.3: Advanced Testing Strategies
 * 
 * This file demonstrates advanced testing strategies including
 * unit testing, integration testing, mocking, test-driven development,
 * and performance testing.
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

// Simple Test Framework
namespace TestFramework {
    
    class TestResult {
    private:
        std::string test_name_;
        bool passed_;
        std::string error_message_;
        std::chrono::milliseconds duration_;
        
    public:
        TestResult(const std::string& test_name, bool passed, const std::string& error_message = "", 
                  std::chrono::milliseconds duration = std::chrono::milliseconds(0))
            : test_name_(test_name), passed_(passed), error_message_(error_message), duration_(duration) {}
        
        const std::string& get_test_name() const { return test_name_; }
        bool passed() const { return passed_; }
        const std::string& get_error_message() const { return error_message_; }
        std::chrono::milliseconds get_duration() const { return duration_; }
    };
    
    class TestSuite {
    private:
        std::string suite_name_;
        std::vector<std::function<void()>> tests_;
        std::vector<TestResult> results_;
        
    public:
        TestSuite(const std::string& name) : suite_name_(name) {}
        
        void add_test(const std::string& test_name, std::function<void()> test_func) {
            tests_.push_back([this, test_name, test_func]() {
                auto start_time = std::chrono::high_resolution_clock::now();
                try {
                    test_func();
                    auto end_time = std::chrono::high_resolution_clock::now();
                    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);
                    results_.emplace_back(test_name, true, "", duration);
                } catch (const std::exception& e) {
                    auto end_time = std::chrono::high_resolution_clock::now();
                    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);
                    results_.emplace_back(test_name, false, e.what(), duration);
                } catch (...) {
                    auto end_time = std::chrono::high_resolution_clock::now();
                    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);
                    results_.emplace_back(test_name, false, "Unknown exception", duration);
                }
            });
        }
        
        void run_tests() {
            std::cout << "Running test suite: " << suite_name_ << std::endl;
            for (auto& test : tests_) {
                test();
            }
        }
        
        void print_results() {
            std::cout << "\n=== Test Results for " << suite_name_ << " ===" << std::endl;
            int passed = 0;
            int failed = 0;
            
            for (const auto& result : results_) {
                if (result.passed()) {
                    std::cout << "✓ " << result.get_test_name() 
                              << " (" << result.get_duration().count() << "ms)" << std::endl;
                    passed++;
                } else {
                    std::cout << "✗ " << result.get_test_name() 
                              << " - " << result.get_error_message() << std::endl;
                    failed++;
                }
            }
            
            std::cout << "\nSummary: " << passed << " passed, " << failed << " failed" << std::endl;
        }
        
        const std::vector<TestResult>& get_results() const {
            return results_;
        }
    };
    
    // Assertion macros
    #define ASSERT_TRUE(condition) \
        if (!(condition)) { \
            throw std::runtime_error("Assertion failed: " #condition); \
        }
    
    #define ASSERT_FALSE(condition) \
        if (condition) { \
            throw std::runtime_error("Assertion failed: !" #condition); \
        }
    
    #define ASSERT_EQUAL(expected, actual) \
        if ((expected) != (actual)) { \
            throw std::runtime_error("Assertion failed: " #expected " != " #actual); \
        }
    
    #define ASSERT_NOT_EQUAL(expected, actual) \
        if ((expected) == (actual)) { \
            throw std::runtime_error("Assertion failed: " #expected " == " #actual); \
        }
    
    #define ASSERT_THROWS(expression, exception_type) \
        try { \
            expression; \
            throw std::runtime_error("Expected exception not thrown"); \
        } catch (const exception_type&) { \
            /* Expected exception caught */ \
        }
}

// Example 1: Unit Testing
namespace UnitTesting {
    
    // Simple Calculator class for testing
    class Calculator {
    public:
        double add(double a, double b) {
            return a + b;
        }
        
        double subtract(double a, double b) {
            return a - b;
        }
        
        double multiply(double a, double b) {
            return a * b;
        }
        
        double divide(double a, double b) {
            if (b == 0) {
                throw std::invalid_argument("Division by zero");
            }
            return a / b;
        }
        
        double power(double base, double exponent) {
            if (base == 0 && exponent < 0) {
                throw std::invalid_argument("Zero to negative power");
            }
            return std::pow(base, exponent);
        }
    };
    
    // User Service for testing
    class UserService {
    private:
        std::unordered_map<std::string, std::string> users_;
        
    public:
        void add_user(const std::string& id, const std::string& name) {
            if (id.empty() || name.empty()) {
                throw std::invalid_argument("ID and name cannot be empty");
            }
            users_[id] = name;
        }
        
        std::string get_user(const std::string& id) {
            auto it = users_.find(id);
            if (it == users_.end()) {
                throw std::runtime_error("User not found");
            }
            return it->second;
        }
        
        void remove_user(const std::string& id) {
            users_.erase(id);
        }
        
        bool user_exists(const std::string& id) {
            return users_.find(id) != users_.end();
        }
        
        size_t user_count() const {
            return users_.size();
        }
    };
    
    void demonstrateUnitTesting() {
        std::cout << "=== Unit Testing Demonstration ===" << std::endl;
        
        TestFramework::TestSuite calculator_tests("Calculator Tests");
        
        // Calculator tests
        calculator_tests.add_test("Add Positive Numbers", []() {
            Calculator calc;
            TestFramework::ASSERT_EQUAL(5.0, calc.add(2.0, 3.0));
        });
        
        calculator_tests.add_test("Add Negative Numbers", []() {
            Calculator calc;
            TestFramework::ASSERT_EQUAL(-1.0, calc.add(-3.0, 2.0));
        });
        
        calculator_tests.add_test("Subtract Numbers", []() {
            Calculator calc;
            TestFramework::ASSERT_EQUAL(2.0, calc.subtract(5.0, 3.0));
        });
        
        calculator_tests.add_test("Multiply Numbers", []() {
            Calculator calc;
            TestFramework::ASSERT_EQUAL(15.0, calc.multiply(3.0, 5.0));
        });
        
        calculator_tests.add_test("Divide Numbers", []() {
            Calculator calc;
            TestFramework::ASSERT_EQUAL(2.5, calc.divide(5.0, 2.0));
        });
        
        calculator_tests.add_test("Divide by Zero Throws", []() {
            Calculator calc;
            TestFramework::ASSERT_THROWS(calc.divide(5.0, 0.0), std::invalid_argument);
        });
        
        calculator_tests.add_test("Power Calculation", []() {
            Calculator calc;
            TestFramework::ASSERT_EQUAL(8.0, calc.power(2.0, 3.0));
        });
        
        calculator_tests.run_tests();
        calculator_tests.print_results();
        
        // User Service tests
        TestFramework::TestSuite user_service_tests("User Service Tests");
        
        user_service_tests.add_test("Add User", []() {
            UserService service;
            service.add_user("user1", "John Doe");
            TestFramework::ASSERT_TRUE(service.user_exists("user1"));
            TestFramework::ASSERT_EQUAL(std::string("John Doe"), service.get_user("user1"));
        });
        
        user_service_tests.add_test("Add Empty User Throws", []() {
            UserService service;
            TestFramework::ASSERT_THROWS(service.add_user("", "John"), std::invalid_argument);
            TestFramework::ASSERT_THROWS(service.add_user("user1", ""), std::invalid_argument);
        });
        
        user_service_tests.add_test("Get Non-existent User Throws", []() {
            UserService service;
            TestFramework::ASSERT_THROWS(service.get_user("nonexistent"), std::runtime_error);
        });
        
        user_service_tests.add_test("Remove User", []() {
            UserService service;
            service.add_user("user1", "John Doe");
            TestFramework::ASSERT_TRUE(service.user_exists("user1"));
            
            service.remove_user("user1");
            TestFramework::ASSERT_FALSE(service.user_exists("user1"));
        });
        
        user_service_tests.add_test("User Count", []() {
            UserService service;
            TestFramework::ASSERT_EQUAL(0, service.user_count());
            
            service.add_user("user1", "John Doe");
            service.add_user("user2", "Jane Smith");
            TestFramework::ASSERT_EQUAL(2, service.user_count());
        });
        
        user_service_tests.run_tests();
        user_service_tests.print_results();
    }
}

// Example 2: Mock Objects
namespace MockTesting {
    
    // Interface for external service
    class EmailService {
    public:
        virtual ~EmailService() = default;
        virtual bool send_email(const std::string& to, const std::string& subject, const std::string& body) = 0;
        virtual int get_sent_count() const = 0;
    };
    
    // Mock implementation
    class MockEmailService : public EmailService {
    private:
        std::vector<std::tuple<std::string, std::string, std::string>> sent_emails_;
        bool should_fail_;
        
    public:
        MockEmailService(bool should_fail = false) : should_fail_(should_fail) {}
        
        bool send_email(const std::string& to, const std::string& subject, const std::string& body) override {
            if (should_fail_) {
                return false;
            }
            
            sent_emails_.emplace_back(to, subject, body);
            return true;
        }
        
        int get_sent_count() const override {
            return sent_emails_.size();
        }
        
        const std::vector<std::tuple<std::string, std::string, std::string>>& get_sent_emails() const {
            return sent_emails_;
        }
        
        void set_should_fail(bool should_fail) {
            should_fail_ = should_fail;
        }
        
        void reset() {
            sent_emails_.clear();
            should_fail_ = false;
        }
    };
    
    // Real implementation
    class RealEmailService : public EmailService {
    public:
        bool send_email(const std::string& to, const std::string& subject, const std::string& body) override {
            // In real implementation, this would send actual emails
            std::cout << "Real email sent to: " << to << " - " << subject << std::endl;
            return true;
        }
        
        int get_sent_count() const override {
            // In real implementation, this would track actual sent emails
            return 0;
        }
    };
    
    // Notification Service that depends on EmailService
    class NotificationService {
    private:
        std::shared_ptr<EmailService> email_service_;
        
    public:
        NotificationService(std::shared_ptr<EmailService> email_service) 
            : email_service_(email_service) {}
        
        bool send_welcome_email(const std::string& user_email, const std::string& user_name) {
            std::string subject = "Welcome to our service!";
            std::string body = "Hello " + user_name + ", welcome to our service!";
            
            return email_service_->send_email(user_email, subject, body);
        }
        
        bool send_password_reset_email(const std::string& user_email) {
            std::string subject = "Password Reset";
            std::string body = "Please click the link to reset your password.";
            
            return email_service_->send_email(user_email, subject, body);
        }
        
        bool send_notification_email(const std::string& user_email, const std::string& message) {
            std::string subject = "Notification";
            std::string body = message;
            
            return email_service_->send_email(user_email, subject, body);
        }
    };
    
    void demonstrateMockTesting() {
        std::cout << "\n=== Mock Testing Demonstration ===" << std::endl;
        
        TestFramework::TestSuite mock_tests("Mock Testing");
        
        mock_tests.add_test("Send Welcome Email Success", []() {
            auto mock_email_service = std::make_shared<MockEmailService>();
            NotificationService notification_service(mock_email_service);
            
            bool result = notification_service.send_welcome_email("user@example.com", "John Doe");
            
            TestFramework::ASSERT_TRUE(result);
            TestFramework::ASSERT_EQUAL(1, mock_email_service->get_sent_count());
            
            const auto& sent_emails = mock_email_service->get_sent_emails();
            TestFramework::ASSERT_EQUAL(std::string("user@example.com"), std::get<0>(sent_emails[0]));
            TestFramework::ASSERT_EQUAL(std::string("Welcome to our service!"), std::get<1>(sent_emails[0]));
        });
        
        mock_tests.add_test("Send Welcome Email Failure", []() {
            auto mock_email_service = std::make_shared<MockEmailService>(true);
            NotificationService notification_service(mock_email_service);
            
            bool result = notification_service.send_welcome_email("user@example.com", "John Doe");
            
            TestFramework::ASSERT_FALSE(result);
            TestFramework::ASSERT_EQUAL(0, mock_email_service->get_sent_count());
        });
        
        mock_tests.add_test("Send Multiple Emails", []() {
            auto mock_email_service = std::make_shared<MockEmailService>();
            NotificationService notification_service(mock_email_service);
            
            notification_service.send_welcome_email("user1@example.com", "John Doe");
            notification_service.send_password_reset_email("user2@example.com");
            notification_service.send_notification_email("user3@example.com", "Test message");
            
            TestFramework::ASSERT_EQUAL(3, mock_email_service->get_sent_count());
        });
        
        mock_tests.add_test("Mock Reset", []() {
            auto mock_email_service = std::make_shared<MockEmailService>();
            NotificationService notification_service(mock_email_service);
            
            notification_service.send_welcome_email("user@example.com", "John Doe");
            TestFramework::ASSERT_EQUAL(1, mock_email_service->get_sent_count());
            
            mock_email_service->reset();
            TestFramework::ASSERT_EQUAL(0, mock_email_service->get_sent_count());
        });
        
        mock_tests.run_tests();
        mock_tests.print_results();
    }
}

// Example 3: Integration Testing
namespace IntegrationTesting {
    
    // Database interface
    class Database {
    public:
        virtual ~Database() = default;
        virtual bool connect() = 0;
        virtual void disconnect() = 0;
        virtual bool execute_query(const std::string& query) = 0;
        virtual std::vector<std::map<std::string, std::string>> select(const std::string& query) = 0;
        virtual bool is_connected() const = 0;
    };
    
    // Mock database for testing
    class MockDatabase : public Database {
    private:
        bool connected_;
        std::vector<std::map<std::string, std::string>> data_;
        
    public:
        MockDatabase() : connected_(false) {
            // Initialize with some test data
            std::map<std::string, std::string> user1;
            user1["id"] = "1";
            user1["name"] = "John Doe";
            user1["email"] = "john@example.com";
            data_.push_back(user1);
            
            std::map<std::string, std::string> user2;
            user2["id"] = "2";
            user2["name"] = "Jane Smith";
            user2["email"] = "jane@example.com";
            data_.push_back(user2);
        }
        
        bool connect() override {
            connected_ = true;
            return true;
        }
        
        void disconnect() override {
            connected_ = false;
        }
        
        bool execute_query(const std::string& query) override {
            if (!connected_) {
                return false;
            }
            
            // Simulate query execution
            if (query.find("INSERT") != std::string::npos) {
                // Simulate insert
                return true;
            } else if (query.find("UPDATE") != std::string::npos) {
                // Simulate update
                return true;
            } else if (query.find("DELETE") != std::string::npos) {
                // Simulate delete
                return true;
            }
            
            return true;
        }
        
        std::vector<std::map<std::string, std::string>> select(const std::string& query) override {
            if (!connected_) {
                return {};
            }
            
            // Return mock data for SELECT queries
            if (query.find("SELECT") != std::string::npos) {
                return data_;
            }
            
            return {};
        }
        
        bool is_connected() const override {
            return connected_;
        }
    };
    
    // User Repository
    class UserRepository {
    private:
        std::shared_ptr<Database> database_;
        
    public:
        UserRepository(std::shared_ptr<Database> db) : database_(db) {}
        
        bool create_user(const std::string& name, const std::string& email) {
            if (!database_->is_connected()) {
                return false;
            }
            
            std::string query = "INSERT INTO users (name, email) VALUES ('" + name + "', '" + email + "')";
            return database_->execute_query(query);
        }
        
        std::vector<std::map<std::string, std::string>> get_all_users() {
            if (!database_->is_connected()) {
                return {};
            }
            
            std::string query = "SELECT * FROM users";
            return database_->select(query);
        }
        
        std::map<std::string, std::string> get_user_by_id(const std::string& id) {
            if (!database_->is_connected()) {
                return {};
            }
            
            std::string query = "SELECT * FROM users WHERE id = " + id;
            auto results = database_->select(query);
            
            if (!results.empty()) {
                return results[0];
            }
            
            return {};
        }
        
        bool update_user(const std::string& id, const std::string& name, const std::string& email) {
            if (!database_->is_connected()) {
                return false;
            }
            
            std::string query = "UPDATE users SET name = '" + name + "', email = '" + email + "' WHERE id = " + id;
            return database_->execute_query(query);
        }
        
        bool delete_user(const std::string& id) {
            if (!database_->is_connected()) {
                return false;
            }
            
            std::string query = "DELETE FROM users WHERE id = " + id;
            return database_->execute_query(query);
        }
    };
    
    // User Service that uses UserRepository
    class UserService {
    private:
        std::shared_ptr<UserRepository> user_repository_;
        
    public:
        UserService(std::shared_ptr<UserRepository> repo) : user_repository_(repo) {}
        
        bool register_user(const std::string& name, const std::string& email) {
            // Business logic validation
            if (name.empty() || email.empty()) {
                return false;
            }
            
            if (email.find('@') == std::string::npos) {
                return false;
            }
            
            return user_repository_->create_user(name, email);
        }
        
        std::vector<std::map<std::string, std::string>> get_all_users() {
            return user_repository_->get_all_users();
        }
        
        std::map<std::string, std::string> get_user(const std::string& id) {
            return user_repository_->get_user_by_id(id);
        }
        
        bool update_user_profile(const std::string& id, const std::string& name, const std::string& email) {
            // Business logic validation
            if (name.empty() || email.empty()) {
                return false;
            }
            
            if (email.find('@') == std::string::npos) {
                return false;
            }
            
            return user_repository_->update_user(id, name, email);
        }
    };
    
    void demonstrateIntegrationTesting() {
        std::cout << "\n=== Integration Testing Demonstration ===" << std::endl;
        
        TestFramework::TestSuite integration_tests("Integration Tests");
        
        integration_tests.add_test("User Registration Flow", []() {
            auto database = std::make_shared<MockDatabase>();
            auto user_repository = std::make_shared<UserRepository>(database);
            UserService user_service(user_repository);
            
            // Connect to database
            TestFramework::ASSERT_TRUE(database->connect());
            
            // Register user
            bool result = user_service.register_user("Test User", "test@example.com");
            TestFramework::ASSERT_TRUE(result);
            
            // Verify user was created
            auto users = user_service.get_all_users();
            TestFramework::ASSERT_TRUE(users.size() >= 1);
            
            database->disconnect();
        });
        
        integration_tests.add_test("User Registration with Invalid Data", []() {
            auto database = std::make_shared<MockDatabase>();
            auto user_repository = std::make_shared<UserRepository>(database);
            UserService user_service(user_repository);
            
            TestFramework::ASSERT_TRUE(database->connect());
            
            // Try to register with empty name
            bool result1 = user_service.register_user("", "test@example.com");
            TestFramework::ASSERT_FALSE(result1);
            
            // Try to register with invalid email
            bool result2 = user_service.register_user("Test User", "invalid-email");
            TestFramework::ASSERT_FALSE(result2);
            
            database->disconnect();
        });
        
        integration_tests.add_test("Database Connection Handling", []() {
            auto database = std::make_shared<MockDatabase>();
            auto user_repository = std::make_shared<UserRepository>(database);
            UserService user_service(user_repository);
            
            // Try to register without connecting
            bool result = user_service.register_user("Test User", "test@example.com");
            TestFramework::ASSERT_FALSE(result);
            
            // Connect and try again
            TestFramework::ASSERT_TRUE(database->connect());
            result = user_service.register_user("Test User", "test@example.com");
            TestFramework::ASSERT_TRUE(result);
        });
        
        integration_tests.add_test("User Profile Update", []() {
            auto database = std::make_shared<MockDatabase>();
            auto user_repository = std::make_shared<UserRepository>(database);
            UserService user_service(user_repository);
            
            TestFramework::ASSERT_TRUE(database->connect());
            
            // Update user profile
            bool result = user_service.update_user_profile("1", "Updated Name", "updated@example.com");
            TestFramework::ASSERT_TRUE(result);
            
            // Verify update
            auto user = user_service.get_user("1");
            TestFramework::ASSERT_FALSE(user.empty());
            
            database->disconnect();
        });
        
        integration_tests.run_tests();
        integration_tests.print_results();
    }
}

// Example 4: Performance Testing
namespace PerformanceTesting {
    
    class PerformanceTestSuite {
    private:
        std::string suite_name_;
        std::vector<std::function<void()>> tests_;
        std::vector<std::pair<std::string, std::chrono::milliseconds>> results_;
        
    public:
        PerformanceTestSuite(const std::string& name) : suite_name_(name) {}
        
        void add_test(const std::string& test_name, std::function<void()> test_func) {
            tests_.push_back([this, test_name, test_func]() {
                auto start_time = std::chrono::high_resolution_clock::now();
                test_func();
                auto end_time = std::chrono::high_resolution_clock::now();
                auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);
                results_.emplace_back(test_name, duration);
            });
        }
        
        void run_tests() {
            std::cout << "Running performance tests: " << suite_name_ << std::endl;
            for (auto& test : tests_) {
                test();
            }
        }
        
        void print_results() {
            std::cout << "\n=== Performance Results for " << suite_name_ << " ===" << std::endl;
            
            std::chrono::milliseconds total_time(0);
            std::chrono::milliseconds min_time(std::chrono::milliseconds::max());
            std::chrono::milliseconds max_time(0);
            
            for (const auto& result : results_) {
                std::cout << result.first << ": " << result.second.count() << "ms" << std::endl;
                total_time += result.second;
                min_time = std::min(min_time, result.second);
                max_time = std::max(max_time, result.second);
            }
            
            std::cout << "\nSummary:" << std::endl;
            std::cout << "Total time: " << total_time.count() << "ms" << std::endl;
            std::cout << "Min time: " << min_time.count() << "ms" << std::endl;
            std::cout << "Max time: " << max_time.count() << "ms" << std::endl;
            std::cout << "Average time: " << total_time.count() / results_.size() << "ms" << std::endl;
        }
    };
    
    // Performance test examples
    class DataProcessor {
    public:
        std::vector<int> process_large_dataset(int size) {
            std::vector<int> data;
            data.reserve(size);
            
            for (int i = 0; i < size; ++i) {
                data.push_back(i * i);
            }
            
            // Simulate some processing
            std::sort(data.begin(), data.end());
            
            return data;
        }
        
        std::vector<std::string> process_strings(const std::vector<std::string>& input) {
            std::vector<std::string> result;
            result.reserve(input.size());
            
            for (const auto& str : input) {
                std::string processed = str;
                std::transform(processed.begin(), processed.end(), processed.begin(), ::toupper);
                result.push_back(processed);
            }
            
            return result;
        }
        
        int fibonacci(int n) {
            if (n <= 1) return n;
            
            int a = 0, b = 1;
            for (int i = 2; i <= n; ++i) {
                int temp = a + b;
                a = b;
                b = temp;
            }
            
            return b;
        }
    };
    
    void demonstratePerformanceTesting() {
        std::cout << "\n=== Performance Testing Demonstration ===" << std::endl;
        
        PerformanceTesting::PerformanceTestSuite perf_tests("Performance Tests");
        
        perf_tests.add_test("Process Small Dataset", []() {
            DataProcessor processor;
            auto result = processor.process_large_dataset(1000);
            TestFramework::ASSERT_EQUAL(1000, static_cast<int>(result.size()));
        });
        
        perf_tests.add_test("Process Medium Dataset", []() {
            DataProcessor processor;
            auto result = processor.process_large_dataset(10000);
            TestFramework::ASSERT_EQUAL(10000, static_cast<int>(result.size()));
        });
        
        perf_tests.add_test("Process Large Dataset", []() {
            DataProcessor processor;
            auto result = processor.process_large_dataset(100000);
            TestFramework::ASSERT_EQUAL(100000, static_cast<int>(result.size()));
        });
        
        perf_tests.add_test("Process String Collection", []() {
            DataProcessor processor;
            std::vector<std::string> input;
            for (int i = 0; i < 1000; ++i) {
                input.push_back("test_string_" + std::to_string(i));
            }
            
            auto result = processor.process_strings(input);
            TestFramework::ASSERT_EQUAL(1000, static_cast<int>(result.size()));
        });
        
        perf_tests.add_test("Calculate Fibonacci", []() {
            DataProcessor processor;
            int result = processor.fibonacci(30);
            TestFramework::ASSERT_EQUAL(832040, result);
        });
        
        perf_tests.run_tests();
        perf_tests.print_results();
    }
}

// Example 5: Test-Driven Development (TDD) Example
namespace TestDrivenDevelopment {
    
    // TDD Example: String Calculator
    class StringCalculator {
    public:
        int add(const std::string& numbers) {
            if (numbers.empty()) {
                return 0;
            }
            
            // Handle single number
            if (numbers.find(',') == std::string::npos && numbers.find('\n') == std::string::npos) {
                return std::stoi(numbers);
            }
            
            // Handle multiple numbers
            std::vector<std::string> tokens;
            std::string current_token;
            
            for (char c : numbers) {
                if (c == ',' || c == '\n') {
                    if (!current_token.empty()) {
                        tokens.push_back(current_token);
                        current_token.clear();
                    }
                } else {
                    current_token += c;
                }
            }
            
            if (!current_token.empty()) {
                tokens.push_back(current_token);
            }
            
            int sum = 0;
            for (const auto& token : tokens) {
                int num = std::stoi(token);
                if (num < 0) {
                    throw std::invalid_argument("Negative numbers not allowed: " + token);
                }
                sum += num;
            }
            
            return sum;
        }
    };
    
    void demonstrateTestDrivenDevelopment() {
        std::cout << "\n=== Test-Driven Development Demonstration ===" << std::endl;
        
        TestFramework::TestSuite tdd_tests("TDD String Calculator Tests");
        
        // Test 1: Empty string should return 0
        tdd_tests.add_test("Empty String Returns Zero", []() {
            StringCalculator calculator;
            TestFramework::ASSERT_EQUAL(0, calculator.add(""));
        });
        
        // Test 2: Single number should return that number
        tdd_tests.add_test("Single Number Returns That Number", []() {
            StringCalculator calculator;
            TestFramework::ASSERT_EQUAL(5, calculator.add("5"));
            TestFramework::ASSERT_EQUAL(10, calculator.add("10"));
        });
        
        // Test 3: Two numbers separated by comma should return sum
        tdd_tests.add_test("Two Numbers Separated by Comma", []() {
            StringCalculator calculator;
            TestFramework::ASSERT_EQUAL(8, calculator.add("3,5"));
            TestFramework::ASSERT_EQUAL(15, calculator.add("7,8"));
        });
        
        // Test 4: Multiple numbers separated by comma should return sum
        tdd_tests.add_test("Multiple Numbers Separated by Comma", []() {
            StringCalculator calculator;
            TestFramework::ASSERT_EQUAL(15, calculator.add("3,5,7"));
            TestFramework::ASSERT_EQUAL(20, calculator.add("1,2,3,4,10"));
        });
        
        // Test 5: Numbers separated by newline should return sum
        tdd_tests.add_test("Numbers Separated by Newline", []() {
            StringCalculator calculator;
            TestFramework::ASSERT_EQUAL(8, calculator.add("3\n5"));
            TestFramework::ASSERT_EQUAL(15, calculator.add("3\n5\n7"));
        });
        
        // Test 6: Numbers separated by comma and newline should return sum
        tdd_tests.add_test("Numbers Separated by Comma and Newline", []() {
            StringCalculator calculator;
            TestFramework::ASSERT_EQUAL(15, calculator.add("3,5\n7"));
            TestFramework::ASSERT_EQUAL(20, calculator.add("1,2\n3,4\n10"));
        });
        
        // Test 7: Negative numbers should throw exception
        tdd_tests.add_test("Negative Numbers Throw Exception", []() {
            StringCalculator calculator;
            TestFramework::ASSERT_THROWS(calculator.add("-1"), std::invalid_argument);
            TestFramework::ASSERT_THROWS(calculator.add("1,-2"), std::invalid_argument);
            TestFramework::ASSERT_THROWS(calculator.add("1,-2,3"), std::invalid_argument);
        });
        
        tdd_tests.run_tests();
        tdd_tests.print_results();
    }
}

int main() {
    std::cout << "=== Advanced Testing Strategies Demonstration ===" << std::endl;
    std::cout << "This program demonstrates advanced testing strategies including\n"
              << "unit testing, integration testing, mocking, performance testing,\n"
              << "and test-driven development.\n" << std::endl;
    
    // Demonstrate various testing strategies
    UnitTesting::demonstrateUnitTesting();
    MockTesting::demonstrateMockTesting();
    IntegrationTesting::demonstrateIntegrationTesting();
    PerformanceTesting::demonstratePerformanceTesting();
    TestDrivenDevelopment::demonstrateTestDrivenDevelopment();
    
    std::cout << "\n=== Key Takeaways ===" << std::endl;
    std::cout << "1. Unit testing validates individual components in isolation" << std::endl;
    std::cout << "2. Mock objects enable testing of dependencies and external services" << std::endl;
    std::cout << "3. Integration testing validates component interactions" << std::endl;
    std::cout << "4. Performance testing ensures system meets performance requirements" << std::endl;
    std::cout << "5. Test-driven development improves code quality and design" << std::endl;
    std::cout << "6. Comprehensive testing strategies ensure software reliability" << std::endl;
    std::cout << "7. Testing frameworks and tools improve testing efficiency" << std::endl;
    std::cout << "8. Automated testing enables continuous integration and deployment" << std::endl;
    
    std::cout << "\nProgram completed successfully!" << std::endl;
    return 0;
}

/*
 * Compilation Instructions:
 * 
 * Using GCC:
 * g++ -std=c++17 -Wall -Wextra -O2 -pthread -o advanced_testing_strategies 03_Advanced_Testing_Strategies.cpp
 * 
 * Using Clang:
 * clang++ -std=c++17 -Wall -Wextra -O2 -pthread -o advanced_testing_strategies 03_Advanced_Testing_Strategies.cpp
 * 
 * Using MSVC (Visual Studio):
 * cl /std:c++17 /EHsc /O2 03_Advanced_Testing_Strategies.cpp
 * 
 * Running:
 * ./advanced_testing_strategies (Linux/macOS)
 * advanced_testing_strategies.exe (Windows)
 * 
 * Note: This lesson requires C++17 or later for some features.
 * C++20 is recommended for best testing support.
 * 
 * Advanced Testing Strategies Notes:
 * - Unit testing validates individual components in isolation
 * - Mock objects enable testing of dependencies and external services
 * - Integration testing validates component interactions
 * - Performance testing ensures system meets performance requirements
 * - Test-driven development improves code quality and design
 * - Comprehensive testing strategies ensure software reliability
 * - Testing frameworks and tools improve testing efficiency
 * - Automated testing enables continuous integration and deployment
 */"""
