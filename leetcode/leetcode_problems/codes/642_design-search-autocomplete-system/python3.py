"""
Problem: Design Search Autocomplete System
Difficulty: Hard
Tags: array, string, hash, sort, search, queue, heap

Approach: Use two pointers or sliding window technique
Time Complexity: O(n) or O(n log n)
Space Complexity: O(n) for hash map
"""

from collections import defaultdict

class TrieNode:
    def __init__(self):
        self.children = {}
        self.sentences = defaultdict(int)

class AutocompleteSystem:
    def __init__(self, sentences: List[str], times: List[int]):
        self.root = TrieNode()
        self.current_node = self.root
        self.current_sentence = ""
        
        for sentence, time in zip(sentences, times):
            self._add_sentence(sentence, time)
    
    def _add_sentence(self, sentence, time):
        node = self.root
        for char in sentence:
            if char not in node.children:
                node.children[char] = TrieNode()
            node = node.children[char]
            node.sentences[sentence] += time
    
    def input(self, c: str) -> List[str]:
        if c == '#':
            self._add_sentence(self.current_sentence, 1)
            self.current_sentence = ""
            self.current_node = self.root
            return []
        
        self.current_sentence += c
        if self.current_node and c in self.current_node.children:
            self.current_node = self.current_node.children[c]
        else:
            self.current_node = None
            return []
        
        candidates = []
        if self.current_node:
            candidates = list(self.current_node.sentences.items())
            candidates.sort(key=lambda x: (-x[1], x[0]))
            return [sentence for sentence, _ in candidates[:3]]
        
        return []