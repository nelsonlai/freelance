/*
 * Problem: Generate Parentheses
 * Difficulty: Medium
 * Tags: string, dp
 * 
 * Approach: String manipulation with hash map or two pointers
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) or O(n * m) for DP table
 */

using System.Collections.Generic;
using System.Text;

public class Solution {
    public IList<string> GenerateParenthesis(int n) {
        IList<string> result = new List<string>();
        Backtrack(result, new StringBuilder(), 0, 0, n);
        return result;
    }
    
    private void Backtrack(IList<string> result, StringBuilder current, int open, int close, int max) {
        if (current.Length == 2 * max) {
            result.Add(current.ToString());
            return;
        }
        
        if (open < max) {
            current.Append('(');
            Backtrack(result, current, open + 1, close, max);
            current.Remove(current.Length - 1, 1);
        }
        
        if (close < open) {
            current.Append(')');
            Backtrack(result, current, open, close + 1, max);
            current.Remove(current.Length - 1, 1);
        }
    }
}