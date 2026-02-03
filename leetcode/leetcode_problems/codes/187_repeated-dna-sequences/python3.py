"""
Problem: Repeated DNA Sequences
Difficulty: Medium
Tags: array, string, tree, hash

Approach: Use two pointers or sliding window technique
Time Complexity: O(n) or O(n log n)
Space Complexity: O(h) for recursion stack where h is height
"""

from collections import defaultdict

class Solution:
    def findRepeatedDnaSequences(self, s: str) -> List[str]:
        if len(s) < 10:
            return []
        
        seen = defaultdict(int)
        result = []
        
        for i in range(len(s) - 9):
            sequence = s[i:i+10]
            seen[sequence] += 1
            if seen[sequence] == 2:
                result.append(sequence)
        
        return result