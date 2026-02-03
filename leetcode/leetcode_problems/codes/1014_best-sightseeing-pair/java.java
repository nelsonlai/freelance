/**
 * Problem: Best Sightseeing Pair
 * Difficulty: Medium
 * Tags: array, dp
 * 
 * Approach: Track best value[i] + i seen so far, maximize with current value[j] - j
 * Time Complexity: O(n)
 * Space Complexity: O(1)
 */

class Solution {
    public int maxScoreSightseeingPair(int[] values) {
        int best = values[0] + 0;
        int maxScore = 0;
        
        for (int j = 1; j < values.length; j++) {
            maxScore = Math.max(maxScore, best + values[j] - j);
            best = Math.max(best, values[j] + j);
        }
        
        return maxScore;
    }
}