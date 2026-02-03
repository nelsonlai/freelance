/*
 * Problem: Valid Square
 * Difficulty: Medium
 * Tags: math
 * 
 * Approach: Optimized algorithm based on problem constraints
 * Time Complexity: O(n) to O(n^2) depending on approach
 * Space Complexity: O(1) to O(n) depending on approach
 */

#include <vector>
#include <algorithm>

using namespace std;

class Solution {
private:
    int dist(vector<int>& p, vector<int>& q) {
        return (p[0] - q[0]) * (p[0] - q[0]) + (p[1] - q[1]) * (p[1] - q[1]);
    }

public:
    bool validSquare(vector<int>& p1, vector<int>& p2, vector<int>& p3, vector<int>& p4) {
        vector<vector<int>> points = {p1, p2, p3, p4};
        vector<int> distances;
        
        for (int i = 0; i < 4; i++) {
            for (int j = i + 1; j < 4; j++) {
                distances.push_back(dist(points[i], points[j]));
            }
        }
        
        sort(distances.begin(), distances.end());
        
        return distances[0] > 0 &&
               distances[0] == distances[1] &&
               distances[1] == distances[2] &&
               distances[2] == distances[3] &&
               distances[4] == distances[5];
    }
};