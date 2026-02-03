/**
 * Problem: Combination Sum
 * Difficulty: Medium
 * Tags: array
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

/**
 * @param {number[]} candidates
 * @param {number} target
 * @return {number[][]}
 */
var combinationSum = function(candidates, target) {
    const result = [];
    
    function backtrack(start, path, remaining) {
        if (remaining === 0) {
            result.push([...path]);
            return;
        }
        if (remaining < 0) {
            return;
        }
        
        for (let i = start; i < candidates.length; i++) {
            path.push(candidates[i]);
            backtrack(i, path, remaining - candidates[i]);
            path.pop();
        }
    }
    
    backtrack(0, [], target);
    return result;
};