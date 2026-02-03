/**
 * Problem: Cutting Ribbons
 * Difficulty: Medium
 * Tags: array, search, binary search
 * 
 * Approach: Binary search on length, check if can get k pieces
 * Time Complexity: O(n log(max_length)) where max_length is max ribbon
 * Space Complexity: O(1)
 */

class Solution {
    public int maxLength(int[] ribbons, int k) {
        int left = 1;
        int right = 0;
        for (int r : ribbons) {
            right = Math.max(right, r);
        }
        
        int result = 0;
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (canCut(ribbons, k, mid)) {
                result = mid;
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
        
        return result;
    }
    
    private boolean canCut(int[] ribbons, int k, int length) {
        int count = 0;
        for (int ribbon : ribbons) {
            count += ribbon / length;
        }
        return count >= k;
    }
}