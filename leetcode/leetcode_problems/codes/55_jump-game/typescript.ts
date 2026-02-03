/**
 * Problem: Jump Game
 * Difficulty: Medium
 * Tags: array, dp, greedy
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) or O(n * m) for DP table
 */

function canJump(nums: number[]): boolean {
    let farthest = 0;
    for (let i = 0; i < nums.length; i++) {
        if (i > farthest) {
            return false;
        }
        farthest = Math.max(farthest, i + nums[i]);
        if (farthest >= nums.length - 1) {
            return true;
        }
    }
    return true;
};