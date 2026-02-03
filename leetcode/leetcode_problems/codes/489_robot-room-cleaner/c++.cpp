/*
 * Problem: Robot Room Cleaner
 * Difficulty: Hard
 * Tags: tree
 * 
 * Approach: DFS or BFS traversal
 * Time Complexity: O(n) where n is number of nodes
 * Space Complexity: O(h) for recursion stack where h is height
 */

/**
 * // This is the robot's control interface.
 * // You should not implement it, or speculate about its implementation
 * class Robot {
 *   public:
 *     // Returns true if the cell in front is open and robot moves into the cell.
 *     // Returns false if the cell in front is blocked and robot stays in the current cell.
 *     bool move();
 *
 *     // Robot will stay in the same cell after calling turnLeft/turnRight.
 *     // Each turn will be 90 degrees.
 *     void turnLeft();
 *     void turnRight();
 *
 *     // Clean the current cell.
 *     void clean();
 * };
 */

#include <unordered_set>
#include <string>

using namespace std;

class Solution {
private:
    vector<vector<int>> directions = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
    unordered_set<string> visited;
    
    void backtrack(int row, int col, int d, Robot& robot) {
        visited.insert(to_string(row) + "," + to_string(col));
        robot.clean();
        
        for (int i = 0; i < 4; i++) {
            int newD = (d + i) % 4;
            int newRow = row + directions[newD][0];
            int newCol = col + directions[newD][1];
            
            string key = to_string(newRow) + "," + to_string(newCol);
            if (visited.find(key) == visited.end() && robot.move()) {
                backtrack(newRow, newCol, newD, robot);
                robot.turnRight();
                robot.turnRight();
                robot.move();
                robot.turnRight();
                robot.turnRight();
            }
            robot.turnRight();
        }
    }

public:
    void cleanRoom(Robot& robot) {
        backtrack(0, 0, 0, robot);
    }
};