/**
 * Problem: Valid Parenthesis String
 * Difficulty: Medium
 * Tags: string, dp, greedy, stack
 * 
 * Approach: String manipulation with hash map or two pointers
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) or O(n * m) for DP table
 */

class Solution {
    public boolean checkValidString(String s) {
        int minOpen = 0, maxOpen = 0;
        
        for (char c : s.toCharArray()) {
            if (c == '(') {
                minOpen++;
                maxOpen++;
            } else if (c == ')') {
                minOpen = Math.max(0, minOpen - 1);
                maxOpen--;
                if (maxOpen < 0) {
                    return false;
                }
            } else {
                minOpen = Math.max(0, minOpen - 1);
                maxOpen++;
            }
        }
        
        return minOpen == 0;
    }
}