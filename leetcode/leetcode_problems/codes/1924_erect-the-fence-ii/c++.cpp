/*
 * Problem: Erect the Fence II
 * Difficulty: Hard
 * Tags: array, math, geometry, smallest enclosing circle
 * 
 * Approach: Find smallest circle enclosing all points (Welzl's algorithm)
 * Time Complexity: O(n) expected
 * Space Complexity: O(n)
 */

#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

class Solution {
private:
    double dist(vector<int>& p1, vector<int>& p2) {
        double dx = p1[0] - p2[0];
        double dy = p1[1] - p2[1];
        return sqrt(dx * dx + dy * dy);
    }
    
    double dist(vector<double>& p1, vector<int>& p2) {
        double dx = p1[0] - p2[0];
        double dy = p1[1] - p2[1];
        return sqrt(dx * dx + dy * dy);
    }
    
    vector<double> circleFrom2Points(vector<int>& p1, vector<int>& p2) {
        double cx = (p1[0] + p2[0]) / 2.0;
        double cy = (p1[1] + p2[1]) / 2.0;
        double r = dist(p1, p2) / 2.0;
        return {cx, cy, r};
    }
    
    vector<double> circleFrom3Points(vector<int>& p1, vector<int>& p2, vector<int>& p3) {
        double ax = p1[0], ay = p1[1];
        double bx = p2[0], by = p2[1];
        double cx = p3[0], cy = p3[1];
        
        double d = 2 * (ax * (by - cy) + bx * (cy - ay) + cx * (ay - by));
        if (abs(d) < 1e-9) {
            return {};
        }
        
        double ux = ((ax*ax + ay*ay) * (by - cy) + (bx*bx + by*by) * (cy - ay) + 
                     (cx*cx + cy*cy) * (ay - by)) / d;
        double uy = ((ax*ax + ay*ay) * (cx - bx) + (bx*bx + by*by) * (ax - cx) + 
                     (cx*cx + cy*cy) * (bx - ax)) / d;
        
        double r = dist({ux, uy}, p1);
        return {ux, uy, r};
    }
    
    bool isInside(vector<double>& circle, vector<int>& p) {
        if (circle.empty()) return false;
        double cx = circle[0], cy = circle[1], r = circle[2];
        return dist({cx, cy}, p) <= r + 1e-9;
    }
    
    vector<double> welzl(vector<vector<int>>& points, vector<vector<int>>& R) {
        if (points.empty() || R.size() == 3) {
            if (R.empty()) {
                return {};
            } else if (R.size() == 1) {
                return {(double)R[0][0], (double)R[0][1], 0.0};
            } else if (R.size() == 2) {
                return circleFrom2Points(R[0], R[1]);
            } else {
                return circleFrom3Points(R[0], R[1], R[2]);
            }
        }
        
        vector<int> p = points[0];
        vector<vector<int>> remaining(points.begin() + 1, points.end());
        vector<double> circle = welzl(remaining, R);
        
        if (circle.empty() || !isInside(circle, p)) {
            R.push_back(p);
            circle = welzl(remaining, R);
            R.pop_back();
        }
        
        return circle;
    }
    
public:
    vector<double> outerTrees(vector<vector<int>>& trees) {
        if (trees.size() == 1) {
            return {(double)trees[0][0], (double)trees[0][1], 0.0};
        }
        
        vector<vector<int>> R;
        vector<double> circle = welzl(trees, R);
        
        return {
            round(circle[0] * 100000.0) / 100000.0,
            round(circle[1] * 100000.0) / 100000.0,
            round(circle[2] * 100000.0) / 100000.0
        };
    }
};