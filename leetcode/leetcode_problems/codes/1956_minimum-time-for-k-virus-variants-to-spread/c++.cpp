/*
 * Problem: Minimum Time For K Virus Variants to Spread
 * Difficulty: Hard
 * Tags: array, math, search, binary search, geometry
 * 
 * Approach: Binary search on time, check if k points can be covered by circles
 * Time Complexity: O(n^2 * log(max_time))
 * Space Complexity: O(1)
 */

#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

class Solution {
private:
    bool canCover(vector<vector<int>>& points, int k, int t) {
        int n = points.size();
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                // Try circle centered at midpoint of points[i] and points[j]
                double cx = (points[i][0] + points[j][0]) / 2.0;
                double cy = (points[i][1] + points[j][1]) / 2.0;
                int count = 0;
                
                for (auto& point : points) {
                    double dist = sqrt(
                        pow(point[0] - cx, 2) + pow(point[1] - cy, 2)
                    );
                    if (dist <= t) {
                        count++;
                    }
                }
                
                if (count >= k) {
                    return true;
                }
            }
        }
        return false;
    }
    
public:
    int minDayskVariants(vector<vector<int>>& points, int k) {
        int left = 0, right = 1e9;
        int result = right;
        
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (canCover(points, k, mid)) {
                result = mid;
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        }
        
        return result;
    }
};
