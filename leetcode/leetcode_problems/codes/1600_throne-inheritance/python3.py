"""
Problem: Throne Inheritance
Difficulty: Medium
Tags: string, tree, hash, search

Approach: Build tree structure, use DFS for inheritance order
Time Complexity: O(n) for getInheritanceOrder where n is descendants
Space Complexity: O(n) for tree
"""

from collections import defaultdict

class ThroneInheritance:

    def __init__(self, kingName: str):
        self.king = kingName
        self.children = defaultdict(list)
        self.dead = set()

    def birth(self, parentName: str, childName: str) -> None:
        self.children[parentName].append(childName)

    def death(self, name: str) -> None:
        self.dead.add(name)

    def getInheritanceOrder(self) -> List[str]:
        result = []
        
        def dfs(name):
            if name not in self.dead:
                result.append(name)
            for child in self.children[name]:
                dfs(child)
        
        dfs(self.king)
        return result