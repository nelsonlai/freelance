"""
Problem: Maximum Number of Weeks for Which You Can Work
Difficulty: Medium
Tags: array, greedy

Approach: If max project <= sum of others + 1, can complete all; otherwise limited by max
Time Complexity: O(n) where n is milestones
Space Complexity: O(1)
"""

class Solution:
    def numberOfWeeks(self, milestones: List[int]) -> int:
        total = sum(milestones)
        max_milestone = max(milestones)
        rest = total - max_milestone
        
        if max_milestone <= rest + 1:
            return total
        else:
            return 2 * rest + 1