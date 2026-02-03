/**
 * Problem: Delay the Resolution of Each Promise
 * Difficulty: Medium
 * Tags: array
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

type Fn = () => Promise<any>

function delayAll(functions: Fn[], ms: number): Fn[] {
    
};