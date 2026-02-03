"""
Problem: Stream of Characters
Difficulty: Hard
Tags: array, string

Approach: Build trie with reversed words, check suffixes in reverse
Time Complexity: O(m) per query where m is max word length
Space Complexity: O(total characters in words)
"""

class TrieNode:
    def __init__(self):
        self.children = {}
        self.is_end = False

class StreamChecker:

    def __init__(self, words: List[str]):
        self.root = TrieNode()
        self.stream = []
        
        # Build trie with reversed words
        for word in words:
            node = self.root
            for char in reversed(word):
                if char not in node.children:
                    node.children[char] = TrieNode()
                node = node.children[char]
            node.is_end = True

    def query(self, letter: str) -> bool:
        self.stream.append(letter)
        node = self.root
        
        # Check suffix in reverse
        for i in range(len(self.stream) - 1, -1, -1):
            if self.stream[i] not in node.children:
                return False
            node = node.children[self.stream[i]]
            if node.is_end:
                return True
        
        return False