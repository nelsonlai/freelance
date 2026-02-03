/**
 * Problem: Robot Bounded In Circle
 * Difficulty: Medium
 * Tags: string, math
 * 
 * Approach: After one cycle, if robot returns to origin or faces different direction, it's bounded
 * Time Complexity: O(n) where n is instructions length
 * Space Complexity: O(1)
 */

class Solution {
    public boolean isRobotBounded(String instructions) {
        int x = 0, y = 0;
        int dx = 0, dy = 1; // facing north
        
        for (char instruction : instructions.toCharArray()) {
            if (instruction == 'G') {
                x += dx;
                y += dy;
            } else if (instruction == 'L') {
                int temp = dx;
                dx = -dy;
                dy = temp;
            } else { // 'R'
                int temp = dx;
                dx = dy;
                dy = -temp;
            }
        }
        
        // Bounded if returns to origin or doesn't face north
        return (x == 0 && y == 0) || (dx != 0 || dy != 1);
    }
}