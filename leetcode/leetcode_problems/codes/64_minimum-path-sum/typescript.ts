/**
 * Problem: Minimum Path Sum
 * Difficulty: Medium
 * Tags: array, dp
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) or O(n * m) for DP table
 */

function minPathSum(grid: number[][]): number {
    const m = grid.length;
    const n = grid[0].length;
    const dp: number[] = new Array(n).fill(Number.MAX_SAFE_INTEGER);
    dp[0] = 0;
    
    for (let i = 0; i < m; i++) {
        dp[0] += grid[i][0];
        for (let j = 1; j < n; j++) {
            dp[j] = Math.min(dp[j], dp[j - 1]) + grid[i][j];
        }
    }
    
    return dp[n - 1];
};