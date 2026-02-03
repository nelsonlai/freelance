/*
 * Problem: Number of Boomerangs
 * Difficulty: Medium
 * Tags: array, math, hash
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) for hash map
 */

#include <vector>
#include <unordered_map>

using namespace std;

class Solution {
public:
    int numberOfBoomerangs(vector<vector<int>>& points) {
        int total = 0;
        for (int i = 0; i < points.size(); i++) {
            unordered_map<int, int> distCount;
            for (int j = 0; j < points.size(); j++) {
                if (i != j) {
                    int dx = points[i][0] - points[j][0];
                    int dy = points[i][1] - points[j][1];
                    int dist = dx * dx + dy * dy;
                    distCount[dist]++;
                }
            }
            for (auto& entry : distCount) {
                total += entry.second * (entry.second - 1);
            }
        }
        return total;
    }
};