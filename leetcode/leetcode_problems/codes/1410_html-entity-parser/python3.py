"""
Problem: HTML Entity Parser
Difficulty: Medium
Tags: string, hash

Approach: Replace HTML entities with characters, process longest first
Time Complexity: O(n) where n is length of text
Space Complexity: O(n) for result
"""

class Solution:
    def entityParser(self, text: str) -> str:
        entities = {
            '&quot;': '"',
            '&apos;': "'",
            '&amp;': '&',
            '&gt;': '>',
            '&lt;': '<',
            '&frasl;': '/'
        }
        
        result = text
        for entity, char in entities.items():
            result = result.replace(entity, char)
        
        return result