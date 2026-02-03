class Solution(object):
    def permuteUnique(self, nums):
        """
        :type nums: List[int]
        :rtype: List[List[int]]
        """
        nums.sort()
        result = []
        used = [False] * len(nums)
        
        def backtrack(current):
            if len(current) == len(nums):
                result.append(current[:])
                return
            
            for i in range(len(nums)):
                if used[i] or (i > 0 and nums[i] == nums[i-1] and not used[i-1]):
                    continue
                used[i] = True
                current.append(nums[i])
                backtrack(current)
                current.pop()
                used[i] = False
        
        backtrack([])
        return result