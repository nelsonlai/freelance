from collections import Counter

class Solution:
    def isNStraightHand(self, hand: List[int], groupSize: int) -> bool:
        if len(hand) % groupSize != 0:
            return False
        
        count = Counter(hand)
        sortedKeys = sorted(count.keys())
        
        for key in sortedKeys:
            if count[key] > 0:
                need = count[key]
                for i in range(groupSize):
                    if count[key + i] < need:
                        return False
                    count[key + i] -= need
        
        return True
