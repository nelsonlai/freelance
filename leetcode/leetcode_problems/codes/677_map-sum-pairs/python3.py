"""
Problem: Map Sum Pairs
Difficulty: Medium
Tags: string, hash

Approach: String manipulation with hash map or two pointers
Time Complexity: O(n) or O(n log n)
Space Complexity: O(n) for hash map
"""

class MapSum:
    def __init__(self):
        self.map = {}
        self.prefix_map = defaultdict(int)

    def insert(self, key: str, val: int) -> None:
        delta = val - self.map.get(key, 0)
        self.map[key] = val
        
        for i in range(1, len(key) + 1):
            self.prefix_map[key[:i]] += delta

    def sum(self, prefix: str) -> int:
        return self.prefix_map[prefix]