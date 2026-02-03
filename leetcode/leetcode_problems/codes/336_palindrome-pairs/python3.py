"""
Problem: Palindrome Pairs
Difficulty: Hard
Tags: array, string, hash

Approach: Use two pointers or sliding window technique
Time Complexity: O(n) or O(n log n)
Space Complexity: O(n) for hash map
"""

class Solution:
    def palindromePairs(self, words: List[str]) -> List[List[int]]:
        word_map = {word: i for i, word in enumerate(words)}
        result = []
        
        for i, word in enumerate(words):
            for j in range(len(word) + 1):
                prefix = word[:j]
                suffix = word[j:]
                
                if prefix == prefix[::-1]:
                    rev_suffix = suffix[::-1]
                    if rev_suffix in word_map and word_map[rev_suffix] != i:
                        result.append([word_map[rev_suffix], i])
                
                if j != len(word) and suffix == suffix[::-1]:
                    rev_prefix = prefix[::-1]
                    if rev_prefix in word_map and word_map[rev_prefix] != i:
                        result.append([i, word_map[rev_prefix]])
        
        return result