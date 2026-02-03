"""
Problem: Remove Duplicate Letters
Difficulty: Medium
Tags: string, graph, greedy, stack

Approach: String manipulation with hash map or two pointers
Time Complexity: O(n) or O(n log n)
Space Complexity: O(1) to O(n) depending on approach
"""

from collections import Counter

class Solution:
    def removeDuplicateLetters(self, s: str) -> str:
        count = Counter(s)
        stack = []
        seen = set()
        
        for char in s:
            count[char] -= 1
            if char in seen:
                continue
            
            while stack and stack[-1] > char and count[stack[-1]] > 0:
                seen.remove(stack.pop())
            
            stack.append(char)
            seen.add(char)
        
        return ''.join(stack)