/**
 * Solution 9.2: Library Book Management System
 * Week 9 - Structures and User-Defined Types
 * 
 * Description: Library book management system
 */

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