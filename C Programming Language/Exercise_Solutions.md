# Complete Exercise Solutions
## C Programming Curriculum - All Levels

---

## BEGINNER LEVEL SOLUTIONS

### Week 1 Solutions

**Solution 1.1: Personal Hello World**
```c
#include <stdio.h>

int main() {
    printf("Hello, my name is [Student Name]!\n");
    printf("I am learning C programming.\n");
    return 0;
}
```

**Solution 1.2: Asterisk Pattern**
```c
#include <stdio.h>

int main() {
    printf("*****\n");
    printf("*   *\n");
    printf("*   *\n");
    printf("*   *\n");
    printf("*****\n");
    return 0;
}
```

**Solution 1.3: Numbers 1-10**
```c
#include <stdio.h>

int main() {
    printf("Numbers from 1 to 10:\n");
    for(int i = 1; i <= 10; i++) {
        printf("%d\n", i);
    }
    return 0;
}
```

### Week 2 Solutions

**Solution 2.1: Rectangle Area Calculator**
```c
#include <stdio.h>

int main() {
    float length, width, area;
    
    printf("Enter the length of rectangle: ");
    scanf("%f", &length);
    
    printf("Enter the width of rectangle: ");
    scanf("%f", &width);
    
    area = length * width;
    
    printf("Area of rectangle = %.2f square units\n", area);
    
    return 0;
}
```

**Solution 2.2: Temperature Converter**
```c
#include <stdio.h>

int main() {
    float fahrenheit, celsius;
    
    printf("Enter temperature in Fahrenheit: ");
    scanf("%f", &fahrenheit);
    
    celsius = (fahrenheit - 32) * 5.0 / 9.0;
    
    printf("%.2f°F = %.2f°C\n", fahrenheit, celsius);
    
    return 0;
}
```

**Solution 2.3: Simple Interest Calculator**
```c
#include <stdio.h>

int main() {
    float principal, rate, time, interest;
    
    printf("Enter principal amount: $");
    scanf("%f", &principal);
    
    printf("Enter rate of interest: ");
    scanf("%f", &rate);
    
    printf("Enter time period (years): ");
    scanf("%f", &time);
    
    interest = (principal * rate * time) / 100;
    
    printf("Simple Interest = $%.2f\n", interest);
    printf("Total Amount = $%.2f\n", principal + interest);
    
    return 0;
}
```

**Solution 2.4: Swap Numbers Without Third Variable**
```c
#include <stdio.h>

int main() {
    int a, b;
    
    printf("Enter two numbers: ");
    scanf("%d %d", &a, &b);
    
    printf("Before swapping: a = %d, b = %d\n", a, b);
    
    // Swapping without third variable
    a = a + b;
    b = a - b;
    a = a - b;
    
    printf("After swapping: a = %d, b = %d\n", a, b);
    
    return 0;
}
```

### Week 3 Solutions

**Solution 3.1: Even or Odd Checker**
```c
#include <stdio.h>

int main() {
    int number;
    
    printf("Enter a number: ");
    scanf("%d", &number);
    
    if (number % 2 == 0) {
        printf("%d is even.\n", number);
    } else {
        printf("%d is odd.\n", number);
    }
    
    return 0;
}
```

**Solution 3.2: Largest of Three Numbers**
```c
#include <stdio.h>

int main() {
    int a, b, c, largest;
    
    printf("Enter three numbers: ");
    scanf("%d %d %d", &a, &b, &c);
    
    if (a >= b && a >= c) {
        largest = a;
    } else if (b >= a && b >= c) {
        largest = b;
    } else {
        largest = c;
    }
    
    printf("The largest number is: %d\n", largest);
    
    return 0;
}
```

**Solution 3.3: Simple Calculator**
```c
#include <stdio.h>

int main() {
    float num1, num2, result;
    char operator;
    
    printf("Enter first number: ");
    scanf("%f", &num1);
    
    printf("Enter operator (+, -, *, /): ");
    scanf(" %c", &operator);
    
    printf("Enter second number: ");
    scanf("%f", &num2);
    
    switch(operator) {
        case '+':
            result = num1 + num2;
            printf("%.2f + %.2f = %.2f\n", num1, num2, result);
            break;
        case '-':
            result = num1 - num2;
            printf("%.2f - %.2f = %.2f\n", num1, num2, result);
            break;
        case '*':
            result = num1 * num2;
            printf("%.2f * %.2f = %.2f\n", num1, num2, result);
            break;
        case '/':
            if (num2 != 0) {
                result = num1 / num2;
                printf("%.2f / %.2f = %.2f\n", num1, num2, result);
            } else {
                printf("Error: Division by zero!\n");
            }
            break;
        default:
            printf("Error: Invalid operator!\n");
    }
    
    return 0;
}
```

