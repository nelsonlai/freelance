#include <vector>
#include <string>
#include <queue>
#include <unordered_set>

using namespace std;

class Solution {
public:
    int shortestPathAllKeys(vector<string>& grid) {
        int m = grid.size(), n = grid[0].length();
        int startR = -1, startC = -1;
        int keys = 0;
        
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                char c = grid[i][j];
                if (c == '@') {
                    startR = i;
                    startC = j;
                } else if (islower(c)) {
                    keys |= 1 << (c - 'a');
                }
            }
        }
        
        queue<vector<int>> q;
        q.push({startR, startC, 0, 0});
        unordered_set<string> visited;
        visited.insert(to_string(startR) + "," + to_string(startC) + ",0");
        
        while (!q.empty()) {
            auto curr = q.front();
            q.pop();
            int r = curr[0], c = curr[1], collected = curr[2], steps = curr[3];
            
            if (collected == keys) {
                return steps;
            }
            
            vector<vector<int>> dirs = {{0,1}, {1,0}, {0,-1}, {-1,0}};
            for (auto& dir : dirs) {
                int nr = r + dir[0], nc = c + dir[1];
                if (nr >= 0 && nr < m && nc >= 0 && nc < n && grid[nr][nc] != '#') {
                    char cell = grid[nr][nc];
                    int newCollected = collected;
                    
                    if (islower(cell)) {
                        newCollected |= 1 << (cell - 'a');
                    } else if (isupper(cell)) {
                        if ((collected & (1 << (cell - 'A'))) == 0) {
                            continue;
                        }
                    }
                    
                    string state = to_string(nr) + "," + to_string(nc) + "," + to_string(newCollected);
                    if (visited.find(state) == visited.end()) {
                        visited.insert(state);
                        q.push({nr, nc, newCollected, steps + 1});
                    }
                }
            }
        }
        return -1;
    }
};
