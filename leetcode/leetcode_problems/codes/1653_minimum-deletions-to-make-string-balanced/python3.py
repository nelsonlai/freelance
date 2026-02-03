"""
Problem: Minimum Deletions to Make String Balanced
Difficulty: Medium
Tags: string, dp, greedy

Approach: For each position, count b's before and a's after, find minimum deletions
Time Complexity: O(n) where n is length
Space Complexity: O(1)
"""

class Solution:
    def minimumDeletions(self, s: str) -> int:
        total_a = s.count('a')
        b_count = 0
        a_count = total_a
        min_deletions = total_a
        
        for char in s:
            if char == 'b':
                b_count += 1
            else:
                a_count -= 1
            min_deletions = min(min_deletions, b_count + a_count)
        
        return min_deletions