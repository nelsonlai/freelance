"""
Problem: Final Value of Variable After Performing Operations
Difficulty: Easy
Tags: array, string

Approach: Count increment and decrement operations
Time Complexity: O(n) where n is number of operations
Space Complexity: O(1)
"""

class Solution:
    def finalValueAfterOperations(self, operations: List[str]) -> int:
        x = 0
        for op in operations:
            if '+' in op:
                x += 1
            else:
                x -= 1
        return x