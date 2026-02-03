"""
Problem: Check If a String Can Break Another String
Difficulty: Medium
Tags: string, greedy, sort

Approach: Sort both strings, check if s1 >= s2 or s2 >= s1 at all positions
Time Complexity: O(n log n) for sorting
Space Complexity: O(n) for sorted strings
"""

class Solution:
    def checkIfCanBreak(self, s1: str, s2: str) -> bool:
        sorted_s1 = sorted(s1)
        sorted_s2 = sorted(s2)
        
        s1_breaks = all(sorted_s1[i] >= sorted_s2[i] for i in range(len(s1)))
        s2_breaks = all(sorted_s2[i] >= sorted_s1[i] for i in range(len(s1)))
        
        return s1_breaks or s2_breaks