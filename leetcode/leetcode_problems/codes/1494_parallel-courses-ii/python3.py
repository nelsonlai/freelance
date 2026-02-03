"""
Problem: Parallel Courses II
Difficulty: Hard
Tags: array, graph, dp

Approach: DP with bitmask - dp[mask] = min semesters to complete courses in mask
Time Complexity: O(3^n) in worst case
Space Complexity: O(2^n) for DP table
"""

class Solution:
    def minNumberOfSemesters(self, n: int, relations: List[List[int]], k: int) -> int:
        prerequisites = [0] * n
        for u, v in relations:
            prerequisites[v-1] |= 1 << (u-1)
        
        dp = [float('inf')] * (1 << n)
        dp[0] = 0
        
        for mask in range(1 << n):
            if dp[mask] == float('inf'):
                continue
            
            available = []
            for i in range(n):
                if (mask >> i) & 1 == 0 and (prerequisites[i] & mask) == prerequisites[i]:
                    available.append(i)
            
            # Try all subsets of available courses of size at most k
            def generate_subsets(arr, k, start, current):
                if len(current) == k or start == len(arr):
                    if current:
                        new_mask = mask
                        for course in current:
                            new_mask |= 1 << course
                        dp[new_mask] = min(dp[new_mask], dp[mask] + 1)
                    return
                
                for i in range(start, len(arr)):
                    generate_subsets(arr, k, i + 1, current + [arr[i]])
            
            generate_subsets(available, k, 0, [])
        
        return dp[(1 << n) - 1]