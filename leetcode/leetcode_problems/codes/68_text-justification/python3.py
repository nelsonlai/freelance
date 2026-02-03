"""
Problem: Text Justification
Difficulty: Hard
Tags: array, string, greedy

Approach: Use two pointers or sliding window technique
Time Complexity: O(n) or O(n log n)
Space Complexity: O(1) to O(n) depending on approach
"""

class Solution:
    def fullJustify(self, words: List[str], maxWidth: int) -> List[str]:
        result = []
        i = 0
        
        while i < len(words):
            line_words = []
            line_length = 0
            
            # Collect words for current line
            while i < len(words) and line_length + len(words[i]) + len(line_words) <= maxWidth:
                line_words.append(words[i])
                line_length += len(words[i])
                i += 1
            
            # Build the line
            if i == len(words) or len(line_words) == 1:
                # Last line or single word: left-justified
                line = ' '.join(line_words)
                line += ' ' * (maxWidth - len(line))
            else:
                # Distribute spaces
                spaces_needed = maxWidth - line_length
                gaps = len(line_words) - 1
                base_spaces = spaces_needed // gaps
                extra_spaces = spaces_needed % gaps
                
                line = line_words[0]
                for j in range(1, len(line_words)):
                    spaces = base_spaces + (1 if j <= extra_spaces else 0)
                    line += ' ' * spaces + line_words[j]
            
            result.append(line)
        
        return result