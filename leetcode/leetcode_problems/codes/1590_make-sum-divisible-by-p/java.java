/**
 * Problem: Make Sum Divisible by P
 * Difficulty: Medium
 * Tags: array, hash
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) for hash map
 */

import java.util.*;

class Solution {
    public int minSubarray(int[] nums, int p) {
        long total = 0;
        for (int num : nums) {
            total += num;
        }
        int remainder = (int)(total % p);
        if (remainder == 0) {
            return 0;
        }
        
        Map<Integer, Integer> lastPos = new HashMap<>();
        lastPos.put(0, -1);
        long prefix = 0;
        int result = nums.length;
        
        for (int i = 0; i < nums.length; i++) {
            prefix = (prefix + nums[i]) % p;
            int target = (int)((prefix - remainder + p) % p);
            
            if (lastPos.containsKey(target)) {
                result = Math.min(result, i - lastPos.get(target));
            }
            
            lastPos.put((int)prefix, i);
        }
        
        return result < nums.length ? result : -1;
    }
}