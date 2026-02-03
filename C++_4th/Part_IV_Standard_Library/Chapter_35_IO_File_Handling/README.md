# Chapter 35: I/O and File Handling

## 📘 Learning Objectives

After completing this chapter, you will:
- Master stream I/O operations
- Understand file input and output
- Learn about string streams and formatting
- Master binary file operations
- Understand I/O error handling and exceptions

## 🎯 Key Concepts

### 1. Stream I/O

- **iostream**: Standard input/output streams
- **Stream operators**: << and >> for formatted I/O
- **Stream states**: good, fail, eof, bad
- **Stream manipulators**: setw, setprecision, hex, oct
- **Stream buffers**: Custom buffering and formatting

### 2. File Operations

- **ifstream**: Input file stream
- **ofstream**: Output file stream
- **fstream**: Bidirectional file stream
- **File modes**: in, out, app, binary, trunc
- **File positioning**: seekg, seekp, tellg, tellp

### 3. String Streams

- **istringstream**: Input string stream
- **ostringstream**: Output string stream
- **stringstream**: Bidirectional string stream
- **String formatting**: Number to string conversion
- **String parsing**: String to number conversion

### 4. Binary File Operations

- **Binary mode**: Reading/writing raw data
- **Data serialization**: Saving objects to files
- **Data deserialization**: Loading objects from files
- **Endianness**: Byte order considerations

### 5. Error Handling

- **Stream states**: Checking for errors
- **Exception handling**: Stream exceptions
- **Error recovery**: Clearing error states
- **Validation**: Input validation and error checking

## 🧩 Practice Exercises

### Exercise 35.1: Basic I/O
Use stream operators for input and output.

### Exercise 35.2: File Operations
Read from and write to files.

### Exercise 35.3: String Streams
Use string streams for formatting.

### Exercise 35.4: Binary Files
Handle binary file operations.

## 💻 Code Examples

### Basic I/O
```cpp
#include <iostream>
#include <iomanip>

int main() {
    int number;
    double value;
    std::string name;
    
    std::cout << "Enter an integer: ";
    std::cin >> number;
    
    std::cout << "Enter a double: ";
    std::cin >> value;
    
    std::cout << "Enter your name: ";
    std::cin >> name;
    
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "Hello " << name << ", you entered " << number 
              << " and " << value << std::endl;
    
    return 0;
}
```

### File Operations
```cpp
#include <iostream>
#include <fstream>
#include <string>

int main() {
    // Write to file
    std::ofstream outfile("data.txt");
    if (outfile.is_open()) {
        outfile << "Hello, World!" << std::endl;
        outfile << 42 << " " << 3.14 << std::endl;
        outfile.close();
    }
    
    // Read from file
    std::ifstream infile("data.txt");
    if (infile.is_open()) {
        std::string line;
        while (std::getline(infile, line)) {
            std::cout << line << std::endl;
        }
        infile.close();
    }
    
    return 0;
}
```

## 🎓 Key Takeaways

1. **Use RAII for file handling**: Automatic resource management
2. **Check stream states**: Always verify I/O operations
3. **Use string streams**: For formatting and parsing
4. **Handle errors gracefully**: Check for I/O failures
5. **Use appropriate file modes**: Text vs binary operations

## 🔗 Next Steps

After mastering I/O and file handling, proceed to Chapter 36 to learn about regular expressions.

## 📚 Additional Resources

- C++ Reference: I/O Streams
- C++ Core Guidelines: I/O
- Practice with different file formats
