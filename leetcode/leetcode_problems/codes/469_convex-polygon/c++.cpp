/*
 * Problem: Convex Polygon
 * Difficulty: Medium
 * Tags: array, math
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

#include <vector>

using namespace std;

class Solution {
private:
    long long crossProduct(vector<int>& o, vector<int>& a, vector<int>& b) {
        return (long long)(a[0] - o[0]) * (b[1] - o[1]) - 
               (long long)(a[1] - o[1]) * (b[0] - o[0]);
    }

public:
    bool isConvex(vector<vector<int>>& points) {
        int n = points.size();
        if (n < 3) {
            return false;
        }
        
        long long prev = 0;
        for (int i = 0; i < n; i++) {
            long long curr = crossProduct(points[i], points[(i+1)%n], points[(i+2)%n]);
            if (curr != 0) {
                if (prev * curr < 0) {
                    return false;
                }
                prev = curr;
            }
        }
        
        return true;
    }
};