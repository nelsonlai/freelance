/*
 * Problem: Minimum Area Rectangle
 * Difficulty: Medium
 * Tags: array, math, hash, sort
 * 
 * Approach: Group points by x-coordinate, for each pair of x-coordinates find common y-coordinates
 * Time Complexity: O(n^2) in worst case
 * Space Complexity: O(n) for storing points
 */

#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <climits>

using namespace std;

class Solution {
public:
    int minAreaRect(vector<vector<int>>& points) {
        unordered_map<int, unordered_set<int>> xToY;
        for (auto& point : points) {
            xToY[point[0]].insert(point[1]);
        }
        
        vector<int> xCoords;
        for (auto& pair : xToY) {
            xCoords.push_back(pair.first);
        }
        sort(xCoords.begin(), xCoords.end());
        
        int minArea = INT_MAX;
        for (int i = 0; i < xCoords.size(); i++) {
            for (int j = i + 1; j < xCoords.size(); j++) {
                int x1 = xCoords[i], x2 = xCoords[j];
                unordered_set<int> commonY = xToY[x1];
                for (auto it = commonY.begin(); it != commonY.end();) {
                    if (xToY[x2].find(*it) == xToY[x2].end()) {
                        it = commonY.erase(it);
                    } else {
                        ++it;
                    }
                }
                
                if (commonY.size() >= 2) {
                    vector<int> sortedY(commonY.begin(), commonY.end());
                    sort(sortedY.begin(), sortedY.end());
                    for (int k = 0; k < sortedY.size() - 1; k++) {
                        int height = sortedY[k + 1] - sortedY[k];
                        int area = abs(x2 - x1) * height;
                        minArea = min(minArea, area);
                    }
                }
            }
        }
        
        return minArea == INT_MAX ? 0 : minArea;
    }
};