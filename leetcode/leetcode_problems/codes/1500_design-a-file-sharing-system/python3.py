"""
Problem: Design a File Sharing System
Difficulty: Medium
Tags: hash, sort, queue, heap

Approach: Track chunks per user, users per chunk, reuse user IDs
Time Complexity: O(1) for most operations
Space Complexity: O(n * m) for chunks
"""

import heapq

class FileSharing:

    def __init__(self, m: int):
        self.user_chunks = {}
        self.chunk_users = {i: set() for i in range(1, m + 1)}
        self.available_ids = []
        self.next_id = 1

    def join(self, ownedChunks: List[int]) -> int:
        if self.available_ids:
            user_id = heapq.heappop(self.available_ids)
        else:
            user_id = self.next_id
            self.next_id += 1
        
        self.user_chunks[user_id] = set(ownedChunks)
        for chunk in ownedChunks:
            self.chunk_users[chunk].add(user_id)
        
        return user_id

    def leave(self, userID: int) -> None:
        for chunk in self.user_chunks[userID]:
            self.chunk_users[chunk].discard(userID)
        del self.user_chunks[userID]
        heapq.heappush(self.available_ids, userID)

    def request(self, userID: int, chunkID: int) -> List[int]:
        users = sorted(self.chunk_users[chunkID])
        if users:
            self.user_chunks[userID].add(chunkID)
            self.chunk_users[chunkID].add(userID)
        return users