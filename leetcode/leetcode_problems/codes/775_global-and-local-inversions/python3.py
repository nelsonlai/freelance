class Solution:
    def isIdealPermutation(self, nums: List[int]) -> bool:
        maxVal = -1
        for i in range(len(nums) - 2):
            maxVal = max(maxVal, nums[i])
            if maxVal > nums[i + 2]:
                return False
        return True
