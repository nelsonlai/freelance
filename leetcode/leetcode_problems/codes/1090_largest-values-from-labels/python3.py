"""
Problem: Largest Values From Labels
Difficulty: Medium
Tags: array, greedy, hash, sort

Approach: Sort by value descending, greedily select respecting label limits
Time Complexity: O(n log n) for sorting
Space Complexity: O(n) for items and label counts
"""

class Solution:
    def largestValsFromLabels(self, values: List[int], labels: List[int], numWanted: int, useLimit: int) -> int:
        items = sorted(zip(values, labels), reverse=True)
        label_count = {}
        result = 0
        count = 0
        
        for value, label in items:
            if count >= numWanted:
                break
            if label_count.get(label, 0) < useLimit:
                result += value
                label_count[label] = label_count.get(label, 0) + 1
                count += 1
        
        return result