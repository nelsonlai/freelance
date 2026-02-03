/**
 * Problem: Verify Preorder Sequence in Binary Search Tree
 * Difficulty: Medium
 * Tags: array, tree, search, stack
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(h) for recursion stack where h is height
 */

import java.util.*;

class Solution {
    public boolean verifyPreorder(int[] preorder) {
        Stack<Integer> stack = new Stack<>();
        int lowerBound = Integer.MIN_VALUE;
        
        for (int val : preorder) {
            if (val < lowerBound) {
                return false;
            }
            
            while (!stack.isEmpty() && val > stack.peek()) {
                lowerBound = stack.pop();
            }
            
            stack.push(val);
        }
        
        return true;
    }
}