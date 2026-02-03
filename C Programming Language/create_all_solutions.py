#!/usr/bin/env python3
"""
Complete script to generate ALL individual C files from Exercise_Solutions.md
"""

import os
import re

BASE_DIR = "/Users/nelsonlai/sources/freelance/The C Programming Language/solutions"

# All remaining solutions
remaining_solutions = [
    # Week 7 remaining solutions
    {
        "path": "intermediate/week7/solution_7_3_string_reverse_pointers.c",
        "title": "Solution 7.3: String Reverser Using Pointers",
        "week": "Week 7 - Pointers Fundamentals",
        "description": "Create a function to reverse a string using pointers",
        "code": '''#include <stdio.h>
#include <string.h>

void reverseString(char *str) {
    char *start = str;
    char *end = str + strlen(str) - 1;
    
    while (start < end) {
        // Swap characters
        char temp = *start;
        *start = *end;
        *end = temp;
        
        start++;
        end--;
    }
}

int main() {
    char str[100];
    
    printf("Enter a string: ");
    fgets(str, sizeof(str), stdin);
    
    // Remove newline character
    str[strcspn(str, "\\n")] = '\\0';
    
    printf("Original string: %s\\n", str);
    
    reverseString(str);
    
    printf("Reversed string: %s\\n", str);
    
    return 0;
}'''
    },
    {
        "path": "intermediate/week7/solution_7_4_array_sort_pointers.c",
        "title": "Solution 7.4: Array Sort Using Pointers",
        "week": "Week 7 - Pointers Fundamentals",
        "description": "Sort an array using pointers",
        "code": '''#include <stdio.h>

void sortArray(int *arr, int n) {
    for (int i = 0; i < n-1; i++) {
        for (int j = 0; j < n-i-1; j++) {
            if (*(arr + j) > *(arr + j + 1)) {
                // Swap using pointers
                int temp = *(arr + j);
                *(arr + j) = *(arr + j + 1);
                *(arr + j + 1) = temp;
            }
        }
    }
}

void printArray(int *arr, int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", *(arr + i));
    }
    printf("\\n");
}

int main() {
    int n;
    
    printf("Enter number of elements: ");
    scanf("%d", &n);
    
    int arr[n];
    
    printf("Enter %d elements: ", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }
    
    printf("Original array: ");
    printArray(arr, n);
    
    sortArray(arr, n);
    
    printf("Sorted array: ");
    printArray(arr, n);
    
    return 0;
}'''
    },
    # Week 8 remaining solutions
    {
        "path": "intermediate/week8/solution_8_1_matrix_multiplication.c",
        "title": "Solution 8.1: Matrix Multiplication",
        "week": "Week 8 - Advanced Arrays and Strings",
        "description": "Matrix multiplication program",
        "code": '''#include <stdio.h>

void multiplyMatrices(int first[10][10], int second[10][10], int result[10][10], 
                     int r1, int c1, int r2, int c2) {
    // Initialize result matrix to zero
    for (int i = 0; i < r1; i++) {
        for (int j = 0; j < c2; j++) {
            result[i][j] = 0;
        }
    }
    
    // Multiply matrices
    for (int i = 0; i < r1; i++) {
        for (int j = 0; j < c2; j++) {
            for (int k = 0; k < c1; k++) {
                result[i][j] += first[i][k] * second[k][j];
            }
        }
    }
}

void printMatrix(int matrix[10][10], int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\\n");
    }
}

int main() {
    int first[10][10], second[10][10], result[10][10];
    int r1, c1, r2, c2;
    
    printf("Enter rows and columns for first matrix: ");
    scanf("%d %d", &r1, &c1);
    
    printf("Enter rows and columns for second matrix: ");
    scanf("%d %d", &r2, &c2);
    
    if (c1 != r2) {
        printf("Matrix multiplication not possible!\\n");
        return 1;
    }
    
    printf("Enter elements of first matrix:\\n");
    for (int i = 0; i < r1; i++) {
        for (int j = 0; j < c1; j++) {
            scanf("%d", &first[i][j]);
        }
    }
    
    printf("Enter elements of second matrix:\\n");
    for (int i = 0; i < r2; i++) {
        for (int j = 0; j < c2; j++) {
            scanf("%d", &second[i][j]);
        }
    }
    
    multiplyMatrices(first, second, result, r1, c1, r2, c2);
    
    printf("Result matrix:\\n");
    printMatrix(result, r1, c2);
    
    return 0;
}'''
    },
    {
        "path": "intermediate/week8/solution_8_2_word_count_cmdline.c",
        "title": "Solution 8.2: Word Count with Command Line Arguments",
        "week": "Week 8 - Advanced Arrays and Strings",
        "description": "Word count program using command line arguments",
        "code": '''#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int countWords(FILE *file) {
    int words = 0;
    int inWord = 0;
    int ch;
    
    while ((ch = fgetc(file)) != EOF) {
        if (isspace(ch)) {
            inWord = 0;
        } else if (!inWord) {
            inWord = 1;
            words++;
        }
    }
    
    return words;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <filename>\\n", argv[0]);
        return 1;
    }
    
    FILE *file = fopen(argv[1], "r");
    if (file == NULL) {
        printf("Error: Cannot open file '%s'\\n", argv[1]);
        return 1;
    }
    
    int wordCount = countWords(file);
    fclose(file);
    
    printf("File '%s' contains %d words.\\n", argv[1], wordCount);
    
    return 0;
}'''
    },
    {
        "path": "intermediate/week8/solution_8_3_string_tokenizer.c",
        "title": "Solution 8.3: String Tokenizer",
        "week": "Week 8 - Advanced Arrays and Strings",
        "description": "String tokenizer program",
        "code": '''#include <stdio.h>
#include <string.h>

void tokenizeString(char *str, char delimiter) {
    char *token = strtok(str, &delimiter);
    int count = 0;
    
    printf("Tokens:\\n");
    while (token != NULL) {
        count++;
        printf("%d: %s\\n", count, token);
        token = strtok(NULL, &delimiter);
    }
    
    printf("Total tokens: %d\\n", count);
}

int main() {
    char str[200];
    char delimiter;
    
    printf("Enter a string: ");
    fgets(str, sizeof(str), stdin);
    
    // Remove newline character
    str[strcspn(str, "\\n")] = '\\0';
    
    printf("Enter delimiter: ");
    scanf("%c", &delimiter);
    
    tokenizeString(str, delimiter);
    
    return 0;
}'''
    },
    # Advanced Week 9 remaining solutions
    {
        "path": "advanced/week9/solution_9_2_library_management.c",
        "title": "Solution 9.2: Library Book Management System",
        "week": "Week 9 - Structures and User-Defined Types",
        "description": "Library book management system",
        "code": '''#include <stdio.h>
#include <string.h>

#define MAX_BOOKS 100

struct Book {
    int id;
    char title[100];
    char author[50];
    int year;
    float price;
    int isAvailable;
};

struct Book library[MAX_BOOKS];
int bookCount = 0;

void addBook() {
    if (bookCount >= MAX_BOOKS) {
        printf("Library is full!\\n");
        return;
    }
    
    struct Book *b = &library[bookCount];
    
    printf("Enter book ID: ");
    scanf("%d", &b->id);
    
    printf("Enter book title: ");
    getchar(); // consume newline
    fgets(b->title, sizeof(b->title), stdin);
    b->title[strcspn(b->title, "\\n")] = '\\0'; // remove newline
    
    printf("Enter author name: ");
    fgets(b->author, sizeof(b->author), stdin);
    b->author[strcspn(b->author, "\\n")] = '\\0'; // remove newline
    
    printf("Enter publication year: ");
    scanf("%d", &b->year);
    
    printf("Enter price: ");
    scanf("%f", &b->price);
    
    b->isAvailable = 1; // Book is available by default
    
    bookCount++;
    printf("Book added successfully!\\n");
}

void displayBooks() {
    if (bookCount == 0) {
        printf("No books in library.\\n");
        return;
    }
    
    printf("\\n--- Library Catalog ---\\n");
    printf("ID\\tTitle\\t\\t\\tAuthor\\t\\tYear\\tPrice\\tStatus\\n");
    printf("-----------------------------------------------------------------------\\n");
    
    for (int i = 0; i < bookCount; i++) {
        printf("%d\\t%-20s\\t%-15s\\t%d\\t%.2f\\t%s\\n",
               library[i].id, library[i].title, library[i].author,
               library[i].year, library[i].price,
               library[i].isAvailable ? "Available" : "Borrowed");
    }
}

void borrowBook() {
    int id;
    printf("Enter book ID to borrow: ");
    scanf("%d", &id);
    
    for (int i = 0; i < bookCount; i++) {
        if (library[i].id == id) {
            if (library[i].isAvailable) {
                library[i].isAvailable = 0;
                printf("Book '%s' borrowed successfully!\\n", library[i].title);
            } else {
                printf("Book is already borrowed!\\n");
            }
            return;
        }
    }
    
    printf("Book with ID %d not found.\\n", id);
}

void returnBook() {
    int id;
    printf("Enter book ID to return: ");
    scanf("%d", &id);
    
    for (int i = 0; i < bookCount; i++) {
        if (library[i].id == id) {
            if (!library[i].isAvailable) {
                library[i].isAvailable = 1;
                printf("Book '%s' returned successfully!\\n", library[i].title);
            } else {
                printf("Book is already available!\\n");
            }
            return;
        }
    }
    
    printf("Book with ID %d not found.\\n", id);
}

int main() {
    int choice;
    
    while (1) {
        printf("\\n--- Library Management System ---\\n");
        printf("1. Add Book\\n");
        printf("2. Display All Books\\n");
        printf("3. Borrow Book\\n");
        printf("4. Return Book\\n");
        printf("5. Exit\\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                addBook();
                break;
            case 2:
                displayBooks();
                break;
            case 3:
                borrowBook();
                break;
            case 4:
                returnBook();
                break;
            case 5:
                printf("Goodbye!\\n");
                return 0;
            default:
                printf("Invalid choice!\\n");
        }
    }
}'''
    },
    # Advanced Week 10 remaining solutions
    {
        "path": "advanced/week10/solution_10_2_word_frequency.c",
        "title": "Solution 10.2: Word Frequency Counter",
        "week": "Week 10 - File Input/Output",
        "description": "Word frequency counter",
        "code": '''#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_WORDS 1000
#define MAX_WORD_LENGTH 50

struct WordCount {
    char word[MAX_WORD_LENGTH];
    int count;
};

struct WordCount wordList[MAX_WORDS];
int wordCount = 0;

void toLowerCase(char *str) {
    for (int i = 0; str[i]; i++) {
        str[i] = tolower(str[i]);
    }
}

int findWord(char *word) {
    for (int i = 0; i < wordCount; i++) {
        if (strcmp(wordList[i].word, word) == 0) {
            return i;
        }
    }
    return -1;
}

void addWord(char *word) {
    toLowerCase(word);
    
    int index = findWord(word);
    if (index != -1) {
        wordList[index].count++;
    } else if (wordCount < MAX_WORDS) {
        strcpy(wordList[wordCount].word, word);
        wordList[wordCount].count = 1;
        wordCount++;
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <filename>\\n", argv[0]);
        return 1;
    }
    
    FILE *file = fopen(argv[1], "r");
    if (file == NULL) {
        printf("Error: Cannot open file '%s'\\n", argv[1]);
        return 1;
    }
    
    char word[MAX_WORD_LENGTH];
    
    while (fscanf(file, "%49s", word) == 1) {
        // Remove punctuation
        int len = strlen(word);
        while (len > 0 && !isalnum(word[len-1])) {
            word[len-1] = '\\0';
            len--;
        }
        
        if (len > 0) {
            addWord(word);
        }
    }
    
    fclose(file);
    
    printf("Word Frequency Report\\n");
    printf("=====================\\n");
    
    for (int i = 0; i < wordCount; i++) {
        printf("%-20s: %d\\n", wordList[i].word, wordList[i].count);
    }
    
    printf("\\nTotal unique words: %d\\n", wordCount);
    
    return 0;
}'''
    },
    # Advanced Week 11 remaining solutions
    {
        "path": "advanced/week11/solution_11_1_dynamic_strings.c",
        "title": "Solution 11.1: Dynamic String Manipulation",
        "week": "Week 11 - Dynamic Memory Management",
        "description": "Dynamic string manipulation",
        "code": '''#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* createString(const char* initial) {
    if (initial == NULL) {
        return NULL;
    }
    
    int len = strlen(initial);
    char* str = (char*)malloc((len + 1) * sizeof(char));
    
    if (str != NULL) {
        strcpy(str, initial);
    }
    
    return str;
}

char* concatenateStrings(const char* str1, const char* str2) {
    if (str1 == NULL || str2 == NULL) {
        return NULL;
    }
    
    int len1 = strlen(str1);
    int len2 = strlen(str2);
    
    char* result = (char*)malloc((len1 + len2 + 1) * sizeof(char));
    
    if (result != NULL) {
        strcpy(result, str1);
        strcat(result, str2);
    }
    
    return result;
}

char* resizeString(char* str, int newSize) {
    if (str == NULL || newSize <= 0) {
        return NULL;
    }
    
    char* newStr = (char*)realloc(str, newSize * sizeof(char));
    
    return newStr;
}

int main() {
    char* str1 = createString("Hello");
    char* str2 = createString(" World");
    
    if (str1 == NULL || str2 == NULL) {
        printf("Memory allocation failed!\\n");
        return 1;
    }
    
    printf("String 1: %s\\n", str1);
    printf("String 2: %s\\n", str2);
    
    char* combined = concatenateStrings(str1, str2);
    if (combined != NULL) {
        printf("Combined: %s\\n", combined);
    }
    
    // Resize string to accommodate more text
    str1 = resizeString(str1, 100);
    if (str1 != NULL) {
        strcat(str1, " from C!");
        printf("Extended string 1: %s\\n", str1);
    }
    
    // Free allocated memory
    free(str1);
    free(str2);
    free(combined);
    
    printf("Memory freed successfully!\\n");
    
    return 0;
}'''
    },
    # Expert Week 13 solutions
    {
        "path": "expert/week13/solution_13_1_file_copy_syscalls.c",
        "title": "Solution 13.1: File Copy Using System Calls",
        "week": "Week 13 - System Programming Basics",
        "description": "File copy using system calls",
        "code": '''#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <errno.h>
#include <string.h>

#define BUFFER_SIZE 4096

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <source> <destination>\\n", argv[0]);
        return 1;
    }
    
    int src_fd = open(argv[1], O_RDONLY);
    if (src_fd == -1) {
        fprintf(stderr, "Error opening source file '%s': %s\\n", 
                argv[1], strerror(errno));
        return 1;
    }
    
    struct stat src_stat;
    if (fstat(src_fd, &src_stat) == -1) {
        fprintf(stderr, "Error getting source file stats: %s\\n", strerror(errno));
        close(src_fd);
        return 1;
    }
    
    int dst_fd = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, src_stat.st_mode);
    if (dst_fd == -1) {
        fprintf(stderr, "Error creating destination file '%s': %s\\n", 
                argv[2], strerror(errno));
        close(src_fd);
        return 1;
    }
    
    char buffer[BUFFER_SIZE];
    ssize_t bytes_read, bytes_written;
    off_t total_bytes = 0;
    
    while ((bytes_read = read(src_fd, buffer, BUFFER_SIZE)) > 0) {
        bytes_written = write(dst_fd, buffer, bytes_read);
        if (bytes_written != bytes_read) {
            fprintf(stderr, "Error writing to destination file: %s\\n", 
                    strerror(errno));
            close(src_fd);
            close(dst_fd);
            return 1;
        }
        total_bytes += bytes_written;
    }
    
    if (bytes_read == -1) {
        fprintf(stderr, "Error reading from source file: %s\\n", strerror(errno));
        close(src_fd);
        close(dst_fd);
        return 1;
    }
    
    close(src_fd);
    close(dst_fd);
    
    printf("Successfully copied %ld bytes from '%s' to '%s'\\n", 
           total_bytes, argv[1], argv[2]);
    
    return 0;
}'''
    },
    {
        "path": "expert/week13/solution_13_2_process_monitor.c",
        "title": "Solution 13.2: Process Monitor Utility",
        "week": "Week 13 - System Programming Basics",
        "description": "Process monitor utility",
        "code": '''#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <signal.h>
#include <string.h>

volatile sig_atomic_t keep_running = 1;

void signal_handler(int sig) {
    keep_running = 0;
}

void print_process_info(pid_t pid, const char* command) {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    
    printf("[%ld.%06ld] Process %d (%s) ", 
           tv.tv_sec, tv.tv_usec, pid, command);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <command> [args...]\\n", argv[0]);
        return 1;
    }
    
    signal(SIGINT, signal_handler);
    
    pid_t pid = fork();
    
    if (pid == -1) {
        perror("fork failed");
        return 1;
    }
    
    if (pid == 0) {
        // Child process - execute the command
        execvp(argv[1], &argv[1]);
        perror("execvp failed");
        return 1;
    } else {
        // Parent process - monitor the child
        print_process_info(pid, argv[1]);
        printf("started\\n");
        
        int status;
        struct timeval start_time, end_time;
        gettimeofday(&start_time, NULL);
        
        // Monitor process
        while (keep_running) {
            pid_t result = waitpid(pid, &status, WNOHANG);
            
            if (result == pid) {
                // Process has terminated
                gettimeofday(&end_time, NULL);
                
                double elapsed = (end_time.tv_sec - start_time.tv_sec) + 
                               (end_time.tv_usec - start_time.tv_usec) / 1000000.0;
                
                print_process_info(pid, argv[1]);
                
                if (WIFEXITED(status)) {
                    printf("exited with status %d after %.3f seconds\\n", 
                           WEXITSTATUS(status), elapsed);
                } else if (WIFSIGNALED(status)) {
                    printf("terminated by signal %d after %.3f seconds\\n", 
                           WTERMSIG(status), elapsed);
                }
                break;
            } else if (result == -1) {
                perror("waitpid failed");
                break;
            }
            
            // Sleep for a short time before checking again
            usleep(100000); // 100ms
        }
        
        if (!keep_running) {
            // Interrupted by signal, kill child process
            kill(pid, SIGTERM);
            waitpid(pid, &status, 0);
            print_process_info(pid, argv[1]);
            printf("terminated by user\\n");
        }
    }
    
    return 0;
}'''
    }
]

def create_solution_file(solution):
    """Create a C file for a single solution"""
    file_path = os.path.join(BASE_DIR, solution["path"])
    
    # Create directory if it doesn't exist
    os.makedirs(os.path.dirname(file_path), exist_ok=True)
    
    # Create the file content
    content = f'''/**
 * {solution["title"]}
 * {solution["week"]}
 * 
 * Description: {solution["description"]}
 */

{solution["code"]}'''
    
    # Write the file
    with open(file_path, 'w') as f:
        f.write(content)
    
    print(f"Created: {file_path}")

def main():
    """Generate all remaining solution files"""
    print("Generating remaining C solution files...")
    
    for solution in remaining_solutions:
        create_solution_file(solution)
    
    print(f"\nGenerated {len(remaining_solutions)} additional solution files!")
    
    # Show directory structure
    print("\nDirectory structure created:")
    for root, dirs, files in os.walk(BASE_DIR):
        level = root.replace(BASE_DIR, '').count(os.sep)
        indent = ' ' * 2 * level
        print(f"{indent}{os.path.basename(root)}/")
        subindent = ' ' * 2 * (level + 1)
        for file in files:
            if file.endswith('.c'):
                print(f"{subindent}{file}")

if __name__ == "__main__":
    main()
