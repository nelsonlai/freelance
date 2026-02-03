/*
 * Problem: Longest Valid Parentheses
 * Difficulty: Hard
 * Tags: string, tree, dp, stack
 * 
 * Approach: String manipulation with hash map or two pointers
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) or O(n * m) for DP table
 */

using System.Collections.Generic;

public class Solution {
    public int LongestValidParentheses(string s) {
        Stack<int> stack = new Stack<int>();
        stack.Push(-1);
        int maxLen = 0;
        
        for (int i = 0; i < s.Length; i++) {
            if (s[i] == '(') {
                stack.Push(i);
            } else {
                stack.Pop();
                if (stack.Count == 0) {
                    stack.Push(i);
                } else {
                    maxLen = Math.Max(maxLen, i - stack.Peek());
                }
            }
        }
        
        return maxLen;
    }
}