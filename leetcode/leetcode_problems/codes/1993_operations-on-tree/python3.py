"""
Problem: Operations on Tree
Difficulty: Medium
Tags: array, tree, hash, search

Approach: Tree with locking mechanism - check ancestors and descendants
Time Complexity: O(n) for unlock, O(h) for lock where h is height
Space Complexity: O(n)
"""

from collections import defaultdict

class LockingTree:
    def __init__(self, parent: List[int]):
        self.parent = parent
        self.locked = {}
        self.children = defaultdict(list)
        for i, p in enumerate(parent):
            if p != -1:
                self.children[p].append(i)
    
    def lock(self, num: int, user: int) -> bool:
        if num in self.locked:
            return False
        self.locked[num] = user
        return True
    
    def unlock(self, num: int, user: int) -> bool:
        if num not in self.locked or self.locked[num] != user:
            return False
        del self.locked[num]
        return True
    
    def upgrade(self, num: int, user: int) -> bool:
        if num in self.locked:
            return False
        
        # Check if any ancestor is locked
        node = num
        while node != -1:
            if node in self.locked:
                return False
            node = self.parent[node]
        
        # Check if any descendant is locked
        def has_locked_descendant(node):
            if node in self.locked:
                return True
            for child in self.children[node]:
                if has_locked_descendant(child):
                    return True
            return False
        
        if not has_locked_descendant(num):
            return False
        
        # Unlock all descendants
        def unlock_descendants(node):
            if node in self.locked:
                del self.locked[node]
            for child in self.children[node]:
                unlock_descendants(child)
        
        unlock_descendants(num)
        self.locked[num] = user
        return True