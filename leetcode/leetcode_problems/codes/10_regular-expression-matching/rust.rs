// Problem: Regular Expression Matching
// Difficulty: Hard
// Tags: string, dp
// 
// Approach: String manipulation with hash map or two pointers
// Time Complexity: O(n) or O(n log n)
// Space Complexity: O(n) or O(n * m) for DP table

impl Solution {
    pub fn is_match(s: String, p: String) -> bool {
        let s_chars: Vec<char> = s.chars().collect();
        let p_chars: Vec<char> = p.chars().collect();
        let m = s_chars.len();
        let n = p_chars.len();
        
        let mut dp = vec![vec![false; n + 1]; m + 1];
        dp[0][0] = true;
        
        for j in 2..=n {
            if p_chars[j - 1] == '*' {
                dp[0][j] = dp[0][j - 2];
            }
        }
        
        for i in 1..=m {
            for j in 1..=n {
                if p_chars[j - 1] == '*' {
                    dp[i][j] = dp[i][j - 2] || 
                               (dp[i - 1][j] && (s_chars[i - 1] == p_chars[j - 2] || p_chars[j - 2] == '.'));
                } else {
                    dp[i][j] = dp[i - 1][j - 1] && (s_chars[i - 1] == p_chars[j - 1] || p_chars[j - 1] == '.');
                }
            }
        }
        
        dp[m][n]
    }
}