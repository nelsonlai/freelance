/*
 * Problem: The Maze
 * Difficulty: Medium
 * Tags: array, search
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

#include <vector>
#include <queue>
#include <unordered_set>
#include <string>

using namespace std;

class Solution {
public:
    bool hasPath(vector<vector<int>>& maze, vector<int>& start, vector<int>& destination) {
        int m = maze.size(), n = maze[0].size();
        vector<vector<int>> directions = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
        unordered_set<string> visited;
        queue<vector<int>> q;
        q.push(start);
        visited.insert(to_string(start[0]) + "," + to_string(start[1]));
        
        while (!q.empty()) {
            vector<int> curr = q.front();
            q.pop();
            if (curr[0] == destination[0] && curr[1] == destination[1]) {
                return true;
            }
            
            for (auto& dir : directions) {
                int x = curr[0], y = curr[1];
                while (x + dir[0] >= 0 && x + dir[0] < m && 
                       y + dir[1] >= 0 && y + dir[1] < n && 
                       maze[x + dir[0]][y + dir[1]] == 0) {
                    x += dir[0];
                    y += dir[1];
                }
                
                string key = to_string(x) + "," + to_string(y);
                if (visited.find(key) == visited.end()) {
                    visited.insert(key);
                    q.push({x, y});
                }
            }
        }
        
        return false;
    }
};