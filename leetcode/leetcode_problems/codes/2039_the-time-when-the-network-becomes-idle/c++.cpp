/*
 * Problem: The Time When the Network Becomes Idle
 * Difficulty: Medium
 * Tags: array, graph, search, BFS
 * 
 * Approach: BFS to find shortest distances, calculate when each server becomes idle
 * Time Complexity: O(n + m) where n is nodes, m is edges
 * Space Complexity: O(n + m)
 */

#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

class Solution {
public:
    int networkBecomesIdle(vector<vector<int>>& edges, vector<int>& patience) {
        int n = patience.size();
        vector<vector<int>> graph(n);
        
        for (auto& edge : edges) {
            graph[edge[0]].push_back(edge[1]);
            graph[edge[1]].push_back(edge[0]);
        }
        
        // BFS to find shortest distances from node 0
        vector<int> dist(n, -1);
        dist[0] = 0;
        queue<int> q;
        q.push(0);
        
        while (!q.empty()) {
            int node = q.front();
            q.pop();
            for (int neighbor : graph[node]) {
                if (dist[neighbor] == -1) {
                    dist[neighbor] = dist[node] + 1;
                    q.push(neighbor);
                }
            }
        }
        
        int maxTime = 0;
        
        for (int i = 1; i < n; i++) {
            int roundTrip = 2 * dist[i];
            int idleTime;
            
            // Calculate when last message is sent
            if (roundTrip <= patience[i]) {
                // No resend needed
                idleTime = roundTrip + 1;
            } else {
                // Last resend happens at: patience[i] * floor((roundTrip - 1) / patience[i])
                int lastSend = patience[i] * ((roundTrip - 1) / patience[i]);
                idleTime = lastSend + roundTrip + 1;
            }
            
            maxTime = max(maxTime, idleTime);
        }
        
        return maxTime;
    }
};