/*
 * Problem: Second Minimum Time to Reach Destination
 * Difficulty: Hard
 * Tags: array, graph, search, BFS, Dijkstra
 * 
 * Approach: Modified BFS/Dijkstra to find second shortest path considering traffic lights
 * Time Complexity: O(n + m) where n is nodes, m is edges
 * Space Complexity: O(n + m)
 */

#include <vector>
#include <queue>
#include <algorithm>
#include <climits>

using namespace std;

class Solution {
public:
    int secondMinimum(int n, vector<vector<int>>& edges, int time, int change) {
        vector<vector<int>> graph(n + 1);
        
        for (auto& edge : edges) {
            int u = edge[0];
            int v = edge[1];
            graph[u].push_back(v);
            graph[v].push_back(u);
        }
        
        // dist[i][0] = shortest time to node i
        // dist[i][1] = second shortest time to node i
        vector<vector<int>> dist(n + 1, vector<int>(2, INT_MAX));
        dist[1][0] = 0;
        
        queue<pair<int, int>> q;
        q.push({1, 0});
        
        while (!q.empty()) {
            auto [node, currentTime] = q.front();
            q.pop();
            
            // Calculate wait time due to traffic light
            // Light changes every 2*change seconds
            if ((currentTime / change) % 2 == 1) {
                // Red light - wait until next green
                currentTime = ((currentTime / change) + 1) * change;
            }
            
            int nextTime = currentTime + time;
            
            for (int neighbor : graph[node]) {
                if (nextTime < dist[neighbor][0]) {
                    // New shortest path
                    dist[neighbor][1] = dist[neighbor][0];
                    dist[neighbor][0] = nextTime;
                    q.push({neighbor, nextTime});
                } else if (nextTime > dist[neighbor][0] && nextTime < dist[neighbor][1]) {
                    // New second shortest path
                    dist[neighbor][1] = nextTime;
                    q.push({neighbor, nextTime});
                }
            }
        }
        
        return dist[n][1];
    }
};