/**
 * Problem: Pow(x, n)
 * Difficulty: Medium
 * Tags: array, math
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

function myPow(x: number, n: number): number {
    if (n === 0) {
        return 1.0;
    }
    let N = n;
    if (N < 0) {
        x = 1 / x;
        N = -N;
    }
    
    let result = 1.0;
    while (N > 0) {
        if (N % 2 === 1) {
            result *= x;
        }
        x *= x;
        N = Math.floor(N / 2);
    }
    
    return result;
};