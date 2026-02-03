/**
 * LibraryApp.java - Main application class
 * 
 * This demonstrates a complete multi-file Java project with:
 * - Package structure (com.example.library)
 * - Model classes (Book, Member)
 * - Service class (LibraryService)
 * - Utility class (ValidationUtil)
 * - Main application class
 */

package com.example.library.main;

import com.example.library.model.Book;
import com.example.library.model.Member;
import com.example.library.service.LibraryService;

public class LibraryApp {
    public static void main(String[] args) {
        System.out.println("=== LIBRARY MANAGEMENT SYSTEM ===\n");
        
        // Create library service
        LibraryService library = new LibraryService();
        
        // Add books
        System.out.println("--- Adding Books ---");
        library.addBook("978-0134685991", "Effective Java", "Joshua Bloch", 2018);
        library.addBook("978-0596009205", "Head First Java", "Kathy Sierra", 2005);
        library.addBook("978-0132350884", "Clean Code", "Robert C. Martin", 2008);
        library.addBook("978-0201633610", "Design Patterns", "Gang of Four", 1994);
        
        // Add members
        System.out.println("\n--- Adding Members ---");
        library.addMember("M001", "Alice Johnson", "alice@example.com");
        library.addMember("M002", "Bob Smith", "bob@example.com");
        library.addMember("M003", "Charlie Brown", "charlie@example.com");
        
        // Display all books
        System.out.println("\n--- All Books ---");
        for (Book book : library.getAllBooks()) {
            System.out.println(book);
        }
        
        // Search books
        System.out.println("\n--- Searching Books ---");
        System.out.println("Books with 'Java' in title:");
        for (Book book : library.searchBooksByTitle("Java")) {
            System.out.println("  - " + book.getTitle());
        }
        
        System.out.println("\nBooks by 'Joshua Bloch':");
        for (Book book : library.searchBooksByAuthor("Joshua")) {
            System.out.println("  - " + book.getTitle());
        }
        
        // Borrow books
        System.out.println("\n--- Borrowing Books ---");
        library.borrowBook("M001", "978-0134685991");
        library.borrowBook("M001", "978-0596009205");
        library.borrowBook("M002", "978-0132350884");
        
        // Display members
        System.out.println("\n--- All Members ---");
        for (Member member : library.getAllMembers()) {
            System.out.println(member);
            System.out.println("  Borrowed books:");
            for (String isbn : member.getBorrowedBooks()) {
                Book book = library.findBook(isbn);
                if (book != null) {
                    System.out.println("    - " + book.getTitle());
                }
            }
        }
        
        // Return a book
        System.out.println("\n--- Returning Books ---");
        library.returnBook("M001", "978-0134685991");
        
        // Statistics
        System.out.println("\n--- Statistics ---");
        System.out.println("Total books: " + library.getTotalBooks());
        System.out.println("Available books: " + library.getAvailableBooks());
        System.out.println("Total members: " + library.getTotalMembers());
        
        System.out.println("\n=== PROJECT STRUCTURE ===");
        System.out.println("com.example.library/");
        System.out.println("  ├── model/");
        System.out.println("  │   ├── Book.java");
        System.out.println("  │   └── Member.java");
        System.out.println("  ├── service/");
        System.out.println("  │   └── LibraryService.java");
        System.out.println("  ├── util/");
        System.out.println("  │   └── ValidationUtil.java");
        System.out.println("  └── main/");
        System.out.println("      └── LibraryApp.java");
    }
}

