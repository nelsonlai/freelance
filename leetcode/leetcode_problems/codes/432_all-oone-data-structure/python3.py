"""
Problem: All O`one Data Structure
Difficulty: Hard
Tags: string, hash, linked_list

Approach: String manipulation with hash map or two pointers
Time Complexity: O(n) or O(n log n)
Space Complexity: O(n) for hash map
"""

from collections import defaultdict

class AllOne:

    def __init__(self):
        self.count = defaultdict(int)
        self.min_count = float('inf')
        self.max_count = 0

    def inc(self, key: str) -> None:
        self.count[key] += 1
        count = self.count[key]
        self.max_count = max(self.max_count, count)
        if count == 1:
            self.min_count = min(self.min_count, 1)
        else:
            if self.min_count == count - 1:
                self.min_count = min([v for v in self.count.values() if v > 0], default=float('inf'))

    def dec(self, key: str) -> None:
        if key in self.count:
            self.count[key] -= 1
            if self.count[key] == 0:
                del self.count[key]
                if not self.count:
                    self.min_count = float('inf')
                    self.max_count = 0
                else:
                    self.min_count = min(self.count.values())
                    self.max_count = max(self.count.values())
            else:
                self.min_count = min(self.count.values())
                if self.max_count == self.count[key] + 1:
                    self.max_count = max(self.count.values())

    def getMaxKey(self) -> str:
        if not self.count:
            return ""
        for key, count in self.count.items():
            if count == self.max_count:
                return key
        return ""

    def getMinKey(self) -> str:
        if not self.count:
            return ""
        for key, count in self.count.items():
            if count == self.min_count:
                return key
        return ""