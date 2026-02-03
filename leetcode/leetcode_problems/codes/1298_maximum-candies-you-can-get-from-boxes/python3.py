"""
Problem: Maximum Candies You Can Get from Boxes
Difficulty: Hard
Tags: array, graph, search

Approach: BFS - start with initial boxes, collect keys and open boxes
Time Complexity: O(n + m) where n is boxes, m is total keys/contained boxes
Space Complexity: O(n) for queue and visited
"""

from collections import deque

class Solution:
    def maxCandies(self, status: List[int], candies: List[int], keys: List[List[int]], containedBoxes: List[List[int]], initialBoxes: List[int]) -> int:
        n = len(status)
        opened = [False] * n
        has_key = status[:]
        queue = deque(initialBoxes)
        total_candies = 0
        
        while queue:
            box = queue.popleft()
            if opened[box]:
                continue
            
            if has_key[box]:
                opened[box] = True
                total_candies += candies[box]
                
                # Collect keys
                for key in keys[box]:
                    if not has_key[key]:
                        has_key[key] = True
                        if not opened[key]:
                            queue.append(key)
                
                # Add contained boxes
                for contained in containedBoxes[box]:
                    if not opened[contained]:
                        queue.append(contained)
            else:
                # Don't have key yet, add back to queue
                queue.append(box)
        
        return total_candies