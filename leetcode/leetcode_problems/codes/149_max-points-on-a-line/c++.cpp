/*
 * Problem: Max Points on a Line
 * Difficulty: Hard
 * Tags: array, math, hash
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) for hash map
 */

#include <unordered_map>
#include <string>
#include <algorithm>

using namespace std;

class Solution {
public:
    int maxPoints(vector<vector<int>>& points) {
        if (points.size() <= 2) {
            return points.size();
        }
        
        int maxPoints = 0;
        
        for (int i = 0; i < points.size(); i++) {
            unordered_map<string, int> slopeCount;
            int samePoint = 1;
            
            for (int j = i + 1; j < points.size(); j++) {
                int x1 = points[i][0], y1 = points[i][1];
                int x2 = points[j][0], y2 = points[j][1];
                
                if (x1 == x2 && y1 == y2) {
                    samePoint++;
                } else {
                    int dx = x2 - x1;
                    int dy = y2 - y1;
                    int g = gcd(dx, dy);
                    string slope = to_string(dx / g) + "/" + to_string(dy / g);
                    slopeCount[slope]++;
                }
            }
            
            int currentMax = samePoint;
            for (auto& p : slopeCount) {
                currentMax = max(currentMax, samePoint + p.second);
            }
            maxPoints = max(maxPoints, currentMax);
        }
        
        return maxPoints;
    }
    
private:
    int gcd(int a, int b) {
        return b == 0 ? a : gcd(b, a % b);
    }
};