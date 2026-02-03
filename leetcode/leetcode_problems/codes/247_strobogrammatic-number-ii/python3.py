"""
Problem: Strobogrammatic Number II
Difficulty: Medium
Tags: array, string

Approach: Use two pointers or sliding window technique
Time Complexity: O(n) or O(n log n)
Space Complexity: O(1) to O(n) depending on approach
"""

class Solution:
    def findStrobogrammatic(self, n: int) -> List[str]:
        def helper(m):
            if m == 0:
                return ['']
            if m == 1:
                return ['0', '1', '8']
            
            prev = helper(m - 2)
            result = []
            for s in prev:
                if m != n:
                    result.append('0' + s + '0')
                result.append('1' + s + '1')
                result.append('6' + s + '9')
                result.append('8' + s + '8')
                result.append('9' + s + '6')
            return result
        
        return helper(n)