/**
 * Problem: Longest Common Subpath
 * Difficulty: Hard
 * Tags: array, hash, search, rolling hash, binary search
 * 
 * Approach: Binary search on length, use rolling hash to check if subpath exists in all paths
 * Time Complexity: O(m * L * log(min_path_length)) where m is paths, L is avg path length
 * Space Complexity: O(L)
 */

import java.util.*;

class Solution {
    private static final long MOD1 = 1000000007;
    private static final long MOD2 = 1000000009;
    private static final long BASE1 = 100001;
    private static final long BASE2 = 100003;
    
    public int longestCommonSubpath(int n, int[][] paths) {
        int minLen = Integer.MAX_VALUE;
        for (int[] path : paths) {
            minLen = Math.min(minLen, path.length);
        }
        
        int left = 0, right = minLen;
        int result = 0;
        
        while (left <= right) {
            int mid = (left + right) / 2;
            if (check(paths, mid)) {
                result = mid;
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
        
        return result;
    }
    
    private boolean check(int[][] paths, int length) {
        if (length == 0) return true;
        
        Set<Long> hashSet = new HashSet<>();
        long hash1 = 0, hash2 = 0;
        long pow1 = 1, pow2 = 1;
        
        // First path
        for (int i = 0; i < paths[0].length; i++) {
            hash1 = (hash1 * BASE1 + paths[0][i]) % MOD1;
            hash2 = (hash2 * BASE2 + paths[0][i]) % MOD2;
            
            if (i >= length - 1) {
                if (i >= length) {
                    hash1 = (hash1 - paths[0][i - length] * pow1 % MOD1 + MOD1) % MOD1;
                    hash2 = (hash2 - paths[0][i - length] * pow2 % MOD2 + MOD2) % MOD2;
                }
                hashSet.add(hash1 * MOD2 + hash2);
            }
            
            if (i < length - 1) {
                pow1 = (pow1 * BASE1) % MOD1;
                pow2 = (pow2 * BASE2) % MOD2;
            }
        }
        
        // Check other paths
        for (int p = 1; p < paths.length; p++) {
            Set<Long> tempSet = new HashSet<>();
            hash1 = 0;
            hash2 = 0;
            pow1 = 1;
            pow2 = 1;
            
            for (int i = 0; i < paths[p].length; i++) {
                hash1 = (hash1 * BASE1 + paths[p][i]) % MOD1;
                hash2 = (hash2 * BASE2 + paths[p][i]) % MOD2;
                
                if (i >= length - 1) {
                    if (i >= length) {
                        hash1 = (hash1 - paths[p][i - length] * pow1 % MOD1 + MOD1) % MOD1;
                        hash2 = (hash2 - paths[p][i - length] * pow2 % MOD2 + MOD2) % MOD2;
                    }
                    long hash = hash1 * MOD2 + hash2;
                    if (hashSet.contains(hash)) {
                        tempSet.add(hash);
                    }
                }
                
                if (i < length - 1) {
                    pow1 = (pow1 * BASE1) % MOD1;
                    pow2 = (pow2 * BASE2) % MOD2;
                }
            }
            
            if (tempSet.isEmpty()) {
                return false;
            }
            hashSet = tempSet;
        }
        
        return true;
    }
}