/*
 * Problem: Regular Expression Matching
 * Difficulty: Hard
 * Tags: string, dp
 * 
 * Approach: String manipulation with hash map or two pointers
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) or O(n * m) for DP table
 */

public class Solution {
    public bool IsMatch(string s, string p) {
        int m = s.Length, n = p.Length;
        bool[,] dp = new bool[m + 1, n + 1];
        dp[0, 0] = true;
        
        for (int j = 2; j <= n; j++) {
            if (p[j - 1] == '*') {
                dp[0, j] = dp[0, j - 2];
            }
        }
        
        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                if (p[j - 1] == '*') {
                    dp[i, j] = dp[i, j - 2] || 
                               (dp[i - 1, j] && (s[i - 1] == p[j - 2] || p[j - 2] == '.'));
                } else {
                    dp[i, j] = dp[i - 1, j - 1] && (s[i - 1] == p[j - 1] || p[j - 1] == '.');
                }
            }
        }
        
        return dp[m, n];
    }
}