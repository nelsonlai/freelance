"""
Problem: Parallel Courses III
Difficulty: Hard
Tags: array, graph, dp, topological sort

Approach: Topological sort with DP - calculate max time to complete each course
Time Complexity: O(n + m) where n is courses, m is relations
Space Complexity: O(n + m)
"""

from collections import defaultdict, deque

class Solution:
    def minimumTime(self, n: int, relations: List[List[int]], time: List[int]) -> int:
        graph = defaultdict(list)
        in_degree = [0] * (n + 1)
        
        for prev, next_course in relations:
            graph[prev].append(next_course)
            in_degree[next_course] += 1
        
        # dp[i] = minimum time to complete course i
        dp = [0] * (n + 1)
        queue = deque()
        
        # Start with courses that have no prerequisites
        for i in range(1, n + 1):
            if in_degree[i] == 0:
                queue.append(i)
                dp[i] = time[i - 1]
        
        while queue:
            course = queue.popleft()
            
            for next_course in graph[course]:
                dp[next_course] = max(dp[next_course], dp[course] + time[next_course - 1])
                in_degree[next_course] -= 1
                if in_degree[next_course] == 0:
                    queue.append(next_course)
        
        return max(dp)