"""
Problem: Repeated String Match
Difficulty: Medium
Tags: string, tree

Approach: String manipulation with hash map or two pointers
Time Complexity: O(n) or O(n log n)
Space Complexity: O(h) for recursion stack where h is height
"""

class Solution:
    def repeatedStringMatch(self, a: str, b: str) -> int:
        if not b:
            return 0
        
        count = (len(b) + len(a) - 1) // len(a)
        repeated = a * count
        
        if b in repeated:
            return count
        
        repeated += a
        if b in repeated:
            return count + 1
        
        return -1