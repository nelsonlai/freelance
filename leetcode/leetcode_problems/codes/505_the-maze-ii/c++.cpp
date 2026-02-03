/*
 * Problem: The Maze II
 * Difficulty: Medium
 * Tags: array, graph, search, queue, heap
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

#include <vector>
#include <queue>
#include <unordered_map>
#include <string>
#include <climits>

using namespace std;

class Solution {
public:
    int shortestDistance(vector<vector<int>>& maze, vector<int>& start, vector<int>& destination) {
        int m = maze.size(), n = maze[0].size();
        vector<vector<int>> directions = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
        priority_queue<vector<int>, vector<vector<int>>, greater<vector<int>>> heap;
        unordered_map<string, int> distances;
        
        heap.push({0, start[0], start[1]});
        distances[to_string(start[0]) + "," + to_string(start[1])] = 0;
        
        while (!heap.empty()) {
            auto curr = heap.top();
            heap.pop();
            int dist = curr[0], x = curr[1], y = curr[2];
            
            if (x == destination[0] && y == destination[1]) {
                return dist;
            }
            
            string key = to_string(x) + "," + to_string(y);
            if (distances.find(key) != distances.end() && distances[key] < dist) {
                continue;
            }
            
            for (auto& dir : directions) {
                int nx = x, ny = y, steps = 0;
                while (nx + dir[0] >= 0 && nx + dir[0] < m && 
                       ny + dir[1] >= 0 && ny + dir[1] < n && 
                       maze[nx + dir[0]][ny + dir[1]] == 0) {
                    nx += dir[0];
                    ny += dir[1];
                    steps++;
                }
                
                string newKey = to_string(nx) + "," + to_string(ny);
                if (distances.find(newKey) == distances.end() || distances[newKey] > dist + steps) {
                    distances[newKey] = dist + steps;
                    heap.push({dist + steps, nx, ny});
                }
            }
        }
        
        return -1;
    }
};