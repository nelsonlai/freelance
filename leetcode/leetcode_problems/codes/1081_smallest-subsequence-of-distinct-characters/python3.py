"""
Problem: Smallest Subsequence of Distinct Characters
Difficulty: Medium
Tags: string, graph, greedy, stack

Approach: Monotonic stack - maintain lexicographically smallest subsequence
Time Complexity: O(n)
Space Complexity: O(n) for stack
"""

class Solution:
    def smallestSubsequence(self, s: str) -> str:
        last_occurrence = {char: i for i, char in enumerate(s)}
        stack = []
        seen = set()
        
        for i, char in enumerate(s):
            if char in seen:
                continue
            
            while stack and stack[-1] > char and last_occurrence[stack[-1]] > i:
                seen.remove(stack.pop())
            
            stack.append(char)
            seen.add(char)
        
        return ''.join(stack)