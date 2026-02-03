"""
Problem: Filling Bookcase Shelves
Difficulty: Medium
Tags: array, dp

Approach: DP - for each book, try placing it on new shelf or current shelf
Time Complexity: O(n^2)
Space Complexity: O(n) for DP array
"""

class Solution:
    def minHeightShelves(self, books: List[List[int]], shelfWidth: int) -> int:
        n = len(books)
        dp = [float('inf')] * (n + 1)
        dp[0] = 0
        
        for i in range(1, n + 1):
            width = 0
            height = 0
            for j in range(i, 0, -1):
                width += books[j - 1][0]
                if width > shelfWidth:
                    break
                height = max(height, books[j - 1][1])
                dp[i] = min(dp[i], dp[j - 1] + height)
        
        return dp[n]