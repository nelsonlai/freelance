"""
Problem: Substring with Concatenation of All Words
Difficulty: Hard
Tags: array, string, tree, hash

Approach: Use two pointers or sliding window technique
Time Complexity: O(n) or O(n log n)
Space Complexity: O(h) for recursion stack where h is height
"""

from collections import Counter

class Solution:
    def findSubstring(self, s: str, words: List[str]) -> List[int]:
        if not s or not words:
            return []
        
        word_len = len(words[0])
        total_len = len(words) * word_len
        word_count = Counter(words)
        result = []
        
        for i in range(word_len):
            left = i
            seen = {}
            count = 0
            
            for j in range(i, len(s) - word_len + 1, word_len):
                word = s[j:j + word_len]
                
                if word in word_count:
                    seen[word] = seen.get(word, 0) + 1
                    count += 1
                    
                    while seen[word] > word_count[word]:
                        left_word = s[left:left + word_len]
                        seen[left_word] -= 1
                        count -= 1
                        left += word_len
                    
                    if count == len(words):
                        result.append(left)
                        left_word = s[left:left + word_len]
                        seen[left_word] -= 1
                        count -= 1
                        left += word_len
                else:
                    seen.clear()
                    count = 0
                    left = j + word_len
        
        return result