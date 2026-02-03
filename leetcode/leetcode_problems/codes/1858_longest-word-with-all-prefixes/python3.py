"""
Problem: Longest Word With All Prefixes
Difficulty: Medium
Tags: array, string, trie

Approach: Use Trie to check if all prefixes exist
Time Complexity: O(n * m) where n is words, m is avg length
Space Complexity: O(n * m)
"""

class TrieNode:
    def __init__(self):
        self.children = {}
        self.is_end = False

class Solution:
    def longestWord(self, words: List[str]) -> str:
        root = TrieNode()
        
        # Build trie
        for word in words:
            node = root
            for char in word:
                if char not in node.children:
                    node.children[char] = TrieNode()
                node = node.children[char]
            node.is_end = True
        
        result = ""
        
        def dfs(node, path):
            nonlocal result
            if len(path) > len(result) or (len(path) == len(result) and path < result):
                result = path
            
            for char, child in sorted(node.children.items()):
                if child.is_end:
                    dfs(child, path + char)
        
        dfs(root, "")
        return result