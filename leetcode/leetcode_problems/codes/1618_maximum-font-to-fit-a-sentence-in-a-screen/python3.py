"""
Problem: Maximum Font to Fit a Sentence in a Screen
Difficulty: Medium
Tags: array, string, sort, search, binary search

Approach: Binary search on font sizes, check if text fits
Time Complexity: O(log k * n) where k is number of fonts, n is text length
Space Complexity: O(1)
"""

class Solution:
    def maxFont(self, text: str, w: int, h: int, fonts: List[int], fontInfo: 'FontInfo') -> int:
        fonts.sort()
        left, right = 0, len(fonts) - 1
        result = -1
        
        while left <= right:
            mid = (left + right) // 2
            fontSize = fonts[mid]
            
            if fontInfo.getHeight(fontSize) > h:
                right = mid - 1
                continue
            
            total_width = sum(fontInfo.getWidth(fontSize, ch) for ch in text)
            
            if total_width <= w:
                result = fontSize
                left = mid + 1
            else:
                right = mid - 1
        
        return result