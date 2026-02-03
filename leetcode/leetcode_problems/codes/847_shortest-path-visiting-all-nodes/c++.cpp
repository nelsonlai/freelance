#include <vector>
#include <queue>
#include <unordered_set>
#include <string>

using namespace std;

class Solution {
public:
    int shortestPathLength(vector<vector<int>>& graph) {
        int n = graph.size();
        int target = (1 << n) - 1;
        queue<pair<int, int>> q;
        unordered_set<string> visited;
        
        for (int i = 0; i < n; i++) {
            q.push({i, 1 << i});
            visited.insert(to_string(i) + "," + to_string(1 << i));
        }
        
        int steps = 0;
        while (!q.empty()) {
            int size = q.size();
            for (int i = 0; i < size; i++) {
                auto [node, state] = q.front();
                q.pop();
                if (state == target) {
                    return steps;
                }
                for (int neighbor : graph[node]) {
                    int newState = state | (1 << neighbor);
                    string key = to_string(neighbor) + "," + to_string(newState);
                    if (visited.find(key) == visited.end()) {
                        visited.insert(key);
                        q.push({neighbor, newState});
                    }
                }
            }
            steps++;
        }
        return -1;
    }
};
