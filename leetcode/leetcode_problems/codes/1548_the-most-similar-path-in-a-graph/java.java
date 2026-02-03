/**
 * Problem: The Most Similar Path in a Graph
 * Difficulty: Hard
 * Tags: array, string, graph, dp
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) or O(n * m) for DP table
 */

import java.util.*;

class Solution {
    public List<Integer> mostSimilar(int n, int[][] roads, String[] names, String[] targetPath) {
        List<List<Integer>> graph = new ArrayList<>();
        for (int i = 0; i < n; i++) {
            graph.add(new ArrayList<>());
        }
        for (int[] road : roads) {
            graph.get(road[0]).add(road[1]);
            graph.get(road[1]).add(road[0]);
        }
        
        int m = targetPath.length;
        int[][] dp = new int[m][n];
        int[][] parent = new int[m][n];
        
        for (int i = 0; i < m; i++) {
            Arrays.fill(dp[i], Integer.MAX_VALUE);
            Arrays.fill(parent[i], -1);
        }
        
        for (int j = 0; j < n; j++) {
            dp[0][j] = names[j].equals(targetPath[0]) ? 0 : 1;
        }
        
        for (int i = 1; i < m; i++) {
            for (int j = 0; j < n; j++) {
                for (int neighbor : graph.get(j)) {
                    int cost = names[j].equals(targetPath[i]) ? 0 : 1;
                    if (dp[i-1][neighbor] != Integer.MAX_VALUE && dp[i-1][neighbor] + cost < dp[i][j]) {
                        dp[i][j] = dp[i-1][neighbor] + cost;
                        parent[i][j] = neighbor;
                    }
                }
            }
        }
        
        int minIdx = 0;
        for (int j = 1; j < n; j++) {
            if (dp[m-1][j] < dp[m-1][minIdx]) {
                minIdx = j;
            }
        }
        
        List<Integer> result = new ArrayList<>();
        result.add(minIdx);
        for (int i = m - 1; i > 0; i--) {
            result.add(parent[i][result.get(result.size() - 1)]);
        }
        Collections.reverse(result);
        return result;
    }
}