/*
 * Problem: Graph Valid Tree
 * Difficulty: Medium
 * Tags: tree, graph, search
 * 
 * Approach: DFS or BFS traversal
 * Time Complexity: O(n) where n is number of nodes
 * Space Complexity: O(h) for recursion stack where h is height
 */

#include <vector>
#include <unordered_set>

using namespace std;

class Solution {
private:
    bool dfs(int node, int parent, vector<vector<int>>& graph, unordered_set<int>& visited) {
        if (visited.find(node) != visited.end()) {
            return false;
        }
        
        visited.insert(node);
        for (int neighbor : graph[node]) {
            if (neighbor != parent) {
                if (!dfs(neighbor, node, graph, visited)) {
                    return false;
                }
            }
        }
        return true;
    }

public:
    bool validTree(int n, vector<vector<int>>& edges) {
        if (edges.size() != n - 1) {
            return false;
        }
        
        vector<vector<int>> graph(n);
        for (auto& edge : edges) {
            graph[edge[0]].push_back(edge[1]);
            graph[edge[1]].push_back(edge[0]);
        }
        
        unordered_set<int> visited;
        
        if (!dfs(0, -1, graph, visited)) {
            return false;
        }
        
        return visited.size() == n;
    }
};