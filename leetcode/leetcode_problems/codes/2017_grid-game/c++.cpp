/*
 * Problem: Grid Game
 * Difficulty: Medium
 * Tags: array
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
    long long gridGame(vector<vector<int>>& grid) {
        int n = grid[0].size();
        long long topSum = 0;
        for (int num : grid[0]) {
            topSum += num;
        }
        long long bottomSum = 0;
        long long result = LLONG_MAX;
        
        for (int i = 0; i < n; i++) {
            topSum -= grid[0][i];
            result = min(result, max(topSum, bottomSum));
            bottomSum += grid[1][i];
        }
        
        return result;
    }
};