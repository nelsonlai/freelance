"""
Problem: Minimum Number of Swaps to Make the String Balanced
Difficulty: Medium
Tags: array, string, greedy, stack

Approach: Count unmatched closing brackets, need (count+1)//2 swaps
Time Complexity: O(n) where n is length
Space Complexity: O(1)
"""

class Solution:
    def minSwaps(self, s: str) -> int:
        balance = 0
        max_unmatched = 0
        
        for char in s:
            if char == '[':
                balance += 1
            else:
                balance -= 1
            max_unmatched = max(max_unmatched, -balance)
        
        return (max_unmatched + 1) // 2