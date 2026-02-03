// Problem: Pow(x, n)
// Difficulty: Medium
// Tags: array, math
// 
// Approach: Use two pointers or sliding window technique
// Time Complexity: O(n) or O(n log n)
// Space Complexity: O(1) to O(n) depending on approach

func myPow(x float64, n int) float64 {
    if n == 0 {
        return 1.0
    }
    N := int64(n)
    if N < 0 {
        x = 1 / x
        N = -N
    }
    
    result := 1.0
    for N > 0 {
        if N%2 == 1 {
            result *= x
        }
        x *= x
        N /= 2
    }
    
    return result
}