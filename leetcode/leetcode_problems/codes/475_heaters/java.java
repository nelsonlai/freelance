/**
 * Problem: Heaters
 * Difficulty: Medium
 * Tags: array, sort, search
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

import java.util.*;

class Solution {
    public int findRadius(int[] houses, int[] heaters) {
        Arrays.sort(houses);
        Arrays.sort(heaters);
        int radius = 0;
        int i = 0;
        
        for (int house : houses) {
            while (i < heaters.length - 1 && 
                   Math.abs(heaters[i+1] - house) <= Math.abs(heaters[i] - house)) {
                i++;
            }
            radius = Math.max(radius, Math.abs(heaters[i] - house));
        }
        
        return radius;
    }
}