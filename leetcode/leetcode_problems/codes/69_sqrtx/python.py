class Solution(object):
    def mySqrt(self, x):
        """
        :type x: int
        :rtype: int
        """
        if x < 2:
            return x
        
        # Newton's method: x_{n+1} = (x_n + S/x_n) / 2
        guess = x
        while guess * guess > x:
            guess = (guess + x // guess) // 2
        
        return guess
        