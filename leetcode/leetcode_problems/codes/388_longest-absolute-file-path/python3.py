"""
Problem: Longest Absolute File Path
Difficulty: Medium
Tags: string, tree, search, stack

Approach: String manipulation with hash map or two pointers
Time Complexity: O(n) or O(n log n)
Space Complexity: O(h) for recursion stack where h is height
"""

class Solution:
    def lengthLongestPath(self, input: str) -> int:
        lines = input.split('\n')
        stack = []
        max_length = 0
        
        for line in lines:
            depth = line.count('\t')
            name = line.replace('\t', '')
            
            while len(stack) > depth:
                stack.pop()
            
            current_length = (stack[-1] if stack else 0) + len(name) + (1 if stack else 0)
            
            if '.' in name:
                max_length = max(max_length, current_length)
            else:
                stack.append(current_length)
        
        return max_length