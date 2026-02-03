"""
Problem: Smallest String With A Given Numeric Value
Difficulty: Medium
Tags: string, greedy

Approach: Greedy - use 'a' as much as possible, then 'z' at the end
Time Complexity: O(n) where n is length
Space Complexity: O(n) for result string
"""

class Solution:
    def getSmallestString(self, n: int, k: int) -> str:
        result = ['a'] * n
        k -= n  # Each 'a' contributes 1
        
        for i in range(n - 1, -1, -1):
            if k <= 0:
                break
            add = min(k, 25)  # Max 25 to get 'z'
            result[i] = chr(ord('a') + add)
            k -= add
        
        return ''.join(result)