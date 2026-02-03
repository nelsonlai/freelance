class Solution:
    def maxSubarraySumCircular(self, nums: List[int]) -> int:
        total = sum(nums)
        max_sum = cur_max = nums[0]
        min_sum = cur_min = nums[0]
        
        for i in range(1, len(nums)):
            cur_max = max(nums[i], cur_max + nums[i])
            max_sum = max(max_sum, cur_max)
            cur_min = min(nums[i], cur_min + nums[i])
            min_sum = min(min_sum, cur_min)
        
        return max_sum if total == min_sum else max(max_sum, total - min_sum)
