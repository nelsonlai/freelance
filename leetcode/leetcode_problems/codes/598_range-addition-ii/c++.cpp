/*
 * Problem: Range Addition II
 * Difficulty: Easy
 * Tags: array, math
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

#include <vector>
#include <climits>

using namespace std;

class Solution {
public:
    int maxCount(int m, int n, vector<vector<int>>& ops) {
        if (ops.empty()) {
            return m * n;
        }
        
        int minRow = INT_MAX;
        int minCol = INT_MAX;
        
        for (auto& op : ops) {
            minRow = min(minRow, op[0]);
            minCol = min(minCol, op[1]);
        }
        
        return minRow * minCol;
    }
};