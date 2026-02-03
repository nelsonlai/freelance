class Solution:
    def rotatedDigits(self, n: int) -> int:
        valid = {0, 1, 8, 2, 5, 6, 9}
        invalid = {3, 4, 7}
        result = 0
        
        for num in range(1, n + 1):
            digits = set(int(d) for d in str(num))
            if digits & invalid:
                continue
            if digits & {2, 5, 6, 9}:
                result += 1
        
        return result
