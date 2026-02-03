"""
Problem: Get Watched Videos by Your Friends
Difficulty: Medium
Tags: array, graph, hash, sort, search

Approach: BFS to find friends at level k, count videos, sort by frequency then name
Time Complexity: O(n + m + v log v) where n is people, m is edges, v is videos
Space Complexity: O(n + v) for queue and video counts
"""

from collections import deque, Counter

class Solution:
    def watchedVideosByFriends(self, watchedVideos: List[List[str]], friends: List[List[int]], id: int, level: int) -> List[str]:
        queue = deque([(id, 0)])
        visited = {id}
        level_friends = []
        
        while queue:
            person, dist = queue.popleft()
            if dist == level:
                level_friends.append(person)
            elif dist < level:
                for friend in friends[person]:
                    if friend not in visited:
                        visited.add(friend)
                        queue.append((friend, dist + 1))
        
        video_count = Counter()
        for friend in level_friends:
            for video in watchedVideos[friend]:
                video_count[video] += 1
        
        return sorted(video_count.keys(), key=lambda v: (video_count[v], v))