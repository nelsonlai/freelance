"""
Problem: Most Visited Sector in  a Circular Track
Difficulty: Easy
Tags: array, sort

Approach: Count visits for each sector, handle wrap-around from last to first
Time Complexity: O(n * m) where n is sectors, m is rounds length
Space Complexity: O(n) for counts
"""

class Solution:
    def mostVisited(self, n: int, rounds: List[int]) -> List[int]:
        counts = [0] * (n + 1)
        
        for i in range(len(rounds) - 1):
            start = rounds[i]
            end = rounds[i + 1]
            
            if start <= end:
                for j in range(start, end + 1):
                    counts[j] += 1
            else:
                for j in range(start, n + 1):
                    counts[j] += 1
                for j in range(1, end + 1):
                    counts[j] += 1
        
        max_count = max(counts)
        return [i for i in range(1, n + 1) if counts[i] == max_count]