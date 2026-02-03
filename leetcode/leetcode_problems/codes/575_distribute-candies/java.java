/**
 * Problem: Distribute Candies
 * Difficulty: Easy
 * Tags: array, hash
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) for hash map
 */

import java.util.*;

class Solution {
    public int distributeCandies(int[] candyType) {
        Set<Integer> uniqueTypes = new HashSet<>();
        for (int type : candyType) {
            uniqueTypes.add(type);
        }
        int maxCandies = candyType.length / 2;
        return Math.min(uniqueTypes.size(), maxCandies);
    }
}