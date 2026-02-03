#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

class Solution {
private:
    double area(vector<int>& p1, vector<int>& p2, vector<int>& p3) {
        return abs(p1[0]*(p2[1]-p3[1]) + p2[0]*(p3[1]-p1[1]) + p3[0]*(p1[1]-p2[1])) / 2.0;
    }

public:
    double largestTriangleArea(vector<vector<int>>& points) {
        double maxArea = 0;
        int n = points.size();
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                for (int k = j + 1; k < n; k++) {
                    maxArea = max(maxArea, area(points[i], points[j], points[k]));
                }
            }
        }
        return maxArea;
    }
};
