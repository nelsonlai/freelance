/*
 * Problem: Jump Game II
 * Difficulty: Medium
 * Tags: array, dp, greedy
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) or O(n * m) for DP table
 */

int jump(int* nums, int numsSize) {
    int jumps = 0;
    int currentEnd = 0;
    int farthest = 0;
    
    for (int i = 0; i < numsSize - 1; i++) {
        if (i + nums[i] > farthest) {
            farthest = i + nums[i];
        }
        if (i == currentEnd) {
            jumps++;
            currentEnd = farthest;
        }
    }
    
    return jumps;
}