"""
Problem: Verifying an Alien Dictionary
Difficulty: Easy
Tags: array, string, graph, hash, sort

Approach: Create mapping from alien order, then check if adjacent words are sorted
Time Complexity: O(n * m) where n is number of words, m is average length
Space Complexity: O(1) for character mapping
"""

class Solution:
    def isAlienSorted(self, words: List[str], order: str) -> bool:
        order_map = {c: i for i, c in enumerate(order)}
        
        for i in range(len(words) - 1):
            word1, word2 = words[i], words[i + 1]
            
            # Find first differing character
            for j in range(min(len(word1), len(word2))):
                if word1[j] != word2[j]:
                    if order_map[word1[j]] > order_map[word2[j]]:
                        return False
                    break
            else:
                # One word is prefix of another
                if len(word1) > len(word2):
                    return False
        
        return True