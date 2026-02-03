/**
 * Problem: Minimum Cost to Separate Sentence Into Rows
 * Difficulty: Medium
 * Tags: array, string, dp
 * 
 * Approach: DP - minimize cost of splitting sentence into rows with max width k
 * Time Complexity: O(n^2) where n is number of words
 * Space Complexity: O(n)
 */

class Solution {
    public int minimumCost(String sentence, int k) {
        String[] words = sentence.split(" ");
        int n = words.length;
        
        // dp[i] = minimum cost to split words[i:]
        long[] dp = new long[n + 1];
        for (int i = 0; i < n; i++) {
            dp[i] = Long.MAX_VALUE;
        }
        dp[n] = 0;
        
        for (int i = n - 1; i >= 0; i--) {
            int length = 0;
            for (int j = i; j < n; j++) {
                if (j > i) {
                    length += 1;  // space
                }
                length += words[j].length();
                
                if (length > k) {
                    break;
                }
                
                // Cost is (k - length)^2
                long cost = (long)(k - length) * (k - length);
                if (dp[j + 1] != Long.MAX_VALUE) {
                    dp[i] = Math.min(dp[i], cost + dp[j + 1]);
                }
            }
        }
        
        return (int) dp[0];
    }
}