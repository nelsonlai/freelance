/**
 * ValidationUtil.java - Utility class for validation
 */

package com.example.library.util;

import java.util.regex.Pattern;

public class ValidationUtil {
    // ISBN pattern: 10 or 13 digits, optionally with hyphens
    private static final Pattern ISBN_PATTERN = Pattern.compile("^\\d{10}|\\d{13}|\\d{1,3}-\\d{1,3}-\\d{1,5}-\\d{1,7}-\\d{1,7}$");
    
    // Email pattern
    private static final Pattern EMAIL_PATTERN = Pattern.compile("^[A-Za-z0-9+_.-]+@[A-Za-z0-9.-]+\\.[A-Za-z]{2,}$");
    
    public static boolean isValidIsbn(String isbn) {
        if (isbn == null || isbn.trim().isEmpty()) {
            return false;
        }
        // Remove hyphens for validation
        String cleaned = isbn.replace("-", "");
        return cleaned.length() == 10 || cleaned.length() == 13;
    }
    
    public static boolean isValidEmail(String email) {
        if (email == null || email.trim().isEmpty()) {
            return false;
        }
        return EMAIL_PATTERN.matcher(email).matches();
    }
    
    public static boolean isValidYear(int year) {
        return year >= 1000 && year <= 9999;
    }
}