**Solution 3.4: Multiplication Table**
```c
#include <stdio.h>

int main() {
    int number;
    
    printf("Enter a number: ");
    scanf("%d", &number);
    
    printf("Multiplication table of %d:\n", number);
    for (int i = 1; i <= 10; i++) {
        printf("%d x %d = %d\n", number, i, number * i);
    }
    
    return 0;
}
```

### Week 4 Solutions

**Solution 4.1: Fibonacci Series**
```c
#include <stdio.h>

int main() {
    int n, first = 0, second = 1, next;
    
    printf("Enter number of terms: ");
    scanf("%d", &n);
    
    printf("Fibonacci Series: ");
    
    if (n >= 1) {
        printf("%d ", first);
    }
    if (n >= 2) {
        printf("%d ", second);
    }
    
    for (int i = 3; i <= n; i++) {
        next = first + second;
        printf("%d ", next);
        first = second;
        second = next;
    }
    printf("\n");
    
    return 0;
}
```

**Solution 4.2: Factorial Calculator**
```c
#include <stdio.h>

int main() {
    int number;
    long long factorial = 1;
    
    printf("Enter a number: ");
    scanf("%d", &number);
    
    if (number < 0) {
        printf("Factorial is not defined for negative numbers.\n");
    } else {
        for (int i = 1; i <= number; i++) {
            factorial *= i;
        }
        printf("Factorial of %d = %lld\n", number, factorial);
    }
    
    return 0;
}
```

**Solution 4.3: Palindrome Checker**
```c
#include <stdio.h>

int main() {
    int number, original, reversed = 0, remainder;
    
    printf("Enter a number: ");
    scanf("%d", &number);
    
    original = number;
    
    while (number != 0) {
        remainder = number % 10;
        reversed = reversed * 10 + remainder;
        number /= 10;
    }
    
    if (original == reversed) {
        printf("%d is a palindrome.\n", original);
    } else {
        printf("%d is not a palindrome.\n", original);
    }
    
    return 0;
}
```

**Solution 4.4: Prime Numbers 1-100**
```c
#include <stdio.h>

int main() {
    int isPrime;
    
    printf("Prime numbers between 1 and 100:\n");
    
    for (int num = 2; num <= 100; num++) {
        isPrime = 1;  // Assume number is prime
        
        for (int i = 2; i * i <= num; i++) {
            if (num % i == 0) {
                isPrime = 0;  // Number is not prime
                break;
            }
        }
        
        if (isPrime) {
            printf("%d ", num);
        }
    }
    printf("\n");
    
    return 0;
}
```

---

## INTERMEDIATE LEVEL SOLUTIONS

### Week 5 Solutions

**Solution 5.1: Prime Number Function**
```c
#include <stdio.h>

int isPrime(int n) {
    if (n <= 1) {
        return 0;  // Not prime
    }
    
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            return 0;  // Not prime
        }
    }
    
    return 1;  // Prime
}

int main() {
    int number;
    
    printf("Enter a number: ");
    scanf("%d", &number);
    
    if (isPrime(number)) {
        printf("%d is a prime number.\n", number);
    } else {
        printf("%d is not a prime number.\n", number);
    }
    
    return 0;
}
```

**Solution 5.2: Recursive Fibonacci**
```c
#include <stdio.h>

int fibonacci(int n) {
    if (n <= 1) {
        return n;
    }
    return fibonacci(n - 1) + fibonacci(n - 2);
}

int main() {
    int terms;
    
    printf("Enter number of terms: ");
    scanf("%d", &terms);
    
    printf("Fibonacci Series: ");
    for (int i = 0; i < terms; i++) {
        printf("%d ", fibonacci(i));
    }
    printf("\n");
    
    return 0;
}
```

**Solution 5.3: Recursive Power Function**
```c
#include <stdio.h>

double power(double base, int exponent) {
    if (exponent == 0) {
        return 1;
    } else if (exponent > 0) {
        return base * power(base, exponent - 1);
    } else {
        return 1 / power(base, -exponent);
    }
}

int main() {
    double base;
    int exponent;
    
    printf("Enter base: ");
    scanf("%lf", &base);
    
    printf("Enter exponent: ");
    scanf("%d", &exponent);
    
    printf("%.2f^%d = %.2f\n", base, exponent, power(base, exponent));
    
    return 0;
}
```

