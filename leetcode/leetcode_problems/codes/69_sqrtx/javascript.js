/**
 * Problem: Sqrt(x)
 * Difficulty: Easy
 * Tags: math, search
 * 
 * Approach: Newton's method for square root
 * Time Complexity: O(log log n) - converges quadratically
 * Space Complexity: O(1)
 */

/**
 * @param {number} x
 * @return {number}
 */
var mySqrt = function(x) {
    if (x < 2) {
        return x;
    }
    
    // Newton's method: x_{n+1} = (x_n + S/x_n) / 2
    let guess = x;
    while (guess * guess > x) {
        guess = Math.floor((guess + Math.floor(x / guess)) / 2);
    }
    
    return guess;
};