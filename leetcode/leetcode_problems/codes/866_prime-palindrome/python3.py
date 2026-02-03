class Solution:
    def primePalindrome(self, n: int) -> int:
        def isPrime(x):
            if x < 2:
                return False
            for i in range(2, int(x**0.5) + 1):
                if x % i == 0:
                    return False
            return True
        
        def reverse(x):
            result = 0
            while x:
                result = result * 10 + x % 10
                x //= 10
            return result
        
        if n <= 2:
            return 2
        if n <= 3:
            return 3
        if n <= 5:
            return 5
        if n <= 7:
            return 7
        if n <= 11:
            return 11
        
        length = len(str(n))
        for l in range(length, 10):
            for root in range(10**(l//2), 10**((l+1)//2)):
                s = str(root)
                palindrome = int(s + s[-2::-1] if l % 2 else s + s[::-1])
                if palindrome >= n and isPrime(palindrome):
                    return palindrome
        
        return -1
