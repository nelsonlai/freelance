/**
 * Problem: One Edit Distance
 * Difficulty: Medium
 * Tags: array, string
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

class Solution {
    public boolean isOneEditDistance(String s, String t) {
        int m = s.length();
        int n = t.length();
        
        if (Math.abs(m - n) > 1) {
            return false;
        }
        
        if (m > n) {
            return isOneEditDistance(t, s);
        }
        
        int i = 0;
        while (i < m && s.charAt(i) == t.charAt(i)) {
            i++;
        }
        
        if (i == m) {
            return n == m + 1;
        }
        
        if (m == n) {
            return s.substring(i + 1).equals(t.substring(i + 1));
        } else {
            return s.substring(i).equals(t.substring(i + 1));
        }
    }
}