class Solution:
    def preimageSizeFZF(self, k: int) -> int:
        def trailingZeroes(n):
            count = 0
            while n:
                n //= 5
                count += n
            return count
        
        left, right = 0, 5 * (k + 1)
        while left < right:
            mid = (left + right) // 2
            zeros = trailingZeroes(mid)
            if zeros < k:
                left = mid + 1
            else:
                right = mid
        
        count = 0
        n = left
        while trailingZeroes(n) == k:
            count += 1
            n += 1
        
        return count
