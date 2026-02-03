/**
 * Problem: Strong Password Checker
 * Difficulty: Hard
 * Tags: string, greedy, queue, heap
 * 
 * Approach: String manipulation with hash map or two pointers
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

import java.util.*;

class Solution {
    public int strongPasswordChecker(String password) {
        int n = password.length();
        int missingTypes = 3;
        boolean hasLower = false, hasUpper = false, hasDigit = false;
        
        for (char c : password.toCharArray()) {
            if (Character.isLowerCase(c)) {
                hasLower = true;
            } else if (Character.isUpperCase(c)) {
                hasUpper = true;
            } else if (Character.isDigit(c)) {
                hasDigit = true;
            }
        }
        
        if (hasLower) missingTypes--;
        if (hasUpper) missingTypes--;
        if (hasDigit) missingTypes--;
        
        int replace = 0;
        int one = 0, two = 0;
        
        int i = 0;
        while (i < n) {
            int length = 1;
            while (i + length < n && password.charAt(i + length) == password.charAt(i)) {
                length++;
            }
            
            if (length >= 3) {
                replace += length / 3;
                if (length % 3 == 0) one++;
                else if (length % 3 == 1) two++;
            }
            
            i += length;
        }
        
        if (n < 6) {
            return Math.max(missingTypes, 6 - n);
        } else if (n <= 20) {
            return Math.max(missingTypes, replace);
        } else {
            int delete = n - 20;
            replace -= Math.min(delete, one);
            replace -= Math.min(Math.max(delete - one, 0), two * 2) / 2;
            replace -= Math.max(delete - one - 2 * two, 0) / 3;
            return delete + Math.max(missingTypes, replace);
        }
    }
}