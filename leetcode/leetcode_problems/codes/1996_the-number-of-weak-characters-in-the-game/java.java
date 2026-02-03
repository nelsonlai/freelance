/**
 * Problem: The Number of Weak Characters in the Game
 * Difficulty: Medium
 * Tags: array, greedy, sort
 * 
 * Approach: Sort by attack descending, defense ascending, track max defense
 * Time Complexity: O(n log n) for sorting
 * Space Complexity: O(1)
 */

import java.util.*;

class Solution {
    public int numberOfWeakCharacters(int[][] properties) {
        Arrays.sort(properties, (a, b) -> {
            if (a[0] != b[0]) {
                return Integer.compare(b[0], a[0]);  // Descending by attack
            }
            return Integer.compare(a[1], b[1]);  // Ascending by defense
        });
        
        int count = 0;
        int maxDefense = 0;
        
        for (int[] prop : properties) {
            if (prop[1] < maxDefense) {
                count++;
            }
            maxDefense = Math.max(maxDefense, prop[1]);
        }
        
        return count;
    }
}