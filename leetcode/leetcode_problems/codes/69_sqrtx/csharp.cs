/*
 * Problem: Sqrt(x)
 * Difficulty: Easy
 * Tags: math, search
 * 
 * Approach: Newton's method for square root
 * Time Complexity: O(log log n) - converges quadratically
 * Space Complexity: O(1)
 */

public class Solution {
    public int MySqrt(int x) {
        if (x < 2) {
            return x;
        }
        
        // Newton's method: x_{n+1} = (x_n + S/x_n) / 2
        long guess = x;
        while (guess * guess > x) {
            guess = (guess + x / guess) / 2;
        }
        
        return (int) guess;
    }
}