**Solution 5.4: Number Reverser Function**
```c
#include <stdio.h>

int reverseNumber(int num) {
    int reversed = 0;
    
    while (num != 0) {
        reversed = reversed * 10 + num % 10;
        num /= 10;
    }
    
    return reversed;
}

int main() {
    int number;
    
    printf("Enter a number: ");
    scanf("%d", &number);
    
    printf("Reversed number: %d\n", reverseNumber(number));
    
    return 0;
}
```

### Week 6 Solutions

**Solution 6.1: Largest Element in Array**
```c
#include <stdio.h>

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
    
    printf("Largest element: %d\n", largest);
    
    return 0;
}
```

**Solution 6.2: Array Reverser**
```c
#include <stdio.h>

void printArray(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
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
}
```

**Solution 6.3: Vowel Counter**
```c
#include <stdio.h>
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
    str[strcspn(str, "\n")] = '\0';
    
    int vowels = countVowels(str);
    
    printf("Number of vowels: %d\n", vowels);
    
    return 0;
}
```

**Solution 6.4: Bubble Sort**
```c
#include <stdio.h>

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
    printf("\n");
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
}
```

### Week 7 Solutions

**Solution 7.1: Maximum Using Pointers**
```c
#include <stdio.h>

int findMax(int *a, int *b) {
    return (*a > *b) ? *a : *b;
}

int main() {
    int num1, num2;
    
    printf("Enter two numbers: ");
    scanf("%d %d", &num1, &num2);
    
    int max = findMax(&num1, &num2);
    
    printf("Maximum of %d and %d is: %d\n", num1, num2, max);
    
    return 0;
}
```

**Solution 7.2: String Length Using Pointers**
```c
#include <stdio.h>

int stringLength(char *str) {
    int length = 0;
    
    while (*str != '\0') {
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
    if (str[stringLength(str) - 1] == '\n') {
        str[stringLength(str) - 1] = '\0';
    }
    
    printf("Length of string: %d\n", stringLength(str));
    
    return 0;
}
```

**Solution 7.3: String Reverser Using Pointers**
```c
#include <stdio.h>
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
    str[strcspn(str, "\n")] = '\0';
    
    printf("Original string: %s\n", str);
    
    reverseString(str);
    
    printf("Reversed string: %s\n", str);
    
    return 0;
}
```

**Solution 7.4: Array Sort Using Pointers**
```c
#include <stdio.h>

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
    printf("\n");
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
}
```

### Week 8 Solutions

**Solution 8.1: Matrix Multiplication**
```c
#include <stdio.h>

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
        printf("\n");
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
        printf("Matrix multiplication not possible!\n");
        return 1;
    }
    
    printf("Enter elements of first matrix:\n");
    for (int i = 0; i < r1; i++) {
        for (int j = 0; j < c1; j++) {
            scanf("%d", &first[i][j]);
        }
    }
    
    printf("Enter elements of second matrix:\n");
    for (int i = 0; i < r2; i++) {
        for (int j = 0; j < c2; j++) {
            scanf("%d", &second[i][j]);
        }
    }
    
    multiplyMatrices(first, second, result, r1, c1, r2, c2);
    
    printf("Result matrix:\n");
    printMatrix(result, r1, c2);
    
    return 0;
}
```

**Solution 8.2: Word Count with Command Line Arguments**
```c
#include <stdio.h>
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
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }
    
    FILE *file = fopen(argv[1], "r");
    if (file == NULL) {
        printf("Error: Cannot open file '%s'\n", argv[1]);
        return 1;
    }
    
    int wordCount = countWords(file);
    fclose(file);
    
    printf("File '%s' contains %d words.\n", argv[1], wordCount);
    
    return 0;
}
```

**Solution 8.3: String Tokenizer**
```c
#include <stdio.h>
#include <string.h>

void tokenizeString(char *str, char delimiter) {
    char *token = strtok(str, &delimiter);
    int count = 0;
    
    printf("Tokens:\n");
    while (token != NULL) {
        count++;
        printf("%d: %s\n", count, token);
        token = strtok(NULL, &delimiter);
    }
    
    printf("Total tokens: %d\n", count);
}

int main() {
    char str[200];
    char delimiter;
    
    printf("Enter a string: ");
    fgets(str, sizeof(str), stdin);
    
    // Remove newline character
    str[strcspn(str, "\n")] = '\0';
    
    printf("Enter delimiter: ");
    scanf("%c", &delimiter);
    
    tokenizeString(str, delimiter);
    
    return 0;
}
```

