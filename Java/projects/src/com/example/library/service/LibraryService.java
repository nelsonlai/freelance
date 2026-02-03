/**
 * LibraryService.java - Service class handling business logic
 */

package com.example.library.service;

import com.example.library.model.Book;
import com.example.library.model.Member;
import com.example.library.util.ValidationUtil;
import java.util.*;

public class LibraryService {
    private Map<String, Book> books;  // ISBN -> Book
    private Map<String, Member> members;  // MemberID -> Member
    
    public LibraryService() {
        this.books = new HashMap<>();
        this.members = new HashMap<>();
    }
    
    // Book operations
    public boolean addBook(String isbn, String title, String author, int year) {
        if (!ValidationUtil.isValidIsbn(isbn)) {
            System.out.println("Invalid ISBN format");
            return false;
        }
        
        if (books.containsKey(isbn)) {
            System.out.println("Book with ISBN " + isbn + " already exists");
            return false;
        }
        
        Book book = new Book(isbn, title, author, year);
        books.put(isbn, book);
        System.out.println("Book added: " + title);
        return true;
    }
    
    public Book findBook(String isbn) {
        return books.get(isbn);
    }
    
    public List<Book> searchBooksByTitle(String keyword) {
        List<Book> results = new ArrayList<>();
        String lowerKeyword = keyword.toLowerCase();
        for (Book book : books.values()) {
            if (book.getTitle().toLowerCase().contains(lowerKeyword)) {
                results.add(book);
            }
        }
        return results;
    }
    
    public List<Book> searchBooksByAuthor(String author) {
        List<Book> results = new ArrayList<>();
        String lowerAuthor = author.toLowerCase();
        for (Book book : books.values()) {
            if (book.getAuthor().toLowerCase().contains(lowerAuthor)) {
                results.add(book);
            }
        }
        return results;
    }
    
    public boolean borrowBook(String memberId, String isbn) {
        Member member = members.get(memberId);
        Book book = books.get(isbn);
        
        if (member == null) {
            System.out.println("Member not found");
            return false;
        }
        
        if (book == null) {
            System.out.println("Book not found");
            return false;
        }
        
        if (!book.isAvailable()) {
            System.out.println("Book is not available");
            return false;
        }
        
        book.setAvailable(false);
        member.borrowBook(isbn);
        System.out.println("Book borrowed successfully");
        return true;
    }
    
    public boolean returnBook(String memberId, String isbn) {
        Member member = members.get(memberId);
        Book book = books.get(isbn);
        
        if (member == null || book == null) {
            return false;
        }
        
        if (member.returnBook(isbn)) {
            book.setAvailable(true);
            System.out.println("Book returned successfully");
            return true;
        }
        
        System.out.println("Member did not borrow this book");
        return false;
    }
    
    // Member operations
    public boolean addMember(String memberId, String name, String email) {
        if (!ValidationUtil.isValidEmail(email)) {
            System.out.println("Invalid email format");
            return false;
        }
        
        if (members.containsKey(memberId)) {
            System.out.println("Member with ID " + memberId + " already exists");
            return false;
        }
        
        Member member = new Member(memberId, name, email);
        members.put(memberId, member);
        System.out.println("Member added: " + name);
        return true;
    }
    
    public Member findMember(String memberId) {
        return members.get(memberId);
    }
    
    // Statistics
    public int getTotalBooks() {
        return books.size();
    }
    
    public int getAvailableBooks() {
        return (int) books.values().stream()
            .filter(Book::isAvailable)
            .count();
    }
    
    public int getTotalMembers() {
        return members.size();
    }
    
    public List<Book> getAllBooks() {
        return new ArrayList<>(books.values());
    }
    
    public List<Member> getAllMembers() {
        return new ArrayList<>(members.values());
    }
}

