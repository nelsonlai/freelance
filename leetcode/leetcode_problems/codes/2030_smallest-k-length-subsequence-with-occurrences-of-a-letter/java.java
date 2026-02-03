/**
 * Problem: Smallest K-Length Subsequence With Occurrences of a Letter
 * Difficulty: Hard
 * Tags: string, graph, greedy, stack
 * 
 * Approach: Greedy with stack - maintain smallest lexicographic subsequence while ensuring letter count
 * Time Complexity: O(n) where n is length
 * Space Complexity: O(n)
 */

import java.util.*;

class Solution {
    public String smallestSubsequence(String s, int k, char letter, int repetition) {
        int n = s.length();
        // Count remaining occurrences of letter after each position
        int[] letterCount = new int[n];
        int count = 0;
        for (int i = n - 1; i >= 0; i--) {
            if (s.charAt(i) == letter) {
                count++;
            }
            letterCount[i] = count;
        }
        
        Stack<Character> stack = new Stack<>();
        int letterUsed = 0;  // Count of letter used in stack
        
        for (int i = 0; i < n; i++) {
            char c = s.charAt(i);
            // Pop if we can maintain k-length and letter requirement
            while (!stack.isEmpty() && stack.peek() > c) {
                // Check if we can still form valid subsequence after popping
                int remainingChars = n - i;
                int remainingLetters = letterCount[i];
                int stackSize = stack.size();
                
                // After popping, we need: (k - stackSize) chars and (repetition - letterUsed) letters
                if (stackSize + remainingChars >= k && letterUsed + remainingLetters >= repetition) {
                    char popped = stack.pop();
                    if (popped == letter) {
                        letterUsed--;
                    }
                } else {
                    break;
                }
            }
            
            // Add current character if we have space
            if (stack.size() < k) {
                stack.push(c);
                if (c == letter) {
                    letterUsed++;
                }
            } else {
                // Replace if current is smaller and we can maintain requirements
                if (!stack.isEmpty() && stack.peek() > c) {
                    char popped = stack.pop();
                    if (popped == letter) {
                        letterUsed--;
                    }
                    stack.push(c);
                    if (c == letter) {
                        letterUsed++;
                    }
                }
            }
        }
        
        StringBuilder result = new StringBuilder();
        for (char c : stack) {
            result.append(c);
        }
        return result.toString();
    }
}