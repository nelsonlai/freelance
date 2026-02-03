/**
 * Problem: Decode Ways II
 * Difficulty: Hard
 * Tags: string, dp
 * 
 * Approach: String manipulation with hash map or two pointers
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) or O(n * m) for DP table
 */

class Solution {
    public int numDecodings(String s) {
        int MOD = 1000000007;
        int n = s.length();
        long[] dp = new long[n + 1];
        dp[0] = 1;
        
        if (s.charAt(0) == '*') {
            dp[1] = 9;
        } else if (s.charAt(0) != '0') {
            dp[1] = 1;
        }
        
        for (int i = 2; i <= n; i++) {
            char curr = s.charAt(i - 1);
            char prev = s.charAt(i - 2);
            
            if (curr == '*') {
                dp[i] = (dp[i] + 9 * dp[i-1]) % MOD;
            } else if (curr != '0') {
                dp[i] = (dp[i] + dp[i-1]) % MOD;
            }
            
            if (prev == '*') {
                if (curr == '*') {
                    dp[i] = (dp[i] + 15 * dp[i-2]) % MOD;
                } else if (curr <= '6') {
                    dp[i] = (dp[i] + 2 * dp[i-2]) % MOD;
                } else {
                    dp[i] = (dp[i] + dp[i-2]) % MOD;
                }
            } else if (prev == '1') {
                if (curr == '*') {
                    dp[i] = (dp[i] + 9 * dp[i-2]) % MOD;
                } else {
                    dp[i] = (dp[i] + dp[i-2]) % MOD;
                }
            } else if (prev == '2') {
                if (curr == '*') {
                    dp[i] = (dp[i] + 6 * dp[i-2]) % MOD;
                } else if (curr <= '6') {
                    dp[i] = (dp[i] + dp[i-2]) % MOD;
                }
            }
        }
        
        return (int)dp[n];
    }
}