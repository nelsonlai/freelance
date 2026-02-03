/**
 * Problem: Queries on a Permutation With Key
 * Difficulty: Medium
 * Tags: array, tree
 * 
 * Approach: Simulate - find index, move to front, track positions
 * Time Complexity: O(q * m) where q is queries length
 * Space Complexity: O(m) for permutation
 */

import java.util.*;

class Solution {
    public int[] processQueries(int[] queries, int m) {
        List<Integer> perm = new ArrayList<>();
        for (int i = 1; i <= m; i++) {
            perm.add(i);
        }
        
        int[] result = new int[queries.length];
        for (int i = 0; i < queries.length; i++) {
            int idx = perm.indexOf(queries[i]);
            result[i] = idx;
            perm.remove(idx);
            perm.add(0, queries[i]);
        }
        
        return result;
    }
}