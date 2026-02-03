/**
 * Problem: Optimal Account Balancing
 * Difficulty: Hard
 * Tags: array, dp
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) or O(n * m) for DP table
 */

import java.util.*;

class Solution {
    public int minTransfers(int[][] transactions) {
        Map<Integer, Integer> balance = new HashMap<>();
        for (int[] t : transactions) {
            balance.put(t[0], balance.getOrDefault(t[0], 0) - t[2]);
            balance.put(t[1], balance.getOrDefault(t[1], 0) + t[2]);
        }
        
        List<Integer> debts = new ArrayList<>();
        for (int amount : balance.values()) {
            if (amount != 0) {
                debts.add(amount);
            }
        }
        
        return dfs(0, debts);
    }
    
    private int dfs(int start, List<Integer> debts) {
        while (start < debts.size() && debts.get(start) == 0) {
            start++;
        }
        if (start == debts.size()) {
            return 0;
        }
        
        int minTransfers = Integer.MAX_VALUE;
        for (int i = start + 1; i < debts.size(); i++) {
            if (debts.get(start) * debts.get(i) < 0) {
                debts.set(i, debts.get(i) + debts.get(start));
                minTransfers = Math.min(minTransfers, 1 + dfs(start + 1, debts));
                debts.set(i, debts.get(i) - debts.get(start));
            }
        }
        
        return minTransfers;
    }
}