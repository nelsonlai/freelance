"""
Problem: Find a Value of a Mysterious Function Closest to Target
Difficulty: Hard
Tags: array, tree, search

Approach: For each starting position, track AND values, update minimum difference
Time Complexity: O(n^2) in worst case, but typically O(n * log(max(arr)))
Space Complexity: O(log(max(arr))) for unique AND values
"""

class Solution:
    def closestToTarget(self, arr: List[int], target: int) -> int:
        result = float('inf')
        
        for i in range(len(arr)):
            current_and = arr[i]
            result = min(result, abs(current_and - target))
            
            for j in range(i + 1, len(arr)):
                current_and &= arr[j]
                result = min(result, abs(current_and - target))
                
                if current_and < target:
                    break
        
        return result