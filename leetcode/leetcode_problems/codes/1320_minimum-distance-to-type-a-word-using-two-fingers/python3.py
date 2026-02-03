"""
Problem: Minimum Distance to Type a Word Using Two Fingers
Difficulty: Hard
Tags: string, dp

Approach: DP - dp[i][finger1][finger2] = min distance, can optimize by tracking last positions
Time Complexity: O(n * 26 * 26) where n is word length
Space Complexity: O(26 * 26) using rolling array
"""

class Solution:
    def minimumDistance(self, word: str) -> int:
        def distance(a, b):
            if a == 26 or b == 26:  # 26 means no finger placed
                return 0
            return abs(a // 6 - b // 6) + abs(a % 6 - b % 6)
        
        n = len(word)
        dp = {}
        dp[(26, 26)] = 0
        
        for char in word:
            pos = ord(char) - ord('A')
            new_dp = {}
            
            for (f1, f2), cost in dp.items():
                # Use finger 1
                new_dp[(pos, f2)] = min(new_dp.get((pos, f2), float('inf')), 
                                       cost + distance(f1, pos))
                # Use finger 2
                new_dp[(f1, pos)] = min(new_dp.get((f1, pos), float('inf')), 
                                       cost + distance(f2, pos))
            
            dp = new_dp
        
        return min(dp.values())