/**
 * Problem: Letter Tile Possibilities
 * Difficulty: Medium
 * Tags: string, hash
 * 
 * Approach: Backtracking - generate all possible sequences with counts
 * Time Complexity: O(2^n) worst case
 * Space Complexity: O(n) for recursion
 */

import java.util.*;

class Solution {
    private int result = 0;
    
    public int numTilePossibilities(String tiles) {
        Map<Character, Integer> count = new HashMap<>();
        for (char c : tiles.toCharArray()) {
            count.put(c, count.getOrDefault(c, 0) + 1);
        }
        
        backtrack(count);
        return result - 1; // Subtract empty sequence
    }
    
    private void backtrack(Map<Character, Integer> count) {
        result++;
        for (char c : count.keySet()) {
            if (count.get(c) > 0) {
                count.put(c, count.get(c) - 1);
                backtrack(count);
                count.put(c, count.get(c) + 1);
            }
        }
    }
}