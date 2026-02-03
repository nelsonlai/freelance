/*
 * Problem: Valid Parentheses
 * Difficulty: Easy
 * Tags: string, stack
 * 
 * Approach: String manipulation with hash map or two pointers
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

using System.Collections.Generic;

public class Solution {
    public bool IsValid(string s) {
        Stack<char> stack = new Stack<char>();
        Dictionary<char, char> mapping = new Dictionary<char, char> {
            {')', '('},
            {'}', '{'},
            {']', '['}
        };
        
        foreach (char c in s) {
            if (mapping.ContainsKey(c)) {
                if (stack.Count == 0 || stack.Pop() != mapping[c]) {
                    return false;
                }
            } else {
                stack.Push(c);
            }
        }
        
        return stack.Count == 0;
    }
}