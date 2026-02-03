/**
 * Problem: Find in Mountain Array
 * Difficulty: Hard
 * Tags: array, search
 * 
 * Approach: Find peak, then binary search in both ascending and descending parts
 * Time Complexity: O(log n)
 * Space Complexity: O(1)
 */

/**
 * // This is MountainArray's API interface.
 * // You should not implement it, or speculate about its implementation
 * interface MountainArray {
 *     public int get(int index);
 *     public int length();
 * }
 */
 
class Solution {
    public int findInMountainArray(int target, MountainArray mountainArr) {
        int n = mountainArr.length();
        
        // Find peak
        int left = 0, right = n - 1;
        while (left < right) {
            int mid = (left + right) / 2;
            if (mountainArr.get(mid) < mountainArr.get(mid + 1)) {
                left = mid + 1;
            } else {
                right = mid;
            }
        }
        int peak = left;
        
        // Search in ascending part
        left = 0;
        right = peak;
        while (left <= right) {
            int mid = (left + right) / 2;
            int val = mountainArr.get(mid);
            if (val == target) {
                return mid;
            } else if (val < target) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
        
        // Search in descending part
        left = peak;
        right = n - 1;
        while (left <= right) {
            int mid = (left + right) / 2;
            int val = mountainArr.get(mid);
            if (val == target) {
                return mid;
            } else if (val > target) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
        
        return -1;
    }
}