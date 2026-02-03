class Solution:
    def superpalindromesInRange(self, left: str, right: str) -> int:
        def is_palindrome(s):
            return s == s[::-1]
        
        L = int(left)
        R = int(right)
        count = 0
        
        for i in range(1, 100000):
            s = str(i)
            p1 = int(s + s[::-1])
            p1_sq = p1 * p1
            if p1_sq > R:
                break
            if p1_sq >= L and is_palindrome(str(p1_sq)):
                count += 1
            
            p2 = int(s + s[:-1][::-1])
            p2_sq = p2 * p2
            if p2_sq >= L and p2_sq <= R and is_palindrome(str(p2_sq)):
                count += 1
        
        return count
