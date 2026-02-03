#include <vector>

using namespace std;

class Solution {
private:
    vector<vector<int>> result;
    
    void dfs(vector<vector<int>>& graph, int node, vector<int>& path) {
        if (node == graph.size() - 1) {
            result.push_back(path);
            return;
        }
        
        for (int neighbor : graph[node]) {
            path.push_back(neighbor);
            dfs(graph, neighbor, path);
            path.pop_back();
        }
    }

public:
    vector<vector<int>> allPathsSourceTarget(vector<vector<int>>& graph) {
        vector<int> path = {0};
        dfs(graph, 0, path);
        return result;
    }
};
