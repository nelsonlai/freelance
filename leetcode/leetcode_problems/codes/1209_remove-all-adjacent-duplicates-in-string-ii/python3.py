"""
Problem: Remove All Adjacent Duplicates in String II
Difficulty: Medium
Tags: string, tree, stack

Approach: Use stack to track characters and their counts, remove when count reaches k
Time Complexity: O(n) where n is the length of s
Space Complexity: O(n) for stack
"""

class Solution:
    def removeDuplicates(self, s: str, k: int) -> str:
        stack = []  # [(char, count)]
        
        for char in s:
            if stack and stack[-1][0] == char:
                stack[-1] = (char, stack[-1][1] + 1)
                if stack[-1][1] == k:
                    stack.pop()
            else:
                stack.append((char, 1))
        
        return ''.join(char * count for char, count in stack)