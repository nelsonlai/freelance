/**
 * Problem: Count Ways to Build Rooms in an Ant Colony
 * Difficulty: Hard
 * Tags: array, tree, graph, dp, math, combinatorics
 * 
 * Approach: Tree DP with combinatorics - count ways to order children
 * Time Complexity: O(n) where n is rooms
 * Space Complexity: O(n)
 */

import java.util.*;

class Solution {
    private static final int MOD = 1000000007;
    private List<List<Integer>> graph;
    private long[] fact;
    private long[] invFact;
    
    public int waysToBuildRooms(int[] prevRoom) {
        int n = prevRoom.length;
        graph = new ArrayList<>();
        for (int i = 0; i < n; i++) {
            graph.add(new ArrayList<>());
        }
        
        for (int i = 1; i < n; i++) {
            graph.get(prevRoom[i]).add(i);
        }
        
        // Precompute factorials
        fact = new long[n + 1];
        invFact = new long[n + 1];
        fact[0] = 1;
        invFact[0] = 1;
        for (int i = 1; i <= n; i++) {
            fact[i] = (fact[i - 1] * i) % MOD;
            invFact[i] = modInverse(fact[i], MOD);
        }
        
        long[] result = dfs(0);
        return (int) result[1];
    }
    
    private long[] dfs(int node) {
        long totalSize = 1;
        long ways = 1;
        
        List<long[]> children = new ArrayList<>();
        for (int child : graph.get(node)) {
            long[] childResult = dfs(child);
            children.add(childResult);
            totalSize += childResult[0];
        }
        
        long remaining = totalSize - 1;
        for (long[] child : children) {
            long childSize = child[0];
            long childWays = child[1];
            long comb = nCr((int) remaining, (int) childSize);
            ways = (ways * comb % MOD * childWays) % MOD;
            remaining -= childSize;
        }
        
        return new long[]{totalSize, ways};
    }
    
    private long nCr(int n, int r) {
        if (r > n || r < 0) return 0;
        return fact[n] * invFact[r] % MOD * invFact[n - r] % MOD;
    }
    
    private long modInverse(long a, long m) {
        return power(a, m - 2, m);
    }
    
    private long power(long base, long exp, long mod) {
        long result = 1;
        while (exp > 0) {
            if ((exp & 1) == 1) {
                result = (result * base) % mod;
            }
            base = (base * base) % mod;
            exp >>= 1;
        }
        return result;
    }
}