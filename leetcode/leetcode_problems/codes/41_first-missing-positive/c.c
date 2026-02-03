/*
 * Problem: First Missing Positive
 * Difficulty: Hard
 * Tags: array, hash, sort
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) for hash map
 */

int firstMissingPositive(int* nums, int numsSize) {
    // Place each number in its correct position
    for (int i = 0; i < numsSize; i++) {
        while (nums[i] >= 1 && nums[i] <= numsSize && nums[nums[i] - 1] != nums[i]) {
            int temp = nums[nums[i] - 1];
            nums[nums[i] - 1] = nums[i];
            nums[i] = temp;
        }
    }
    
    // Find the first missing positive
    for (int i = 0; i < numsSize; i++) {
        if (nums[i] != i + 1) {
            return i + 1;
        }
    }
    
    return numsSize + 1;
}