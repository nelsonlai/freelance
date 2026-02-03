class Solution:
    def smallestRangeI(self, nums: List[int], k: int) -> int:
        min_val = min(nums)
        max_val = max(nums)
        return max(0, max_val - min_val - 2 * k)
