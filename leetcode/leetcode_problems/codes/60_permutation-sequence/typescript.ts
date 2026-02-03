/**
 * Problem: Permutation Sequence
 * Difficulty: Hard
 * Tags: math
 * 
 * Approach: Optimized algorithm based on problem constraints
 * Time Complexity: O(n) to O(n^2) depending on approach
 * Space Complexity: O(1) to O(n) depending on approach
 */

function getPermutation(n: number, k: number): string {
    const nums: number[] = [];
    for (let i = 1; i <= n; i++) {
        nums.push(i);
    }
    
    const fact: number[] = [1];
    for (let i = 1; i < n; i++) {
        fact[i] = fact[i - 1] * i;
    }
    
    k--; // Convert to 0-indexed
    const result: number[] = [];
    
    for (let i = n - 1; i >= 0; i--) {
        const index = Math.floor(k / fact[i]);
        result.push(nums[index]);
        nums.splice(index, 1);
        k %= fact[i];
    }
    
    return result.join('');
};