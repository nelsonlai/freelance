/**
 * Problem: Partition Array Into Three Parts With Equal Sum
 * Difficulty: Easy
 * Tags: array, greedy
 * 
 * Approach: Check if sum is divisible by 3, then find two split points
 * Time Complexity: O(n)
 * Space Complexity: O(1)
 */

class Solution {
    public boolean canThreePartsEqualSum(int[] arr) {
        int total = 0;
        for (int num : arr) {
            total += num;
        }
        if (total % 3 != 0) {
            return false;
        }
        
        int target = total / 3;
        int currentSum = 0;
        int count = 0;
        
        for (int num : arr) {
            currentSum += num;
            if (currentSum == target) {
                count++;
                currentSum = 0;
                if (count == 2) {
                    return true;
                }
            }
        }
        
        return false;
    }
}