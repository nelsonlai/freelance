"""
Problem: Verify Preorder Serialization of a Binary Tree
Difficulty: Medium
Tags: string, tree, stack

Approach: String manipulation with hash map or two pointers
Time Complexity: O(n) or O(n log n)
Space Complexity: O(h) for recursion stack where h is height
"""

class Solution:
    def isValidSerialization(self, preorder: str) -> bool:
        slots = 1
        for node in preorder.split(','):
            slots -= 1
            if slots < 0:
                return False
            if node != '#':
                slots += 2
        return slots == 0