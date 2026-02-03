/**
 * Problem: Remove All Adjacent Duplicates in String II
 * Difficulty: Medium
 * Tags: string, tree, stack
 * 
 * Approach: Use stack to track characters and their counts, remove when count reaches k
 * Time Complexity: O(n) where n is the length of s
 * Space Complexity: O(n) for stack
 */
import java.util.*;

class Solution {
    public String removeDuplicates(String s, int k) {
        Stack<int[]> stack = new Stack<>(); // [char, count]
        
        for (char c : s.toCharArray()) {
            if (!stack.isEmpty() && stack.peek()[0] == c) {
                stack.peek()[1]++;
                if (stack.peek()[1] == k) {
                    stack.pop();
                }
            } else {
                stack.push(new int[]{c, 1});
            }
        }
        
        StringBuilder result = new StringBuilder();
        for (int[] pair : stack) {
            result.append(String.valueOf((char) pair[0]).repeat(pair[1]));
        }
        
        return result.toString();
    }
}