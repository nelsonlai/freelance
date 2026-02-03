"""
Problem: Build an Array With Stack Operations
Difficulty: Medium
Tags: array, stack

Approach: Simulate - push numbers 1 to n, pop if not in target
Time Complexity: O(n) where n is max number
Space Complexity: O(n) for result
"""

class Solution:
    def buildArray(self, target: List[int], n: int) -> List[str]:
        result = []
        target_set = set(target)
        target_idx = 0
        
        for i in range(1, n + 1):
            result.append("Push")
            if i not in target_set:
                result.append("Pop")
            else:
                target_idx += 1
                if target_idx == len(target):
                    break
        
        return result