/**
 * Problem: Remove All Adjacent Duplicates In String
 * Difficulty: Easy
 * Tags: string, stack
 * 
 * Approach: Use stack to remove adjacent duplicates
 * Time Complexity: O(n)
 * Space Complexity: O(n) for stack
 */

import java.util.*;

class Solution {
    public String removeDuplicates(String s) {
        Stack<Character> stack = new Stack<>();
        for (char c : s.toCharArray()) {
            if (!stack.isEmpty() && stack.peek() == c) {
                stack.pop();
            } else {
                stack.push(c);
            }
        }
        
        StringBuilder result = new StringBuilder();
        while (!stack.isEmpty()) {
            result.append(stack.pop());
        }
        return result.reverse().toString();
    }
}