**Solution 8.4: Tic-Tac-Toe Game**
```c
#include <stdio.h>

char board[3][3];

void initializeBoard() {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            board[i][j] = ' ';
        }
    }
}

void printBoard() {
    printf("\n");
    for (int i = 0; i < 3; i++) {
        printf(" %c | %c | %c \n", board[i][0], board[i][1], board[i][2]);
        if (i < 2) {
            printf("---|---|---\n");
        }
    }
    printf("\n");
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
    
    printf("Tic-Tac-Toe Game\n");
    printf("Players take turns. Enter row (0-2) and column (0-2).\n");
    
    while (1) {
        printBoard();
        
        printf("Player %c, enter your move (row col): ", currentPlayer);
        scanf("%d %d", &row, &col);
        
        if (row < 0 || row > 2 || col < 0 || col > 2 || board[row][col] != ' ') {
            printf("Invalid move! Try again.\n");
            continue;
        }
        
        board[row][col] = currentPlayer;
        
        if (checkWin()) {
            printBoard();
            printf("Player %c wins!\n", currentPlayer);
            break;
        }
        
        if (isBoardFull()) {
            printBoard();
            printf("It's a draw!\n");
            break;
        }
        
        currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
    }
    
    return 0;
}
```

---

## ADVANCED LEVEL SOLUTIONS

### Week 9 Solutions

**Solution 9.1: Student Management System**
```c
#include <stdio.h>
#include <string.h>

#define MAX_STUDENTS 100

struct Student {
    int id;
    char name[50];
    int age;
    float gpa;
};

struct Student students[MAX_STUDENTS];
int studentCount = 0;

void addStudent() {
    if (studentCount >= MAX_STUDENTS) {
        printf("Cannot add more students. Database full!\n");
        return;
    }
    
    struct Student *s = &students[studentCount];
    
    printf("Enter student ID: ");
    scanf("%d", &s->id);
    
    printf("Enter student name: ");
    scanf("%s", s->name);
    
    printf("Enter student age: ");
    scanf("%d", &s->age);
    
    printf("Enter student GPA: ");
    scanf("%f", &s->gpa);
    
    studentCount++;
    printf("Student added successfully!\n");
}

void displayStudents() {
    if (studentCount == 0) {
        printf("No students in database.\n");
        return;
    }
    
    printf("\n--- Student Database ---\n");
    printf("ID\tName\t\tAge\tGPA\n");
    printf("--------------------------------\n");
    
    for (int i = 0; i < studentCount; i++) {
        printf("%d\t%-15s\t%d\t%.2f\n", 
               students[i].id, students[i].name, 
               students[i].age, students[i].gpa);
    }
}

void searchStudent() {
    int id;
    printf("Enter student ID to search: ");
    scanf("%d", &id);
    
    for (int i = 0; i < studentCount; i++) {
        if (students[i].id == id) {
            printf("Student found:\n");
            printf("ID: %d\n", students[i].id);
            printf("Name: %s\n", students[i].name);
            printf("Age: %d\n", students[i].age);
            printf("GPA: %.2f\n", students[i].gpa);
            return;
        }
    }
    
    printf("Student with ID %d not found.\n", id);
}

int main() {
    int choice;
    
    while (1) {
        printf("\n--- Student Management System ---\n");
        printf("1. Add Student\n");
        printf("2. Display All Students\n");
        printf("3. Search Student\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                addStudent();
                break;
            case 2:
                displayStudents();
                break;
            case 3:
                searchStudent();
                break;
            case 4:
                printf("Goodbye!\n");
                return 0;
            default:
                printf("Invalid choice!\n");
        }
    }
}
```

