"""
Problem: Matchsticks to Square
Difficulty: Medium
Tags: array, dp

Approach: Use two pointers or sliding window technique
Time Complexity: O(n) or O(n log n)
Space Complexity: O(n) or O(n * m) for DP table
"""

class Solution:
    def makesquare(self, matchsticks: List[int]) -> bool:
        total = sum(matchsticks)
        if total % 4 != 0:
            return False
        
        side = total // 4
        matchsticks.sort(reverse=True)
        sides = [0] * 4
        
        def backtrack(index):
            if index == len(matchsticks):
                return all(s == side for s in sides)
            
            for i in range(4):
                if sides[i] + matchsticks[index] <= side:
                    sides[i] += matchsticks[index]
                    if backtrack(index + 1):
                        return True
                    sides[i] -= matchsticks[index]
                    if sides[i] == 0:
                        break
            return False
        
        return backtrack(0)