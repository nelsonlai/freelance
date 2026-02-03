/**
 * Problem: Sum of Floored Pairs
 * Difficulty: Hard
 * Tags: array, math, search, prefix sum
 * 
 * Approach: Count frequency, use prefix sum to count pairs efficiently
 * Time Complexity: O(n + max * log(max)) where max is max value
 * Space Complexity: O(max)
 */

import java.util.*;

class Solution {
    private static final int MOD = 1000000007;
    
    public int sumOfFlooredPairs(int[] nums) {
        int maxVal = Arrays.stream(nums).max().orElse(0);
        Map<Integer, Integer> count = new HashMap<>();
        for (int num : nums) {
            count.put(num, count.getOrDefault(num, 0) + 1);
        }
        
        long[] prefix = new long[maxVal + 1];
        for (int i = 1; i <= maxVal; i++) {
            prefix[i] = prefix[i - 1] + count.getOrDefault(i, 0);
        }
        
        long result = 0;
        for (Map.Entry<Integer, Integer> entry : count.entrySet()) {
            int num = entry.getKey();
            int freq = entry.getValue();
            
            for (int multiple = num; multiple <= maxVal; multiple += num) {
                int end = Math.min(multiple + num - 1, maxVal);
                long cnt = prefix[end] - prefix[multiple - 1];
                result = (result + (multiple / num) * cnt * freq) % MOD;
            }
        }
        
        return (int) result;
    }
}