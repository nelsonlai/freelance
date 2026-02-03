/*
 * Problem: Find if Path Exists in Graph
 * Difficulty: Easy
 * Tags: array, graph, search, BFS/DFS
 * 
 * Approach: BFS or DFS to check if path exists from source to destination
 * Time Complexity: O(n + m) where n is nodes, m is edges
 * Space Complexity: O(n)
 */

#include <vector>
#include <queue>

using namespace std;

class Solution {
public:
    bool validPath(int n, vector<vector<int>>& edges, int source, int destination) {
        if (source == destination) {
            return true;
        }
        
        vector<vector<int>> graph(n);
        for (auto& edge : edges) {
            graph[edge[0]].push_back(edge[1]);
            graph[edge[1]].push_back(edge[0]);
        }
        
        queue<int> q;
        vector<bool> visited(n, false);
        q.push(source);
        visited[source] = true;
        
        while (!q.empty()) {
            int node = q.front();
            q.pop();
            if (node == destination) {
                return true;
            }
            
            for (int neighbor : graph[node]) {
                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    q.push(neighbor);
                }
            }
        }
        
        return false;
    }
};