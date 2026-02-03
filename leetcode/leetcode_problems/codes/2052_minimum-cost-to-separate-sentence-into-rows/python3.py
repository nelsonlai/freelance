"""
Problem: Minimum Cost to Separate Sentence Into Rows
Difficulty: Medium
Tags: array, string, dp

Approach: DP - minimize cost of splitting sentence into rows with max width k
Time Complexity: O(n^2) where n is number of words
Space Complexity: O(n)
"""

class Solution:
    def minimumCost(self, sentence: str, k: int) -> int:
        words = sentence.split()
        n = len(words)
        
        # dp[i] = minimum cost to split words[i:]
        dp = [float('inf')] * (n + 1)
        dp[n] = 0
        
        for i in range(n - 1, -1, -1):
            length = 0
            for j in range(i, n):
                if j > i:
                    length += 1  # space
                length += len(words[j])
                
                if length > k:
                    break
                
                # Cost is (k - length)^2
                cost = (k - length) ** 2
                dp[i] = min(dp[i], cost + dp[j + 1])
        
        return dp[0]