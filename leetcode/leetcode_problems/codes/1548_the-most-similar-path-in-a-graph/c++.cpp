/*
 * Problem: The Most Similar Path in a Graph
 * Difficulty: Hard
 * Tags: array, string, graph, dp
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) or O(n * m) for DP table
 */

#include <vector>
#include <string>
#include <algorithm>
#include <climits>

using namespace std;

class Solution {
public:
    vector<int> mostSimilar(int n, vector<vector<int>>& roads, vector<string>& names, vector<string>& targetPath) {
        vector<vector<int>> graph(n);
        for (auto& road : roads) {
            graph[road[0]].push_back(road[1]);
            graph[road[1]].push_back(road[0]);
        }
        
        int m = targetPath.size();
        vector<vector<int>> dp(m, vector<int>(n, INT_MAX));
        vector<vector<int>> parent(m, vector<int>(n, -1));
        
        for (int j = 0; j < n; j++) {
            dp[0][j] = (names[j] == targetPath[0]) ? 0 : 1;
        }
        
        for (int i = 1; i < m; i++) {
            for (int j = 0; j < n; j++) {
                for (int neighbor : graph[j]) {
                    int cost = (names[j] == targetPath[i]) ? 0 : 1;
                    if (dp[i-1][neighbor] != INT_MAX && dp[i-1][neighbor] + cost < dp[i][j]) {
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
        
        vector<int> result;
        result.push_back(minIdx);
        for (int i = m - 1; i > 0; i--) {
            result.push_back(parent[i][result.back()]);
        }
        reverse(result.begin(), result.end());
        return result;
    }
};