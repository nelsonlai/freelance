from collections import Counter

class Solution:
    def threeSumMulti(self, arr: List[int], target: int) -> int:
        MOD = 10**9 + 7
        count = Counter(arr)
        keys = sorted(count.keys())
        result = 0
        
        for i, x in enumerate(keys):
            for j, y in enumerate(keys[i:], i):
                z = target - x - y
                if z < y:
                    break
                if z not in count:
                    continue
                
                if x == y == z:
                    result += count[x] * (count[x] - 1) * (count[x] - 2) // 6
                elif x == y:
                    result += count[x] * (count[x] - 1) // 2 * count[z]
                elif y == z:
                    result += count[x] * count[y] * (count[y] - 1) // 2
                else:
                    result += count[x] * count[y] * count[z]
        
        return result % MOD
