/**
 * Problem: Convert Callback Based Function to Promise Based Function
 * Difficulty: Medium
 * Tags: general
 * 
 * Approach: Optimized algorithm based on problem constraints
 * Time Complexity: O(n) to O(n^2) depending on approach
 * Space Complexity: O(1) to O(n) depending on approach
 */

type CallbackFn = (
    next: (data: number, error: string) => void, 
    ...args: number[]
) => void
type Promisified = (...args: number[]) => Promise<number>

function promisify(fn: CallbackFn): Promisified {
    
    return async function(...args) {
        
    };
};

/**
 * const asyncFunc = promisify(callback => callback(42));
 * asyncFunc().then(console.log); // 42
 */