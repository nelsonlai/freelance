/*
 * Problem: Generate Random Point in a Circle
 * Difficulty: Medium
 * Tags: array, dp, math
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) or O(n * m) for DP table
 */

#include <vector>
#include <random>
#include <cmath>

using namespace std;

class Solution {
private:
    double radius;
    double xCenter;
    double yCenter;
    mt19937 gen;
    uniform_real_distribution<double> dis;

public:
    Solution(double radius, double x_center, double y_center) 
        : radius(radius), xCenter(x_center), yCenter(y_center), 
          gen(random_device{}()), dis(0.0, 1.0) {
    }
    
    vector<double> randPoint() {
        double angle = dis(gen) * 2 * M_PI;
        double r = radius * sqrt(dis(gen));
        double x = xCenter + r * cos(angle);
        double y = yCenter + r * sin(angle);
        return {x, y};
    }
};

/**
 * Your Solution object will be instantiated and called as such:
 * Solution* obj = new Solution(radius, x_center, y_center);
 * vector<double> param_1 = obj->randPoint();
 */