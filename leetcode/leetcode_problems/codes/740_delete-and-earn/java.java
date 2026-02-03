import java.util.*;

class Solution {
    public int deleteAndEarn(int[] nums) {
        Map<Integer, Integer> count = new HashMap<>();
        int maxNum = 0;
        for (int num : nums) {
            count.put(num, count.getOrDefault(num, 0) + 1);
            maxNum = Math.max(maxNum, num);
        }
        
        int[] dp = new int[maxNum + 1];
        dp[1] = count.getOrDefault(1, 0);
        
        for (int i = 2; i <= maxNum; i++) {
            dp[i] = Math.max(dp[i - 1], dp[i - 2] + i * count.getOrDefault(i, 0));
        }
        
        return dp[maxNum];
    }
}
