/*
 * Problem: Line Reflection
 * Difficulty: Medium
 * Tags: array, math, hash
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) for hash map
 */

#include <vector>
#include <unordered_set>
#include <algorithm>
#include <climits>

using namespace std;

class Solution {
public:
    bool isReflected(vector<vector<int>>& points) {
        if (points.empty()) {
            return true;
        }
        
        unordered_set<string> pointSet;
        int minX = INT_MAX;
        int maxX = INT_MIN;
        
        for (auto& point : points) {
            minX = min(minX, point[0]);
            maxX = max(maxX, point[0]);
            pointSet.insert(to_string(point[0]) + "," + to_string(point[1]));
        }
        
        double midX = (minX + maxX) / 2.0;
        
        for (auto& point : points) {
            double reflectedX = 2 * midX - point[0];
            string reflected = to_string((int)reflectedX) + "," + to_string(point[1]);
            if (pointSet.find(reflected) == pointSet.end()) {
                return false;
            }
        }
        
        return true;
    }
};