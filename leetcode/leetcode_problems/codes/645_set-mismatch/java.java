/**
 * Problem: Set Mismatch
 * Difficulty: Easy
 * Tags: array, hash, sort
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) for hash map
 */

import java.util.*;

class Solution {
    public int[] findErrorNums(int[] nums) {
        int n = nums.length;
        int expectedSum = n * (n + 1) / 2;
        int actualSum = 0;
        Set<Integer> seen = new HashSet<>();
        int duplicate = 0;
        
        for (int num : nums) {
            actualSum += num;
            if (seen.contains(num)) {
                duplicate = num;
            }
            seen.add(num);
        }
        
        int missing = expectedSum - (actualSum - duplicate);
        return new int[]{duplicate, missing};
    }
}