"""
Problem: Smallest Rectangle Enclosing Black Pixels
Difficulty: Hard
Tags: array, search

Approach: Use two pointers or sliding window technique
Time Complexity: O(n) or O(n log n)
Space Complexity: O(1) to O(n) depending on approach
"""

class Solution:
    def minArea(self, image: List[List[str]], x: int, y: int) -> int:
        m, n = len(image), len(image[0])
        
        def searchRows(i, j, opt):
            while i != j:
                mid = (i + j) // 2
                if ('1' in image[mid]) == opt:
                    j = mid
                else:
                    i = mid + 1
            return i
        
        def searchCols(i, j, opt):
            while i != j:
                mid = (i + j) // 2
                if any(image[k][mid] == '1' for k in range(m)) == opt:
                    j = mid
                else:
                    i = mid + 1
            return i
        
        top = searchRows(0, x, True)
        bottom = searchRows(x, m, False)
        left = searchCols(0, y, True)
        right = searchCols(y, n, False)
        
        return (bottom - top) * (right - left)