"""
Problem: Sum of k-Mirror Numbers
Difficulty: Hard
Tags: math, palindrome

Approach: Generate palindromes in base 10, check if also palindrome in base k
Time Complexity: O(n * log(n)) where n is number of palindromes to check
Space Complexity: O(1)
"""

class Solution:
    def kMirror(self, k: int, n: int) -> int:
        def isPalindromeInBase(num, base):
            digits = []
            while num > 0:
                digits.append(num % base)
                num //= base
            return digits == digits[::-1]
        
        def generatePalindromes():
            # Generate palindromes in base 10
            yield 1
            yield 2
            yield 3
            yield 4
            yield 5
            yield 6
            yield 7
            yield 8
            yield 9
            
            length = 2
            while True:
                # Generate palindromes of current length
                half = length // 2
                start = 10 ** (half - 1)
                end = 10 ** half
                
                for num in range(start, end):
                    num_str = str(num)
                    if length % 2 == 0:
                        palindrome = int(num_str + num_str[::-1])
                    else:
                        for mid in range(10):
                            palindrome = int(num_str + str(mid) + num_str[::-1])
                            yield palindrome
                    if length % 2 == 0:
                        yield palindrome
                
                length += 1
        
        result = 0
        count = 0
        for palindrome in generatePalindromes():
            if isPalindromeInBase(palindrome, k):
                result += palindrome
                count += 1
                if count == n:
                    break
        
        return result