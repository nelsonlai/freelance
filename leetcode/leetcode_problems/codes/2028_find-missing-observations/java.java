/**
 * Problem: Find Missing Observations
 * Difficulty: Medium
 * Tags: array, math
 * 
 * Approach: Calculate total needed, distribute evenly with constraints (1-6 per die)
 * Time Complexity: O(n) where n is missing observations
 * Space Complexity: O(n)
 */

class Solution {
    public int[] missingRolls(int[] rolls, int mean, int n) {
        int m = rolls.length;
        int total = mean * (m + n);
        int observedSum = 0;
        for (int roll : rolls) {
            observedSum += roll;
        }
        int missingSum = total - observedSum;
        
        if (missingSum < n || missingSum > 6 * n) {
            return new int[0];
        }
        
        // Distribute evenly
        int base = missingSum / n;
        int remainder = missingSum % n;
        
        int[] result = new int[n];
        for (int i = 0; i < n; i++) {
            result[i] = base;
            if (i < remainder) {
                result[i]++;
            }
        }
        
        // Validate all are in range [1, 6]
        for (int val : result) {
            if (val < 1 || val > 6) {
                return new int[0];
            }
        }
        
        return result;
    }
}