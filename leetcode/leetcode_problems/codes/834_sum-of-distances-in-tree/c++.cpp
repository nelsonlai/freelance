#include <vector>

using namespace std;

class Solution {
private:
    vector<vector<int>> graph;
    vector<int> count;
    vector<int> ans;
    
    void dfs(int node, int parent) {
        for (int child : graph[node]) {
            if (child != parent) {
                dfs(child, node);
                count[node] += count[child];
                ans[node] += ans[child] + count[child];
            }
        }
    }
    
    void dfs2(int node, int parent) {
        for (int child : graph[node]) {
            if (child != parent) {
                ans[child] = ans[node] - count[child] + count.size() - count[child];
                dfs2(child, node);
            }
        }
    }

public:
    vector<int> sumOfDistancesInTree(int n, vector<vector<int>>& edges) {
        graph.resize(n);
        for (auto& edge : edges) {
            graph[edge[0]].push_back(edge[1]);
            graph[edge[1]].push_back(edge[0]);
        }
        
        count.assign(n, 1);
        ans.assign(n, 0);
        
        dfs(0, -1);
        dfs2(0, -1);
        return ans;
    }
};
