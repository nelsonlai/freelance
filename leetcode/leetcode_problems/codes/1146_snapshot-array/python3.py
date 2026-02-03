"""
Problem: Snapshot Array
Difficulty: Medium
Tags: array, hash, search

Approach: Store snapshots as list of (snap_id, value) pairs for each index, use binary search
Time Complexity: O(log k) for get where k is number of snapshots per index
Space Complexity: O(n * k) where n is length, k is number of snapshots
"""

class SnapshotArray:

    def __init__(self, length: int):
        self.snap_id = 0
        self.data = [[] for _ in range(length)]

    def set(self, index: int, val: int) -> None:
        if self.data[index] and self.data[index][-1][0] == self.snap_id:
            self.data[index][-1] = (self.snap_id, val)
        else:
            self.data[index].append((self.snap_id, val))

    def snap(self) -> int:
        self.snap_id += 1
        return self.snap_id - 1

    def get(self, index: int, snap_id: int) -> int:
        import bisect
        history = self.data[index]
        if not history or history[0][0] > snap_id:
            return 0
        
        # Binary search for the last value at or before snap_id
        pos = bisect.bisect_right(history, (snap_id, float('inf'))) - 1
        return history[pos][1] if pos >= 0 else 0