/*
 * Problem: Largest Color Value in a Directed Graph
 * Difficulty: Hard
 * Tags: array, string, graph, dp, topological sort
 * 
 * Approach: Topological sort with DP to track max color count per path
 * Time Complexity: O(n + m) where n is nodes, m is edges
 * Space Complexity: O(n + m)
 */

#include <vector>
#include <queue>
#include <string>
#include <algorithm>

using namespace std;

class Solution {
public:
    int largestPathValue(string colors, vector<vector<int>>& edges) {
        int n = colors.size();
        vector<vector<int>> graph(n);
        vector<int> indegree(n, 0);
        
        for (auto& edge : edges) {
            graph[edge[0]].push_back(edge[1]);
            indegree[edge[1]]++;
        }
        
        vector<vector<int>> dp(n, vector<int>(26, 0));
        queue<int> q;
        
        for (int i = 0; i < n; i++) {
            if (indegree[i] == 0) {
                q.push(i);
            }
        }
        
        int processed = 0;
        int result = 0;
        
        while (!q.empty()) {
            int node = q.front();
            q.pop();
            processed++;
            
            int colorIdx = colors[node] - 'a';
            dp[node][colorIdx]++;
            result = max(result, dp[node][colorIdx]);
            
            for (int neighbor : graph[node]) {
                for (int c = 0; c < 26; c++) {
                    dp[neighbor][c] = max(dp[neighbor][c], dp[node][c]);
                }
                
                indegree[neighbor]--;
                if (indegree[neighbor] == 0) {
                    q.push(neighbor);
                }
            }
        }
        
        return processed == n ? result : -1;
    }
};