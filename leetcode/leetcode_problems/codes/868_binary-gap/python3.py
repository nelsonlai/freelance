class Solution:
    def binaryGap(self, n: int) -> int:
        last = None
        result = 0
        i = 0
        while n:
            if n & 1:
                if last is not None:
                    result = max(result, i - last)
                last = i
            n >>= 1
            i += 1
        return result
