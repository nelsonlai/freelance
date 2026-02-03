/**
 * Problem: Random Point in Non-overlapping Rectangles
 * Difficulty: Medium
 * Tags: array, math, search
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

import java.util.*;

class Solution {
    private int[][] rects;
    private int[] weights;
    private Random random;

    public Solution(int[][] rects) {
        this.rects = rects;
        this.random = new Random();
        this.weights = new int[rects.length];
        
        int total = 0;
        for (int i = 0; i < rects.length; i++) {
            int area = (rects[i][2] - rects[i][0] + 1) * (rects[i][3] - rects[i][1] + 1);
            total += area;
            weights[i] = total;
        }
    }
    
    public int[] pick() {
        int target = random.nextInt(weights[weights.length - 1]);
        int index = Arrays.binarySearch(weights, target + 1);
        if (index < 0) {
            index = -(index + 1);
        }
        
        int[] rect = rects[index];
        int x = random.nextInt(rect[2] - rect[0] + 1) + rect[0];
        int y = random.nextInt(rect[3] - rect[1] + 1) + rect[1];
        
        return new int[]{x, y};
    }
}

/**
 * Your Solution object will be instantiated and called as such:
 * Solution obj = new Solution(rects);
 * int[] param_1 = obj.pick();
 */