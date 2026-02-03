"""
Problem: 24 Game
Difficulty: Hard
Tags: array, math

Approach: Use two pointers or sliding window technique
Time Complexity: O(n) or O(n log n)
Space Complexity: O(1) to O(n) depending on approach
"""

class Solution:
    def judgePoint24(self, cards: List[int]) -> bool:
        def dfs(nums):
            if len(nums) == 1:
                return abs(nums[0] - 24) < 1e-6
            
            for i in range(len(nums)):
                for j in range(i + 1, len(nums)):
                    a, b = nums[i], nums[j]
                    new_nums = [nums[k] for k in range(len(nums)) if k != i and k != j]
                    
                    for result in [a + b, a - b, b - a, a * b, a / b if b != 0 else None, b / a if a != 0 else None]:
                        if result is not None:
                            if dfs(new_nums + [result]):
                                return True
            
            return False
        
        return dfs(cards)