class Solution {
    public int countPalindromicSubsequences(String s) {
        int n = s.length();
        int MOD = 1000000007;
        long[][] dp = new long[n][n];
        
        for (int i = 0; i < n; i++) {
            dp[i][i] = 1;
        }
        
        for (int length = 2; length <= n; length++) {
            for (int i = 0; i < n - length + 1; i++) {
                int j = i + length - 1;
                if (s.charAt(i) == s.charAt(j)) {
                    int left = i + 1, right = j - 1;
                    while (left <= right && s.charAt(left) != s.charAt(i)) {
                        left++;
                    }
                    while (left <= right && s.charAt(right) != s.charAt(i)) {
                        right--;
                    }
                    
                    if (left > right) {
                        dp[i][j] = dp[i+1][j-1] * 2 + 2;
                    } else if (left == right) {
                        dp[i][j] = dp[i+1][j-1] * 2 + 1;
                    } else {
                        dp[i][j] = dp[i+1][j-1] * 2 - dp[left+1][right-1];
                    }
                } else {
                    dp[i][j] = dp[i+1][j] + dp[i][j-1] - dp[i+1][j-1];
                }
                dp[i][j] = (dp[i][j] % MOD + MOD) % MOD;
            }
        }
        
        return (int) dp[0][n-1];
    }
}
