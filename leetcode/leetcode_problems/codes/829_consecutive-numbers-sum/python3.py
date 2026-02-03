class Solution:
    def consecutiveNumbersSum(self, n: int) -> int:
        result = 0
        k = 1
        while k * (k - 1) < 2 * n:
            if (2 * n - k * (k - 1)) % (2 * k) == 0:
                result += 1
            k += 1
        return result
