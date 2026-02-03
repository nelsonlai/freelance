class Solution {
    public int maxSubarraySumCircular(int[] nums) {
        int total = 0;
        for (int num : nums) {
            total += num;
        }
        
        int maxSum = nums[0], curMax = nums[0];
        int minSum = nums[0], curMin = nums[0];
        
        for (int i = 1; i < nums.length; i++) {
            curMax = Math.max(nums[i], curMax + nums[i]);
            maxSum = Math.max(maxSum, curMax);
            curMin = Math.min(nums[i], curMin + nums[i]);
            minSum = Math.min(minSum, curMin);
        }
        
        return total == minSum ? maxSum : Math.max(maxSum, total - minSum);
    }
}
