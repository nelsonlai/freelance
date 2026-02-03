"""
Problem: Stamping The Sequence
Difficulty: Hard
Tags: array, string, greedy, stack, queue

Approach: Work backwards - find positions where stamp can be placed, greedily stamp
Time Complexity: O(n * m) where n is target length, m is stamp length
Space Complexity: O(n) for result and visited array
"""

class Solution:
    def movesToStamp(self, stamp: str, target: str) -> List[int]:
        n, m = len(target), len(stamp)
        target_list = list(target)
        result = []
        visited = [False] * n
        
        def canStamp(pos):
            changed = False
            for i in range(m):
                if target_list[pos + i] == '?':
                    continue
                if target_list[pos + i] != stamp[i]:
                    return False
                changed = True
            if changed:
                for i in range(m):
                    target_list[pos + i] = '?'
            return changed
        
        changed = True
        while changed:
            changed = False
            for i in range(n - m + 1):
                if not visited[i] and canStamp(i):
                    visited[i] = True
                    result.append(i)
                    changed = True
        
        return result[::-1] if all(c == '?' for c in target_list) else []