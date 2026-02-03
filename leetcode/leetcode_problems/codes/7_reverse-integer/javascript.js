/**
 * Problem: Reverse Integer
 * Difficulty: Medium
 * Tags: math
 * 
 * Approach: Optimized algorithm based on problem constraints
 * Time Complexity: O(n) to O(n^2) depending on approach
 * Space Complexity: O(1) to O(n) depending on approach
 */

/**
 * @param {number} x
 * @return {number}
 */
var reverse = function(x) {
    const INT_MAX = Math.pow(2, 31) - 1;
    const INT_MIN = -Math.pow(2, 31);
    
    let result = 0;
    
    while (x !== 0) {
        const digit = x % 10;
        x = Math.trunc(x / 10);
        
        if (result > Math.floor(INT_MAX / 10) || 
            (result === Math.floor(INT_MAX / 10) && digit > 7)) {
            return 0;
        }
        if (result < Math.ceil(INT_MIN / 10) || 
            (result === Math.ceil(INT_MIN / 10) && digit < -8)) {
            return 0;
        }
        
        result = result * 10 + digit;
    }
    
    return result;
};