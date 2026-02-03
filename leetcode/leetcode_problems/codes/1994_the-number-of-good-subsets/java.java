/**
 * Problem: The Number of Good Subsets
 * Difficulty: Hard
 * Tags: array, dp, math, hash, bitmask
 * 
 * Approach: DP with bitmask - track products that are square-free
 * Time Complexity: O(n * 2^10) where n is length, 10 is primes <= 30
 * Space Complexity: O(2^10)
 */

import java.util.*;

class Solution {
    private static final int MOD = 1000000007;
    private static final int[] PRIMES = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};
    
    public int numberOfGoodSubsets(int[] nums) {
        Map<Integer, Integer> count = new HashMap<>();
        for (int num : nums) {
            count.put(num, count.getOrDefault(num, 0) + 1);
        }
        
        int[] dp = new int[1 << 10];
        dp[0] = 1;
        
        for (int num = 2; num <= 30; num++) {
            if (!count.containsKey(num)) {
                continue;
            }
            int mask = getMask(num);
            if (mask == -1) {
                continue;
            }
            
            for (int prevMask = (1 << 10) - 1; prevMask >= 0; prevMask--) {
                if ((prevMask & mask) == 0) {
                    dp[prevMask | mask] = (int) ((dp[prevMask | mask] + 
                        (long) dp[prevMask] * count.get(num)) % MOD);
                }
            }
        }
        
        long result = 0;
        for (int i = 1; i < (1 << 10); i++) {
            result = (result + dp[i]) % MOD;
        }
        
        if (count.containsKey(1)) {
            result = (result * pow(2, count.get(1))) % MOD;
        }
        
        return (int) result;
    }
    
    private int getMask(int num) {
        int mask = 0;
        for (int i = 0; i < PRIMES.length; i++) {
            if (num % PRIMES[i] == 0) {
                if ((num / PRIMES[i]) % PRIMES[i] == 0) {
                    return -1;
                }
                mask |= (1 << i);
            }
        }
        return mask;
    }
    
    private long pow(long base, int exp) {
        long result = 1;
        while (exp > 0) {
            if ((exp & 1) == 1) {
                result = (result * base) % MOD;
            }
            base = (base * base) % MOD;
            exp >>= 1;
        }
        return result;
    }
}