**Solution 9.2: Library Book Management System**
```c
#include <stdio.h>
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
        printf("Library is full!\n");
        return;
    }
    
    struct Book *b = &library[bookCount];
    
    printf("Enter book ID: ");
    scanf("%d", &b->id);
    
    printf("Enter book title: ");
    getchar(); // consume newline
    fgets(b->title, sizeof(b->title), stdin);
    b->title[strcspn(b->title, "\n")] = '\0'; // remove newline
    
    printf("Enter author name: ");
    fgets(b->author, sizeof(b->author), stdin);
    b->author[strcspn(b->author, "\n")] = '\0'; // remove newline
    
    printf("Enter publication year: ");
    scanf("%d", &b->year);
    
    printf("Enter price: ");
    scanf("%f", &b->price);
    
    b->isAvailable = 1; // Book is available by default
    
    bookCount++;
    printf("Book added successfully!\n");
}

void displayBooks() {
    if (bookCount == 0) {
        printf("No books in library.\n");
        return;
    }
    
    printf("\n--- Library Catalog ---\n");
    printf("ID\tTitle\t\t\tAuthor\t\tYear\tPrice\tStatus\n");
    printf("-----------------------------------------------------------------------\n");
    
    for (int i = 0; i < bookCount; i++) {
        printf("%d\t%-20s\t%-15s\t%d\t%.2f\t%s\n",
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
                printf("Book '%s' borrowed successfully!\n", library[i].title);
            } else {
                printf("Book is already borrowed!\n");
            }
            return;
        }
    }
    
    printf("Book with ID %d not found.\n", id);
}

void returnBook() {
    int id;
    printf("Enter book ID to return: ");
    scanf("%d", &id);
    
    for (int i = 0; i < bookCount; i++) {
        if (library[i].id == id) {
            if (!library[i].isAvailable) {
                library[i].isAvailable = 1;
                printf("Book '%s' returned successfully!\n", library[i].title);
            } else {
                printf("Book is already available!\n");
            }
            return;
        }
    }
    
    printf("Book with ID %d not found.\n", id);
}

int main() {
    int choice;
    
    while (1) {
        printf("\n--- Library Management System ---\n");
        printf("1. Add Book\n");
        printf("2. Display All Books\n");
        printf("3. Borrow Book\n");
        printf("4. Return Book\n");
        printf("5. Exit\n");
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
                printf("Goodbye!\n");
                return 0;
            default:
                printf("Invalid choice!\n");
        }
    }
}
```

### Week 10 Solutions

**Solution 10.1: File Copying Utility**
```c
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s <source_file> <destination_file>\n", argv[0]);
        return 1;
    }
    
    FILE *source = fopen(argv[1], "rb");
    if (source == NULL) {
        printf("Error: Cannot open source file '%s'\n", argv[1]);
        return 1;
    }
    
    FILE *destination = fopen(argv[2], "wb");
    if (destination == NULL) {
        printf("Error: Cannot create destination file '%s'\n", argv[2]);
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
    
    printf("File copied successfully!\n");
    printf("Bytes copied: %ld\n", bytescopied);
    
    return 0;
}
```

**Solution 10.2: Word Frequency Counter**
```c
#include <stdio.h>
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
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }
    
    FILE *file = fopen(argv[1], "r");
    if (file == NULL) {
        printf("Error: Cannot open file '%s'\n", argv[1]);
        return 1;
    }
    
    char word[MAX_WORD_LENGTH];
    
    while (fscanf(file, "%49s", word) == 1) {
        // Remove punctuation
        int len = strlen(word);
        while (len > 0 && !isalnum(word[len-1])) {
            word[len-1] = '\0';
            len--;
        }
        
        if (len > 0) {
            addWord(word);
        }
    }
    
    fclose(file);
    
    printf("Word Frequency Report\n");
    printf("=====================\n");
    
    for (int i = 0; i < wordCount; i++) {
        printf("%-20s: %d\n", wordList[i].word, wordList[i].count);
    }
    
    printf("\nTotal unique words: %d\n", wordCount);
    
    return 0;
}
```

### Week 11 Solutions

**Solution 11.1: Dynamic String Manipulation**
```c
#include <stdio.h>
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
        printf("Memory allocation failed!\n");
        return 1;
    }
    
    printf("String 1: %s\n", str1);
    printf("String 2: %s\n", str2);
    
    char* combined = concatenateStrings(str1, str2);
    if (combined != NULL) {
        printf("Combined: %s\n", combined);
    }
    
    // Resize string to accommodate more text
    str1 = resizeString(str1, 100);
    if (str1 != NULL) {
        strcat(str1, " from C!");
        printf("Extended string 1: %s\n", str1);
    }
    
    // Free allocated memory
    free(str1);
    free(str2);
    free(combined);
    
    printf("Memory freed successfully!\n");
    
    return 0;
}
```

