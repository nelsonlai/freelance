"""
Problem: Combination Sum III
Difficulty: Medium
Tags: array

Approach: Use two pointers or sliding window technique
Time Complexity: O(n) or O(n log n)
Space Complexity: O(1) to O(n) depending on approach
"""

class Solution:
    def combinationSum3(self, k: int, n: int) -> List[List[int]]:
        result = []
        
        def backtrack(start, remaining, path):
            if len(path) == k and remaining == 0:
                result.append(path[:])
                return
            
            if len(path) >= k or remaining < 0:
                return
            
            for i in range(start, 10):
                path.append(i)
                backtrack(i + 1, remaining - i, path)
                path.pop()
        
        backtrack(1, n, [])
        return result