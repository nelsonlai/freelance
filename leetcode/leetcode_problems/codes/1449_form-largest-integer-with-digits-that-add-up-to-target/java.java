/**
 * Problem: Form Largest Integer With Digits That Add up to Target
 * Difficulty: Hard
 * Tags: array, string, dp
 * 
 * Approach: DP - dp[i] = largest string for cost i, try all digits
 * Time Complexity: O(target * 9)
 * Space Complexity: O(target)
 */

class Solution {
    public String largestNumber(int[] cost, int target) {
        String[] dp = new String[target + 1];
        dp[0] = "";
        
        for (int i = 1; i <= target; i++) {
            dp[i] = "";
            for (int digit = 9; digit >= 1; digit--) {
                int c = cost[digit - 1];
                if (i >= c && (i == c || !dp[i - c].isEmpty())) {
                    String candidate = digit + dp[i - c];
                    if (candidate.length() > dp[i].length() || 
                        (candidate.length() == dp[i].length() && candidate.compareTo(dp[i]) > 0)) {
                        dp[i] = candidate;
                    }
                }
            }
        }
        
        return dp[target].isEmpty() ? "0" : dp[target];
    }
}