/*
 * Problem: Maximum Distance in Arrays
 * Difficulty: Medium
 * Tags: array, greedy, sort
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

class Solution {
public:
    int maxDistance(vector<vector<int>>& arrays) {
        int minVal = arrays[0][0];
        int maxVal = arrays[0].back();
        int result = 0;
        
        for (int i = 1; i < arrays.size(); i++) {
            result = max(result, max(abs(arrays[i].back() - minVal),
                                    abs(maxVal - arrays[i][0])));
            minVal = min(minVal, arrays[i][0]);
            maxVal = max(maxVal, arrays[i].back());
        }
        
        return result;
    }
};