**Solution 11.2: Resizable Array Implementation**
```c
#include <stdio.h>
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
        printf("Array is NULL\n");
        return;
    }
    
    printf("Array (size: %d, capacity: %d): [", arr->size, arr->capacity);
    for (int i = 0; i < arr->size; i++) {
        printf("%d", arr->data[i]);
        if (i < arr->size - 1) {
            printf(", ");
        }
    }
    printf("]\n");
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
        printf("Failed to create array!\n");
        return 1;
    }
    
    // Add elements
    for (int i = 1; i <= 10; i++) {
        append(arr, i * 10);
        printArray(arr);
    }
    
    // Manually resize
    printf("\nResizing to capacity 5...\n");
    resize(arr, 5);
    printArray(arr);
    
    freeArray(arr);
    printf("Array freed successfully!\n");
    
    return 0;
}
```

---

## EXPERT LEVEL SOLUTIONS

### Week 13 Solutions

**Solution 13.1: File Copy Using System Calls**
```c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <errno.h>
#include <string.h>

#define BUFFER_SIZE 4096

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <source> <destination>\n", argv[0]);
        return 1;
    }
    
    int src_fd = open(argv[1], O_RDONLY);
    if (src_fd == -1) {
        fprintf(stderr, "Error opening source file '%s': %s\n", 
                argv[1], strerror(errno));
        return 1;
    }
    
    struct stat src_stat;
    if (fstat(src_fd, &src_stat) == -1) {
        fprintf(stderr, "Error getting source file stats: %s\n", strerror(errno));
        close(src_fd);
        return 1;
    }
    
    int dst_fd = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, src_stat.st_mode);
    if (dst_fd == -1) {
        fprintf(stderr, "Error creating destination file '%s': %s\n", 
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
            fprintf(stderr, "Error writing to destination file: %s\n", 
                    strerror(errno));
            close(src_fd);
            close(dst_fd);
            return 1;
        }
        total_bytes += bytes_written;
    }
    
    if (bytes_read == -1) {
        fprintf(stderr, "Error reading from source file: %s\n", strerror(errno));
        close(src_fd);
        close(dst_fd);
        return 1;
    }
    
    close(src_fd);
    close(dst_fd);
    
    printf("Successfully copied %ld bytes from '%s' to '%s'\n", 
           total_bytes, argv[1], argv[2]);
    
    return 0;
}
```

**Solution 13.2: Process Monitor Utility**
```c
#include <stdio.h>
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
        fprintf(stderr, "Usage: %s <command> [args...]\n", argv[0]);
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
        printf("started\n");
        
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
                    printf("exited with status %d after %.3f seconds\n", 
                           WEXITSTATUS(status), elapsed);
                } else if (WIFSIGNALED(status)) {
                    printf("terminated by signal %d after %.3f seconds\n", 
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
            printf("terminated by user\n");
        }
    }
    
    return 0;
}
```

### Week 14 Solutions

