"""
Problem: Minimum Space Wasted From Packaging
Difficulty: Hard
Tags: array, sort, search, binary search

Approach: Sort packages, for each supplier try all boxes, use binary search
Time Complexity: O(n log n + m * (k log k + n log k)) where n is packages, m is suppliers, k is boxes
Space Complexity: O(1)
"""

import bisect

class Solution:
    def minWastedSpace(self, packages: List[int], boxes: List[List[int]]) -> int:
        packages.sort()
        total = sum(packages)
        MOD = 10**9 + 7
        result = float('inf')
        
        for supplier_boxes in boxes:
            supplier_boxes.sort()
            if supplier_boxes[-1] < packages[-1]:
                continue
            
            wasted = 0
            prev = 0
            
            for box in supplier_boxes:
                # Find packages that fit in this box
                idx = bisect.bisect_right(packages, box)
                if idx > prev:
                    wasted += box * (idx - prev)
                    prev = idx
                    if prev == len(packages):
                        break
            
            if prev == len(packages):
                result = min(result, wasted - total)
        
        return result % MOD if result != float('inf') else -1