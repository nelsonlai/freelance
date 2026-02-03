/*
 * Problem: Trapping Rain Water II
 * Difficulty: Hard
 * Tags: array, search, queue, heap
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

#include <vector>
#include <queue>
#include <climits>

using namespace std;

class Solution {
public:
    int trapRainWater(vector<vector<int>>& heightMap) {
        if (heightMap.empty() || heightMap[0].empty()) {
            return 0;
        }
        
        int m = heightMap.size();
        int n = heightMap[0].size();
        vector<vector<bool>> visited(m, vector<bool>(n, false));
        priority_queue<vector<int>, vector<vector<int>>, greater<vector<int>>> heap;
        
        for (int i = 0; i < m; i++) {
            heap.push({heightMap[i][0], i, 0});
            heap.push({heightMap[i][n-1], i, n-1});
            visited[i][0] = true;
            visited[i][n-1] = true;
        }
        
        for (int j = 0; j < n; j++) {
            heap.push({heightMap[0][j], 0, j});
            heap.push({heightMap[m-1][j], m-1, j});
            visited[0][j] = true;
            visited[m-1][j] = true;
        }
        
        vector<vector<int>> directions = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
        int water = 0;
        
        while (!heap.empty()) {
            vector<int> cell = heap.top();
            heap.pop();
            int height = cell[0];
            int i = cell[1];
            int j = cell[2];
            
            for (auto& dir : directions) {
                int ni = i + dir[0];
                int nj = j + dir[1];
                if (ni >= 0 && ni < m && nj >= 0 && nj < n && !visited[ni][nj]) {
                    visited[ni][nj] = true;
                    water += max(0, height - heightMap[ni][nj]);
                    heap.push({max(height, heightMap[ni][nj]), ni, nj});
                }
            }
        }
        
        return water;
    }
};