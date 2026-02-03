/*
 * Problem: Strange Printer II
 * Difficulty: Hard
 * Tags: array, graph, sort
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <queue>

using namespace std;

class Solution {
public:
    bool isPrintable(vector<vector<int>>& targetGrid) {
        int m = targetGrid.size();
        int n = targetGrid[0].size();
        unordered_set<int> colors;
        for (auto& row : targetGrid) {
            for (int cell : row) {
                colors.insert(cell);
            }
        }
        
        unordered_map<int, vector<int>> bounds;
        for (int color : colors) {
            int minR = INT_MAX, maxR = -1;
            int minC = INT_MAX, maxC = -1;
            for (int i = 0; i < m; i++) {
                for (int j = 0; j < n; j++) {
                    if (targetGrid[i][j] == color) {
                        minR = min(minR, i);
                        maxR = max(maxR, i);
                        minC = min(minC, j);
                        maxC = max(maxC, j);
                    }
                }
            }
            bounds[color] = {minR, maxR, minC, maxC};
        }
        
        unordered_map<int, unordered_set<int>> graph;
        for (int color : colors) {
            graph[color] = unordered_set<int>();
        }
        
        for (int color : colors) {
            auto& b = bounds[color];
            for (int i = b[0]; i <= b[1]; i++) {
                for (int j = b[2]; j <= b[3]; j++) {
                    int other = targetGrid[i][j];
                    if (other != color) {
                        graph[other].insert(color);
                    }
                }
            }
        }
        
        unordered_map<int, int> inDegree;
        for (int color : colors) {
            inDegree[color] = 0;
        }
        
        for (int color : colors) {
            for (int neighbor : graph[color]) {
                inDegree[neighbor]++;
            }
        }
        
        queue<int> q;
        for (int color : colors) {
            if (inDegree[color] == 0) {
                q.push(color);
            }
        }
        
        int processed = 0;
        while (!q.empty()) {
            int color = q.front();
            q.pop();
            processed++;
            
            for (int neighbor : graph[color]) {
                inDegree[neighbor]--;
                if (inDegree[neighbor] == 0) {
                    q.push(neighbor);
                }
            }
        }
        
        return processed == colors.size();
    }
};