"""
Problem: Erect the Fence
Difficulty: Hard
Tags: array, tree, math

Approach: Use two pointers or sliding window technique
Time Complexity: O(n) or O(n log n)
Space Complexity: O(h) for recursion stack where h is height
"""

class Solution:
    def outerTrees(self, trees: List[List[int]]) -> List[List[int]]:
        def cross(o, a, b):
            return (a[0] - o[0]) * (b[1] - o[1]) - (a[1] - o[1]) * (b[0] - o[0])
        
        trees.sort()
        lower = []
        for tree in trees:
            while len(lower) >= 2 and cross(lower[-2], lower[-1], tree) < 0:
                lower.pop()
            lower.append(tuple(tree))
        
        upper = []
        for tree in reversed(trees):
            while len(upper) >= 2 and cross(upper[-2], upper[-1], tree) < 0:
                upper.pop()
            upper.append(tuple(tree))
        
        return list(set(lower[:-1] + upper[:-1]))