/**
 * Problem: Circle and Rectangle Overlapping
 * Difficulty: Medium
 * Tags: math
 * 
 * Approach: Find closest point on rectangle to circle center, check if distance <= radius
 * Time Complexity: O(1)
 * Space Complexity: O(1)
 */

class Solution {
    public boolean checkOverlap(int radius, int xCenter, int yCenter, int x1, int y1, int x2, int y2) {
        int closestX = Math.max(x1, Math.min(xCenter, x2));
        int closestY = Math.max(y1, Math.min(yCenter, y2));
        
        int dx = xCenter - closestX;
        int dy = yCenter - closestY;
        
        return dx * dx + dy * dy <= radius * radius;
    }
}