"""
Problem: Design Skiplist
Difficulty: Hard
Tags: tree, sort, search, linked_list

Approach: Implement skip list with multiple levels, use random coin flip for level assignment
Time Complexity: O(log n) average for search/add/erase
Space Complexity: O(n) for storing nodes
"""

import random

class SkiplistNode:
    def __init__(self, val, level):
        self.val = val
        self.next = [None] * level

class Skiplist:

    def __init__(self):
        self.max_level = 16
        self.head = SkiplistNode(-1, self.max_level)
        self.level = 1

    def _random_level(self):
        level = 1
        while random.random() < 0.5 and level < self.max_level:
            level += 1
        return level

    def _find(self, target):
        update = [None] * self.max_level
        curr = self.head
        
        for i in range(self.level - 1, -1, -1):
            while curr.next[i] and curr.next[i].val < target:
                curr = curr.next[i]
            update[i] = curr
        
        return update

    def search(self, target: int) -> bool:
        update = self._find(target)
        if update[0].next[0] and update[0].next[0].val == target:
            return True
        return False

    def add(self, num: int) -> None:
        update = self._find(num)
        new_level = self._random_level()
        
        if new_level > self.level:
            for i in range(self.level, new_level):
                update[i] = self.head
            self.level = new_level
        
        new_node = SkiplistNode(num, new_level)
        for i in range(new_level):
            new_node.next[i] = update[i].next[i]
            update[i].next[i] = new_node

    def erase(self, num: int) -> bool:
        update = self._find(num)
        if not update[0].next[0] or update[0].next[0].val != num:
            return False
        
        node = update[0].next[0]
        for i in range(len(node.next)):
            update[i].next[i] = node.next[i]
        
        while self.level > 1 and self.head.next[self.level - 1] is None:
            self.level -= 1
        
        return True