class Solution:
    def mirrorReflection(self, p: int, q: int) -> int:
        g = self.gcd(p, q)
        p //= g
        q //= g
        
        if q % 2 == 0:
            return 0
        if p % 2 == 0:
            return 2
        return 1
    
    def gcd(self, a, b):
        while b:
            a, b = b, a % b
        return a
