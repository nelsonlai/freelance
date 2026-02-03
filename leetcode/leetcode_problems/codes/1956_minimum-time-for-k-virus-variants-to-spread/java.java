/**
 * Problem: Minimum Time For K Virus Variants to Spread
 * Difficulty: Hard
 * Tags: array, math, search, binary search, geometry
 * 
 * Approach: Binary search on time, check if k points can be covered by circles
 * Time Complexity: O(n^2 * log(max_time))
 * Space Complexity: O(1)
 */

import java.util.*;

class Solution {
    public int minDayskVariants(int[][] points, int k) {
        int left = 0, right = (int) 1e9;
        int result = right;
        
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (canCover(points, k, mid)) {
                result = mid;
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        }
        
        return result;
    }
    
    private boolean canCover(int[][] points, int k, int t) {
        int n = points.length;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                // Try circle centered at midpoint of points[i] and points[j]
                double cx = (points[i][0] + points[j][0]) / 2.0;
                double cy = (points[i][1] + points[j][1]) / 2.0;
                int count = 0;
                
                for (int[] point : points) {
                    double dist = Math.sqrt(
                        Math.pow(point[0] - cx, 2) + Math.pow(point[1] - cy, 2)
                    );
                    if (dist <= t) {
                        count++;
                    }
                }
                
                if (count >= k) {
                    return true;
                }
            }
        }
        return false;
    }
}
