/*
 * Problem: Cut Off Trees for Golf Event
 * Difficulty: Hard
 * Tags: array, tree, search, queue, heap
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(h) for recursion stack where h is height
 */

#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

class Solution {
private:
    int bfs(vector<vector<int>>& forest, vector<int>& start, vector<int>& end) {
        int m = forest.size();
        int n = forest[0].size();
        queue<vector<int>> q;
        vector<vector<bool>> seen(m, vector<bool>(n, false));
        q.push({start[0], start[1], 0});
        seen[start[0]][start[1]] = true;
        
        vector<vector<int>> dirs = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
        
        while (!q.empty()) {
            auto curr = q.front();
            q.pop();
            int x = curr[0], y = curr[1], steps = curr[2];
            
            if (x == end[0] && y == end[1]) {
                return steps;
            }
            
            for (auto& dir : dirs) {
                int nx = x + dir[0];
                int ny = y + dir[1];
                if (nx >= 0 && nx < m && ny >= 0 && ny < n && 
                    !seen[nx][ny] && forest[nx][ny] != 0) {
                    seen[nx][ny] = true;
                    q.push({nx, ny, steps + 1});
                }
            }
        }
        
        return -1;
    }

public:
    int cutOffTree(vector<vector<int>>& forest) {
        vector<vector<int>> trees;
        for (int i = 0; i < forest.size(); i++) {
            for (int j = 0; j < forest[i].size(); j++) {
                if (forest[i][j] > 1) {
                    trees.push_back({forest[i][j], i, j});
                }
            }
        }
        
        sort(trees.begin(), trees.end());
        
        int result = 0;
        vector<int> start = {0, 0};
        
        for (auto& tree : trees) {
            vector<int> end = {tree[1], tree[2]};
            int steps = bfs(forest, start, end);
            if (steps == -1) {
                return -1;
            }
            result += steps;
            start = end;
        }
        
        return result;
    }
};