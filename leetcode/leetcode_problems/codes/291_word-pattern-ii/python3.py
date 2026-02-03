"""
Problem: Word Pattern II
Difficulty: Medium
Tags: string, hash

Approach: String manipulation with hash map or two pointers
Time Complexity: O(n) or O(n log n)
Space Complexity: O(n) for hash map
"""

class Solution:
    def wordPatternMatch(self, pattern: str, s: str) -> bool:
        def backtrack(pattern_idx, s_idx, char_to_word, word_to_char):
            if pattern_idx == len(pattern) and s_idx == len(s):
                return True
            if pattern_idx == len(pattern) or s_idx == len(s):
                return False
            
            char = pattern[pattern_idx]
            
            if char in char_to_word:
                word = char_to_word[char]
                if s[s_idx:s_idx + len(word)] != word:
                    return False
                return backtrack(pattern_idx + 1, s_idx + len(word), char_to_word, word_to_char)
            
            for end in range(s_idx + 1, len(s) + 1):
                word = s[s_idx:end]
                
                if word in word_to_char:
                    continue
                
                char_to_word[char] = word
                word_to_char[word] = char
                
                if backtrack(pattern_idx + 1, end, char_to_word, word_to_char):
                    return True
                
                del char_to_word[char]
                del word_to_char[word]
            
            return False
        
        return backtrack(0, 0, {}, {})