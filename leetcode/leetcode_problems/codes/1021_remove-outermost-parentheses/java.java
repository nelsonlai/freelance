/**
 * Problem: Remove Outermost Parentheses
 * Difficulty: Easy
 * Tags: string, stack
 * 
 * Approach: Track depth, skip outermost parentheses
 * Time Complexity: O(n)
 * Space Complexity: O(1) excluding output
 */

class Solution {
    public String removeOuterParentheses(String s) {
        StringBuilder result = new StringBuilder();
        int depth = 0;
        
        for (char c : s.toCharArray()) {
            if (c == '(') {
                if (depth > 0) {
                    result.append(c);
                }
                depth++;
            } else {
                depth--;
                if (depth > 0) {
                    result.append(c);
                }
            }
        }
        
        return result.toString();
    }
}