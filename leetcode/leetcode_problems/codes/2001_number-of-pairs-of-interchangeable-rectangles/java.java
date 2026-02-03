/**
 * Problem: Number of Pairs of Interchangeable Rectangles
 * Difficulty: Medium
 * Tags: array, math, hash
 * 
 * Approach: Count rectangles with same aspect ratio, calculate pairs using n*(n-1)/2
 * Time Complexity: O(n) where n is number of rectangles
 * Space Complexity: O(n) for hash map
 */

import java.util.*;

class Solution {
    public long interchangeableRectangles(int[][] rectangles) {
        Map<String, Integer> ratioCount = new HashMap<>();
        
        for (int[] rect : rectangles) {
            int w = rect[0], h = rect[1];
            int g = gcd(w, h);
            String ratio = (w / g) + "/" + (h / g);
            ratioCount.put(ratio, ratioCount.getOrDefault(ratio, 0) + 1);
        }
        
        long result = 0;
        for (int count : ratioCount.values()) {
            if (count > 1) {
                result += (long) count * (count - 1) / 2;
            }
        }
        
        return result;
    }
    
    private int gcd(int a, int b) {
        while (b != 0) {
            int temp = b;
            b = a % b;
            a = temp;
        }
        return a;
    }
}