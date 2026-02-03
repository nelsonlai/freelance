"""
Problem: Super Washing Machines
Difficulty: Hard
Tags: array, greedy

Approach: Use two pointers or sliding window technique
Time Complexity: O(n) or O(n log n)
Space Complexity: O(1) to O(n) depending on approach
"""

class Solution:
    def findMinMoves(self, machines: List[int]) -> int:
        total = sum(machines)
        n = len(machines)
        
        if total % n != 0:
            return -1
        
        target = total // n
        result = 0
        balance = 0
        
        for load in machines:
            balance += load - target
            result = max(result, abs(balance), load - target)
        
        return result