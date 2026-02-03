/**
 * Problem: Ternary Expression Parser
 * Difficulty: Medium
 * Tags: string, stack
 * 
 * Approach: String manipulation with hash map or two pointers
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

import java.util.*;

class Solution {
    public String parseTernary(String expression) {
        Stack<Character> stack = new Stack<>();
        int i = expression.length() - 1;
        
        while (i >= 0) {
            if (expression.charAt(i) == '?') {
                char condition = stack.pop();
                char trueVal = stack.pop();
                char falseVal = stack.pop();
                stack.push(condition == 'T' ? trueVal : falseVal);
                i--;
            } else if (expression.charAt(i) != ':') {
                stack.push(expression.charAt(i));
            }
            i--;
        }
        
        return String.valueOf(stack.pop());
    }
}