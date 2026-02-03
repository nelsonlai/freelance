"""
Problem: Word Ladder II
Difficulty: Hard
Tags: string, hash, search

Approach: String manipulation with hash map or two pointers
Time Complexity: O(n) or O(n log n)
Space Complexity: O(n) for hash map
"""

from collections import defaultdict, deque

class Solution:
    def findLadders(self, beginWord: str, endWord: str, wordList: List[str]) -> List[List[str]]:
        if endWord not in wordList:
            return []
        
        wordSet = set(wordList)
        wordSet.add(beginWord)
        
        neighbors = defaultdict(list)
        for word in wordSet:
            for i in range(len(word)):
                pattern = word[:i] + '*' + word[i+1:]
                neighbors[pattern].append(word)
        
        distance = {beginWord: 0}
        parents = defaultdict(list)
        queue = deque([beginWord])
        found = False
        
        while queue and not found:
            size = len(queue)
            for _ in range(size):
                word = queue.popleft()
                for i in range(len(word)):
                    pattern = word[:i] + '*' + word[i+1:]
                    for neighbor in neighbors[pattern]:
                        if neighbor not in distance:
                            distance[neighbor] = distance[word] + 1
                            parents[neighbor].append(word)
                            queue.append(neighbor)
                        elif distance[neighbor] == distance[word] + 1:
                            parents[neighbor].append(word)
                        if neighbor == endWord:
                            found = True
        
        result = []
        if found:
            def backtrack(word, path):
                if word == beginWord:
                    result.append(path[::-1])
                    return
                for parent in parents[word]:
                    backtrack(parent, path + [parent])
            
            backtrack(endWord, [endWord])
        
        return result