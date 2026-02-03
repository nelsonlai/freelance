/**
 * Member.java - Model class representing a library member
 */

package com.example.library.model;

import java.util.ArrayList;
import java.util.List;

public class Member {
    private String memberId;
    private String name;
    private String email;
    private List<String> borrowedBooks;  // List of ISBNs
    
    public Member(String memberId, String name, String email) {
        this.memberId = memberId;
        this.name = name;
        this.email = email;
        this.borrowedBooks = new ArrayList<>();
    }
    
    // Getters
    public String getMemberId() {
        return memberId;
    }
    
    public String getName() {
        return name;
    }
    
    public String getEmail() {
        return email;
    }
    
    public List<String> getBorrowedBooks() {
        return new ArrayList<>(borrowedBooks);  // Return copy
    }
    
    // Methods
    public void borrowBook(String isbn) {
        if (!borrowedBooks.contains(isbn)) {
            borrowedBooks.add(isbn);
        }
    }
    
    public boolean returnBook(String isbn) {
        return borrowedBooks.remove(isbn);
    }
    
    public int getBorrowedCount() {
        return borrowedBooks.size();
    }
    
    @Override
    public String toString() {
        return String.format("Member[ID: %s, Name: %s, Email: %s, Borrowed: %d]",
                memberId, name, email, borrowedBooks.size());
    }
}

