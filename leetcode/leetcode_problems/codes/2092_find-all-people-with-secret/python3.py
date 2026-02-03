"""
Problem: Find All People With Secret
Difficulty: Hard
Tags: array, graph, BFS, sort

Approach: Sort meetings by time, use BFS to spread secret at each time
Time Complexity: O(m log m + n) where m is meetings, n is people
Space Complexity: O(n + m)
"""

from collections import defaultdict, deque

class Solution:
    def findAllPeople(self, n: int, meetings: List[List[int]], firstPerson: int) -> List[int]:
        # Group meetings by time
        meetings_by_time = defaultdict(list)
        for x, y, time in meetings:
            meetings_by_time[time].append((x, y))
        
        # People who know the secret
        knows_secret = {0, firstPerson}
        
        # Process meetings in chronological order
        for time in sorted(meetings_by_time.keys()):
            graph = defaultdict(list)
            current_meeting_people = set()
            
            # Build graph for current time
            for x, y in meetings_by_time[time]:
                graph[x].append(y)
                graph[y].append(x)
                current_meeting_people.add(x)
                current_meeting_people.add(y)
            
            # BFS from people who know secret
            queue = deque([p for p in current_meeting_people if p in knows_secret])
            visited = set(queue)
            
            while queue:
                person = queue.popleft()
                knows_secret.add(person)
                for neighbor in graph[person]:
                    if neighbor not in visited:
                        visited.add(neighbor)
                        queue.append(neighbor)
        
        return sorted(list(knows_secret))