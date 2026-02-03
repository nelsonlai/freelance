"""
Problem: Additive Number
Difficulty: Medium
Tags: string

Approach: String manipulation with hash map or two pointers
Time Complexity: O(n) or O(n log n)
Space Complexity: O(1) to O(n) depending on approach
"""

class Solution:
    def isAdditiveNumber(self, num: str) -> bool:
        def isValid(num1, num2, start):
            if start == len(num):
                return True
            
            total = num1 + num2
            total_str = str(total)
            
            if not num.startswith(total_str, start):
                return False
            
            return isValid(num2, total, start + len(total_str))
        
        n = len(num)
        for i in range(1, n // 2 + 1):
            if num[0] == '0' and i > 1:
                break
            num1 = int(num[:i])
            
            for j in range(i + 1, n):
                if num[i] == '0' and j > i + 1:
                    break
                num2 = int(num[i:j])
                
                if isValid(num1, num2, j):
                    return True
        
        return False