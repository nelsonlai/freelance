"""
Problem: Find the Shortest Superstring
Difficulty: Hard
Tags: array, string, tree, dp

Approach: Traveling Salesman Problem with DP - find optimal order to concatenate words
Time Complexity: O(n^2 * (2^n + m)) where n is number of words, m is average word length
Space Complexity: O(n * 2^n) for DP table
"""

class Solution:
    def shortestSuperstring(self, words: List[str]) -> str:
        n = len(words)
        
        # Calculate overlap between words
        overlap = [[0] * n for _ in range(n)]
        for i in range(n):
            for j in range(n):
                if i != j:
                    for k in range(min(len(words[i]), len(words[j])), 0, -1):
                        if words[i][-k:] == words[j][:k]:
                            overlap[i][j] = k
                            break
        
        # DP: dp[mask][i] = maximum overlap ending with word i using mask
        dp = [[0] * n for _ in range(1 << n)]
        parent = [[-1] * n for _ in range(1 << n)]
        
        for mask in range(1, 1 << n):
            for i in range(n):
                if not (mask & (1 << i)):
                    continue
                prev_mask = mask ^ (1 << i)
                if prev_mask == 0:
                    continue
                for j in range(n):
                    if prev_mask & (1 << j):
                        val = dp[prev_mask][j] + overlap[j][i]
                        if val > dp[mask][i]:
                            dp[mask][i] = val
                            parent[mask][i] = j
        
        # Find best ending word
        last = 0
        max_val = dp[(1 << n) - 1][0]
        for i in range(1, n):
            if dp[(1 << n) - 1][i] > max_val:
                max_val = dp[(1 << n) - 1][i]
                last = i
        
        # Reconstruct path
        path = []
        mask = (1 << n) - 1
        while last != -1:
            path.append(last)
            new_mask = mask ^ (1 << last)
            last = parent[mask][last]
            mask = new_mask
        path.reverse()
        
        # Build result
        result = words[path[0]]
        for i in range(1, len(path)):
            overlap_len = overlap[path[i-1]][path[i]]
            result += words[path[i]][overlap_len:]
        
        return result