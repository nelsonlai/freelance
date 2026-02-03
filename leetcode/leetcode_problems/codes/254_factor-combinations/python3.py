"""
Problem: Factor Combinations
Difficulty: Medium
Tags: general

Approach: Optimized algorithm based on problem constraints
Time Complexity: O(n) to O(n^2) depending on approach
Space Complexity: O(1) to O(n) depending on approach
"""

class Solution:
    def getFactors(self, n: int) -> List[List[int]]:
        def backtrack(start, target, path, result):
            if target == 1 and len(path) > 1:
                result.append(path[:])
                return
            
            for i in range(start, int(target ** 0.5) + 1):
                if target % i == 0:
                    path.append(i)
                    backtrack(i, target // i, path, result)
                    path.pop()
            
            if target >= start:
                path.append(target)
                backtrack(target, 1, path, result)
                path.pop()
        
        result = []
        backtrack(2, n, [], result)
        return result