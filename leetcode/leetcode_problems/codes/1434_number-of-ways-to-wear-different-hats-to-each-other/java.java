/**
 * Problem: Number of Ways to Wear Different Hats to Each Other
 * Difficulty: Hard
 * Tags: array, dp
 * 
 * Approach: DP with bitmask - dp[mask][hat] = ways to assign hats to people in mask
 * Time Complexity: O(n * 2^n * m) where n is people, m is hats
 * Space Complexity: O(2^n * m)
 */

import java.util.*;

class Solution {
    public int numberWays(List<List<Integer>> hats) {
        int MOD = 1000000007;
        int n = hats.size();
        List<List<Integer>> hatToPeople = new ArrayList<>();
        for (int i = 0; i <= 40; i++) {
            hatToPeople.add(new ArrayList<>());
        }
        
        for (int person = 0; person < n; person++) {
            for (int hat : hats.get(person)) {
                hatToPeople.get(hat).add(person);
            }
        }
        
        long[] dp = new long[1 << n];
        dp[0] = 1;
        
        for (int hat = 1; hat <= 40; hat++) {
            long[] newDp = dp.clone();
            for (int person : hatToPeople.get(hat)) {
                for (int mask = 0; mask < (1 << n); mask++) {
                    if ((mask & (1 << person)) != 0) {
                        newDp[mask] = (newDp[mask] + dp[mask ^ (1 << person)]) % MOD;
                    }
                }
            }
            dp = newDp;
        }
        
        return (int) dp[(1 << n) - 1];
    }
}