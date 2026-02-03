/**
 * Problem: Convert Callback Based Function to Promise Based Function
 * Difficulty: Medium
 * Tags: general
 * 
 * Approach: Optimized algorithm based on problem constraints
 * Time Complexity: O(n) to O(n^2) depending on approach
 * Space Complexity: O(1) to O(n) depending on approach
 */

/**
 * @param {Function} fn
 * @return {Function<Promise<number>>}
 */
var promisify = function(fn) {
    
    return async function(...args) {
        
    }
};

/**
 * const asyncFunc = promisify(callback => callback(42));
 * asyncFunc().then(console.log); // 42
 */