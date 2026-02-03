from collections import Counter

class Solution:
    def numFriendRequests(self, ages: List[int]) -> int:
        count = Counter(ages)
        result = 0
        
        for ageA, countA in count.items():
            for ageB, countB in count.items():
                if ageB <= 0.5 * ageA + 7 or ageB > ageA or (ageB > 100 and ageA < 100):
                    continue
                result += countA * countB
                if ageA == ageB:
                    result -= countA
        
        return result
