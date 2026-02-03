/**
 * Problem: Number of Ways to Separate Numbers
 * Difficulty: Hard
 * Tags: array, string, dp
 * 
 * Approach: DP - dp[i][j] = ways to form valid sequence ending at position i with last number of length j
 * Time Complexity: O(n^2) where n is length
 * Space Complexity: O(n^2)
 */

class Solution {
    private static final int MOD = 1000000007;
    
    public int numberOfCombinations(String num) {
        int n = num.length();
        
        if (num.charAt(0) == '0') {
            return 0;
        }
        
        // dp[i][j] = number of ways to form sequence ending at i with last number of length j
        long[][] dp = new long[n + 1][n + 1];
        dp[0][0] = 1;
        
        // Precompute LCP (longest common prefix) for string comparison
        int[][] lcp = new int[n + 1][n + 1];
        for (int i = n - 1; i >= 0; i--) {
            for (int j = n - 1; j >= 0; j--) {
                if (num.charAt(i) == num.charAt(j)) {
                    lcp[i][j] = 1 + lcp[i + 1][j + 1];
                } else {
                    lcp[i][j] = 0;
                }
            }
        }
        
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= i; j++) {
                if (num.charAt(i - j) == '0') {
                    continue;
                }
                
                if (i - j == 0) {
                    dp[i][j] = 1;
                } else {
                    // Try all possible previous lengths
                    for (int k = 1; k <= Math.min(j, i - j); k++) {
                        if (compare(num, i - j, i, k, lcp)) {
                            dp[i][j] = (dp[i][j] + dp[i - j][k]) % MOD;
                        }
                    }
                    // Also try shorter previous number
                    if (i - j >= j) {
                        for (int k = 1; k < j; k++) {
                            dp[i][j] = (dp[i][j] + dp[i - j][k]) % MOD;
                        }
                    }
                }
            }
        }
        
        long result = 0;
        for (int j = 0; j <= n; j++) {
            result = (result + dp[n][j]) % MOD;
        }
        
        return (int) result;
    }
    
    private boolean compare(String num, int i, int j, int len, int[][] lcp) {
        if (i < len || j < len) {
            return false;
        }
        int common = lcp[i - len][j - len];
        if (common >= len) {
            return true;
        }
        return num.charAt(i - len + common) >= num.charAt(j - len + common);
    }
}
