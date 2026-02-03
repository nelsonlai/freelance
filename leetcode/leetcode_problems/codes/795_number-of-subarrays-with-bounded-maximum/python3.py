class Solution:
    def numSubarrayBoundedMax(self, nums: List[int], left: int, right: int) -> int:
        def count(bound):
            result = 0
            cur = 0
            for num in nums:
                cur = cur + 1 if num <= bound else 0
                result += cur
            return result
        
        return count(right) - count(left - 1)
