from collections import defaultdict

class Solution:
    def areSentencesSimilar(self, sentence1: List[str], sentence2: List[str], similarPairs: List[List[str]]) -> bool:
        if len(sentence1) != len(sentence2):
            return False
        
        similar = defaultdict(set)
        for pair in similarPairs:
            similar[pair[0]].add(pair[1])
            similar[pair[1]].add(pair[0])
        
        for i in range(len(sentence1)):
            if sentence1[i] != sentence2[i] and sentence2[i] not in similar[sentence1[i]]:
                return False
        
        return True
