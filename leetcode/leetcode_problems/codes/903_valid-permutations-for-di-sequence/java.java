class Solution {
    public int numPermsDISequence(String s) {
        int n = s.length();
        int MOD = 1000000007;
        int[] dp = new int[n + 1];
        Arrays.fill(dp, 1);
        
        for (int i = 0; i < n; i++) {
            int[] newDp = new int[n + 1];
            if (s.charAt(i) == 'I') {
                for (int j = 0; j < n - i; j++) {
                    for (int k = 0; k <= j; k++) {
                        newDp[j] = (newDp[j] + dp[k]) % MOD;
                    }
                }
            } else {
                for (int j = 0; j < n - i; j++) {
                    for (int k = j + 1; k <= n - i; k++) {
                        newDp[j] = (newDp[j] + dp[k]) % MOD;
                    }
                }
            }
            dp = newDp;
        }
        
        return dp[0];
    }
}
