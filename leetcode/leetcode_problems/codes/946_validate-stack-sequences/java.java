/**
 * Problem: Validate Stack Sequences
 * Difficulty: Medium
 * Tags: array, stack
 * 
 * Approach: Simulate stack operations - push elements and pop when matching
 * Time Complexity: O(n)
 * Space Complexity: O(n) for stack
 */

import java.util.*;

class Solution {
    public boolean validateStackSequences(int[] pushed, int[] popped) {
        Stack<Integer> stack = new Stack<>();
        int popIdx = 0;
        
        for (int num : pushed) {
            stack.push(num);
            while (!stack.isEmpty() && stack.peek() == popped[popIdx]) {
                stack.pop();
                popIdx++;
            }
        }
        
        return stack.isEmpty();
    }
}