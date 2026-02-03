"""
Problem: Sqrt(x)
Difficulty: Easy
Tags: math, search

Approach: Newton's method for square root
Time Complexity: O(log log n) - converges quadratically
Space Complexity: O(1)
"""

class Solution:
    def mySqrt(self, x: int) -> int:
        if x < 2:
            return x
        
        # Newton's method: x_{n+1} = (x_n + S/x_n) / 2
        guess = x
        while guess * guess > x:
            guess = (guess + x // guess) // 2
        
        return guess

    def bestSqrt(self, x: float) -> float:

        # Newton's method: x_{n+1} = (x_n + S/x_n) / 2
        guess = x
        while abs(guess * guess - x) > 1e-6:
            guess = (guess + x / guess) / 2
        return round(guess, 4)

if __name__ == "__main__":
    solution = Solution()
    print(solution.bestSqrt(4))
    print(solution.bestSqrt(8))
    print(solution.bestSqrt(16))
    print(solution.bestSqrt(25))
    print(solution.bestSqrt(36))
    print(solution.bestSqrt(49))
    print(solution.bestSqrt(64))
    print(solution.bestSqrt(77))
    print(solution.bestSqrt(81))
    print(solution.bestSqrt(100))