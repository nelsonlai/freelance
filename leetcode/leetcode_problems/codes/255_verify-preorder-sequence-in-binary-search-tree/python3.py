"""
Problem: Verify Preorder Sequence in Binary Search Tree
Difficulty: Medium
Tags: array, tree, search, stack

Approach: Use two pointers or sliding window technique
Time Complexity: O(n) or O(n log n)
Space Complexity: O(h) for recursion stack where h is height
"""

class Solution:
    def verifyPreorder(self, preorder: List[int]) -> bool:
        stack = []
        lower_bound = float('-inf')
        
        for val in preorder:
            if val < lower_bound:
                return False
            
            while stack and val > stack[-1]:
                lower_bound = stack.pop()
            
            stack.append(val)
        
        return True