/*
 * Problem: Maximum Number of Darts Inside of a Circular Dartboard
 * Difficulty: Hard
 * Tags: array, math
 * 
 * Approach: For each pair of points, find circles containing them, check all points
 * Time Complexity: O(n^3) where n is number of darts
 * Space Complexity: O(1)
 */

#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

class Solution {
public:
    int numPoints(vector<vector<int>>& darts, int r) {
        int n = darts.size();
        int maxCount = 1;
        
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                double x1 = darts[i][0], y1 = darts[i][1];
                double x2 = darts[j][0], y2 = darts[j][1];
                double dx = x2 - x1, dy = y2 - y1;
                double dist = sqrt(dx * dx + dy * dy);
                
                if (dist > 2 * r) {
                    continue;
                }
                
                double midX = (x1 + x2) / 2, midY = (y1 + y2) / 2;
                double h = sqrt(r * r - (dist / 2) * (dist / 2));
                
                for (int sign = -1; sign <= 1; sign += 2) {
                    double centerX = midX - sign * h * dy / dist;
                    double centerY = midY + sign * h * dx / dist;
                    
                    int count = 0;
                    for (auto& dart : darts) {
                        double dx2 = dart[0] - centerX;
                        double dy2 = dart[1] - centerY;
                        if (dx2 * dx2 + dy2 * dy2 <= r * r + 1e-9) {
                            count++;
                        }
                    }
                    maxCount = max(maxCount, count);
                }
            }
        }
        
        return maxCount;
    }
};