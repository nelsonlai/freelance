/*
 * Problem: Perfect Rectangle
 * Difficulty: Hard
 * Tags: array, math, hash
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) for hash map
 */

#include <vector>
#include <unordered_map>
#include <set>
#include <climits>

using namespace std;

class Solution {
public:
    bool isRectangleCover(vector<vector<int>>& rectangles) {
        unordered_map<string, int> corners;
        long area = 0;
        int minX = INT_MAX, minY = INT_MAX;
        int maxX = INT_MIN, maxY = INT_MIN;
        
        for (auto& rect : rectangles) {
            int x1 = rect[0], y1 = rect[1], x2 = rect[2], y2 = rect[3];
            minX = min(minX, x1);
            minY = min(minY, y1);
            maxX = max(maxX, x2);
            maxY = max(maxY, y2);
            
            area += (long)(x2 - x1) * (y2 - y1);
            
            string points[] = {to_string(x1) + "," + to_string(y1),
                              to_string(x1) + "," + to_string(y2),
                              to_string(x2) + "," + to_string(y1),
                              to_string(x2) + "," + to_string(y2)};
            for (string point : points) {
                corners[point]++;
            }
        }
        
        long expectedArea = (long)(maxX - minX) * (maxY - minY);
        if (area != expectedArea) {
            return false;
        }
        
        set<string> cornerPoints = {to_string(minX) + "," + to_string(minY),
                                    to_string(minX) + "," + to_string(maxY),
                                    to_string(maxX) + "," + to_string(minY),
                                    to_string(maxX) + "," + to_string(maxY)};
        
        for (auto& entry : corners) {
            int count = entry.second;
            if (cornerPoints.find(entry.first) != cornerPoints.end()) {
                if (count != 1) {
                    return false;
                }
            } else {
                if (count % 2 != 0) {
                    return false;
                }
            }
        }
        
        return true;
    }
};