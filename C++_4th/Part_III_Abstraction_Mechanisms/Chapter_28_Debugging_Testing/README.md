# Chapter 28: Debugging and Testing

## 📘 Learning Objectives

After completing this chapter, you will:
- Master C++ debugging techniques and tools
- Understand unit testing frameworks and practices
- Learn about test-driven development (TDD)
- Master debugging tools and techniques
- Understand code coverage and quality metrics

## 🎯 Key Concepts

### 1. Debugging Techniques

- **Debugger usage**: GDB, LLDB, Visual Studio Debugger
- **Breakpoints**: Conditional and data breakpoints
- **Watch expressions**: Variable monitoring
- **Call stack analysis**: Stack trace analysis
- **Memory debugging**: Memory leak detection

### 2. Unit Testing

- **Testing frameworks**: Google Test, Catch2, Boost.Test
- **Test organization**: Test suites and fixtures
- **Assertions**: Test assertions and expectations
- **Mock objects**: Test doubles and mocking
- **Test data**: Test data generation and management

### 3. Test-Driven Development

- **TDD cycle**: Red-Green-Refactor
- **Test-first design**: Writing tests before code
- **Refactoring**: Code improvement with tests
- **Test maintenance**: Keeping tests up to date
- **Test quality**: Writing effective tests

### 4. Debugging Tools

- **Static analysis**: Clang Static Analyzer, PVS-Studio
- **Dynamic analysis**: Valgrind, AddressSanitizer
- **Memory debugging**: MemorySanitizer, ThreadSanitizer
- **Performance profiling**: Profiling tools
- **Code coverage**: Coverage analysis tools

### 5. Quality Assurance

- **Code review**: Peer review processes
- **Static analysis**: Automated code analysis
- **Continuous integration**: Automated testing
- **Quality metrics**: Code quality measurement
- **Documentation**: Code documentation practices

## 🧩 Practice Exercises

### Exercise 28.1: Debugging
Use debugger to find and fix bugs.

### Exercise 28.2: Unit Testing
Write comprehensive unit tests.

### Exercise 28.3: Test-Driven Development
Practice TDD with a small project.

### Exercise 28.4: Code Coverage
Achieve high code coverage with tests.

## 💻 Code Examples

### Unit Testing with Google Test
```cpp
#include <gtest/gtest.h>
#include <vector>
#include <algorithm>

// Function to test
int find_max(const std::vector<int>& data) {
    if (data.empty()) {
        throw std::invalid_argument("Empty vector");
    }
    return *std::max_element(data.begin(), data.end());
}

// Test cases
TEST(FindMaxTest, BasicTest) {
    std::vector<int> data = {1, 5, 3, 9, 2};
    EXPECT_EQ(find_max(data), 9);
}

TEST(FindMaxTest, SingleElement) {
    std::vector<int> data = {42};
    EXPECT_EQ(find_max(data), 42);
}

TEST(FindMaxTest, EmptyVector) {
    std::vector<int> data;
    EXPECT_THROW(find_max(data), std::invalid_argument);
}

TEST(FindMaxTest, NegativeNumbers) {
    std::vector<int> data = {-1, -5, -3, -9, -2};
    EXPECT_EQ(find_max(data), -1);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
```

### Mock Objects
```cpp
#include <gtest/gtest.h>
#include <gmock/gmock.h>

// Interface to mock
class Database {
public:
    virtual ~Database() = default;
    virtual bool save(const std::string& data) = 0;
    virtual std::string load(int id) = 0;
};

// Mock implementation
class MockDatabase : public Database {
public:
    MOCK_METHOD(bool, save, (const std::string&), (override));
    MOCK_METHOD(std::string, load, (int), (override));
};

// Class under test
class DataManager {
private:
    Database* db;
public:
    DataManager(Database* database) : db(database) {}
    
    bool store_data(const std::string& data) {
        return db->save(data);
    }
    
    std::string retrieve_data(int id) {
        return db->load(id);
    }
};

// Test with mock
TEST(DataManagerTest, StoreData) {
    MockDatabase mock_db;
    DataManager manager(&mock_db);
    
    EXPECT_CALL(mock_db, save("test data"))
        .WillOnce(::testing::Return(true));
    
    bool result = manager.store_data("test data");
    EXPECT_TRUE(result);
}
```

## 🎓 Key Takeaways

1. **Use debugger effectively** for bug identification
2. **Write comprehensive tests** for code reliability
3. **Practice test-driven development** for better design
4. **Use debugging tools** for systematic bug fixing
5. **Maintain code quality** with continuous testing

## 🔗 Next Steps

After mastering debugging and testing, proceed to Chapter 29 to learn about advanced topics.

## 📚 Additional Resources

- C++ Reference: Debugging
- C++ Core Guidelines: Testing
- Practice with testing frameworks and tools
