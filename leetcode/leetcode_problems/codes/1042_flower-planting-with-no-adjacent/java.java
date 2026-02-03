/**
 * Problem: Flower Planting With No Adjacent
 * Difficulty: Medium
 * Tags: array, graph, search
 * 
 * Approach: Greedy coloring - assign first available color to each garden
 * Time Complexity: O(n + m) where m is number of paths
 * Space Complexity: O(n) for graph and result
 */

import java.util.*;

class Solution {
    public int[] gardenNoAdj(int n, int[][] paths) {
        List<List<Integer>> graph = new ArrayList<>();
        for (int i = 0; i <= n; i++) {
            graph.add(new ArrayList<>());
        }
        
        for (int[] path : paths) {
            graph.get(path[0]).add(path[1]);
            graph.get(path[1]).add(path[0]);
        }
        
        int[] result = new int[n + 1];
        
        for (int i = 1; i <= n; i++) {
            boolean[] used = new boolean[5];
            for (int neighbor : graph.get(i)) {
                used[result[neighbor]] = true;
            }
            
            for (int color = 1; color <= 4; color++) {
                if (!used[color]) {
                    result[i] = color;
                    break;
                }
            }
        }
        
        return Arrays.copyOfRange(result, 1, n + 1);
    }
}