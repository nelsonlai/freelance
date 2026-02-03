/**
 * Problem: Freedom Trail
 * Difficulty: Hard
 * Tags: string, dp, search
 * 
 * Approach: String manipulation with hash map or two pointers
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) or O(n * m) for DP table
 */

import java.util.*;

class Solution {
    private Map<String, Integer> memo = new HashMap<>();
    
    public int findRotateSteps(String ring, String key) {
        Map<Character, List<Integer>> charPositions = new HashMap<>();
        for (int i = 0; i < ring.length(); i++) {
            charPositions.computeIfAbsent(ring.charAt(i), k -> new ArrayList<>()).add(i);
        }
        return dp(0, 0, ring, key, charPositions);
    }
    
    private int dp(int ringPos, int keyPos, String ring, String key, Map<Character, List<Integer>> charPositions) {
        if (keyPos == key.length()) {
            return 0;
        }
        
        String memoKey = ringPos + "," + keyPos;
        if (memo.containsKey(memoKey)) {
            return memo.get(memoKey);
        }
        
        int minSteps = Integer.MAX_VALUE;
        char targetChar = key.charAt(keyPos);
        
        for (int pos : charPositions.get(targetChar)) {
            int steps = Math.min(Math.abs(pos - ringPos), ring.length() - Math.abs(pos - ringPos));
            minSteps = Math.min(minSteps, steps + 1 + dp(pos, keyPos + 1, ring, key, charPositions));
        }
        
        memo.put(memoKey, minSteps);
        return minSteps;
    }
}