/*
 * Problem: Circle and Rectangle Overlapping
 * Difficulty: Medium
 * Tags: math
 * 
 * Approach: Find closest point on rectangle to circle center, check if distance <= radius
 * Time Complexity: O(1)
 * Space Complexity: O(1)
 */

#include <algorithm>

using namespace std;

class Solution {
public:
    bool checkOverlap(int radius, int xCenter, int yCenter, int x1, int y1, int x2, int y2) {
        int closestX = max(x1, min(xCenter, x2));
        int closestY = max(y1, min(yCenter, y2));
        
        int dx = xCenter - closestX;
        int dy = yCenter - closestY;
        
        return dx * dx + dy * dy <= radius * radius;
    }
};