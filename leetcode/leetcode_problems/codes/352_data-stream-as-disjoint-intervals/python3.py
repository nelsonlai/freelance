"""
Problem: Data Stream as Disjoint Intervals
Difficulty: Hard
Tags: graph, hash, sort, search

Approach: Use hash map for O(1) lookups
Time Complexity: O(n) to O(n^2) depending on approach
Space Complexity: O(n) for hash map
"""

class SummaryRanges:

    def __init__(self):
        self.intervals = []

    def addNum(self, value: int) -> None:
        intervals = self.intervals
        new_interval = [value, value]
        inserted = False
        
        for i, interval in enumerate(intervals):
            if interval[1] < value - 1:
                continue
            elif interval[0] > value + 1:
                intervals.insert(i, new_interval)
                inserted = True
                break
            else:
                interval[0] = min(interval[0], value)
                interval[1] = max(interval[1], value)
                inserted = True
                break
        
        if not inserted:
            intervals.append(new_interval)
        
        merged = []
        for interval in intervals:
            if merged and merged[-1][1] + 1 >= interval[0]:
                merged[-1][1] = max(merged[-1][1], interval[1])
            else:
                merged.append(interval)
        
        self.intervals = merged

    def getIntervals(self) -> List[List[int]]:
        return self.intervals