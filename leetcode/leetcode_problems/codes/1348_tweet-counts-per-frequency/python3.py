"""
Problem: Tweet Counts Per Frequency
Difficulty: Medium
Tags: string, hash, sort, search

Approach: Store tweets in sorted list per tweet name, binary search for range
Time Complexity: O(log n) for recordTweet, O(n) for getTweetCountsPerFrequency
Space Complexity: O(n) for storing tweets
"""

from collections import defaultdict
import bisect

class TweetCounts:

    def __init__(self):
        self.tweets = defaultdict(list)

    def recordTweet(self, tweetName: str, time: int) -> None:
        bisect.insort(self.tweets[tweetName], time)

    def getTweetCountsPerFrequency(self, freq: str, tweetName: str, startTime: int, endTime: int) -> List[int]:
        if tweetName not in self.tweets:
            return []
        
        times = self.tweets[tweetName]
        interval = {'minute': 60, 'hour': 3600, 'day': 86400}[freq]
        
        result = []
        current = startTime
        
        while current <= endTime:
            next_time = min(current + interval, endTime + 1)
            left = bisect.bisect_left(times, current)
            right = bisect.bisect_left(times, next_time)
            result.append(right - left)
            current = next_time
        
        return result