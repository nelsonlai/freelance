#!/usr/bin/env python3
"""
Script to generate individual C files for all exercise solutions
Based on the Exercise_Solutions.md file
"""

import os
import re

# Base directory for solutions
BASE_DIR = "/Users/nelsonlai/sources/freelance/The C Programming Language/solutions"

# Solution data extracted from Exercise_Solutions.md
solutions = [
    # Week 6 Solutions
    {
        "path": "intermediate/week6/solution_6_1_largest_element.c",
        "title": "Solution 6.1: Largest Element in Array",
        "week": "Week 6 - Arrays and String Basics",
        "description": "Find the largest element in an array",
        "code": '''#include <stdio.h>

int main() {
    int n, largest;
    
    printf("Enter number of elements: ");
    scanf("%d", &n);
    
    int arr[n];
    
    printf("Enter %d elements: ", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }
    
    largest = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] > largest) {
            largest = arr[i];
        }
    }
    
    printf("Largest element: %d\\n", largest);
    
    return 0;
}'''
    },
    {
        "path": "intermediate/week6/solution_6_2_array_reverser.c",
        "title": "Solution 6.2: Array Reverser",
        "week": "Week 6 - Arrays and String Basics",
        "description": "Reverse an array",
        "code": '''#include <stdio.h>

void printArray(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
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
    
    // Reverse the array
    for (int i = 0; i < n/2; i++) {
        int temp = arr[i];
        arr[i] = arr[n-1-i];
        arr[n-1-i] = temp;
    }
    
    printf("Reversed array: ");
    printArray(arr, n);
    
    return 0;
}'''
    },
    {
        "path": "intermediate/week6/solution_6_3_vowel_counter.c",
        "title": "Solution 6.3: Vowel Counter",
        "week": "Week 6 - Arrays and String Basics",
        "description": "Count vowels in a string",
        "code": '''#include <stdio.h>
#include <string.h>
#include <ctype.h>

int countVowels(char str[]) {
    int count = 0;
    int len = strlen(str);
    
    for (int i = 0; i < len; i++) {
        char ch = tolower(str[i]);
        if (ch == 'a' || ch == 'e' || ch == 'i' || ch == 'o' || ch == 'u') {
            count++;
        }
    }
    
    return count;
}

int main() {
    char str[100];
    
    printf("Enter a string: ");
    fgets(str, sizeof(str), stdin);
    
    // Remove newline character
    str[strcspn(str, "\\n")] = '\\0';
    
    int vowels = countVowels(str);
    
    printf("Number of vowels: %d\\n", vowels);
    
    return 0;
}'''
    },
    {
        "path": "intermediate/week6/solution_6_4_bubble_sort.c",
        "title": "Solution 6.4: Bubble Sort",
        "week": "Week 6 - Arrays and String Basics",
        "description": "Implement bubble sort for an array",
        "code": '''#include <stdio.h>

void bubbleSort(int arr[], int n) {
    for (int i = 0; i < n-1; i++) {
        for (int j = 0; j < n-i-1; j++) {
            if (arr[j] > arr[j+1]) {
                // Swap elements
                int temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
}

void printArray(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
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
    
    bubbleSort(arr, n);
    
    printf("Sorted array: ");
    printArray(arr, n);
    
    return 0;
}'''
    },
    {
        "path": "intermediate/week7/solution_7_1_max_pointers.c",
        "title": "Solution 7.1: Maximum Using Pointers",
        "week": "Week 7 - Pointers Fundamentals",
        "description": "Write a function to find maximum using pointers",
        "code": '''#include <stdio.h>

int findMax(int *a, int *b) {
    return (*a > *b) ? *a : *b;
}

int main() {
    int num1, num2;
    
    printf("Enter two numbers: ");
    scanf("%d %d", &num1, &num2);
    
    int max = findMax(&num1, &num2);
    
    printf("Maximum of %d and %d is: %d\\n", num1, num2, max);
    
    return 0;
}'''
    },
    {
        "path": "intermediate/week7/solution_7_2_string_length_pointers.c",
        "title": "Solution 7.2: String Length Using Pointers",
        "week": "Week 7 - Pointers Fundamentals",
        "description": "Implement string length function using pointers",
        "code": '''#include <stdio.h>

int stringLength(char *str) {
    int length = 0;
    
    while (*str != '\\0') {
        length++;
        str++;
    }
    
    return length;
}

int main() {
    char str[100];
    
    printf("Enter a string: ");
    fgets(str, sizeof(str), stdin);
    
    // Remove newline character
    if (str[stringLength(str) - 1] == '\\n') {
        str[stringLength(str) - 1] = '\\0';
    }
    
    printf("Length of string: %d\\n", stringLength(str));
    
    return 0;
}'''
    },
    {
        "path": "intermediate/week8/solution_8_4_tic_tac_toe.c",
        "title": "Solution 8.4: Tic-Tac-Toe Game",
        "week": "Week 8 - Advanced Arrays and Strings",
        "description": "Tic-tac-toe game using 2D array",
        "code": '''#include <stdio.h>

char board[3][3];

void initializeBoard() {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            board[i][j] = ' ';
        }
    }
}

void printBoard() {
    printf("\\n");
    for (int i = 0; i < 3; i++) {
        printf(" %c | %c | %c \\n", board[i][0], board[i][1], board[i][2]);
        if (i < 2) {
            printf("---|---|---\\n");
        }
    }
    printf("\\n");
}

int checkWin() {
    // Check rows
    for (int i = 0; i < 3; i++) {
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2] && board[i][0] != ' ') {
            return 1;
        }
    }
    
    // Check columns
    for (int j = 0; j < 3; j++) {
        if (board[0][j] == board[1][j] && board[1][j] == board[2][j] && board[0][j] != ' ') {
            return 1;
        }
    }
    
    // Check diagonals
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[0][0] != ' ') {
        return 1;
    }
    if (board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[0][2] != ' ') {
        return 1;
    }
    
    return 0;
}

int isBoardFull() {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == ' ') {
                return 0;
            }
        }
    }
    return 1;
}

int main() {
    int row, col;
    char currentPlayer = 'X';
    
    initializeBoard();
    
    printf("Tic-Tac-Toe Game\\n");
    printf("Players take turns. Enter row (0-2) and column (0-2).\\n");
    
    while (1) {
        printBoard();
        
        printf("Player %c, enter your move (row col): ", currentPlayer);
        scanf("%d %d", &row, &col);
        
        if (row < 0 || row > 2 || col < 0 || col > 2 || board[row][col] != ' ') {
            printf("Invalid move! Try again.\\n");
            continue;
        }
        
        board[row][col] = currentPlayer;
        
        if (checkWin()) {
            printBoard();
            printf("Player %c wins!\\n", currentPlayer);
            break;
        }
        
        if (isBoardFull()) {
            printBoard();
            printf("It's a draw!\\n");
            break;
        }
        
        currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
    }
    
    return 0;
}'''
    },
    {
        "path": "advanced/week10/solution_10_1_file_copy.c",
        "title": "Solution 10.1: File Copying Utility",
        "week": "Week 10 - File Input/Output",
        "description": "File copying utility",
        "code": '''#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s <source_file> <destination_file>\\n", argv[0]);
        return 1;
    }
    
    FILE *source = fopen(argv[1], "rb");
    if (source == NULL) {
        printf("Error: Cannot open source file '%s'\\n", argv[1]);
        return 1;
    }
    
    FILE *destination = fopen(argv[2], "wb");
    if (destination == NULL) {
        printf("Error: Cannot create destination file '%s'\\n", argv[2]);
        fclose(source);
        return 1;
    }
    
    int ch;
    long bytescopied = 0;
    
    while ((ch = fgetc(source)) != EOF) {
        fputc(ch, destination);
        bytescopied++;
    }
    
    fclose(source);
    fclose(destination);
    
    printf("File copied successfully!\\n");
    printf("Bytes copied: %ld\\n", bytescopied);
    
    return 0;
}'''
    },
    {
        "path": "advanced/week11/solution_11_2_dynamic_array.c",
        "title": "Solution 11.2: Resizable Array Implementation",
        "week": "Week 11 - Dynamic Memory Management",
        "description": "Resizable array implementation",
        "code": '''#include <stdio.h>
#include <stdlib.h>

struct DynamicArray {
    int* data;
    int size;
    int capacity;
};

struct DynamicArray* createArray(int initialCapacity) {
    struct DynamicArray* arr = (struct DynamicArray*)malloc(sizeof(struct DynamicArray));
    
    if (arr != NULL) {
        arr->data = (int*)malloc(initialCapacity * sizeof(int));
        if (arr->data != NULL) {
            arr->size = 0;
            arr->capacity = initialCapacity;
        } else {
            free(arr);
            arr = NULL;
        }
    }
    
    return arr;
}

int resize(struct DynamicArray* arr, int newCapacity) {
    if (arr == NULL || newCapacity <= 0) {
        return 0;
    }
    
    int* newData = (int*)realloc(arr->data, newCapacity * sizeof(int));
    if (newData == NULL) {
        return 0; // Reallocation failed
    }
    
    arr->data = newData;
    arr->capacity = newCapacity;
    
    if (arr->size > newCapacity) {
        arr->size = newCapacity;
    }
    
    return 1; // Success
}

int append(struct DynamicArray* arr, int value) {
    if (arr == NULL) {
        return 0;
    }
    
    if (arr->size >= arr->capacity) {
        // Double the capacity
        if (!resize(arr, arr->capacity * 2)) {
            return 0;
        }
    }
    
    arr->data[arr->size] = value;
    arr->size++;
    
    return 1;
}

void printArray(struct DynamicArray* arr) {
    if (arr == NULL) {
        printf("Array is NULL\\n");
        return;
    }
    
    printf("Array (size: %d, capacity: %d): [", arr->size, arr->capacity);
    for (int i = 0; i < arr->size; i++) {
        printf("%d", arr->data[i]);
        if (i < arr->size - 1) {
            printf(", ");
        }
    }
    printf("]\\n");
}

void freeArray(struct DynamicArray* arr) {
    if (arr != NULL) {
        free(arr->data);
        free(arr);
    }
}

int main() {
    struct DynamicArray* arr = createArray(2);
    
    if (arr == NULL) {
        printf("Failed to create array!\\n");
        return 1;
    }
    
    // Add elements
    for (int i = 1; i <= 10; i++) {
        append(arr, i * 10);
        printArray(arr);
    }
    
    // Manually resize
    printf("\\nResizing to capacity 5...\\n");
    resize(arr, 5);
    printArray(arr);
    
    freeArray(arr);
    printf("Array freed successfully!\\n");
    
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
    """Generate all solution files"""
    print("Generating C solution files...")
    
    for solution in solutions:
        create_solution_file(solution)
    
    print(f"\nGenerated {len(solutions)} solution files successfully!")

if __name__ == "__main__":
    main()
