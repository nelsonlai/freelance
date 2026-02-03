"""
Problem: Find the Celebrity
Difficulty: Medium
Tags: array, graph

Approach: Use two pointers or sliding window technique
Time Complexity: O(n) or O(n log n)
Space Complexity: O(1) to O(n) depending on approach
"""

# The knows API is already defined for you.
# return a bool, whether a knows b
# def knows(a: int, b: int) -> bool:

class Solution:
    def findCelebrity(self, n: int) -> int:
        candidate = 0
        
        for i in range(1, n):
            if knows(candidate, i):
                candidate = i
        
        for i in range(n):
            if i != candidate:
                if knows(candidate, i) or not knows(i, candidate):
                    return -1
        
        return candidate