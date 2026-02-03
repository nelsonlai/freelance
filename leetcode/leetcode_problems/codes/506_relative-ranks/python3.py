"""
Problem: Relative Ranks
Difficulty: Easy
Tags: array, sort, queue, heap

Approach: Use two pointers or sliding window technique
Time Complexity: O(n) or O(n log n)
Space Complexity: O(1) to O(n) depending on approach
"""

class Solution:
    def findRelativeRanks(self, score: List[int]) -> List[str]:
        sorted_scores = sorted([(s, i) for i, s in enumerate(score)], reverse=True)
        result = [""] * len(score)
        medals = ["Gold Medal", "Silver Medal", "Bronze Medal"]
        
        for rank, (s, idx) in enumerate(sorted_scores):
            if rank < 3:
                result[idx] = medals[rank]
            else:
                result[idx] = str(rank + 1)
        
        return result