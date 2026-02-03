#include <vector>
#include <queue>
#include <unordered_set>
#include <string>

using namespace std;

class Solution {
public:
    int swimInWater(vector<vector<int>>& grid) {
        int n = grid.size();
        priority_queue<vector<int>, vector<vector<int>>, greater<vector<int>>> heap;
        heap.push({grid[0][0], 0, 0});
        unordered_set<string> visited;
        visited.insert("0,0");
        vector<vector<int>> directions = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
        
        while (!heap.empty()) {
            auto curr = heap.top();
            heap.pop();
            int time = curr[0], r = curr[1], c = curr[2];
            if (r == n - 1 && c == n - 1) {
                return time;
            }
            
            for (auto& dir : directions) {
                int nr = r + dir[0], nc = c + dir[1];
                string key = to_string(nr) + "," + to_string(nc);
                if (nr >= 0 && nr < n && nc >= 0 && nc < n && visited.find(key) == visited.end()) {
                    visited.insert(key);
                    heap.push({max(time, grid[nr][nc]), nr, nc});
                }
            }
        }
        
        return -1;
    }
};
