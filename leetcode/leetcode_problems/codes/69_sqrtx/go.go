// Problem: Sqrt(x)
// Difficulty: Easy
// Tags: math, search
// 
// Approach: Newton's method for square root
// Time Complexity: O(log log n) - converges quadratically
// Space Complexity: O(1)

func mySqrt(x int) int {
    if x < 2 {
        return x
    }
    
    // Newton's method: x_{n+1} = (x_n + S/x_n) / 2
    guess := x
    for guess*guess > x {
        guess = (guess + x/guess) / 2
    }
    
    return guess
}