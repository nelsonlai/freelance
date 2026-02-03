class Solution:
    def countPrimeSetBits(self, left: int, right: int) -> int:
        primes = {2, 3, 5, 7, 11, 13, 17, 19}
        result = 0
        
        for num in range(left, right + 1):
            bits = bin(num).count('1')
            if bits in primes:
                result += 1
        
        return result
