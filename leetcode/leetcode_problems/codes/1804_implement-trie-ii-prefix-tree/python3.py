"""
Problem: Implement Trie II (Prefix Tree)
Difficulty: Medium
Tags: string, tree, trie

Approach: Standard Trie with word count and prefix count
Time Complexity: O(m) per operation where m is word length
Space Complexity: O(n * m) where n is words, m is avg length
"""

class TrieNode:
    def __init__(self):
        self.children = {}
        self.word_count = 0
        self.prefix_count = 0

class Trie:

    def __init__(self):
        self.root = TrieNode()

    def insert(self, word: str) -> None:
        node = self.root
        for char in word:
            if char not in node.children:
                node.children[char] = TrieNode()
            node = node.children[char]
            node.prefix_count += 1
        node.word_count += 1

    def countWordsEqualTo(self, word: str) -> int:
        node = self.root
        for char in word:
            if char not in node.children:
                return 0
            node = node.children[char]
        return node.word_count

    def countWordsStartingWith(self, prefix: str) -> int:
        node = self.root
        for char in prefix:
            if char not in node.children:
                return 0
            node = node.children[char]
        return node.prefix_count

    def erase(self, word: str) -> None:
        node = self.root
        for char in word:
            if char not in node.children:
                return
            node = node.children[char]
            node.prefix_count -= 1
        node.word_count -= 1