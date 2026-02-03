from collections import Counter
import math

class Solution:
    def hasGroupsSizeX(self, deck: List[int]) -> bool:
        count = Counter(deck)
        values = list(count.values())
        gcd_val = values[0]
        
        for val in values[1:]:
            gcd_val = math.gcd(gcd_val, val)
        
        return gcd_val >= 2
