/**
 * Problem: Shortest Palindrome
 * Difficulty: Hard
 * Tags: string, hash
 * 
 * Approach: String manipulation with hash map or two pointers
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) for hash map
 */

class Solution {
    public String shortestPalindrome(String s) {
        if (s == null || s.length() == 0) {
            return s;
        }
        
        String rev = new StringBuilder(s).reverse().toString();
        for (int i = 0; i < s.length(); i++) {
            if (s.substring(0, s.length() - i).equals(rev.substring(i))) {
                return rev.substring(0, i) + s;
            }
        }
        return rev + s;
    }
}