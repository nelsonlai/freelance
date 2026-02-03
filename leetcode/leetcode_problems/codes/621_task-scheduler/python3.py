"""
Problem: Task Scheduler
Difficulty: Medium
Tags: array, greedy, hash, sort, queue, heap

Approach: Use two pointers or sliding window technique
Time Complexity: O(n) or O(n log n)
Space Complexity: O(n) for hash map
"""

from collections import Counter

class Solution:
    def leastInterval(self, tasks: List[str], n: int) -> int:
        count = Counter(tasks)
        max_count = max(count.values())
        max_count_tasks = sum(1 for c in count.values() if c == max_count)
        
        return max(len(tasks), (max_count - 1) * (n + 1) + max_count_tasks)