**Solution 14.1: Memory Pool Allocator with Debugging**
```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define POOL_SIZE 4096
#define MAGIC_NUMBER 0xDEADBEEF

struct BlockHeader {
    size_t size;
    uint32_t magic;
    int is_free;
    struct BlockHeader* next;
};

struct MemoryPool {
    char* pool;
    struct BlockHeader* free_list;
    size_t total_size;
    size_t used_size;
    int allocation_count;
};

struct MemoryPool* create_pool(size_t size) {
    struct MemoryPool* pool = malloc(sizeof(struct MemoryPool));
    if (!pool) return NULL;
    
    pool->pool = malloc(size);
    if (!pool->pool) {
        free(pool);
        return NULL;
    }
    
    pool->total_size = size;
    pool->used_size = 0;
    pool->allocation_count = 0;
    
    // Initialize free list with entire pool
    pool->free_list = (struct BlockHeader*)pool->pool;
    pool->free_list->size = size - sizeof(struct BlockHeader);
    pool->free_list->magic = MAGIC_NUMBER;
    pool->free_list->is_free = 1;
    pool->free_list->next = NULL;
    
    return pool;
}

void* pool_alloc(struct MemoryPool* pool, size_t size) {
    if (!pool || size == 0) return NULL;
    
    // Align size to 8 bytes
    size = (size + 7) & ~7;
    
    struct BlockHeader* current = pool->free_list;
    struct BlockHeader* prev = NULL;
    
    while (current) {
        if (current->is_free && current->size >= size) {
            // Found suitable block
            if (current->size > size + sizeof(struct BlockHeader)) {
                // Split block
                struct BlockHeader* new_block = 
                    (struct BlockHeader*)((char*)current + sizeof(struct BlockHeader) + size);
                new_block->size = current->size - size - sizeof(struct BlockHeader);
                new_block->magic = MAGIC_NUMBER;
                new_block->is_free = 1;
                new_block->next = current->next;
                
                current->size = size;
                current->next = new_block;
            }
            
            current->is_free = 0;
            pool->used_size += current->size + sizeof(struct BlockHeader);
            pool->allocation_count++;
            
            return (char*)current + sizeof(struct BlockHeader);
        }
        
        prev = current;
        current = current->next;
    }
    
    return NULL; // No suitable block found
}

void pool_free(struct MemoryPool* pool, void* ptr) {
    if (!pool || !ptr) return;
    
    struct BlockHeader* header = 
        (struct BlockHeader*)((char*)ptr - sizeof(struct BlockHeader));
    
    if (header->magic != MAGIC_NUMBER) {
        printf("ERROR: Invalid magic number! Possible corruption or invalid pointer.\n");
        return;
    }
    
    if (header->is_free) {
        printf("WARNING: Double free detected!\n");
        return;
    }
    
    header->is_free = 1;
    pool->used_size -= header->size + sizeof(struct BlockHeader);
    pool->allocation_count--;
    
    // Coalesce adjacent free blocks
    struct BlockHeader* current = pool->free_list;
    while (current && current->next) {
        if (current->is_free && current->next->is_free) {
            struct BlockHeader* next = current->next;
            if ((char*)current + sizeof(struct BlockHeader) + current->size == (char*)next) {
                current->size += next->size + sizeof(struct BlockHeader);
                current->next = next->next;
                continue;
            }
        }
        current = current->next;
    }
}

void print_pool_stats(struct MemoryPool* pool) {
    if (!pool) return;
    
    printf("\n--- Memory Pool Statistics ---\n");
    printf("Total size: %zu bytes\n", pool->total_size);
    printf("Used size: %zu bytes\n", pool->used_size);
    printf("Free size: %zu bytes\n", pool->total_size - pool->used_size);
    printf("Active allocations: %d\n", pool->allocation_count);
    printf("Fragmentation: %.2f%%\n", 
           (double)pool->used_size / pool->total_size * 100);
    
    printf("\nBlock list:\n");
    struct BlockHeader* current = pool->free_list;
    int block_num = 0;
    
    while (current) {
        printf("Block %d: size=%zu, %s\n", 
               block_num++, current->size, 
               current->is_free ? "FREE" : "USED");
        current = current->next;
    }
}

void destroy_pool(struct MemoryPool* pool) {
    if (pool) {
        if (pool->allocation_count > 0) {
            printf("WARNING: Destroying pool with %d active allocations!\n", 
                   pool->allocation_count);
        }
        free(pool->pool);
        free(pool);
    }
}

int main() {
    struct MemoryPool* pool = create_pool(POOL_SIZE);
    if (!pool) {
        printf("Failed to create memory pool!\n");
        return 1;
    }
    
    printf("Memory pool created successfully!\n");
    print_pool_stats(pool);
    
    // Test allocations
    void* ptr1 = pool_alloc(pool, 100);
    void* ptr2 = pool_alloc(pool, 200);
    void* ptr3 = pool_alloc(pool, 50);
    
    printf("\nAfter allocations:\n");
    print_pool_stats(pool);
    
    // Test free
    pool_free(pool, ptr2);
    
    printf("\nAfter freeing middle block:\n");
    print_pool_stats(pool);
    
    // Test allocation in freed space
    void* ptr4 = pool_alloc(pool, 150);
    
    printf("\nAfter reallocating:\n");
    print_pool_stats(pool);
    
    // Clean up
    pool_free(pool, ptr1);
    pool_free(pool, ptr3);
    pool_free(pool, ptr4);
    
    printf("\nAfter freeing all:\n");
    print_pool_stats(pool);
    
    destroy_pool(pool);
    
    return 0;
}
```

This comprehensive solution set covers all exercises from beginner to expert level, providing detailed implementations that demonstrate proper C programming techniques, memory management, error handling, and system programming concepts. Each solution includes proper error checking, clear comments, and follows good coding practices.
