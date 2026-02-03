"""
Problem: Merge Triplets to Form Target Triplet
Difficulty: Medium
Tags: array, greedy

Approach: Only use triplets where all values <= target, check if can form target
Time Complexity: O(n) where n is triplets
Space Complexity: O(1)
"""

class Solution:
    def mergeTriplets(self, triplets: List[List[int]], target: List[int]) -> bool:
        found = [False] * 3
        
        for triplet in triplets:
            if all(triplet[i] <= target[i] for i in range(3)):
                for i in range(3):
                    if triplet[i] == target[i]:
                        found[i] = True
        
        return all(found)