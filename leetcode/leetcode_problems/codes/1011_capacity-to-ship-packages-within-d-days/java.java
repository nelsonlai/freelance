/**
 * Problem: Capacity To Ship Packages Within D Days
 * Difficulty: Medium
 * Tags: array, search
 * 
 * Approach: Binary search on capacity - find minimum capacity that allows shipping in d days
 * Time Complexity: O(n * log(sum(weights)))
 * Space Complexity: O(1)
 */

class Solution {
    public int shipWithinDays(int[] weights, int days) {
        int left = 0, right = 0;
        for (int w : weights) {
            left = Math.max(left, w);
            right += w;
        }
        
        while (left < right) {
            int mid = (left + right) / 2;
            if (canShip(weights, days, mid)) {
                right = mid;
            } else {
                left = mid + 1;
            }
        }
        
        return left;
    }
    
    private boolean canShip(int[] weights, int days, int capacity) {
        int current = 0;
        int needed = 1;
        for (int weight : weights) {
            if (current + weight > capacity) {
                needed++;
                current = weight;
            } else {
                current += weight;
            }
        }
        return needed <= days;
    }
}