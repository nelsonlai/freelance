/**
 * Problem: 24 Game
 * Difficulty: Hard
 * Tags: array, math
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

import java.util.*;

class Solution {
    public boolean judgePoint24(int[] cards) {
        List<Double> nums = new ArrayList<>();
        for (int card : cards) {
            nums.add((double)card);
        }
        return dfs(nums);
    }
    
    private boolean dfs(List<Double> nums) {
        if (nums.size() == 1) {
            return Math.abs(nums.get(0) - 24) < 1e-6;
        }
        
        for (int i = 0; i < nums.size(); i++) {
            for (int j = i + 1; j < nums.size(); j++) {
                double a = nums.get(i);
                double b = nums.get(j);
                List<Double> newNums = new ArrayList<>();
                
                for (int k = 0; k < nums.size(); k++) {
                    if (k != i && k != j) {
                        newNums.add(nums.get(k));
                    }
                }
                
                for (double result : new double[]{a + b, a - b, b - a, a * b, a / b, b / a}) {
                    if (Double.isFinite(result)) {
                        newNums.add(result);
                        if (dfs(newNums)) {
                            return true;
                        }
                        newNums.remove(newNums.size() - 1);
                    }
                }
            }
        }
        
        return false;
    }
}