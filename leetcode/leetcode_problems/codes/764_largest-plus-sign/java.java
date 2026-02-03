import java.util.*;

class Solution {
    public int orderOfLargestPlusSign(int n, int[][] mines) {
        Set<String> banned = new HashSet<>();
        for (int[] mine : mines) {
            banned.add(mine[0] + "," + mine[1]);
        }
        
        int[][] dp = new int[n][n];
        for (int[] row : dp) {
            Arrays.fill(row, n);
        }
        
        for (int i = 0; i < n; i++) {
            int count = 0;
            for (int j = 0; j < n; j++) {
                count = banned.contains(i + "," + j) ? 0 : count + 1;
                dp[i][j] = Math.min(dp[i][j], count);
            }
            
            count = 0;
            for (int j = n - 1; j >= 0; j--) {
                count = banned.contains(i + "," + j) ? 0 : count + 1;
                dp[i][j] = Math.min(dp[i][j], count);
            }
        }
        
        for (int j = 0; j < n; j++) {
            int count = 0;
            for (int i = 0; i < n; i++) {
                count = banned.contains(i + "," + j) ? 0 : count + 1;
                dp[i][j] = Math.min(dp[i][j], count);
            }
            
            count = 0;
            for (int i = n - 1; i >= 0; i--) {
                count = banned.contains(i + "," + j) ? 0 : count + 1;
                dp[i][j] = Math.min(dp[i][j], count);
            }
        }
        
        int result = 0;
        for (int[] row : dp) {
            for (int val : row) {
                result = Math.max(result, val);
            }
        }
        return result;
    }
}
