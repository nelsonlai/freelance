/**
 * Problem: Kids With the Greatest Number of Candies
 * Difficulty: Easy
 * Tags: array
 * 
 * Approach: Find max, check if each kid can have max with extra candies
 * Time Complexity: O(n) where n is length of candies
 * Space Complexity: O(n) for result
 */

import java.util.*;

class Solution {
    public List<Boolean> kidsWithCandies(int[] candies, int extraCandies) {
        int maxCandies = 0;
        for (int candy : candies) {
            maxCandies = Math.max(maxCandies, candy);
        }
        
        List<Boolean> result = new ArrayList<>();
        for (int candy : candies) {
            result.add(candy + extraCandies >= maxCandies);
        }
        
        return result;
    }
}