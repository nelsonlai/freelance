"""
Problem: Split Concatenated Strings
Difficulty: Medium
Tags: array, string, graph, greedy

Approach: Use two pointers or sliding window technique
Time Complexity: O(n) or O(n log n)
Space Complexity: O(1) to O(n) depending on approach
"""

class Solution:
    def splitLoopedString(self, strs: List[str]) -> str:
        strs = [max(s, s[::-1]) for s in strs]
        result = ''.join(strs)
        
        for i, s in enumerate(strs):
            for start in [s, s[::-1]]:
                for j in range(len(start)):
                    candidate = start[j:] + ''.join(strs[i+1:]) + ''.join(strs[:i]) + start[:j]
                    if candidate > result:
                        result = candidate
        
        return result