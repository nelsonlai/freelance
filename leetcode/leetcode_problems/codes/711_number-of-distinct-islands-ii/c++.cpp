#include <vector>
#include <string>
#include <set>
#include <stack>
#include <algorithm>

using namespace std;

class Solution {
private:
    vector<vector<int>> dfs(vector<vector<int>>& grid, int i, int j) {
        int m = grid.size(), n = grid[0].size();
        vector<vector<int>> shape;
        stack<vector<int>> st;
        st.push({i, j});
        grid[i][j] = 0;
        
        while (!st.empty()) {
            vector<int> curr = st.top();
            st.pop();
            shape.push_back({curr[0] - i, curr[1] - j});
            vector<vector<int>> dirs = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
            for (auto& dir : dirs) {
                int nr = curr[0] + dir[0], nc = curr[1] + dir[1];
                if (nr >= 0 && nr < m && nc >= 0 && nc < n && grid[nr][nc] == 1) {
                    grid[nr][nc] = 0;
                    st.push({nr, nc});
                }
            }
        }
        return shape;
    }
    
    string normalize(vector<vector<int>> shape) {
        vector<vector<vector<int>>> rotations;
        rotations.push_back(shape);
        rotations.push_back(transform(shape, [](int x, int y) { return vector<int>{-x, y}; }));
        rotations.push_back(transform(shape, [](int x, int y) { return vector<int>{x, -y}; }));
        rotations.push_back(transform(shape, [](int x, int y) { return vector<int>{-x, -y}; }));
        rotations.push_back(transform(shape, [](int x, int y) { return vector<int>{y, x}; }));
        rotations.push_back(transform(shape, [](int x, int y) { return vector<int>{-y, x}; }));
        rotations.push_back(transform(shape, [](int x, int y) { return vector<int>{y, -x}; }));
        rotations.push_back(transform(shape, [](int x, int y) { return vector<int>{-y, -x}; }));
        
        for (auto& rot : rotations) {
            sort(rot.begin(), rot.end());
        }
        
        sort(rotations.begin(), rotations.end());
        
        auto& first = rotations[0];
        if (first.empty()) return "";
        int minX = first[0][0], minY = first[0][1];
        string result = "";
        for (auto& p : first) {
            result += to_string(p[0] - minX) + "," + to_string(p[1] - minY) + ";";
        }
        return result;
    }
    
    vector<vector<int>> transform(vector<vector<int>> shape, function<vector<int>(int, int)> func) {
        vector<vector<int>> result;
        for (auto& p : shape) {
            result.push_back(func(p[0], p[1]));
        }
        return result;
    }

public:
    int numDistinctIslands2(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size();
        set<string> seen;
        
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 1) {
                    auto shape = dfs(grid, i, j);
                    seen.insert(normalize(shape));
                }
            }
        }
        
        return seen.size();
    }
};
