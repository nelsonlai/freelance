/**
 * Problem: Permutations
 * Difficulty: Medium
 * Tags: array
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

function permute(nums: number[]): number[][] {
    const result: number[][] = [];
    
    function backtrack(current: number[]): void {
        if (current.length === nums.length) {
            result.push([...current]);
            return;
        }
        
        for (const num of nums) {
            if (current.includes(num)) continue;
            current.push(num);
            backtrack(current);
            current.pop();
        }
    }
    
    backtrack([]);
    return result;
};