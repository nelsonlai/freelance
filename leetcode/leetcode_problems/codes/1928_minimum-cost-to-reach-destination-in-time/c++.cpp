/*
 * Problem: Minimum Cost to Reach Destination in Time
 * Difficulty: Hard
 * Tags: array, graph, dp, shortest path
 * 
 * Approach: DP with time constraint - dp[city][time] = min cost
 * Time Complexity: O(maxTime * (n + m)) where n is cities, m is edges
 * Space Complexity: O(n * maxTime)
 */

#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

class Solution {
public:
    int minCost(int maxTime, vector<vector<int>>& edges, vector<int>& passingFees) {
        int n = passingFees.size();
        vector<vector<pair<int, int>>> graph(n);
        
        for (auto& edge : edges) {
            graph[edge[0]].push_back({edge[1], edge[2]});
            graph[edge[1]].push_back({edge[0], edge[2]});
        }
        
        vector<vector<int>> dp(n, vector<int>(maxTime + 1, INT_MAX));
        dp[0][0] = passingFees[0];
        
        for (int time = 0; time <= maxTime; time++) {
            for (int u = 0; u < n; u++) {
                if (dp[u][time] == INT_MAX) {
                    continue;
                }
                
                for (auto& [v, edgeTime] : graph[u]) {
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
        
        int result = INT_MAX;
        for (int time = 0; time <= maxTime; time++) {
            result = min(result, dp[n - 1][time]);
        }
        
        return result == INT_MAX ? -1 : result;
    }
};