/*
 * Problem: Best Position for a Service Centre
 * Difficulty: Hard
 * Tags: array, math
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

class Solution {
private:
    double dist(double x, double y, vector<vector<int>>& positions) {
        double sum = 0;
        for (auto& pos : positions) {
            double dx = x - pos[0];
            double dy = y - pos[1];
            sum += sqrt(dx * dx + dy * dy);
        }
        return sum;
    }
    
public:
    double getMinDistSum(vector<vector<int>>& positions) {
        int n = positions.size();
        double x = 0, y = 0;
        for (auto& pos : positions) {
            x += pos[0];
            y += pos[1];
        }
        x /= n;
        y /= n;
        
        double step = 100.0;
        double minDist = dist(x, y, positions);
        
        while (step > 1e-6) {
            bool improved = false;
            vector<vector<double>> directions = {{0, step}, {0, -step}, {step, 0}, {-step, 0}};
            
            for (auto& dir : directions) {
                double newX = x + dir[0];
                double newY = y + dir[1];
                double newDist = dist(newX, newY, positions);
                if (newDist < minDist) {
                    minDist = newDist;
                    x = newX;
                    y = newY;
                    improved = true;
                    break;
                }
            }
            
            if (!improved) {
                step /= 2;
            }
        }
        
        return minDist;
    }
};