#include <vector>
#include <unordered_map>

using namespace std;

class Solution {
private:
    unordered_map<int, vector<int>> graph;
    unordered_map<int, int> color;
    
    bool dfs(int node, int c) {
        if (color.find(node) != color.end()) {
            return color[node] == c;
        }
        color[node] = c;
        for (int neighbor : graph[node]) {
            if (!dfs(neighbor, 1 - c)) {
                return false;
            }
        }
        return true;
    }

public:
    bool possibleBipartition(int n, vector<vector<int>>& dislikes) {
        for (auto& dislike : dislikes) {
            graph[dislike[0]].push_back(dislike[1]);
            graph[dislike[1]].push_back(dislike[0]);
        }
        
        for (int i = 1; i <= n; i++) {
            if (color.find(i) == color.end()) {
                if (!dfs(i, 0)) {
                    return false;
                }
            }
        }
        return true;
    }
};
