/**
 * Problem: Remove Duplicate Letters
 * Difficulty: Medium
 * Tags: string, graph, greedy, stack
 * 
 * Approach: String manipulation with hash map or two pointers
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

import java.util.*;

class Solution {
    public String removeDuplicateLetters(String s) {
        int[] count = new int[26];
        for (char c : s.toCharArray()) {
            count[c - 'a']++;
        }
        
        boolean[] seen = new boolean[26];
        Stack<Character> stack = new Stack<>();
        
        for (char c : s.toCharArray()) {
            count[c - 'a']--;
            if (seen[c - 'a']) {
                continue;
            }
            
            while (!stack.isEmpty() && stack.peek() > c && count[stack.peek() - 'a'] > 0) {
                seen[stack.pop() - 'a'] = false;
            }
            
            stack.push(c);
            seen[c - 'a'] = true;
        }
        
        StringBuilder sb = new StringBuilder();
        while (!stack.isEmpty()) {
            sb.append(stack.pop());
        }
        return sb.reverse().toString();
    }
}