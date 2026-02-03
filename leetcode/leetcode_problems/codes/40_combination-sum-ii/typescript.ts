/**
 * Problem: Combination Sum II
 * Difficulty: Medium
 * Tags: array
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

function combinationSum2(candidates: number[], target: number): number[][] {
    candidates.sort((a, b) => a - b);
    const result: number[][] = [];
    
    function backtrack(start: number, path: number[], remaining: number): void {
        if (remaining === 0) {
            result.push([...path]);
            return;
        }
        if (remaining < 0) {
            return;
        }
        
        for (let i = start; i < candidates.length; i++) {
            if (i > start && candidates[i] === candidates[i - 1]) {
                continue;
            }
            path.push(candidates[i]);
            backtrack(i + 1, path, remaining - candidates[i]);
            path.pop();
        }
    }
    
    backtrack(0, [], target);
    return result;
};