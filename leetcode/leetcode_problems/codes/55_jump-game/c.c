/*
 * Problem: Jump Game
 * Difficulty: Medium
 * Tags: array, dp, greedy
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) or O(n * m) for DP table
 */

#include <stdbool.h>

bool canJump(int* nums, int numsSize) {
    int farthest = 0;
    for (int i = 0; i < numsSize; i++) {
        if (i > farthest) {
            return false;
        }
        if (i + nums[i] > farthest) {
            farthest = i + nums[i];
        }
        if (farthest >= numsSize - 1) {
            return true;
        }
    }
    return true;
}