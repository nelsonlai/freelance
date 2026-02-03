/**
 * Problem: Most Stones Removed with Same Row or Column
 * Difficulty: Medium
 * Tags: array, graph, hash, search
 * 
 * Approach: Union-Find to group stones in same row/column, answer is total - number of groups
 * Time Complexity: O(n * α(n)) where α is inverse Ackermann function
 * Space Complexity: O(n) for Union-Find
 */

import java.util.*;

class Solution {
    private Map<Integer, Integer> parent = new HashMap<>();
    
    public int removeStones(int[][] stones) {
        for (int[] stone : stones) {
            union(stone[0], ~stone[1]);
        }
        
        Set<Integer> groups = new HashSet<>();
        for (int[] stone : stones) {
            groups.add(find(stone[0]));
        }
        
        return stones.length - groups.size();
    }
    
    private int find(int x) {
        if (!parent.containsKey(x)) {
            parent.put(x, x);
        }
        if (parent.get(x) != x) {
            parent.put(x, find(parent.get(x)));
        }
        return parent.get(x);
    }
    
    private void union(int x, int y) {
        parent.put(find(x), find(y));
    }
}