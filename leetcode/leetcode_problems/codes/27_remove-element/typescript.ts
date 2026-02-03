/**
 * Problem: Remove Element
 * Difficulty: Easy
 * Tags: array, sort
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

function removeElement(nums: number[], val: number): number {
    let writeIndex = 0;
    for (let i = 0; i < nums.length; i++) {
        if (nums[i] !== val) {
            nums[writeIndex] = nums[i];
            writeIndex++;
        }
    }
    return writeIndex;
};