#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cassert>
#include <cmath>
#include <ctime>

// Demonstrates C Standard Library compatibility
int main() {
    std::cout << "C Standard Library Compatibility Demonstration" << std::endl;
    std::cout << "===============================================" << std::endl;
    
    // 1. C Standard Library Headers
    std::cout << "\n1. C STANDARD LIBRARY HEADERS:" << std::endl;
    
    // stdio.h functions
    std::cout << "  Using stdio.h functions:" << std::endl;
    printf("    printf: Hello from C!\n");
    
    char buffer[100];
    sprintf(buffer, "    sprintf: Number %d, Float %.2f\n", 42, 3.14159);
    printf("%s", buffer);
    
    // stdlib.h functions
    std::cout << "  Using stdlib.h functions:" << std::endl;
    int random_num = rand() % 100;
    printf("    Random number: %d\n", random_num);
    
    double strtod_result = strtod("3.14159", nullptr);
    printf("    strtod result: %.5f\n", strtod_result);
    
    int atoi_result = atoi("12345");
    printf("    atoi result: %d\n", atoi_result);
    
    // string.h functions
    std::cout << "  Using string.h functions:" << std::endl;
    char str1[] = "Hello";
    char str2[] = "World";
    char str3[20];
    
    strcpy(str3, str1);
    strcat(str3, " ");
    strcat(str3, str2);
    printf("    Concatenated string: %s\n", str3);
    printf("    String length: %zu\n", strlen(str3));
    printf("    String comparison: %d\n", strcmp(str1, str2));
    
    // 2. Memory Management
    std::cout << "\n2. MEMORY MANAGEMENT:" << std::endl;
    
    // malloc/free
    int* ptr = (int*)malloc(5 * sizeof(int));
    if (ptr != nullptr) {
        for (int i = 0; i < 5; ++i) {
            ptr[i] = i * 2;
        }
        printf("  malloc array: ");
        for (int i = 0; i < 5; ++i) {
            printf("%d ", ptr[i]);
        }
        printf("\n");
        free(ptr);
    }
    
    // calloc/realloc
    int* ptr2 = (int*)calloc(3, sizeof(int));
    if (ptr2 != nullptr) {
        printf("  calloc initialized array: ");
        for (int i = 0; i < 3; ++i) {
            printf("%d ", ptr2[i]);
        }
        printf("\n");
        
        ptr2 = (int*)realloc(ptr2, 5 * sizeof(int));
        if (ptr2 != nullptr) {
            ptr2[3] = 10;
            ptr2[4] = 20;
            printf("  realloc extended array: ");
            for (int i = 0; i < 5; ++i) {
                printf("%d ", ptr2[i]);
            }
            printf("\n");
        }
        free(ptr2);
    }
    
    // 3. Mathematical Functions
    std::cout << "\n3. MATHEMATICAL FUNCTIONS:" << std::endl;
    
    double x = 2.5;
    printf("  x = %.2f\n", x);
    printf("  sin(x) = %.6f\n", sin(x));
    printf("  cos(x) = %.6f\n", cos(x));
    printf("  sqrt(x) = %.6f\n", sqrt(x));
    printf("  pow(x, 2) = %.6f\n", pow(x, 2));
    printf("  log(x) = %.6f\n", log(x));
    printf("  exp(x) = %.6f\n", exp(x));
    printf("  fabs(-x) = %.6f\n", fabs(-x));
    printf("  ceil(x) = %.0f\n", ceil(x));
    printf("  floor(x) = %.0f\n", floor(x));
    printf("  round(x) = %.0f\n", round(x));
    
    // 4. Character Classification
    std::cout << "\n4. CHARACTER CLASSIFICATION:" << std::endl;
    
    char test_chars[] = "Hello123!@#";
    printf("  Test string: %s\n", test_chars);
    
    for (int i = 0; test_chars[i] != '\0'; ++i) {
        char c = test_chars[i];
        printf("  '%c': alpha=%d, digit=%d, alnum=%d, space=%d, punct=%d\n",
               c, isalpha(c), isdigit(c), isalnum(c), isspace(c), ispunct(c));
    }
    
    // Character conversion
    char upper_char = toupper('a');
    char lower_char = tolower('A');
    printf("  toupper('a') = '%c'\n", upper_char);
    printf("  tolower('A') = '%c'\n", lower_char);
    
    // 5. String Manipulation
    std::cout << "\n5. STRING MANIPULATION:" << std::endl;
    
    char str[50] = "Hello, World!";
    printf("  Original string: %s\n", str);
    
    // String length
    printf("  Length: %zu\n", strlen(str));
    
    // String copy
    char str_copy[50];
    strcpy(str_copy, str);
    printf("  Copied string: %s\n", str_copy);
    
    // String concatenation
    strcat(str_copy, " How are you?");
    printf("  Concatenated: %s\n", str_copy);
    
    // String comparison
    printf("  strcmp(\"Hello\", \"World\"): %d\n", strcmp("Hello", "World"));
    printf("  strcmp(\"Hello\", \"Hello\"): %d\n", strcmp("Hello", "Hello"));
    printf("  strcmp(\"World\", \"Hello\"): %d\n", strcmp("World", "Hello"));
    
    // String search
    char* found = strchr(str, 'o');
    if (found) {
        printf("  First 'o' found at position: %ld\n", found - str);
    }
    
    found = strstr(str, "World");
    if (found) {
        printf("  \"World\" found at position: %ld\n", found - str);
    }
    
    // 6. File I/O
    std::cout << "\n6. FILE I/O:" << std::endl;
    
    // Write to file
    FILE* file = fopen("c_test.txt", "w");
    if (file != nullptr) {
        fprintf(file, "Hello from C file I/O!\n");
        fprintf(file, "Number: %d, Float: %.2f\n", 42, 3.14159);
        fclose(file);
        printf("  File written successfully\n");
    }
    
    // Read from file
    file = fopen("c_test.txt", "r");
    if (file != nullptr) {
        char line[100];
        printf("  File contents:\n");
        while (fgets(line, sizeof(line), file) != nullptr) {
            printf("    %s", line);
        }
        fclose(file);
    }
    
    // 7. Time Functions
    std::cout << "\n7. TIME FUNCTIONS:" << std::endl;
    
    time_t current_time = time(nullptr);
    printf("  Current time: %ld\n", current_time);
    
    struct tm* timeinfo = localtime(&current_time);
    printf("  Local time: %s", asctime(timeinfo));
    
    char time_str[100];
    strftime(time_str, sizeof(time_str), "%Y-%m-%d %H:%M:%S", timeinfo);
    printf("  Formatted time: %s\n", time_str);
    
    // 8. Random Number Generation
    std::cout << "\n8. RANDOM NUMBER GENERATION:" << std::endl;
    
    srand(static_cast<unsigned int>(time(nullptr)));
    
    printf("  Random numbers: ");
    for (int i = 0; i < 5; ++i) {
        printf("%d ", rand() % 100);
    }
    printf("\n");
    
    // 9. Error Handling
    std::cout << "\n9. ERROR HANDLING:" << std::endl;
    
    // errno usage
    errno = 0;
    double result = sqrt(-1.0);
    if (errno != 0) {
        printf("  Error occurred: %s\n", strerror(errno));
    }
    
    // perror usage
    FILE* error_file = fopen("nonexistent.txt", "r");
    if (error_file == nullptr) {
        perror("  File open error");
    }
    
    // 10. Assertions
    std::cout << "\n10. ASSERTIONS:" << std::endl;
    
    int value = 42;
    assert(value > 0);
    printf("  Assertion passed: value > 0\n");
    
    // This would cause assertion failure in debug mode
    // assert(value < 0);
    
    // 11. C++ and C Interoperability
    std::cout << "\n11. C++ AND C INTEROPERABILITY:" << std::endl;
    
    // Using C functions in C++
    std::string cpp_string = "Hello from C++";
    const char* c_string = cpp_string.c_str();
    printf("  C++ string as C string: %s\n", c_string);
    
    // Using C++ features with C data
    char c_buffer[100];
    strcpy(c_buffer, "Hello, World!");
    std::string cpp_string2(c_buffer);
    std::cout << "  C string as C++ string: " << cpp_string2 << std::endl;
    
    // 12. Performance Comparison
    std::cout << "\n12. PERFORMANCE COMPARISON:" << std::endl;
    
    const int num_iterations = 1000000;
    
    // C-style string operations
    auto start = std::chrono::high_resolution_clock::now();
    
    char c_result[1000] = "";
    for (int i = 0; i < num_iterations / 1000; ++i) {
        strcat(c_result, "a");
    }
    
    auto end = std::chrono::high_resolution_clock::now();
    auto c_time = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    
    // C++ string operations
    start = std::chrono::high_resolution_clock::now();
    
    std::string cpp_result;
    for (int i = 0; i < num_iterations / 1000; ++i) {
        cpp_result += "a";
    }
    
    end = std::chrono::high_resolution_clock::now();
    auto cpp_time = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    
    printf("  C string operations time: %ld microseconds\n", c_time.count());
    printf("  C++ string operations time: %ld microseconds\n", cpp_time.count());
    printf("  C++ speedup: %.2fx\n", (double)c_time.count() / cpp_time.count());
    
    // 13. Best Practices
    std::cout << "\n13. BEST PRACTICES:" << std::endl;
    
    // Always check return values
    FILE* safe_file = fopen("safe_test.txt", "w");
    if (safe_file != nullptr) {
        fprintf(safe_file, "Safe file operations\n");
        fclose(safe_file);
        printf("  Safe file operations completed\n");
    } else {
        perror("  Safe file open failed");
    }
    
    // Use const correctness
    const char* const_string = "This is a constant string";
    printf("  Constant string: %s\n", const_string);
    
    // Proper memory management
    int* safe_ptr = (int*)malloc(10 * sizeof(int));
    if (safe_ptr != nullptr) {
        // Use the memory
        for (int i = 0; i < 10; ++i) {
            safe_ptr[i] = i;
        }
        printf("  Safe memory allocation completed\n");
        free(safe_ptr);
    }
    
    // 14. Common Pitfalls
    std::cout << "\n14. COMMON PITFALLS:" << std::endl;
    
    // Buffer overflow prevention
    char safe_buffer[10];
    strncpy(safe_buffer, "Hello, World!", sizeof(safe_buffer) - 1);
    safe_buffer[sizeof(safe_buffer) - 1] = '\0';
    printf("  Safe string copy: %s\n", safe_buffer);
    
    // Null pointer checks
    char* null_ptr = nullptr;
    if (null_ptr != nullptr) {
        printf("  This won't be printed\n");
    } else {
        printf("  Null pointer check passed\n");
    }
    
    // 15. Modern C++ with C Libraries
    std::cout << "\n15. MODERN C++ WITH C LIBRARIES:" << std::endl;
    
    // Using C libraries with modern C++ features
    std::vector<int> cpp_vector = {1, 2, 3, 4, 5};
    
    // Convert to C array for C function
    int* c_array = cpp_vector.data();
    printf("  C++ vector as C array: ");
    for (size_t i = 0; i < cpp_vector.size(); ++i) {
        printf("%d ", c_array[i]);
    }
    printf("\n");
    
    // Using C++ algorithms with C data
    std::sort(cpp_vector.begin(), cpp_vector.end());
    printf("  Sorted C++ vector: ");
    for (int val : cpp_vector) {
        printf("%d ", val);
    }
    printf("\n");
    
    std::cout << "\nC Standard Library compatibility demonstration completed!" << std::endl;
    return 0;
}
