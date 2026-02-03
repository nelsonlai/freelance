// Problem: Divide Two Integers
// Difficulty: Medium
// Tags: math
// 
// Approach: Optimized algorithm based on problem constraints
// Time Complexity: O(n) to O(n^2) depending on approach
// Space Complexity: O(1) to O(n) depending on approach

func divide(dividend int, divisor int) int {
    if dividend == -2147483648 && divisor == -1 {
        return 2147483647
    }
    
    negative := (dividend < 0) != (divisor < 0)
    dvd := int64(dividend)
    dvs := int64(divisor)
    if dvd < 0 {
        dvd = -dvd
    }
    if dvs < 0 {
        dvs = -dvs
    }
    
    quotient := 0
    for dvd >= dvs {
        temp := dvs
        multiple := 1
        for dvd >= (temp << 1) {
            temp <<= 1
            multiple <<= 1
        }
        dvd -= temp
        quotient += multiple
    }
    
    if negative {
        return -quotient
    }
    return quotient
}