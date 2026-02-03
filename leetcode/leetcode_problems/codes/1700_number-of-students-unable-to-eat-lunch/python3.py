"""
Problem: Number of Students Unable to Eat Lunch
Difficulty: Easy
Tags: array, stack, queue, simulation

Approach: Simulate queue - if no student wants top sandwich, remaining students can't eat
Time Complexity: O(n) where n is number of students
Space Complexity: O(1)
"""

from collections import deque

class Solution:
    def countStudents(self, students: List[int], sandwiches: List[int]) -> int:
        queue = deque(students)
        sandwich_idx = 0
        
        while queue and sandwich_idx < len(sandwiches):
            if queue[0] == sandwiches[sandwich_idx]:
                queue.popleft()
                sandwich_idx += 1
            else:
                # Check if any student wants this sandwich
                if sandwiches[sandwich_idx] not in queue:
                    break
                queue.append(queue.popleft())
        
        return len(queue)