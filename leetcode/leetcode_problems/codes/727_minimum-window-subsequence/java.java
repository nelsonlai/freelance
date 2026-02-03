class Solution {
    public String minWindow(String s1, String s2) {
        int m = s1.length(), n = s2.length();
        int[][] dp = new int[m + 1][n + 1];
        
        for (int i = 0; i <= m; i++) {
            for (int j = 0; j <= n; j++) {
                dp[i][j] = -1;
            }
            dp[i][0] = i;
        }
        
        int minLen = Integer.MAX_VALUE;
        int start = -1;
        
        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                if (s1.charAt(i-1) == s2.charAt(j-1)) {
                    dp[i][j] = dp[i-1][j-1];
                } else {
                    dp[i][j] = dp[i-1][j];
                }
            }
            
            if (dp[i][n] != -1) {
                int length = i - dp[i][n];
                if (length < minLen) {
                    minLen = length;
                    start = dp[i][n];
                }
            }
        }
        
        return start != -1 ? s1.substring(start, start + minLen) : "";
    }
}
