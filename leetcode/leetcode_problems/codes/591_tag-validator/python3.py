"""
Problem: Tag Validator
Difficulty: Hard
Tags: string, stack

Approach: String manipulation with hash map or two pointers
Time Complexity: O(n) or O(n log n)
Space Complexity: O(1) to O(n) depending on approach
"""

import re

class Solution:
    def isValid(self, code: str) -> bool:
        if not code.startswith('<') or not code.endswith('>'):
            return False
        
        stack = []
        i = 0
        while i < len(code):
            if i > 0 and not stack:
                return False
            
            if code[i:i+9] == '<![CDATA[':
                j = i + 9
                i = code.find(']]>', j)
                if i == -1:
                    return False
                i += 3
            elif code[i:i+2] == '</':
                j = i + 2
                i = code.find('>', j)
                if i == -1:
                    return False
                tag = code[j:i]
                if not stack or stack.pop() != tag:
                    return False
                i += 1
            elif code[i] == '<':
                j = i + 1
                i = code.find('>', j)
                if i == -1:
                    return False
                tag = code[j:i]
                if not tag or len(tag) > 9 or not all(c.isupper() for c in tag):
                    return False
                stack.append(tag)
                i += 1
            else:
                i += 1
        
        return len(stack) == 0