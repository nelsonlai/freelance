/**
 * Problem: Count All Possible Routes
 * Difficulty: Hard
 * Tags: array, dp
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) or O(n * m) for DP table
 */

import java.util.*;

class Solution {
    private static final int MOD = 1000000007;
    private Map<String, Integer> memo = new HashMap<>();
    
    public int countRoutes(int[] locations, int start, int finish, int fuel) {
        return dp(start, fuel, locations, finish);
    }
    
    private int dp(int city, int remainingFuel, int[] locations, int finish) {
        if (remainingFuel < 0) {
            return 0;
        }
        
        String key = city + "," + remainingFuel;
        if (memo.containsKey(key)) {
            return memo.get(key);
        }
        
        int result = (city == finish) ? 1 : 0;
        
        for (int nextCity = 0; nextCity < locations.length; nextCity++) {
            if (nextCity != city) {
                int cost = Math.abs(locations[city] - locations[nextCity]);
                if (cost <= remainingFuel) {
                    result = (result + dp(nextCity, remainingFuel - cost, locations, finish)) % MOD;
                }
            }
        }
        
        memo.put(key, result);
        return result;
    }
}