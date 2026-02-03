class Solution {
    func mySqrt(_ x: Int) -> Int {
        if x < 2 {
            return x
        }
        
        // Newton's method: x_{n+1} = (x_n + S/x_n) / 2
        var guess = x
        while guess * guess > x {
            guess = (guess + x / guess) / 2
        }
        
        return guess
    }
}