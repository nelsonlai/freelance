"""
Problem: Crawler Log Folder
Difficulty: Easy
Tags: array, string, stack

Approach: Simulate folder navigation, track depth
Time Complexity: O(n) where n is length of logs
Space Complexity: O(1)
"""

class Solution:
    def minOperations(self, logs: List[str]) -> int:
        depth = 0
        for log in logs:
            if log == '../':
                if depth > 0:
                    depth -= 1
            elif log != './':
                depth += 1
        return depth