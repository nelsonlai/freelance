#include <vector>
#include <queue>
#include <climits>

using namespace std;

class Solution {
public:
    int reachableNodes(vector<vector<int>>& edges, int maxMoves, int n) {
        vector<vector<pair<int, int>>> graph(n);
        for (auto& edge : edges) {
            graph[edge[0]].push_back({edge[1], edge[2] + 1});
            graph[edge[1]].push_back({edge[0], edge[2] + 1});
        }
        
        vector<int> dist(n, INT_MAX);
        dist[0] = 0;
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> heap;
        heap.push({0, 0});
        
        while (!heap.empty()) {
            auto [d, node] = heap.top();
            heap.pop();
            if (d > dist[node]) continue;
            for (auto [neighbor, weight] : graph[node]) {
                if (dist[node] + weight < dist[neighbor]) {
                    dist[neighbor] = dist[node] + weight;
                    heap.push({dist[neighbor], neighbor});
                }
            }
        }
        
        int result = 0;
        for (int d : dist) {
            if (d <= maxMoves) result++;
        }
        
        for (auto& edge : edges) {
            int u = edge[0], v = edge[1], w = edge[2];
            int a = max(0, maxMoves - dist[u]);
            int b = max(0, maxMoves - dist[v]);
            result += min(a + b, w);
        }
        
        return result;
    }
};
