"""
Problem: Plates Between Candles
Difficulty: Medium
Tags: array, string, prefix sum, binary search

Approach: Use prefix sum for plates, binary search for nearest candles
Time Complexity: O(n + q log n) where n is length, q is queries
Space Complexity: O(n)
"""

import bisect

class Solution:
    def platesBetweenCandles(self, s: str, queries: List[List[int]]) -> List[int]:
        n = len(s)
        # Store positions of candles
        candles = []
        # Prefix sum of plates
        prefix_plates = [0] * (n + 1)
        
        for i, char in enumerate(s):
            if char == '|':
                candles.append(i)
            prefix_plates[i + 1] = prefix_plates[i] + (1 if char == '*' else 0)
        
        result = []
        
        for left, right in queries:
            # Find first candle >= left
            left_idx = bisect.bisect_left(candles, left)
            # Find last candle <= right
            right_idx = bisect.bisect_right(candles, right) - 1
            
            if left_idx < len(candles) and right_idx >= left_idx:
                left_candle = candles[left_idx]
                right_candle = candles[right_idx]
                # Count plates between candles
                count = prefix_plates[right_candle + 1] - prefix_plates[left_candle]
                result.append(count)
            else:
                result.append(0)
        
        return result