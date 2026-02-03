class Solution:
    def sumSubseqWidths(self, nums: List[int]) -> int:
        MOD = 10**9 + 7
        nums.sort()
        n = len(nums)
        result = 0
        
        pow2 = [1]
        for i in range(1, n):
            pow2.append(pow2[-1] * 2 % MOD)
        
        for i, num in enumerate(nums):
            result = (result + num * (pow2[i] - pow2[n - 1 - i])) % MOD
        
        return result
