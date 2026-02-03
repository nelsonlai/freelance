"""
Problem: Lexicographically Smallest String After Applying Operations
Difficulty: Medium
Tags: string, graph, search

Approach: String manipulation with hash map or two pointers
Time Complexity: O(n) or O(n log n)
Space Complexity: O(1) to O(n) depending on approach
"""

class Solution:
    def findLexSmallestString(self, s: str, a: int, b: int) -> str:
        from collections import deque
        
        queue = deque([s])
        visited = {s}
        result = s
        
        while queue:
            current = queue.popleft()
            result = min(result, current)
            
            # Rotate
            rotated = current[-b:] + current[:-b]
            if rotated not in visited:
                visited.add(rotated)
                queue.append(rotated)
            
            # Add a to odd indices
            chars = list(current)
            for i in range(1, len(chars), 2):
                chars[i] = str((int(chars[i]) + a) % 10)
            added = ''.join(chars)
            if added not in visited:
                visited.add(added)
                queue.append(added)
        
        return result