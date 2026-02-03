/**
 * Problem: Probability of a Two Boxes Having The Same Number of Distinct Balls
 * Difficulty: Hard
 * Tags: array, dp, math
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) or O(n * m) for DP table
 */

import java.util.*;

class Solution {
    private Map<String, Double> memo = new HashMap<>();
    
    public double getProbability(int[] balls) {
        int total = 0;
        for (int ball : balls) {
            total += ball;
        }
        int n = balls.length;
        
        long totalWays = ways(0, 0, 0, 0, 0, balls, n);
        long allWays = comb(total, total / 2);
        
        return (double) totalWays / allWays;
    }
    
    private long ways(int color, int box1Count, int box1Colors, int box2Count, int box2Colors, int[] balls, int n) {
        if (color == n) {
            if (box1Count == box2Count && box1Colors == box2Colors) {
                return 1;
            }
            return 0;
        }
        
        String key = color + "," + box1Count + "," + box1Colors + "," + box2Count + "," + box2Colors;
        if (memo.containsKey(key)) {
            return (long) memo.get(key);
        }
        
        long result = 0;
        for (int i = 0; i <= balls[color]; i++) {
            int newBox1 = box1Count + i;
            int newBox2 = box2Count + (balls[color] - i);
            int newColors1 = box1Colors + (i > 0 ? 1 : 0);
            int newColors2 = box2Colors + (i < balls[color] ? 1 : 0);
            
            long comb = comb(balls[color], i);
            result += comb * ways(color + 1, newBox1, newColors1, newBox2, newColors2, balls, n);
        }
        
        memo.put(key, (double) result);
        return result;
    }
    
    private long comb(int n, int k) {
        if (k > n - k) {
            k = n - k;
        }
        long result = 1;
        for (int i = 0; i < k; i++) {
            result = result * (n - i) / (i + 1);
        }
        return result;
    }
}