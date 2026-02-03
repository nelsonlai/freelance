/*
 * Problem: The Maze III
 * Difficulty: Hard
 * Tags: array, string, graph, search, queue, heap
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

#include <vector>
#include <string>
#include <queue>
#include <unordered_map>
#include <climits>

using namespace std;

class Solution {
public:
    string findShortestWay(vector<vector<int>>& maze, vector<int>& ball, vector<int>& hole) {
        int m = maze.size(), n = maze[0].size();
        vector<vector<int>> directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
        vector<string> dirNames = {"u", "d", "l", "r"};
        
        priority_queue<vector<int>, vector<vector<int>>, greater<vector<int>>> heap;
        unordered_map<string, int> visited;
        
        heap.push({0, ball[0], ball[1], 0});
        visited[to_string(ball[0]) + "," + to_string(ball[1])] = 0;
        
        while (!heap.empty()) {
            auto curr = heap.top();
            heap.pop();
            int dist = curr[0], x = curr[1], y = curr[2], pathCode = curr[3];
            
            if (x == hole[0] && y == hole[1]) {
                string path = "";
                int code = pathCode;
                while (code > 0) {
                    path = dirNames[(code - 1) % 4] + path;
                    code = (code - 1) / 4;
                }
                return path;
            }
            
            string key = to_string(x) + "," + to_string(y);
            if (visited.find(key) != visited.end() && visited[key] < dist) {
                continue;
            }
            visited[key] = dist;
            
            for (int i = 0; i < 4; i++) {
                auto dir = directions[i];
                int nx = x, ny = y, steps = 0;
                while (nx + dir[0] >= 0 && nx + dir[0] < m && 
                       ny + dir[1] >= 0 && ny + dir[1] < n && 
                       maze[nx + dir[0]][ny + dir[1]] == 0) {
                    nx += dir[0];
                    ny += dir[1];
                    steps++;
                    if (nx == hole[0] && ny == hole[1]) {
                        break;
                    }
                }
                
                string newKey = to_string(nx) + "," + to_string(ny);
                if (visited.find(newKey) == visited.end() || visited[newKey] > dist + steps) {
                    int newPathCode = pathCode * 4 + i + 1;
                    heap.push({dist + steps, nx, ny, newPathCode});
                }
            }
        }
        
        return "impossible";
    }
};