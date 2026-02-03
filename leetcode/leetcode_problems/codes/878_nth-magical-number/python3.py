class Solution:
    def nthMagicalNumber(self, n: int, a: int, b: int) -> int:
        MOD = 10**9 + 7
        
        def gcd(x, y):
            while y:
                x, y = y, x % y
            return x
        
        L = a * b // gcd(a, b)
        left, right = 0, n * min(a, b)
        
        while left < right:
            mid = (left + right) // 2
            if mid // a + mid // b - mid // L < n:
                left = mid + 1
            else:
                right = mid
        
        return left % MOD
