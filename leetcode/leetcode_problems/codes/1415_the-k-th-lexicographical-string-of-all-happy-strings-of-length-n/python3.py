"""
Problem: The k-th Lexicographical String of All Happy Strings of Length n
Difficulty: Medium
Tags: string, graph, sort

Approach: Generate happy strings in lexicographical order, return k-th
Time Complexity: O(n * 3^n) in worst case
Space Complexity: O(n) for recursion
"""

class Solution:
    def getHappyString(self, n: int, k: int) -> str:
        result = []
        count = 0
        
        def backtrack(current):
            nonlocal count
            if len(current) == n:
                count += 1
                if count == k:
                    result.append(''.join(current))
                return
            
            for char in 'abc':
                if not current or current[-1] != char:
                    current.append(char)
                    backtrack(current)
                    current.pop()
                    if result:
                        return
        
        backtrack([])
        return result[0] if result else ""