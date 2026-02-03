"""
Problem: Delete Duplicate Folders in System
Difficulty: Hard
Tags: array, string, hash, trie, tree serialization

Approach: Build trie, serialize subtrees, mark duplicates, collect non-duplicate paths
Time Complexity: O(n * m) where n is paths, m is avg depth
Space Complexity: O(n * m)
"""

from collections import defaultdict

class TrieNode:
    def __init__(self):
        self.children = {}
        self.count = 0

class Solution:
    def deleteDuplicateFolder(self, paths: List[List[str]]) -> List[List[str]]:
        root = TrieNode()
        
        # Build trie
        for path in sorted(paths):
            node = root
            for folder in path:
                if folder not in node.children:
                    node.children[folder] = TrieNode()
                node = node.children[folder]
        
        # Serialize and count
        serial_map = defaultdict(int)
        
        def serialize(node):
            if not node.children:
                return ""
            children_str = ",".join(f"{k}({serialize(node.children[k])})" for k in sorted(node.children.keys()))
            serial_map[children_str] += 1
            return children_str
        
        serialize(root)
        
        # Mark duplicates
        def mark_duplicates(node):
            if not node.children:
                return ""
            children_str = ",".join(f"{k}({mark_duplicates(node.children[k])})" for k in sorted(node.children.keys()))
            if serial_map[children_str] > 1:
                node.count = -1
            return children_str
        
        mark_duplicates(root)
        
        # Collect paths
        result = []
        
        def collect(node, path):
            if node.count == -1:
                return
            if path:
                result.append(path[:])
            for folder, child in node.children.items():
                if child.count != -1:
                    collect(child, path + [folder])
        
        collect(root, [])
        return result