"""
Problem: Maximum Number of People That Can Be Caught in Tag
Difficulty: Medium
Tags: array, greedy, two pointers

Approach: Two pointers - match taggers (1) with runners (0) within distance
Time Complexity: O(n) where n is length
Space Complexity: O(1)
"""

class Solution:
    def catchMaximumAmountofPeople(self, team: List[int], dist: int) -> int:
        taggers = [i for i, t in enumerate(team) if t == 1]
        runners = [i for i, t in enumerate(team) if t == 0]
        
        if not taggers or not runners:
            return 0
        
        count = 0
        t_idx = r_idx = 0
        
        while t_idx < len(taggers) and r_idx < len(runners):
            if abs(taggers[t_idx] - runners[r_idx]) <= dist:
                count += 1
                t_idx += 1
                r_idx += 1
            elif taggers[t_idx] < runners[r_idx]:
                t_idx += 1
            else:
                r_idx += 1
        
        return count