class Solution {
    public int numSubarrayBoundedMax(int[] nums, int left, int right) {
        return count(nums, right) - count(nums, left - 1);
    }
    
    private int count(int[] nums, int bound) {
        int result = 0;
        int cur = 0;
        for (int num : nums) {
            cur = num <= bound ? cur + 1 : 0;
            result += cur;
        }
        return result;
    }
}
