/**
 * Problem: Check if String Is Decomposable Into Value-Equal Substrings
 * Difficulty: Easy
 * Tags: string, greedy
 * 
 * Approach: Check if can be decomposed into substrings of length 2 or 3, exactly one of length 2
 * Time Complexity: O(n) where n is length
 * Space Complexity: O(1)
 */

class Solution {
    public boolean isDecomposable(String s) {
        int i = 0;
        int n = s.length();
        boolean hasTwo = false;
        
        while (i < n) {
            if (i + 2 < n && s.charAt(i) == s.charAt(i + 1) && s.charAt(i + 1) == s.charAt(i + 2)) {
                i += 3;
            } else if (i + 1 < n && s.charAt(i) == s.charAt(i + 1)) {
                if (hasTwo) {
                    return false;
                }
                hasTwo = true;
                i += 2;
            } else {
                return false;
            }
        }
        
        return hasTwo;
    }
}