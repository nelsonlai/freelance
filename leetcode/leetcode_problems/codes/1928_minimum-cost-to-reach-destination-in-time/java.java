/**
 * Problem: Minimum Cost to Reach Destination in Time
 * Difficulty: Hard
 * Tags: array, graph, dp, shortest path
 * 
 * Approach: DP with time constraint - dp[city][time] = min cost
 * Time Complexity: O(maxTime * (n + m)) where n is cities, m is edges
 * Space Complexity: O(n * maxTime)
 */

class Solution {
    public int minCost(int maxTime, int[][] edges, int[] passingFees) {
        int n = passingFees.length;
        List<int[]>[] graph = new List[n];
        for (int i = 0; i < n; i++) {
            graph[i] = new ArrayList<>();
        }
        
        for (int[] edge : edges) {
            graph[edge[0]].add(new int[]{edge[1], edge[2]});
            graph[edge[1]].add(new int[]{edge[0], edge[2]});
        }
        
        int[][] dp = new int[n][maxTime + 1];
        for (int i = 0; i < n; i++) {
            Arrays.fill(dp[i], Integer.MAX_VALUE);
        }
        dp[0][0] = passingFees[0];
        
        for (int time = 0; time <= maxTime; time++) {
            for (int u = 0; u < n; u++) {
                if (dp[u][time] == Integer.MAX_VALUE) {
                    continue;
                }
                
                for (int[] edge : graph[u]) {
                    int v = edge[0];
                    int edgeTime = edge[1];
                    int newTime = time + edgeTime;
                    if (newTime <= maxTime) {
                        int newCost = dp[u][time] + passingFees[v];
                        if (newCost < dp[v][newTime]) {
                            dp[v][newTime] = newCost;
                        }
                    }
                }
            }
        }
        
        int result = Integer.MAX_VALUE;
        for (int time = 0; time <= maxTime; time++) {
            result = Math.min(result, dp[n - 1][time]);
        }
        
        return result == Integer.MAX_VALUE ? -1 : result;
    }
}