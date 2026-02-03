"""
Problem: Latest Time by Replacing Hidden Digits
Difficulty: Easy
Tags: string, greedy

Approach: Greedily maximize each digit from left to right with constraints
Time Complexity: O(1)
Space Complexity: O(1)
"""

class Solution:
    def maximumTime(self, time: str) -> str:
        result = list(time)
        
        # Hour: HH
        if result[0] == '?':
            if result[1] == '?' or int(result[1]) < 4:
                result[0] = '2'
            else:
                result[0] = '1'
        
        if result[1] == '?':
            if result[0] == '2':
                result[1] = '3'
            else:
                result[1] = '9'
        
        # Minute: MM
        if result[3] == '?':
            result[3] = '5'
        if result[4] == '?':
            result[4] = '9'
        
        return ''.join(result)