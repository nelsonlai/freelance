/*
 * Problem: Path with Maximum Probability
 * Difficulty: Medium
 * Tags: array, graph, queue, heap
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

class Solution {
public:
    double maxProbability(int n, vector<vector<int>>& edges, vector<double>& succProb, int start_node, int end_node) {
        vector<vector<pair<int, double>>> graph(n);
        for (int i = 0; i < edges.size(); i++) {
            int u = edges[i][0];
            int v = edges[i][1];
            double prob = succProb[i];
            graph[u].push_back({v, prob});
            graph[v].push_back({u, prob});
        }
        
        vector<double> maxProb(n, 0.0);
        maxProb[start_node] = 1.0;
        
        priority_queue<pair<double, int>> heap;
        heap.push({1.0, start_node});
        
        while (!heap.empty()) {
            auto [prob, node] = heap.top();
            heap.pop();
            
            if (node == end_node) {
                return prob;
            }
            
            if (prob < maxProb[node]) {
                continue;
            }
            
            for (auto& [next, edgeProb] : graph[node]) {
                double newProb = prob * edgeProb;
                if (newProb > maxProb[next]) {
                    maxProb[next] = newProb;
                    heap.push({newProb, next});
                }
            }
        }
        
        return 0.0;
    }
};