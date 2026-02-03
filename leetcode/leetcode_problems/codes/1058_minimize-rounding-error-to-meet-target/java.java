/**
 * Problem: Minimize Rounding Error to Meet Target
 * Difficulty: Medium
 * Tags: array, string, greedy, math, sort
 * 
 * Approach: Round down all, then round up those with largest fractional parts
 * Time Complexity: O(n log n) for sorting
 * Space Complexity: O(n)
 */

import java.util.*;

class Solution {
    public String minimizeError(String[] prices, int target) {
        int floorSum = 0;
        List<Double> fractions = new ArrayList<>();
        
        for (String price : prices) {
            double f = Double.parseDouble(price);
            floorSum += (int) f;
            fractions.add(f - (int) f);
        }
        
        if (target < floorSum || target > floorSum + prices.length) {
            return "-1";
        }
        
        fractions.sort(Collections.reverseOrder());
        int roundsNeeded = target - floorSum;
        double error = 0;
        
        for (int i = 0; i < roundsNeeded; i++) {
            error += fractions.get(i);
        }
        for (int i = roundsNeeded; i < fractions.size(); i++) {
            error += 1 - fractions.get(i);
        }
        
        return String.format("%.3f", error);
    }
}