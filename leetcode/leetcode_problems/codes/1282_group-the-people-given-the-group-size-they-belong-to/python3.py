"""
Problem: Group the People Given the Group Size They Belong To
Difficulty: Medium
Tags: array, greedy, hash

Approach: Group by size, split into groups of that size
Time Complexity: O(n) where n is length of groupSizes
Space Complexity: O(n) for groups
"""

from collections import defaultdict

class Solution:
    def groupThePeople(self, groupSizes: List[int]) -> List[List[int]]:
        groups_by_size = defaultdict(list)
        for i, size in enumerate(groupSizes):
            groups_by_size[size].append(i)
        
        result = []
        for size, people in groups_by_size.items():
            for i in range(0, len(people), size):
                result.append(people[i:i+size])
        
        return result