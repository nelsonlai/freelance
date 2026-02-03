class Solution:
    def dominantIndex(self, nums: List[int]) -> int:
        maxIdx = 0
        for i in range(1, len(nums)):
            if nums[i] > nums[maxIdx]:
                maxIdx = i
        
        for i in range(len(nums)):
            if i != maxIdx and nums[maxIdx] < 2 * nums[i]:
                return -1
        
        return maxIdx
