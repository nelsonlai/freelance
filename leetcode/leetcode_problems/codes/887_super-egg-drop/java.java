class Solution {
    public int superEggDrop(int k, int n) {
        int[][] dp = new int[n + 1][k + 1];
        
        for (int m = 1; m <= n; m++) {
            for (int e = 1; e <= k; e++) {
                dp[m][e] = dp[m - 1][e - 1] + dp[m - 1][e] + 1;
                if (dp[m][e] >= n) {
                    return m;
                }
            }
        }
        return n;
    }
}
