from collections import defaultdict

class Solution:
    def areSentencesSimilarTwo(self, sentence1: List[str], sentence2: List[str], similarPairs: List[List[str]]) -> bool:
        if len(sentence1) != len(sentence2):
            return False
        
        graph = defaultdict(set)
        for pair in similarPairs:
            graph[pair[0]].add(pair[1])
            graph[pair[1]].add(pair[0])
        
        def dfs(word1, word2, visited):
            if word1 == word2:
                return True
            visited.add(word1)
            for neighbor in graph[word1]:
                if neighbor not in visited:
                    if dfs(neighbor, word2, visited):
                        return True
            return False
        
        for i in range(len(sentence1)):
            if sentence1[i] != sentence2[i]:
                if not dfs(sentence1[i], sentence2[i], set()):
                    return False
        
        return True
