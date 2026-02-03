from collections import Counter

class Solution(object):
    def findSubstring(self, s, words):
        """
        :type s: str
        :type words: List[str]
        :rtype: List[int]
        """
        if not s or not words:
            return []
        
        word_len = len(words[0])
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