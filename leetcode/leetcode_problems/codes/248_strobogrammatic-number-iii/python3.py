"""
Problem: Strobogrammatic Number III
Difficulty: Hard
Tags: array, string

Approach: Use two pointers or sliding window technique
Time Complexity: O(n) or O(n log n)
Space Complexity: O(1) to O(n) depending on approach
"""

class Solution:
    def strobogrammaticInRange(self, low: str, high: str) -> int:
        def findStrobogrammatic(n, m):
            if n == 0:
                return ['']
            if n == 1:
                return ['0', '1', '8']
            
            prev = findStrobogrammatic(n - 2, m)
            result = []
            for s in prev:
                if n != m:
                    result.append('0' + s + '0')
                result.append('1' + s + '1')
                result.append('6' + s + '9')
                result.append('8' + s + '8')
                result.append('9' + s + '6')
            return result
        
        def countUpTo(n_str):
            count = 0
            for length in range(1, len(n_str)):
                for num in findStrobogrammatic(length, length):
                    if len(num) == 1 or num[0] != '0':
                        count += 1
            
            valid = []
            for num in findStrobogrammatic(len(n_str), len(n_str)):
                if len(num) == 1 or num[0] != '0':
                    if len(num) < len(n_str) or num <= n_str:
                        valid.append(num)
            count += len(valid)
            return count
        
        low_count = countUpTo(low)
        if self.isStrobogrammatic(low):
            low_count -= 1
        
        return max(0, countUpTo(high) - low_count)
    
    def isStrobogrammatic(self, num: str) -> bool:
        strobogrammatic = {'0': '0', '1': '1', '6': '9', '8': '8', '9': '6'}
        left, right = 0, len(num) - 1
        while left <= right:
            if num[left] not in strobogrammatic or strobogrammatic[num[left]] != num[right]:
                return False
            left += 1
            right -= 1
        return True