/**
 * Problem: Maximum Compatibility Score Sum
 * Difficulty: Medium
 * Tags: array, dp, bitmask, Hungarian algorithm
 * 
 * Approach: DP with bitmask - assign students to mentors optimally
 * Time Complexity: O(n * 2^n) where n is students
 * Space Complexity: O(2^n)
 */

import java.util.*;

class Solution {
    public int maxCompatibilitySum(int[][] students, int[][] mentors) {
        int n = students.length;
        int[][] score = new int[n][n];
        
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                score[i][j] = calculateScore(students[i], mentors[j]);
            }
        }
        
        int[] dp = new int[1 << n];
        Arrays.fill(dp, -1);
        return dp(0, 0, n, score, dp);
    }
    
    private int dp(int mask, int mentorIdx, int n, int[][] score, int[] memo) {
        if (mentorIdx == n) {
            return 0;
        }
        
        if (memo[mask] != -1) {
            return memo[mask];
        }
        
        int result = 0;
        for (int i = 0; i < n; i++) {
            if ((mask & (1 << i)) == 0) {
                result = Math.max(result, score[i][mentorIdx] + 
                    dp(mask | (1 << i), mentorIdx + 1, n, score, memo));
            }
        }
        
        return memo[mask] = result;
    }
    
    private int calculateScore(int[] student, int[] mentor) {
        int score = 0;
        for (int i = 0; i < student.length; i++) {
            if (student[i] == mentor[i]) {
                score++;
            }
        }
        return score;
    }
}