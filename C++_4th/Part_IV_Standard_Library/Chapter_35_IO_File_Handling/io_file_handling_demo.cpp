#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <stdexcept>

// Demonstrates I/O and file handling
int main() {
    std::cout << "I/O and File Handling Demonstration" << std::endl;
    std::cout << "===================================" << std::endl;
    
    // 1. Basic stream I/O
    std::cout << "\n1. BASIC STREAM I/O:" << std::endl;
    
    std::cout << "Enter your name: ";
    std::string name;
    std::getline(std::cin, name);
    
    std::cout << "Enter your age: ";
    int age;
    std::cin >> age;
    
    std::cout << "Enter your height (in meters): ";
    double height;
    std::cin >> height;
    
    std::cout << "\nHello, " << name << "!" << std::endl;
    std::cout << "You are " << age << " years old and " 
              << std::fixed << std::setprecision(2) << height 
              << " meters tall." << std::endl;
    
    // 2. Stream manipulators
    std::cout << "\n2. STREAM MANIPULATORS:" << std::endl;
    
    int number = 255;
    double pi = 3.14159265359;
    
    std::cout << "Decimal: " << number << std::endl;
    std::cout << "Hexadecimal: " << std::hex << number << std::endl;
    std::cout << "Octal: " << std::oct << number << std::endl;
    std::cout << "Decimal again: " << std::dec << number << std::endl;
    
    std::cout << "Pi with different precision:" << std::endl;
    std::cout << "Default: " << pi << std::endl;
    std::cout << "2 decimal places: " << std::fixed << std::setprecision(2) << pi << std::endl;
    std::cout << "Scientific notation: " << std::scientific << pi << std::endl;
    std::cout << "Default notation: " << std::defaultfloat << pi << std::endl;
    
    // 3. File operations
    std::cout << "\n3. FILE OPERATIONS:" << std::endl;
    
    // Write to text file
    std::cout << "Writing to text file..." << std::endl;
    std::ofstream text_file("demo.txt");
    if (text_file.is_open()) {
        text_file << "Hello, World!" << std::endl;
        text_file << "This is a demonstration of file I/O." << std::endl;
        text_file << "Numbers: " << 42 << " " << 3.14 << " " << 2.718 << std::endl;
        text_file << "Name: " << name << std::endl;
        text_file << "Age: " << age << std::endl;
        text_file.close();
        std::cout << "Text file written successfully." << std::endl;
    } else {
        std::cout << "Error: Could not open file for writing." << std::endl;
    }
    
    // Read from text file
    std::cout << "\nReading from text file..." << std::endl;
    std::ifstream input_file("demo.txt");
    if (input_file.is_open()) {
        std::string line;
        while (std::getline(input_file, line)) {
            std::cout << "Read: " << line << std::endl;
        }
        input_file.close();
    } else {
        std::cout << "Error: Could not open file for reading." << std::endl;
    }
    
    // 4. String streams
    std::cout << "\n4. STRING STREAMS:" << std::endl;
    
    // Output string stream
    std::ostringstream oss;
    oss << "String stream demo" << std::endl;
    oss << "Number: " << 123 << std::endl;
    oss << "Float: " << std::fixed << std::setprecision(3) << 45.678 << std::endl;
    
    std::string oss_result = oss.str();
    std::cout << "Output string stream result:" << std::endl;
    std::cout << oss_result;
    
    // Input string stream
    std::string data = "John 25 1.75 Engineer";
    std::istringstream iss(data);
    
    std::string person_name, profession;
    int person_age;
    double person_height;
    
    iss >> person_name >> person_age >> person_height >> profession;
    
    std::cout << "\nParsed data:" << std::endl;
    std::cout << "Name: " << person_name << std::endl;
    std::cout << "Age: " << person_age << std::endl;
    std::cout << "Height: " << person_height << std::endl;
    std::cout << "Profession: " << profession << std::endl;
    
    // 5. Binary file operations
    std::cout << "\n5. BINARY FILE OPERATIONS:" << std::endl;
    
    // Write binary data
    std::cout << "Writing binary data..." << std::endl;
    std::ofstream binary_file("data.bin", std::ios::binary);
    if (binary_file.is_open()) {
        int numbers[] = {1, 2, 3, 4, 5};
        double values[] = {1.1, 2.2, 3.3, 4.4, 5.5};
        
        binary_file.write(reinterpret_cast<const char*>(numbers), sizeof(numbers));
        binary_file.write(reinterpret_cast<const char*>(values), sizeof(values));
        
        binary_file.close();
        std::cout << "Binary file written successfully." << std::endl;
    }
    
    // Read binary data
    std::cout << "Reading binary data..." << std::endl;
    std::ifstream binary_input("data.bin", std::ios::binary);
    if (binary_input.is_open()) {
        int read_numbers[5];
        double read_values[5];
        
        binary_input.read(reinterpret_cast<char*>(read_numbers), sizeof(read_numbers));
        binary_input.read(reinterpret_cast<char*>(read_values), sizeof(read_values));
        
        std::cout << "Read numbers: ";
        for (int i = 0; i < 5; ++i) {
            std::cout << read_numbers[i] << " ";
        }
        std::cout << std::endl;
        
        std::cout << "Read values: ";
        for (int i = 0; i < 5; ++i) {
            std::cout << std::fixed << std::setprecision(1) << read_values[i] << " ";
        }
        std::cout << std::endl;
        
        binary_input.close();
    }
    
    // 6. File positioning
    std::cout << "\n6. FILE POSITIONING:" << std::endl;
    
    std::ofstream pos_file("position.txt");
    if (pos_file.is_open()) {
        pos_file << "Line 1" << std::endl;
        pos_file << "Line 2" << std::endl;
        pos_file << "Line 3" << std::endl;
        
        std::streampos pos = pos_file.tellp();
        std::cout << "Current position: " << pos << std::endl;
        
        pos_file.seekp(0, std::ios::beg);
        pos_file << "Modified Line 1" << std::endl;
        
        pos_file.close();
    }
    
    std::ifstream pos_input("position.txt");
    if (pos_input.is_open()) {
        std::string line;
        while (std::getline(pos_input, line)) {
            std::cout << "Read: " << line << std::endl;
        }
        pos_input.close();
    }
    
    // 7. Error handling
    std::cout << "\n7. ERROR HANDLING:" << std::endl;
    
    // Check stream states
    std::ifstream error_file("nonexistent.txt");
    if (!error_file.is_open()) {
        std::cout << "Error: File does not exist." << std::endl;
    }
    
    // Stream state checking
    std::cout << "Stream state flags:" << std::endl;
    std::cout << "good: " << std::boolalpha << error_file.good() << std::endl;
    std::cout << "fail: " << std::boolalpha << error_file.fail() << std::endl;
    std::cout << "bad: " << std::boolalpha << error_file.bad() << std::endl;
    std::cout << "eof: " << std::boolalpha << error_file.eof() << std::endl;
    
    // Clear error state
    error_file.clear();
    std::cout << "After clear - good: " << std::boolalpha << error_file.good() << std::endl;
    
    // 8. CSV file handling
    std::cout << "\n8. CSV FILE HANDLING:" << std::endl;
    
    // Write CSV file
    std::ofstream csv_file("data.csv");
    if (csv_file.is_open()) {
        csv_file << "Name,Age,Height,Profession" << std::endl;
        csv_file << "Alice,25,1.65,Engineer" << std::endl;
        csv_file << "Bob,30,1.80,Doctor" << std::endl;
        csv_file << "Charlie,35,1.75,Teacher" << std::endl;
        csv_file.close();
    }
    
    // Read CSV file
    std::ifstream csv_input("data.csv");
    if (csv_input.is_open()) {
        std::string line;
        bool first_line = true;
        
        while (std::getline(csv_input, line)) {
            if (first_line) {
                std::cout << "Header: " << line << std::endl;
                first_line = false;
                continue;
            }
            
            std::istringstream csv_line(line);
            std::string field;
            std::vector<std::string> fields;
            
            while (std::getline(csv_line, field, ',')) {
                fields.push_back(field);
            }
            
            if (fields.size() >= 4) {
                std::cout << "Name: " << fields[0] 
                          << ", Age: " << fields[1]
                          << ", Height: " << fields[2]
                          << ", Profession: " << fields[3] << std::endl;
            }
        }
        csv_input.close();
    }
    
    // 9. Formatted output
    std::cout << "\n9. FORMATTED OUTPUT:" << std::endl;
    
    std::vector<std::string> names = {"Alice", "Bob", "Charlie", "Diana"};
    std::vector<int> ages = {25, 30, 35, 28};
    std::vector<double> salaries = {50000.0, 60000.0, 70000.0, 55000.0};
    
    std::cout << std::left << std::setw(10) << "Name" 
              << std::setw(5) << "Age" 
              << std::setw(12) << "Salary" << std::endl;
    std::cout << std::string(27, '-') << std::endl;
    
    for (size_t i = 0; i < names.size(); ++i) {
        std::cout << std::left << std::setw(10) << names[i]
                  << std::setw(5) << ages[i]
                  << std::right << std::setw(12) << std::fixed << std::setprecision(2) 
                  << salaries[i] << std::endl;
    }
    
    // 10. Stream buffer operations
    std::cout << "\n10. STREAM BUFFER OPERATIONS:" << std::endl;
    
    std::string buffer_data = "This is buffer data";
    std::istringstream buffer_stream(buffer_data);
    
    std::cout << "Buffer content: ";
    char c;
    while (buffer_stream.get(c)) {
        std::cout << c;
    }
    std::cout << std::endl;
    
    // 11. Custom stream manipulator
    std::cout << "\n11. CUSTOM STREAM MANIPULATOR:" << std::endl;
    
    auto print_separator = [](std::ostream& os) -> std::ostream& {
        os << "----------------------------------------" << std::endl;
        return os;
    };
    
    std::cout << print_separator;
    std::cout << "This is separated content" << std::endl;
    std::cout << print_separator;
    
    // 12. File appending
    std::cout << "\n12. FILE APPENDING:" << std::endl;
    
    std::ofstream append_file("append.txt", std::ios::app);
    if (append_file.is_open()) {
        append_file << "This line is appended." << std::endl;
        append_file << "Another appended line." << std::endl;
        append_file.close();
    }
    
    std::ifstream read_append("append.txt");
    if (read_append.is_open()) {
        std::string line;
        while (std::getline(read_append, line)) {
            std::cout << "Appended file: " << line << std::endl;
        }
        read_append.close();
    }
    
    // Clean up files
    std::remove("demo.txt");
    std::remove("data.bin");
    std::remove("position.txt");
    std::remove("data.csv");
    std::remove("append.txt");
    
    std::cout << "\nI/O and file handling demonstration completed!" << std::endl;
    return 0;
}
