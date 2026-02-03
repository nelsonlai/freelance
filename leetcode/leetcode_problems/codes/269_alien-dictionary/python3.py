"""
Problem: Alien Dictionary
Difficulty: Hard
Tags: array, string, graph, sort, search

Approach: Use two pointers or sliding window technique
Time Complexity: O(n) or O(n log n)
Space Complexity: O(1) to O(n) depending on approach
"""

from collections import defaultdict, deque

class Solution:
    def alienOrder(self, words: List[str]) -> str:
        graph = defaultdict(set)
        indegree = defaultdict(int)
        
        for word in words:
            for char in word:
                indegree[char] = 0
        
        for i in range(len(words) - 1):
            word1, word2 = words[i], words[i + 1]
            if len(word1) > len(word2) and word1.startswith(word2):
                return ""
            
            for j in range(min(len(word1), len(word2))):
                if word1[j] != word2[j]:
                    if word2[j] not in graph[word1[j]]:
                        graph[word1[j]].add(word2[j])
                        indegree[word2[j]] += 1
                    break
        
        queue = deque([char for char in indegree if indegree[char] == 0])
        result = []
        
        while queue:
            char = queue.popleft()
            result.append(char)
            
            for neighbor in graph[char]:
                indegree[neighbor] -= 1
                if indegree[neighbor] == 0:
                    queue.append(neighbor)
        
        return ''.join(result) if len(result) == len(indegree) else ""