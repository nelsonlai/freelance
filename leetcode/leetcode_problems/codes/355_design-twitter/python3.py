"""
Problem: Design Twitter
Difficulty: Medium
Tags: hash, linked_list, queue, heap

Approach: Use hash map for O(1) lookups
Time Complexity: O(n) to O(n^2) depending on approach
Space Complexity: O(n) for hash map
"""

from collections import defaultdict
import heapq

class Twitter:

    def __init__(self):
        self.time = 0
        self.tweets = defaultdict(list)
        self.follows = defaultdict(set)

    def postTweet(self, userId: int, tweetId: int) -> None:
        self.tweets[userId].append((self.time, tweetId))
        self.time -= 1

    def getNewsFeed(self, userId: int) -> List[int]:
        heap = []
        self.follows[userId].add(userId)
        
        for followeeId in self.follows[userId]:
            if followeeId in self.tweets:
                tweets = self.tweets[followeeId]
                if tweets:
                    time, tweetId = tweets[-1]
                    heapq.heappush(heap, (time, tweetId, followeeId, len(tweets) - 1))
        
        result = []
        while heap and len(result) < 10:
            time, tweetId, followeeId, index = heapq.heappop(heap)
            result.append(tweetId)
            if index > 0:
                next_time, next_tweetId = self.tweets[followeeId][index - 1]
                heapq.heappush(heap, (next_time, next_tweetId, followeeId, index - 1))
        
        return result

    def follow(self, followerId: int, followeeId: int) -> None:
        self.follows[followerId].add(followeeId)

    def unfollow(self, followerId: int, followeeId: int) -> None:
        if followeeId in self.follows[followerId]:
            self.follows[followerId].remove(followeeId)