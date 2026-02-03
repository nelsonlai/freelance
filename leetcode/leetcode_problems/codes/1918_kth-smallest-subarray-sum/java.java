/**
 * Problem: Kth Smallest Subarray Sum
 * Difficulty: Medium
 * Tags: array, search, binary search
 * 
 * Approach: Binary search on answer, count subarrays with sum <= target
 * Time Complexity: O(n log(sum)) where sum is total sum
 * Space Complexity: O(1)
 */

class Solution {
    public int kthSmallestSubarraySum(int[] nums, int k) {
        int left = Integer.MAX_VALUE;
        int right = 0;
        
        for (int num : nums) {
            left = Math.min(left, num);
            right += num;
        }
        
        int result = right;
        
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (countSubarrays(nums, mid) >= k) {
                result = mid;
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        }
        
        return result;
    }
    
    private int countSubarrays(int[] nums, int target) {
        int count = 0;
        int left = 0;
        int currentSum = 0;
        
        for (int right = 0; right < nums.length; right++) {
            currentSum += nums[right];
            while (currentSum > target) {
                currentSum -= nums[left];
                left++;
            }
            count += right - left + 1;
        }
        
        return count;
    }
}