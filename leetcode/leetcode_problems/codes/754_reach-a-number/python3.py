class Solution:
    def reachNumber(self, target: int) -> int:
        target = abs(target)
        n = 0
        sum = 0
        
        while sum < target or (sum - target) % 2 != 0:
            n += 1
            sum += n
        
        return n
