#include <vector>
#include <unordered_map>
#include <queue>
#include <climits>

using namespace std;

class Solution {
public:
    int networkDelayTime(vector<vector<int>>& times, int n, int k) {
        unordered_map<int, vector<pair<int, int>>> graph;
        for (auto& time : times) {
            graph[time[0]].push_back({time[1], time[2]});
        }
        
        vector<int> dist(n + 1, INT_MAX);
        dist[k] = 0;
        
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> heap;
        heap.push({0, k});
        
        while (!heap.empty()) {
            auto [d, node] = heap.top();
            heap.pop();
            if (d > dist[node]) continue;
            for (auto& [neighbor, weight] : graph[node]) {
                if (dist[node] + weight < dist[neighbor]) {
                    dist[neighbor] = dist[node] + weight;
                    heap.push({dist[neighbor], neighbor});
                }
            }
        }
        
        int maxDist = 0;
        for (int i = 1; i <= n; i++) {
            if (dist[i] == INT_MAX) return -1;
            maxDist = max(maxDist, dist[i]);
        }
        return maxDist;
    }
};
