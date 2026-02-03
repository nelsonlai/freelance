/**
 * Problem: Maximum Average Subarray II
 * Difficulty: Hard
 * Tags: array, search
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

class Solution {
    public double findMaxAverage(int[] nums, int k) {
        double left = Integer.MIN_VALUE, right = Integer.MAX_VALUE;
        for (int num : nums) {
            left = Math.min(left, num);
            right = Math.max(right, num);
        }
        
        while (right - left > 1e-5) {
            double mid = (left + right) / 2;
            if (canAchieve(nums, k, mid)) {
                left = mid;
            } else {
                right = mid;
            }
        }
        
        return left;
    }
    
    private boolean canAchieve(int[] nums, int k, double target) {
        double[] prefix = new double[nums.length + 1];
        double minPrefix = 0;
        
        for (int i = 0; i < nums.length; i++) {
            prefix[i + 1] = prefix[i] + nums[i] - target;
            if (i >= k - 1) {
                if (prefix[i + 1] >= minPrefix) {
                    return true;
                }
                minPrefix = Math.min(minPrefix, prefix[i - k + 2]);
            }
        }
        
        return false;
    }
}