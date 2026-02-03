"""
Problem: Exclusive Time of Functions
Difficulty: Medium
Tags: array, string, stack

Approach: Use two pointers or sliding window technique
Time Complexity: O(n) or O(n log n)
Space Complexity: O(1) to O(n) depending on approach
"""

class Solution:
    def exclusiveTime(self, n: int, logs: List[str]) -> List[int]:
        result = [0] * n
        stack = []
        prev_time = 0
        
        for log in logs:
            parts = log.split(':')
            func_id = int(parts[0])
            status = parts[1]
            time = int(parts[2])
            
            if status == 'start':
                if stack:
                    result[stack[-1]] += time - prev_time
                stack.append(func_id)
                prev_time = time
            else:
                result[stack.pop()] += time - prev_time + 1
                prev_time = time + 1
        
        return result