"""
Problem: Minimum Number of Food Buckets to Feed the Hamsters
Difficulty: Medium
Tags: string, greedy

Approach: Greedy - place bucket to the right of hamster if possible, else to the left
Time Complexity: O(n) where n is string length
Space Complexity: O(1)
"""

class Solution:
    def minimumBuckets(self, hamsters: str) -> int:
        n = len(hamsters)
        buckets = 0
        i = 0
        
        while i < n:
            if hamsters[i] == 'H':
                # Try to place bucket to the right first
                if i + 1 < n and hamsters[i + 1] == '.':
                    buckets += 1
                    i += 3  # Skip next two positions
                elif i - 1 >= 0 and hamsters[i - 1] == '.':
                    buckets += 1
                    i += 1
                else:
                    # Cannot feed this hamster
                    return -1
            else:
                i += 1
        
        return buckets