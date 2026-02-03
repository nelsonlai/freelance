/*
 * Problem: 3Sum Closest
 * Difficulty: Medium
 * Tags: array, sort
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

#include <stdlib.h>
#include <limits.h>

int compare(const void* a, const void* b) {
    return *(int*)a - *(int*)b;
}

int threeSumClosest(int* nums, int numsSize, int target) {
    qsort(nums, numsSize, sizeof(int), compare);
    int closestSum = nums[0] + nums[1] + nums[2];
    
    for (int i = 0; i < numsSize - 2; i++) {
        int left = i + 1, right = numsSize - 1;
        while (left < right) {
            int currentSum = nums[i] + nums[left] + nums[right];
            int currentDiff = abs(currentSum - target);
            int closestDiff = abs(closestSum - target);
            
            if (currentDiff < closestDiff) {
                closestSum = currentSum;
            }
            
            if (currentSum < target) {
                left++;
            } else if (currentSum > target) {
                right--;
            } else {
                return currentSum;
            }
        }
    }
    
    return closestSum;
}