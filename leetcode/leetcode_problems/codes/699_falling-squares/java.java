/**
 * Problem: Falling Squares
 * Difficulty: Hard
 * Tags: array, tree, stack
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(h) for recursion stack where h is height
 */

import java.util.*;

class Solution {
    public List<Integer> fallingSquares(int[][] positions) {
        List<Integer> result = new ArrayList<>();
        List<int[]> heights = new ArrayList<>();
        
        for (int[] pos : positions) {
            int left = pos[0];
            int sideLength = pos[1];
            int right = left + sideLength;
            int currentHeight = sideLength;
            
            for (int[] h : heights) {
                int prevLeft = h[0];
                int prevRight = h[1];
                int prevHeight = h[2];
                
                if (right > prevLeft && left < prevRight) {
                    currentHeight = Math.max(currentHeight, prevHeight + sideLength);
                }
            }
            
            heights.add(new int[]{left, right, currentHeight});
            int maxHeight = 0;
            for (int[] h : heights) {
                maxHeight = Math.max(maxHeight, h[2]);
            }
            result.add(maxHeight);
        }
        
        return result;
    }
}