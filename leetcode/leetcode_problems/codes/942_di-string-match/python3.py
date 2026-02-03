"""
Problem: DI String Match
Difficulty: Easy
Tags: array, string, greedy

Approach: Greedy - use smallest available number for 'I', largest for 'D'
Time Complexity: O(n)
Space Complexity: O(n) for result array
"""

class Solution:
    def diStringMatch(self, s: str) -> List[int]:
        n = len(s)
        result = []
        low, high = 0, n
        
        for char in s:
            if char == 'I':
                result.append(low)
                low += 1
            else:
                result.append(high)
                high -= 1
        
        result.append(low)  # or high, they're equal now
        return result