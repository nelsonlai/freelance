/**
 * Problem: Magnetic Force Between Two Balls
 * Difficulty: Medium
 * Tags: array, sort, search
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

import java.util.*;

class Solution {
    public int maxDistance(int[] position, int m) {
        Arrays.sort(position);
        int n = position.length;
        
        int left = 1, right = position[n-1] - position[0];
        int result = 0;
        
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (canPlace(position, m, mid)) {
                result = mid;
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
        
        return result;
    }
    
    private boolean canPlace(int[] position, int m, int distance) {
        int count = 1;
        int last = position[0];
        for (int i = 1; i < position.length; i++) {
            if (position[i] - last >= distance) {
                count++;
                last = position[i];
                if (count >= m) {
                    return true;
                }
            }
        }
        return false;
    }
}