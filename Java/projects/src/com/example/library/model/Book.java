/**
 * PROJECT EXAMPLE - Library Management System
 * 
 * This is a multi-file project demonstrating:
 * - Package structure
 * - Multiple classes working together
 * - Separation of concerns (Model, Service, Util)
 * 
 * Book.java - Model class representing a book
 */

package com.example.library.model;

public class Book {
    private String isbn;
    private String title;
    private String author;
    private int year;
    private boolean isAvailable;
    
    public Book(String isbn, String title, String author, int year) {
        this.isbn = isbn;
        this.title = title;
        this.author = author;
        this.year = year;
        this.isAvailable = true;
    }
    
    // Getters
    public String getIsbn() {
        return isbn;
    }
    
    public String getTitle() {
        return title;
    }
    
    public String getAuthor() {
        return author;
    }
    
    public int getYear() {
        return year;
    }
    
    public boolean isAvailable() {
        return isAvailable;
    }
    
    // Setters
    public void setAvailable(boolean available) {
        isAvailable = available;
    }
    
    @Override
    public String toString() {
        return String.format("Book[ISBN: %s, Title: %s, Author: %s, Year: %d, Available: %s]",
                isbn, title, author, year, isAvailable);
    }
    
    @Override
    public boolean equals(Object obj) {
        if (this == obj) return true;
        if (obj == null || getClass() != obj.getClass()) return false;
        Book book = (Book) obj;
        return isbn != null ? isbn.equals(book.isbn) : book.isbn == null;
    }
    
    @Override
    public int hashCode() {
        return isbn != null ? isbn.hashCode() : 0;
    }
}

