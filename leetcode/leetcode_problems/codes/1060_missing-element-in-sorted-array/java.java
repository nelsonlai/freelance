/**
 * Problem: Missing Element in Sorted Array
 * Difficulty: Medium
 * Tags: array, sort, search
 * 
 * Approach: Binary search - find position where missing count reaches k
 * Time Complexity: O(log n)
 * Space Complexity: O(1)
 */

class Solution {
    public int missingElement(int[] nums, int k) {
        int n = nums.length;
        if (k > missingCount(nums, n - 1)) {
            return nums[n - 1] + k - missingCount(nums, n - 1);
        }
        
        int left = 0, right = n - 1;
        while (left < right) {
            int mid = (left + right) / 2;
            if (missingCount(nums, mid) < k) {
                left = mid + 1;
            } else {
                right = mid;
            }
        }
        
        return nums[left - 1] + k - missingCount(nums, left - 1);
    }
    
    private int missingCount(int[] nums, int idx) {
        return nums[idx] - nums[0] - idx;
    }
}