/**
 * Problem: Shopping Offers
 * Difficulty: Medium
 * Tags: array, dp
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) or O(n * m) for DP table
 */

import java.util.*;

class Solution {
    public int shoppingOffers(List<Integer> price, List<List<Integer>> special, List<Integer> needs) {
        Map<String, Integer> memo = new HashMap<>();
        return dfs(price, special, needs, memo);
    }
    
    private int dfs(List<Integer> price, List<List<Integer>> special, List<Integer> needs, Map<String, Integer> memo) {
        String key = needs.toString();
        if (memo.containsKey(key)) {
            return memo.get(key);
        }
        
        int cost = 0;
        for (int i = 0; i < needs.size(); i++) {
            cost += price.get(i) * needs.get(i);
        }
        
        for (List<Integer> offer : special) {
            List<Integer> newNeeds = new ArrayList<>(needs);
            boolean valid = true;
            
            for (int i = 0; i < needs.size(); i++) {
                if (needs.get(i) < offer.get(i)) {
                    valid = false;
                    break;
                }
                newNeeds.set(i, needs.get(i) - offer.get(i));
            }
            
            if (valid) {
                cost = Math.min(cost, offer.get(offer.size() - 1) + dfs(price, special, newNeeds, memo));
            }
        }
        
        memo.put(key, cost);
        return cost;
    }
}