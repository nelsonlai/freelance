"""
Problem: Count Number of Teams
Difficulty: Medium
Tags: array, tree, dp

Approach: For each middle soldier, count smaller/larger on left and right
Time Complexity: O(n^2) where n is length of rating
Space Complexity: O(1)
"""

class Solution:
    def numTeams(self, rating: List[int]) -> int:
        n = len(rating)
        count = 0
        
        for j in range(1, n - 1):
            left_smaller = sum(1 for i in range(j) if rating[i] < rating[j])
            left_larger = sum(1 for i in range(j) if rating[i] > rating[j])
            right_larger = sum(1 for k in range(j + 1, n) if rating[k] > rating[j])
            right_smaller = sum(1 for k in range(j + 1, n) if rating[k] < rating[j])
            
            count += left_smaller * right_larger + left_larger * right_smaller
        
        return count