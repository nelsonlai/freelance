/**
 * Problem: Longest Absolute File Path
 * Difficulty: Medium
 * Tags: string, tree, search, stack
 * 
 * Approach: String manipulation with hash map or two pointers
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(h) for recursion stack where h is height
 */

import java.util.*;

class Solution {
    public int lengthLongestPath(String input) {
        String[] lines = input.split("\n");
        List<Integer> stack = new ArrayList<>();
        int maxLength = 0;
        
        for (String line : lines) {
            int depth = 0;
            while (depth < line.length() && line.charAt(depth) == '\t') {
                depth++;
            }
            String name = line.substring(depth);
            
            while (stack.size() > depth) {
                stack.remove(stack.size() - 1);
            }
            
            int currentLength = (stack.isEmpty() ? 0 : stack.get(stack.size() - 1)) + name.length() + (stack.isEmpty() ? 0 : 1);
            
            if (name.contains(".")) {
                maxLength = Math.max(maxLength, currentLength);
            } else {
                stack.add(currentLength);
            }
        }
        
        return maxLength;
    }
}