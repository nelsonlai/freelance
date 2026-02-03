/**
 * Problem: Smallest Subsequence of Distinct Characters
 * Difficulty: Medium
 * Tags: string, graph, greedy, stack
 * 
 * Approach: Monotonic stack - maintain lexicographically smallest subsequence
 * Time Complexity: O(n)
 * Space Complexity: O(n) for stack
 */

import java.util.*;

class Solution {
    public String smallestSubsequence(String s) {
        Map<Character, Integer> lastOccurrence = new HashMap<>();
        for (int i = 0; i < s.length(); i++) {
            lastOccurrence.put(s.charAt(i), i);
        }
        
        Stack<Character> stack = new Stack<>();
        Set<Character> seen = new HashSet<>();
        
        for (int i = 0; i < s.length(); i++) {
            char c = s.charAt(i);
            if (seen.contains(c)) {
                continue;
            }
            
            while (!stack.isEmpty() && stack.peek() > c && lastOccurrence.get(stack.peek()) > i) {
                seen.remove(stack.pop());
            }
            
            stack.push(c);
            seen.add(c);
        }
        
        StringBuilder result = new StringBuilder();
        while (!stack.isEmpty()) {
            result.append(stack.pop());
        }
        return result.reverse().toString();
    }
}