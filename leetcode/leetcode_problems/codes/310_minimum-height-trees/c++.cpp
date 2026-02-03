/*
 * Problem: Minimum Height Trees
 * Difficulty: Medium
 * Tags: array, tree, graph, sort, search
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(h) for recursion stack where h is height
 */

#include <vector>
#include <queue>
#include <unordered_set>

using namespace std;

class Solution {
public:
    vector<int> findMinHeightTrees(int n, vector<vector<int>>& edges) {
        if (n == 1) {
            return {0};
        }
        
        vector<unordered_set<int>> graph(n);
        for (auto& edge : edges) {
            graph[edge[0]].insert(edge[1]);
            graph[edge[1]].insert(edge[0]);
        }
        
        queue<int> leaves;
        for (int i = 0; i < n; i++) {
            if (graph[i].size() == 1) {
                leaves.push(i);
            }
        }
        
        while (n > 2) {
            n -= leaves.size();
            int size = leaves.size();
            for (int i = 0; i < size; i++) {
                int leaf = leaves.front();
                leaves.pop();
                int neighbor = *graph[leaf].begin();
                graph[neighbor].erase(leaf);
                if (graph[neighbor].size() == 1) {
                    leaves.push(neighbor);
                }
            }
        }
        
        vector<int> result;
        while (!leaves.empty()) {
            result.push_back(leaves.front());
            leaves.pop();
        }
        return result;
    }
};