/**
 * Problem: Bind Function to Context
 * Difficulty: Medium
 * Tags: dp
 * 
 * Approach: Dynamic programming with memoization or tabulation
 * Time Complexity: O(n * m) where n and m are problem dimensions
 * Space Complexity: O(n) or O(n * m) for DP table
 */

type Fn = (...args) => any

interface Function {
    bindPolyfill(obj: Record<any, any>): Fn;
}

Function.prototype.bindPolyfill = function(obj): Fn {
    
}