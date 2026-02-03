"""
Problem: Largest Palindrome Product
Difficulty: Hard
Tags: math

Approach: Optimized algorithm based on problem constraints
Time Complexity: O(n) to O(n^2) depending on approach
Space Complexity: O(1) to O(n) depending on approach
"""

class Solution:
    def largestPalindrome(self, n: int) -> int:
        if n == 1:
            return 9
        
        max_num = 10 ** n - 1
        min_num = 10 ** (n - 1)
        
        for i in range(max_num, min_num - 1, -1):
            palindrome = int(str(i) + str(i)[::-1])
            
            j = max_num
            while j * j >= palindrome:
                if palindrome % j == 0 and min_num <= palindrome // j <= max_num:
                    return palindrome % 1337
                j -= 1
        
        return 0