#include <vector>
#include <unordered_map>
#include <queue>

using namespace std;

class Solution {
public:
    int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int k) {
        unordered_map<int, vector<pair<int, int>>> graph;
        for (auto& flight : flights) {
            graph[flight[0]].push_back({flight[1], flight[2]});
        }
        
        priority_queue<vector<int>, vector<vector<int>>, greater<vector<int>>> heap;
        heap.push({0, src, k + 1});
        unordered_map<int, int> visited;
        
        while (!heap.empty()) {
            auto curr = heap.top();
            heap.pop();
            int cost = curr[0], node = curr[1], stops = curr[2];
            
            if (node == dst) {
                return cost;
            }
            
            if (stops > 0) {
                for (auto& edge : graph[node]) {
                    int neighbor = edge.first, weight = edge.second;
                    int newCost = cost + weight;
                    if (visited.find(neighbor) == visited.end() || visited[neighbor] < stops - 1) {
                        visited[neighbor] = stops - 1;
                        heap.push({newCost, neighbor, stops - 1});
                    }
                }
            }
        }
        
        return -1;
    }
};
