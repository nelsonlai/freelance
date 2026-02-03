#include <vector>
#include <unordered_map>

using namespace std;

class Solution {
private:
    vector<vector<int>> graph;
    vector<int> quiet;
    vector<int> result;
    
    int dfs(int node) {
        if (result[node] >= 0) {
            return result[node];
        }
        result[node] = node;
        for (int neighbor : graph[node]) {
            int candidate = dfs(neighbor);
            if (quiet[candidate] < quiet[result[node]]) {
                result[node] = candidate;
            }
        }
        return result[node];
    }

public:
    vector<int> loudAndRich(vector<vector<int>>& richer, vector<int>& quiet) {
        int n = quiet.size();
        this->quiet = quiet;
        result.assign(n, -1);
        graph.resize(n);
        
        for (auto& edge : richer) {
            graph[edge[1]].push_back(edge[0]);
        }
        
        for (int i = 0; i < n; i++) {
            dfs(i);
        }
        return result;
    }
};
