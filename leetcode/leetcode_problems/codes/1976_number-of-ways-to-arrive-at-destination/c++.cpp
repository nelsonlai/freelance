/*
 * Problem: Number of Ways to Arrive at Destination
 * Difficulty: Medium
 * Tags: array, graph, dp, sort, Dijkstra
 * 
 * Approach: Dijkstra to find shortest paths, count ways using DP
 * Time Complexity: O((n + m) log n) where n is nodes, m is edges
 * Space Complexity: O(n + m)
 */

#include <vector>
#include <queue>
#include <climits>

using namespace std;

class Solution {
private:
    static constexpr int MOD = 1000000007;
    
public:
    int countPaths(int n, vector<vector<int>>& roads) {
        vector<vector<pair<int, int>>> graph(n);
        for (auto& road : roads) {
            graph[road[0]].push_back({road[1], road[2]});
            graph[road[1]].push_back({road[0], road[2]});
        }
        
        vector<long long> dist(n, LLONG_MAX);
        vector<long long> ways(n, 0);
        dist[0] = 0;
        ways[0] = 1;
        
        priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> heap;
        heap.push({0, 0});
        
        while (!heap.empty()) {
            auto [d, u] = heap.top();
            heap.pop();
            
            if (d > dist[u]) {
                continue;
            }
            
            for (auto& [v, time] : graph[u]) {
                if (dist[u] + time < dist[v]) {
                    dist[v] = dist[u] + time;
                    ways[v] = ways[u];
                    heap.push({dist[v], v});
                } else if (dist[u] + time == dist[v]) {
                    ways[v] = (ways[v] + ways[u]) % MOD;
                }
            }
        }
        
        return ways[n - 1];
    }
};
