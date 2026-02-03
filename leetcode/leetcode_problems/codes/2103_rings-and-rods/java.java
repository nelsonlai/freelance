/**
 * Problem: Rings and Rods
 * Difficulty: Easy
 * Tags: string, hash
 * 
 * Approach: String manipulation with hash map or two pointers
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) for hash map
 */

import java.util.*;

class Solution {
    public int countPoints(String rings) {
        Map<Character, Set<Character>> rods = new HashMap<>();
        for (int i = 0; i < rings.length(); i += 2) {
            char color = rings.charAt(i);
            char rod = rings.charAt(i + 1);
            rods.putIfAbsent(rod, new HashSet<>());
            rods.get(rod).add(color);
        }
        
        int count = 0;
        for (Set<Character> colors : rods.values()) {
            if (colors.size() == 3) {
                count++;
            }
        }
        return count;
    }
}