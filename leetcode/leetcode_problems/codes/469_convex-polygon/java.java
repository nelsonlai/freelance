/**
 * Problem: Convex Polygon
 * Difficulty: Medium
 * Tags: array, math
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

import java.util.*;

class Solution {
    public boolean isConvex(List<List<Integer>> points) {
        int n = points.size();
        if (n < 3) {
            return false;
        }
        
        long prev = 0;
        for (int i = 0; i < n; i++) {
            List<Integer> o = points.get(i);
            List<Integer> a = points.get((i + 1) % n);
            List<Integer> b = points.get((i + 2) % n);
            
            long cross = crossProduct(o, a, b);
            if (cross != 0) {
                if (prev * cross < 0) {
                    return false;
                }
                prev = cross;
            }
        }
        
        return true;
    }
    
    private long crossProduct(List<Integer> o, List<Integer> a, List<Integer> b) {
        return (long)(a.get(0) - o.get(0)) * (b.get(1) - o.get(1)) - 
               (long)(a.get(1) - o.get(1)) * (b.get(0) - o.get(0));
    }
}