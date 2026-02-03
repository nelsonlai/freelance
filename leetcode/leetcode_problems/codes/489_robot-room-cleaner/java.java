/**
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
 * interface Robot {
 *     // Returns true if the cell in front is open and robot moves into the cell.
 *     // Returns false if the cell in front is blocked and robot stays in the current cell.
 *     public boolean move();
 *
 *     // Robot will stay in the same cell after calling turnLeft/turnRight.
 *     // Each turn will be 90 degrees.
 *     public void turnLeft();
 *     public void turnRight();
 *
 *     // Clean the current cell.
 *     public void clean();
 * }
 */

import java.util.*;

class Solution {
    private int[][] directions = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
    private Set<String> visited = new HashSet<>();
    
    public void cleanRoom(Robot robot) {
        backtrack(0, 0, 0, robot);
    }
    
    private void backtrack(int row, int col, int d, Robot robot) {
        visited.add(row + "," + col);
        robot.clean();
        
        for (int i = 0; i < 4; i++) {
            int newD = (d + i) % 4;
            int newRow = row + directions[newD][0];
            int newCol = col + directions[newD][1];
            
            if (!visited.contains(newRow + "," + newCol) && robot.move()) {
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
}