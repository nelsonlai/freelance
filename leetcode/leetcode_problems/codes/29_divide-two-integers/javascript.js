/**
 * Problem: Divide Two Integers
 * Difficulty: Medium
 * Tags: math
 * 
 * Approach: Optimized algorithm based on problem constraints
 * Time Complexity: O(n) to O(n^2) depending on approach
 * Space Complexity: O(1) to O(n) depending on approach
 */

/**
 * @param {number} dividend
 * @param {number} divisor
 * @return {number}
 */
var divide = function(dividend, divisor) {
    const INT_MAX = 2**31 - 1;
    const INT_MIN = -(2**31);
    
    if (dividend === INT_MIN && divisor === -1) {
        return INT_MAX;
    }
    
    const negative = (dividend < 0) !== (divisor < 0);
    let dvd = Math.abs(dividend);
    let dvs = Math.abs(divisor);
    
    let quotient = 0;
    while (dvd >= dvs) {
        let temp = dvs;
        let multiple = 1;
        while (dvd >= (temp << 1)) {
            temp <<= 1;
            multiple <<= 1;
        }
        dvd -= temp;
        quotient += multiple;
    }
    
    return negative ? -quotient : quotient;
};