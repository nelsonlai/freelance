"""
Problem: Statistics from a Large Sample
Difficulty: Medium
Tags: array, math, sort

Approach: Calculate min, max, mean, median, mode from count array
Time Complexity: O(n) where n is count length
Space Complexity: O(1)
"""

class Solution:
    def sampleStats(self, count: List[int]) -> List[float]:
        total = sum(count)
        min_val = next(i for i, c in enumerate(count) if c > 0)
        max_val = next(i for i in range(len(count) - 1, -1, -1) if count[i] > 0)
        
        mean = sum(i * c for i, c in enumerate(count)) / total
        
        mode = max(range(len(count)), key=lambda i: count[i])
        
        median = 0
        cumsum = 0
        for i, c in enumerate(count):
            cumsum += c
            if cumsum >= total / 2:
                if total % 2 == 1:
                    median = i
                else:
                    if cumsum > total / 2:
                        median = i
                    else:
                        median = (i + next(j for j in range(i + 1, len(count)) if count[j] > 0)) / 2
                break
        
        return [float(min_val), float(max_val), mean, median, float(mode)]