/**
 * Problem: Detect Capital
 * Difficulty: Easy
 * Tags: string
 * 
 * Approach: String manipulation with hash map or two pointers
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

class Solution {
    public boolean detectCapitalUse(String word) {
        if (word.length() <= 1) {
            return true;
        }
        
        if (Character.isUpperCase(word.charAt(0))) {
            return allUpperCase(word.substring(1)) || allLowerCase(word.substring(1));
        } else {
            return allLowerCase(word.substring(1));
        }
    }
    
    private boolean allUpperCase(String s) {
        for (char c : s.toCharArray()) {
            if (!Character.isUpperCase(c)) {
                return false;
            }
        }
        return true;
    }
    
    private boolean allLowerCase(String s) {
        for (char c : s.toCharArray()) {
            if (!Character.isLowerCase(c)) {
                return false;
            }
        }
        return true;
    }
}