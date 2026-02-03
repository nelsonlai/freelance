"""
Problem: Maximum Number of Tasks You Can Assign
Difficulty: Hard
Tags: array, greedy, binary search, sort

Approach: Binary search on number of tasks, greedy matching with pills
Time Complexity: O(n log n * log(min(n, m))) where n is tasks, m is workers
Space Complexity: O(n)
"""

from collections import deque

class Solution:
    def maxTaskAssign(self, tasks: List[int], workers: List[int], pills: int, strength: int) -> int:
        tasks.sort()
        workers.sort()
        
        def canAssign(k):
            # Check if we can assign k smallest tasks
            if k > len(workers):
                return False
            
            task_list = tasks[:k]
            worker_list = workers[-k:]
            
            used_pills = 0
            task_idx = len(task_list) - 1
            
            # Use deque for efficient matching
            dq = deque()
            
            for worker in worker_list:
                # Add tasks that this worker can handle with pill
                while task_idx >= 0 and task_list[task_idx] > worker + strength:
                    task_idx -= 1
                
                # Add tasks that this worker can handle
                while task_idx >= 0 and task_list[task_idx] <= worker + strength:
                    dq.appendleft(task_list[task_idx])
                    task_idx -= 1
                
                # Try to assign without pill first
                if dq and dq[-1] <= worker:
                    dq.pop()
                elif dq and used_pills < pills:
                    # Use pill for hardest task
                    dq.popleft()
                    used_pills += 1
                else:
                    return False
            
            return True
        
        left, right = 0, min(len(tasks), len(workers))
        result = 0
        
        while left <= right:
            mid = (left + right) // 2
            if canAssign(mid):
                result = mid
                left = mid + 1
            else:
                right = mid - 1
        
        return result