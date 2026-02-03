"""
Problem: Parallel Courses
Difficulty: Medium
Tags: array, graph, sort

Approach: Topological sort with BFS - find minimum semesters needed
Time Complexity: O(V + E) where V is number of courses, E is number of relations
Space Complexity: O(V + E) for graph and queue
"""

class Solution:
    def minimumSemesters(self, n: int, relations: List[List[int]]) -> int:
        from collections import deque, defaultdict
        
        graph = defaultdict(list)
        in_degree = [0] * (n + 1)
        
        for prev, next_course in relations:
            graph[prev].append(next_course)
            in_degree[next_course] += 1
        
        queue = deque([i for i in range(1, n + 1) if in_degree[i] == 0])
        semesters = 0
        courses_taken = 0
        
        while queue:
            size = len(queue)
            semesters += 1
            for _ in range(size):
                course = queue.popleft()
                courses_taken += 1
                for next_course in graph[course]:
                    in_degree[next_course] -= 1
                    if in_degree[next_course] == 0:
                        queue.append(next_course)
        
        return semesters if courses_taken == n else -1