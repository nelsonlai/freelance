/**
 * Problem: Number of Ways to Reorder Array to Get Same BST
 * Difficulty: Hard
 * Tags: array, tree, graph, dp, math, search
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) or O(n * m) for DP table
 */

import java.util.*;

class Solution {
    private static final int MOD = 1000000007;
    
    public int numOfWays(int[] nums) {
        List<Integer> list = new ArrayList<>();
        for (int num : nums) {
            list.add(num);
        }
        return (ways(list) - 1) % MOD;
    }
    
    private int nCr(int n, int r) {
        if (r > n || r < 0) {
            return 0;
        }
        if (r == 0 || r == n) {
            return 1;
        }
        r = Math.min(r, n - r);
        long result = 1;
        for (int i = 0; i < r; i++) {
            result = result * (n - i) / (i + 1);
        }
        return (int) (result % MOD);
    }
    
    private int ways(List<Integer> arr) {
        if (arr.size() <= 2) {
            return 1;
        }
        
        int root = arr.get(0);
        List<Integer> left = new ArrayList<>();
        List<Integer> right = new ArrayList<>();
        
        for (int x : arr) {
            if (x < root) {
                left.add(x);
            } else if (x > root) {
                right.add(x);
            }
        }
        
        long leftWays = ways(left);
        long rightWays = ways(right);
        
        return (int) ((long) nCr(left.size() + right.size(), left.size()) * leftWays % MOD * rightWays % MOD);
    }
}