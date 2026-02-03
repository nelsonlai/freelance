"""
Problem: High Five
Difficulty: Easy
Tags: array, hash, sort, queue, heap

Approach: Group by student, keep top 5 scores, calculate average
Time Complexity: O(n log n) for sorting
Space Complexity: O(n) for scores
"""

from collections import defaultdict
import heapq

class Solution:
    def highFive(self, items: List[List[int]]) -> List[List[int]]:
        scores = defaultdict(list)
        
        for student_id, score in items:
            heapq.heappush(scores[student_id], score)
            if len(scores[student_id]) > 5:
                heapq.heappop(scores[student_id])
        
        result = []
        for student_id in sorted(scores.keys()):
            avg = sum(scores[student_id]) // 5
            result.append([student_id, avg])
        
        return result